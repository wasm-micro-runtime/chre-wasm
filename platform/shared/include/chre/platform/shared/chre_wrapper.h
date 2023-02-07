#ifndef _CHRE_WRAPPER_H_
#define _CHRE_WRAPPER_H_

#include "chre/platform/shared/chre_api_wrapper/audio_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/ble_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/common_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/event_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/gnss_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/nanoapp_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/re_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/sensor_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/toolchain_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/user_settings_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/version_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/wifi_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/wwan_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/nanoapp_support_wasm_wrapper.h"
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

#ifdef __cplusplus
}
#endif

#endif