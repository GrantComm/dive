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
        m_capture_type = CaptureFileType::kDive;
        m_dive_file = file_name;
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
}