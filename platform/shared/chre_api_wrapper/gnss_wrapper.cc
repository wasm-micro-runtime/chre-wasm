#include "chre/platform/shared/chre_api_wrapper/gnss_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

//! struct chreGnssDataEvent begin
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreGnssDataEvent) {
    const struct chreGnssDataEvent *native_event = 
            reinterpret_cast<const struct chreGnssDataEvent *>(nativeData);
    
    uint32_t offset_event = 0;
    uint32_t offset_event_measurements = 0;

    struct chreGnssDataEvent *pointer_event = NULL;
    struct chreGnssMeasurement *pointer_event_measurements = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;
    uint32_t secondLevelSize = 0;
    //caculate the size of level 1
    totalSize += sizeof(struct chreGnssDataEvent);
    //caculate the size of level 2
    secondLevelSize = native_event->measurement_count * sizeof(struct chreGnssMeasurement);
    totalSize += secondLevelSize;

    offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,
                                              reinterpret_cast<void**>(dataBuffer));
    
    if(!offset_event) {
        LOGE("Allocate memory for struct chreGnssDataEvent in Wasm failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreGnssDataEvent *>(nowBuffer);
    offset_event = wasm_runtime_addr_native_to_app(WasmModuleInst, reinterpret_cast<void*>(pointer_event));
    nowBuffer += sizeof(chreGnssDataEvent);
    memcpy(pointer_event, native_event, offsetof(struct chreGnssDataEvent, measurements));

    //copy level 2
    pointer_event_measurements = reinterpret_cast<struct chreGnssMeasurement *>(nowBuffer);
    offset_event_measurements = wasm_runtime_addr_native_to_app(WasmModuleInst, 
                                        reinterpret_cast<void*>(pointer_event_measurements));
    nowBuffer += secondLevelSize;
    memcpy(pointer_event_measurements, native_event->measurements, secondLevelSize);
    
    //link level 2 to level 1
    pointer_event->measurements = 
                reinterpret_cast<struct chreGnssMeasurement *>(offset_event_measurements);
    
    if (dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in native2wasm: struct chreGnssDataEvent");
        goto fail1;
    }
    return offset_event;
fail1:
    wasm_runtime_module_free(WasmModuleInst, offset_event);
fail0:
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreGnssDataEvent){
    const struct chreGnssDataEvent *wasm_event = NULL;
    const struct chreGnssMeasurement *wasm_event_measurements = NULL;

    struct chreGnssDataEvent *pointer_event = NULL;
    struct chreGnssMeasurement *pointer_event_measurements = NULL;

    uint8_t *dataBuffer = NULL, *nowBuffer = NULL;
    uint32_t totalSize = 0;
    uint32_t secondLevelSize = 0;
    //caculate the size of level 1 and validate boundary
    totalSize += sizeof(struct chreGnssDataEvent);
    if(!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                   sizeof(struct chreGnssDataEvent))) {
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    //caculate the size of level 2
    wasm_event = reinterpret_cast<const struct chreGnssDataEvent *>(
                wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));

    secondLevelSize = wasm_event->measurement_count * sizeof(struct chreGnssMeasurement);
    totalSize += secondLevelSize;
    if(!wasm_runtime_validate_app_addr(WasmModuleInst,
            reinterpret_cast<uint32_t>(wasm_event->measurements), secondLevelSize)) {
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    wasm_event_measurements = reinterpret_cast<struct chreGnssMeasurement *>(
        wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->measurements)));

    dataBuffer = reinterpret_cast<uint8_t*>(chreHeapAlloc(totalSize));
    if(!dataBuffer) {
        LOGE("Allocate memory for struct chreGnssDataEvent in Native failed!");
        goto fail0;
    }
    nowBuffer = dataBuffer;
    
    //copy level 1
    pointer_event = reinterpret_cast<struct chreGnssDataEvent *>(nowBuffer);
    nowBuffer += sizeof(struct chreGnssDataEvent);
    memcpy(pointer_event, wasm_event, offsetof(struct chreGnssDataEvent, measurements));

    //copy level 2
    pointer_event_measurements = reinterpret_cast<struct chreGnssMeasurement *>(nowBuffer);
    nowBuffer += secondLevelSize;
    memcpy(pointer_event_measurements, wasm_event_measurements, secondLevelSize);

    //link level 2 to level 1
    pointer_event->measurements = pointer_event_measurements;
    if(dataBuffer + totalSize != nowBuffer) {
        LOGE("Copy the wrong size of memory in wasm2native: struct chreGnssDataEvent");
        goto fail1;
    }
    return pointer_event;
fail1:
    chreHeapFree(dataBuffer);
fail0:
    return nullptr;
}


FREE_WASM_EVENT_FUNCTION_DECLARATION(chreGnssDataEvent) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreGnssDataEvent) {
    chreHeapFree(nativeData);
}

//! struct chreGnssLocationEvent begin
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreGnssLocationEvent);

/**
 * CHRE API Wrapper
*/
uint32_t chreGnssGetCapabilitiesWrapper(wasm_exec_env_t exec_env){
    return chreGnssGetCapabilities();
}

bool chreGnssLocationSessionStartAsyncWrapper(wasm_exec_env_t exec_env, uint32_t minIntervalMs,
                                              uint32_t minTimeToNextFixMs, const void *cookie){
    return chreGnssLocationSessionStartAsync(minIntervalMs, minTimeToNextFixMs, cookie);
}
bool chreGnssLocationSessionStopAsyncWrapper(wasm_exec_env_t exec_env, const void *cookie){
    return chreGnssLocationSessionStopAsync(cookie);
}
bool chreGnssMeasurementSessionStartAsyncWrapper(wasm_exec_env_t exec_env, uint32_t minIntervalMs,
                                                 const void *cookie){
    return chreGnssMeasurementSessionStartAsync(minIntervalMs, cookie);
}
bool chreGnssMeasurementSessionStopAsyncWrapper(wasm_exec_env_t exec_env, const void *cookie){
    return chreGnssMeasurementSessionStopAsync(cookie);
}
bool chreGnssConfigurePassiveLocationListenerWrapper(wasm_exec_env_t exec_env, bool enable){
    return chreGnssConfigurePassiveLocationListener(enable);
}

#ifdef __cplusplus
}
#endif