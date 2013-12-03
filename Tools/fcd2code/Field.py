
import re;
import logging;

from FCDElement import FCDElement;

podTable = {
    "bool"    : True,

    "Char8"   : True,
    "UChar8"  : True,
    "SChar8"  : True,

    "UInt8"   : True,
    "Int8"    : True,

    "UInt16"  : True,
    "Int16"   : True,

    "UInt32"  : True,
    "Int32"   : True,

    "UInt64"  : True,
    "Int64"   : True,

    "Real16"  : True,
    "Real32"  : True,
    "Real64"  : True,
    "Real128" : True,

    "Real"    : True
}

includeTable = {
    "Bool"                : "Sys",
    "Int8"                : "Sys",
    "UInt8"               : "Sys",
    "Int16"               : "Sys",
    "UInt16"              : "Sys",
    "Int32"               : "Sys",
    "UInt32"              : "Sys",
    "Int64"               : "Sys",
    "UInt64"              : "Sys",
    "Real16"              : "Sys",
    "Real32"              : "Sys",
    "Fixed32"             : "Sys",
    "Real64"              : "Sys",
    "Real"                : "Sys",

    "Color3f"             : "Base",
    "Color3r"             : "Base",
    "Color3fx"            : "Base",
    "Color4f"             : "Base",
    "Color4r"             : "Base",
    "Color4fx"            : "Base",
    "Color3ub"            : "Base",
    "Color4ub"            : "Base",
    "String"              : "Base",
    "Time"                : "Base",
    "BoxVolume"           : "Base",
    "BitVector"           : "Base",
    "GLenum"              : "Base",
    "Plane"               : "Base",
    "RenderPropBitVector" : "Base",

    "Matrix"              : "Math",
    "Matrixr"             : "Math",
    "Matrix4d"            : "Math",
    "Matrix4fx"           : "Math",
    "Quaternion"          : "Math",
    "Quaternionr"         : "Math",
    "Quaternionfx"        : "Math",

    "Vec2ub"              : "Vec",
    "Vec2b"               : "Vec",
    "Vec2us"              : "Vec",
    "Vec2s"               : "Vec",
    "Vec2u"               : "Vec",
    "Vec2i"               : "Vec",
    "Vec2f"               : "Vec",
    "Vec2r"               : "Vec",
    "Vec2fx"              : "Vec",
    "Vec2d"               : "Vec",
    "Vec2ld"              : "Vec",

    "Vec3ub"              : "Vec",
    "Vec3b"               : "Vec",
    "Vec3us"              : "Vec",
    "Vec3s"               : "Vec",
    "Vec3u"               : "Vec",
    "Vec3i"               : "Vec",
    "Vec3f"               : "Vec",
    "Vec3r"               : "Vec",
    "Vec3fx"              : "Vec",
    "Vec3d"               : "Vec",
    "Vec3ld"              : "Vec",

    "Vec4ub"              : "Vec",
    "Vec4b"               : "Vec",
    "Vec4us"              : "Vec",
    "Vec4s"               : "Vec",
    "Vec4u"               : "Vec",
    "Vec4i"               : "Vec",
    "Vec4f"               : "Vec",
    "Vec4r"               : "Vec",
    "Vec4fx"              : "Vec",
    "Vec4d"               : "Vec",
    "Vec4ld"              : "Vec",

    "Pnt2ub"              : "Vec",
    "Pnt2b"               : "Vec",
    "Pnt2us"              : "Vec",
    "Pnt2s"               : "Vec",
    "Pnt2f"               : "Vec",
    "Pnt2r"               : "Vec",
    "Pnt2fx"              : "Vec",
    "Pnt2d"               : "Vec",
    "Pnt2ld"              : "Vec",

    "Pnt3ub"              : "Vec",
    "Pnt3b"               : "Vec",
    "Pnt3us"              : "Vec",
    "Pnt3s"               : "Vec",
    "Pnt3f"               : "Vec",
    "Pnt3r"               : "Vec",
    "Pnt3fx"              : "Vec",
    "Pnt3d"               : "Vec",
    "Pnt3ld"              : "Vec",


    "Pnt4ub"              : "Vec",
    "Pnt4b"               : "Vec",
    "Pnt4us"              : "Vec",
    "Pnt4s"               : "Vec",
    "Pnt4f"               : "Vec",
    "Pnt4r"               : "Vec",
    "Pnt4fx"              : "Vec",
    "Pnt4d"               : "Vec",
    "Pnt4ld"              : "Vec",

    "VoidP"               : "Sys"
}

class Field(FCDElement):
    """Represents a <Field/> element from a .fcd file.
    """
    
    def __init__(self):
        super(Field, self).__init__();
        self.m_log              = logging.getLogger("Field");
        self.m_fieldContainer   = None;
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.setFCD("name",                           "",         True);
        self.setFCD("category",                       "",         True);
        self.setFCD("type",                           "",         True);
        self.setFCD("pointerType",                    "",         True);
        self.setFCD("typeNamespace",                  "",         True);
        self.setFCD("cardinality",                    "",         True);
        self.setFCD("visibility",                     "external", True);
        self.setFCD("fieldFlags",                     "",         True);
        self.setFCD("defaultValue",                   "",         True);
        self.setFCD("access",                         "public",   True);
        self.setFCD("defaultHeader",                  "",         True);
        self.setFCD("fieldHeader",                    "(AUTO)",   True);
        self.setFCD("typeHeader",                     "(AUTO)",   True);
        self.setFCD("description",                    "",         True);
        self.setFCD("linkSParent",                    "false",    True);
        self.setFCD("linkMParent",                    "false",    True);
        self.setFCD("removeTo",                       "",         True);
        self.setFCD("removeToSet",                    "false",    True);
        self.setFCD("pod",                            "(AUTO)",   True);
        self.setFCD("storeless",                      "false",    True);
        self.setFCD("virtual",                        "false",    True);
        self.setFCD("publicRead",                     "false",    True);

        self.setFCD("clearMField",                    "true",     True);
      
        # are mf access functions for ptr field available (they might be user generated)
        self.setFCD("hasPushToField",                 "false",    True);
        self.setFCD("hasAssignMField",                "false",    True);
        self.setFCD("hasInsertIntoMField",            "false",    True);
        self.setFCD("hasReplaceInMFieldIndex",        "false",    True);
        self.setFCD("hasReplaceInMFieldObject",       "false",    True);
        self.setFCD("hasRemoveFromMFieldIndex",       "false",    True);
        self.setFCD("hasRemoveFromMFieldObject",      "false",    True);
        self.setFCD("hasClearField",                  "false",    True);

        # names of the mf access functions for ptr field
        self.setFCD("pushToFieldAs",                  "",         True);
        self.setFCD("assignMFieldAs",                 "",         True);
        self.setFCD("insertIntoMFieldAs",             "",         True);
        self.setFCD("replaceInMFieldIndexAs",         "",         True);
        self.setFCD("replaceInMFieldObjectAs",        "",         True);
        self.setFCD("removeFromMFieldIndexAs",        "",         True);
        self.setFCD("removeFromMFieldObjectAs",       "",         True);
        self.setFCD("clearFieldAs",                   "",         True);

        self.setFCD("ptrFieldAccess",                 "std",      True);

        self.setFCD("disallowNULL",                   "false",    True);
        self.setFCD("childParentType",                "",         True);
        self.setFCD("linkParentField",                "XX",       True);

        self.setFCD("interfaceType",                  "",         True);
        self.setFCD("customBinCopy",                  "false",    True);
        self.setFCD("customSync",                     "false",    True);

        self.setFCD("fromNamespace",                  "OSG",      True);

        self.setFCD("osg2Ignore",                     "false",    True);

    def setFieldContainer(self, container):
        self.m_fieldContainer = container;
    
    def getFieldContainer(self):
        return self.m_fieldContainer;
    
    #
    # Common tests
       
    def isProtected(self):
        return self["access"] == "protected";
    
    def isPublic(self):
        return self["access"] == "public";

    def isPublicRead(self):
        return self["publicRead"] == "true" or self.isPublic();

    def isPublicWrite(self):
        return self.isPublic();

    def hasAccess(self):
        return self["access"] != "none";
    
    def isSField(self):
        return self["isSField"];
    
    def isMField(self):
        return self["isMField"];
    
    def isPtrField(self):
        return self["category"] == "pointer";

    def isChildField(self):
        return self["pointertype"] == "child";

    def isParentField(self):
        return self["pointertype"] == "parent";

    #
    # Fill out dictionary from in (fcd) dictionary
    
    def finalize(self):

        # make sure old files work
        if self.getFCD("category") == "":
            if self.getFCD("type").endswith("Ptr"):
                self.setFCD("category", "pointer");
                self.setFCD("type", self.getFCD("type")[:-3]);
 
        typeStart = self.getFCD("type").rfind("::");

        if typeStart != -1:
            self.setFCD("typeNamespace", self.getFCD("type")[:typeStart]);
            self.setFCD("type", self.getFCD("type")[typeStart+2:]);

        self["isStoreless"] = self.getFCD("storeless") == "True";

        # -----------------------------------------------------------------
        # Type and Namespace
        # -----------------------------------------------------------------
            
        TypeRaw           = self.getFCD("type");
        TypeRawCaps       = self._upcaseFirst(TypeRaw);
        
        Type              = self.getFCD("type");
        TypeNS            = self.getFCD("typeNamespace");
        TypeCaps          = self._upcaseFirst(Type);
        
        self.nsFilePrefix = ""
        
        if TypeNS != ""                                           and \
           TypeNS == self.m_fieldContainer.getFCD("libnamespace") and \
           TypeNS != "OSG"                                        and \
           TypeNS != "std"                                        :

           self.nsFilePrefix = TypeNS
           TypeNS = ""

        if TypeNS != "" and not TypeNS.endswith("::"):
            TypeNS = TypeNS + "::"

        # -----------------------------------------------------------------
        # Category
        # -----------------------------------------------------------------
                   
        self["category"]        = "";
        self["pointertype"]     = "";
        self["pointerbasetype"] = "";
        self["isChildField"]    = False
        self["isParentField"]   = False

        if self.getFCD("category") == "data" or self.getFCD("category") == "":
            self.m_log.info("finalize: \"category\" is empty, assuming \"data\"");
            FieldType     = Type;
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = TypeCaps;

        elif self.getFCD("category") == "pointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "internal";
         
            TypeCaps      = self._upcaseFirst(Type + "Ptr");
            Type          = Type + " *";
            FieldType     = "Unrec" + TypeRaw + "Ptr"; # + "InternalPtr";
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = "Unrec" + TypeRawCaps + "Ptr"; # + "InternalPtr";

        elif self.getFCD("category") == "recpointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "internal";
         
            TypeCaps      = self._upcaseFirst(Type + "Ptr");
            Type          = Type + " *";
            FieldType     = "Rec" + TypeRaw + "Ptr"; # + "InternalPtr";
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = "Rec" + TypeRawCaps + "Ptr"; # + "InternalPtr";
            
        elif self.getFCD("category") == "childpointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "child";
            self["isChildField"]    = True

            if self.getFCD("childParentType") == "":
                self["childparenttype"] = "FieldContainer"
            else:
                self["childparenttype"] = self.getFCD("childParentType")
                
            TypeCaps      = self._upcaseFirst(Type + "Ptr");
            Type          = Type + " *";
            FieldType     = "Unrec" + "Child" + TypeRaw + "Ptr";
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = "Unrec" + "Child" + TypeRawCaps + "Ptr";
            
        elif self.getFCD("category") == "parentpointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "parent";
            self["isParentField"]   = True
         
            TypeCaps      = self._upcaseFirst(Type);
            Type          = Type + " *";
            FieldType     = "Parent" + TypeRaw + "Ptr";
            self["FieldTypeRaw"]  = TypeRaw + "Ptr";
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = "Parent" + TypeRawCaps + "Ptr";
        
        elif self.getFCD("category") == "weakpointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "weak";
         
            TypeCaps      = self._upcaseFirst(Type + "Ptr");
            Type          = Type + " *";
            FieldType     = "Weak" + TypeRaw + "Ptr"; #TypeRaw + "WeakPtr";
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = "Weak" + TypeRawCaps + "Ptr"; #TypeRawCaps + "WeakPtr";
        elif self.getFCD("category") == "uncountedpointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "uncounted";
         
            TypeCaps      = self._upcaseFirst(Type + "Ptr");
            Type          = Type + " *";
            FieldType     = "Uncounted" + TypeRaw + "Ptr"; #TypeRaw + "WeakPtr";
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = "Uncounted" + TypeRawCaps + "Ptr"; #TypeRawCaps + "WeakPtr";
            
        elif self.getFCD("category") == "custompointer":
            self["category"]        = "pointer";
            self["pointertype"]     = "internal";
            Type          = Type + " *";
            FieldType     = Type;
            FieldTypeNS   = TypeNS;
            FieldTypeCaps = TypeCaps;
            
        else:
            self.m_log.warning("finalize: \"category\" has invalid value: >%s<",
                self.getFCD("category"));    
              
        if TypeNS == "std::":
            FieldTypeNS = "";
                
        self["Type"]          = Type;
        self["TypeNamespace"] = TypeNS;
        self["TypeNS"]        = TypeNS;
        self["TypeCaps"]      = TypeCaps;

        if self.getFCD("interfaceType") != "":
          self["FullType"]    = self.getFCD("interfaceType");
        else:
          self["FullType"]    = TypeNS + Type;

        self["TypeRaw"]       = TypeRaw;

        self["FieldType"]     = FieldType;
        self["FieldTypeNS"]   = FieldTypeNS;
        self["FieldTypeCaps"] = FieldTypeCaps
        
        self["linkParentField"] = self.getFCD("linkParentField");

        if self.getFCD("customBinCopy") == "" or \
           self.getFCD("customBinCopy") == "false":

            self["customBinCopy"] = False
        else:
            self["customBinCopy"] = True

        if self.getFCD("customSync") == "" or \
           self.getFCD("customSync") == "false":

            self["customSync"] = False
        else:
            self["customSync"] = True

            

        # -----------------------------------------------------------------
        # Name and Cardinality
        # -----------------------------------------------------------------
          
        self["Name"]          = self.getFCD("name")[0].upper() + self.getFCD("name")[1:];
        self["DescName"]      = self.getFCD("name");

        if self.getFCD("name") == "id":
            self.m_log.warning("finalize: invalid field name: >%s<", 
                               self.getFCD("name"))
            self["Name"] = self["Name"] + "_invalidFieldname"
            self["DescName"] = self["DescName"] + "_invalidFieldname"

        self["isSField"] = False;
        self["isMField"] = False;
        
        if self.getFCD("cardinality") == "single":
            self["cardinality"] = "single"
            self["isSField"]    = True;
            self["CARD"]        = "SF";
            self["VarName"]     = "sf" + self["Name"];
        elif self.getFCD("cardinality") == "multi":
            self["cardinality"] = "multi"
            self["isMField"]    = True;
            self["CARD"]        = "MF";
            self["VarName"]     = "mf" + self["Name"];
        else:
            self.m_log.warning("finalize: \"cardinality\" has invalid value: %s",
                self.getFCD("cardinality"));

        if self.getFCD("access") == "protected":
            self["access"] = "protected";
            self["isProtected"] = True;
        elif self.getFCD("access") == "public":
            self["access"] = "public";
            self["isPublic"] = True;
        elif self.getFCD("access") == "none":
            self["access"] = "none";
            self["noAccess"] = True;
        else:
            self.m_log.warning("finalize: \"access\" has invalid value: >%s<", 
                self.getFCD("access"));

        #Public Read
        if self.getFCD("publicRead") == "true" or self["access"] == "public":
            self["publicRead"] = "true";
            self["isPublicRead"] = True;
        else:
            self["publicRead"] = "false";
            self["isPublicRead"] = False;

        #Public Write
        if "isPublic" in self and self["access"] == "public" and self["pointertype"] != "parent":
            self["isPublicWrite"] = True;
        else:
            self["isPublicWrite"] = False;
                 
        if self.getFCD("description").strip() == "":
            self["Description"]     = "";
            self["SafeDescription"] = "\"\"";
        else:
            self["Description"]     = self._formatString    (self.getFCD("description"), 4)
            self["SafeDescription"] = self._formatSafeString(self.getFCD("description"), 8)
        
        if self["isMField"] == True:
            self["GenFieldFlags"] = "(Field::MFDefaultFlags"
        else:
            self["GenFieldFlags"] = "(Field::SFDefaultFlags"
        
        if self.getFCD("linkSParent") == "true":
            self["linkSParent"] = True;
            self["GenFieldFlags"] = \
                self["GenFieldFlags"] + " | Field::FLinkParents"
        else:
            self["linkSParent"] = False;
        
        if self.getFCD("linkMParent") == "true":
            self["linkMParent"] = True;
            self["GenFieldFlags"] = \
                self["GenFieldFlags"] + " | Field::FLinkParents"
        else:
            self["linkMParent"] = False;
        
       

#         if ((self.getFCD("header") == "")      or
#             (self.getFCD("header") == "(AUTO)")  ):
#             if self.getFieldContainer().isSystemComponent():
#                 typeInclude = "OSG";
#             else:
#                 typeInclude = "OpenSG/OSG";
            
#             if includeTable.has_key(TypeRawCaps):
#                 typeInclude = typeInclude + includeTable[TypeRawCaps] + "Fields.h"
#             else:
#                 typeInclude = typeInclude + TypeRawCaps + "Fields.h"

#         else:
#             typeInclude = self.getFCD("header");
        
#         self["TypeInclude"] = typeInclude;

        
        if self.getFieldContainer().isDecoratable() or \
           self.getFCD("virtual") == "true":

            self["MethodType"] = "virtual";

        else:

            self["MethodType"] = "";
        

        isPod = True

        if self.getFCD("pod") == "(AUTO)":

            if podTable.has_key(self.getFCD("type")) == True:
                isPod = podTable[self.getFCD("type")]
            else:
                isPod = False

        elif self.getFCD("pod") == "false":
            isPod = False

        if isPod == True:
            self["RetConst"] = "     ";
            self["RetRef"]   = " ";
            self["ArgRef"]   = "";
        else:
            self["RetConst"] = "const";
            self["RetRef"]   = "&";
            self["ArgRef"]   = "&";
       
        if self.getFCD("defaultValue") != "":
            if self["category"] == "pointer" and self["cardinality"] == "single": 
                self["TypedDefault"] = self.getFCD("defaultValue");
            elif self["category"] == "pointer" and self["cardinality"] == "multi":
                self["TypedDefault"] = "";
            else:
                self["TypedDefault"] = \
                    self["FullType"] + "(" + \
                    self.getFCD("defaultValue") + ")";
        else:
            if self["category"] == "pointer" and self["cardinality"] == "single":
#                self["TypedDefault"] = self["TypeNS"] + self["Type"] + "(NULL)";
                self["TypedDefault"] = "NULL";
            else:
                self["TypedDefault"] = "";
            
        if self.getFCD("visibility") == "external":
            self["Visibility"] = "false";
        elif self.getFCD("visibility") == "internal":
            self["Visibility"] = "true";
#            self["GenFieldFlags"] = \
#                self["GenFieldFlags"] + " | Field::FInternal"
        else:
            self.m_log.warning("finalize: \"visibility\" has invalid value: %s",
                self.getFCD("visibility"));

        self["writePushToField"]            = False;
        self["hasPushToField"]              = False;
        self["writeAssignMField"]           = False;
        self["hasAssignMField"]             = False;
        self["writeInsertIntoMField"]       = False;
        self["hasInsertIntoMField"]         = False;
        self["writeReplaceInMFieldIndex"]   = False;
        self["hasRemoveFromMFieldIndex"]    = False;
        self["writeReplaceInMFieldObject"]  = False;
        self["hasReplaceInMFieldObject"]    = False;
        self["writeRemoveFromMFieldIndex"]  = False;
        self["hasRemoveFromMFieldIndex"]    = False;
        self["writeRemoveFromMFieldObject"] = False;
        self["hasRemoveFromMFieldObject"]   = False;
        self["writeClearField"]             = False;
        self["hasClearField"]               = False;

        self["ptrFieldCustomAccess"]        = False;
        self["ptrFieldNullCheckAccess"]     = False;
        self["ptrFieldStandardAccess"]      = False;

        if self.getFCD("ptrFieldAccess") == "std":
            self["ptrFieldStandardAccess"]      = True;
            self["writePushToField"]            = True;
            self["hasPushToField"]              = True;
            self["writeRemoveFromMFieldIndex"]  = True;
            self["hasRemoveFromMFieldIndex"]    = True;
            self["writeRemoveFromMFieldObject"] = True;
            self["hasRemoveFromMFieldObject"]   = True;
            self["writeClearField"]             = True;
            self["hasClearField"]               = True;
            self["writeAssignMField"]           = True;
            self["hasAssignMField"]             = True;
    
        elif self.getFCD("ptrFieldAccess") == "nullCheck":
            self["ptrFieldNullCheckAccess"]     = True;
            self["writePushToField"]            = True;
            self["hasPushToField"]              = True;
            self["writeAssignMField"]           = True;
            self["hasAssignMField"]             = True;
            self["writeInsertIntoMField"]       = True;
            self["hasInsertIntoMField"]         = True;
            self["writeReplaceInMFieldIndex"]   = True;
            self["hasReplaceInMFieldIndex"]     = True;
            self["writeReplaceInMFieldObject"]  = True;
            self["hasReplaceInMFieldObject"]    = True;
            self["writeRemoveFromMFieldIndex"]  = True;
            self["hasRemoveFromMFieldIndex"]    = True;
            self["writeRemoveFromMFieldObject"] = True;
            self["hasRemoveFromMFieldObject"]   = True;
            self["writeClearField"]             = True;
            self["hasClearField"]               = True;
            
        elif self.getFCD("ptrFieldAccess") == "custom":
            self["ptrFieldCustomAccess"]      = True;
            self["hasPushToField"]            = (self.getFCD("hasPushToField")            == "true" or
                                                 self.getFCD("pushToFieldAs")             != ""       );
            self["hasAssignMField"]           = (self.getFCD("hasAssignMField")           == "true" or
                                                 self.getFCD("assignMFieldAs")            != ""       );
            self["hasInsertIntoMField"]       = (self.getFCD("hasInsertIntoMField")       == "true" or
                                                 self.getFCD("insertIntoMFieldAs")        != ""       );
            self["hasReplaceInMFieldIndex"]   = (self.getFCD("hasReplaceInMFieldIndex")   == "true" or
                                                 self.getFCD("replaceInMFieldIndexAs")    != ""       );
            self["hasReplaceInMFieldObject"]  = (self.getFCD("hasReplaceInMFieldObject")  == "true" or
                                                 self.getFCD("replaceInMFieldObjectAs")   != ""       );
            self["hasRemoveFromMFieldIndex"]  = (self.getFCD("hasRemoveFromMFieldIndex")  == "true" or
                                                 self.getFCD("removeFromMFieldIndexAs")   != ""       );
            self["hasRemoveFromMFieldObject"] = (self.getFCD("hasRemoveFromMFieldObject") == "true" or
                                                 self.getFCD("removeFromMFieldObjectAs")  != ""       );
            self["hasClearField"]             = (self.getFCD("hasClearField")             == "true" or
                                                 self.getFCD("clearFieldAs")              != ""       );
            
        else:
            print "Unknown pointer field acess mode ", self.getFCD("ptrFieldAccess")
            sys.exit(1)
        
        if self["ptrFieldStandardAccess"]:
            self["GenFieldFlags"] += " | Field::FStdAccess";
        elif self["ptrFieldNullCheckAccess"]:
            self["GenFieldFlags"] += " | Field::FNullCheckAccess";
        elif self["ptrFieldCustomAccess"]:
            self["GenFieldFlags"] += " | Field::FCustomAccess";
        
        self["GenFieldFlags"] = self["GenFieldFlags"] + ")"
        # No changes to GenFieldFlags past this point!            
               
        if self.getFCD("pushToFieldAs") != "":
            self["PushToField"] = self.getFCD("pushToFieldAs");
        else:
            self["PushToField"] = "pushTo" + self["Name"];



        if self.getFCD("assignMFieldAs") != "":
            self["AssignMField"] = self.getFCD("assignMFieldAs");
        else:
            self["AssignMField"] = "assign" + self["Name"];



        if self.getFCD("insertIntoMFieldAs") != "":
            self["InsertIntoMField"] = self.getFCD("insertIntoMFieldAs");
        else:
            self["InsertIntoMField"] = "insertInto" + self["Name"];

        

        if self.getFCD("replaceInMFieldIndexAs") != "":
            self["ReplaceInMFieldIndex"] = self.getFCD("replaceInMFieldIndexAs");
        else:
            self["ReplaceInMFieldIndex"] = "replaceIn" + self["Name"];
        


        if self.getFCD("replaceInMFieldObjectAs") != "":
            self["ReplaceInMFieldObject"] = self.getFCD("replaceInMFieldObjectAs");
        else:
            self["ReplaceInMFieldObject"] = "replaceObjIn" + self["Name"];
        


        if self.getFCD("removeFromMFieldIndexAs") != "":
            self["RemoveFromMFieldIndex"] = self.getFCD("removeFromMFieldIndexAs");
        else:
            self["RemoveFromMFieldIndex"] = "removeFrom" + self["Name"];
        


        if self.getFCD("removeFromMFieldObjectAs") != "":
            self["RemoveFromMFieldObject"] = self.getFCD("removeFromMFieldObjectAs");
        else:
            self["RemoveFromMFieldObject"] = "removeObjFrom" + self["Name"];
        


        if self.getFCD("clearFieldAs") != "":
            self["ClearField"] = self.getFCD("clearFieldAs");
        else:
            self["ClearField"] = "clear" + self["Name"];
        



        if self.getFCD("removeTo") != "":
            self.setFCD("removeToSet", True);
            self["isRemoveToSet"]         = True;
            self["RemoveTo"]              = self.getFCD("removeTo");
        else:
            self.setFCD("removeToSet", False);
            self["isRemoveToSet"]         = False;
        
        if self.getFCD("clearMField") == "true":
            self["doClearMField"] = True;
        else:
            self["doClearMField"] = False;

            
        fieldFlagsOverride = False;
        flags              = None,
        
        if self.isSField():
            if self.getFCD("fieldFlags") != "":
                fieldFlagsOverride = True;
            else:
                flags = self["GenFieldFlags"];
            
        elif self.isMField():
            if self.getFCD("fieldFlags") != "":
                fieldFlagsOverride = True;
            else:
                flags = self["GenFieldFlags"];
        
        if fieldFlagsOverride:
            flagsFCD = self.getFCD("fieldFlags").split(",");
            numFlags = len(flagsFCD);
            
            flags = "(";
            
            for i, flag in enumerate(flagsFCD):
                flag = flag.replace(" ",  "");
                flag = flag.replace("\t", "");
                flag = flag.replace("\n", "");
                
                if (i == 0)  and (i != numFlags - 1):
                    flags = flags + "Field::" + flag + " |";
                    continue;
                
                if i == numFlags - 1:
                    if i != 0:
                        flags = flags + " Field::" + flag;
                    else:
                        flags = flags + "Field::" + flag;
                    
                    continue;
                
                flags = flags + " Field::" + flag + " |";
            
            flags = flags + ")";
        
        self["Flags"] = flags;
        
        # Headers

        if self.getFCD("defaultHeader") != "":
            self["needDefaultInclude"] = True;
            
            if ((self.getFCD("defaultHeader").find("\"") == -1) and
                (self.getFCD("defaultHeader").find("<")  == -1)    ):
                self["DefaultInclude"] = "\"" + self.getFCD("defaultHeader") + "\"";
            else:
                self["DefaultInclude"] = self.getFCD("defaultHeader");
        else:
            self["needDefaultInclude"] = False;


        fieldInclude = "";
        
        if ((self.getFCD("fieldHeader") == ""      ) or 
            (self.getFCD("fieldHeader") == "(AUTO)")   ):
            
            if self.getFieldContainer().isSystemComponent():
                fieldInclude = "OSG" + self.nsFilePrefix
            else:
                fieldInclude = "OpenSG/OSG" + self.nsFilePrefix

            if includeTable.has_key(TypeRawCaps):
                fieldInclude = "\"" + fieldInclude + includeTable[TypeRawCaps] + "Fields.h" + "\""
            else:
                fieldInclude = "\"" + fieldInclude + TypeRawCaps               + "Fields.h" + "\""

        else:
            if ((self.getFCD("fieldHeader").find("\"") == -1) and
                (self.getFCD("fieldHeader").find("<")  == -1)    ):
                fieldInclude = "\"" + self.getFCD("fieldHeader") + "\"";
            else:
                fieldInclude = self.getFCD("fieldHeader");

        self["FieldInclude"]     = fieldInclude
        self["needFieldInclude"] = True;

                    
        typeInclude = "";
        
        if self["category"] == "pointer":
            if ((self.getFCD("typeHeader") == "")      or
                (self.getFCD("typeHeader") == "(AUTO)")  ):

                if self.getFieldContainer().isSystemComponent():
                    typeInclude = "OSG" + self.nsFilePrefix; 
                else:
                    typeInclude = "OpenSG/OSG" + self.nsFilePrefix;
            
                typeInclude = typeInclude + TypeRawCaps;
                     
                typeInclude = typeInclude.replace("Parent", "");
                typeInclude = "\"" + typeInclude + ".h" + "\""

            else:
                if ((self.getFCD("typeHeader").find("\"") == -1) and
                    (self.getFCD("typeHeader").find("<")  == -1)    ):
                    typeInclude = "\"" + self.getFCD("typeHeader") + "\"";
                else:
                    typeInclude = self.getFCD("typeHeader");
            
            self["TypeInclude"]     = typeInclude;
            self["needTypeInclude"] = True;

        else:
            self["TypeInclude"]     = None
            self["needTypeInclude"] = False
            

        # hack for now
        if self.isPtrField():
            self["isPtrField"] = True;

        
    def _dumpValues(self):
        self.m_log.info("Field dumpValues:");
        super(Field, self)._dumpValues(self.m_log);
    
