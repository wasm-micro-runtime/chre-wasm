#include "chre/platform/shared/chre_api_wrapper/version_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"


uint32_t chreGetApiVersionWrapper(wasm_exec_env_t exec_env) { 
    return chreGetApiVersion();
}

uint32_t chreGetVersionWrapper(wasm_exec_env_t exec_env) {
    return chreGetVersion();
}

uint64_t chreGetPlatformIdWrapper(wasm_exec_env_t exec_env) {
    return chreGetPlatformId();
}
