#include "chre/event.h"
#include "stddef.h"
#include "wasm_export.h"

#ifndef _EVENT_WRAPPER_H_
#define _EVENT_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Data provided with CHRE_EVENT_MESSAGE_FROM_HOST.
 * @see struct chreMessageFromHostData in chre/event.h
 */
typedef struct chreMessageFromHostDataWrapper {
    /**
     * Message type supplied by the host.
     *
     * @note In CHRE API v1.0, support for forwarding this field from the host
     * was not strictly required, and some implementations did not support it.
     * However, its support is mandatory as of v1.1.
     */
    union {
        /**
         * The preferred name to use when referencing this field.
         *
         * @since v1.1
         */
        uint32_t messageType;

        /**
         * @deprecated This is the name for the messageType field used in v1.0.
         * Left to allow code to compile against both v1.0 and v1.1 of the API
         * definition without needing to use #ifdefs. This will be removed in a
         * future API update - use messageType instead.
         */
        uint32_t reservedMessageType;
    };

    /**
     * The size, in bytes of the following 'message'.
     *
     * This can be 0.
     */
    uint32_t messageSize;

    /**
     * The message from the host.
     *
     * These contents are of a format that the host and nanoapp must have
     * established beforehand.
     *
     * This data is 'messageSize' bytes in length.  Note that if 'messageSize'
     * is 0, this might be NULL.
     */
    //! const void *message;
    uint32_t messagePointer;

    /**
     * An identifier for the host-side entity that sent this message.  Unless
     * this is set to CHRE_HOST_ENDPOINT_UNSPECIFIED, it can be used in
     * chreSendMessageToHostEndpoint() to send a directed reply that will only
     * be received by the given entity on the host.  Endpoint identifiers are
     * opaque values assigned at runtime, so they cannot be assumed to always
     * describe a specific entity across restarts.
     *
     * If running on a CHRE API v1.0 implementation, this field will always be
     * set to CHRE_HOST_ENDPOINT_UNSPECIFIED.
     *
     * @since v1.1
     */
    uint16_t hostEndpoint;
} chreMessageFromHostDataWrapper;
static_assert(sizeof(chreMessageFromHostDataWrapper) == 16
              && offsetof(chreMessageFromHostDataWrapper, messageType) == 0
              && offsetof(chreMessageFromHostDataWrapper, messageSize) == 4
              && offsetof(chreMessageFromHostDataWrapper, messagePointer) == 8
              && offsetof(chreMessageFromHostDataWrapper, hostEndpoint) == 12);
//! chreMessageFromHostData begin
uint32_t chreMessageFromHostDataWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreMessageFromHostData *eventData);
chreMessageFromHostData *chreMessageFromHostDataCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreMessageFromHostDataWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreMessageFromHostDataRelease(chreMessageFromHostData *eventData);

/**
 * Data provided with CHRE_EVENT_TIMER and CHRE_EVENT_NANOAPP_STARTED.
 * @see struct chreNanoappInfo in chre/event.h
 */
typedef chreNanoappInfo chreNanoappInfoWrapper;
static_assert(sizeof(chreNanoappInfoWrapper) == 16
              && offsetof(chreNanoappInfoWrapper, appId) == 0
              && offsetof(chreNanoappInfoWrapper, version) == 8
              && offsetof(chreNanoappInfoWrapper, instanceId) == 12);

//! chreNanoappInfo begin
uint32_t chreNanoappInfoWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                const chreNanoappInfo *eventData);
chreNanoappInfo *chreNanoappInfoCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreNanoappInfoWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreNanoappInfoRelease(chreNanoappInfo *eventData);

typedef chreHostEndpointNotification chreHostEndpointNotificationWrapper;
static_assert(sizeof(chreHostEndpointNotificationWrapper) == 4
              && offsetof(chreHostEndpointNotificationWrapper, hostEndpointId) == 0
              && offsetof(chreHostEndpointNotificationWrapper, notificationType) == 2
              && offsetof(chreHostEndpointNotificationWrapper, reserved) == 3);


/**
 * Data provided with CHRE_EVENT_HOST_ENDPOINT_NOTIFICATION.
 * @see struct chreHostEndpointInfo in chre/event.h
 */
typedef chreHostEndpointInfo chreHostEndpointInfoWrapper;
static_assert(sizeof(chreHostEndpointInfoWrapper) == 106
                     && offsetof(chreHostEndpointInfoWrapper, hostEndpointId) == 0
                     && offsetof(chreHostEndpointInfoWrapper, hostEndpointType) == 2
                     && offsetof(chreHostEndpointInfoWrapper, packageName) == 4
                     && offsetof(chreHostEndpointInfoWrapper, attributionTag) == 55);

uint32_t chreHostEndpointInfoWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreHostEndpointInfo *eventData);
chreHostEndpointInfo *chreHostEndpointInfoCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreHostEndpointInfoWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreHostEndpointInfoRelease(chreHostEndpointInfo *eventData);

typedef chreNanoappRpcService chreNanoappRpcServiceWrapper;
static_assert(sizeof(chreNanoappRpcServiceWrapper) == 16
                     && offsetof(chreNanoappRpcServiceWrapper, id) == 0
                     && offsetof(chreNanoappRpcServiceWrapper, version) == 8);

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

bool chreGetNanoappInfoByAppIdWrapper(wasm_exec_env_t exec_env, uint64_t appId, chreNanoappInfoWrapper *info);

bool chreGetNanoappInfoByInstanceIdWrapper(wasm_exec_env_t exec_env, uint32_t instanceId,
                                           chreNanoappInfoWrapper *info);

void chreConfigureNanoappInfoEventsWrapper(wasm_exec_env_t exec_env, bool enable);


void chreConfigureHostSleepStateEventsWrapper(wasm_exec_env_t exec_env, bool enable);

bool chreIsHostAwakeWrapper(wasm_exec_env_t exec_env);

void chreConfigureDebugDumpEventWrapper(wasm_exec_env_t exec_env, bool enable);


bool chreConfigureHostEndpointNotificationsWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                                    bool enable);

bool chrePublishRpcServicesWrapper(wasm_exec_env_t exec_env, chreNanoappRpcServiceWrapper *services,
                                    size_t numServices);

bool chreGetHostEndpointInfoWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                    chreHostEndpointInfoWrapper *info);
#ifdef __cplusplus
}
#endif
#endif