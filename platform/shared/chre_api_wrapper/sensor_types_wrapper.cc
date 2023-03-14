#include "chre/platform/shared/chre_api_wrapper/sensor_types_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"

/** clang format off */
/**
 * @note This macro is used to implement conversion functions 
 * of the flexible structure without pointer members
*/

#define FLEX_STRUCTURE_CONVERT_FUNCTIONS_IMPLEMENT(type)                                    \
    NATIVE_TO_WASM_FUNCTION_DECLARATION(type) {                                             \
        const struct type* native_event= NULL;                                              \
        uint32_t offset_event = 0;                                                          \
        struct type* pointer_event = NULL;                                                  \
        uint32_t totalSize = 0;                                                             \
        if (!nativeData) {                                                                  \
            LOGE("The pointer to be copied is NULL");                                       \
            goto fail0;                                                                     \
        }                                                                                   \
        native_event = reinterpret_cast<const struct type*>(nativeData);                    \
                                                                                            \
        totalSize += sizeof(struct chreSensorDataHeader);                                   \
        totalSize += native_event->header.readingCount                                      \
                            * (sizeof(struct type) - sizeof(struct chreSensorDataHeader));  \
                                                                                            \
        offset_event = wasm_runtime_module_malloc(WasmModuleInst, totalSize,                \
                                                reinterpret_cast<void**>(&pointer_event));  \
        if(!offset_event) {                                                                 \
            LOGE("Allocate memory for struct chreGnssDataEvent in Wasm failed!");           \
            goto fail0;                                                                     \
        }                                                                                   \
        memcpy(pointer_event, native_event, totalSize);                                     \
        return offset_event;                                                                \
    fail0:                                                                                  \
        return 0;                                                                           \
    }                                                                                       \
                                                                                            \
    WASM_TO_NATIVE_FUNCTION_DECLARATION(type) {                                             \
        const struct type* wasm_event= NULL;                                                \
        struct type* pointer_event = NULL;                                                  \
        uint32_t totalSize = 0;                                                             \
        if (!eventDataForWASM) {                                                            \
            LOGE("The offset to be copied is 0");                                           \
            goto fail0;                                                                     \
        }                                                                                   \
        wasm_event = reinterpret_cast<const struct type*>(                                  \
                        wasm_runtime_addr_app_to_native(WasmModuleInst, eventDataForWASM)); \
                                                                                            \
        totalSize += sizeof(struct chreSensorDataHeader);                                   \
        totalSize += wasm_event->header.readingCount                                        \
                            * (sizeof(struct type) - sizeof(struct chreSensorDataHeader));  \
                                                                                            \
        pointer_event = reinterpret_cast<struct type*>(chreHeapAlloc(totalSize));           \
        if(!pointer_event) {                                                                \
            LOGE("Allocate memory for struct chreGnssDataEvent in Native failed!");         \
            goto fail0;                                                                     \
        }                                                                                   \
        memcpy(pointer_event, wasm_event, totalSize);                                       \
        return pointer_event;                                                               \
    fail0:                                                                                  \
        return nullptr;                                                                     \
    }                                                                                       \
                                                                                            \
    FREE_WASM_EVENT_FUNCTION_DECLARATION(type) {                                            \
        wasm_runtime_module_free(WasmModuleInst, eventDataForWASM);                         \
    }                                                                                       \
                                                                                            \
    FREE_NATIVE_EVENT_FUNCTION_DECLARATION(type) {                                          \
        chreHeapFree(nativeData);                                                           \
    }
/** clang format on */

/**
 * @note for struct chreSensorThreeAxisData
*/
FLEX_STRUCTURE_CONVERT_FUNCTIONS_IMPLEMENT(chreSensorThreeAxisData);

/**
 * @note for struct chreSensorOccurrenceData
*/
FLEX_STRUCTURE_CONVERT_FUNCTIONS_IMPLEMENT(chreSensorOccurrenceData);

/**
 * @note for struct chreSensorFloatData
*/
FLEX_STRUCTURE_CONVERT_FUNCTIONS_IMPLEMENT(chreSensorFloatData);

/**
 * @note for struct chreSensorByteData
*/
FLEX_STRUCTURE_CONVERT_FUNCTIONS_IMPLEMENT(chreSensorByteData);

/**
 * @note for struct chreSensorUint64Data
*/
FLEX_STRUCTURE_CONVERT_FUNCTIONS_IMPLEMENT(chreSensorUint64Data);

