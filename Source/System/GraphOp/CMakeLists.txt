
IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)


IF(${PROJECT_NAME} STREQUAL "OSGSystem")

    ADD_SUBDIRECTORY(Base)

ELSEIF(${PROJECT_NAME} STREQUAL "OSGUtil")

    #################
    # OSGEffectGroups
    #################

    CLEAR_PROJECT(OSGUtil)

    SET(OSGUtil_Add_SubDir ../Window ../Statistics)
    SET(OSGUtil_OSG_Dependencies OSGGroup 
                                 OSGState
                                 OSGDrawable 
                                 OSGWindow 
                                 OSGText)

    SET(OSGUtil_Test_OSG_Dependencies OSGWindowGLUT)
    SET(OSGUtil_Test_Ext_Inc_Dependencies OSG_GLUT_INC_DIR)

    SETUP_PROJECT(OSGUtil OSG_COMPILEUTILLIB)

ENDIF()
