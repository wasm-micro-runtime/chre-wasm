#include "chre/platform/shared/chre_api_wrapper/wrapper_data_map.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif
static std::map<wasm_module_inst_t, std::map<const void* ,uint32_t> > eventDataMap;
uint32_t getOffset(wasm_module_inst_t WasmModuleInst, const void *nativeData) {
    uint32_t offset = 0;
    auto moduleMap = eventDataMap.find(WasmModuleInst);
    if (eventDataMap.end() ==  moduleMap) {
        eventDataMap[WasmModuleInst] = std::map<const void* ,uint32_t>();
        moduleMap = eventDataMap.find(WasmModuleInst);
    }
    auto result = moduleMap->second.find(nativeData);
    if (moduleMap->second.end() != result) {
       offset = result->second; 
    }
    return offset;
}
bool setNativeData(wasm_module_inst_t WasmModuleInst, const void *nativeData, uint32_t dataOffset) {
    bool state = true;
    auto moduleMap = eventDataMap.find(WasmModuleInst);
    if (eventDataMap.end() ==  moduleMap) {
        eventDataMap[WasmModuleInst] = std::map<const void* ,uint32_t>();
        moduleMap = eventDataMap.find(WasmModuleInst);
    }
    auto result = moduleMap->second.find(nativeData);
    if (moduleMap->second.end() != result) {
        state = false; 
    } else {
        moduleMap->second[nativeData] = dataOffset;
    }
    return state;
}
bool delNativeData(wasm_module_inst_t WasmModuleInst, const void *nativeData) {
    bool state = true;
    auto moduleMap = eventDataMap.find(WasmModuleInst);
    if (eventDataMap.end() ==  moduleMap) {
        eventDataMap[WasmModuleInst] = std::map<const void* ,uint32_t>();
        moduleMap = eventDataMap.find(WasmModuleInst);
        state = false;
    }
    auto result = moduleMap->second.find(nativeData);
    if (state) {
        if (moduleMap->second.end() == result) {
            state = false; 
        } else {
            moduleMap->second.erase(result);
        }
    }
    return state;
}
bool delModuleInstanceMap(wasm_module_inst_t WasmModuleInst) {
    bool state = false;
    auto moduleMap = eventDataMap.find(WasmModuleInst);
    if (eventDataMap.end() !=  moduleMap) {
        eventDataMap.erase(moduleMap);
        state = true;
    }
    return state;
}

#ifdef __cplusplus
}
#endif