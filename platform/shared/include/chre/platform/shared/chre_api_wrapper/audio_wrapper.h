#include "chre/audio.h"
#include "stddef.h"
#include "wasm_export.h"

#ifndef _AUDIO_WRAPPER_H_
#define _AUDIO_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Structures */

//! This is a structure wrapper for struct chreAudioSource in Wasm
//! @see struct chreAudioSource
typedef struct chreAudioSourceWrapper {
  //! const char *name;
  uint32_t namePointer; // 4 bytes

  uint32_t sampleRate; // 4 bytes

  uint64_t minBufferDuration; // 8 bytes

  uint64_t maxBufferDuration; // 8 bytes

  uint8_t format; // 1 bytes
  uint8_t _padding_0[7]; //7 bytes
}chreAudioSourceWrapper;
static_assert(sizeof(chreAudioSourceWrapper) == 32
              && offsetof(chreAudioSourceWrapper, namePointer) == 0
              && offsetof(chreAudioSourceWrapper, sampleRate) == 4
              && offsetof(chreAudioSourceWrapper, minBufferDuration) == 8
              && offsetof(chreAudioSourceWrapper, maxBufferDuration) == 16
              && offsetof(chreAudioSourceWrapper, format) == 24);

//! This is a structure wrapper for struct chreAudioSourceStatus in Wasm
//! @see struct chreAudioSourceStatus
typedef chreAudioSourceStatus chreAudioSourceStatusWrapper;
static_assert(sizeof(chreAudioSourceStatusWrapper) == 2
              && offsetof(chreAudioSourceStatusWrapper, enabled) == 0
              && offsetof(chreAudioSourceStatusWrapper, suspended) == 1);

//! This is a structure wrapper for struct chreAudioSourceStatusEvent in Wasm
//! The nanoappHandleEvent argument for CHRE_EVENT_AUDIO_SAMPLING_CHANGE in Wasm
//! @see struct chreAudioSourceStatusEvent
typedef struct chreAudioSourceStatusEventWrapper {
  uint32_t handle; // 4 bytes

  chreAudioSourceStatusWrapper status; // 2 bytes

  uint8_t _padding_0[2]; // 2 bytes
}chreAudioSourceStatusEventWrapper;
static_assert(sizeof(chreAudioSourceStatusEventWrapper) == 8
              && offsetof(chreAudioSourceStatusEvent, handle) == 0
              && offsetof(chreAudioSourceStatusEvent, status) == 4);

//! struct chreAudioSourceStatusEvent begin
/**
 * Apply memory for struct chreAudioSourceStatusEventWrapper (in Wasm), read data from 
 * struct chreAudioSourceStatusEvent (in native) and copy it to
 * struct chreAudioSourceStatusEventWrapper. This allows Wasm nanoapp to access the
 * corresponding data
 * 
 * @param WasmModuleInst
 * The pointer to a Wasm nanoapp instance can be used to manage memory in Wasm nanoapp
 * and get Wasm function pointers from Wasm nanoapp. This function will apply for memory
 * from this instance to generate a structure in Wasm world.
 * @param eventData
 * The pointer to the data which will be copied.
 * @return A value representing the memory address in WASM world. it can be used directly
 * in native world, and need to be converted to native address by using WAMR API.  
*/
uint32_t chreAudioSourceStatusEventWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreAudioSourceStatusEvent *eventData);


chreAudioSourceStatusEvent *chreAudioSourceStatusEventCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreAudioSourceStatusEventWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreAudioSourceStatusEventRelease(chreAudioSourceStatusEvent *eventData);


//! This is a structure wrapper for struct chreAudioDataEvent in Wasm
//! The nanoappHandleEvent argument for CHRE_EVENT_AUDIO_DATA in Wasm
//! @see struct chreAudioDataEvent
typedef struct chreAudioDataEventWrapper {
  uint8_t version;  //1 byte

  uint8_t reserved[3];  //3 bytes

  uint32_t handle;  //4 bytes

  uint64_t timestamp;   //8 bytes

  uint32_t sampleRate;  //4 bytes

  uint32_t sampleCount; //4 bytes

  uint8_t format;   //1 bytes
  uint8_t _padding_0[3]; //3 bytes
  union {
    //！ const uint8_t *samplesULaw8;
    uint32_t samplesULaw8Poiner;
    //！ const int16_t *samplesS16;
    uint32_t samplesS16Pointer;
  }; //4 bytes
}chreAudioDataEventWrapper;
static_assert(sizeof(chreAudioDataEventWrapper) == 32
              && offsetof(chreAudioDataEventWrapper, version) == 0
              && offsetof(chreAudioDataEventWrapper, reserved) == 1
              && offsetof(chreAudioDataEventWrapper, handle) == 4
              && offsetof(chreAudioDataEventWrapper, timestamp) == 8
              && offsetof(chreAudioDataEventWrapper, sampleRate) == 16
              && offsetof(chreAudioDataEventWrapper, sampleCount) == 20
              && offsetof(chreAudioDataEventWrapper, format) == 24
              && offsetof(chreAudioDataEventWrapper, samplesULaw8Poiner) == 28);

//! struct chreAudioDataEvent begin
uint32_t chreAudioDataEventWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreAudioDataEvent *eventData);
chreAudioDataEvent *chreAudioDataEventCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM);

void chreAudioDataEventWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM);

void chreAudioDataEventRelease(chreAudioDataEvent *eventData);

/* Wrappers of CHRE APIs */

//problem: const char* in chreAudioSource
//! This is a function wrapper for chreAudioGetSource
//! @see function chreAudioGetSource in chre/audio.h
bool chreAudioGetSourceWrapper(wasm_exec_env_t exec_env, 
                    uint32_t handle, chreAudioSourceWrapper *audioSource);

//! This is a function wrapper for chreAudioConfigureSource
//! @see function chreAudioConfigureSource in chre/audio.h
bool chreAudioConfigureSourceWrapper(wasm_exec_env_t exec_env,
                                     uint32_t handle, bool enable,
                                     uint64_t bufferDuration,
                                     uint64_t deliveryInterval);

//! This is a function wrapper for chreAudioGetStatus
//! @see function chreAudioGetStatus in chre/audio.h
bool chreAudioGetStatusWrapper(wasm_exec_env_t exec_env, uint32_t handle,
                               chreAudioSourceStatusWrapper *status);

#ifdef __cplusplus
}
#endif

#endif