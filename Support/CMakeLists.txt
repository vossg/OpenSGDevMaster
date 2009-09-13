CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(OpenSGSupport)

IF(NOT WIN32)
  MESSAGE(ERROR " Windows only, on unix or unix imposters use your package"
                " system to install the required packages")
ENDIF(NOT WIN32)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
                      "${OpenSGSupport_SOURCE_DIR}/../CMake")

##############################################
# Initial cache to make life easier on Windows
##############################################

IF(EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  INCLUDE(${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
ENDIF(EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)

##########################
# Disallow in-source build
##########################

IF("${OpenSGSupport_SOURCE_DIR}"  STREQUAL "${OpenSGSupport_BINARY_DIR}")
  MESSAGE(FATAL_ERROR "OpenSGSupport requires an out of source Build. \n"
                      "Please create a separate binary directory and run "
                      "CMake there.")
ENDIF("${OpenSGSupport_SOURCE_DIR}"  STREQUAL "${OpenSGSupport_BINARY_DIR}")


##############
# Compiler
##############

OPTION(BUILD_SHARED_LIBS "Set to ON to build dynamic libraries" ON)
OPTION(BUILD_STATIC_LIBS "Set to ON to build static libraries" ON)

IF(WIN32)
    OPTION(OSG_DISABLE_MICROSOFT_SECURE_CXXX "" OFF)
ENDIF(WIN32)

SET(OSG_PLATFORM_64 0)
SET(OSG_PLATFORM_32 0)
SET(OSG_LIBDIR_SUFFIX "")

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(OSG_PLATFORM_64 1)
    SET(OSG_LIBDIR_SUFFIX "64")
ELSE()
    SET(OSG_PLATFORM_32 1)
ENDIF()


IF(${CMAKE_CXX_PLATFORM_ID} STREQUAL "Linux")
    SET(LINUX 1)
ENDIF()

IF(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)


IF(NOT OSG_COMPILER_DEFAULTS)
   INCLUDE(../CMake/SetupCompiler.cmake)
   SET( OSG_COMPILER_DEFAULTS 1 CACHE INTERNAL "Defaults written" FORCE ) #INTERNAL
ENDIF(NOT OSG_COMPILER_DEFAULTS)

INCLUDE(../CMake/UpdateCompiler.cmake)
INCLUDE(../CMake/BuildFunctions.cmake)
INCLUDE(../CMake/ConfigurePackages.cmake)

SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)

FIND_PACKAGE(OpenGL)

OSG_CONFIGURE_BOOST()

ADD_SUBDIRECTORY(zlib)
ADD_SUBDIRECTORY(libpng)
ADD_SUBDIRECTORY(libjpeg)
ADD_SUBDIRECTORY(freeglut)
ADD_SUBDIRECTORY(libtiff)
ADD_SUBDIRECTORY(pcre)
ADD_SUBDIRECTORY(libiconv)
ADD_SUBDIRECTORY(libxml2)
ADD_SUBDIRECTORY(collada)
ADD_SUBDIRECTORY(OpenEXR)
ADD_SUBDIRECTORY(glew)

SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
                              CACHE STRING "OpenSGSupport Build Types" FORCE )

