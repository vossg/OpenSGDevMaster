
IF(NOT OSGBUILD_SYSTEM)
    RETURN()
ENDIF(NOT OSGBUILD_SYSTEM)

###########
# OSGSystem
###########

CLEAR_PROJECT(OSGSystem)

SET(OSGSystem_OSG_Dependencies OSGBase)
SET(OSGSystem_Extra_Inc ${CMAKE_SOURCE_DIR}/Source/External)
SET(OSGSystem_Ext_Lib_Dependencies 
    ZLIB_LIBRARIES OPENGL_gl_LIBRARY OPENGL_glu_LIBRARY)

IF(WIN32 AND ZLIB_FOUND)
    SET(OSGSystem_Ext_Inc_Dependencies ZLIB_INCLUDE_DIR)
ENDIF(WIN32 AND ZLIB_FOUND)

SET(OSGSystem_Test_OSG_Dependencies OSGDrawable
                                    OSGState
                                    OSGGroup
                                    OSGWindow
                                    OSGWindowGLUT
                                    OSGUtil)

SET(OSGSystem_Test_Ext_Inc_Dependencies OSG_GLUT_INC_DIR)

SETUP_PROJECT(OSGSystem OSG_COMPILESYSTEMLIB)



###########
# The Rest
###########

IF(OSGBUILD_STATE)

    ###########
    # OSGState
    ###########

    PROJECT(OSGState)

    ADD_SUBDIRECTORY(State)

ENDIF(OSGBUILD_STATE)


IF(OSGBUILD_GROUP)

    ###########
    # OSGGroup
    ###########

    PROJECT(OSGGroup)

    ADD_SUBDIRECTORY(NodeCores)

ENDIF(OSGBUILD_GROUP)


IF(OSGBUILD_WINDOW)

    ############
    # OSGWindow
    ############

    PROJECT(OSGWindow)

    ADD_SUBDIRECTORY(Window)

ENDIF(OSGBUILD_WINDOW)


IF(OSGBUILD_DRAWABLE)

    #############
    # OSGDrawable
    #############

    PROJECT(OSGDrawable)

    ADD_SUBDIRECTORY(NodeCores)

ENDIF(OSGBUILD_DRAWABLE)


IF(OSGBUILD_TEXT)

    #############
    # OSGText
    #############

    PROJECT(OSGText)

    ADD_SUBDIRECTORY(Text)

ENDIF(OSGBUILD_TEXT)


IF(OSGBUILD_CLUSTER)

    #############
    # OSGCluster
    #############

    PROJECT(OSGCluster)

    ADD_SUBDIRECTORY(Cluster)

ENDIF(OSGBUILD_CLUSTER)


IF(OSGBUILD_EFFECTGROUPS)

    #################
    # OSGEffectGroups
    #################

    PROJECT(OSGEffectGroups)

    ADD_SUBDIRECTORY(NodeCores)

ENDIF(OSGBUILD_EFFECTGROUPS)


IF(OSGBUILD_UTIL)

    #################
    # OSGUtil
    #################

    PROJECT(OSGUtil)

    ADD_SUBDIRECTORY(GraphOp)

ENDIF(OSGBUILD_UTIL)


IF(OSGBUILD_FILEIO)

    #################
    # OSGFileIO
    #################

    PROJECT(OSGFileIO)

    ADD_SUBDIRECTORY(FileIO)

ENDIF(OSGBUILD_FILEIO)


IF(OSGBUILD_IMAGEFILEIO)

    #################
    # OSGImageFileIO
    #################

    PROJECT(OSGImageFileIO)

    ADD_SUBDIRECTORY(Image)

ENDIF(OSGBUILD_IMAGEFILEIO)
