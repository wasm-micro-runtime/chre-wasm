#include "chre/platform/shared/chre_api_wrapper/common_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include <stddef.h>
#include <memory.h>
#include "wasm_export.h"

#ifdef __cplusplus
extern "C" {
#endif

//! struct chreAsyncResult begin
uint32_t chreAsyncResultWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                const chreAsyncResult *eventData) {
    uint32_t structDataOffset = 0;
    chreAsyncResultWrapper *structData = NULL;
    if (!eventData) {
        goto fail;
    }
    structDataOffset = wasm_runtime_module_malloc(WasmModuleInst,
                                                  sizeof(chreAsyncResultWrapper),
                                                  reinterpret_cast<void**>(&structData));
    if(!structDataOffset) {
        goto fail;
    }
    //! copy the part of the struct chreAsyncResult
    memcpy(structData, eventData, offsetof(chreAsyncResultWrapper, cookiePointer));
    //! the cookie must be passed from the same nanoapp
    /**
     * @todo maybe we need to discuss what the value of nullptr is here
    */
    structData->cookiePointer = wasm_runtime_addr_native_to_app(WasmModuleInst,
                                            const_cast<void*>(eventData->cookie));
    return structDataOffset;
fail:
    LOGE("Allocate memory for struct chreAsyncResult in Wasm failed");
    return 0;
}
chreAsyncResult *chreAsyncResultCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                               uint32_t eventDataForWASM) {
    chreAsyncResultWrapper *structData = nullptr;
    chreAsyncResult *eventData = nullptr;
    if(!(structData = static_cast<chreAsyncResultWrapper *> (
        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        goto fail;
    }
    if(!(eventData = static_cast<chreAsyncResult *>(
                        chreHeapAlloc(sizeof(chreAsyncResult))))) {
        goto fail;
    }
    memcpy(eventData, structData, offsetof(chreAsyncResultWrapper, cookiePointer));
    eventData->cookie = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                        structData->cookiePointer);
    return eventData;
fail:
    LOGE("Allocate memory for struct chreAsyncResult in Native failed!");
    return nullptr;
}

void chreAsyncResultWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

void chreAsyncResultRelease(chreAsyncResult *eventData) {
    chreHeapFree(eventData);
}

#ifdef __cplusplus
}
#endif