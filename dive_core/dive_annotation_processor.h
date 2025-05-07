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

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include "dive_core/stl_replacement.h"
#include "third_party/gfxreconstruct/framework/decode/annotation_handler.h"
#include "util/platform.h"
#include "util/defines.h"

struct ApiCallInfo;

/// Manages writing
class DiveAnnotationProcessor : public gfxrecon::decode::AnnotationHandler
{
  public:

  struct VulkanCommandInfo {
    public:
      VulkanCommandInfo(std::string name, uint32_t index) {m_name = name; m_index = index;}
      const std::string GetVkCmdName() { return m_name; }
      uint32_t GetVkCmdIndex() { return m_index; }
      void SetCmdCount(uint32_t cmd_count) { m_cmd_count = cmd_count; }
      uint32_t GetCmdCount() { return m_cmd_count; }
    private:
      std::string m_name;
      uint32_t m_index;
      uint32_t m_cmd_count; // Only used by vkBeginCommandBuffers
      // Args need to be added
  };

struct SubmitInfo {
public:
    SubmitInfo() = default;
    SubmitInfo(std::string name) : m_name(name) {}
    std::string GetSubmitText() const { return m_name; }
    void SetCommandBufferCount(uint32_t cmd_buffer_count) { m_cmd_buffer_count = cmd_buffer_count; }
    uint32_t GetCommandBufferCount() const { return m_cmd_buffer_count; }
    const DiveVector<VulkanCommandInfo>& GetVkCmds() const { return vulkan_cmds; }
    void AppendVkCmd(VulkanCommandInfo vkCmd) { vulkan_cmds.push_back(vkCmd); }
private:
    std::string m_name;
    uint32_t m_cmd_buffer_count;
    DiveVector<VulkanCommandInfo> vulkan_cmds;
    // Args need to be added
};

    DiveAnnotationProcessor();
    ~DiveAnnotationProcessor();

    /// Output data at end of stream such as closing the JSON array.
    void EndStream();
    void Destroy();
    bool IsValid() const;

    /// Get a clean fresh JSON tree to build a block's representation in.
    /// Users can build the JSON representation of their blocks in this tree before
    /// calling WriteBlockEnd() to serialize it out to the stream.
    void WriteBlockStart();

    /// Finalise the current block and stream it out.
    void WriteBlockEnd(std::string str, uint32_t cmd_buffer_index) override;
    /*
    /// Start the JSON tree for a function call, building the top-level object
    /// with index and function fields, adding name and thread to the function.
    /// @return The "function" object field for the caller to populate further
    /// with return value if any and arguments.
    nlohmann::ordered_json& WriteApiCallStart(const ApiCallInfo& call_info, const std::string_view command_name);

    /// Start the JSON tree for a method call, building the top-level object
    /// with index and function fields, adding name and thread to the function.
    /// @return The "method" object field for the caller to populate further
    /// with return value if any and arguments.
    nlohmann::ordered_json& WriteApiCallStart(const ApiCallInfo&     call_info,
                                              const std::string_view object_type,
                                              const format::HandleId object_id,
                                              const std::string_view command_name);*/

    void WriteMarker(const char* name, const std::string_view marker_type, uint64_t frame_number);

    uint32_t GetNumStreams() const { return num_streams_; }

    /// @brief Convert annotations, which are simple {type:enum, key:string, value:string} objects.
    virtual void ProcessAnnotation(uint64_t               block_index,
                                   gfxrecon::format::AnnotationType type,
                                   const std::string&     label,
                                   const std::string&     data) override;

    bool        WriteBinaryFile(const std::string& filename, uint64_t data_size, const uint8_t* data);

    inline void SetCurrentBlockIndex(uint64_t block_index) { block_index_ = block_index; }

    DiveVector<std::unique_ptr<SubmitInfo>> getSubmits() { return std::move(m_submits);; }

  private:
    DiveVector<std::unique_ptr<SubmitInfo>> m_submits;
    SubmitInfo* m_curr_submit = nullptr;
    uint32_t m_command_buffer_count = 0;
    std::vector<VulkanCommandInfo> m_pre_submit_commands; // Buffer for commands before a submit
    uint64_t               block_index_;
    uint32_t               num_streams_{ 0 };
    /// Number of side-files generated for dumping binary blobs etc.
    uint32_t num_files_{ 0 };

    // Account for markers being broadcast to all decoders, all consumers, unlike functions and metadata blocks which
    // are tagged with an API family. A marker is only converted if it differs in one of these three attributes.
    std::string last_marker_name_;
    std::string last_marker_type_;
    uint64_t    last_frame_number_{ 0 };

    bool first_{ true };
};