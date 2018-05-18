CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(OpenSGSupport)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
                      "${OpenSGSupport_SOURCE_DIR}/../CMake")

##############################################
# Initial cache to make life easier on Windows
##############################################

IF(NOT _OSGINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  GET_FILENAME_COMPONENT(_OSGTMPF "${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt" REALPATH)
  GET_FILENAME_COMPONENT(_OSGTMP  "${_OSGTMPF}" PATH)

  SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${_OSGTMP}")
  SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${_OSGTMP}/CMake")
MESSAGE("xx ${_OSGTMP}")

  INCLUDE(${_OSGTMPF})
  SET(_OSGINITCACHELOADED TRUE CACHE INTERNAL "")
ENDIF(NOT _OSGINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)

##############################################
# Disallow in-source build
##############################################

IF("${OpenSGSupport_SOURCE_DIR}"  STREQUAL "${OpenSGSupport_BINARY_DIR}")
  MESSAGE(FATAL_ERROR "OpenSGSupport requires an out of source Build. \n"
                      "Please create a separate binary directory and run "
                      "CMake there.")
ENDIF("${OpenSGSupport_SOURCE_DIR}"  STREQUAL "${OpenSGSupport_BINARY_DIR}")

##############################################
# Common
##############################################

INCLUDE(OSGCommonSupportConfig)

OSG_COMMONSUPP_SETUP()

INCLUDE(OpenSGVersion)

SET(OSG_BUILD_ACTIVE TRUE)

FOREACH(_OSG_GLOBAL_DEP_DEF ${OSG_GLOBAL_DEP_DEFS})
  ADD_DEFINITIONS(-D${_OSG_GLOBAL_DEP_DEF})
ENDFOREACH(_OSG_GLOBAL_DEP_DEF)

##############################################
# Subdirs
##############################################

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

ENDIF(WIN32)

ADD_SUBDIRECTORY(glew)
ADD_SUBDIRECTORY(collada)
ADD_SUBDIRECTORY(opennurbs)
ADD_SUBDIRECTORY(libMini)

##############################################
# contrib support
##############################################

FILE(GLOB_RECURSE OSG_SUPPORT_CONFIG_FILES RELATIVE "${CMAKE_SOURCE_DIR}"
     "../Source/Contrib/*CMakeLists.Support.*.txt")

FOREACH(OSG_CONTRIB_SUPPORT ${OSG_SUPPORT_CONFIG_FILES})
  INCLUDE(${OSG_CONTRIB_SUPPORT})
ENDFOREACH()

##############################################
# extra support
##############################################

OSG_COMMON_SUPP_EXTERNAL()

OSG_COMMON_SUPP_WRITE_CONFIG(OSGSupportConfig.cmake)

##############################################
# install packaging
##############################################

IF(NOT WIN32)
  CONFIGURE_FILE(CMakeLists.packaging.unix.txt 
                 ${CMAKE_BINARY_DIR}/CMakeLists.packaging.txt
                 @ONLY                                      )
ELSE()
  IF(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
    SET(OSG_WIN_SEC "nosec")
  ELSE()
    SET(OSG_WIN_SEC "msdefault")
  ENDIF()

  CONFIGURE_FILE(CMakeLists.packaging.win.txt 
                 ${CMAKE_BINARY_DIR}/CMakeLists.packaging.txt
                 @ONLY                                      )

  INSTALL(FILES 
            "${CMAKE_SOURCE_DIR}/../CMake/Packaging/Windows/OpenSG2_Icon.ico"
            DESTINATION share/OpenSG/Packaging
            COMPONENT   packaging
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ            )

  INSTALL(FILES 
            "${CMAKE_SOURCE_DIR}/../CMake/Packaging/Windows/InstallerHeader.bmp"
            DESTINATION share/OpenSG/Packaging
            COMPONENT   packaging
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

INSTALL(FILES ${CMAKE_SOURCE_DIR}/COPYING
        DESTINATION share/doc/OpenSG
        COMPONENT doc
        PERMISSIONS OWNER_WRITE OWNER_READ
                    GROUP_READ
                    WORLD_READ
        RENAME COPYING.support)

##############################################
# Component install Setting
##############################################

GET_CMAKE_PROPERTY(OSG_COMPONENT_LIST COMPONENTS)

IF(NOT WIN32)
  ADD_CUSTOM_TARGET(OSG_preinstall
                    make preinstall
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
ELSE()
ENDIF()

FOREACH(_OSG_CMP ${OSG_COMPONENT_LIST})

  IF(NOT WIN32)

    ADD_CUSTOM_TARGET(
      INSTALL_${_OSG_CMP}
      COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${_OSG_CMP} -P cmake_install.cmake
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ELSE()

    SET(_OSG_CMP_CONF Release)

    IF(${_OSG_CMP} MATCHES ^debug_)
      SET(_OSG_CMP_CONF Debug)
    ENDIF()

    ADD_CUSTOM_TARGET(
      INSTALL_${_OSG_CMP}
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

##############################################
# cuda cleanup
##############################################

IF(CUDA_FOUND)
  CUDA_BUILD_CLEAN_TARGET()
ENDIF(CUDA_FOUND)
