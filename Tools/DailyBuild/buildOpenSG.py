
import sys,os,subprocess,shutil,platform,time,errno
import urllib, tarfile, zipfile, sys, os, shutil, glob, stat
import commands
import optparse
import fnmatch

common_deps_src = [\
    ("OSGColladaSrcDir", "http://sourceforge.net/projects/collada-dom/files/Collada%20DOM/Collada%20DOM%202.2/Collada%20DOM%202.2.zip/download", "Collada DOM 2.2.zip", "collada-dom"),\
    ("OSGLibMiniSrcDir", "http://stereofx.org/download/mini/MINI-9.8.zip", None, "mini"),\
    ("OSGOpenNurbsSrcDir", "http://files.na.mcneel.com/opennurbs/5.0/2011-02-02/opennurbs_20110202.zip", None, None),\
    ("OSGGLEWSrcDir", "http://sourceforge.net/projects/glew/files/glew/1.7.0/glew-1.7.0.zip/download", None, None)\
  ]

bq_deps_src = [("BOOST_ROOT", "http://sourceforge.net/projects/boost/files/boost/1.44.0/boost_1_44_0.zip/download", None, None), \
               ("BOOST_JAM", "http://sourceforge.net/projects/boost/files/boost-jam/3.1.18/boost-jam-3.1.18-1-ntx86.zip/download", None, None),\
               ("QT_ROOT", "ftp://ftp.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.4.zip", None, None) \
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
               ]

linux_deps_src = [("OSGDoxygenSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/doxygen_r752.tar.gz", None, None) ]
               
common_deps_fhg = [\
    ("OSGColladaSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/Collada%20DOM%202.2.zip", "Collada DOM 2.2.zip", "collada-dom"),\
    ("OSGLibMiniSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/MINI-9.8.zip", None, "mini"),\
    ("OSGOpenNurbsSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/opennurbs_20110202.zip", None, None),\
    ("OSGGLEWSrcDir", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/glew-1.7.0.zip", None, None)\
  ]

bq_deps_fhg = [("BOOST_ROOT", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/boost_1_44_0.zip", None, None), \
               ("BOOST_JAM", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/boost-jam-3.1.18-1-ntx86.zip", None, None),\
               ("QT_ROOT", "http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support//qt-everywhere-opensource-src-4.7.4.zip", None, None), \
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
               ]

linux_deps_fhg = linux_deps_src

failed_support_libs = []

##############################################
# Base Builder
##############################################

class OSGBaseBuilder:

  def __init__(self, 
               startup_path,  
               oOptions    ,
               subDir      = None ):

    if subDir == None:
      subDir = ""

    extraUp = ""

    if subDir != "":
      extraUp = ".."

    self.startup_path        = startup_path
    self.download_path       = os.path.join(self.startup_path, "Downloads")
    self.unpack_path         = os.path.join(self.startup_path, "Unpack")
    self.build_path          = os.path.join(self.startup_path, subDir)
    self.suppBuild_path      = os.path.join(self.startup_path, subDir, "OpenSG.Support.build")
    self.suppInst_path       = os.path.join(self.startup_path, subDir, "OpenSG.Support.install").replace('\\', '/')

    self.osg_path            = os.path.join(self.startup_path, "OpenSG")
    self.dbgBuild_path       = os.path.join(self.startup_path, subDir, "OpenSG.build")
    self.optBuild_path       = os.path.join(self.startup_path, subDir, "OpenSG.build.opt")
    self.osgInst_path        = os.path.join(self.startup_path, subDir, "OpenSG.install").replace('\\', '/')

    self.osgaddons_path      = os.path.join(self.startup_path, "OSGAddOns")
    self.dbgBuildAddOns_path = os.path.join(self.startup_path, subDir, "OSGAddOns.build")
    self.optBuildAddOns_path = os.path.join(self.startup_path, subDir, "OSGAddOns.build.opt")
    self.osgAddonsInst_path  = os.path.join(self.startup_path, subDir, "OSGAddOns.install").replace('\\', '/')

    self.osgRel_path         = os.path.join("..", extraUp, "OpenSG")
    self.osgBuildRel_path    = os.path.join("..",          "OpenSG.build")
    self.suppRel_path        = os.path.join("..", extraUp, "OpenSG", "Support")

    self.osgAddOnsRel_path      = os.path.join("..", extraUp, "OSGAddOns")
    self.osgAddOnsBuildRel_path = os.path.join("..",          "OSGAddOns.build")

    self.buildSubDir      = subDir

    self.noSuppDirInit    = None

    self.boostroot_path   = None
    self.boostjam_path    = None
    self.boostjam         = None

    self.qtroot_path      = None
    self.qtsrc_path       = None

    self.cmSuppArchFile   = os.path.join(self.unpack_path,    "CMakeSupportArchs.txt")
    self.cmSupportFile    = os.path.join(self.osg_path,       "CMakeSupport.txt")
    self.cmOSGFile        = os.path.join(self.osg_path,       "CMakeOSG.txt")
    self.cmOSGAddOnsFile  = os.path.join(self.osgaddons_path, "CMakeOSGAddOns.txt")

    self.nodownload     = oOptions.nodownload     # optNoDownload
    self.sgdownload     = oOptions.sgdownload     # optSGDownload
    self.nounpack       = oOptions.nounpack       # optNoUnpack
    self.nogitclone     = oOptions.nogitclone     # optNoGitClone
    self.localgitclone  = oOptions.localgitclone  # optLocalGitClone
    self.updatelocalgit = oOptions.updatelocalgit

    self.nosupportbuild = oOptions.nosupportbuild # optNoSupportBuild
    self.noboostbuild   = oOptions.noboostbuild   # optNoBoostBuild
    self.noqtbuild      = oOptions.noqtbuild      # optNoQtBuild
    self.bqonly         = oOptions.bqonly
    self.noosgbuild     = oOptions.noosgbuild     # optNoOSGBuild
    self.nomssecure     = oOptions.nomssecure     # optNoMSSecure

    self.nopython       = oOptions.nopython 
    self.debugonly      = oOptions.debugonly
    self.releaseonly    = oOptions.releaseonly

    self.nobuildaddons  = oOptions.noaddonsbuild    
    self.addonswithosg  = oOptions.instaddonswithosg

    self.noSuppDirInit  = oOptions.nosuppdirinit
    self.useVS2008      = oOptions.useVS2008


    self.cmakeCmd       = None
    self.makeCmd        = None

    self.vcvars         = None

    self.gitCmd         = None

    if self.sgdownload == True:
      self.common_deps = common_deps_fhg
      self.bq_deps     = bq_deps_fhg
      self.win_deps    = win_deps_fhg
      self.linux_deps  = linux_deps_fhg
    else:
      self.common_deps = common_deps_src
      self.bq_deps     = bq_deps_src
      self.win_deps    = win_deps_src
      self.linux_deps  = linux_deps_src

    if self.buildSubDir != None and self.buildSubDir != "" and not os.path.exists(self.buildSubDir):
      os.mkdir(self.buildSubDir)

    return

  def openLog(self):
    
    if os.path.exists("log.txt") == True:
      self.logOut = file("log.txt", "a")
    else:
      self.logOut = file("log.txt", "w")
   

  def closeLog(self):
    self.logOut.close()

  def exitOne(self):
      self.closeLog()
      sys.exit(1)

  def handleRetCode(self, rc, info):

    if rc != 0:
      print "%-27s : [Failed]" % info
      self.logOut.write("%-27s : [Failed]\n" % info)
      self.logOut.flush()
      os.fsync(self.logOut.fileno())
      self.exitOne()
    else:
      print "%-27s : [Ok]" % info
      self.logOut.write("%-27s : [Ok]\n" % info)
      self.logOut.flush()
      os.fsync(self.logOut.fileno())

  def dumpOptions(self):

    print "download             : ", not self.nodownload
    print "sgdownload           : ", self.sgdownload

    print "unpack               : ", not self.nounpack

    print "gitclone             : ", not self.nogitclone
    print "localgitclone        : ", self.localgitclone
    print "updatelocalgit       : ", self.updatelocalgit
    print "support build        : ", not self.nosupportbuild

    print "boost build          : ", not self.noboostbuild
    print "qt build             : ", not self.noqtbuild
    print "bq build             : ", self.bqonly

    print "osg build            : ", not self.noosgbuild
    print "osg addons build     : ", not self.nobuildaddons
    print "inst addons with osg : ", self.addonswithosg
    print "ms secure            : ", self.nomssecure
    print "vs2008               : ", self.useVS2008

    print "python               : ", not self.nopython
    print "debug only           : ", self.debugonly
    print "release only         : ", self.releaseonly

    print "build subdir         : ", self.buildSubDir
    print "No SuppDir init      : ", self.noSuppDirInit

    print "build                : ", self.build_path
    print "supp.build           : ", self.suppBuild_path
    print "supp.inst            : ", self.suppInst_path
    
    print "osg.dbg.build        : ", self.dbgBuild_path
    print "osg.opt.build        : ", self.optBuild_path
    print "osg.install          : ", self.osgInst_path


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

  def removeTree(self, dirname):

    if os.path.isdir(dirname):
      shutil.rmtree(dirname)

  def initDir(self, dirname, createDir = True):

    print "init dir ", dirname

#    if os.path.isdir(dirname):
#      shutil.rmtree(dirname)
    self.removeTree(dirname)

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

#            if os.path.exists(dir):
#              shutil.rmtree(dir)
            self.removeTree(dir)

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
        self.closeLog()
        self.exitOne()

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

      if self.sgdownload == True:
        try:
          self.getUrl("http://opensg.fraunhofer.sg/user/gerrit/OpenSG.Support/wake_up_server.txt", "wake_up_server.txt")
        except:
          print "don't care"

        if os.path.exists("wake_up_server.txt") == True:
          os.remove("wake_up_server.txt")

      if self.bqonly == False:
        self.prepareArchives(cmSupportOut, self.common_deps)

      if system == "windows":
        if self.bqonly == False:
          self.prepareArchives(cmSupportOut, self.win_deps)

        self.prepareArchives(cmSupportOut, self.bq_deps)

      if system == "unix":
        self.prepareArchives(cmSupportOut, self.linux_deps)

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

    if self.nogitclone == True:
      return


    ## OpenSG

    self.initDir("OpenSG", False)

    if self.localgitclone == False:
      gitCloneCmd = [self.gitCmd, "clone", "git://opensg.git.sourceforge.net/gitroot/opensg/opensg", "OpenSG"]
    else:

      if self.updatelocalgit == True:

        os.chdir("OpenSG.repo")


        gitCmd = [self.gitCmd, "fetch"]

        retcode = subprocess.call(gitCmd)

        self.handleRetCode(retcode, "update local fetch")


        gitCmd = [self.gitCmd, "pull", ".", "remotes/origin/master"]

        retcode = subprocess.call(gitCmd)

        self.handleRetCode(retcode, "update local pull")

      
        os.chdir(self.startup_path)


      gitCloneCmd = [self.gitCmd, "clone", "OpenSG.repo", "OpenSG"]


    retcode = subprocess.call(gitCloneCmd)

    self.handleRetCode(retcode, "Cloning git")

    ## OSGAddOne

    self.initDir("OSGAddOns", False)

    if self.localgitclone == False:
      gitCloneCmd = [self.gitCmd, "clone", "git@github.com:vossg/OSGAddOnsGV.git", "OSGAddOns"]
    else:

      if self.updatelocalgit == True:

        os.chdir("OSGAddOns.repo")


        gitCmd = [self.gitCmd, "fetch"]

        retcode = subprocess.call(gitCmd)

        self.handleRetCode(retcode, "update local fetch")


        gitCmd = [self.gitCmd, "pull", ".", "remotes/origin/master"]

        retcode = subprocess.call(gitCmd)

        self.handleRetCode(retcode, "update local pull")

      
        os.chdir(self.startup_path)


      gitCloneCmd = [self.gitCmd, "clone", "OSGAddOns.repo", "OSGAddOns"]

    retcode = subprocess.call(gitCloneCmd)

    self.handleRetCode(retcode, "Cloning OSGAddOns git")

  def buildBoost(self):

    print "Building boost ...."
    return

  def buildQt(self):

    print "Building qt ...."
    return

  def buildOSGSupport(self):

    if self.noSuppDirInit == False:
      self.initDir(self.suppBuild_path)
      self.initDir(self.suppInst_path)

    if system == "windows":
      self.buildBoost()

    if system == "windows":
      self.buildQt()

    if self.bqonly == True:
      return

    os.chdir(self.suppBuild_path)

    cmCfgCmd = [self.cmakeCmd,
                "-G",
                self.cmakeGen,
                "-C", 
                self.cmSupportFile, 
                self.suppRel_path]

    print "Supp cmake : ", cmCfgCmd

    retcode = subprocess.call(cmCfgCmd)

    self.handleRetCode(retcode, "Support Initial CMake")

    os.chdir(self.startup_path)



  def prepOSG(self):

    if self.noosgbuild == False:
      self.initDir(self.osgInst_path)

#    if system == "windows":
#      self.checkBoostPath()

    cmOSGOut = file(self.cmOSGFile, "w")
    cmOSGOut.write("# OSG libs defines\n\n")
    cmOSGOut.write('SET(CMAKE_INSTALL_PREFIX "%s" CACHE PATH "")\n' % self.osgInst_path)
    cmOSGOut.write('SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)\n')

    if self.vcvars != None:
      cmOSGOut.write('SET(BOOST_ROOT "%s" CACHE PATH "" FORCE)\n' % self.suppInst_path)
      cmOSGOut.write('SET(QT_QMAKE_EXECUTABLE "%s/qt/bin/qmake.exe" CACHE FILEPATH "" FORCE)\n' % self.suppInst_path)
    
    cmOSGOut.write('SET(OSG_USE_OSGSUPPORT_LIBS     ON  CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_SUPPORT_ROOT "%s" CACHE PATH "")\n' % self.suppInst_path)
    cmOSGOut.write('SET(OSG_USE_STATIC_SUPPORT_LIBS OFF CACHE BOOL "")\n')

    cmOSGOut.write('SET(OSGBUILD_EXAMPLES_SIMPLE   ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGBUILD_EXAMPLES_ADVANCED ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGBUILD_EXAMPLES_TUTORIAL ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_INSTALL_EXAMPLES       ON CACHE BOOL "")\n')

    cmOSGOut.write('SET(OSG_DOXY_DOC_TYPE Developer CACHE STRING "" FORCE)\n\n')

    cmOSGOut.write('SET(OSG_ENABLE_PAR_PARTITION_DRAWING ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_ENABLE_DEFAULT_READONLY_CHANGELIST ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSG_DISABLE_SOURCE_GROUPS ON CACHE BOOL "")\n\n')

    cmOSGOut.write('SET(OSGEXCLUDE_EXAMPLES_ADVANCED_FROM_ALL ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGEXCLUDE_EXAMPLES_SIMPLE_FROM_ALL   ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGEXCLUDE_TESTS_FROM_ALL             ON CACHE BOOL "")\n')
    cmOSGOut.write('SET(OSGEXCLUDE_UNITTESTS_FROM_ALL         ON CACHE BOOL "")\n\n')

    if self.nopython == False:
      cmOSGOut.write('# OpenSG Python\n\n')

      cmOSGOut.write('SET(OSG_PYTHON_MODULE_BASE_DIR "%s/Bindings/Python" CACHE PATH "" FORCE)\n\n' % self.osgaddons_path)
      cmOSGOut.write('SET(OSGBUILD_PYTHON_BINDINGS ON CACHE BOOL "" FORCE)\n\n')

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

    self.handleRetCode(retcode, "OSG Initial CMake")

    os.chdir(self.startup_path)

  def reconfigureOSG(self, changeDir = False):

    if changeDir == True:
      os.chdir(self.dbgBuild_path)

    cmCfgCmd = [self.cmakeCmd, "."]

    print "runnuing ", cmCfgCmd

    retcode = subprocess.call(cmCfgCmd)

    self.handleRetCode(retcode, "OSG cmake . Run")

    if changeDir == True:
      os.chdir(self.startup_path)

  def configureOSGAddOns(self, Variant = "Debug"):

    if Variant == "Debug":
      workDir = self.dbgBuildAddOns_path
    elif Variant == "Release":
      workDir = self.optBuildAddOns_path
    else:
      sys.exit(1);

    self.initDir(workDir)

    os.chdir(workDir)

    cmCfgCmd = [self.cmakeCmd,
                "-G",
                self.cmakeGen,
                "-C", 
                self.cmOSGAddOnsFile, 
                ("-DCMAKE_BUILD_TYPE:STRING=%s" % Variant), 
                self.osgAddOnsRel_path]

    print "runnuing ", cmCfgCmd

    retcode = subprocess.call(cmCfgCmd)

    self.handleRetCode(retcode, "OSG Initial CMake")

    os.chdir(self.startup_path)

  def prepOSGAddOns(self):

    if self.nobuildaddons == False or self.addonswithosg == False:
      self.initDir(self.osgAddonsInst_path)

    cmOSGAddOnsOut = file(self.cmOSGAddOnsFile, "w")
    cmOSGAddOnsOut.write("# OSG AddOns libs defines\n\n")

    cmOSGAddOnsOut.write('SET(OpenSG_DIR "%s" CACHE PATH "" FORCE)\n\n' % self.osgInst_path)
    cmOSGAddOnsOut.write('SET(OSG_BUILD_ACTIVE TRUE CACHE BOOL "" FORCE)\n\n')

    cmOSGAddOnsOut.write('# OpenSG Support\n\n')

    cmOSGAddOnsOut.write('# Initialized from OpenSG install, change only if really needed\n')
    cmOSGAddOnsOut.write('#SET(OSG_SUPPORT_ROOT "" CACHE PATH "" FORCE)\n\n')

    cmOSGAddOnsOut.write('#SET(OSG_USE_OSGSUPPORT_LIBS TRUE CACHE BOOL "" FORCE)\n\n')

    if self.nopython == False:
      cmOSGAddOnsOut.write('# OpenSG Python\n\n')

      cmOSGAddOnsOut.write('SET(OSG_PYTHON_MODULE_BASE_DIR "%s/Bindings/Python" CACHE PATH "" FORCE)\n\n' % self.osgaddons_path)
      cmOSGAddOnsOut.write('SET(OSGBUILD_PYTHON_BINDINGS ON CACHE BOOL "" FORCE)\n\n')

    cmOSGAddOnsOut.write('# If OpenSG was build with CUDA enabled\n\n')

    cmOSGAddOnsOut.write('#SET(CUDA_TOOLKIT_ROOT_DIR "" CACHE PATH "" FORCE)\n\n')

    cmOSGAddOnsOut.write('#SET(OSG_ENABLE_CUDA ON CACHE BOOL "Build OpenSG with CUDA support"  FORCE)\n\n')

    cmOSGAddOnsOut.write('# cmake\n\n')

    cmOSGAddOnsOut.write('SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)\n')

    if self.addonswithosg == False:
      cmOSGAddOnsOut.write('SET(CMAKE_INSTALL_PREFIX "%s" CACHE PATH "" FORCE)\n\n' % self.osgAddonsInst_path)
    else:
      cmOSGAddOnsOut.write('SET(CMAKE_INSTALL_PREFIX "%s" CACHE PATH "")\n' % self.osgInst_path)

    cmOSGAddOnsOut.write('IF(WIN32)\n')
    cmOSGAddOnsOut.write('  SET(OSG_ENABLE_FCD2CODE OFF CACHE BOOL "" FORCE)\n')
    cmOSGAddOnsOut.write('ENDIF()\n\n')

    cmOSGAddOnsOut.write('# Sofa\n\n')

    cmOSGAddOnsOut.write('#SET(SOFA_ROOT "" CACHE PATH "" FORCE)\n\n')

    cmOSGAddOnsOut.close()

##############################################
# Windows Base Builder
##############################################

class OSGWinBaseBuilder(OSGBaseBuilder):

  def __init__(self, 
               startup_path,  
               oOptions    ):

    buildSubDir = "MSDefaults"

    if oOptions.nomssecure == True:
      buildSubDir = "NoMSSec"

##32    self.fallbackPaths = ["C:/Program Files/Microsoft Visual Studio 10.0/VC",
#                          "C:/Program Files/Git/bin"]

##32    cmdirs = glob.glob("C:/Program Files/CMake *")

    if oOptions.useVS2008 == True:
      self.fallbackPaths = ["C:/Program Files/Microsoft Visual Studio 9.0/VC",
                            "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC",
                            "C:/Program Files/Git/bin",
                            "C:/Program Files (x86)/Git/bin"]

      self.boostToolset = "toolset=msvc-9.0"
    else:
      self.fallbackPaths = ["C:/Program Files/Microsoft Visual Studio 10.0/VC",
                            "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC",
                            "C:/Program Files/Git/bin",
                            "C:/Program Files (x86)/Git/bin"]

      self.boostToolset = "toolset=msvc-10.0"
      
    cmdirs = glob.glob("C:/Program Files*/CMake *")

    for path in cmdirs:
      self.fallbackPaths.append(os.path.join(path, "bin").replace('\\', '/'))

    print "cmd : ", cmdirs


    OSGBaseBuilder.__init__(self, 
                            startup_path,
                            oOptions,
                            buildSubDir )

    #"-d+2",
    #"-q",
    self.boostCommonOpts = ["-d+1",
                            "--without-mpi",
                            "--stagedir=./stage." + self.buildSubDir,
                            "--build-dir=./bin.v2." + self.buildSubDir,
                            self.boostToolset,
                            "variant=debug,release",
                            "threading=multi",
                            "link=shared,static",
                            "runtime-link=shared"]

#    if self.vcvarsarch != None and self.vcvarsarch == "amd64":
#      # boost.python fails to link on win64 (1.44), have to try a later release, was a python problem
#      self.boostCommonOpts.append("--without-python")

    self.boostAddrOpt    = None

    self.boostMSDefines  = ["define=_CRT_SECURE_NO_DEPRECATE",
                            "define=_CRT_SECURE_NO_WARNINGS",
                            "define=_CRT_NONSTDC_NO_DEPRECATE",
                            "define=_SECURE_SCL=0",
                            "define=_SCL_SECURE_NO_WARNINGS",
                            "define=_SCL_SECURE_NO_DEPRECATE",
                            "define=_HAS_ITERATOR_DEBUGGING=0" ]

    self.qtPlatform      = None


    self.cmakeCmd  = self.which("cmake.exe")
    self.vcvars    = self.which("vcvarsall.bat")
    self.gitCmd    = self.which("git.exe")

    print "cm  : ", self.cmakeCmd
    print "vcv : ", self.vcvars
    print "git : ", self.gitCmd 

    if self.cmakeCmd == None:
      print "Error could not find cmake"
      self.exitOne()

    if self.vcvars == None:
      print "Error could not find vcvars.bat"
      self.exitOne()

    if self.gitCmd == None:
      print "Error could not find git"
      self.exitOne()

    return

  def handleRemoveReadonly(self, func, path, exc):
    excvalue = exc[1]

    if func in (os.rmdir, os.remove) and excvalue.errno == errno.EACCES:
      # ensure parent directory is writeable too
      pardir = os.path.abspath(os.path.join(path, os.path.pardir))

      if not os.access(pardir, os.W_OK):
        os.chmod(pardir, stat.S_IRWXU| stat.S_IRWXG| stat.S_IRWXO)

      os.chmod(path, stat.S_IRWXU| stat.S_IRWXG| stat.S_IRWXO) # 0777
      func(path)
    else:
      raise

  def removeTree(self, dirname):

    if os.path.isdir(dirname):
      shutil.rmtree(dirname, ignore_errors = False, onerror = self.handleRemoveReadonly)
#      shutil.rmtree(dirname)

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
      self.exitOne()

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

    self.handleRetCode(retcode, "Boost Build")

    boostInstallCmd = []

    boostInstallCmd.extend(boostBaseCmd)

    boostInstallCmd.extend(["--prefix=" + self.suppInst_path])
    boostInstallCmd.extend(["install"])

    print "boost install cmd: ", boostInstallCmd

    if self.noboostbuild == False:
      retcode = subprocess.call(boostInstallCmd)

      self.handleRetCode(retcode, "Boost Install")

    binPath = os.path.join(self.suppInst_path, "bin")
    libPath = os.path.join(self.suppInst_path, "lib")

    if self.noboostbuild == False:
      os.mkdir(binPath);

      for file in os.listdir(libPath):
        if fnmatch.fnmatch(file, '*.dll'):
          srcFile = os.path.join(libPath, file)
          dstFile = os.path.join(binPath, file)
          shutil.move(srcFile, dstFile)

    os.chdir(startup_path)

    return
                   
  def checkQtPath(self):

    if self.qtsrc_path == None:
      files = glob.glob(os.path.join(self.unpack_path, "qt-*"))
      print "br : ", files
      if len(files) == 1:
        self.qtsrc_path = files[0].replace('\\', '/')

    self.qtroot_path = os.path.join(self.build_path, "qt.build").replace('\\', '/')
      
    print "  qt src  path   ", self.qtsrc_path
    print "  qt root path   ", self.qtroot_path

  def buildQt(self):
    print "win build qt"

    self.checkQtPath()

    self.initDir(self.qtroot_path, False)

    if not os.path.exists(self.qtroot_path):
      print "copy qt"

      if self.noqtbuild == False:
        shutil.copytree(self.qtsrc_path, self.qtroot_path);
      else:
        os.mkdir(self.qtroot_path)

    os.chdir(self.qtroot_path)

    qtBaseCmd = [self.vcvars, self.vcvarsarch, "&"]

    qtConfigureCmd = []
    qtConfigureCmd.extend(qtBaseCmd)

    qtConfigureCmd.extend(["configure",
                           "-opensource",
                           "-platform", self.qtPlatform,
                           "-nomake", "examples",
                           "-nomake", "demos",
                           "-nomake", "docs",
                           "-debug-and-release",
                           "-mmx",
                           "-sse",
                           "-sse2",
                           "-plugin-sql-sqlite",
                           "-no-dbus",
                           "-no-phonon",
                           "-no-phonon-backend",
                           "-no-webkit",
                           "-no-scripttools"])
    
    if self.nomssecure == True:
      qtConfigureCmd.extend(["-D", "_CRT_SECURE_NO_DEPRECATE",
                             "-D", "_CRT_SECURE_NO_WARNINGS",
                             "-D", "_CRT_NONSTDC_NO_DEPRECATE",
                             "-D", "_SECURE_SCL=0",
                             "-D", "_SCL_SECURE_NO_WARNINGS",
                             "-D", "_SCL_SECURE_NO_DEPRECATE",
                             "-D", "_HAS_ITERATOR_DEBUGGING=0"])
              
                   
    qtConfigureCmd.extend(["<",
                           "yanswer"])

    print "qt configure : ", qtConfigureCmd

    qtCfgAnswer = file("yanswer", "w")
    qtCfgAnswer.write("y")
    qtCfgAnswer.close()

    
    if self.noqtbuild == False:
      retcode = subprocess.call(qtConfigureCmd)

      self.handleRetCode(retcode, "Qt Configure")

    qtBuildCmd = []
    qtBuildCmd.extend(qtBaseCmd)
    qtBuildCmd.extend(["nmake"])

    print "qt build : ", qtBuildCmd

    if self.noqtbuild == False:
      retcode = subprocess.call(qtBuildCmd)

      self.handleRetCode(retcode, "Qt Build")

    qtInstallBat = file("qtinstall.bat", "w")

    (unpackDrive, unpackTail) = os.path.splitdrive(self.unpack_path);
    (qtDrive,     qtTail    ) = os.path.splitdrive(self.qtroot_path);

    qtSetInstRoot = "set INSTALL_ROOT=";
    qtSetInstRoot += unpackTail;
    qtSetInstRoot += "\\qt.tmpinstall\n";

    print "foo ", qtSetInstRoot;

    qtInstallBat.write(qtSetInstRoot)
    qtInstallBat.write("\n")
    qtInstallBat.write("nmake install\n\n")
    qtInstallBat.close()

    qtInstallCmd = []
    qtInstallCmd.extend(qtBaseCmd)
    qtInstallCmd.extend(["qtinstall.bat"])

    print "qt install tmp : ", qtInstallCmd

    if self.noqtbuild == False:
      retcode = subprocess.call(qtInstallCmd)
      self.handleRetCode(retcode, "Qt Install")

    qtTmpInstallPath    = self.unpack_path + "\\qt.tmpinstall";
    qtTmpInstallPath   += qtTail
    qtFinalInstallPath  = self.suppInst_path + "/qt"

    print "foo ", qtTmpInstallPath.replace('\\', '/')
    print "bar ", qtFinalInstallPath

    if self.noqtbuild == False:
      shutil.move(qtTmpInstallPath.replace('\\', '/'), qtFinalInstallPath)

    qtLocalConfigFile = qtFinalInstallPath + "/bin/qt.conf"

    if self.noqtbuild == False:
      qtLocalConf = file(qtLocalConfigFile, "w")

      qtLocalConf.write("[Paths]\n");
      qtLocalConf.write("Prefix=\n");
      qtLocalConf.write("Documentation=../doc\n");
      qtLocalConf.write("Headers=../include\n");
      qtLocalConf.write("Libraries=../lib\n");
      qtLocalConf.write("Binaries=\n");
      qtLocalConf.write("Plugins=../plugins\n");
      qtLocalConf.write("Data=..\n");
      qtLocalConf.write("Translations=../translations\n");
      qtLocalConf.write("Settings=../etc\n");
      qtLocalConf.write("Examples=../examples\n");
      qtLocalConf.write("Demos=../demos\n");

      qtLocalConf.close();

    os.chdir(startup_path)

  def buildOSGSupport(self):

    if self.nosupportbuild == True:
      return

    OSGBaseBuilder.buildOSGSupport(self)

    if self.bqonly == True:
      return

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

    self.handleRetCode(retcode, "Build OSG Support Debug")

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

    self.handleRetCode(retcode, "Build OSG Support Release")

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

    self.handleRetCode(retcode, "Install OSG Support Debug")

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

    self.handleRetCode(retcode, "Install OSG Support Release")

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

    self.handleRetCode(retcode, "Build OSG All")

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

    self.handleRetCode(retcode, "Install OSG All")

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
               oOptions    ):

    self.vcvarsarch = "x86"

    OSGWinBaseBuilder.__init__(self, 
                               startup_path,
                               oOptions    )

    if self.useVS2008 == True:
      self.cmakeGen = "Visual Studio 2008 9"
      self.qtPlatform   = "win32-msvc2008"
    else:
      self.cmakeGen = "Visual Studio 10"
      self.qtPlatform   = "win32-msvc2010"

    self.boostAddrOpt = ["address-model=32"]


    print "Build for Win32"

    return

##############################################
# Win64 Builder
##############################################

class OSGWin64Builder(OSGWinBaseBuilder):

  def __init__(self, 
               startup_path,  
               oOptions    ):

    self.vcvarsarch = "amd64"

    OSGWinBaseBuilder.__init__(self, 
                               startup_path,
                               oOptions    )

    self.boostAddrOpt = ["address-model=64"]

    if self.useVS2008 == True:
      self.cmakeGen = "Visual Studio 9 2008 Win64"
      self.qtPlatform   = "win32-msvc2008"
    else:
      self.cmakeGen = "Visual Studio 10 Win64"
      self.qtPlatform   = "win32-msvc2010"


    print "Build for Win64"

    return


##############################################
# Unix Base Builder
##############################################

class OSGUnixBaseBuilder(OSGBaseBuilder):

  def __init__(self, 
               startup_path,  
               oOptions    ):

    OSGBaseBuilder.__init__(self, 
                            startup_path,
                            oOptions    )

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

    self.handleRetCode(retcode, "Build OSG Support Release")

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    self.handleRetCode(retcode, "Install OSG Support Release")

    cmCfgOptCmd = [self.cmakeCmd, "-DCMAKE_BUILD_TYPE:STRING=Debug", "."]
    retcode = subprocess.call(cmCfgOptCmd)

    self.handleRetCode(retcode, "Configure OSG Support Debug")

    mkBldCmd = [self.makeCmd]
    retcode = subprocess.call(mkBldCmd)

    self.handleRetCode(retcode, "Build OSG Support Debug")

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    self.handleRetCode(retcode, "Install OSG Support Debug")

    os.chdir(self.startup_path)

  def buildOSGDbg(self):

    if self.noosgbuild == True:
      return

    OSGBaseBuilder.configureOSG(self)

    os.chdir(self.dbgBuild_path)

    mkBldCmd = [self.makeCmd, "OSGAll"]
    retcode = subprocess.call(mkBldCmd)

    self.handleRetCode(retcode, "Build OSG Debug")

    if self.nopython == False:
      mkBldCmd = [self.makeCmd, "OSGPy"]
      print "run : ", mkBldCmd

      retcode = subprocess.call(mkBldCmd)

      self.handleRetCode(retcode, "Build OSG Py Debug")

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    self.handleRetCode(retcode, "Install OSG Debug")

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

    self.handleRetCode(retcode, "Configure OSG Release")

    mkBldCmd = [self.makeCmd, "OSGAll"]
    retcode = subprocess.call(mkBldCmd)

    self.handleRetCode(retcode, "Build OSG Release")

    if self.nopython == False:
      mkBldCmd = [self.makeCmd, "OSGPy"]
      print "run : ", mkBldCmd

      retcode = subprocess.call(mkBldCmd)

      self.handleRetCode(retcode, "Build OSG Py Relase")

    mkInstCmd = [self.makeCmd, "install"]
    retcode = subprocess.call(mkInstCmd)

    self.handleRetCode(retcode, "Install OSG Release")

    os.chdir(self.startup_path)

  def buildOpenSG(self):

    if self.noosgbuild == True:
      return

    if self.releaseonly == False:
      self.buildOSGDbg()

    if self.debugonly == False:
      self.buildOSGOpt()

  def buildOSGAddOnsDbg(self):

    if self.nobuildaddons == True:
      return

    OSGBaseBuilder.configureOSGAddOns(self)

    os.chdir(self.dbgBuildAddOns_path)

    mkBldCmd = [self.makeCmd, "OSGAll"]
    print "run : ", mkBldCmd

    retcode = subprocess.call(mkBldCmd)

    self.handleRetCode(retcode, "Build OSGAddOns Debug")

    if self.nopython == False:
      mkBldCmd = [self.makeCmd, "OSGPy"]
      print "run : ", mkBldCmd

      retcode = subprocess.call(mkBldCmd)

      self.handleRetCode(retcode, "Build OSGAddOns Py Debug")

    mkInstCmd = [self.makeCmd, "install"]
    print "run : ", mkInstCmd

    retcode = subprocess.call(mkInstCmd)

    self.handleRetCode(retcode, "Install OSGAddOns Debug")

    os.chdir(self.startup_path)

  def buildOSGAddOnsOpt(self):

    if self.nobuildaddons == True:
      return

    OSGBaseBuilder.configureOSGAddOns(self, "Release")

    os.chdir(self.optBuildAddOns_path)

    mkBldCmd = [self.makeCmd, "OSGAll"]
    print "run : ", mkBldCmd
    retcode = subprocess.call(mkBldCmd)

    self.handleRetCode(retcode, "Build OSGAddOns Release")

    if self.nopython == False:
      mkBldCmd = [self.makeCmd, "OSGPy"]
      print "run : ", mkBldCmd
      retcode = subprocess.call(mkBldCmd)

      self.handleRetCode(retcode, "Build OSGAddOns Py Release")

    mkInstCmd = [self.makeCmd, "install"]
    print "run : ", mkInstCmd
    retcode = subprocess.call(mkInstCmd)

    self.handleRetCode(retcode, "Install OSG Release")

    os.chdir(self.startup_path)



  def buildOSGAddOns(self):

    if self.nobuildaddons == True:
      return

    if self.releaseonly == False:
      self.buildOSGAddOnsDbg()

    if self.debugonly == False:
      self.buildOSGAddOnsOpt()

##############################################
# Linux Builder
##############################################

class OSGLinuxBuilder(OSGUnixBaseBuilder):

  def __init__(self, 
               startup_path,  
               oOptions    ):

    OSGUnixBaseBuilder.__init__(self, 
                                startup_path,
                                oOptions    )

    print "Build for Linux"

    return

##############################################
# OSX Builder
##############################################

class OSGOSXBuilder(OSGUnixBaseBuilder):

  def __init__(self, 
               startup_path,  
               oOptions    ):

    OSGUnixBaseBuilder.__init__(self, 
                                startup_path,
                                oOptions    )

    print "Build for OSX"

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
m_parser.add_option("--update-localgit",
                    action="store_true",
                    default=False,
                    dest="updatelocalgit",
                    help="update local git repo before cloning",
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
m_parser.add_option("-q", 
                    "--no-qtbuild",
                    action="store_true",
                    default=False,
                    dest="noqtbuild",
                    help="no qt build (just install existing)",
                    metavar="OpenSG");
m_parser.add_option("--bq-only",
                    action="store_true",
                    default=False,
                    dest="bqonly",
                    help="only build boost and qt",
                    metavar="OpenSG");
m_parser.add_option("-o", 
                    "--no-osbbuild",
                    action="store_true",
                    default=False,
                    dest="noosgbuild",
                    help="no osg build (reuse existing)",
                    metavar="OpenSG");

m_parser.add_option("-a", 
                    "--no-addonsbuild",
                    action="store_true",
                    default=False,
                    dest="noaddonsbuild",
                    help="no osg addons build",
                    metavar="OpenSG");

m_parser.add_option("--addonWithOpenSGInst",
                    action="store_true",
                    default=False,
                    dest="instaddonswithosg",
                    help="install AddOns with OpenSG",
                    metavar="OpenSG");

m_parser.add_option("-p", 
                    "--no-python",
                    action="store_true",
                    default=False,
                    dest="nopython",
                    help="no osg python bindings build",
                    metavar="OpenSG");

m_parser.add_option("--debug",
                    action="store_true",
                    default=False,
                    dest="debugonly",
                    help="build only debug",
                    metavar="OpenSG");

m_parser.add_option("--release",
                    action="store_true",
                    default=False,
                    dest="releaseonly",
                    help="build only release",
                    metavar="OpenSG");

m_parser.add_option("--no-mssecure",
                    action="store_true",
                    default=False,
                    dest="nomssecure",
                    help="disable ms secure/debug settings",
                    metavar="OpenSG");

m_parser.add_option("--force-win32",
                    action="store_true",
                    default=False,
                    dest="forceWin32",
                    help="force win32 build on win64 machines",
                    metavar="OpenSG");

m_parser.add_option("--no-suppdirinit",
                    action="store_true",
                    default=False,
                    dest="nosuppdirinit",
                    help="do not clear and init Support build/inst subdirs",
                    metavar="OpenSG");

m_parser.add_option("--vs2008",
                    action="store_true",
                    default=False,
                    dest="useVS2008",
                    help="use vs2008",
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
  if platform.machine() == "AMD64" and not m_options.forceWin32 :
    builder = OSGWin64Builder(startup_path,
                              m_options   )
  else:
    builder = OSGWin32Builder(startup_path,
                              m_options   )

elif(platform.system() == "Linux"):

  system = "unix"
  builder = OSGLinuxBuilder(startup_path,
                            m_options   )

if(platform.system() == "Darwin"):

  system = "unix"
  builder = OSGOSXBuilder(startup_path,
                          m_options   )

builder.dumpOptions()

print "Building OpenSG for %s in %s" % (system, startup_path)

builder.openLog()

builder.cloneGit()

builder.prepareOSGSupport()

if len(failed_support_libs) != 0:
  print "##########################################################"
  print "the following support downloads/archives contains errors: "

  for var in failed_support_libs:
    print "  ", var

  print "##########################################################"

  builder.handleRetCode(1, "Prepare SupportArchives")

builder.handleRetCode(0, "Prepare SupportArchives")

builder.buildOSGSupport()

builder.prepOSG()

builder.buildOpenSG()

builder.prepOSGAddOns()

builder.buildOSGAddOns()

builder.closeLog()
