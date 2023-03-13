#ifndef _AUDIO_WRAPPER_H_
#define _AUDIO_WRAPPER_H_

#include "chre/audio.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"
#ifdef __cplusplus
extern "C" {
#endif

//! struct chreAudioSourceStatusEvent begin

CONVERSION_FUNCTIONS_DECLARATION(chreAudioSourceStatusEvent);

//! struct chreAudioDataEvent begin
CONVERSION_FUNCTIONS_DECLARATION(chreAudioDataEvent);

/* Wrappers of CHRE APIs */

//problem: const char* in chreAudioSource
//! This is a function wrapper for chreAudioGetSource
//! @see function chreAudioGetSource in chre/audio.h
bool chreAudioGetSourceWrapper(wasm_exec_env_t exec_env, 
                    uint32_t handle, chreAudioSource *audioSource);

//! This is a function wrapper for chreAudioConfigureSource
//! @see function chreAudioConfigureSource in chre/audio.h
bool chreAudioConfigureSourceWrapper(wasm_exec_env_t exec_env,
                                     uint32_t handle, bool enable,
                                     uint64_t bufferDuration,
                                     uint64_t deliveryInterval);

//! This is a function wrapper for chreAudioGetStatus
//! @see function chreAudioGetStatus in chre/audio.h
bool chreAudioGetStatusWrapper(wasm_exec_env_t exec_env, uint32_t handle,
                               chreAudioSourceStatus *status);

#ifdef __cplusplus
}
#endif

#endif