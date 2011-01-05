
How to build and work with the support packages:

1) Download:

 1a) Boost

  If you don't have the need to modify the visual studio security c****
  or need a 64bit version you might download the prebuild packages from
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

 1b) Qt

 a) dll + opt + debug + 32Bit + vc9

configure -opensource -platform win32-msvc2008  -direct3d 

 b) dll + opt + debug + 32Bit + vc9 + no ms secure c****

configure -opensource -platform win32-msvc2008  -direct3d -D _CRT_SECURE_NO_DEPRECATE -D _CRT_SECURE_NO_WARNINGS -D _CRT_NONSTDC_NO_DEPRECATE -D _SECURE_SCL=0 -D _SCL_SECURE_NO_WARNINGS -D _SCL_SECURE_NO_DEPRECATE -D _HAS_ITERATOR_DEBUGGING=0


 1c) VTK

 1b) Rest
http://pecl2.php.net/downloads/php-windows-builds/source/zlib-1.2.3-source.zip

http://pecl2.php.net/downloads/php-windows-builds/source/libpng-1.2.37-source.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libjpeg-6b-source.zip
ftp://ftp.remotesensing.org/pub/libtiff/tiff-3.8.2.zip

 http://prdownloads.sourceforge.net/freeglut/freeglut-2.6.0-rc1.tar.gz\?download

 or

 http://www.xmission.com/~nate/glut/glut-3.7.6-src.zip

http://nchc.dl.sourceforge.net/sourceforge/collada-dom/collada-dom-2.2.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libxml2-2.7.3-src.zip
ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-7.9.zip
http://pecl2.php.net/downloads/php-windows-builds/source/libiconv-1.12-source.zip

http://hebbut.net/Public.Offerings/lib_xxx/downloads/OpenEXR-CVS.20081031.7z

http://sourceforge.net/projects/expat/files/expat/2.0.1/expat-2.0.1.tar.gz/download
http://download.osgeo.org/gdal/gdal154.zip

https://sourceforge.net/project/downloading.php\?group_id=67586\&filename=glew-1.5.1-src.zip
http://cudpp.googlecode.com/files/cudpp_src_1.1.zip

2) Unpack to disk

3) Point OSGFreeGlutSrcDir, OSGJpegLibSrcDir, OSGLibPNGSrcDir, 
   OSGTiffLibSrcDir, OSGZLibSrcDir, OSGColladaSrcDir, OSGPcreSrcDir,
   OSGLibXml2SrcDir, ....., and OSGLibIconvSrcDir to the appropriate directories, e.g.

   OSGFreeGlutSrcDir:PATH=X:/..../OpenSG-Support/Unpack/freeglut-2.6.0
   OSGJpegLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/jpeg-6b
   OSGLibPNGSrcDir:PATH=X:/....//OpenSG-Support/Unpack/libpng-1.2.37
   OSGTiffLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/tiff-3.8.2
   OSGZLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/zlib-1.2.3-source
   OSGColladaSrcDir:PATH=X:/..../OpenSG-Support/Unpack/collada-dom
   OSGPcreSrcDir:PATH=X:/..../OpenSG-Support/Unpack/pcre-7.9
   OSGLibXml2SrcDir:PATH=X:/..../OpenSG-Unpack/libxml2-2.7.3
   OSGLibIconvSrcDir:PATH=X:/..../OpenSG-Support/Unpack/libiconv-1.12-source
   .
   .
   .

4) Build + Install

5) Configure OpenSG.

  5a) activate OSG_USE_OSGSUPPORT_LIBS

    set OSG_SUPPORT_ROOT the where you installed the support libs, e.g.

    OSG_SUPPORT_ROOT:PATH=X:/..../OpenSG-Support/install

    choose to use dlls / static libs according to what you build or prefer

    OSG_USE_STATIC_SUPPORT_LIBS:BOOL=OFF

    Please make sure to use the same boost libs and _SECURE settings as for
    the support libs. This is currently neither checked/enforced nor
    automatically transferred.

  5b) set by hand

  5a is strongly recommended !

6) Doxygen

  As we use some custom doxygen extensions building the documentation works
  best with the customized doxygen version. For linux check out revision 752
  to the disk and setup the OSGDoxygenSrcDir to point to it.

  svn checkout -r 752 https://doxygen.svn.sourceforge.net/svnroot/doxygen/trunk doxygen

  After the build and install steps the custom binary should be picked up by the 
  main OpenSG cmake script.


Finally a small word of caution. The packages are build to work with OpenSG,
there might not be as general as possible. For example some of the internal package
headers are not installed (libxml2, iconv, pcre) as the are not directly
included by OpenSG. If you need them let us know.


Support Package <-> OpenSG Feature dependencies:
================================================

1) must haves, without them OpenSG itself won't build:

 -) boost
 -) zlib

2) File formats:

 -) Collada SceneFileType
      collada-dom, libiconv, libxml2, pcre 

 -) Tiff ImageFileType
      tiff
  
 -) PNG ImageFileType
      libpng

 -) JPG ImageFileType
      libjpeg

 -) GDAL ImageFileType
      gdal, expat
 
 -) OpenEXR ImageFileType
      OpenEXR

3) Window types

 -) GLUTWindow
      freeglut
 
 -) QTWindow
      qt

4) Rest

 -) Source/Contrib/VTK
      vtk

 -) Source/Contrib/Compute
      cudpp

 -) Easy testing
      glew

have fun
  gerrit

