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

#include "dive_command_hierarchy.h"
#include "dive_core/common/emulate_pm4.h"
#include "dive_strings.h"
#include <iostream>

namespace Dive
{

// =================================================================================================
// DiveCommandHierarchyCreator
// =================================================================================================
DiveCommandHierarchyCreator::DiveCommandHierarchyCreator(
CommandHierarchy                  &command_hierarchy,
GfxrVulkanCommandHierarchyCreator &gfxr_command_hierarchy_creator,
CommandHierarchyCreator           &pm4_command_hierarchy_creator) :
    m_command_hierarchy(command_hierarchy),
    m_gfxr_command_hierarchy_creator(gfxr_command_hierarchy_creator),
    m_pm4_command_hierarchy_creator(pm4_command_hierarchy_creator)
{
}

//--------------------------------------------------------------------------------------------------
bool DiveCommandHierarchyCreator::ProcessDiveSubmits(
const DiveVector<SubmitInfo>                                            &submits,
const IMemoryManager                                                    &mem_manager,
const std::vector<std::unique_ptr<DiveAnnotationProcessor::SubmitInfo>> &gfxr_submits)
{
    bool result = m_pm4_command_hierarchy_creator.ProcessSubmits(submits, mem_manager);
    
    if (result != false)
    {
        result = m_gfxr_command_hierarchy_creator.ProcessGfxrSubmits(gfxr_submits);
    }
    else
    {
        return result;
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
uint64_t DiveCommandHierarchyCreator::AddNode(NodeType                  type,
                                              std::string             &&desc,
                                              CommandHierarchy::AuxInfo aux_info)
{
    uint64_t node_index = m_command_hierarchy.AddNode(type, std::move(desc), aux_info);
    for (uint32_t i = 0; i < CommandHierarchy::kTopologyTypeCount; ++i)
    {
        DIVE_ASSERT(m_node_children[i][0].size() == node_index);
        DIVE_ASSERT(m_node_children[i][1].size() == node_index);
        m_node_children[i][0].resize(m_node_children[i][0].size() + 1);
        m_node_children[i][1].resize(m_node_children[i][1].size() + 1);

        m_node_start_shared_child[i].resize(m_node_start_shared_child[i].size() + 1);
        m_node_end_shared_child[i].resize(m_node_end_shared_child[i].size() + 1);
        m_node_root_node_index[i].resize(m_node_root_node_index[i].size() + 1);
        DIVE_ASSERT(m_node_start_shared_child[i].size() == m_node_end_shared_child[i].size());
        DIVE_ASSERT(m_node_start_shared_child[i].size() == m_node_root_node_index[i].size());
    }

    return node_index;
}

//--------------------------------------------------------------------------------------------------
bool DiveCommandHierarchyCreator::CreateTrees(CommandHierarchy       &command_hierarchy_ptr,
                                              DiveCaptureData        &dive_capture_data,
                                              bool                    flatten_chain_nodes,
                                              std::optional<uint64_t> reserve_size)
{
    std::cout << "DiveCommandHierarchyCreator::CreateTrees" << std::endl;

    m_pm4_command_hierarchy_creator.CreateTrees(dive_capture_data.getPm4CaptureData(),
                                                flatten_chain_nodes,
                                                reserve_size,
                                                false);

    m_gfxr_command_hierarchy_creator.CreateTrees();

    if (!ProcessDiveSubmits(dive_capture_data.getPm4CaptureData().GetSubmits(),
                            dive_capture_data.getPm4CaptureData().GetMemoryManager(),
                            dive_capture_data.getGfxrCaptureData().GetGfxrSubmits()))
    {
        return false;
    }

    CreateTopologies();

    return true;
}

//--------------------------------------------------------------------------------------------------
void DiveCommandHierarchyCreator::OnCommand(uint32_t                                   parent_index,
                                            DiveAnnotationProcessor::VulkanCommandInfo vk_cmd_info)
{
    m_gfxr_command_hierarchy_creator.OnCommand(parent_index, vk_cmd_info);
}

//--------------------------------------------------------------------------------------------------
void DiveCommandHierarchyCreator::OnGfxrSubmit(
uint32_t                                   submit_index,
const DiveAnnotationProcessor::SubmitInfo &submit_info)
{
    m_gfxr_command_hierarchy_creator.OnGfxrSubmit(submit_index, submit_info);
}

//--------------------------------------------------------------------------------------------------
void DiveCommandHierarchyCreator::CreateTopologies()
{
    // m_pm4_command_hierarchy_creator.CreateTopologies();
    uint64_t total_num_children[CommandHierarchy::kTopologyTypeCount] = {};
    uint64_t total_num_shared_children[CommandHierarchy::kTopologyTypeCount] = {};

    // Convert the m_node_children temporary structure into CommandHierarchy's topologies
    for (uint32_t topology = 0; topology < CommandHierarchy::kTopologyTypeCount; ++topology)
    {
        size_t              num_pm4_nodes = m_pm4_command_hierarchy_creator.get_node_children(topology, 0).size();
        size_t              total_num_nodes = num_pm4_nodes + m_gfxr_command_hierarchy_creator.get_node_children(topology).size();

        SharedNodeTopology &cur_topology = m_command_hierarchy.m_topology[topology];
        cur_topology.SetNumNodes(total_num_nodes);

        // Optional loop: Pre-reserve to prevent the resize() from allocating memory later
        // Note: The number of children for some of the topologies have been determined
        // earlier in this function already
        if (total_num_children[topology] == 0 && total_num_shared_children[topology] == 0)
        {
            for (uint64_t node_index = 0; node_index < num_pm4_nodes; ++node_index)
            {
                total_num_children[topology] += m_pm4_command_hierarchy_creator.get_node_children(topology, 0)[node_index].size();
                total_num_shared_children[topology] += m_pm4_command_hierarchy_creator.get_node_children(topology, 1)[node_index].size();
            }
        }
        cur_topology.m_children_list.reserve(total_num_children[topology]);
        cur_topology.m_shared_children_list.reserve(total_num_shared_children[topology]);

        for (uint64_t node_index = 0; node_index < num_pm4_nodes; ++node_index)
        {
            DIVE_ASSERT(m_pm4_command_hierarchy_creator.get_node_children(topology, 0).size() ==
                        m_pm4_command_hierarchy_creator.get_node_children(topology, 1).size());
            cur_topology.AddChildren(node_index, m_pm4_command_hierarchy_creator.get_node_children(topology, 0)[node_index]);
            cur_topology.AddSharedChildren(node_index, m_pm4_command_hierarchy_creator.get_node_children(topology, 1)[node_index]);
        }

        cur_topology.m_start_shared_child = std::move(m_pm4_command_hierarchy_creator.get_node_start_shared_child(topology));
        cur_topology.m_end_shared_child = std::move(m_pm4_command_hierarchy_creator.get_node_end_shared_child(topology));
        cur_topology.m_root_node_index = std::move(m_pm4_command_hierarchy_creator.get_node_root_node_index(topology));

        // Add the gfxr nodes to the topology.
        for (uint64_t node_index = num_pm4_nodes; node_index < total_num_nodes; ++node_index)
        {
            cur_topology.AddChildren(node_index, m_pm4_command_hierarchy_creator.get_node_children(topology, 0)[node_index]);
        }
    }
}
}  // namespace Dive
