
import logging;

class FieldContainer:
    """Represents all information read from a .fcd file for a FieldContainer.
       The data from the .fcd file is stored in the m_fcdDict dictionary via
       setFCDEntry/getFCDEntry and during finalization the actual data used by
       the templates is filled into m_dict, which can be accessed via the []
       operator.
    """

    def __init__(self):
        self.m_log = logging.getLogger("FieldContainer");
        
        self.m_fcdDict = {};
        self.m_dict    = {};
        self.m_fields  = [];
        
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.m_fcdDict = dict([ ("name",                  None),
                                ("parent",                None),
                                ("library",               None),
                                ("pointerfieldtypes",     None),
                                ("structure",             None),
                                ("systemcomponent",       "true"),
                                ("parentsystemcomponent", "true"),
                                ("decoratable",           "false"),
                                ("useLocalIncludes",      "false"),
                                ("isNodeCore",            "false"),
                                ("description",           ""),
                                ("group",                 "NULL"),
                                ("namespace",             None),
                                ("decorateeFieldFlags",   ""),
                                ("additionalIncludes",    "")     ]);
                                
    
    #
    # Modify the input (fcd) dictionary
    
    def setFCDEntry(self, fcdName, fcdValue):
        """ Set data from the fcd file.
        """
        self.m_fcdDict[fcdName] = fcdValue;
    
    def getFCDEntry(self, fcdName):
        """ Get data set from the fcd file.
        """
        return self.m_fcdDict.get(fcdName, None);
    
    #
    # Modify the output dictionary
    
    def setEntry(self, name, value):
        """ Set data derived from the fcd entries.
        """
        self.m_dict[name] = value;
    
    def getEntry(self, name):
        """ Get data derived from the fcd entries.
        """
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
    # Access fields
    
    def addField(self, field):
        idx = len(self.m_fields);
        field.setFieldContainer(self);
        self.m_fields.append(field);
        return idx;
    
    #
    # Common tests
    
    def isSystemComponent(self):
        return self["isSystemComponent"];
    
    def isDecoratable(self):
        return self["isDecoratable"];
    
    def setupFieldContainer(self):
        self["Classname"]   = self.getFCDEntry("name");
        self["CLASSNAME"]   = self.getFCDEntry("name").upper();
        self["Parent"]      = self.getFCDEntry("parent");
        self["isDecorator"] = False;
    
    def setupDecorator(self):
        self["Classname"]   = self.getFCDEntry("name") + "Decorator";
        self["CLASSNAME"]   = self.getFCDEntry("name").upper() + "DECORATOR";
        self["Parent"]      = self.getFCDEntry("name");
        self["isDecorator"] = True;
    
    def finalize(self):
        if len(self.m_fields) > 0:
            self["hasFields"] = True;
        else:
            self["hasFields"] = False;
        
        if self.getFCDEntry("library") != None:
            self["isInLibrary"] = True;
            self["Libname"]     = self.getFCDEntry("library");
            self["LIBNAME"]     = self.getFCDEntry("library").upper();
        else:
            self["isInLibrary"] = False;
            self["Libname"]     = None;
            self["LIBNAME"]     = None;
        
        if self.getFCDEntry("name") != None:
            self["Classname"] = self.getFCDEntry("name");
            self["CLASSNAME"] = self.getFCDEntry("name").upper();
        else:
            self.m_log.warning("finalize: \"name\" has no valid value.");
            self["Classname"] = "<UNDEF>";
            self["CLASSNAME"] = "<UNDEF>";
        
        if self.getFCDEntry("parent") != None:
            self["Parent"] = self.getFCDEntry("parent");
        else:
            self.m_log.warning("finalize: \"parent\" has no valid value.");
            self["Parent"] = "<UNDEF>";
        
        if self.getFCDEntry("decoratable") == "true":
            self["isDecoratable"] = True;
        else:
            self["isDecoratable"] = False;
        
        if self.getFCDEntry("systemcomponent") == "true":
            self["isSystemComponent"] = True;
        else:
            self["isSystemComponent"] = False;
        
        if self.getFCDEntry("structure") == "concrete":
            self["isAbstract"] = False;
        elif self.getFCDEntry("structure") == "abstract":
            self["isAbstract"] = True;
        else:
            self.m_log.warning("finalize: \"structure\" has no valid value.");
        
        if ((self.getFCDEntry("parentsystemcomponent") == "true") and
            (self.getFCDEntry("systemcomponent")       == "false")   ):
            self["ParentHeaderPrefix"] = "OpenSG/";
        else:
            self["ParentHeaderPrefix"] = "";
        
        if self.getFCDEntry("systemcomponent") == "false":
            self["HeaderPrefix"] = "OpenSG/";
        else:
            self["HeaderPrefix"] = "";
        
        if ((self.getFCDEntry("description") == None) or
            (self.getFCDEntry("description") == ""  )   ):
            self["Description"]     = "";
            self["SafeDescription"] = "";
        else:
            safeDesc = self.getFCDEntry("description");
            safeDesc = safeDesc.replace("\\", "\\\\");
            safeDesc = safeDesc.replace("\t", "\\t");
            safeDesc = safeDesc.replace("\n", "\\n");
            safeDesc = safeDesc.replace("\"", "\\\"");
            self["Description"]     = self.getFCDEntry("description");
            self["SafeDescription"] = safeDesc;
            
        self["Fcdxml"]          = "\"\"";
        
        self["hasPrivateFields"]   = False;
        self["hasProtectedFields"] = False;
        self["hasPublicFields"]    = False;
        self["hasPtrFields"]       = False;
        
        self["Fields"]  = [];
        self["SFields"] = [];
        self["MFields"] = [];
        
        for i, field in enumerate(self.m_fields):
            
            field.finalize();
            
            if i == 0:
                field["prevField"]    = None;
                field["isFirstField"] = True;
            else:
                field["prevField"]    = self.m_fields[i - 1];
                field["isFirstField"] = False;
            
            if i == len(self.m_fields) - 1:
                field["Separator"]   = "";
                field["nextField"]   = None;
                field["isLastField"] = True;
            else:
                field["Separator"]   = ",";
                field["nextField"]   = self.m_fields[i + 1];
                field["isLastField"] = False;
            
            self["Fields"].append(field);
            
            if field.isPrivate():
                self["hasPrivateFields"] = True;
                
            if field.isProtected():
                self["hasProtectedFields"] = True;
            
            if field.isPublic():
                self["hasPublicFields"] = True;
            
            if field.isPtrField():
                self["hasPtrFields"] = True;
            
            if field.isSField():
                self["SFields"].append(field);
            
            if field.isMField():
                self["MFields"].append(field);
        
        self["PointerField"]   = False;
        self["SFPointerField"] = False;
        self["MFPointerField"] = False;
        
        if self.getFCDEntry("pointerfieldtypes") == "both":
            self["PointerField"]   = True;
            self["SFPointerField"] = True;
            self["MFPointerField"] = True;
        elif self.getFCDEntry("pointerfieldtypes") == "single":
            self["PointerField"]   = True;
            self["SFPointerField"] = True;
        elif self.getFCDEntry("pointerfieldtypes") == "multi":
            self["PointerField"]   = True;
            self["MFPointerField"] = True;
        
        self["MethodType"]  = "";
        
        if self.getFCDEntry("decoratable") == "true":
            self["MethodType"] = "virtual";
        
        if self.getFCDEntry("group") != None:
            self["Group"] = self.getFCDEntry("group");
        else:
            self["Group"] = "NULL";
        
        if self.getFCDEntry("namespace") != None:
            self["Namespace"] = self.getFCDEntry("namespace");
        else:
            self["Namespace"] = "0";
        
        decorateeFieldFlags = self.getFCDEntry("decorateeFieldFlags");
        if (decorateeFieldFlags == None) or (decorateeFieldFlags == ""):
            self["DecorateeFieldFlags"] = decorateeFieldFlags;
        else:
            dffList  = decorateeFieldFlags.split(",");
            numFlags = len(dffList);
            decorateeFieldFlags = "(";
            
            for i, flag in enumerate(dffList):
                flag = flag.strip();
                
                if (i == 0) and (i != numFlags - 1):
                    decorateeFieldFlags = decorateeFieldFlags + "Field::" + flag + " |";
                    continue;
                
                if i == numFlags - 1:
                    if i == 0:
                        decorateeFieldFlags = decorateeFieldFlags + "Field::" + flag;
                    else:
                        decorateeFieldFlags = decorateeFieldFlags + " Field::" + flag;
                    continue;
                
                decorateeFieldFlags = decorateeFieldFlags + " Field::" + flag + " |";
            decorateeFieldFlags = decorateeFieldFlags + ")";
            self["DecorateeFieldFlags"] = decorateeFieldFlags;
        
        includesList = self.getFCDEntry("additionalIncludes").split(",");
        self["AdditionalIncludes"] = [];
        for include in includesList:
            include = include.strip();
            if include != "":
                self["AdditionalIncludes"].append(include);
    
    def dumpValues(self):
        self.m_log.info("FieldContainer.dump: fcdDict:");
        for key, value in self.m_fcdDict.iteritems():
            self.m_log.info(key + "    >" + str(value) + "<");
        
        self.m_log.info("  FieldContainer.dump: Dict:");
        for key, value in self.m_dict.iteritems():
            self.m_log.info("  " + key + "    >" + str(value) + "<");
        
        for field in self.m_fields:
            field.dumpValues();