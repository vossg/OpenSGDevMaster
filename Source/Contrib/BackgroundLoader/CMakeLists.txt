
IF(NOT OSGBUILD_BACKGROUNDLOADER)
    RETURN()
ENDIF(NOT OSGBUILD_BACKGROUNDLOADER)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

############################
# OSGContribBackgroundLoader
############################

CLEAR_PROJECT(OSGContribBackgroundLoader)

SET(OSGContribBackgroundLoader_OSG_Dependencies OSGBase
                                                OSGSystem
                                                OSGDrawable
                                                OSGUtil)

SET(OSGContribBackgroundLoader_Test_OSG_Dependencies OSGGroup
                                                     OSGWindow
                                                     OSGWindowGLUT)

SET(OSGContribBackgroundLoader_Ext_Lib_Dependencies OSG_BOOST_LIBS)

IF(WIN32 AND GLUT_FOUND)
    SET(OSGContribBackgroundLoader_Ext_Inc_Dependencies GLUT_INCLUDE_DIR)
ENDIF(WIN32 AND GLUT_FOUND)

SETUP_PROJECT(OSGContribBackgroundLoader OSG_COMPILECONTRIBBACKGROUNDLOADERLIB)

