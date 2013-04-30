CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(OSGGLEWSrcDir)

  MESSAGE(STATUS "adding glew from : ${OSGGLEWSrcDir}")

  PROJECT(OSGGLEW)

  SET(${PROJECT_NAME}SharedTarget osgglew)
  SET(${PROJECT_NAME}StaticTarget libosgglew)

  SET(OSG_GLEW_SRCS ${OSGGLEWSrcDir}/src/glew.c)

  SET(OSG_GLEW_HDR ${OSGGLEWSrcDir}/include/GL/glew.h
                   ${OSGGLEWSrcDir}/include/GL/glxew.h
                   ${OSGGLEWSrcDir}/include/GL/wglew.h)

  INCLUDE_DIRECTORIES(${OSGGLEWSrcDir}/include)

  SET(OSGGLEWLIB_DEF WIN32_MEAN_AND_LEAN;VC_EXTRALEAN;_VC80_UPGRADE=0x0600)

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_GLEW_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                            DEBUG_POSTFIX "D")
    ENDIF(WIN32)

    SET(OSGGLEWLIB_DEF_SHARED ${OSGGLEWLIB_DEF};GLEW_BUILD;_WINDLL)
                          
    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGGLEWLIB_DEF_SHARED}")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_gl_LIBRARY})

    IF(WIN32)

      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  CONFIGURATIONS Release
                  RUNTIME DESTINATION bin COMPONENT release_runtimes
                  LIBRARY DESTINATION lib COMPONENT release_libraries
                  ARCHIVE DESTINATION lib COMPONENT release_libraries)

      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  CONFIGURATIONS Debug
                  RUNTIME DESTINATION bin COMPONENT debug_runtimes
                  LIBRARY DESTINATION lib COMPONENT debug_libraries
                  ARCHIVE DESTINATION lib COMPONENT debug_libraries)

    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries)
    ENDIF(WIN32)

  ENDIF(BUILD_SHARED_LIBS)

  INSTALL(FILES ${OSG_GLEW_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/GL
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  SET(OSG_GLEW_INCLUDE_DIR ${OSGGLEWSrcDir}/include CACHE PATH "")
  SET(OSG_GLEW_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGGLEWSrcDir)
  MESSAGE(STATUS "ignoring glew")

  SET(OSGGLEWSrcDir "" CACHE PATH "")
ENDIF(OSGGLEWSrcDir)
