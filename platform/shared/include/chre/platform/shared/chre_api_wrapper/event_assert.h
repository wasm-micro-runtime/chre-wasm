#include <stddef.h>
#ifdef _CHRE_EVENT_H_
/**
 * @note for struct chreMessageFromHostData
*/
static_assert(sizeof(struct chreMessageFromHostData) == 16
              && offsetof(struct chreMessageFromHostData, messageType) == 0
              && offsetof(struct chreMessageFromHostData, messageSize) == 4
              && offsetof(struct chreMessageFromHostData, message) == 8
              && offsetof(struct chreMessageFromHostData, hostEndpoint) == 12);

/**
 * @note for struct chreNanoappInfo
*/
static_assert(sizeof(struct chreNanoappInfo) == 16
              && offsetof(struct chreNanoappInfo, appId) == 0
              && offsetof(struct chreNanoappInfo, version) == 8
              && offsetof(struct chreNanoappInfo, instanceId) == 12);

/**
 * @note for struct chreHostEndpointNotification
*/
static_assert(sizeof(struct chreHostEndpointNotification) == 4
              && offsetof(struct chreHostEndpointNotification, hostEndpointId) == 0
              && offsetof(struct chreHostEndpointNotification, notificationType) == 2
              && offsetof(struct chreHostEndpointNotification, reserved) == 3);

/**
 * @note for struct chreHostEndpointInfo
*/
static_assert(sizeof(struct chreHostEndpointInfo) == 106
                     && offsetof(struct chreHostEndpointInfo, hostEndpointId) == 0
                     && offsetof(struct chreHostEndpointInfo, hostEndpointType) == 2
                     && offsetof(struct chreHostEndpointInfo, packageName) == 4
                     && offsetof(struct chreHostEndpointInfo, attributionTag) == 55);

/**
 * @note for struct chreNanoappRpcService
*/
static_assert(sizeof(struct chreNanoappRpcService) == 12
                     && offsetof(struct chreNanoappRpcService, id) == 0
                     && offsetof(struct chreNanoappRpcService, version) == 8);
#endif