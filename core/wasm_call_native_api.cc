
#include "chre/core/wasm_call_native_api.h"
#include "wasm_export.h"
#include "chre/platform/shared/chre_wrapper.h"
#define REG_NATIVE_FUNC(func_name, signature) \
    { #func_name, (void*) (func_name##Wrapper), signature, NULL }

#ifndef NULL
#define NULL 0
#endif

namespace chre{
/*for wwan.h end*/
NativeSymbol native_symbols[] = {
    //! audio.h begin
    REG_NATIVE_FUNC(chreAudioGetSource,"(i*)i"),
    REG_NATIVE_FUNC(chreAudioConfigureSource,"(iiII)i"),
    REG_NATIVE_FUNC(chreAudioGetStatus,"(i*)i"),
    //! audio.h end

    //! ble.h begin
    REG_NATIVE_FUNC(chreBleGetCapabilities,"()i"),
    REG_NATIVE_FUNC(chreBleGetFilterCapabilities,"()i"),
    REG_NATIVE_FUNC(chreBleStartScanAsync,"(ii*)i"),
    REG_NATIVE_FUNC(chreBleStopScanAsync,"()i"),
    //! ble.h end
    //event.h begin
    REG_NATIVE_FUNC(chreSendEvent,"(iiii)i"),
    REG_NATIVE_FUNC(chreSendMessageToHost,"(*~ii)i"),
    REG_NATIVE_FUNC(chreSendMessageToHostEndpoint,"(*~iii)i"),
    REG_NATIVE_FUNC(chreSendMessageWithPermissions,"(*~iiii)i"),
    REG_NATIVE_FUNC(chreGetNanoappInfoByAppId,"(I*)i"),
    REG_NATIVE_FUNC(chreGetNanoappInfoByInstanceId,"(i*)i"),
    REG_NATIVE_FUNC(chreConfigureNanoappInfoEvents, "(i)"),
    REG_NATIVE_FUNC(chreConfigureHostSleepStateEvents, "(i)"),
    REG_NATIVE_FUNC(chreIsHostAwake,"()i"),
    REG_NATIVE_FUNC(chreConfigureDebugDumpEvent, "(i)"),
    REG_NATIVE_FUNC(chreConfigureHostEndpointNotifications,"(ii)i"),
    REG_NATIVE_FUNC(chrePublishRpcServices,"(*i)i"),
    REG_NATIVE_FUNC(chreGetHostEndpointInfo,"(i*)i"),
    // { "chreGetHostEndpointInfoWrapper", (void*) (chreGetHostEndpointInfoWrapper), "(i$)i", NULL },
    //! event.h end
    //! gnss.h begin
    REG_NATIVE_FUNC(chreGnssGetCapabilities,"()i"),
    REG_NATIVE_FUNC(chreGnssLocationSessionStartAsync,"(ii*)i"),
    REG_NATIVE_FUNC(chreGnssLocationSessionStopAsync,"(*)i"),
    REG_NATIVE_FUNC(chreGnssMeasurementSessionStartAsync,"(i*)i"),
    REG_NATIVE_FUNC(chreGnssMeasurementSessionStopAsync,"(*)i"),
    REG_NATIVE_FUNC(chreGnssConfigurePassiveLocationListener,"(i)i"),
    //! gnss.h end 
    
    //! re.h begin
    REG_NATIVE_FUNC(chreGetAppId,"()I"),
    REG_NATIVE_FUNC(chreGetInstanceId,"()i"),
    // REG_NATIVE_FUNC(chreLog,"(i$*)"),
    REG_NATIVE_FUNC(chreGetTime,"()I"),
    REG_NATIVE_FUNC(chreGetEstimatedHostTimeOffset,"()I"),
    REG_NATIVE_FUNC(chreTimerSet,"(I*i)i"),
    REG_NATIVE_FUNC(chreTimerCancel,"(i)i"),
    REG_NATIVE_FUNC(chreAbort,"(i)"),
    REG_NATIVE_FUNC(chreHeapAlloc,"(i)i"),
    REG_NATIVE_FUNC(chreHeapFree,"(i)"),
    // REG_NATIVE_FUNC(chreDebugDumpLog,"$*"),
    //! re.h end
   
   //! sensor.h begin
    REG_NATIVE_FUNC(chreSensorFindDefault,"(i*)i"),
    REG_NATIVE_FUNC(chreSensorFind,"(ii*)"),
    REG_NATIVE_FUNC(chreGetSensorInfo,"(i*)i"),
    REG_NATIVE_FUNC(chreGetSensorSamplingStatus,"(i*)i"),
    REG_NATIVE_FUNC(chreSensorConfigure,"(iiII)i"),
    REG_NATIVE_FUNC(chreSensorConfigureBiasEvents,"(ii)i"),
    REG_NATIVE_FUNC(chreSensorGetThreeAxisBias, "(i*)i"),
    REG_NATIVE_FUNC(chreSensorFlushAsync,"(i*)i"),
    //! sensor.h end

    //! user_settings.h begin
    REG_NATIVE_FUNC(chreUserSettingGetState, "(i)i"),
    REG_NATIVE_FUNC(chreUserSettingConfigureEvents,"(ii)"),
    //! user_settings.h end

    //! version.h begin
    REG_NATIVE_FUNC(chreGetApiVersion,"()i"),
    REG_NATIVE_FUNC(chreGetVersion,"()i"),
    REG_NATIVE_FUNC(chreGetPlatformId,"()I"),
    //! version.h end
 
    //! wifi.h begin
    REG_NATIVE_FUNC(chreWifiGetCapabilities,"()i"),
    REG_NATIVE_FUNC(chreWifiNanGetCapabilities,"(*)i"),
    REG_NATIVE_FUNC(chreWifiConfigureScanMonitorAsync,"(i*)i"),
    REG_NATIVE_FUNC(chreWifiRequestScanAsync,"(i*)i"),
    REG_NATIVE_FUNC(chreWifiRequestRangingAsync,"(i*)i"),
    REG_NATIVE_FUNC(chreWifiNanSubscribe,"(**)i"),
    REG_NATIVE_FUNC(chreWifiNanSubscribeCancel,"(i)i"),
    REG_NATIVE_FUNC(chreWifiNanRequestRangingAsync,"(**)i"),
    //! wifi.h end

    //! wwan.h begin
    REG_NATIVE_FUNC(chreWwanGetCapabilities,"()i"),
    REG_NATIVE_FUNC(chreWwanGetCellInfoAsync,"(*)i"),
    //! wwan.h end
};
uint32_t native_symbols_count = sizeof(native_symbols) / sizeof(NativeSymbol);
}
