

#ifndef GFXRECON_UTIL_DIVE_UTIL_H
#define GFXRECON_UTIL_DIVE_UTIL_H

#include "util/defines.h"
#include "util/to_string.h"
#include "util/logging.h"
#include "format/format.h"
#include <iostream>
#include <map>

#ifndef WIN32
#include "format/platform_types.h"
#endif

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(util)

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const short& data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const int& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned short& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned int& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long long& data);
                 
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::nullptr_t data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, float data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, double data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::string_view data);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::wstring_view data);

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId handle);

void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t& data);

template <typename T>
void FieldToDiveAsHex(std::map<std::string, std::map<std::string, std::string>>& data_map, const T data)
{
    std::cout << "HERE, FieldToDiveAsHex to_hex_variable_width = " << to_hex_variable_width(data) << std::endl;
    // jdata = to_hex_variable_width(data);
}

template <typename T>
void FieldToDiveAsFixedWidthBinary(std::map<std::string, std::map<std::string, std::string>>& data_map,
                                   const T data)
{
    std::cout << "HERE, FieldToDiveAsFixedWidthBinary to_hex_variable_width = " << to_binary_fixed_width(data) << std::endl;
    // jdata = to_binary_fixed_width(data);
}

template <typename T>
void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const T* data, size_t num_elements)
{
    if (data)
    {
        for (size_t i = 0; i < num_elements; ++i)
        {
            FieldToDive(data_map, data[i]);
        }
    }
    else
    {
        std::cout << "HERE, FieldToDive data is null " << std::endl;
        // data_map = nullptr;
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const float data[4]);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t data[4]);

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint64_t data[4]);

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId* data, size_t num_elements);

#if defined(D3D12_SUPPORT)
/// @brief Turn a D3D12 or DXGI HRESULT into a string with the same character
/// sequence as the identifier of the C macro defining it in a header like
/// winerror.h.
/// @param hresult A D3D12 or DXGI result code.
std::string HresultToString(const HRESULT hresult);
void        HresultToJson(nlohmann::ordered_json& jdata, const HRESULT hresult, const util::JsonOptions& options);

void FieldToJson(nlohmann::ordered_json&                                  jdata,
                 const format::InitDx12AccelerationStructureGeometryDesc& data,
                 const util::JsonOptions&                                 options);
void FieldToJson(nlohmann::ordered_json& jdata, const format::DxgiAdapterDesc& data, const util::JsonOptions& options);
void FieldToJson(nlohmann::ordered_json& jdata, const format::Dx12RuntimeInfo& data, const util::JsonOptions& options);
void FieldToJson(nlohmann::ordered_json& jdata, const util::filepath::FileInfo& data, const util::JsonOptions& options);
#endif

GFXRECON_END_NAMESPACE(util)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_UTIL_DIVE_UTIL_H
