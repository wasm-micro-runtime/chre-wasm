#include "chre/platform/shared/chre_api_wrapper/audio_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"
#ifdef __cplusplus
extern "C" {
#endif

//problem: const char* in chreAudioSource
bool chreAudioGetSourceWrapper(wasm_exec_env_t exec_env, uint32_t handle, 
                               struct chreAudioSourceWrapper *audioSource) {
    return false;
}


bool chreAudioConfigureSourceWrapper(wasm_exec_env_t exec_env,
                                     uint32_t handle, bool enable,
                                     uint64_t bufferDuration,
                                     uint64_t deliveryInterval) {
    return chreAudioConfigureSource(handle, enable, bufferDuration, deliveryInterval);
}
/**
 * The function chreAudioGetStatus has not been implemented in CHRE
 * @todo
*/
#if 0
bool chreAudioGetStatusWrapper(wasm_exec_env_t exec_env, uint32_t handle,
                               chreAudioSourceStatusWrapper *status){
    return chreAudioGetStatus(handle, static_cast<chreAudioSourceStatus*>(status));
}
#endif

uint32_t chreAudioSourceStatusEventWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreAudioSourceStatusEvent *eventData) {
    uint32_t offset = 0;
    chreAudioSourceStatusEventWrapper *data = NULL;
    offset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreAudioSourceStatusEventWrapper),
                                        reinterpret_cast<void**>(&data));
    if(0 != offset) {
        memcpy(data, reinterpret_cast<const chreAudioSourceStatusEventWrapper *>(eventData), 
               sizeof(chreAudioSourceStatusEventWrapper));
    } else {
        LOGE("Allocate memory for struct chreAudioSourceStatusEvent in Wasm failed!");
    }
    return offset;
}

chreAudioSourceStatusEvent *chreAudioSourceStatusEventCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                                     uint32_t eventDataForWASM) {
    chreAudioSourceStatusEventWrapper *structData = static_cast<chreAudioSourceStatusEventWrapper *>(
                                                    wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                                                    eventDataForWASM));
    chreAudioSourceStatusEvent *eventData = NULL;
    if (!structData) {
        LOGE("Try to copy memory not belong to the current Wasm instance!");
        goto fail;
    }
    eventData = reinterpret_cast<chreAudioSourceStatusEvent *>(chreHeapAlloc(sizeof(chreAudioSourceStatusEvent)));
    if (!eventData) {
        LOGE("Allocate memory for struct chreAudioSourceStatusEvent in Native failed!");
        goto fail;
    }
    memcpy(eventData, structData, sizeof(chreAudioSourceStatusEvent));
    return eventData;

fail:
    return nullptr;
}

void chreAudioSourceStatusEventWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                              uint32_t eventDataForWASM){
    if(eventDataForWASM)
        wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

void chreAudioSourceStatusEventRelease(chreAudioSourceStatusEvent *eventData){
    chreHeapFree(eventData);
}

//! struct chreAudioDataEvent begin
uint32_t chreAudioDataEventWrapperCopiedFromNative(wasm_module_inst_t WasmModuleInst,
                                                           const chreAudioDataEvent *eventData){
    uint32_t structOffset = 0;
    uint32_t samepleBuffer = 0;
    uint32_t samepleBufferLength = eventData->sampleCount;
    chreAudioDataEventWrapper *strcutData = NULL;
    uint8_t *samepleBufferInNative = NULL;

    //! Caculate the number of bytes used by the buffer
    //! If it is 16-bit sample, multiply the result by 2
    if (eventData->format == chreAudioDataFormat::CHRE_AUDIO_DATA_FORMAT_16_BIT_SIGNED_PCM) {
        samepleBufferLength<<=1;
    }
    if(!(structOffset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreAudioDataEventWrapper),
                                        reinterpret_cast<void**>(&strcutData)))){
        goto fail1;
    } else if(!(samepleBuffer = wasm_runtime_module_malloc(WasmModuleInst, samepleBufferLength,
                                               reinterpret_cast<void**>(&samepleBufferInNative)))) {
        goto fail2;
    }

    //! Copy the part of memory (before pointers occuring)
    memcpy(strcutData, reinterpret_cast<const chreAudioDataEventWrapper *>(eventData), 
            offsetof(chreAudioDataEventWrapper, _padding_0));
    //! Copy the sameple buffer
    memcpy(samepleBufferInNative, eventData->samplesULaw8, samepleBufferLength);
    //! Set the Wasm pointer to the structure from Wasm
    strcutData->samplesULaw8Poiner = samepleBuffer;

    return structOffset;
fail2:
    wasm_runtime_module_free(WasmModuleInst, structOffset);
fail1:
    LOGE("Allocate memory for struct chreAudioDataEvent in Wasm failed!");
    return 0;
}

chreAudioDataEvent *chreAudioDataEventCopiedFromWASM(wasm_module_inst_t WasmModuleInst,
                                                     uint32_t eventDataForWASM) {
    chreAudioDataEvent *eventData = nullptr;
    chreAudioDataEventWrapper *structData = NULL;
    uint8_t *bufferData = NULL;
    uint32_t bufferDataLength = 0;
    if(!(structData = static_cast<chreAudioDataEventWrapper *>(
                        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        LOGE("Try to copy memory not belong to the current Wasm instance!");
        goto fail1;
    }
    if(!(eventData = static_cast<chreAudioDataEvent*>(chreHeapAlloc(sizeof(chreAudioDataEvent))))) {
        LOGE("Allocate memory for struct chreAudioDataEvent in Native failed!");
        goto fail1;
    }
    bufferDataLength = structData->sampleCount;
    if (structData->format == chreAudioDataFormat::CHRE_AUDIO_DATA_FORMAT_16_BIT_SIGNED_PCM) {
        bufferDataLength <<= 1;
    }
    if (!(bufferData = static_cast<uint8_t*>(chreHeapAlloc(bufferDataLength)))) {
        LOGE("Allocate memory for samplesULaw8 of struct chreAudioDataEvent in Native failed!")
        goto fail2;
    }
    //! Copy the part of data before the pointer member
    memcpy(eventData, structData, offsetof(chreAudioDataEventWrapper, _padding_0));
    //! Saved the pointer
    eventData->samplesULaw8 = bufferData;
fail2:
    chreHeapFree(eventData);
fail1:
    return nullptr;
}

void chreAudioDataEventWrapperRelease(wasm_module_inst_t WasmModuleInst,
                                      uint32_t eventDataForWASM) {
    chreAudioDataEventWrapper *structData = static_cast<chreAudioDataEventWrapper *>(
                                            wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                                            eventDataForWASM));
    uint32_t bufferOffset = 0;
    if (NULL != structData) {
        bufferOffset = structData->samplesULaw8Poiner;
        wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
        wasm_runtime_module_free(WasmModuleInst, bufferOffset);
    } else {
        LOGW("Attempt to free memory that does not belong to the current Wasm module instance!");
    }
}


void chreAudioDataEventRelease(chreAudioDataEvent *eventData) {
    chreHeapFree(const_cast<uint8_t*>(eventData->samplesULaw8));
    chreHeapFree(eventData);
}

#ifdef __cplusplus
}
#endif