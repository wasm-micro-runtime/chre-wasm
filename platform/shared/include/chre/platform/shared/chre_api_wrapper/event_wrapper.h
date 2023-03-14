#ifndef _EVENT_WRAPPER_H_
#define _EVENT_WRAPPER_H_

#include "chre/event.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"
#ifdef __cplusplus
extern "C" {
#endif


/**
 * Data provided with CHRE_EVENT_MESSAGE_FROM_HOST.
 * @see struct chreMessageFromHostData in chre/event.h
 */

//! chreMessageFromHostData begin
CONVERSION_FUNCTIONS_DECLARATION(chreMessageFromHostData);


/**
 * Data provided with CHRE_EVENT_TIMER and CHRE_EVENT_NANOAPP_STARTED.
 * @see struct chreNanoappInfo in chre/event.h
 */

//! chreNanoappInfo begin
CONVERSION_FUNCTIONS_DECLARATION(chreNanoappInfo);


/**
 * Data provided with CHRE_EVENT_HOST_ENDPOINT_NOTIFICATION.
 * @see struct chreHostEndpointInfo in chre/event.h
 */

//! struct chreHostEndpointInfo Begin
CONVERSION_FUNCTIONS_DECLARATION(chreHostEndpointInfo);

/**
 * CHRE API Wrapper
*/
bool chreSendEventWrapper(wasm_exec_env_t exec_env, uint16_t eventType,
                          uint32_t eventDataForWASM, uint32_t funcOffset,
                          uint32_t targetInstanceId);


bool chreSendMessageToHostWrapper(wasm_exec_env_t exec_env, uint32_t messageForWASM,
                                  uint32_t messageSize, uint32_t messageType,
                                  uint32_t funcOffset);


bool chreSendMessageToHostEndpointWrapper(wasm_exec_env_t exec_env, uint32_t messageForWASM, uint32_t messageSize,
                                          uint32_t messageType, uint16_t hostEndpoint,
                                          uint32_t funcOffset);


bool chreSendMessageWithPermissionsWrapper(wasm_exec_env_t exec_env, uint32_t messagePointer, uint32_t messageSize,
                                            uint32_t messageType, uint16_t hostEndpoint,
                                            uint32_t messagePermissions,
                                            uint32_t funcOffset);

bool chreGetNanoappInfoByAppIdWrapper(wasm_exec_env_t exec_env, uint64_t appId, chreNanoappInfo *info);

bool chreGetNanoappInfoByInstanceIdWrapper(wasm_exec_env_t exec_env, uint32_t instanceId,
                                           chreNanoappInfo *info);

void chreConfigureNanoappInfoEventsWrapper(wasm_exec_env_t exec_env, bool enable);


void chreConfigureHostSleepStateEventsWrapper(wasm_exec_env_t exec_env, bool enable);

bool chreIsHostAwakeWrapper(wasm_exec_env_t exec_env);

void chreConfigureDebugDumpEventWrapper(wasm_exec_env_t exec_env, bool enable);


bool chreConfigureHostEndpointNotificationsWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                                    bool enable);

bool chrePublishRpcServicesWrapper(wasm_exec_env_t exec_env, chreNanoappRpcService *services,
                                    size_t numServices);

bool chreGetHostEndpointInfoWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                    chreHostEndpointInfo *info);
#ifdef __cplusplus
}
#endif
#endif