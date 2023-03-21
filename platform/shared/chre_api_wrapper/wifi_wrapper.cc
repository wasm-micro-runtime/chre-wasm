#include "chre/util/macros.h"
#include "chre/platform/shared/chre_api_wrapper/wifi_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/wrapper_data_map.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//! for struct chreWifiScanEvent
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreWifiScanEvent) {
    const struct chreWifiScanEvent* native_event = NULL;
    
    uint32_t offset_event = 0;
    uint32_t offset_event_scannedFreqList = 0;
    uint32_t offset_event_results = 0;

    struct chreWifiScanEvent* pointer_event = NULL;
    uint32_t* pointer_event_scannedFreqList = NULL;
    struct chreWifiScanResult* pointer_event_results = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    uint32_t size_event_scannedFreqList = 0;
    uint32_t size_event_results = 0;
    if (!nativeData) {
        goto fail0;
    }
    native_event = reinterpret_cast<const struct chreWifiScanEvent*>(nativeData);

    //caculate the size of level 1
    totalSize += sizeof(chreWifiScanEvent);
    //caculate the size of level 2
    //level 2: scannedFreqList, uint32_t *
    size_event_scannedFreqList = native_event->scannedFreqListLen * sizeof(uint32_t);
    totalSize += size_event_scannedFreqList;
    //level 2: results, struct chreWifiScanResult *
    size_event_results = native_event->resultCount * sizeof(struct chreWifiScanResult);
    totalSize += size_event_results;

    if (!(offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,
                                                   reinterpret_cast<void**>(&dataBuffer)))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiScanEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiScanEvent);
    memcpy(pointer_event, native_event, sizeof(struct chreWifiScanEvent));
    
    //copy level2: scannedFreqList
    pointer_event_scannedFreqList = reinterpret_cast<uint32_t*>(nowBuffer);
    offset_event_scannedFreqList = wasm_runtime_addr_native_to_app(WasmModuleInst, 
                                                  reinterpret_cast<void*>(nowBuffer));
    nowBuffer += size_event_scannedFreqList;
    memcpy(pointer_event_scannedFreqList,
           native_event->scannedFreqList, size_event_scannedFreqList);
    //link level2 to level 1
    pointer_event->scannedFreqList =
            reinterpret_cast<uint32_t*>(offset_event_scannedFreqList);

    //copy level2: results
    pointer_event_results = reinterpret_cast<struct chreWifiScanResult*>(nowBuffer);
    offset_event_results = wasm_runtime_addr_native_to_app(WasmModuleInst, 
                                                  reinterpret_cast<void*>(nowBuffer));
    nowBuffer += size_event_results;
    memcpy(pointer_event_results, native_event->results, size_event_results);
    //link level2 to level 1
    pointer_event->results =
            reinterpret_cast<struct chreWifiScanResult*>(offset_event_results);
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreBleAdvertisementEvent");
        goto fail1;
    }
    return offset_event;
fail1:
    wasm_runtime_module_free(WasmModuleInst, offset_event);
fail0:
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreWifiScanEvent) {
    const struct chreWifiScanEvent* wasm_event = NULL;
    const uint32_t* wasm_event_scannedFreqList = NULL;
    const struct chreWifiScanResult* wasm_event_results = NULL;

    struct chreWifiScanEvent* pointer_event = NULL;
    uint32_t* pointer_event_scannedFreqList = NULL;
    struct chreWifiScanResult* pointer_event_results = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    uint32_t size_event_scannedFreqList = 0;
    uint32_t size_event_results = 0;
    if (!eventDataForWASM) {
        goto fail0;
    }
    // validate level 1 boundary
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                        sizeof(struct chreWifiScanEvent))){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event = reinterpret_cast<const struct chreWifiScanEvent*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));

    //caculate the size of level 1
    totalSize += sizeof(chreWifiScanEvent);

    //caculate the size of level 2
    //level 2: scannedFreqList, uint32_t *
    size_event_scannedFreqList = wasm_event->scannedFreqListLen * sizeof(uint32_t);
    totalSize += size_event_scannedFreqList;    // validate level 2 boundary
    if (!wasm_runtime_validate_app_addr(WasmModuleInst,
                reinterpret_cast<uint32_t>(wasm_event->scannedFreqList), size_event_scannedFreqList)){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event_scannedFreqList = reinterpret_cast<uint32_t*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->scannedFreqList)));
    //level 2: results, struct chreWifiScanResult *
    size_event_results = wasm_event->resultCount * sizeof(struct chreWifiScanResult);
    totalSize += size_event_results;
    if (!wasm_runtime_validate_app_addr(WasmModuleInst,
                reinterpret_cast<uint32_t>(wasm_event->results), size_event_results)){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event_results = reinterpret_cast<struct chreWifiScanResult*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->results)));
  
    if (!(dataBuffer = reinterpret_cast<uint8_t*>(chreHeapAlloc(totalSize)))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiScanEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiScanEvent);
    memcpy(pointer_event, wasm_event, sizeof(struct chreWifiScanEvent));
    
    //copy level2: scannedFreqList
    pointer_event_scannedFreqList = reinterpret_cast<uint32_t*>(nowBuffer);
    nowBuffer += size_event_scannedFreqList;
    memcpy(pointer_event_scannedFreqList,
           wasm_event_scannedFreqList, size_event_scannedFreqList);
    //link level2 to level 1
    pointer_event->scannedFreqList = pointer_event_scannedFreqList;

    //copy level2: results
    pointer_event_results = reinterpret_cast<struct chreWifiScanResult*>(nowBuffer);
    nowBuffer += size_event_results;
    memcpy(pointer_event_results, wasm_event_results, size_event_results);
    //link level2 to level 1
    pointer_event->results = pointer_event_results;
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreBleAdvertisementEvent");
        goto fail1;
    }
    return pointer_event;
fail1:
    chreHeapFree(reinterpret_cast<void*>(dataBuffer));
fail0:
    return 0;  
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreWifiScanEvent) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreWifiScanEvent) {
    chreHeapFree(nativeData);
}

//! for struct chreWifiRangingEvent
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreWifiRangingEvent) {
    const struct chreWifiRangingEvent* native_event = NULL;
    
    uint32_t offset_event = 0;
    uint32_t offset_event_results = 0;

    struct chreWifiRangingEvent* pointer_event = NULL;
    struct chreWifiRangingResult* pointer_event_results = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    uint32_t size_event_results = 0;
    if (!nativeData) {
        goto fail0;
    }
    native_event = reinterpret_cast<const struct chreWifiRangingEvent*>(nativeData);

    //caculate the size of level 1
    totalSize += sizeof(chreWifiRangingEvent);
    //level 2: results, struct chreWifiScanResult *
    size_event_results = native_event->resultCount * sizeof(struct chreWifiRangingResult);
    totalSize += size_event_results;

    if (!(offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,
                                                   reinterpret_cast<void**>(&dataBuffer)))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiRangingEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiRangingEvent);
    memcpy(pointer_event, native_event, sizeof(struct chreWifiRangingEvent));
  
    //copy level2: results
    pointer_event_results = reinterpret_cast<struct chreWifiRangingResult*>(nowBuffer);
    offset_event_results = wasm_runtime_addr_native_to_app(WasmModuleInst, 
                                                  reinterpret_cast<void*>(nowBuffer));
    nowBuffer += size_event_results;
    memcpy(pointer_event_results, native_event->results, size_event_results);
    //link level2 to level 1
    pointer_event->results =
            reinterpret_cast<struct chreWifiRangingResult*>(offset_event_results);
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreBleAdvertisementEvent");
        goto fail1;
    }
    return offset_event;
fail1:
    wasm_runtime_module_free(WasmModuleInst, offset_event);
fail0:
    return 0;
}


WASM_TO_NATIVE_FUNCTION_DECLARATION(chreWifiRangingEvent) {
    const struct chreWifiRangingEvent* wasm_event = NULL;
    const struct chreWifiRangingResult* wasm_event_results = NULL;

    struct chreWifiRangingEvent* pointer_event = NULL;
    struct chreWifiRangingResult* pointer_event_results = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    uint32_t size_event_results = 0;
    if (!eventDataForWASM) {
        goto fail0;
    }
    // validate level 1 boundary
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                        sizeof(struct chreWifiRangingEvent))){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event = reinterpret_cast<const struct chreWifiRangingEvent*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));

    //caculate the size of level 1
    totalSize += sizeof(chreWifiRangingEvent);

    //caculate the size of level 2
    //level 2: results, struct chreWifiScanResult *
    size_event_results = wasm_event->resultCount * sizeof(struct chreWifiScanResult);
    totalSize += size_event_results;
    if (!wasm_runtime_validate_app_addr(WasmModuleInst,
                reinterpret_cast<uint32_t>(wasm_event->results), size_event_results)){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event_results = reinterpret_cast<struct chreWifiRangingResult*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->results)));
  
    if (!(dataBuffer = reinterpret_cast<uint8_t*>(chreHeapAlloc(totalSize)))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiRangingEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiRangingEvent);
    memcpy(pointer_event, wasm_event, sizeof(struct chreWifiRangingEvent));

    //copy level2: results
    pointer_event_results = reinterpret_cast<struct chreWifiRangingResult*>(nowBuffer);
    nowBuffer += size_event_results;
    memcpy(pointer_event_results, wasm_event_results, size_event_results);
    //link level2 to level 1
    pointer_event->results = pointer_event_results;
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreBleAdvertisementEvent");
        goto fail1;
    }
    return pointer_event;
fail1:
    chreHeapFree(reinterpret_cast<void*>(dataBuffer));
fail0:
    return 0;  
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreWifiRangingEvent) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreWifiRangingEvent) {
    chreHeapFree(nativeData);
}

//! for struct chreWifiNanIdentifierEvent
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreWifiNanIdentifierEvent) {
    const struct chreWifiNanIdentifierEvent* native_event = NULL;
    uint32_t offset_event = 0;
    struct chreWifiNanIdentifierEvent* pointer_event = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    if (!nativeData) {
        goto fail0;
    }
    native_event = reinterpret_cast<const struct chreWifiNanIdentifierEvent*>(nativeData);

    //caculate the size of level 1
    totalSize += sizeof(chreWifiNanIdentifierEvent);

    if (!(offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,
                                                   reinterpret_cast<void**>(&dataBuffer)))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiNanIdentifierEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiNanIdentifierEvent);
    memcpy(pointer_event, native_event, offsetof(struct chreWifiNanIdentifierEvent, result.cookie));
    pointer_event->result.cookie = reinterpret_cast<void *>(
        wasm_runtime_addr_native_to_app(WasmModuleInst, const_cast<void *>(native_event->result.cookie)));
    return offset_event;
fail0:
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreWifiNanIdentifierEvent) {
    const struct chreWifiNanIdentifierEvent* wasm_event = NULL;
    struct chreWifiNanIdentifierEvent* pointer_event = NULL;

    if (!eventDataForWASM) {
        goto fail0;
    }
    wasm_event = reinterpret_cast<const struct chreWifiNanIdentifierEvent*>(
                        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));

    if (!(pointer_event = reinterpret_cast<struct chreWifiNanIdentifierEvent*>(
                                    chreHeapAlloc(sizeof(chreWifiNanIdentifierEvent))))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Native failed!");
        goto fail0;
    }
    
    memcpy(pointer_event, wasm_event, offsetof(struct chreWifiNanIdentifierEvent, result.cookie));
    pointer_event->result.cookie = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                        reinterpret_cast<uint32_t>(wasm_event->result.cookie));
    return pointer_event;
fail0:
    return nullptr;
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreWifiNanIdentifierEvent) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreWifiNanIdentifierEvent) {
    chreHeapFree(nativeData);
}

//! for struct chreWifiNanDiscoveryEvent
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreWifiNanDiscoveryEvent) {
    const struct chreWifiNanDiscoveryEvent* native_event = NULL;
    
    uint32_t offset_event = 0;
    uint32_t offset_event_serviceSpecificInfo = 0;

    struct chreWifiNanDiscoveryEvent* pointer_event = NULL;
    uint8_t* pointer_event_serviceSpecificInfo = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    uint32_t size_event_serviceSpecificInfo = 0;
    if (!nativeData) {
        goto fail0;
    }
    native_event = reinterpret_cast<const struct chreWifiNanDiscoveryEvent*>(nativeData);

    //caculate the size of level 1
    totalSize += sizeof(chreWifiNanDiscoveryEvent);
    //level 2
    size_event_serviceSpecificInfo = native_event->serviceSpecificInfoSize;
    totalSize += size_event_serviceSpecificInfo;

    if (!(offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,
                                                   reinterpret_cast<void**>(&dataBuffer)))) {
        LOGE("Allocate memory for struct chreWifiNanDiscoveryEvent in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiNanDiscoveryEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiNanDiscoveryEvent);
    memcpy(pointer_event, native_event, sizeof(struct chreWifiNanDiscoveryEvent));
  
    //copy level2: serviceSpecificInfo
    pointer_event_serviceSpecificInfo = reinterpret_cast<uint8_t*>(nowBuffer);
    offset_event_serviceSpecificInfo = wasm_runtime_addr_native_to_app(WasmModuleInst, 
                                                  reinterpret_cast<void*>(nowBuffer));
    nowBuffer += size_event_serviceSpecificInfo;
    memcpy(pointer_event_serviceSpecificInfo, native_event->serviceSpecificInfo, size_event_serviceSpecificInfo);
    //link level2 to level 1
    pointer_event->serviceSpecificInfo =
            reinterpret_cast<uint8_t*>(offset_event_serviceSpecificInfo);
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreWifiNanDiscoveryEvent");
        goto fail1;
    }
    return offset_event;
fail1:
    wasm_runtime_module_free(WasmModuleInst, offset_event);
fail0:
    return 0;
}


WASM_TO_NATIVE_FUNCTION_DECLARATION(chreWifiNanDiscoveryEvent) {
    const struct chreWifiNanDiscoveryEvent* wasm_event = NULL;
    const uint8_t* wasm_event_serviceSpecificInfo = NULL;

    struct chreWifiNanDiscoveryEvent* pointer_event = NULL;
    uint8_t* pointer_event_serviceSpecificInfo = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;

    uint32_t size_event_serviceSpecificInfo = 0;
    if (!eventDataForWASM) {
        goto fail0;
    }
    // validate level 1 boundary
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                        sizeof(struct chreWifiNanDiscoveryEvent))){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event = reinterpret_cast<const struct chreWifiNanDiscoveryEvent*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));

    //caculate the size of level 1
    totalSize += sizeof(chreWifiNanDiscoveryEvent);

    //caculate the size of level 2
    //level 2: serviceSpecificInfo, struct chreWifiScanResult *
    size_event_serviceSpecificInfo = wasm_event->serviceSpecificInfoSize;
    totalSize += size_event_serviceSpecificInfo;
    if (!wasm_runtime_validate_app_addr(WasmModuleInst,
                reinterpret_cast<uint32_t>(wasm_event->serviceSpecificInfo), size_event_serviceSpecificInfo)){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event_serviceSpecificInfo = reinterpret_cast<uint8_t*>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->serviceSpecificInfo)));
  
    if (!(dataBuffer = reinterpret_cast<uint8_t*>(chreHeapAlloc(totalSize)))) {
        LOGE("Allocate memory for struct chreWifiScanEvent in Native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreWifiNanDiscoveryEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreWifiNanDiscoveryEvent);
    memcpy(pointer_event, wasm_event, sizeof(struct chreWifiNanDiscoveryEvent));

    //copy level2: serviceSpecificInfo
    pointer_event_serviceSpecificInfo = reinterpret_cast<uint8_t*>(nowBuffer);
    nowBuffer += size_event_serviceSpecificInfo;
    memcpy(pointer_event_serviceSpecificInfo, wasm_event_serviceSpecificInfo, size_event_serviceSpecificInfo);
    //link level2 to level 1
    pointer_event->serviceSpecificInfo = pointer_event_serviceSpecificInfo;
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreWifiNanDiscoveryEvent");
        goto fail1;
    }
    return pointer_event;
fail1:
    chreHeapFree(reinterpret_cast<void*>(dataBuffer));
fail0:
    return 0;  
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreWifiNanDiscoveryEvent) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreWifiNanDiscoveryEvent) {
    chreHeapFree(nativeData);
}

//for struct chreWifiNanSessionLostEvent
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreWifiNanSessionLostEvent);

//for struct chreWifiNanSessionTerminatedEvent
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreWifiNanSessionTerminatedEvent);


uint32_t chreWifiGetCapabilitiesWrapper(wasm_exec_env_t exec_env) {
    return chreWifiGetCapabilities();
}

bool chreWifiNanGetCapabilitiesWrapper(wasm_exec_env_t exec_env, struct chreWifiNanCapabilities *capabilities) {
    return chreWifiNanGetCapabilities(capabilities);
}

bool chreWifiConfigureScanMonitorAsyncWrapper(wasm_exec_env_t exec_env, bool enable, const void *cookie) {
    return chreWifiConfigureScanMonitorAsync(enable, cookie);
}

bool chreWifiRequestScanAsyncWrapper(wasm_exec_env_t exec_env, uint32_t offset_params, const void *cookie) {
    struct chreWifiScanParams tmp;
    wasm_module_inst_t WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
    if (!WasmModuleInst) {
        goto fail0;
    }
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, offset_params, sizeof(struct chreWifiScanParams))){
        goto fail0;
    }
    tmp = *(reinterpret_cast<struct chreWifiScanParams*>(
                wasm_runtime_addr_app_to_native(WasmModuleInst, offset_params)));
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, reinterpret_cast<uint32_t>(tmp.frequencyList),
                                       tmp.frequencyListLen * sizeof(*tmp.frequencyList))){
        goto fail0;
    }
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, reinterpret_cast<uint32_t>(tmp.ssidList),
                                       tmp.ssidListLen * sizeof(*tmp.ssidList))){
        goto fail0;
    }
    tmp.frequencyList = reinterpret_cast<const uint32_t *>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(tmp.frequencyList)));
    tmp.ssidList = reinterpret_cast<const struct chreWifiSsidListItem *>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(tmp.ssidList)));
    return chreWifiRequestScanAsync(&tmp, cookie);
fail0:
    return false;
}

bool chreWifiRequestRangingAsyncWrapper(wasm_exec_env_t exec_env, uint32_t offset_params,
                                 const void *cookie) {
    struct chreWifiRangingParams tmp;
    wasm_module_inst_t WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
    if (!WasmModuleInst) {
        goto fail0;
    }
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, offset_params, sizeof(struct chreWifiRangingParams))){
        goto fail0;
    }
    tmp = *(reinterpret_cast<struct chreWifiRangingParams*>
                (wasm_runtime_addr_app_to_native(WasmModuleInst, offset_params)));
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, reinterpret_cast<uint32_t>(tmp.targetList),
                                       tmp.targetListLen * sizeof(*tmp.targetList))){
        goto fail0;
    }
    tmp.targetList = reinterpret_cast<const struct chreWifiRangingTarget *>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(tmp.targetList)));
    return chreWifiRequestRangingAsync(&tmp, cookie);
fail0:
    return false;
}

bool chreWifiNanSubscribeWrapper(wasm_exec_env_t exec_env, struct chreWifiNanSubscribeConfig *config,
                          const void *cookie) {
    char *service = NULL;
    uint8_t *serviceSpecificInfo = NULL;
    uint8_t *matchFilter = NULL;

    uint32_t serviceOffset = 0;
    uint32_t serviceSpecificInfoOffset = 0;
    uint32_t matchFilterOffset = 0;

    uint32_t serviceLength = 0;

    wasm_module_inst_t WasmModuleInst = NULL;

    bool success = (WasmModuleInst=wasm_runtime_get_module_inst(exec_env)) && chreWifiNanSubscribe(config, cookie);

    if (success) {
        // try to find a existed mapping service name
        if(0 != (serviceOffset = getOffset(WasmModuleInst, config->service))) {
            config->service = reinterpret_cast<const char*>(serviceOffset);
        } else {
            serviceLength = strlen(config->service) + 1;
            WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
            serviceOffset = wasm_runtime_module_malloc(WasmModuleInst, serviceLength + 1, \
                                                    reinterpret_cast<void**>(&service));
            success = static_cast<bool>(serviceOffset);
            if (success) {
                memcpy(service, config->service, serviceLength);
                config->service = reinterpret_cast<const char*>(serviceOffset);
                // map this native data to the WASM offset
                setNativeData(WasmModuleInst, service, serviceOffset);
            }
        }

        // try to find a existd mapping serviceSpecificInfo
        if (success && 0 != (serviceSpecificInfoOffset = getOffset(WasmModuleInst,
                                                                   config->serviceSpecificInfo))) {
            config->serviceSpecificInfo = reinterpret_cast<const uint8_t *> (serviceSpecificInfoOffset);
        } else {
            WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
            serviceSpecificInfoOffset = wasm_runtime_module_malloc(WasmModuleInst,
                                            config->serviceSpecificInfoSize,
                                            reinterpret_cast<void**>(&serviceSpecificInfo));
            success = static_cast<bool>(serviceSpecificInfoOffset);
            if (success) {
                memcpy(serviceSpecificInfo, config->serviceSpecificInfo, config->serviceSpecificInfoSize);
                config->serviceSpecificInfo = reinterpret_cast<const uint8_t *>(serviceSpecificInfoOffset);
                // map this native data to the WASM offset
                setNativeData(WasmModuleInst, serviceSpecificInfo, serviceSpecificInfoOffset);
            }
        }

        // try to find a existd mapping matchFilter
        if (success && 0 != (matchFilterOffset = getOffset(WasmModuleInst,
                                                                   config->matchFilter))) {
            config->matchFilter = reinterpret_cast<const uint8_t *> (matchFilterOffset);
        } else {
            WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
            matchFilterOffset = wasm_runtime_module_malloc(WasmModuleInst,
                                            config->matchFilterLength,
                                            reinterpret_cast<void**>(&matchFilter));
            success = static_cast<bool>(matchFilterOffset);
            if (success) {
                memcpy(matchFilter, config->matchFilter, config->matchFilterLength);
                config->matchFilter = reinterpret_cast<const uint8_t *>(matchFilterOffset);
                // map this native data to the WASM offset
                setNativeData(WasmModuleInst, matchFilter, matchFilterOffset);
            }
        }
    }
    return success;
}

bool chreWifiNanSubscribeCancelWrapper(wasm_exec_env_t exec_env, uint32_t subscriptionID) {
    return chreWifiNanSubscribeCancel(subscriptionID);
}

bool chreWifiNanRequestRangingAsyncWrapper(wasm_exec_env_t exec_env, const struct chreWifiNanRangingParams *params,
                                    const void *cookie) {
    return chreWifiNanRequestRangingAsync(params, cookie);
}

#ifdef __cplusplus
}
#endif