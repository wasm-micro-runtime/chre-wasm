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
//! struct chreBleAdvertisementEvent Begin
uint32_t chreBleAdvertisementEventWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                   const chreBleAdvertisementEvent *eventData) {
    uint32_t structDataOffset = 0;
    uint32_t reportsOffset = 0;
    uint32_t dataOfReportsOffset = 0;
    chreBleAdvertisementEventWrapper *structData = NULL;
    chreBleAdvertisingReportWrapper *reports = NULL;
    uint8_t *dataOfReports = NULL;
    uint32_t reportsSize = 0;
    uint32_t dataOfReportsSize = 0;

    chreBleAdvertisingReport* reportOfEventData = NULL;
    if (!eventData) {
        goto fail1;
    }
    //apply memory for the first level
    if(!(structDataOffset = wasm_runtime_module_malloc(WasmModuleInst,
                                                       sizeof(chreBleAdvertisementEventWrapper),
                                                       static_cast<void**>(&structData)))) {
        goto fail1;
    }
    //! caculate the second level size
    reportsSize = eventData->numReports * sizeof(chreBleAdvertisingReportWrapper);
    //! apply memory for the second level
    if(!(reportsOffset = wasm_runtime_module_malloc(WasmModuleInst, reportsSize,
                                                    static_cast<void**>(reports)))) {
        goto fail2;
    }
    //! copy the first level
    memcpy(structData, eventData, offsetof(chreBleAdvertisementEventWrapper, reportsPointer));
    for (int i = 0;i < eventData->numReports; ++i) {
        reports[i].dataPointer = 0;
    }
    structData->reportsPointer = reportsOffset;
    //!  and copy the second level
    reportOfEventData = eventData->reports;
    for (int i = 0;i < eventData->numReports; ++i) {
        //! caculate the third level size
        dataOfReportsSize = reportOfEventData[i].dataLength;
        //！ apply memory for the third level
        if(!(dataOfReportsOffset = wasm_runtime_module_malloc(WasmModuleInst, dataOfReportsSize,
                                                          static_cast<void**>(dataOfReports)))) {
            goto fail3;
        }
        //! copy the second level
        memcpy(&reports[i], &reportOfEventData[i], offsetof(chreBleAdvertisingReportWrapper,
                                                            dataPointer));
        reports[i].dataPointer = dataOfReportsOffset;
        reports[i].reserved = 0;
        //! copy the third level
        memcpy(dataOfReports, reportOfEventData[i].data, dataOfReportsSize);
    }
    return structDataOffset;
fail3:
    for (int i = 0; i < eventData->numReports;++i) {
        if (0 == reports[i].dataPointer) {
            break;
        }
        wasm_runtime_module_free(WasmModuleInst, reports[i].dataPointer);
    }
    wasm_runtime_module_free(WasmModuleInst, reportsOffset);
fail2:
    wasm_runtime_module_free(WasmModuleInst, structDataOffset);
fail1:
    LOGE("Allocate memory for struct chreBleAdvertisementEvent in Wasm failed!");
    return 0;
}
chreBleAdvertisementEvent *chreBleAdvertisementEventCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                            uint32_t eventDataForWASM) {
    chreBleAdvertisementEvent *eventData = NULL;
    chreBleAdvertisingReport *reportsOfeventData = NULL;
    uint8_t *dataOfReport = NULL;

    chreBleAdvertisementEventWrapper *structData = NULL;
    chreBleAdvertisingReportWrapper *reports = NULL;

    uint32_t reportsOfeventDataSize = 0;
    uint32_t dataOfReportSize = 0;

    bool success = true;
    if (!(structData = static_cast<chreBleAdvertisementEventWrapper *>(
                            wasm_runtime_addr_app_to_native(WasmModuleInst,
                            eventDataForWASM)))) {
        LOGE("Try to copy memory not belonging to the current Wasm module!");
        success = false;
        goto fail1;
    }
    if (!(structData = static_cast<chreBleAdvertisingReport *>(
                            wasm_runtime_addr_app_to_native(WasmModuleInst,
                            structData->reportsPointer)))) {
        LOGE("Try to copy memory not belonging to the current Wasm module!");
        success = false;
        goto fail1;
    }
    //copy the first level
    if(!(eventData = static_cast<chreBleAdvertisementEvent*>(
                        chreHeapAlloc(sizeof(chreBleAdvertisementEvent))))) {
        success = false;
        goto fail1;
    }
    //caculate the second level size
    reportsOfeventDataSize = structData->numReports * sizeof(chreBleAdvertisingReport);
    if(!(reportsOfeventData = static_cast<chreBleAdvertisingReport*>(
                        chreHeapAlloc(reportsOfeventDataSize)))) {
        success = false;
        goto fail2;
    }
    // copy the first level
    eventData->reserved = structData->reserved;
    eventData->numReports = structData->numReports;
    eventData->reports = reportsOfeventData;
    for (int i = 0;i < structData->numReports; ++i) {
        reportsOfeventData[i].data = NULL;
    }
    // copy the second level
    for (int i = 0;i < structData->numReports; ++i) {
        dataOfReportSize = reports[i].dataLength;
        if(!(dataOfReport = static_cast<uint8_t*>(chreHeapAlloc(dataOfReportSize)))) {
        success = false;
            goto fail3;
        }
        memcpy(&reportsOfeventData[i], &reports[i],
               offsetof(chreBleAdvertisingReportWrapper, dataPointer));
        reportsOfeventData[i].data = dataOfReport;
        // copy the third level
        memcpy(dataOfReport, reports->data, dataOfReportSize);
        reportsOfeventData[i].reserved = reports[i].reserved;
    }
    return eventData;
fail3:
    for (int i = 0;i < structData->numReports; ++i) {
        if(!reportsOfeventData[i].data) {
            break;
        }
        chreHeapFree(reportsOfeventData[i].data);
    }
    chreHeapFree(reportsOfeventData);
fail2:
    chreHeapFree(eventData);
fail1:
    if (!success) {
        LOGE("Try to release memory not belonging to the current Wasm moudle!");
    }
    return nullptr;
}

void chreBleAdvertisementEventWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                      uint32_t eventDataForWASM) {
    chreBleAdvertisementEventWrapper *structData = NULL;
    chreBleAdvertisingReportWrapper *reports = NULL;
    bool success = true;
    if (!(structData = wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM))) {
        success = false;
        goto fail1;
    }
    if (!(reports = wasm_runtime_addr_app_to_native(WasmModuleInst, structData->reportsPointer))) {
        success = false;
        goto fail2;
    }
    for (int i = 0; i < eventData->numReports; ++i) {
        if (0 == reports[i].dataPointer) {
            success = false;
            goto fail3;
        }
        wasm_runtime_module_free(WasmModuleInst, reports[i].dataPointer);
    }
fail3:
    wasm_runtime_module_free(WasmModuleInst, structData->reportsPointer);
fail2:
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
fail1:
    if(!success) {
        LOGE("Try to release memory not belongs to the current Wasm Module");
    }
}

void chreBleAdvertisementEventRelease(chreBleAdvertisementEvent *eventData) {
    chreBleAdvertisingReport *reportsOfeventData = NULL;
    if (!eventData) {
        return;
    }
    reportsOfeventData = eventData->reports;
    if (!reportsOfeventData) {
        goto fail1;
    }
    for (int i = 0;i < eventData->numReports; ++i) {
        if(!reportsOfeventData[i].data) {
            goto fail2;
        }
        chreHeapFree(reportsOfeventData[i].data);
    }
fail2:
    chreHeapFree(reportsOfeventData);
fail1:
    chreHeapFree(eventData);
}

/**
 * CHRE API Wrapper
*/
uint32_t chreBleGetCapabilitiesWrapper(wasm_exec_env_t exec_env){
    return chreBleGetCapabilities();
}

uint32_t chreBleGetFilterCapabilitiesWrapper(wasm_exec_env_t exec_env){
    return chreBleGetFilterCapabilities()
}

bool chreBleStartScanAsyncWrapper(wasm_exec_env_t exec_env, enum chreBleScanMode mode,
                                  uint32_t reportDelayMs, const chreBleScanFilterWrapper *filter) {
    chreBleScanFilter tmp;
    tmp.rssiThreshold = filter->rssiThreshold;
    tmp.scanFilterCount = filter->scanFilterCount;
    wasm_module_inst_t WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
    if (!WasmModuleInst) {
        goto fail;
    }
    tmp.scanFilters = wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                      filter->scanFiltersPointer);
    chreBleStartScanAsync(mode, reportDelayMs, &tmp);
fail:
    return false;
}

bool chreBleStopScanAsyncWrapper(wasm_exec_env_t exec_env) {
    chreBleStopScanAsync();
}

#ifdef __cplusplus
}
#endif