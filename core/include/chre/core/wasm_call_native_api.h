#ifndef CHRE_PLATFORM_WASM_CALL_NATIVE_API_H_
#define CHRE_PLATFORM_WASM_CALL_NATIVE_API_H_
#include "wasm_export.h"
#include <stdint.h>
namespace chre {
    extern NativeSymbol native_symbols[];
    extern uint32_t native_symbols_count;
}
#endif