#################
# OSGImageFileIO
#################

CLEAR_PROJECT(OSGImageFileIO)

SET(OSGImageFileIO_OSG_Dependencies OSGSystem)

SET(OSGImageFileIO_Ext_Inc_Dependencies PNG_PNG_INCLUDE_DIR
                                        JPEG_INCLUDE_DIR
                                        TIFF_INCLUDE_DIR
                                        GDAL_INCLUDE_DIR)
SET(OSGImageFileIO_Ext_Lib_Dependencies PNG_LIBRARY
                                        JPEG_LIBRARY
                                        TIFF_LIBRARY
                                        GDAL_LIBRARY)

SET(OSGImageFileIO_Test_OSG_Dependencies OSGText 
                                         OSGWindow
                                         OSGUtil
                                         OSGWindowGLUT)

SETUP_PROJECT(OSGImageFileIO COMPILEIMAGEFILEIOLIB)
