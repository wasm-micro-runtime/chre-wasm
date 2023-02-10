
#ifndef _EVENT_TRANSFORM_H_
#define _EVENT_TRANSFORM_H_
#include "chre/platform/shared/chre_api_wrapper/event_transform.h"
#include "wasm_export.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t copyEventFromNativeToWASM(wasm_module_inst_t WasmModuleInst, 
                        uint16_t eventType, const void *eventData);

void* copyEventFromWASMToNative(wasm_module_inst_t WasmModuleInst, 
                        uint16_t eventType, uint32_t eventDataForWASM);

void freeEventFromWASM(wasm_module_inst_t WasmModuleInst, 
                        uint16_t eventType, uint32_t eventDataForWASM);

void freeEventFromNative(uint16_t eventType, void *eventData);

chreEventCompleteFunction* getCompleteFunction(uint32_t eventType);
#ifdef __cplusplus
}
#endif

#endif
