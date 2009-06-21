
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CubesAppUnified)

# we need to find the cmake modules that come with OpenSG, the easiest way is to use
# the ones in the source tree. If you only have an installed version of OpenSG,
# the path below to <prefix>/share/OpenSG/cmake
LIST(APPEND CMAKE_MODULE_PATH "${CubesAppUnified_SOURCE_DIR}/../../../../CMake")

#############################################################################
# find sources

FILE(GLOB SRCFILES "*.cpp")

#############################################################################
# get dependencies

# these variables contain info about libs and headers
SET(DEP_INCLUDE_DIRS)
SET(DEP_LIBRARY_DIRS)
SET(DEP_LIBRARIES)

# the list of OpenSG libraries needed
SET(OSG_COMPONENTS OSGBase
                   OSGDrawable
                   OSGGroup
                   OSGState
                   OSGSystem
                   OSGUtil
                   OSGWindow
                   OSGWindowGLUT)

# append the platform window library
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

#############
#### Cubes

# make sure the source directory is searched for headers
LIST(APPEND DEP_INCLUDE_DIRS "${CubesAppUnified_SOURCE_DIR}")

#############################################################################
# build application

INCLUDE_DIRECTORIES(${OpenSG_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${DEP_INCLUDE_DIRS}   )

LINK_DIRECTORIES(${OpenSG_LIBRARY_DIRS})
LINK_DIRECTORIES(${DEP_LIBRARY_DIRS}   )

ADD_EXECUTABLE(CubesAppUnified ${SRCFILES})

TARGET_LINK_LIBRARIES(CubesAppUnified ${OpenSG_LIBRARIES})
TARGET_LINK_LIBRARIES(CubesAppUnified ${DEP_LIBRARIES})
