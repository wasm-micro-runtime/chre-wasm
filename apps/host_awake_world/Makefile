#
# Host Awake World Nanoapp Makefile
#

# Environment Checks ###########################################################

ifeq ($(CHRE_PREFIX),)
ifneq ($(ANDROID_BUILD_TOP),)
CHRE_PREFIX = $(ANDROID_BUILD_TOP)/system/chre
else
$(error "You must run 'lunch' to setup ANDROID_BUILD_TOP, or explicitly define \
         the CHRE_PREFIX environment variable to point to the CHRE root \
         directory.")
endif
endif

# Nanoapp Configuration ########################################################

NANOAPP_NAME = host_awake_world
NANOAPP_ID = 0x012345678900000d
NANOAPP_VERSION = 0x00000001

NANOAPP_NAME_STRING = \"Host\ Awake\ World\"
NANOAPP_IS_SYSTEM_NANOAPP = 1
NANOAPP_VENDOR_STRING = \"Intel\"
# Common Compiler Flags ########################################################

COMMON_CFLAGS += -I.

# Defines
COMMON_CFLAGS += -DNANOAPP_MINIMUM_LOG_LEVEL=CHRE_LOG_LEVEL_DEBUG

# Common Source Files ##########################################################

COMMON_SRCS += host_awake_world.cc

# Makefile Includes ############################################################

include $(CHRE_PREFIX)/build/nanoapp/wasm_app.mk
