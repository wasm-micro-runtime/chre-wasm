#include "chre/platform/shared/chre_api_wrapper/audio_wrapper.h"
#include "chre/platform/log.h"
#include "chre/platform/shared/chre_api_wrapper/wrapper_data_map.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"
#ifdef __cplusplus
extern "C" {
#endif


bool chreAudioGetSourceWrapper(wasm_exec_env_t exec_env, uint32_t handle, 
                               struct chreAudioSource *audioSource) {
    uint32_t nameOffset = 0;
    char *name = NULL;
    uint32_t nameLength = 0;
    wasm_module_inst_t WasmModuleInst = NULL;
    bool success = (NULL!=exec_env)&&(WasmModuleInst = wasm_runtime_get_module_inst(exec_env))
                    && chreAudioGetSource(handle, audioSource);
    if (success) {
        // try to find a existed mapping name
        if(0 != (nameOffset = getOffset(WasmModuleInst, audioSource->name))) {
            audioSource->name = reinterpret_cast<const char*>(nameOffset);
        } else {
            nameLength = strlen(audioSource->name) + 1;
            WasmModuleInst = wasm_runtime_get_module_inst(exec_env);
            nameOffset = wasm_runtime_module_malloc(WasmModuleInst, nameLength + 1, \
                                                    reinterpret_cast<void**>(&name));
            success = static_cast<bool>(nameOffset);
            if (success) {
                memcpy(name, audioSource->name, nameLength);
                audioSource->name = reinterpret_cast<const char*>(nameOffset);
                // map this native data to the WASM offset
                setNativeData(WasmModuleInst, audioSource, nameOffset);
            }
        }
    }
    return success;
}


bool chreAudioConfigureSourceWrapper(wasm_exec_env_t exec_env,
                                     uint32_t handle, bool enable,
                                     uint64_t bufferDuration,
                                     uint64_t deliveryInterval) {
    return chreAudioConfigureSource(handle, enable, bufferDuration, deliveryInterval);
}
/**
 * @todo chreAudioGetStatus is not supported
*/
bool chreAudioGetStatusWrapper(wasm_exec_env_t exec_env, uint32_t handle,
                               chreAudioSourceStatus *status){
    // return chreAudioGetStatus(handle, status);
    return false;
}

//! struct chreAudioSourceStatusEvent begin

NATIVE_TO_WASM_FUNCTION_DECLARATION(chreAudioSourceStatusEvent){
    const chreAudioSourceStatusEvent *eventData = 
          reinterpret_cast<const chreAudioSourceStatusEvent *>(nativeData);
    uint32_t offset = 0;
    chreAudioSourceStatusEvent *data = NULL;
    offset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreAudioSourceStatusEvent),
                                        reinterpret_cast<void**>(&data));
    if(0 != offset) {
        memcpy(data, eventData, sizeof(chreAudioSourceStatusEvent));
    } else {
        LOGE("Allocate memory for struct chreAudioSourceStatusEvent in Wasm failed!");
    }
    return offset;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreAudioSourceStatusEvent){
    chreAudioSourceStatusEvent *dataLevel1 = static_cast<chreAudioSourceStatusEvent *>(
                                                    wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                                                    eventDataForWASM));
    chreAudioSourceStatusEvent *eventData = NULL;
    if (!dataLevel1) {
        LOGE("Try to copy memory not belonging to the current Wasm instance!");
        goto fail;
    }
    eventData = reinterpret_cast<chreAudioSourceStatusEvent *>(chreHeapAlloc(sizeof(chreAudioSourceStatusEvent)));
    if (!eventData) {
        LOGE("Allocate memory for struct chreAudioSourceStatusEvent in Native failed!");
        goto fail;
    }
    memcpy(eventData, dataLevel1, sizeof(chreAudioSourceStatusEvent));
    return eventData;

fail:
    return nullptr;
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreAudioSourceStatusEvent){
    if(eventDataForWASM)
        wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreAudioSourceStatusEvent){
    chreHeapFree(nativeData);
}

//! struct chreAudioDataEvent begin
NATIVE_TO_WASM_FUNCTION_DECLARATION(chreAudioDataEvent){
    const chreAudioDataEvent *eventData = 
          reinterpret_cast<const chreAudioDataEvent *>(nativeData);
    uint32_t structOffset = 0;
    uint32_t samepleBuffer = 0;
    uint32_t samepleBufferLength = eventData->sampleCount;
    chreAudioDataEvent *strcutData = NULL;
    uint8_t *samepleBufferInNative = NULL;

    //! Caculate the number of bytes used by the buffer
    //! If it is 16-bit sample, multiply the result by 2
    if (eventData->format == chreAudioDataFormat::CHRE_AUDIO_DATA_FORMAT_16_BIT_SIGNED_PCM) {
        samepleBufferLength<<=1;
    }
    if(!(structOffset = wasm_runtime_module_malloc(WasmModuleInst, sizeof(chreAudioDataEvent),
                                        reinterpret_cast<void**>(&strcutData)))){
        goto fail1;
    } else if(!(samepleBuffer = wasm_runtime_module_malloc(WasmModuleInst, samepleBufferLength,
                                               reinterpret_cast<void**>(&samepleBufferInNative)))) {
        goto fail2;
    }

    //! Copy the part of memory (before pointers occuring)
    memcpy(strcutData, reinterpret_cast<const chreAudioDataEvent *>(eventData), 
            offsetof(chreAudioDataEvent, samplesULaw8));
    //! Copy the sameple buffer
    memcpy(samepleBufferInNative, eventData->samplesULaw8, samepleBufferLength);
    //! Set the Wasm pointer to the structure from Wasm
    strcutData->samplesULaw8 = reinterpret_cast<const unsigned char *>(samepleBuffer);

    return structOffset;
fail2:
    wasm_runtime_module_free(WasmModuleInst, structOffset);
fail1:
    LOGE("Allocate memory for struct chreAudioDataEvent in Wasm failed!");
    return 0;
}

WASM_TO_NATIVE_FUNCTION_DECLARATION(chreAudioDataEvent){
    // native event
    chreAudioDataEvent *eventData = NULL;
    // wasm event
    chreAudioDataEvent *structData = NULL;
    uint8_t *bufferData = NULL;
    uint32_t bufferDataLength = 0;
    if(!(structData = static_cast<chreAudioDataEvent *>(
                        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)))) {
        LOGE("Try to copy memory not belonging to the current Wasm instance!");
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
    memcpy(eventData, structData, offsetof(chreAudioDataEvent, samplesULaw8));
    //! Saved the pointer
    eventData->samplesULaw8 = bufferData;
    return eventData;
fail2:
    chreHeapFree(eventData);
fail1:
    return nullptr;
}

FREE_WASM_EVENT_FUNCTION_DECLARATION(chreAudioDataEvent){
    chreAudioDataEvent *structData = static_cast<chreAudioDataEvent *>(
                                            wasm_runtime_addr_app_to_native(WasmModuleInst,
                                                                            eventDataForWASM));
    uint32_t bufferOffset = 0;
    if (NULL != structData) {
        bufferOffset = reinterpret_cast<uint32_t>(structData->samplesULaw8);
        wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);
        if(0 != bufferOffset) {
            wasm_runtime_module_free(WasmModuleInst, bufferOffset);
        }
    } else {
        LOGW("Attempt to free memory that does not belong to the current Wasm module instance!");
    }
}

FREE_NATIVE_EVENT_FUNCTION_DECLARATION(chreAudioDataEvent){ 
    const chreAudioDataEvent *eventData = 
                            reinterpret_cast<const chreAudioDataEvent *>(nativeData);
    if (!nativeData) {
        LOGE("");
        return;
    }
    chreHeapFree(const_cast<uint8_t*>(eventData->samplesULaw8));
    chreHeapFree(const_cast<chreAudioDataEvent *>(eventData));
}

#ifdef __cplusplus
}
#endif