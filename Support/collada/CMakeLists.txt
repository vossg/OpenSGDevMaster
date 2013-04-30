CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(WIN32)
  IF(OSGColladaSrcDir AND OSGPcreSrcDir AND OSGLibXml2SrcDir)
    SET(_OSG_COLLADA_PRECOND TRUE)
  ELSE()
    SET(_OSG_COLLADA_PRECOND FALSE)
  ENDIF(OSGColladaSrcDir AND OSGPcreSrcDir AND OSGLibXml2SrcDir)
ELSE(WIN32)
  FIND_PACKAGE(LibXml2)

  IF(OSGColladaSrcDir AND LIBXML2_FOUND)
    SET(_OSG_COLLADA_PRECOND TRUE)
  ELSE()
    SET(_OSG_COLLADA_PRECOND FALSE)
  ENDIF(OSGColladaSrcDir AND LIBXML2_FOUND)
ENDIF(WIN32)


IF(_OSG_COLLADA_PRECOND)

  MESSAGE(STATUS "adding collada from : ${OSGColladaSrcDir}")

  PROJECT(OSGCollada)

  SET(${PROJECT_NAME}SharedTarget_14 osgcollada14dom22)
  SET(${PROJECT_NAME}SharedTarget_15 osgcollada15dom22)

  IF(WIN32)
    SET(${PROJECT_NAME}StaticTarget_14 libosgcollada14dom24)
    SET(${PROJECT_NAME}StaticTarget_15 libosgcollada15dom24)
  ELSE(WIN32)
    SET(${PROJECT_NAME}StaticTarget_14 osgcollada14dom24lib)
    SET(${PROJECT_NAME}StaticTarget_15 osgcollada15dom24lib)
  ENDIF(WIN32)

#  FILE(GLOB variable [RELATIVE path] [globbing expressions]...)

  FILE(GLOB OSG_COLLADADAE_SRCS "${OSGColladaSrcDir}/dom/src/dae/*.cpp")

  SET(OSG_COLLADADAE_SRCS ${OSG_COLLADADAE_SRCS}
                          ${OSGColladaSrcDir}/dom/src/modules/STLDatabase/daeSTLDatabase.cpp
                          ${OSGColladaSrcDir}/dom/src/modules/stdErrPlugin/stdErrPlugin.cpp
                          ${OSGColladaSrcDir}/dom/src/modules/LIBXMLPlugin/daeLIBXMLPlugin.cpp
                          ${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/ioapi.c
                          ${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/zip.c
                          ${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/unzip.c)

  IF(WIN32)
    SET(OSG_COLLADADAE_SRCS ${OSG_COLLADADAE_SRCS}
                            ${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/iowin32.c)
  ENDIF()

  FILE(GLOB OSG_COLLADADAE_HDR "${OSGColladaSrcDir}/dom/include/dae/*.h")
  FILE(GLOB OSG_COLLADA_HDR    "${OSGColladaSrcDir}/dom/include/*.h")
  FILE(GLOB OSG_COLLADA14_SRCS "${OSGColladaSrcDir}/dom/src/1.4/dom/*.cpp")
  FILE(GLOB OSG_COLLADA15_SRCS "${OSGColladaSrcDir}/dom/src/1.5/dom/*.cpp")
  FILE(GLOB OSG_COLLADA14_HDR  "${OSGColladaSrcDir}/dom/include/1.4/dom/*.h")
  FILE(GLOB OSG_COLLADA15_HDR  "${OSGColladaSrcDir}/dom/include/1.5/dom/*.h")

  SET(OSG_COLLADAMOD_HDR ${OSGColladaSrcDir}/dom/include/modules/daeLIBXMLPlugin.h
                         ${OSGColladaSrcDir}/dom/include/modules/stdErrPlugin.h
                         ${OSGColladaSrcDir}/dom/include/modules/daeSTLDatabase.h)

  SET(OSGCOLLADA_DEF DOM_INCLUDE_LIBXML)

  IF(APPLE)
    SET(OSGCOLLADA_DEF ${OSGCOLLADA_DEF};USE_FILE32API)
  ENDIF()

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/crypt.h"
                     "${CMAKE_BINARY_DIR}/collada/include/crypt.h")
  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/ioapi.h"
                     "${CMAKE_BINARY_DIR}/collada/include/ioapi.h")

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/iowin32.h"
                     "${CMAKE_BINARY_DIR}/collada/include/iowin32.h")

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/unzip.h"
                     "${CMAKE_BINARY_DIR}/collada/include/unzip.h")
  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGColladaSrcDir}/dom/external-libs/minizip-1.1/zip.h"
                     "${CMAKE_BINARY_DIR}/collada/include/zip.h")

  INCLUDE_DIRECTORIES(${OSG_BOOST_INCDIRS})
  INCLUDE_DIRECTORIES(${OSGColladaSrcDir}/dom/include)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/include)

  IF(UNIX AND APPLE AND EXISTS /sw/include)
    INCLUDE_DIRECTORIES(/sw/include)
  ENDIF(UNIX AND APPLE AND EXISTS /sw/include)

  IF(UNIX AND APPLE AND EXISTS /sw/lib)
    LINK_DIRECTORIES(/sw/lib)
  ENDIF(UNIX AND APPLE AND EXISTS /sw/lib)

  IF(WIN32)
    INCLUDE_DIRECTORIES(${OSGPcreSrcDir})
    INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/pcre)
    INCLUDE_DIRECTORIES(${OSGLibXml2SrcDir}/include)
    INCLUDE_DIRECTORIES(${OSG_ZLIB_INCLUDE_DIR})
  ELSE(WIN32)
    INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
  ENDIF(WIN32)


  ## 1.4 ##

  ADD_SUBDIRECTORY(Dom14)

  ## 1.5 ##

  IF(OSG_BUILD_COLLADADOM_15)

    ADD_SUBDIRECTORY(Dom15)

  ENDIF(OSG_BUILD_COLLADADOM_15)


  INSTALL(FILES ${OSG_COLLADA_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)
  INSTALL(FILES ${OSG_COLLADADAE_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/dae
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)
  INSTALL(FILES ${OSG_COLLADAMOD_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/modules
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_COLLADA14_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/1.4/dom
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  IF(OSG_BUILD_COLLADADOM_15)
    INSTALL(FILES ${OSG_COLLADA15_HDR}
            DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/1.5/dom
            COMPONENT code_headers
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ)
  ENDIF(OSG_BUILD_COLLADADOM_15)

ELSE(_OSG_COLLADA_PRECOND)
  MESSAGE(STATUS "ignoring collada")

  SET(OSGColladaSrcDir "" CACHE PATH "")
ENDIF(_OSG_COLLADA_PRECOND)
