
from __future__ import generators

import os, sys, traceback, re, imp, types, string, copy
import distutils.util
import SConsAddons

import SConsAddons.Options.VTK
import SConsAddons.Options.Boost
import SConsAddons.Builders
import SConsAddons.EnvironmentBuilder
import SCons.SConf

from SConsAddons.Variants           import zipVariants
from SConsAddons.Util               import GetPlatform

import SConsAddons.Util as sca_util

Configure = SCons.SConf.SConf

if sys.version[:3] == "2.2":
    import optik.textwrap as textwrap
else:
    import textwrap

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

def VTKGetSettings(self):

    if self.vtkVersionNum:
      return [(self.baseDirKey, self.baseDir),
              ('VtkVersion', self.vtkVersionNum),]
    else:
      return [(self.baseDirKey, self.baseDir),]

def VTKSetInitial(self, optDict):
      " Set initial values from given dict "
      if self.verbose:
         print "   Applying initial VTK settings."
      if optDict.has_key(self.baseDirKey):
         self.baseDir = optDict[self.baseDirKey]
         if self.verbose:
            print "   %s specified or cached. [%s]."% \
                     (self.baseDirKey, self.baseDir)
                     
      if optDict.has_key('VtkVersion'):
         self.vtkVersion = 'vtk-%s' %(optDict['VtkVersion'])
         self.vtkVersionNum = optDict['VtkVersion']
      else:
         self.vtkVersion = 'vtk'
         self.vtkVersionNum = None

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
            self.toolset = "il"
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

def BoostValidate(self, env):
      " Check to make sure that the current settings work and are valid. """
      # Check that path exist
      # Check that an include file: boost/version.hpp  exists
      passed = True
      self.available = False
      
      if not self.baseDir:
         self.checkRequired("Boost base dir not set")
         return
      
      if not os.path.isdir(self.baseDir):    # If we don't have a directory
         self.checkRequired("Boost base dir is not a directory: %s" % self.baseDir)
         return

      # Make sure we have a valid inc dir or try to find one
      if self.incDir:
         # Check the version header is there         
         version_header = pj(self.incDir, 'boost', 'version.hpp')         
         if not os.path.isfile(version_header):
            self.checkRequired("Boost version.hpp header does not exist:%s"%version_header)
            return
         
      # --- Find include path --- #
      # If inc dir not set, try to find it      
      # - Try just include, try local, then try subdirs in reverse sorted order (to get most recent)
      else:
         print "   Searching for correct boost include dir...",
         base_include_dir = pj(self.baseDir, 'include')
         potential_dirs = [base_include_dir, self.baseDir]
         if os.path.isdir(base_include_dir):
            inc_dirs = [pj(base_include_dir,d) for d in os.listdir(base_include_dir)]
            inc_dirs.sort()
            inc_dirs.reverse()
            potential_dirs.extend(inc_dirs)
         
         for d in potential_dirs:
            if os.path.isfile(pj(d,'boost','version.hpp')):
               self.incDir = d
               break
         
         if self.incDir:
            print "  found: ", self.incDir
         else:
            print "  not found."
            self.checkRequired("Can not find boost include directory.")
            return

         
      print "   boost include path: ", self.incDir
      
      # --- Check version requirement --- #
      version_header = pj(self.incDir, 'boost', 'version.hpp')
      ver_file = file(version_header)
      ver_file_contents = ver_file.read()
      ver_match = re.search("define\s+?BOOST_VERSION\s+?(\d*)",
                            ver_file_contents)
      if not ver_match:
         self.checkRequired("   could not find BOOST_VERSION in file: %s"%version_header)
         return

      lib_ver_match = re.search("define\s+?BOOST_LIB_VERSION\s+?\"(.*)\"",
                                ver_file_contents)
      if lib_ver_match:
         self.libVersionStr = lib_ver_match.group(1)
      else:         
         print "WARNING: Could not determine library version string"
         self.libVersionStr = None

      found_ver_str = int(ver_match.group(1))
      found_ver_str = str(found_ver_str / 100000) + '.' + str(found_ver_str / 100 % 1000) + '.' + str(found_ver_str % 100)
      req_ver = [int(n) for n in self.requiredVersion.split('.')]
      found_ver = [int(n) for n in found_ver_str.split('.')]
      print "   boost version:", ".".join([str(x) for x in found_ver])
      if found_ver < req_ver:
         self.checkRequired("   Boost version is too old! Required %s but found %s"%(self.requiredVersion,found_ver_str))
         return

      arch_str = SConsAddons.Util.GetArch()
      # Set lists of the options we want
      self.found_incs = [self.incDir]
      self.found_incs_as_flags = [env["INCPREFIX"] + p for p in self.found_incs];

      if re.search(r'64', arch_str):
         self.found_lib_paths = [pj(self.baseDir, 'lib64')]
      else:
         self.found_lib_paths = [pj(self.baseDir, 'lib')]
         
      self.found_defines = []
      # Note: This doesn't work because the configure context uses the static
      #       run-time and this makes boost error out.
      #if self.preferDynamic:
      #   self.found_defines.append("BOOST_ALL_DYN_LINK")      
      #if not self.autoLink:
      #   self.found_defines.append("BOOST_ALL_NO_LIB")

      ######## BUILD CHECKS ###########  
      # --- Check building against libraries --- #   
      def check_lib(libname, lib_filename, env):         
         """ Helper method that checks if we can compile code that uses
             capabilities from the boost library 'libname' and get the
             symbols from the library lib_filename.
         """
         header_to_check = pj('boost','config.hpp')
         if self.headerMap.has_key(libname):
            header_to_check = self.headerMap[libname]

         # Create config environment
         # - Need to extend the environment
         conf_env = env.Copy()
         conf_env.Append(CPPPATH= self.found_incs, 
                         LIBPATH = self.found_lib_paths,
                         CPPDEFINES = self.found_defines)
         if "python" == libname:
            conf_env.Append(CPPPATH = self.python_inc_dir,
                            LIBPATH = self.python_lib_path,
                            LINKFLAGS = self.python_link_flags,
                            #LIBS = [lib_filename,] + self.python_extra_libs
                            LIBS = self.python_extra_libs
                         )
         
         # Thread library needs some additional libraries on Linux... (yuck)
         if "thread" == libname:
            conf_env.Append(LIBS = [lib_filename,] + self.thread_extra_libs)
         
         conf_ctxt = Configure(conf_env)
         result = conf_ctxt.CheckLibWithHeader(lib_filename, header_to_check, "c++")
         conf_ctxt.Finish()         
         return result
      

      # For each lib we are supposed to have
      #  - Search through possible names for that library
      #     - If we find one that works, store it
      for libname in self.lib_names:
         possible_lib_names = self.buildFullLibNamePossibilities(libname,env)
         
         found_fullname = None
         for testname in possible_lib_names:
            result = check_lib(libname, testname, env)
            if result:
               found_fullname = testname
               break
            
         if not found_fullname:
            passed = False
            self.checkRequired("Unable to find library: %s tried: %s"%(libname,possible_lib_names))
         else:
            self.found_libs[libname] = found_fullname
            print "  %s: %s"%(libname, found_fullname)

      # --- Handle final settings ---- #     
      if not passed:
         # Clear everything
         self.baseDir = None
         self.incDir = None
         edict = env.Dictionary()
         for k in (self.baseDirKey, self.incDirKey):
            if edict.has_key(k):
               del edict[k]
         self.found_incs = None
         self.found_lib_paths = []
         self.found_libs = {}
         self.found_defines = []
      else:
         self.available = True




def BuilderCreateDefineBuilder(target, source, env):
   """ Custom builder for creating a define file.

      The builder works by creating "#define" values in a file.      
      If value is a list, then first entry is the value and second is help text.
      There is a special case when the value is 'False' as a bool.  In this case
      the variable is not even defined.
      
      Example:
      definemap = {
         'USES_OPTION1'   : True,
         'USES_OPTION2'   : (5,"Value to set something")
      }
      
      my_file = env.StringFormatBuilder('file.out','file.in', definemap=definemap, headerguard="MY_FILE_H")
      env.AddPostAction (my_file, Chmod('$TARGET', 0644))
      env.Depends(my_file, 'version.h')
   """
   targets = map(lambda x: str(x), target)
   sources = map(lambda x: str(x), source)
   definemap = env['definemap']

   # Build each target from its source
   for i in range(len(targets)):
      #print "Generating file " + targets[i]
      content = ""
      for (define,value) in definemap.iteritems():
         help_text = None
         if isinstance(value, (types.ListType,types.TupleType)):
            help_text = value[1]
            value = value[0]
         if help_text:
            content += "/* %s */\n"%help_text
         if sys.version[:3] == "2.2":
            value = int(value)
            if not value:
               content += "/* #define %s %s */\n\n"%(define,str(value))
               continue            
         else:
            if isinstance(value, types.BooleanType):     # Convert from bool to int
               value = int(value)
               if not value:
                  content += "/* #define %s %s */\n\n"%(define,str(value))
                  continue            

         content += "#define %s %s\n\n"%(define,str(value))
      guard = "_GUARD_%s_"%SConsAddons.Builders.randomHeaderGuard(8) 
      if env.has_key("headerguard"):
         guard = env["headerguard"]
      content = "#ifndef %(guard)s\n#define %(guard)s\n\n%(content)s\n\n#endif\n"%vars()
      
      # Write out the target file with the new contents
      open(targets[i], 'w').write(content)      

def UtilGetArch():
   """ Return identifier for CPU architecture. """
   if not hasattr(os, 'uname'):
      platform = distutils.util.get_platform()
      arch = ""
      if re.search(r'i.86', platform):
         arch = 'ia32'
      # x86_64 (aka, x64, EM64T)
      elif re.search(r'x86_64', platform):
         arch = 'x64'
         # PowerPC
      elif re.search(r'ia64', platform):
         arch = 'ia64'
         # PowerPC
      elif re.search(r'Power_Mac', platform):
         arch = 'ppc'
      elif re.search(r'ppc64', platform):
         arch = 'ppc64'
   else:
      arch_str = os.uname()[4]
      if re.search(r'i.86', arch_str):
         arch = 'ia32'
      # x86_64 (aka, x64, EM64T)
      elif re.search(r'x86_64', arch_str):
         arch = 'x64'
      elif re.search(r'ia64', arch_str):
         arch = 'ia64'
      # PowerPC Macintosh
      elif re.search(r'Power Macintosh', arch_str):
         # XXX: Not sure if this actually works. -PH 7/24/2006
         if re.search(r'64', arch_str):
            arch = 'ppc64'
         else:
            arch = 'ppc'
      elif re.search(r'ppc64', arch_str):
         arch = 'ppc64'

   return arch


# ---- Helpers ---- #
def EnvironmentBuilderDetectValidArchs():
   """ Helper method that uses environment builder and SCon Confs to detect valid
       arch targets for the current system.
       Returns list of valid archs with the default first.
   """
   def CheckArch(context, archName):
      """ Custom config context check for checking arch in this method. """
      context.Message( 'Checking for arch [%s] ...'%archName )
      ret = context.TryCompile("""int main() { return 0; }""",'.c')
      context.Result( ret )
      return ret
   
   valid_archs = []

#   print GetArch
#   print Util.GetArch
   
   cur_arch = SConsAddons.Util.GetArch()
   
   if "ia32" == cur_arch:
      valid_archs.append(SConsAddons.EnvironmentBuilder.EnvironmentBuilder.IA32_ARCH)
   elif "x64" == cur_arch:
      valid_archs.append(SConsAddons.EnvironmentBuilder.EnvironmentBuilder.X64_ARCH)
   elif "ppc" == cur_arch:
      valid_archs.append(SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC_ARCH)   
   elif "ppc64" == cur_arch:
      valid_archs.append(SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC64_ARCH)      
   elif "ia64" == cur_arch:
      valid_archs.append(SConsAddons.EnvironmentBuilder.EnvironmentBuilder.IA64_ARCH)      

   # Only handle case of non-windows and using gcc compiler for now
   test_env = SConsAddons.EnvironmentBuilder.EnvironmentBuilder().buildEnvironment()
   if GetPlatform() == "win32" or test_env["CC"] != 'gcc':
      return valid_archs

   # We are going to try to compile a program targetting potential valid architectures
   # if the build works, then we add that one to valid possible architectures
   arch_checks = []
   if GetPlatform() == "darwin":    # Treat Darwin specially
      arch_checks = [SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC_ARCH,
                     SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC64_ARCH,
                     SConsAddons.EnvironmentBuilder.EnvironmentBuilder.IA32_ARCH]
   elif cur_arch in ["ia32","x64"]: # Check x86 platforms
      arch_checks = [SConsAddons.EnvironmentBuilder.EnvironmentBuilder.IA32_ARCH,
                     SConsAddons.EnvironmentBuilder.EnvironmentBuilder.X64_ARCH]
   elif cur_arch in ["ppc","ppc64"]:   # Check PowerPC architectures
      arch_checks = [SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC_ARCH,
                     SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC64_ARCH]
   elif cur_arch in ["ia64"]: # Check x86 platforms
      arch_checks = [SConsAddons.EnvironmentBuilder.EnvironmentBuilder.IA64_ARCH]

   for test_arch in arch_checks:
      if test_arch not in valid_archs:
         env_bldr = SConsAddons.EnvironmentBuilder.EnvironmentBuilder()
         env_bldr.setCpuArch(test_arch)
         conf_env = env_bldr.buildEnvironment()
         conf_ctxt = conf_env.Configure(custom_tests={"CheckArch":CheckArch})
         passed_test = conf_ctxt.CheckArch(test_arch)
         conf_ctxt.Finish()
         if passed_test:
            valid_archs.append(test_arch)

   return valid_archs

def EnvironmentBuilder_gcc_linux_misc(bldr, env):
   assert isinstance(bldr, SConsAddons.EnvironmentBuilder.EnvironmentBuilder)
   if bldr.cpuArch:

      if bldr.cpuArch == SConsAddons.EnvironmentBuilder.EnvironmentBuilder.IA32_ARCH:
         env.Append(CCFLAGS = ['-m32'],
                    CXXFLAGS = ['-m32'],
                    LINKFLAGS = ['-m32'])
      elif bldr.cpuArch == SConsAddons.EnvironmentBuilder.EnvironmentBuilder.X64_ARCH:
         env.Append(CCFLAGS = ['-m64'],
                    CXXFLAGS = ['-m64'],
                    LINKFLAGS = ['-m64'])
      elif bldr.cpuArch == SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC_ARCH:
         env.Append(CCFLAGS = ['-m32'],
                    CXXFLAGS = ['-m32'],
                    LINKFLAGS = ['-m32'])
      elif bldr.cpuArch == SConsAddons.EnvironmentBuilder.EnvironmentBuilder.PPC64_ARCH:
         env.Append(CCFLAGS = ['-m64'],
                    CXXFLAGS = ['-m64'],
                    LINKFLAGS = ['-m64'])
      else:
         assert False, "Invalid arch used for Linux gcc."

      if bldr.extraWarningLevel == SConsAddons.EnvironmentBuilder.EnvironmentBuilder.GV:
          env.Append(CCFLAGS = ['-Winline', '-Wreturn-type', '-Werror'])



   # ---- Command-line option processing ---- #
def EnvironmentBuilderAddOptions(self, opts):
      """ The EnvironmentBuilder has support for adding command line options to an
          option processing object.  This object has to be an instance
          of SConsAddons.Options.   Once the options are added, the user
          will be able to set defaults for the environment builder.
          
          TODO: Add options for tags.
      """
      import SConsAddons.Options as sca_opts
      
      assert isinstance(opts, sca_opts.Options)
      opts.AddOption(sca_opts.SeparatorOption("\nEnvironment Builder Defaults"))      
      opts.AddOption(sca_opts.EnumOption('default_debug_level',
                                         'Default debug level for environment builder.',
                                         'standard', 
                                         ['none','minimal','standard','extensive','maximum'],
                                         {'none':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.NONE,
                                          'minimal':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.STANDARD,
                                          'standard':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.STANDARD,
                                          'extensive':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.EXTENSIVE,
                                          'maximum':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.MAXIMUM}))
      opts.AddOption(sca_opts.EnumOption('default_opt_level',
                                         'Default optimization level for environment builder.',
                                         'standard', 
                                         ['none','minimal','standard','extensive','maximum'],
                                         {'none':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.NONE,
                                          'minimal':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.STANDARD,
                                          'standard':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.STANDARD,
                                          'extensive':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.EXTENSIVE,
                                          'maximum':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.MAXIMUM}))
      opts.AddOption(sca_opts.EnumOption('default_warning_level',
                                         'Default optimization level for environment builder.',
                                         'standard', [],
                                         {'none':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.NONE,
                                          'minimal':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.STANDARD,
                                          'standard':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.STANDARD,
                                          'extensive':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.EXTENSIVE,
                                          'maximum':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.MAXIMUM}))            
      opts.AddOption(sca_opts.EnumOption('extra_warning_level',
                                         'extra warning level for environment builder.',
                                         'none', [],
                                         {'none':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.NONE,
                                          'gv':SConsAddons.EnvironmentBuilder.EnvironmentBuilder.GV}))            

      if GetPlatform() == "darwin":
         opts.Add(sca_opts.BoolOption('darwin_universal',
                                      'Build universal binaries.', False))
         opts.Add('darwin_sdk', 'Darwin Platform SDK.', '')

def EnvironmentBuilderReadOptions(self, optEnv):
      """ Read the processed options from the given environment. """
      self.defaultDebugLevel   = optEnv["default_debug_level"]
      self.defaultOptLevel     = optEnv["default_opt_level"]
      self.defaultWarningLevel = optEnv["default_warning_level"]
      self.extraWarningLevel   = optEnv["extra_warning_level"]

      if GetPlatform() == "darwin":
         self.darwinUniversalEnabled = optEnv["darwin_universal"]
         self.darwinSdk = optEnv["darwin_sdk"]

def VariantsHelperFillDefaultVariants(self, varKeys):
      """ Fill the variants variable with default allowable settings. """
      if "type" in varKeys:
         self.variants["type"] = [["debug","optimized"], True]
         if sca_util.GetPlatform() == "win32":
            self.variants["type"][0].append("hybrid")
      
      if "libtype" in varKeys:
         self.variants["libtype"] = [["shared","static"], False]
      
      if "arch" in varKeys:
         valid_archs = SConsAddons.EnvironmentBuilder.detectValidArchs()
         if len(valid_archs) == 0:
            valid_archs = ["default"]
         print "Valid archs: ", valid_archs
         self.variants["arch"] = [valid_archs[:], True]


def BoolOptionTextToBool(self, val):
        """
        Converts strings to True/False depending on the 'truth' expressed by
        the string. If the string can't be converted, the original value
        will be returned.
        """

        if sys.version[:3] == "2.2":
            if isinstance(val, types.IntType):
                return val
        else:
            if isinstance(val, types.BooleanType):
                return val


        lval = string.lower(val)
        if lval in SConsAddons.Options.BoolOption.true_strings: return True
        if lval in SConsAddons.Options.BoolOption.false_strings: return False
        raise ValueError("Invalid value for boolean option: %s" % val)



def apply():

    print "### Apply OpenSG SCons AddOn Hacks ###"

    SConsAddons.Options.StandardPackageOption.__init__ = \
        StandardPackageOption__init__

    SConsAddons.Options.StandardPackageOption.apply    = \
        StandardPackageApply

    setattr(SConsAddons.Options.VTK.VTK, "incDir",  None)
    setattr(SConsAddons.Options.VTK.VTK, "libDir",  None)
    setattr(SConsAddons.Options.VTK.VTK, "library", None)

    setattr(SConsAddons.EnvironmentBuilder.EnvironmentBuilder, "GV", 5)
    setattr(SConsAddons.EnvironmentBuilder.EnvironmentBuilder,
            "extraWarningLevel",
            SConsAddons.EnvironmentBuilder.EnvironmentBuilder.NONE)

    SConsAddons.Options.VTK.VTK.validate    = VTKValidate
    SConsAddons.Options.VTK.VTK.getSettings = VTKGetSettings
    SConsAddons.Options.VTK.VTK.setInitial  = VTKSetInitial

    SConsAddons.Options.Boost.Boost.find = BoostFind
    SConsAddons.Options.Boost.Boost.validate = BoostValidate

    SConsAddons.Builders.CreateDefineBuilder = BuilderCreateDefineBuilder

    SConsAddons.Variants.VariantsHelper.fillDefaultVariants = \
        VariantsHelperFillDefaultVariants
    
    SConsAddons.Util.GetArch = UtilGetArch
    sca_util.GetArch         = UtilGetArch
    GetArch                  = UtilGetArch
    

    SConsAddons.EnvironmentBuilder.detectValidArchs = \
        EnvironmentBuilderDetectValidArchs

    SConsAddons.EnvironmentBuilder.gcc_linux_misc = \
        EnvironmentBuilder_gcc_linux_misc


    SConsAddons.EnvironmentBuilder.EnvironmentBuilder.addOptions = \
        EnvironmentBuilderAddOptions

    SConsAddons.EnvironmentBuilder.EnvironmentBuilder.readOptions = \
        EnvironmentBuilderReadOptions

    funcList = copy.copy(SConsAddons.EnvironmentBuilder.default_funcs)

    
    SConsAddons.EnvironmentBuilder.default_funcs = []
    
    for f in funcList:
        (compiler_list,platform_list, func) = f

        if 'gcc' in compiler_list and 'linux' in platform_list:
            SConsAddons.EnvironmentBuilder.default_funcs.append([compiler_list, platform_list, EnvironmentBuilder_gcc_linux_misc])
        else:
            SConsAddons.EnvironmentBuilder.default_funcs.append([compiler_list, platform_list, func])            

    SConsAddons.Options.BoolOption.textToBool = BoolOptionTextToBool
