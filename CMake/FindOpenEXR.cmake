# - Find collada dom libraries
# Find the collada dom libraries and headers
#
# This module specifies the following variables:
#  OPENEXR_INCLUDE_DIR
#  OPENEXR_LIBRARIES
#  OPENEXR_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  OPENEXR_LIBRARY_DEBUG        debug library
#  OPENEXR_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  OPENEXR_ROOT_DIR
#  OPENEXR_INCLUDE_DIR
#  OPENEXR_LIBRARY_DIR


# default include search paths
SET(__OPENEXR_INCLUDE_SEARCH_DIRS
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
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    /sw/lib
    /opt/local/lib64
    /opt/local/lib
    /opt/lib64
    /opt/lib)

# handle OPENEXR_ROOT_DIR input variable
IF(OPENEXR_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${OPENEXR_ROOT_DIR} OPENEXR_ROOT_DIR)

    SET(__OPENEXR_INCLUDE_SEARCH_DIRS "${OPENEXR_ROOT_DIR}/OpenEXR"
                                      "${__OPENEXR_INCLUDE_SEARCH_DIRS}")

    SET(__OPENEXR_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__OPENEXR_LIBDIR_SUFFIX_IN} __OPENEXR_LIBDIR_SUFFIX)

    SET(__OPENEXR_LIBRARY_SEARCH_DIRS "${OPENEXR_ROOT_DIR}/lib/${__OPENEXR_LIBDIR_SUFFIX}"
                                            "${__OPENEXR_LIBRARY_SEARCH_DIRS}")
ENDIF(OPENEXR_ROOT_DIR)


# handle OPENEXR_INCLUDE_DIR input variable
IF(OPENEXR_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${OPENEXR_INCLUDE_DIR} OPENEXR_INCLUDE_DIR)
    SET(__OPENEXR_INCLUDE_SEARCH_DIRS "${OPENEXR_INCLUDE_DIR}"
                                      "${__OPENEXR_INCLUDE_SEARCH_DIRS}")
ENDIF(OPENEXR_INCLUDE_DIR)

# handle OPENEXR_LIBRARY_DIR input variable
IF(OPENEXR_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${OPENEXR_LIBRARY_DIR} OPENEXR_LIBRARY_DIR)
    SET(__OPENEXR_LIBRARY_SEARCH_DIRS "${OPENEXR_LIBRARY_DIR}"
                                      "${__OPENEXR_LIBRARY_SEARCH_DIRS}")
ENDIF(OPENEXR_LIBRARY_DIR)


# locate headers
FIND_PATH(OPENEXR_INCLUDE_DIR OpenEXR/ImfIO.h
    PATHS ${__OPENEXR_INCLUDE_SEARCH_DIRS})

# locate libraries
FIND_LIBRARY(OPENEXR_LIBRARY_IMF_RELEASE
    NAMES IlmImf
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(OPENEXR_LIBRARY_HALF_RELEASE
    NAMES Half ilmhalf
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(OPENEXR_LIBRARY_IEX_RELEASE
    NAMES Iex ilmiex
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(OPENEXR_LIBRARY_ILMTHREAD_RELEASE
    NAMES IlmThread
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})


FIND_LIBRARY(OPENEXR_LIBRARY_IMF_DEBUG
    NAMES IlmImf-d IlmImfd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(OPENEXR_LIBRARY_HALF_DEBUG
    NAMES Half-d Halfd ilmhalf-d ilmhalfd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(OPENEXR_LIBRARY_IEX_DEBUG
    NAMES Iex-d Iexd ilmiex-d ilmiexd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(OPENEXR_LIBRARY_ILMTHREAD_DEBUG
    NAMES IlmThread-d IlmThreadd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS})



# handle the QUIETLY and REQUIRED arguments and set OPENEXR_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPENEXR DEFAULT_MSG 
                                          OPENEXR_LIBRARY_IMF_RELEASE
                                          OPENEXR_LIBRARY_HALF_RELEASE
                                          OPENEXR_LIBRARY_IEX_RELEASE
                                          OPENEXR_LIBRARY_ILMTHREAD_RELEASE
                                          OPENEXR_INCLUDE_DIR)

IF(OPENEXR_INCLUDE_DIR)
    LIST(APPEND OPENEXR_INCLUDE_DIR "${OPENEXR_INCLUDE_DIR}/OpenEXR")
ENDIF(OPENEXR_INCLUDE_DIR)

# set output variables
IF(OPENEXR_FOUND)
    LIST(APPEND OPENEXR_LIBRARIES "${OPENEXR_LIBRARY_IMF_RELEASE}")
    LIST(APPEND OPENEXR_LIBRARIES "${OPENEXR_LIBRARY_HALF_RELEASE}")
    LIST(APPEND OPENEXR_LIBRARIES "${OPENEXR_LIBRARY_IEX_RELEASE}")
    LIST(APPEND OPENEXR_LIBRARIES "${OPENEXR_LIBRARY_ILMTHREAD_RELEASE}")

#    LIST(APPEND OPENEXR_LIBRARIES "debug:${OPENEXR_LIBRARY_IMF_RELEASE}")
#    LIST(APPEND OPENEXR_LIBRARIES "debug:${OPENEXR_LIBRARY_HALF_RELEASE}")
#    LIST(APPEND OPENEXR_LIBRARIES "debug:${OPENEXR_LIBRARY_IEX_RELEASE}")

#    SET(OPENEXR_LIBRARIES_RELEASE "${OPENEXR_LIBRARY_IMF_RELEASE}"
#                                  "${OPENEXR_LIBRARY_HALF_RELEASE}"
#                                  "${OPENEXR_LIBRARY_IEX_RELEASE}")

#    SET(OPENEXR_LIBRARIES_DEBUG "${OPENEXR_LIBRARY_IMF_DEBUG}"
#                                "${OPENEXR_LIBRARY_HALF_DEBUG}"
#                                "${OPENEXR_LIBRARY_IEX_DEBUG}")
ENDIF(OPENEXR_FOUND)
