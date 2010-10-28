CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGPcreSrcDir)

  PROJECT(OSGPcre)

  SET(${PROJECT_NAME}SharedTargetPcre    osgpcre)
  SET(${PROJECT_NAME}SharedTargetPcrecpp osgpcrecpp)
  SET(${PROJECT_NAME}StaticTargetPcre    libosgpcre)
  SET(${PROJECT_NAME}StaticTargetPcrecpp libosgpcrecpp)

  SET(OSG_PCRE_SRCS ${OSGPcreSrcDir}/pcre_compile.c
                    ${OSGPcreSrcDir}/pcre_config.c
                    ${OSGPcreSrcDir}/pcre_dfa_exec.c
                    ${OSGPcreSrcDir}/pcre_exec.c
                    ${OSGPcreSrcDir}/pcre_fullinfo.c
                    ${OSGPcreSrcDir}/pcre_get.c
                    ${OSGPcreSrcDir}/pcre_globals.c
                    ${OSGPcreSrcDir}/pcre_info.c
                    ${OSGPcreSrcDir}/pcre_maketables.c
                    ${OSGPcreSrcDir}/pcre_newline.c
                    ${OSGPcreSrcDir}/pcre_ord2utf8.c
                    ${OSGPcreSrcDir}/pcre_refcount.c
                    ${OSGPcreSrcDir}/pcre_study.c
                    ${OSGPcreSrcDir}/pcre_tables.c
                    ${OSGPcreSrcDir}/pcre_try_flipped.c
                    ${OSGPcreSrcDir}/pcre_ucd.c
                    ${OSGPcreSrcDir}/pcre_valid_utf8.c
                    ${OSGPcreSrcDir}/pcre_version.c
                    ${OSGPcreSrcDir}/pcre_xclass.c
                    ${CMAKE_BINARY_DIR}/pcre/pcre_chartables.c)

  SET(OSG_PCRECPP_SRCS ${OSGPcreSrcDir}/pcre_scanner.cc
                       ${OSGPcreSrcDir}/pcre_stringpiece.cc
                       ${OSGPcreSrcDir}/pcrecpp.cc)

  SET(OSG_PCRE_HDR ${OSGPSrcDir})
  SET(OSG_PCRECPP_HDR ${OSGPSrcDir})

  ADD_DEFINITIONS(-DHAVE_CONFIG_H)

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGPcreSrcDir}/pcre_chartables.c.dist"
                     "${CMAKE_BINARY_DIR}/pcre/pcre_chartables.c")

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGPcreSrcDir}/pcre.h.generic"
                     "${CMAKE_BINARY_DIR}/pcre/pcre.h")

  SET(pcre_have_ulong_long 1)
  SET(pcre_have_long_long 1)

  CONFIGURE_FILE("${OSGPcreSrcDir}/pcrecpparg.h.in"
                 "${CMAKE_BINARY_DIR}/pcre/pcrecpparg.h")

  SET(pcre_have_type_traits 0)
  SET(pcre_have_bits_type_traits 0)

  CONFIGURE_FILE("${OSGPcreSrcDir}/pcre_stringpiece.h.in"
                 "${CMAKE_BINARY_DIR}/pcre/pcre_stringpiece.h")

  INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/pcre)
  INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/pcre)
  INCLUDE_DIRECTORIES(${OSGPcreSrcDir})

  IF(BUILD_SHARED_LIBS)

    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetPcre} SHARED 
                                                   ${OSG_PCRE_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTargetPcre})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetPcre} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetPcre}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetPcrecpp} SHARED 
                                                      ${OSG_PCRECPP_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTargetPcrecpp})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetPcrecpp} PROPERTIES
                          DEBUG_POSTFIX "D")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTargetPcrecpp} ${${PROJECT_NAME}SharedTargetPcre})

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetPcrecpp}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetPcre} STATIC 
                                                   ${OSG_PCRE_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetPcre})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetPcre} PROPERTIES
                          DEBUG_POSTFIX "D"
                          COMPILE_DEFINITIONS PCRE_STATIC)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetPcre}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetPcrecpp} STATIC 
                                                      ${OSG_PCRECPP_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetPcrecpp})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetPcrecpp} PROPERTIES
                          DEBUG_POSTFIX "D"
                          COMPILE_DEFINITIONS PCRE_STATIC)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetPcrecpp}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

#  INSTALL(FILES ${OSG_PCRE_HDR}
#          DESTINATION include
#          PERMISSIONS OWNER_WRITE OWNER_READ
#                      GROUP_READ
#                      WORLD_READ)

ELSE(OSGPcreSrcDir)
  SET(OSGPcreSrcDir "" CACHE PATH "")
ENDIF(OSGPcreSrcDir)
