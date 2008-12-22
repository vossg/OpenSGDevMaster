
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

SET(OSGContribBackgroundLoader_Test_Ext_Inc_Dependencies OSG_GLUT_INC_DIR)

SETUP_PROJECT(OSGContribBackgroundLoader OSG_COMPILECONTRIBBACKGROUNDLOADERLIB)

