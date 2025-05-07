/*
 Copyright 2025 Google LLC

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include "vulkan_command_hierarchy.h"
#include "dive_strings.h"
#include <string>

namespace Dive
{
    VulkanCommandHierarchyCreator::VulkanCommandHierarchyCreator(){}
    bool VulkanCommandHierarchyCreator::CreateTrees(CommandHierarchy *command_hierarchy_ptr,
        const CaptureData      &capture_data,
        std::optional<uint64_t> reserve_size)
    {
        m_command_hierarchy_ptr = command_hierarchy_ptr;
        m_capture_data_ptr = &capture_data;

        // Clear/Reset internal data structures, just in case
        *m_command_hierarchy_ptr = CommandHierarchy();

        if (reserve_size.has_value())
        {
            for (uint32_t topology = 0; topology < (CommandHierarchy::kTopologyTypeCount); ++topology)
            {
                m_node_root_node_index[topology].reserve(*reserve_size);

                m_node_children[topology][0].reserve(*reserve_size);
                m_node_children[topology][1].reserve(*reserve_size);

                m_command_hierarchy_ptr->m_nodes.m_node_type.reserve(*reserve_size);
                m_command_hierarchy_ptr->m_nodes.m_description.reserve(*reserve_size);
                m_command_hierarchy_ptr->m_nodes.m_metadata.reserve(*reserve_size);
            }
        }

        // Add a dummy root node for easier management
        uint64_t root_node_index = AddNode(NodeType::kRootNode, "", 0);
        DIVE_VERIFY(root_node_index == Topology::kRootNodeIndex);

        // Add each engine type to the frame_node
        DiveVector<uint64_t> engine_nodes;
        for (uint32_t engine_type = 0; engine_type < (uint32_t)EngineType::kCount; ++engine_type)
        {
            uint64_t node_index = AddNode(NodeType::kEngineNode, kEngineTypeStrings[engine_type], 0);
            AddChild(CommandHierarchy::kEngineTopology, Topology::kRootNodeIndex, node_index);
        }
        if (!ProcessGfxrSubmits(capture_data.GetGfxrSubmits(), capture_data.GetMemoryManager()))
        {
            return false;
        }
        // Convert the info in m_node_children into VulkanGfxrCommandHierarchy's topologies
        CreateTopologies();

        return true;
    }

    //--------------------------------------------------------------------------------------------------
    uint64_t VulkanCommandHierarchyCreator::AddNode(NodeType                  type,
        std::string             &&desc, char *metadata_ptr, uint32_t      metadata_size)
    {
        uint64_t node_index = m_command_hierarchy_ptr->AddGfxrNode(type, std::move(desc), metadata_ptr, metadata_size);

        for (uint32_t i = 0; i < CommandHierarchy::kTopologyTypeCount; ++i)
        {
            DIVE_ASSERT(m_node_children[i][0].size() == node_index);
            DIVE_ASSERT(m_node_children[i][1].size() == node_index);
            m_node_children[i][0].resize(m_node_children[i][0].size() + 1);
            m_node_children[i][1].resize(m_node_children[i][0].size() + 1);

            m_node_root_node_index[i].resize(m_node_root_node_index[i].size() + 1);
        }
        return node_index;
    }

    //--------------------------------------------------------------------------------------------------
    void VulkanCommandHierarchyCreator::AddChild(CommandHierarchy::TopologyType type,
    uint64_t                       node_index,
    uint64_t                       child_node_index)
    {
        // Store children info into the temporary m_node_children
        // Use this to create the appropriate topology later
        DIVE_ASSERT(node_index < m_node_children[type][0].size());
        m_node_children[type][0][node_index].push_back(child_node_index);
    }

    void VulkanCommandHierarchyCreator::AddSharedChild(CommandHierarchy::TopologyType type,
        uint64_t                       node_index,
        uint64_t                       child_node_index)
    {
        // Store children info into the temporary m_node_children
        // Use this to create the appropriate topology later
        DIVE_ASSERT(node_index < m_node_children[type][1].size());
        m_node_children[type][1][node_index].push_back(child_node_index);
    }

    //--------------------------------------------------------------------------------------------------
    uint64_t VulkanCommandHierarchyCreator::GetChildNodeIndex(CommandHierarchy::TopologyType type,
        uint64_t                       node_index,
        uint64_t child_index) const
    {
        DIVE_ASSERT(node_index < m_node_children[type][0].size());
        DIVE_ASSERT(child_index < m_node_children[type][0][node_index].size());
        return m_node_children[type][0][node_index][child_index];
    }

    //--------------------------------------------------------------------------------------------------
    void VulkanCommandHierarchyCreator::SetSharedChildRootNodeIndex(CommandHierarchy::TopologyType type,
        uint64_t                       node_index,
        uint64_t root_node_index)
    {
        DIVE_ASSERT(node_index < m_node_root_node_index[type].size());
        m_node_root_node_index[type][node_index] = root_node_index;
    }

    //--------------------------------------------------------------------------------------------------
    bool VulkanCommandHierarchyCreator::OnCmd(uint32_t parent_index, DiveAnnotationProcessor::VulkanCommandInfo vk_cmd_info)
    {
        std::ostringstream vk_cmd_string_stream;
        vk_cmd_string_stream << vk_cmd_info.GetVkCmdName();
        if (vk_cmd_info.GetVkCmdName() == "vkBeginCommandBuffer")
        {
            uint64_t cmd_buffer_index = AddNode(NodeType::kPacketNode, vk_cmd_string_stream.str());
            m_cur_command_buffer_node_index = cmd_buffer_index;
            AddChild(CommandHierarchy::TopologyType::kEngineTopology, m_cur_submit_node_index, cmd_buffer_index);
            AddChild(CommandHierarchy::TopologyType::kSubmitTopology, m_cur_submit_node_index, cmd_buffer_index);
        }
        else
        {
            vk_cmd_string_stream << ", Command Buffer Index: " << std::to_string(vk_cmd_info.GetVkCmdIndex());
            uint64_t vk_cmd_index = AddNode(NodeType::kPacketNode, vk_cmd_string_stream.str());
            AddChild(CommandHierarchy::TopologyType::kEngineTopology, m_cur_command_buffer_node_index, vk_cmd_index);
            AddChild(CommandHierarchy::TopologyType::kSubmitTopology, m_cur_command_buffer_node_index, vk_cmd_index);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------------
    void VulkanCommandHierarchyCreator::OnGfxrSubmitStart(uint32_t submit_index, const DiveAnnotationProcessor::SubmitInfo &submit_info)
    {
        std::ostringstream submit_string_stream;
        submit_string_stream << submit_info.GetSubmitText() << ": "<< submit_index;
        submit_string_stream << ", Command Buffer Count: " << std::to_string(submit_info.GetCommandBufferCount());
        // Create submit node
        uint64_t submit_node_index = AddNode(NodeType::kSubmitNode,
                                            submit_string_stream.str());
        // Add submit node as child to the appropriate engine node
        uint64_t engine_node_index = GetChildNodeIndex(CommandHierarchy::kEngineTopology, Topology::kRootNodeIndex, 0);
        AddChild(CommandHierarchy::kEngineTopology, engine_node_index, submit_node_index);

        // Add submit node to the other topologies as children to the root node
        AddChild(CommandHierarchy::kSubmitTopology, Topology::kRootNodeIndex, submit_node_index);
        AddChild(CommandHierarchy::kAllEventTopology, Topology::kRootNodeIndex, submit_node_index);
        m_cur_submit_node_index = submit_node_index;
    }

    //--------------------------------------------------------------------------------------------------
    void VulkanCommandHierarchyCreator::OnGfxrSubmitEnd(uint32_t submit_index, const DiveAnnotationProcessor::SubmitInfo &submit_info)
    {
    }
    void VulkanCommandHierarchyCreator::CreateTopologies()
    {
        uint64_t total_num_children[CommandHierarchy::kTopologyTypeCount] = {};

        CommandHierarchy::TopologyType src_topology = CommandHierarchy::kAllEventTopology;
        CommandHierarchy::TopologyType dst_topology = CommandHierarchy::kVulkanCallTopology;
        size_t                         num_nodes = m_node_children[src_topology][0].size();
        DIVE_ASSERT(num_nodes == m_node_children[src_topology][1].size());
        for (size_t node_index = 0; node_index < num_nodes; ++node_index)
        {
            // Ensure topology was not previously filled-in
            DIVE_ASSERT(m_node_children[dst_topology][0][node_index].empty());
            DIVE_ASSERT(m_node_children[dst_topology][1][node_index].empty());

            // Go through primary children of a particular node, and only add non-ignored nodes
            const DiveVector<uint64_t> &children = m_node_children[src_topology][0][node_index];

            // Optionally pre-reserve the maximum size for performance reasons
            // This may result in slightly more memory being used
            m_node_children[dst_topology][0][node_index].reserve(children.size());

            for (size_t child = 0; child < children.size(); ++child)
            {
                AddChild(dst_topology, node_index, children[child]);
            }

            // Shared children should remain the same
            const DiveVector<uint64_t> &shared = m_node_children[src_topology][1][node_index];
            m_node_children[CommandHierarchy::kVulkanCallTopology][1][node_index] = shared;

            // Cache # of children
            total_num_children[src_topology] += m_node_children[src_topology][0][node_index].size();

            total_num_children[dst_topology] += m_node_children[dst_topology][0][node_index].size();
        }

        for (uint32_t topology = 0; topology < CommandHierarchy::kTopologyTypeCount; ++topology)
        {
            num_nodes = m_node_children[topology][0].size();
            Topology &cur_topology = m_command_hierarchy_ptr->m_topology[topology];
            cur_topology.SetNumNodes(num_nodes);

            for (uint64_t node_index = 0; node_index < num_nodes; ++node_index)
            {
                DIVE_ASSERT(m_node_children[topology][0].size() == m_node_children[topology][1].size());
                cur_topology.AddChildren(node_index, m_node_children[topology][0][node_index]);
                //DELETE THIS
                //uint64_t vk_cmd_index = AddNode(NodeType::kPacketNode, "TEst");
                //AddChild(CommandHierarchy::TopologyType::kSubmitTopology, node_index, vk_cmd_index);
            }
            cur_topology.m_root_node_index = std::move(m_node_root_node_index[topology]);
        }
    }
}