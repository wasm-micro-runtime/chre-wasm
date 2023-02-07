#include "chre/ble.h"
#include "stddef.h"
#include "wasm_export.h"

#ifndef _BLE_WRAPPER_H_
#define _BLE_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Structures */
/** 
 * @see struct chreBleGenericFilter in chre/ble.h
*/
typedef chreBleGenericFilter chreBleGenericFilterWrapper;
static_assert(sizeof(chreBleGenericFilter) == 2 + CHRE_BLE_DATA_LEN_MAX + CHRE_BLE_DATA_LEN_MAX
              && offsetof(chreBleGenericFilter, type) == 0
              && offsetof(chreBleGenericFilter, len) == 1
              && offsetof(chreBleGenericFilter, data) == 2
              && offsetof(chreBleGenericFilter, dataMask) == 2 + CHRE_BLE_DATA_LEN_MAX);

/**
 * @see struct chreBleScanFilter in chre/ble.h
*/
typedef struct chreBleScanFilterWrapper {
  //! RSSI threshold filter (Corresponding HCI OCF: 0x0157, Sub: 0x01), where
  //! advertisements with RSSI values below this threshold may be disregarded.
  //! An rssiThreshold value of CHRE_BLE_RSSI_THRESHOLD_NONE indicates no RSSI
  //! filtering.
  int8_t rssiThreshold;

  //! Number of generic scan filters provided in the scanFilters array.
  //! A scanFilterCount value of 0 indicates no generic scan filters.
  uint8_t scanFilterCount;

  //! Pointer to an array of scan filters. If the array contains more than one
  //! entry, advertisements matching any of the entries will be returned
  //! (functional OR).
  //!   const struct chreBleGenericFilter *scanFilters;
  uint32_t scanFiltersPointer;
}chreBleScanFilterWrapper;

static_assert(sizeof(chreBleScanFilterWrapper) == 8
              && offsetof(chreBleScanFilterWrapper, rssiThreshold) == 0
              && offsetof(chreBleScanFilterWrapper, scanFilterCount) == 1
              && offsetof(chreBleScanFilterWrapper, scanFiltersPointer) == 4);

/**
 * @see struct chreBleAdvertisingReport in chre/ble.h
*/
typedef struct chreBleAdvertisingReportWrapper {
  //! The base timestamp, in nanoseconds, in the same time base as chreGetTime()
  uint64_t timestamp;

  //! @see CHRE_BLE_EVENT
  uint8_t eventTypeAndDataStatus;

  //! Advertising address type as defined in enum chreBleAddressType
  uint8_t addressType;

  //! Advertising device address
  uint8_t address[CHRE_BLE_ADDRESS_LEN];

  //! Advertiser PHY on primary advertising physical channel, if supported, as
  //! defined in enum chreBlePhyType.
  uint8_t primaryPhy;

  //! Advertiser PHY on secondary advertising physical channel, if supported, as
  //! defined in enum chreBlePhyType.
  uint8_t secondaryPhy;

  //! Value of the Advertising SID subfield in the ADI field of the PDU among
  //! the range of [0, 0x0f].
  //! CHRE_BLE_ADI_NONE indicates no ADI field was provided.
  //! Other values are reserved.
  uint8_t advertisingSid;

  //! Transmit (Tx) power in dBm. Typical values are [-127, 20].
  //! CHRE_BLE_TX_POWER_NONE indicates Tx power not available.
  int8_t txPower;

  //! Interval of the periodic advertising in 1.25 ms intervals, i.e.
  //! time = periodicAdvertisingInterval * 1.25 ms
  //! 0 means no periodic advertising. Minimum value is otherwise 6 (7.5 ms).
  uint16_t periodicAdvertisingInterval;

  //! RSSI in dBm. Typical values are [-127, 20].
  //! CHRE_BLE_RSSI_NONE indicates RSSI is not available.
  int8_t rssi;

  //! Direct address type (i.e. only accept connection requests from a known
  //! peer device) as defined in enum chreBleAddressType.
  uint8_t directAddressType;

  //! Direct address (i.e. only accept connection requests from a known peer
  //! device).
  uint8_t directAddress[CHRE_BLE_ADDRESS_LEN];

  //! Length of data field. Acceptable range is [0, 31] for legacy and
  //! [0, 229] for extended advertisements.
  uint16_t dataLength;

  //! dataLength bytes of data, or null if dataLength is 0
  //! const uint8_t *data;
  uint32_t dataPointer;
  //! Reserved for future use; set to 0
  uint32_t reserved;
}chreBleAdvertisingReportWrapper;
static_assert(sizeof(chreBleAdvertisingReportWrapper) == 40
              && offsetof(chreBleAdvertisingReportWrapper, timestamp) == 0
              && offsetof(chreBleAdvertisingReportWrapper, eventTypeAndDataStatus) == 8
              && offsetof(chreBleAdvertisingReportWrapper, addressType) == 9
              && offsetof(chreBleAdvertisingReportWrapper, address) == 10
              && offsetof(chreBleAdvertisingReportWrapper, primaryPhy) == 10 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, secondaryPhy) == 11 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, advertisingSid) == 12 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, txPower) == 13 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, periodicAdvertisingInterval) == 14 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, rssi) == 16 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, directAddressType) == 17 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, directAddress) == 18 +  CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, dataLength) == 18 + 2 * CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, dataPointer) == 20 + 2 * CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReportWrapper, reserved) == 24 + 2 * CHRE_BLE_ADDRESS_LEN);

/**nanoappHandleEvent argument: CHRE_EVENT_BLE_ADVERTISEMENT
 * @see struct chreBleAdvertisementEvent in chre/ble.h
*/
typedef struct chreBleAdvertisementEventWrapper {
  //! Reserved for future use; set to 0
  uint16_t reserved;

  //! Number of advertising reports in this event
  uint16_t numReports;

  //! Array of length numReports
  // const struct chreBleAdvertisingReport *reports;
  uint32_t reportsPointer;
}chreBleAdvertisementEventWrapper;
static_assert(sizeof(chreBleAdvertisementEventWrapper) == 8
              && offsetof(chreBleAdvertisementEventWrapper, reserved) == 0
              && offsetof(chreBleAdvertisementEventWrapper, numReports) == 2
              && offsetof(chreBleAdvertisementEventWrapper, reportsPointer) == 4);

//! struct chreBleAdvertisementEvent Begin
uint32_t chreBleAdvertisementEventWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreBleAdvertisementEvent *eventData);
chreBleAdvertisementEvent *chreBleAdvertisementEventCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreBleAdvertisementEventWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreBleAdvertisementEventRelease(chreBleAdvertisementEvent *eventData);

/**
 * CHRE API Wrapper
*/
uint32_t chreBleGetCapabilitiesWrapper(wasm_exec_env_t exec_env);

uint32_t chreBleGetFilterCapabilitiesWrapper(wasm_exec_env_t exec_env);

bool chreBleStartScanAsyncWrapper(wasm_exec_env_t exec_env, enum chreBleScanMode mode,
                                  uint32_t reportDelayMs, const chreBleScanFilterWrapper *filter);

bool chreBleStopScanAsyncWrapper(wasm_exec_env_t exec_env);

#ifdef __cplusplus
}
#endif
#endif