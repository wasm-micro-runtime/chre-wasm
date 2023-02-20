#
# Build targets for an x86 processor
#

# wasm32 Environment Checks #######################################################

ifeq ($(ANDROID_BUILD_TOP),)
$(error "You should supply an ANDROID_BUILD_TOP environment variable \
         containing a path to the Android source tree. This is typically \
         provided by initializing the Android build environment.")
endif
export WASM32_TOOLS_PREFIX=/opt/wasi-sdk/bin/

# wasm32 Tools ####################################################################

TARGET_CC  = $(WASM32_TOOLS_PREFIX)clang++

# wasm Compiler Flags ###########################################################

WASM32_CFLAGS += --target=wasm32-wasi
WASM32_CFLAGS += -O0
WASM32_CFLAGS += -z stack-size=4096
WASM32_CFLAGS += -Wl,--initial-memory=65536
WASM32_CFLAGS += -Wl,--strip-all,--no-entry
WASM32_CFLAGS += -nostdlib
WASM32_CFLAGS += --sysroot=/opt/wasi-sdk/share/wasi-sysroot
WASM32_CFLAGS += -Wl,--export=nanoappStart
WASM32_CFLAGS += -Wl,--export=nanoappEnd
WASM32_CFLAGS += -Wl,--export=nanoappHandleEvent
WASM32_CFLAGS += -Wl,--export=getnanoappHandleEvent
WASM32_CFLAGS += -Wl,--export=getNanoappInfo
WASM32_CFLAGS += -Wl,--allow-undefined

# Add WASM32 compiler flags.
TARGET_CFLAGS += $(WASM32_CFLAGS)

# x86 is purely used for testing, so always include debugging symbols
TARGET_CFLAGS += -g

# Enable position independence.
TARGET_CFLAGS += -fpic

# Disable double promotion warning for logging
TARGET_CFLAGS += -Wno-double-promotion

# Optimization Level ###########################################################

TARGET_CFLAGS += -O$(OPT_LEVEL)

# Variant Specific Sources #####################################################

#TARGET_VARIANT_SRCS += $(X86_SRCS)
