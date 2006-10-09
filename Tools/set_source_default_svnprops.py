#
# Run in source directory to change all file eol-style's
#

import os, sys, os.path
pj = os.path.join

def isSourceFile(fname):
   if fname in ["SConstruct","SConscript","build.info"]:
      return True
   ext = os.path.splitext(fname)[1]
   return ext in [".c",".cpp",".h",".inl",".ins",".fcd",".yy",".ll",".py"]

def isWindowsFile(fname):
   ext = os.path.splitext(fname)[1]
   return ext in [".dsp",".dsw"]

source_files = []
msvs_files = []

for root, dirs, files in os.walk('.'):
   source_files.extend([pj(root,f) for f in files if isSourceFile(f)])
   msvs_files.extend([pj(root,f) for f in files if isWindowsFile(f)])

print "Source files: "

for f in source_files:
   print f
 
print "Windows files: "
for f in msvs_files:
   print f

print "Setting eol-styles"
for f in source_files:
   cmd = "svn propset svn:eol-style native %s"%f
   print "cmd: %s ..."%cmd,
   os.system(cmd)
   print "[OK]"

print "Setting keywords=Id"
for f in source_files:
   cmd = "svn propset svn:keywords Id %s"%f
   print "cmd: %s ..."%cmd,
   os.system(cmd)
   print "[OK]"
