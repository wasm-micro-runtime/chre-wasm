#include <stddef.h>
#ifdef _CHRE_AUDIO_H_
/**
 * @note for struct struct chreAudioSource 
*/
static_assert(sizeof(struct chreAudioSource) == 28
              && offsetof(struct chreAudioSource, name) == 0
              && offsetof(struct chreAudioSource, sampleRate) == 4
              && offsetof(struct chreAudioSource, minBufferDuration) == 8
              && offsetof(struct chreAudioSource, maxBufferDuration) == 16
              && offsetof(struct chreAudioSource, format) == 24);

/**
 * @note for struct struct chreAudioSourceStatus 
*/
static_assert(sizeof(struct chreAudioSourceStatus) == 2
              && offsetof(struct chreAudioSourceStatus, enabled) == 0
              && offsetof(struct chreAudioSourceStatus, suspended) == 1);

/**
 * @note for struct struct chreAudioSourceStatusEvent 
*/
static_assert(sizeof(struct chreAudioSourceStatusEvent) == 8
              && offsetof(struct chreAudioSourceStatusEvent, handle) == 0
              && offsetof(struct chreAudioSourceStatusEvent, status) == 4);

/**
 * @note for struct struct chreAudioDataEvent 
*/
static_assert(sizeof(struct chreAudioDataEvent) == 32
              && offsetof(struct chreAudioDataEvent, version) == 0
              && offsetof(struct chreAudioDataEvent, reserved) == 1
              && offsetof(struct chreAudioDataEvent, handle) == 4
              && offsetof(struct chreAudioDataEvent, timestamp) == 8
              && offsetof(struct chreAudioDataEvent, sampleRate) == 16
              && offsetof(struct chreAudioDataEvent, sampleCount) == 20
              && offsetof(struct chreAudioDataEvent, format) == 24
              && offsetof(struct chreAudioDataEvent, samplesULaw8) == 28);
#endif
