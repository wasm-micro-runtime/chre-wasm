#ifndef _WIFI_WRAPPER_H_
#define _WIFI_WRAPPER_H_

#include "chre/wifi.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

//! for struct chreAsyncResult, please see it common_wrapper.h

//! for struct chreWifiScanEvent
CONVERSION_FUNCTIONS_DECLARATION(chreWifiScanEvent);
//! for struct chreWifiRangingEvent
CONVERSION_FUNCTIONS_DECLARATION(chreWifiRangingEvent);
//! for struct chreWifiNanIdentifierEvent
CONVERSION_FUNCTIONS_DECLARATION(chreWifiNanIdentifierEvent);
//! for struct chreWifiNanDiscoveryEvent
CONVERSION_FUNCTIONS_DECLARATION(chreWifiNanDiscoveryEvent);
//! for struct chreWifiNanSessionLostEvent
CONVERSION_FUNCTIONS_DECLARATION(chreWifiNanSessionLostEvent);
//! for struct chreWifiNanSessionTerminatedEvent
CONVERSION_FUNCTIONS_DECLARATION(chreWifiNanSessionTerminatedEvent);

uint32_t chreWifiGetCapabilitiesWrapper(wasm_exec_env_t exec_env);

bool chreWifiNanGetCapabilitiesWrapper(wasm_exec_env_t exec_env, struct chreWifiNanCapabilities *capabilities);

bool chreWifiConfigureScanMonitorAsyncWrapper(wasm_exec_env_t exec_env, bool enable, const void *cookie);

bool chreWifiRequestScanAsyncWrapper(wasm_exec_env_t exec_env, uint32_t params, const void *cookie);

bool chreWifiRequestRangingAsyncWrapper(wasm_exec_env_t exec_env, uint32_t params, const void *cookie);

bool chreWifiNanSubscribeWrapper(wasm_exec_env_t exec_env, struct chreWifiNanSubscribeConfig *config,
                          const void *cookie);

bool chreWifiNanSubscribeCancelWrapper(wasm_exec_env_t exec_env, uint32_t subscriptionID);

bool chreWifiNanRequestRangingAsyncWrapper(wasm_exec_env_t exec_env, const struct chreWifiNanRangingParams *params,
                                    const void *cookie);

#ifdef __cplusplus
}
#endif
#endif