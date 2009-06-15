
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(OpenSGExamplesTutorial)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../../CMake")

# show build command lines
SET(CMAKE_VERBOSE_MAKEFILE ON)

#############################################################################
# find sources

FILE(GLOB SRCFILES "*.cpp")

#############################################################################
# get dependencies

SET(OSG_COMPONENTS OSGBase
                   OSGCluster
                   OSGDrawable
                   OSGFileIO
                   OSGGroup
                   OSGImageFileIO
                   OSGState
                   OSGSystem
                   OSGUtil
                   OSGText
                   OSGWindow
                   OSGWindowGLUT)

SET(DEP_INCLUDE_DIRS)
SET(DEP_LIBRARY_DIRS)
SET(DEP_LIBRARIES)

#############
#### GL

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLU REQUIRED)
LIST(APPEND DEP_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
LIST(APPEND DEP_LIBRARIES ${OPENGL_gl_LIBRARY})
LIST(APPEND DEP_LIBRARIES ${OPENGL_glu_LIBRARY})

#############
#### GLUT

FIND_PACKAGE(GLUT REQUIRED)
LIST(APPEND DEP_INCLUDE_DIRS ${GLUT_INCLUDE_DIR})
LIST(APPEND DEP_LIBRARIES ${GLUT_LIBRARIES})

#############
#### Collada (optional, required if OSGFileIO is used 
####          and was built with collada support)

FIND_PACKAGE(Collada)

IF(COLLADA_FOUND)
    LIST(APPEND DEP_INCLUDE_DIRS ${COLLADA_INCLUDE_DIRS})
    LIST(APPEND DEP_LIBRARY_DIRS ${COLLADA_LIBRARY_DIRS})
ENDIF(COLLADA_FOUND)

#############
#### Boost

SET(Boost_USE_MULTITHREAD ON)
SET(Boost_STATIC_LIBS OFF)

FIND_PACKAGE(Boost REQUIRED)

IF(Boost_FOUND)
    LIST(APPEND DEP_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    LIST(APPEND DEP_LIBRARY_DIRS ${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

#############
#### OpenSG

FIND_PACKAGE(OpenSG REQUIRED COMPONENTS ${OSG_COMPONENTS})

#############################################################################
# build executables

FOREACH(SRC ${SRCFILES})

    GET_FILENAME_COMPONENT(EXE ${SRC} NAME_WE)

    INCLUDE_DIRECTORIES(${OpenSG_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${DEP_INCLUDE_DIRS})

    LINK_DIRECTORIES(${OpenSG_LIBRARY_DIRS})
    LINK_DIRECTORIES(${DEP_LIBRARY_DIRS})

    ADD_EXECUTABLE(${EXE} ${SRC})

    TARGET_LINK_LIBRARIES(${EXE} ${OpenSG_LIBRARIES})
    TARGET_LINK_LIBRARIES(${EXE} ${DEP_LIBRARIES})
ENDFOREACH(SRC)
