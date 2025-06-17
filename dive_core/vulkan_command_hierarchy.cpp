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
#include <iostream>
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
            }
        }

        // Add a dummy root node for easier management
        uint64_t root_node_index = AddNode(NodeType::kRootNode, "", 0);
        DIVE_VERIFY(root_node_index == Topology::kRootNodeIndex);

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
        uint64_t node_index = m_command_hierarchy_ptr->AddGfxrNode(type, std::move(desc));

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
        DIVE_ASSERT(node_index < m_node_children[type][0].size());
        m_node_children[type][0][node_index].push_back(child_node_index);
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

    void VulkanCommandHierarchyCreator::GetArgs(const nlohmann::ordered_json& j, uint64_t curr_index, const std::string& current_path) {
        if (j.is_object()) {
            for (auto const& [key, val] : j.items()) {
                if (val.is_object()) {
                    uint64_t object_node_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, key.c_str());
                    AddChild(CommandHierarchy::TopologyType::kSubmitTopology, curr_index, object_node_index);

                    GetArgs(val, object_node_index, "");
                } else if (val.is_array()) {
                    uint64_t array_node_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, key.c_str());
                    AddChild(CommandHierarchy::TopologyType::kSubmitTopology, curr_index, array_node_index);
                        for (size_t i = 0; i < val.size(); ++i) {
                        const auto& element = val[i];
                        if (element.is_object()) {
                            GetArgs(element, array_node_index, "");
                        } else if (element.is_array()) {
                            uint64_t nested_array_node_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, "element_" + std::to_string(i));
                            AddChild(CommandHierarchy::TopologyType::kSubmitTopology, array_node_index, nested_array_node_index);
                            GetArgs(element, nested_array_node_index, "");
                        } else {
                            std::ostringstream vk_cmd_arg_string_stream;
                            vk_cmd_arg_string_stream << element;
                            uint64_t arg_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, vk_cmd_arg_string_stream.str());
                            AddChild(CommandHierarchy::TopologyType::kSubmitTopology, array_node_index, arg_index);
                        }
                    }
                } else {
                    std::ostringstream vk_cmd_arg_string_stream;
                    vk_cmd_arg_string_stream << key << ":" << val; // key:value format for primitive
                    uint64_t vk_cmd_arg_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, vk_cmd_arg_string_stream.str());
                    AddChild(CommandHierarchy::TopologyType::kSubmitTopology, curr_index, vk_cmd_arg_index);
                }
            }
        } else if (j.is_array()) {
            for (size_t i = 0; i < j.size(); ++i) {
                const auto& element = j[i];
                if (element.is_object() || element.is_array()) {
                    GetArgs(element, curr_index, "");
                } else {
                    std::ostringstream vk_cmd_arg_string_stream;
                    vk_cmd_arg_string_stream << element;
                    uint64_t arg_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, vk_cmd_arg_string_stream.str());
                    AddChild(CommandHierarchy::TopologyType::kSubmitTopology, curr_index, arg_index);
                }
            }
        } else {
            if (!current_path.empty()) {
                std::ostringstream vk_cmd_arg_string_stream;
                vk_cmd_arg_string_stream << current_path << ":" << j;
                uint64_t vk_cmd_arg_index = AddNode(NodeType::kGfxrVulkanCommandArgNode, vk_cmd_arg_string_stream.str());
                AddChild(CommandHierarchy::TopologyType::kSubmitTopology, curr_index, vk_cmd_arg_index);
            }
        }
    }


    //--------------------------------------------------------------------------------------------------
    bool VulkanCommandHierarchyCreator::OnCommand(uint32_t parent_index, DiveAnnotationProcessor::VulkanCommandInfo vk_cmd_info)
    {
        std::ostringstream vk_cmd_string_stream;
        vk_cmd_string_stream << vk_cmd_info.GetVkCmdName();
        if (vk_cmd_info.GetVkCmdName() == "vkBeginCommandBuffer")
        {
            uint64_t cmd_buffer_index = AddNode(NodeType::kGfxrVulkanCommandBufferNode, vk_cmd_string_stream.str());
            m_cur_command_buffer_node_index = cmd_buffer_index;
            GetArgs(vk_cmd_info.GetArgs(), m_cur_command_buffer_node_index, "");
            AddChild(CommandHierarchy::TopologyType::kSubmitTopology, m_cur_submit_node_index, cmd_buffer_index);
        }
        else
        {
            // vk_cmd_string_stream << ", CMD Buffer Index: " << std::to_string(vk_cmd_info.GetVkCmdIndex());
            uint64_t vk_cmd_index = AddNode(NodeType::kGfxrVulkanCommandNode, vk_cmd_string_stream.str());
            GetArgs(vk_cmd_info.GetArgs(), vk_cmd_index, "");
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

        // Add submit node to the other topologies as children to the root node
        AddChild(CommandHierarchy::kSubmitTopology, Topology::kRootNodeIndex, submit_node_index);
        AddChild(CommandHierarchy::kAllEventTopology, Topology::kRootNodeIndex, submit_node_index);
        m_cur_submit_node_index = submit_node_index;
    }

    //--------------------------------------------------------------------------------------------------
    void VulkanCommandHierarchyCreator::OnGfxrSubmitEnd(uint32_t submit_index, const DiveAnnotationProcessor::SubmitInfo &submit_info)
    {
    }

    //--------------------------------------------------------------------------------------------------
    void VulkanCommandHierarchyCreator::CreateTopologies()
    {
        uint64_t total_num_children[CommandHierarchy::kTopologyTypeCount] = {};
    
        // Convert the m_node_children temporary structure into CommandHierarchy's topologies
        for (uint32_t topology = 0; topology < CommandHierarchy::kTopologyTypeCount; ++topology)
        {
            size_t    num_nodes = m_node_children[topology][0].size();
            Topology &cur_topology = m_command_hierarchy_ptr->m_topology[topology];
            cur_topology.SetNumNodes(num_nodes);

            if (total_num_children[topology] == 0)
            {
                for (uint64_t node_index = 0; node_index < num_nodes; ++node_index)
                {
                    auto &node_children = m_node_children[topology];
                    total_num_children[topology] += node_children[0][node_index].size();
                }
            }
            cur_topology.m_children_list.reserve(total_num_children[topology]);

            for (uint64_t node_index = 0; node_index < num_nodes; ++node_index)
            {
                DIVE_ASSERT(m_node_children[topology][0].size() == m_node_children[topology][1].size());
                cur_topology.AddChildren(node_index, m_node_children[topology][0][node_index]);
            }
        }
    }
}
