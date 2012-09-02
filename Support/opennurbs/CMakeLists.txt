CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FUNCTION(PROCESS_FILES SUBDIR OUTLIST FILES)
  FOREACH(_ON_FILE ${${FILES}})
    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OSGOpenNurbsSrcDir}/${SUBDIR}/${_ON_FILE}"
              "${CMAKE_BINARY_DIR}/External/opennurbs/${SUBDIR}/")

      LIST(APPEND TMP_OUTLIST "${CMAKE_BINARY_DIR}/External/opennurbs/${SUBDIR}/${_ON_FILE}")
  ENDFOREACH()


  SET(${OUTLIST} ${TMP_OUTLIST} PARENT_SCOPE)
ENDFUNCTION()

IF(OSGOpenNurbsSrcDir)

  PROJECT(OSGOpenNurbs)

  SET(${PROJECT_NAME}SharedTarget osgopennurbs)
  IF(WIN32)
    SET(${PROJECT_NAME}StaticTarget libosgopennurbs)
  ELSE(WIN32)
    SET(${PROJECT_NAME}StaticTarget osgopennurbslib)
  ENDIF(WIN32)


  SET(OSG_OPENNURBS_LSRCS opennurbs_3dm_attributes.cpp  
                          opennurbs_3dm_properties.cpp  
                          opennurbs_3dm_settings.cpp  
                          opennurbs_annotation.cpp  
                          opennurbs_annotation2.cpp  
                          opennurbs_arc.cpp  
                          opennurbs_arccurve.cpp  
                          opennurbs_archive.cpp  
                          opennurbs_array.cpp  
                          opennurbs_base32.cpp  
                          opennurbs_base64.cpp  
                          opennurbs_basic.cpp  
                          opennurbs_beam.cpp  
                          opennurbs_bezier.cpp  
                          opennurbs_beziervolume.cpp  
                          opennurbs_bitmap.cpp  
                          opennurbs_bounding_box.cpp  
                          opennurbs_box.cpp  
                          opennurbs_brep.cpp  
                          opennurbs_brep_extrude.cpp  
                          opennurbs_brep_io.cpp  
                          opennurbs_brep_isvalid.cpp  
                          opennurbs_brep_region.cpp  
                          opennurbs_brep_tools.cpp  
                          opennurbs_brep_v2valid.cpp  
                          opennurbs_circle.cpp  
                          opennurbs_color.cpp  
                          opennurbs_compress.cpp
                          opennurbs_cone.cpp  
                          opennurbs_crc.cpp  
                          opennurbs_curve.cpp  
                          opennurbs_curveonsurface.cpp  
                          opennurbs_curveproxy.cpp  
                          opennurbs_cylinder.cpp  
                          opennurbs_defines.cpp  
                          opennurbs_detail.cpp  
                          opennurbs_dimstyle.cpp  
                          opennurbs_ellipse.cpp  
                          opennurbs_embedded_file.cpp   
                          opennurbs_error.cpp  
                          opennurbs_error_message.cpp  
                          opennurbs_evaluate_nurbs.cpp  
                          opennurbs_extensions.cpp  
                          opennurbs_font.cpp  
                          opennurbs_fsp.cpp 
                          opennurbs_geometry.cpp  
                          opennurbs_gl.cpp  
                          opennurbs_group.cpp  
                          opennurbs_hatch.cpp  
                          opennurbs_instance.cpp  
                          opennurbs_intersect.cpp  
                          opennurbs_knot.cpp  
                          opennurbs_layer.cpp  
                          opennurbs_light.cpp  
                          opennurbs_line.cpp  
                          opennurbs_linecurve.cpp  
                          opennurbs_linetype.cpp  
                          opennurbs_lookup.cpp  
                          opennurbs_massprop.cpp  
                          opennurbs_material.cpp  
                          opennurbs_math.cpp  
                          opennurbs_matrix.cpp  
                          opennurbs_memory.c  
                          opennurbs_memory_util.c  
                          opennurbs_mesh.cpp  
                          opennurbs_mesh_ngon.cpp  
                          opennurbs_mesh_tools.cpp  
                          opennurbs_morph.cpp  
                          opennurbs_nurbscurve.cpp  
                          opennurbs_nurbssurface.cpp  
                          opennurbs_nurbsvolume.cpp  
                          opennurbs_object.cpp  
                          opennurbs_object_history.cpp  
                          opennurbs_objref.cpp  
                          opennurbs_offsetsurface.cpp  
                          opennurbs_optimize.cpp  
                          opennurbs_plane.cpp  
                          opennurbs_planesurface.cpp  
                          opennurbs_pluginlist.cpp  
                          opennurbs_point.cpp  
                          opennurbs_pointcloud.cpp  
                          opennurbs_pointgeometry.cpp  
                          opennurbs_pointgrid.cpp  
                          opennurbs_polycurve.cpp  
                          opennurbs_polyedgecurve.cpp  
                          opennurbs_polyline.cpp  
                          opennurbs_polylinecurve.cpp  
                          opennurbs_quaternion.cpp  
                          opennurbs_rand.cpp  
                          opennurbs_revsurface.cpp  
                          opennurbs_rtree.cpp  
                          opennurbs_sort.cpp
                          opennurbs_sphere.cpp  
                          opennurbs_string.cpp  
                          opennurbs_sum.cpp  
                          opennurbs_sumsurface.cpp  
                          opennurbs_surface.cpp  
                          opennurbs_surfaceproxy.cpp  
                          opennurbs_textlog.cpp  
                          opennurbs_torus.cpp  
                          opennurbs_unicode.cpp
                          opennurbs_userdata.cpp  
                          opennurbs_uuid.cpp  
                          opennurbs_viewport.cpp  
                          opennurbs_workspace.cpp  
                          opennurbs_wstring.cpp  
                          opennurbs_xform.cpp 
                          opennurbs_zlib.cpp 
                          opennurbs_zlib_memory.cpp)

  SET(OSG_OPENNURBS_LHDR opennurbs.h  
                         opennurbs_3dm.h  
                         opennurbs_3dm_attributes.h  
                         opennurbs_3dm_properties.h  
                         opennurbs_3dm_settings.h  
                         opennurbs_annotation.h  
                         opennurbs_annotation2.h  
                         opennurbs_arc.h  
                         opennurbs_arccurve.h  
                         opennurbs_archive.h  
                         opennurbs_base32.h  
                         opennurbs_base64.h  
                         opennurbs_beam.h  
                         opennurbs_bezier.h  
                         opennurbs_bitmap.h  
                         opennurbs_bounding_box.h  
                         opennurbs_box.h  
                         opennurbs_brep.h  
                         opennurbs_circle.h  
                         opennurbs_color.h 
                         opennurbs_compress.h
                         opennurbs_cone.h  
                         opennurbs_crc.h  
                         opennurbs_curve.h  
                         opennurbs_curveonsurface.h  
                         opennurbs_curveproxy.h  
                         opennurbs_cylinder.h  
                         opennurbs_defines.h  
                         opennurbs_detail.h  
                         opennurbs_dimstyle.h  
                         opennurbs_ellipse.h  
                         opennurbs_error.h  
                         opennurbs_evaluate_nurbs.h  
                         opennurbs_extensions.h  
                         opennurbs_font.h  
                         opennurbs_fpoint.h
                         opennurbs_fsp_defs.h
                         opennurbs_fsp.h
                         opennurbs_geometry.h  
                         opennurbs_gl.h  
                         opennurbs_group.h  
                         opennurbs_hatch.h  
                         opennurbs_hsort_template.h
                         opennurbs_instance.h  
                         opennurbs_intersect.h  
                         opennurbs_knot.h  
                         opennurbs_layer.h  
                         opennurbs_light.h  
                         opennurbs_line.h  
                         opennurbs_linecurve.h  
                         opennurbs_linestyle.h  
                         opennurbs_linetype.h  
                         opennurbs_lookup.h  
                         opennurbs_mapchan.h  
                         opennurbs_massprop.h  
                         opennurbs_material.h  
                         opennurbs_math.h  
                         opennurbs_matrix.h  
                         opennurbs_memory.h  
                         opennurbs_mesh.h  
                         opennurbs_nurbscurve.h  
                         opennurbs_nurbssurface.h  
                         opennurbs_object.h  
                         opennurbs_object_history.h  
                         opennurbs_objref.h  
                         opennurbs_offsetsurface.h  
                         opennurbs_optimize.h  
                         opennurbs_plane.h  
                         opennurbs_planesurface.h  
                         opennurbs_pluginlist.h  
                         opennurbs_point.h  
                         opennurbs_pointcloud.h  
                         opennurbs_pointgeometry.h  
                         opennurbs_pointgrid.h  
                         opennurbs_polycurve.h  
                         opennurbs_polyedgecurve.h  
                         opennurbs_polyline.h  
                         opennurbs_polylinecurve.h  
                         opennurbs_qsort_template.h
                         opennurbs_quaternion.h  
                         opennurbs_rand.h  
                         opennurbs_rendering.h  
                         opennurbs_revsurface.h  
                         opennurbs_rtree.h  
                         opennurbs_sphere.h  
                         opennurbs_string.h  
                         opennurbs_sumsurface.h  
                         opennurbs_surface.h  
                         opennurbs_surfaceproxy.h  
                         opennurbs_system.h  
                         opennurbs_textlog.h  
                         opennurbs_texture.h  
                         opennurbs_texture_mapping.h  
                         opennurbs_torus.h  
                         opennurbs_unicode.h
                         opennurbs_userdata.h  
                         opennurbs_uuid.h  
                         opennurbs_viewport.h  
                         opennurbs_workspace.h  
                         opennurbs_xform.h  
                         opennurbs_zlib.h)

  SET(OSG_OPENNURBS_HDR_PATCH opennurbs_array_defs.h
                              opennurbs_array.h  
                              opennurbs_system.h  
                              opennurbs_version.h   )

  SET(OSG_OPENNURBS_ZLIB_LSRCS adler32.c 
		                       compress.c 
		                       crc32.c 
		                       deflate.c 
		                       infback.c 
		                       inffast.c 
		                       inflate.c 
		                       inftrees.c 
		                       trees.c 
		                       uncompr.c 
		                       zutil.c)

  SET(OSG_OPENNURBS_ZLIB_LHDR crc32.h
		                      deflate.h
		                      inffast.h
		                      inffixed.h
		                      inflate.h 
		                      inftrees.h
		                      trees.h 
		                      zconf.h 
		                      zlib.h 
		                      zutil.h)

  SET(OSG_OPENNURBS_PATCHES 01_array_defs.patch
                            02_version.patch 
                            03_system.patch
                            04_array.patch    )

  SET(OSGOPENNURBS_DEF  MY_ZCALLOC;Z_PREFIX)

  IF(WIN32)
    SET(OSGOPENNURBS_DEF  ${OSGOPENNURBS_DEF};UNICODE;_UNICODE)
  ELSE(WIN32)
    SET(OSGOPENNURBS_DEF  ${OSGOPENNURBS_DEF};_GNU_SOURCE)
  ENDIF(WIN32)


  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${OSGOpenNurbsSrcDir}/patched")
  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/External/opennurbs/")
  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/External/opennurbs/zlib/")

  FOREACH(_ON_PATCHED_HDR ${OSG_OPENNURBS_HDR_PATCH})
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy "${OSGOpenNurbsSrcDir}/${_ON_PATCHED_HDR}" "${OSGOpenNurbsSrcDir}/patched/")
  ENDFOREACH()

  FOREACH(_ON_PATCH ${OSG_OPENNURBS_PATCHES})
    EXECUTE_PROCESS(COMMAND "patch" "-p1" 
                    INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${_ON_PATCH}"
                    WORKING_DIRECTORY "${OSGOpenNurbsSrcDir}/patched")
  ENDFOREACH()

  PROCESS_FILES(. "OSG_OPENNURBS_SRCS" OSG_OPENNURBS_LSRCS)
  PROCESS_FILES(. "OSG_OPENNURBS_HDR"  OSG_OPENNURBS_LHDR)

  PROCESS_FILES(zlib "OSG_OPENNURBS_ZLIB_SRCS" OSG_OPENNURBS_ZLIB_LSRCS)
  PROCESS_FILES(zlib "OSG_OPENNURBS_ZLIB_HDR"  OSG_OPENNURBS_ZLIB_LHDR)

  FOREACH(_ON_PATCHED_HDR ${OSG_OPENNURBS_HDR_PATCH})
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OSGOpenNurbsSrcDir}/patched/${_ON_PATCHED_HDR}"
                                   "${CMAKE_BINARY_DIR}/External/opennurbs/")
    LIST(APPEND OSG_OPENNURBS_HDR "${CMAKE_BINARY_DIR}/External/opennurbs/${_ON_PATCHED_HDR}")
  ENDFOREACH()

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
                  CONFIGURATIONS Release
                  RUNTIME DESTINATION lib COMPONENT release_libraries
                  LIBRARY DESTINATION lib COMPONENT release_libraries
                  ARCHIVE DESTINATION lib COMPONENT release_libraries)

      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                  CONFIGURATIONS Debug
                  RUNTIME DESTINATION lib COMPONENT debug_libraries
                  LIBRARY DESTINATION lib COMPONENT debug_libraries
                  ARCHIVE DESTINATION lib COMPONENT debug_libraries)
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
