#ifndef _MACROS_FOR_WRAPPER_H_
#define _MACROS_FOR_WRAPPER_H_
/* clang format off */
#define NATIVE_TO_WASM_FUNCTION_DECLARATION(type) \
        uint32_t type##Dup2WASM(wasm_module_inst_t WasmModuleInst,  const void *nativeData)

#define WASM_TO_NATIVE_FUNCTION_DECLARATION(type) \
        type* type##Dup2Native(wasm_module_inst_t WasmModuleInst, \
                                                         uint32_t eventDataForWASM)
#define FREE_WASM_EVENT_FUNCTION_DECLARATION(type) \
        void type##WASMRelease(wasm_module_inst_t WasmModuleInst,    \
                                  uint32_t eventDataForWASM)

#define FREE_NATIVE_EVENT_FUNCTION_DECLARATION(type) \
        void type##NativeRelease(void *nativeData)

/** 
 * These macros will call functions to convert data from Wasm to Native
 * or from Native to Wasm.
 * @todo This marco is used for all switch cases in functionxxxxx
 * @note Before use these marcos, the wasmModuleInst must be declared firstly!
*/

#define NATIVE_TO_WASM(type, offset, from)                                \
    do {                                                                  \
        offset = type##Dup2WASM(                                          \
                   WasmModuleInst, reinterpret_cast<const void*>(from) ); \
    } while(0);

#define WASM_TO_NATIVE(type, offset, to)                    \
    do {                                                    \
        to = type##Dup2Native(WasmModuleInst, offset);      \
    } while(0);

#define FREE_WASM_EVENT(type, offset)                       \
    do {                                                    \
        type##WASMRelease(WasmModuleInst, offset);          \
    } while(0);

#define FREE_NATIVE_EVENT(type, pointer)                                      \
    do {                                                                      \
        type##NativeRelease(reinterpret_cast<void*>(pointer));                \
    } while(0);

#define CONVERSION_FUNCTIONS_DECLARATION(type)          \
            NATIVE_TO_WASM_FUNCTION_DECLARATION(type);  \
            WASM_TO_NATIVE_FUNCTION_DECLARATION(type);  \
            FREE_WASM_EVENT_FUNCTION_DECLARATION(type); \
            FREE_NATIVE_EVENT_FUNCTION_DECLARATION(type);

/**
 * @note This is macro is for quickly writing functions of the structure with no pointer, 
 *       which are used to convert data between native and wasm 
*/
#define STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(type)                                         \
    NATIVE_TO_WASM_FUNCTION_DECLARATION(type) {                                                     \
        const type *native_event =                                                                  \
                reinterpret_cast<const type *>(nativeData);                                         \
        uint32_t offset_event = 0;                                                                  \
        struct type *pointer_event = NULL;                                                          \
        if(!(offset_event = wasm_runtime_module_malloc(WasmModuleInst, sizeof(type),                \
                                                    reinterpret_cast<void**>(&pointer_event)))) {   \
            goto fail0;                                                                             \
        }                                                                                           \
        memcpy(pointer_event, native_event, sizeof(type));                                          \
        return offset_event;                                                                        \
    fail0:                                                                                          \
        LOGE("Allocate memory for struct " #type " in Wasm failed!");                               \
        return 0;                                                                                   \
    }                                                                                               \
                                                                                                    \
    WASM_TO_NATIVE_FUNCTION_DECLARATION(type) {                                                     \
        const struct type *wasm_event = NULL;                                                       \
        type *pointer_event = NULL;                                                                 \
        if (!wasm_runtime_validate_app_addr(WasmModuleInst, eventDataForWASM,                       \
                                            sizeof(struct type))){                                  \
            LOGE("The wasm memory to be copied is out of the boundary");                            \
            goto fail0;                                                                             \
        }                                                                                           \
        if(!(pointer_event = reinterpret_cast<struct type*>(                                        \
                                chreHeapAlloc(sizeof(struct type))))) {                             \
            LOGE("Allocate memory for struct " #type " in Native failed!");                         \
            goto fail0;                                                                             \
        }                                                                                           \
        wasm_event = reinterpret_cast<struct type*>(                                                \
                                wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)); \
                                                                                                    \
        memcpy(pointer_event, wasm_event, sizeof(struct type));                                     \
        return pointer_event;                                                                       \
    fail0:                                                                                          \
        return nullptr;                                                                             \
    }                                                                                               \
                                                                                                    \
    FREE_WASM_EVENT_FUNCTION_DECLARATION(type) {                                                    \
        wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);                                 \
    }                                                                                               \
                                                                                                    \
    FREE_NATIVE_EVENT_FUNCTION_DECLARATION(type) {                                                  \
        chreHeapFree(nativeData);                                                                   \
    }
/* clang format on */
#endif