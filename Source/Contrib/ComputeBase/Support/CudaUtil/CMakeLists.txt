
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(OSGContribComputeBase.SetupHelper)

SET(OSG_CUDA_UTIL_BUILD FALSE CACHE INTERNAL "" FORCE)

MESSAGE(STATUS "add CudaUtil")

IF(OSGNVidiaSDKSrcDir)

  PROJECT(OSGCudaUtil)

  SET(${PROJECT_NAME}SharedTarget    osgcudautil)
  SET(${PROJECT_NAME}EmuSharedTarget osgcudautilE)

  IF(NOT WIN32)
    SET(OSG_CUDAUTIL_PLT_SRC_INPUT stopwatch_linux.cpp)
  ELSE()
    SET(OSG_CUDAUTIL_PLT_SRC_INPUT stopwatch_win.cpp)
  ENDIF()

  SET(OSG_CUDAUTIL_SRC_INPUT cutil.cpp
                             bank_checker.cpp
                             stopwatch.cpp
                             ${OSG_CUDAUTIL_PLT_SRC_INPUT})

  IF(NOT WIN32)
    SET(OSG_CUDAUTIL_PLT_HDR_INPUT stopwatch_linux.h)
  ELSE()
    SET(OSG_CUDAUTIL_PLT_HDR_INPUT stopwatch_win.h)
  ENDIF()

  SET(OSG_CUDAUTIL_HDR_INPUT cutil.h
                             cutil_inline.h
                             cutil_math.h
                             cutil_inline_bankchecker.h
                             cutil_inline_runtime.h
                             cutil_inline_drvapi.h
                             cutil_gl_inline.h
                             cutil_gl_error.h
                             error_checker.h
                             stopwatch.h
                             bank_checker.h
                             stopwatch_base.h
                             stopwatch_base.inl
                             ${OSG_CUDAUTIL_PLT_HDR_INPUT})

  SetupFiles(OSG_CUDAUTIL_SRC_INPUT 
             OSG_CUDAUTIL_SRCS 
             "${OSGNVidiaSDKSrcDir}/C/common/src"
             "${OSG_SUPP_CC_BBASE}/CudaUtil/src")

  SetupFiles(OSG_CUDAUTIL_HDR_INPUT 
             OSG_CUDAUTIL_HDR 
             "${OSGNVidiaSDKSrcDir}/C/common/inc"
             "${OSG_SUPP_CC_BBASE}/CudaUtil/src")

  IF(NOT WIN32)
    IF(NOT EXISTS ${_OSGSUPP_DST_DIR}/GL/glew.h)
      FILE(MAKE_DIRECTORY ${_OSGSUPP_DST_DIR}/GL)
      FILE(WRITE ${_OSGSUPP_DST_DIR}/GL/glew.h "/* dummy on unix */\n"
                                               "#include <GL/gl.h>\n")
    ENDIF(NOT EXISTS ${_OSGSUPP_DST_DIR}/GL/glew.h)
  ENDIF(NOT WIN32)

  INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/CudaUtil/src")
  INCLUDE_DIRECTORIES("${CUDA_TOOLKIT_INCLUDE}")
  INCLUDE_DIRECTORIES("${OSG_NVSDK_COMMON_INCLUDEDIR}")

  IF(UNIX)
    SET(OSGCUDACOMLIB_DEF GL_GLEXT_PROTOTYPES=1)
  ENDIF(UNIX)


  ## device lib

  ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_CUDAUTIL_SRCS})

  ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

  IF(WIN32)
    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEBUG_POSTFIX "D")
  ENDIF(WIN32)

  SET(OSGCUDACOMLIB_DEF_SHARED ${OSGCUDACOMLIB_DEF};BUILD_DLL)
                          
  SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                        COMPILE_DEFINITIONS "${OSGCUDACOMLIB_DEF_SHARED}")

  TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_gl_LIBRARY})
  TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OPENGL_glu_LIBRARY})
  TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OSG_NVSDK_COMMON_LIBRARY})
    
  IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${GLUT_glut_LIBRARY})
  ELSE()
#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OSG_GLUT_SHARED_LIBRARY})
  ENDIF()

  IF(WIN32)
#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} ${OSG_GLEW_SHARED_LIBRARY})
  ENDIF()

  ## emu lib

  ADD_LIBRARY(${${PROJECT_NAME}EmuSharedTarget} SHARED ${OSG_CUDAUTIL_SRCS})

  ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}EmuSharedTarget})

  IF(WIN32)
    SET_TARGET_PROPERTIES(${${PROJECT_NAME}EmuSharedTarget} PROPERTIES
                          DEBUG_POSTFIX "D")
  ENDIF(WIN32)

  SET(OSGCUDACOMEMULIB_DEF_SHARED ${OSGCUDACOMLIB_DEF};BUILD_DLL;__DEVICE_EMULATION__)
                          
  SET_TARGET_PROPERTIES(${${PROJECT_NAME}EmuSharedTarget} PROPERTIES
                        COMPILE_DEFINITIONS "${OSGCUDACOMEMULIB_DEF_SHARED}")

  TARGET_LINK_LIBRARIES(${${PROJECT_NAME}EmuSharedTarget} ${OPENGL_gl_LIBRARY})
  TARGET_LINK_LIBRARIES(${${PROJECT_NAME}EmuSharedTarget} ${OPENGL_glu_LIBRARY})
  TARGET_LINK_LIBRARIES(${${PROJECT_NAME}EmuSharedTarget} ${OSG_NVSDK_COMMON_LIBRARY})
    
  IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}EmuSharedTarget} ${GLUT_glut_LIBRARY})
  ELSE()
#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}EmuSharedTarget} ${OSG_GLUT_SHARED_LIBRARY})
  ENDIF()

  IF(WIN32)
#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}EmuSharedTarget} ${OSG_GLEW_SHARED_LIBRARY})
  ENDIF()


  IF(WIN32)
    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                    CONFIGURATIONS ${_OSG_INSTALL_CONFIGS}
                    RUNTIME DESTINATION bin
                    LIBRARY DESTINATION lib
                    ARCHIVE DESTINATION lib)

    INSTALL(TARGETS ${${PROJECT_NAME}EmuSharedTarget}
                    CONFIGURATIONS ${_OSG_INSTALL_CONFIGS}
                    RUNTIME DESTINATION bin
                    LIBRARY DESTINATION lib
                    ARCHIVE DESTINATION lib)
  ELSE(WIN32)
    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                    RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                    LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                    ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})

    INSTALL(TARGETS ${${PROJECT_NAME}EmuSharedTarget}
                    RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                    LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                    ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
  ENDIF(WIN32)


  INSTALL(FILES ${OSG_CUDAUTIL_HDR} 
          DESTINATION include/cuda
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  IF(NOT WIN32)
    INSTALL(FILES ${_OSGSUPP_DST_DIR}/GL/glew.h
            DESTINATION include/cuda/GL
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ)
  ENDIF(NOT WIN32)

  SET(OSG_CUDA_UTIL_BUILD TRUE CACHE INTERNAL "" FORCE)
  SET(OSG_CUDA_UTIL_INCLUDEDIR "${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/CudaUtil/src" CACHE PATH "")

ELSE(OSGNVidiaSDKSrcDir)
  SET(OSGNVidiaSDKSrcDir "" CACHE PATH "")
ENDIF(OSGNVidiaSDKSrcDir)
