
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(OpenSGSimpleExamples)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OpenSGSimpleExamples_SOURCE_DIR}/../../CMake")

# show build command lines
SET(CMAKE_VERBOSE_MAKEFILE ON)

#############################################################################
# get dependencies

SET(OSG_COMPONENTS OSGBase OSGCluster OSGDrawable OSGSystem OSGUtil OSGWindowGLUT)

SET(DEP_INCLUDE_DIRS)
SET(DEP_LIBRARY_DIRS)
SET(DEP_LIBRARIES)

#############
#### GLUT

FIND_PACKAGE(GLUT REQUIRED)
LIST(APPEND DEP_INCLUDE_DIRS ${GLUT_INCLUDE_DIRS})
LIST(APPEND DEP_LIBRARY_DIRS ${GLUT_LIBRARY_DIRS})
LIST(APPEND DEP_LIBRARIES ${GLUT_LIBRARIES})

#############
#### X11 (optional)

FIND_PACKAGE(X11)

IF(X11_FOUND)
    LIST(APPEND OSG_COMPONENTS OSGWindowX)
    LIST(APPEND DEP_INCLUDE_DIRS ${X11_X11_INCLUDE_PATH})
    LIST(APPEND DEP_LIBRARIES ${X11_X11_LIB})
ENDIF(X11_FOUND)

#############
#### OpenSG

FIND_PACKAGE(OpenSG REQUIRED COMPONENTS ${OSG_COMPONENTS})

#############################################################################
# find sources

FILE(GLOB SRCFILES "*.cpp")

IF(NOT X11_FOUND)
    LIST(REMOVE_ITEM SRCFILES "${PROJECT_SOURCE_DIR}/clusterserverx.cpp")
ENDIF(NOT X11_FOUND)


# stuff that is broken -- these examples need to be fixed
LIST(REMOVE_ITEM SRCFILES "${PROJECT_SOURCE_DIR}/clusterclientshader.cpp")
LIST(REMOVE_ITEM SRCFILES "${PROJECT_SOURCE_DIR}/geometryshader.cpp")
LIST(REMOVE_ITEM SRCFILES "${PROJECT_SOURCE_DIR}/phongshaderwithglmaterials.cpp")
LIST(REMOVE_ITEM SRCFILES "${PROJECT_SOURCE_DIR}/shader.cpp")

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
