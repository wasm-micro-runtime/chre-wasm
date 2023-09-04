#
# Google Reference CHRE Implementation for Linux on x86
#

include $(CHRE_PREFIX)/build/clean_build_template_args.mk

TARGET_NAME = intel_wasm32_linux
TARGET_CFLAGS = -DCHRE_MESSAGE_TO_HOST_MAX_SIZE=2048
TARGET_VARIANT_SRCS = $(INTEL_WASM_LINUX_SRCS)
TARGET_BIN_LDFLAGS = $(INTEL_WASM_LINUX_BIN_LDFLAGS)
TARGET_SO_EARLY_LIBS = $(INTEL_WASM_LINUX_EARLY_LIBS)
TARGET_SO_LATE_LIBS = $(INTEL_WASM_LINUX_LATE_LIBS)
TARGET_PLATFORM_ID = 0x476f6f676c000001
TARGET_CFLAGS += -DCHRE_FIRST_SUPPORTED_API_VERSION=CHRE_API_VERSION_1_1
# We don't these file when building wasm nanoapp
#TARGET_CFLAGS += $(SIM_CFLAGS)
#TARGET_VARIANT_SRCS += $(SIM_SRCS)

# Enable conversion warnings for the simulator. Since this is a platform 100%
# within our control we expect that there will be no conversion issues. It would
# be nice to enable this globally in the tools_config.mk but some vendor header
# files do not compile cleanly with it.
TARGET_CFLAGS += -Wconversion

# Add the target CFLAGS after the -Wconversion warning to allow targets to
# disable it.
TARGET_CFLAGS += $(INTEL_WASM_LINUX_CFLAGS)

ifneq ($(filter $(TARGET_NAME)% all, $(MAKECMDGOALS)),)
ifneq ($(IS_NANOAPP_BUILD),)
include $(CHRE_PREFIX)/build/nanoapp/intel_wasm.mk
else
$(error only Support building wasm nanoapp now!)
endif
include $(CHRE_PREFIX)/build/arch/wasm32.mk
# Source files.
CC_SRCS = $(filter %.cc, $(COMMON_SRCS) $(TARGET_VARIANT_SRCS))
CPP_SRCS = $(filter %.cpp, $(COMMON_SRCS) $(TARGET_VARIANT_SRCS))
C_SRCS = $(filter %.c, $(COMMON_SRCS) $(TARGET_VARIANT_SRCS))

# Object files.
CC_OBJS = $(patsubst %.cc, %.o, \
                           $(CC_SRCS))
CPP_OBJS = $(patsubst %.cpp, %.o, \
                            $(CPP_SRCS))
C_OBJS = $(patsubst %.c, %.o, \
							$(C_SRCS))

# compile
#C_COMPILE:
#	$(TARGET_CC) -c --target=wasm32-wasi $(TARGET_CFLAGS) $(COMMON_C_FLAGS) $(COMMON_CFLAGS) $(C_SRCS)
#CPP_COMPILE:
#	$(TARGET_CPP_C) -c --target=wasm32-wasi $(TARGET_CFLAGS) $(COMMON_CXX_FLAGS) $(COMMON_CFLAGS) $(CC_SRCS) $(CPP_SRCS)

#OBJS = $(CC_OBJS) $(CPP_OBJS) $(C_OBJS)
#$(info $(TARGET_CC))
#$(TARGET_NAME):C_COMPILE CPP_COMPILE
$(TARGET_NAME):
	$(TARGET_CC) -o $(OUTPUT_NAME).wasm $(WASM32_CFLAGS) $(TARGET_CFLAGS) $(COMMON_CFLAGS) --std=c++17 $(CC_SRCS) $(CPP_SRCS)
#	$(TARGET_CC) -o $(OUTPUT_NAME).wasm $(WASM32_CFLAGS) $(TARGET_CFLAGS) $(COMMON_CFLAGS) $(CC_OBJS) $(CPP_OBJS) $(C_OBJS)
endif