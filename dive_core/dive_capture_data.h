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

#pragma once
#include "dive_core/gfxr_capture_data.h"
#include "dive_core/pm4_capture_data.h"

namespace Dive
{

class CommandHierarchy;

//--------------------------------------------------------------------------------------------------
class DiveCaptureData
{
public:
    DiveCaptureData();
    DiveCaptureData(Pm4CaptureData m_pm4_capture_data, GfxrCaptureData m_gfxr_capture_data);
    virtual ~DiveCaptureData();
    DiveCaptureData &operator=(DiveCaptureData &&) = default;

    CaptureData::LoadResult LoadFile(const char *file_name);
    const Pm4CaptureData   &getPm4CaptureData() const;
    const GfxrCaptureData  &getGfxrCaptureData() const;

private:
    ProgressTracker *m_progress_tracker;
    ILog            *m_log_ptr;
    Pm4CaptureData   m_pm4_capture_data;
    GfxrCaptureData  m_gfxr_capture_data;
};

}  // namespace Dive
