
import re;
import logging;

class Field:
    """Represents all information read from a .fcd file for a Field.
       The data from the .fcd file is stored in the m_fcdDict dictionary via
       setFCDEntry/getFCDEntry and during finalization the actual data used by
       the templates is filled into m_dict, which can be accessed via the []
       operator.
    """

    def __init__(self):
        self.m_log = logging.getLogger("Field");
        self.m_fieldContainer = None;
        self.m_fcdDict        = {};
        self.m_dict           = {};
        
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.m_fcdDict = dict([ ("name",                     None),
                                ("type",                     None),
                                ("typeNamespace",            ""),
                                ("cardinality",              None),
                                ("visibility",               "external"),
                                ("flags",                    ""),
                                ("defaultValue",             None),
                                ("access",                   "public"),
                                ("defaultHeader",            None),
                                ("header",                   "(AUTO)"),
                                ("description",              ""),
                                ("checkNilPtr",              "true"),
                                ("linkSParent",              "false"),
                                ("linkMParent",              "false"),
                                ("doRefCount",               "true"),
                                ("passFieldMask",            "false"),
                                ("removeTo",                 ""),
                                ("removeToSet",              "false"),
                                ("clearMField",              "true"),
                                ("pushToField",              ""),
                                ("insertIntoMField",         ""),
                                ("replaceInMFieldIndex",     ""),
                                ("replaceInMFieldObject",    ""),
                                ("removeFromMFieldIndex",    ""),
                                ("removeFromMFieldObject",   ""),
                                ("clearField",               ""),
                                ("pushToFieldAs",            ""),
                                ("insertIntoMFieldAs",       ""),
                                ("replaceInMFieldIndexAs",   ""),
                                ("replaceInMFieldObjectAs",  ""),
                                ("removeFromMFieldIndexAs",  ""),
                                ("removeFromMFieldObjectAs", ""),
                                ("clearFieldAs",             ""),
                                ("needClassInclude",         "true") ]);
    
    def setFieldContainer(self, container):
        self.m_fieldContainer = container;
    
    def getFieldContainer(self):
        return self.m_fieldContainer;
    
    #
    # Modify the input (fcd) dictionary
    
    def setFCDEntry(self, fcdName, fcdValue):
        self.m_fcdDict[fcdName] = fcdValue;
    
    def getFCDEntry(self, fcdName):
        return self.m_fcdDict.get(fcdName, None);
    
    #
    # Modify the output dictionary
    
    def setEntry(self, name, value):
        self.m_dict[name] = value;
    
    def getEntry(self, name):
        return self.m_dict.get(name, None);
    
    #
    # Emulate a mapping type - gives access to the output dictionary
    
    def __getitem__(self, key):
        return self.getEntry(key);
    
    def __setitem__(self, key, value):
        self.setEntry(key, value);
    
    def has_key(self, key):
        return self.m_dict.has_key(key);
    
    def __contains__(self, key):
        return (key in self.m_dict);
    
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
        fullType  = self.getFCDEntry("type");
        typeName  = self.getFCDEntry("type");
        namespace = self.getFCDEntry("typeNamespace");
        
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
        
        self["Name"]          = self.getFCDEntry("name")[0].upper() + self.getFCDEntry("name")[1:];
        self["DescName"]      = self.getFCDEntry("name");
        
        self["isPrivate"]   = False;
        self["isProtected"] = False;
        self["isPublic"]    = False;
        
        if self.getFCDEntry("access") == "private":
            self["isPrivate"] = True;
        elif self.getFCDEntry("access") == "protected":
            self["isProtected"] = True;
        elif self.getFCDEntry("access") == "public":
            self["isPublic"] = True;
        else:
            self.m_log.warning("finalize: \"access\" has invalid value: %s", 
                self.getFCDEntry("access"));
        
        self["isSField"] = False;
        self["isMField"] = False;
        
        if self.getFCDEntry("cardinality") == "single":
            self["isSField"] = True;
            self["CARD"]     = "SF";
            self["VarName"]  = "sf" + self["Name"];
        elif self.getFCDEntry("cardinality") == "multi":
            self["isMField"] = True;
            self["CARD"]     = "MF";
            self["VarName"]  = "mf" + self["Name"];
        else:
            self.m_log.warning("finalize: \"cardinality\" has invalid value: %s",
                self.getFCDEntry("cardinality"));
        
        if self["Type"].endswith("Ptr"):
            self["isPtrField"] = True;
        else:
            self["isPtrField"] = False;
        
        # escape character sequences not allowed in a C string.
        safeDesc = self.getFCDEntry("description");
        safeDesc = safeDesc.replace("\\", "\\\\");
        safeDesc = safeDesc.replace("\t", "\\t");
        safeDesc = safeDesc.replace("\n", "\\n");
        safeDesc = safeDesc.replace("\"", "\\\"");
        
        self["Description"]     = self.getFCDEntry("description");
        self["SafeDescription"] = safeDesc;
        
        if self.getFCDEntry("doRefCount") == "true":
            self["doRefCount"] = True;
        else:
            self["doRefCount"] = False;
        
        if self.getFCDEntry("linkSParent") == "true":
            self["linkSParent"] = True;
        else:
            self["linkSParent"] = False;
        
        if self.getFCDEntry("linkMParent") == "true":
            self["linkMParent"] = True;
        else:
            self["linkMParent"] = False;
        
        if self.getFCDEntry("checkNilPtr") == "true":
            self["checkNilPtr"] = True;
        else:
            self["checkNilPtr"] = False;
        
        if self.getFCDEntry("passFieldMask") == "true":
            self["PassFieldMask"] = True;
        else:
            self["PassFieldMask"] = False;
        
        typeInclude = "";
        
        if ((self.getFCDEntry("header") == "")      or
            (self.getFCDEntry("header") == "(AUTO)")  ):
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
            typeInclude = self.getFCDEntry("header");
        
        self["TypeInclude"] = typeInclude;
        
        if self.getFieldContainer().isDecoratable():
            self["MethodType"] = "virtual";
        else:
            self["MethodType"] = "";
        
        if ((self.getFCDEntry("defaultHeader") != None) and
            (self.getFCDEntry("defaultHeader") != ""  )    ):
            self["hasDefaultHeader"] = True;
            
            if ((self.getFCDEntry("defaultHeader").find("\"") == -1) and
                (self.getFCDEntry("defaultHeader").find("<")  == -1)    ):
                self["DefaultHeader"] = "\"" + self.getFCDEntry("defaultHeader") + "\"";
            else:
                self["DefaultHeader"] = self.getFCDEntry("defaultHeader");
        else:
            self["hasDefaultHeader"] = False;
        
        if ((self.getFCDEntry("defaultValue") != None) and
            (self.getFCDEntry("defaultValue") != ""  )    ):
            self["TypedDefault"] = \
                self["TypeNamespace"] + self["Type"] + "(" + \
                self.getFCDEntry("defaultValue") + ")";
        else:
            self["TypedDefault"] = "";
        
        if self.getFCDEntry("visibility") == "external":
            self["Visibility"] = "false";
        elif self.getFCDEntry("visibility") == "internal":
            self["Visibility"] = "true";
        else:
            self.m_log.warning("finalize: \"visibility\" has invalid value: %s",
                self.getFCDEntry("visibility"));
        
        fieldFlagsOverride = False;
        flags              = None,
        
        if self.isSField():
            if ((self.getFCDEntry("fieldFlags") != None) and
                (self.getFCDEntry("fieldFlags") != ""  )    ):
                fieldFlagsOverride = True;
            else:
                flags = "Field::SFDefaultFlags";
            
        elif self.isMField():
            if ((self.getFCDEntry("fieldFlags") != None) and
                (self.getFCDEntry("fieldFlags") != ""  )    ):
                fieldFlagsOverride = True;
            else:
                flags = "Field::MFDefaultFlags";
        
        if fieldFlagsOverride:
            flagsFCD = self.getFCDEntry("fieldFlags").split(",");
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
        
        self["Flags"]           = flags;
        
        self["writePushToField"]            = False;
        self["writeInsertIntoMField"]       = False;
        self["writeReplaceInMFieldIndex"]   = False;
        self["writeReplaceInMFieldObject"]  = False;
        self["writeRemoveFromMFieldIndex"]  = False;
        self["writeRemoveFromMFieldObject"] = False;
        self["writeClearField"]             = False;
        
        if self.getFCDEntry("pushToField") == "":
            self["writePushToField"] = True;
            if self.getFCDEntry("pushToFieldAs") == "":
                self["PushToField"] = "pushTo" + self["Name"];
            else:
                self["PushToField"] = self.getFCDEntry("pushToFieldAs");
        else:
            self["PushToField"] = self.getFCDEntry("pushToField");
        
        if self.getFCDEntry("insertIntoMField") == "":
            self["writeInsertIntoMField"] = True;
            if self.getFCDEntry("insertIntoMFieldAs") == "":
                self["InsertIntoMField"] = "insertInto" + self["Name"];
            else:
                self["InsertIntoMField"] = self.getFCDEntry("insertIntoMFieldAs");
        else:
            self["InsertIntoMField"] = self.getFCDEntry("insertIntoMField");
        
        if self.getFCDEntry("replaceInMFieldIndex") == "":
            self["writeReplaceInMFieldIndex"] = True;
            if self.getFCDEntry("replaceInMFieldIndexAs") == "":
                self["ReplaceInMFieldIndex"] = "replaceIn" + self["Name"];
            else:
                self["ReplaceInMFieldIndex"] = self.getFCDEntry("replaceInMFieldIndexAs");
        else:
            self["ReplaceInMFieldIndex"] = self.getFCDEntry("replaceInMFieldIndex");
        
        if self.getFCDEntry("replaceInMFieldObject") == "":
            self["writeReplaceInMFieldObject"] = True;
            if self.getFCDEntry("replaceInMFieldObjectAs") == "":
                self["ReplaceInMFieldObject"] = "replaceIn" + self["Name"];
            else:
                self["ReplaceInMFieldObject"] = self.getFCDEntry("replaceInMFieldObjectAs");
        else:
            self["ReplaceInMFieldObject"] = self.getFCDEntry("replaceInMFieldObject");
        
        if self.getFCDEntry("removeFromMFieldIndex") == "":
            self["writeRemoveFromMFieldIndex"] = True;
            if self.getFCDEntry("removeFromMFieldIndexAs") == "":
                self["RemoveFromMFieldIndex"] = "removeFrom" + self["Name"];
            else:
                self["RemoveFromMFieldIndex"] = self.getFCDEntry("removeFromMFieldIndexAs");
        else:
            self["RemoveFromMFieldIndex"] = self.getFCDEntry("removeFromMFieldIndex");
        
        if self.getFCDEntry("removeFromMFieldObject") == "":
            self["writeRemoveFromMFieldObject"] = True;
            if self.getFCDEntry("removeFromMFieldObjectAs") == "":
                self["RemoveFromMFieldObject"] = "removeFrom" + self["Name"];
            else:
                self["RemoveFromMFieldObject"] = self.getFCDEntry("removeFromMFieldObjectAs");
        else:
            self["RemoveFromMFieldObject"] = self.getFCDEntry("removeFromMFieldObject");
        
        if self.getFCDEntry("clearField") == "":
            self["writeClearField"] = True;
            if self.getFCDEntry("clearFieldAs") == "":
                self["ClearField"] = "clear" + self["Name"];
            else:
                self["ClearField"] = self.getFCDEntry("clearFieldAs");
        else:
            self["ClearField"] = self.getFCDEntry("clearField");
        
        if self.getFCDEntry("removeTo") != "":
            self.setFCDEntry("removeToSet", True);
            self["isRemoveToSet"]         = True;
            self["RemoveTo"]              = self.getFCDEntry("removeTo");
        else:
            self.setFCDEntry("removeToSet", False);
            self["isRemoveToSet"]         = False;
        
        if self.getFCDEntry("clearMField") == "true":
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
        
    def dumpValues(self):
        self.m_log.info("Field dumpValues: fcdDict:");
        for key, value in self.m_fcdDict.iteritems():
            self.m_log.info(key + "   >" + str(value) + "<");
        
        self.m_log.info("  Field dumpValues: Dict:");
        for key, value in self.m_dict.iteritems():
            self.m_log.info("  " + key + "   >"+ str(value) + "<");
            