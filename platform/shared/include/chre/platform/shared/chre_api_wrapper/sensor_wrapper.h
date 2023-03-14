#include "chre/sensor.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifndef _SENSOR_WRAPPER_H_
#define _SENSOR_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @note for struct chreSensorSamplingStatusEvent
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorSamplingStatusEvent);


/**
 * @note for struct chreSensorFlushCompleteEvent
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorFlushCompleteEvent);


bool chreSensorFindDefaultWrapper(wasm_exec_env_t exec_env, uint8_t sensorType, uint32_t *handle);

bool chreSensorFindWrapper(wasm_exec_env_t exec_env, uint8_t sensorType, uint8_t sensorIndex, uint32_t *handle);

bool chreGetSensorInfoWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle, struct chreSensorInfo *info);

bool chreGetSensorSamplingStatusWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle,
                                 struct chreSensorSamplingStatus *status);

bool chreSensorConfigureWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle,
                         enum chreSensorConfigureMode mode,
                         uint64_t interval, uint64_t latency);

bool chreSensorConfigureBiasEventsWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle, bool enable);

bool chreSensorGetThreeAxisBiasWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle,
                                struct chreSensorThreeAxisData *bias);

bool chreSensorFlushAsyncWrapper(wasm_exec_env_t exec_env, uint32_t sensorHandle, const void *cookie);

#ifdef __cplusplus
}
#endif
#endif
