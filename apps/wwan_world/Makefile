#
# WWAN World Nanoapp Makefile
#

# Environment Checks ###########################################################

ifeq ($(CHRE_PREFIX),)
$(error "The CHRE_PREFIX environment variable must be set to a path to the \
         CHRE project root. Example: export CHRE_PREFIX=$$HOME/chre")
endif

# Nanoapp Configuration ########################################################

NANOAPP_NAME = wwan_world
NANOAPP_ID = 0x01234567890000F6
NANOAPP_VERSION = 0x00000000

NANOAPP_NAME_STRING = \"WWAN\ World\"
# Common Compiler Flags ########################################################

COMMON_CFLAGS += -I.

COMMON_CFLAGS += -DNANOAPP_MINIMUM_LOG_LEVEL=CHRE_LOG_LEVEL_DEBUG
COMMON_CFLAGS += -DLOG_TAG=\"[WwanWorld]\"
# Common Source Files ##########################################################

COMMON_SRCS += wwan_world.cc

# Permission declarations ######################################################

CHRE_NANOAPP_USES_WWAN = true

# Makefile Includes ############################################################

include $(CHRE_PREFIX)/build/nanoapp/app.mk
