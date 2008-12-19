
IF(NOT OSGBUILD_VTK)
    RETURN()
ENDIF(NOT OSGBUILD_VTK)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

###############
# OSGContribVTK
###############

CLEAR_PROJECT(OSGContribVTK)

SET(OSGContribVTK_OSG_Dependencies OSGBase
                                   OSGSystem
                                   OSGDrawable
                                   OSGState)

IF(VTK_FOUND)

    SET(OSGContribVTK_Ext_Inc_Dependencies VTK_INCLUDE_DIRS)
    SET(OSGContribVTK_Ext_LibDir_Dependencies VTK_LIBRARY_DIRS)
    SET(OSGContribVTK_Ext_Lib_Dependencies OSG_VTK_LIBS)

ENDIF(VTK_FOUND)

SET(OSGContribVTK_Test_OSG_Dependencies OSGGroup
                                        OSGCluster
                                        OSGUtil 
                                        OSGWindow
                                        OSGWindowGLUT)

SETUP_PROJECT(OSGContribVTK OSG_COMPILECONTRIBVTKLIB)

