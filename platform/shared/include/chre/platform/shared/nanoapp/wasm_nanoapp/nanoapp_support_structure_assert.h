#if defined(CHRE_PLATFORM_SHARED_NANOAPP_SUPPORT_WASM_H_) ||  defined(CHRE_PLATFORM_SHARED_NANOAPP_SUPPORT_LIB_DSO_H_)
#include<stddef.h>
static_assert(
    sizeof(struct chreNslNanoappInfo) == 52
    && offsetof(struct chreNslNanoappInfo, magic) == 0
    && offsetof(struct chreNslNanoappInfo, structMinorVersion) == 4
    && offsetof(struct chreNslNanoappInfo, reserved) == 6
    && offsetof(struct chreNslNanoappInfo, targetApiVersion) == 8
    && offsetof(struct chreNslNanoappInfo, vendor) == 12
    && offsetof(struct chreNslNanoappInfo, name) == 16
    && offsetof(struct chreNslNanoappInfo, appId) == 20
    && offsetof(struct chreNslNanoappInfo, appVersion) == 28
    && offsetof(struct chreNslNanoappInfo, entryPoints) == 32
    && offsetof(struct chreNslNanoappInfo, appVersionString) == 44
    && offsetof(struct chreNslNanoappInfo, appPermissions) == 48
);
#endif