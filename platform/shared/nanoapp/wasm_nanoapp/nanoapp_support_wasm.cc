#include "chre_nsl_internal/platform/shared/nanoapp/wasm_nanoapp/nanoapp_support_wasm.h"

#include <chre.h>
#include <stdio.h>

#include "chre_nsl_internal/util/macros.h"
#include "chre_nsl_internal/util/system/napp_permissions.h"

#ifdef CHRE_NANOAPP_USES_WIFI
#include "chre_nsl_internal/util/system/wifi_util.h"
#endif
namespace {

constexpr uint32_t kNanoappPermissions = 0
// DO NOT USE this macro outside of specific CHQTS nanoapps. This is only used
// to allow testing of invalid permission declarations.
#ifdef CHRE_TEST_NANOAPP_PERMS
                                         | CHRE_TEST_NANOAPP_PERMS
#else
#ifdef CHRE_NANOAPP_USES_AUDIO
    | static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_AUDIO)
#endif
#ifdef CHRE_NANOAPP_USES_BLE
    | static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_BLE)
#endif
#ifdef CHRE_NANOAPP_USES_GNSS
    | static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_GNSS)
#endif
#ifdef CHRE_NANOAPP_USES_WIFI
    | static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_WIFI)
#endif
#ifdef CHRE_NANOAPP_USES_WWAN
    | static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_WWAN)
#endif
#endif  // CHRE_TEST_NANOAPP_PERMS
    ;

#if defined(CHRE_SLPI_UIMG_ENABLED) || defined(CHRE_TCM_ENABLED)
constexpr int kIsTcmNanoapp = 1;
#else
constexpr int kIsTcmNanoapp = 0;
#endif  // CHRE_SLPI_UIMG_ENABLED

#if !defined(CHRE_NANOAPP_DISABLE_BACKCOMPAT) && defined(CHRE_NANOAPP_USES_GNSS)
// Return a v1.3+ GnssLocationEvent for the nanoapp when running on a v1.2-
// platform.
chreGnssLocationEvent translateLegacyGnssLocation(
    const chreGnssLocationEvent &legacyEvent) {
  // Copy v1.2- fields over to a v1.3+ event.
  chreGnssLocationEvent newEvent = {};
  newEvent.timestamp = legacyEvent.timestamp;
  newEvent.latitude_deg_e7 = legacyEvent.latitude_deg_e7;
  newEvent.longitude_deg_e7 = legacyEvent.longitude_deg_e7;
  newEvent.altitude = legacyEvent.altitude;
  newEvent.speed = legacyEvent.speed;
  newEvent.bearing = legacyEvent.bearing;
  newEvent.accuracy = legacyEvent.accuracy;
  newEvent.flags = legacyEvent.flags;

  // Unset flags that are defined in v1.3+ but not in v1.2-.
  newEvent.flags &= ~(CHRE_GPS_LOCATION_HAS_ALTITUDE_ACCURACY |
                      CHRE_GPS_LOCATION_HAS_SPEED_ACCURACY |
                      CHRE_GPS_LOCATION_HAS_BEARING_ACCURACY);
  return newEvent;
}

void nanoappHandleEventCompat(uint32_t senderInstanceId, uint16_t eventType,
                              const void *eventData) {
  if (eventType == CHRE_EVENT_GNSS_LOCATION &&
      chreGetApiVersion() < CHRE_API_VERSION_1_3) {
    chreGnssLocationEvent event = translateLegacyGnssLocation(
        *static_cast<const chreGnssLocationEvent *>(eventData));
    nanoappHandleEvent(senderInstanceId, eventType, &event);
  } else {
    nanoappHandleEvent(senderInstanceId, eventType, eventData);
  }
}
#endif

}  // anonymous namespace

extern "C" const char _chreNanoappUnstableId[]
      __attribute__((aligned(8))) = NANOAPP_UNSTABLE_ID;

extern "C" const struct chreNslNanoappInfo _chreNanoappInfo = {
    /* magic */ CHRE_NSL_NANOAPP_INFO_MAGIC,
    /* structMinorVersion */ CHRE_NSL_NANOAPP_INFO_STRUCT_MINOR_VERSION,
    /* isSystemNanoapp */ NANOAPP_IS_SYSTEM_NANOAPP,
    /* isTcmNanoapp */ kIsTcmNanoapp,
    /* reservedFlags */ 0,
    /* reserved */ 0,
    /* targetApiVersion */ CHRE_API_VERSION,

    // These values are supplied by the build environment.
    /* vendor */ NANOAPP_VENDOR_STRING,
    /* name */ NANOAPP_NAME_STRING,
    /* appId */ NANOAPP_ID,
    /* appVersion */ NANOAPP_VERSION,
    /* entryPoints */
    {
        /* start */ nanoappStart,
#if !defined(CHRE_NANOAPP_DISABLE_BACKCOMPAT) && defined(CHRE_NANOAPP_USES_GNSS)
        /* handleEvent */ nanoappHandleEventCompat,
#else
        /* handleEvent */ nanoappHandleEvent,
#endif
        /* end */ nanoappEnd,
    },
    /* appVersionString */ _chreNanoappUnstableId,
    /* appPermissions */ kNanoappPermissions,
};

#ifdef __cplusplus
extern "C" {
#endif
const chreNslNanoappInfo* getNanoappInfo(){
    return &_chreNanoappInfo;
}

/**
 * @note It is implemented in native, and thwe wasm nanoapp will use
 * "wasm call native" to call this function.
*/
void chreLogWrapper(enum chreLogLevel, const char*, const char*);
/**
 * @todo do we need a flex size buffer?
*/
void chreLog(enum chreLogLevel level, const char *formatStr, ...) {
    // This is for linux
    char strBuffer[512];
    va_list args;
    va_start(args, formatStr);
    vsnprintf(strBuffer, 512, formatStr, args);
    va_end(args);
    chreLogWrapper(level, "%s", strBuffer);
}

void chreDebugDumpLogWrapper(const char*, const char*);
/**
 * @todo we may use macros CHRE_MESSAGE_TO_HOST_MAX_SIZE
*/
void chreDebugDumpLog(const char *formatStr, ...) {
    char strBuffer[512];
    va_list args;
    va_start(args, formatStr);
    vsnprintf(strBuffer, 512, formatStr, args);
    va_end(args);
    chreDebugDumpLogWrapper("%s", strBuffer);
}


#ifdef __cplusplus
}
#endif