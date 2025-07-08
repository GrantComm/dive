/*
 Copyright 2019 Google LLC

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

#include "dive_capture_data.h"

namespace Dive
{

// =================================================================================================
// DiveCaptureData
// =================================================================================================
DiveCaptureData::DiveCaptureData()
    : m_pm4_capture_data(),
      m_gfxr_capture_data()
{
}

//--------------------------------------------------------------------------------------------------
DiveCaptureData::~DiveCaptureData()
{
}

//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult DiveCaptureData::LoadFile(const char *file_name)
{
    CaptureData::LoadResult result;

    m_gfxr_capture_data = GfxrCaptureData();
    result = m_gfxr_capture_data.LoadCaptureFile(file_name);
    m_pm4_capture_data = Pm4CaptureData(m_progress_tracker);                              
    /*m_capture_metadata = CaptureMetadata();
    result = m_pm4_capture_data.LoadFile(file_name);*/
    return result;
}

//--------------------------------------------------------------------------------------------------
const Pm4CaptureData& DiveCaptureData::getPm4CaptureData() const
{
    return m_pm4_capture_data;
}

//--------------------------------------------------------------------------------------------------
const GfxrCaptureData& DiveCaptureData::getGfxrCaptureData() const
{
    return m_gfxr_capture_data;
}
}  // namespace Dive
