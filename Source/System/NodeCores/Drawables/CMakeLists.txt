
IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

IF(${PROJECT_NAME} STREQUAL "OSGSystem")

    ADD_SUBDIRECTORY(Base)

ELSEIF(${PROJECT_NAME} STREQUAL "OSGDrawable")

    ###########
    # OSGWindow
    ###########

    CLEAR_PROJECT(OSGDrawable)

    SET(OSGDrawable_Add_SubDir ../../Material)
    SET(OSGDrawable_OSG_Dependencies OSGState)

    SET(OSGDrawable_Test_OSG_Dependencies OSGWindowGLUT
                                          OSGUtil)

    SETUP_PROJECT(OSGDrawable OSG_COMPILEDRAWABLELIB)

ENDIF()
