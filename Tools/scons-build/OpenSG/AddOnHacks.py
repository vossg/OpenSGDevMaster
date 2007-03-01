
import os, sys, traceback, re, imp, types
import SConsAddons

import SConsAddons.Options.VTK
import SConsAddons.Options.Boost

from SConsAddons.EnvironmentBuilder import EnvironmentBuilder, detectValidArchs
from SConsAddons.Variants           import zipVariants
from SConsAddons.Util               import GetPlatform

import SConsAddons.Util as sca_util

pj = os.path.join

def StandardPackageOption__init__(self, name, help, header=None, library=None,
                                  symbol="main", required=False, cxxflags=None):
        self.baseKey = name
        self.incDirKey = name + "_incdir"
        self.libDirKey = name + "_libdir"
        
        SConsAddons.Options.PackageOption.__init__(self,name,[self.baseKey,self.incDirKey,self.libDirKey],help)
        self.available = False        
        self.baseDir = None 
        self.incDir = None
        self.libDir = None
        self.header = header
        self.library = library
        self.symbol = symbol
        self.required = required
        self.cxxflags = cxxflags
        

def StandardPackageApply(self, env):
    if self.incDir:
        if self.verbose:
            print "Appending inc_dir:", self.incDir
        env.Append(CPPPATH = [self.incDir])
    if self.libDir:
        if self.verbose:
            print "Appending lib_dir:", self.libDir
        env.Append(LIBPATH = [self.libDir])
    if self.library:
        if self.verbose:
            print "Adding lib:", self.library
        env.Append(LIBS = [self.library])
    if self.cxxflags:
        if self.verbose:
            print "Adding cxxflags:", self.cxxflags
        env.Append(CXXFLAGS = self.cxxflags)


      

def VTKValidate(self, env):
      # Check that path exists
      # Check that an include file (include/osg/Version) exists
      # Update the temps for later usage
      passed = False
      self.available = False

      if self.baseDir is None:
         self.checkRequired("VTK base dir (VtkBaseDir) was not specified")
         return

      if not os.path.isdir(self.baseDir):
         self.checkRequired("VTK base dir %s does not exist" % self.baseDir)
         return
         
      vtk_version_file = pj(self.baseDir, 'include', self.vtkVersion, 'vtkConfigure.h')
      if not os.path.isfile(vtk_version_file):
         self.checkRequired("%s not found" % vtk_version_file)
         return
      else:
         passed = True

      # TODO: Check version requirement

      # If not pass, then clear everything
      # Else we pass, set up the real data structures to use (initialized in
      # constructor)
      if not passed:
         # Clear everything
         self.baseDir = None
         edict = env.Dictionary()
         if edict.has_key(self.baseDirKey):
            del edict[self.baseDirKey]
      else:
         self.incDir = os.path.join(self.baseDir, 'include',self.vtkVersion )
         self.library = self.libList
         self.libDir = os.path.join(self.baseDir, 'lib')
         self.available = True
         print "[OK]"

def BoostFind(self, env):
      """ If base dir was not specified, attempt to find boost
          using some very basic searches.
      """
      # --- Determine toolset --- #
      if self.toolset == "auto":
         print "   Boost, autofinding toolset... ",
         
         if env["CC"] == "gcc":
            if sca_util.GetPlatform() == 'darwin':
               self.toolset = "darwin"
            else:
               self.toolset = "gcc"
         elif env["CC"] == "cl" and env.has_key("MSVS"):
            ver = env["MSVS"]["VERSION"]
            if "7.1" == ver:
               self.toolset = "vc71"
            elif "7.0" == ver:
               self.toolset = "vc7"
         elif sca_util.GetPlatform() == 'darwin' and env['CC'] == 'cc':
            self.toolset = "darwin"
         elif env["CC"] == "icc":
            self.toolset = "icc"
         else:
            self.checkRequired("Could not auto determine boost toolset.")
            return
         
         print " toolset: [%s]"%self.toolset
         
      # Quick exit if nothing to find
      if self.baseDir != None:
         return
      
      ver_header = None
      boost_header = pj("boost","version.hpp")

      # Find boost/version.hpp
      print "   searching for boost..."
      
      # May be able to use configure context here...
      directories_to_check = [env.Dictionary().get("CPPPATH"), pj("/","usr","include"),
                              pj("/","usr","local","include")]

      for d in directories_to_check:
         if None != d:
            ver_header = env.FindFile(boost_header, d)
            if ver_header:
               break

      if None == ver_header:
         self.checkRequired("   could not find boost header [%s] in paths: %s"%(boost_header,directories_to_check))
      else:
         ver_header = str(ver_header)
         print "   found at: %s\n"%ver_header

         # find base dir
         self.incDir = os.path.dirname(os.path.dirname(ver_header))
         self.baseDir = os.path.dirname(self.incDir)         

def apply():

    print "### Apply OpenSG SCons AddOn Hacks ###"

    SConsAddons.Options.StandardPackageOption.__init__ = StandardPackageOption__init__
    SConsAddons.Options.StandardPackageOption.apply    = StandardPackageApply

    setattr(SConsAddons.Options.VTK.VTK, "incDir",  None)
    setattr(SConsAddons.Options.VTK.VTK, "libDir",  None)
    setattr(SConsAddons.Options.VTK.VTK, "library", None)

    SConsAddons.Options.VTK.VTK.validate = VTKValidate

    SConsAddons.Options.Boost.Boost.find = BoostFind
