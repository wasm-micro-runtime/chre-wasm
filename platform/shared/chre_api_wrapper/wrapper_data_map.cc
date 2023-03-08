#include "chre/platform/shared/chre_api_wrapper/wrapper_data_map.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif
static std::map<wasm_module_inst_t, std::map<void* ,uint32_t>> eventDataMap;
uint32_t getOffset(wasm_module_inst_t WASMModuleInst, void *nativeData) {
    uint32_t offset = 0;
    auto moduleMap = eventDataMap.find(WASMModuleInst);
    if (eventDataMap.end() ==  moduleMap) {
        eventDataMap[WASMModuleInst] = std::map<void* ,uint32_t>();
    }
    auto result = moduleMap.find(nativeData);
    if (moduleMap.end() != result) {
       offset = result->second; 
    }
    return offset;
}
bool setNativeData(wasm_module_inst_t WASMModuleInst, void *nativeData, uint32 dataOffset) {
    bool state = true;
    auto moduleMap = eventDataMap.find(WASMModuleInst);
    if (eventDataMap.end() ==  moduleMap) {
        eventDataMap[WASMModuleInst] = std::map<void* ,uint32_t>();
    }
    auto result = moduleMap.find(nativeData);
    if (moduleMap.end() != result) {
        state = false; 
    } else {
        moduleMap[nativeData] = dataOffset;
    }
    return state;
}
bool delNativeData(wasm_module_inst_t WasmModuleInst, void *nativeData) {
    bool state = true;
    auto moduleMap = eventDataMap.find(WASMModuleInst);
    if (eventDataMap.end() ==  moduleMap) {
        eventDataMap[WASMModuleInst] = std::map<void* ,uint32_t>();
    }
    auto result = moduleMap.find(nativeData);
    if (moduleMap.end() == result) {
        state = false; 
    } else {
        moduleMap.erase(result);
    }
    return state;
}

#ifdef __cplusplus
}
#endif