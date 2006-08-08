
ifeq ($(DBG),)
DBG_BASE := dbg
endif

#########################################################################
# Get Job Type
#########################################################################

OPT_TARGETS=opt optLnk optClean optclean optCleanLnk optcleanLnk TestOpt

LNK_TARGETS=dbgLnk optLnk dbgCleanLnk dbgCleanLnk optCleanLnk optcleanLnk \
			cleanLnk CleanLnk testsLnk TestLnk

NONBUILDTARGETS    = depend commonclean dbgclean optclean clean commonClean	 \
					 dbgClean optClean Clean commonDepClean dbgDepClean		 \
					 optDepClean DepClean LibClean dbkLnk cleanLnk fcdToBase \
                     fcdToBaseCompat

TESTBUILDTARGETS   = Test TestLnk dbg opt dbgLnk optLnk

ifeq ($(MAKECMDGOALS),)
SUB_JOB := build
else
FILTEREDCMDGOALS := $(strip $(filter-out $(NONBUILDTARGETS), $(MAKECMDGOALS)))
FILTEREDTSTGOALS := $(strip $(filter-out $(TESTBUILDTARGETS),$(MAKECMDGOALS)))

ifeq ($(FILTEREDCMDGOALS),)
SUB_JOB := admin
else
SUB_JOB := build
endif
endif

#ifneq ($(MAKECMDGOALS),)

DBGCMDGOAL := $(strip $(filter $(OPT_TARGETS),$(MAKECMDGOALS)))

ifneq ($(DBGCMDGOAL),)
$(warning Detected OPT)
DBG_BASE=opt
DEBUG_VERSION=0
else
$(warning Detected DBG)
DBG_BASE=dbg
DEBUG_VERSION=1
endif

DEBUG_CHAR:=

DBGLNKCMDGOAL := $(strip $(filter $(LNK_TARGETS),$(MAKECMDGOALS)))

ifneq ($(DBGLNKCMDGOAL),)
LNK=lnk
LNK_SUFFIX=Lnk
$(warning Detected Link Lib)
else
LNK=
LNK_SUFFIX=
$(warning Detected Shared Lib)
endif

#endif

DBG := $(DBG_BASE)$(LNK)

ifeq ($(MAKECMDGOALS),depend)
OSGNODEPSREBUILD=0
endif
ifeq ($(MAKECMDGOALS),dsp)
OSGNODEPSREBUILD=0
endif

ifeq ($(DEBUG_MAKE),1)
$(warning DBG=$(DBG))
endif

MAKEMAJOR := \
	$(shell $(MAKE) --version | head -1 | cut -d' ' -f 4 | cut -d'.' -f 1)

MAKEMINOR := \
	$(shell $(MAKE) --version | head -1 | cut -d' ' -f 4 | cut -d'.' -f 2)

ifeq ($(MAKEMAJOR),)
MAKEMAJOR := \
	$(shell $(MAKE) --version | head -1 | cut -d' ' -f 3 | cut -d'.' -f 1)

MAKEMINOR := \
	$(shell $(MAKE) --version | head -1 | cut -d' ' -f 3 | cut -d'.' -f 2)
endif


MAKEMAJOR := $(strip $(MAKEMAJOR))
MAKEMINOR := $(strip $(MAKEMINOR))

ifeq ($(MAKEMAJOR),3)

MAKE_OLD_DOLLAR := 1

ifeq ($(MAKEMINOR),80)
MAKE_OLD_DOLLAR := 0
endif

ifeq ($(MAKEMINOR),81)
MAKE_OLD_DOLLAR := 0
endif

else
$(error Unknown GNU make major version $(MAKEMAJOR) please contact info@opensg.org)
endif

