CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGLibMiniSrcDir)

  PROJECT(OSGLibMini)

  IF(WIN32)
    SET(${PROJECT_NAME}StaticTarget libosgmini)
  ELSE(WIN32)
    SET(${PROJECT_NAME}StaticTarget osgmini)
  ENDIF(WIN32)

  SET(OSG_LIBMINI_SRCS ${OSGLibMiniSrcDir}/mini.cpp 
                       ${OSGLibMiniSrcDir}/miniOGL.cpp
	                   ${OSGLibMiniSrcDir}/miniv3f.cpp 
                       ${OSGLibMiniSrcDir}/miniv3d.cpp 
                       ${OSGLibMiniSrcDir}/miniv4f.cpp 
                       ${OSGLibMiniSrcDir}/miniv4d.cpp
	                   ${OSGLibMiniSrcDir}/minimath.cpp 
                       ${OSGLibMiniSrcDir}/minimpfp.cpp 
                       ${OSGLibMiniSrcDir}/minitime.cpp  
                       ${OSGLibMiniSrcDir}/miniio.cpp 
                       ${OSGLibMiniSrcDir}/minirgb.cpp 
                       ${OSGLibMiniSrcDir}/minicrs.cpp
	                   ${OSGLibMiniSrcDir}/ministub.cpp 
                       ${OSGLibMiniSrcDir}/minitile.cpp 
                       ${OSGLibMiniSrcDir}/miniload.cpp
	                   ${OSGLibMiniSrcDir}/minicoord.cpp 
                       ${OSGLibMiniSrcDir}/miniwarp.cpp
	                   ${OSGLibMiniSrcDir}/minilayer.cpp 
                       ${OSGLibMiniSrcDir}/miniterrain.cpp 
                       ${OSGLibMiniSrcDir}/miniearth.cpp
	                   ${OSGLibMiniSrcDir}/minicache.cpp 
                       ${OSGLibMiniSrcDir}/minishader.cpp
	                   ${OSGLibMiniSrcDir}/miniray.cpp 
                       ${OSGLibMiniSrcDir}/ministrip.cpp
	                   ${OSGLibMiniSrcDir}/minipoint.cpp 
                       ${OSGLibMiniSrcDir}/minitext.cpp 
                       ${OSGLibMiniSrcDir}/minisky.cpp 
                       ${OSGLibMiniSrcDir}/miniglobe.cpp
	                   ${OSGLibMiniSrcDir}/minitree.cpp 
                       ${OSGLibMiniSrcDir}/minibrick.cpp
                       ${OSGLibMiniSrcDir}/minilod.cpp
	                   ${OSGLibMiniSrcDir}/minimesh.cpp 
                       ${OSGLibMiniSrcDir}/minibspt.cpp 
                       ${OSGLibMiniSrcDir}/miniproj.cpp
	                   ${OSGLibMiniSrcDir}/pnmbase.cpp
                       ${OSGLibMiniSrcDir}/pnmsample.cpp
	                   ${OSGLibMiniSrcDir}/database.cpp 
                       ${OSGLibMiniSrcDir}/datafill.cpp
	                   ${OSGLibMiniSrcDir}/datacloud.cpp 
                       ${OSGLibMiniSrcDir}/datacache.cpp 
                       ${OSGLibMiniSrcDir}/datagrid.cpp
	                   ${OSGLibMiniSrcDir}/datacalc.cpp 
                       ${OSGLibMiniSrcDir}/dataparse.cpp
	                   ${OSGLibMiniSrcDir}/lunascan.cpp 
                       ${OSGLibMiniSrcDir}/lunaparse.cpp 
                       ${OSGLibMiniSrcDir}/lunacode.cpp)

  SET(OSG_LIBMINI_HDR ${OSGLibMiniSrcDir}/minibase.h
	                  ${OSGLibMiniSrcDir}/minivec.h 
                      ${OSGLibMiniSrcDir}/minimtx.h
	                  ${OSGLibMiniSrcDir}/minidyna.h 
                      ${OSGLibMiniSrcDir}/minigeom.h 
                      ${OSGLibMiniSrcDir}/minisort.h 
                      ${OSGLibMiniSrcDir}/ministring.h
                      ${OSGLibMiniSrcDir}/mini.h 
#                      ${OSGLibMiniSrcDir}/miniOGL.h
	                  ${OSGLibMiniSrcDir}/miniv3f.h
                      ${OSGLibMiniSrcDir}/miniv3d.h 
                      ${OSGLibMiniSrcDir}/miniv4f.h 
                      ${OSGLibMiniSrcDir}/miniv4d.h
	                  ${OSGLibMiniSrcDir}/minimath.h 
                      ${OSGLibMiniSrcDir}/minimpfp.h 
                      ${OSGLibMiniSrcDir}/minitime.h  
                      ${OSGLibMiniSrcDir}/miniio.h 
                      ${OSGLibMiniSrcDir}/minirgb.h 
                      ${OSGLibMiniSrcDir}/minicrs.h
	                  ${OSGLibMiniSrcDir}/ministub.h 
                      ${OSGLibMiniSrcDir}/minitile.h 
                      ${OSGLibMiniSrcDir}/miniload.h
	                  ${OSGLibMiniSrcDir}/minicoord.h 
                      ${OSGLibMiniSrcDir}/miniwarp.h
	                  ${OSGLibMiniSrcDir}/minilayer.h 
                      ${OSGLibMiniSrcDir}/miniterrain.h 
                      ${OSGLibMiniSrcDir}/miniearth.h
	                  ${OSGLibMiniSrcDir}/minicache.h 
                      ${OSGLibMiniSrcDir}/minishader.h
	                  ${OSGLibMiniSrcDir}/miniray.h 
                      ${OSGLibMiniSrcDir}/ministrip.h
	                  ${OSGLibMiniSrcDir}/minipoint.h 
                      ${OSGLibMiniSrcDir}/minitext.h 
                      ${OSGLibMiniSrcDir}/minisky.h 
                      ${OSGLibMiniSrcDir}/miniglobe.h
	                  ${OSGLibMiniSrcDir}/minitree.h 
                      ${OSGLibMiniSrcDir}/minibrick.h 
                      ${OSGLibMiniSrcDir}/minilod.h
	                  ${OSGLibMiniSrcDir}/minimesh.h 
                      ${OSGLibMiniSrcDir}/minibspt.h 
                      ${OSGLibMiniSrcDir}/miniproj.h
	                  ${OSGLibMiniSrcDir}/pnmbase.h 
                      ${OSGLibMiniSrcDir}/pnmsample.h
	                  ${OSGLibMiniSrcDir}/database.h 
                      ${OSGLibMiniSrcDir}/datafill.h
	                  ${OSGLibMiniSrcDir}/datacloud.h 
                      ${OSGLibMiniSrcDir}/datacache.h 
                      ${OSGLibMiniSrcDir}/datagrid.h
	                  ${OSGLibMiniSrcDir}/datacalc.h 
                      ${OSGLibMiniSrcDir}/dataparse.h
	                  ${OSGLibMiniSrcDir}/lunascan.h 
                      ${OSGLibMiniSrcDir}/lunaparse.h 
                      ${OSGLibMiniSrcDir}/lunacode.h)

  SET(OSGLIBMINI_DEF )

  INCLUDE_DIRECTORIES(${OSGLibMiniSrcDir})
  INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/External/mini)

  IF(EXISTS ${OSGLibMiniSrcDir}/GL)
    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_directory "${OSGLibMiniSrcDir}/GL" "${OSGLibMiniSrcDir}/GL.org")
    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E remove_directory "${OSGLibMiniSrcDir}/GL")
  ENDIF()

  IF(WIN32)
    IF(EXISTS "${OSGLibMiniSrcDir}/miniOGL.h")
      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E rename "${OSGLibMiniSrcDir}/miniOGL.h" "${OSGLibMiniSrcDir}/miniOGL.h.in")
    ENDIF()

    FILE(READ "${OSGLibMiniSrcDir}/miniOGL.h.in" _MINIOGL_FILE_IN)

    string(REPLACE "#include <GL/glext.h>"
                   "#include \"miniGLext.h\"" _MINIOGL_FILE_IN_P1 "${_MINIOGL_FILE_IN}")

    FILE(WRITE "${CMAKE_BINARY_DIR}/External/mini/miniOGL.h.proc" "${_MINIOGL_FILE_IN_P1}")

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_BINARY_DIR}/External/mini/miniOGL.h.proc" "${CMAKE_BINARY_DIR}/External/mini/miniOGL.h")

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OSGLibMiniSrcDir}/GL.org/glext.h" "${CMAKE_BINARY_DIR}/External/mini/miniGLext.h")

    SET(OSG_LIBMINI_HDR ${OSG_LIBMINI_HDR} ${CMAKE_BINARY_DIR}/External/mini/miniOGL.h)
    SET(OSG_LIBMINI_HDR ${OSG_LIBMINI_HDR} ${CMAKE_BINARY_DIR}/External/mini/miniGLext.h)
  ELSE(WIN32)
    SET(OSG_LIBMINI_HDR ${OSG_LIBMINI_HDR} ${OSGLibMiniSrcDir}/miniOGL.h)
  ENDIF(WIN32)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_LIBMINI_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                            DEBUG_POSTFIX "D")
    ENDIF(WIN32)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGLIBMINI_DEF}")


    IF(WIN32)    
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
              CONFIGURATIONS Release Debug
              RUNTIME DESTINATION bin
              LIBRARY DESTINATION lib
              ARCHIVE DESTINATION lib)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
    ENDIF(WIN32)
  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_LIBMINI_HDR}
          DESTINATION include/mini
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

ELSE(OSGLibMiniSrcDir)
  SET(OSGLibMiniSrcDir "" CACHE PATH "")
ENDIF(OSGLibMiniSrcDir)
