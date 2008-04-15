
import os
import os.path
import sys

import SCons.Util
import SConsAddons.Util as sca_util
from LibraryUtils import *

pj = os.path.join

class BuildInfoScanner(object):
    """
    Recursively scans a directory tree for build.info files and constructs
    a list of libraries and their dependencies from their contents.
    
    - Finding build.info files:
        Every file found can override the settings inherited from parent
        directories.
        - Keep a stack of library names, we add to the top library.
        - All subdirectories of the baseDir are scanned, unless it is in
        ignoredDirs.
        - File names are relative to baseDir
    
    - Evaluating a build.info file:
        Input variables:
        - option_pass: If True, we only collect options.
        - opts:        Either None or an Options object to add options to.
        - platform:    The current plarform string.
        - compiler:    The current compiler being used.
        Output variables:
        - library: Name of the library to which the current directory belongs.
        - stop_traversal: If True, ignore this directory and everything below it.
    
        - osg_dep_libs: List of OpenSG library names, this library depends upon (for linking).
        - libs: List of external library names, this library depends upon.
        - frameworks: List of framework names, this library depends upon.
        - cpppath: Additional include paths for building.
        - libpath: Additional library paths for linking.
        - frameworkpath: Additional framework paths to set.
    
        - osg_test_libs: List of OpenSG library names, this library depends
                        upon for builing tests.
        - other_test_libs: List of external library names, this library depends
                            upon for building tests.
        - test_cpppath: Additional include paths for building tests.
        - test_libpath: Additional library paths for linking tests.
    """

    def __init__(self, baseDir, opts, env, ignoredDirs = None, verbose = False):
        self.baseDir       = baseDir
        self.ignoredDirs   = ignoredDirs
        self.opts          = opts
        self.env           = env
        self.platform      = sca_util.GetPlatform();
        self.verbose       = verbose
        
        self.libMap        = {}
        self.libNameStack  = []
        self.libAttributes = ["osg_dep_libs", "libs", "frameworks", "cpppath",
                              "libpath", "frameworkpath","osg_test_libs",
                              "other_test_libs","test_cpppath",
                              "test_libpath", "cxx_flags"]
    
    def scan(self, scanDir = ""):
        """Scan for build.info files in baseDir/scanDir keeping all file paths
           relative to baseDir.
           Returns the library map constructed from the files.
        """
        self._recursiveScan(scanDir)
        return self.libMap

    def _recursiveScan(self, scanDir = ""):
        """The actual recursive scanning routine.
        """
        fullDir = pj(self.baseDir, scanDir)
        scanDirContents = [pj(scanDir, f) for f in os.listdir(fullDir)]
        files = [f for f in scanDirContents if os.path.isfile(pj(self.baseDir, f))]
        dirs  = [d for d in scanDirContents if os.path.isdir(pj(self.baseDir, d))]
        
        hasBuildInfo = os.path.exists(pj(fullDir, "build.info"))
        
        if hasBuildInfo:
            biFilename = pj(fullDir, "build.info")
            
            if self.verbose:
                print "    Reading: ", biFilename
            else:
                sys.stdout.write(".")
            
            biDict = dict([("option_pass",    False),
                           ("opts",           self.opts),
                           ("platform",       self.platform),
                           ("compiler",       self.env["CXX"]),
                           ("stop_traversal", False)])
            
            for attrib in self.libAttributes:
                biDict[attrib] = []
            
            execfile(biFilename, biDict)
            
            if biDict["stop_traversal"]:
                if self.verbose:
                    print "    Pruning traversal."
                return False
            
            if not biDict.has_key("library") or biDict["library"] == None:
                print "ERROR: No 'library' specified in build.info file: ", biFilename
                sys.exit(1)
            
            libName = biDict["library"]
            if not self.libMap.has_key(libName):
                self.libMap[libName] = LibraryInfo(name = libName)
                if self.verbose:
                    print "Created new LibraryInfo: ", libName
            
            self.libNameStack.append(libName)
            
            if self.verbose:
                print "Library name: ", libName
            
            # Add all the lib options from the evaluation
            # - Only add on the unique ones
            for attrib in self.libAttributes:
                attribList = getattr(self.libMap[libName], attrib)
                attribList.extend([a for a in biDict[attrib] if a not in attribList])

        # Collect source files from all directories and put them into
        # the active library object
        testFiles     = [f for f in files if (os.path.basename(f).startswith("test") and
                                              os.path.splitext(f)[1] in [".cpp",".cc",".mm"])];
        unittestFiles = [f for f in files if (os.path.basename(f).endswith("Test.cpp") and
                                              os.path.basename(f).startswith("OSG"))]
        sourceFiles   = [f for f in files if (os.path.splitext(f)[1] in [".cpp", ".cc", ".mm"] and
                                              os.path.basename(f).startswith("OSG") and
                                              f not in testFiles and f not in unittestFiles)]
        headerFiles   = [f for f in files if (os.path.splitext(f)[1] in [".h", ".inl", ".ins", ".hpp"] and
                                              os.path.basename(f).startswith("OSG"))]
        
        if self.env['enable_scanparse_in_builddir'] == True:
            parserFiles  = [f for f in files if (os.path.splitext(f)[1] in [".yy"] and
                                                 os.path.basename(f).startswith("OSG") )]
            lexerFiles   = [f for f in files if (os.path.splitext(f)[1] in [".ll"] and
                                                 os.path.basename(f).startswith("OSG") )]
        
            for f in parserFiles:
                sourceFiles.append(f)
                headerFiles.append(SCons.Util.splitext(f)[0] + '.hpp')

            for f in lexerFiles:
                sourceFiles.append(f)


#        print "FOO ", self.libNameStack
#        if len(self.libNameStack) != 0 and self.libNameStack[-1] == 'OSGSystem':
#            print sourceFiles
        

        # Add files to their library object
        if (len(testFiles) or len(unittestFiles) or
            len(sourceFiles) or len(headerFiles)):
            if len(self.libNameStack) == 0 or self.libNameStack[-1] == "":
                print "ERROR: Attempt to add source files without library.  " + \
                      "In dir: %s" % fullDir
                sys.exit(1)
            libName = self.libNameStack[-1]
            self.libMap[libName].source_files   += sourceFiles
            self.libMap[libName].header_files   += headerFiles
            self.libMap[libName].test_files     += testFiles
            self.libMap[libName].unittest_files += unittestFiles
        
        # Recurse into subdirectories
        for d in dirs:
            if not os.path.basename(d) in self.ignoredDirs:
                popStack = self._recursiveScan(d)
                if popStack:
                    del self.libNameStack[-1]
        
        # return if anything was added to the libNameStack
        if hasBuildInfo:
            return True
        else:
            return False
