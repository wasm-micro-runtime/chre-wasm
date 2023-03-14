#include<stddef.h>
#ifdef _CHRE_USER_SETTINGS_H_

/**
 * @note for struct chreSensorDataHeader
*/
static_assert(sizeof(struct chreUserSettingChangedEvent) == 2
              && offsetof(struct chreUserSettingChangedEvent, setting) == 0
              && offsetof(struct chreUserSettingChangedEvent, settingState) == 1);

#endif