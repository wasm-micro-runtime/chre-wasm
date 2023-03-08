#ifndef _WRAPPER_DATA_MAP_H_
#define _WRAPPER_DATA_MAP_H_
#include <map>
#include "wasm_export.h"
#ifdef __cplusplus
extern "C" {
#endif

uint32_t getOffset(wasm_module_inst_t WasmModuleInst, void *nativeData);
bool setNativeData(wasm_module_inst_t WASMModuleInst, void *nativeData, uint32 dataOffset) {
bool delNativeData(wasm_module_inst_t WasmModuleInst, void *nativeData);
#ifdef __cplusplus
}#endif

#endif