#!python
try:
   import wing.wingdbstub;       # stuff for debugging
   print "Loaded wingdb stub for debugging..."
except:
   pass

import os, string, sys, re, glob, copy, types
#sys.path.insert(0,pj('tools','scons-addons','src'))
print "WARNING:"
print "WARNING: The build is currently in development.  It needs the svn version of scons-addons"
print "WARNING:"

import SCons.Environment
import SCons
import SConsAddons.Util as sca_util
import SConsAddons.Options as sca_opts
import SConsAddons.Variants as sca_variants
import SConsAddons.Builders
import SConsAddons.Options.CppUnit
import SConsAddons.Options.Boost
from SConsAddons.EnvironmentBuilder import EnvironmentBuilder

# Aliases
GetPlatform = sca_util.GetPlatform
Export('GetPlatform')
pj = os.path.join

# ------ HELPER METHODS -------- #

   
#------------------------------------------------------------------------------
# Main build setup
#------------------------------------------------------------------------------
EnsureSConsVersion(0,96)
SourceSignatures('MD5')
#SourceSignatures('timestamp')
SConsignFile('.sconsign.'+GetPlatform())

# Figure out what version of CppDom we're using
print "Building OpenSG."

platform = sca_util.GetPlatform()
unspecified_prefix = "use-instlinks"
buildDir = "build." + platform      
option_filename = "config.cache." + platform

# Create base environment to use for option processing
# - Register the substitution builder
# - Setup the directories used for sconf processing
if GetPlatform() == "win32":
   common_env = Environment()
else:
   common_env = Environment(ENV = os.environ)
SConsAddons.Builders.registerSubstBuilder(common_env)
common_env["CONFIGUREDIR"] = '.sconf_temp_'+platform
common_env["CONFIGURELOG"] = 'sconf.log_'+platform

# Create variant helper and builder
variant_helper = sca_variants.VariantsHelper()
base_bldr = EnvironmentBuilder()

# --------------- #
# --- OPTIONS --- #
# --------------- #
# Find all build.info files that may have options
build_info_files = []
for root, dirs, files in os.walk(os.getcwd()):
   build_info_files += [pj(root,f) for f in files if f == "build.info"]

print "Build info files found: ", build_info_files

opts = sca_opts.Options(files = [option_filename, 'options.custom'],
                                   args= ARGUMENTS)

# Create option objects
boost_options = SConsAddons.Options.Boost.Boost("boost","1.31.0",required=True)

# Setup options
opts.AddOption(sca_opts.SeparatorOption("\nStandard settings"))
opts.Add('prefix', 'Installation prefix', unspecified_prefix)
opts.AddOption(sca_opts.SeparatorOption("\nPackage Options"))
opts.AddOption( boost_options )
base_bldr.addOptions(opts)             # Add environment builder options
variant_helper.addOptions(opts)        # Add variant building options

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
   opts.Process(common_env)               # Process the options
   try:                                   # Try to save the options if possible
      opts.Save(option_filename, common_env)
   except LookupError, le:
      pass
   
   # --- Collect all Source and Header files --- #
   class LibraryInfo(object):
      """ Helper class for capturing all the files that we are finding in source tree. """
      def __init__(self, name=""):
         self.name = name
         self.source_files = []
         self.header_files = []
         self.test_files = []      
   
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
   # When evaluating build.info files:
   #   input vars:
   #      option_pass: If true, we are just trying to get options
   #      opts: If not none, this is an options object that can have options added
   #   output vars:
   #      library: Name of the library to add code to
   #      osg_lib_deps: OpenSG libraries that this one depends upon
   #      lib_deps: Standard libraries that this one depends upon

   lib_map = {"empty_lib":LibraryInfo("empty_lib")}    # Map from name to library we are using
   
   dir_ignores = [".svn", "ES"]

   def scan_libs(base_dir, cur_dir, name_stack):
      """ Scan library directory.
          base_dir: Directory to keep all paths relative to
          cur_dir: Directory to examine.
          name_stack: Current stack of library names
      """
      global lib_map
      print "dir: ", cur_dir
      full_dir = pj(base_dir, cur_dir)
      dir_contents = [pj(cur_dir,f) for f in os.listdir(full_dir)]
      files = [f for f in dir_contents if os.path.isfile(pj(base_dir,f))]
      dirs  = [d for d in dir_contents if os.path.isdir(pj(base_dir,d))]
      have_build_info = os.path.exists(pj(full_dir,"build.info"))
      if have_build_info:
         bi_filename = pj(full_dir,"build.info")
         print "   Evaluating: ", bi_filename         
         ns = {"option_pass":False, 
               "library":None,
               "osg_lib_deps":[],
               "lib_deps":[]}
         execfile(bi_filename, ns)
         if not ns.has_key("library"):
            print "Error: Must specify 'library' value in build.info file:", bi_filename
            sys.exit(1)         
         lib_name = ns["library"]
         if not lib_map.has_key(lib_name):
            lib_map[lib_name] = LibraryInfo(name=lib_name)
         name_stack.append(lib_name)
      
      test_files =   [f for f in files if os.path.basename(f).startswith("test") and f.endswith(".cpp")]
      source_files = [f for f in files if (os.path.splitext(f)[1] in [".cpp",]) and\
                                          (f not in test_files)]
      header_files = [f for f in files if os.path.splitext(f)[1] in [".h",".inl",".ins"]]      
      
      print "Adding to lib:[%s]  source: [%s]"%(name_stack[-1],source_files)
      lib_name = name_stack[-1]
      lib_map[lib_name].source_files += source_files
      lib_map[lib_name].header_files += header_files
      lib_map[lib_name].test_files   += test_files

      # Recurse into subdirectories
      for d in dirs:
         if not os.path.basename(d) in dir_ignores:
            scan_libs(base_dir, d, copy.copy(name_stack))
   
   scan_libs(pj(os.getcwd(),"Source"), '', ["empty_lib",])   
   
   # HACK: Work around issue with getting yacc output into a library
   if 0:
      parser_env = common_env.Copy()
      parser_env.Append(YACCFLAGS = ["-d","-v","-pOSGScanParseSkel_","-bOSGScanParseSkel_"])
      source_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
      target_file = "Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.tab.c"
      yfiles = parser_env.CFile(target=target_file, source=source_file)
      print "yfiles: ", yfiles

      lib_map["OSGFileIO"].source_files.append(yfiles[0])
      lib_map["OSGFileIO"].header_files.append(yfiles[1])

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
   paths['pkgconfig'] = pj(paths['lib'], 'pkgconfig')
   paths['include']   = pj(paths['base'], 'include')   
   paths['bin']       = pj(paths['base'], 'bin')   
   print "using prefix: ", paths['base']         
      
   print "types: ",    variant_helper.variants["type"] 
   print "libtypes: ", variant_helper.variants["libtype"] 
   print "archs: ",    variant_helper.variants["arch"] 
   
   sub_dirs = ['Source']   
   
   # ---- FOR EACH VARIANT ----- #   
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
      full_build_dir = pj(buildDir,combo_dir)      
      for d in sub_dirs:
         SConscript(pj(d,'SConscript'), build_dir=pj(full_build_dir, d), duplicate=0)

   
   common_env.Alias('install', inst_paths['base'])

   # Close up with aliases and defaults   
   Default('.')

