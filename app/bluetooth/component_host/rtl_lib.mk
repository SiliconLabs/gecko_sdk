################################################################################
# Real-Time Locationing library component                                      #
################################################################################

ifeq (, $(filter $(MAKECMDGOALS), clean export help))
  ifeq (, $(filter $(UNAME), darwin linux))
    ifneq ($(CC), x86_64-w64-mingw32-gcc)
      $(error Toolchain not supported by RTL lib.)
    endif
  endif
endif

RTL_DIR = $(SDK_DIR)/util/silicon_labs/aox
LIBNAME := aox_static

override INCLUDEPATHS += $(RTL_DIR)/inc

override CFLAGS += -DRTL_LIB

ifeq ($(OS),posix)
override LDFLAGS += \
-L$(RTL_DIR)/lib/release/gcc/$(UNAME_M)/$(UNAME) \
-l$(LIBNAME) \
-lm \
-lstdc++ \
-lpthread
else
override LDFLAGS += \
"$(RTL_DIR)/lib/release/gcc/$(UNAME_M)/windows/lib$(LIBNAME).a" \
-lstdc++ \
-lpthread
endif

PROJ_FILES += $(wildcard $(RTL_DIR)/lib/release/gcc/*/*/lib$(LIBNAME).a)
