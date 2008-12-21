
IF(NOT OSGBUILD_COMPLEXSCENEMANAGER)
    RETURN()
ENDIF(NOT OSGBUILD_COMPLEXSCENEMANAGER)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)


#################
# OSGContribCSM
#################

CLEAR_PROJECT(OSGContribCSM)

SET(OSGContribCSM_OSG_Dependencies OSGBase
                                   OSGSystem
                                   OSGDrawable  
                                   OSGCluster
                                   OSGFileIO
                                   OSGUtil)

IF(UNIX)
    SET(OSGContribCSM_OSG_Dependencies ${OSGContribCSM_OSG_Dependencies}
                                       OSGWindowX)
ENDIF(UNIX)

IF(GLUT_FOUND AND OSGBUILD_WINDOWGLUT)
    SET(OSGContribCSM_OSG_Dependencies ${OSGContribCSM_OSG_Dependencies}
                                       OSGWindowGLUT)

    IF(WIN32)
        SET(OSGContribCSM_Ext_Inc_Dependencies GLUT_INCLUDE_DIR)
    ENDIF(WIN32)
ENDIF(GLUT_FOUND AND OSGBUILD_WINDOWGLUT)

IF(WIN32)
    SET(OSGContribCSM_OSG_Dependencies ${OSGContribCSM_OSG_Dependencies}
                                       OSGWindowWIN32)
ENDIF(WIN32)

SETUP_PROJECT(OSGContribCSM OSG_COMPILECONTRIBCSMLIB)
