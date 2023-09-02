#include <stdint.h>
#include "chre/platform/shared/nanoapp_support_lib_dso.h"
#ifndef _NANOAPP_SUPPORT_WASM_WRAPPER_
#define _NANOAPP_SUPPORT_WASM_WRAPPER_
#ifdef __cplusplus
extern "C" {
#endif
chreNslNanoappInfo* createNativeChreNslNanoappInfoFromWrapper(chreNslNanoappInfoWrapper* wrapperData);
#ifdef __cplusplus
}
#endif
#endif