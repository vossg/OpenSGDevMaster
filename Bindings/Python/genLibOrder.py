#!/usr/bin/python

import libOrder

#print "Gen Lib Order \n", libOrder.libInfo

orderedLibs = ""

done = False

i = 0

while (True):

  currentLib = None

  for (libName, libDep) in libOrder.libInfo.items():

#    print "N: ", libName
#    print "D: ", libDep
#    print "L: ", len(libDep)

  
    if libDep != None and len(libDep) == 0:
      if len(orderedLibs) == 0:
        orderedLibs = libName
      else:
        orderedLibs = orderedLibs + ";" + libName

      libOrder.libInfo[libName] = None
      currentLib = libName
      break

  if currentLib != None:
#    print "delete lib ", currentLib

    del libOrder.libInfo[currentLib]

    for (libName, libDep) in libOrder.libInfo.items():
      try:
        libDep.remove(currentLib)
      except:
        continue
  else:
    break

#orderedLibs = orderedLibs + "]"
#print "ORDERED:\n"

print orderedLibs

