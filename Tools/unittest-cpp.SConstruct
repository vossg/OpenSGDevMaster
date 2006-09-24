#
# Trivial SCons build file for UnitTest++
#

import glob, os
import SCons
pj = os.path.join

base = pj("unittest-cpp","UnitTest++")

# Collect the sources. This assumes everything in the directory is needed
sources=glob.glob(pj(base, "src", "*.cpp"))
if os.name == "nt":
    os_dir = "Win32"
else:
    os_dir = "Posix"
sources += glob.glob(pj(base, "src", os_dir, "*.cpp"))

# Build the library
StaticLibrary(pj(base,"UnitTest++"), sources)

# Build the Tests
testsources=glob.glob(pj(base, "src", "tests", "*.cpp"))
Program(pj(base, "TestUnitTest++"), testsources, LIBS="UnitTest++", LIBPATH=base)

# Run the Test once the program is built
def runTest(target, source, env):
    os.system(str(target[0]))
    
AddPostAction(pj(base, "TestUnitTest++"), runTest)
