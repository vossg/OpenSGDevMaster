
How to build and work with the support packages:

1) Download:

 1a) Boost

  If you don't have the need to modify the visual studion security c****
  or need 64bit version you might download the prebuild packages from
  boost consulting instead. 

  Otherwise download:

http://nchc.dl.sourceforge.net/sourceforge/boost/boost_1_37_0.tar.gz
http://nchc.dl.sourceforge.net/sourceforge/boost/boost-jam-3.1.17-1-ntx86.zip

build 

  a) dll + static lib + dll runtime + opt + dbg + 32 bit + vc9

..\bjam.exe -d+2 --stagedir=./stage toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=32 stage

  b) dll + static lib + dll runtime + opt + dbg + 32 bit + vc9 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=32 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_SECURE_SCL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage

  c) dll + static lib + dll runtime + opt + dbg + 64 bit + vc9

..\bjam.exe -d+2 --stagedir=./stage toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=64 stage

  d) dll + static lib + dll runtime + opt + dbg + 64 bit + vc9 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=64 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_SECURE_SCL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage

Please note that you need different source/build directories for the 32 bit, 64 bit,
scecurity and non security versions, as the standards cmake find boost module
only seems to work with the single 'stage' dir.

 1b) Rest
http://pecl2.php.net/downloads/php-windows-builds/source/zlib-1.2.3-source.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libpng-1.2.37-source.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libjpeg-6b-source.zip
ftp://ftp.remotesensing.org/pub/libtiff/tiff-3.8.2.zip
http://prdownloads.sourceforge.net/freeglut/freeglut-2.6.0-rc1.tar.gz?download
http://nchc.dl.sourceforge.net/sourceforge/collada-dom/collada-dom-2.2.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libxml2-2.7.3-src.zip
ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-7.9.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libiconv-1.12-source.zip
http://hebbut.net/Public.Offerings/lib_xxx/downloads/OpenEXR-CVS.20081031.7z

2) Unpack to disk

3) Point OSGFreeGlutSrcDir, OSGJpegLibSrcDir, OSGLibPNGSrcDir, 
   OSGTiffLibSrcDir, OSGZLibSrcDir, OSGColladaSrcDir, OSGPcreSrcDir,
   OSGLibXml2SrcDir, and OSGLibIconvSrcDir to the appropriate directories, e.g.

   OSGFreeGlutSrcDir:PATH=X:/..../OpenSG-Support/Unpack/freeglut-2.6.0
   OSGJpegLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/jpeg-6b
   OSGLibPNGSrcDir:PATH=X:/....//OpenSG-Support/Unpack/libpng-1.2.37
   OSGTiffLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/tiff-3.8.2
   OSGZLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/zlib-1.2.3-source/zlib
   OSGColladaSrcDir:PATH=X:/..../OpenSG-Support/Unpack/collada-dom
   OSGPcreSrcDir:PATH=X:/..../OpenSG-Support/Unpack/pcre-7.9
   OSGLibXml2SrcDir:PATH=X:/..../OpenSG-Unpack/libxml2-2.7.3
   OSGLibIconvSrcDir:PATH=X:/..../OpenSG-Support/Unpack/libiconv-1.12-source

4) Select which variants to build

  BUILD_SHARED_LIBS: build dlls where possible
  BUILD_STATIC_LIBS: build static libs where possible

5) Build + Install

6) Configure OpenSG.

  7a) activate OSG_USE_OSGSUPPORT_LIBS

    set OSG_SUPPORT_ROOT the where you installed the support libs, e.g.

    OSG_SUPPORT_ROOT:PATH=X:/..../OpenSG-Support/install

    choose to use dlls / static libs according to what you build or prefer

    OSG_USE_STATIC_SUPPORT_LIBS:BOOL=OFF

    Please make sure to use the same boost libs and _SECURE settings as for
    the support libs. This is currently neither checked/enforced nor
    automatically transferred.

  7b) set by hand

  7a is strongly recommended !

Finally a small word of caution. The packages are build to work with OpenSG,
there might not be as general as possible. For example some of the internal package
headers are not installed (libxml2, iconv, pcre) as the are not directly
included by OpenSG. If you need them let us know.

have fun
  gerrit

