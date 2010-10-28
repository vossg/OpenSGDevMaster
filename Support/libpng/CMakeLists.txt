CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGLibPNGSrcDir AND OSGZLibSrcDir)

  PROJECT(OSGLibPNG)

  SET(${PROJECT_NAME}SharedTarget osgpng)
  SET(${PROJECT_NAME}StaticTarget libosgpng)

  SET(OSG_LIBPNG_SRCS ${OSGLibPNGSrcDir}/png.c
                      ${OSGLibPNGSrcDir}/pngerror.c
                      ${OSGLibPNGSrcDir}/pngget.c
                      ${OSGLibPNGSrcDir}/pngmem.c
                      ${OSGLibPNGSrcDir}/pngpread.c
                      ${OSGLibPNGSrcDir}/pngread.c
                      ${OSGLibPNGSrcDir}/pngrio.c
                      ${OSGLibPNGSrcDir}/pngrtran.c
                      ${OSGLibPNGSrcDir}/pngrutil.c
                      ${OSGLibPNGSrcDir}/pngset.c
                      ${OSGLibPNGSrcDir}/pngtrans.c
                      ${OSGLibPNGSrcDir}/pngwio.c
                      ${OSGLibPNGSrcDir}/pngwrite.c
                      ${OSGLibPNGSrcDir}/pngwtran.c
                      ${OSGLibPNGSrcDir}/pngwutil.c
                      ${OSGLibPNGSrcDir}/scripts/pngw32.def)

  SET(OSG_LIBPNG_HDR ${OSGLibPNGSrcDir}/png.h 
                     ${OSGLibPNGSrcDir}/pngconf.h)

  INCLUDE_DIRECTORIES(${OSG_ZLIB_INCLUDE_DIR})

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_LIBPNG_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEFINE_SYMBOL PNG_BUILD_DLL   
                          DEBUG_POSTFIX "D")

    SET(OSGPNGLIB_DEF_SHARED ZLIB_DLL)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGPNGLIB_DEF_SHARED}")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} osgzlib)

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_LIBPNG_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_LIBPNG_HDR}
          DESTINATION include
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  SET(OSG_PNG_INCLUDE_DIR ${OSGLibPNGSrcDir} CACHE PATH "")
  SET(OSG_PNG_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
  SET(OSG_PNG_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGLibPNGSrcDir AND OSGZLibSrcDir)

  SET(OSGLibPNGSrcDir "" CACHE PATH "")

ENDIF(OSGLibPNGSrcDir AND OSGZLibSrcDir)
