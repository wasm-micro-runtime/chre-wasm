#include "chre/user_settings.h"
#include "stddef.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_api_wrapper/macros_for_wrapper.h"

#ifndef _USER_SETTINGS_WRAPPER_H_
#define _USER_SETTINGS_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @note for struct chreUserSettingChangedEvent
*/
CONVERSION_FUNCTIONS_DECLARATION(chreUserSettingChangedEvent);

int8_t chreUserSettingGetStateWrapper(wasm_exec_env_t exec_env, uint8_t setting);

void chreUserSettingConfigureEventsWrapper(wasm_exec_env_t exec_env, uint8_t setting, bool enable);

#ifdef __cplusplus
}
#endif
#endif