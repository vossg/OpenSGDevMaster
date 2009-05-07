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
    /usr/include
    /usr/include/colladadom
    /sw/include
    /opt/local/include
    /opt/local/include/colladadom
    /opt/include
    /opt/include/colladadom)

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

# handle COLLADA_ROOT_DIR input variable
IF(COLLADA_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${COLLADA_ROOT_DIR} COLLADA_ROOT_DIR)

    SET(__COLLADA_INCLUDE_SEARCH_DIRS "${COLLADA_ROOT_DIR}/include"
                                      "${COLLADA_ROOT_DIR}/include/colladadom"
                                      "${__COLLADA_INCLUDE_SEARCH_DIRS}")
    SET(__COLLADA_LIBRARY_SEARCH_DIRS "${COLLADA_ROOT_DIR}/lib"
                                      "${COLLADA_ROOT_DIR}/lib64"
                                      "${__COLLADA_LIBRARY_SEARCH_DIRS}")
ENDIF(COLLADA_ROOT_DIR)

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

# locate libraries
FIND_LIBRARY(COLLADA_LIBRARY_RELEASE
    NAMES collada_dom collada14dom libcollada14dom21
    PATHS ${__COLLADA_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(COLLADA_LIBRARY_DEBUG
    NAMES collada_dom-d collada14dom-d libcollada14dom21-d
    PATHS ${__COLLADA_LIBRARY_SEARCH_DIRS})


# handle the QUIETLY and REQUIRED arguments and set COLLADA_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COLLADA DEFAULT_MSG COLLADA_LIBRARY_RELEASE
                                                      COLLADA_DAE_INCLUDE_DIR
                                                      COLLADA_DOM_INCLUDE_DIR)

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
