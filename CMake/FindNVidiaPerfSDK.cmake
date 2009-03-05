# - Find collada dom libraries
# Find the collada dom libraries and headers
#
# This module specifies the following variables:
#  NVIDIAPERFSDK_INCLUDE_DIR
#  NVIDIAPERFSDK_LIBRARIES
#  NVIDIAPERFSDK_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  NVIDIAPERFSDK_LIBRARY_DEBUG        debug library
#  NVIDIAPERFSDK_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  NVIDIAPERFSDK_ROOT_DIR
#  NVIDIAPERFSDK_INCLUDE_DIR
#  NVIDIAPERFSDK_LIBRARY_DIR


# default include search paths
SET(__NVIDIAPERFSDK_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/local/include/colladadom
    /usr/include
    /usr/include/colladadom
    /sw/include
    /opt/local/include
    /opt/local/include/colladadom
    /opt/include
    /opt/include/colladadom)

# default library search paths
SET(__NVIDIAPARFSDK_LIBRARY_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/local/lib64
    /usr/lib
    /usr/lib64
    /sw/lib
    /opt/local/lib
    /opt/local/lib64
    /opt/lib
    /opt/lib64)

# handle NVIDIAPERFSDK_ROOT_DIR input variable
IF(NVIDIAPERFSDK_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${NVIDIAPERFSDK_ROOT_DIR} NVIDIAPERFSDK_ROOT_DIR)

    SET(__NVIDIAPERFSDK_INCLUDE_SEARCH_DIRS "${NVIDIAPERFSDK_ROOT_DIR}/inc"
                                            "${__NVIDIAPERFSDK_INCLUDE_SEARCH_DIRS}")

    SET(__NVIDIAPERFSDK_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__NVIDIAPERFSDK_LIBDIR_SUFFIX_IN} __NVIDIAPERFSDK_LIBDIR_SUFFIX)

    SET(__NVIDIAPERFSDK_LIBRARY_SEARCH_DIRS "${NVIDIAPERFSDK_ROOT_DIR}/lib/${__NVIDIAPERFSDK_LIBDIR_SUFFIX}"
                                            "${__NVIDIAPERFSDK_LIBRARY_SEARCH_DIRS}")
ENDIF(NVIDIAPERFSDK_ROOT_DIR)

# handle NVIDIAPERFSDK_INCLUDE_DIR input variable
IF(NVIDIAPERFSDK_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${NVIDIAPERFSDK_INCLUDE_DIR} NVIDIAPERFSDK_INCLUDE_DIR)
    SET(__NVIDIAPERFSDK_INCLUDE_SEARCH_DIRS "${NVIDIAPERFSDK_INCLUDE_DIR}"
                                            "${__NVIDIAPERFSDK_INCLUDE_SEARCH_DIRS}")
ENDIF(NVIDIAPERFSDK_INCLUDE_DIR)

# handle NVIDIAPERFSDK_LIBRARY_DIR input variable
IF(NVIDIAPERFSDK_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${NVIDIAPERFSDK_LIBRARY_DIR} NVIDIAPERFSDK_LIBRARY_DIR)
    SET(__NVIDIAPERFSDK_LIBRARY_SEARCH_DIRS "${NVIDIAPERFSDK_LIBRARY_DIR}"
                                            "${__NVIDIAPERFSDK_LIBRARY_SEARCH_DIRS}")
ENDIF(NVIDIAPERFSDK_LIBRARY_DIR)


# locate headers
FIND_PATH(NVIDIAPERFSDK_INCLUDE_DIR NVPerfSDK.h
    PATHS ${__NVIDIAPERFSDK_INCLUDE_SEARCH_DIRS})


# locate libraries
FIND_LIBRARY(NVIDIAPERFSDK_LIBRARY_RELEASE
    NAMES NVPerfSDK
    PATHS ${__NVIDIAPERFSDK_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(NVIDIAPERFSDK_LIBRARY_DEBUG
    NAMES NVPerfSDK-d
    PATHS ${__NVIDIAPERFSDK_LIBRARY_SEARCH_DIRS})


# handle the QUIETLY and REQUIRED arguments and set NVIDIAPERFSDK_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(NVIDIAPERFSDK DEFAULT_MSG NVIDIAPERFSDK_LIBRARY_RELEASE
                                                            NVIDIAPERFSDK_INCLUDE_DIR)

# set output variables
IF(NVIDIAPERFSDK_FOUND)
    SET(NVIDIAPERFSDK_LIBRARIES "${NVIDIAPERFSDK_LIBRARY_RELEASE}")
ENDIF(NVIDIAPERFSDK_FOUND)
