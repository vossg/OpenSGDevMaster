#!python
#
# SCons build script for OpenSG
#

# If we have wingide, try loading the debugging extenstions
try:
   import wing.wingdbstub
   print "Loaded wingdb stub for debugging..."
except:
   pass

import os, string, sys, re, glob, copy, types, traceback, pprint
pj = os.path.join

print "WARNING:"
print "WARNING: The build is currently in development.  It needs the svn version of scons-addons"
print "WARNING:"

sys.path.insert(0,pj('Tools','scons-addons','src'))
sys.path.insert(0,pj('Tools','scons-build'))

import SCons.Environment
import SCons
import SConsAddons.Util as sca_util
import SConsAddons.Options as sca_opts
import SConsAddons.Variants as sca_variants
import SConsAddons.Builders
import SConsAddons.Options.Boost
from SConsAddons.EnvironmentBuilder import EnvironmentBuilder
from LibraryUtils import *
from sets import Set

# Aliases
GetPlatform = sca_util.GetPlatform
Export('GetPlatform')
pj = os.path.join

# Build TODO
# - Support selection of WS/ES
# - Support selection of compiler to build with
# - QT support
# - Contrib libraries
# - Library specific defines (if needed)
# - Build on windows
# - Project files for windows

# ------ HELPER METHODS -------- #

# ------------------ BUILDERS ------------------- #
# fcdProcess builder
# - Custom builder for fcdProcess
def registerFcdProcessBuilder(env, required=True):
   print "Setting up fcdProcess builder...",
   
   fcdProcess_cmd = pj("Tools", "fcdProcess","fcdProcess.pl")
   fcdProcess_cmd = os.path.abspath(fcdProcess_cmd)
   if not os.path.isfile(fcdProcess_cmd):
      print " Warning: fcdProcess not found at: ", fcdProcess_cmd      
      if required:
         sys.exit(1)
      return
   
   template_files = glob.glob(pj("Tools","fcdProcess","*Template*"))   
   
      
   def prop_emitter(target,source,env, template_files=template_files):
      """ Returns a list of files including all output forms and
          The input templates as sources.
      """
      assert str(source[0]).endswith(".fcd")
      assert len(source) == 1

      base_name = os.path.splitext(str(source[0]))[0]

      # Targets are all the files that we build
      target = []
      for ext in ["Base.cpp","Base.h","Base.inl","Fields.h"]:
         target.append(base_name+ext)
      
      # Sources are the fcd file and all the template files
      source.extend(template_files)

      return (target, source)
   
   
   fcdprocess_builder = Builder(action = fcdProcess_cmd + ' -c -b -d $SOURCE -p ${TARGET.dir}',
                              src_suffix = '.fcd',
                              suffix = 'unused.h',
                              emitter = prop_emitter)
   env.Append(BUILDERS = {'FcdProcess' : fcdprocess_builder});
   print "[OK]"

   
#------------------------------------------------------------------------------
# Main build setup
#------------------------------------------------------------------------------
EnsureSConsVersion(0,96)
SourceSignatures('MD5')
#SourceSignatures('timestamp')
SConsignFile('.sconsign.'+GetPlatform())
opensg_version_string = file("VERSION").readline().strip()

# Figure out what version of CppDom we're using
print "Building OpenSG ", opensg_version_string

platform = sca_util.GetPlatform()
unspecified_prefix = "use-instlinks"
buildDir = "build." + platform      
option_filename = "option.cache." + platform

# Create base environment to use for option processing
if GetPlatform() == "win32":
   common_env = Environment()
else:
   common_env = Environment(ENV = os.environ)
# Setup the directories used for sconf processing
common_env["CONFIGUREDIR"] = '.sconf_temp_'+platform
common_env["CONFIGURELOG"] = 'sconf.log_'+platform
SConsAddons.Builders.registerDefineBuilder(common_env)
SConsAddons.Builders.registerSubstBuilder(common_env)

# Create variant helper and builder
variant_helper = sca_variants.VariantsHelper()
base_bldr = EnvironmentBuilder()

# --------------- #
# --- OPTIONS --- #
# --------------- #
# Find all build.info files that may have options
#build_info_files = []
#for root, dirs, files in os.walk(pj(os.getcwd(),'Source')):
#   build_info_files += [pj(root,f) for f in files if f == "build.info"]
#
#print "Build info files found: ", build_info_files

opts = sca_opts.Options(files = [option_filename, 'options.custom'],
                                   args= ARGUMENTS)

# Create option objects
boost_options = sca_opts.Boost.Boost("boost","1.31.0",required=True)

glut_libname = "glut"
tiff_libname = "tiff"
if "win32" == platform:
   glut_libname = "glut32"
   tiff_libname = "tif32"
   
jpeg_option = sca_opts.StandardPackageOption("jpeg","Jpeg library location",
                                             library="jpeg", required=False)
tiff_option = sca_opts.StandardPackageOption("tiff","Tiff library location",
                                             library=tiff_libname, required=False)
png_option = sca_opts.StandardPackageOption("png","PNG library location",
                                             library="png", required=False)
glut_option = sca_opts.StandardPackageOption("glut","GLUT library location",
                                             library=glut_libname, header="GL/glut.h", required=False)

format_options = [jpeg_option,tiff_option,png_option]
# Setup options
opts.AddOption(sca_opts.SeparatorOption("\nStandard settings"))
opts.Add('prefix', 'Installation prefix', unspecified_prefix)
opts.AddOption(sca_opts.SeparatorOption("\nPackage Options"))
opts.AddOption( boost_options )
opts.AddOption( glut_option )
opts.AddOption(sca_opts.SeparatorOption("\nFormat Options"))
for o in format_options:
   opts.AddOption(o)
opts.AddOption(sca_opts.BoolOption("enable_gif","Enable GIF support.",True))   
# Custom options
opts.AddOption(sca_opts.SeparatorOption("\nAdvanced Options"))
opts.AddOption(sca_opts.EnumOption("fcptr_mode","Set the pointer mode to use for field containers",
                                   "MT_FCPTR",["SINGLE_THREAD","MT_CPTR","MT_FCPTR"]))
opts.AddOption(sca_opts.BoolOption("disable_deprecated","Disable deprecated code.",False))
opts.AddOption(sca_opts.BoolOption("disable_glut_glsubdir","Do not use GL subdir while including glut.h",False))
opts.AddOption(sca_opts.BoolOption("osg_1_compat","Enable opensg 1.x compatibility.",False))
opts.AddOption(sca_opts.BoolOption("osg_deprecated_props","Enable deprecated property types.",False))
opts.Add("build_suffix", "Suffix to append to build directory.  Useful for compiling multiple variations on same platform.", "")                                    
opts.AddOption(sca_opts.BoolOption("enable_fcdprocess","If true, enable support for fcdProcess in the build.",False))
opts.Add("icc_gnu_compat","<GCC Verion> to make the icc resultbinary compatible to the given gcc version. (unsupported)")
if "win32" == platform:
   opts.AddOption(sca_opts.BoolOption("win_localstorage", "Use local storage instead of __declspec to get thread local storage on windows",
                                      True))
if "win32" != platform:
   opts.AddOption(sca_opts.BoolOption("pthread_elf_tls", "Enable elf thread local storage with pthreads.",
                                      ("linux"==platform)))
                                      
                                    
base_bldr.addOptions(opts)             # Add environment builder options
variant_helper.addOptions(opts)        # Add variant building options

try:
   opts.Process(common_env)               # Process the options
except Exception, ex:
   if not SConsAddons.Util.hasHelpFlag():
      print "Option error: ", str(ex)
      traceback.print_exc()
      sys.exit(1)

help_text = """--- OpenSG Build system ---
%s
Targets:
   install - Install OpenSG
      ex: 'scons install prefix=$HOME/software' to install in your account
   Type 'scons' to just build it
 
"""%(opts.GenerateHelpText(common_env),)

#help_text = opts.GenerateHelpText(common_env) + help_text
Help(help_text)


# --- MAIN BUILD STEPS ---- #
# If we are running the build
if not SConsAddons.Util.hasHelpFlag():
   try:                                   # Try to save the options if possible
      opts.Save(option_filename, common_env)
   except LookupError, le:
      pass
   
   # Update settings
   if common_env["build_suffix"] != "":
      buildDir = buildDir + "." + common_env["build_suffix"]
      
   # .fcd processing
   if common_env["enable_fcdprocess"]:      
      registerFcdProcessBuilder(common_env)
      
      fcd_files = []
      for root, dirs, files in os.walk(pj(os.getcwd(),'Source')):
         fcd_files += [pj(root,f) for f in files if f.endswith(".fcd")]
      
      for f in fcd_files:
         fcd_targets = common_env.FcdProcess(source=f)
         NoClean(fcd_targets)

   
   # --- Collect all Source and Header files --- #         
   
   # --- Find and process all the build.info files ---- #
   # - Find them
   # This is a little more complex then I would like. The complexity
   # comes from the fact that we are recursing in the directories
   # and that any file found overrides the current settings.
   # Basic idea is:
   #   - Keep track of a library stack that we are adding
   #   - Recurse into each subdirectory of source
   #   - Keep all file names relative to the Source directory (so they work in builddir)
   #
   # ----- BUILD.INFO FILES ------- #
   # When evaluating build.info files:
   #   input vars:
   #      option_pass: If true, we are just trying to get options
   #      opts: If not none, this is an options object that can have options added
   #      platform: The current platform string ("win32", "linux", )
   #      compiler: The current compiler being used ("g++","cl", )
   #   output vars:
   #      library: Name of the library to add code to
   #      stop_traversal: If set tru, do not traverse into this directory
   #      - Dependencies
   #         osg_dep_libs: Name of OpenSG libraries that we depend upon (need for link)
   #         libs: Name of non-OpenSG libraries we depend upon
   #         cpppath: Additional cpp paths that we should set for building
   #         libpath: Additional library paths that we should set
   #      - Tests
   #         osg_test_libs: OpenSG libraries that we need when building tests
   #         other_test_libs: Other libraries we need when building tests
   #         test_cpppath: Additional cpppaths for building tests
   #         test_libpath: Additional lib paths we need for building tests
   #
   lib_map = {}    # Map from name to library we are using   
   dir_ignores = [".svn", "ES","EGL"]   

   def scan_libs(base_dir, cur_dir, name_stack):
      """ Scan library directory.
          base_dir: Directory to keep all paths relative to
          cur_dir: Directory to examine.
          name_stack: Current stack of library names
      """
      global lib_map
      #print "dir: ", cur_dir
      full_dir = pj(base_dir, cur_dir)
      dir_contents = [pj(cur_dir,f) for f in os.listdir(full_dir)]
      files = [f for f in dir_contents if os.path.isfile(pj(base_dir,f))]
      dirs  = [d for d in dir_contents if os.path.isdir(pj(base_dir,d))]
      have_build_info = os.path.exists(pj(full_dir,"build.info"))
      cur_lib = None          # The current library we are adding to

      lib_attrib_names = ["osg_dep_libs","libs","cpppath","libpath",
                          "osg_test_libs","other_test_libs","test_cpppath", "test_libpath"]
      # If we have a build info file
      # - Setup namespace and evaluate it
      # - Create on demand
      # - Fill with anything from the file
      if have_build_info:
         bi_filename = pj(full_dir,"build.info")
         print "   Evaluating: ", bi_filename         
         
         # Custom options
         ns = {"option_pass":False, 
               "opts":opts,
               "library":None,
               "platform":platform,
               "compiler":common_env["CXX"],
               "stop_traversal":False,               
         }
         # Options for the lib package
         for n in lib_attrib_names:
            ns[n] = []
            
         execfile(bi_filename, ns)
         if ns["stop_traversal"]:          # Don't traverse any further
            print "   Pruning traversal."
            return
         if not ns.has_key("library"):
            print "Error: Must specify 'library' value in build.info file:", bi_filename
            sys.exit(1)         
         lib_name = ns["library"]
         if not lib_map.has_key(lib_name):
            lib_map[lib_name] = LibraryInfo(name=lib_name)
         name_stack.append(lib_name)
         cur_lib = lib_map[lib_name]
         
         # Add all the lib options from the evaluation
         for n in lib_attrib_names:
            getattr(cur_lib,n).extend(ns[n])
         
      
      test_files =   [f for f in files if os.path.basename(f).startswith("test") and f.endswith(".cpp")]
      source_files = [f for f in files if (os.path.splitext(f)[1] in [".cpp",".cc"]) and\
                                          (f not in test_files)]
      header_files = [f for f in files if os.path.splitext(f)[1] in [".h",".inl",".ins",".hpp"] and\
                                         (os.path.basename(f).startswith("OSG"))]      
      
      #print "Adding to lib:[%s]  source: [%s]"%(name_stack[-1],source_files)
      if len(test_files) or len(source_files) or len(header_files):
         if len(name_stack) == 0:
            print "Error: Attempted to add source with no library build.info specifed.  In dir: %s"%pj(base_dir,cur_dir)
            sys.exit(1)
         lib_name = name_stack[-1]
         lib_map[lib_name].source_files += source_files
         lib_map[lib_name].header_files += header_files
         lib_map[lib_name].test_files   += test_files

      # Recurse into subdirectories
      for d in dirs:
         if not os.path.basename(d) in dir_ignores:
            scan_libs(base_dir, d, copy.copy(name_stack))
   
   scan_libs(pj(os.getcwd(),"Source"), '', [])   
   
   # Hack to handle the generation of the parser from .y
   # This pretty hacky to allow using a version of the file from the repository if yacc is not installed
   if "yacc" in common_env["TOOLS"]:
      parser_env = common_env.Copy()
      parser_env.Append(YACCFLAGS = ["-d","-v","-pOSGScanParseSkel_","-bOSGScanParseSkel_"])
      source_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
      target_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
      yfiles = parser_env.CXXFile(target=target_file,source=source_file)   
      NoClean(yfiles)
      print "yfiles: ", yfiles 
      #if not yfiles[0] in lib_map["OSGFileIO"].source_files:
      #   lib_map["OSGFileIO"].source_files.append(yfiles[0])
      #if not yfiles[1] in lib_map["OSGFileIO"].header_files:
      #   lib_map["OSGFileIO"].header_files.append(yfiles[1])
   else:
      print "WARNING: bison not available.  If you change .yy files they will not be built."
   
   # Hack to handle the generation of the scanner from .lpp
   # This pretty hacky to allow using a version of the file from the repository if lex is not installed
   if "lex" in common_env["TOOLS"]:
      lexer_env = common_env.Copy()
      lexer_env.Append(LEXFLAGS = ["-+","-POSGScanParseSkel_"])
      source_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelScanner.ll"
      target_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelScanner.cpp"
      lfiles = lexer_env.CXXFile(target=target_file,source=source_file)   
      NoClean(lfiles)
      Depends(lfiles, "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.hpp") # the scanner includes the token header from the parser...
      print "lfiles: ", lfiles 
      #if not lfiles[0] in lib_map["OSGFileIO"].source_files:
      #   lib_map["OSGFileIO"].source_files.append(lfiles[0])
   else:
      print "WARNING: flex not available.  If you change .ll files they will not be built."   

   # -- Common builder settings
   variant_helper.readOptions(common_env)
   base_bldr.readOptions(common_env)
   #base_bldr.enableWarnings()
   base_bldr.enableWarnings(EnvironmentBuilder.MINIMAL)
  
   # Apply any common package options
   # Update environment for boost options
   boost_options.apply(common_env)    
     
   # If defaulting to instlinks prefix:
   #  - Use symlinks
   #  - Manually set the used prefix to the instlinks of the build dir
   if common_env['prefix'] == unspecified_prefix:
      if hasattr(os,'symlink'):
         common_env['INSTALL'] = SConsAddons.Util.symlinkInstallFunc
      common_env['prefix'] = pj( Dir('.').get_abspath(), buildDir, 'instlinks')
   
   # --- Setup installation paths --- #
   paths = {}
   paths['base']      = os.path.abspath(common_env['prefix'])
   paths['lib']       = pj(paths['base'], 'lib')
   paths['include']   = pj(paths['base'], 'include')   
   paths['bin']       = pj(paths['base'], 'bin')   
   print "using prefix: ", paths['base']         
      
   # ---- Generate OSGConfigured.h --- #
   definemap = {"OSG_DISABLE_DEPRECATED": (common_env["disable_deprecated"],
                                           "Disable interface that will go away in the future"),                
                "OSG_NO_GLUT_GLSUBDIR":(common_env["disable_glut_glsubdir"],"Don't use GL subdir for glut"),
                "OSG_MT_FIELDCONTAINERPTR":("MT_FCPTR" == common_env["fcptr_mode"]),
                "OSG_MT_CPTR_ASPECT":("MT_CPTR" == common_env["fcptr_mode"]),
                "OSG_1_COMPAT":common_env["osg_1_compat"],
                "OSG_DEPRECATED_PROPS":common_env["osg_deprecated_props"],
                
                "OSG_WITH_JPG":jpeg_option.isAvailable(),
                "OSG_WITH_TIF":tiff_option.isAvailable(),
                "OGG_WITH_PNG":png_option.isAvailable(),
                "OSG_WITH_GLUT":glut_option.isAvailable(),
                "OSG_WITH_GIF":common_env["enable_gif"],
               }
   if "win32" == platform:   # Win32 specific defines
      definemap.update( {"OSG_WIN32_ASPECT_USE_LOCALSTORAGE": common_env["win_localstorage"],} )
   else:
      definemap.update( {"OSG_PTHREAD_ELF_TLS":(common_env["pthread_elf_tls"],"Use elf tls with pthreads."),} )
   
   common_env.DefineBuilder(pj(paths["include"],"OpenSG","OSGConfigured.h"),Value(definemap), 
                            definemap=definemap)
   
   # ---- FOR EACH VARIANT ----- #   
   # This is the core of the build.
   print "types: ",    variant_helper.variants["type"] 
   print "libtypes: ", variant_helper.variants["libtype"] 
   print "archs: ",    variant_helper.variants["arch"]    
   common_env.Append(CPPPATH = [paths['include'],pj(paths['include'],"OpenSG")])
   
   for combo in variant_helper.iterate(locals(), base_bldr, common_env):            
      #baseEnv = env_bldr.applyToEnvironment(common_env.Copy(), variant=combo,options=opts)      
      print "   Processing combo: ", ", ".join(['%s:%s'%(i[0],i[1]) for i in combo.iteritems()])

      inst_paths = copy.copy(paths)
      if GetPlatform() != "win32" and "debug" == combo["type"]:
         inst_paths["lib"] = pj(inst_paths["lib"],"debug")      
      if "x64" == combo["arch"]:
         inst_paths['lib'] = inst_paths['lib'] + '64'                  
      
      Export('build_env','inst_paths','opts', 'variant_pass','combo',
             'lib_map','boost_options', 
             'shared_lib_suffix','static_lib_suffix')
      
      # Process subdirectories
      sub_dirs = ['Source']   
      full_build_dir = pj(buildDir,combo_dir)
      for d in sub_dirs:
         SConscript(pj(d,'SConscript'), build_dir=pj(full_build_dir, d), duplicate=0)
   
   common_env.Alias('install', paths['base'])
   
   # Build -config file
   # - Create string that can build libmap
   lib_map_build_list = []
   for (name,lib) in lib_map.iteritems():
      lib_map_build_list.append(lib.dump())
   lib_map_str = pprint.pformat(lib_map_build_list)
   
   submap = {'@LIB_MAP_STR@':lib_map_str,
             '@PREFIX@':common_env["prefix"],
             '@LIBPATH@':paths["lib"],
             '@INCPATH@':paths["include"],
             '@VERSION@':opensg_version_string,
             '@LIBRARY_UTIL_SRC@':file(pj('Tools','scons-build','LibraryUtils.py')).read()}
   # Install two scripts so we have one with osg2 in the name to let users be sure they get the right version             
   for n in ["osg-config","osg2-config"]:
      osg_config = common_env.SubstBuilder(pj(paths['bin'],n),
                              'osg-config.in', submap=submap)   
      common_env.AddPostAction(osg_config, Chmod('$TARGET', 0755))
      common_env.Depends(osg_config, Value(lib_map_str))

   # Close up with aliases and defaults   
   Default('.')

