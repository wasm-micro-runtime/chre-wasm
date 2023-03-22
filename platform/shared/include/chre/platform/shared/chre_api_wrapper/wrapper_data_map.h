#ifndef _WRAPPER_DATA_MAP_H_
#define _WRAPPER_DATA_MAP_H_

#include <map>
#include "wasm_export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the offset mapping to nativeData in WASM Module instance
 * @param WASMModuleInst the WASM module instance to find a offset
 * @param nativeData the native data to be mapped to the offset
*/
uint32_t getOffset(wasm_module_inst_t WASMModuleInst, const void *nativeData);
bool setNativeData(wasm_module_inst_t WASMModuleInst, const void *nativeData, uint32_t dataOffset);
bool delNativeData(wasm_module_inst_t WASMModuleInst, const void *nativeData);
bool delModuleInstanceMap(wasm_module_inst_t WASMModuleInst);

#ifdef __cplusplus
}
#endif
#endif