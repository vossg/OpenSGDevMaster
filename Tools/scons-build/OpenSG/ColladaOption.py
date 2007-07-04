
import os
from SConsAddons.Options import StandardPackageOption
import SCons.Util
from types import *

import SCons.SConf
Configure = SCons.SConf.SConf

pj = os.path.join

class ColladaOption(StandardPackageOption):

    def __init__(self,
                 name,
                 help,
                 header=None,
                 library=None,
                 symbol="main",
                 required=False):
        
        StandardPackageOption.__init__(self,
                                       name,
                                       help,
                                       header,
                                       library,
                                       symbol,
                                       required)
    def find(self,env):
        StandardPackageOption.find(self, env)

        print "CSDK  find"
        print self.baseDir

        if type(self.incDir) is StringType:
            if self.incDir and \
                   os.path.exists(pj(self.incDir, '1.4')):

                self.incDir = [self.incDir, pj(self.incDir, '1.4')]

        print "INC : ", self.incDir
        print "LIB : ", self.libDir

    def apply(self, env):

#        StandardPackageOption.apply(self, env)
#            
#            self.incDir = pj(self.baseDir, 'common', 'inc')
#
#        if self.libDir is None and \
#            os.path.exists(pj(self.baseDir, 'common', 'lib')):
#            
#            self.libDir = pj(self.baseDir, 'common', 'lib')
        
        if self.incDir:
            if self.verbose:
                print "Appending inc_dir:", self.incDir

            env.Append(CPPPATH = self.incDir)

        if self.libDir:
            if self.verbose:
                print "Appending lib_dir:", self.libDir

            env.Append(LIBPATH = [self.libDir])

        if self.library:
            if self.verbose:
                print "Adding lib:", self.library
            env.Append(LIBS = [self.library])

