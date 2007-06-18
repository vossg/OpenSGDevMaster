
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
        self.setFCD("type",                     "");
        self.setFCD("typeNamespace",            "");
        self.setFCD("cardinality",              "");
        self.setFCD("visibility",               "external");
        self.setFCD("fieldFlags",               "");
        self.setFCD("defaultValue",             "");
        self.setFCD("access",                   "public");
        self.setFCD("defaultHeader",            "");
        self.setFCD("header",                   "(AUTO)");
        self.setFCD("description",              "");
        self.setFCD("checkNilPtr",              "true");
        self.setFCD("linkSParent",              "false");
        self.setFCD("linkMParent",              "false");
        self.setFCD("doRefCount",               "true");
        self.setFCD("passFieldMask",            "false");
        self.setFCD("removeTo",                 "");
        self.setFCD("removeToSet",              "false");
        self.setFCD("clearMField",              "true");
        self.setFCD("pushToField",              "");
        self.setFCD("insertIntoMField",         "");
        self.setFCD("replaceInMFieldIndex",     "");
        self.setFCD("replaceInMFieldObject",    "");
        self.setFCD("removeFromMFieldIndex",    "");
        self.setFCD("removeFromMFieldObject",   "");
        self.setFCD("clearField",               "");
        self.setFCD("pushToFieldAs",            "");
        self.setFCD("insertIntoMFieldAs",       "");
        self.setFCD("replaceInMFieldIndexAs",   "");
        self.setFCD("replaceInMFieldObjectAs",  "");
        self.setFCD("removeFromMFieldIndexAs",  "");
        self.setFCD("removeFromMFieldObjectAs", "");
        self.setFCD("clearFieldAs",             "");
        self.setFCD("needClassInclude",         "true");
    
    def setFieldContainer(self, container):
        self.m_fieldContainer = container;
    
    def getFieldContainer(self):
        return self.m_fieldContainer;
    
    #
    # Common tests
    
    def isPrivate(self):
        return self["isPrivate"];
    
    def isProtected(self):
        return self["isProtected"];
    
    def isPublic(self):
        return self["isPublic"];
    
    def isSField(self):
        return self["isSField"];
    
    def isMField(self):
        return self["isMField"];
    
    def isPtrField(self):
        return self["isPtrField"];
    
    #
    # Fill out dictionary from in (fcd) dictionary
    
    def finalize(self):
        fullType  = self.getFCD("type");
        typeName  = self.getFCD("type");
        namespace = self.getFCD("typeNamespace");
        
        if namespace != None and namespace != "":
            if namespace.endswith("::"):
                fullType = namespace + fullType;
            else:
                fullType = namespace + "::" + fullType;
        else:
            typeStart = fullType.rfind("::");
            
            if typeStart != -1:
                typeName  = fullType[typeStart+2:];
                namespace = fullType[:typeStart+2];
            else:
                typeName  = fullType;
                namespace = "";
        
        if namespace == "std::":
            namespace = "";
        
        self["Type"]          = fullType;
        self["TypeCaps"]      = typeName[0].upper() + typeName[1:];
        self["TypeNamespace"] = namespace;
        
        self["Name"]          = self.getFCD("name")[0].upper() + self.getFCD("name")[1:];
        self["DescName"]      = self.getFCD("name");
        
        self["isPrivate"]   = False;
        self["isProtected"] = False;
        self["isPublic"]    = False;
        self["noAccess"]    = False;
        
        if self.getFCD("access") == "private":
            self["isPrivate"] = True;
        elif self.getFCD("access") == "protected":
            self["isProtected"] = True;
        elif self.getFCD("access") == "public":
            self["isPublic"] = True;
        elif self.getFCD("access") == "none":
            self["noAccess"] = True;
        else:
            self.m_log.warning("finalize: \"access\" has invalid value: %s", 
                self.getFCD("access"));
        
        self["isSField"] = False;
        self["isMField"] = False;
        
        if self.getFCD("cardinality") == "single":
            self["isSField"] = True;
            self["CARD"]     = "SF";
            self["VarName"]  = "sf" + self["Name"];
        elif self.getFCD("cardinality") == "multi":
            self["isMField"] = True;
            self["CARD"]     = "MF";
            self["VarName"]  = "mf" + self["Name"];
        else:
            self.m_log.warning("finalize: \"cardinality\" has invalid value: %s",
                self.getFCD("cardinality"));
        
        if self["Type"].endswith("Ptr"):
            self["isPtrField"] = True;
        else:
            self["isPtrField"] = False;
        
        if self.getFCD("description").strip() == "":
            self["Description"]     = "";
            self["SafeDescription"] = "\"\"";
        else:
            self["Description"]     = self._formatString    (self.getFCD("description"), 4)
            self["SafeDescription"] = self._formatSafeString(self.getFCD("description"), 8)
        
        if self.getFCD("doRefCount") == "true":
            self["doRefCount"] = True;
        else:
            self["doRefCount"] = False;
        
        if self.getFCD("linkSParent") == "true":
            self["linkSParent"] = True;
        else:
            self["linkSParent"] = False;
        
        if self.getFCD("linkMParent") == "true":
            self["linkMParent"] = True;
        else:
            self["linkMParent"] = False;
        
        if self.getFCD("checkNilPtr") == "true":
            self["checkNilPtr"] = True;
        else:
            self["checkNilPtr"] = False;
        
        if self.getFCD("passFieldMask") == "true":
            self["PassFieldMask"] = True;
        else:
            self["PassFieldMask"] = False;
        
        typeInclude = "";
        
        if ((self.getFCD("header") == "")      or
            (self.getFCD("header") == "(AUTO)")  ):
            if self.getFieldContainer().isSystemComponent():
                typeInclude = "OSG";
            else:
                typeInclude = "OpenSG/OSG";
            
            typeInclude = typeInclude + self["TypeCaps"];
            
            if typeInclude.endswith("Ptr"):
                typeInclude = typeInclude[:-3];
        
            typeInclude = typeInclude.replace("GLP::", "");
            typeInclude = typeInclude + "Fields.h";
            
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
            self["TypedDefault"] = \
                self["Type"] + "(" + \
                self.getFCD("defaultValue") + ")";
        else:
            if self["isPtrField"] == True and self["isSField"] == True:
               self["TypedDefault"] = "NullFC";
            else:
               self["TypedDefault"] = "";
            
        
        if self.getFCD("visibility") == "external":
            self["Visibility"] = "false";
        elif self.getFCD("visibility") == "internal":
            self["Visibility"] = "true";
        else:
            self.m_log.warning("finalize: \"visibility\" has invalid value: %s",
                self.getFCD("visibility"));
        
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
        self["writeInsertIntoMField"]       = False;
        self["writeReplaceInMFieldIndex"]   = False;
        self["writeReplaceInMFieldObject"]  = False;
        self["writeRemoveFromMFieldIndex"]  = False;
        self["writeRemoveFromMFieldObject"] = False;
        self["writeClearField"]             = False;
        
        if self.getFCD("pushToField") == "":
            self["writePushToField"] = True;
            if self.getFCD("pushToFieldAs") == "":
                self["PushToField"] = "pushTo" + self["Name"];
            else:
                self["PushToField"] = self.getFCD("pushToFieldAs");
        else:
            self["PushToField"] = self.getFCD("pushToField");
        
        if self.getFCD("insertIntoMField") == "":
            self["writeInsertIntoMField"] = True;
            if self.getFCD("insertIntoMFieldAs") == "":
                self["InsertIntoMField"] = "insertInto" + self["Name"];
            else:
                self["InsertIntoMField"] = self.getFCD("insertIntoMFieldAs");
        else:
            self["InsertIntoMField"] = self.getFCD("insertIntoMField");
        
        if self.getFCD("replaceInMFieldIndex") == "":
            self["writeReplaceInMFieldIndex"] = True;
            if self.getFCD("replaceInMFieldIndexAs") == "":
                self["ReplaceInMFieldIndex"] = "replaceIn" + self["Name"];
            else:
                self["ReplaceInMFieldIndex"] = self.getFCD("replaceInMFieldIndexAs");
        else:
            self["ReplaceInMFieldIndex"] = self.getFCD("replaceInMFieldIndex");
        
        if self.getFCD("replaceInMFieldObject") == "":
            self["writeReplaceInMFieldObject"] = True;
            if self.getFCD("replaceInMFieldObjectAs") == "":
                self["ReplaceInMFieldObject"] = "replaceIn" + self["Name"];
            else:
                self["ReplaceInMFieldObject"] = self.getFCD("replaceInMFieldObjectAs");
        else:
            self["ReplaceInMFieldObject"] = self.getFCD("replaceInMFieldObject");
        
        if self.getFCD("removeFromMFieldIndex") == "":
            self["writeRemoveFromMFieldIndex"] = True;
            if self.getFCD("removeFromMFieldIndexAs") == "":
                self["RemoveFromMFieldIndex"] = "removeFrom" + self["Name"];
            else:
                self["RemoveFromMFieldIndex"] = self.getFCD("removeFromMFieldIndexAs");
        else:
            self["RemoveFromMFieldIndex"] = self.getFCD("removeFromMFieldIndex");
        
        if self.getFCD("removeFromMFieldObject") == "":
            self["writeRemoveFromMFieldObject"] = True;
            if self.getFCD("removeFromMFieldObjectAs") == "":
                self["RemoveFromMFieldObject"] = "removeFrom" + self["Name"];
            else:
                self["RemoveFromMFieldObject"] = self.getFCD("removeFromMFieldObjectAs");
        else:
            self["RemoveFromMFieldObject"] = self.getFCD("removeFromMFieldObject");
        
        if self.getFCD("clearField") == "":
            self["writeClearField"] = True;
            if self.getFCD("clearFieldAs") == "":
                self["ClearField"] = "clear" + self["Name"];
            else:
                self["ClearField"] = self.getFCD("clearFieldAs");
        else:
            self["ClearField"] = self.getFCD("clearField");
        
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
        
        if self.isPtrField():
            if self.getFieldContainer().isSystemComponent():
                classInclude = "OSG";
            else:
                classInclude = "OpenSG/OSG";
            
            classInclude = classInclude + self["TypeCaps"];
            
            if classInclude.endswith("Ptr"):
                classInclude = classInclude[:-3];
            
            classInclude = classInclude.replace("Parent", "");
            classInclude = classInclude + ".h";
            
            self["ClassInclude"]     = classInclude;
            self["needClassInclude"] = True;
        
    def _dumpValues(self):
        self.m_log.info("Field dumpValues:");
        super(Field, self)._dumpValues(self.m_log);
    
