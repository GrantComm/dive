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

#include "decode/decode_dive_util.h"
#include "util/defines.h"
#include <cmath>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const StringDecoder& data)
{
    const char* const decoded_data = data.GetPointer();
    if (decoded_data)
    {
        // FieldToDive(data_map, decoded_data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const StringDecoder* data)
{
    if (data)
    {
        FieldToDive(data_map, *data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, int>>& data_map, const StringArrayDecoder* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_data = data->GetPointer();
        for (size_t i = 0; i < data->GetLength(); ++i)
        {
            // data_map[i] = std::string(decoded_data[i]);
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, int>>& data_map, const WStringDecoder& data)
{
    const wchar_t* const decoded_data = data.GetPointer();
    if (decoded_data)
    {
        // FieldToDive(data_map, decoded_data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const WStringDecoder* data)
{
    if (data)
    {
        FieldToDive(data_map, *data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const WStringArrayDecoder& data)
{
    const auto decoded_data = data.GetPointer();
    if (decoded_data)
    {
        for (size_t i = 0; i < data.GetLength(); ++i)
        {
            // FieldToDive(data_map[i], decoded_data[i]);
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const float data[4])
{
    FieldToDive(data_map, data, 4);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t data[4])
{
    FieldToDive(data_map, data, 4);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint64_t data[4])
{
    FieldToDive(data_map, data, 4);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const short& data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const int& data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long& data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long long& data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned short& data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned int& data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long& data)
{
    // // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long long& data)
{
    //// jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::nullptr_t data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, float data)
{
    if (std::isnan(data))
    {
        GFXRECON_LOG_WARNING_ONCE("Converting a NAN to zero.");
        data = 0.0f;
    }
    else if (std::isinf(data))
    {
        GFXRECON_LOG_WARNING_ONCE("Converting an infinity to max or min.");
        if (data < 0)
        {
            data = std::numeric_limits<float>::min();
        }
        else
        {
            data = std::numeric_limits<float>::max();
        }
    }
    // Normal and denormal/subnormal numbers pass through unchanged and unremarked.

    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, double data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::string_view data)
{
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::wstring_view data)
{
/*#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    jdata = utf8_conv.to_bytes(data.data(), data.data() + data.length());*/
}

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId handle)
{
    /*if (options.hex_handles)
    {
        // A JSON string
        jdata = util::to_hex_variable_width(handle);
    }
    else
    {
        // A JSON number
        jdata = handle;
    }*/
}

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId* data, size_t num_elements)
{
    /*if (data)
    {
        for (size_t i = 0; i < num_elements; ++i)
        {
            HandleToJson(jdata[i], data[i], options);
        }
    }
    else
    {
        jdata = nullptr;
    }*/
}

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PointerDecoder<uint32_t, uint32_t>& data)
{
    if (data.GetPointer())
    {
        const auto decoded_value = data.GetPointer();
        const auto length        = data.GetLength();
        if (length > 1)
        {
            for (size_t i = 0; i < length; ++i)
            {
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            // data_map = *decoded_value;
        }
    }
}

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PointerDecoder<int32_t, int32_t>& data)
{
    if (data.GetPointer())
    {
        const auto decoded_value = data.GetPointer();
        const auto length        = data.GetLength();
        if (length > 1)
        {
            for (size_t i = 0; i < length; ++i)
            {
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            // data_map = *decoded_value;
        }
    }
}

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PointerDecoder<uint64_t, uint64_t>& data)
{
    if (data.GetPointer())
    {
        const auto decoded_value = data.GetPointer();
        const auto length        = data.GetLength();
        if (length > 1)
        {
            for (size_t i = 0; i < length; ++i)
            {
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            // data_map = *decoded_value;
        }
    }
}

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PointerDecoder<int64_t, int64_t>& data)
{
    if (data.GetPointer())
    {
        const auto decoded_value = data.GetPointer();
        const auto length        = data.GetLength();
        if (length > 1)
        {
            for (size_t i = 0; i < length; ++i)
            {
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            // data_map = *decoded_value;
        }
    }
}

void Bool32ToDive(std::map<std::string, std::map<std::string, int>>& data_map, const PointerDecoder<uint32_t, uint32_t>* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length        = data->GetLength();

        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                // util::Bool32ToDive(data_map[i], decoded_value[i]);
            }
        }
        else if (length == 1)
        {
            // util::Bool32ToDive(data_map, *decoded_value);
        }
    }
}

void Bool32ToDive(std::map<std::string, std::map<std::string, int>>& data_map, const PointerDecoder<int, int>* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length        = data->GetLength();

        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                // util::Bool32ToDive(data_map[i], decoded_value[i]);
            }
        }
        else if (length == 1)
        {
            // util::Bool32ToDive(data_map, *decoded_value);
        }
    }
}

void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t& data)
{
    // data_map = static_cast<bool>(data);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
