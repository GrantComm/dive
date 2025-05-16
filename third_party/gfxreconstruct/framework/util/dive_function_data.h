
#ifndef DIVE_FUNCTION_DATA_H
#define DIVE_FUNCTION_DATA_H

#include "util/defines.h"
#include "../../external/nlohmann/include/nlohmann/json.hpp"
#include <cstdint>
#include <string>


GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(util)

class DiveFunctionData
{
  public:
  DiveFunctionData(std::string name, uint32_t cmd_buffer_index, uint64_t block_index, nlohmann::ordered_json args);

  std::string GetFunctionName();
  uint32_t GetCmdBufferIndex();
  uint64_t GetBlockIndex();
  nlohmann::ordered_json GetArgs();

  std::string name_;
  uint32_t cmd_buffer_index_;
  uint64_t block_index_;
  nlohmann::ordered_json args_;
};

GFXRECON_END_NAMESPACE(util)
GFXRECON_END_NAMESPACE(gfxrecon)
#endif // DIVE_FUNCTION_DATA_HH
