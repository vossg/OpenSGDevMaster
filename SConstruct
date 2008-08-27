#!python
#
# SCons build script for OpenSG
import os, string, sys, re, glob, copy, types, traceback, pprint, tempfile, shutil
pj = os.path.join

# If we have wingide, try loading the debugging extenstions
try:
   import wing.wingdbstub
   print "Loaded wingdb stub for debugging..."
except:
   pass

# Extend paths for scons-addons and scons-build if needed
# - this allows a development version of scons-addons to be
#   in the standard python path and used instead.
try:
   import SConsAddons.Util
   print "Using SConsAddons from: ", os.path.dirname(SConsAddons.Util.__file__)
except:
   sys.path.insert(0,pj('Tools','scons-addons','src'))
   print "Using SConsAddons from: Tools/scons-addons/src"

sys.path.insert(0,pj('Tools','scons-build'))

print "-------------------------------------------------"
print "WARNING: The build is currently in development.  "
print "            - It needs the svn version of scons-addons"
print "WARNING:"

import SCons.Environment
import SCons
import SConsAddons.Util as sca_util
import SConsAddons.Options as sca_opts
import SConsAddons.Variants as sca_variants
import SConsAddons.Builders
import SConsAddons.Options.Boost
import SConsAddons.Options.VTK
from SConsAddons.EnvironmentBuilder import EnvironmentBuilder
from LibraryUtils import *
from sets import Set
from socket import gethostname

import OpenSG.AddOnHacks
import OpenSG.ColladaOption

from BuildInfoScanner import BuildInfoScanner
from RevisionTagWriter import RevisionTagWriter

# If we have pysvn, load it
try:
   import pysvn
   have_pysvn = True
except:
   have_pysvn = False

# Aliases
GetPlatform = sca_util.GetPlatform
Export('GetPlatform')
verbose_build = False

# Build TODO
# - Support selection of WS/ES
# - Support selection of compiler to build with
# - QT support
# - Contrib libraries
# - Library specific defines (if needed)
# - Build on windows
# - Project files for windows

# ---------------------------------------------------------------------------- #
# ------------------------------ HELPER METHODS ------------------------------ #
# ---------------------------------------------------------------------------- #

# ---------------- #
# --- BUILDERS --- #
# ---------------- #

# fcd2code builder
# - Custom builder for fcd2code
def registerfcd2codeBuilder(env, required=True):
   print "Setting up fcd2code builder...",
   
   fcd2code_cmd = pj("Tools", "fcd2code","fcd2code")
   fcd2code_cmd = os.path.abspath(fcd2code_cmd)
   if not os.path.isfile(fcd2code_cmd):
      print " Warning: fcd2code not found at: ", fcd2code_cmd
      if required:
         sys.exit(1)
      return
   
   template_files = glob.glob(pj("Tools",
                                 "fcd2code",
                                 "*TemplateFieldContainer*Base*.txt"))

   template_files.append(glob.glob(pj("Tools",
                                      "fcd2code",
                                      "*TemplateFieldContainer*Field*.txt")))

   template_files.append(glob.glob(pj("Tools",
                                      "fcd2code",
                                      "*.py")))


   
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
   
   
   fcd2code_builder = Builder(action = " ".join([sys.executable, fcd2code_cmd]) + ' -c -b -d $SOURCE -p ${TARGET.dir}',
                              src_suffix = '.fcd',
                              suffix = 'unused.h',
                              emitter = prop_emitter)
   env.Append(BUILDERS = {'fcd2code' : fcd2code_builder})
   print "[OK]"


# fbd2code builder
# - Custom builder for fbd2code
def registerfbd2codeBuilder(env, required=True):
   print "Setting up fbd2code builder...",
   
   fbd2code_cmd = pj("Tools", "fcd2code","fcd2code")
   fbd2code_cmd = os.path.abspath(fbd2code_cmd)
   if not os.path.isfile(fbd2code_cmd):
      print " Warning: fcd2code not found at: ", fbd2code_cmd
      if required:
         sys.exit(1)
      return
   
   template_files = glob.glob(pj("Tools",
                                 "fcd2code",
                                 "*TemplateFieldBundle*Base*.txt"))

   template_files.append(glob.glob(pj("Tools",
                                      "fcd2code",
                                      "*TemplateFieldBundle*Field*.txt")))

   template_files.append(glob.glob(pj("Tools",
                                      "fcd2code",
                                      "*Template*.py")))
   
   def prop_emitter(target,source,env, template_files=template_files):
      """ Returns a list of files including all output forms and
          The input templates as sources.
      """
      assert str(source[0]).endswith(".fbd")
      assert len(source) == 1

      base_name = os.path.splitext(str(source[0]))[0]

      # Targets are all the files that we build
      target = []
      for ext in ["Base.cpp","Base.h","Base.inl","Fields.h"]:
         target.append(base_name+ext)
      
      # Sources are the fbd file and all the template files
      source.extend(template_files)

      return (target, source)
   
   
   fbd2code_builder = Builder(action = " ".join([sys.executable,
                              fbd2code_cmd]) + ' -c -b -B -d $SOURCE -p ${TARGET.dir}',
                              src_suffix = '.fbd',
                              suffix = 'unused.h',
                              emitter = prop_emitter)
   env.Append(BUILDERS = {'fbd2code' : fbd2code_builder})
   print "[OK]"


def addScanParseSkel(common_env):
   """ This is an ugly hack to add the lex/yacc support into the build.  It is ugly because of a couple of things.
      - We use some very custom flags
      - We need to post process the scanner to include a different file then normal.
      - We are forcing this to be done in the source tree in a subdir without actually going there.
      - Dependency management seems to be a little messed up right now in the code or scons.
      - BUGS: Scons does not seem to recognize that the files we are building here are source
              files for the libraries.  This makes it so we have to run the build twice if the files change.
              Scons cannot recognize whether the existing files are current or not, if they come out of 
               svn. This can result in spurious regens, which break the code if the wrong versions of 
               flex/bison are present.
   """
   # Hack to handle the generation of the parser from .y
   # This pretty hacky to allow using a version of the file from the repository if yacc is not installed
   # 1. Call bison: OSGScanParseSkelParser.yy -> OSGScanParseSkelParser.hpp .cpp .output (we don't need the last one)
   if "yacc" in common_env["TOOLS"]:
      if common_env["enable_scanparse_regen"]:
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
         print "WARNING: enable_scanparse_regen disabled. If you change .yy files they will not be rebuilt."
         common_env["TOOLS"].remove('yacc')
   else:
      print "WARNING: bison not available.  If you change .yy files they cannot be rebuilt."
   
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

      if common_env["enable_scanparse_regen"]:
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
         print "WARNING: enable_scanparse_regen disabled. If you change .ll files they will not be rebuilt."
         common_env["TOOLS"].remove('lex')
   else:
      print "WARNING: flex not available.  If you change .ll files they cannot be rebuilt."

# -------------------- #
# --- OPTION TYPES --- #
# -------------------- #

class SimpleAppendOption(sca_opts.SimpleOption):
   """
   Variant of the simple option wrapper that appends a value to the environment instead
   of replacing it.
   """
   def __init__(self, name, key, help):
      """
      Create an option
      name - the name of the commandline option
      key - the name of the key in the environment to append to
      help - Help text about the option object
      """
      sca_opts.SimpleOption.__init__(self, name, name, help + " (Use ':' to separate multiple)", \
                                     None, None, None, None)
      self.key = key

   """
   We want these options to be applied before all others, to have them have effect on e.g.
   StandardPackageOption tests, so override completeProcess instead of apply.
   """
   def completeProcess(self, env):
      if self.value:
         for i in self.value.split(os.pathsep):
            exec("env.Append(%s = [i])" % self.key)

# ---------------------------------------------------------------------------- #
# ----------------------------- Main build setup ----------------------------- #
# ---------------------------------------------------------------------------- #

EnsureSConsVersion(0,96,92)
SourceSignatures('MD5')
#SourceSignatures('timestamp')
opensg_version_string = file("VERSION").readline().strip()

print "Building OpenSG ", opensg_version_string

OpenSG.AddOnHacks.apply()

# Allow user to pass an options file on the command line, with the
# option_file=myOptFile syntax

platform = sca_util.GetPlatform()
unspecified_prefix = "use-instlinks"


# Create base environment to use for option processing
if GetPlatform() == "win32":
   # XXX: Temp hack to get msvs version setting
   if ARGUMENTS.has_key("MSVS_VERSION"):
      common_env = Environment(MSVS_VERSION=ARGUMENTS["MSVS_VERSION"], 
                                tools = ['default', 'doxygen'], 
                                toolpath = '.')
   else:
      common_env = Environment(tools = ['default', 'doxygen'], toolpath = '.')
else:
   if ARGUMENTS.has_key("icc"):
      use_cxxlib_icc = False

      if ARGUMENTS.has_key("cxxlib-icc"):
         use_cxxlib_icc = True

      common_env = Environment(ENV = os.environ,
                               tools=['gnulink', 'intelicc', 'intelicpc', 'doxygen'],
                               cxxlib_icc=use_cxxlib_icc, 
                               toolpath = ['.', 'Tools/scons-build/OpenSG/Tools'])
   else:
      common_env = Environment(ENV = os.environ, 
                               toolpath = ['.', 'Tools/scons-build/OpenSG/Tools'],
                               tools = ['g++', 'gcc', 'gnulink', 'osg_yacc',
                                        'osg_lex', 'doxygen'])

SConsignFile('.sconsign.'+GetPlatform()+common_env.subst('$CXX'))
buildDir = "build." + platform + '.' + common_env.subst('$CXX')

option_filename = "option.cache." + platform + '.' + common_env.subst('$CXX')

if ARGUMENTS.has_key("options_file"):
   opt_file = ARGUMENTS["options_file"]
   if os.path.exists(opt_file):
      print "Reading options from: %s" % str(opt_file)
      option_filename = opt_file
   else:
      print "Options file '%s' not found.. will continue with default '%s'" % \
      (opt_file, option_filename)

# Check if the GL subdir should be used - can not be done with the regular options
# stuff as sca_opts.StandardPackageOption for glut depends on this value
if ARGUMENTS.has_key("disable_glut_glsubdir") and ARGUMENTS["disable_glut_glsubdir"]:
    glsubdir = ""
else:
    glsubdir = "GL/"

# Setup the directories used for sconf processing
common_env["CONFIGUREDIR"] = '.sconf_temp_'+platform+'_'+common_env.subst('$CXX')
common_env["CONFIGURELOG"] = 'sconf.log_'+platform+'_'+common_env.subst('$CXX')
if common_env.has_key("MSVS"):
   common_env["CONFIGUREDIR"] += "." + common_env["MSVS"]["VERSION"]
   common_env["CONFIGURELOG"] += "." + common_env["MSVS"]["VERSION"]

SConsAddons.Builders.registerDefineBuilder(common_env)
SConsAddons.Builders.registerSubstBuilder(common_env)

# Create variant helper and builder
variant_helper = sca_variants.VariantsHelper(variantKeys=["type", "arch"])
base_bldr = EnvironmentBuilder()

# ----------------- #
# --- CONFIGURE --- #
# ----------------- #

# There is nothing to do ATM - sca_opts.StandardPackageOption can handle
# everything so far.

# --------------- #
# --- OPTIONS --- #
# --------------- #

# Options are stored in one of these groups:
# - required_libs_options:  Libraries needed to build OpenSG
# - optional_libs_options:  Libraries needed for/providing additional functionality
# - build_options:          Options to select build/install directories and
#                           special build steps.
# - feature_options:        Options to enable/disable or tweak certain features
#                           of OpenSG.
# - misc_options:           Options that do not fit anywhere else.
# - extra_libs_options:     Should not be changed - it's only to allow building
#                           with additional libraries that are not integrated into
#                           the build
#
# There is special handling for image formats, because some are directly
# supported and others require external libs, they may end up in different
# option groups, but in the help message they should show up together - see below.

#
# 1) Setup options
#    Create Option objects and store them in their group.

opts = sca_opts.Options(files = [option_filename, 'options.custom'],
                                   args= ARGUMENTS)

# Handle library name differences between platforms
if "win32" == platform:
    glut_libname = "glut32"
    tiff_libname = "tif32"
    zlib_libname = "zlib"
    jpeg_libname = "libjpeg"
    png_libname = "libpng"
else:
    glut_libname = "glut"
    tiff_libname = "tiff"
    zlib_libname = "z"
    jpeg_libname = "jpeg"
    png_libname = "png"


# Build options - source and destination directories etc.
build_options = {}
build_options["install_prefix"] = sca_opts.SimpleOption(
    "prefix", "prefix", "Installation prefix", unspecified_prefix, None, None, None)
build_options["build_suffix"] = sca_opts.SimpleOption(
    "build_suffix", "build_suffix",
    "Suffix to append to build directory.  Useful for compiling multiple variations on the same platform",
    "", None, None, None)
build_options["enable_fcd2code"] = sca_opts.BoolOption(
    "enable_fcd2code", "Enable code generation pass (from .fcd files) during build", False)
build_options["enable_fbd2code"] = sca_opts.BoolOption(
    "enable_fbd2code", "Enable code generation pass (from .fbd files) during build", False)
build_options["enable_distcc"] = sca_opts.BoolOption(
    "enable_distcc", "Enable use of distcc during build. (distcc must be in your path)", False)
build_options["enable_unittests"] = sca_opts.BoolOption(
    "enable_unittests", "Enable building and running of the unit tests after build", True)
build_options["enable_revision_tags"] = sca_opts.BoolOption(
    "enable_revision_tags", "Enable updating of OSG*Def.cpp files with current svn revision numbers", False)
build_options["enable_gv_beta"] = sca_opts.BoolOption(
    "enable_gv_beta", "Enable gv testing stuff", False)

# Options for required external libraries
required_libs_options = {}
if "win32" == platform:

    toolset = "auto"

    if common_env.has_key("MSVS"):
       toolset = 'vc' + common_env["MSVS"]["VERSION"].replace('.', '')

    required_libs_options["boost"] = sca_opts.Boost.Boost(
        "boost", "1.31.0", libs = ["filesystem"], required = True, 
        useVersion = True, allowLibNameFallbacks=True, toolset = toolset);
else:
    required_libs_options["boost"] = sca_opts.Boost.Boost(
        "boost", "1.31.0", libs = ["filesystem"], required = True, useVersion = True, allowLibNameFallbacks=True);

# Options for optional external libraries
optional_libs_options = {}
optional_libs_options["jpeg"] = sca_opts.StandardPackageOption(
    "jpeg", "Location of the JPEG library", library = jpeg_libname, required = False)

optional_libs_options["tiff"] = sca_opts.StandardPackageOption(
    "tiff", "Location of the TIFF library", library = tiff_libname, required = False)

optional_libs_options["png"] = sca_opts.StandardPackageOption(
    "png", "Location of the PNG library", library = png_libname, required = False)

optional_libs_options["glut"] = sca_opts.StandardPackageOption(
    "glut", "Location of the GLUT library", library = glut_libname,
    header = glsubdir + "glut.h", required = False)

optional_libs_options["X"] = sca_opts.StandardPackageOption(
    "X", "Location of the X library", library = 'X11',
    required = False)

optional_libs_options["freetype"] = sca_opts.StandardPackageOption(
    "freetype", "Location of freetype2 library", library = "freetype",
    header = "freetype/config/ftheader.h", required = False)

if "win32" != platform:
   optional_libs_options["freetype"].incDir = '/usr/include/freetype2'

optional_libs_options["fontconfig"] = sca_opts.StandardPackageOption(
    "fontconfig", "Location of fontconfig library", library = "fontconfig",
    header = "fontconfig/fontconfig.h", required = False)

optional_libs_options["zlib"] = sca_opts.StandardPackageOption(
    "zlib", "Location of the zlib compression library", library = zlib_libname,
    header = "zlib.h", required = False)

optional_libs_options["NVPerfSDK"] = sca_opts.StandardPackageOption(
    "NVPerfSDK", "Location of the NVPerfSDK library", library = "NVPerfSDK",
    header = "NVPerfSDK.h", required = False)

collada_lib_prefix = ""
if "win32" == platform:
    collada_lib_prefix = "lib"
optional_libs_options["collada"] = OpenSG.ColladaOption.ColladaOption(
    "collada", "Location of the collada dom library", library =
    ["%scollada_dae" % collada_lib_prefix,
     "%scollada_LIBXMLPlugin" % collada_lib_prefix,
     "%scollada_STLDatabase" % collada_lib_prefix,
     "%scollada_dom" % collada_lib_prefix,
     "%scollada_stdErrPlugin" % collada_lib_prefix,
     "%scollada_dae" % collada_lib_prefix],
    header = "dae/daeIntegrationObject.h", required = False)

xml2_lib = ["xml2"]
if "win32" == platform:
    # Link against the static versions of libiconv and libxml2 on Windows.
    xml2_lib = ["iconv_a", "libxml2_a"]
optional_libs_options["xml2"] = sca_opts.StandardPackageOption(
    "xml2", "Location of the xml2 library", library = xml2_lib,
    required = False)

vtk_libs = ['vtkRendering',
            'vtkIO',
            'vtkGraphics',
            'vtkImaging',
            'vtkFiltering',
            'vtkCommon',
            'vtkftgl',
            'vtkDICOMParser',
            'vtksys',
#            'verdict',
            'vtkNetCDF'
#            'vtkmetaio'
            ]

#if "win32" != platform:
#    vtk_libs.append('vtkMPEG2Encode')

optional_libs_options['vtk'] = sca_opts.VTK.VTK(
   "vtk",
   "Location of the vtk libraries",
   required = False,
   libList = vtk_libs)

# Feature options - select library/interface features
feature_options = {}
feature_options["gif"] = sca_opts.BoolOption(
    "enable_gif", "Enable GIF support", True)

feature_options["fcptr_mode"] = sca_opts.EnumOption(
    "fcptr_mode", "Select the mode for field container pointers",
    "MT_CPTR", ["SINGLE_THREAD", "MT_CPTR"])

feature_options["disable_deprecated"] = sca_opts.BoolOption(
    "disable_deprecated", "Disable deprecated interfaces and code", False)

feature_options["disable_glut_glsubdir"] = sca_opts.BoolOption(
    "disable_glut_glsubdir", "Do not use GL subdir when including glut.h", False)

feature_options["enable_osg1_compat"] = sca_opts.BoolOption(
    "enable_osg1_compat", "Enable OpenSG 1.x compatibility", False)

feature_options["enable_deprecated_props"] = sca_opts.BoolOption(
    "enable_deprecated_props", "Enable deprecated property types.", False)

feature_options["enable_new_osb_io"] = sca_opts.BoolOption(
    "enable_new_osb_io", "Enable the new OSB IO facilities.", False)

feature_options["enable_scanparse_regen"] = sca_opts.BoolOption(
    "enable_scanparse_regen", "Enable regenerating the scanner/parser files using flex and bison", False);

feature_options["enable_testcontainer"] = sca_opts.BoolOption(
    "enable_testcontainer", "Enable container used for testing (from Source/Test)", False)

feature_options["enable_gldefinemapper"] = sca_opts.BoolOption(
    "enable_gldefinemapper", "Enable GLDefinemapper so gl constants are read/written as GL_XXX", False)

feature_options["docs_mode"] = sca_opts.EnumOption(
    "docs_mode", "Select the mode for documentation generation",
    "NONE", ["NONE", "STANDALONE", "TRAC", "DEVELOPER"])

feature_options["enable_valgrind_checks"] = sca_opts.BoolOption(
    "enable_valgrind_checks", "Enable valgrind check code embedded in OpenSG.", False)

feature_options["enable_memory_debugging"] = sca_opts.BoolOption(
    "enable_memory_debugging", "Enable memory debugging checks in OpenSG.", False)

feature_options["enable_scanparse_in_builddir"] = sca_opts.BoolOption(
    "enable_scanparse_in_builddir", "Enable scanparse files generated into the builddir", False)

if "win32" == platform:
    feature_options["enable_win_localstorage"] = sca_opts.BoolOption(
        "enable_win_localstorage", "Enable use of local storage instead of __declspec to "+
        "get thread local storage on windows", True)

if "win32" != platform:
    feature_options["enable_elf_localstorage"] = sca_opts.BoolOption(
        "enable_elf_localstorage", "Enable use of elf thread local storage with pthreads",
        ("linux" == platform))

# Misc options
misc_options = {}
#misc_options["icc_compat"] = sca_opts.SimpleOption(
#    "icc_gnu_compat", "icc_gnu_compat", "<GCC Version> Make the binaries built " +
#                      "with icc compatible with the given verion of gcc. (unsupported)",
#                      "", None, None, None)

# Options to specify additional library/header search paths and librarys to
# link agains.
extra_libs_options = {}
extra_libs_options["incdir"] = SimpleAppendOption('add_incdir', 'CPPPATH', 'Additional include dir')
extra_libs_options["libdir"] = SimpleAppendOption('add_libdir', 'LIBPATH', 'Additional library dir')
extra_libs_options["lib"]    = SimpleAppendOption('add_lib',    'LIBS',    'Additional library')

# Group all image format options together.
image_format_options = {}
image_format_options["jpeg"] = optional_libs_options["jpeg"]
image_format_options["tiff"] = optional_libs_options["tiff"]
image_format_options["png"]  = optional_libs_options["png"]
image_format_options["gif"]  = feature_options["gif"]

#
# 2) Register options
#    This should not require any changes unless a new option group is added.

for opt in extra_libs_options.itervalues():
    if opt not in image_format_options.itervalues():
        opts.AddOption(opt)

opts.AddOption(sca_opts.SeparatorOption("\nBuild/Install settings"))
for opt in build_options.itervalues():
    if opt not in image_format_options.itervalues():
        opts.AddOption(opt)

opts.AddOption(sca_opts.SeparatorOption("\nPackage settings (required libs)"))
for opt in required_libs_options.itervalues():
    if opt not in image_format_options.itervalues():
        opts.AddOption(opt)

opts.AddOption(sca_opts.SeparatorOption("\nPackage settings (optional libs)"))
for opt in optional_libs_options.itervalues():
    if opt not in image_format_options.itervalues():
        opts.AddOption(opt)

for opt in image_format_options.itervalues():
    opts.AddOption(opt)


opts.AddOption(sca_opts.SeparatorOption("\nAdvanced options"))
for opt in feature_options.itervalues():
    if opt not in image_format_options.itervalues():
        opts.AddOption(opt)

for opt in misc_options.itervalues():
    if opt not in image_format_options.itervalues():
        opts.AddOption(opt)

# Add environment builder options
base_bldr.addOptions(opts)

# Add variant building options
variant_helper.addOptions(opts)

#
# 3) Process options

try:
   opts.Process(common_env)
except Exception, ex:
   if not SConsAddons.Util.hasHelpFlag():
      print "Option error: ", str(ex)
      traceback.print_exc()
      sys.exit(1)

#
# 4) Generate help message

help_text = \
"""--- OpenSG Build system ---
%s
Targets:
   install - Install OpenSG
      ex: 'scons install prefix=$HOME/software' to install in your account
   Type 'scons' to just build it

""" % (opts.GenerateHelpText(common_env),)

Help(help_text)

# --------------------------------------------------------------------------- #
# ---------------------------- MAIN BUILD STEPS ----------------------------- #
# --------------------------------------------------------------------------- #

# If we are running the build
if not SConsAddons.Util.hasHelpFlag():
   try:                                   # Try to save the options if possible
      if not ARGUMENTS.has_key("options_file"):
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
   if common_env["enable_fcd2code"]:
      registerfcd2codeBuilder(common_env)
      
      fcd_files = []
      for root, dirs, files in os.walk(pj(os.getcwd(),'Source')):
         fcd_files += [pj(root,f) for f in files if f.endswith(".fcd")]
      
      for f in fcd_files:
         fcd_targets = common_env.fcd2code(source=f)
         NoClean(fcd_targets)
   
   # .fbd processing
   if common_env["enable_fbd2code"]:
      registerfbd2codeBuilder(common_env)
      
      fbd_files = []
      for root, dirs, files in os.walk(pj(os.getcwd(),'Source')):
         fbd_files += [pj(root,f) for f in files if f.endswith(".fbd")]
      
      for f in fbd_files:
         fbd_targets = common_env.fbd2code(source=f)
         NoClean(fbd_targets)

   # Distcc enable
   if common_env["enable_distcc"] and WhereIs("distcc"):
      common_env.Prepend(CXX = "distcc ", CC = "distcc ")


   # Trigger recursive scanning of library directorties
   if not verbose_build:
      print "Scanning libraries: ",
   biScanner = BuildInfoScanner("Source", opts, common_env,
                                [".svn", "ES", "EGL"], verbose_build)
   lib_map   = biScanner.scan()
   if not verbose_build:
      print "  found %s libraries" % len(lib_map)
   
   # Add lexer to the build
#   addScanParseSkel(common_env)      
      
   # -- Common builder settings
   variant_helper.readOptions(common_env)
   base_bldr.readOptions(common_env)
   #base_bldr.enableWarnings()
   base_bldr.enableWarnings(EnvironmentBuilder.MINIMAL)
   
   # Apply any common package options
   # Update environment for boost options
   required_libs_options["boost"].apply(common_env)
     
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

   if not common_env.has_key("icc_gnu_compat"):
      common_env["icc_gnu_compat"] = False
   
   # ---- Generate OSGConfigured.h --- #
   definemap = {"OSG_DISABLE_DEPRECATED"      : (common_env["disable_deprecated"],
                                                 "Disable interface that will go away in the future"),
                "OSG_NO_GLUT_GLSUBDIR"        : (common_env["disable_glut_glsubdir"],
                                                 "Don't use GL subdir for glut"),
                "OSG_MT_CPTR_ASPECT"          : ("MT_CPTR" == common_env["fcptr_mode"]),
                "OSG_1_COMPAT"                : common_env["enable_osg1_compat"],
                "OSG_DEPRECATED_PROPS"        : common_env["enable_deprecated_props"],
                "OSG_NEW_OSB_IO"              : common_env["enable_new_osb_io"],
                "OSG_ICC_GNU_COMPAT"          : common_env["icc_gnu_compat"],
                "OSG_ENABLE_VALGRIND_CHECKS"  : common_env["enable_valgrind_checks"],
                "OSG_ENABLE_MEMORY_DEBUGGING" : common_env["enable_memory_debugging"],
                
                "OSG_WITH_JPG"                : image_format_options["jpeg"].isAvailable(),
                "OSG_WITH_TIF"                : image_format_options["tiff"].isAvailable(),
                "OSG_WITH_PNG"                : image_format_options["png"].isAvailable(),
                "OSG_WITH_GIF"                : image_format_options["gif"].getValue(),
                "OSG_WITH_GLUT"               : optional_libs_options["glut"].isAvailable(),
                "OSG_WITH_ZLIB"               : optional_libs_options["zlib"].isAvailable(),
                "OSG_WITH_NVPERFSDK"          : optional_libs_options["NVPerfSDK"].isAvailable(),
                "OSG_WITH_VTK"                : optional_libs_options["vtk"].isAvailable(),
                "OSG_WITH_COLLADA"            : optional_libs_options["collada"].isAvailable(),
                "OSG_GV_BETA"                 : common_env["enable_gv_beta"],
                "OSG_GL_DEFMAPPER"            : common_env["enable_gldefinemapper"],
                "OSG_PREBUILD_SCANPARSE"      : not common_env["enable_scanparse_in_builddir"]
               }
   if "win32" == platform:   # Win32 specific defines
      definemap.update(
         {"OSG_WIN32_ASPECT_USE_LOCALSTORAGE" : (common_env["enable_win_localstorage"],
                                                 "Enable use of local storage instead of __declspec."),} )
   else:
      definemap.update(
         {"OSG_PTHREAD_ELF_TLS" : (common_env["enable_elf_localstorage"], "Use elf tls with pthreads."),
          "OSG_WITH_FT2"        : optional_libs_options["freetype"].isAvailable(),
          "OSG_WITH_FONTCONFIG" : optional_libs_options["fontconfig"].isAvailable()
         } )

   if "darwin" == platform:
      definemap.update( {"OSG_WITH_GLUT" : True,} )
   
   common_env.DefineBuilder(pj(paths["include"], "OpenSG", "OSGConfigured.h"),
                            Value(definemap), definemap=definemap)

   if "win32" == platform:
       common_env.Append(LINKFLAGS = SCons.Util.CLVar('/nodefaultlib'))

   #common_env.Append(CXXFLAGS = "-H") # Use this for pch script generation
   
   # Unit Testing framework
   # - Build the framework
   if common_env["enable_unittests"]:
      # Until they have the SConstruct in their svn, let's just copy it over
      SConscript(pj("Tools", "unittest-cpp.SConstruct"))
      
      # set the needed vars
      unittest_inc     = pj(os.getcwd(), "Tools", "unittest-cpp", "UnitTest++", "src")
      unittest_libpath = pj(os.getcwd(), "Tools", "unittest-cpp", "UnitTest++")
      unittest_lib     = "UnitTest++"
      unittest_runner  = pj(os.getcwd(), "Tools", "UnitTestRunner.cpp")
      Export('unittest_inc', 'unittest_lib', 'unittest_libpath', 'unittest_runner')
   
   # Revision tracking
   # For each library, find its Def.cpp file(s) and set the revision to the highest one found
   # in the source tree. Recommended before building anything that's distributed (dailybuild, release etc.)
   # This could go into scons-addons at some point...
   if common_env["enable_revision_tags"]:
      tagWriter = RevisionTagWriter(lib_map)
      tagWriter.run()
      
   # Documentation
   if "NONE" != common_env["docs_mode"] and not ARGUMENTS.has_key("ignore_docs"):
      # Todo: 
      #   - put output into build dir
      #   - handle different doc levels
      #   - handle different output types

      # Get all used source/header files
      dox_inp = "INPUT = "
      for (name,lib) in lib_map.iteritems():
         for i in lib.doc_extra_files:
            dox_inp += "../" + i + " "

         if ARGUMENTS.has_key("simple_docs"):
            for i in lib.doc_source_files:
               dox_inp += "../" + i + " "
            for i in lib.doc_header_files:
               dox_inp += "../" + i + " "
         else:
            for i in lib.source_files:
               dox_inp += "../Source/" + i + " "
            for i in lib.header_files:
               dox_inp += "../Source/" + i + " "

      # Write it to a file that's included by doxygen
      # Need to do this to avoid environment size problems
      f = open(pj("Doc","opensg_input.doxy"), 'w')
      f.write(dox_inp)
      f.close()
      
      # Need to use my private doxygen version until the parameter macro patch is in
      if "dream.lite3d.com" == gethostname():
         common_env["DOXYGEN"] = "/home/reiners/software/DocumentationTools/doxygen-cvs/doxygen-070225/bin//doxygen"
      common_env["DOX_VERSION"] = opensg_version_string
      
      if "STANDALONE" == common_env["docs_mode"]:
         common_env.Doxygen(pj("Doc","standalone.doxy"))
      elif "TRAC" == common_env["docs_mode"]:
         common_env.Doxygen(pj("Doc","trac.doxy"))
      elif "DEVELOPER" == common_env["docs_mode"]:
         common_env.Doxygen(pj("Doc","developer.doxy"))
      else:
         raise "Unknown docs_mode %s" % common_env["docs_mode"]
      
   if not ARGUMENTS.has_key("docs_only"):

      # ---- FOR EACH VARIANT ----- #
      # This is the core of the build.
      if verbose_build:
         print "types: ",    variant_helper.variants["type"]
         #print "libtypes: ", variant_helper.variants["libtype"]
         print "archs: ",    variant_helper.variants["arch"]
      
      # We tread the first variant type special (auto link from libs here)
      try:
         default_combo_type = variant_helper.variants["type"][0][0]
      except:
         default_combo_type = None
      
      # XXX: This is a hack to deal with what seems to be a bug in SCons. It
      # sets up the shared linker flags for the Apple GCC case to use -shared
      # instead of -dynamiclib.
      if "darwin" == platform:
         common_env['SHLINKFLAGS'] = SCons.Util.CLVar('$LINKFLAGS -dynamiclib')

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
      
         Export('build_env', 'inst_paths', 'opts', 'variant_pass', 'combo',
                'lib_map', 'shared_lib_suffix', 'static_lib_suffix',
                'default_combo_type', 'verbose_build')
      
         # Process subdirectories
         sub_dirs = ['Source']
         full_build_dir = pj(buildDir, combo_dir)
         for d in sub_dirs:
            SConscript(pj(d, 'SConscript'), build_dir = pj(full_build_dir, d), duplicate = 0)
      
         # Build -config file based on first set installed
         if 0 == variant_pass:
            # - Create string using pprint.pformat that can build libmap (see osg-config.in for read)
            lib_map_build_list = []
            for (name,lib) in lib_map.iteritems():
               lib_map_build_list.append(lib.dump())
            
               # Add an alias just for this lib and its unittests
               Alias(name[3:], [ pj(full_build_dir, "Source", "lib" + name + common_env["SHLIBSUFFIX"]), \
                                 pj(full_build_dir, "unittest", "run" + name)\
                               ])

            lib_map_str = pprint.pformat(lib_map_build_list)
  
            if "win32" == platform:
                inst_inc_path = inst_paths["include"].replace('\\','\\\\')
                inst_prefix   = common_env["prefix"].replace('\\','\\\\')
                inst_lib_path = inst_paths["lib"].replace('\\','\\\\')
            else:
                inst_inc_path = inst_paths["include"]
                inst_prefix   = common_env["prefix"]
                inst_lib_path = inst_paths["lib"]

            submap = {'@LIB_MAP_STR@'      : lib_map_str,
                      '@PREFIX@'           : inst_prefix,
                      '@LIBPATH@'          : inst_lib_path,
                      '@INCPATH@'          : inst_inc_path,
                      '@VERSION@'          : opensg_version_string,
                      '@LIBRARY_UTIL_SRC@' : file(pj('Tools','scons-build','LibraryUtils.py')).read()}
            # Install two scripts so we have one with osg2 in the name to let users be sure they get the right version
            for n in ["osg2-config"]:
               osg_config = common_env.SubstBuilder(pj(paths['bin'],n),
                                                    'osg-config.in', submap=submap)
               common_env.AddPostAction(osg_config, Chmod('$TARGET', 0755))
               common_env.Depends(osg_config, Value(lib_map_str))
   
   common_env.Alias('install', paths['base'])
   
   # Close up with aliases and defaults
   Default('.')

# ------------------------------------ #
# --- Helper classes and functions --- #
# ------------------------------------ #
