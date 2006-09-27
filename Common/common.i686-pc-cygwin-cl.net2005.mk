
### Binaries #######################################################

CC_PATH    := /cygdrive/c/Program Files/Microsoft Visual Studio 8/VC/bin

CC         := "$(CC_PATH)/cl.exe" 

LD_SHARED  := "$(CC_PATH)/link.exe" -dll -map

LD_LNK     := "$(CC_PATH)/link" -lib -NODEFAULTLIB

RANLIB     := 

LD         := "$(CC_PATH)/link.exe"

FLEX       := flex.exe
BISON      := bison.exe 

SUB_MAKE   := make

LINK       := cp

SED        := sed

### Patterns #########################################################

ifeq ($(OS_BASE), cygwin)
ifneq ($(DBGCMDGOAL),)
$(warning Detected OPT)
DEBUG_CHAR:=
else
$(warning Detected DBG)
DEBUG_CHAR:=D
endif
endif

COMPILER_LOGO        := 
PEDANTIC_ERRORS      := 0

SO_PRAEFIX           := 
SO_SEARCH_SUFFIX     := .dll
SO_SUFFIX            := $(DEBUG_CHAR).dll
LIB_SEARCH_SUFFIX    := .lib
LIB_SUFFIX           := $(DEBUG_CHAR).lib

LNK_LIB_SUFFIX       := $(DEBUG_CHAR)Lnk.lib

OBJ_SUFFIX           := .obj
EXE_SUFFIX           := .exe


OS_BASE              := cygwin
OS_CMPLR             := cl.net
OS_CMPLR_DEF         := cl.net2005.ms_stl
MS_COMPILER_VERSION  := vs8



LIBDIR_BASE          := lib
OBJDIR_BASE          := obj
EXEDIR_BASE          := exe

TEST_SRC_PATTERN     := test%.cpp

INC_OPTION           := -I

MAK_SUFFIX           := .mk
DEP_SUFFIX           := .d

INCL_$(OS_BASE)      :=
INCL_$(OS_BASE)_DEP  :=
INCL_EXP_$(OS_BASE)  :=
LIBS_$(OS_BASE)      :=
OSG_LIB_EXT          := 

CONFIGURED_QT           :=0
CONFIGURED_GLUT         :=1
CONFIGURED_STLPORT      :=0
CONFIGURED_GLUT         :=1
CONFIGURED_JPG          :=1
CONFIGURED_TIF          :=1
CONFIGURED_PNG          :=1
CONFIGURED_MNG          :=0
CONFIGURED_FREETYPE     :=@ac_gdz_conf_package_freetype1_e1@
CONFIGURED_TEXT         :=0
CONFIGURED_PACKAGE_DEFS := -DOSG_WITH_GLUT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF

CONFIGURED_GVBETA       :=0



LIBPATH_OPTION       := -LIBPATH:
LIBLNK_OPTION        := 

OBJ_OPTION           := -Fo

NO_STDINC_DEP_OPTION := -X

COMPONLY_OPTION      := -c

DEPEND_OPTION        := -QM -nologo

LD_OUTOPT            := -out:

LNK_LD_OUTOPT        := -out:

DIR_SEP              := /

II_FILESDIR          := 

### Defines #######################################################

COMPILERVERSION := $(shell $(CC) 2>&1 | head -1 | cut -d' ' -f 8)
COMPILERMAJORVERSION := $(shell $(CC) 2>&1 | head -1 | cut -d' ' -f 8 | sed -e 's/\..*//')

ifeq ($(CONFIGURED_GVBETA),1)
DEF_GVBETA := -DOSG_GV_BETA
else
DEF_GVBETA :=
endif

# For QT
QT_PLATTFORMDEF := -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT        \
                   -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG

SOURCE_DEFINES   := $(CONFIGURED_PACKAGE_DEFS)

SYSTEM_DEFINES   := -DWIN32 -D_WINDOWS 				                 \
				    -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 	     \
                    -D_WIN32_WINNT=0x0400                            \
                    -D_OSG_HAVE_CONFIGURED_H_                        \
                    $(DEF_GVBETA)
#-D_HAS_EXCEPTIONS=0

#ifeq ($(COMPILERVERSION),501)
#SYSTEM_DEFINES   := $(SYSTEM_DEFINES) -DOSG_SUPPORT_NO_GEO_INTERFACE=1
#endif

ifeq ($(LNK),lnk)
RUNTIME_DEFINES  = 
else
RUNTIME_DEFINES  = -DOSG_BUILD_DLL 
endif


### Warnings #######################################################

WARNINGS	   		:= -W3

WARNINGS_C_OFF		:= 

# 4049 compiler limit : terminating line number emission
# 4065 switch statement contains 'default' but no 'case' labels
# 4099 'identifier' : type name first seen using 'objecttype1' now 
#      seen using 'objecttype2'
# 4231 nonstandard extension used : 'identifier' before template 
#      explicit instantiation
# 4250 'class1' : inherits 'class2::member' via dominance
# 4251 'identifier' : class 'type' needs to have dll-interface to be used by 
#       clients of class 'type2'
# 4275 non – DLL-interface classkey 'identifier' used as base for 
#      DLL-interface classkey 'identifier'
# 4355 'this' : used in base member initializer list
# 4996 'sprintf' was declared deprecated (also for many other C functions)

WARNINGS_CPP_OFF 	:= $(WARNINGS_C_OFF) -w44049 -w44065 \
						-w44251 -w44275 -w44099 -w44250 -w44231 \
                        -w44290 -w44996

WARN_ERR_CPP        :=

### Language #######################################################

LANG_FLAGS          = 

#-Qvc6 -Qansi
#-GX
ifeq ($(COMPILERMAJORVERSION), 14)
# Cl.net 2005 options
COMPILER    		=  -EHsc -FD -GR -Zm1200

# Need to have the Framework SDK
# Yes, this is a hack
LIBPATHS_$(OS_BASE) := $(LIBPATH_OPTION)"C:\Program Files\Microsoft Platform SDK\Lib"   $(LIBPATHS_$(OS_BASE))
INCL_$(OS_BASE) := $(INC_OPTION)"C:\Program Files\Microsoft Platform SDK\Include"   $(INCL_$(OS_BASE))

else
# other cl.net options
COMPILER    		=  -GX -FD -GR -Zm1200
endif

ifeq ($(LNK),lnk)
COMPILER_RUNTIME_DBG    = -MTd
COMPILER_RUNTIME_OPT    = -MT
else
COMPILER_RUNTIME_DBG    = -MDd
COMPILER_RUNTIME_OPT    = -MD
endif

CCFLAGS_EXT_OPT  := -O2 -Ob1 -MD
ifeq ($(COMPILERMAJORVERSION), 14)
# Cl.net 2005 options
CCFLAGS_EXT_DBG  := -ZI -Od -RTC1 -D_DEBUG -DOSG_DEBUG -MDd
else
# other cl.net options
CCFLAGS_EXT_DBG  := -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd
endif

### Optimize / Debug ###############################################

ifeq ($(PRINT_INLINE), 1)
COMP_INLINE :=
endif

ifeq ($(DEBUG_VERSION), 0)
	COMP_OPTIMIZE    =  -O2 -Ob1
	COMP_DEBUG       = 
        COMPILER_RUNTIME = $(COMPILER_RUNTIME_OPT)
else
	COMP_OPTIMIZE    =
ifeq ($(COMPILERMAJORVERSION), 14)
# Cl.net 2005 options
	COMP_DEBUG       =  -ZI -Od -D_DEBUG -DOSG_DEBUG
else
# other cl.net options
	COMP_DEBUG       =  -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG
endif
        COMPILER_RUNTIME = $(COMPILER_RUNTIME_DBG)
endif

### Compiler Flags ################################################


DEFINES     = $(SOURCE_DEFINES) $(SYSTEM_DEFINES) $(RUNTIME_DEFINES)    \
              $(QT_PLATTFORMDEF)

# C Compiler Flags

CFLAGS   := $(WARNINGS) $(WARNINGS_C_OFF) -D__STDC__ 						\
		    $(DEFINES) $(COMPILER) $(COMPILER_RUNTIME)                      \
            $(COMP_OPTIMIZE) $(COMP_DEBUG)

# CPP Compiler Flags

CCFLAGS  := $(WARNINGS) $(WARNINGS_CPP_OFF) $(WARN_ERR_CPP) $(DEFINES)      \
		    $(COMPILER) $(COMPILER_RUNTIME) $(COMP_OPTIMIZE) $(COMP_DEBUG)  \
            $(COMPILER_LOGO)

CCFLAGS_EXT         := $(WARNINGS_CPP_OFF) $(WARN_ERR_CPP) $(SYSTEM_DEFINES) $(RUNTIME_DEFINES) $(COMPILER)
QT_PLATTFORMDEF_EXT := $(QT_PLATTFORMDEF)

# Assembler Flags

ASFLAGS  := $(WARNINGS) $(WARNINGS_C_OFF) $(DEFINES) 	\
	 	    $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) 


# Linker Flags

ifeq ($(PRINT_INLINE), 1)
LINK_INLINE :=
endif

ifeq ($(DEBUG_VERSION), 0)
	LINK_OPTIMIZE    = 
	AR_FLAGS         = 
	LINK_DEBUG       = 
else
	LINK_OPTIMIZE    =
	AR_FLAGS         = -Debug
	LINK_DEBUG       = -Debug 
endif

# added -FORCE:MULTIPLE because of multiple defined symbols in the Experimental/QTWidgets code,
# looks like a compiler bug?
LD_FLAGS += $(COMPILER_LOGO) -NODEFAULTLIB $(LINK_OPTIMIZE) $(LINK_DEBUG) -FORCE:MULTIPLE

LD_FLAGS_EXT     := -NODEFAULTLIB
LD_FLAGS_EXT_OPT := 
LD_FLAGS_EXT_DBG := -Debug








### BASE DIRS #########################################################

INCL_$(OS_BASE) := $(INC_OPTION)"..\Base" $(INCL_$(OS_BASE))
INCL_$(OS_BASE)_DEP := $(INC_OPTION)"..\Base" $(INCL_$(OS_BASE_DEP))
LIBS_$(OS_BASE) := user32.lib kernel32.lib MSVCPRT$(DEBUG_CHAR).lib MSVCRT$(DEBUG_CHAR).lib winmm.lib wsock32.lib oldnames.lib 

INCLUDE_SYSTEM  := 
LINK_SYSTEM     := 

ADD_INCLUDE     := /p/COVR-SIG/Software/OpenSG-Support.net/include:/p/COVR-SIG/Software/OpenSG-Support.net/Boost/include/boost-1_33_1
ADD_LINK        := /p/COVR-SIG/Software/OpenSG-Support.net/lib
ADD_LIBS        := 
ADD_DEFS        := 

include /c/user/gerrit/Projects/OpenSG/svn/OpenSG/Builds/i686-pc-cygwin-cl.net2005/CommonPackages/commonSTL.mk


LINK_COMPILER   := 

ifneq ($(INCLUDE_SYSTEM),)
INCL_$(OS_BASE) := $(INCL_$(OS_BASE)) $(INC_OPTION)$(INCLUDE_SYSTEM)
endif

ifneq ($(LINK_SYSTEM),)
LIBPATHS_$(OS_BASE) := $(LIBPATH_OPTION)$(LINK_SYSTEM)   $(LIBPATHS_$(OS_BASE))
endif

ifneq ($(LINK_COMPILER),)
LIBPATHS_$(OS_BASE) := $(LIBPATH_OPTION)$(LINK_COMPILER) $(LIBPATHS_$(OS_BASE))
endif

#########################################################################
# Build include directive
#########################################################################

ifeq ($(OS_BASE), cygwin)
ifeq ($(OS_CMPLR),g++)
buildCIncPath      = $(INC_OPTION)$(1) 
else
buildCIncPath      = $(INC_OPTION)"$(shell cygpath -w $(1))"
buildCIncPathDep   = $(INC_OPTION)"$(shell cygpath -u $(1))"
endif
else
buildCIncPath      = $(INC_OPTION)$(1) 
buildCIncPathDep   = $(INC_OPTION)$(1) 
endif

ifeq ($(OS_BASE), cygwin)
buildCLibPath      = $(LIBPATH_OPTION)"$(shell cygpath -w $(1))"
else
buildCLibPath      = $(LIBPATH_OPTION)$(1)
endif

ifneq ($(ADD_INCLUDE),)

ADD_INCLUDE := $(subst :, ,$(ADD_INCLUDE))

ADD_INCL_$(OS_BASE) := \
	$(foreach dir,$(ADD_INCLUDE),$(call buildCIncPath,$(dir)))

INCL_$(OS_BASE) := $(INCL_$(OS_BASE)) $(ADD_INCL_$(OS_BASE))

ADD_INCL_$(OS_BASE)_DEP := \
	$(foreach dir,$(ADD_INCLUDE),$(call buildCIncPathDep,$(dir)))

INCL_$(OS_BASE)_DEP := $(INCL_$(OS_BASE)_DEP) $(ADD_INCL_$(OS_BASE)_DEP)

endif

ifneq ($(ADD_LINK),)

ADD_LINK := $(subst :, ,$(ADD_LINK))

ADD_LIBPATHS_$(OS_BASE) := \
	$(foreach dir,$(ADD_LINK),$(call buildCLibPath,$(dir)))

LIBPATHS_$(OS_BASE) := $(LIBPATHS_$(OS_BASE)) $(ADD_LIBPATHS_$(OS_BASE))

endif

ifneq ($(ADD_LIBS),)

ADD_LIBS := $(subst :, ,$(ADD_LIBS))

ifeq ($(OS_BASE),cygwin)
ADD_LIBS_$(OS_BASE) := $(foreach lib,$(ADD_LIBS),$(lib)$(LIB_SUFFIX))
else
ADD_LIBS_$(OS_BASE) := $(foreach lib,$(ADD_LIBS),$(LIBLNK_OPTION)$(lib))
endif

LIBS_$(OS_BASE) := $(ADD_LIBS_$(OS_BASE)) $(LIBS_$(OS_BASE))

endif

ifneq ($(ADD_DEFS),)

ADD_DEFS := $(subst :, ,$(ADD_DEFS))

ADD_DEFS_$(OS_BASE) := $(foreach def,$(ADD_DEFS),-D$(def))

CCFLAGS     := $(CCFLAGS)     $(ADD_DEFS_$(OS_BASE))
CCFLAGS_EXT := $(CCFLAGS_EXT) $(ADD_DEFS_$(OS_BASE))

endif

LIBS_$(OS_BASE) := $(LIBS_$(OS_BASE)) $(ADD_OS_LIB)
