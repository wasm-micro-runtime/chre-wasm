#ifdef _CHRE_WIFI_H_
#include<stddef.h>

/**
 * @note for struct chreWifiSsidListItem
*/
static_assert(sizeof(struct chreWifiSsidListItem) == 1 + CHRE_WIFI_SSID_MAX_LEN
              && offsetof(struct chreWifiSsidListItem, ssidLen) == 0
              && offsetof(struct chreWifiSsidListItem, ssid[0]) == 1);

/**
 * @note for struct chreWifiScanParams
*/
static_assert(sizeof(struct chreWifiScanParams) == 28
              && offsetof(struct chreWifiScanParams, scanType) == 0
              && offsetof(struct chreWifiScanParams, maxScanAgeMs) == 4
              && offsetof(struct chreWifiScanParams, frequencyListLen) == 8
              && offsetof(struct chreWifiScanParams, frequencyList) == 12
              && offsetof(struct chreWifiScanParams, ssidListLen) == 16
              && offsetof(struct chreWifiScanParams, ssidList) == 20
              && offsetof(struct chreWifiScanParams, radioChainPref) == 24
              && offsetof(struct chreWifiScanParams, channelSet) == 25);

/**
 * @note for struct chreWifiScanResult
*/
static_assert(sizeof(struct chreWifiScanResult) == 34 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, ageMs) == 0
              && offsetof(struct chreWifiScanResult, capabilityInfo) == 4
              && offsetof(struct chreWifiScanResult, ssidLen) == 6
              && offsetof(struct chreWifiScanResult, ssid[0]) == 7
              && offsetof(struct chreWifiScanResult, bssid) == 7 + CHRE_WIFI_SSID_MAX_LEN
              && offsetof(struct chreWifiScanResult, flags) == 7 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, rssi) == 8 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, band) == 9 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, primaryChannel) == 10 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, centerFreqPrimary) == 14 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, centerFreqSecondary) == 18 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, channelWidth) == 22 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, securityMode) == 23 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, radioChain) == 24 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, rssiChain0) == 25 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, rssiChain1) == 26 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiScanResult, reserved[0]) == 27 + CHRE_WIFI_SSID_MAX_LEN + CHRE_WIFI_BSSID_LEN);

/**
 * @note for struct chreWifiScanResult
*/
static_assert(sizeof(struct chreWifiScanEvent) == 28
              && offsetof(struct chreWifiScanEvent, version) == 0
              && offsetof(struct chreWifiScanEvent, resultCount) == 1
              && offsetof(struct chreWifiScanEvent, resultTotal) == 2
              && offsetof(struct chreWifiScanEvent, eventIndex) == 3
              && offsetof(struct chreWifiScanEvent, scanType) == 4
              && offsetof(struct chreWifiScanEvent, ssidSetSize) == 5
              && offsetof(struct chreWifiScanEvent, scannedFreqListLen) == 6
              && offsetof(struct chreWifiScanEvent, referenceTime) == 8
              && offsetof(struct chreWifiScanEvent, scannedFreqList) == 16
              && offsetof(struct chreWifiScanEvent, results) == 20
              && offsetof(struct chreWifiScanEvent, radioChainPref) == 24);

/**
 * @note for struct chreWifiRangingTarget
*/
static_assert(sizeof(struct chreWifiRangingTarget) == 24
              && offsetof(struct chreWifiRangingTarget, macAddress[0]) == 0
              && offsetof(struct chreWifiRangingTarget, primaryChannel) == 2 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingTarget, centerFreqPrimary) == 6 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingTarget, centerFreqSecondary) == 10 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingTarget, channelWidth) == 14 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingTarget, reserved[0]) == 15 + CHRE_WIFI_BSSID_LEN);

/**
 * @note for struct chreWifiRangingParams
*/
static_assert(sizeof(struct chreWifiRangingParams) == 8
              && offsetof(struct chreWifiRangingParams, targetListLen) == 0
              && offsetof(struct chreWifiRangingParams, targetList) == 4);

/**
 * @note for struct chreWifiRangingResult
*/
static_assert(sizeof(struct chreWifiRangingResult) == 56
              && offsetof(struct chreWifiRangingResult, timestamp) == 0
              && offsetof(struct chreWifiRangingResult, macAddress[0]) == 8
              && offsetof(struct chreWifiRangingResult, status) == 8 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, rssi) == 9 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, distance) == 10 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, distanceStdDev) == 14 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.latitude) == 18 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.longitude) == 26 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.altitude) == 34 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.latitudeUncertainty) == 38 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.longitudeUncertainty) == 39 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.altitudeType) == 40 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, lci.altitudeUncertainty) == 41 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, flags) == 42 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiRangingResult, reserved[0]) == 43 + CHRE_WIFI_BSSID_LEN);

/**
 * @note for struct chreWifiRangingEvent
*/
static_assert(sizeof(struct chreWifiRangingEvent) == 8
              && offsetof(struct chreWifiRangingEvent, version) == 0
              && offsetof(struct chreWifiRangingEvent, resultCount) == 1
              && offsetof(struct chreWifiRangingEvent, reserved[0]) == 2
              && offsetof(struct chreWifiRangingEvent, results) == 4);

/**
 * @note for struct chreWifiNanCapabilities
*/
static_assert(sizeof(struct chreWifiNanCapabilities) == 12
              && offsetof(struct chreWifiNanCapabilities, maxMatchFilterLength) == 0
              && offsetof(struct chreWifiNanCapabilities, maxServiceSpecificInfoLength) == 4
              && offsetof(struct chreWifiNanCapabilities, maxServiceNameLength) == 8
              && offsetof(struct chreWifiNanCapabilities, reserved[0]) == 9);

/**
 * @note for struct chreWifiNanIdentifierEvent
*/
static_assert(sizeof(struct chreWifiNanIdentifierEvent) == 12
              && offsetof(struct chreWifiNanIdentifierEvent, id) == 0
              && offsetof(struct chreWifiNanIdentifierEvent, result) == 4);

/**
 * @note for struct chreWifiNanRangingParams
*/
static_assert(sizeof(struct chreWifiNanRangingParams) == CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiNanRangingParams, macAddress[0]) == 0);


/**
 * @note for struct chreWifiNanSubscribeConfig
*/
static_assert(sizeof(struct chreWifiNanSubscribeConfig) == 24
              && offsetof(struct chreWifiNanSubscribeConfig, subscribeType) == 0
              && offsetof(struct chreWifiNanSubscribeConfig, service) == 4
              && offsetof(struct chreWifiNanSubscribeConfig, serviceSpecificInfo) == 8
              && offsetof(struct chreWifiNanSubscribeConfig, serviceSpecificInfoSize) == 12
              && offsetof(struct chreWifiNanSubscribeConfig, matchFilter) == 16
              && offsetof(struct chreWifiNanSubscribeConfig, matchFilterLength) == 20);

/**
 * @note for struct chreWifiNanDiscoveryEvent
*/
static_assert(sizeof(struct chreWifiNanDiscoveryEvent) == 18 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiNanDiscoveryEvent, subscribeId) == 0
              && offsetof(struct chreWifiNanDiscoveryEvent, publishId) == 4
              && offsetof(struct chreWifiNanDiscoveryEvent, publisherAddress) == 8
              && offsetof(struct chreWifiNanDiscoveryEvent, serviceSpecificInfo) == 10 + CHRE_WIFI_BSSID_LEN
              && offsetof(struct chreWifiNanDiscoveryEvent, serviceSpecificInfoSize) == 14 + CHRE_WIFI_BSSID_LEN);

/**
 * @note for struct chreWifiNanSessionLostEvent
*/
static_assert(sizeof(struct chreWifiNanSessionLostEvent) == 8
              && offsetof(struct chreWifiNanSessionLostEvent, id) == 0
              && offsetof(struct chreWifiNanSessionLostEvent, peerId) == 4);

/**
 * @note for struct chreWifiNanSessionTerminatedEvent
*/
static_assert(sizeof(struct chreWifiNanSessionTerminatedEvent) == 8
              && offsetof(struct chreWifiNanSessionTerminatedEvent, id) == 0
              && offsetof(struct chreWifiNanSessionTerminatedEvent, reason) == 4
              && offsetof(struct chreWifiNanSessionTerminatedEvent, reserved[0]) == 5);

#endif