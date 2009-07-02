
How to build and work with the support packages:

1) Download:

http://pecl2.php.net/downloads/php-windows-builds/source/zlib-1.2.3-source.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libpng-1.2.37-source.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libjpeg-6b-source.zip
ftp://ftp.remotesensing.org/pub/libtiff/tiff-3.8.2.zip
http://prdownloads.sourceforge.net/freeglut/freeglut-2.6.0-rc1.tar.gz?download

2) Unpack to disk

3) Point OSGFreeGlutSrcDir, OSGJpegLibSrcDir, OSGLibPNGSrcDir, 
   OSGTiffLibSrcDir, and OSGZLibSrcDir to the appropriate directories, e.g.

   OSGFreeGlutSrcDir:PATH=X:/..../OpenSG-Support/Unpack/freeglut-2.6.0
   OSGJpegLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/jpeg-6b
   OSGLibPNGSrcDir:PATH=X:/....//OpenSG-Support/Unpack/libpng-1.2.37
   OSGTiffLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/tiff-3.8.2
   OSGZLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/zlib-1.2.3-source/zlib

4) Select which variants to build

  BUILD_SHARED_LIBS: build dlls where possible
  BUILD_STATIC_LIBS: build static libs where possible

5) Install

6) Configure OpenSG.

  6a) activate OSG_USE_OSGSUPPORT_LIBS

    set OSG_SUPPORT_ROOT the where you installed the support libs, e.g.

    OSG_SUPPORT_ROOT:PATH=X:/..../OpenSG-Support/install

    choose to use dlls / static libs according to what you build or prefer

    OSG_USE_STATIC_SUPPORT_LIBS:BOOL=OFF

  6b) set by hand

  6a is strongly recommended !

have fun
  gerrit

