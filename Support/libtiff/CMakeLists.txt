CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGTiffLibSrcDir AND OSGZLibSrcDir AND OSGJpegLibSrcDir)

  PROJECT(OSGTiffLib)

  SET(${PROJECT_NAME}SharedTarget osgtiff)
  SET(${PROJECT_NAME}StaticTarget libosgtiff)

  SET(OSG_TIFFLIB_SRCS ${OSGTiffLibSrcDir}/libtiff/tif_aux.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_close.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_codec.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_color.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_compress.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_dir.c
                       ${OSGTiffLibSrcDir}/libtiff/tif_dirinfo.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_dirread.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_dirwrite.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_dumpmode.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_error.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_extension.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_fax3.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_fax3sm.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_getimage.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_jpeg.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_ojpeg.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_flush.c
                       ${OSGTiffLibSrcDir}/libtiff/tif_luv.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_lzw.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_next.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_open.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_packbits.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_pixarlog.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_predict.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_print.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_read.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_stream.cxx
                       ${OSGTiffLibSrcDir}/libtiff/tif_swab.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_strip.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_thunder.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_tile.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_version.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_warning.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_write.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_zip.c 
                       ${OSGTiffLibSrcDir}/libtiff/tif_unix.c)

  SET(OSG_TIFFLIB_HDR ${OSGTiffLibSrcDir}/libtiff/tiff.h 
                      ${OSGTiffLibSrcDir}/libtiff/tiffio.h
                      ${OSGTiffLibSrcDir}/libtiff/tiffconf.h
                      ${OSGTiffLibSrcDir}/libtiff/tiffvers.h)

  SET(OSGTIFFLIB_DEF  AVOID_WIN32_FILEIO;CHECK_JPEG_YCBCR_SUBSAMPLING;DEFAULT_EXTRASAMPLE_AS_ALPHA;STRIPCHOP_DEFAULT=TIFF_STRIPCHOP;STRIP_SIZE_DEFAULT=8192;LOGLUV_SUPPORT;NEXT_SUPPORT;THUNDER_SUPPORT;LZW_SUPPORT;PACKBITS_SUPPORT;CCITT_SUPPORT;TIF_PLATFORM_CONSOLE;FILLODER_LSB2MSB)

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGTiffLibSrcDir}/libtiff/tif_config.h.vc"
                     "${CMAKE_BINARY_DIR}/libtiff/tif_config.h")
  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGTiffLibSrcDir}/libtiff/tiffconf.h.vc"
                     "${CMAKE_BINARY_DIR}/libtiff/tiffconf.h")
  
  INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/libtiff)
  INCLUDE_DIRECTORIES(${OSG_ZLIB_INCLUDE_DIR})
  INCLUDE_DIRECTORIES(${OSGJpegLibSrcDir})

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_TIFFLIB_SRCS}
                                                      ${OSGTiffLibSrcDir}/libtiff/libtiff.def)

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET(OSGTIFFLIB_DEF_SHARED ${OSGTIFFLIB_DEF};ZLIB_DLL)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGTIFFLIB_DEF_SHARED}")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} osgzlib)
    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} libosgjpg)

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_TIFFLIB_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGTIFFLIB_DEF}")


    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_TIFFLIB_HDR}
          DESTINATION include
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

ELSE(OSGTiffLibSrcDir AND OSGZLibSrcDir AND OSGJpegLibSrcDir)
  SET(OSGTiffLibSrcDir "" CACHE PATH "")
ENDIF(OSGTiffLibSrcDir AND OSGZLibSrcDir AND OSGJpegLibSrcDir)
