#include <stddef.h>
#ifdef CHRE_BLE_H_
/**
 * @note for struct struct chreBleGenericFilter 
*/
static_assert(sizeof(chreBleGenericFilter) == 2 + CHRE_BLE_DATA_LEN_MAX + CHRE_BLE_DATA_LEN_MAX
              && offsetof(chreBleGenericFilter, type) == 0
              && offsetof(chreBleGenericFilter, len) == 1
              && offsetof(chreBleGenericFilter, data) == 2
              && offsetof(chreBleGenericFilter, dataMask) == 2 + CHRE_BLE_DATA_LEN_MAX);

/**
 * @note for struct struct chreBleScanFilter 
*/
static_assert(sizeof(chreBleScanFilter) == 8
              && offsetof(chreBleScanFilter, rssiThreshold) == 0
              && offsetof(chreBleScanFilter, scanFilterCount) == 1
              && offsetof(chreBleScanFilter, scanFilters) == 4);

/**
 * @note for struct struct chreBleAdvertisingReport 
*/
static_assert(sizeof(chreBleAdvertisingReport) == 40
              && offsetof(chreBleAdvertisingReport, timestamp) == 0
              && offsetof(chreBleAdvertisingReport, eventTypeAndDataStatus) == 8
              && offsetof(chreBleAdvertisingReport, addressType) == 9
              && offsetof(chreBleAdvertisingReport, address) == 10
              && offsetof(chreBleAdvertisingReport, primaryPhy) == 10 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, secondaryPhy) == 11 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, advertisingSid) == 12 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, txPower) == 13 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, periodicAdvertisingInterval) == 14 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, rssi) == 16 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, directAddressType) == 17 + CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, directAddress) == 18 +  CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, dataLength) == 18 + 2 * CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, data) == 20 + 2 * CHRE_BLE_ADDRESS_LEN
              && offsetof(chreBleAdvertisingReport, reserved) == 24 + 2 * CHRE_BLE_ADDRESS_LEN);

/**
 * @note for struct struct chreBleAdvertisementEvent 
*/
static_assert(sizeof(chreBleAdvertisementEvent) == 8
              && offsetof(chreBleAdvertisementEvent, reserved) == 0
              && offsetof(chreBleAdvertisementEvent, numReports) == 2
              && offsetof(chreBleAdvertisementEvent, reports) == 4);
#endif