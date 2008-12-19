
IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

IF(${PROJECT_NAME} STREQUAL "OSGCluster")

    ############
    # OSGCluster
    ############

    CLEAR_PROJECT(OSGCluster)

    SET(OSGCluster_OSG_Dependencies OSGWindow OSGGroup OSGDrawable OSGState)

    SET(OSGCluster_Test_OSG_Dependencies OSGUtil OSGWindowGLUT)

    SETUP_PROJECT(OSGCluster OSG_COMPILECLUSTERLIB)

ENDIF()

