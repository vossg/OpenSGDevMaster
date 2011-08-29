
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

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
                   OSGUtil    )

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
#### OpenGL

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLU REQUIRED)

LIST(APPEND DEP_LIBRARIES ${OPENGL_gl_LIBRARY})
LIST(APPEND DEP_LIBRARIES ${OPENGL_glu_LIBRARY})

#############
#### OpenSG

FIND_PACKAGE(OpenSG REQUIRED COMPONENTS ${OSG_COMPONENTS})

#############################################################################
# build library

INCLUDE_DIRECTORIES(${OpenSG_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${DEP_INCLUDE_DIRS}   )

LINK_DIRECTORIES(${OpenSG_LIBRARY_DIRS})
LINK_DIRECTORIES(${DEP_LIBRARY_DIRS}   )

# make sure symbols are marked dllexport on windows
ADD_DEFINITIONS(-DOSG_COMPILECUBESLIBLIB)

ADD_LIBRARY(CubesLib SHARED ${SRCFILES})

TARGET_LINK_LIBRARIES(CubesLib ${OpenSG_LIBRARIES})
TARGET_LINK_LIBRARIES(CubesLib ${DEP_LIBRARIES})
