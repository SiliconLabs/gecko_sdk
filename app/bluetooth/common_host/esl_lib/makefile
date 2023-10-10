################################################################################
# General project settings                                                     #
################################################################################

PROJECTNAME = esl_lib
SDK_DIR = ../../../..

# Enable security for ESL C LIB NCP by default
# It can be disabled by assigning zero value to the SECURITY variable
# e.g. via command line like 'make SECURITY=0'.
# If enabled, make sure that openssl is available in your environment.
SECURITY ?= 1

ifneq (, $(filter $(MAKECMDGOALS), export))
# Collect all resources when exporting.
MEMCHECK_DEFAULT = 1
else
MEMCHECK_DEFAULT = 0
endif

# Memory leak check is disabled by default. Enable it like this: make MEMCHECK=1
MEMCHECK ?= $(MEMCHECK_DEFAULT)

# Security related settings
ifneq ($(SECURITY), 0)
  # Suppress OpenSSL 3.0 warnings until proper update is made on ncp_sec
  override CFLAGS += -DOPENSSL_API_COMPAT=0x10101000L
  # Override some secure NCP host component default settings
  override CFLAGS += -DPEEK_US_SLEEP=1
  override CFLAGS += -DRECV_FUNC_US_SLEEP=1
  override CFLAGS += -DMSG_RECV_TIMEOUT_MS=2
endif

# NCP config override
override CFLAGS += -DDEFAULT_HOST_BUFLEN=16384

################################################################################
# Components                                                                   #
#                                                                              #
# After setting up the toolchain, components can contribute to the project by  #
# appending items to the project variables like INCLUDEPATHS or C_SRC.         #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/toolchain.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_assert.mk
include $(SDK_DIR)/app/bluetooth/component_host/ncp_host_bt.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_timer.mk
include $(SDK_DIR)/app/bluetooth/component_host/slist.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_queue.mk
include $(SDK_DIR)/app/bluetooth/component_host/l2cap_transfer.mk
include $(SDK_DIR)/app/bluetooth/component_host/ots_client.mk
include $(SDK_DIR)/app/bluetooth/component_host/ncp_version.mk


################################################################################
# Include paths                                                                #
################################################################################

override INCLUDEPATHS += . \
$(SDK_DIR)/app/bluetooth/common_host/system \
$(SDK_DIR)/platform/common/inc \
$(SDK_DIR)/protocol/bluetooth/inc


################################################################################
# Input files                                                                  #
################################################################################

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common_host/system/system.c \
esl_lib.c \
esl_lib_core.c \
esl_lib_image_transfer.c \
esl_lib_connection.c \
esl_lib_pawr.c \
simple_argparse.c \
esl_lib_command_list.c \
esl_lib_event_list.c \
esl_lib_ap_control.c \
esl_lib_storage.c \
esl_lib_log.c
ifneq ($(MEMCHECK), 0)
override C_SRC += esl_lib_memory.c
endif

################################################################################
# Target rules                                                                 #
################################################################################

EXE_DIR = lib

ifeq (, $(filter $(UNAME), darwin linux))
    EXT := .dll
else ifeq (, $(filter $(UNAME), linux))
    EXT := .dylib
else
    EXT := .so
endif

override CFLAGS += -fPIC

ifneq ($(MEMCHECK), 0)
override CFLAGS += -DESL_LIB_MEMORY_LEAK_CHECK
endif

ifeq (, $(filter $(UNAME), darwin))
override CFLAGS += -shared
endif

override LDFLAGS += -shared \
-fPIC \
-lpthread

################################################################################
# Common target rules                                                          #
################################################################################

.SUFFIXES:				# ignore builtin rules
.PHONY: all debug release clean clean_export export help

# Default directories
OBJ_DIR ?= obj
EXE_DIR ?= exe
EXPORT_DIR ?= export

CFLAGS_DEBUG ?= -O0 -g3
CFLAGS_RELEASE ?= -DNDEBUG

HELP_MESSAGE += \
"Available build targets for $(PROJECTNAME)\n" \
"  debug   - default target, optimized for debugging\n" \
"  release - build with defult compiler optimization\n" \
"  clean   - remove build directories\n" \
"  export  - copy all project resources into '$(EXPORT_DIR)' directory\n" \
"  help    - print this help message\n"

ifeq (, $(filter $(UNAME), darwin linux))
# Enable escape sequence
HELP_FLAG = -e
else
HELP_FLAG =
endif

# uniq is a function which removes duplicate elements from a list
uniq = $(strip $(if $1,$(firstword $1) \
       $(call uniq,$(filter-out $(firstword $1),$1))))

# reverse is a function that reverse the list
reverse = $(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1)))) $(firstword $(1))

INCFLAGS = $(addprefix -I, $(INCLUDEPATHS))

C_FILES = $(notdir $(C_SRC) )
C_PATHS = $(call uniq, $(dir $(C_SRC) ) )

C_OBJS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o))
C_DEPS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.d))
OBJS = $(C_OBJS)

# Project resources
INC_FILES = $(foreach dir,$(INCLUDEPATHS),$(wildcard $(dir)/*.h))
PROJ_FILES += $(call uniq, $(C_SRC) $(INC_FILES) $(MAKEFILE_LIST) $(OTHER_FILES))
TECHNOLOGY = $(word 3,$(call reverse, $(subst /, ,$(CURDIR))))
DST_DIR = $(EXPORT_DIR)/app/$(TECHNOLOGY)/example_host/$(PROJECTNAME)/
DST_FILES = $(addprefix $(DST_DIR), $(PROJ_FILES))

vpath %.c $(C_PATHS)

# Create directories and do a clean which is compatible with parallell make
$(shell mkdir $(OBJ_DIR)>$(NULLDEVICE) 2>&1)
$(shell mkdir $(EXE_DIR)>$(NULLDEVICE) 2>&1)
ifeq (clean,$(findstring clean, $(MAKECMDGOALS)))
  ifneq ($(filter $(MAKECMDGOALS),all debug release),)
    $(shell rm -rf $(OBJ_DIR)/*.*>$(NULLDEVICE) 2>&1)
    $(shell rm -rf $(EXE_DIR)/*.*>$(NULLDEVICE) 2>&1)
  endif
endif

# Default build is debug build
all:      debug

debug:    CFLAGS += $(CFLAGS_DEBUG)
debug:    $(EXE_DIR)/$(PROJECTNAME)

release:  CFLAGS += $(CFLAGS_RELEASE)
release:  $(EXE_DIR)/$(PROJECTNAME)

# Create objects from C SRC files
$(OBJ_DIR)/%.o: %.c
	@echo "Building file: $<"
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

# Link
$(EXE_DIR)/$(PROJECTNAME): $(OBJS) $(LIBS)
	@echo "Linking target: $@ for $(OS) $(UNAME) $(UNAME_M)"
	$(CC) $^ -o $@$(EXT) $(LDFLAGS)

$(PROJECTNAME)_wrapper.py: $(PROJECTNAME).h
	@echo "Generating Python wrapper"
	ctypesgen --no-gnu-types --allow-gnu-c --no-macro-warnings -I$(SDK_DIR)/platform/common/inc $(PROJECTNAME).h $(SDK_DIR)/platform/common/inc/sl_status.h -x sl_status_get_string_n -x sl_status_print -o $(PROJECTNAME)_wrapper.py  2> /dev/null
	@echo "Fixing up Python wrapper"
	../../script/ctypesgen_wrapper_fix.py $(PROJECTNAME)_wrapper.py -v

clean: clean_export
ifeq ($(filter $(MAKECMDGOALS),all debug release export),)
	rm -rf $(OBJ_DIR) $(EXE_DIR)
	rm -f $(PROJECTNAME)_wrapper.py
endif

clean_export:
	@if [ -d $(EXPORT_DIR) ]; then \
		read -p "Enter 'y' to remove '$(EXPORT_DIR)': " ans && if [ _$$ans = _y ]; then rm -rf $(EXPORT_DIR); fi \
	fi

# Collect project files for exporting
$(DST_FILES) : $(addprefix $(DST_DIR), %) : %
	@mkdir -p $(dir $@) && cp -pRv $< $@

export: $(DST_FILES)
	@echo "Exporting done."

help:
	@echo $(HELP_FLAG) $(HELP_MESSAGE)

# include auto-generated dependency files (explicit rules)
ifneq (clean,$(findstring clean, $(MAKECMDGOALS)))
-include $(C_DEPS)
endif
