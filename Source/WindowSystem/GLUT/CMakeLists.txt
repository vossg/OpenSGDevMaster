
IF(NOT OSGBUILD_WINDOWGLUT)
    RETURN()
ENDIF(NOT OSGBUILD_WINDOWGLUT)

IF(NOT GLUT_FOUND)
    RETURN()
ENDIF(NOT GLUT_FOUND)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

#################
# OSGWindowGLUT
#################

CLEAR_PROJECT(OSGWindowGLUT)

SET(OSGWindowGLUT_OSG_Dependencies OSGBase OSGSystem)

SET(OSGWindowGLUT_Ext_Inc_Dependencies OSG_GLUT_INC_DIR)
SET(OSGWindowGLUT_Ext_Lib_Dependencies GLUT_LIBRARIES)

SET(OSGWindowGLUT_Test_OSG_Dependencies OSGGroup 
                                        OSGDrawable
                                        OSGState
                                        OSGText
                                        OSGWindow
                                        OSGFileIO
                                        OSGImageFileIO
                                        OSGUtil)

SETUP_PROJECT(OSGWindowGLUT OSG_COMPILEWINDOWGLUTLIB)

