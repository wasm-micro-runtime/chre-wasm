
#include "chre/platform/shared/chre_api_wrapper/audio_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/ble_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/common_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/event_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/gnss_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/nanoapp_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/re_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/sensor_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/sensor_types_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/toolchain_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/user_settings_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/version_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/wifi_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/wwan_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/event_transform.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
// static NATIVE_TO_WASM_FUNCTION_DECLARATION(other);
// static WASM_TO_NATIVE_FUNCTION_DECLARATION(other);
// static FREE_WASM_EVENT_FUNCTION_DECLARATION(other);
// static FREE_NATIVE_EVENT_FUNCTION_DECLARATION(other);

static const convertFunctions functionTable[] = {
    //! CHRE_EVENT_MESSAGE_FROM_HOST, struct chreMessageFromHostData
    {
        CHRE_EVENT_MESSAGE_FROM_HOST,
        CONVERSION_FUNCTION_POINTERS(chreMessageFromHostData)
    },
    //! CHRE_EVENT_TIMER, 'cookie' given to chreTimerSet() method
    {
        CHRE_EVENT_TIMER,
        CONVERSION_FUNCTION_POINTERS(cookie)
    },
    //! CHRE_EVENT_NANOAPP_STARTED, struct chreNanoappInfo
    {
        CHRE_EVENT_NANOAPP_STARTED,
        CONVERSION_FUNCTION_POINTERS(chreNanoappInfo)
    },
    //! CHRE_EVENT_NANOAPP_STOPPED, struct chreNanoappInfo
    {
        CHRE_EVENT_NANOAPP_STOPPED,
        CONVERSION_FUNCTION_POINTERS(chreNanoappInfo)
    },
    //! CHRE_EVENT_HOST_AWAKE, NULL
    {
        CHRE_EVENT_HOST_AWAKE,
        nullptr, nullptr, nullptr, nullptr
    },
    //! CHRE_EVENT_HOST_ASLEEP, NULL
    {
        CHRE_EVENT_HOST_ASLEEP,
        nullptr, nullptr, nullptr, nullptr
    },
    //! CHRE_EVENT_DEBUG_DUMP, NULL
    {
        CHRE_EVENT_DEBUG_DUMP,
        nullptr, nullptr, nullptr, nullptr
    },
    //! CHRE_EVENT_HOST_ENDPOINT_NOTIFICATION, struct chreHostEndpointNotification
    {
        CHRE_EVENT_NANOAPP_STOPPED,
        CONVERSION_FUNCTION_POINTERS(chreHostEndpointNotification)
    },
    // chre/sensor.h begin
    //! CHRE_EVENT_SENSOR_ACCELEROMETER_DATA, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_ACCELEROMETER_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_INSTANT_MOTION_DETECT_DATA, struct chreSensorOccurrenceData
    {
        CHRE_EVENT_SENSOR_INSTANT_MOTION_DETECT_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorOccurrenceData)
    },
    //! CHRE_EVENT_SENSOR_STATIONARY_DETECT_DATA, struct chreSensorOccurrenceData
    {
        CHRE_EVENT_SENSOR_STATIONARY_DETECT_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorOccurrenceData)
    },
    //! CHRE_EVENT_SENSOR_GYROSCOPE_DATA, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_GYROSCOPE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_GEOMAGNETIC_FIELD_DATA, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_GEOMAGNETIC_FIELD_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_PRESSURE_DATA, struct chreSensorFloatData
    {
        CHRE_EVENT_SENSOR_PRESSURE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorFloatData)
    },
    //! CHRE_EVENT_SENSOR_LIGHT_DATA, struct chreSensorFloatData
    {
        CHRE_EVENT_SENSOR_LIGHT_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorFloatData)
    },
    //! CHRE_EVENT_SENSOR_PROXIMITY_DATA, struct chreSensorByteData
    {
        CHRE_EVENT_SENSOR_PROXIMITY_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorByteData)
    },
    //! CHRE_EVENT_SENSOR_STEP_DETECT_DATA, struct chreSensorOccurrenceData
    {
        CHRE_EVENT_SENSOR_STEP_DETECT_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorOccurrenceData)
    },
    //! CHRE_EVENT_SENSOR_STEP_COUNTER_DATA, struct chreSensorUint64Data
    {
        CHRE_EVENT_SENSOR_STEP_COUNTER_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorUint64Data)
    },
    //! CHRE_EVENT_SENSOR_HINGE_ANGLE_DATA, struct chreSensorFloatData
    {
        CHRE_EVENT_SENSOR_HINGE_ANGLE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorFloatData)
    },
    //! CHRE_EVENT_SENSOR_UNCALIBRATED_ACCELEROMETER_DATA, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_UNCALIBRATED_ACCELEROMETER_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_UNCALIBRATED_GYROSCOPE_DATA, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_UNCALIBRATED_GYROSCOPE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_UNCALIBRATED_GEOMAGNETIC_FIELD_DATA, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_UNCALIBRATED_GEOMAGNETIC_FIELD_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_ACCELEROMETER_TEMPERATURE_DATA, struct chreSensorFloatData
    {
        CHRE_EVENT_SENSOR_ACCELEROMETER_TEMPERATURE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorFloatData)
    },
    //! CHRE_EVENT_SENSOR_GYROSCOPE_TEMPERATURE_DATA, struct chreSensorFloatData
    {
        CHRE_EVENT_SENSOR_GYROSCOPE_TEMPERATURE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorFloatData)
    },
    //! CHRE_EVENT_SENSOR_GEOMAGNETIC_FIELD_TEMPERATURE_DATA, struct chreSensorFloatData
    {
        CHRE_EVENT_SENSOR_GEOMAGNETIC_FIELD_TEMPERATURE_DATA,
        CONVERSION_FUNCTION_POINTERS(chreSensorFloatData)
    },
    //! sensor events which are not data from the sensor
    //! CHRE_EVENT_SENSOR_SAMPLING_CHANGE, struct chreSensorSamplingStatusEvent
    {
        CHRE_EVENT_SENSOR_SAMPLING_CHANGE,
        CONVERSION_FUNCTION_POINTERS(chreSensorSamplingStatusEvent)
    },
    //! CHRE_EVENT_SENSOR_GYROSCOPE_BIAS_INFO, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_GYROSCOPE_BIAS_INFO,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_GEOMAGNETIC_FIELD_BIAS_INFO, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_GEOMAGNETIC_FIELD_BIAS_INFO,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_ACCELEROMETER_BIAS_INFO, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_ACCELEROMETER_BIAS_INFO,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_FLUSH_COMPLETE, struct chreSensorFlushCompleteEvent
    {
        CHRE_EVENT_SENSOR_FLUSH_COMPLETE,
        CONVERSION_FUNCTION_POINTERS(chreSensorFlushCompleteEvent)
    },
    //! CHRE_EVENT_SENSOR_UNCALIBRATED_GYROSCOPE_BIAS_INFO, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_UNCALIBRATED_GYROSCOPE_BIAS_INFO,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_UNCALIBRATED_GEOMAGNETIC_FIELD_BIAS_INFO, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_UNCALIBRATED_GEOMAGNETIC_FIELD_BIAS_INFO,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    //! CHRE_EVENT_SENSOR_UNCALIBRATED_ACCELEROMETER_BIAS_INFO, struct chreSensorThreeAxisData
    {
        CHRE_EVENT_SENSOR_UNCALIBRATED_ACCELEROMETER_BIAS_INFO,
        CONVERSION_FUNCTION_POINTERS(chreSensorThreeAxisData)
    },
    // chre/gnss.h begin
    //! CHRE_EVENT_GNSS_ASYNC_RESULT, struct chreAsyncResult
    {
        CHRE_EVENT_GNSS_ASYNC_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreAsyncResult)
    },
    //! CHRE_EVENT_GNSS_LOCATION, struct chreGnssLocationEvent
    {
        CHRE_EVENT_GNSS_LOCATION,
        CONVERSION_FUNCTION_POINTERS(chreGnssLocationEvent)
    },
    //! CHRE_EVENT_GNSS_DATA, struct chreGnssDataEvent
    {
        CHRE_EVENT_GNSS_DATA,
        CONVERSION_FUNCTION_POINTERS(chreGnssDataEvent)
    },
    //! chre/wifi.h begin
    //! CHRE_EVENT_WIFI_ASYNC_RESULT, struct chreAsyncResult
    {
        CHRE_EVENT_WIFI_ASYNC_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreAsyncResult)
    },
    //! CHRE_EVENT_WIFI_SCAN_RESULT, struct chreWifiScanEvent
    {
        CHRE_EVENT_WIFI_SCAN_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreWifiScanEvent)
    },
    //! CHRE_EVENT_WIFI_RANGING_RESULT, struct chreWifiRangingEvent
    {
        CHRE_EVENT_WIFI_RANGING_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreWifiRangingEvent)
    },
    //! CHRE_EVENT_WIFI_NAN_IDENTIFIER_RESULT, struct chreWifiNanIdentifierEvent
    {
        CHRE_EVENT_WIFI_NAN_IDENTIFIER_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreWifiNanIdentifierEvent)
    },
    //! CHRE_EVENT_WIFI_NAN_DISCOVERY_RESULT, struct chreWifiNanDiscoveryEvent
    {
        CHRE_EVENT_WIFI_NAN_DISCOVERY_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreWifiNanDiscoveryEvent)
    },
    //! CHRE_EVENT_WIFI_NAN_SESSION_LOST, struct chreWifiNanSessionLostEvent
    {
        CHRE_EVENT_WIFI_NAN_SESSION_LOST,
        CONVERSION_FUNCTION_POINTERS(chreWifiNanSessionLostEvent)
    },
    //! CHRE_EVENT_WIFI_NAN_SESSION_TERMINATED, struct chreWifiNanSessionTerminatedEvent
    {
        CHRE_EVENT_WIFI_NAN_SESSION_TERMINATED,
        CONVERSION_FUNCTION_POINTERS(chreWifiNanSessionTerminatedEvent)
    },

    //! chre/wwan.h begin
    //! CHRE_EVENT_WWAN_CELL_INFO_RESULT, struct chreWwanCellInfoResult
    {
        CHRE_EVENT_WWAN_CELL_INFO_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreWwanCellInfoResult)
    },

    //! chre/audio.h
    //! CHRE_EVENT_AUDIO_SAMPLING_CHANGE, struct chreAudioSourceStatusEvent
    {
        CHRE_EVENT_AUDIO_SAMPLING_CHANGE,
        CONVERSION_FUNCTION_POINTERS(chreAudioSourceStatusEvent)
    },
    //! CHRE_EVENT_AUDIO_DATA, struct chreAudioDataEvent
    {
        CHRE_EVENT_AUDIO_DATA,
        CONVERSION_FUNCTION_POINTERS(chreAudioDataEvent)
    },

    //! chre/user_settings.h begin
    //! CHRE_EVENT_SETTING_CHANGED_LOCATION, struct chreUserSettingChangedEvent
    {
        CHRE_EVENT_SETTING_CHANGED_LOCATION,
        CONVERSION_FUNCTION_POINTERS(chreUserSettingChangedEvent)
    },
    //! CHRE_EVENT_SETTING_CHANGED_WIFI_AVAILABLE, struct chreUserSettingChangedEvent
    {
        CHRE_EVENT_SETTING_CHANGED_WIFI_AVAILABLE,
        CONVERSION_FUNCTION_POINTERS(chreUserSettingChangedEvent)
    },
    //! CHRE_EVENT_SETTING_CHANGED_AIRPLANE_MODE, struct chreUserSettingChangedEvent
    {
        CHRE_EVENT_SETTING_CHANGED_AIRPLANE_MODE,
        CONVERSION_FUNCTION_POINTERS(chreUserSettingChangedEvent)
    },
    //! CHRE_EVENT_SETTING_CHANGED_MICROPHONE, struct chreUserSettingChangedEvent
    {
        CHRE_EVENT_SETTING_CHANGED_MICROPHONE,
        CONVERSION_FUNCTION_POINTERS(chreUserSettingChangedEvent)
    },
    //! CHRE_EVENT_SETTING_CHANGED_BLE_AVAILABLE, struct chreUserSettingChangedEvent
    {
        CHRE_EVENT_SETTING_CHANGED_BLE_AVAILABLE,
        CONVERSION_FUNCTION_POINTERS(chreUserSettingChangedEvent)
    },

    //! chre/ble.h begin
    //! CHRE_EVENT_BLE_ASYNC_RESULT, struct chreAsyncResult
    {
        CHRE_EVENT_BLE_ASYNC_RESULT,
        CONVERSION_FUNCTION_POINTERS(chreAsyncResult)
    },
    //! CHRE_EVENT_BLE_ADVERTISEMENT, struct chreBleAdvertisementEvent
    {
        CHRE_EVENT_BLE_ADVERTISEMENT,
        CONVERSION_FUNCTION_POINTERS(chreBleAdvertisementEvent)
    },  
};

static uint32_t funtionTableSize = sizeof(functionTable) / sizeof(convertFunctions);

// static const otherTypeConvertFunctions = {
//     0,
//     CONVERSION_FUNCTION_POINTERS(other)
// }

const convertFunctions* getConvertFunctions(const uint32_t type) {
    for(uint32_t i = 0;i < funtionTableSize;i++) {
        if(functionTable[i].eventType == type) {
            return &functionTable[i];
        }
    }
    // return &otherTypeConvertFunctions;
    return nullptr;
}

#ifdef __cplusplus
}
#endif
