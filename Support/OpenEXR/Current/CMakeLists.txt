CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(OSGIlmBaseSrcDir)

  PROJECT(OSGOpenExr)

  SET(${PROJECT_NAME}SharedTargetHalf osgHalf)
  SET(${PROJECT_NAME}StaticTargetHalf libosgHalf)

  SET(${PROJECT_NAME}SharedTargetIex osgIex)
  SET(${PROJECT_NAME}StaticTargetIex libosgIex)

  SET(${PROJECT_NAME}SharedTargetIlmThread osgilmthread)
  SET(${PROJECT_NAME}StaticTargetIlmThread libosgilmthread)

  SET(${PROJECT_NAME}SharedTargetIlmImf osgilmimf)
  SET(${PROJECT_NAME}StaticTargetIlmImf libosgilmimf)

  SET(OSG_OEXR_HALF_SRCS ${OSGIlmBaseSrcDir}/Half/half.cpp)

  SET(OSG_OEXR_IEX_SRCS ${OSGIlmBaseSrcDir}/Iex/IexBaseExc.cpp
                        ${OSGIlmBaseSrcDir}/Iex/IexThrowErrnoExc.cpp)

  SET(OSG_OEXR_ITR_SRCS ${OSGIlmBaseSrcDir}/IlmThread/IlmThread.cpp
                        ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadMutex.cpp
                        ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadMutexWin32.cpp
                        ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadPool.cpp
                        ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadSemaphore.cpp
                        ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadSemaphoreWin32.cpp
                        ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadWin32.cpp)

  SET(OSG_OEXR_IMF_SRCS ${OSGOpenExrSrcDir}/IlmImf/b44ExpLogTable.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfAcesFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfB44Compressor.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfBoxAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfChannelList.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfChannelListAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfChromaticities.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfChromaticitiesAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfCompressionAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfCompressor.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfConvert.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfCRgbaFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfDoubleAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfEnvmap.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfEnvmapAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfFloatAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfFrameBuffer.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfFramesPerSecond.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfHeader.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfHuf.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfInputFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfIntAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfIO.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfKeyCode.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfKeyCodeAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfLineOrderAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfLut.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfMatrixAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfMisc.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfMultiView.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfOpaqueAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfOutputFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfPizCompressor.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfPreviewImage.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfPreviewImageAttribute.cpp
                        ${CMAKE_BINARY_DIR}/OpenEXR/ImfPxr24Compressor.cpp
#                        ${OSGOpenExrSrcDir}/IlmImf/ImfPxr24Compressor.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfRational.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfRationalAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfRgbaFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfRgbaYca.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfRleCompressor.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfScanLineInputFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfStandardAttributes.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfStdIO.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfStringAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfStringVectorAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTestFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfThreading.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTileDescriptionAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTiledInputFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTiledMisc.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTiledOutputFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTiledRgbaFile.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTileOffsets.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTimeCode.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfTimeCodeAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfVecAttribute.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfVersion.cpp
                        ${OSGOpenExrSrcDir}/IlmImf/ImfWav.cpp
                        ${CMAKE_BINARY_DIR}/OpenEXR/ImfZipCompressor.cpp)
#                        ${OSGOpenExrSrcDir}/IlmImf/ImfZipCompressor.cpp)


  SET(OSG_OEXR_HALF_HDR ${OSGIlmBaseSrcDir}/Half/half.h
                        ${OSGIlmBaseSrcDir}/Half/halfFunction.h
                        ${OSGIlmBaseSrcDir}/Half/halfLimits.h)

  SET(OSG_OEXR_IEX_HDR ${OSGIlmBaseSrcDir}/Iex/Iex.h
                       ${OSGIlmBaseSrcDir}/Iex/IexBaseExc.h
                       ${OSGIlmBaseSrcDir}/Iex/IexErrnoExc.h
                       ${OSGIlmBaseSrcDir}/Iex/IexMacros.h
                       ${OSGIlmBaseSrcDir}/Iex/IexMathExc.h
                       ${OSGIlmBaseSrcDir}/Iex/IexThrowErrnoExc.h
                       ${OSGIlmBaseSrcDir}/config/IlmBaseConfig.h)

  SET(OSG_OEXR_ITR_HDR ${OSGIlmBaseSrcDir}/IlmThread/IlmThread.h
                       ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadMutex.h
                       ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadPool.h
                       ${OSGIlmBaseSrcDir}/IlmThread/IlmThreadSemaphore.h)

  SET(OSG_OEXR_IMF_HDR ${OSGOpenExrSrcDir}/IlmImf/ImfAcesFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfArray.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfAutoArray.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfB44Compressor.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfBoxAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfCRgbaFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfChannelList.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfChannelListAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfChromaticities.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfChromaticitiesAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfCompression.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfCompressionAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfCompressor.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfConvert.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfDoubleAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfEnvmap.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfEnvmapAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfFloatAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfFrameBuffer.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfFramesPerSecond.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfHeader.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfHuf.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfIO.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfInputFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfInt64.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfIntAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfKeyCode.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfKeyCodeAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfLineOrder.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfLineOrderAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfLut.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfMatrixAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfMisc.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfMultiView.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfName.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfOpaqueAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfOutputFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfPixelType.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfPizCompressor.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfPreviewImage.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfPreviewImageAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfPxr24Compressor.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfRational.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfRationalAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfRgba.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfRgbaFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfRgbaYca.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfRleCompressor.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfScanLineInputFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfStandardAttributes.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfStdIO.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfStringAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfStringVectorAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTestFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfThreading.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTileDescription.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTileDescriptionAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTileOffsets.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTiledInputFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTiledMisc.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTiledOutputFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTiledRgbaFile.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTimeCode.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfTimeCodeAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfVecAttribute.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfVersion.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfWav.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfXdr.h
                       ${OSGOpenExrSrcDir}/IlmImf/ImfZipCompressor.h
                       ${OSGOpenExrSrcDir}/IlmImf/b44ExpLogTable.h
                       ${OSGOpenExrSrcDir}/IlmImf/imfattribute.h)

  SET(OSG_OEXR_MATH_HDR ${OSGIlmBaseSrcDir}/Imath/ImathBox.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathExc.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathFun.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathInt64.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathLimits.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathMath.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathMatrix.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathShear.h
                        ${OSGIlmBaseSrcDir}/Imath/ImathVec.h
                        ${OSGIlmBaseSrcDir}/Imath/imathplatform.h)

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${CMAKE_CURRENT_SOURCE_DIR}/toFloat.h"
                     "${CMAKE_BINARY_DIR}/OpenEXR/include/toFloat.h")

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${CMAKE_CURRENT_SOURCE_DIR}/elut.h"
                     "${CMAKE_BINARY_DIR}/OpenEXR/include/elut.h")



  FILE(READ "${OSGOpenExrSrcDir}/IlmImf/ImfZipCompressor.cpp" _OEXRCPR_FILE_IN)
          
  string(REPLACE "#define ZLIB_WINAPI"
                 "//#define ZLIB_WINAPI" _OEXRCPR_FILE_IN_P1 "${_OEXRCPR_FILE_IN}")
    
  FILE(WRITE "${CMAKE_BINARY_DIR}/OpenEXR/ImfZipCompressor.cpp.proc" "${_OEXRCPR_FILE_IN_P1}")

  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_BINARY_DIR}/OpenEXR/ImfZipCompressor.cpp.proc" "${CMAKE_BINARY_DIR}/OpenEXR/ImfZipCompressor.cpp")



  FILE(READ "${OSGOpenExrSrcDir}/IlmImf/ImfPxr24Compressor.cpp" _OEXRCPR_FILE_IN)
          
  string(REPLACE "#define ZLIB_WINAPI"
                 "//#define ZLIB_WINAPI" _OEXRCPR_FILE_IN_P1 "${_OEXRCPR_FILE_IN}")
    
  FILE(WRITE "${CMAKE_BINARY_DIR}/OpenEXR/ImfPxr24Compressor.cpp.proc" "${_OEXRCPR_FILE_IN_P1}")

  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_BINARY_DIR}/OpenEXR/ImfPxr24Compressor.cpp.proc" "${CMAKE_BINARY_DIR}/OpenEXR/ImfPxr24Compressor.cpp")


  INCLUDE_DIRECTORIES(${OSGIlmBaseSrcDir}/config)
  INCLUDE_DIRECTORIES(${OSGOpenExrSrcDir}/config)
  INcLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/OpenEXR/include)

  IF(BUILD_STATIC_LIBS)

    # Half

    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetHalf} STATIC 
                ${OSG_OEXR_HALF_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetHalf})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetHalf} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetHalf}
                CONFIGURATIONS Release
                RUNTIME DESTINATION lib COMPONENT release_libraries
                LIBRARY DESTINATION lib COMPONENT release_libraries
                ARCHIVE DESTINATION lib COMPONENT release_libraries)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetHalf}
                CONFIGURATIONS Debug
                RUNTIME DESTINATION lib COMPONENT debug_libraries
                LIBRARY DESTINATION lib COMPONENT debug_libraries
                ARCHIVE DESTINATION lib COMPONENT debug_libraries)


    # Iex

    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetIex} STATIC 
                ${OSG_OEXR_IEX_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetIex})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetIex} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIex}
                CONFIGURATIONS Release
                RUNTIME DESTINATION lib COMPONENT release_libraries
                LIBRARY DESTINATION lib COMPONENT release_libraries
                ARCHIVE DESTINATION lib COMPONENT release_libraries)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIex}
                CONFIGURATIONS Debug
                RUNTIME DESTINATION lib COMPONENT debug_libraries
                LIBRARY DESTINATION lib COMPONENT debug_libraries
                ARCHIVE DESTINATION lib COMPONENT debug_libraries)


    # IlmThread

    ADD_SUBDIRECTORY(IlmThread)

    # IlmImf

    ADD_SUBDIRECTORY(IlmImf)

  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_OEXR_HALF_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/OpenEXR
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_IEX_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/OpenEXR
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_ITR_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/OpenEXR
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_IMF_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/OpenEXR
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_MATH_HDR}
          DESTINATION include${OSG_SUPPORT_INC_SUBDIR}/OpenEXR
          COMPONENT code_headers
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

ELSE(OSGIlmBaseSrcDir)
    SET(OSGIlmBaseSrcDir "" CACHE PATH "")
ENDIF(OSGIlmBaseSrcDir)

