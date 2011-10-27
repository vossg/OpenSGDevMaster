
import sys,os,subprocess,shutil,platform,time
import urllib, tarfile, zipfile, sys, os, shutil, glob
import commands
import optparse

common_deps_src = [\
    ("OSGColladaSrcDir", "http://sourceforge.net/projects/collada-dom/files/Collada%20DOM/Collada%20DOM%202.2/Collada%20DOM%202.2.zip/download", "Collada DOM 2.2.zip", "collada-dom"),\
    ("OSGLibMiniSrcDir", "http://stereofx.org/download/mini/MINI-9.8.zip", None, "mini"),\
    ("OSGOpenNurbsSrcDir", "http://files.na.mcneel.com/opennurbs/5.0/2011-02-02/opennurbs_20110202.zip", None, None),\
    ("OSGGLEWSrcDir", "http://sourceforge.net/projects/glew/files/glew/1.7.0/glew-1.7.0.zip/download", None, None)\
              ]

win_deps_src = [("OSGZLibSrcDir", "http://sourceforge.net/projects/libpng/files/zlib/1.2.5/zlib125.zip/download", None, None), \
                ("OSGFreeGlutSrcDir", "http://sourceforge.net/projects/freeglut/files/freeglut/freeglut-2.6.0.tar.gz/download", None, None),\
                ("OSGLibPNGSrcDir", "http://sourceforge.net/projects/libpng/files/libpng15/older-releases/1.5.4/lpng154.zip/download", None, None),\
                ("OSGJpegLibSrcDir", "http://sourceforge.net/projects/libjpeg/files/libjpeg/6b/jpegsr6.zip/download", None, "jpeg-6b"),\
                ("OSGTiffLibSrcDir", "http://download.osgeo.org/libtiff/tiff-3.8.2.zip", None, None),\
                ("OSGPcreSrcDir","http://sourceforge.net/projects/pcre/files/pcre/8.12/pcre-8.12.zip/download", None, None),\
                ("OSGOpenExrSrcDir", "http://download.savannah.nongnu.org/releases/openexr/openexr-1.7.0.tar.gz", None, None),\
                ("OSGIlmBaseSrcDir", "http://download.savannah.nongnu.org/releases/openexr/ilmbase-1.0.2.tar.gz", None, None),\
                ("OSGGdalSrcDir", "http://download.osgeo.org/gdal/gdal180.zip", None, "gdal-1.8.0"),\
                ("OSGExpatSrcDir", "http://sourceforge.net/projects/expat/files/expat/2.0.1/expat-2.0.1.tar.gz/download", None, None),\
                ("OSGLibXml2SrcDir", "ftp://xmlsoft.org/libxml2/libxml2-2.7.8.tar.gz", None, None), \
                ("BOOST_ROOT", "http://sourceforge.net/projects/boost/files/boost/1.44.0/boost_1_44_0.zip/download", None, None), \
                ("BOOST_JAM", "http://sourceforge.net/projects/boost/files/boost-jam/3.1.18/boost-jam-3.1.18-1-ntx86.zip/download", None, None)\
           ]

common_deps_fhg = [\
    ("OSGColladaSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/Collada%20DOM%202.2.zip", "Collada DOM 2.2.zip", "collada-dom"),\
    ("OSGLibMiniSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/MINI-9.8.zip", None, "mini"),\
    ("OSGOpenNurbsSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/opennurbs_20110202.zip", None, None),\
    ("OSGGLEWSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/glew-1.7.0.zip", None, None)\
              ]

win_deps_fhg = [("OSGZLibSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/zlib125.zip", None, None), \
                ("OSGFreeGlutSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/freeglut-2.6.0.tar.gz", None, None),\
                ("OSGLibPNGSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/lpng154.zip", None, None),\
                ("OSGJpegLibSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/jpegsr6.zip", None, "jpeg-6b"),\
                ("OSGTiffLibSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/tiff-3.8.2.zip", None, None),\
                ("OSGPcreSrcDir","http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/pcre-8.12.zip", None, None),\
                ("OSGOpenExrSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/openexr-1.7.0.tar.gz", None, None),\
                ("OSGIlmBaseSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/ilmbase-1.0.2.tar.gz", None, None),\
                ("OSGGdalSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/gdal180.zip", None, "gdal-1.8.0"),\
                ("OSGExpatSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/expat-2.0.1.tar.gz", None, None),\
                ("OSGLibXml2SrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/libxml2-2.7.8.tar.gz", None, None), \
                ("BOOST_ROOT", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/boost_1_44_0.zip", None, None), \
                ("BOOST_JAM", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/boost-jam-3.1.18-1-ntx86.zip", None, None)\
           ]

failed_support_libs = []

##############################################
# Base Builder
##############################################

class OSGBaseBuilder:

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False,
               subDir            = None ):

    if subDir == None:
      subDir = ""

    extraUp = ""

    if subDir != "":
      extraUp = ".."

    self.startup_path     = startup_path
    self.download_path    = os.path.join(self.startup_path, "Downloads")
    self.unpack_path      = os.path.join(self.startup_path, "Unpack")
    self.suppBuild_path   = os.path.join(self.startup_path, subDir, "OpenSG.Support.build")
    self.suppInst_path    = os.path.join(self.startup_path, subDir, "OpenSG.Support.install").replace('\\', '/')

    self.osg_path         = os.path.join(self.startup_path, "OpenSG")
    self.dbgBuild_path    = os.path.join(self.startup_path, subDir, "OpenSG.build")
    self.optBuild_path    = os.path.join(self.startup_path, subDir, "OpenSG.build.opt")
    self.osgInst_path     = os.path.join(self.startup_path, subDir, "OpenSG.install").replace('\\', '/')

    self.osgRel_path      = os.path.join("..", extraUp, "OpenSG")
    self.osgBuildRel_path = os.path.join("..",          "OpenSG.build")
    self.suppRel_path     = os.path.join("..", extraUp, "OpenSG", "Support")

    self.buildSubDir      = subDir

    self.boostroot_path   = None
    self.boostjam_path    = None
    self.boostjam         = None

    self.cmSuppArchFile   = os.path.join(self.unpack_path, "CMakeSupportArchs.txt")
    self.cmSupportFile    = os.path.join(self.osg_path,    "CMakeSupport.txt")
    self.cmOSGFile        = os.path.join(self.osg_path,    "CMakeOSG.txt")

    self.nodownload     = optNoDownload
    self.sgdownload     = optSGDownload
    self.nounpack       = optNoUnpack
    self.nogitclone     = optNoGitClone
    self.localgitclone  = optLocalGitClone

    self.nosupportbuild = optNoSupportBuild
    self.noboostbuild   = optNoBoostBuild
    self.noosgbuild     = optNoOSGBuild
    self.nomssecure     = optNoMSSecure

    self.cmakeCmd       = None
    self.makeCmd        = None

    self.vcvars         = None

    self.gitCmd         = None

    if self.sgdownload == True:
      self.common_deps = common_deps_fhg
      self.win_deps    = win_deps_fhg
    else:
      self.common_deps = common_deps_src
      self.win_deps    = win_deps_src

    if self.buildSubDir != None and self.buildSubDir != "" and not os.path.exists(self.buildSubDir):
      os.mkdir(self.buildSubDir)

    return

  def dumpOptions(self):

    print "download      : ", not self.nodownload
    print "sgdownload    : ", self.sgdownload

    print "unpack        : ", not self.nounpack

    print "gitclone      : ", not self.nogitclone
    print "localgitclone : ", self.localgitclone
    print "support build : ", not self.nosupportbuild
    print "boost build   : ", not self.noboostbuild

    print "osg build     : ", not self.noosgbuild

    print "ms secure     : ", self.nomssecure

    print "build subdir  : ", self.buildSubDir

    print "supp.build    : ", self.suppBuild_path
    print "supp.inst     : ", self.suppInst_path
    
    print "osg.dbg.build : ", self.dbgBuild_path
    print "osg.opt.build : ", self.optBuild_path
    print "osg.install   : ", self.osgInst_path

  def which(self, program):

    def is_exe(fpath):
      return os.path.exists(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)

    if fpath:
      if is_exe(program):
        return program
    else:
      for path in os.environ["PATH"].split(os.pathsep):
        exe_file = os.path.join(path, program)

        if is_exe(exe_file):
          return exe_file

      for path in self.fallbackPaths:
        exe_file = os.path.join(path, program)

        if is_exe(exe_file):
          return exe_file

    return None

  def initDir(self, dirname, createDir = True):

    print "init dir ", dirname

    if os.path.isdir(dirname):
      shutil.rmtree(dirname)

    if createDir == True:
      os.mkdir(dirname)

  def progress(self, count, blocksize, size):

    text="%d / %d" % (count * blocksize, size)
    text += len(text) * '\b'
    sys.stdout.write(text)
    sys.stdout.flush()
        
  def getUrl(self, url, file):

    if os.path.exists(file):
      print "%s exists, not downloading." % file
      return
                
    sys.stdout.write("Downloading %s: " % file)
    urllib.urlretrieve(url=url, filename=file, reporthook=self.progress)
    print


  def prepareArchives(self, cmCfgFileOut, deps):

    print "downloading to %s" % self.download_path

    os.chdir(self.download_path)

    for var, url, arcfile, dir in deps:

      print "processing dep %s | %s | %s | %s" % (var, url, arcfile, dir)

      # Get filename from URL, if not provided explicitly
      if not arcfile:
        arcfile=url.rsplit('/', 1)[1]
                
        if arcfile == "download":
          arcfile=url.rsplit('/', 2)[1]

      if self.nodownload == False:
        try:
          self.getUrl(url, arcfile)
        except:
          print "################"
          print "#### failed ####"
          print "################"
          failed_support_libs.append(url)
          continue


      if arcfile.endswith(".tar.gz") or arcfile.endswith(".tar"):
                
        if not dir:
          if arcfile.endswith(".tar.gz"):
            dir = arcfile[:-7]
          elif arcfile.endswith(".tar"):
            dir = arcfile[:-4]
                
        dir = os.path.join(self.unpack_path, dir)

        print "untar %s | %s" % (arcfile, dir) 

        if not os.path.exists(dir):
          try:
            print "Untarring %s..." % arcfile
                      
            t = tarfile.open(arcfile, "r")             
            t.extractall(path=dir)
            t.close()
          except:
            print "################"
            print "#### failed ####"
            print "################"
            failed_support_libs.append(url)
            continue
        
      elif arcfile.endswith(".zip"):
 
        if not dir:
          dir = arcfile[:-4]

        dir = os.path.join(self.unpack_path, dir)

        print "bar %s | %s " % (arcfile, dir)

        if not os.path.exists(dir):
          print "Unzipping %s..." % arcfile
        
          try:
            z = zipfile.ZipFile(arcfile, "r")          
            z.extractall(path=dir)
            z.close()
          except:

            if os.path.exists(dir):
              shutil.rmtree(dir)

            unzipCmd  = self.which("unzip")

            if unzipCmd != None:
              uzCmd = [unzipCmd, "-q", arcfile, "-d", dir]
              print "uz : ", uzCmd

              try:
                retcode = subprocess.call(uzCmd)

                if retcode != 0:
                  print "################"
                  print "#### failed ####"
                  print "################"
                  failed_support_libs.append(url)
                  continue
                 
              except:
                print "################"
                print "#### failed ####"
                print "################"
                failed_support_libs.append(url)
                continue
            else:
              print "################"
              print "#### failed ####"
              print "################"
              failed_support_libs.append(url)
              continue
        
      else:
        print "Unknown file type for '%s', aborting!" % file
        sys.exit(1)

      # Only one dir? Move up 
      files = glob.glob(os.path.join(dir, "*"))

      print "foo ", files
        
      if len(files)==1 and os.path.isdir(files[0]):
        print "Just one dir, moving up."
        tmpDir = os.path.join(self.unpack_path, "bootstrap_dummy" + arcfile)

        print "foo %s | %s | %s" % (tmpDir, dir, files[0])

        shutil.move(files[0], tmpDir)
        os.removedirs(dir)
        os.rename(tmpDir, dir)

      cmCfgFileOut.write(('SET(%s "%s" CACHE PATH "")\n' % (var,  dir)).replace('\\', '/'))

      if var == "BOOST_ROOT":
        self.boostroot_path = dir.replace('\\', '/')

      if var == "BOOST_JAM":
        self.boostjam_path =  dir.replace('\\', '/')

    os.chdir(self.startup_path)

  def prepareSupportArchives(self):

    if self.nodownload == False:
      self.initDir(self.download_path)

    if self.nounpack == False:
      self.initDir(self.unpack_path)

      cmSupportOut = file(self.cmSuppArchFile, "w")
      cmSupportOut.write("# Auto-downloaded support libs defines\n\n")

      self.prepareArchives(cmSupportOut, self.common_deps)

      if system == "windows":
        self.prepareArchives(cmSupportOut, self.win_deps)

      cmSupportOut.write('\n')

      cmSupportOut.close()

  def prepareOSGSupport(self):

      self.prepareSupportArchives()

      cmSupportOut = file(self.cmSupportFile, "w")
      
      cmSuppArchOut = file(self.cmSuppArchFile, "r")

      for line in cmSuppArchOut.readlines():
        cmSupportOut.write(line)

      cmSuppArchOut.close()

      cmSupportOut.write('SET(CMAKE_INSTALL_PREFIX "%s" CACHE PATH "")\n' % self.suppInst_path)
      cmSupportOut.write('SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)\n')
      cmSupportOut.write('SET(CMAKE_BUILD_TYPE Release CACHE STRING "xxx" FORCE)\n\n')

      cmSupportOut.write('IF(WIN32)\n')
      cmSupportOut.write('  SET(Boost_USE_STATIC_LIBS ON CACHE INTERNAL "")\n')
      if self.nomssecure == True:
        cmSupportOut.write('  OPTION(OSG_DISABLE_MICROSOFT_SECURE_CXXX "" ON)\n')
      cmSupportOut.write('ENDIF(WIN32)\n\n')

      cmSupportOut.write('OPTION(OSG_USE_OSGSUPPORT_LIBS     "" ON)\n')
      cmSupportOut.write('OPTION(OSG_USE_STATIC_SUPPORT_LIBS "" ON)\n')

      cmSupportOut.close()

  def cloneGit(self):

    if self.nogitclone == False:
      self.initDir("OpenSG", False)
      if self.localgitclone == False:
        gitCloneCmd = [self.gitCmd, "clone", "git://opensg.git.sourceforge.net/gitroot/opensg/opensg", "OpenSG"]
      else:
        gitCloneCmd = [self.gitCmd, "clone", "OpenSG.repo", "OpenSG"]

      retcode = subprocess.call(gitCloneCmd)

  def buildBoost(self):

    print "Building boost ...."
    return

  def buildOSGSupport(self):

    self.initDir(self.suppBuild_path)
    self.initDir(self.suppInst_path)

    if system == "windows":
      self.buildBoost()

    os.chdir(self.suppBuild_path)

    cmCfgCmd = [self.cmakeCmd,
                "-G",
                self.cmakeGen,
                "-C", 
                self.cmSupportFile, 
                self.suppRel_path]

    print "Supp cmake : ", cmCfgCmd

    retcode = subprocess.call(cmCfgCmd)

    os.chdir(self.startup_path)



  def prepOSG(self):

    if self.noosgbuild == False:
      self.initDir(self.osgInst_path)

    if system == "windows":
      self.checkBoostPath()

    cmOSGOut = file(self.cmOSGFile, "w")
    cmOSGOut.write("# OSG libs defines\n\n")
    cmOSGOut.write('SET(CMAKE_INSTALL_PREFIX "%s" CACHE PATH "")\n' % self.osgInst_path)
    cmOSGOut.write('SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)\n')

    cmOSGOut.write('SET(BOOST_ROOT "%s" CACHE PATH "" FORCE)\n' % self.suppInst_path)

    cmOSGOut.write('SET(OSG_USE_OSGSUPPORT_LIBS     ON  CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_SUPPORT_ROOT "%s" CACHE PATH "")\n' % self.suppInst_path)
    cmOSGOut.write('SET(OSG_USE_STATIC_SUPPORT_LIBS OFF CACHE BOOL "")\n')

    cmOSGOut.write('SET(OSGBUILD_EXAMPLES_SIMPLE   ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGBUILD_EXAMPLES_ADVANCED ON CACHE BOOL "")\n')

    cmOSGOut.write('SET(OSG_ENABLE_PAR_PARTITION_DRAWING ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_ENABLE_DEFAULT_READONLY_CHANGELIST ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_DISABLE_SOURCE_GROUPS ON CACHE BOOL "")\n\n')

    cmOSGOut.write('SET(OSGEXCLUDE_EXAMPLES_ADVANCED_FROM_ALL ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGEXCLUDE_EXAMPLES_SIMPLE_FROM_ALL   ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGEXCLUDE_TESTS_FROM_ALL             ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGEXCLUDE_UNITTESTS_FROM_ALL         ON CACHE BOOL "")\n\n')

    cmOSGOut.write('IF(WIN32)\n')
    cmOSGOut.write('  IF(CMAKE_SIZEOF_VOID_P EQUAL 8)\n')
    cmOSGOut.write('    SET(CG_ROOT "C:/Program Files (x86)/NVIDIA Corporation/Cg" CACHE PATH "" FORCE)\n')
    cmOSGOut.write('  ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)\n')
    cmOSGOut.write('    SET(CG_ROOT "C:/Program Files/NVIDIA Corporation/Cg" CACHE PATH "" FORCE)\n')
    cmOSGOut.write('  ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)\n')
    if self.nomssecure == True:
      cmOSGOut.write('  OPTION(OSG_DISABLE_MICROSOFT_SECURE_CXXX "" ON)\n')
    cmOSGOut.write('ENDIF(WIN32)\n\n')

    cmOSGOut.write('SET(OSGBUILD_OSGTestGroupLib OFF CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGBUILD_OSGTestSystemLib OFF CACHE BOOL "")\n')

    cmOSGOut.close()

  def configureOSG(self):

    self.initDir(self.dbgBuild_path)

    os.chdir(self.dbgBuild_path)

    cmCfgCmd = [self.cmakeCmd,
                "-G",
                self.cmakeGen,
                "-C", 
                self.cmOSGFile, 
                "-DCMAKE_BUILD_TYPE:STRING=Debug", 
                self.osgRel_path]

    print "runnuing ", cmCfgCmd

    retcode = subprocess.call(cmCfgCmd)

    os.chdir(self.startup_path)

  def reconfigureOSG(self, changeDir = False):

    if changeDir == True:
      os.chdir(self.dbgBuild_path)

    cmCfgCmd = [self.cmakeCmd, "."]

    print "runnuing ", cmCfgCmd

    retcode = subprocess.call(cmCfgCmd)

    if changeDir == True:
      os.chdir(self.startup_path)


##############################################
# Windows Base Builder
##############################################

class OSGWinBaseBuilder(OSGBaseBuilder):

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False):

    buildSubDir = "MSDefaults"

    if optNoMSSecure == True:
      buildSubDir = "NoMSSec"

    OSGBaseBuilder.__init__(self, 
                            startup_path,
                            optNoDownload,
                            optSGDownload,
                            optNoUnpack,
                            optNoGitClone,
                            optLocalGitClone,
                            optNoSupportBuild,
                            optNoBoostBuild,
                            optNoOSGBuild,
                            optNoMSSecure,
                            buildSubDir)

    #"-d+2",
    #"-q",
    self.boostCommonOpts = ["-d0",
                            "--without-mpi",
                            "--stagedir=./stage." + self.buildSubDir,
                            "--build-dir=./bin.v2." + self.buildSubDir,
                            "toolset=msvc-10.0",
                            "variant=debug,release",
                            "threading=multi",
                            "link=shared,static",
                            "runtime-link=shared"]

    if self.vcvarsarch != None and self.vcvarsarch == "amd64":
      # boost.python fails to link on win64 (1.44), have to try a later release
      self.boostCommonOpts.append("--without-python")

    self.boostAddrOpt    = None

    self.boostMSDefines  = ["define=_CRT_SECURE_NO_DEPRECATE",
                            "define=_CRT_SECURE_NO_WARNINGS",
                            "define=_CRT_NONSTDC_NO_DEPRECATE",
                            "define=_SECURE_SCL=0",
                            "define=_SCL_SECURE_NO_WARNINGS",
                            "define=_SCL_SECURE_NO_DEPRECATE",
                            "define=_HAS_ITERATOR_DEBUGGING=0" ]

    print "foo ", self
    print "bar ", self.fallbackPaths

    self.cmakeCmd  = self.which("cmake.exe")
    self.vcvars    = self.which("vcvarsall.bat")
    self.gitCmd    = self.which("git.exe")

    print "cm  : ", self.cmakeCmd
    print "vcv : ", self.vcvars
    print "git : ", self.gitCmd 

    if self.cmakeCmd == None:
      print "Error could not find cmake"
      sys.exit(1)

    if self.vcvars == None:
      print "Error could not find vcvars.bat"
      sys.exit(1)

    if self.gitCmd == None:
      print "Error could not find git"
      sys.exit(1)

    return

  def checkBoostPath(self):

    if self.boostroot_path == None:
      files = glob.glob(os.path.join(self.unpack_path, "boost_*"))
      print "br : ", files
      if len(files) == 1:
        self.boostroot_path = files[0].replace('\\', '/')

    if self.boostjam_path == None:
      files = glob.glob(os.path.join(self.unpack_path, "boost-jam*"))
      print "bj : ", files
      if len(files) == 1:
        self.boostjam_path = files[0].replace('\\', '/')

    if(self.boostroot_path == None or self.boostjam_path == None):
      sys.exit(1)

    self.boostjam = os.path.join(self.boostjam_path, "bjam.exe")

    print "  boost path   ", self.boostroot_path
    print "  boost jam    ", self.boostjam_path
    print "  boost jam exe", self.boostjam

  def buildBoost(self):

    print "Building boost ...."
    print "win cfg:"

    self.checkBoostPath()

    boostBaseCmd = [self.vcvars, self.vcvarsarch, "&"]
    boostBaseCmd.extend([self.boostjam])
    boostBaseCmd.extend(self.boostCommonOpts)
    boostBaseCmd.extend(self.boostAddrOpt)

    if self.nomssecure == True:
      boostBaseCmd.extend(self.boostMSDefines)


    os.chdir(self.boostroot_path)


    boostBuildCmd = []
    boostBuildCmd.extend(boostBaseCmd)

    boostBuildCmd.extend(["stage"])

    print "boost build cmd: ", boostBuildCmd

    if self.noboostbuild == False:
      retcode = subprocess.call(boostBuildCmd)


    boostInstallCmd = []

    boostInstallCmd.extend(boostBaseCmd)

    boostInstallCmd.extend(["--prefix=" + self.suppInst_path])
    boostInstallCmd.extend(["install"])

    print "boost install cmd: ", boostInstallCmd

    retcode = subprocess.call(boostInstallCmd)


    os.chdir(startup_path)

    return

  def buildOSGSupport(self):

    if self.nosupportbuild == True:
      return

    OSGBaseBuilder.buildOSGSupport(self)

    os.chdir(self.suppBuild_path)

    print "building osg support"

    buildCmd = [self.vcvars, 
                self.vcvarsarch, 
                "&",
                "devenv",
                "/build",
                "Debug",
                "/project",
                "ALL_BUILD",
                "OpenSGSupport.sln"]

    retcode = subprocess.call(buildCmd)

    buildCmd = [self.vcvars, 
                self.vcvarsarch, 
                "&",
                "devenv",
                "/build",
                "Release",
                "/project",
                "ALL_BUILD",
                "OpenSGSupport.sln"]

    retcode = subprocess.call(buildCmd)

    print "building osg support"

    buildCmd = [self.vcvars, 
                self.vcvarsarch, 
                "&",
                "devenv",
                "/build",
                "Debug",
                "/project",
                "INSTALL",
                "OpenSGSupport.sln"]

    retcode = subprocess.call(buildCmd)

    buildCmd = [self.vcvars, 
                self.vcvarsarch, 
                "&",
                "devenv",
                "/build",
                "Release",
                "/project",
                "INSTALL",
                "OpenSGSupport.sln"]

    retcode = subprocess.call(buildCmd)

    os.chdir(self.startup_path)

  def buildOpenSGVariant(self, variant):

    print "building osg variant : ", variant

    os.chdir(self.dbgBuild_path)

    buildCmd = [self.vcvars, 
                self.vcvarsarch, 
                "&",
                "devenv",
                "/build",
                variant,
                "/project",
                "OSGAll",
                "OpenSG.sln"]

    print "build cmd : ", buildCmd
    retcode = subprocess.call(buildCmd)

    self.reconfigureOSG(False)

    buildCmd = [self.vcvars, 
                self.vcvarsarch, 
                "&",
                "devenv",
                "/build",
                variant,
                "/project",
                "INSTALL",
                "OpenSG.sln"]

    print "install cmd : ", buildCmd
    retcode = subprocess.call(buildCmd)

    self.reconfigureOSG(False)

    os.chdir(self.startup_path)

  def buildOpenSG(self):

    if self.noosgbuild == True:
      return

    OSGBaseBuilder.configureOSG(self)

    self.buildOpenSGVariant("Debug")
    self.buildOpenSGVariant("DebugOpt")
    self.buildOpenSGVariant("ReleaseNoOpt")
    self.buildOpenSGVariant("Release")

##############################################
# Win32 Builder
##############################################

class OSGWin32Builder(OSGWinBaseBuilder):

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False):

    

    self.fallbackPaths = ["C:/Program Files/Microsoft Visual Studio 10.0/VC",
                          "C:/Program Files/Git/bin"]

    cmdirs = glob.glob("C:/Program Files/CMake *")

    for path in cmdirs:
      self.fallbackPaths.append(os.path.join(path, "bin").replace('\\', '/'))

    print "cmd : ", cmdirs

    self.vcvarsarch = "x86"

    OSGWinBaseBuilder.__init__(self, 
                               startup_path,
                               optNoDownload,
                               optSGDownload,
                               optNoUnpack,
                               optNoGitClone,
                               optLocalGitClone,
                               optNoSupportBuild,
                               optNoBoostBuild,
                               optNoOSGBuild,
                               optNoMSSecure    )


    self.cmakeGen = "Visual Studio 10"

    self.boostAddrOpt = ["address-model=32"]

    return

##############################################
# Win64 Builder
##############################################

class OSGWin64Builder(OSGWinBaseBuilder):

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False):

    self.fallbackPaths = ["C:/Program Files/Microsoft Visual Studio 10.0/VC",
                          "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC",
                          "C:/Program Files/Git/bin",
                          "C:/Program Files (x86)/Git/bin"]

    cmdirs = glob.glob("C:/Program Files*/CMake *")

    for path in cmdirs:
      self.fallbackPaths.append(os.path.join(path, "bin").replace('\\', '/'))

    print "cmd : ", cmdirs

    self.vcvarsarch = "amd64"

    OSGWinBaseBuilder.__init__(self, 
                               startup_path,
                               optNoDownload,
                               optSGDownload,
                               optNoUnpack,
                               optNoGitClone,
                               optLocalGitClone,
                               optNoSupportBuild,
                               optNoBoostBuild,
                               optNoOSGBuild,
                               optNoMSSecure)

    self.boostAddrOpt = ["address-model=64"]

    self.cmakeGen = "Visual Studio 10 Win64"

    return


##############################################
# Unix Base Builder
##############################################

class OSGUnixBaseBuilder(OSGBaseBuilder):

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False):

    OSGBaseBuilder.__init__(self, 
                            startup_path,
                            optNoDownload,
                            optSGDownload,
                            optNoUnpack,
                            optNoGitClone,
                            optLocalGitClone,
                            optNoSupportBuild,
                            optNoBoostBuild,
                            optNoOSGBuild,
                            optNoMSSecure)

    self.cmakeCmd = "cmake"
    self.makeCmd  = "make"
    self.gitCmd   = "git"

    self.cmakeGen = "Unix Makefiles"

    return

  def buildOSGSupport(self):

    if self.nosupportbuild == True:
      return

    OSGBaseBuilder.buildOSGSupport(self)

    os.chdir(self.suppBuild_path)

    mkBldCmd = [self.makeCmd]
    retcode = subprocess.call(mkBldCmd)

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    cmCfgOptCmd = [self.cmakeCmd, "-DCMAKE_BUILD_TYPE:STRING=Debug", "."]
    retcode = subprocess.call(cmCfgOptCmd)

    mkBldCmd = [self.makeCmd]
    retcode = subprocess.call(mkBldCmd)

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    os.chdir(self.startup_path)

  def buildOSGDbg(self):

    if self.noosgbuild == True:
      return

    OSGBaseBuilder.configureOSG(self)

    os.chdir(self.dbgBuild_path)

    mkBldCmd = [self.makeCmd, "OSGAll"]
    retcode = subprocess.call(mkBldCmd)

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    os.chdir(self.startup_path)

  def buildOSGOpt(self):

    if self.noosgbuild == True:
      return

    self.initDir(self.optBuild_path)

    os.chdir(self.optBuild_path)

    cmCfgCmd = ["cmake", 
                "-DOSG_BUILD_DEPENDEND:INTERNAL=true", 
                "-DCMAKE_VERBOSE_MAKEFILE:INTERNAL=true", 
                "-DOSG_REFERENCE_DIR:INTERNAL=" + self.osgBuildRel_path, 
                "-DCMAKE_BUILD_TYPE:STRING=Release", 
                self.osgRel_path]
    print "runnuing ", cmCfgCmd
    retcode = subprocess.call(cmCfgCmd)

    mkBldCmd = [self.makeCmd, "OSGAll"]
    retcode = subprocess.call(mkBldCmd)

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    os.chdir(self.startup_path)

  def buildOpenSG(self):

    if self.noosgbuild == True:
      return

    self.buildOSGDbg()
    self.buildOSGOpt()

##############################################
# Linux Builder
##############################################

class OSGLinuxBuilder(OSGUnixBaseBuilder):

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False):

    OSGUnixBaseBuilder.__init__(self, 
                                startup_path,
                                optNoDownload,
                                optSGDownload,
                                optNoUnpack,
                                optNoGitClone,
                                optLocalGitClone,
                                optNoSupportBuild,
                                optNoBoostBuild,
                                optNoOSGBuild,
                                optNoMSSecure)

    return

##############################################
# OSX Builder
##############################################

class OSGOSXBuilder(OSGUnixBaseBuilder):

  def __init__(self, 
               startup_path,  
               optNoDownload     = False,
               optSGDownload     = False,
               optNoUnpack       = False,
               optNoGitClone     = False,
               optLocalGitClone  = False,
               optNoSupportBuild = False,
               optNoBoostBuild   = False,
               optNoOSGBuild     = False,
               optNoMSSecure     = False):

    OSGUnixBaseBuilder.__init__(self, 
                                startup_path,
                                optNoDownload,
                                optSGDownload,
                                optNoUnpack,
                                optNoGitClone,
                                optLocalGitClone,
                                optNoSupportBuild,
                                optNoBoostBuild,
                                optNoOSGBuild,
                                optNoMSSecure)

    return






builder      = None;

startup_path = os.getcwd()

m_parser = optparse.OptionParser();


m_parser.add_option("-d", 
                    "--no-download",
                    action="store_true",
                    default=False,
                    dest="nodownload",
                    help="no archive download (reuse existing)",
                    metavar="OpenSG");
m_parser.add_option("--sg-download",
                    action="store_true",
                    default=False,
                    dest="sgdownload",
                    help="download from sg mirror",
                    metavar="OpenSG");
m_parser.add_option("-u", 
                    "--no-unpack",
                    action="store_true",
                    default=False,
                    dest="nounpack",
                    help="no archive unpacking (reuse existing), warning download will not run if --no-unpack is set !",
                    metavar="OpenSG");
m_parser.add_option("-g", 
                    "--no-gitclone",
                    action="store_true",
                    default=False,
                    dest="nogitclone",
                    help="no git clone (re use existing repo)",
                    metavar="OpenSG");
m_parser.add_option("-l", 
                    "--local-gitclone",
                    action="store_true",
                    default=False,
                    dest="localgitclone",
                    help="clone from OpenSG.repo in the current directory",
                    metavar="OpenSG");
m_parser.add_option("-s", 
                    "--no-supportbuild",
                    action="store_true",
                    default=False,
                    dest="nosupportbuild",
                    help="no support build (reuse existing)",
                    metavar="OpenSG");
m_parser.add_option("-b", 
                    "--no-boostbuild",
                    action="store_true",
                    default=False,
                    dest="noboostbuild",
                    help="no boost build (just install existing)",
                    metavar="OpenSG");
m_parser.add_option("-o", 
                    "--no-osbbuild",
                    action="store_true",
                    default=False,
                    dest="noosgbuild",
                    help="no osg build (reuse existing)",
                    metavar="OpenSG");

m_parser.add_option("--no-mssecure",
                    action="store_true",
                    default=False,
                    dest="nomssecure",
                    help="disable ms secure/debug settings",
                    metavar="OpenSG");

args = sys.argv[1:];
        
(m_options, m_args) = m_parser.parse_args(args);

print "sys   : ", platform.system()
print "arch  : ", platform.architecture()
print "mach  : ", platform.machine()
print "plat  : ", platform.platform()
print "uname : ", platform.uname()


# ----- defines -----
if(platform.system() == "Microsoft" or platform.system() == "Windows"):
  system = "windows"
  if platform.machine() == "AMD64":
    builder = OSGWin64Builder(startup_path,
                              m_options.nodownload,
                              m_options.sgdownload,
                              m_options.nounpack,
                              m_options.nogitclone,
                              m_options.localgitclone,
                              m_options.nosupportbuild,
                              m_options.noboostbuild,
                              m_options.noosgbuild,
                              m_options.nomssecure)
  else:
    builder = OSGWin32Builder(startup_path,
                              m_options.nodownload,
                              m_options.sgdownload,
                              m_options.nounpack,
                              m_options.nogitclone,
                              m_options.localgitclone,
                              m_options.nosupportbuild,
                              m_options.noboostbuild,
                              m_options.noosgbuild,
                              m_options.nomssecure)
elif(platform.system() == "Linux"):
  system = "unix"
  builder = OSGLinuxBuilder(startup_path,
                            m_options.nodownload,
                            m_options.sgdownload,
                            m_options.nounpack,
                            m_options.nogitclone,
                            m_options.localgitclone,
                            m_options.nosupportbuild,
                            m_options.noboostbuild,
                            m_options.noosgbuild,
                            m_options.nomssecure)
if(platform.system() == "Darwin"):
  system = "unix"
  builder = OSGOSXBuilder(startup_path,
                          m_options.nodownload,
                          m_options.sgdownload,
                          m_options.nounpack,
                          m_options.nogitclone,
                          m_options.localgitclone,
                          m_options.nosupportbuild,
                          m_options.noboostbuild,
                          m_options.noosgbuild,
                          m_options.nomssecure)

builder.dumpOptions()

print "Building OpenSG for %s in %s" % (system, startup_path)

builder.cloneGit()

builder.prepareOSGSupport()

if len(failed_support_libs) != 0:
  print "##########################################################"
  print "the following support downloads/archives contains errors: "

  for var in failed_support_libs:
    print "  ", var

  print "##########################################################"

builder.buildOSGSupport()

builder.prepOSG()

builder.buildOpenSG()
