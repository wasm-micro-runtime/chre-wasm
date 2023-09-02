
#include "chre/platform/shared/chre_api_wrapper/re_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

uint64_t chreGetAppIdWrapper(wasm_exec_env_t exec_env) {
    return chreGetAppId();
}

uint32_t chreGetInstanceIdWrapper(wasm_exec_env_t exec_env) {
    return chreGetInstanceId();
}


/**
 * @note we firstly output string to a buffer 'data' in wasm
*/
void chreLogWrapper(wasm_exec_env_t exec_env, enum chreLogLevel level, const char *formatStr, const char* data) {
    chreLog(level, formatStr, data);
}

uint64_t chreGetTimeWrapper(wasm_exec_env_t exec_env){
    return chreGetTime();
}

int64_t chreGetEstimatedHostTimeOffsetWrapper(wasm_exec_env_t exec_env){
    return chreGetEstimatedHostTimeOffset();
}

uint32_t chreTimerSetWrapper(wasm_exec_env_t exec_env, uint64_t duration, const void *cookie, bool oneShot){
    return chreTimerSet(duration, cookie, oneShot);
}

bool chreTimerCancelWrapper(wasm_exec_env_t exec_env, uint32_t timerId) {
    return chreTimerCancel(timerId);
}

void chreAbortWrapper(wasm_exec_env_t exec_env, uint32_t abortCode) {
    chreAbort(abortCode);
}

uint32_t chreHeapAllocWrapper(wasm_exec_env_t exec_env, uint32_t bytes) {
    wasm_module_inst_t WasmModuleInst  = wasm_runtime_get_module_inst(exec_env);
    return wasm_runtime_module_malloc(WasmModuleInst, bytes, NULL);
}

void chreHeapFreeWrapper(wasm_exec_env_t exec_env, uint32_t ptr){
    wasm_module_inst_t WasmModuleInst  = wasm_runtime_get_module_inst(exec_env);
    wasm_runtime_module_free(WasmModuleInst, ptr);
}
/**
 * @note we firstly output string to a buffer 'data' in wasm
*/
void chreDebugDumpLogWrapper(wasm_exec_env_t exec_env, const char *formatStr, const char* data) {
    chreDebugDumpLog(formatStr, data);
}

#ifdef __cplusplus
}
#endif
