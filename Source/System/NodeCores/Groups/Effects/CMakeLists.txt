
CHECK_PROJECT("OSGEffectGroups")

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)


IF(${PROJECT_NAME} STREQUAL "OSGEffectGroups")

    #################
    # OSGEffectGroups
    #################

    CLEAR_PROJECT(OSGEffectGroups)

    SET(OSGEffectGroups_OSG_Dependencies OSGGroup 
                                         OSGDrawable 
                                         OSGState 
                                         OSGWindow)

    SET(OSGEffectGroups_Test_OSG_Dependencies OSGUtil OSGWindowGLUT)

    SETUP_PROJECT(OSGEffectGroups OSG_COMPILEEFFECTGROUPSLIB)

ENDIF()

