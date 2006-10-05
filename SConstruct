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

import os, string, sys, re, glob, copy, types, traceback, pprint, tempfile, shutil
pj = os.path.join

print "-------------------------------------------------"
print "WARNING: The build is currently in development.  "
print "            - It needs the svn version of scons-addons"
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
verbose_build = False

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


def addScanParseSkel(common_env):
   """ This is an ugly hack to add the lex/yacc support into the build.  It is ugly because of a couple of things.
      - We use some very custom flags
      - We need to post process the scanner to include a different file then normal.
      - We are forcing this to be done in the source tree in a subdir without actually going there.
      - Dependency management seems to be a little messed up right now in the code or scons.
      - BUGS: Scons does not seem to recognize that the files we are building here are source
              files for the libraries.  This makes it so we have to run the build twice if the files change.
   """
   # Hack to handle the generation of the parser from .y
   # This pretty hacky to allow using a version of the file from the repository if yacc is not installed
   # 1. Call bison: OSGScanParseSkelParser.yy -> OSGScanParseSkelParser.hpp .cpp .output (we don't need the last one) 
   if "yacc" in common_env["TOOLS"]:
      parser_env = common_env.Copy()
      parser_env.Append(YACCFLAGS = ["-d","-v","-pOSGScanParseSkel_","-bOSGScanParseSkel_"])
      source_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
      target_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
      yfiles = parser_env.CXXFile(target=target_file,source=source_file)   
      NoClean(yfiles)
      #print "yfiles: ", yfiles

      # Make sure the parser files have been found for OSGFileIO
      y_cpp_file = str(yfiles[0]).replace("Source/","",1) 
      y_hpp_file = str(yfiles[1]).replace("Source/","",1)
      #if not y_cpp_file in lib_map["OSGSystem"].source_files:
      #   lib_map["OSGSystem"].source_files.append(y_cpp_file)
      #if not y_hpp_file in lib_map["OSGSystem"].header_files:
      #   lib_map["OSGSystem"].header_files.append(y_hpp_file)
      #print " yy source: %s \n header: %s"%(lib_map["OSGSystem"].source_files, lib_map["OSGSystem"].header_files)
   else:
      print "WARNING: bison not available.  If you change .yy files they will not be built."
   
   # Hack to handle the generation of the scanner from .lpp
   # This pretty hacky to allow using a version of the file from the repository if lex is not installed
   # 2. Call flex: OSGScanParseSkelScanner.lpp -> OSGScanParseSkelScanner.cpp (this one needs to be filtered to change the include) 
   if "lex" in common_env["TOOLS"]:
      def filter_header(target, source, env):
         """ Custom filter to change the include file for the flexlexer.h"""
         fname = str(target[0])
         contents = open(fname).readlines()
         for i in range(len(contents)):
            if contents[i] == "#include <FlexLexer.h>\n":
               contents[i] = "#include \"%s\"\n" % os.path.split(OSG_flexlexer_h)[1]
               break
         open(fname,'w').writelines(contents)
         #print "filter_header: Created ", fname      

      lexer_env = common_env.Copy()
      lexer_env.Append(LEXFLAGS = ["-+","-POSGScanParseSkel_"])

      lexer_dir       = pj('Source','System','FileIO','ScanParseSkel')
      sys_flexlexer_h = "/usr/include/FlexLexer.h"
      OSG_flexlexer_h = pj(lexer_dir,"OSGScanParseSkelScanner_FlexLexer.h")
      source_file     = pj(lexer_dir,"OSGScanParseSkelScanner.ll")
      target_file     = pj(lexer_dir,"OSGScanParseSkelScanner.cpp")

      # Replace lex builder with new action that calls flex and then filters
      std_lex_action = Action("$LEXCOM", "$LEXCOMSTR")      
      filter_action = Action(filter_header, lambda t,s,e: "Filtering header: %s %s"%(str(t),str(s)))
      cxx_file_builder = lexer_env['BUILDERS']['CXXFile']
      cxx_file_builder.add_action('.ll', Action([std_lex_action, filter_action]))            
      lfiles = lexer_env.CXXFile(target=target_file,source=source_file)
      NoClean(lfiles)
      #print "lfiles: ", lfiles 
      
      # If available, copy the system FlexLexer.h file to local source dir
      if os.path.exists(sys_flexlexer_h):      
         flexlex_cp = lexer_env.Command(OSG_flexlexer_h, sys_flexlexer_h,[Copy('$TARGET','$SOURCE'),])
         Depends(lfiles, flexlex_cp)

      #Depends(lfiles, "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.hpp") # the scanner includes the token header from the parser...
      if vars().has_key('yfiles'):
         Depends(lfiles, yfiles)      
      
      # Strip off "Source/" since this will be in the build dir
      scanner_src = target_file.replace("Source/","",1)
      #if not scanner_src in lib_map["OSGSystem"].source_files:
      #   lib_map["OSGSystem"].source_files.append(scanner_src)
      #print "FileIO source files: ", lib_map["OSGSystem"].source_files         
   else:
      print "WARNING: flex not available.  If you change .ll files they will not be built."  
   
#------------------------------------------------------------------------------
# Main build setup
#------------------------------------------------------------------------------
EnsureSConsVersion(0,96,92)
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

if ARGUMENTS.has_key("buildbot_slave"):
   print "Buildbot slave build initiated"
   build_slave_filename = "buildbot.options"
   if ARGUMENTS["buildbot_slave"] not in ["true", "1", "yes"]:
      build_slave_filename = ARGUMENTS["buildbot_slave"]
   buildbot_options_file = os.path.abspath(os.path.join(os.getcwd(), "..", "..", build_slave_filename))
   if os.path.exists(buildbot_options_file):
      print "Buildbot slave:"
      print "      found options file: %s" % str(buildbot_options_file)
      execfile(buildbot_options_file, ARGUMENTS)
      print "      finished processing options"
   else:
      print "Buildbot slave: Options file not found.. will continue with defaults"

# Create base environment to use for option processing
if GetPlatform() == "win32":
   # XXX: Temp hack to get msvs version setting
   if ARGUMENTS.has_key("MSVS_VERSION"):
      common_env = Environment(MSVS_VERSION=ARGUMENTS["MSVS_VERSION"])
   else:
      common_env = Environment()
else:
   common_env = Environment(ENV = os.environ)
# Setup the directories used for sconf processing
common_env["CONFIGUREDIR"] = '.sconf_temp_'+platform
common_env["CONFIGURELOG"] = 'sconf.log_'+platform
if common_env.has_key("MSVS"):
   common_env["CONFIGUREDIR"] += "." + common_env["MSVS"]["VERSION"]
   common_env["CONFIGURELOG"] += "." + common_env["MSVS"]["VERSION"]

SConsAddons.Builders.registerDefineBuilder(common_env)
SConsAddons.Builders.registerSubstBuilder(common_env)

# Create variant helper and builder
variant_helper = sca_variants.VariantsHelper(variantKeys=["type","arch"])
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
boost_options = sca_opts.Boost.Boost("boost","1.31.0",libs=['filesystem'],required=True)

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
zlib_option = sca_opts.StandardPackageOption("zlib","zlib library location",
                                             library="z", header="zlib.h", required=False)                                             

format_options = [jpeg_option,tiff_option,png_option,zlib_option]
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
opts.AddOption(sca_opts.BoolOption("enable_unittests","If true, enable unit tests in the build.",True))
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
  
   if common_env.has_key("MSVS"):
      import pprint
      print "Found MSVS. using version: ", common_env["MSVS"]["VERSION"]
      pprint.pprint(common_env["MSVS"])

   # Update settings
   if common_env.has_key("MSVS"):
      buildDir += "." + common_env["MSVS"]["VERSION"]
   if common_env["build_suffix"] != "":
      buildDir += "." + common_env["build_suffix"]
      
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
         if verbose_build:
            print "   Evaluating: ", bi_filename         
         else:
            sys.stdout.write(".")
         
         # Custom options
         ns = {"option_pass":False, 
               "opts":opts,
               "library":None,
               "platform":platform,
               "compiler":common_env["CXX"],
               "stop_traversal":False
         }
         # Options for the lib package
         for n in lib_attrib_names:
            ns[n] = []
            
         execfile(bi_filename, ns)
         if ns["stop_traversal"]:          # Don't traverse any further
            if verbose_build:
               print "   Pruning traversal."
            return
         if not ns.has_key("library"):
            print "Error: Must specify 'library' value in build.info file:", bi_filename
            sys.exit(1)         
         lib_name = ns["library"]
         if not lib_map.has_key(lib_name):
            lib_map[lib_name] = LibraryInfo(name=lib_name)
            if verbose_build:
               print "Created new LibraryInfo: ", lib_name
         name_stack.append(lib_name)
         cur_lib = lib_map[lib_name]
   
         if verbose_build:
            print "lib name: ", lib_name
         
         # Add all the lib options from the evaluation
         # - Only add on the unique ones
         for n in lib_attrib_names:
            attrib_list = getattr(cur_lib,n)
            attrib_list.extend([x for x in ns[n] if x not in attrib_list])
      
      # Collect source files from all directories and put them into the active library object         
      test_files =   [f for f in files if os.path.basename(f).startswith("test") and f.endswith(".cpp")]
      unittest_files =   [f for f in files if os.path.basename(f).endswith("Test.cpp") and\
                                              os.path.basename(f).startswith("OSG")]
      source_files = [f for f in files if (os.path.splitext(f)[1] in [".cpp",".cc"]) and\
                                          (os.path.basename(f).startswith("OSG") and\
                                           f not in test_files and f not in unittest_files)]
      header_files = [f for f in files if os.path.splitext(f)[1] in [".h",".inl",".ins",".hpp"] and\
                                         (os.path.basename(f).startswith("OSG"))]      
      
      #print "Adding to lib:[%s]  source: [%s]"%(name_stack[-1],source_files)
      if len(test_files) or len(source_files) or len(header_files):
         if len(name_stack) == 0:
            print "Error: Attempted to add source with no library build.info specifed.  In dir: %s"%pj(base_dir,cur_dir)
            sys.exit(1)
         lib_name = name_stack[-1]
         lib_map[lib_name].source_files     += source_files
         lib_map[lib_name].header_files     += header_files
         lib_map[lib_name].test_files       += test_files
         lib_map[lib_name].unittest_files   += unittest_files

      # Recurse into subdirectories
      for d in dirs:
         if not os.path.basename(d) in dir_ignores:
            scan_libs(base_dir, d, copy.copy(name_stack))
   
   # Trigger recursive scanning of library directorties
   if not verbose_build:
      print "Scanning libraries: ",
   scan_libs(pj(os.getcwd(),"Source"), '', [])
   if not verbose_build:
      print "  found %s libraries"%len(lib_map)
   
   # Add lexer to the build
   addScanParseSkel(common_env) 

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
   print "Using prefix: ", paths['base']         
   common_env.Append(CPPPATH = [paths['include'],pj(paths['include'],"OpenSG")])
      
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
                "OSG_WITH_ZLIB":zlib_option.isAvailable()
               }
   if "win32" == platform:   # Win32 specific defines
      definemap.update( {"OSG_WIN32_ASPECT_USE_LOCALSTORAGE": common_env["win_localstorage"],} )
   else:
      definemap.update( {"OSG_PTHREAD_ELF_TLS":(common_env["pthread_elf_tls"],"Use elf tls with pthreads."),} )
   
   common_env.DefineBuilder(pj(paths["include"],"OpenSG","OSGConfigured.h"),Value(definemap), 
                            definemap=definemap)
   
   # Unit Testing framework
   # - Build the framework
   if common_env["enable_unittests"]:      
      # common_env.Append(CXXFLAGS = "-H") # Use this for pch script generation
      # Until they have the SConstruct in their svn, let's just copy it over
      SConscript(pj("Tools", "unittest-cpp.SConstruct"))   
   
      # set the needed vars
      unittest_inc = pj(os.getcwd(),"Tools","unittest-cpp","UnitTest++","src");
      unittest_libpath = pj(os.getcwd(),"Tools","unittest-cpp","UnitTest++");
      unittest_lib = "UnitTest++";
      unittest_runner = pj(os.getcwd(),"Tools","UnitTestRunner.cpp");
      Export('unittest_inc', 'unittest_lib', 'unittest_libpath', 'unittest_runner')
   
      
   # ---- FOR EACH VARIANT ----- #   
   # This is the core of the build.
   if verbose_build:
      print "types: ",    variant_helper.variants["type"] 
      print "libtypes: ", variant_helper.variants["libtype"] 
      print "archs: ",    variant_helper.variants["arch"]    
      
   # We tread the first variant type special (auto link from libs here)
   default_combo_type = variant_helper.variants["type"][0][0]
   
   for combo in variant_helper.iterate(locals(), base_bldr, common_env):            
      #baseEnv = env_bldr.applyToEnvironment(common_env.Copy(), variant=combo,options=opts)      
      print "   Processing combo: ", ", ".join(['%s:%s'%(i[0],i[1]) for i in combo.iteritems()])

      inst_paths = copy.copy(paths)
      if "x64" == combo["arch"]:
         inst_paths['lib'] = inst_paths['lib'] + '64'                  
      inst_paths["lib_inst_combo"] = inst_paths["lib"]
      if GetPlatform() != "win32":
         if "debug" == combo["type"]:
            inst_paths["lib_inst_combo"] = pj(inst_paths["lib_inst_combo"],"debug")      
         else:
            inst_paths["lib_inst_combo"] = pj(inst_paths["lib_inst_combo"],"opt")      
      
      Export('build_env','inst_paths','opts', 'variant_pass','combo',
             'lib_map','boost_options', 
             'shared_lib_suffix','static_lib_suffix',
             'default_combo_type','verbose_build',)
      
      # Process subdirectories
      sub_dirs = ['Source']   
      full_build_dir = pj(buildDir,combo_dir)
      for d in sub_dirs:
         SConscript(pj(d,'SConscript'), build_dir=pj(full_build_dir, d), duplicate=0)
         
      # Build -config file based on first set installed
      if 0 == variant_pass:
         # - Create string using pprint.pformat that can build libmap (see osg-config.in for read)
         lib_map_build_list = []
         for (name,lib) in lib_map.iteritems():
            lib_map_build_list.append(lib.dump())
         lib_map_str = pprint.pformat(lib_map_build_list)

         submap = {'@LIB_MAP_STR@':lib_map_str,
                   '@PREFIX@':common_env["prefix"],
                   '@LIBPATH@':inst_paths["lib"],
                   '@INCPATH@':inst_paths["include"],
                   '@VERSION@':opensg_version_string,
                   '@LIBRARY_UTIL_SRC@':file(pj('Tools','scons-build','LibraryUtils.py')).read()}
         # Install two scripts so we have one with osg2 in the name to let users be sure they get the right version             
         for n in ["osg-config","osg2-config"]:
            osg_config = common_env.SubstBuilder(pj(paths['bin'],n),
                                    'osg-config.in', submap=submap)   
            common_env.AddPostAction(osg_config, Chmod('$TARGET', 0755))
            common_env.Depends(osg_config, Value(lib_map_str))

   
   common_env.Alias('install', paths['base'])   
   
   # Close up with aliases and defaults   
   Default('.')

