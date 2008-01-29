import imp
import sys

import SCons.Builder
import SCons.Errors
import SCons.Scanner
import SCons.Scanner.C
import SCons.Scanner.D
import SCons.Scanner.LaTeX
import SCons.Scanner.Prog

def createCPPFileBuilders(env):
    """This is a utility function that creates the CFile/CXXFile
    Builders in an Environment if they
    are not there already.

    If they are there already, we return the existing ones.

    This is a separate function because soooo many Tools
    use this functionality.

    The return is a 2-tuple of (CFile, CXXFile)
    """

    try:
        cpp_file = env['BUILDERS']['CPPFile']
    except KeyError:
        cpp_file = SCons.Builder.Builder(action = {},
                                         emitter = {},
                                         suffix = {None:'$CPPFILESUFFIX'})
        env['BUILDERS']['CPPFile'] = cpp_file
        env['CPPFILESUFFIX'] = '.cpp'

    static_obj, shared_obj = SCons.Tool.createObjBuilders(env)

    static_obj.add_src_builder('CPPFile')
    shared_obj.add_src_builder('CPPFile')

    return cpp_file
