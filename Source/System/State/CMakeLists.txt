
IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

IF(${PROJECT_NAME} STREQUAL "OSGSystem")

    COLLECT_SUBDIRS()

ELSEIF(${PROJECT_NAME} STREQUAL "OSGState")

    ###########
    # OSGState
    ###########

    CLEAR_PROJECT(OSGState)

    SET(OSGState_OSG_Dependencies OSGSystem)

    SET(OSGState_Test_OSG_Dependencies OSGDrawable
                                       OSGWindowGLUT
                                       OSGUtil)

    SETUP_PROJECT(OSGState OSG_COMPILESTATELIB)

ENDIF()
