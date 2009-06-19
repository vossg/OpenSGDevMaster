
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CubesLib)

# we need to find the cmake modules that come with OpenSG, the easiest way is to use
# the ones in the source tree. If you only have an installed version of OpenSG,
# the path below to <prefix>/share/OpenSG/cmake
LIST(APPEND CMAKE_MODULE_PATH "${CubesLib_SOURCE_DIR}/../../../../CMake")

#############################################################################
# find sources

FILE(GLOB SRCFILES "*.cpp")

#############################################################################
# get dependencies

SET(DEP_INCLUDE_DIRS)
SET(DEP_LIBRARY_DIRS)
SET(DEP_LIBRARIES)

SET(OSG_COMPONENTS OSGBase
                   OSGDrawable
                   OSGGroup
                   OSGState
                   OSGSystem
                   OSGUtil
                   OSGWindow
                   OSGWindowGLUT)

IF(UNIX)
    IF(APPLE)
        LIST(APPEND OSG_COMPONENTS OSGWindowCarbon)
    ELSE(APPLE)
        LIST(APPEND OSG_COMPONENTS OSGWindowX)
    ENDIF(APPLE)
ENDIF(UNIX)

IF(WIN32)
    LIST(APPEND OSG_COMPONENTS OSGWindowWIN32)
ENDIF(WIN32)

#############
#### GLUT

FIND_PACKAGE(GLUT REQUIRED)
LIST(APPEND DEP_INCLUDE_DIRS ${GLUT_INCLUDE_DIR})
LIST(APPEND DEP_LIBRARIES ${GLUT_LIBRARIES})

IF(UNIX AND NOT APPLE)
    FIND_PACKAGE(X11)

    IF(X11_FOUND)
        LIST(APPEND DEP_INCLUDE_DIRS ${X11_X11_INCLUDE_PATH})
        LIST(APPEND DEP_LIBRARIES ${X11_X11_LIB})
    ELSE(X11_FOUND)
        MESSAGE(FATAL_ERROR "Could not find X11 libraries")
    ENDIF(X11_FOUND)
ENDIF(UNIX AND NOT APPLE)

#############
#### Boost

SET(Boost_USE_MULTITHREAD ON)
SET(Boost_STATIC_LIBS OFF)

FIND_PACKAGE(Boost REQUIRED)

IF(Boost_FOUND AND Boost_MINOR_VERSION GREATER "34")
    SET(Boost_COMPONENTS system ${Boost_COMPONENTS})

    FIND_PACKAGE(Boost COMPONENTS ${Boost_COMPONENTS} REQUIRED)
ENDIF(Boost_FOUND AND Boost_MINOR_VERSION GREATER "34")

IF(Boost_FOUND)
    LIST(APPEND DEP_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    LIST(APPEND DEP_LIBRARY_DIRS ${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

#############
#### OpenSG

FIND_PACKAGE(OpenSG REQUIRED COMPONENTS ${OSG_COMPONENTS})

#############################################################################
# build library

INCLUDE_DIRECTORIES(${OpenSG_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${DEP_INCLUDE_DIRS}   )

LINK_DIRECTORIES(${OpenSG_LIBRARY_DIRS})
LINK_DIRECTORIES(${DEP_LIBRARY_DIRS}   )

ADD_LIBRARY(CubesLib SHARED ${SRCFILES})

TARGET_LINK_LIBRARIES(CubesLib ${OpenSG_LIBRARIES})
TARGET_LINK_LIBRARIES(CubesLib ${DEP_LIBRARIES})
