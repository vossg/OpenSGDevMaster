CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGLibIconvSrcDir)

  PROJECT(OSGLibIconv)

  SET(${PROJECT_NAME}SharedTarget osgiconv)
  SET(${PROJECT_NAME}StaticTarget libosgiconv)

  SET(OSG_LIBICONV_SRCS ${OSGLibIconvSrcDir}/source/lib/iconv.c
                        ${OSGLibIconvSrcDir}/source/libcharset/lib/localcharset.c
                        ${OSGLibIconvSrcDir}/source/lib/relocatable.c)

  SET(OSG_LIBICONV_HDR ${OSGLibIconvSrcDir}/source/include/iconv.h)

  SET(OSGLIBICONV_DEF _UNICODE;UNICODE;relocate=libiconv_relocate;set_relocation_prefix=libiconv_set_relocation_prefix;HAVE_CONFIG_H;ENABLE_RELOCATABLE=1;IN_LIBRARY;NO_XMALLOC;INSTALLPREFIX="${CMAKE_INSTALL_PREFIX}";INSTALLDIR="${CMAKE_INSTALL_PREFIX}";LIBDIR="${CMAKE_INSTALL_PREFIX}")
  
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/source)
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/source/lib)
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/source/include)

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

ELSE(OSGLibIconvSrcDir)
  SET(OSGLibIconvSrcDir "" CACHE PATH "")
ENDIF(OSGLibIconvSrcDir)
