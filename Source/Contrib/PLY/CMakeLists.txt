
IF(NOT OSGBUILD_PLY)
    RETURN()
ENDIF(NOT OSGBUILD_PLY)

IF(OSG_VERBOSE_SCAN)
    MESSAGE( STATUS "Looking at : ${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(OSG_VERBOSE_SCAN)

###############
# OSGContribPLY
###############

CLEAR_PROJECT(OSGContribPLY)

SET(OSGContribPLY_OSG_Dependencies OSGBase
                                   OSGSystem
                                   OSGDrawable)

SETUP_PROJECT(OSGContribPLY OSG_COMPILECONTRIBPLYLIB)

