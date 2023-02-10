
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
#include "chre/platform/shared/chre_api_wrapper/event_transform.h"
#include "chre/platform/shared/chre_wrapper.h"
/* clang format off */

//! This marco is used for all switch cases in function copyEventFromNativeToWASM
#define NATIVE_TO_WASM(type, offset, from)                                \
    do {                                                                  \
        offset = type##WrapperCopiedFromNative(                           \
                    WasmModuleInst, (const type*)(from));      \
    } while(0);

#define WASM_TO_NATIVE(type, offset, to)                    \
    do {                                                    \
        to = type##CopiedFromWASM(WasmModuleInst, offset);  \
    } while(0);

#define FREE_WASM_EVENT(type, offset)                       \
    do {                                                    \
        type##WrapperRelease(WasmModuleInst, offset);       \
    } while(0);

#define FREE_NATIVE_EVENT(type, pointer)                                      \
    do {                                                                      \
        type##Release(static_cast<type*>(const_cast<void*>(pointer)));        \
    } while(0);
/* clang format on */

#ifdef __cplusplus
extern "C" {
#endif

uint32_t copyEventFromNativeToWASM(wasm_module_inst_t WasmModuleInst, 
                        uint16_t eventType, const void *eventData) {
    uint32_t eventDataForWASM = 0;
    switch (eventType) {
        //struct ChreAudioSourceStatusEvent
        case CHRE_EVENT_AUDIO_SAMPLING_CHANGE:
            NATIVE_TO_WASM(chreAudioSourceStatusEvent, \
                           eventDataForWASM,           \
                           eventData)
        break;
    }
    return eventDataForWASM;
}

void* copyEventFromWASMToNative(wasm_module_inst_t WasmModuleInst, 
                        uint16_t eventType, uint32_t eventDataForWASM) {
    void *eventData = nullptr;
    switch (eventType) {
        case CHRE_EVENT_AUDIO_SAMPLING_CHANGE:
        //todo: use a allocator to allocate memory for structure
        WASM_TO_NATIVE(chreAudioSourceStatusEvent, eventDataForWASM,\
                       eventData)
        break;
    }
    return eventData;
}

void freeEventFromWASM(wasm_module_inst_t WasmModuleInst, 
                        uint16_t eventType, uint32_t eventDataForWASM) {
    switch (eventType) {
        case CHRE_EVENT_AUDIO_SAMPLING_CHANGE:
        FREE_WASM_EVENT(chreAudioSourceStatusEvent, eventDataForWASM)
        break;
    }
}
void freeEventFromNative(uint16_t eventType, void *eventData) {
    switch (eventType) {
        case CHRE_EVENT_AUDIO_SAMPLING_CHANGE:
        FREE_NATIVE_EVENT(chreAudioSourceStatusEvent, eventData);
        break;
    }
}

chreEventCompleteFunction* getCompleteFunction(uint32_t eventType) {
    return nullptr;
}
#ifdef __cplusplus
}
#endif
