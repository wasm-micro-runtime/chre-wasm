#ifndef _BLE_WRAPPER_H_
#define _BLE_WRAPPER_H_

#include "chre/ble.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

//! struct chreBleAdvertisementEvent Begin
CONVERSION_FUNCTIONS_DECLARATION(chreBleAdvertisementEvent);

/**
 * CHRE API Wrapper
*/
uint32_t chreBleGetCapabilitiesWrapper(wasm_exec_env_t exec_env);

uint32_t chreBleGetFilterCapabilitiesWrapper(wasm_exec_env_t exec_env);

bool chreBleStartScanAsyncWrapper(wasm_exec_env_t exec_env, enum chreBleScanMode mode,
                                  uint32_t reportDelayMs, const chreBleScanFilter *filter);

bool chreBleStopScanAsyncWrapper(wasm_exec_env_t exec_env);

#ifdef __cplusplus
}
#endif
#endif