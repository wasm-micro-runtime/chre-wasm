/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <chre.h>
#include <cinttypes>

#include "chre/util/macros.h"
#include "chre/util/nanoapp/log.h"
#include "chre/util/time.h"

#define LOG_TAG "[WwanWorld]"

#ifdef CHRE_NANOAPP_INTERNAL
namespace chre {
namespace {
#endif  // CHRE_NANOAPP_INTERNAL
using chre::Nanoseconds;
using chre::Seconds;
//! A fake/unused cookie to pass into the cell info request.
const uint32_t kCellInfoCookie = 0x1337;

//! The interval for cell info requests.
const Nanoseconds kCellInfoInterval = Nanoseconds(Seconds(10));

//! A handle for  the cyclic timer to request periodic cell info.
uint32_t gCellInfoTimerHandle;

namespace {

/**
 * Handles a timer event.
 *
 * @param eventData The cookie passed to the timer request.
 */
void handleTimerEvent(const void *eventData) {
  const uint32_t *timerHandle = static_cast<const uint32_t *>(eventData);
  if (*timerHandle == gCellInfoTimerHandle) {
    if (chreWwanGetCellInfoAsync(&kCellInfoCookie)) {
      LOGI("Requested cell info successfully");
    } else {
      LOGE("Failed to request cell info");
    }
  } else {
    LOGE("Received invalid timer handle");
  }
}

void logNrCellInfo(const chreWwanCellInfoNr &nr) {
  LOGI("  NR cell detected");
  LOGI("    mcc %" PRId32, nr.cellIdentityNr.mcc);
  LOGI("    mnc %" PRId32, nr.cellIdentityNr.mnc);
  LOGI("    nci %" PRId64, chreWwanUnpackNrNci(&nr.cellIdentityNr));
  LOGI("    pci %" PRId32, nr.cellIdentityNr.pci);
  LOGI("    tac %" PRId32, nr.cellIdentityNr.tac);
  LOGI("    nrarfcn %" PRId32, nr.cellIdentityNr.nrarfcn);
  LOGI("    ssRsrp %" PRId32 ", %" PRId32 " dBm", nr.signalStrengthNr.ssRsrp,
       -1 * nr.signalStrengthNr.ssRsrp);
  LOGI("    ssRsrq %" PRId32 ", %.1f dB", nr.signalStrengthNr.ssRsrq,
       static_cast<float>(nr.signalStrengthNr.ssRsrp) / 2.0f);
  LOGI("    ssSinr %" PRId32 ", %.1f dB", nr.signalStrengthNr.ssSinr,
       static_cast<float>(nr.signalStrengthNr.ssSinr) / 2.0f);
  LOGI("    csiRsrp %" PRId32 ", %" PRId32 " dBm", nr.signalStrengthNr.csiRsrp,
       -1 * nr.signalStrengthNr.csiRsrp);
  LOGI("    csiRsrq %" PRId32 ", %.1f dB", nr.signalStrengthNr.csiRsrq,
       static_cast<float>(nr.signalStrengthNr.csiRsrp) / 2.0f);
  LOGI("    csiSinr %" PRId32 ", %.1f dB", nr.signalStrengthNr.csiSinr,
       static_cast<float>(nr.signalStrengthNr.csiSinr) / 2.0f);
}

/**
 * Logs a CHRE WWAN cell info result.
 *
 * @param cell the cell info to log.
 */
void logChreWwanInfo(const chreWwanCellInfo *cell) {
  LOGI("Found cell at time %" PRIu64, cell->timeStamp);
  LOGI("  timestamp type %" PRIu8, cell->timeStampType);
  LOGI("  registered %" PRIu8, cell->registered);

  switch (cell->cellInfoType) {
    case CHRE_WWAN_CELL_INFO_TYPE_GSM:
      LOGI("  GSM cell detected");
      LOGI("    mcc %" PRId32, cell->CellInfo.gsm.cellIdentityGsm.mcc);
      LOGI("    mnc %" PRId32, cell->CellInfo.gsm.cellIdentityGsm.mnc);
      LOGI("    lac %" PRId32, cell->CellInfo.gsm.cellIdentityGsm.lac);
      LOGI("    cid %" PRId32, cell->CellInfo.gsm.cellIdentityGsm.cid);
      LOGI("    arfcn %" PRId32, cell->CellInfo.gsm.cellIdentityGsm.arfcn);
      LOGI("    bsic %" PRIu8, cell->CellInfo.gsm.cellIdentityGsm.bsic);
      break;
    case CHRE_WWAN_CELL_INFO_TYPE_CDMA:
      LOGW("  CDMA unsupported");
      break;
    case CHRE_WWAN_CELL_INFO_TYPE_LTE:
      LOGI("  LTE cell detected");
      LOGI("    mcc %" PRId32, cell->CellInfo.lte.cellIdentityLte.mcc);
      LOGI("    mnc %" PRId32, cell->CellInfo.lte.cellIdentityLte.mnc);
      LOGI("    ci %" PRId32, cell->CellInfo.lte.cellIdentityLte.ci);
      LOGI("    pci %" PRId32, cell->CellInfo.lte.cellIdentityLte.pci);
      LOGI("    tac %" PRId32, cell->CellInfo.lte.cellIdentityLte.tac);
      LOGI("    earfcn %" PRId32, cell->CellInfo.lte.cellIdentityLte.earfcn);
      break;
    case CHRE_WWAN_CELL_INFO_TYPE_WCDMA:
      LOGI("  WCDMA cell detected");
      LOGI("    mcc %" PRId32, cell->CellInfo.wcdma.cellIdentityWcdma.mcc);
      LOGI("    mnc %" PRId32, cell->CellInfo.wcdma.cellIdentityWcdma.mnc);
      LOGI("    lac %" PRId32, cell->CellInfo.wcdma.cellIdentityWcdma.lac);
      LOGI("    cid %" PRId32, cell->CellInfo.wcdma.cellIdentityWcdma.cid);
      LOGI("    psc %" PRId32, cell->CellInfo.wcdma.cellIdentityWcdma.psc);
      LOGI("    uarfcn %" PRId32,
           cell->CellInfo.wcdma.cellIdentityWcdma.uarfcn);
      break;
    case CHRE_WWAN_CELL_INFO_TYPE_TD_SCDMA:
      LOGW("  TD-SCDMA unsupported");
      break;
    case CHRE_WWAN_CELL_INFO_TYPE_NR:
      logNrCellInfo(cell->CellInfo.nr);
      break;
    default:
      LOGE("  invalid cell info type %" PRIu8, cell->cellInfoType);
      break;
  };
}

/**
 * Handles a WWAN cell info result.
 *
 * @param result a WWAN cell info result.
 */
void handleCellInfoResult(const chreWwanCellInfoResult *result) {
  if (result->errorCode != CHRE_ERROR_NONE) {
    LOGE("Failed to request WWAN cell info with %" PRIu8, result->errorCode);
  } else {
    LOGD("Received %" PRIu8 " cell info results with version %" PRIu8,
         result->cellInfoCount, result->version);

    for (uint8_t i = 0; i < result->cellInfoCount; i++) {
      logChreWwanInfo(&result->cells[i]);
    }
  }
}

}  // namespace

bool nanoappStart() {
  LOGI("App started as instance %" PRIu32, chreGetInstanceId());

  const char *wwanCapabilitiesStr;
  uint32_t wwanCapabilities = chreWwanGetCapabilities();
  switch (wwanCapabilities) {
    case CHRE_WWAN_GET_CELL_INFO:
      wwanCapabilitiesStr = "GET_CELL_INFO";
      break;
    case CHRE_WWAN_CAPABILITIES_NONE:
      wwanCapabilitiesStr = "NONE";
      break;
    default:
      wwanCapabilitiesStr = "INVALID";
  }

  LOGI("Detected WWAN support as: %s (%" PRIu32 ")", wwanCapabilitiesStr,
       wwanCapabilities);

  if (wwanCapabilities & CHRE_WWAN_GET_CELL_INFO) {
    gCellInfoTimerHandle =
        chreTimerSet(kCellInfoInterval.toRawNanoseconds(),
                     &gCellInfoTimerHandle /* data */, false /* oneShot */);
    if (gCellInfoTimerHandle == CHRE_TIMER_INVALID) {
      LOGE("Failed to set a periodic cell info timer");
    } else {
      LOGI("Set a timer to request periodic cell info");
    }
  }

  return true;
}

void nanoappHandleEvent(uint32_t senderInstanceId, uint16_t eventType,
                        const void *eventData) {
  UNUSED_VAR(senderInstanceId);

  switch (eventType) {
    case CHRE_EVENT_TIMER:
      handleTimerEvent(eventData);
      break;
    case CHRE_EVENT_WWAN_CELL_INFO_RESULT:
      handleCellInfoResult(
          static_cast<const chreWwanCellInfoResult *>(eventData));
      break;
    default:
      LOGW("Unhandled event type %" PRIu16, eventType);
  }
}

void nanoappEnd() {
  LOGI("Stopped");
}

#ifdef CHRE_NANOAPP_INTERNAL
}  // anonymous namespace
}  // namespace chre

#include "chre/platform/static_nanoapp_init.h"
#include "chre/util/nanoapp/app_id.h"
#include "chre/util/system/napp_permissions.h"

CHRE_STATIC_NANOAPP_INIT(WwanWorld, chre::kWwanWorldAppId, 0,
                         chre::NanoappPermissions::CHRE_PERMS_WWAN);
#endif  // CHRE_NANOAPP_INTERNAL
