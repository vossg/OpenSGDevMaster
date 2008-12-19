
IF(NOT OSGBUILD_WINDOWX)
    RETURN()
ENDIF(NOT OSGBUILD_WINDOWX)

IF(NOT UNIX)
    RETURN()
ENDIF(NOT UNIX)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

#################
# OSGWindowX
#################

CLEAR_PROJECT(OSGWindowX)

SET(OSGWindowX_OSG_Dependencies OSGBase OSGSystem)

SET(OSGWindowX_Ext_Lib_Dependencies OSG_X_LIBS)

SET(OSGWindowX_Test_OSG_Dependencies OSGDrawable 
                                     OSGGroup
                                     OSGWindow
                                     OSGUtil)

SETUP_PROJECT(OSGWindowX OSG_COMPILEWINDOWXLIB)

