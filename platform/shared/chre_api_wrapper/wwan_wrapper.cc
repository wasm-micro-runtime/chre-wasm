#include "chre/util/macros.h"
#include "chre/platform/shared/chre_api_wrapper/wwan_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

NATIVE_TO_WASM_FUNCTION_DECLARATION(chreWwanCellInfoResult) {
    const struct chreWwanCellInfoResult* native_event = NULL;
    
    uint32_t offset_event = 0;
    uint32_t offset_event_cells = 0;

    struct chreWwanCellInfoResult *pointer_event  = NULL;
    struct chreWwanCellInfo *pointer_event_cells  = NULL;

    uint8_t *dataBuffer = NULL;
    uint8_t *nowBuffer = NULL;

    uint32_t totalSize = 0;
    uint32_t secondLevelSize = 0;
    if(!WasmModuleInst || !nativeData) {
        goto fail0;
    }
    native_event = reinterpret_cast<const struct chreWwanCellInfoResult*>(nativeData);
    
    // caculate the size of level 1
    totalSize += sizeof(struct chreWwanCellInfoResult);
    // calculate the size o level 2
    secondLevelSize = native_event->cellInfoCount * sizeof(*native_event->cells);
    totalSize += secondLevelSize;

    offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,
                        reinterpret_cast<void**>(&dataBuffer));
    if (!offset_event) {
        LOGE("Allocate memory for struct chreWwanCellInfoResult in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;

    // copy level 1
    pointer_event = reinterpret_cast<struct chreWwanCellInfoResult*>(nowBuffer);
    nowBuffer += sizeof(struct chreWwanCellInfoResult);
    memcpy(pointer_event, native_event, sizeof(struct chreWwanCellInfoResult));
    // copy level 2
    offset_event_cells = wasm_runtime_addr_native_to_app(WasmModuleInst,
                                reinterpret_cast<void*>(nowBuffer));
    pointer_event_cells = reinterpret_cast<chreWwanCellInfo *>(nowBuffer);
    nowBuffer += secondLevelSize;
    memcpy(pointer_event_cells, native_event->cells, secondLevelSize);

    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreWwanCellInfoResult");
        goto fail1;
    }
    // link level 2 to level 1
    pointer_event->cells = 
            reinterpret_cast<const struct chreWwanCellInfo *>(offset_event_cells);
    if (native_event->cookie)    
        pointer_event->cookie = reinterpret_cast<void*>(
            wasm_runtime_addr_native_to_app(WasmModuleInst, const_cast<void*>(native_event->cookie)));
    
    return offset_event;
fail1:
    wasm_runtime_module_free(WasmModuleInst, offset_event);
fail0:
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreWwanCellInfoResult) {
    const struct chreWwanCellInfoResult *wasm_event = NULL;
    const struct chreWwanCellInfo *wasm_event_cells = NULL;

    struct chreWwanCellInfoResult *pointer_event  = NULL;
    struct chreWwanCellInfo *pointer_event_cells  = NULL;

    uint8_t *dataBuffer = NULL;
    uint8_t *nowBuffer = NULL;

    uint32_t totalSize = 0;
    uint32_t secondLevelSize = 0;
    if(!WasmModuleInst || !eventDataForWASM) {
        goto fail0;
    }
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                    sizeof(struct chreWwanCellInfoResult))){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0; 
    }
    wasm_event = reinterpret_cast<const struct chreWwanCellInfoResult*>(
        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));
    
    // caculate the size of level 1
    totalSize += sizeof(struct chreWwanCellInfoResult);
    // calculate the size of level 2
    secondLevelSize = wasm_event->cellInfoCount * sizeof(*wasm_event->cells);
    totalSize += secondLevelSize;
    // validate level 2
    if (!wasm_runtime_validate_app_addr(WasmModuleInst,
                    reinterpret_cast<uint32_t>(wasm_event->cells),
                    wasm_event->cellInfoCount * sizeof(*wasm_event->cells))){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0; 
    }
    wasm_event_cells = reinterpret_cast<const struct chreWwanCellInfo *>(
        wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->cells)));

    // allocate memory
    dataBuffer = reinterpret_cast<uint8_t*>(chreHeapAlloc(totalSize));
    if (!dataBuffer) {
        LOGE("Allocate memory for struct chreWwanCellInfoResult in Native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;

    // copy level 1
    pointer_event = reinterpret_cast<struct chreWwanCellInfoResult*>(nowBuffer);
    nowBuffer += sizeof(struct chreWwanCellInfoResult);
    memcpy(pointer_event, wasm_event, sizeof(struct chreWwanCellInfoResult));
    // copy level 2
    pointer_event_cells = reinterpret_cast<chreWwanCellInfo *>(nowBuffer);
    nowBuffer += secondLevelSize;
    memcpy(pointer_event_cells, wasm_event_cells, secondLevelSize);

    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in wasm2native: struct chreWwanCellInfoResult");
        goto fail1;
    }
    // link level 2 to level 1
    pointer_event->cells = pointer_event_cells;
    if (wasm_event->cookie)
        pointer_event->cookie = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                            reinterpret_cast<uint32_t>(wasm_event->cookie));
    return pointer_event;
fail1:
    chreHeapFree(dataBuffer);
fail0:
    return 0;
}


uint32_t chreWwanGetCapabilitiesWrapper(wasm_exec_env_t exec_env) {
    return  chreWwanGetCapabilities();
}


bool chreWwanGetCellInfoAsyncWrapper(wasm_exec_env_t exec_env, const void *cookie) {
    return chreWwanGetCellInfoAsync(cookie);
}

#ifdef __cplusplus
}
#endif