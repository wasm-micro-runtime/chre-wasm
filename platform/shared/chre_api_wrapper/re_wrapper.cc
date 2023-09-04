
#include "chre/platform/shared/chre_api_wrapper/re_wrapper.h"
#include "chre/platform/log.h"
#include "bh_common.h"
#include "bh_log.h"

#ifdef __cplusplus
extern "C" {
#endif


void
wasm_runtime_set_exception(wasm_module_inst_t module, const char *exception);

uint32_t
wasm_runtime_module_realloc(wasm_module_inst_t module, uint32_t ptr, uint32_t size,
                            void **p_native_addr);

/* clang-format off */
#define get_module_inst(exec_env) \
    wasm_runtime_get_module_inst(exec_env)

#define validate_app_addr(offset, size) \
    wasm_runtime_validate_app_addr(module_inst, offset, size)

#define validate_app_str_addr(offset) \
    wasm_runtime_validate_app_str_addr(module_inst, offset)

#define validate_native_addr(addr, size) \
    wasm_runtime_validate_native_addr(module_inst, addr, size)

#define addr_app_to_native(offset) \
    wasm_runtime_addr_app_to_native(module_inst, offset)

#define addr_native_to_app(ptr) \
    wasm_runtime_addr_native_to_app(module_inst, ptr)

#define module_malloc(size, p_native_addr) \
    wasm_runtime_module_malloc(module_inst, size, p_native_addr)

#define module_free(offset) \
    wasm_runtime_module_free(module_inst, offset)
/* clang-format on */

typedef int (*out_func_t)(int c, void *ctx);

#define _INTSIZEOF(n) (((uint32_t)sizeof(n) + 3) & (uint32_t)~3)
#define _va_arg(ap, t) (*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))

#define CHECK_VA_ARG(ap, t)                                  \
    do {                                                     \
        if ((uint8_t *)ap + _INTSIZEOF(t) > native_end_addr) { \
            if (fmt_buf != temp_fmt) {                       \
                wasm_runtime_free(fmt_buf);                  \
            }                                                \
            goto fail;                                       \
        }                                                    \
    } while (0)


/* clang-format off */
#define PREPARE_TEMP_FORMAT()                                \
    char temp_fmt[32], *s, *fmt_buf = temp_fmt;              \
    uint32_t fmt_buf_len = (uint32_t)sizeof(temp_fmt);           \
    int32_t n;                                                 \
                                                             \
    /* additional 2 bytes: one is the format char,           \
       the other is `\0` */                                  \
    if ((uint32_t)(fmt - fmt_start_addr + 2) >= fmt_buf_len) { \
        bh_assert((uint32_t)(fmt - fmt_start_addr) <=          \
                  UINT32_MAX - 2);                           \
        fmt_buf_len = (uint32_t)(fmt - fmt_start_addr + 2);    \
        if (!(fmt_buf = (char*)wasm_runtime_malloc(fmt_buf_len))) { \
            print_err(out, ctx);                             \
            break;                                           \
        }                                                    \
    }                                                        \
                                                             \
    memset(fmt_buf, 0, fmt_buf_len);                         \
    bh_memcpy_s(fmt_buf, fmt_buf_len, fmt_start_addr,        \
                (uint32_t)(fmt - fmt_start_addr + 1));
/* clang-format on */

#define OUTPUT_TEMP_FORMAT()            \
    do {                                \
        if (n > 0) {                    \
            s = buf;                    \
            while (*s)                  \
                out((int)(*s++), ctx);  \
        }                               \
                                        \
        if (fmt_buf != temp_fmt) {      \
            wasm_runtime_free(fmt_buf); \
        }                               \
    } while (0)


struct str_context {
    char *str;
    uint32_t max;
    uint32_t count;
};

uint64_t chreGetAppIdWrapper(wasm_exec_env_t exec_env) {
    return chreGetAppId();
}

uint32_t chreGetInstanceIdWrapper(wasm_exec_env_t exec_env) {
    return chreGetInstanceId();
}


static int
sprintf_out(int c, struct str_context *ctx)
{
    if (!ctx->str || ctx->count >= ctx->max) {
        ctx->count++;
        return c;
    }

    if (ctx->count == ctx->max - 1) {
        ctx->str[ctx->count++] = '\0';
    }
    else {
        ctx->str[ctx->count++] = (char)c;
    }

    return c;
}

static void
print_err(out_func_t out, void *ctx)
{
    out('E', ctx);
    out('R', ctx);
    out('R', ctx);
}

static bool
_vprintf_wa(out_func_t out, void *ctx, const char *fmt, _va_list ap,
            wasm_module_inst_t module_inst)
{
    int might_format = 0; /* 1 if encountered a '%' */
    int long_ctr = 0;
    uint8_t *native_end_addr;
    const char *fmt_start_addr = NULL;

    if (!wasm_runtime_get_native_addr_range(module_inst, (uint8_t *)ap, NULL,
                                            &native_end_addr))
        goto fail;

    /* fmt has already been adjusted if needed */

    while (*fmt) {
        if (!might_format) {
            if (*fmt != '%') {
                out((int)*fmt, ctx);
            }
            else {
                might_format = 1;
                long_ctr = 0;
                fmt_start_addr = fmt;
            }
        }
        else {
            switch (*fmt) {
                case '.':
                case '+':
                case '-':
                case ' ':
                case '#':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    goto still_might_format;

                case 't': /* ptrdiff_t */
                case 'z': /* size_t (32bit on wasm) */
                    long_ctr = 1;
                    goto still_might_format;

                case 'j':
                    /* intmax_t/uintmax_t */
                    long_ctr = 2;
                    goto still_might_format;

                case 'l':
                    long_ctr++;
                    /* Fall through */
                case 'h':
                    /* FIXME: do nothing for these modifiers */
                    goto still_might_format;

                case 'o':
                case 'd':
                case 'i':
                case 'u':
                case 'p':
                case 'x':
                case 'X':
                case 'c':
                {
                    char buf[64];
                    PREPARE_TEMP_FORMAT();

                    if (long_ctr < 2) {
                        int32_t d;

                        CHECK_VA_ARG(ap, uint32_t);
                        d = _va_arg(ap, int32_t);

                        if (long_ctr == 1) {
                            uint32_t fmt_end_idx = (uint32_t)(fmt - fmt_start_addr);

                            if (fmt_buf[fmt_end_idx - 1] == 'l'
                                || fmt_buf[fmt_end_idx - 1] == 'z'
                                || fmt_buf[fmt_end_idx - 1] == 't') {
                                /* The %ld, %zd and %td should be treated as
                                 * 32bit integer in wasm */
                                fmt_buf[fmt_end_idx - 1] = fmt_buf[fmt_end_idx];
                                fmt_buf[fmt_end_idx] = '\0';
                            }
                        }

                        n = snprintf(buf, sizeof(buf), fmt_buf, d);
                    }
                    else {
                        int64 lld;

                        /* Make 8-byte aligned */
                        ap = (_va_list)(((uintptr_t)ap + 7) & ~(uintptr_t)7);
                        CHECK_VA_ARG(ap, uint64);
                        lld = _va_arg(ap, int64);
                        n = snprintf(buf, sizeof(buf), fmt_buf, lld);
                    }

                    OUTPUT_TEMP_FORMAT();
                    break;
                }

                case 's':
                {
                    char buf_tmp[128], *buf = buf_tmp;
                    char *start;
                    uint32_t s_offset, str_len, buf_len;

                    PREPARE_TEMP_FORMAT();

                    CHECK_VA_ARG(ap, int32_t);
                    s_offset = _va_arg(ap, uint32_t);

                    if (!validate_app_str_addr(s_offset)) {
                        if (fmt_buf != temp_fmt) {
                            wasm_runtime_free(fmt_buf);
                        }
                        return false;
                    }

                    s = start = (char*)addr_app_to_native(s_offset);

                    str_len = (uint32_t)strlen(start);
                    if (str_len >= UINT32_MAX - 64) {
                        print_err(out, ctx);
                        if (fmt_buf != temp_fmt) {
                            wasm_runtime_free(fmt_buf);
                        }
                        break;
                    }

                    /* reserve 64 more bytes as there may be width description
                     * in the fmt */
                    buf_len = str_len + 64;

                    if (buf_len > (uint32_t)sizeof(buf_tmp)) {
                        if (!(buf = (char*)wasm_runtime_malloc(buf_len))) {
                            print_err(out, ctx);
                            if (fmt_buf != temp_fmt) {
                                wasm_runtime_free(fmt_buf);
                            }
                            break;
                        }
                    }

                    n = snprintf(buf, buf_len, fmt_buf,
                                 (s_offset == 0 && str_len == 0) ? NULL
                                                                 : start);

                    OUTPUT_TEMP_FORMAT();

                    if (buf != buf_tmp) {
                        wasm_runtime_free(buf);
                    }

                    break;
                }

                case '%':
                {
                    out((int)'%', ctx);
                    break;
                }

                case 'e':
                case 'E':
                case 'g':
                case 'G':
                case 'f':
                case 'F':
                {
                    double f64;
                    char buf[64];
                    PREPARE_TEMP_FORMAT();

                    /* Make 8-byte aligned */
                    ap = (_va_list)(((uintptr_t)ap + 7) & ~(uintptr_t)7);
                    CHECK_VA_ARG(ap, double);
                    f64 = _va_arg(ap, double);
                    n = snprintf(buf, sizeof(buf), fmt_buf, f64);

                    OUTPUT_TEMP_FORMAT();
                    break;
                }

                case 'n':
                    /* print nothing */
                    break;

                default:
                    out((int)'%', ctx);
                    out((int)*fmt, ctx);
                    break;
            }

            might_format = 0;
        }

    still_might_format:
        ++fmt;
    }
    return true;

fail:
    wasm_runtime_set_exception(module_inst, "out of bounds memory access");
    return false;
}

/**
 * @note we firstly output string to a buffer 'data' in wasm
*/
void chreLogWrapper(wasm_exec_env_t exec_env, enum chreLogLevel level, const char *formatStr, _va_list va_args) {
    //chreLog(level, formatStr, data);
    wasm_module_inst_t module_inst = get_module_inst(exec_env);
    struct str_context ctx;
    const int strSize = 512;
    char str[strSize];
    /* str and format have been checked by runtime */
    if (!validate_native_addr(va_args, sizeof(uint32_t))) {
        LOGE("The variable argument passed to chreLog in invalid!");
        return;
    }

    ctx.str = str;
    ctx.max = strSize;
    ctx.count = 0;

    if (!_vprintf_wa((out_func_t)sprintf_out, &ctx, formatStr, va_args,
                     module_inst)) {
        LOGE("vsprintf fail in chreLogWrapper!");
        return;
    }

    if (ctx.count < ctx.max) {
        str[ctx.count] = '\0';
    }
    chreLog(level, "%s", str);
}

uint64_t chreGetTimeWrapper(wasm_exec_env_t exec_env){
    return chreGetTime();
}

int64_t chreGetEstimatedHostTimeOffsetWrapper(wasm_exec_env_t exec_env){
    return chreGetEstimatedHostTimeOffset();
}

uint32_t chreTimerSetWrapper(wasm_exec_env_t exec_env, uint64_t duration, const void *cookie, bool oneShot){
    return chreTimerSet(duration, cookie, oneShot);
}

bool chreTimerCancelWrapper(wasm_exec_env_t exec_env, uint32_t timerId) {
    return chreTimerCancel(timerId);
}

void chreAbortWrapper(wasm_exec_env_t exec_env, uint32_t abortCode) {
    chreAbort(abortCode);
}

uint32_t chreHeapAllocWrapper(wasm_exec_env_t exec_env, uint32_t bytes) {
    wasm_module_inst_t WasmModuleInst  = wasm_runtime_get_module_inst(exec_env);
    return wasm_runtime_module_malloc(WasmModuleInst, bytes, NULL);
}

void chreHeapFreeWrapper(wasm_exec_env_t exec_env, uint32_t ptr){
    wasm_module_inst_t WasmModuleInst  = wasm_runtime_get_module_inst(exec_env);
    wasm_runtime_module_free(WasmModuleInst, ptr);
}
/**
 * @note we firstly output string to a buffer 'data' in wasm
*/
void chreDebugDumpLogWrapper(wasm_exec_env_t exec_env, const char *formatStr, _va_list va_args) {
    wasm_module_inst_t module_inst = get_module_inst(exec_env);
    struct str_context ctx;
    const int strSize = 512;
    char str[strSize];
    /* str and format have been checked by runtime */
    if (!validate_native_addr(va_args, sizeof(uint32_t))) {
        LOGE("The variable argument passed to chreLog in invalid!");
        return;
    }

    ctx.str = str;
    ctx.max = strSize;
    ctx.count = 0;

    if (!_vprintf_wa((out_func_t)sprintf_out, &ctx, formatStr, va_args,
                     module_inst)) {
        LOGE("vsprintf fail in chreDebugDumpLogWrapper!");
        return;
    }

    if (ctx.count < ctx.max) {
        str[ctx.count] = '\0';
    }
    chreDebugDumpLog("%s", str);
}


#ifdef __cplusplus
}
#endif
