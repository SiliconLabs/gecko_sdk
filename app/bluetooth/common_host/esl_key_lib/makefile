################################################################################
# General project settings                                                     #
################################################################################

PROJECTNAME = esl_key_lib
SDK_DIR = ../../../..

################################################################################
# Components                                                                   #
#                                                                              #
# After setting up the toolchain, components can contribute to the project by  #
# appending items to the project variables like INCLUDEPATHS or C_SRC.         #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/toolchain.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk

################################################################################
# Include paths                                                                #
################################################################################

override INCLUDEPATHS += . \
$(SDK_DIR)/util/third_party/sqlite \
$(SDK_DIR)/app/bluetooth/common_host/system \
$(SDK_DIR)/platform/common/inc \
$(SDK_DIR)/protocol/bluetooth/inc \
$(SDK_DIR)/app/bluetooth/common/esl_tag_core/inc \
$(SDK_DIR)/app/bluetooth/common/esl_tag_core/config \
$(SDK_DIR)/app/bluetooth/common_host/ncp_host \
$(SDK_DIR)/app/bluetooth/common/ead_core \

################################################################################
# Input files                                                                  #
################################################################################

override C_SRC += \
esl_key_lib.c \
$(SDK_DIR)/util/third_party/sqlite/sqlite3.c

################################################################################
# Target rules                                                                 #
################################################################################

EXE_DIR = lib

override CFLAGS += -fPIC -static

ifeq (, $(filter $(UNAME), darwin))
override CFLAGS += -shared
endif

override LDFLAGS += -shared -fPIC

ifeq (, $(filter $(UNAME), darwin linux))
    EXT := .dll
    override CFLAGS += -static-libgcc -DWIN_DLL
else ifeq (, $(filter $(UNAME), linux))
    EXT := .dylib
    override LDFLAGS += -lpthread -ldl -lc
else
    EXT := .so
    override LDFLAGS += -lpthread -ldl -lc
endif

################################################################################
# Common target rules                                                          #
################################################################################

.SUFFIXES:				# ignore builtin rules
.PHONY: all debug release clean clean_export clean_keep_sql export help

# Default directories
OBJ_DIR ?= obj
EXE_DIR ?= exe
EXPORT_DIR ?= export

CFLAGS_DEBUG ?= -O0 -g3
CFLAGS_RELEASE ?= -DNDEBUG \
-DAPP_LOG_CONFIG_H -DAPP_LOG_ENABLE=0 \
-DAPP_LOG_LEVEL_FILTER_ENABLE=0 \
-DAPP_LOG_LEVEL_FILTER_THRESHOLD=0 \
-DAPP_LOG_LEVEL_MASK_ENABLE=0 \
-DAPP_LOG_LEVEL_MASK_DEBUG=0 \
-DAPP_LOG_LEVEL_MASK_INFO=0 \
-DAPP_LOG_LEVEL_MASK_WARNING=0 \
-DAPP_LOG_LEVEL_MASK_ERROR=0 \
-DAPP_LOG_LEVEL_MASK_CRITICAL=0

HELP_MESSAGE += \
"Available build targets for $(PROJECTNAME)\n" \
"  debug          - default target, optimized for debugging\n" \
"  release        - build with defult compiler optimization\n" \
"  clean          - remove build directories\n" \
"  clean_keep_sql - remove build directories but keep sqlite3 files\n" \
"  export         - copy all project resources into '$(EXPORT_DIR)' directory\n" \
"  help           - print this help message\n"

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
	ctypesgen --no-gnu-types --allow-gnu-c --no-macro-warnings $(INCFLAGS) $(PROJECTNAME).h -o $(PROJECTNAME)_wrapper.py 2> /dev/null
	@echo "Fixing up Python wrapper"
	../../script/ctypesgen_wrapper_fix.py $(PROJECTNAME)_wrapper.py -v

clean: clean_export
ifeq ($(filter $(MAKECMDGOALS),all debug release export),)
	rm -rf $(OBJ_DIR) $(EXE_DIR)
	rm -f $(PROJECTNAME)_wrapper.py
endif

clean_keep_sql: clean_export
ifeq ($(filter $(MAKECMDGOALS),all debug release export),)
	find $(OBJ_DIR) ! \( -type f -and -iname "sqlite3.*" \) -delete || true
	rm -rf $(EXE_DIR)
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
