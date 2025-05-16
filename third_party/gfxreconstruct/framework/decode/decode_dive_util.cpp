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
#include <string>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const StringDecoder& data)
{
    const char* const decoded_data = data.GetPointer();
    if (decoded_data)
    {
        std::cout << "HERE, FieldToDive, StringDecoder (&)" << std::endl;
        // FieldToDive(data_map, decoded_data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const StringDecoder* data)
{
    if (data)
    {
        std::cout << "HERE, FieldToDive, StringDecoder (*)" << std::endl;
        FieldToDive(data_map, *data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const StringArrayDecoder* data)
{
    std::cout << "HERE, FieldToDive, StringArrayDecoder (*)" << std::endl;
    if (data && data->GetPointer())
    {
        const auto decoded_data = data->GetPointer();
        for (size_t i = 0; i < data->GetLength(); ++i)
        {
            std::cout << "HERE, decoded_data[" <<std::to_string(i) << "] = " << std::string(decoded_data[i]) << std::endl;
            // data_map[i] = std::string(decoded_data[i]);
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const WStringDecoder& data)
{
    std::cout << "HERE, FieldToDive, WStringDecoder (&)" << std::endl;
    const wchar_t* const decoded_data = data.GetPointer();
    if (decoded_data)
    {
        // FieldToDive(data_map, decoded_data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const WStringDecoder* data)
{
    std::cout << "HERE, FieldToDive, WStringDecoder (*)" << std::endl;
    if (data)
    {
        FieldToDive(data_map, *data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const WStringArrayDecoder& data)
{
    std::cout << "HERE, FieldToDive, WStringArrayDecoder (&)" << std::endl;
    const auto decoded_data = data.GetPointer();
    if (decoded_data)
    {
        for (size_t i = 0; i < data.GetLength(); ++i)
        {
            
            // FieldToDive(data_map[i], decoded_data[i]);
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, double data)
{
    std::cout << "HERE, FieldToDive, double" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::string_view data)
{
    std::cout << "HERE, FieldToDive, std::string_view" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::wstring_view data)
{
    std::cout << "HERE, FieldToDive, std::wstring_view" << std::endl;
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
                std::cout << "HERE, PointerDecoder #1 called, i =  " << std::to_string(i) << std::endl;
                std::cout << "HERE, PointerDecoder #1 val = " << std::to_string(decoded_value[i]) << std::endl;
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            std::cout << "HERE, PointerDecoder #1 no pointer val = " << decoded_value << std::endl;
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
                std::cout << "HERE, PointerDecoder #2 called, i =  " << std::to_string(i) << std::endl;
                std::cout << "HERE, PointerDecoder #2 val = " << std::to_string(decoded_value[i]) << std::endl;
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            std::cout << "HERE, PointerDecoder #2 (l == 1) val = " << decoded_value << std::endl;
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
                std::cout << "HERE, PointerDecoder #3 called, i =  " << std::to_string(i) << std::endl;
                std::cout << "HERE, PointerDecoder #3 val = " << std::to_string(decoded_value[i]) << std::endl;
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            std::cout << "HERE, PointerDecoder #3 no pointer val = " << decoded_value << std::endl;
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
                std::cout << "HERE, PointerDecoder #4 called, i =  " << std::to_string(i) << std::endl;
                std::cout << "HERE, PointerDecoder #4 val = " << std::to_string(decoded_value[i]) << std::endl;
                // data_map[i] = decoded_value[i];
            }
        }
        else
        {
            std::cout << "HERE, PointerDecoder #4 no pointer val = " << decoded_value << std::endl;
            // data_map = *decoded_value;
        }
    }
}

void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PointerDecoder<uint32_t, uint32_t>* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length        = data->GetLength();

        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                std::cout << "HERE, PointerDecoder #5 called, i =  " << std::to_string(i) << std::endl;
                std::cout << "HERE, PointerDecoder #5 val = " << std::to_string(decoded_value[i]) << std::endl;
                // util::Bool32ToDive(data_map[i], decoded_value[i]);
            }
        }
        else if (length == 1)
        {
            std::cout << "HERE, PointerDecoder #5 (l == 1) val = " << decoded_value << std::endl;
            // util::Bool32ToDive(data_map, *decoded_value);
        }
    }
}

void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PointerDecoder<int, int>* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length        = data->GetLength();

        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                std::cout << "HERE, PointerDecoder #6 called, i =  " << std::to_string(i) << std::endl;
                std::cout << "HERE, PointerDecoder #6 val = " << std::to_string(decoded_value[i]) << std::endl;
                // util::Bool32ToDive(data_map[i], decoded_value[i]);
            }
        }
        else if (length == 1)
        {
            std::cout << "HERE, PointerDecoder #6 (l == 1) val = " << decoded_value << std::endl;
            // util::Bool32ToDive(data_map, *decoded_value);
        }
    }
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
