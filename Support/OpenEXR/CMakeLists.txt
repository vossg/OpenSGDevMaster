CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGOpenExrSrcDir AND OSGZLibSrcDir)

  PROJECT(OSGOpenExr)

  SET(${PROJECT_NAME}SharedTargetHalf osgHalf)
  SET(${PROJECT_NAME}StaticTargetHalf libosgHalf)

  SET(${PROJECT_NAME}SharedTargetIex osgIex)
  SET(${PROJECT_NAME}StaticTargetIex libosgIex)

  SET(${PROJECT_NAME}SharedTargetIlmThread osgilmthread)
  SET(${PROJECT_NAME}StaticTargetIlmThread libosgilmthread)

  SET(${PROJECT_NAME}SharedTargetIlmImf osgilmimf)
  SET(${PROJECT_NAME}StaticTargetIlmImf libosgilmimf)

  SET(OSG_OEXR_HALF_SRCS ${OSGOpenExrSrcDir}/IlmBase/Half/half.cpp)

  SET(OSG_OEXR_IEX_SRCS ${OSGOpenExrSrcDir}/IlmBase/Iex/IexBaseExc.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/Iex/IexThrowErrnoExc.cpp)

  SET(OSG_OEXR_ITR_SRCS ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThread.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThreadMutex.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThreadMutexWin32.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThreadPool.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThreadSemaphore.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThreadSemaphoreWin32.cpp
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread/IlmThreadWin32.cpp)

  SET(OSG_OEXR_IMF_SRCS ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/b44ExpLogTable.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfAcesFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfB44Compressor.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfBoxAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfChannelList.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfChannelListAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfChromaticities.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfChromaticitiesAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfCompressionAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfCompressor.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfConvert.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfCRgbaFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfDoubleAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfEnvmap.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfEnvmapAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfFloatAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfFrameBuffer.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfFramesPerSecond.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfHeader.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfHuf.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfInputFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfIntAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfIO.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfKeyCode.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfKeyCodeAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfLineOrderAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfLut.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfMatrixAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfMisc.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfMultiView.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfOpaqueAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfOutputFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfPizCompressor.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfPreviewImage.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfPreviewImageAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfPxr24Compressor.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfRational.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfRationalAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfRgbaFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfRgbaYca.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfRleCompressor.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfScanLineInputFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfStandardAttributes.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfStdIO.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfStringAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfStringVectorAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTestFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfThreading.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTileDescriptionAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTiledInputFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTiledMisc.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTiledOutputFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTiledRgbaFile.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTileOffsets.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTimeCode.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfTimeCodeAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfVecAttribute.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfVersion.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfWav.cpp
                        ${OSGOpenExrSrcDir}/OpenEXR/IlmImf/ImfZipCompressor.cpp)


  SET(OSG_OEXR_HALF_HDR ${OSGOpenExrSrcDir}/Deploy/include/half.h
                        ${OSGOpenExrSrcDir}/Deploy/include/halfFunction.h
                        ${OSGOpenExrSrcDir}/Deploy/include/halfLimits.h)

  SET(OSG_OEXR_IEX_HDR ${OSGOpenExrSrcDir}/Deploy/include/Iex.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IexBaseExc.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IexErrnoExc.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IexMacros.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IexMathExc.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IexThrowErrnoExc.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IlmBaseConfig.h)

  SET(OSG_OEXR_ITR_HDR ${OSGOpenExrSrcDir}/Deploy/include/IlmThread.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IlmThreadMutex.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IlmThreadPool.h
                       ${OSGOpenExrSrcDir}/Deploy/include/IlmThreadSemaphore.h)

  SET(OSG_OEXR_IMF_HDR ${OSGOpenExrSrcDir}/Deploy/include/ImfAcesFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfArray.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfAutoArray.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfB44Compressor.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfBoxAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfCRgbaFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfChannelList.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfChannelListAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfChromaticities.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfChromaticitiesAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfCompression.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfCompressionAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfCompressor.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfConvert.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfDoubleAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfEnvmap.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfEnvmapAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfFloatAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfFrameBuffer.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfFramesPerSecond.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfHeader.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfHuf.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfIO.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfInputFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfInt64.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfIntAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfKeyCode.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfKeyCodeAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfLineOrder.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfLineOrderAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfLut.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfMatrixAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfMisc.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfMultiView.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfName.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfOpaqueAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfOutputFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfPixelType.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfPizCompressor.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfPreviewImage.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfPreviewImageAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfPxr24Compressor.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfRational.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfRationalAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfRgba.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfRgbaFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfRgbaYca.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfRleCompressor.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfScanLineInputFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfStandardAttributes.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfStdIO.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfStringAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfStringVectorAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTestFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfThreading.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTileDescription.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTileDescriptionAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTileOffsets.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTiledInputFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTiledMisc.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTiledOutputFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTiledRgbaFile.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTimeCode.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfTimeCodeAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfVecAttribute.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfVersion.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfWav.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfXdr.h
                       ${OSGOpenExrSrcDir}/Deploy/include/ImfZipCompressor.h
                       ${OSGOpenExrSrcDir}/Deploy/include/b44ExpLogTable.h
                       ${OSGOpenExrSrcDir}/Deploy/include/imfattribute.h)

  SET(OSG_OEXR_MATH_HDR ${OSGOpenExrSrcDir}/Deploy/include/IexMathExc.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathBox.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathExc.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathFun.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathInt64.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathLimits.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathMath.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathMatrix.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathShear.h
                        ${OSGOpenExrSrcDir}/Deploy/include/ImathVec.h
                        ${OSGOpenExrSrcDir}/Deploy/include/imathplatform.h)

  INCLUDE_DIRECTORIES(${OSGOpenExrSrcDir}/IlmBase/config)
  INCLUDE_DIRECTORIES(${OSGOpenExrSrcDir}/OpenEXR/config)

  IF(BUILD_SHARED_LIBS)

    # Half

#    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetHalf} SHARED 
#                ${OSG_OEXR_HALF_SRCS})

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetHalf} PROPERTIES
#                          DEFINE_SYMBOL HALF_EXPORTS   
#                          DEBUG_POSTFIX "D")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetHalf} PROPERTIES
#                          COMPILE_DEFINITIONS "OPENEXR_DLL")

#    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetHalf}
#                CONFIGURATIONS Release Debug
#                RUNTIME DESTINATION bin
#                LIBRARY DESTINATION lib
#                ARCHIVE DESTINATION lib)


    # Iex

#    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetIex} SHARED 
#                ${OSG_OEXR_IEX_SRCS})

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIex} PROPERTIES
#                          DEFINE_SYMBOL IEX_EXPORTS   
#                          DEBUG_POSTFIX "D")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIex} PROPERTIES
#                          COMPILE_DEFINITIONS "OPENEXR_DLL")

#    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetIex}
#                CONFIGURATIONS Release Debug
#                RUNTIME DESTINATION bin
#                LIBRARY DESTINATION lib
#                ARCHIVE DESTINATION lib)


    # IlmThread

#    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetIlmThread} SHARED 
#                ${OSG_OEXR_ITR_SRCS}
#                ${CMAKE_SOURCE_DIR}/OpenEXR/ilmthread.def)

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIlmThread} PROPERTIES
#                          DEFINE_SYMBOL ILMTHREAD_EXPORTS   
#                          DEBUG_POSTFIX "D")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIlmThread} PROPERTIES
#                          COMPILE_DEFINITIONS "OPENEXR_DLL")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIlmThread} PROPERTIES
#                          COMPILE_FLAGS -I${OSGOpenExrSrcDir}/IlmBase/Iex)

#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTargetIlmThread} ${${PROJECT_NAME}StaticTargetIex})

#    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetIlmThread}
#                CONFIGURATIONS Release Debug
#                RUNTIME DESTINATION bin
#                LIBRARY DESTINATION lib
#                ARCHIVE DESTINATION lib)


    # IlmImf

#    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetIlmImf} SHARED 
#                ${OSG_OEXR_IMF_SRCS})

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIlmImf} PROPERTIES
#                          DEFINE_SYMBOL ILMIMF_EXPORTS   
#                          DEBUG_POSTFIX "D")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIlmImf} PROPERTIES
#                          COMPILE_DEFINITIONS "OPENEXR_DLL")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetIlmImf} PROPERTIES
#                          COMPILE_FLAGS "-DOPENEXR_DLL -I${OSGOpenExrSrcDir}/IlmBase/Half -I${OSGOpenExrSrcDir}/IlmBase/Iex -I${OSGOpenExrSrcDir}/IlmBase/Imath -I${OSGOpenExrSrcDir}/IlmBase/IlmThread -I${OSGOpenExrSrcDir}/OpenExr/IlmImf -DZLIB_DLL -I${OSG_ZLIB_INCLUDE_DIR}")

#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTargetIlmImf} ${${PROJECT_NAME}SharedTargetHalf})
#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTargetIlmImf} ${${PROJECT_NAME}SharedTargetIlmThread})
#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTargetIlmImf} osgzlib)

#    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetIlmImf}
#                CONFIGURATIONS Release Debug
#                RUNTIME DESTINATION bin
#                LIBRARY DESTINATION lib
#                ARCHIVE DESTINATION lib)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)

    # Half

    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetHalf} STATIC 
                ${OSG_OEXR_HALF_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetHalf})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetHalf} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetHalf}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)


    # Iex

    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetIex} STATIC 
                ${OSG_OEXR_IEX_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetIex})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetIex} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIex}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)


    # IlmThread

    ADD_SUBDIRECTORY(IlmThread)

    # IlmImf

    ADD_SUBDIRECTORY(IlmImf)

  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_OEXR_HALF_HDR}
          DESTINATION include/OpenEXR
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_IEX_HDR}
          DESTINATION include/OpenEXR
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_ITR_HDR}
          DESTINATION include/OpenEXR
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_IMF_HDR}
          DESTINATION include/OpenEXR
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  INSTALL(FILES ${OSG_OEXR_MATH_HDR}
          DESTINATION include/OpenEXR
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

ELSE(OSGOpenExrSrcDir AND OSGZLibSrcDir)
  SET(OSGOpenExrSrcDir "" CACHE PATH "")
ENDIF(OSGOpenExrSrcDir AND OSGZLibSrcDir)
