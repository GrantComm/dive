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

#include "capture_data.h"
#include <filesystem>

namespace Dive
{
// =================================================================================================
// SelectedCaptureFiles
// =================================================================================================
SelectedCaptureFiles::SelectedCaptureFiles()
{
    m_capture_type = CaptureFileType::kNone;
}

//--------------------------------------------------------------------------------------------------
void SelectedCaptureFiles::AddSingleFile(std::string file_name)
{
    std::string file_extension = std::filesystem::path(file_name).extension().generic_string();
    if (file_extension.compare(".dive") == 0)
    {
        // TODO: Change the type to CaptureFileType::kDive and once the .dive file contains .gfxr
        // and .rd data.
        m_capture_type = CaptureFileType::kAdrenoPm4;
        m_pm4_file = file_name;
    }
    else if (file_extension.compare(".rd") == 0)
    {
        m_pm4_file = file_name;
        if (m_gfxr_file != "")
        {
            m_capture_type = CaptureFileType::kDive;
        }
        else
        {
            m_capture_type = CaptureFileType::kAdrenoPm4;
        }
    }
    else if (file_extension.compare(".gfxr") == 0)
    {
        m_gfxr_file = file_name;
        if (m_pm4_file != "")
        {
            m_capture_type = CaptureFileType::kDive;
        }
        else
        {
            m_capture_type = CaptureFileType::kGfxr;
        }
    }
}

CaptureFileType SelectedCaptureFiles::GetCaptureType() const
{
    return m_capture_type;
}

std::string SelectedCaptureFiles::PrintSelections()
{
    if (m_capture_type == CaptureFileType::kNone)
    {
        return "No file(s) selected";
    }
    else if (m_capture_type == CaptureFileType::kAdrenoPm4)
    {
        return m_pm4_file;
    }
    else if (m_capture_type == CaptureFileType::kGfxr)
    {
        return m_gfxr_file;
    }
    else
    {
        if (m_gfxr_file != "" && m_pm4_file != "")
        {
            return (m_pm4_file + ", " + m_gfxr_file);
        }

        return m_dive_file;
    }
}

void SelectedCaptureFiles::ResetSelections()
{
    m_pm4_file = "";
    m_gfxr_file = "";
    m_dive_file = "";
    m_capture_type = CaptureFileType::kNone;
}

}  // namespace Dive