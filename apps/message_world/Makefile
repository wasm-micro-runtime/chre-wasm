#
# Message World Nanoapp Makefile
#

# Environment Checks ###########################################################

ifeq ($(CHRE_PREFIX),)
$(error "The CHRE_PREFIX environment variable must be set to a path to the \
         CHRE project root. Example: export CHRE_PREFIX=$$HOME/chre")
endif

# Nanoapp Configuration ########################################################

NANOAPP_NAME = message_world
NANOAPP_ID = 0x01234567890000A1
NANOAPP_VERSION = 0x00000001

# Defines
COMMON_CFLAGS += -DNANOAPP_MINIMUM_LOG_LEVEL=CHRE_LOG_LEVEL_DEBUG

NANOAPP_NAME_STRING = \"MESSAGE\ World\"
# Common Compiler Flags ########################################################

COMMON_CFLAGS += -I.

# Common Source Files ##########################################################

COMMON_SRCS += message_world.cc

# Makefile Includes ############################################################

include $(CHRE_PREFIX)/build/nanoapp/wasm_app.mk
