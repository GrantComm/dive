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

#ifndef GFXRECON_DECODE_DECODE_DIVE_UTIL_H
#define GFXRECON_DECODE_DECODE_DIVE_UTIL_H

/// @file API-independent utilities for converting decode-module types for Dive.

#include "decode/pointer_decoder.h"
#include "decode/handle_pointer_decoder.h"
#include "decode/struct_pointer_decoder.h"
#include "decode/string_decoder.h"
#include "decode/string_array_decoder.h"
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const StringDecoder&     data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const StringDecoder*     data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const StringArrayDecoder& data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const StringArrayDecoder* data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const WStringDecoder&    data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const WStringDecoder*    data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const WStringArrayDecoder& data
                 );

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const short& data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const int& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned short& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned int& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                  const unsigned long long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::nullptr_t data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, float data);

                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, double data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                  const std::string_view data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::wstring_view  data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const float data[4]);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t data[4]);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint64_t data[4]);

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId handle);

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
    const format::HandleId* data,
    size_t num_elements);

template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const PointerDecoder<DecodedType, OutputDecodedType>* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length        = data->GetLength();

        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                std::map<std::string, int> inner_map;

                // FieldToDive(std::string(decoded_value[i]), decoded_value[i]);
            }
        }
        else if (length == 1)
        {
            FieldToDive(data_map, *decoded_value);
        }
    }
}

// Reference to pointer version wraps pointer to pointer version above.
template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const PointerDecoder<DecodedType, OutputDecodedType>& data
                 )
{
    FieldToDive(data_map, &data);
}

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const PointerDecoder<uint32_t, uint32_t>& data
                 );

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const PointerDecoder<int32_t, int32_t>& data
                 );

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const PointerDecoder<uint64_t, uint64_t>& data
                 );

template <>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const PointerDecoder<int64_t, int64_t>& data
                 );

template <typename DecodedType>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const StructPointerDecoder<DecodedType>* data
                 )
{
    /*if (data)
    {
        const auto meta_struct = data->GetMetaStructPointer();
        const auto length      = data->GetLength();
        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                std::map<std::string, int> inner_map;

                FieldToDive(std::string(meta_struct[i]), meta_struct[i]);
            }
        }
        else if (length == 1)
        {
            FieldToDive(data_map, meta_struct);
        }
    }*/
}

// Similar to above but DecodedType is pointed-to
template <typename DecodedType>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const StructPointerDecoder<DecodedType*>* data)
{
    std::cout << "HERE 0 " << std::endl;
}

template <typename THandle>
void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                  const HandlePointerDecoder<THandle>* data)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length        = data->GetLength();

        if (data->IsArray())
        {
            for (size_t i = 0; i < length; ++i)
            {
                // HandleToDive(std::to_string(decoded_value[i]), decoded_value[i]);
            }
        }
        else if (length == 1)
        {
            HandleToDive(data_map, *decoded_value);
        }
    }
}

/// @brief Thunk to HandleToDive to allow the standard FieldToDive name to be
/// used for pointers and arrays where the type of the HandlePointerDecoder
/// allows the correct version to be resolved.
template <typename THandle>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const HandlePointerDecoder<THandle>* data
                 )
{
    HandleToDive(data_map, data);
}

// Same as array FieldToDive above but converts elements pointed-to to hexadecimal
template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDiveAsHex(std::map<std::string, std::map<std::string, std::string>>& data_map,
                      const PointerDecoder<DecodedType, OutputDecodedType>* data
                      )
{
    std::cout << "HERE 1" << std::endl;
}

template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDiveAsHex(std::map<std::string, std::map<std::string, std::string>>& data_map,
                      const PointerDecoder<DecodedType, OutputDecodedType>& data
                      )
{
    FieldToDiveAsHex(data_map, &data);
}

/// Same as array FieldToDive above but converts elements pointed-to to binary
/// as a JSON string rather than as a JSON number type. Useful for bitmasks.
template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDiveAsFixedWidthBinary(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                   const PointerDecoder<DecodedType, OutputDecodedType>& data
                                  )
{
    std::cout << "HERE 2" << std::endl;
}

template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDiveAsFixedWidthBinary(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                   const PointerDecoder<DecodedType, OutputDecodedType>* data
                                   )
{
    if (data)
    {
        FieldToDiveAsFixedWidthBinary(data_map, *data);
    }
}

/// @brief Thunk to FieldToDiveAsFixedWidthBinary because consumers deliver pointers to non-const PointerDecoders
/// and they fail to resolve to the const version above.
template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToDiveAsFixedWidthBinary(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                   PointerDecoder<DecodedType, OutputDecodedType>* data
                                   )
{
    if (data)
    {
        FieldToDiveAsFixedWidthBinary(data_map, *data);
    }
}

template <typename T>
void FieldToDiveAsHex(std::map<std::string, std::map<std::string, std::string>>& data_map, const T data)
{
    // jdata = to_hex_variable_width(data);
}

/// @brief Convert an integer type to JSON but encoded in binary as a JSON string
/// rather than as a JSON number type. Useful for bitmasks.
template <typename T>
void FieldToDiveAsFixedWidthBinary(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                   const T data)
{
    // jdata = to_binary_fixed_width(data);
}

template <typename T>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const T* data,
                 size_t num_elements)
{
    if (data)
    {
        for (size_t i = 0; i < num_elements; ++i)
        {
            // FieldToDive(jdata[i], data[i]);
        }
    }
    else
    {
        // jdata = nullptr;
    }
}

// Used by (e.g.) VkMapMemory's ppData
inline void
FieldToDiveAsHex(std::map<std::string, std::map<std::string, std::string>>& data_map, PointerDecoder<uint64_t, void*>* data)
{
    FieldToDiveAsHex<uint64_t, void*>(data_map, data);
}

inline void
FieldToDiveAsHex(std::map<std::string, std::map<std::string, std::string>>& data_map, PointerDecoder<int64_t, void*>* data)
{
    FieldToDiveAsHex<int64_t, void*>(data_map, data);
}

/// Convert arrays of and pointers to bools. Since VkBool32 is just a typedef of
/// uint32_t we can't use the standard function name and dispatch on the type.
void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                  const PointerDecoder<uint32_t, uint32_t>* data
                   );

/// Convert arrays of and pointers to bools. Since the Windows BOOL is just a
/// typedef of int we can't use the standard function name and dispatch on the type.
void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                  const PointerDecoder<int, int>* data
                  );

void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t& data);

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_DECODE_DIVE_UTIL_H
