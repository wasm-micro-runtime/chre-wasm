#include "chre/common.h"
#include "stddef.h"
#include "wasm_export.h"

#ifndef _COMMON_WRAPPER_H_
#define _COMMON_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/** This is the wrapper of struct chreAsyncResult
 * @see struct chreAsyncResult
*/
typedef struct chreAsyncResultWrapper {
    //! Indicates the request associated with this result. The interpretation of
    //! values in this field is dependent upon the event type provided when this
    //! result was delivered.
    uint8_t requestType;

    //! Set to true if the request was successfully processed
    bool success;

    //! If the request failed (success is false), this is set to a value from
    //! enum chreError (other than CHRE_ERROR_NONE), which may provide
    //! additional information about the nature of the failure.
    //! @see #chreError
    uint8_t errorCode;

    //! Reserved for future use, set to 0
    uint8_t reserved;

    //! Set to the cookie parameter given to the request function tied to this
    //! result
    // const void *cookie;
    uint32_t cookiePointer;
} chreAsyncResultWrapper;
static_assert(sizeof(chreAsyncResultWrapper) == 8
              && offsetof(chreAsyncResultWrapper, requestType) == 0
              && offsetof(chreAsyncResultWrapper, success) == 1
              && offsetof(chreAsyncResultWrapper, errorCode) == 2
              && offsetof(chreAsyncResultWrapper, reserved) == 3
              && offsetof(chreAsyncResultWrapper, cookiePointer) == 4);
//! struct chreAsyncResult begin
uint32_t chreAsyncResultWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreAsyncResult *eventData);
chreAsyncResult *chreAsyncResultCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreAsyncResultWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreAsyncResultRelease(chreAsyncResult *eventData);


#ifdef __cplusplus
}
#endif

#endif