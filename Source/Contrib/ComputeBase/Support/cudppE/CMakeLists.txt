
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(OSGContribComputeBase.SetupHelper)

IF(OSGNVidiaCudPPSrcDir)

  IF(NOT OSG_CUDA_UTIL_BUILD)
    MESSAGE(STATUS "cudcppE needs CudaUtil")
    RETURN()
  ENDIF(NOT OSG_CUDA_UTIL_BUILD)

  MESSAGE(STATUS "add cudppE")


  PROJECT(OSGCudPPE)

  SET(${PROJECT_NAME}SharedTarget osgcudppE)

  IF(WIN32)
    SET(${PROJECT_NAME}StaticTarget libosgcudppE)
  ELSE(WIN32)
    SET(${PROJECT_NAME}StaticTarget osgcudpplibE)
  ENDIF(WIN32)

  SET(${PROJECT_NAME}_EXTRA_DEF __DEVICE_EMULATION__)

  INCLUDE(../cudpp/CudPPCommon.cmake)

ELSE(OSGNVidiaCudPPSrcDir)
  SET(OSGNVidiaCudPPSrcDir "" CACHE PATH "")
ENDIF(OSGNVidiaCudPPSrcDir)
