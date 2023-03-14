#include "chre/version.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifndef _VERSION_WRAPPER_H_
#define _VERSION_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

uint32_t chreGetApiVersionWrapper(wasm_exec_env_t exec_env);

uint32_t chreGetVersionWrapper(wasm_exec_env_t exec_env);

uint64_t chreGetPlatformIdWrapper(wasm_exec_env_t exec_env);

#ifdef __cplusplus
}
#endif
#endif