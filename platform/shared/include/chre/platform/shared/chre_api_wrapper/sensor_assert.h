#include <stddef.h>
#ifndef _CHRE_SENSOR_H_

/**
 * @note for struct chreSensorInfo
*/
static_assert(sizeof(struct chreSensorInfo) == 20
              && offsetof(struct chreSensorInfo, sensorName) == 0
              && offsetof(struct chreSensorInfo, sensorType) == 4
              && offsetof(struct chreSensorInfo, minInterval) == 8
              && offsetof(struct chreSensorInfo, sensorIndex) == 16);

/**
 * @note for struct chreSensorSamplingStatus
*/
static_assert(sizeof(struct chreSensorSamplingStatus) == 20
              && offsetof(struct chreSensorSamplingStatus, interval) == 0
              && offsetof(struct chreSensorSamplingStatus, latency) == 8
              && offsetof(struct chreSensorSamplingStatus, enabled) == 16);

/**
 * @note for struct chreSensorSamplingStatusEvent
*/
static_assert(sizeof(struct chreSensorSamplingStatusEvent) == 24
              && offsetof(struct chreSensorSamplingStatusEvent, sensorHandle) == 0
              && offsetof(struct chreSensorSamplingStatusEvent, status) == 4);

/**
 * @note for struct chreSensorFlushCompleteEvent
*/
static_assert(sizeof(struct chreSensorFlushCompleteEvent) == 12
              && offsetof(struct chreSensorFlushCompleteEvent, sensorHandle) == 0
              && offsetof(struct chreSensorFlushCompleteEvent, errorCode) == 4
              && offsetof(struct chreSensorFlushCompleteEvent, reserved[0]) == 5
              && offsetof(struct chreSensorFlushCompleteEvent, cookie) == 8);

#endif