
#include "chre/util/macros.h"
#include "chre/util/system/napp_permissions.h"
#include "chre/platform/shared/chre_api_wrapper/event_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/event_transform.h"
#include "chre/platform/shared/chre_api_wrapper/event_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @see wasm_runtime_call_indirect in wasm_runtime_common.h
*/
bool
wasm_runtime_call_indirect(WASMExecEnv *exec_env, uint32_t element_indices,
                           uint32_t argc, uint32_t argv[]);

//! struct chreMessageFromHostDataWrapper start
uint32_t chreMessageFromHostDataWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                        const chreMessageFromHostData *eventData) {
    uint32_t structDataOffset = 0;
    uint32_t messageOffset = 0;
    chreMessageFromHostDataWrapper *structData = NULL;
    void* message = NULL;
    uint32_t messageSize = eventData->messageSize;
    if(!(structDataOffset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreMessageFromHostDataWrapper),
                                                       reinterpret_cast<void**>(&structData)))) {
        goto fail1;
    }
    if(messageSize && !(messageOffset  = wasm_runtime_module_malloc(WasmModuleInst, messageSize,
                                                                    reinterpret_cast<void**>(&message)))) {
        goto fail2;
    }
    if(messageSize) {
        memcpy(message, eventData->message, messageSize);
    }
    memcpy(structData, eventData, offsetof(chreMessageFromHostDataWrapper, messagePointer));
    structData->messagePointer = messageOffset;
    structData->hostEndpoint = eventData->hostEndpoint;
    return structDataOffset;
fail2:
    wasm_runtime_module_free(WasmModuleInst, structDataOffset);
fail1:
    LOGE("");
    return 0;
}
chreMessageFromHostData *chreMessageFromHostDataCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                               uint32_t eventDataForWASM) {
    chreMessageFromHostData *eventData = NULL;
    void* messageForEventData = NULL;
    chreMessageFromHostDataWrapper *structData = NULL;
    void *message = NULL;
    if (!(structData = static_cast<chreMessageFromHostDataWrapper*>(
                                    wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        goto fail1;
    }
    if(structData->messagePointer && !(message = wasm_runtime_addr_app_to_native(WasmModuleInst, 
                                                                        structData->messagePointer))) {
        goto fail1;
    }
    if(!(eventData = static_cast<chreMessageFromHostData *>(
                                chreHeapAlloc(sizeof(chreMessageFromHostDataWrapper))))) {
        goto fail1;
    }
    if(!(messageForEventData = chreHeapAlloc(structData->messageSize))) {
        goto fail2;
    }
    memcpy(messageForEventData, message, structData->messageSize);
    memcpy(eventData, structData, offsetof(chreMessageFromHostDataWrapper, messagePointer));
    eventData->message = messageForEventData;
    eventData->hostEndpoint = structData->hostEndpoint;
    return eventData;
fail2:
    chreHeapFree(eventData);
fail1:
    LOGE("");
    return nullptr;
}

void chreMessageFromHostDataWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                           uint32_t eventDataForWASM) {
    chreMessageFromHostDataWrapper *structData = NULL;
    if (!eventDataForWASM || !(structData = reinterpret_cast<chreMessageFromHostDataWrapper*>(
                                    wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        LOGE("");
        return;
    }
    if (structData->messagePointer) {
        wasm_runtime_module_free(WasmModuleInst, structData->messagePointer);
    }
}

void chreMessageFromHostDataRelease(chreMessageFromHostData *eventData) {
    if (!eventData) {
        return;
    }
    if(eventData->message) {
        chreHeapFree(const_cast<void*>(eventData->message));
    }
    chreHeapFree(eventData);
}




//struct chreNanoappInfo start
uint32_t chreNanoappInfoWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                const chreNanoappInfo *eventData) {
    uint32_t structDataOffset = 0;
    chreNanoappInfoWrapper *structData = NULL;
    if(!(structDataOffset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreNanoappInfoWrapper),
                                                       reinterpret_cast<void**>(&structData)))) {
        goto fail1;
    }
    memcpy(structData, eventData, sizeof(chreNanoappInfoWrapper));
    return structDataOffset;
fail1:
    LOGE("");
    return 0;
}
chreNanoappInfo *chreNanoappInfoCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                               uint32_t eventDataForWASM) {
    chreNanoappInfo *eventData = NULL;
    chreNanoappInfoWrapper *structData = NULL;
    if (!(structData = reinterpret_cast<chreNanoappInfoWrapper*>(
                            wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        goto fail1;
    }
    if(!(eventData = reinterpret_cast<chreNanoappInfo*>(chreHeapAlloc(sizeof(chreNanoappInfo))))) {
        goto fail1;
    }
    memcpy(eventData, structData, sizeof(chreNanoappInfo));
    return eventData;
fail1:
    LOGE("");
    return nullptr;    
}

void chreNanoappInfoWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                   uint32_t eventDataForWASM) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

void chreNanoappInfoRelease(chreNanoappInfo *eventData) {
    return chreHeapFree(eventData);
}
//! struct chreHostEndpointInfo begin
uint32_t chreHostEndpointInfoWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                     const chreHostEndpointInfo *eventData) {
    uint32_t structDataOffset = 0;
    chreHostEndpointInfoWrapper *structData = NULL;
    if(!(structDataOffset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreHostEndpointInfoWrapper),
                                                       reinterpret_cast<void**>(&structData)))) {
        goto fail1;
    }
    memcpy(structData, eventData, sizeof(chreHostEndpointInfoWrapper));
    return structDataOffset;
fail1:
    LOGE("");
    return 0;
}

chreHostEndpointInfo *chreHostEndpointInfoCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                         uint32_t eventDataForWASM) {
    chreHostEndpointInfo *eventData = NULL;
    chreHostEndpointInfoWrapper *structData = NULL;
    if (!(structData = reinterpret_cast<chreHostEndpointInfoWrapper*>(
                        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        goto fail1;
    }
    if(!(eventData = reinterpret_cast<chreHostEndpointInfo*>(
                                            chreHeapAlloc(sizeof(chreHostEndpointInfo))))) {
        goto fail1;
    }
    memcpy(eventData, structData, sizeof(chreHostEndpointInfo));
    return eventData;
fail1:
    LOGE("");
    return nullptr;   
}

void chreHostEndpointInfoWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                        uint32_t eventDataForWASM) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

void chreHostEndpointInfoRelease(chreHostEndpointInfo *eventData) {
    chreHeapFree(eventData);
}

/**
 * CHRE API Wrapper
*/


bool chreSendEventWrapper(wasm_exec_env_t exec_env, uint16_t eventType,
                          uint32_t eventDataForWASM,
                          uint32_t funcOffset,
                          uint32_t targetInstanceId) {
    chreEventCompleteFunction* freeFunc = nullptr;
    void *eventData = nullptr;
    uint32_t argv[1];
    wasm_module_inst_t WASMModuleInst = NULL;
    if(!(WASMModuleInst = wasm_runtime_get_module_inst(exec_env))) {
        return false;
    }
    //get new native data
    //All event data is copied here
    if (eventDataForWASM && !(eventData = copyEventFromWASMToNative(WASMModuleInst,
                                                                    eventType,
                                                                    eventDataForWASM))) {
        return false;
    }
    //get free callback function
    if(funcOffset) {
        freeFunc = getCompleteFunction(eventType);
        //free Wasm data
        argv[0] = eventDataForWASM;
        wasm_runtime_call_indirect(exec_env,  funcOffset, 1, argv);
    }
    return chreSendEvent(eventType, eventData, freeFunc, targetInstanceId);
}

void chreMessageFreeFunctionWrapper(void *message, size_t messageSize){
    UNUSED_VAR(messageSize);
    chreHeapFree(message);
}

bool chreSendMessageToHostWrapper(wasm_exec_env_t exec_env, uint32_t messageForWASM,
                                  uint32_t messageSize, uint32_t messageType,
                                  uint32_t funcOffset) {
    return chreSendMessageToHostEndpointWrapper(exec_env, messageForWASM, messageSize, messageType,
                                                 CHRE_HOST_ENDPOINT_BROADCAST, funcOffset);
}


bool chreSendMessageToHostEndpointWrapper(wasm_exec_env_t exec_env, uint32_t messageForWASM, uint32_t messageSize,
                                          uint32_t messageType, uint16_t hostEndpoint,
                                          uint32_t funcOffset) {
    return chreSendMessageWithPermissionsWrapper(exec_env, messageForWASM, messageSize, messageType, hostEndpoint,
                                                 static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_NONE),
                                                 funcOffset);
}


bool chreSendMessageWithPermissionsWrapper(wasm_exec_env_t exec_env, uint32_t messageForWASM, uint32_t messageSize,
                                            uint32_t messageType, uint16_t hostEndpoint,
                                            uint32_t messagePermissions,
                                            uint32_t funcOffset) {
    //native
    void *message = NULL;
    //wasm
    void *messageData = NULL;
    uint32_t argv[2];
    wasm_module_inst_t WasmModuleInst = NULL;
    if (!(WasmModuleInst = wasm_runtime_get_module_inst(exec_env))) {
        goto fail1;
    }
    if (!(messageData = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                        messageForWASM))) {
        goto fail1;
    }
    //allocate new native data space
    if (messageData && !(message = chreHeapAlloc(messageSize))) {
        goto fail1;
    }
    //copy
    if(messageData) {
        memcpy(message, messageData, messageSize);
    }
    //get free callback function
    if(funcOffset) {
        argv[0] = messageForWASM;
        argv[1] = messageSize;
        wasm_runtime_call_indirect(exec_env,  funcOffset, 2, argv);
    }
    return chreSendMessageWithPermissions(message, messageSize, messageType, hostEndpoint,
                                          messagePermissions, chreMessageFreeFunctionWrapper);
fail1:
    LOGE("");
    return false;
}

bool chreGetNanoappInfoByAppIdWrapper(wasm_exec_env_t exec_env, uint64_t appId,
                                      chreNanoappInfoWrapper *info) {
    return chreGetNanoappInfoByAppId(appId, static_cast<chreNanoappInfo*>(info));
}

bool chreGetNanoappInfoByInstanceIdWrapper(wasm_exec_env_t exec_env, uint32_t instanceId,
                                           chreNanoappInfoWrapper *info) {
    return chreGetNanoappInfoByInstanceId(instanceId, static_cast<chreNanoappInfo*>(info));
}

void chreConfigureNanoappInfoEventsWrapper(wasm_exec_env_t exec_env, bool enable) {
    return chreConfigureNanoappInfoEvents(enable);
}


void chreConfigureHostSleepStateEventsWrapper(wasm_exec_env_t exec_env, bool enable) {
    return chreConfigureHostSleepStateEvents(enable);
}

bool chreIsHostAwakeWrapper(wasm_exec_env_t exec_env) {
    return  chreIsHostAwake();
}

void chreConfigureDebugDumpEventWrapper(wasm_exec_env_t exec_env, bool enable) {
    return chreConfigureDebugDumpEvent(enable);
}


bool chreConfigureHostEndpointNotificationsWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                                    bool enable) {
    return chreConfigureHostEndpointNotifications(hostEndpointId, enable);
}

bool chrePublishRpcServicesWrapper(wasm_exec_env_t exec_env, chreNanoappRpcServiceWrapper *services,
                                    size_t numServices) {
    return chrePublishRpcServices(static_cast<chreNanoappRpcService*>(services), numServices);
}

bool chreGetHostEndpointInfoWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                    chreHostEndpointInfoWrapper *info) {
    return chreGetHostEndpointInfo(hostEndpointId, static_cast<chreHostEndpointInfo *>(info));
}
#ifdef __cplusplus
}
#endif