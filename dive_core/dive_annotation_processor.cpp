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
#include "util/output_stream.h"
#include "util/logging.h"
#include "decode/api_decoder.h"
#include <cstdint>
#include <iostream>
#include <ostream>

DiveAnnotationProcessor::DiveAnnotationProcessor()
{
}

DiveAnnotationProcessor::~DiveAnnotationProcessor()
{
}

void DiveAnnotationProcessor::Destroy()
{
}

void DiveAnnotationProcessor::WriteBlockStart()
{
}

void DiveAnnotationProcessor::WriteBlockEnd(std::string function_name, uint32_t cmd_buffer_index)
{
    if (function_name == "vkQueueSubmit" || function_name == "vkQueueSubmit2")
    {
        std::unique_ptr<SubmitInfo> submit_ptr = std::make_unique<SubmitInfo>(function_name);

        for (auto it = m_pre_submit_commands.begin(); it != m_pre_submit_commands.end(); ++it)
        {
            submit_ptr->AppendVkCmd(*it);
        }
        m_pre_submit_commands.clear();
        submit_ptr->SetCommandBufferCount(m_command_buffer_count);
        m_submits.push_back(std::move(submit_ptr));
        m_curr_submit = nullptr;
        m_command_buffer_count = 0;
    }
    else if (function_name.find("vkCmd") != std::string::npos || function_name.find("vkBeginCommandBuffer") != std::string::npos)
    {
        // Don't include the vkEndCommandBuffer call
        if (function_name.find("vkEndCommandBuffer") != std::string::npos)
        {
            return;
        }

        VulkanCommandInfo vkCmd(function_name, cmd_buffer_index);

        if (function_name.find("vkBeginCommandBuffer") != std::string::npos)
        {
            m_command_buffer_count++;
        }

        if (m_curr_submit) // Check if the pointer is not null
        {
            m_curr_submit->AppendVkCmd(vkCmd);
        }
        else
        {
            // No active submit, so buffer the command
            m_pre_submit_commands.push_back(vkCmd);
        }
    }
}

void DiveAnnotationProcessor::WriteBlockEnd(gfxrecon::util::DiveFunctionData function_data)
{
    std::string function_name = function_data.GetFunctionName();

    if (function_name == "vkQueueSubmit" || function_name == "vkQueueSubmit2")
    {
        std::unique_ptr<SubmitInfo> submit_ptr = std::make_unique<SubmitInfo>(function_name);

        for (auto it = m_pre_submit_commands.begin(); it != m_pre_submit_commands.end(); ++it)
        {
            submit_ptr->AppendVkCmd(*it);
        }
        m_pre_submit_commands.clear();
        submit_ptr->SetCommandBufferCount(m_command_buffer_count);
        m_submits.push_back(std::move(submit_ptr));
        m_curr_submit = nullptr;
        m_command_buffer_count = 0;
    }
    else if (function_name.find("vkCmd") != std::string::npos || function_name.find("vkBeginCommandBuffer") != std::string::npos)
    {
        // Don't include the vkEndCommandBuffer call
        if (function_name.find("vkEndCommandBuffer") != std::string::npos)
        {
            return;
        }

        VulkanCommandInfo vkCmd(function_data);

        if (function_name.find("vkBeginCommandBuffer") != std::string::npos)
        {
            m_command_buffer_count++;
        }

        if (m_curr_submit) // Check if the pointer is not null
        {
            m_curr_submit->AppendVkCmd(vkCmd);
        }
        else
        {
            // No active submit, so buffer the command
            m_pre_submit_commands.push_back(vkCmd);
        }
    }
}

/*nlohmann::ordered_json& DiveAnnotationProcessor::WriteApiCallStart(const gfxrecon::decode::ApiCallInfo& call_info, const std::string_view command_name)
{
    auto& json_data = WriteBlockStart();

    json_data[format::kNameIndex] = call_info.index;

    nlohmann::ordered_json& function = json_data[format::kNameFunction];
    function[format::kNameName]      = command_name;
    function[format::kNameThread]    = call_info.thread_id;

    return function;
}

nlohmann::ordered_json& DiveAnnotationProcessor::WriteApiCallStart(const gfxrecon::decode::ApiCallInfo&     call_info,
                                                      const std::string_view object_type,
                                                      const gfxrecon::format::HandleId object_id,
                                                      const std::string_view command_name)
{
    auto& json_data = WriteBlockStart();

    json_data[format::kNameIndex] = call_info.index;

    nlohmann::ordered_json& method = json_data[format::kNameMethod];
    method[format::kNameName]      = command_name;
    method[format::kNameThread]    = call_info.thread_id;

    nlohmann::ordered_json& object  = method[format::kNameObject];
    object[format::kNameObjectType] = object_type;
    FieldToJson(object[format::kNameObjectHandle], object_id, GetOptions());

    return method;
}*/

void DiveAnnotationProcessor::ProcessAnnotation(uint64_t               block_index,
                                   gfxrecon::format::AnnotationType type,
                                   const std::string&     label,
                                   const std::string&     data)
{
    /*auto& json_data     = WriteBlockStart();
    json_data["index"]  = block_index;
    auto& annotation    = json_data["annotation"];
    annotation["type"]  = util::AnnotationTypeToString(type);
    annotation["label"] = label;
    annotation["data"]  = data;
    WriteBlockEnd();*/
}