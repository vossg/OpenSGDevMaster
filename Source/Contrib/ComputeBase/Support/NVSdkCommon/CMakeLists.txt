
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(OSGContribComputeBase.SetupHelper)

SET(OSG_NVSDK_COMMON_BUILD FALSE CACHE INTERNAL "" FORCE)

MESSAGE(STATUS "add NVSdkCommon")

IF(OSGNVidiaSDKSrcDir)

  PROJECT(OSGNVSdkCommon)

  IF(WIN32)
    SET(${PROJECT_NAME}StaticTarget libosgnvsdkcommon)
  ELSE(WIN32)
    SET(${PROJECT_NAME}StaticTarget osgnvsdkcommon)
  ENDIF(WIN32)

  IF(EXISTS ${OSGNVidiaSDKSrcDir}/shared)
    MESSAGE(STATUS "With OpenCL SDK")

    SET(OSG_NVSDKCOMMON_SRC_INPUT rendercheckGL.cpp
                                  cmd_arg_reader.cpp
                                  shrUtils.cpp)
    SET(OSG_NVSDKCOMMON_HDR_INPUT rendercheckGL.h
                                  exception.h
                                  cmd_arg_reader.h
                                  shrUtils.h
                                  nvShaderUtils.h)

    SET(OSG_NVSDKCOMMON_LNK_HDR ${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/NVSdkCommon/src/rendercheck_gl.h)

    SET(OSG_NVSDKCOMMON_SUBDIR shared)

    CopyOrLink(${OSGNVidiaSDKSrcDir}/${OSG_NVSDKCOMMON_SUBDIR}/inc/rendercheckGL.h
               ${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/NVSdkCommon/src/rendercheck_gl.h)
  ELSE()
    MESSAGE(STATUS "Without OpenCL SDK")

    SET(OSG_NVSDKCOMMON_SRC_INPUT rendercheck_gl.cpp
                                  cmd_arg_reader.cpp)

    SET(OSG_NVSDKCOMMON_HDR_INPUT rendercheck_gl.h
                                  exception.h
                                  cmd_arg_reader.h
                                  nvShaderUtils.h)

    SET(OSG_NVSDKCOMMON_LNK_HDR ${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/NVSdkCommon/src/rendercheckGL.h)

    SET(OSG_NVSDKCOMMON_SUBDIR C/common)

    CopyOrLink(${OSGNVidiaSDKSrcDir}/${OSG_NVSDKCOMMON_SUBDIR}/inc/rendercheck_gl.h
               ${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/NVSdkCommon/src/rendercheckGL.h)
  ENDIF()


  SetupFiles(OSG_NVSDKCOMMON_SRC_INPUT 
             OSG_NVSDKCOMMON_SRCS 
             "${OSGNVidiaSDKSrcDir}/${OSG_NVSDKCOMMON_SUBDIR}/src"
             "${OSG_SUPP_CC_BBASE}/NVSdkCommon/src")

  SetupFiles(OSG_NVSDKCOMMON_HDR_INPUT 
             OSG_NVSDKCOMMON_HDR 
             "${OSGNVidiaSDKSrcDir}/${OSG_NVSDKCOMMON_SUBDIR}/inc"
             "${OSG_SUPP_CC_BBASE}/NVSdkCommon/src")

  LIST(APPEND OSG_NVSDKCOMMON_HDR "${OSG_NVSDKCOMMON_LNK_HDR}")

  IF(NOT WIN32)
    IF(NOT EXISTS ${_OSGSUPP_DST_DIR}/GL/glew.h)
      FILE(MAKE_DIRECTORY ${_OSGSUPP_DST_DIR}/GL)
      FILE(WRITE ${_OSGSUPP_DST_DIR}/GL/glew.h "/* dummy on unix */\n")
    ENDIF(NOT EXISTS ${_OSGSUPP_DST_DIR}/GL/glew.h)
  ENDIF(NOT WIN32)

  INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/NVSdkCommon/src")
#  INCLUDE_DIRECTORIES("${CUDA_TOOLKIT_INCLUDE}")
#  INCLUDE_DIRECTORIES("${OSG_CUDA_UTIL_INCLUDEDIR}")

  IF(WIN32)
    INCLUDE_DIRECTORIES("${OSG_GLUT_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES("${OSG_GLEW_INCLUDE_DIR}")
  ENDIF(WIN32)

  IF(UNIX)
    SET(OSGNVSDKCOMLIB_DEF GL_GLEXT_PROTOTYPES=1)
  ENDIF(UNIX)


  ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_NVSDKCOMMON_SRCS})

  ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

  IF(WIN32)
    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")
  ENDIF(WIN32)

  SET(OSGNVSDKCOMLIB_DEF_STATIC ${OSGNVSDKCOMLIB_DEF})

  SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                        COMPILE_DEFINITIONS "${OSGNVSDKCOMLIB_DEF_STATIC}")


  IF(WIN32)
    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS ${_OSG_INSTALL_CONFIGS}
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ELSE(WIN32)
    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
  ENDIF(WIN32)


  INSTALL(FILES ${OSG_NVSDKCOMMON_HDR} 
          DESTINATION include/nvsdk
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  IF(NOT WIN32)
    INSTALL(FILES ${_OSGSUPP_DST_DIR}/GL/glew.h
            DESTINATION include/nvsdk/GL
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ)
  ENDIF(NOT WIN32)

  SET(OSG_NVSDK_COMMON_BUILD TRUE CACHE INTERNAL "" FORCE)
  SET(OSG_NVSDK_COMMON_INCLUDEDIR "${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/NVSdkCommon/src" CACHE PATH "")
  SET(OSG_NVSDK_COMMON_LIBRARY "${${PROJECT_NAME}StaticTarget}" CACHE FILEPATH "")

ELSE(OSGNVidiaSDKSrcDir)
  SET(OSGNVidiaSDKSrcDir "" CACHE PATH "")
ENDIF(OSGNVidiaSDKSrcDir)
