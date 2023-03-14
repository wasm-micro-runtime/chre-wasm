#ifndef _GNSS_WRAPPER_H_
#define _GNSS_WRAPPER_H_

#include "chre/gnss.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

//! struct chreGnssDataEvent begin
CONVERSION_FUNCTIONS_DECLARATION(chreGnssDataEvent);
//! struct chreGnssLocationEvent begin
CONVERSION_FUNCTIONS_DECLARATION(chreGnssLocationEvent);

/**
 * CHRE API Wrapper
*/
uint32_t chreGnssGetCapabilitiesWrapper(wasm_exec_env_t exec_env);

bool chreGnssLocationSessionStartAsyncWrapper(wasm_exec_env_t exec_env, uint32_t minIntervalMs,
                                              uint32_t minTimeToNextFixMs, const void *cookie);

bool chreGnssLocationSessionStopAsyncWrapper(wasm_exec_env_t exec_env, const void *cookie);

bool chreGnssMeasurementSessionStartAsyncWrapper(wasm_exec_env_t exec_env, uint32_t minIntervalMs,
                                                 const void *cookie);

bool chreGnssMeasurementSessionStopAsyncWrapper(wasm_exec_env_t exec_env, const void *cookie);

bool chreGnssConfigurePassiveLocationListenerWrapper(wasm_exec_env_t exec_env, bool enable);
#ifdef __cplusplus
}
#endif

#endif