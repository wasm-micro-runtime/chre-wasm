#include <stddef.h>
#ifdef _CHRE_GNSS_H_
/**
 * @note for struct chreGnssClock
*/
static_assert(sizeof(struct chreGnssClock) == 40
              && offsetof(struct chreGnssClock, time_ns) == 0
              && offsetof(struct chreGnssClock, full_bias_ns) == 8
              && offsetof(struct chreGnssClock, bias_ns) == 16
              && offsetof(struct chreGnssClock, drift_nsps) == 20
              && offsetof(struct chreGnssClock, bias_uncertainty_ns) == 24
              && offsetof(struct chreGnssClock, drift_uncertainty_nsps) == 28
              && offsetof(struct chreGnssClock, hw_clock_discontinuity_count) == 32
              && offsetof(struct chreGnssClock, flags) == 36
              && offsetof(struct chreGnssClock, reserved) == 38);

/**
 * @note for struct chreGnssMeasurement
*/
static_assert(sizeof(struct chreGnssMeasurement) == 64
              && offsetof(struct chreGnssMeasurement, time_offset_ns) == 0
              && offsetof(struct chreGnssMeasurement, accumulated_delta_range_um) == 8
              && offsetof(struct chreGnssMeasurement, received_sv_time_in_ns) == 16
              && offsetof(struct chreGnssMeasurement, received_sv_time_uncertainty_in_ns) == 24
              && offsetof(struct chreGnssMeasurement, pseudorange_rate_mps) == 32
              && offsetof(struct chreGnssMeasurement, pseudorange_rate_uncertainty_mps) == 36
              && offsetof(struct chreGnssMeasurement, accumulated_delta_range_uncertainty_m) == 40
              && offsetof(struct chreGnssMeasurement, c_n0_dbhz) == 44
              && offsetof(struct chreGnssMeasurement, snr_db) == 48
              && offsetof(struct chreGnssMeasurement, state) == 52
              && offsetof(struct chreGnssMeasurement, accumulated_delta_range_state) == 54
              && offsetof(struct chreGnssMeasurement, svid) == 56
              && offsetof(struct chreGnssMeasurement, constellation) == 58
              && offsetof(struct chreGnssMeasurement, multipath_indicator) == 59
              && offsetof(struct chreGnssMeasurement, carrier_frequency_hz) == 60);

/**
 * @note for struct chreGnssDataEvent
*/
static_assert(sizeof(struct chreGnssDataEvent) == 52
              && offsetof(struct chreGnssDataEvent, version) == 0
              && offsetof(struct chreGnssDataEvent, measurement_count) == 1
              && offsetof(struct chreGnssDataEvent, reserved) == 2
              && offsetof(struct chreGnssDataEvent, clock) == 8
              && offsetof(struct chreGnssDataEvent, measurements) == 48);

/**
 * @note for struct chreGnssLocationEvent
*/
static_assert(sizeof(struct chreGnssLocationEvent) == 48
              && offsetof(struct chreGnssLocationEvent, timestamp) == 0
              && offsetof(struct chreGnssLocationEvent, latitude_deg_e7) == 8
              && offsetof(struct chreGnssLocationEvent, longitude_deg_e7) == 12
              && offsetof(struct chreGnssLocationEvent, altitude) == 16
              && offsetof(struct chreGnssLocationEvent, speed) == 20
              && offsetof(struct chreGnssLocationEvent, bearing) == 24
              && offsetof(struct chreGnssLocationEvent, accuracy) == 28
              && offsetof(struct chreGnssLocationEvent, flags) == 32
              && offsetof(struct chreGnssLocationEvent, reserved) == 34
              && offsetof(struct chreGnssLocationEvent, altitude_accuracy) == 36
              && offsetof(struct chreGnssLocationEvent, speed_accuracy) == 40
              && offsetof(struct chreGnssLocationEvent, bearing_accuracy) == 44);
#endif