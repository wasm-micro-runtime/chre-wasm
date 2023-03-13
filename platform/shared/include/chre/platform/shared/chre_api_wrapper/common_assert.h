#include <stddef.h>
#ifdef _COMMON_WRAPPER_H_
/**
 * @note for struct struct chreAsyncResult
*/
static_assert(sizeof(struct chreAsyncResult) == 8
              && offsetof(struct chreAsyncResult, requestType) == 0
              && offsetof(struct chreAsyncResult, success) == 1
              && offsetof(struct chreAsyncResult, errorCode) == 2
              && offsetof(struct chreAsyncResult, reserved) == 3
              && offsetof(struct chreAsyncResult, cookie) == 4);
#endif