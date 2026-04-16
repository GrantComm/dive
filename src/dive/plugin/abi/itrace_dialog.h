/*
 Copyright 2026 Google LLC

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

#include <string>

namespace Dive
{
class AndroidDevice;
}

class ITraceDialog
{
 public:
    virtual ~ITraceDialog() = default;

    virtual void SetResetDialogOnClose(bool reset) = 0;
    virtual void UpdateCaptureFileDirectories(
        std::string on_device_capture_file_directory = "") = 0;
    virtual void SetTraceDialogForCapture() = 0;
    virtual void ResetTraceDialogOnAppStop() = 0;
    virtual Dive::AndroidDevice* GetAndValidateDevice() = 0;

    virtual void OnStartPackage() = 0;
    virtual void OnStopPackage() = 0;
};
