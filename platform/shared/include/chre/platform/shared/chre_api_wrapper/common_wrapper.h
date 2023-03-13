#ifndef _COMMON_WRAPPER_H_
#define _COMMON_WRAPPER_H_

#include "chre/common.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

//! struct chreAsyncResult begin
CONVERSION_FUNCTIONS_DECLARATION(chreAsyncResult);

#ifdef __cplusplus
}
#endif

#include "chre/platform/shared/chre_api_wrapper/common_assert.h"

#endif