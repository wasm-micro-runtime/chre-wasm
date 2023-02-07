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

#ifndef CHRE_PLATFORM_LINUX_PLATFORM_NANOAPP_BASE_H_
#define CHRE_PLATFORM_LINUX_PLATFORM_NANOAPP_BASE_H_

#include <cstdint>
#include <string>

#include "chre/platform/shared/nanoapp_support_lib_dso.h"
#include "wasm_export.h"
namespace chre {

/**
 * Linux-specific nanoapp functionality.
 */
class PlatformNanoappBase {
 public:
  /**
   * Associate this Nanoapp with a nanoapp included in a .so that is pre-loaded
   * onto the filesystem. Actually loading the .so into memory is done when
   * start() is called.
   *
   * @param filename The name of the .so file in /vendor/lib/dsp that holds this
   *        nanoapp. This string is not deep-copied, so the memory must remain
   *        valid for the lifetime of this Nanoapp instance.
   */
  void loadFromFile(const std::string &filename);

  /**
   * Associate this Nanoapp instance with a nanoapp that is statically built
   * into the CHRE binary with the given app info structure.
   */
  void loadStatic(const struct chreNslNanoappInfo *appInfo);

  /**
   * @return true if the app's binary data is resident in memory, i.e. a
   *         previous call to loadFromBuffer() or loadStatic() was successful
   */
  bool isLoaded() const;

 protected:
  //! The app ID we received in the metadata alongside the nanoapp binary. This
  //! is also included in (and checked against) mAppInfo.
  uint64_t mExpectedAppId;

  //! The dynamic shared object (DSO) handle returned by dlopen.
  void *mDsoHandle = nullptr;

  //! Pointer to the app info structure within this nanoapp
  const struct chreNslNanoappInfo *mAppInfo = nullptr;

  bool mIsStatic = false;

  //! If this is a pre-loaded, but non-static nanoapp (i.e. loaded from
  //! loadFromFile), this will be set to the filename string to pass to dlopen()
  std::string mFilename;

  /**TODO_FOR_LJQ */
  //! Flag used to check whether it is Wasm naoapp
  bool mIsWASM = false;
  struct WASMhandle {
    //! The buffer storing Wasm file
    uint8_t *WASMFileBuf = nullptr;
    
    //! The size of the buffer stroring Wasm file
    uint32_t WASMFileSize;

    //! The Wasm module
    wasm_module_t WASMModule = nullptr;
    
    //! The Wasm module instance instantiating from Wasm module
    wasm_module_inst_t WASMModuleInstance = nullptr;

    //! The execution environment related to Wasm module instance
    wasm_exec_env_t ExecEnv = nullptr;

    //! The stack size of the Wasm moudle instance
    uint32_t StackSize = 16 * 1024;
    
    //! The heap size of the Wasm module instance
    uint32_t HeapSize = 16 * 1024;
    
    //! The Wasm funcion pointer to nanoappStart
    wasm_function_inst_t nanoappStartFromWASM;
    
    //! The Wasm funcion pointer to nanoappHandleEvent
    wasm_function_inst_t nanoappHandleEventFromWASM;
    
    //! The Wasm funcion pointer to nanoappEnd
    wasm_function_inst_t nanoappEndFromWASM;
  } mWASMHandle;
  
  /**
   * Calls through to openNanoappFromFile if the nanoapp was loaded from a
   * shared object or returns true if the nanoapp is static.
   *
   * @return true if the nanoapp was loaded successfully.
   */
  bool openNanoapp();

  /**
   * Calls through to openNanoappFromWASMFile or openNanoappFromDLLFile
   * by the app filename, fetches and validates the app info pointer.
   * This will result in execution of any on-load handlers in the nanoapp.
   */
  bool openNanoappFromFile();

  /**
   * Use WAMR to load a Wasm nanoapp by the app filename, fetches and
   * validates the app info pointer. This will result in execution of any
   * on-load handlers in the nanoapp.
   *
   * @return true if the app was opened successfully and the app info
   *         structure passed validation
   */
  bool openNanoappFromWASMFile();

  /**
   * Calls dlopen on the app filename, and fetches and validates the app info
   * pointer. This will result in execution of any on-load handlers (e.g.
   * static global constructors) in the nanoapp.
   *
   * @return true if the app was opened successfully and the app info
   *         structure passed validation
   */
  bool openNanoappFromDLLFile();
  /**
   * Releases the DSO handle if it was active, by calling dlclose(). This will
   * result in execution of any unload handlers in the nanoapp.
   */
  void closeNanoapp();
};

}  // namespace chre

#endif  // CHRE_PLATFORM_LINUX_PLATFORM_NANOAPP_BASE_H_
