CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(OpenSG)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OpenSG_SOURCE_DIR}/CMake")
INCLUDE(OpenSGVersion)

##############################################
# Initial cache to make life easier on Windows
##############################################

IF(NOT _OSGINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  INCLUDE(${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  SET(_OSGINITCACHELOADED TRUE CACHE INTERNAL "")
ENDIF(NOT _OSGINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)


INCLUDE(BuildFunctions)

##########################
# Disallow in-source build
##########################

IF("${OpenSG_SOURCE_DIR}"  STREQUAL "${OpenSG_BINARY_DIR}")
  MESSAGE(FATAL_ERROR "OpenSG requires an out of source Build. \n"
                      "Please create a separate binary directory and run "
                      "CMake there.")
ENDIF("${OpenSG_SOURCE_DIR}"  STREQUAL "${OpenSG_BINARY_DIR}")

SET(OSG_BUILD_ACTIVE TRUE)

##############################################################################
# BUILD OPTIONS
##############################################################################

IF(NOT WIN32)
    IF(OSG_BUILD_DEPENDEND)
        # Hide it from further manipulation
        SET(OSG_BUILD_DEPENDEND ${OSG_BUILD_DEPENDEND} CACHE INTERNAL "")
    ENDIF(OSG_BUILD_DEPENDEND)
ENDIF(NOT WIN32)

OPTION(OSG_VERBOSE_BUILD_MESSAGES "Print verbose messages when generating the build system" OFF)
MARK_AS_ADVANCED(OSG_VERBOSE_BUILD_MESSAGES)

OSG_OPTION(BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON)

OSG_OPTION(OSGBUILD_TESTS                        "Build test programs" ON)
OSG_OPTION(OSGBUILD_UNITTESTS                    "Build/run unit test programs" OFF)
OSG_OPTION(OSGBUILD_EXAMPLES_SIMPLE              "Build example programs during system build" OFF)
OSG_OPTION(OSGBUILD_EXAMPLES_ADVANCED            "Build advanced example programs during system build" OFF)
OSG_OPTION(OSGBUILD_PYTHON_BINDINGS              "Build python bindings" OFF)
OSG_OPTION(OSGBUILD_PYTHON_DUMP_DECLS            "Dump decls while building python" FALSE)

OSG_OPTION(OSGEXCLUDE_TESTS_FROM_ALL             "Exclude test programs from all target" OFF)
OSG_OPTION(OSGEXCLUDE_UNITTESTS_FROM_ALL         "Build/run unit test programs" OFF)
OSG_OPTION(OSGEXCLUDE_EXAMPLES_SIMPLE_FROM_ALL   "Build example programs during system build" OFF)
OSG_OPTION(OSGEXCLUDE_EXAMPLES_ADVANCED_FROM_ALL "Build advanced example programs during system build" OFF)

OSG_OPTION(OSGBUILD_ENABLE_PACKAGING "Generate binary packages with CPack" OFF)
SET(OSGBUILD_PACKAGE_TYPE "" CACHE STRING
    "The type of package to generate (empty->default)")

OSG_OPTION(OSG_ENABLE_NEW_SHADER "" ON)
OSG_OPTION(OSG_ENABLE_OGL2_SHADERFUNCTIONS "" ON)
OSG_OPTION(OSG_ENABLE_OGL_VERTEXATTRIB_FUNCS "" OFF)
OSG_OPTION(OSG_ENABLE_OGL_COREONLY "" OFF)

OSG_SET_CACHE(OSG_SHADER_CACHE_MODE 5 STRING "")

OSG_OPTION(OSG_ENABLE_FCD2CODE "" OFF)
OSG_OPTION(OSG_FCD2CODE_WRITE_CLASS "Write class file during cmake run if only
the fcd file is found" OFF)
OSG_OPTION(OSG_ENABLE_SCANPARSE_REGEN "" OFF)

OSG_OPTION(OSG_ENABLE_GLDEFINE_MAPPER "" ON)
OSG_OPTION(OSG_ENABLE_NEW_OSB_IO "" ON)

OSG_OPTION(OSG_ENABLE_SSE2 "" ON)

OSG_OPTION(OSG_ENABLE_TESTCONTAINER "" OFF)
OSG_OPTION(OSG_ENABLE_VALGRIND_CHECKS "" OFF)
OSG_OPTION(OSG_ENABLE_MEMORY_DEBUGGING "" OFF)
OSG_OPTION(OSG_ENABLE_DOUBLE_MATRIX_STACK "" OFF)
OSG_OPTION(OSG_ENABLE_DEFAULT_READONLY_CHANGELIST "" OFF)
OSG_OPTION(OSG_ENABLE_PAR_PARTITION_DRAWING "" OFF)
OSG_OPTION(OSG_DISABLE_SOURCE_GROUPS "" OFF)
OSG_OPTION(OSG_ENABLE_WRITE_PYTHON_TO_SOURCE "" OFF)

OSG_SET_CACHE(OSG_PYTHON_MODULE_BASE_DIR "" PATH "")

IF(WIN32)
  OPTION(OSG_ENABLE_WIN_LOCALSTORAGE "" ON)
  OPTION(OSG_DISABLE_MICROSOFT_SECURE_CXXX "" OFF)

  IF(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
    OPTION(OSG_DISABLE_MS_ITERATOR_DEBUGGING "" ON)
  ELSE(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
    OPTION(OSG_DISABLE_MS_ITERATOR_DEBUGGING "" OFF)
  ENDIF(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
ELSEIF(APPLE)
  OPTION(OSG_ENABLE_ELF_LOCALSTORAGE "" OFF)
ELSEIF(UNIX)
  OPTION(OSG_ENABLE_ELF_LOCALSTORAGE "" ON)
ENDIF()

OPTION(OSG_ENABLE_AUTOINIT_THREADS "" OFF)

IF(WIN32)
  OSG_OPTION(OSG_USE_SEPARATE_LIBDIRS "" ON)
  OSG_OPTION(OSG_INSTALL_PDB_FILES "" OFF)
ENDIF(WIN32)

OSG_OPTION(OSG_INSTALL_EXAMPLES "" OFF)

OSG_OPTION(OSGCOMPAT_ENABLE                  "" OFF)
OSG_OPTION(OSGCOMPAT_ENABLE_DEPRECATED       "" OFF)
OSG_OPTION(OSGCOMPAT_ENABLE_DEPRECATED_PROPS "" OFF)

OSG_SET_CACHE(OSG_RENDERPROPERTY_BITS 64 STRING "")
OSG_SET_CACHE(OSG_RENDERPROPERTY_UNIQUE_BITS 16 STRING "")

OSG_OPTION(OSG_GENERATE_SEPARATE_LIB_DOC "Generate separate doxygen documentation for contrib libraries" OFF)
OSG_OPTION(OSG_INSTALL_DOXYDOC "Install Doxygen documentation" OFF)

SET(OSG_DOXY_DOC_TYPE "User" CACHE STRING
    "The type of documentation to generate (User, Developer, Trac)")
SET(OSG_DOXY_INPUTS CACHE FILEPATH "include given file instead of autogen")
SET(OSG_DOXY_STDOUT_LOG CACHE FILEPATH "log std to file")

# Not sure
#OPTION(OSG_ENABLE_MTCPTR "" ON)
#OPTION(OSG_ENABLE_GIF    "" ON)

## prep options for OSGConfigured.h

IF(NOT OSGCOMPAT_ENABLE_DEPRECATED)
  SET(OSG_DISABLE_DEPRECATED 1)
ENDIF(NOT OSGCOMPAT_ENABLE_DEPRECATED)

IF(OSG_ENABLE_SSE2)
  SET(OSG_SIMD_SSE 1)
ENDIF(OSG_ENABLE_SSE2)

IF(OSG_ENABLE_NEW_OSB_IO)
  SET(OSG_NEW_OSB_IO 1)
ENDIF(OSG_ENABLE_NEW_OSB_IO)

IF(OSG_ENABLE_GLDEFINE_MAPPER)
  SET(OSG_GL_DEFMAPPER 1)
ENDIF(OSG_ENABLE_GLDEFINE_MAPPER)

IF(OSG_ENABLE_OGL2_SHADERFUNCTIONS)
  SET(OSG_OGL2_SHADERFUNCS 1)
ENDIF(OSG_ENABLE_OGL2_SHADERFUNCTIONS)

IF(OSG_ENABLE_OGL_VERTEXATTRIB_FUNCS)
  SET(OSG_OGL_VERTEXATTRIB_FUNCS 1)
ENDIF(OSG_ENABLE_OGL_VERTEXATTRIB_FUNCS)

IF(OSG_ENABLE_OGL_COREONLY)
  SET(OSG_OGL_COREONLY 1)
ENDIF(OSG_ENABLE_OGL_COREONLY)

IF(OSG_ENABLE_NEW_SHADER)
  SET(OSG_NEW_SHADER 1)
ENDIF(OSG_ENABLE_NEW_SHADER)

IF(OSGCOMPAT_ENABLE)
  SET(OSG_1_COMPAT 1)
ENDIF(OSGCOMPAT_ENABLE)

IF(NOT OSG_ENABLE_SCANPARSE_REGEN)
  SET(OSG_PREBUILD_SCANPARSE 1)
ENDIF(NOT OSG_ENABLE_SCANPARSE_REGEN)

IF(OSG_ENABLE_ELF_LOCALSTORAGE)
  SET(OSG_PTHREAD_ELF_TLS 1)
ENDIF(OSG_ENABLE_ELF_LOCALSTORAGE)

IF(OSG_ENABLE_WIN_LOCALSTORAGE)
  SET(OSG_WIN32_ASPECT_USE_LOCALSTORAGE 1)
ENDIF(OSG_ENABLE_WIN_LOCALSTORAGE)

IF(OSGCOMPAT_ENABLE_DEPRECATED_PROPS)
  SET(OSG_DEPRECATED_PROPS 1)
ENDIF(OSGCOMPAT_ENABLE_DEPRECATED_PROPS)

SET(OSG_SHC_MODE_${OSG_SHADER_CACHE_MODE} 1)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

INCLUDE(ConfigurePackages)

LIST(APPEND OSG_ADDITIONAL_CONFIGURE_LINES "")

IF(OSGEXCLUDE_TESTS_FROM_ALL)
  SET(OSGEXCLUDE_TESTS EXCLUDE_FROM_ALL)
ELSE()
  SET(OSGEXCLUDE_TESTS "")
ENDIF()

IF(OSGEXCLUDE_UNITTESTS_FROM_ALL)
  SET(OSGEXCLUDE_UNITTESTS EXCLUDE_FROM_ALL)
ELSE()
  SET(OSGEXCLUDE_UNITTESTS "")
ENDIF()

IF(OSGEXCLUDE_EXAMPLES_SIMPLE_FROM_ALL)
  SET(OSGEXCLUDE_EXAMPLES_SIMPLE EXCLUDE_FROM_ALL)
ELSE()
  SET(OSGEXCLUDE_EXAMPLES_SIMPLE "")
ENDIF()

IF(OSGEXCLUDE_EXAMPLES_ADVANCED_FROM_ALL)
  SET(OSGEXCLUDE_EXAMPLES_ADVANCED EXCLUDE_FROM_ALL)
ELSE()
  SET(OSGEXCLUDE_EXAMPLES_ADVANCED "")
ENDIF()

#####################
# External extensions
#####################

FOREACH(EXTERNAL ${OSG_EXTRA_EXTERNAL_MODULES})
    OPTION(OSGBUILD_${EXTERNAL}
           "Build using ${EXTERNAL} module" OFF)

    IF(OSGBUILD_${EXTERNAL})
        FIND_PATH(OSG_${EXTERNAL}_SOURCE_DIR
                  CMakeLists.Lib.${EXTERNAL}.txt
                  ${CMAKE_CURRENT_SOURCE_DIR}/../${EXTERNAL})

        OSG_ADD_OPT(OSG_${EXTERNAL}_SOURCE_DIR)

        IF(NOT EXISTS
                ${OSG_${EXTERNAL}_SOURCE_DIR}/CMakeLists.Lib.${EXTERNAL}.txt)

            MESSAGE(SEND_ERROR "Cannot find ${EXTERNAL} sources directory: "
                               "${OSG_${EXTERNAL}_SOURCE_DIR}")
        ELSE()
            LIST(APPEND OSG_EXTERNAL_CONFIGS "${EXTERNAL}")
        ENDIF()
    ENDIF()
ENDFOREACH(EXTERNAL)

OSG_SET_CACHE(OSG_EXTRA_EXTERNAL_MODULES "" STRING
              "Extra modules that OpenSG will try to import.")

OSG_SET_CACHE(OSG_IGNORE_INSTALL "" STRING
              "Extra modules that OpenSG will build but not installed.")

OSG_OPTION(OSG_LINK_EXTERNAL_MODULES_TO_CSM "" FALSE)

##############
# Compiler
##############

SET(OSG_PLATFORM_64 0)
SET(OSG_PLATFORM_32 0)
SET(OSG_APPLE64     0)
SET(OSG_APPLE32     0)
SET(OSG_LIBDIR_SUFFIX "")

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET(OSG_PLATFORM_64 1)
  SET(OSG_LIBDIR_SUFFIX "64")

  IF(NOT WIN32)
    SET(OSG_LIBDIR_BASE_SUFFIX "64")
  ENDIF(NOT WIN32)

  IF(APPLE)
    SET(OSG_APPLE64 1)
  ENDIF(APPLE)

ELSE()
  SET(OSG_PLATFORM_32 1)

  IF(APPLE)
    SET(OSG_APPLE32 1)
  ENDIF(APPLE)
ENDIF()


IF(${CMAKE_CXX_PLATFORM_ID} STREQUAL "Linux")
    SET(LINUX 1)
ENDIF()

IF(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
ENDIF(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)

IF(NOT WIN32) 
  IF(NOT CMAKE_BUILD_TYPE STREQUAL "Debug"          AND 
     NOT CMAKE_BUILD_TYPE STREQUAL "DebugGV"        AND
     NOT CMAKE_BUILD_TYPE STREQUAL "Release"        AND
     NOT CMAKE_BUILD_TYPE STREQUAL "ReleaseGV"      AND
     NOT CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"   )

    MESSAGE(FATAL_ERROR "incorrect build type ${CMAKE_BUILD_TYPE}.\n"
                        "Please use either Release or Debug")

  ENDIF()
ELSEIF(NOT MSVC_IDE)

  IF(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    SET(CMAKE_BUILD_TYPE DebugOpt CACHE STRING
        "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}."
        FORCE)  
  ENDIF()

  IF(NOT CMAKE_BUILD_TYPE STREQUAL "Debug"    AND 
     NOT CMAKE_BUILD_TYPE STREQUAL "DebugOpt" AND
     NOT CMAKE_BUILD_TYPE STREQUAL "Release"  AND
     NOT CMAKE_BUILD_TYPE STREQUAL "ReleaseNoOpt")

    MESSAGE(FATAL_ERROR "incorrect build type ${CMAKE_BUILD_TYPE}.\n"
                        "Please use on of ${CMAKE_CONFIGURATION_TYPES}")

  ENDIF()
ENDIF()

IF(NOT OSG_COMPILER_DEFAULTS)
   INCLUDE(CMake/SetupCompiler.cmake)
   SET( OSG_COMPILER_DEFAULTS 1 CACHE INTERNAL "Defaults written" FORCE ) #INTERNAL
ENDIF(NOT OSG_COMPILER_DEFAULTS)

INCLUDE(CMake/UpdateCompiler.cmake)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
   CMAKE_BUILD_TYPE STREQUAL "DebugGV")

    SET(OSG_LIBDIR_SUFFIX "${OSG_LIBDIR_SUFFIX}/debug")
    SET(OSG_LIBDIR_BUILD_TYPE_SUFFIX "debug")

ENDIF()

ADD_DEFINITIONS(-D OSG_BUILD_ACTIVE)

OSG_CHECK_INSTALL()

##############################################################################
# DEPENDENCIES
##############################################################################

# Global include/library dirs, libs and definitions
SET(OSG_GLOBAL_DEP_INCDIR "")
SET(OSG_GLOBAL_DEP_LIBDIR "")
SET(OSG_GLOBAL_DEP_LIBS   "")
SET(OSG_GLOBAL_DEP_DEFS   "")


#IF(WIN32)
  OSG_OPTION(OSG_USE_OSGSUPPORT_LIBS "" OFF)
  OSG_OPTION(OSG_USE_STATIC_SUPPORT_LIBS "" OFF)

  IF(OSG_USE_OSGSUPPORT_LIBS)
    OSG_SET_CACHE(OSG_SUPPORT_ROOT "" PATH "")
  ENDIF(OSG_USE_OSGSUPPORT_LIBS)

  IF(EXISTS "${OSG_SUPPORT_ROOT}" AND
     EXISTS "${OSG_SUPPORT_ROOT}/include/OSGSupportConfig.cmake")

    INCLUDE("${OSG_SUPPORT_ROOT}/include/OSGSupportConfig.cmake")

    SET(_OSG_FATAL_DMS_COMBO FALSE)

    IF( NOT OSG_DISABLE_MICROSOFT_SECURE_CXXX AND     OSG_SUPPORT_DISABLE_MICROSOFT_SECURE_CXXX)
      SET(_OSG_FATAL_DMS_COMBO TRUE)
    ENDIF()

    IF(     OSG_DISABLE_MICROSOFT_SECURE_CXXX AND NOT OSG_SUPPORT_DISABLE_MICROSOFT_SECURE_CXXX)
      SET(_OSG_FATAL_DMS_COMBO TRUE)
    ENDIF()

    IF(_OSG_FATAL_DMS_COMBO)

      MESSAGE(FATAL_ERROR "Conflicting DISABLE_MS_SECURE settings:\n"
                          "  Support : ${OSG_SUPPORT_DISABLE_MICROSOFT_SECURE_CXXX}\n"
                          "  OpenSG  : ${OSG_DISABLE_MICROSOFT_SECURE_CXXX}")

    ENDIF()
  ENDIF()

IF(WIN32)
   SET(OSG_INSTALL_SUBDIR "" CACHE STRING "add subdir to installed libs")
ENDIF(WIN32)

IF(NOT OSG_BUILD_DEPENDEND)

    ##########
    #### boost
    ##########

    OSG_CONFIGURE_BOOST()

    #########
    #### zlib
    #########

    OSG_CONFIGURE_ZLIB()

#    MESSAGE(STATUS "zlib: ${ZLIB_FOUND}")

    IF(UNIX AND NOT OSG_APPLE32)
        #############
        #### Freetype
        #############

        FIND_PACKAGE(Freetype)

        IF(FREETYPE_FOUND)
            OSG_SET(OSG_WITH_FT2 1)

            FIND_LIBRARY(FONTCONFIG_LIBRARY NAMES fontconfig)

            IF(FONTCONFIG_LIBRARY MATCHES "fontconfig")
                OSG_SET(OSG_WITH_FONTCONFIG 1)
            ENDIF()

        ENDIF(FREETYPE_FOUND)

        OSG_ADD_OPT(FREETYPE_FOUND)
        OSG_ADD_OPT(FREETYPE_INCLUDE_DIR_freetype2)
        OSG_ADD_OPT(FREETYPE_INCLUDE_DIR_ft2build)
        OSG_ADD_OPT(FONTCONFIG_LIBRARY)
        OSG_ADD_OPT(FREETYPE_LIBRARIES)
    ENDIF(UNIX AND NOT OSG_APPLE32)

    ##############
    #### ImageLibs
    ##############

    OSG_CONFIGURE_TIFF()
    OSG_CONFIGURE_PNG()
    OSG_CONFIGURE_JPEG()
    OSG_CONFIGURE_GDAL()
    OSG_CONFIGURE_OPENEXR()

    SET(OSG_EXTERNAL_IMAGELIBS)
    SET(OSG_EXTERNAL_IMAGEINCS)

#    MESSAGE(STATUS "tiff: ${TIFF_FOUND} - png ${PNG_FOUND} - jpg: ${JPEG_FOUND} - exr ${OPENEXR_FOUND}")

    IF(TIFF_FOUND)
        SET(OSG_EXTERNAL_IMAGELIBS ${OSG_EXTERNAL_IMAGELIBS} TIFF_LIBRARIES)
        SET(OSG_EXTERNAL_IMAGEINCS ${OSG_EXTERNAL_IMAGEINCS} TIFF_INCLUDE_DIR)
        OSG_SET(OSG_WITH_TIF 1)
        OSG_ADD_OPT(TIFF_LIBRARIES)
    ENDIF(TIFF_FOUND)

    IF(PNG_FOUND)
        SET(OSG_EXTERNAL_IMAGELIBS ${OSG_EXTERNAL_IMAGELIBS} PNG_LIBRARIES)
        SET(OSG_EXTERNAL_IMAGEINCS ${OSG_EXTERNAL_IMAGEINCS} PNG_INCLUDE_DIR)
        OSG_SET(OSG_WITH_PNG 1)
        OSG_ADD_OPT(PNG_LIBRARIES)
    ENDIF(PNG_FOUND)

    IF(JPEG_FOUND)
        SET(OSG_EXTERNAL_IMAGELIBS ${OSG_EXTERNAL_IMAGELIBS} JPEG_LIBRARIES)
        SET(OSG_EXTERNAL_IMAGEINCS ${OSG_EXTERNAL_IMAGEINCS} JPEG_INCLUDE_DIR)
        OSG_SET(OSG_WITH_JPG 1)
        OSG_ADD_OPT(JPEG_LIBRARIES)
    ENDIF(JPEG_FOUND)

    IF(GDAL_FOUND)
        SET(OSG_EXTERNAL_IMAGELIBS ${OSG_EXTERNAL_IMAGELIBS} GDAL_LIBRARIES)
        SET(OSG_EXTERNAL_IMAGEINCS ${OSG_EXTERNAL_IMAGEINCS} GDAL_INCLUDE_DIR)
        OSG_SET(OSG_WITH_GDAL 1)
        OSG_ADD_OPT(GDAL_LIBRARIES)
    ENDIF(GDAL_FOUND)

    IF(OPENEXR_FOUND)
        SET(OSG_EXTERNAL_IMAGELIBS ${OSG_EXTERNAL_IMAGELIBS} OPENEXR_LIBRARIES)
        SET(OSG_EXTERNAL_IMAGEINCS ${OSG_EXTERNAL_IMAGEINCS} OPENEXR_INCLUDE_DIR)
        OSG_SET(OSG_WITH_IMF 1)

        OSG_ADD_OPT(OPENEXR_LIBRARIES)
        OSG_ADD_OPT(OPENEXR_INCLUDE_DIR)
    ENDIF(OPENEXR_FOUND)


    OSG_ADD_OPT(OSG_EXTERNAL_IMAGELIBS)
    OSG_ADD_OPT(OSG_EXTERNAL_IMAGEINCS)

    #############
    #### Collada
    #############

    #FIND_PACKAGE(Collada)

    OSG_CONFIGURE_COLLADA()

    IF(COLLADA_FOUND)

        OSG_SET(OSG_WITH_COLLADA 1)

        IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
           CMAKE_BUILD_TYPE STREQUAL "DebugOpt")

            OSG_SET(OSG_COLLADA_LIBS ${COLLADA_LIBRARY_DEBUG})

        ELSE()

            OSG_SET(OSG_COLLADA_LIBS ${COLLADA_LIBRARY_RELEASE})

        ENDIF()

        OSG_ADD_OPT(COLLADA_DAE_INCLUDE_DIR)
        OSG_ADD_OPT(COLLADA_DOM_INCLUDE_DIR)

        IF(WIN32 OR COLLADA_TARGET_FOUND)
            SET(OSG_COLLADA_LIBS ${OSG_COLLADA_TARGETS})
        ENDIF(WIN32 OR COLLADA_TARGET_FOUND)

    ELSE(COLLADA_FOUND)

        SET(OSG_COLLADA_LIBS "")

    ENDIF(COLLADA_FOUND)

    OSG_ADD_OPT(COLLADA_FOUND)

    #############
    #### GLUT
    #############

    OSG_CONFIGURE_GLUT()

    IF(GLUT_FOUND)
      OSG_SET(OSG_WITH_GLUT 1)
      OSG_SET(OSG_GLUT_INC_DIR ${GLUT_INCLUDE_DIR})
      OSG_SET(OSG_GLUT_LIBS ${GLUT_LIBRARIES})
    ELSE(GLUT_FOUND)
      OSG_SET(OSG_WITH_GLUT 0)
      OSG_SET(OSG_GLUT_INC_DIR "")
      OSG_SET(OSG_GLUT_LIBS "")
    ENDIF(GLUT_FOUND)

    #############
    #### QT
    #############

    OSG_FIND_PACKAGE(Qt4)

    IF(QT4_FOUND)
        OSG_SET(OSG_WITH_QT 1)
        OSG_SET(OSG_QT4_INC_DIR ${QT_INCLUDE_DIR})
        OSG_SET(OSG_QT4_LIBS ${QT_LIBRARY_DIR})
    ELSE(QT4_FOUND)
        OSG_SET(OSG_QT4_INC_DIR "")
        OSG_SET(OSG_QT4_LIBS "")
    ENDIF(QT4_FOUND)

    #############
    #### OpenGL
    #############

    FIND_PACKAGE(OpenGL REQUIRED)
    FIND_PACKAGE(GLU REQUIRED)

    OSG_ADD_OPT(OPENGL_gl_LIBRARY)
    OSG_ADD_OPT(OPENGL_glu_LIBRARY)

    #############
    #### X11
    #############

    FIND_PACKAGE(X11)

    IF(X11_FOUND)
        OSG_SET(OSG_X_LIBS ${X11_X11_LIB})
        OSG_SET(OSG_X_INC_DIR ${X11_X11_INCLUDE_PATH})
    ENDIF(X11_FOUND)

    OSG_ADD_OPT(X11_FOUND)

    #############
    #### VTK
    #############

    IF(OSG_USE_OSG_VTK_SETUP)
      OSG_CONFIGURE_VTK()
    ELSE(OSG_USE_OSG_VTK_SETUP)
      FIND_PACKAGE(VTK)

      IF(VTK_FOUND)
          OSG_SET(OSG_WITH_VTK 1)
          OSG_SET(OSG_VTK_LIBS vtkRendering)

          OSG_ADD_OPT(OSG_VTK_LIBS)
          OSG_ADD_OPT(VTK_LIBRARY_DIRS)
          OSG_ADD_OPT(VTK_INCLUDE_DIRS)
          OSG_ADD_OPT(VTK_DIR)
      ENDIF(VTK_FOUND)
    ENDIF(OSG_USE_OSG_VTK_SETUP)

    OSG_ADD_OPT(VTK_FOUND)

    ##############
    #### GLEW
    ##############

    IF(WIN32)
      OSG_CONFIGURE_GLEW()
    ENDIF(WIN32)

    ##############
    #### Mini
    ##############

    OSG_CONFIGURE_LIBMINI()

    #############
    #### Python
    #############

    FIND_PACKAGE(PythonInterp)
    FIND_PACKAGE(PythonLibs)

    OSG_ADD_OPT(PYTHON_INCLUDE_PATH)
    OSG_ADD_OPT(PYTHON_LIBRARY)

    IF(Boost_FOUND AND PYTHONLIBS_FOUND)

      FIND_PACKAGE(Boost COMPONENTS python)

      IF(Boost_FOUND AND WIN32)

        SET(OSG_BOOST_PYTHON_TARGETS )
        OSG_ADD_IMPORT_LIB(OSG_BOOST_PYTHON_TARGETS Boost_PYTHON_LIBRARY)
        SET(OSG_BOOST_PYTHON_LIBS ${OSG_BOOST_PYTHON_TARGETS})
      
      ELSE(Boost_FOUND AND WIN32)

        IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR 
           CMAKE_BUILD_TYPE STREQUAL "DebugOpt")

          SET(OSG_BOOST_PYTHON_LIBS ${Boost_PYTHON_LIBRARY_DEBUG})

        ELSE()
          SET(OSG_BOOST_PYTHON_LIBS ${Boost_PYTHON_LIBRARY_RELEASE})
        ENDIF()

      ENDIF(Boost_FOUND AND WIN32)

      # We ignore if boost python fails, we catch that somewhere else
      # so if we get here Boost_FOUND was true in the first place
      SET(Boost_FOUND TRUE)

      FIND_PACKAGE(GCCXML)

      OSG_SET_CACHE(PYOSG_PYPLUSPLUS_DIR "" PATH "")
      OSG_SET_CACHE(PYOSG_PYPLUSPLUS_GOODIES_DIR "" PATH "")
      OSG_SET_CACHE(PYOSG_DIR "" PATH "")

    ENDIF()


    ###############
    #### Flex/Bison
    ###############

    FIND_PROGRAM(FLEX_EXE flex)
    FIND_PROGRAM(BISON_EXE bison)

    OSG_ADD_OPT(FLEX_EXE)
    OSG_ADD_OPT(BISON_EXE)

    ##############
    #### NVPerfSDK
    ##############

    OSG_FIND_PACKAGE(NVidiaPerfSDK)

    IF(NVIDIAPERFSDK_FOUND)
        OSG_SET(OSG_WITH_NVPERFSDK 1)
        OSG_SET(OSG_NVPERFSDK_INC_DIR ${NVIDIAPERFSDK_INCLUDE_DIR})
        OSG_SET(OSG_NVPERFSDK_LIBS ${NVIDIAPERFSDK_LIBRARIES})
    ELSE(NVIDIAPERFSDK_FOUND)
        OSG_SET(OSG_WITH_NVPERFSDK 0)
        OSG_SET(OSG_NVPERFSDK_INC_DIR "")
        OSG_SET(OSG_NVPERFSDK_LIBS "")
    ENDIF(NVIDIAPERFSDK_FOUND)


    #############
    #### Support
    #############

    IF(UNIX)
        FIND_LIBRARY(OSG_THREAD_LIB NAMES pthread)
        FIND_LIBRARY(OSG_DL_LIB     NAMES dl)

        OSG_ADD_OPT(OSG_THREAD_LIB)
        OSG_ADD_OPT(OSG_DL_LIB)
    ENDIF(UNIX)

    IF(APPLE)
        FIND_LIBRARY(OSG_APPLICATIONSERVICES_FRAMEWORK NAMES ApplicationServices)
        FIND_LIBRARY(OSG_CARBON_FRAMEWORK NAMES Carbon)
        FIND_LIBRARY(OSG_COCOA_FRAMEWORK NAMES Cocoa)
    ENDIF(APPLE)

    OSG_ADD_OPT(CMAKE_INSTALL_PREFIX)

ENDIF(NOT OSG_BUILD_DEPENDEND)

FOREACH(EXTERNAL_CONFIG ${OSG_EXTERNAL_CONFIGS})
  IF(EXISTS ${OSG_${EXTERNAL_CONFIG}_SOURCE_DIR}/${EXTERNAL_CONFIG}.Prepare.cmake)
    INCLUDE(${OSG_${EXTERNAL_CONFIG}_SOURCE_DIR}/${EXTERNAL_CONFIG}.Prepare.cmake)
  ENDIF(EXISTS
  ${OSG_${EXTERNAL_CONFIG}_SOURCE_DIR}/${EXTERNAL_CONFIG}.Prepare.cmake)
ENDFOREACH(EXTERNAL_CONFIG ${OSG_EXTERNAL_CONFIGS})

IF(OSG_GLOBAL_PREP AND EXISTS ${OSG_GLOBAL_PREP})
  INCLUDE(${OSG_GLOBAL_PREP})
ENDIF(OSG_GLOBAL_PREP AND EXISTS ${OSG_GLOBAL_PREP})

IF(APPLE AND OSG_COCOA_FRAMEWORK)
    OSG_SET(OSG_NATIVE_WINDOW OSGWindowCocoa)
ELSEIF(WIN32)
    OSG_SET(OSG_NATIVE_WINDOW OSGWindowWIN32)
ELSEIF(UNIX AND X11_FOUND)
    OSG_SET(OSG_NATIVE_WINDOW OSGWindowX)
ELSE()
    OSG_SET(OSG_NATIVE_WINDOW "")
ENDIF()

###############
#### Doxygen
###############

IF(EXISTS "${OSG_SUPPORT_ROOT}/bin/doxygen" AND NOT DOXYGEN_EXECUTABLE)
  SET(DOXYGEN_EXECUTABLE "${OSG_SUPPORT_ROOT}/bin/doxygen" 
                         CACHE FILEPATH "doxygen executable (custom)" FORCE)
ENDIF()

FIND_PACKAGE(Doxygen)

##############################################################################
# Overrides if dependend
##############################################################################

IF(NOT WIN32)
    IF(OSG_BUILD_DEPENDEND)
        MESSAGE(STATUS "Load reference settings")
        INCLUDE(${OSG_REFERENCE_DIR}/CMake.settings)
        # Needed to get the correct vtk/boost settings
        FIND_PACKAGE(VTK)
        OSG_BOOST_DEP_SETUP()
    ELSE(OSG_BUILD_DEPENDEND)
#        OSG_WRITE_SETTINGS(${CMAKE_BINARY_DIR}/CMake.settings)
    ENDIF(OSG_BUILD_DEPENDEND)
ENDIF(NOT WIN32)

##############################################################################
# MAIN BUILD STEPS
##############################################################################

# when adding passes, make sure to add a corresponding pass directory variable
# OSG_PASSDIR_${PASSNAME} - this variable may not be empty!
SET(OSG_CMAKE_PASSES "OSGCOLLECT" "OSGSETUP")

SET(OSG_PASSDIR_OSGCOLLECT "Collect")
SET(OSG_PASSDIR_OSGSETUP   "Build")

ADD_CUSTOM_TARGET(OSGAll)

###############
# Clean
###############

FILE(GLOB OSG_OLD_BUILD_FILES  "${CMAKE_BINARY_DIR}/*.cmake")

IF(OSG_OLD_BUILD_FILES)
    FILE(REMOVE ${OSG_OLD_BUILD_FILES})
ENDIF(OSG_OLD_BUILD_FILES)

FILE(GLOB OSG_OLD_CONFIG_FILES "${CMAKE_BINARY_DIR}/bin/osg2-config.part*.tmp")

IF(OSG_OLD_CONFIG_FILES)
    FILE(REMOVE ${OSG_OLD_CONFIG_FILES})
ENDIF(OSG_OLD_CONFIG_FILES)

###############
# Tests
###############

# optional pass for test programs
IF(OSGBUILD_TESTS)
    LIST(APPEND OSG_CMAKE_PASSES "OSGSETUPTEST")
    SET(OSG_PASSDIR_OSGSETUPTEST "Test")

    ADD_CUSTOM_TARGET(OSGAllTests)
    ADD_DEPENDENCIES(OSGAll OSGAllTests)
ENDIF(OSGBUILD_TESTS)

###############
# UnitTests
###############

IF(OSGBUILD_UNITTESTS)
    ENABLE_TESTING()
    INCLUDE(CTest)

    # optional pass for unittest programs
    LIST(APPEND OSG_CMAKE_PASSES "OSGSETUPUNITTEST")
    SET(OSG_PASSDIR_OSGSETUPUNITTEST "UnitTest")

    ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/Tools/unittest-cpp"
                     "${OSG_PASSDIR_OSGSETUPUNITTEST}")

    SET(OSG_UNITTEST_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Tools/unittest-cpp/UnitTest++/src")
    SET(OSG_UNITTEST_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/bin")
    SET(OSG_UNITTEST_LIBRARY      "UnitTest++")

    ADD_CUSTOM_TARGET(OSGAllUnitTests)
    ADD_DEPENDENCIES(OSGAll OSGAllUnitTests)
ENDIF(OSGBUILD_UNITTESTS)

###############
# Python
###############

# optional pass for test programs
IF(OSGBUILD_PYTHON_BINDINGS)
    LIST(APPEND OSG_CMAKE_PASSES "OSGPYTHON")
    SET(OSG_PASSDIR_OSGPYTHON "Python")

    IF(EXISTS ${PYOSG_PYPLUSPLUS_DIR})
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_DIR "True")
    ELSE()
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_DIR "False")
    ENDIF()

    IF(EXISTS ${PYOSG_PYPLUSPLUS_GOODIES_DIR})
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_GOODIES_DIR "True")
    ELSE()
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_GOODIES_DIR "False")
    ENDIF()

    SET(OSG_CAN_REGEN_PYTHON_BINDINGS FALSE)

    IF(GCCXML                       AND
       PYOSG_DIR                    AND
       PYOSG_PYPLUSPLUS_DIR         AND 
       PYOSG_PYPLUSPLUS_GOODIES_DIR)

     IF(EXISTS ${GCCXML}                       AND
        EXISTS ${PYOSG_DIR}                    AND
        EXISTS ${PYOSG_PYPLUSPLUS_DIR}         AND 
        EXISTS ${PYOSG_PYPLUSPLUS_GOODIES_DIR})

        SET(OSG_CAN_REGEN_PYTHON_BINDINGS TRUE)

      ENDIF()
    ENDIF()

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "${CMAKE_SOURCE_DIR}/Bindings/Python/genLibOrder.py"
                "${CMAKE_BINARY_DIR}/Python/Helper/genLibOrder.py")

    FILE(WRITE  "${CMAKE_BINARY_DIR}/Python/Helper/libOrder.py" "# Lib order information\n\n\nlibInfo = {}\n\n")
    FILE(APPEND "${CMAKE_BINARY_DIR}/Python/Helper/libOrder.py" "fullLibInfo = {}\n\n")

    IF(EXISTS ${PYOSG_DIR})
      FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Python/Helper")
      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${PYOSG_DIR}/src/osggen.py"
                  "${CMAKE_BINARY_DIR}/Python/Helper/osggen.py")


      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${CMAKE_SOURCE_DIR}/Bindings/Python/splitGenHelper.py"
                  "${CMAKE_BINARY_DIR}/Python/Helper/splitGenHelper.py")
     
      #########################
      # settings.py
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/settings.py")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_BINARY_DIR}/Python/Helper/processed/settings.py.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_BINARY_DIR}/Python/Helper/settings.py")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/settings.py.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Python/Helper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")

      #########################
      # PreBoostPython.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/PreBoostPython.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed/PreBoostPython.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/PreBoostPython.h")

      FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

      STRING(REPLACE "<OpenSG/"
                     "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

      FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # OsgPtrHelpers.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/OsgPtrHelpers.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed/OsgPtrHelpers.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/OsgPtrHelpers.h")

      FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

      STRING(REPLACE "<OpenSG/"
                     "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

      FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # pypp_OSGBase_aliases.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/aliases.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed/pypp_aliases.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/pypp_aliases.h")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/pypp_aliases.h.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # ColorWrapper.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/ColorWrapper.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/ColorWrapper.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/ColorWrapper.h")

      FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

      STRING(REPLACE "<OpenSG/"
                     "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

      FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # VecStorageWrappers.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/VecStorageWrappers.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/VecStorageWrappers.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/VecStorageWrappers.h")

      FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

      STRING(REPLACE "<OpenSG/"
                     "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

      FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # BaseWrappers.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/BaseWrappers.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/BaseWrappers.h")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Patches/wrappers.h.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # BaseWrappers.cpp
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.cpp")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/BaseWrappers.cpp.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/BaseWrappers.cpp")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Patches/wrappers.cpp.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")



      #########################
      # SystemWrappers.h
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.h")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed/SystemWrappers.h.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/SystemWrappers.h")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Patches/wrappers.h.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # SystemWrappers.cpp
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.cpp")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed/SystemWrappers.cpp.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/SystemWrappers.cpp")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Patches/wrappers.cpp.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # helpers.py
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/lib/helpers.py")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed/helpers.py.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/helpers.py.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # cored_node.py
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/lib/cored_node.py")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed/cored_node.py.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/cored_node.py.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # fcd_reflector.py
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/lib/fcd_reflector.py")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed/fcd_reflector.py.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/fcd_reflector.py.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" "-p0" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")

    ENDIF(EXISTS ${PYOSG_DIR})

    ADD_CUSTOM_TARGET(OSGPy)
    IF(OSG_CAN_REGEN_PYTHON_BINDINGS)
      ADD_CUSTOM_TARGET(OSGPyGen)
    ENDIF()
#    ADD_CUSTOM_TARGET(OSGPyBuild)

ENDIF(OSGBUILD_PYTHON_BINDINGS)

#################
# Documentation I
#################
SET(OSG_DOXY_HTML_DIR "${CMAKE_BINARY_DIR}/Doc/html")
FILE(MAKE_DIRECTORY ${OSG_DOXY_HTML_DIR})

IF(OSG_GENERATE_SEPARATE_LIB_DOC)
    ADD_CUSTOM_TARGET(Doc)
ENDIF()

IF(DOXYGEN_EXECUTABLE)
    SET(DOXYGEN_VERSION)
    EXECUTE_PROCESS(COMMAND "${DOXYGEN_EXECUTABLE}" "--version"
                    OUTPUT_VARIABLE DOXYGEN_VERSION
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    IF(DOXYGEN_VERSION STREQUAL "1.7.3")
        MESSAGE(WARNING "Detected doxygen version 1.7.3, which is known to crash "
                        "when building OpenSG documentation. "
                        "Please use a different version, sorry for the inconvenience.")
    ENDIF(DOXYGEN_VERSION STREQUAL "1.7.3")
ENDIF(DOXYGEN_EXECUTABLE)

IF(NOT OSG_DOXY_INPUTS)
    # add a pass for doxygen to run
    LIST(APPEND OSG_CMAKE_PASSES "OSGDOXYDOC")
    SET(OSG_PASSDIR_OSGDOXYDOC "Doc")
ENDIF(NOT OSG_DOXY_INPUTS)

# set up variables for the config file
IF(DOXYGEN_DOT_EXECUTABLE)
    SET(OSG_DOXY_HAVE_DOT "YES")
ENDIF(DOXYGEN_DOT_EXECUTABLE)

SET(OSG_DOXY_CONFIGURATION_FILE_IN "${CMAKE_SOURCE_DIR}/Doc/opensg-doxy.in")
SET(OSG_DOXY_CONFIGURATION_FILE    "${CMAKE_BINARY_DIR}/Doc/opensg-doxy")

SET(OSG_DOXY_HTML_CSS "${CMAKE_SOURCE_DIR}/Doc/doxygen_osg.css")

IF(OSG_DOXY_DOC_TYPE STREQUAL "User")
    SET(OSG_DOXY_FULL_PATH_NAMES "YES")
    SET(OSG_DOXY_STRIP_FROM_PATH "${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}")
    SET(OSG_DOXY_INTERNAL_DOCS "NO")
    SET(OSG_DOXY_STRIP_CODE_COMMENTS "YES")
    SET(OSG_DOXY_GENERATE_TREEVIEW "NO")
    SET(OSG_DOXY_SEARCHENGINE "NO")

ELSEIF(OSG_DOXY_DOC_TYPE STREQUAL "Developer")
    SET(OSG_DOXY_FULL_PATH_NAMES "YES")
    SET(OSG_DOXY_STRIP_FROM_PATH "${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}")
    SET(OSG_DOXY_INTERNAL_DOCS "YES")
    SET(OSG_DOXY_STRIP_CODE_COMMENTS "NO")
    SET(OSG_DOXY_GENERATE_TREEVIEW "YES")
    SET(OSG_DOXY_SEARCHENGINE "NO")

ELSEIF(OSG_DOXY_DOC_TYPE STREQUAL "Trac")
    SET(OSG_DOXY_FULL_PATH_NAMES "NO")
    SET(OSG_DOXY_INTERNAL_DOCS "NO")
    SET(OSG_DOXY_STRIP_CODE_COMMENTS "YES")
    SET(OSG_DOXY_HAVE_DOT "NO")
    SET(OSG_DOXY_GENERATE_TREEVIEW "NO")
    SET(OSG_DOXY_HTML_HEADER "${CMAKE_SOURCE_DIR}/Doc/TracHeader.html")
    SET(OSG_DOXY_HTML_FOOTER "${CMAKE_SOURCE_DIR}/Doc/TracFooter.html")
    SET(OSG_DOXY_SEARCHENGINE "NO")

ENDIF(OSG_DOXY_DOC_TYPE STREQUAL "User")

IF(NOT OSG_GENERATE_SEPARATE_LIB_DOC)
  SET(OSG_OpenSG_DOC_DIRECTORY "${CMAKE_BINARY_DIR}/Doc/html/Full")
ELSE()
  SET(OSG_OpenSG_DOC_DIRECTORY "${CMAKE_BINARY_DIR}/Doc/html/Glue")
ENDIF()

FILE(MAKE_DIRECTORY ${OSG_OpenSG_DOC_DIRECTORY})

SET(OSG_DOC_BASIC_INPUT "${CMAKE_BINARY_DIR}/Doc/Include/OSGFullDoc.include")
SET(OSG_DOC_GENERAL_INPUT "${CMAKE_BINARY_DIR}/Doc/Include/OSGGeneralDoc.include")

IF(NOT OSG_GENERATE_SEPARATE_LIB_DOC)
  SET(OSG_DOC_SECTION "all_in_one")
ELSE()
  SET(OSG_DOC_SECTION "separate")
ENDIF()

# write doxygen config file
CONFIGURE_FILE("${OSG_DOXY_CONFIGURATION_FILE_IN}"
               "${OSG_DOXY_CONFIGURATION_FILE}")

SET(OSG_DOC_BASIC_INPUT "${CMAKE_BINARY_DIR}/Doc/Include/OSGDummy.include")

# find/process documentation include files
FILE(GLOB OSG_DOC_INCLUDES "${CMAKE_SOURCE_DIR}/Doc/Include/*.include")

FOREACH(_OSG_DOC_INCLUDE_FULL ${OSG_DOC_INCLUDES})

  GET_FILENAME_COMPONENT(_OSG_DOC_INCLUDE ${_OSG_DOC_INCLUDE_FULL} NAME)

  CONFIGURE_FILE("${_OSG_DOC_INCLUDE_FULL}"
                 "${CMAKE_BINARY_DIR}/Doc/Include/${_OSG_DOC_INCLUDE}")

ENDFOREACH()

IF(OSG_DOXY_INPUTS)
    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
                "@INCLUDE = ${OSG_DOXY_INPUTS}\n")
ENDIF(OSG_DOXY_INPUTS)


IF(DOXYGEN_EXECUTABLE)
  ADD_CUSTOM_TARGET(DocUpload COMMAND unison -batch -ui text opensg_doc)
  ADD_DEPENDENCIES(DocUpload Doc)


  ADD_CUSTOM_TARGET(DocSyncGV
                    COMMAND rsync html -av --delete html rsync://tombstone.camtech.ntu.edu.sg/opensgdoc
                    WORKING_DIRECTORY Doc)

  ADD_CUSTOM_TARGET(DocCompleteGV)
  ADD_DEPENDENCIES(DocCompleteGV Doc DocSyncGV)
ENDIF(DOXYGEN_EXECUTABLE)

ADD_CUSTOM_TARGET(OSGAllLibs)
ADD_DEPENDENCIES(OSGAll OSGAllLibs)

ADD_CUSTOM_TARGET(OSGAllCoreLibs)
ADD_CUSTOM_TARGET(OSGAllContribLibs)

###############
# Passes
###############

FOREACH(_OSGCORE_EXT_DIR ${OSG_CORE_EXTENSIONS})
  MESSAGE(STATUS "processing core ext : ${_OSGCORE_EXT_DIR}")

  FILE(GLOB_RECURSE _OSG_LIBRARY_EXT_CONFIG_FILES
       "${_OSGCORE_EXT_DIR}/*CMakeLists.Extension.*.txt")

  FOREACH(_OSGCORE_EXT_FILE ${_OSG_LIBRARY_EXT_CONFIG_FILES})
    MESSAGE(STATUS "   Found and process ${_OSGCORE_EXT_FILE}")
    INCLUDE(${_OSGCORE_EXT_FILE})
  ENDFOREACH(_OSGCORE_EXT_FILE ${OSG_LIBRARY_EXT_CONFIG_FILES})


ENDFOREACH(_OSGCORE_EXT_DIR ${OSG_CORE_EXTENSIONS})

# Find files describing libraries to build, but make sure base
# and system are processed first
FILE(GLOB_RECURSE OSG_LIBRARY_CONFIG_FILE_BASE RELATIVE "${CMAKE_SOURCE_DIR}"
     "Source/CMakeLists.Lib.OSGBase.txt")

FILE(GLOB_RECURSE OSG_LIBRARY_CONFIG_FILE_SYSTEM RELATIVE "${CMAKE_SOURCE_DIR}"
     "Source/CMakeLists.Lib.OSGSystem.txt")

FILE(GLOB_RECURSE _OSG_LIBRARY_CONFIG_FILES RELATIVE "${CMAKE_SOURCE_DIR}"
     "Source/*CMakeLists.Lib.*.txt")

LIST(REMOVE_ITEM _OSG_LIBRARY_CONFIG_FILES ${OSG_LIBRARY_CONFIG_FILE_BASE})
LIST(REMOVE_ITEM _OSG_LIBRARY_CONFIG_FILES ${OSG_LIBRARY_CONFIG_FILE_SYSTEM})

LIST(APPEND OSG_LIBRARY_CONFIG_FILES ${OSG_LIBRARY_CONFIG_FILE_BASE})
LIST(APPEND OSG_LIBRARY_CONFIG_FILES ${OSG_LIBRARY_CONFIG_FILE_SYSTEM})

FOREACH(_OSG_LIBRARY_CONFIG ${_OSG_LIBRARY_CONFIG_FILES})
  STRING(REGEX MATCH Source/Contrib _OSG_FOUND_CONTRIB_CONFIG ${_OSG_LIBRARY_CONFIG})

  IF(_OSG_FOUND_CONTRIB_CONFIG)
    LIST(APPEND _OSG_CONTRIB_LIBRARY_CONFIG_FILES ${_OSG_LIBRARY_CONFIG})
  ELSE()
    LIST(APPEND OSG_LIBRARY_CONFIG_FILES ${_OSG_LIBRARY_CONFIG})
  ENDIF(_OSG_FOUND_CONTRIB_CONFIG)
ENDFOREACH(_OSG_LIBRARY_CONFIG ${_OSG_LIBRARY_CONFIG_FILES})

LIST(APPEND OSG_LIBRARY_CONFIG_FILES ${_OSG_CONTRIB_LIBRARY_CONFIG_FILES})

FOREACH(_OSG_LIBRARY_CONFIG ${OSG_LIBRARY_CONFIG_FILES})

  GET_FILENAME_COMPONENT(_OSG_LIBCONFIG_DIR
                         ${_OSG_LIBRARY_CONFIG}
                          PATH)

  GET_FILENAME_COMPONENT(_OSG_LIBCONFIG_BASENAME
                         ${_OSG_LIBRARY_CONFIG}
                          NAME)

  STRING(REPLACE CMakeLists.Lib. "" _OSG_LIBCONFIG_BASENAME_1
                     ${_OSG_LIBCONFIG_BASENAME})

  GET_FILENAME_COMPONENT(_OSG_LIBCONFIG_BASENAME
                         ${_OSG_LIBCONFIG_BASENAME_1}
                         NAME_WE)

  IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_OSG_LIBCONFIG_DIR}/${_OSG_LIBCONFIG_BASENAME}.Prepare.cmake")
    INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/${_OSG_LIBCONFIG_DIR}/${_OSG_LIBCONFIG_BASENAME}.Prepare.cmake")
  ENDIF()

ENDFOREACH()

IF(CUDA_FOUND)
  SET(OSG_WITH_CUDA 1)
ENDIF(CUDA_FOUND)
IF(OPENCL_FOUND)
  SET(OSG_WITH_OPENCL)
ENDIF(OPENCL_FOUND)

IF(NOT WIN32)
  IF(NOT OSG_BUILD_DEPENDEND)
    OSG_WRITE_SETTINGS(${CMAKE_BINARY_DIR}/CMake.settings)
  ENDIF(NOT OSG_BUILD_DEPENDEND)
ENDIF(NOT WIN32)

# run build passes
FOREACH(PASS ${OSG_CMAKE_PASSES})
    SET(OSG_CMAKE_PASS ${PASS})

    MESSAGE(STATUS "\nPASS : ${OSG_CMAKE_PASS} in ${OSG_PASSDIR_${PASS}}\n")

    FOREACH(LIBCONFIGFILE ${OSG_LIBRARY_CONFIG_FILES})
        GET_FILENAME_COMPONENT(LIBCONFIGDIR "${LIBCONFIGFILE}" PATH)
        GET_FILENAME_COMPONENT(LIBFILENAME  "${LIBCONFIGFILE}" NAME)
        STRING(REPLACE "CMakeLists.Lib." "" LIBFILENAME "${LIBFILENAME}")
        STRING(REPLACE ".txt"            "" LIBFILENAME "${LIBFILENAME}")

        STRING(REGEX MATCH OSGContrib*|OSGTest* _OSG_IS_CONTRIBLIB ${LIBFILENAME})

        IF(_OSG_IS_CONTRIBLIB)
          SET(OSG_MAIN_LIB_TARGET OSGAllContribLibs)
        ELSE()
          SET(OSG_MAIN_LIB_TARGET OSGAllCoreLibs)
        ENDIF()

        ADD_SUBDIRECTORY("${LIBCONFIGDIR}" "${OSG_PASSDIR_${PASS}}/${LIBFILENAME}")
    ENDFOREACH(LIBCONFIGFILE)

    SET(OSG_MAIN_LIB_TARGET OSGAllContribLibs)

    FOREACH(EXTERNAL_CONFIG ${OSG_EXTERNAL_CONFIGS})
        ADD_SUBDIRECTORY("${OSG_${EXTERNAL_CONFIG}_SOURCE_DIR}"
                         "External/${EXTERNAL_CONFIG}/${OSG_PASSDIR_${PASS}}")
    ENDFOREACH(EXTERNAL_CONFIG ${OSG_EXTERNAL_CONFIGS})

ENDFOREACH()


###############
# OSGConfigured
###############


EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy
                     "${CMAKE_SOURCE_DIR}/OSGConfigured.h.cmake"
                     "${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h.tmp.cmake")

FOREACH(_OSG_ADD_CONFIGURE_LINE ${OSG_ADDITIONAL_CONFIGURE_LINES})
  FILE(APPEND "${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h.tmp.cmake" "\n${_OSG_ADD_CONFIGURE_LINE}\n")
ENDFOREACH()

FILE(APPEND "${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h.tmp.cmake" "\n#endif // _OSGCONFIGURED_H_\n")

CONFIGURE_FILE("${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h.tmp.cmake"
               "${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h.tmp")

EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h.tmp"
                     "${CMAKE_BINARY_DIR}/Source/Base/Base/OSGConfigured.h")

#################
# Examples/Simple
#################

ADD_CUSTOM_TARGET(OSGAllExamples)
ADD_DEPENDENCIES(OSGAll OSGAllExamples)

IF(OSGBUILD_EXAMPLES_SIMPLE)
    ADD_CUSTOM_TARGET(OSGAllSimpleExamples)
    ADD_SUBDIRECTORY("Examples/Simple")
    ADD_DEPENDENCIES(OSGAllExamples OSGAllSimpleExamples)
ENDIF(OSGBUILD_EXAMPLES_SIMPLE)

###################
# Examples/Advanced
###################

IF(OSGBUILD_EXAMPLES_ADVANCED)
    ADD_CUSTOM_TARGET(OSGAllAdvancedExamples)
    ADD_SUBDIRECTORY("Examples/Advanced/DeferredShading")
    ADD_DEPENDENCIES(OSGAllExamples OSGAllAdvancedExamples)
ENDIF(OSGBUILD_EXAMPLES_ADVANCED)

###################
# External Examples
###################

FOREACH(_OSGCORE_EXT_EXAMPLE_DIR ${OSG_CORE_EXAMPLE_EXTENSIONS})
  MESSAGE(STATUS "processing example ext : ${_OSGCORE_EXT_EXAMPLE_DIR}")

  IF(EXISTS ${_OSGCORE_EXT_EXAMPLE_DIR}/CMakeLists.Examples.txt)
    MESSAGE(STATUS "   Found and process ${_OSGCORE_EXT_EXAMPLE_DIR}/CMakeLists.Examples.txt")
    INCLUDE(${_OSGCORE_EXT_EXAMPLE_DIR}/CMakeLists.Examples.txt)
  ENDIF(EXISTS ${_OSGCORE_EXT_EXAMPLE_DIR}/CMakeLists.Examples.txt)
ENDFOREACH(_OSGCORE_EXT_EXAMPLE_DIR ${OSG_CORE_EXAMPLE_EXTENSIONS})

##################
# Documentation II
##################

SET(OSG_DOC_PIPES "")

IF(OSG_DOXY_STDOUT_LOG)
    SET(OSG_DOC_PIPES > ${OSG_DOXY_STDOUT_LOG})
ENDIF(OSG_DOXY_STDOUT_LOG)

IF(DOXYGEN_EXECUTABLE)
    IF(NOT OSG_GENERATE_SEPARATE_LIB_DOC)
        ADD_CUSTOM_TARGET(Doc
            VERBATIM
            COMMAND ${DOXYGEN_EXECUTABLE} ${OSG_DOXY_CONFIGURATION_FILE} ${OSG_DOC_PIPES})
    ENDIF()
ENDIF()

##################
# osg2-config
##################

# osg2-config is created from multiple parts (parts 1 and 3 static, part 2
# is generated during the OSGCOLLECT pass.

# substitute variables in static parts
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/CMake/osg2-config.part1.in"
               "${CMAKE_BINARY_DIR}/bin/osg2-config.part1.tmp")
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/CMake/osg2-config.part3.in"
               "${CMAKE_BINARY_DIR}/bin/osg2-config.part3.tmp")

# read in all parts
FILE(READ "${CMAKE_BINARY_DIR}/bin/osg2-config.part1.tmp" OSG2_CONFIG_PART1_CONTENT)
FILE(READ "${CMAKE_BINARY_DIR}/bin/osg2-config.part2.tmp" OSG2_CONFIG_PART2_CONTENT)
FILE(READ "${CMAKE_BINARY_DIR}/bin/osg2-config.part3.tmp" OSG2_CONFIG_PART3_CONTENT)

# concatenate final file
FILE(WRITE  "${CMAKE_BINARY_DIR}/bin/osg2-config" "${OSG2_CONFIG_PART1_CONTENT}")
FILE(APPEND "${CMAKE_BINARY_DIR}/bin/osg2-config" "${OSG2_CONFIG_PART2_CONTENT}")
FILE(APPEND "${CMAKE_BINARY_DIR}/bin/osg2-config" "${OSG2_CONFIG_PART3_CONTENT}")

FILE(REMOVE  "${CMAKE_BINARY_DIR}/bin/osg2-config.part1.tmp")
FILE(REMOVE  "${CMAKE_BINARY_DIR}/bin/osg2-config.part2.tmp")
FILE(REMOVE  "${CMAKE_BINARY_DIR}/bin/osg2-config.part3.tmp")

INSTALL(PROGRAMS "${CMAKE_BINARY_DIR}/bin/osg2-config"
        DESTINATION bin
        COMPONENT development_tools)

##################
# cmake modules
##################

INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindOpenSG.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindCollada.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindOpenEXR.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindGLUT_OpenSG.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindJPEG_OpenSG.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindPNG_OpenSG.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindTIFF_OpenSG.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/FindZLIB_OpenSG.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/SetupCompiler.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/UpdateCompiler.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/BuildFunctions.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/ConfigurePackages.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/ExternalProjectHelper.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/OpenSGVersion.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(FILES "${CMAKE_BINARY_DIR}/OpenSGExtDep.cmake"
        DESTINATION share/OpenSG/cmake
        COMPONENT development_configuration)
INSTALL(DIRECTORY "${CMAKE_SOURCE_DIR}/Tools/fcd2code"
        DESTINATION bin
        COMPONENT development_tools
        PATTERN "*.pyc" EXCLUDE
        PATTERN ".svn"  EXCLUDE)

##################
# Global Python
##################

IF(OSGBUILD_PYTHON_BINDINGS)
  EXECUTE_PROCESS(COMMAND ${PYTHON_EXECUTABLE} Python/Helper/genLibOrder.py
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  OUTPUT_VARIABLE _OSG_LIBORDER)

  SET(_OSG_PY_MOD_LIST "osg2ModuleList = [\n")

  FOREACH(_OSG_LIB ${_OSG_LIBORDER})
    STRING(REPLACE "\n" "" _OSG_LIB ${_OSG_LIB})
    SET(OSG_PYTHON_ALL_IMPORTS "${OSG_PYTHON_ALL_IMPORTS}from ..${_OSG_LIB} import *\n")
    SET(_OSG_PY_MOD_LIST "${_OSG_PY_MOD_LIST}  ${_OSG_LIB}Py,\n")
  ENDFOREACH()

  SET(OSG_PYTHON_ALL_IMPORTS "${OSG_PYTHON_ALL_IMPORTS}\n\n${_OSG_PY_MOD_LIST}  ]\n\n")

  SET(_OSG_GEN_INIT_FILE_IN  "${CMAKE_SOURCE_DIR}/Bindings/Python/osg.__init__.py.in")
  SET(_OSG_GEN_INIT_FILE_OUT "${CMAKE_SOURCE_DIR}/Bindings/Python/module/__init__.py")

  CONFIGURE_FILE("${_OSG_GEN_INIT_FILE_IN}"
                 "${_OSG_GEN_INIT_FILE_OUT}")

  IF(WIN32) 

    SET(_OSG_TARGET_PYLIBDIR    lib/python/${_OSG_ISC}rel/osg2)
    SET(_OSG_TARGET_PYLIBDIR_D  lib/python/${_OSG_ISC}debug/osg2)
    SET(_OSG_TARGET_PYLIBDIR_RN lib/python/${_OSG_ISC}relnoopt/osg2)
    SET(_OSG_TARGET_PYLIBDIR_DO lib/python/${_OSG_ISC}debugopt/osg2)

    INSTALL(FILES          ${_OSG_GEN_INIT_FILE_OUT} 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR}/osg
            CONFIGURATIONS Release)

    INSTALL(FILES       ${_OSG_GEN_INIT_FILE_OUT} 
            DESTINATION ${_OSG_TARGET_PYLIBDIR_D}/osg
              CONFIGURATIONS Debug)

    INSTALL(FILES       ${_OSG_GEN_INIT_FILE_OUT} 
            DESTINATION ${_OSG_TARGET_PYLIBDIR_DO}/osg
            CONFIGURATIONS DebugOpt)

    INSTALL(FILES       ${_OSG_GEN_INIT_FILE_OUT} 
            DESTINATION ${_OSG_TARGET_PYLIBDIR_RN}/osg
            CONFIGURATIONS ReleaseNoOpt)


    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/osg2/__init__.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR}
            CONFIGURATIONS Release)

    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/__init__.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR}/helpers
            CONFIGURATIONS Release)


    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/osg2/__init__.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR_D}
            CONFIGURATIONS Debug)

    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/__init__.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR_D}/helpers
            CONFIGURATIONS Debug)


    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/osg2/__init__.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR_DO}
            CONFIGURATIONS DebugOpt)

    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/__init__.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR_DO}/helpers
            CONFIGURATIONS DebugOpt)


    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/osg2/__init__.py
            DESTINATION    ${_OSG_TARGET_PYLIBDIR_RN}
            CONFIGURATIONS ReleaseNoOpt)

    INSTALL(FILES          ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/__init__.py
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py 
                           ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py 
            DESTINATION    ${_OSG_TARGET_PYLIBDIR_RN}/helpers
            CONFIGURATIONS ReleaseNoOpt)

  ELSE(WIN32)   

    GET_FILENAME_COMPONENT(_PY_VERSION_DIR ${PYTHON_INCLUDE_PATH} NAME)
    SET(_OSG_PY_INST_BASE 
        "lib${OSG_LIBDIR_BASE_SUFFIX}/${_PY_VERSION_DIR}/site-packages/${OSG_LIBDIR_BUILD_TYPE_SUFFIX}/osg2")

    INSTALL(FILES       ${_OSG_GEN_INIT_FILE_OUT} 
            DESTINATION ${_OSG_PY_INST_BASE}/osg)

    INSTALL(FILES       ${CMAKE_SOURCE_DIR}/Bindings/Python/osg2/__init__.py 
            DESTINATION ${_OSG_PY_INST_BASE})

    INSTALL(FILES       ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/__init__.py 
                        ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py 
                        ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py 
                        ${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py 
            DESTINATION ${_OSG_PY_INST_BASE}/helpers)

  ENDIF(WIN32)

ENDIF()

##################
# Documentation
##################
IF(DOXYGEN_EXECUTABLE)
    IF(OSG_INSTALL_DOXYDOC)
        INSTALL(DIRECTORY "${OSG_DOXY_HTML_DIR}"
                DESTINATION share/OpenSG/documentation
                COMPONENT documentation)
    ENDIF()
ENDIF()

##################
# Images/Icons
##################

#INSTALL(DIRECTORY "${CMAKE_SOURCE_DIR}/Data/Images"
#        DESTINATION share/OpenSG
#        COMPONENT data_images)

##################
# Packaging
##################

IF(OSGBUILD_ENABLE_PACKAGING)

    SET(SYSTEM_SPEC  ${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR})

    SET(CPACK_PACKAGE_NAME                "OpenSG")
    SET(CPACK_PACKAGE_VERSION             ${OSG_VERSION})
    SET(CPACK_PACKAGE_VERSION_MAJOR       ${OSG_VERSION_MAJOR})
    SET(CPACK_PACKAGE_VERSION_MINOR       ${OSG_VERSION_MINOR})
    SET(CPACK_PACKAGE_VERSION_PATCH       ${OSG_VERSION_PATCH})
    SET(CPACK_PACKAGE_VENDOR              "OpenSG")
    SET(CPACK_PACKAGE_CONTACT             "Dirk Reiners <dirk@www.opensg.org>")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenSG is a portable scenegraph system to create realtime 3D graphics programs")
    SET(CPACK_RESOURCE_FILE_LICENSE       "${CMAKE_SOURCE_DIR}/COPYING")
    SET(CPACK_PACKAGE_FILE_NAME           "${PROJECT_NAME}-${OSG_VERSION}-${SYSTEM_SPEC}-${CMAKE_BUILD_TYPE}")

    if (EXISTS "${CMAKE_SOURCE_DIR}/README.txt")
        set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
        set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
    endif ()

    if (EXISTS "${CMAKE_SOURCE_DIR}/Welcome.txt")
        set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/Welcome.txt")
    endif()

    #Define Components
    SET(CPACK_COMPONENTS_ALL development_tools
        development_configuration
        code_headers
        libraries
        debug_program_db
        release_program_db
        debug_libraries
        release_libraries
        debug_runtimes
        release_runtimes
        data_images
        examples_basic
        examples_advanced
        Unspecified
        )


    #Components
    #Runtime
    SET(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "Files needed to execute software with OpenSG.")

    SET(CPACK_COMPONENT_DEBUG_RUNTIMES_DISPLAY_NAME "Debug Runtime")
    SET(CPACK_COMPONENT_DEBUG_RUNTIMES_DESCRIPTION "Debug Runtimes Libraries Description")
    SET(CPACK_COMPONENT_DEBUG_RUNTIMES_GROUP "Runtime")
    SET(CPACK_COMPONENT_DEBUG_RUNTIMES_INSTALL_TYPES Full Developer Runtime)

    SET(CPACK_COMPONENT_RELEASE_RUNTIMES_DISPLAY_NAME "Release Runtime")
    SET(CPACK_COMPONENT_RELEASE_RUNTIMES_DESCRIPTION "Release Runtime Libraries Description")
    SET(CPACK_COMPONENT_RELEASE_RUNTIMES_GROUP "Runtime")
    SET(CPACK_COMPONENT_RELEASE_RUNTIMES_INSTALL_TYPES Full Developer Runtime)

    #Development
    SET(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "Development files needed to develop software with OpenSG.")

    #Libraries
    SET(CPACK_COMPONENT_RELEASE_LIBRARIES_DISPLAY_NAME "Release Libraries")
    SET(CPACK_COMPONENT_RELEASE_LIBRARIES_DESCRIPTION "Release Libraries Description")
    SET(CPACK_COMPONENT_RELEASE_LIBRARIES_GROUP "Development")
    set(CPACK_COMPONENT_RELEASE_LIBRARIES_INSTALL_TYPES Full Developer)

    SET(CPACK_COMPONENT_DEBUG_LIBRARIES_DISPLAY_NAME "Debug Libraries")
    SET(CPACK_COMPONENT_DEBUG_LIBRARIES_DESCRIPTION "Debug Libraries Description")
    SET(CPACK_COMPONENT_DEBUG_LIBRARIES_GROUP "Development")
    SET(CPACK_COMPONENT_DEBUG_LIBRARIES_INSTALL_TYPES Full Developer)

    #Program database
    SET(CPACK_COMPONENT_RELEASE_PROGRAM_DB_DISPLAY_NAME "Release Program Database")
    SET(CPACK_COMPONENT_RELEASE_PROGRAM_DB_DESCRIPTION "Release Program Database Description")
    SET(CPACK_COMPONENT_RELEASE_PROGRAM_DB_GROUP "Development")
    SET(CPACK_COMPONENT_RELEASE_PROGRAM_DB_INSTALL_TYPES Full Developer)

    SET(CPACK_COMPONENT_DEBUG_PROGRAM_DB_DISPLAY_NAME "Debug Program Database")
    SET(CPACK_COMPONENT_DEBUG_PROGRAM_DB_DESCRIPTION "Debug Program Database Description")
    SET(CPACK_COMPONENT_DEBUG_PROGRAM_DB_GROUP "Development")
    SET(CPACK_COMPONENT_DEBUG_PROGRAM_DB_INSTALL_TYPES Full Developer)

    #Tools
    SET(CPACK_COMPONENT_DEVELOPMENT_TOOLS_DISPLAY_NAME "Tools")
    SET(CPACK_COMPONENT_DEVELOPMENT_TOOLS_DESCRIPTION "Tools Description")
    SET(CPACK_COMPONENT_DEVELOPMENT_TOOLS_GROUP "Development")
    SET(CPACK_COMPONENT_DEVELOPMENT_TOOLS_INSTALL_TYPES Full Developer)

    #Configuration
    SET(CPACK_COMPONENT_DEVELOPMENT_CONFIGURATION_DISPLAY_NAME "Cmake Configuration")
    SET(CPACK_COMPONENT_DEVELOPMENT_CONFIGURATION_DESCRIPTION "Cmake files")
    SET(CPACK_COMPONENT_DEVELOPMENT_CONFIGURATION_GROUP "Development")
    SET(CPACK_COMPONENT_DEVELOPMENT_CONFIGURATION_INSTALL_TYPES Full Developer)

    #Headers
    SET(CPACK_COMPONENT_CODE_HEADERS_DISPLAY_NAME "C++ Headers")
    SET(CPACK_COMPONENT_CODE_HEADERS_DESCRIPTION "C++ Header, inline, and insert files.")
    SET(CPACK_COMPONENT_CODE_HEADERS_GROUP "Development")
    SET(CPACK_COMPONENT_CODE_HEADERS_INSTALL_TYPES Full Developer)

    #Examples
    SET(CPACK_COMPONENT_GROUP_EXAMPES_DESCRIPTION "OpenSG Examples.")

    SET(CPACK_COMPONENT_EXAMPLES_BASIC_DISPLAY_NAME "Simple Examples")
    SET(CPACK_COMPONENT_EXAMPLES_BASIC_DESCRIPTION "A Collection of Simple OpenSG Examples")
    SET(CPACK_COMPONENT_EXAMPLES_BASIC_GROUP "Examples")
    SET(CPACK_COMPONENT_EXAMPLES_BASIC_INSTALL_TYPES Full Developer)

    SET(CPACK_COMPONENT_EXAMPLES_ADVANCED_DISPLAY_NAME "Advanced Examples")
    SET(CPACK_COMPONENT_EXAMPLES_ADVANCED_DESCRIPTION "A Collection of Advanced OpenSG Examples")
    SET(CPACK_COMPONENT_EXAMPLES_ADVANCED_GROUP "Examples")
    SET(CPACK_COMPONENT_EXAMPLES_ADVANCED_INSTALL_TYPES Full Developer)

    #Shared Data
    SET(CPACK_COMPONENT_GROUP_DATA_DESCRIPTION "Extra Data files.")

    SET(CPACK_COMPONENT_DATA_IMAGES_DISPLAY_NAME "Images")
    SET(CPACK_COMPONENT_DATA_IMAGES_DESCRIPTION "OpenSG Images and Icons")
    SET(CPACK_COMPONENT_DATA_IMAGES_GROUP "Data")
    SET(CPACK_COMPONENT_DATA_IMAGES_INSTALL_TYPES Full Developer Runtime)

    #Documentation
    SET(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "Documentation.")

    #Dependencies
    #Boost
    #Base

    #NSIS specific configuration
    IF(WIN32)
        INCLUDE(InstallRequiredSystemLibraries)
        IF(OSGBUILD_PACKAGE_TYPE STREQUAL "NSIS")
            IF(MSVC AND (${CMAKE_VERSION} VERSION_GREATER "2.8.0" OR
                         ${CMAKE_VERSION} VERSION_EQUAL   "2.8.0"   ))
                 include(CMakeDetermineVSServicePack)
                 DetermineVSServicePack( my_service_pack )

                 IF( my_service_pack )
                     SET(CPACK_PACKAGE_FILE_NAME       "${PROJECT_NAME}-${OSG_VERSION}-${SYSTEM_SPEC}-${my_service_pack}")
                 ENDIF()
            ENDIF()

            #Extra install commands
            SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "")
            SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "")


            SET(CPACK_NSIS_MUI_ICON            "${CMAKE_SOURCE_DIR}/CMake/Packaging/Windows/OpenSG2_Icon.ico")
            SET(CPACK_NSIS_MUI_UNIICON         "${CMAKE_SOURCE_DIR}/CMake/Packaging/Windows/OpenSG2_Icon.ico")
            FILE(TO_NATIVE_PATH                "${CMAKE_SOURCE_DIR}/CMake/Packaging/Windows/InstallerHeader.bmp" CPACK_PACKAGE_ICON)
            SET(CPACK_NSIS_MODIFY_PATH         ON)
            SET(CPACK_NSIS_INSTALLED_ICON_NAME "${CPACK_PACKAGE_NAME}")
            SET(CPACK_NSIS_HELP_LINK           "http://www.opensg.org/wiki/Help")
            SET(CPACK_NSIS_URL_INFO_ABOUT      "http://www.opensg.org")
            SET(CPACK_NSIS_CONTACT             "${CPACK_PACKAGE_CONTACT}")
            SET(CPACK_NSIS_CREATE_ICONS_EXTRA  "createShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME} Directory.lnk' '$INSTDIR'")
            SET(CPACK_NSIS_DELETE_ICONS_EXTRA  "Delete '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME} Directory.lnk'")
            SET(CPACK_NSIS_MENU_LINKS          "")
            #FILE(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/CMake/Packaging/Windows/InstallFinish.bmp" CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP)
            #FILE(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/CMake/Packaging/Windows/UnInstallFinish.bmp" CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP)
        ENDIF()
    ENDIF()


    # Date macro by Benoit RAT (www.neub.co.nr)
    MACRO (TODAY RESULT)
        IF (WIN32)
            EXECUTE_PROCESS(COMMAND "date /T" OUTPUT_VARIABLE ${RESULT})
            string(REGEX REPLACE "(..)/(..)/..(..).*" "\\3\\2\\1" "${RESULT}" "${${RESULT}}")
        ELSEIF(UNIX)
            EXECUTE_PROCESS(COMMAND "date" "+%d/%m/%Y" OUTPUT_VARIABLE ${RESULT})
            string(REGEX REPLACE "(..)/(..)/..(..).*" "\\3\\2\\1" "${RESULT}" "${${RESULT}}")
        ELSE (WIN32)
            MESSAGE(SEND_ERROR "date not implemented")
            SET(${RESULT} 000000)
        ENDIF (WIN32)
    ENDMACRO (TODAY)

    TODAY(DATE)

    # Determine package type
    IF(OSGBUILD_PACKAGE_TYPE STREQUAL "")
        IF(WIN32)
            SET(OSGBUILD_PACKAGE_TYPE "ZIP")
        ELSE(WIN32)
            SET(OSGBUILD_PACKAGE_TYPE "RPM")
        ENDIF(WIN32)
    ENDIF(OSGBUILD_PACKAGE_TYPE STREQUAL "")

    STRING(TOUPPER ${OSGBUILD_PACKAGE_TYPE} CPACK_GENERATOR)

    IF(${CPACK_GENERATOR} STREQUAL "TBZ2")
        SET( PACK_EXT "tar.bz2" )
    ELSEIF(${CPACK_GENERATOR} STREQUAL "TGZ")
        SET( PACK_EXT "tar.gz" )
    ELSE()
        STRING(TOLOWER ${OSGBUILD_PACKAGE_TYPE} PACK_EXT)
    ENDIF()

    SET(PACKAGE "${CPACK_PACKAGE_FILE_NAME}.${PACK_EXT}")
    SET(OUTFILE "${CPACK_PACKAGE_FILE_NAME}-${BUILDNAME}-${DATE}.${PACK_EXT}")

    INCLUDE(CPack)


    # For some reason using ${CPACK_OUTPUT_FILE_NAME} in here doesn't work, and neither does setting PACKAGE to it. :(
    IF(WIN32)
        #TODO: Need a way to do this on Windows
        #ADD_CUSTOM_TARGET(PackageUpload COMMAND curl -F "code=${OPENSG_UPLOAD_CODE}" -F "quiet=1" -F "out=${OUTFILE}" -F "file=@${PACKAGE}" http://www.opensg.org/htdocs/drop.php )
        #ADD_DEPENDENCIES(PackageUpload "${CPACK_OUTPUT_FILE_NAME}")
    ELSE(WIN32)
        ADD_CUSTOM_TARGET(PackageUpload COMMAND curl -F "code=${OPENSG_UPLOAD_CODE}" -F "quiet=1" -F "out=${OUTFILE}" -F "file=@${PACKAGE}" http://www.opensg.org/htdocs/drop.php )
        ADD_DEPENDENCIES(PackageUpload "${CPACK_OUTPUT_FILE_NAME}")
    ENDIF(WIN32)


ENDIF(OSGBUILD_ENABLE_PACKAGING)

IF(WIN32)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;DebugOpt;ReleaseNoOpt"
                              CACHE STRING "OpenSG Build Types" FORCE )
ENDIF(WIN32)

IF(OSG_WITH_CUDA)
  CUDA_BUILD_CLEAN_TARGET()
ENDIF(OSG_WITH_CUDA)

