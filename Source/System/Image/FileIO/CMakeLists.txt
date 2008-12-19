#################
# OSGImageFileIO
#################

CLEAR_PROJECT(OSGImageFileIO)

SET(OSGImageFileIO_OSG_Dependencies OSGSystem)

SET(OSGImageFileIO_Ext_Inc_Dependencies ${OSG_EXTERNAL_IMAGEINCS})
SET(OSGImageFileIO_Ext_Lib_Dependencies ${OSG_EXTERNAL_IMAGELIBS})

SET(OSGImageFileIO_Test_OSG_Dependencies OSGText 
                                         OSGWindow
                                         OSGUtil
                                         OSGWindowGLUT)

SETUP_PROJECT(OSGImageFileIO COMPILEIMAGEFILEIOLIB)
