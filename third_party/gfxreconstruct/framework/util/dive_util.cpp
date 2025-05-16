

#include "util/dive_util.h"
#include "util/to_string.h"
#include "util/logging.h"
#include "util/strings.h"

#include <codecvt> // For encoding wstring_view to utf8.

#if defined(D3D12_SUPPORT)
#include <winerror.h> // D3D12 and DXGI HRESULT return values.
// Still needed for D3D12 return values
// <https://learn.microsoft.com/en-us/windows/win32/direct3d12/d3d12-graphics-reference-returnvalues>
#include <d3d12.h>
#include <d3d9.h>
#include <unordered_map>
#include "generated/generated_dx12_enum_to_json.h"
#endif

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(util)

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const float data[4])
{
    std::cout << "HERE, FieldToDive, float[]" << std::endl;
    FieldToDive(data_map, data, 4);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t data[4])
{
    std::cout << "HERE, FieldToDive, uint32_t[]" << std::endl;
    FieldToDive(data_map, data, 4);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint64_t data[4])
{
    std::cout << "HERE, FieldToDive, uint64_t[]" << std::endl;
    FieldToDive(data_map, data, 4);
}

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId handle)
{
    std::cout << "HERE, HandleToDive: val = " << util::to_hex_variable_width(handle) << std::endl;
}

void HandleToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::HandleId* data, size_t num_elements)
{
    std::cout << "HERE, NUM ELEMENTS: " << std::to_string(num_elements) << std::endl;
    if (data)
    {
        for (size_t i = 0; i < num_elements; ++i)
        {
            std::cout << "HERE, call HandleToDive in loop: val = " << util::to_hex_variable_width(data[i]) << std::endl;
            std::map<std::string, std::map<std::string, std::string>> data_map_2;
            HandleToDive(data_map_2, data[i]);
        }
    }
    else
    {
        std::cout << "HERE, data is null" << std::endl;
        // jdata = nullptr;
    }
}

// The following look trivial but there is some work in a header-only
// library hidden in the assignments so we can give the inlining of that code a
// natural place to stop right here.

void Bool32ToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const uint32_t& data)
{
    std::cout << "HERE, Bool32ToDive val = " << std::to_string(static_cast<bool>(data)) << std::endl;

    // data_map = static_cast<bool>(data);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const short& data)
{
    std::cout << "HERE, FieldToDive, short" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const int& data)
{
    std::cout << "HERE, FieldToDive, int" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long& data)
{
    std::cout << "HERE, FieldToDive, long" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const long long& data)
{
    std::cout << "HERE, FieldToDive, long long" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned short& data)
{
    std::cout << "HERE, FieldToDive, unsigned short" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned int& data)
{
    std::cout << "HERE, FieldToDive, unsigned int" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long& data)
{
    std::cout << "HERE, FieldToDive, unsigned long" << std::endl;
    // // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const unsigned long long& data)
{
    std::cout << "HERE, FieldToDive, unsigned long long" << std::endl;
    //// jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const std::nullptr_t data)
{
    std::cout << "HERE, FieldToDive, unsigned nullptr_t" << std::endl;
    // jdata = data;
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, float data)
{
    std::cout << "HERE, FieldToDive, data" << std::endl;
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

#if defined(D3D12_SUPPORT)

// const char * might be better to avoid two copies of each string in the process at runtime (one in the static data
// section for the literal string and one on the heap in the map). Even better would be for this to be a const array of
// pairs of HRESULT and const char*const with a flat_map style adaptor so the "map" itself could live in the const data
// section rather than being heap allocated as it is now. Possibly expand with more from
// <https://learn.microsoft.com/en-us/windows/win32/com/com-error-codes-10> as docs for
// D3D12_DEVICE_REMOVED_EXTENDED_DATA1's HRESULT member lead there.
const static std::unordered_map<HRESULT, std::string> kHresults{
    // Basic names for zero and one from <winerror.h> also used by D3D12:
    { S_OK, "S_OK" },
    { S_FALSE, "S_FALSE" },
    // D3D12 Errors from <winerror.h>:
    // <https://learn.microsoft.com/en-us/windows/win32/direct3d12/d3d12-graphics-reference-returnvalues>
    { D3D12_ERROR_ADAPTER_NOT_FOUND, "D3D12_ERROR_ADAPTER_NOT_FOUND" },
    { D3D12_ERROR_DRIVER_VERSION_MISMATCH, "D3D12_ERROR_DRIVER_VERSION_MISMATCH" },
    { D3D12_ERROR_INVALID_REDIST, "D3D12_ERROR_INVALID_REDIST" },
    // D3D9 Errors inherited by D3D12:
    { D3DERR_INVALIDCALL, "D3DERR_INVALIDCALL" },
    { D3DERR_WASSTILLDRAWING, "D3DERR_WASSTILLDRAWING" },
    // DXGI Errors from <winerror.h>:
    // https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-error
    { DXGI_ERROR_ACCESS_DENIED, "DXGI_ERROR_ACCESS_DENIED" },
    { DXGI_ERROR_ACCESS_LOST, "DXGI_ERROR_ACCESS_LOST" },
    { DXGI_ERROR_ALREADY_EXISTS, "DXGI_ERROR_ALREADY_EXISTS" },
    { DXGI_ERROR_CANNOT_PROTECT_CONTENT, "DXGI_ERROR_CANNOT_PROTECT_CONTENT" },
    { DXGI_ERROR_DEVICE_HUNG, "DXGI_ERROR_DEVICE_HUNG" },
    { DXGI_ERROR_DEVICE_REMOVED, "DXGI_ERROR_DEVICE_REMOVED" },
    { DXGI_ERROR_DEVICE_RESET, "DXGI_ERROR_DEVICE_RESET" },
    { DXGI_ERROR_DRIVER_INTERNAL_ERROR, "DXGI_ERROR_DRIVER_INTERNAL_ERROR" },
    { DXGI_ERROR_FRAME_STATISTICS_DISJOINT, "DXGI_ERROR_FRAME_STATISTICS_DISJOINT" },
    { DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE, "DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE" },
    { DXGI_ERROR_INVALID_CALL, "DXGI_ERROR_INVALID_CALL" },
    { DXGI_ERROR_MORE_DATA, "DXGI_ERROR_MORE_DATA" },
    { DXGI_ERROR_NAME_ALREADY_EXISTS, "DXGI_ERROR_NAME_ALREADY_EXISTS" },
    { DXGI_ERROR_NONEXCLUSIVE, "DXGI_ERROR_NONEXCLUSIVE" },
    { DXGI_ERROR_NOT_CURRENTLY_AVAILABLE, "DXGI_ERROR_NOT_CURRENTLY_AVAILABLE" },
    { DXGI_ERROR_NOT_FOUND, "DXGI_ERROR_NOT_FOUND" },
    { DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED, "DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED" },
    { DXGI_ERROR_REMOTE_OUTOFMEMORY, "DXGI_ERROR_REMOTE_OUTOFMEMORY" },
    { DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE, "DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE" },
    { DXGI_ERROR_SDK_COMPONENT_MISSING, "DXGI_ERROR_SDK_COMPONENT_MISSING" },
    { DXGI_ERROR_SESSION_DISCONNECTED, "DXGI_ERROR_SESSION_DISCONNECTED" },
    { DXGI_ERROR_UNSUPPORTED, "DXGI_ERROR_UNSUPPORTED" },
    { DXGI_ERROR_WAIT_TIMEOUT, "DXGI_ERROR_WAIT_TIMEOUT" },
    { DXGI_ERROR_WAS_STILL_DRAWING, "DXGI_ERROR_WAS_STILL_DRAWING" },
    // Extra OLE Codes from <winerror.h> (we should never see these from DX12/DXGI but just in case):
    { E_UNEXPECTED, "E_UNEXPECTED" },
    { E_NOINTERFACE, "E_NOINTERFACE" },
    { E_POINTER, "E_POINTER" },
    { E_HANDLE, "E_HANDLE" },
    { E_ABORT, "E_ABORT" },
    { E_ACCESSDENIED, "E_ACCESSDENIED" },
    // Misc errors:
    { E_FAIL, "E_FAIL" },
    { E_OUTOFMEMORY, "E_OUTOFMEMORY" },
    { E_INVALIDARG, "E_INVALIDARG" },
    { E_NOTIMPL, "E_NOTIMPL" },
};

/// @brief Turn a D3D12 or DXGI HRESULT into a string with the same character
/// sequence as the identifier of the C macro defining it in a header like
/// winerror.h.
/// @param hresult A D3D12 or DXGI result code.
std::string HresultToString(const HRESULT hresult)
{
    const auto  found = kHresults.find(hresult);
    std::string result;
    if (found != kHresults.end())
    {
        result = found->second;
    }
    else
    {
        result = util::to_hex_variable_width(static_cast<unsigned long>(hresult));
        GFXRECON_LOG_DEBUG("HresultToString() passed unkown HRESULT: %s.", result.c_str());
    }
    return result;
}

void HresultToJson(nlohmann::ordered_json& jdata, const HRESULT hresult, const util::JsonOptions& options)
{
    FieldToJson(jdata, HresultToString(hresult), options);
}

void FieldToJson(nlohmann::ordered_json&                                  jdata,
                 const format::InitDx12AccelerationStructureGeometryDesc& data,
                 const util::JsonOptions&                                 options)
{
    /// @todo handle enums and so on.
    FieldToJson(jdata["geometry_type"], static_cast<D3D12_RAYTRACING_GEOMETRY_TYPE>(data.geometry_type), options);
    FieldToJson_D3D12_RAYTRACING_GEOMETRY_FLAGS(
        jdata["geometry_flags"], static_cast<D3D12_RAYTRACING_GEOMETRY_FLAGS>(data.geometry_flags), options);
    FieldToJson(jdata["aabbs_count"], data.aabbs_count, options);
    FieldToJson(jdata["aabbs_stride"], data.aabbs_stride, options);
    Bool32ToJson(jdata["triangles_has_transform"], data.triangles_has_transform, options);
    FieldToJson(jdata["triangles_index_format"], static_cast<DXGI_FORMAT>(data.triangles_index_format), options);
    FieldToJson(jdata["triangles_vertex_format"], static_cast<DXGI_FORMAT>(data.triangles_vertex_format), options);
    FieldToJson(jdata["triangles_index_count"], data.triangles_index_count, options);
    FieldToJson(jdata["triangles_vertex_count"], data.triangles_vertex_count, options);
    FieldToJson(jdata["triangles_vertex_stride"], data.triangles_vertex_stride, options);
}

void FieldToJson(nlohmann::ordered_json& jdata, const format::DxgiAdapterDesc& data, const util::JsonOptions& options)
{
    FieldToJson(jdata["Description"], std::wstring_view(data.Description), options);
    FieldToJson(jdata["VendorId"], data.VendorId, options);
    FieldToJson(jdata["DeviceId"], data.DeviceId, options);
    FieldToJson(jdata["SubSysId"], data.SubSysId, options);
    FieldToJson(jdata["Revision"], data.Revision, options);
    FieldToJson(jdata["DedicatedVideoMemory"], data.DedicatedVideoMemory, options);
    FieldToJson(jdata["DedicatedSystemMemory"], data.DedicatedSystemMemory, options);
    FieldToJson(jdata["SharedSystemMemory"], data.SharedSystemMemory, options);
    FieldToJson(jdata["LuidLowPart"], data.LuidLowPart, options);
    FieldToJson(jdata["LuidHighPar"], data.LuidHighPart, options);
    // Should we break out the packed data? (2 bits (LSB) to store Type and 30 bits for object ID)
    FieldToJson(jdata["extra_info"], data.extra_info, options);
}

void FieldToJson(nlohmann::ordered_json& jdata, const format::Dx12RuntimeInfo& data, const util::JsonOptions& options)
{
    FieldToJson(jdata["version"], data.version, util::filepath::kFileVersionSize, options);
    FieldToJson(jdata["src"], util::strings::ViewOfCharArray(data.src, util::filepath::kMaxFilePropertySize), options);
}

void FieldToJson(nlohmann::ordered_json& jdata, const util::filepath::FileInfo& data, const util::JsonOptions& options)
{
    FieldToJson(jdata["ProductVersion"],
                strings::ViewOfCharArray(data.ProductVersion, filepath::kMaxFilePropertySize),
                options);
    FieldToJson(
        jdata["FileVersion"], strings::ViewOfCharArray(data.FileVersion, filepath::kMaxFilePropertySize), options);
    FieldToJson(jdata["AppVersion"], data.AppVersion, filepath::kMaxFilePropertySize, options);
    FieldToJson(jdata["AppName"], strings::ViewOfCharArray(data.AppName, filepath::kMaxFilePropertySize), options);
    FieldToJson(
        jdata["CompanyName"], strings::ViewOfCharArray(data.CompanyName, filepath::kMaxFilePropertySize), options);
    FieldToJson(jdata["FileDescription"],
                strings::ViewOfCharArray(data.FileDescription, filepath::kMaxFilePropertySize),
                options);
    FieldToJson(
        jdata["InternalName"], strings::ViewOfCharArray(data.InternalName, filepath::kMaxFilePropertySize), options);
    FieldToJson(jdata["OriginalFilename"],
                strings::ViewOfCharArray(data.OriginalFilename, filepath::kMaxFilePropertySize),
                options);
    FieldToJson(
        jdata["ProductName"], strings::ViewOfCharArray(data.ProductName, filepath::kMaxFilePropertySize), options);
}

#endif

static std::string GenerateFilename(const std::string_view filename, const uint64_t instance_counter)
{
    std::string fullname{ filename };
    return fullname.append("-").append(std::to_string(instance_counter)).append(".bin");
}

static bool WriteBinaryFile(const std::string& filename, uint64_t data_size, const uint8_t* data)
{
    FILE* file_output = nullptr;
    bool  written_all = false;
    if (util::platform::FileOpen(&file_output, filename.c_str(), "wb") == 0)
    {
        written_all = util::platform::FileWrite(data, static_cast<size_t>(data_size), file_output);
        if (!written_all)
        {
            GFXRECON_LOG_ERROR("Failed to write %" PRIu64 " bytes to file %s.", data_size, filename.c_str());
        }
        util::platform::FileClose(file_output);
    }
    else
    {
        GFXRECON_LOG_ERROR("Failed to open file %s for writing.", filename.c_str());
    }
    return written_all;
}

GFXRECON_END_NAMESPACE(util)
GFXRECON_END_NAMESPACE(gfxrecon)