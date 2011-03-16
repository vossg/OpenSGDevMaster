
##############################################################################
# ZLIB
##############################################################################

MACRO(OSG_CONFIGURE_ZLIB)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

        IF(EXISTS ${OSG_SUPPORT_ROOT}/include/zlib.h)
            SET(ZLIB_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
        ENDIF()

        IF(OSG_USE_STATIC_SUPPORT_LIBS)
            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgzlib.lib)
                SET(ZLIB_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgzlib.lib)
            ENDIF()
            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgzlibD.lib)
                SET(ZLIB_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgzlibD.lib)
            ENDIF()
        ELSE()
            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgzlib.lib)
                SET(ZLIB_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgzlib.lib)
            ENDIF()
            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgzlibD.lib)
                SET(ZLIB_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgzlibD.lib)
            ENDIF()
        ENDIF()

        IF(ZLIB_INCLUDE_DIR)
            IF(ZLIB_LIBRARY_DEBUG OR ZLIB_LIBRARY_RELEASE)
                SET(ZLIB_FOUND TRUE)
            ENDIF()
        ENDIF()

        IF(ZLIB_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_ZLIB_TARGETS ZLIB_LIBRARY)
          SET(ZLIB_LIBRARIES ${OSG_ZLIB_TARGETS} CACHE STRING "" FORCE)
        ENDIF(ZLIB_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT ZLIB_FOUND)

        OSG_FIND_PACKAGE(ZLIB_OpenSG)

        IF(ZLIB_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_ZLIB_TARGETS ZLIB_LIBRARY)

          SET(ZLIB_LIBRARIES ${OSG_ZLIB_TARGETS} CACHE STRING "" FORCE)

          OSG_ADD_OPT(ZLIB_LIBRARIES)
        ENDIF(ZLIB_FOUND)

    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT ZLIB_FOUND)

    IF(ZLIB_FOUND)
        OSG_SET(OSG_WITH_ZLIB 1)
    ENDIF(ZLIB_FOUND)

ENDMACRO(OSG_CONFIGURE_ZLIB)

##############################################################################
# GLUT
##############################################################################

MACRO(OSG_CONFIGURE_GLUT)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

        IF(EXISTS ${OSG_SUPPORT_ROOT}/include/GL/glut.h)
            SET(GLUT_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
        ENDIF()

#        IF(OSG_USE_STATIC_SUPPORT_LIBS)
#            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgfreeglut.lib)
#                SET(GLUT_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgfreeglut.lib)
#            ENDIF()
#            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgfreeglutD.lib)
#                SET(GLUT_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgfreeglutD.lib)
#            ENDIF()
#         ELSE()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgglut.lib)
            SET(GLUT_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgglut.lib)
        ENDIF()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgglutD.lib)
            SET(GLUT_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgglutD.lib)
        ENDIF()
#   ENDIF()

        IF(GLUT_INCLUDE_DIR)
          IF(GLUT_LIBRARY_DEBUG OR GLUT_LIBRARY_RELEASE)
            SET(GLUT_FOUND TRUE)
          ENDIF()
        ENDIF()

        IF(GLUT_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_GLUT_TARGETS GLUT_LIBRARY)
          SET(GLUT_LIBRARIES ${OSG_GLUT_TARGETS} CACHE STRING "" FORCE)
        ENDIF(GLUT_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT GLUT_FOUND)

      IF(WIN32)
        OSG_FIND_PACKAGE(GLUT_OpenSG)

        IF(GLUT_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_GLUT_TARGETS GLUT_glut_LIBRARY)

          SET(GLUT_LIBRARIES ${OSG_GLUT_TARGETS} CACHE STRING "" FORCE)
        ENDIF(GLUT_FOUND)

      ELSE(WIN32)
        OSG_FIND_PACKAGE(GLUT)
      ENDIF(WIN32)

    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT GLUT_FOUND)

ENDMACRO(OSG_CONFIGURE_GLUT)

##############################################################################
# GDAL
##############################################################################

MACRO(OSG_CONFIGURE_GDAL)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

        IF(EXISTS ${OSG_SUPPORT_ROOT}/include/gdal/gdal_priv.h)
            SET(GDAL_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
        ENDIF()

        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osggdal.lib)
            SET(GDAL_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osggdal.lib)
        ENDIF()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osggdalD.lib)
            SET(GDAL_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osggdalD.lib)
        ENDIF()

        IF(GDAL_INCLUDE_DIR)
          IF(GDAL_LIBRARY_DEBUG OR GDAL_LIBRARY_RELEASE)
            SET(GDAL_FOUND TRUE)
          ENDIF()
        ENDIF()

        IF(GDAL_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_GDAL_TARGETS GDAL_LIBRARY)
          SET(GDAL_LIBRARIES ${OSG_GDAL_TARGETS} CACHE STRING "" FORCE)
        ENDIF(GDAL_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT GDAL_FOUND)

      IF(WIN32)
        OSG_FIND_PACKAGE(GDAL)

#        IF(GDAL_FOUND)
#          OSG_ADD_IMPORT_LIB(OSG_GDAL_TARGETS GDAL_LIBRARY)

#          SET(GDAL_LIBRARIES ${OSG_GDAL_TARGETS} CACHE STRING "" FORCE)
#        ENDIF(GDAL_FOUND)

      ELSE(WIN32)
        OSG_FIND_PACKAGE(GDAL)
      ENDIF(WIN32)

    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT GDAL_FOUND)

ENDMACRO(OSG_CONFIGURE_GDAL)

##############################################################################
# PNG
##############################################################################

MACRO(OSG_CONFIGURE_PNG)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

      IF(EXISTS ${OSG_SUPPORT_ROOT}/include/png.h)
        SET(PNG_PNG_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
      ENDIF()

      IF(OSG_USE_STATIC_SUPPORT_LIBS)
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgpng.lib)
          SET(PNG_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgpng.lib)
        ENDIF()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgpngD.lib)
          SET(PNG_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgpngD.lib)
        ENDIF()
      ELSE()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgpng.lib)
          SET(PNG_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgpng.lib)
        ENDIF()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgpngD.lib)
          SET(PNG_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgpngD.lib)
        ENDIF()
      ENDIF()

      IF(PNG_PNG_INCLUDE_DIR)
        IF(PNG_LIBRARY_DEBUG OR PNG_LIBRARY_RELEASE)
          SET(PNG_FOUND TRUE)
        ENDIF()
      ENDIF()

      IF(PNG_FOUND)
        OSG_ADD_IMPORT_LIB(OSG_PNG_TARGETS PNG_LIBRARY)
        SET(PNG_LIBRARIES ${OSG_PNG_TARGETS} CACHE STRING "" FORCE)
      ENDIF(PNG_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT PNG_FOUND)

        OSG_FIND_PACKAGE(PNG_OpenSG)

        IF(PNG_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_PNG_TARGETS PNG_LIBRARY)

          SET(PNG_LIBRARIES ${OSG_PNG_TARGETS} CACHE STRING "" FORCE)

          SET(PNG_INCLUDE_DIR "${PNG_INCLUDE_DIR};${ZLIB_INCLUDE_DIR}")

          SET_TARGET_PROPERTIES(${OSG_PNG_TARGETS} PROPERTIES
                                IMPORTED_LINK_INTERFACE_LIBRARIES ${OSG_ZLIB_TARGETS})

          OSG_ADD_OPT(OSG_PNG_TARGETS)

        ENDIF(PNG_FOUND)
    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT PNG_FOUND)

ENDMACRO(OSG_CONFIGURE_PNG)

##############################################################################
# TIFF
##############################################################################

MACRO(OSG_CONFIGURE_TIFF)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

      IF(EXISTS ${OSG_SUPPORT_ROOT}/include/tiff.h)
        SET(TIFF_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
      ENDIF()

      IF(OSG_USE_STATIC_SUPPORT_LIBS)
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgtiff.lib)
          SET(TIFF_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgtiff.lib)
        ENDIF()
          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgtiffD.lib)
            SET(TIFF_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgtiffD.lib)
          ENDIF()
        ELSE()
          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgtiff.lib)
            SET(TIFF_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgtiff.lib)
          ENDIF()
          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgtiffD.lib)
            SET(TIFF_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgtiffD.lib)
          ENDIF()
        ENDIF()

        IF(TIFF_INCLUDE_DIR)
          IF(TIFF_LIBRARY_DEBUG OR TIFF_LIBRARY_RELEASE)
            SET(TIFF_FOUND TRUE)
          ENDIF()
        ENDIF()

        IF(TIFF_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_TIFF_TARGETS TIFF_LIBRARY)
          SET(TIFF_LIBRARIES ${OSG_TIFF_TARGETS} CACHE STRING "" FORCE)
        ENDIF(TIFF_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT TIFF_FOUND)
        OSG_FIND_PACKAGE(TIFF_OpenSG)

        IF(TIFF_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_TIFF_TARGETS TIFF_LIBRARY)

          SET(TIFF_LIBRARIES ${OSG_TIFF_TARGETS} CACHE STRING "" FORCE)
        ENDIF(TIFF_FOUND)
    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT TIFF_FOUND)

ENDMACRO(OSG_CONFIGURE_TIFF)

##############################################################################
# OpenEXR
##############################################################################

MACRO(OSG_CONFIGURE_OPENEXR)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

      IF(EXISTS ${OSG_SUPPORT_ROOT}/include/OpenEXR/ImfIO.h)
        SET(OPENEXR_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include;${OSG_SUPPORT_ROOT}/include/OpenEXR CACHE PATH "" FORCE)
      ENDIF()

      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgilmimf.lib)
        SET(OPENEXR_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgilmimf.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgilmimfD.lib)
        SET(OPENEXR_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgilmimfD.lib)
      ENDIF()

        #      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/)
        #        SET(OPENEXR__LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/)
        #     ENDIF()
        #      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/)
        #        SET(OPENEXR__LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/)
        #     ENDIF()

      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgilmthread.lib)
        SET(OPENEXR_ILMTHREAD_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgilmthread.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgilmthreadD.lib)
        SET(OPENEXR_ILMTHREAD_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgilmthreadD.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgIex.lib)
        SET(OPENEXR_IEX_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgIex.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgIexD.lib)
        SET(OPENEXR_IEX_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgIexD.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgHalf.lib)
        SET(OPENEXR_HALF_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgHalf.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgHalfD.lib)
        SET(OPENEXR_HALF_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgHalfD.lib)
      ENDIF()

      IF(OPENEXR_INCLUDE_DIR)
        IF(OPENEXR_LIBRARY_DEBUG OR OPENEXR_LIBRARY_RELEASE)
          SET(OPENEXR_FOUND TRUE)
        ENDIF()
      ENDIF()

      IF(OPENEXR_FOUND)
        OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_LIBRARY)
        OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_ILMTHREAD_LIBRARY)
        OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_IEX_LIBRARY)
        OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_HALF_LIBRARY)

        SET(OPENEXR_LIBRARIES ${OSG_OPENEXR_TARGETS} CACHE STRING "" FORCE)
      ENDIF(OPENEXR_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT OPENEXR_FOUND)
        OSG_FIND_PACKAGE(OpenEXR)

        IF(OPENEXR_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_LIBRARY_IMF)
          OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_LIBRARY_ILMTHREAD)
          OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_LIBRARY_IEX)
          OSG_ADD_IMPORT_LIB(OSG_OPENEXR_TARGETS OPENEXR_LIBRARY_HALF)

          SET(OPENEXR_LIBRARIES ${OSG_OPENEXR_TARGETS} CACHE STRING "" FORCE)
        ENDIF(OPENEXR_FOUND)
    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT OPENEXR_FOUND)

ENDMACRO(OSG_CONFIGURE_OPENEXR)

##############################################################################
# JPEG
##############################################################################

MACRO(OSG_CONFIGURE_JPEG)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

      IF(EXISTS ${OSG_SUPPORT_ROOT}/include/jpeglib.h)
        SET(JPEG_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
      ENDIF()

      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgjpg.lib)
        SET(JPEG_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgjpg.lib)
      ENDIF()
      IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgjpgD.lib)
        SET(JPEG_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgjpgD.lib)
      ENDIF()

      IF(JPEG_INCLUDE_DIR)
        IF(JPEG_LIBRARY_DEBUG OR JPEG_LIBRARY_RELEASE)
          SET(JPEG_FOUND TRUE)
        ENDIF()
      ENDIF()

      IF(JPEG_FOUND)
        OSG_ADD_IMPORT_LIB(OSG_JPEG_TARGETS JPEG_LIBRARY)
        SET(JPEG_LIBRARIES ${OSG_JPEG_TARGETS} CACHE STRING "" FORCE)
      ENDIF(JPEG_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT JPEG_FOUND)
      OSG_FIND_PACKAGE(JPEG_OpenSG)

      IF(JPEG_FOUND)
        OSG_ADD_IMPORT_LIB(OSG_JPEG_TARGETS JPEG_LIBRARY)

        SET(JPEG_LIBRARIES ${OSG_JPEG_TARGETS} CACHE STRING "" FORCE)
      ENDIF(JPEG_FOUND)
    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT JPEG_FOUND)

ENDMACRO(OSG_CONFIGURE_JPEG)

##############################################################################
# Collada
##############################################################################

MACRO(OSG_CONFIGURE_COLLADA)
    IF(OSG_USE_OSGSUPPORT_LIBS)

        IF(EXISTS ${OSG_SUPPORT_ROOT}/include/dae.h)
            SET(COLLADA_DAE_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
        ENDIF()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/include/1.4/dom/domTypes.h)
            SET(COLLADA_DOM_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include/1.4 CACHE PATH "" FORCE)
        ENDIF()

        IF(UNIX)
            IF(OSG_USE_STATIC_SUPPORT_LIBS)
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgcollada14dom22.a)
                    SET(COLLADA_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgcollada14dom22.a "" CACHE INTERNAL "" FORCE)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/debug/libosgcollada14dom22.a)
                    SET(COLLADA_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/debug/libosgcollada14dom22.a "" CACHE INTERNAL "" FORCE)
                ENDIF()
            ELSE(OSG_USE_STATIC_SUPPORT_LIBS)
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgcollada14dom22${CMAKE_SHARED_LIBRARY_SUFFIX})
                    SET(COLLADA_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgcollada14dom22${CMAKE_SHARED_LIBRARY_SUFFIX} "" CACHE INTERNAL "" FORCE)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/debug/libosgcollada14dom22${CMAKE_SHARED_LIBRARY_SUFFIX})
                    SET(COLLADA_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/debug/libosgcollada14dom22${CMAKE_SHARED_LIBRARY_SUFFIX} "" CACHE INTERNAL "" FORCE)
                ENDIF()
            ENDIF(OSG_USE_STATIC_SUPPORT_LIBS)
        ELSEIF(WIN32)
            IF(OSG_USE_STATIC_SUPPORT_LIBS)
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgcollada14dom22.lib)
                    SET(COLLADA_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgcollada14dom22.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgcollada14dom22D.lib)
                    SET(COLLADA_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgcollada14dom22D.lib)
                ENDIF()

                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgxml2.lib)
                    SET(COLLADA_XML2_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgxml2.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgxml2D.lib)
                    SET(COLLADA_XML2_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgxml2D.lib)
                ENDIF()

                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgpcrecpp.lib)
                    SET(COLLADA_PCRECPP_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgpcrecpp.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgpcrecppD.lib)
                    SET(COLLADA_PCRECPP_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgpcrecppD.lib)
                ENDIF()

                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgminizip.lib)
                    SET(COLLADA_MINIZIP_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgminizip.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgminizipD.lib)
                    SET(COLLADA_MINIZIP_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgminizipD.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgiconv.lib)
                    SET(COLLADA_ICONV_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgiconv.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgiconvD.lib)
                    SET(COLLADA_ICONV_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgiconvD.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgpcre.lib)
                    SET(COLLADA_PCRE_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgpcre.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgpcreD.lib)
                    SET(COLLADA_PCRE_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgpcreD.lib)
                ENDIF()
            ELSE(OSG_USE_STATIC_SUPPORT_LIBS)
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgcollada14dom22.lib)
                    SET(COLLADA_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgcollada14dom22.lib)
                ENDIF()
                IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgcollada14dom22D.lib)
                    SET(COLLADA_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgcollada14dom22D.lib)
                ENDIF()
            ENDIF(OSG_USE_STATIC_SUPPORT_LIBS)
        ENDIF()

        SET(OSG_COLLADA_TARGETS )

        #   SET(COLLADA_LIBRARIES ${OSG_COLLADA_TARGETS} CACHE STRING "" FORCE)

        IF(COLLADA_DAE_INCLUDE_DIR AND COLLADA_DOM_INCLUDE_DIR)
            IF(COLLADA_LIBRARY_DEBUG OR COLLADA_LIBRARY_RELEASE)
                SET(COLLADA_FOUND TRUE)
            ENDIF()
        ENDIF()

        IF(COLLADA_FOUND)
            OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_LIBRARY)

            SET(COLLADA_TARGET_FOUND TRUE)

            IF(OSG_USE_STATIC_SUPPORT_LIBS)
                IF(UNIX)
                ELSEIF(WIN32)
                    OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_XML2_LIBRARY)
                    OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_PCRECPP_LIBRARY)
                    OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_MINIZIP_LIBRARY)
                    OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_ICONV_LIBRARY)
                    OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_PCRE_LIBRARY)
                ENDIF()
            ENDIF(OSG_USE_STATIC_SUPPORT_LIBS)
        ENDIF(COLLADA_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS)

    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT COLLADA_FOUND)

        FIND_PACKAGE(Collada)

        SET(OSG_COLLADA_TARGETS)

        IF(COLLADA_FOUND)
            OSG_ADD_IMPORT_LIB(OSG_COLLADA_TARGETS COLLADA_LIBRARY)
        ENDIF(COLLADA_FOUND)

    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT COLLADA_FOUND)

ENDMACRO(OSG_CONFIGURE_COLLADA)

##############################################################################
# Boost
##############################################################################

MACRO(OSG_CONFIGURE_BOOST)
    SET(Boost_USE_MULTITHREADED ON )

    IF(NOT Boost_USE_STATIC_LIBS)
        SET(Boost_USE_STATIC_LIBS OFF CACHE INTERNAL "")
    ENDIF(NOT Boost_USE_STATIC_LIBS)

    FIND_PACKAGE(Boost COMPONENTS filesystem)

    IF(Boost_FOUND)

        IF(${Boost_MINOR_VERSION} GREATER 34)
          FIND_PACKAGE(Boost COMPONENTS system)
        ENDIF(${Boost_MINOR_VERSION} GREATER 34)

        LIST(APPEND OSG_GLOBAL_DEP_INCDIR OSG_BOOST_INCDIRS)

        IF(NOT Boost_USE_STATIC_LIBS)
            LIST(APPEND OSG_GLOBAL_DEP_DEFS "BOOST_ALL_DYN_LINK")
        ENDIF(NOT Boost_USE_STATIC_LIBS)

        IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR 
           CMAKE_BUILD_TYPE STREQUAL "DebugOpt")

          IF(${Boost_MINOR_VERSION} GREATER 34)
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_DEBUG} 
                               ${Boost_SYSTEM_LIBRARY_DEBUG})
          ELSE()
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_DEBUG})
          ENDIF(${Boost_MINOR_VERSION} GREATER 34)

        ELSE()

          IF(${Boost_MINOR_VERSION} GREATER 34)
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_RELEASE} 
                               ${Boost_SYSTEM_LIBRARY_RELEASE})
          ELSE()
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_RELEASE})
          ENDIF(${Boost_MINOR_VERSION} GREATER 34)

        ENDIF()

        SET(OSG_BOOST_INCDIRS ${Boost_INCLUDE_DIR})

        OSG_ADD_OPT(BOOST_ROOT)

        IF(WIN32)

            SET(OSG_BOOST_TARGETS )

            OSG_ADD_IMPORT_LIB(OSG_BOOST_TARGETS Boost_FILESYSTEM_LIBRARY)

            IF(${Boost_MINOR_VERSION} GREATER 34)
                FIND_PACKAGE(Boost COMPONENTS system)

                OSG_ADD_IMPORT_LIB(OSG_BOOST_TARGETS Boost_SYSTEM_LIBRARY)
            ENDIF()

            SET(OSG_BOOST_LIBS ${OSG_BOOST_TARGETS})

        ENDIF(WIN32)

        IF(APPLE)
            FIND_PACKAGE(Boost COMPONENTS system)

            IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR 
               CMAKE_BUILD_TYPE STREQUAL "DebugOpt")

              SET(OSG_BOOST_LIBS ${OSG_BOOST_LIBS} ${Boost_SYSTEM_LIBRARY_DEBUG})

            ELSE()

              SET(OSG_BOOST_LIBS ${OSG_BOOST_LIBS} ${Boost_SYSTEM_LIBRARY_RELEASE})

            ENDIF()

        ENDIF(APPLE)

    ELSE(Boost_FOUND)

        MESSAGE(SEND_ERROR "BOOST NOTFOUND." ${Boost_ERROR_REASON})

        IF(NOT BOOST_ROOT)
            SET(BOOST_ROOT "" CACHE PATH "")
        ENDIF(NOT BOOST_ROOT)

    ENDIF(Boost_FOUND)
ENDMACRO(OSG_CONFIGURE_BOOST)

##############################################################################
# Glew
##############################################################################

MACRO(OSG_CONFIGURE_GLEW)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

      IF(EXISTS ${OSG_SUPPORT_ROOT}/include/GL/glew.h)
        SET(GLEW_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
      ENDIF()

#      IF(OSG_USE_STATIC_SUPPORT_LIBS)
#        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgglew.lib)
#          SET(GLEW_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/libosgglew.lib)
#        ENDIF()
#        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/libosgglewD.lib)
#          SET(GLEW_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/libosgglewD.lib)
#        ENDIF()
#      ELSE()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgglew.lib)
          SET(GLEW_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgglew.lib)
        ENDIF()
        IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgglewD.lib)
          SET(GLEW_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgglewD.lib)
        ENDIF()
#      ENDIF()

      IF(GLEW_INCLUDE_DIR)
        IF(GLEW_LIBRARY_DEBUG OR GLEW_LIBRARY_RELEASE)
          SET(GLEW_FOUND TRUE)
        ENDIF()
      ENDIF()

      IF(GLEW_FOUND)
        OSG_ADD_IMPORT_LIB(OSG_GLEW_TARGETS GLEW_LIBRARY)
        SET(GLEW_LIBRARIES ${OSG_GLEW_TARGETS} CACHE STRING "" FORCE)
      ENDIF(GLEW_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

#    IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT GLEW_FOUND)
#
#      OSG_FIND_PACKAGE(GLEW)
#
#    ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT GLEW_FOUND)

ENDMACRO(OSG_CONFIGURE_GLEW)

##############################################################################
# LibMini
##############################################################################

MACRO(OSG_CONFIGURE_LIBMINI)

    IF(OSG_USE_OSGSUPPORT_LIBS)

        IF(EXISTS ${OSG_SUPPORT_ROOT}/include/mini/mini.h)
            SET(OSG_LIBMINI_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
        ENDIF()

        SET(OSG_LIBMINI_LIBRARY_RELEASE "" CACHE INTERNAL "" FORCE)
        SET(OSG_LIBMINI_LIBRARY_DEBUG  "" CACHE INTERNAL "" FORCE)
        SET(OSG_LIBMINI_FOUND FALSE CACHE INTERNAL "" FORCE)

        IF(UNIX)

          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgmini.a)
            SET(OSG_LIBMINI_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgmini.a)
          ENDIF()
          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/debug/libosgmini.a)
            SET(OSG_LIBMINI_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/debug/libosgmini.a)
          ENDIF()

        ELSEIF(WIN32)

          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgmini.lib)
              SET(OSG_LIBMINI_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgmini.lib)
          ENDIF()
          IF(EXISTS ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgminiD.lib)
              SET(OSG_LIBMINI_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib${OSG_LIBDIR_BASE_SUFFIX}/libosgminiD.lib)
          ENDIF()

        ENDIF()

        IF(OSG_LIBMINI_INCLUDE_DIR)
            IF(OSG_LIBMINI_LIBRARY_DEBUG OR OSG_LIBMINI_LIBRARY_RELEASE)
                SET(OSG_LIBMINI_FOUND TRUE CACHE INTERNAL "" FORCE)
            ENDIF()
        ENDIF()

        IF(OSG_LIBMINI_FOUND)
          OSG_ADD_IMPORT_LIB(OSG_LIBMINI_TARGETS OSG_LIBMINI_LIBRARY)
          SET(OSG_LIBMINI_LIBRARIES ${OSG_LIBMINI_TARGETS} CACHE STRING "" FORCE)
        ENDIF(OSG_LIBMINI_FOUND)

    ENDIF(OSG_USE_OSGSUPPORT_LIBS)

    IF(OSG_LIBMINI_FOUND)
        OSG_SET(OSG_WITH_LIBMINI 1)
    ENDIF(OSG_LIBMINI_FOUND)

ENDMACRO(OSG_CONFIGURE_LIBMINI)

##############################################################################
# VTK
##############################################################################

MACRO(OSG_CONFIGURE_VTK)
    OSG_SET(VTK_NO_LIBRARY_DEPENDS TRUE)
    FIND_PACKAGE(VTK)

    IF(VTK_FOUND)
        OSG_SET(OSG_WITH_VTK 1)

        SET(OSG_VTK_LIBS )

        SET(VTK_GRAPHICS_OSGLIB_RELEASE )
        SET(VTK_GRAPHICS_OSGLIB_DEBUG )

        SET(VTK_RENDERING_OSGLIB_RELEASE )
        SET(VTK_RENDERING_OSGLIB_DEBUG )

        SET(VTK_COMMON_OSGLIB_RELEASE )
        SET(VTK_COMMON_OSGLIB_DEBUG )

        SET(VTK_FILTERING_OSGLIB_RELEASE )
        SET(VTK_FILTERING_OSGLIB_DEBUG )

        SET(VTK_IO_OSGLIB_RELEASE )
        SET(VTK_IO_OSGLIB_DEBUG )


        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkGraphics.lib)
          SET(VTK_GRAPHICS_OSGLIB_RELEASE ${VTK_LIBRARY_DIRS}/vtkGraphics.lib)
        ENDIF()
        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkGraphicsD.lib)
          SET(VTK_GRAPHICS_OSGLIB_DEBUG ${VTK_LIBRARY_DIRS}/vtkGraphicsD.lib)
        ENDIF()


        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkRendering.lib)
          SET(VTK_RENDERING_OSGLIB_RELEASE ${VTK_LIBRARY_DIRS}/vtkRendering.lib)
        ENDIF()
        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkRenderingD.lib)
          SET(VTK_RENDERING_OSGLIB_DEBUG ${VTK_LIBRARY_DIRS}/vtkRenderingD.lib)
        ENDIF()


        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkCommon.lib)
          SET(VTK_COMMON_OSGLIB_RELEASE ${VTK_LIBRARY_DIRS}/vtkCommon.lib)
        ENDIF()
        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkCommonD.lib)
          SET(VTK_COMMON_OSGLIB_DEBUG ${VTK_LIBRARY_DIRS}/vtkCommonD.lib)
        ENDIF()


        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkFiltering.lib)
          SET(VTK_FILTERING_OSGLIB_RELEASE ${VTK_LIBRARY_DIRS}/vtkFiltering.lib)
        ENDIF()
        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkFilteringD.lib)
          SET(VTK_FILTERING_OSGLIB_DEBUG ${VTK_LIBRARY_DIRS}/vtkFilteringD.lib)
        ENDIF()


        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkIO.lib)
          SET(VTK_IO_OSGLIB_RELEASE ${VTK_LIBRARY_DIRS}/vtkIO.lib)
        ENDIF()
        IF(EXISTS ${VTK_LIBRARY_DIRS}/vtkIOD.lib)
          SET(VTK_IO_OSGLIB_DEBUG ${VTK_LIBRARY_DIRS}/vtkIOD.lib)
        ENDIF()

        OSG_ADD_IMPORT_LIB(OSG_VTK_LIBS VTK_GRAPHICS_OSGLIB)
        OSG_ADD_IMPORT_LIB(OSG_VTK_LIBS VTK_RENDERING_OSGLIB)
        OSG_ADD_IMPORT_LIB(OSG_VTK_LIBS VTK_COMMON_OSGLIB)
        OSG_ADD_IMPORT_LIB(OSG_VTK_LIBS VTK_FILTERING_OSGLIB)
        OSG_ADD_IMPORT_LIB(OSG_VTK_LIBS VTK_IO_OSGLIB)

#        OSG_ADD_OPT(OSG_VTK_LIBS)
        OSG_ADD_OPT(VTK_LIBRARY_DIRS)
        OSG_ADD_OPT(VTK_INCLUDE_DIRS)
        OSG_ADD_OPT(VTK_DIR)
    ENDIF(VTK_FOUND)
ENDMACRO(OSG_CONFIGURE_VTK)

##############################################################################
# OSG_ADD_GLUTPACKAGE
##############################################################################

MACRO(OSG_ADD_GLUTPACKAGE OSG_DO_SETUP_TEST)
  IF("${OSG_DO_SETUP_TEST}" STREQUAL "ON" OR "${OSG_DO_SETUP_TEST}" STREQUAL "TRUE")
    SET(${PROJECT_NAME}_DEP_TEST_INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR} OSG_GLUT_INC_DIR)
    SET(${PROJECT_NAME}_DEP_TEST_LIB ${${PROJECT_NAME}_DEP_TEST_LIB} GLUT_LIBRARIES)

#    IF(OSG_USE_OSGSUPPORT_LIBS AND OSG_USE_STATIC_SUPPORT_LIBS)
#      SET(${PROJECT_NAME}_DEP_TEST_LIB ${${PROJECT_NAME}_DEP_TEST_LIB} GLUT_LIBRARIES)
#      SET(${PROJECT_NAME}_DEP_TEST_DEFS ${${PROJECT_NAME}_DEP_TEST_DEFS};FREEGLUT_STATIC)
#    ENDIF()
  ELSE()
    SET(${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_DEP_LIB} GLUT_LIBRARIES)
    SET(${PROJECT_NAME}_DEP_INCDIR ${${PROJECT_NAME}_DEP_INCDIR} OSG_GLUT_INC_DIR)

#    IF(OSG_USE_OSGSUPPORT_LIBS AND OSG_USE_STATIC_SUPPORT_LIBS)
#      SET(${PROJECT_NAME}_DEP_DEFS ${${PROJECT_NAME}_DEP_DEFS};FREEGLUT_STATIC)
#    ENDIF()
  ENDIF()
ENDMACRO(OSG_ADD_GLUTPACKAGE SETUP_TEST)

##############################################################################
# OSG_ADD_GLEWPACKAGE
##############################################################################

MACRO(OSG_ADD_GLEWPACKAGE OSG_DO_SETUP_TEST)
  IF("${OSG_DO_SETUP_TEST}" STREQUAL "ON" OR "${OSG_DO_SETUP_TEST}" STREQUAL "TRUE")
    SET(${PROJECT_NAME}_DEP_TEST_INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR} GLEW_INCLUDE_DIR)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)
      SET(${PROJECT_NAME}_DEP_TEST_LIB ${${PROJECT_NAME}_DEP_TEST_LIB} GLEW_LIBRARIES)
#      IF(AND OSG_USE_STATIC_SUPPORT_LIBS)
#        SET(${PROJECT_NAME}_DEP_TEST_DEFS ${${PROJECT_NAME}_DEP_TEST_DEFS};GLEW_STATIC)
#      ELSE()
#        SET(${PROJECT_NAME}_DEP_TEST_DEFS ${${PROJECT_NAME}_DEP_TEST_DEFS};GLEW_BUILD)
#      ENDIF()
    ENDIF()
  ELSE()
    SET(${PROJECT_NAME}_DEP_INCDIR ${${PROJECT_NAME}_DEP_INCDIR} GLEW_INCLUDE_DIR)

    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)
      SET(${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_DEP_LIB} GLEW_LIBRARIES)
    ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)

#    IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32 AND OSG_USE_STATIC_SUPPORT_LIBS)
#      SET(${PROJECT_NAME}_DEP_DEFS ${${PROJECT_NAME}_DEP_DEFS};GLEW_STATIC)
#    ELSE()
#      SET(${PROJECT_NAME}_DEP_DEFS ${${PROJECT_NAME}_DEP_DEFS};GLEW_BUILD)
#    ENDIF()
  ENDIF()
ENDMACRO(OSG_ADD_GLEWPACKAGE SETUP_TEST)
