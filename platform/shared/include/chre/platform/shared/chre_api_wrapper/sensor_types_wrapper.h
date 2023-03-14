
#include "chre/sensor_types.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifndef _SENSOR_TYPE_WRAPPER_H_
#define _SENSOR_TYPE_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @note for struct chreSensorThreeAxisData
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorThreeAxisData);

/**
 * @note for struct chreSensorOccurrenceData
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorOccurrenceData);

/**
 * @note for struct chreSensorFloatData
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorFloatData);

/**
 * @note for struct chreSensorByteData
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorByteData);

/**
 * @note for struct chreSensorUint64Data
*/
CONVERSION_FUNCTIONS_DECLARATION(chreSensorUint64Data);

#ifdef __cplusplus
}
#endif
#endif