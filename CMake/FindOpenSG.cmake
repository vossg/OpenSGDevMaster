# - Find OpenSG 2 libraries
# Find the specified OpenSG 2 libraries and header files.
#
# Since OpenSG consists of a number of libraries you need to specify which
# of those you want to use. To do so, pass a list of their names after
# the COMPONENTS argument to FIND_PACKAGE. A typical call looks like this:
# FIND_PACKAGE(OpenSG REQUIRED COMPONENTS OSGBase OSGSystem OSGDrawable)
#
# This module specifies the following variables:
#  OpenSG_INCLUDE_DIRS
#  OpenSG_LIBRARIES
#  OpenSG_LIBRARY_DIRS
#
#  For each component COMP the capitalized name (e.g. OSGBASE, OSGSYSTEM):
#  OpenSG_${COMP}_LIBRARY
#  OpenSG_${COMP}_LIBRARY_RELEASE
#  OpenSG_${COMP}_LIBRARY_DEBUG
#
#  You can control where this module attempts to locate libraries and headers:
#  you can use the following input variables:
#  OPENSG_ROOT          root of an installed OpenSG with include/OpenSG and lib below it
#  OPENSG_INCLUDE_DIR   header directory
#  OPENSG_LIBRARY_DIR   library directory

# OpenSG_DIR is what is automaticall added by cmake
IF(NOT OPENSG_ROOT AND OpenSG_DIR)
  SET(OPENSG_ROOT ${OpenSG_DIR})
ENDIF(NOT OPENSG_ROOT AND OpenSG_DIR)

IF(NOT OSG_FORCE_CACHE_UPDATE)
  SET(__OpenSG_IN_CACHE TRUE)
  IF(OpenSG_INCLUDE_DIR)
    FOREACH(COMPONENT ${OpenSG_FIND_COMPONENTS})
        STRING(TOUPPER ${COMPONENT} COMPONENT)
        IF(NOT OpenSG_${COMPONENT}_FOUND)
            SET(__OpenSG_IN_CACHE FALSE)
        ENDIF(NOT OpenSG_${COMPONENT}_FOUND)
    ENDFOREACH(COMPONENT)
  ELSE(OpenSG_INCLUDE_DIR)
    SET(__OpenSG_IN_CACHE FALSE)
  ENDIF(OpenSG_INCLUDE_DIR)
ENDIF(NOT OSG_FORCE_CACHE_UPDATE)

# The reason that we failed to find OpenSG. This will be set to a
# user-friendly message when we fail to find some necessary piece of
# OpenSG.
set(OpenSG_ERROR_REASON)

############################################
#
# Check the existence of the libraries.
#
############################################
# This macro is directly taken from FindBoost.cmake that comes with the cmake
# distribution. It is NOT my work, only minor modifications have been made to
# remove references to boost.
#########################################################################

MACRO(__OpenSG_ADJUST_LIB_VARS basename component)
    IF(OpenSG_INCLUDE_DIR)
        IF(NOT WIN32)
          IF(OpenSG_${basename}_LIBRARY_DEBUG AND OpenSG_${basename}_LIBRARY_RELEASE)
          # if the generator supports configuration types then set
          # optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
              IF (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
                  SET(OpenSG_${basename}_LIBRARY optimized ${OpenSG_${basename}_LIBRARY_RELEASE} debug ${OpenSG_${basename}_LIBRARY_DEBUG})
              ELSE(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
                  # if there are no configuration types and CMAKE_BUILD_TYPE has no value
                  # then just use the release libraries
                  SET(OpenSG_${basename}_LIBRARY ${OpenSG_${basename}_LIBRARY_RELEASE} )
              ENDIF(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)

              SET(OpenSG_${basename}_LIBRARIES optimized ${OpenSG_${basename}_LIBRARY_RELEASE} debug ${OpenSG_${basename}_LIBRARY_DEBUG})
          ENDIF(OpenSG_${basename}_LIBRARY_DEBUG AND OpenSG_${basename}_LIBRARY_RELEASE)
    
          # if only the release version was found, set the debug variable also to the release version
          IF(OpenSG_${basename}_LIBRARY_RELEASE AND NOT OpenSG_${basename}_LIBRARY_DEBUG)
              SET(OpenSG_${basename}_LIBRARY       ${OpenSG_${basename}_LIBRARY_RELEASE})
              SET(OpenSG_${basename}_LIBRARIES     ${OpenSG_${basename}_LIBRARY_RELEASE})
          ENDIF(OpenSG_${basename}_LIBRARY_RELEASE AND NOT OpenSG_${basename}_LIBRARY_DEBUG)
    
          # if only the debug version was found, set the release variable also to the debug version
          IF(OpenSG_${basename}_LIBRARY_DEBUG AND NOT OpenSG_${basename}_LIBRARY_RELEASE)
              SET(OpenSG_${basename}_LIBRARY         ${OpenSG_${basename}_LIBRARY_DEBUG})
              SET(OpenSG_${basename}_LIBRARIES       ${OpenSG_${basename}_LIBRARY_DEBUG})
          ENDIF(OpenSG_${basename}_LIBRARY_DEBUG AND NOT OpenSG_${basename}_LIBRARY_RELEASE)
        
          IF(OpenSG_${basename}_LIBRARY)
              SET(OpenSG_${basename}_LIBRARY ${OpenSG_${basename}_LIBRARY} CACHE FILEPATH "The OpenSG ${basename} library")
              GET_FILENAME_COMPONENT(OpenSG_LIBRARY_DIRS "${OpenSG_${basename}_LIBRARY}" PATH)
              SET(OpenSG_LIBRARY_DIRS ${OpenSG_LIBRARY_DIRS} CACHE FILEPATH "OpenSG library directory")
              SET(OpenSG_${basename}_FOUND ON CACHE INTERNAL "Whether the OpenSG ${basename} library found")
          ENDIF(OpenSG_${basename}_LIBRARY)
        ELSE(NOT WIN32)
          IF(OpenSG_${basename}_LIBRARY_DEBUG OR OpenSG_${basename}_LIBRARY_DEBUGOPT OR 
             OpenSG_${basename}_LIBRARY_RELEASE OR OpenSG_${basename}_LIBRARY_RELEASENOOPT)

              SET(OpenSG_${basename}_FOUND ON CACHE INTERNAL "Whether the OpenSG ${basename} library found")

              SET(OpenSG_${basename}_LIBRARY ${component})
          ENDIF()
        ENDIF(NOT WIN32)
    ENDIF(OpenSG_INCLUDE_DIR)

    # Make variables changeble to the advanced user
    MARK_AS_ADVANCED(
        OpenSG_${basename}_LIBRARY
        OpenSG_${basename}_LIBRARY_RELEASE
        OpenSG_${basename}_LIBRARY_DEBUG
    )
ENDMACRO(__OpenSG_ADJUST_LIB_VARS)


FUNCTION(SETUP_OSG_LIB_TARGETS COMPONENT UPPERCOMPONENT)

  ADD_LIBRARY(${COMPONENT} SHARED IMPORTED)

  IF(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE)

    GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR_OPT ${OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE}
                           PATH)
      
    IF(UNIX)
      SET(OSG_IMP_RELEASE IMPORTED_LOCATION_RELEASE ${OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE})
    ELSE(UNIX)
      SET(OSG_IMP_RELEASE IMPORTED_IMPLIB_RELEASE ${OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE}
                          IMPORTED_LOCATION_RELEASE ${OSG_TMP_LIB_DIR_OPT})
    ENDIF(UNIX)

  ENDIF(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE)


  IF(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT)

    GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR_OPT ${OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT}
                           PATH)
      
    IF(UNIX)
      SET(OSG_IMP_RELEASENOOPT IMPORTED_LOCATION_RELEASENOOPT ${OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT})
    ELSE(UNIX)
      SET(OSG_IMP_RELEASENOOPT IMPORTED_IMPLIB_RELEASENOOPT ${OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT} 
                               IMPORTED_LOCATION_RELEASENOOPT ${OSG_TMP_LIB_DIR_OPT})
    ENDIF(UNIX)

  ENDIF(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT)


  IF(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG)

    GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR_DBG ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG}
                           PATH)

    IF(UNIX)
      SET(OSG_IMP_DEBUG IMPORTED_LOCATION_DEBUG ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG})
      SET(OSG_IMP_DEBUG ${OSG_IMP_DEBUG} IMPORTED_LOCATION_DEBUGGV ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG})
    ELSE(UNIX)
      SET(OSG_IMP_DEBUG IMPORTED_IMPLIB_DEBUG ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG}
                        IMPORTED_LOCATION_DEBUG ${OSG_TMP_LIB_DIR_DBG})
    ENDIF(UNIX)

  ENDIF(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG)


  IF(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT)

    GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR_DBG ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT}
                           PATH)

    IF(UNIX)
      SET(OSG_IMP_DEBUGOPT IMPORTED_LOCATION_DEBUGOPT ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT})
      SET(OSG_IMP_DEBUGOPT ${OSG_IMP_DEBUGOPT} IMPORTED_LOCATION_DEBUGOPTGV ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT})
    ELSE(UNIX)
      SET(OSG_IMP_DEBUGOPT IMPORTED_IMPLIB_DEBUGOPT ${OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT}
                           IMPORTED_LOCATION_DEBUGOPT ${OSG_TMP_LIB_DIR_DBG})
    ENDIF(UNIX)

  ENDIF(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT)

  IF(OSG_IMP_RELEASE OR OSG_IMP_RELEASENOOPT OR OSG_IMP_DEBUG OR OSG_IMP_DEBUGOPT)
    SET_TARGET_PROPERTIES(${COMPONENT} PROPERTIES
                          ${OSG_IMP_RELEASE}
                          ${OSG_IMP_RELEASENOOPT}
                          ${OSG_IMP_DEBUG}
                          ${OSG_IMP_DEBUGOPT}       )
  ENDIF(OSG_IMP_RELEASE OR OSG_IMP_RELEASENOOPT OR OSG_IMP_DEBUG OR OSG_IMP_DEBUGOPT)  

ENDFUNCTION(SETUP_OSG_LIB_TARGETS)

#-------------------------------------------------------------------------------


IF(__OpenSG_IN_CACHE)
    # values are already in the cache

    SET(OpenSG_FOUND TRUE)
    FOREACH(COMPONENT ${OpenSG_FIND_COMPONENTS})
        STRING(TOUPPER ${COMPONENT} UPPERCOMPONENT)

        # avoid setting up componentes more than once - which is not
        # allowed for import libraries
        IF(NOT TARGET ${COMPONENT})
            __OpenSG_ADJUST_LIB_VARS(${UPPERCOMPONENT} ${COMPONENT})

            SET(OpenSG_LIBRARIES ${OpenSG_LIBRARIES} ${OpenSG_${UPPERCOMPONENT}_LIBRARY})
            SETUP_OSG_LIB_TARGETS(${COMPONENT} ${UPPERCOMPONENT})
        ENDIF(NOT TARGET ${COMPONENT})
    ENDFOREACH(COMPONENT)

    SET(OpenSG_INCLUDE_DIRS "${OpenSG_INCLUDE_DIR}" "${OpenSG_INCLUDE_DIR}/OpenSG")

ELSE(__OpenSG_IN_CACHE)
    # need to search for libs

    SET(__OpenSG_INCLUDE_SEARCH_DIRS
        C:/OpenSG/include
        "C:/OpenSG"
        "$ENV{ProgramFiles}/OpenSG"
        /sw/local/include
    )

    SET(__OpenSG_LIBRARIES_SEARCH_DIRS
        C:/OpenSG/lib
        "C:/OpenSG"
        "$ENV{ProgramFiles}/OpenSG"
        /sw/local/lib
    )

    # handle input variable OPENSG_ROOT
    IF(OPENSG_ROOT)
        FILE(TO_CMAKE_PATH ${OPENSG_ROOT} OPENSG_ROOT)
        SET(__OpenSG_INCLUDE_SEARCH_DIRS
            ${OPENSG_ROOT}/include
            ${OPENSG_ROOT}
            ${__OpenSG_INCLUDE_SEARCH_DIRS})

        SET(__OpenSG_LIBRARIES_SEARCH_DIRS
            ${OPENSG_ROOT}/lib
            ${OPENSG_ROOT}/stage/lib
            ${__OpenSG_LIBRARIES_SEARCH_DIRS})
    ENDIF(OPENSG_ROOT)

    # handle input variable OPENSG_INCLUDE_DIR
    IF(OPENSG_INCLUDE_DIR)
        FILE(TO_CMAKE_PATH ${OPENSG_INCLUDE_DIR} OPENSG_INCLUDE_DIR)
        SET(__OpenSG_INCLUDE_SEARCH_DIRS
            ${OPENSG_INCLUDE_DIR} ${__OpenSG_INCLUDE_SEARCH_DIRS})
    ENDIF(OPENSG_INCLUDE_DIR)

    # handle input variable OPENSG_LIBRARY_DIR
    IF(OPENSG_LIBRARY_DIR)
        FILE(TO_CMAKE_PATH ${OPENSG_LIBRARY_DIR} OPENSG_LIBRARY_DIR)
        SET(__OpenSG_LIBRARIES_SEARCH_DIRS
            ${OPENSG_LIBRARY_DIR} ${__OpenSG_LIBRARIES_SEARCH_DIRS})
    ENDIF(OPENSG_LIBRARY_DIR)


    IF(NOT OpenSG_INCLUDE_DIR)
        # try to find include dirrectory by searching for OSGConfigured.h

        FIND_PATH(OpenSG_INCLUDE_DIR
            NAMES         OpenSG/OSGConfigured.h
            HINTS         ${__OpenSG_INCLUDE_SEARCH_DIRS})
    ENDIF(NOT OpenSG_INCLUDE_DIR)

    # ------------------------------------------------------------------------
    #  Begin finding OpenSG libraries
    # ------------------------------------------------------------------------
    FOREACH(COMPONENT ${OpenSG_FIND_COMPONENTS})
        STRING(TOUPPER ${COMPONENT} UPPERCOMPONENT)
        SET(OpenSG_${UPPERCOMPONENT}_LIBRARY "OpenSG_${UPPERCOMPONENT}_LIBRARY-NOTFOUND" )
        SET(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE "OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE-NOTFOUND" )
        SET(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG "OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG-NOTFOUND")

        IF(WIN32)
          SET(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT "OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT-NOTFOUND" )
          SET(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT "OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT-NOTFOUND")
        ENDIF(WIN32)

        FIND_LIBRARY(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASE
            NAMES  ${COMPONENT}
            HINTS  ${__OpenSG_LIBRARIES_SEARCH_DIRS}
            PATH_SUFFIXES "release" "rel" "opt" "relwithdbg"
        )
   
        IF(WIN32)
          FIND_LIBRARY(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG
              NAMES  "${COMPONENT}D"
              HINTS  ${__OpenSG_LIBRARIES_SEARCH_DIRS}
              PATH_SUFFIXES "debug" "dbg" "debugopt"
          )

          FIND_LIBRARY(OpenSG_${UPPERCOMPONENT}_LIBRARY_RELEASENOOPT
              NAMES  "${COMPONENT}RN"
              HINTS  ${__OpenSG_LIBRARIES_SEARCH_DIRS}
              PATH_SUFFIXES "relnoopt"
          )

          FIND_LIBRARY(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUGOPT
              NAMES  "${COMPONENT}DO"
              HINTS  ${__OpenSG_LIBRARIES_SEARCH_DIRS}
              PATH_SUFFIXES "debugopt"
          )
        ELSE(WIN32)
          FIND_LIBRARY(OpenSG_${UPPERCOMPONENT}_LIBRARY_DEBUG
              NAMES  ${COMPONENT}
              HINTS  ${__OpenSG_LIBRARIES_SEARCH_DIRS}
              PATH_SUFFIXES "debug" "dbg"
          )
        ENDIF(WIN32)
    
        __OpenSG_ADJUST_LIB_VARS(${UPPERCOMPONENT} ${COMPONENT})

    ENDFOREACH(COMPONENT)
    # ------------------------------------------------------------------------
    #  End finding OpenSG libraries
    # ------------------------------------------------------------------------

    SET(OpenSG_INCLUDE_DIRS "${OpenSG_INCLUDE_DIR}" "${OpenSG_INCLUDE_DIR}/OpenSG")

    SET(OpenSG_FOUND FALSE)

    IF(OpenSG_INCLUDE_DIR)
        SET(OpenSG_FOUND TRUE)

        # check if all requested components were found
        SET(__OpenSG_CHECKED_COMPONENT FALSE)
        SET(__OpenSG_MISSING_COMPONENTS)

        FOREACH(COMPONENT ${OpenSG_FIND_COMPONENTS})
            STRING(TOUPPER ${COMPONENT} COMPONENT)
            SET(__OpenSG_CHECKED_COMPONENT TRUE)

            IF(NOT OpenSG_${COMPONENT}_FOUND)
                STRING(TOLOWER ${COMPONENT} COMPONENT)
                LIST(APPEND __OpenSG_MISSING_COMPONENTS ${COMPONENT})
                SET(OpenSG_FOUND FALSE)
            ENDIF(NOT OpenSG_${COMPONENT}_FOUND)
        ENDFOREACH(COMPONENT)

        IF(__OpenSG_MISSING_COMPONENTS)
            # We were unable to find some libraries, so generate a sensible
            # error message that lists the libraries we were unable to find.
            SET(OpenSG_ERROR_REASON
                "${OpenSG_ERROR_REASON}\nThe following OpenSG libraries could not be found:\n")
            FOREACH(COMPONENT ${__OpenSG_MISSING_COMPONENTS})
                SET(OpenSG_ERROR_REASON
                    "${OpenSG_ERROR_REASON}        ${COMPONENT}\n")
            ENDFOREACH(COMPONENT)
        
            LIST(LENGTH OpenSG_FIND_COMPONENTS __OpenSG_NUM_COMPONENTS_WANTED)
            LIST(LENGTH __OpenSG_MISSING_COMPONENTS __OpenSG_NUM_MISSING_COMPONENTS)
            IF(${__OpenSG_NUM_COMPONENTS_WANTED} EQUAL ${__OpenSG_NUM_MISSING_COMPONENTS})
                SET(OpenSG_ERROR_REASON
                "${OpenSG_ERROR_REASON}No OpenSG libraries were found. You may need to set OPENSG_LIBRARY_DIR to the directory containing OpenSG libraries or OPENSG_ROOT to the location of OpenSG.")
            ELSE(${__OpenSG_NUM_COMPONENTS_WANTED} EQUAL ${__OpenSG_NUM_MISSING_COMPONENTS})
                SET(OpenSG_ERROR_REASON
                "${OpenSG_ERROR_REASON}Some (but not all) of the required OpenSG libraries were found. You may need to install these additional OpenSG libraries. Alternatively, set OPENSG_LIBRARY_DIR to the directory containing OpenSG libraries or OPENSG_ROOT to the location of OpenSG.")
            ENDIF(${__OpenSG_NUM_COMPONENTS_WANTED} EQUAL ${__OpenSG_NUM_MISSING_COMPONENTS})
        ENDIF(__OpenSG_MISSING_COMPONENTS)

    ENDIF(OpenSG_INCLUDE_DIR)

    IF(OpenSG_FOUND)
        IF(NOT OpenSG_FIND_QUIETLY)
            MESSAGE(STATUS "OpenSG found.")
        ENDIF(NOT OpenSG_FIND_QUIETLY)

        IF (NOT OpenSG_FIND_QUIETLY)
            MESSAGE(STATUS "Found the following OpenSG libraries:")
        ENDIF(NOT OpenSG_FIND_QUIETLY)

        FOREACH(COMPONENT  ${OpenSG_FIND_COMPONENTS})
            STRING(TOUPPER ${COMPONENT} UPPERCOMPONENT)
            IF(OpenSG_${UPPERCOMPONENT}_FOUND)
                IF(NOT OpenSG_FIND_QUIETLY)
                    MESSAGE(STATUS "  ${COMPONENT}")
                ENDIF(NOT OpenSG_FIND_QUIETLY)

                SETUP_OSG_LIB_TARGETS(${COMPONENT} ${UPPERCOMPONENT})

                SET(OpenSG_LIBRARIES ${OpenSG_LIBRARIES} ${OpenSG_${UPPERCOMPONENT}_LIBRARY})
            ENDIF(OpenSG_${UPPERCOMPONENT}_FOUND)
        ENDFOREACH(COMPONENT)

    ELSE(OpenSG_FOUND)
        IF(OpenSG_FIND_REQUIRED)
            MESSAGE(SEND_ERROR "Unable to find the requested OpenSG libraries.\n${OpenSG_ERROR_REASON}")
        ENDIF(OpenSG_FIND_REQUIRED)
    ENDIF(OpenSG_FOUND)

ENDIF(__OpenSG_IN_CACHE)
