
#ifndef _EVENT_TRANSFORM_H_
#define _EVENT_TRANSFORM_H_

#include "chre/platform/shared/chre_api_wrapper/event_transform.h"
#include "wasm_export.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct convertFunctions {
    uint32_t eventType;
    uint32_t (*native2Wasm)(wasm_module_inst_t ,  const void *);
    void* (*wasm2Native)(wasm_module_inst_t , uint32_t);
    void (*wasmRelease)(wasm_module_inst_t, uint32_t);
    void (*nativeRelease)(void *);
}convertFunctions;

const convertFunctions* getConvertFunctions(const uint32_t type);
#ifdef __cplusplus
}
#endif

#endif
