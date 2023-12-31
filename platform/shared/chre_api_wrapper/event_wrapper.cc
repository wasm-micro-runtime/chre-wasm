#include "chre/util/macros.h"
#include "chre/util/system/napp_permissions.h"
#include "chre/platform/shared/chre_api_wrapper/event_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/event_transform.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include <stddef.h>
#include <stdint.h>

#include <map>

#ifdef __cplusplus
extern "C" {
#endif

//! struct chreMessageFromHostData start
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreMessageFromHostData) {
    const struct chreMessageFromHostData *native_event = 
            reinterpret_cast<const struct chreMessageFromHostData *>(nativeData);
    uint32_t offset_event = 0;
    uint32_t offset_event_message = 0;

    struct chreMessageFromHostData *pointer_event = NULL;
    void *pointer_event_message = NULL;

    uint32_t totalSize = 0;
    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;

    //caculate size
    // level 1
    totalSize += sizeof(struct chreMessageFromHostData);
    // level 2
    totalSize += native_event->messageSize;

    offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize, 
                                              reinterpret_cast<void**>(&dataBuffer));
    if (!offset_event) {
        LOGE("Allocate memory for struct chreMessageFromHostData in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;

    //copy level 1
    pointer_event = reinterpret_cast<struct chreMessageFromHostData *>(nowBuffer);
    nowBuffer += sizeof(struct chreMessageFromHostData);
    memcpy(pointer_event, native_event, sizeof(struct chreMessageFromHostData));

    //copy level 2
    if (0 != native_event->messageSize) {
        offset_event_message = wasm_runtime_addr_native_to_app(WasmModuleInst, nowBuffer);
        pointer_event_message = nowBuffer;
        nowBuffer += native_event->messageSize;
        memcpy(pointer_event_message, native_event->message, native_event->messageSize);
        pointer_event->message = reinterpret_cast<void*>(offset_event_message);
    }

    if (nowBuffer + totalSize != dataBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreMessageFromHostData");
        goto fail1;
    }
    return offset_event;
fail1:
    wasm_runtime_module_free(WasmModuleInst, offset_event);
fail0:
    return 0;
}
WASM_TO_NATIVE_FUNCTION_DECLARATION(chreMessageFromHostData) {
    const struct chreMessageFromHostData *wasm_event = NULL;
    const void *wasm_event_message = NULL;
    
    struct chreMessageFromHostData *pointer_event = NULL;
    void *pointer_event_message = NULL;

    uint32_t totalSize = 0;
    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;

    //caculate size and validate boundary
    //level 1
    totalSize += sizeof(struct chreMessageFromHostData); 
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                        sizeof(struct chreMessageFromHostData))) {
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event = reinterpret_cast<const struct chreMessageFromHostData *>(
                        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));
    //level 2
    totalSize += wasm_event->messageSize;
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->message),
                                        wasm_event->messageSize)) {
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event_message = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                reinterpret_cast<uint32_t>(wasm_event->message));

    dataBuffer = reinterpret_cast<uint8_t *>(chreHeapAlloc(totalSize));
    if (!dataBuffer) {
        LOGE("Allocate memory for struct chreMessageFromHostData in Native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    //copy level 1
    pointer_event = reinterpret_cast<struct chreMessageFromHostData*>(nowBuffer);
    nowBuffer += sizeof(struct chreMessageFromHostData);
    memcpy(pointer_event, wasm_event, sizeof(struct chreMessageFromHostData));
    //copy level 2
    if (0 != wasm_event->messageSize) {
        pointer_event_message = reinterpret_cast<void *>(nowBuffer);
        nowBuffer += wasm_event->messageSize;
        memcpy(pointer_event_message, wasm_event_message, wasm_event->messageSize);
        pointer_event->message = pointer_event_message;
    }
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in wasm2native: struct chreMessageFromHostData");
        goto fail1;
    }
    return pointer_event;
fail1:
    chreHeapFree(dataBuffer);
fail0:
    return nullptr;
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreMessageFromHostData) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreMessageFromHostData) {
    chreHeapFree(nativeData);
}


//struct chreNanoappInfo start
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreNanoappInfo);

//! struct chreHostEndpointInfo start
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreHostEndpointInfo);

//! struct chreHostEndpointNotification
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreHostEndpointNotification);
//! cookie event begin
NATIVE_TO_WASM_FUNCTION_DECLARATION(cookie) {
    if(!WasmModuleInst) {
        return 0;
    }
    return wasm_runtime_addr_native_to_app(WasmModuleInst, const_cast<void*>(nativeData));
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(cookie) {
    if(!WasmModuleInst) {
        return 0;
    }
    return wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM);
}
FREE_WASM_EVENT_FUNCTION_DECLARATION(cookie) {
    UNUSED_VAR(WasmModuleInst);
    UNUSED_VAR(eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(cookie) {
    UNUSED_VAR(nativeData);
}

/**
 * CHRE API Wrapper
*/

/**
 * @todo Serialization
*/
typedef struct mapInternalEventData{
    wasm_exec_env_t execEnv;
    const convertFunctions *functions;
    uint32_t originFuncOffset;
    uint32_t originDataOffset;
} mapInternalEventData;

static std::map<void*, mapInternalEventData> eventDataMap;

void freeFunc(uint16_t eventType, void *eventData) {
    auto item = eventDataMap.find(eventData);
    wasm_module_inst_t WasmModuleInst = NULL;
    uint32_t argv[2];
    if (item == eventDataMap.end()) {
        return;
    }
    argv[0] = eventType;
    argv[1] = item->second.originDataOffset;
    WasmModuleInst = wasm_runtime_get_module_inst(item->second.execEnv);
    if(item->second.originFuncOffset)
        wasm_runtime_call_indirect(item->second.execEnv,  item->second.originFuncOffset, 2, argv);
    item->second.functions->nativeRelease(eventData);
    eventDataMap.erase(item);
}

bool chreSendEventWrapper(wasm_exec_env_t exec_env, uint16_t eventType,
                          uint32_t eventDataForWASM,
                          uint32_t funcOffset,
                          uint32_t targetInstanceId) {
    chreEventCompleteFunction* freeFunc = nullptr;
    void *eventData = nullptr;
    wasm_module_inst_t WasmModuleInst = NULL;
    if(!(WasmModuleInst = wasm_runtime_get_module_inst(exec_env))) {
        return false;
    }
    //get function pointers
    const convertFunctions *funcs = getConvertFunctions(eventType);
    //get new native data
    //All event data is copied here
    if (eventDataForWASM && !(eventData = funcs->wasm2Native(WasmModuleInst, eventDataForWASM))) {
        return false;
    }
    //mapping data
    eventDataMap[eventData] = {
        exec_env,
        funcs,
        funcOffset,
        eventDataForWASM
    };
    return chreSendEvent(eventType, eventData, freeFunc, targetInstanceId);
}

bool chreSendMessageToHostWrapper(wasm_exec_env_t exec_env, void* message,
                                  uint32_t messageSize, uint32_t messageType,
                                  uint32_t funcOffset) {
    return chreSendMessageToHostEndpointWrapper(exec_env, message, messageSize, messageType,
                                                 CHRE_HOST_ENDPOINT_BROADCAST, funcOffset);
}


bool chreSendMessageToHostEndpointWrapper(wasm_exec_env_t exec_env, void* message, uint32_t messageSize,
                                          uint32_t messageType, uint16_t hostEndpoint,
                                          uint32_t funcOffset) {
    return chreSendMessageWithPermissionsWrapper(exec_env, message, messageSize, messageType, hostEndpoint,
                                                 static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_NONE),
                                                 funcOffset);
}


typedef struct mapInternalMessageData{
    wasm_exec_env_t execEnv;
    uint32_t originFuncOffset;
} mapInternalMessageData;

static std::map<void*, mapInternalMessageData> messageDataMap;

static void messageFreeFunc(void *message, size_t messageSize) {
    auto item = messageDataMap.find(message);
    uint32_t offset = 0;
    uint32_t argv[2];
    wasm_module_inst_t WasmModuleInst = NULL;
    if(messageDataMap.end() == item || !item->second.originFuncOffset) {
        return;
    }
    if(!(WasmModuleInst = wasm_runtime_get_module_inst(item->second.execEnv))) {
        LOGE("The Wasm Module Instance is NULL!");
    }

    offset = wasm_runtime_addr_native_to_app(WasmModuleInst, message);
    argv[0] = offset;
    argv[1] = messageSize;
    if(!wasm_runtime_call_indirect(item->second.execEnv, item->second.originFuncOffset, 2, argv)) {
        LOGE("Calling callback function in WASM for message failed! Error: %s",wasm_runtime_get_exception(WasmModuleInst));
    }
    messageDataMap.erase(item);
}

bool chreSendMessageWithPermissionsWrapper(wasm_exec_env_t exec_env, void* message, uint32_t messageSize,
                                            uint32_t messageType, uint16_t hostEndpoint,
                                            uint32_t messagePermissions,
                                            uint32_t funcOffset) {
    wasm_module_inst_t WasmModuleInst = NULL;
    if(!exec_env || !(WasmModuleInst = wasm_runtime_get_module_inst(exec_env))) {
        return false;
    }
    messageDataMap[message] = {
        exec_env,
        funcOffset
    };
    return chreSendMessageWithPermissions(message, messageSize, messageType, hostEndpoint,
                                          messagePermissions, messageFreeFunc);
}

bool chreGetNanoappInfoByAppIdWrapper(wasm_exec_env_t exec_env, uint64_t appId,
                                      chreNanoappInfo *info) {
    return chreGetNanoappInfoByAppId(appId, static_cast<chreNanoappInfo*>(info));
}

bool chreGetNanoappInfoByInstanceIdWrapper(wasm_exec_env_t exec_env, uint32_t instanceId,
                                           chreNanoappInfo *info) {
    return chreGetNanoappInfoByInstanceId(instanceId, info);
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

bool chrePublishRpcServicesWrapper(wasm_exec_env_t exec_env, chreNanoappRpcService *services,
                                    size_t numServices) {
    return chrePublishRpcServices(services, numServices);
}

bool chreGetHostEndpointInfoWrapper(wasm_exec_env_t exec_env, uint16_t hostEndpointId,
                                    chreHostEndpointInfo *info) {
    return chreGetHostEndpointInfo(hostEndpointId, info);
}
#ifdef __cplusplus
}
#endif