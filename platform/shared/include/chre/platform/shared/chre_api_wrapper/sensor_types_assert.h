#include <stddef.h>

#ifdef _CHRE_SENSOR_TYPES_H_
/**
 * @note for struct chreSensorDataHeader
*/
static_assert(sizeof(struct chreSensorDataHeader) == 16
              && offsetof(struct chreSensorDataHeader, baseTimestamp) == 0
              && offsetof(struct chreSensorDataHeader, sensorHandle) == 8
              && offsetof(struct chreSensorDataHeader, readingCount) == 12
              && offsetof(struct chreSensorDataHeader, accuracy) == 14
              && offsetof(struct chreSensorDataHeader, reserved) == 15);

/**
 * @note for struct chreSensorThreeAxisData
*/
static_assert(sizeof(struct chreSensorThreeAxisData) == 32
              && offsetof(struct chreSensorThreeAxisData, header) == 0
              && offsetof(struct chreSensorThreeAxisData, readings[0].timestampDelta) == 16
              && offsetof(struct chreSensorThreeAxisData, readings[0].x) == 20
              && offsetof(struct chreSensorThreeAxisData, readings[0].y) == 24
              && offsetof(struct chreSensorThreeAxisData, readings[0].z) == 28);

/**
 * @note for struct chreSensorOccurrenceData
*/
static_assert(sizeof(struct chreSensorOccurrenceData) == 20
              && offsetof(struct chreSensorOccurrenceData, header) == 0
              && offsetof(struct chreSensorOccurrenceData, readings[0].timestampDelta) == 16);

/**
 * @note for struct chreSensorFloatData
*/
static_assert(sizeof(struct chreSensorFloatData) == 24
              && offsetof(struct chreSensorFloatData, header) == 0
              && offsetof(struct chreSensorFloatData, readings[0].timestampDelta) == 16
              && offsetof(struct chreSensorFloatData, readings[0].value) == 20);

/**
 * @note for struct chreSensorByteData
*/
static_assert(sizeof(struct chreSensorByteData) == 24
              && offsetof(struct chreSensorByteData, header) == 0
              && offsetof(struct chreSensorByteData, readings[0].timestampDelta) == 16
              && offsetof(struct chreSensorByteData, readings[0].value) == 20);

/**
 * @note for struct chreSensorUint64Data
*/
static_assert(sizeof(struct chreSensorUint64Data) == 28
              && offsetof(struct chreSensorUint64Data, header) == 0
              && offsetof(struct chreSensorUint64Data, readings[0].timestampDelta) == 16
              && offsetof(struct chreSensorUint64Data, readings[0].value) == 20);
#endif