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
uint64_t chreGetAppIdWrapper(wasm_exec_env_t exec_env);

uint32_t chreGetInstanceIdWrapper(wasm_exec_env_t exec_env);

void chreLogWrapper(wasm_exec_env_t exec_env, enum chreLogLevel level, const char *formatStr, _va_list va_args);

uint64_t chreGetTimeWrapper(wasm_exec_env_t exec_env);

int64_t chreGetEstimatedHostTimeOffsetWrapper(wasm_exec_env_t exec_env);

uint32_t chreTimerSetWrapper(wasm_exec_env_t exec_env, uint64_t duration, const void *cookie, bool oneShot);

bool chreTimerCancelWrapper(wasm_exec_env_t exec_env, uint32_t timerId);

void chreAbortWrapper(wasm_exec_env_t exec_env, uint32_t abortCode);

uint32_t chreHeapAllocWrapper(wasm_exec_env_t exec_env, uint32_t bytes);

void chreHeapFreeWrapper(wasm_exec_env_t exec_env, uint32_t ptr);

void chreDebugDumpLogWrapper(wasm_exec_env_t exec_env, const char *formatStr, _va_list va_args);

#ifdef __cplusplus
}
#endif
#endif