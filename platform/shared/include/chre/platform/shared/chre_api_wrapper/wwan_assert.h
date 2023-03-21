#ifdef _CHRE_WWAN_H_
#include <stddef.h>

/**
 * @see struct chreWwanCellIdentityGsm
*/
static_assert(sizeof(struct chreWwanCellIdentityGsm) == 24
              && offsetof(struct chreWwanCellIdentityGsm, mcc) == 0
              && offsetof(struct chreWwanCellIdentityGsm, mnc) == 4
              && offsetof(struct chreWwanCellIdentityGsm, lac) == 8
              && offsetof(struct chreWwanCellIdentityGsm, cid) == 12
              && offsetof(struct chreWwanCellIdentityGsm, arfcn) == 16
              && offsetof(struct chreWwanCellIdentityGsm, bsic) == 20
              && offsetof(struct chreWwanCellIdentityGsm, reserved[0]) == 21);

/**
 * @see struct chreWwanCellIdentityWcdma
*/
static_assert(sizeof(struct chreWwanCellIdentityWcdma) == 24
              && offsetof(struct chreWwanCellIdentityWcdma, mcc) == 0
              && offsetof(struct chreWwanCellIdentityWcdma, mnc) == 4
              && offsetof(struct chreWwanCellIdentityWcdma, lac) == 8
              && offsetof(struct chreWwanCellIdentityWcdma, cid) == 12
              && offsetof(struct chreWwanCellIdentityWcdma, psc) == 16
              && offsetof(struct chreWwanCellIdentityWcdma, uarfcn) == 20);

/**
 * @see struct chreWwanCellIdentityCdma
*/
static_assert(sizeof(struct chreWwanCellIdentityCdma) == 20
              && offsetof(struct chreWwanCellIdentityCdma, networkId) == 0
              && offsetof(struct chreWwanCellIdentityCdma, systemId) == 4
              && offsetof(struct chreWwanCellIdentityCdma, basestationId) == 8
              && offsetof(struct chreWwanCellIdentityCdma, longitude) == 12
              && offsetof(struct chreWwanCellIdentityCdma, latitude) == 16);

/**
 * @see struct chreWwanCellIdentityLte
*/
static_assert(sizeof(struct chreWwanCellIdentityLte) == 24
              && offsetof(struct chreWwanCellIdentityLte, mcc) == 0
              && offsetof(struct chreWwanCellIdentityLte, mnc) == 4
              && offsetof(struct chreWwanCellIdentityLte, ci) == 8
              && offsetof(struct chreWwanCellIdentityLte, pci) == 12
              && offsetof(struct chreWwanCellIdentityLte, tac) == 16
              && offsetof(struct chreWwanCellIdentityLte, earfcn) == 20);

/**
 * @see struct chreWwanCellIdentityTdscdma
*/
static_assert(sizeof(struct chreWwanCellIdentityTdscdma) == 20
              && offsetof(struct chreWwanCellIdentityTdscdma, mcc) == 0
              && offsetof(struct chreWwanCellIdentityTdscdma, mnc) == 4
              && offsetof(struct chreWwanCellIdentityTdscdma, lac) == 8
              && offsetof(struct chreWwanCellIdentityTdscdma, cid) == 12
              && offsetof(struct chreWwanCellIdentityTdscdma, cpid) == 16);

/**
 * @see struct chreWwanCellIdentityNr
*/
static_assert(sizeof(struct chreWwanCellIdentityNr) == 28
              && offsetof(struct chreWwanCellIdentityNr, mcc) == 0
              && offsetof(struct chreWwanCellIdentityNr, mnc) == 4
              && offsetof(struct chreWwanCellIdentityNr, nci0) == 8
              && offsetof(struct chreWwanCellIdentityNr, nci1) == 12
              && offsetof(struct chreWwanCellIdentityNr, pci) == 16
              && offsetof(struct chreWwanCellIdentityNr, tac) == 20
              && offsetof(struct chreWwanCellIdentityNr, nrarfcn) == 24);

/**
 * @see struct chreWwanSignalStrengthGsm
*/
static_assert(sizeof(struct chreWwanSignalStrengthGsm) == 12
              && offsetof(struct chreWwanSignalStrengthGsm, signalStrength) == 0
              && offsetof(struct chreWwanSignalStrengthGsm, bitErrorRate) == 4
              && offsetof(struct chreWwanSignalStrengthGsm, timingAdvance) == 8);

/**
 * @see struct chreWwanSignalStrengthWcdma
*/
static_assert(sizeof(struct chreWwanSignalStrengthWcdma) == 8
              && offsetof(struct chreWwanSignalStrengthWcdma, signalStrength) == 0
              && offsetof(struct chreWwanSignalStrengthWcdma, bitErrorRate) == 4);

/**
 * @see struct chreWwanSignalStrengthCdma
*/
static_assert(sizeof(struct chreWwanSignalStrengthCdma) == 8
              && offsetof(struct chreWwanSignalStrengthCdma, dbm) == 0
              && offsetof(struct chreWwanSignalStrengthCdma, ecio) == 4);

/**
 * @see struct chreWwanSignalStrengthEvdo
*/
static_assert(sizeof(struct chreWwanSignalStrengthEvdo) == 12
              && offsetof(struct chreWwanSignalStrengthEvdo, dbm) == 0
              && offsetof(struct chreWwanSignalStrengthEvdo, ecio) == 4
              && offsetof(struct chreWwanSignalStrengthEvdo, signalNoiseRatio) == 8);

/**
 * @see struct chreWwanSignalStrengthLte
*/
static_assert(sizeof(struct chreWwanSignalStrengthLte) == 24
              && offsetof(struct chreWwanSignalStrengthLte, signalStrength) == 0
              && offsetof(struct chreWwanSignalStrengthLte, rsrp) == 4
              && offsetof(struct chreWwanSignalStrengthLte, rsrq) == 8
              && offsetof(struct chreWwanSignalStrengthLte, rssnr) == 12
              && offsetof(struct chreWwanSignalStrengthLte, cqi) == 16
              && offsetof(struct chreWwanSignalStrengthLte, timingAdvance) == 20);

/**
 * @see struct chreWwanSignalStrengthTdscdma
*/
static_assert(sizeof(struct chreWwanSignalStrengthTdscdma) == 4
              && offsetof(struct chreWwanSignalStrengthTdscdma, rscp) == 0);

/**
 * @see struct chreWwanSignalStrengthNr
*/
static_assert(sizeof(struct chreWwanSignalStrengthNr) == 24
              && offsetof(struct chreWwanSignalStrengthNr, ssRsrp) == 0
              && offsetof(struct chreWwanSignalStrengthNr, ssRsrq) == 4
              && offsetof(struct chreWwanSignalStrengthNr, ssSinr) == 8
              && offsetof(struct chreWwanSignalStrengthNr, csiRsrp) == 12
              && offsetof(struct chreWwanSignalStrengthNr, csiRsrq) == 16
              && offsetof(struct chreWwanSignalStrengthNr, csiSinr) == 20);

/**
 * @see struct chreWwanCellInfoGsm
*/
static_assert(sizeof(struct chreWwanCellInfoGsm) == 36
              && offsetof(struct chreWwanCellInfoGsm, cellIdentityGsm) == 0
              && offsetof(struct chreWwanCellInfoGsm, signalStrengthGsm) == 24);

/**
 * @see struct chreWwanCellInfoWcdma
*/
static_assert(sizeof(struct chreWwanCellInfoWcdma) == 32
              && offsetof(struct chreWwanCellInfoWcdma, cellIdentityWcdma) == 0
              && offsetof(struct chreWwanCellInfoWcdma, signalStrengthWcdma) == 24);

/**
 * @see struct chreWwanCellInfoCdma
*/
static_assert(sizeof(struct chreWwanCellInfoCdma) == 40
              && offsetof(struct chreWwanCellInfoCdma, cellIdentityCdma) == 0
              && offsetof(struct chreWwanCellInfoCdma, signalStrengthCdma) == 20
              && offsetof(struct chreWwanCellInfoCdma, signalStrengthEvdo) == 28);

/**
 * @see struct chreWwanCellInfoLte
*/
static_assert(sizeof(struct chreWwanCellInfoLte) == 48
              && offsetof(struct chreWwanCellInfoLte, cellIdentityLte) == 0
              && offsetof(struct chreWwanCellInfoLte, signalStrengthLte) == 24);

/**
 * @see struct chreWwanCellInfoTdscdma
*/
static_assert(sizeof(struct chreWwanCellInfoTdscdma) == 24
              && offsetof(struct chreWwanCellInfoTdscdma, cellIdentityTdscdma) == 0
              && offsetof(struct chreWwanCellInfoTdscdma, signalStrengthTdscdma) == 20);


/**
 * @see struct chreWwanCellInfoNr
*/
static_assert(sizeof(struct chreWwanCellInfoNr) == 52
              && offsetof(struct chreWwanCellInfoNr, cellIdentityNr) == 0
              && offsetof(struct chreWwanCellInfoNr, signalStrengthNr) == 28);


/**
 * @see struct chreWwanCellInfo
*/
static_assert(sizeof(struct chreWwanCellInfo) == 64
              && offsetof(struct chreWwanCellInfo, timeStamp) == 0
              && offsetof(struct chreWwanCellInfo, cellInfoType) == 8
              && offsetof(struct chreWwanCellInfo, timeStampType) == 9
              && offsetof(struct chreWwanCellInfo, registered) == 10
              && offsetof(struct chreWwanCellInfo, reserved) == 11
              && offsetof(struct chreWwanCellInfo, CellInfo) == 12);

/**
 * @see struct chreWwanCellInfoResult
*/
static_assert(sizeof(struct chreWwanCellInfoResult) == 12
              && offsetof(struct chreWwanCellInfoResult, version) == 0
              && offsetof(struct chreWwanCellInfoResult, errorCode) == 1
              && offsetof(struct chreWwanCellInfoResult, cellInfoCount) == 2
              && offsetof(struct chreWwanCellInfoResult, reserved) == 3
              && offsetof(struct chreWwanCellInfoResult, cookie) == 4
              && offsetof(struct chreWwanCellInfoResult, cells) == 8);

#endif