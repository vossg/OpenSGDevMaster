CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(OpenSGSupport)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
                      "${OpenSGSupport_SOURCE_DIR}/../CMake")

##############################################
# Initial cache to make life easier on Windows
##############################################

IF(NOT _OSGINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  INCLUDE(${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  SET(_OSGINITCACHELOADED TRUE CACHE INTERNAL "")
ENDIF(NOT _OSGINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)

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

SET(BUILD_SHARED_LIBS ON CACHE INTERNAL "Set to ON to build dynamic libraries" FORCE)
SET(BUILD_STATIC_LIBS ON CACHE INTERNAL "Set to ON to build static libraries"  FORCE)

IF(WIN32)
  OPTION(OSG_DISABLE_MICROSOFT_SECURE_CXXX "" OFF)

  IF(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
    OPTION(OSG_DISABLE_MS_ITERATOR_DEBUGGING "" ON)
  ELSE(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
    OPTION(OSG_DISABLE_MS_ITERATOR_DEBUGGING "" OFF)
  ENDIF(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
ENDIF(WIN32)

SET(OSG_PLATFORM_64 0)
SET(OSG_PLATFORM_32 0)
SET(OSG_LIBDIR_SUFFIX "")

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(OSG_PLATFORM_64 1)
    SET(OSG_LIBDIR_SUFFIX "64")
  IF(NOT WIN32)
    SET(OSG_LIBDIR_BASE_SUFFIX "64")
  ENDIF(NOT WIN32)
ELSE()
    SET(OSG_PLATFORM_32 1)
ENDIF()

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(OSG_LIBDIR_SUFFIX "${OSG_LIBDIR_SUFFIX}/debug")
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
INCLUDE(../CMake/OpenSGVersion)

SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)
SET(OSG_BUILD_ACTIVE TRUE)

FIND_PACKAGE(OpenGL)

OSG_CONFIGURE_BOOST()

ADD_CUSTOM_TARGET(ALL_CUDA_BUILD)
ADD_CUSTOM_TARGET(ALL_STANDARD_BUILD)

IF(OSGGlutSrcDir AND OSGFreeGlutSrcDir)
  MESSAGE(FATAL_ERROR "choose either glut or freeglut")
ENDIF(OSGGlutSrcDir AND OSGFreeGlutSrcDir)

IF(WIN32)
  ADD_SUBDIRECTORY(zlib)
  ADD_SUBDIRECTORY(libpng)
  ADD_SUBDIRECTORY(libjpeg)
  ADD_SUBDIRECTORY(freeglut)
  ADD_SUBDIRECTORY(glut)
  ADD_SUBDIRECTORY(libtiff)
  ADD_SUBDIRECTORY(pcre)
#  ADD_SUBDIRECTORY(libiconv)
  ADD_SUBDIRECTORY(libxml2)
  ADD_SUBDIRECTORY(OpenEXR)
  ADD_SUBDIRECTORY(expat)
  ADD_SUBDIRECTORY(gdal)
ELSE(WIN32)
  IF(NOT APPLE)
    ADD_SUBDIRECTORY(doxygen)
  ENDIF(NOT APPLE)

  SET(OSG_SUPPORT_INC_SUBDIR "/OpenSG")
ENDIF(WIN32)

ADD_SUBDIRECTORY(glew)
ADD_SUBDIRECTORY(collada)

IF(NOT APPLE)
  ADD_SUBDIRECTORY(opennurbs)
ENDIF(NOT APPLE)

ADD_SUBDIRECTORY(libMini)

SET(OSG_EXTRA_EXTERNAL_SUPPORT "" CACHE STRING 
    "Extra modules that OpenSG will try to compile.")

FILE(GLOB_RECURSE OSG_SUPPORT_CONFIG_FILES RELATIVE "${CMAKE_SOURCE_DIR}"
     "../Source/Contrib/*CMakeLists.Support.*.txt")

FOREACH(OSG_CONTRIB_SUPPORT ${OSG_SUPPORT_CONFIG_FILES})
  INCLUDE(${OSG_CONTRIB_SUPPORT})
ENDFOREACH()

FOREACH(EXTERNAL ${OSG_EXTRA_EXTERNAL_SUPPORT})

  IF(NOT DEFINED OSG_${EXTERNAL}_SUPP_SOURCE_DIR)
    SET(OSG_${EXTERNAL}_SUPP_SOURCE_DIR "OSG_${EXTERNAL}_SUPP_SOURCE_DIR-NOTFOUND" CACHE PATH "")
  ENDIF()
    
  IF(OSG_${EXTERNAL}_SUPP_SOURCE_DIR AND
     EXISTS ${OSG_${EXTERNAL}_SUPP_SOURCE_DIR}/CMakeLists.txt)
     ADD_SUBDIRECTORY(${OSG_${EXTERNAL}_SUPP_SOURCE_DIR} External/${EXTERNAL})
  ENDIF()

ENDFOREACH(EXTERNAL)

SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
                              CACHE STRING "OpenSGSupport Build Types" FORCE )

FILE(WRITE  "${CMAKE_BINARY_DIR}/OSGSupportConfig.cmake" 
            "SET(OSG_SUPPORT_DISABLE_MICROSOFT_SECURE_CXXX ${OSG_DISABLE_MICROSOFT_SECURE_CXXX} CACHE INTERNAL \"\")\n\n")
FILE(APPEND  "${CMAKE_BINARY_DIR}/OSGSupportConfig.cmake" 
             "SET(OSG_SUPPORT_DISABLE_MS_ITERATOR_DEBUGGING ${OSG_DISABLE_MS_ITERATOR_DEBUGGING} CACHE INTERNAL \"\")\n\n")

INSTALL(FILES ${CMAKE_BINARY_DIR}/OSGSupportConfig.cmake
        DESTINATION include${OSG_SUPPORT_INC_SUBDIR}
        COMPONENT development_configuration
        PERMISSIONS OWNER_WRITE OWNER_READ
                    GROUP_READ
                    WORLD_READ)

IF(NOT WIN32)
  CONFIGURE_FILE(CMakeLists.packaging.unix.txt 
                 ${CMAKE_BINARY_DIR}/CMakeLists.packaging.txt
                 @ONLY                                      )
ELSE()
  CONFIGURE_FILE(CMakeLists.packaging.win.txt 
                 ${CMAKE_BINARY_DIR}/CMakeLists.packaging.txt
                 @ONLY                                      )

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/../CMake/Packaging/Windows/OpenSG2_Icon.ico"
          DESTINATION share/OpenSG/Packaging
          COMPONENT packaging
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ            )

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/../CMake/Packaging/Windows/InstallerHeader.bmp"
          DESTINATION share/OpenSG/Packaging
          COMPONENT packaging
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ            )

ENDIF()

INSTALL(FILES ${CMAKE_BINARY_DIR}/CMakeLists.packaging.txt
        DESTINATION share/OpenSG/Packaging
        COMPONENT packaging
        PERMISSIONS OWNER_WRITE OWNER_READ
                    GROUP_READ
                    WORLD_READ
        RENAME CMakeLists.txt)

###########################
# Component install Setting
###########################

GET_CMAKE_PROPERTY(OSG_COMPONENT_LIST COMPONENTS)

IF(NOT WIN32)
  ADD_CUSTOM_TARGET(OSG_preinstall
                    make preinstall
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
ELSE()
ENDIF()

FOREACH(_OSG_CMP ${OSG_COMPONENT_LIST})

  IF(NOT WIN32)

    ADD_CUSTOM_TARGET(INSTALL_${_OSG_CMP}
                      COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${_OSG_CMP} -P cmake_install.cmake
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ELSE()

    SET(_OSG_CMP_CONF Release)

    IF(${_OSG_CMP} MATCHES ^debug_)
      SET(_OSG_CMP_CONF Debug)
    ENDIF()

    ADD_CUSTOM_TARGET(INSTALL_${_OSG_CMP}
                      COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${_OSG_CMP} -DCMAKE_INSTALL_CONFIG_NAME=${_OSG_CMP_CONF} -P cmake_install.cmake
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ENDIF()

  IF(NOT WIN32)
    ADD_DEPENDENCIES(INSTALL_${_OSG_CMP} OSG_preinstall)
  ELSE()
  ENDIF()

ENDFOREACH()


IF(WIN32)

ELSE()

  ADD_CUSTOM_TARGET(INSTALL_runtime)

  ADD_DEPENDENCIES(INSTALL_runtime INSTALL_libraries)
ENDIF()



IF(CUDA_FOUND)
  CUDA_BUILD_CLEAN_TARGET()
ENDIF(CUDA_FOUND)
