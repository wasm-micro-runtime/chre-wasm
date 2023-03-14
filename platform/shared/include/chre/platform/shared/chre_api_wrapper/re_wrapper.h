#ifndef _RE_WRAPPER_H_
#define _RE_WRAPPER_H_

#include "chre/re.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace {
    typedef char *_va_list; 
}
uint64_t chreGetAppIdWapper(wasm_exec_env_t exec_env);

uint32_t chreGetInstanceIdWapper(wasm_exec_env_t exec_env);
/**
 * @todo complete it
*/
void chreLogWapper(wasm_exec_env_t exec_env, enum chreLogLevel level, const char *formatStr, _va_list va_args);

uint64_t chreGetTimeWapper(wasm_exec_env_t exec_env);

int64_t chreGetEstimatedHostTimeOffsetWapper(wasm_exec_env_t exec_env);

uint32_t chreTimerSetWapper(wasm_exec_env_t exec_env, uint64_t duration, const void *cookie, bool oneShot);

bool chreTimerCancelWapper(wasm_exec_env_t exec_env, uint32_t timerId);

void chreAbortWapper(wasm_exec_env_t exec_env, uint32_t abortCode);

uint32_t chreHeapAllocWapper(wasm_exec_env_t exec_env, uint32_t bytes);

void chreHeapFreeWapper(wasm_exec_env_t exec_env, uint32_t ptr);

void chreDebugDumpLogWapper(wasm_exec_env_t exec_env, const char *formatStr, _va_list va_args);

#ifdef __cplusplus
}
#endif
#endif