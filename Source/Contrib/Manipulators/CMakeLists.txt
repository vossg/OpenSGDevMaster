
IF(NOT OSGBUILD_MANIPULATORS)
    RETURN()
ENDIF(NOT OSGBUILD_MANIPULATORS)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

#################
# OSGContribGUI
#################

CLEAR_PROJECT(OSGContribGUI)

SET(OSGContribGUI_OSG_Dependencies OSGBase
                                   OSGSystem
                                   OSGGroup
                                   OSGDrawable
                                   OSGState)

SET(OSGContribGUI_Test_OSG_Dependencies OSGWindow OSGUtil OSGWindowGLUT)

SETUP_PROJECT(OSGContribGUI OSG_COMPILECONTRIBGUILIB)
