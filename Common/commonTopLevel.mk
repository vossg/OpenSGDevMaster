
.SUFFIXES:	.src .prj

SUB_JOB := admin

INSTLINK := cp

#########################################################################
# Parallel Settings
#########################################################################

$(PROJ)TOPMAKEPAR :=

ifdef $(PROJ)TOPPARJOBS
ifneq ($($(PROJ)TOPPARJOBS), 0)
$(PROJ)TOPMAKEPAR = -j $($(PROJ)TOPPARJOBS)
endif
endif

$(PROJ)SUBMAKEPAR :=

ifneq ($($(PROJ)SUBPARJOBS),)
ifneq ($($(PROJ)SUBPARJOBS),0)
$(PROJ)SUBMAKEPAR = -j $($(PROJ)SUBPARJOBS)
endif
endif


SUB_MAKE      := $(MAKE) -r -k $($(PROJ)SUBMAKEPAR)

SUB_MAKEFILE  := Makefile

#########################################################################
# Normal lib Targets
#########################################################################

SUB_LIBTARGETS   := $(addsuffix .src, $(SUB_LIBS))
SUB_TESTTARGETS  := $(addsuffix .src, $(SUB_TESTS))

dbg:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile dbg_internal

dbg_internal: SUB_TARGET := dbg
dbg_internal: SUB_JOB := build
dbg_internal: $(SUB_LIBTARGETS) 

dbgLnk:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile dbg_internalLnk

dbg_internalLnk: SUB_TARGET := dbgLnk
dbg_internalLnk: SUB_JOB := build
dbg_internalLnk: $(SUB_LIBTARGETS) 

opt:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile opt_internal


opt_internal: SUB_TARGET := opt
opt_internal: SUB_JOB := build
opt_internal: $(SUB_LIBTARGETS) 

optLnk:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile opt_internalLnk


opt_internalLnk: SUB_TARGET := optLnk
opt_internalLnk: SUB_JOB := build
opt_internalLnk: $(SUB_LIBTARGETS) 

#########################################################################
# test
#########################################################################

tests: SUB_TARGET := dbg
tests: SUB_JOB := build
tests: $(SUB_TESTTARGETS)

testsOpt: SUB_TARGET := opt
testsOpt: SUB_JOB := build
testsOpt: $(SUB_TESTTARGETS)

testsLnk: SUB_TARGET := TestLnk
testsLnk: SUB_JOB := build
testsLnk: $(SUB_TESTTARGETS)

#########################################################################
# clean
#########################################################################

dbgclean: SUB_TARGET := dbgclean
dbgclean: $(SUB_LIBTARGETS)

optclean: SUB_TARGET := optclean
optclean: $(SUB_LIBTARGETS)

clean: SUB_TARGET := clean
clean: $(SUB_LIBTARGETS)

dbgcleanLnk: SUB_TARGET := dbgcleanLnk
dbgcleanLnk: $(SUB_LIBTARGETS)

optcleanLnk: SUB_TARGET := optcleanLnk
optcleanLnk: $(SUB_LIBTARGETS)

cleanLnk: SUB_TARGET := cleanLnk
cleanLnk: $(SUB_LIBTARGETS) $(SUB_TESTTARGETS)

allclean: dbgclean optclean

dbgClean: SUB_TARGET := dbgClean
dbgClean: $(SUB_LIBTARGETS) 

optClean: SUB_TARGET := optClean
optClean: $(SUB_LIBTARGETS) 

Clean: SUB_TARGET := Clean
Clean: $(SUB_LIBTARGETS) 

CleanLnk: SUB_TARGET := CleanLnk
CleanLnk: $(SUB_LIBTARGETS) $(SUB_TESTTARGETS)

LibClean: SUB_TARGET := LibClean
LibClean: $(SUB_LIBTARGETS) 

DepClean: SUB_TARGET := DepClean
DepClean: $(SUB_LIBTARGETS) 

distclean: SUB_TARGET := distclean
distclean: $(SUB_LIBTARGETS)

testsclean: SUB_TARGET := clean
testsclean: SUB_JOB := build
testsclean: $(SUB_TESTTARGETS)

testsoptclean: SUB_TARGET := optclean
testsoptclean: SUB_JOB := build
testsoptclean: $(SUB_TESTTARGETS)

testsdbgclean: SUB_TARGET := dbgclean
testsdbgclean: SUB_JOB := build
testsdbgclean: $(SUB_TESTTARGETS)

testsClean: SUB_TARGET := Clean
testsClean: SUB_JOB := build
testsClean: $(SUB_TESTTARGETS)

testsoptClean: SUB_TARGET := optClean
testsoptClean: SUB_JOB := build
testsoptClean: $(SUB_TESTTARGETS)

testsdbgClean: SUB_TARGET := dbgClean
testsdbgClean: SUB_JOB := build
testsdbgClean: $(SUB_TESTTARGETS)

#########################################################################
# depend
#########################################################################

depend: SUB_TARGET := depend
depend: $(SUB_LIBTARGETS)

#########################################################################
# fcdToBase
#########################################################################

fcdToBase: SUB_TARGET := fcdToBase
fcdToBase: $(SUB_LIBTARGETS)

fcdToBaseCompat: SUB_TARGET := fcdToBaseCompat
fcdToBaseCompat: $(SUB_LIBTARGETS)

#########################################################################
# dsp
#########################################################################

dsp: SUB_TARGET := dsp
dsp: $(SUB_LIBTARGETS)
	@cp Base/OSGConfigured.h $(OSGPOOL)/VSBuild/VS6
	@cp Base/unistd.h $(OSGPOOL)/VSBuild/VS6

dsp7: SUB_TARGET := dsp7
dsp7: $(SUB_LIBTARGETS)
	@cp Base/OSGConfigured.h $(OSGPOOL)/VSBuild/VS7
	@cp Base/unistd.h $(OSGPOOL)/VSBuild/VS7

#########################################################################
# install
#########################################################################

INSTALL_EXISTS := $(shell if test ! -d $(INSTALL_DIR) ; then echo "not"; fi  )
INSTALL_WRITABLE := $(shell if test ! -w $(INSTALL_DIR) ; then echo "not"; fi  )

install-test:
ifeq ($(INSTALL_EXISTS),not)
	$(error Install dir $(INSTALL_DIR) doesn't exist! I can't install there)
endif
ifeq ($(INSTALL_WRITABLE),not)
	$(error Install dir $(INSTALL_DIR) exists but is not writable! I can't install there)
endif

ifeq ($(CONFIGURED_GVBETA),0)
GV_EXCLUDE  := -o -name Gerrit 
GV_ADD_PATH := 
else
GV_EXCLUDE := -o -name tmp_gv
GV_ADD_PATH :=
endif

GV_EXCLUDE := -o -name Experimental -o -name Contrib -o -name Foo -o -name Impl

install-xxx:
	CURRDIR=`pwd`;                                                          \
	find $$CURRDIR/Base -follow                                             \
	    \( -type d \( -name CVS -o -name '*Test' -o -name include  -o       \
	       -name Tools -o -name tmp \) -prune \)                            \
	    -o -type f                                                          \
	-exec $($(PROJ)POOL)/Common/sedIncBuild {} $(INSTALL_DIR)/include/OpenSG \; ; \


install-includes_sub: SUB_TARGET := install-includes
install-includes_sub: $(SUB_LIBTARGETS) 

update-includes_sub: SUB_TARGET := update-includes
update-includes_sub: $(SUB_LIBTARGETS) 

INST_PACKAGE_NAME := OpenSG

install-prep:
	@if [ ! -w $(INSTALL_DIR)/include ]; then                               \
            mkdir $(INSTALL_DIR)/include;                                   \
     fi;
	@if [ ! -w $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME) ]; then          \
            mkdir $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME);              \
	 else																	\
	    	rm -f $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME)/*.hpp; 		\
	    	rm -f $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME)/*.h;   		\
	    	rm -f $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME)/*.inl;		\
	    	rm -f $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME)/*.ins;		\
     fi;

install-includes_loc:
	@find Base -type f -exec cp {} $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME) \; -print

update-includes_loc:
	@find Base -type f -exec $($(PROJ)POOL)/Common/sedIncU {} $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME) \; -print

install-includes_chmod:
	@find $(INSTALL_DIR)/include/$(INST_PACKAGE_NAME) -type f               \
     -exec chmod 444 {} \;  ;


install-includes: install-test install-prep install-includes_sub install-includes_loc install-includes_chmod

update-includes: install-test update-includes_sub update-includes_loc install-includes_chmod

install-libs: install-test
	@echo $(SO_SEARCH_SUFFIX)
	@if [ ! -w $(INSTALL_DIR)/lib ]; then mkdir $(INSTALL_DIR)/lib; fi
	@if [ ! -w $(INSTALL_DIR)/lib/dbg ]; then mkdir $(INSTALL_DIR)/lib/dbg; fi
	@if [ ! -w $(INSTALL_DIR)/lib/opt ]; then mkdir $(INSTALL_DIR)/lib/opt; fi
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -follow -name 'lib-dbg'                       \
                 -exec find {} -name '*\$(SO_SEARCH_SUFFIX)' -print \;` ;   \
	cd $(INSTALL_DIR)/lib/dbg;                                              \
	rm -f *$(SO_SEARCH_SUFFIX);                                             \
	for t in $$BUILDLIBS;                                                   \
	do                                                                      \
	    echo $$t;                                                           \
	    $(INSTLINK) $$t .;                                                  \
	done;                                                                   \
	cd $$CURRDIR;
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -follow -name 'lib-opt'                       \
                 -exec find {} -name '*\$(SO_SEARCH_SUFFIX)' -print \;` ;   \
	cd $(INSTALL_DIR)/lib/opt;                                              \
	rm -f *$(SO_SEARCH_SUFFIX);                                             \
	for t in $$BUILDLIBS;                                                   \
	do                                                                      \
	    echo $$t;                                                           \
	    $(INSTLINK) $$t .;                                                  \
	done;                                                                   \
	cd $$CURRDIR;
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -follow -name 'lib-dbglnk'                    \
	                -exec find {} -name '*\$(LNK_LIB_SUFFIX)' -print \;` ;  \
	cd $(INSTALL_DIR)/lib/dbg;                                              \
	rm -f *$(LNK_LIB_SUFFIX);                                               \
	for t in $$BUILDLIBS;                                                   \
	do                                                                      \
	    echo $$t;                                                           \
	    $(INSTLINK) $$t .;                                                  \
	done;                                                                   \
	cd $$CURRDIR;
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -follow -name 'lib-optlnk'                    \
	                -exec find {} -name '*\$(LNK_LIB_SUFFIX)' -print \;` ;  \
	cd $(INSTALL_DIR)/lib/opt;                                              \
	rm -f *$(LNK_LIB_SUFFIX);                                               \
	for t in $$BUILDLIBS;                                                   \
	do                                                                      \
	    echo $$t;                                                           \
	    $(INSTLINK) $$t .;                                                  \
	done;                                                                   \
	cd $$CURRDIR;
ifeq ($(OS_BASE),cygwin)
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -follow -name 'lib-dbg'                       \
	             -exec find {} -name '*\$(LIB_SEARCH_SUFFIX)' -print \;` ;  \
	cd $(INSTALL_DIR)/lib/dbg;                                              \
	for t in $$BUILDLIBS;                                                   \
	do                                                                      \
	    echo  $$t;                                                          \
	    $(INSTLINK) $$t .;                                                  \
	done;                                                                   \
	cd $$CURRDIR;
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -follow -name 'lib-opt'                       \
	             -exec find {} -name '*\$(LIB_SEARCH_SUFFIX)' -print \;` ;  \
	cd $(INSTALL_DIR)/lib/opt;                                              \
	for t in $$BUILDLIBS;                                                   \
	do                                                                      \
	    echo  $$t;                                                          \
	    $(INSTLINK) $$t .;                                                  \
	done;                                                                   \
	cd $$CURRDIR;
endif


fcdToBase_old:
	@FCDEDIT=$($(PROJ)POOL)/Tools/fcdEdit/fcdEdit;                          \
	CURRDIRBASE=`pwd` ;                                                     \
        echo "Collecting .fcd files...";                                        \
	cd $($(PROJ)POOL) ;                                                     \
	for i in `find . -follow                                                \
	    \( -type d \( -name CVS -o -name Test -o -name Builds -o            \
	       -name Tools -o -name Examples -o -name '*/.*' \) -prune \)       \
	    -o -type f -name '*\.fcd' -print` ;                                 \
	do                                                                      \
	    echo $$i ;                                                          \
	    CURRDIR=`pwd` ;                                                     \
	    cd `dirname $$i` ;                                                  \
	    $$FCDEDIT -b `basename $$i`;                                        \
	    cd $$CURRDIR ;                                                      \
	done;                                                                   \
	cd $$CURRDIRBASE

INSTALL_DIR_SED  := $(shell echo $(INSTALL_DIR)  | sed -e 's/\//\\\//g')
LD_SED           := $(shell echo $(LD)           | sed -e 's/\//\\\//g')
LD_FLAGS_EXT_SED := $(shell echo $(LD_FLAGS_EXT) | sed -e 's/\//\\\//g')

install-bin: install-test
	@if [ ! -w $(INSTALL_DIR)/bin ]; then mkdir $(INSTALL_DIR)/bin; fi
	@echo "installing $(INSTALL_DIR)/bin/osg-config from CommonPackages/osg-config" 
	@VERSION=`cat $($(PROJ)POOL)/VERSION`;                                  \
	ICOMP=`echo $(CC) | sed -e 's|^[ ]*||' -e 's|[ ]*$$||'`;                \
	cat CommonPackages/osg-config |                                         \
	$(SED) -e 's/@am_gdz_system_flags@/\"$(CCFLAGS_EXT)\"/g'                \
	       -e 's/@am_gdz_system_flags_opt@/\"$(CCFLAGS_EXT_OPT)\"/g'        \
	       -e 's/@am_gdz_system_flags_dbg@/\"$(CCFLAGS_EXT_DBG)\"/g'        \
	       -e 's|@am_gdz_base_libs@|\"$(LIBS_$(OS_BASE))\"|g' 				\
	       -e 's|@am_gdz_add_inc@|%%%$(subst \,\\,$(ADD_INCL_$(OS_BASE)))%%%|g'		\
	       -e 's|@am_gdz_add_link@|%%%$(subst \,\\,$(ADD_LIBPATHS_$(OS_BASE)))%%%|g'\
           -e "s|%%%|'|g"													 \
	       -e 's/@am_gdz_link_flags@/\"$(LD_FLAGS_EXT_SED)\"/g'             \
	       -e 's/@am_gdz_link_flags_opt@/\"$(LD_FLAGS_EXT_OPT)\"/g'         \
	       -e 's/@am_gdz_link_flags_dbg@/\"$(LD_FLAGS_EXT_DBG)\"/g'         \
	       -e 's/@am_gdz_install_dir@/"$(INSTALL_DIR_SED)\"/g'              \
	       -e "s|@am_gdz_compiler@|\"$$ICOMP\"|g"                           \
	       -e "s/@am_gdz_version@/$$VERSION/g"                              \
	       -e 's/@am_gdz_qt_cflags@/\"$(QT_PLATTFORMDEF_EXT)\"/g'           \
	       -e 's/@am_gdz_exe_linker@/\"$(LD_SED)\"/g'                       \
	       -e "s/@am_gdz_compiler_id@/$(OS_CMPLR)/g"                        \
		   -e "s/MSVCPRTD/MSVCPRT\$$\{dbg_char\}/g"							\
		   -e "s/MSVCRTD/MSVCRT\$$\{dbg_char\}/g"							\
	    > $(INSTALL_DIR)/bin/osg-config
	@chmod 755 $(INSTALL_DIR)/bin/osg-config

install-libs-ln: INSTLINK := $(LINK)
install-libs-ln: install-libs

install-libs-cp: INSTLINK := cp
install-libs-cp: install-libs

install-ln: install-includes install-libs-ln install-bin
install-cp: install-includes install-libs-cp install-bin
install: install-includes install-libs-cp install-bin

install-gabe: INSTLINK := cp
install-gabe: install-includes-gabe install-libs-cp

update-ln: update-includes install-libs-ln install-bin
update: update-includes install-libs-cp install-bin

%.src:
	@if [ -d $* ]; then                                                     \
	    cd $*;                                                              \
	    $(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET) SUB_JOB=$(SUB_JOB);    \
	    cd ..;                                                              \
	fi

#########################################################################
# Collection Targets
#########################################################################

dbgall: dbg tests

optall: opt testsOpt

all:    dbgall optall

#########################################################################
# Help Target
#########################################################################

help:
	@echo 
	@echo "Targets supported on this level (Top):"
	@echo "======================================"
	@echo 
	@echo "Creation targets"
	@echo 
	@echo "<default>  compile the same versions of the configured libraries as last time"
	@echo "dbg        compile the debug versions of the configured libraries"
	@echo "opt        compile the optimized versions of the configured libraries"
	@echo "dbgLnk     compile the debug versions of the configured libraries (static libs)"
	@echo "optLnk     compile the optimized versions of the configured libraries (static libs)"
	@echo "depend     explicitly create the dependency information"
	@echo 
	@echo "dsp        create dsp files in VSBuild/* from the current config" 
	@echo 
	@echo "tests      build dbg tests"
	@echo "testsOpt   build opt tests"
	@echo 
	@echo "dbgall     make dbg ; make tests"
	@echo "optall     make opt ; make testsOpt"
	@echo "all        make dbgall ; make optall"
	@echo 
	@echo "Cleanup targets"
	@echo 
	@echo "remove temporary result files: object files, flex/bison/moc output etc.,"
	@echo "dbgclean    for the debugging libraries only"
	@echo "optclean    for the optimized libraries only"
	@echo "clean       for the same libraries as last time"
	@echo "allclean    dbgclean and optclean"
	@echo 
	@echo "remove dependency files"
	@echo "dbgDepClean    for the debugging libraries only"
	@echo "optDepClean    for the optimized libraries only"
	@echo "DepClean       for the same libraries as last time"
	@echo 
	@echo "same as clean + dependencies + results (libs/programs)"
	@echo "dbgClean    for the debugging libraries only"
	@echo "optClean    for the optimized libraries only"
	@echo "Clean       for the same libraries as last time"
	@echo "distclean   dbgClean and optClean"
	@echo 
	@echo "LibClean   remove libraries"
	@echo "ExeClean   remove executables"
	@echo 
	@echo "Installation targets"
	@echo 
	@echo "The installation base directory is the one given to configure as --prefix,"
	@echo "but it can be set on the make line with INSTALL_DIR=<dir>"
	@echo "install the libraries into INSTALL_DIR/lib/{dbg,opt}"
	@echo "install-libs-ln   using links"
	@echo "install-libs-cp   copying them"
	@echo "install-libs      linking or copying them, the same as last time"
	@echo "install-includes  install the include files into INSTALL_DIR/include"
	@echo "update-includes   install the include files into INSTALL_DIR/include iff the source is newer"
	@echo "install-bin       install osg-config into INSTALL_DIR/bin"
	@echo "install-ln        install-includes + install-libs-ln + install-bin"
	@echo "install-cp        install-includes + install-libs-cp + install-bin"
	@echo "install           install-includes + install-libs-cp + install-bin"
	@echo "update-ln         update-includes  + install-libs-ln + install-bin"
	@echo "update            update-includes  + install-libs-cp + install-bin"
	@echo 
	@echo "Other targets"
	@echo 
	@echo "fcdToBase    run through the tree and regenerate all the Base sources"
	@echo 
	@echo "Useful Environment Variables"
	@echo 
	@echo "OSGSUBPARJOBS       number of parallel compiler jobs to run"
	@echo "OSGNODEPS=1         do not evaluate the dependencies"
	@echo "OSGNODEPSREBUILD=1  do not rebuld the dependency files"
