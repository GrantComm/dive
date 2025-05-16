#include "dive_function_data.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(util)

DiveFunctionData::DiveFunctionData(std::string name, uint32_t cmd_buffer_index, uint64_t block_index, nlohmann::ordered_json args) : name_(name), cmd_buffer_index_(cmd_buffer_index), block_index_(block_index), args_(args){}

std::string DiveFunctionData::GetFunctionName(){
    return name_;
}
uint32_t DiveFunctionData::GetCmdBufferIndex(){
    return cmd_buffer_index_;
}
uint64_t DiveFunctionData::GetBlockIndex(){
    return block_index_;
}
nlohmann::ordered_json DiveFunctionData::GetArgs(){
    return args_;
}

GFXRECON_END_NAMESPACE(util)
GFXRECON_END_NAMESPACE(gfxrecon)