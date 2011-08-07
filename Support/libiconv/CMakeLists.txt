CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGLibIconvSrcDir)

  PROJECT(OSGLibIconv)

  SET(${PROJECT_NAME}SharedTarget osgiconv)
  SET(${PROJECT_NAME}StaticTarget libosgiconv)

  SET(OSGLibIconvLibSrcDir ${OSGLibIconvSrcDir} CACHE PATH "")

  IF(EXISTS ${OSGLibIconvSrcDir}/source)
    SET(OSGLibIconvSrcDir ${OSGLibIconvSrcDir}/source CACHE PATH "" FORCE)
  ELSEIF(EXISTS ${OSGLibIconvSrcDir}/src/libiconv/1.9.2/libiconv-1.9.2)
    SET(OSGLibIconvLibSrcDir ${OSGLibIconvSrcDir}/src/libiconv/1.9.2/libiconv-1.9.2-src CACHE PATH "" FORCE)
    SET(OSGLibIconvSrcDir ${OSGLibIconvSrcDir}/src/libiconv/1.9.2/libiconv-1.9.2 CACHE PATH "" FORCE)
  ENDIF()

  SET(OSG_LIBICONV_SRCS ${OSGLibIconvLibSrcDir}/lib/iconv.c
                        ${OSGLibIconvLibSrcDir}/libcharset/lib/localcharset.c
                        ${OSGLibIconvLibSrcDir}/lib/relocatable.c)

  IF(NOT EXISTS ${OSGLibIconvSrcDir}/include/iconv.h)

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                       "${CMAKE_CURRENT_SOURCE_DIR}/iconv.h"
                       "${CMAKE_BINARY_DIR}/libiconv/include/iconv.h")

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                       "${CMAKE_CURRENT_SOURCE_DIR}/config.h"
                       "${CMAKE_BINARY_DIR}/libiconv/config.h")

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                       "${CMAKE_CURRENT_SOURCE_DIR}/localcharset.h"
                       "${CMAKE_BINARY_DIR}/libiconv/localcharset.h")
    

    SET(OSG_LIBICONV_HDR ${CMAKE_BINARY_DIR}/libiconv/include/iconv.h)

    INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/libiconv/include)
    INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/libiconv)

  ELSE()

    SET(OSG_LIBICONV_HDR ${OSGLibIconvSrcDir}/include/iconv.h)

  ENDIF()


  SET(OSGLIBICONV_DEF _UNICODE;UNICODE;relocate=libiconv_relocate;set_relocation_prefix=libiconv_set_relocation_prefix;HAVE_CONFIG_H;ENABLE_RELOCATABLE=1;IN_LIBRARY;NO_XMALLOC;INSTALLPREFIX="${CMAKE_INSTALL_PREFIX}";INSTALLDIR="${CMAKE_INSTALL_PREFIX}";LIBDIR="${CMAKE_INSTALL_PREFIX}")
  
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir})
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/lib)
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/libcharset/include)
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/include)

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_LIBICONV_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET(OSGLIBICONV_DEF_SHARED ${OSGLIBICONV_DEF};BUILDING_LIBICONV;BUILDING_DLL;PIC;)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGLIBICONV_DEF_SHARED}")

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_LIBICONV_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGLIBICONV_DEF}")


    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_LIBICONV_HDR}
          DESTINATION include
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  IF(NOT EXISTS ${OSGLibIconvSrcDir}/include/iconv.h)
    SET(OSG_ICONV_INCLUDE_DIR ${CMAKE_BINARY_DIR}/libiconv/include CACHE PATH "" FORCE)
  ELSE()
    SET(OSG_ICONV_INCLUDE_DIR ${OSGLibIconvSrcDir}/include CACHE PATH "" FORCE)
  ENDIF()

  SET(OSG_ICONV_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "" FORCE)
  SET(OSG_ICONV_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "" FORCE)

ELSE(OSGLibIconvSrcDir)
  SET(OSGLibIconvSrcDir "" CACHE PATH "")
ENDIF(OSGLibIconvSrcDir)
