/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "chre/platform/platform_nanoapp.h"

#include <dlfcn.h>
#include <cinttypes>

#include "chre/platform/assert.h"
#include "chre/platform/log.h"
#include "chre/platform/shared/nanoapp_dso_util.h"
#include "chre/util/system/napp_permissions.h"
#include "chre_api/chre/version.h"

#include "wasm_export.h"
#include "bh_platform.h"
#include "bh_read_file.h"
#include "chre/platform/shared/chre_wrapper.h"
#include "chre/platform/shared/chre_api_wrapper/wrapper_data_map.h"

namespace chre {

PlatformNanoapp::~PlatformNanoapp() {
  closeNanoapp();
}

bool PlatformNanoapp::start() {
  uint32 argv[2] = {0};
  bool success = openNanoapp();
  if (success){
    if(mIsWASM) {
      success = wasm_runtime_call_wasm(mWASMHandle.ExecEnv,
                        mWASMHandle.nanoappStartFromWASM, 0, argv);
      if(!success){
        LOGE("Call nanoappStartFromWASM failed!"
          "Nanoapp name: %s Nanoapp id: 0x%016" PRIx64 ") ",
          mAppInfo->name, mAppInfo->appId
          );
        LOGE("Wasm world Error Info: %s", wasm_runtime_get_exception(mWASMHandle.WASMModuleInstance));
      } else{
        success = static_cast<bool>(argv[0]);
      }
    } else {
      success = mAppInfo->entryPoints.start();
    }
  }
  return success;
}

void PlatformNanoapp::handleEvent(uint32_t senderInstanceId, uint16_t eventType,
                                  const void *eventData) {
  uint32 eventOffset = 0;
  uint32 argv[4];
  const convertFunctions *funcs = nullptr;
  if (mIsWASM) {
    funcs = getConvertFunctions(eventType);
    eventOffset = funcs->native2Wasm(mWASMHandle.WASMModuleInstance, eventData);
    if (0 == eventOffset) {
      LOGE("Allocate Memory for Wasm failed! "
        "Nanoapp name: %s Nanoapp id: 0x%016" PRIx64 ") "
        "Event type: 0x%016" PRIx64 ") "
        "Sender instance Id: 0x%016" PRIx64 ")",
        mAppInfo->name, mAppInfo->appId, eventType, senderInstanceId
        );
        return;
    }
    argv[0] = senderInstanceId;
    argv[1] = eventType;
    argv[2] = eventOffset;
    if (!wasm_runtime_call_wasm(mWASMHandle.ExecEnv, mWASMHandle.nanoappHandleEventFromWASM, 3, argv)) {
      LOGE("Call nanoappHandleEventFromWASM failed! "
        "Nanoapp name: %s Nanoapp id: 0x%016" PRIx64 ") "
        "Event type: 0x%016" PRIx64 ") "
        "Sender instance Id: 0x%016" PRIx64 ")",
        mAppInfo->name, mAppInfo->appId, eventType, senderInstanceId
        );
      LOGE("Wasm world Error Info: %s", wasm_runtime_get_exception(mWASMHandle.WASMModuleInstance));
    }
    funcs->wasmRelease(mWASMHandle.WASMModuleInstance, eventOffset);
  } else {
    mAppInfo->entryPoints.handleEvent(senderInstanceId, eventType, eventData);
  }
}

void PlatformNanoapp::end() {
  uint32_t argv[2];
  if (mIsWASM) {
    if(!wasm_runtime_call_wasm(mWASMHandle.ExecEnv,
                        mWASMHandle.nanoappEndFromWASM, 0, argv)){
      LOGE("Call nanoappEndFromWASM failed!"
        "Nanoapp name: %s Nanoapp id: 0x%016" PRIx64 ") ",
        mAppInfo->name, mAppInfo->appId
        );
      LOGE("Wasm world Error Info: %s", wasm_runtime_get_exception(mWASMHandle.WASMModuleInstance));
    }
  }
  else {
    mAppInfo->entryPoints.end();
  }
  // delete the WASM Module Instance map
  delModuleInstanceMap(mWASMHandle.WASMModuleInstance);
  closeNanoapp();
}

uint64_t PlatformNanoapp::getAppId() const {
  return (mAppInfo == nullptr) ? 0 : mAppInfo->appId;
}

uint32_t PlatformNanoapp::getAppVersion() const {
  return mAppInfo->appVersion;
}

uint32_t PlatformNanoapp::getTargetApiVersion() const {
  return CHRE_API_VERSION;
}

const char *PlatformNanoapp::getAppName() const {
  return (mAppInfo != nullptr) ? mAppInfo->name : "Unknown";
}

bool PlatformNanoapp::supportsAppPermissions() const {
  return (mAppInfo != nullptr) ? (mAppInfo->structMinorVersion >=
                                  CHRE_NSL_NANOAPP_INFO_STRUCT_MINOR_VERSION)
                               : false;
}

uint32_t PlatformNanoapp::getAppPermissions() const {
  return (supportsAppPermissions())
             ? mAppInfo->appPermissions
             : static_cast<uint32_t>(chre::NanoappPermissions::CHRE_PERMS_NONE);
}

bool PlatformNanoapp::isSystemNanoapp() const {
  return (mAppInfo != nullptr && mAppInfo->isSystemNanoapp);
}

void PlatformNanoapp::logStateToBuffer(
    DebugDumpWrapper & /* debugDump */) const {}

void PlatformNanoappBase::loadFromFile(const std::string &filename) {
  CHRE_ASSERT(!isLoaded());
  mFilename = filename;
}

void PlatformNanoappBase::loadStatic(const struct chreNslNanoappInfo *appInfo) {
  CHRE_ASSERT(!isLoaded());
  mIsStatic = true;
  mAppInfo = appInfo;
}

bool PlatformNanoappBase::isLoaded() const {
  return (mIsStatic || mDsoHandle != nullptr || mIsWASM);
}

bool PlatformNanoappBase::openNanoapp() {
  bool success = false;

  if (mIsStatic) {
    success = true;
  } else if (!mFilename.empty()) {
    success = openNanoappFromFile();
  } else {
    CHRE_ASSERT(false);
  }

  return success;
}

bool PlatformNanoappBase::openNanoappFromFile() {
  CHRE_ASSERT(!mFilename.empty());
  CHRE_ASSERT_LOG(mDsoHandle == nullptr && mWASMHandle.ExecEnv == nullptr, "Re-opening nanoapp");
  bool success = false;

  if(mFilename.size() > 5 && 0 == mFilename.substr(mFilename.size()-5).compare(".wasm")) {
    success = openNanoappFromWASMFile();
  } else {
    success = openNanoappFromWASMFile();
  }
  return success;
}

bool PlatformNanoappBase::openNanoappFromWASMFile(){
  CHRE_ASSERT(!mFilename.empty());
  CHRE_ASSERT_LOG(mDsoHandle == nullptr && mWASMHandle.ExecEnv == nullptr, "Re-opening nanoapp");
  char error_buf[128];
  //Because they will store the return value of the C api, they are set to NULL
  wasm_function_inst_t getNanoappInfo = NULL;
  chreNslNanoappInfoWrapper* nanoappInfo = NULL;
  uint32 argv[2];
  if(!(mWASMHandle.WASMFileBuf = (uint8 *)bh_read_file_to_buffer(mFilename.c_str(), &mWASMHandle.WASMFileSize))) {
    LOGE("Load Wasm file into buffer failed!");
    goto fail0;
  } else if(!(mWASMHandle.WASMModule = wasm_runtime_load(mWASMHandle.WASMFileBuf, mWASMHandle.WASMFileSize,
                                        error_buf, sizeof(error_buf)))) {
    LOGE("Load Wasm module from buffer failed!");
    goto fail1;
  } else if(!(mWASMHandle.WASMModuleInstance =
            wasm_runtime_instantiate(mWASMHandle.WASMModule, mWASMHandle.StackSize, mWASMHandle.HeapSize,
                                      error_buf, sizeof(error_buf)))) {
    LOGE("Instantitate Wasm instance from module failed!");
    goto fail2;
  } else if(!(mWASMHandle.ExecEnv = wasm_runtime_create_exec_env(mWASMHandle.WASMModuleInstance, mWASMHandle.HeapSize))) {
    LOGE("Create Wasm execution environment from instance failed!");
    goto fail3;
  }
  
  mWASMHandle.nanoappStartFromWASM 
          = wasm_runtime_lookup_function(mWASMHandle.WASMModuleInstance, "nanoappStart", NULL);
  mWASMHandle.nanoappHandleEventFromWASM
          = wasm_runtime_lookup_function(mWASMHandle.WASMModuleInstance, "nanoappStart", NULL);
  mWASMHandle.nanoappHandleEventFromWASM
          = wasm_runtime_lookup_function(mWASMHandle.WASMModuleInstance, "nanoappStart", NULL);
  getNanoappInfo =  wasm_runtime_lookup_function(mWASMHandle.WASMModuleInstance, "getNanoappInfo", NULL);
  if(!mWASMHandle.nanoappStartFromWASM || !mWASMHandle.nanoappHandleEventFromWASM
      || !mWASMHandle.nanoappHandleEventFromWASM || !getNanoappInfo ) {
        goto fail4;
  }
  if(!wasm_runtime_call_wasm(mWASMHandle.ExecEnv, getNanoappInfo, 0, argv)){
      LOGE("Failed to get appinfo from Wasm world: %s", mFilename.c_str());
      LOGE("Wasm world Error Info: %s", wasm_runtime_get_exception(mWASMHandle.WASMModuleInstance));
      goto fail4;
  }
  nanoappInfo = static_cast<chreNslNanoappInfoWrapper*>(
    wasm_runtime_addr_app_to_native(mWASMHandle.WASMModuleInstance, argv[0]));
  mAppInfo = createNativeChreNslNanoappInfoFromWrapper(nanoappInfo);
  if (!mAppInfo){
    LOGE("No Space for copying appinfo from Wasm memory");
    goto fail4;
  }
  
  mIsWASM = true;
  LOGI("Nanoapp loaded: %s (0x%016" PRIx64 ") version 0x%" PRIx32
      " uimg %d system %d from file %s",
      mAppInfo->name, mAppInfo->appId, mAppInfo->appVersion,
      mAppInfo->isTcmNanoapp, mAppInfo->isSystemNanoapp,
      mFilename.c_str());
  if (mAppInfo->structMinorVersion >=
      CHRE_NSL_NANOAPP_INFO_STRUCT_MINOR_VERSION) {
    LOGI("Nanoapp permissions: 0x%" PRIx32, mAppInfo->appPermissions);
  }
  return true;

fail4:
  mWASMHandle.nanoappStartFromWASM = nullptr;
  mWASMHandle.nanoappHandleEventFromWASM = nullptr;
  mWASMHandle.nanoappEndFromWASM = nullptr;
  wasm_runtime_destroy_exec_env(mWASMHandle.ExecEnv);
fail3:
  mWASMHandle.ExecEnv = nullptr;
  wasm_runtime_deinstantiate(mWASMHandle.WASMModuleInstance);
fail2:
  mWASMHandle.WASMModuleInstance = nullptr;
  wasm_runtime_unload(mWASMHandle.WASMModule);
fail1:
  mWASMHandle.WASMModule = nullptr;
  wasm_runtime_free(mWASMHandle.WASMFileBuf);
fail0:
  mWASMHandle.WASMFileBuf = nullptr;
  return false;
}

bool PlatformNanoappBase::openNanoappFromDLLFile(){
  CHRE_ASSERT(!mFilename.empty());
  CHRE_ASSERT_LOG(mDsoHandle == nullptr && mWASMHandle.ExecEnv == nullptr, "Re-opening nanoapp");
  bool success = false;

  mDsoHandle = dlopen(mFilename.c_str(), RTLD_NOW | RTLD_GLOBAL);
  if (mDsoHandle == nullptr) {
    LOGE("Failed to load nanoapp from file %s: %s", mFilename.c_str(),
         dlerror());
  } else {
    mAppInfo = static_cast<const struct chreNslNanoappInfo *>(
        dlsym(mDsoHandle, CHRE_NSL_DSO_NANOAPP_INFO_SYMBOL_NAME));
    if (mAppInfo == nullptr) {
      LOGE("Failed to find app info symbol in %s: %s", mFilename.c_str(),
           dlerror());
    } else {
      // TODO(b/120778991): reenable this check after adding support for passing
      // in the .napp_header to the simulator
      // success = validateAppInfo(0 /* skip ID validation */, 0, mAppInfo);
      success = true;
      if (!success) {
        mAppInfo = nullptr;
      } else {
        LOGI("Nanoapp loaded: %s (0x%016" PRIx64 ") version 0x%" PRIx32
             " uimg %d system %d from file %s",
             mAppInfo->name, mAppInfo->appId, mAppInfo->appVersion,
             mAppInfo->isTcmNanoapp, mAppInfo->isSystemNanoapp,
             mFilename.c_str());
        if (mAppInfo->structMinorVersion >=
            CHRE_NSL_NANOAPP_INFO_STRUCT_MINOR_VERSION) {
          LOGI("Nanoapp permissions: 0x%" PRIx32, mAppInfo->appPermissions);
        }
      }
    }
  }

  return success;
}

void PlatformNanoappBase::closeNanoapp() {
  if (mDsoHandle != nullptr) {
    mAppInfo = nullptr;
    if (dlclose(mDsoHandle) != 0) {
      LOGE("dlclose failed: %s", dlerror());
    }
    mDsoHandle = nullptr;
  } else if (mIsWASM) {
    wasm_runtime_destroy_exec_env(mWASMHandle.ExecEnv);
    wasm_runtime_deinstantiate(mWASMHandle.WASMModuleInstance);
    wasm_runtime_unload(mWASMHandle.WASMModule);
    wasm_runtime_free(mWASMHandle.WASMFileBuf);
    mIsWASM = false;
    mWASMHandle.ExecEnv = nullptr;
    mWASMHandle.WASMModuleInstance = nullptr;
    mWASMHandle.WASMModule = nullptr;
    mWASMHandle.WASMFileBuf = nullptr;
  }
}

}  // namespace chre
