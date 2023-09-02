#include "chre/platform/shared/chre_api_wrapper/ble_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"
#define MALLOC_FROM_MODULE(offset, type, pointer) \
            offset = wasm_runtime_module_malloc(WasmModuleInst,\
                        sizeof(type), static_cast<void**>(&pointer));
#ifdef __cplusplus
extern "C" {
#endif

// wasm_module_inst_t WasmModuleInst,  const void *nativeData

//! struct chreBleAdvertisementEvent Begin
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreBleAdvertisementEvent){
    const chreBleAdvertisementEvent *nativeEvent = reinterpret_cast<const chreBleAdvertisementEvent*>(nativeData);
    uint32_t offset_event = 0;
    uint32_t offset_event_reports = 0;
    uint32_t offset_event_reports_data = 0;
    
    struct chreBleAdvertisementEvent *pointer_event = NULL;
    struct chreBleAdvertisingReport *pointer_event_reports = NULL;
    uint8_t *pointer_event_reports_data = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t dataOffset = 0;
    uint32_t totalSize = 0;
    uint32_t secondLevelSize = 0;
    //caculate the size of level 1
    totalSize += sizeof(struct chreBleAdvertisementEvent);
    //caculate the size of level 2
    secondLevelSize = nativeEvent->numReports * sizeof(struct chreBleAdvertisingReport);
    totalSize += secondLevelSize;
    //caculate the size of level 3
    for(uint16_t i = 0;i < nativeEvent->numReports;++i) {
        totalSize += nativeEvent->reports[i].dataLength;
    }
    // malloc 'totalSize' memory
    dataOffset = wasm_runtime_module_malloc(WasmModuleInst, totalSize, reinterpret_cast<void**>(&dataBuffer));
    if (0 == dataOffset) {
        LOGE("Allocate memory for struct chreBleAdvertisementEvent in Wasm failed!");
        goto fail;
    }
    nowBuffer = dataBuffer;
    //copy first level
    offset_event = dataOffset;
    pointer_event = reinterpret_cast<struct chreBleAdvertisementEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreBleAdvertisementEvent);
    memcpy(pointer_event, nativeEvent, offsetof(struct chreBleAdvertisementEvent, reports));
    
    //copy second level
    if (0 != secondLevelSize) {
        offset_event_reports = wasm_runtime_addr_native_to_app(WasmModuleInst, nowBuffer);
        pointer_event_reports = reinterpret_cast<struct chreBleAdvertisingReport*>(nowBuffer);
        nowBuffer += secondLevelSize;
        
        pointer_event->reports = reinterpret_cast<struct chreBleAdvertisingReport*>(offset_event_reports);
        memcpy(pointer_event_reports, nativeEvent->reports, secondLevelSize);

        //copy third level
        for (uint16_t i = 0; i<nativeEvent->numReports ;++i) {
            const struct chreBleAdvertisingReport *nowReports = &(nativeEvent->reports[i]);
            if (0 == nowReports->dataLength){
                continue;
            }
            offset_event_reports_data = wasm_runtime_addr_native_to_app(WasmModuleInst, nowBuffer);
            pointer_event_reports_data = nowBuffer;
            nowBuffer +=  nowReports->dataLength;

            pointer_event_reports[i].data = reinterpret_cast<const uint8_t *>(offset_event_reports_data);
            memcpy(pointer_event_reports_data, nowReports->data, nowReports->dataLength);
        }
    }
    if (nowBuffer != dataBuffer + totalSize) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreBleAdvertisementEvent");
        wasm_runtime_module_free(WasmModuleInst, dataOffset);
        goto fail;
    }
    return dataOffset;
fail:
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreBleAdvertisementEvent){
    const struct chreBleAdvertisementEvent *wasm_event = NULL;
    const struct chreBleAdvertisingReport *wasm_event_reports = NULL;
    const uint8_t *wasm_event_reports_data = NULL;

    struct chreBleAdvertisementEvent *pointer_event = NULL;
    struct chreBleAdvertisingReport *pointer_event_reports = NULL;
    uint8_t *pointer_event_reports_data = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;
    uint32_t secondLevelSize = 0;


    wasm_event = reinterpret_cast<const struct chreBleAdvertisementEvent*>(
        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));
    if (!wasm_event) {
        LOGE("Fail to convert app address to native address");
        goto fail0;
    }
    wasm_event_reports =  reinterpret_cast<const struct chreBleAdvertisingReport *>(
        wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->reports)));
    
    //caculate the size of level 1
    totalSize += sizeof(struct chreBleAdvertisementEvent);
    //caculate the size of level 2
    secondLevelSize = pointer_event->numReports * sizeof(struct chreBleAdvertisingReport);
    totalSize += secondLevelSize;
    //caculate the size of level 3
    for(uint16_t i = 0;i < wasm_event->numReports;++i) {
        totalSize += wasm_event_reports[i].dataLength;
    }
    // malloc 'totalSize' memory
    dataBuffer = reinterpret_cast<uint8_t*>(chreHeapAlloc(totalSize));
    if (!dataBuffer) {
        LOGE("Allocate memory for struct chreBleAdvertisementEvent in native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    //copy first level
    pointer_event = reinterpret_cast<struct chreBleAdvertisementEvent*>(nowBuffer);
    nowBuffer += sizeof(struct chreBleAdvertisementEvent*);
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                sizeof(chreBleAdvertisementEvent))) {
        goto fail1;
    }
    memcpy(pointer_event, wasm_event, offsetof(struct chreBleAdvertisementEvent, reports));
    
    //copy second level
    if (0 != secondLevelSize) {
        pointer_event_reports = reinterpret_cast<struct chreBleAdvertisingReport*>(nowBuffer);
        nowBuffer += secondLevelSize;
        
        pointer_event->reports = pointer_event_reports;
        if(!wasm_runtime_validate_app_addr(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->reports),
                secondLevelSize)) {
            goto fail1;
        }
        memcpy(pointer_event_reports, wasm_event_reports, secondLevelSize);

        //copy third level
        for (uint16_t i = 0; i<wasm_event->numReports ;++i) {
            if (0 == wasm_event_reports[i].dataLength) {
                continue;
            }
            if(!wasm_runtime_validate_app_addr(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event_reports[i].data),
                    wasm_event_reports->dataLength)) {
                goto fail1;
            }
            wasm_event_reports_data = reinterpret_cast<uint8_t*>(
                    wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event_reports[i].data)));
            
            pointer_event_reports_data = nowBuffer;
            nowBuffer +=  wasm_event_reports[i].dataLength;

            pointer_event_reports[i].data = pointer_event_reports_data;
            memcpy(pointer_event_reports_data, wasm_event_reports_data, wasm_event_reports[i].dataLength);
        }
    }
    if (nowBuffer != dataBuffer + totalSize) {
        LOGE("Copy the wrong size of memory in wasm2native: struct chreBleAdvertisementEvent");
        chreHeapFree(dataBuffer);
        goto fail0;
    }
    return pointer_event;
fail1:
    LOGE("The wasm memory to be copied is out of the boundary");
    chreHeapFree(dataBuffer);
fail0:
    return nullptr;
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreBleAdvertisementEvent){
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreBleAdvertisementEvent){
    chreHeapFree(nativeData);
}

/**
 * CHRE API Wrapper
*/
uint32_t chreBleGetCapabilitiesWrapper(wasm_exec_env_t exec_env){
    return chreBleGetCapabilities();
}

uint32_t chreBleGetFilterCapabilitiesWrapper(wasm_exec_env_t exec_env){
    return chreBleGetFilterCapabilities();
}

bool chreBleStartScanAsyncWrapper(wasm_exec_env_t exec_env, enum chreBleScanMode mode,
                                  uint32_t reportDelayMs, const struct chreBleScanFilter *filter) {
    struct chreBleScanFilter tmp;
    if (!filter) {
        return chreBleStartScanAsync(mode, reportDelayMs, nullptr);
    }
    tmp.rssiThreshold = filter->rssiThreshold;
    tmp.scanFilterCount = filter->scanFilterCount;
    wasm_module_inst_t WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
    if (!WasmModuleInst) {
        goto fail;
    }
    tmp.scanFilters = static_cast<chreBleGenericFilter *>(
            wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(filter->scanFilters)));
    return chreBleStartScanAsync(mode, reportDelayMs, &tmp);
fail:
    return false;
}

bool chreBleStopScanAsyncWrapper(wasm_exec_env_t exec_env) {
    return chreBleStopScanAsync();
}

#ifdef __cplusplus
}
#endif