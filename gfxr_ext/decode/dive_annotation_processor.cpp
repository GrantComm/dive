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

#include "dive_annotation_processor.h"
#include <cstdint>
#include <iostream>
#include <ostream>
#include "decode/api_decoder.h"
#include "util/logging.h"
#include "util/output_stream.h"

void DiveAnnotationProcessor::WriteBlockEnd(const gfxrecon::util::DiveFunctionData& function_data)
{
    std::string function_name = function_data.GetFunctionName();
    VulkanCommandInfo vkCmd(function_data);

    if (function_name == "vkQueueSubmit" || function_name == "vkQueueSubmit2")
    {
        std::unique_ptr<SubmitInfo> submit_ptr = std::make_unique<SubmitInfo>(function_name);

        submit_ptr->SetVulkanCommands(m_current_submit_commands);
        m_current_submit_commands.clear();
        submit_ptr->SetCommandBufferCount(m_current_submit_command_buffer_count);
        m_submits.push_back(std::move(submit_ptr));
        m_current_submit_command_buffer_count = 0;
    }
    else if (function_name.find("vkBeginCommandBuffer") != std::string::npos)
    {
        m_current_submit_command_buffer_count++;
        m_current_submit_commands.push_back(vkCmd);
        // Store an index instead of a pointer.
        m_begin_command_buffer_index = m_current_submit_commands.size() - 1;
    }
    else if (function_name.find("vkCmdDraw") != std::string::npos)
    {
        m_current_command_buffer_draw_count++;
        m_current_submit_commands.push_back(vkCmd);
    }
    else if (function_name.find("vkEndCommandBuffer") != std::string::npos)
    {
        try
        {
            VulkanCommandInfo& begin_cmd_info = m_current_submit_commands.at(m_begin_command_buffer_index);
            begin_cmd_info.SetDrawCallCount(m_current_command_buffer_draw_count);
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Index out of range. " << e.what() << std::endl;
        }

        m_current_submit_commands.push_back(vkCmd);

        // Reset state for the next command buffer.
        m_current_command_buffer_draw_count = 0;
    }
    else
    {
        m_current_submit_commands.push_back(vkCmd);
    }
}
