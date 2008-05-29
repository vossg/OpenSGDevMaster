
import re;
import logging;

from FCDElement import FCDElement;

class Field(FCDElement):
    """Represents a <Field/> element from a .fcd file.
    """
    
    def __init__(self):
        super(Field, self).__init__();
        self.m_log            = logging.getLogger("Field");
        self.m_fieldContainer = None;
        
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.setFCD("name",                     "");
        self.setFCD("category",                 "");
        self.setFCD("type",                     "");
        self.setFCD("pointerType",              "");
        self.setFCD("typeNamespace",            "");
        self.setFCD("cardinality",              "");
        self.setFCD("visibility",               "external");
        self.setFCD("fieldFlags",               "");
        self.setFCD("defaultValue",             "");
        self.setFCD("access",                   "public");
        self.setFCD("defaultHeader",            "");
        self.setFCD("header",                   "(AUTO)");
        self.setFCD("description",              "");
        self.setFCD("linkSParent",              "false");
        self.setFCD("linkMParent",              "false");
        self.setFCD("removeTo",                 "");
        self.setFCD("removeToSet",              "false");

        self.setFCD("clearMField",              "true");

        self.setFCD("pushToField",              "");
        self.setFCD("assignMField",             "");
        self.setFCD("insertIntoMField",         "");
        self.setFCD("replaceInMFieldIndex",     "");
        self.setFCD("replaceInMFieldObject",    "");
        self.setFCD("removeFromMFieldIndex",    "");
        self.setFCD("removeFromMFieldObject",   "");
        self.setFCD("clearField",               "");

        self.setFCD("pushToFieldAs",            "");
        self.setFCD("assignMFieldAs",           "");
        self.setFCD("insertIntoMFieldAs",       "");
        self.setFCD("replaceInMFieldIndexAs",   "");
        self.setFCD("replaceInMFieldObjectAs",  "");
        self.setFCD("removeFromMFieldIndexAs",  "");
        self.setFCD("removeFromMFieldObjectAs", "");
        self.setFCD("clearFieldAs",             "");

        self.setFCD("ptrFieldAccess",           "std")

        self.setFCD("disallowNULL",             "false");
        self.setFCD("needClassInclude",         "true");
        self.setFCD("childParentType",          "");
        self.setFCD("linkParentField",          "XX");
    
    def setFieldContainer(self, container):
        self.m_fieldContainer = container;
    
    def getFieldContainer(self):
        return self.m_fieldContainer;
    
    #
    # Common tests
    
    def isPrivate(self):
        return self["access"] == "private";
    
    def isProtected(self):
        return self["access"] == "protected";
    
    def isPublic(self):
        return self["access"] == "public";
    
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

        # -----------------------------------------------------------------
        # Type and Namespace
        # -----------------------------------------------------------------
            
        TypeRaw           = self.getFCD("type");
        TypeRawCaps       = self._upcaseFirst(TypeRaw);
        
        Type              = self.getFCD("type");
        TypeNS            = self.getFCD("typeNamespace");
        TypeCaps          = self._upcaseFirst(Type);
        
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
            
        else:
            self.m_log.warning("finalize: \"category\" has invalid value: >%s<",
                self.getFCD("category"));    
              
        if TypeNS == "std::":
            FieldTypeNS = "";
                
        self["Type"]          = Type;
        self["TypeNamespace"] = TypeNS;
        self["TypeNS"]        = TypeNS;
        self["TypeCaps"]      = TypeCaps;
        self["FullType"]      = TypeNS + Type;
        self["TypeRaw"]       = TypeRaw;

        self["FieldType"]     = FieldType;
        self["FieldTypeNS"]   = FieldTypeNS;
        self["FieldTypeCaps"] = FieldTypeCaps
        
        self["linkParentField"] = self.getFCD("linkParentField");

        # -----------------------------------------------------------------
        # Name and Cardinality
        # -----------------------------------------------------------------

        self["Name"]          = self.getFCD("name")[0].upper() + self.getFCD("name")[1:];
        self["DescName"]      = self.getFCD("name");
               
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

        if self.getFCD("access") == "private":
            self["access"] = "private";
            self["isPrivate"] = True;
        elif self.getFCD("access") == "protected":
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
        
       
        typeInclude = "";
        
        if ((self.getFCD("header") == "")      or
            (self.getFCD("header") == "(AUTO)")  ):
            if self.getFieldContainer().isSystemComponent():
                typeInclude = "OSG";
            else:
                typeInclude = "OpenSG/OSG";
            
            typeInclude = typeInclude + TypeRawCaps + "Fields.h"                
        else:
            typeInclude = self.getFCD("header");
        
        self["TypeInclude"] = typeInclude;
        
        if self.getFieldContainer().isDecoratable():
            self["MethodType"] = "virtual";
        else:
            self["MethodType"] = "";
        
        if self.getFCD("defaultHeader") != "":
            self["hasDefaultHeader"] = True;
            
            if ((self.getFCD("defaultHeader").find("\"") == -1) and
                (self.getFCD("defaultHeader").find("<")  == -1)    ):
                self["DefaultHeader"] = "\"" + self.getFCD("defaultHeader") + "\"";
            else:
                self["DefaultHeader"] = self.getFCD("defaultHeader");
        else:
            self["hasDefaultHeader"] = False;
        
        if self.getFCD("defaultValue") != "":
            if self["category"] == "pointer" and self["cardinality"] == "single": 
                self["TypedDefault"] = self.getFCD("defaultValue")
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
            self["GenFieldFlags"] = \
                self["GenFieldFlags"] + " | Field::FInternal"
        else:
            self.m_log.warning("finalize: \"visibility\" has invalid value: %s",
                self.getFCD("visibility"));

        self["GenFieldFlags"] = self["GenFieldFlags"] + ")"
        
        fieldFlagsOverride = False;
        flags              = None,
        
        if self.isSField():
            if self.getFCD("fieldFlags") != "":
                fieldFlagsOverride = True;
            else:
                flags = "Field::SFDefaultFlags";
            
        elif self.isMField():
            if self.getFCD("fieldFlags") != "":
                fieldFlagsOverride = True;
            else:
                flags = "Field::MFDefaultFlags";
        
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
        


        self["writePushToField"]            = False;
        self["writeAssignMField"]           = False;
        self["writeInsertIntoMField"]       = False;
        self["writeReplaceInMFieldIndex"]   = False;
        self["writeReplaceInMFieldObject"]  = False;
        self["writeRemoveFromMFieldIndex"]  = False;
        self["writeRemoveFromMFieldObject"] = False;
        self["writeClearField"]             = False;

        self["ptrFieldCustomAccess"]        = False;
        self["ptrFieldNullCheckAccess"]     = False;
        self["ptrFieldStandardAccess"]      = False;

        if self.getFCD("ptrFieldAccess") == "std":
            self["ptrFieldStandardAccess"]      = True;
            self["writePushToField"]            = True;
            self["writeRemoveFromMFieldIndex"]  = True;
            self["writeRemoveFromMFieldObject"] = True;
            self["writeClearField"]             = True;
            self["writeAssignMField"]           = True;
        elif self.getFCD("ptrFieldAccess") == "nullCheck":
            self["ptrFieldNullCheckAccess"]     = True;
            self["writePushToField"]            = True;
            self["writeAssignMField"]           = True;
            self["writeInsertIntoMField"]       = True;
            self["writeReplaceInMFieldIndex"]   = True;
            self["writeReplaceInMFieldObject"]  = True;
            self["writeRemoveFromMFieldIndex"]  = True;
            self["writeRemoveFromMFieldObject"] = True;
            self["writeClearField"]             = True;
        elif self.getFCD("ptrFieldAccess") == "custom":
            self["ptrFieldCustomAccess"]        = True;
        else:
            print "Unknown pointer field acess mode ", self.getFCD("ptrFieldAccess")
            sys.exit(1)
           
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
            self["ReplaceInMFieldObject"] = "replaceIn" + self["Name"];
        


        if self.getFCD("removeFromMFieldIndexAs") != "":
            self["RemoveFromMFieldIndex"] = self.getFCD("removeFromMFieldIndexAs");
        else:
            self["RemoveFromMFieldIndex"] = "removeFrom" + self["Name"];
        


        if self.getFCD("removeFromMFieldObjectAs") != "":
            self["RemoveFromMFieldObject"] = self.getFCD("removeFromMFieldObjectAs");
        else:
            self["RemoveFromMFieldObject"] = "removeFrom" + self["Name"];
        


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
        
        classInclude = "";
        
        if self["category"] == "pointer":
            if self.getFieldContainer().isSystemComponent():
                classInclude = "OSG";
            else:
                classInclude = "OpenSG/OSG";
            
            classInclude = classInclude + self["TypeCaps"];
            
            if classInclude.endswith("Ptr"):
                classInclude = classInclude[:-3];

#            if classInclude.endswith("P"):
#                classInclude = classInclude[:-1];
            
            classInclude = classInclude.replace("Parent", "");
            classInclude = classInclude + ".h";
            
            self["ClassInclude"]     = classInclude;
            self["needClassInclude"] = True;

        # hack for now
        if self.isPtrField():
            self["isPtrField"] = True;

        
    def _dumpValues(self):
        self.m_log.info("Field dumpValues:");
        super(Field, self)._dumpValues(self.m_log);
    
