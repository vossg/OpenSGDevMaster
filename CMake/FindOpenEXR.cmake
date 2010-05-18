# - Find OpenEXR image format libraries
# Find the OpenEXR high dynamic range (HDR) image format libraries and headers
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
#
#  OPENEXR_ROOT_DIR          look for headers in ${OPENEXR_ROOT_DIR}/include/OpenEXR
#                            look for libs in    ${OPENEXR_ROOT_DIR}/lib
#  OPENEXR_INCLUDE_DIR       look for headers in ${OPENEXR_INCLUDE_DIR}/OpenEXR
#  OPENEXR_LIBRARY_DIR       look for libs in    ${OPENEXR_LIBRARY_DIR}
#
#  Note: Setting these variables will skip searching the system default paths.


# default include search paths
SET(__OPENEXR_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/include)

# default library search paths
SET(__OPENEXR_LIBRARY_SEARCH_DIRS
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

    SET(__OPENEXR_INCLUDE_SEARCH_DIRS "${OPENEXR_ROOT_DIR}/include"
                                      "${__OPENEXR_INCLUDE_SEARCH_DIRS}")

    SET(__OPENEXR_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__OPENEXR_LIBDIR_SUFFIX_IN} __OPENEXR_LIBDIR_SUFFIX)

    SET(__OPENEXR_LIBRARY_SEARCH_DIRS "${OPENEXR_ROOT_DIR}/lib/${__OPENEXR_LIBDIR_SUFFIX}"
                                      "${OPENEXR_ROOT_DIR}/lib"
                                      "${__OPENEXR_LIBRARY_SEARCH_DIRS}")

    # skip default paths since the user specified explicit ones
    SET(__OPENEXR_NO_DEFAULT_INC_PATH NO_DEFAULT_PATH)
    SET(__OPENEXR_NO_DEFAULT_LIB_PATH NO_DEFAULT_PATH)
ENDIF(OPENEXR_ROOT_DIR)


# handle OPENEXR_INCLUDE_DIR input variable
IF(OPENEXR_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${OPENEXR_INCLUDE_DIR} OPENEXR_INCLUDE_DIR)
    SET(__OPENEXR_INCLUDE_SEARCH_DIRS "${OPENEXR_INCLUDE_DIR}"
                                      "${__OPENEXR_INCLUDE_SEARCH_DIRS}")
    SET(__OPENEXR_NO_DEFAULT_INC_PATH NO_DEFAULT_PATH)
ENDIF(OPENEXR_INCLUDE_DIR)

# handle OPENEXR_LIBRARY_DIR input variable
IF(OPENEXR_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${OPENEXR_LIBRARY_DIR} OPENEXR_LIBRARY_DIR)
    SET(__OPENEXR_LIBRARY_SEARCH_DIRS "${OPENEXR_LIBRARY_DIR}"
                                      "${__OPENEXR_LIBRARY_SEARCH_DIRS}")
    SET(__OPENEXR_NO_DEFAULT_LIB_PATH NO_DEFAULT_PATH)
ENDIF(OPENEXR_LIBRARY_DIR)


# locate headers
FIND_PATH(OPENEXR_INCLUDE_DIR OpenEXR/ImfIO.h
    PATHS ${__OPENEXR_INCLUDE_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_INC_PATH})

# locate libraries
FIND_LIBRARY(OPENEXR_LIBRARY_IMF_RELEASE
    NAMES IlmImf
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})

FIND_LIBRARY(OPENEXR_LIBRARY_HALF_RELEASE
    NAMES Half ilmhalf
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})

FIND_LIBRARY(OPENEXR_LIBRARY_IEX_RELEASE
    NAMES Iex ilmiex
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})

FIND_LIBRARY(OPENEXR_LIBRARY_ILMTHREAD_RELEASE
    NAMES IlmThread
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})


FIND_LIBRARY(OPENEXR_LIBRARY_IMF_DEBUG
    NAMES IlmImf-d IlmImfd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})

FIND_LIBRARY(OPENEXR_LIBRARY_HALF_DEBUG
    NAMES Half-d Halfd ilmhalf-d ilmhalfd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})

FIND_LIBRARY(OPENEXR_LIBRARY_IEX_DEBUG
    NAMES Iex-d Iexd ilmiex-d ilmiexd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})

FIND_LIBRARY(OPENEXR_LIBRARY_ILMTHREAD_DEBUG
    NAMES IlmThread-d IlmThreadd
    PATHS ${__OPENEXR_LIBRARY_SEARCH_DIRS} ${__OPENEXR_NO_DEFAULT_LIB_PATH})



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
