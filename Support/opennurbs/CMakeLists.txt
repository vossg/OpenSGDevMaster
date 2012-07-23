CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(OSGOpenNurbsSrcDir)

  PROJECT(OSGOpenNurbs)

  SET(${PROJECT_NAME}SharedTarget osgopennurbs)
  IF(WIN32)
    SET(${PROJECT_NAME}StaticTarget libosgopennurbs)
  ELSE(WIN32)
    SET(${PROJECT_NAME}StaticTarget osgopennurbslib)
  ENDIF(WIN32)

  SET(OSG_OPENNURBS_SRCS ${OSGOpenNurbsSrcDir}/opennurbs_3dm_attributes.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_3dm_properties.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_3dm_settings.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_annotation.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_annotation2.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_arc.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_arccurve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_archive.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_array.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_base32.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_base64.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_basic.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_beam.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_bezier.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_beziervolume.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_bitmap.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_bounding_box.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_box.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_changesrf.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_extrude.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_io.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_isvalid.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_kinky.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_region.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_tools.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_brep_v2valid.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_circle.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_color.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_cone.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_crc.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_curve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_curveonsurface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_curveproxy.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_cylinder.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_defines.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_detail.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_dimstyle.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_ellipse.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_error.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_error_message.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_evaluate_nurbs.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_extensions.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_font.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_geometry.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_gl.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_group.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_hatch.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_instance.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_intersect.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_knot.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_layer.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_light.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_line.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_linecurve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_linetype.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_lookup.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_massprop.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_material.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_math.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_matrix.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_memory.c  
                         ${OSGOpenNurbsSrcDir}/opennurbs_memory_util.c  
                         ${OSGOpenNurbsSrcDir}/opennurbs_mesh.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_mesh_ngon.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_mesh_tools.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_morph.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_nurbscurve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_nurbssurface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_nurbsvolume.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_object.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_object_history.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_objref.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_offsetsurface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_optimize.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_plane.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_planesurface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_pluginlist.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_point.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_pointcloud.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_pointgeometry.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_pointgrid.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_polycurve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_polyedgecurve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_polyline.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_polylinecurve.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_quaternion.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_rand.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_revsurface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_rtree.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_sphere.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_string.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_sum.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_sumsurface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_surface.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_surfaceproxy.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_textlog.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_torus.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_userdata.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_uuid.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_viewport.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_workspace.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_wstring.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_x.cpp  
                         ${OSGOpenNurbsSrcDir}/opennurbs_xform.cpp 
                         ${OSGOpenNurbsSrcDir}/opennurbs_zlib.cpp 
                         ${OSGOpenNurbsSrcDir}/opennurbs_zlib_memory.cpp)

  SET(OSG_OPENNURBS_HDR ${OSGOpenNurbsSrcDir}/opennurbs.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_3dm.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_3dm_attributes.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_3dm_properties.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_3dm_settings.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_annotation.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_annotation2.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_arc.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_arccurve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_archive.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_array.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_array_defs.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_base32.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_base64.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_beam.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_bezier.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_bitmap.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_bounding_box.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_box.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_brep.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_circle.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_color.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_cone.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_crashtest.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_crc.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_curve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_curveonsurface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_curveproxy.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_cylinder.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_defines.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_detail.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_dimstyle.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_ellipse.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_error.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_evaluate_nurbs.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_extensions.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_font.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_fpoint.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_geometry.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_gl.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_group.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_hatch.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_instance.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_intersect.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_knot.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_layer.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_light.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_line.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_linecurve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_linestyle.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_linetype.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_lookup.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_mapchan.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_massprop.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_material.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_math.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_matrix.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_memory.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_mesh.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_nurbscurve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_nurbssurface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_object.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_object_history.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_objref.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_offsetsurface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_optimize.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_plane.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_planesurface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_pluginlist.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_point.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_pointcloud.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_pointgeometry.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_pointgrid.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_polycurve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_polyedgecurve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_polyline.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_polylinecurve.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_quaternion.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_rand.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_rendering.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_revsurface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_rtree.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_sphere.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_string.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_sumsurface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_surface.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_surfaceproxy.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_system.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_textlog.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_texture.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_texture_mapping.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_torus.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_userdata.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_uuid.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_version.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_viewport.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_workspace.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_x.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_xform.h  
                        ${OSGOpenNurbsSrcDir}/opennurbs_zlib.h)

  SET(OSG_OPENNURBS_ZLIB_SRCS ${OSGOpenNurbsSrcDir}/zlib/adler32.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/compress.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/crc32.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/deflate.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/infback.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/inffast.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/inflate.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/inftrees.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/trees.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/uncompr.c 
		                      ${OSGOpenNurbsSrcDir}/zlib/zutil.c)

  SET(OSG_OPENNURBS_ZLIB_HDR ${OSGOpenNurbsSrcDir}/zlib/crc32.h
		                     ${OSGOpenNurbsSrcDir}/zlib/deflate.h
		                     ${OSGOpenNurbsSrcDir}/zlib/inffast.h
		                     ${OSGOpenNurbsSrcDir}/zlib/inffixed.h
		                     ${OSGOpenNurbsSrcDir}/zlib/inflate.h 
		                     ${OSGOpenNurbsSrcDir}/zlib/inftrees.h
		                     ${OSGOpenNurbsSrcDir}/zlib/trees.h 
		                     ${OSGOpenNurbsSrcDir}/zlib/zconf.h 
		                     ${OSGOpenNurbsSrcDir}/zlib/zlib.h 
		                     ${OSGOpenNurbsSrcDir}/zlib/zutil.h)

  SET(OSGOPENNURBS_DEF  _GNU_SOURCE;MY_ZCALLOC;Z_PREFIX)

  IF(WIN32)
    SET(OSGOPENNURBS_DEF  ${OSGOPENNURBS_DEF};UNICODE;_UNICODE)
  ENDIF(WIN32)

#  EXECUTE_PROCESS(
#    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
#                     "${OSGTiffLibSrcDir}/libtiff/tif_config.h.vc"
#                     "${CMAKE_BINARY_DIR}/libtiff/tif_config.h")
#  EXECUTE_PROCESS(
#    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
#                     "${OSGTiffLibSrcDir}/libtiff/tiffconf.h.vc"
#                     "${CMAKE_BINARY_DIR}/libtiff/tiffconf.h")
  
#  INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/libtiff)
#  INCLUDE_DIRECTORIES(${OSGJpegLibSrcDir})

  IF(WIN32)
    INCLUDE_DIRECTORIES(${OSG_ZLIB_INCLUDE_DIR})
  ENDIF(WIN32)

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED 
                  ${OSG_OPENNURBS_SRCS}
                  ${OSG_OPENNURBS_ZLIB_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                            DEBUG_POSTFIX "D")

      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_gl_LIBRARY}
                                                           ${OPENGL_glu_LIBRARY}
                                                           Rpcrt4)
    ENDIF(WIN32)

    IF(APPLE)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_gl_LIBRARY})
    ENDIF(APPLE)

    IF(WIN32)
      SET(OSGOPENNURBS_DEF_SHARED ${OSGOPENNURBS_DEF};ON_DLL_EXPORTS;ON_COMPILING_OPENNURBS)
    ELSE(WIN32)
      SET(OSGOPENNURBS_DEF_SHARED ${OSGOPENNURBS_DEF})
    ENDIF(WIN32)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGOPENNURBS_DEF_SHARED}")

    IF(WIN32)    
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION bin COMPONENT runtimes
                  LIBRARY DESTINATION lib COMPONENT libraries
                  ARCHIVE DESTINATION lib COMPONENT libraries)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries)
    ENDIF(WIN32)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_OPENNURBS_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                            DEBUG_POSTFIX "D")
    ENDIF(WIN32)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGOPENNURBS_DEF}")


    IF(WIN32)    
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION bin COMPONENT libraries
                  LIBRARY DESTINATION lib COMPONENT libraries
                  ARCHIVE DESTINATION lib COMPONENT libraries)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT static_libraries
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT static_libraries
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT static_libraries)
    ENDIF(WIN32)

  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_OPENNURBS_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/opennurbs
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OPENNURBS_ZLIB_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/opennurbs/zlib
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

ELSE(OSGOpenNurbsSrcDir)
  SET(OSGOpenNurbsSrcDir "" CACHE PATH "")
ENDIF(OSGOpenNurbsSrcDir)
