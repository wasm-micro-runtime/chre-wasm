
#include "chre/platform/shared/chre_api_wrapper/re_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

uint64_t chreGetAppIdWapper(wasm_exec_env_t exec_env) {
    return chreGetAppId();
}

uint32_t chreGetInstanceIdWapper(wasm_exec_env_t exec_env) {
    return chreGetInstanceId();
}

/**
 * @todo complete it
*/
void chreLogWapper(wasm_exec_env_t exec_env, enum chreLogLevel level, const char *formatStr, _va_list va_args) {
    /**chreLog*/
}

uint64_t chreGetTimeWapper(wasm_exec_env_t exec_env){
    return chreGetTime();
}

int64_t chreGetEstimatedHostTimeOffsetWapper(wasm_exec_env_t exec_env){
    return chreGetEstimatedHostTimeOffset();
}

uint32_t chreTimerSetWapper(wasm_exec_env_t exec_env, uint64_t duration, const void *cookie, bool oneShot){
    return chreTimerSet(duration, cookie, oneShot);
}

bool chreTimerCancelWapper(wasm_exec_env_t exec_env, uint32_t timerId) {
    return chreTimerCancel(timerId);
}

void chreAbortWapper(wasm_exec_env_t exec_env, uint32_t abortCode) {
    chreAbort(abortCode);
}

uint32_t chreHeapAllocWapper(wasm_exec_env_t exec_env, uint32_t bytes) {
    wasm_module_inst_t WasmModuleInst  = wasm_runtime_get_module_inst(exec_env);
    return wasm_runtime_module_malloc(WasmModuleInst, bytes, NULL);
}

void chreHeapFreeWapper(wasm_exec_env_t exec_env, uint32_t ptr){
    wasm_module_inst_t WasmModuleInst  = wasm_runtime_get_module_inst(exec_env);
    wasm_runtime_module_free(WasmModuleInst, ptr);
}
/**
 * @todo complete it
*/
void chreDebugDumpLogWapper(wasm_exec_env_t exec_env, const char *formatStr, _va_list va_args) {

}

#ifdef __cplusplus
}
#endif
