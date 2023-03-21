#ifndef _WWAN_WRAPPER_H_
#define _WWAN_WRAPPER_H_

#include "chre/wwan.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

//! for struct chreWwanCellInfoResult
CONVERSION_FUNCTIONS_DECLARATION(chreWwanCellInfoResult);

uint32_t chreWwanGetCapabilitiesWrapper(wasm_exec_env_t exec_env);


bool chreWwanGetCellInfoAsyncWrapper(wasm_exec_env_t exec_env, const void *cookie);

#ifdef __cplusplus
}
#endif

#endif