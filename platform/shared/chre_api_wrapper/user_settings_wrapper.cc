#include "chre/platform/shared/chre_api_wrapper/user_settings_wrapper.h"
#include "chre/platform/log.h"
#include "chre/re.h"
#include "memory.h"
#include "stddef.h"

STRUCTURE_WITH_NO_POINTER_FUNCTIONS_IMPLEMENT(chreUserSettingChangedEvent);


int8_t chreUserSettingGetStateWrapper(wasm_exec_env_t exec_env, uint8_t setting) {
    return chreUserSettingGetState(setting);
}

void chreUserSettingConfigureEventsWrapper(wasm_exec_env_t exec_env, uint8_t setting, bool enable) {
    return chreUserSettingConfigureEvents(setting, enable);
}
