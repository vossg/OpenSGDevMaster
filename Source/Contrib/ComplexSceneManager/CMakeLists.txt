
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

IF(GLUT_FOUND)
    SET(OSGContribCSM_OSG_Dependencies ${OSGContribCSM_OSG_Dependencies}
                                       OSGWindowGLUT)
ENDIF(GLUT_FOUND)

SETUP_PROJECT(OSGContribCSM OSG_COMPILECONTRIBCSMLIB)
