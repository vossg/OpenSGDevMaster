# PyOpenSG is (C) Copyright 2005-2009 by Allen Bierbaum
#
# This file is part of PyOpenSG.
#
# PyOpenSG is free software; you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# PyOpenSG is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import osg2
import sys

class AllocationError(Exception):
   pass

class CoredNode(object):
   """ Mixin object for a Cored node type """
   coreType = None
   __slots__ = ['mNode', 'mCore']

   def create(cls):
      obj = cls()
      obj.mNode = osg2.OSGBase.Node.create()
      obj.mCore = cls.coreType.create()
      obj.mNode.setCore(obj.mCore)
      return obj
   create = classmethod(create)

   def __new__(cls, *args, **kwargs):
      # A cored not can only be created from within the cored_node module and from code named 'create'.
      if __name__ != sys._getframe(1).f_globals['__name__'] or \
         'create' != sys._getframe(1).f_code.co_name:
         raise AllocationError("Can't construct a '%s' directly, use %s.create()"%(cls.__name__, cls.__name__))
      return object.__new__(cls, *args, **kwargs)

   def __init__(self):
      self.mNode = None
      self.mCore = None
      
   def core(self):
      assert self.mNode.getCore() == self.mCore
      return self.mCore
   
   def node(self):
      return self.mNode

   def __getattr__(self, name):
      return getattr(self.mCore, name)

   # Use code to find the calling frame.
   def __setattr__(self, name, value):
      # Figure out the module that we were called from. If it is not
      # the current module, then throw an exception.
      if __name__ != sys._getframe(1).f_globals['__name__']:
         raise AttributeError("Can't set attributes on a %s."%self.__class__.__name__)
      object.__setattr__(self, name, value)

   def setCore(self, newCore):
      self.mCore = newCore
      self.mNode.setCore(newCore)

def addNodeCoreTypes(globalDict, osg2Module):

   node_cores = []

   node_cores.extend([(n,c) for (n,c) in osg2Module.__dict__.iteritems() if isinstance(c,type) \
                     and (osg2.OSGBase.NodeCore in c.__mro__) and not c.__name__.endswith("Base")])

   for (name,ctype) in node_cores:
      cored_node_classname = "%sNode"%name
      cored_node_class = type(cored_node_classname, (CoredNode,), {'coreType':ctype,})            

      globalDict[cored_node_classname] = cored_node_class
