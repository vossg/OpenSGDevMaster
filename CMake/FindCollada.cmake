# - Find collada dom libraries
# Find the collada dom libraries and headers
#
# This module specifies the following variables:
#  COLLADA_INCLUDE_DIRS
#  COLLADA_LIBRARIES
#  COLLADA_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  COLLADA_DAE_INCLUDE_DIR      DAE header files
#  COLLADA_DOM_INCLUDE_DIR      DOM header files
#  COLLADA_LIBRARY_DEBUG        debug library
#  COLLADA_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  COLLADA_ROOT_DIR
#  COLLADA_INCLUDE_DIR
#  COLLADA_LIBRARY_DIR


# default include search paths
SET(__COLLADA_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/local/include/colladadom
    /usr/local/include/collada-dom
    /usr/include
    /usr/include/colladadom
    /usr/include/collada-dom
    /sw/include
    /opt/local/include
    /opt/local/include/colladadom
    /opt/local/include/collada-dom
    /opt/include
    /opt/include/colladadom
    /opt/include/collada-dom)

# default library search paths
SET(__COLLADA_LIBRARY_SEARCH_DIRS
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

SET(COLLADA_ROOT_DIR_ENV "$ENV{COLLADA_ROOT_DIR}")

IF(NOT COLLADA_ROOT_DIR AND COLLADA_ROOT_DIR_ENV)
    SET(COLLADA_ROOT_DIR "${COLLADA_ROOT_DIR_ENV}")
ENDIF(NOT COLLADA_ROOT_DIR AND COLLADA_ROOT_DIR_ENV)

# handle COLLADA_ROOT_DIR input variable
IF(COLLADA_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${COLLADA_ROOT_DIR} COLLADA_ROOT_DIR)

    SET(__COLLADA_INCLUDE_SEARCH_DIRS "${COLLADA_ROOT_DIR}/include"
                                      "${COLLADA_ROOT_DIR}/include/colladadom"
                                      "${COLLADA_ROOT_DIR}/include/collada-dom"
                                      "${__COLLADA_INCLUDE_SEARCH_DIRS}")
    SET(__COLLADA_LIBRARY_SEARCH_DIRS "${COLLADA_ROOT_DIR}/lib"
                                      "${COLLADA_ROOT_DIR}/lib64"
                                      "${__COLLADA_LIBRARY_SEARCH_DIRS}")
ENDIF(COLLADA_ROOT_DIR)

IF(OSG_SUPPORT_ROOT AND OSG_USE_OSGSUPPORT_LIBS)
    FILE(TO_CMAKE_PATH ${OSG_SUPPORT_ROOT} _OSG_SUPPORT_ROOT)

    SET(__COLLADA_INCLUDE_SEARCH_DIRS "${_OSG_SUPPORT_ROOT}/include"
                                      "${_OSG_SUPPORT_ROOT}/include/colladadom"
                                      "${_OSG_SUPPORT_ROOT}/include/collada-dom"
                                      "${__COLLADA_INCLUDE_SEARCH_DIRS}")
    SET(__COLLADA_LIBRARY_SEARCH_DIRS "${_OSG_SUPPORT_ROOT}/lib"
                                      "${_OSG_SUPPORT_ROOT}/lib64"
                                      "${__COLLADA_LIBRARY_SEARCH_DIRS}")
ENDIF(OSG_SUPPORT_ROOT AND OSG_USE_OSGSUPPORT_LIBS)


# handle COLLADA_INCLUDE_DIR input variable
IF(COLLADA_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${COLLADA_INCLUDE_DIR} COLLADA_INCLUDE_DIR)
    SET(__COLLADA_INCLUDE_SEARCH_DIRS "${COLLADA_INCLUDE_DIR}"
                                      "${__COLLADA_INCLUDE_SEARCH_DIRS}")
ENDIF(COLLADA_INCLUDE_DIR)

# handle COLLADA_LIBRARY_DIR input variable
IF(COLLADA_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${COLLADA_LIBRARY_DIR} COLLADA_LIBRARY_DIR)
    SET(__COLLADA_LIBRARY_SEARCH_DIRS "${COLLADA_LIBRARY_DIR}"
                                      "${__COLLADA_LIBRARY_SEARCH_DIRS}")
ENDIF(COLLADA_LIBRARY_DIR)


# locate headers
FIND_PATH(COLLADA_DAE_INCLUDE_DIR dae.h
    PATHS ${__COLLADA_INCLUDE_SEARCH_DIRS})

FIND_PATH(COLLADA_DOM_INCLUDE_DIR "dom/domNode.h"
    PATHS ${__COLLADA_INCLUDE_SEARCH_DIRS}
    PATH_SUFFIXES "1.4")

IF(OSG_USE_OSGSUPPORT_LIBS)
# locate libraries 
FIND_LIBRARY(COLLADA_LIBRARY_RELEASE
    NAMES osgcollada14dom22 osgcollada14dom22lib collada_dom collada14dom libcollada14dom21
    PATHS ${__COLLADA_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(COLLADA_LIBRARY_DEBUG
    NAMES osgcollada14dom22 osgcollada14dom22lib collada_dom-d collada14dom-d libcollada14dom21-d
    PATH_SUFFIXES debug
    PATHS ${__COLLADA_LIBRARY_SEARCH_DIRS})
ELSE()
# locate libraries
FIND_LIBRARY(COLLADA_LIBRARY_RELEASE
    NAMES collada_dom collada14dom libcollada14dom21
    PATHS ${__COLLADA_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(COLLADA_LIBRARY_DEBUG
    NAMES collada_dom-d collada14dom-d libcollada14dom21-d
    PATHS ${__COLLADA_LIBRARY_SEARCH_DIRS})
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set COLLADA_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COLLADA DEFAULT_MSG COLLADA_LIBRARY_RELEASE
                                                      COLLADA_DAE_INCLUDE_DIR
                                                      COLLADA_DOM_INCLUDE_DIR)

# if only the debug or release lib was found, use it for both configurations,
# except on windows where the runtimes have to match
IF(NOT WIN32)
    IF(COLLADA_LIBRARY_RELEASE AND NOT COLLADA_LIBRARY_DEBUG)
        SET(COLLADA_LIBRARY_DEBUG "${COLLADA_LIBRARY_RELEASE}")
    ELSEIF(COLLADA_LIBRARY_DEBUG AND NOT COLLADA_LIBRARY_RELEASE)
        SET(COLLADA_LIBRARY_RELEASE "${COLLADA_LIBRARY_DEBUG}")
    ENDIF(COLLADA_LIBRARY_RELEASE AND NOT COLLADA_LIBRARY_DEBUG)
ENDIF(NOT WIN32)

# set output variables
IF(COLLADA_FOUND)
    GET_FILENAME_COMPONENT(__COLLADA_LIB_DIR_RELEASE "${COLLADA_LIBRARY_RELEASE}" PATH)
    GET_FILENAME_COMPONENT(__COLLADA_LIB_DIR_DEBUG   "${COLLADA_LIBRARY_DEBUG}"   PATH)

    SET(COLLADA_LIBRARY_DIRS "${__COLLADA_LIB_DIR_RELEASE}"
                             "${__COLLADA_LIB_DIR_DEBUG}"  )
    SET(COLLADA_INCLUDE_DIRS "${COLLADA_DAE_INCLUDE_DIR}"
                             "${COLLADA_DOM_INCLUDE_DIR}"  )
    
    SET(COLLADA_LIBRARIES "${COLLADA_LIBRARY_RELEASE}")
ENDIF(COLLADA_FOUND)
