CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGGlutSrcDir)

  PROJECT(OSGGlut)

  SET(${PROJECT_NAME}SharedTarget osgglut)

  SET(OSG_GLUT_SRCS ${OSGGlutSrcDir}/lib/glut/glut_8x13.c
                    ${OSGGlutSrcDir}/lib/glut/glut_9x15.c
                    ${OSGGlutSrcDir}/lib/glut/glut_bitmap.c
                    ${OSGGlutSrcDir}/lib/glut/glut_bwidth.c
                    ${OSGGlutSrcDir}/lib/glut/glut_cindex.c
                    ${OSGGlutSrcDir}/lib/glut/glut_cmap.c
                    ${OSGGlutSrcDir}/lib/glut/glut_cursor.c
                    ${OSGGlutSrcDir}/lib/glut/glut_dials.c
                    ${OSGGlutSrcDir}/lib/glut/glut_dstr.c
                    ${OSGGlutSrcDir}/lib/glut/glut_event.c
                    ${OSGGlutSrcDir}/lib/glut/glut_ext.c
                    ${OSGGlutSrcDir}/lib/glut/glut_fcb.c
                    ${OSGGlutSrcDir}/lib/glut/glut_fullscrn.c
                    ${OSGGlutSrcDir}/lib/glut/glut_gamemode.c
                    ${OSGGlutSrcDir}/lib/glut/glut_get.c
                    ${OSGGlutSrcDir}/lib/glut/glut_glxext.c
                    ${OSGGlutSrcDir}/lib/glut/glut_hel10.c
                    ${OSGGlutSrcDir}/lib/glut/glut_hel12.c
                    ${OSGGlutSrcDir}/lib/glut/glut_hel18.c
                    ${OSGGlutSrcDir}/lib/glut/glut_init.c
                    ${OSGGlutSrcDir}/lib/glut/glut_input.c
                    ${OSGGlutSrcDir}/lib/glut/glut_joy.c
                    ${OSGGlutSrcDir}/lib/glut/glut_key.c
                    ${OSGGlutSrcDir}/lib/glut/glut_keyctrl.c
                    ${OSGGlutSrcDir}/lib/glut/glut_keyup.c
#                    ${OSGGlutSrcDir}/lib/glut/glut_menu.c
#                    ${OSGGlutSrcDir}/lib/glut/glut_menu2.c
                    ${OSGGlutSrcDir}/lib/glut/glut_mesa.c
                    ${OSGGlutSrcDir}/lib/glut/glut_modifier.c
                    ${OSGGlutSrcDir}/lib/glut/glut_mroman.c
                    ${OSGGlutSrcDir}/lib/glut/glut_overlay.c
                    ${OSGGlutSrcDir}/lib/glut/glut_roman.c
                    ${OSGGlutSrcDir}/lib/glut/glut_shapes.c
                    ${OSGGlutSrcDir}/lib/glut/glut_space.c
                    ${OSGGlutSrcDir}/lib/glut/glut_stroke.c
                    ${OSGGlutSrcDir}/lib/glut/glut_swap.c
                    ${OSGGlutSrcDir}/lib/glut/glut_swidth.c
                    ${OSGGlutSrcDir}/lib/glut/glut_tablet.c
                    ${OSGGlutSrcDir}/lib/glut/glut_teapot.c
                    ${OSGGlutSrcDir}/lib/glut/glut_tr10.c
                    ${OSGGlutSrcDir}/lib/glut/glut_tr24.c
                    ${OSGGlutSrcDir}/lib/glut/glut_util.c
                    ${OSGGlutSrcDir}/lib/glut/glut_vidresize.c
                    ${OSGGlutSrcDir}/lib/glut/glut_warp.c
                    ${OSGGlutSrcDir}/lib/glut/glut_win.c
                    ${OSGGlutSrcDir}/lib/glut/glut_winmisc.c
                    ${OSGGlutSrcDir}/lib/glut/win32_glx.c
                    ${OSGGlutSrcDir}/lib/glut/win32_menu.c
                    ${OSGGlutSrcDir}/lib/glut/win32_util.c
                    ${OSGGlutSrcDir}/lib/glut/win32_winproc.c
                    ${OSGGlutSrcDir}/lib/glut/win32_x11.c)

  SET(OSG_GLUT_HDR ${OSGGlutSrcDir}/include/GL/glut.h)

  INCLUDE_DIRECTORIES(${OSGGlutSrcDir}/include)

  ADD_DEFINITIONS(-U"GLUT_USE_SGI_OPENGL")

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED 
                ${OSG_GLUT_SRCS}
                ${OSGGlutSrcDir}/lib/glut/glut.def)

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEFINE_SYMBOL GLUT32_EXPORTS   
                          DEBUG_POSTFIX "D")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_gl_LIBRARY}
                                                         ${OPENGL_glu_LIBRARY})

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_SHARED_LIBS)


  INSTALL(FILES ${OSG_GLUT_HDR}
          DESTINATION include/GL
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  SET(OSG_GLUT_INCLUDE_DIR ${OSGGlutSrcDir}/include CACHE PATH "")
  SET(OSG_GLUT_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
  SET(OSG_GLUT_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGGlutSrcDir)
  SET(OSGGlutSrcDir "" CACHE PATH "")
ENDIF(OSGGlutSrcDir)
