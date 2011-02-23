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

# Simple wrapper for FCD XML data in field type


import osg2
try:
   import xml.etree.ElementTree as ET
except:
   import elementtree.ElementTree as ET

class FcdReflector(object):
   def __init__(self, fctype, mergeParents=False):      
      """
        @param mergeParents: If true, merge in the parent's fields.
      """
      self.fc_type = fctype
      xml_data = fctype.getFcdXML()
      if xml_data and xml_data != "":
         self.element = ET.fromstring(xml_data)
      else:
         self.element = None
      
      if self.element and mergeParents:
         fc_type = fctype.getParent()
         while fc_type:
            xml_data = fc_type.getFcdXML()
            if xml_data and xml_data != "":
               new_elt = ET.fromstring(xml_data)
               if new_elt:
                  for n in new_elt:
                     self.element.append(n)
            fc_type = fc_type.getParent()
         

   def hasData(self):
      """ Return true if we wrap XML data successfully.
          Note: Some object types may not have an fcd file as a backend so they
          may return false.
      """
      return self.element != None
   
   def fields(self):
      """ return wrappers for all child fields. """
      if len(self.element) == 0:
         return []
      else:
         return [FieldReflector(f,self) for f in self.element.findall("Field")]
   
   def getField(self, name):
      """ Return a wrapper around the first field named name. """
      for f in self.element.findall("Field"):
         if name == f.attrib["name"]:
            return FieldReflector(f,self)
      return None
   
   def getAttrib(self):
      return self.element.attrib
   attrib = property(getAttrib, doc='Return the element.attrib property')
      
   def getName(self):
      return self.element.get("name")   
   def getType(self):
      return self.element.get("type")
   
   def getDocumentation(self):
      return self.element.text
   def getCardinality(self):
      return self.element.get("cardinality")
   def getVisibility(self):
      return self.element.get("visibility")
   def getAccess(self):
      return self.element.get("access")
   

class FieldReflector(FcdReflector):
   def __init__(self, fieldElement, parent):
      self.parent = parent
      self.element = fieldElement
