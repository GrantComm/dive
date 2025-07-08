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
DiveCommandHierarchyCreator::DiveCommandHierarchyCreator(CommandHierarchy &command_hierarchy, EmulateStateTracker &state_tracker, GfxrVulkanCommandHierarchyCreator &gfxr_command_hierarchy_creator, CommandHierarchyCreator &pm4_command_hierarchy_creator) :
m_command_hierarchy(command_hierarchy), m_state_tracker(state_tracker), m_gfxr_command_hierarchy_creator(gfxr_command_hierarchy_creator), m_pm4_command_hierarchy_creator(pm4_command_hierarchy_creator)
{
    m_state_tracker.Reset();
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
                                          DiveCaptureData      &dive_capture_data,
                                          bool                    flatten_chain_nodes,
                                          std::optional<uint64_t> reserve_size)
{
    std::cout << "DiveCommandHierarchyCreator::CreateTrees" << std::endl;

    m_pm4_command_hierarchy_creator.CreateTrees(dive_capture_data.getPm4CaptureData(), flatten_chain_nodes, reserve_size);

    m_gfxr_command_hierarchy_creator.CreateTrees();

    if (!ProcessDiveSubmits(dive_capture_data.getPm4CaptureData().GetSubmits(), dive_capture_data.getPm4CaptureData().GetMemoryManager(), dive_capture_data.getGfxrCaptureData().GetGfxrSubmits()))
    {
        return false;
    }

    CreateTopologies();

    return true;
}

//--------------------------------------------------------------------------------------------------
void DiveCommandHierarchyCreator::OnCommand(
uint32_t                                   parent_index,
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
    m_pm4_command_hierarchy_creator.CreateTopologies();
}
}  // namespace Dive