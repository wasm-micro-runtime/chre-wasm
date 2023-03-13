#include "chre/platform/shared/chre_api_wrapper/common_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include <stddef.h>
#include <memory.h>
#include "wasm_export.h"

#ifdef __cplusplus
extern "C" {
#endif

NATIVE_TO_WASM_FUNCTION_DECLARATION(chreAsyncResult) {
    const struct chreAsyncResult *native_event = 
            reinterpret_cast<const struct chreAsyncResult *>(nativeData);

    uint32_t offset_event = 0;

    struct chreAsyncResult *pointer_event = NULL;
    offset_event = wasm_runtime_module_malloc(WasmModuleInst, sizeof(struct chreAsyncResult),
                                                        reinterpret_cast<void**>(&pointer_event));
    if(!offset_event) {
        LOGE("Allocate memory for struct chreAsyncResult in Wasm failed");
        goto fail0;
    }
    memcpy(pointer_event, native_event, offsetof(struct chreAsyncResult, cookie));
    pointer_event->cookie = reinterpret_cast<const void*>(
            wasm_runtime_addr_native_to_app(WasmModuleInst, const_cast<void*>(native_event->cookie)));
    return offset_event;
fail0:
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreAsyncResult) {
    const struct chreAsyncResult *wasm_event =NULL;
    
    struct chreAsyncResult *pointer_event = NULL;
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM, sizeof(struct chreAsyncResult))) {
        LOGE("Try to copied wasm memory out of boundary");
        goto fail;
    }
    if (!(pointer_event = 
            reinterpret_cast<struct chreAsyncResult*>(chreHeapAlloc(sizeof(struct chreAsyncResult))))) {
        LOGE("Allocate memory for struct chreAsyncResult in Native failed!");    
    }
    wasm_event = reinterpret_cast<const struct chreAsyncResult *>(
                    wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));
    memcpy(pointer_event, wasm_event, offsetof(struct chreAsyncResult, cookie));
    pointer_event->cookie = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                    reinterpret_cast<uint32_t>(wasm_event->cookie));
    return pointer_event;
fail:
    return nullptr;
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreAsyncResult) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreAsyncResult) {
    chreHeapFree(nativeData);
}

#ifdef __cplusplus
}
#endif