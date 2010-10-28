CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGFreeGlutSrcDir)

  PROJECT(OSGFreeGlut)

  SET(${PROJECT_NAME}SharedTarget osgglut)
  SET(${PROJECT_NAME}StaticTarget libosgglut)

  SET(OSG_FREEGLUT_SRCS ${OSGFreeGlutSrcDir}/src/freeglut_callbacks.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_cursor.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_display.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_ext.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_font.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_font_data.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_gamemode.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_geometry.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_glutfont_definitions.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_init.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_input_devices.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_joystick.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_main.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_menu.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_misc.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_overlay.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_state.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_stroke_mono_roman.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_stroke_roman.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_structure.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_teapot.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_videoresize.c
                        ${OSGFreeGlutSrcDir}/src/freeglut_window.c)

  SET(OSG_FREEGLUT_HDR ${OSGFreeGlutSrcDir}/include/GL/glut.h
                       ${OSGFreeGlutSrcDir}/include/GL/freeglut.h
                       ${OSGFreeGlutSrcDir}/include/GL/freeglut_std.h
                       ${OSGFreeGlutSrcDir}/include/GL/freeglut_ext.h)

  INCLUDE_DIRECTORIES(${OSGFreeGlutSrcDir}/include)

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_FREEGLUT_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEFINE_SYMBOL FREEGLUT_EXPORTS   
                          DEBUG_POSTFIX "D")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_gl_LIBRARY})

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_FREEGLUT_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D"
                          COMPILE_DEFINITIONS FREEGLUT_STATIC)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_FREEGLUT_HDR}
          DESTINATION include/GL
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  SET(OSG_GLUT_INCLUDE_DIR ${OSGFreeGlutSrcDir}/include CACHE PATH "")
  SET(OSG_GLUT_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
  SET(OSG_GLUT_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGFreeGlutSrcDir)
  SET(OSGFreeGlutSrcDir "" CACHE PATH "")
ENDIF(OSGFreeGlutSrcDir)
