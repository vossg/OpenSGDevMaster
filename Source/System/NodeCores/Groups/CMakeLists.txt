
IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

IF(${PROJECT_NAME} STREQUAL "OSGSystem")

    ADD_SUBDIRECTORY(Base)

ELSEIF(${PROJECT_NAME} STREQUAL "OSGGroup")

    ###########
    # OSGGroup
    ###########

    CLEAR_PROJECT(OSGGroup)

    SET(OSGGroup_OSG_Dependencies OSGState)

    SET(OSGGroup_Test_OSG_Dependencies OSGDrawable
                                       OSGWindowGLUT
                                       OSGUtil)

    SET(OSGGroup_Test_Ext_Inc_Dependencies OSG_GLUT_INC_DIR)

    SETUP_PROJECT(OSGGroup OSG_COMPILEGROUPLIB)

ELSEIF(${PROJECT_NAME} STREQUAL "OSGEffectGroups")

    ADD_SUBDIRECTORY(Effects)

ENDIF()

