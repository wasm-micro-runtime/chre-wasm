#include "chre/platform/shared/chre_api_wrapper/wrapper_data_map.h"
#include "chre/platform/shared/chre_api_wrapper/sensor_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"

/**
 * @note for struct chreSensorSamplingStatusEvent
*/
STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreSensorSamplingStatusEvent);


/**
 * @note for struct chreSensorFlushCompleteEvent
*/
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreSensorFlushCompleteEvent) {
    const chreSensorFlushCompleteEvent *native_event =
                reinterpret_cast<const chreSensorFlushCompleteEvent *>(nativeData);
    uint32_t offset_event = 0;
    struct chreSensorFlushCompleteEvent *pointer_event = NULL;
    if(!(offset_event = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreSensorFlushCompleteEvent),
                                                reinterpret_cast<void**>(&pointer_event)))) {
        goto fail0;
    }
    memcpy(pointer_event, native_event, offsetof(struct chreSensorFlushCompleteEvent, cookie));
    pointer_event->cookie = reinterpret_cast<const void*>(
        wasm_runtime_addr_native_to_app(WasmModuleInst,
                                        const_cast<void*>(native_event->cookie)));
    return offset_event;
fail0:
    LOGE("Allocate memory for struct chreSensorFlushCompleteEvent in Wasm failed!");
    return 0; 
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreSensorFlushCompleteEvent) {
    const struct chreSensorFlushCompleteEvent *wasm_event = NULL;
    chreSensorFlushCompleteEvent *pointer_event = NULL;
    if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,
                                        sizeof(struct chreSensorFlushCompleteEvent))){
        LOGE("The wasm memory to be copied is out of the boundary");
        goto fail0;
    }
    if(!(pointer_event = reinterpret_cast<struct chreSensorFlushCompleteEvent*>(
                            chreHeapAlloc(sizeof(struct chreSensorFlushCompleteEvent))))) {
        LOGE("Allocate memory for struct chreSensorFlushCompleteEvent in Native failed!");
        goto fail0;
    }
    wasm_event = reinterpret_cast<struct chreSensorFlushCompleteEvent*>(
                            wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM));

    memcpy(pointer_event, wasm_event, offsetof(struct chreSensorFlushCompleteEvent, cookie));
    pointer_event->cookie = reinterpret_cast<const void*>(
        wasm_runtime_addr_app_to_native(WasmModuleInst, reinterpret_cast<uint32_t>(wasm_event->cookie)));
    return pointer_event;
fail0:
    return nullptr;
}


FREE_WASM_EVENT_FUNCTION_DECLARATION(chreSensorFlushCompleteEvent) {
    wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreSensorFlushCompleteEvent) {
    chreHeapFree(nativeData);
}


bool chreSensorFindDefaultWrapper(wasm_exec_env_t exec_env, uint8_t sensorType, uint32_t *handle){
    return chreSensorFindDefault(sensorType, handle);
}

bool chreSensorFindWrapper(wasm_exec_env_t exec_env, uint8_t sensorType, uint8_t sensorIndex, uint32_t *handle) {
    return chreSensorFind(sensorType, sensorIndex, handle);
}

bool chreGetSensorInfoWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle, struct chreSensorInfo *info) {
    uint32_t offset_sensorName = 0;
    uint32_t length_sensorName = 0;
    char *pointer_sensorName = NULL;
    wasm_module_inst_t WasmModuleInst = NULL;
    bool success =  chreGetSensorInfo(sensorHandle, info);
    if (success) {
        // try to find a existed mapping name
        if(0 != (offset_sensorName = getOffset(WasmModuleInst, info->sensorName))) {
            info->sensorName = reinterpret_cast<const char*>(offset_sensorName);
        } else {
            length_sensorName = strlen(info->sensorName) + 1;
            WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
            offset_sensorName = wasm_runtime_module_malloc(WasmModuleInst, length_sensorName + 1,
                                                    reinterpret_cast<void**>(&pointer_sensorName));
            success = static_cast<bool>(offset_sensorName);
            if (success) {
                memcpy(pointer_sensorName, info->sensorName, length_sensorName);
                info->sensorName = reinterpret_cast<const char*>(offset_sensorName);
                // map this native data to the WASM offset
                setNativeData(WasmModuleInst, pointer_sensorName, offset_sensorName);
            }
        }
    }
    return success;
}

bool chreGetSensorSamplingStatusWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle,
                                        struct chreSensorSamplingStatus *status) {
    return chreGetSensorSamplingStatus(sensorHandle, status);
}

bool chreSensorConfigureWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle,
                                enum chreSensorConfigureMode mode,
                                uint64_t interval, uint64_t latency) {
    return chreSensorConfigure(sensorHandle, mode, interval, latency);
}

bool chreSensorConfigureBiasEventsWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle, bool enable) {
    return chreSensorConfigureBiasEvents(sensorHandle, enable);
}

bool chreSensorGetThreeAxisBiasWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle,
                                       struct chreSensorThreeAxisData *bias) {
    return chreSensorGetThreeAxisBias(sensorHandle, bias);
}

bool chreSensorFlushAsyncWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle, const void *cookie) {
    return chreSensorFlushAsync(sensorHandle, cookie);
}
