
SUB_DIR     := WindowSystem/Cocoa
PACKAGENAME := WindowSystemCocoa

INCL_DIR    := $($(PROJ)POOL)/$(SUB_DIR)

HAS_INCL    := 1
HAS_LIB     := 

REQUIRED_SYSTEM_PACKAGES :=

include $($(PROJ)POOL)/$($(PROJ)COMMON)/commonPackage.mk

