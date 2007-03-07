#
# Trivial SCons build file for UnitTest++
#

import glob, os
import SCons
pj = os.path.join
import SConsAddons.Util as sca_util

base = pj("unittest-cpp","UnitTest++")

# We need to make this work with variants.
if sca_util.GetPlatform() == "win32":
   if ARGUMENTS.has_key("MSVS_VERSION"):
      base_env = Environment(MSVS_VERSION=ARGUMENTS["MSVS_VERSION"])
   else:
      base_env = Environment()

   base_env.Append(CXXFLAGS = ['/wd4530', '/MD'])
else:
   base_env = Environment(ENV = os.environ)

# Create a library environment because we do not want to link default libs.
lib_env = base_env.Copy()
if sca_util.GetPlatform() == "win32":
   lib_env.Append(ARFLAGS = SCons.Util.CLVar('/nodefaultlib'))

# Collect the sources. This assumes everything in the directory is needed
sources=glob.glob(pj(base, "src", "*.cpp"))
if os.name == "nt":
    os_dir = "Win32"
else:
    os_dir = "Posix"
sources += glob.glob(pj(base, "src", os_dir, "*.cpp"))

# Build the library
lib_env.StaticLibrary(pj(base,"UnitTest++"), sources)

# Build the Tests
testsources=glob.glob(pj(base, "src", "tests", "*.cpp"))
base_env.Program(pj(base, "TestUnitTest++"), testsources, LIBS="UnitTest++", LIBPATH=base)

# Run the Test once the program is built
def runTest(target, source, env):
    os.system(str(target[0]))
    
base_env.AddPostAction(pj(base, "TestUnitTest++"), runTest)
