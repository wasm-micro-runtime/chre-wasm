#include <cstring>

#include "chre/core/wamr_embed.h"
#include "chre/core/wasm_call_native_api.h"
#include "chre/platform/log.h"
#include "wasm_export.h"
namespace chre {
    /**TODO_FOR_LJQ*/
    //todo: need to adujust the size if globalHeapBuffer
    //todo: need to use constant
    static char globalHeapBuffer[512 * 1024];
    static RuntimeInitArgs init_args;
    
    bool WebAssemblyMicroRuntime::init() {
        bool success = true;
        memset(&init_args, 0, sizeof(RuntimeInitArgs));
        //todo: do we need Alloc_With_Allocator?
        /* configure the memory allocator for the runtime */
        init_args.mem_alloc_type = Alloc_With_Pool;
        init_args.mem_alloc_option.pool.heap_buf = globalHeapBuffer;
        init_args.mem_alloc_option.pool.heap_size = sizeof(globalHeapBuffer);
        init_args.native_module_name = "env";
        init_args.n_native_symbols = native_symbols_count;
        init_args.native_symbols = native_symbols;

        /**TODO_FOR_LJQ*/
        //todo: we don't need mullti-thread?
        /* set maximum thread number if needed when multi-thread is enabled,
        the default value is 4 */
        init_args.max_thread_num = 4;

        /* initialize runtime environment with user configurations*/
        if (!wasm_runtime_full_init(&init_args)) {
            LOGE("WAMR initialization failed!");
            success = false;
        }
        return success;
    }
    void WebAssemblyMicroRuntime::deinit() {
        wasm_runtime_unregister_natives("env", native_symbols);
        wasm_runtime_destroy();
        return;
    }

}