
import logging;

from FCDElement import FCDElement;

class FieldContainer(FCDElement):
    """Represents a <Field/> element from a .fcd file.
    """

    def __init__(self):
        super(FieldContainer, self).__init__();
        self.m_log    = logging.getLogger("FieldContainer");
        self.m_fields = [];
        self.m_usedTypeInclude  = {};
        self.m_usedFieldInclude = {};
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.setFCD("name",                       "",       True);
        self.setFCD("parent",                     "",       True);
        self.setFCD("mixinparent",                "",       True);
        self.setFCD("mixinheader",                "",       True);
        self.setFCD("library",                    "",       True);
        self.setFCD("pointerfieldtypes",          "",       True);
        self.setFCD("structure",                  "",       True);
        self.setFCD("systemcomponent",            "true",   True);
        self.setFCD("parentsystemcomponent",      "true",   True);
        self.setFCD("decoratable",                "false",  True);
        self.setFCD("useLocalIncludes",           "false",  True);
        self.setFCD("isNodeCore",                 "false",  True);
        self.setFCD("isBundle",                   "false",  True);
        self.setFCD("description",                "",       True);
        self.setFCD("group",                      "",       True);
#        self.setFCD("namespace",                  "",       True);
        self.setFCD("decorateeFieldFlags",        "",       True);
        self.setFCD("additionalIncludes",         "",       True);
        self.setFCD("additionalPriorityIncludes", "",       True);
        self.setFCD("fcdFileLines",               [],       True);
        self.setFCD("fieldsUnmarkedOnCreate",     "0",      True);
        self.setFCD("libnamespace",               "OSG",    True);
        self.setFCD("parentnamespace",            "",       True);
        self.setFCD("childFields",                "none",   True);
        self.setFCD("parentFields",               "none",   True);
        self.setFCD("docGroupBase",               "",       True);
        self.setFCD("realparent",                 "",       True);
        self.setFCD("authors",                    "",       True);
        self.setFCD("typeDescAddable",            "false",  True);
        self.setFCD("dynFCDerived",               "false",  True);
        self.setFCD("dynFCDerived",               "false",  True);
        self.setFCD("package",                    "OSG",    True);
    #
    # Access fields
    
    def addField(self, field):
        idx = len(self.m_fields);
        field.setFieldContainer(self);
        self.m_fields.append(field);
        return idx;

    def subField(self, field):
        self.m_fields.remove(field)

    #
    # Common tests
    
    def isSystemComponent(self):
        return self["isSystemComponent"];
    
    def isDecoratable(self):
        return self["isDecoratable"];

    def hasAuthors(self):
        return len(self["authors"]) != 0;
    
    def setupFieldContainer(self):
        self["Classname"]    = self.getFCD("name");
        self["CLASSNAME"]    = self.getFCD("name").upper();
        self["Parent"]       = self.getFCD("parent");
        self["isDecorator"]  = False;
        self["nsFilePrefix"] = "";

        if (self.getFCD("libnamespace") != "" and \
            self.getFCD("libnamespace") != "OSG"):
          self["nsFilePrefix"] = self.getFCD("libnamespace");

        self["nsParentFilePrefix"] = ""        

        if self.getFCD("parentnamespace") == "" and \
           self.getFCD("libnamespace")    != "OSG" :

          self["nsParentFilePrefix"] = self.getFCD("libnamespace")
        else:
          if self.getFCD("parentnamespace") != "OSG":
            self["nsParentFilePrefix"] = self.getFCD("parentnamespace")

    def setupDecorator(self):
        self["Classname"]    = self.getFCD("name") + "Decorator";
        self["CLASSNAME"]    = self.getFCD("name").upper() + "DECORATOR";
        self["Parent"]       = self.getFCD("name");
        self["RealParent"]   = self.getFCD("name");
        self["isDecorator"]  = True;

        if (self.getFCD("libnamespace") != "" and \
            self.getFCD("libnamespace") != "OSG"):
          self["nsFilePrefix"] = self.getFCD("libnamespace");

    def finalize(self):
        if len(self.m_fields) > 0:
            self["hasFields"] = True;
        else:
            self["hasFields"] = False;
        
            
        if self.getFCD("library") != "":
            self["isInLibrary"] = True;
            self["Libname"]     = self.getFCD("library");
            self["LIBNAME"]     = self.getFCD("library").upper();
        else:
            if self.getFCD("systemcomponent") == "true":
                self.m_log.error("finalize: \"library\" not set for a systemcomponent.");
                self["isInLibrary"] = True;
                self["Libname"]     = "<UNDEF>";
                self["LIBNAME"]     = "<UNDEF>";
            else:
                self["isInLibrary"] = False;
                self["Libname"]     = None;
                self["LIBNAME"]     = None;

        if self.getFCD("docGroupBase") != "":
            self["DocGroupBase"] = self.getFCD("docGroupBase")
        else:
            self["DocGroupBase"] = "Grp" + str(self["Libname"])
        
        if self.getFCD("name") != "":
            self["Classname"] = self.getFCD("name");
            self["CLASSNAME"] = self.getFCD("name").upper();
        else:
            self.m_log.error("finalize: \"name\" has no valid value.");
            self["Classname"] = "<UNDEF>";
            self["CLASSNAME"] = "<UNDEF>";
        
        if self.getFCD("authors") != "":
            self["hasAuthors"] = True;
            self["authors"] = self.getFCD("authors");
            self["Authors"] = self.getFCD("authors");
        else:
            self["hasAuthors"] = False;
            self["authors"] = "";
            self["Authors"] = "";

        self["Package"] = self.getFCD("package");

        #Create the Authors comment text
        self["AuthorsCommentText"] = "";
        if self.hasAuthors():
            MaxLineLength = 78;
            ContactPreText   = " * contact: ";
            SubLinesPreText  = " *          ";
            SubLinesPostText = "*";

            AuthorTextLength = MaxLineLength - len(ContactPreText) - len(SubLinesPostText);

            #Split the authors into a list
            AuthorList = self["Authors"].split(",");

            #Create a comment line for each author
            for AuthorIndex in range(len(AuthorList)):

                AuthorCommentLine = AuthorList[AuthorIndex];
                AuthorCommentLine = AuthorCommentLine.strip();

                if len(AuthorCommentLine) <= AuthorTextLength:
                    AuthorCommentLine += (" "*(AuthorTextLength-len(AuthorCommentLine)));
                else:
                    AuthorCommentLine = AuthorCommentLine[0:AuthorTextLength];
                    self.m_log.error("finalize: \"authors\": Max size of per-author text cannot be greater than: " 
                                    + str(AuthorTextLength) + ". Truncating to " + AuthorCommentLine);

                #If this is the first line
                if AuthorIndex == 0 :
                    AuthorCommentLine = ContactPreText + AuthorCommentLine;
                else :
                    AuthorCommentLine = SubLinesPreText + AuthorCommentLine;
                    
                AuthorCommentLine = AuthorCommentLine + SubLinesPostText;

                #If this is not the first line
                if AuthorIndex != 0 :
                    #Add a newline before this line
                    AuthorCommentLine = "\n" + AuthorCommentLine;

                self["AuthorsCommentText"] += AuthorCommentLine;


        if self.getFCD("parent") != "":
            self["Parent"] = self.getFCD("parent");
        else:
            self.m_log.error("finalize: \"parent\" has no valid value.");
            self["Parent"] = "<UNDEF>";

        if self.getFCD("realparent") != "":
            self["RealParent"] = self.getFCD("realparent");
        else:
            self["RealParent"] = self["Parent"];

     
        
        if self.getFCD("decoratable") == "true":
            self["isDecoratable"] = True;
        else:
            self["isDecoratable"] = False;

        if self.getFCD("isBundle") == "true":
            self["isBundle"] = True;
        else:
            self["isBundle"] = False;
        
        if self.getFCD("systemcomponent") == "true":
            self["isSystemComponent"] = True;
        else:
            self["isSystemComponent"] = False;
        
        if self.getFCD("structure") == "concrete":
            self["isAbstract"] = False;
        elif self.getFCD("structure") == "abstract":
            self["isAbstract"] = True;
        else:
            self.m_log.warning("finalize: \"structure\" has no valid value.");
        
        if ((self.getFCD("parentsystemcomponent") == "true") and
            (self.getFCD("systemcomponent")       == "false")   ):
            self["ParentHeaderPrefix"] = "OpenSG/";
        else:
            self["ParentHeaderPrefix"] = "";
        
        if self.getFCD("systemcomponent") == "false":
            self["HeaderPrefix"] = "OpenSG/";
        else:
            self["HeaderPrefix"] = "";
        
        if self.getFCD("description").strip() == "":
            self["Description"]     = "";
            self["SafeDescription"] = "\"\"";
        else:
            self["Description"]     = self._formatString    (self.getFCD("description"), 4)
            self["SafeDescription"] = self._formatSafeString(self.getFCD("description"), 4)
        
        self["hasProtectedFields"] = False;
        self["hasPublicFields"]    = False;
        self["hasPtrFields"]       = False;
        self["hasChildFields"]     = False;
        self["hasParentFields"]    = False;

        self["Fields"]  = [];
        self["SFields"] = [];
        self["MFields"] = [];

        self["hasValueMField"] = False;
        
        foundChildField = False;

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

            # only use type includes once
            if self.m_usedTypeInclude.has_key(field["TypeInclude"]):
                field["needTypeInclude"] = False;
            else:
                self.m_usedTypeInclude[field["TypeInclude"]] = True;

            # only use field includes once
            if self.m_usedFieldInclude.has_key(field["FieldInclude"]):
                field["needFieldInclude"] = False;
            else:
                self.m_usedFieldInclude[field["FieldInclude"]] = True;

            self["Fields"].append(field);
                           
            if field.isProtected():
                self["hasProtectedFields"] = True;
            
            if field.isPublic() or field.isPublicRead():
                self["hasPublicFields"] = True;
            
            if field.isPtrField() and field.hasAccess() and not field.isParentField():
                self["hasPtrFields"] = True;
            
            if field.isChildField():

                if foundChildField == False:
                    field["isFirstChildField"] = True
                    foundChildField = True
                else:
                    field["isFirstChildField"] = False

                self["hasChildFields"] = True

            if field["category"] == "pointer" and field["pointertype"] == "parent":
                self["hasParentFields"] = True;

            if field.isSField():
                self["SFields"].append(field);
            
            if field.isMField():
                self["MFields"].append(field);

                if not field.isPtrField():
                    self["hasValueMField"] = True;

        if self.getFCD("isNodeCore") == "true" or self.getFCD("isNodeCore") == "True":
            self["isNodeCore"] = True;
        else:
            self["isNodeCore"] = False;
            
        self["PointerField"]   = False;
        self["SFPointerField"] = False;
        self["MFPointerField"] = False;
        self["ChildField"]     = False;
        self["ChildSFields"]   = False;
        self["ChildMFields"]   = False;
        self["ChildSParent"]   = False;
        self["ChildMParent"]   = False;
        self["ParentSFields"]  = False;
        self["ParentMFields"]  = False;
        self["ParentField"]    = False;

        TraitsNS = 1;

        if self.getFCD("pointerfieldtypes") == "both":
            self["PointerField"]   = True;
            self["SFPointerField"] = True;
            self["MFPointerField"] = True;
        elif self.getFCD("pointerfieldtypes") == "single":
            self["PointerField"]   = True;
            self["SFPointerField"] = True;
        elif self.getFCD("pointerfieldtypes") == "multi":
            self["PointerField"]   = True;
            self["MFPointerField"] = True;


        if self.getFCD("childFields") == "multi" or \
           self.getFCD("childFields") == "both":
            self["ChildMFields"] = True
            self["ChildField"]   = True
            self["ChildNS"]      = '%d' % TraitsNS

        if self.getFCD("childFields") == "single" or \
           self.getFCD("childFields") == "both":
            self["ChildSFields"] = True
            self["ChildField"]   = True
            self["ChildNS"]      = '%d' % TraitsNS
            
        if self.getFCD("childFields") == "single" or \
           self.getFCD("childFields") == "multi"  or \
           self.getFCD("childFields") == "both":
            TraitsNS += 1


        if self.getFCD("parentFields") == "multi" or \
           self.getFCD("parentFields") == "both":
            self["ParentMFields"] = True
            self["ParentField"]   = True
            self["ParentNS"]      = '%d' % TraitsNS

        if self.getFCD("parentFields") == "single" or \
           self.getFCD("parentFields") == "both":
            self["ParentSFields"] = True
            self["ParentField"]   = True
            self["ParentNS"]      = '%d' % TraitsNS


        self["MethodType"]  = "";
        
        if self.getFCD("decoratable") == "true":
            self["MethodType"] = "virtual";

        if self.getFCD("group") != "":
            self["Group"] = self.getFCD("group");
        else:
            if self["CLASSNAME"]     .endswith("ATTACHMENT") == True or \
               self["Parent"].upper().endswith("ATTACHMENT") == True:
                self["Group"] = self["Classname"]
            else:
                self["Group"] = "NULL";

#        if self.getFCD("namespace") != "":
#            self["Namespace"] = self.getFCD("namespace");
#        else:
#            self["Namespace"] = "0";

        self["inExternalNamespace"] = False;
        self["LibNamespace"]        = "OSG";
        self["LIBNAMESPACE"]        = "OSG";
        self["IMPORTNAMESPACE"]     = "";
        self["nsConst"]             = "nsOSG";
        self["nsFilePrefix"] = "";

        if self.getFCD("libnamespace") != "":

          self["LibNamespace"]    = self.getFCD("libnamespace");
          self["LIBNAMESPACE"]    = self.getFCD("libnamespace").upper();

          if self["LIBNAMESPACE"] != "OSG":
            self["IMPORTNAMESPACE"]     = "OSG_IMPORT_NAMESPACE;\n";
            self["inExternalNamespace"] = True;
            self["nsConst"]             = "ns" + self.getFCD("libnamespace");
            self["nsFilePrefix"]        = self.getFCD("libnamespace");

        self["FieldsUnmarkedOnCreate"] = self.getFCD("fieldsUnmarkedOnCreate");
        self["TypeDescAddable"] = self.getFCD("typeDescAddable");
        self["DynFCDerived"] = self.getFCD("dynFCDerived");

        if self.getFCD("dynFCDerived") == "true":
            self["isDynFCDerived"] = True;
        else:
            self["isDynFCDerived"] = False;

        if self.getFCD("mixinparent") != "":
            self["MixinParent"] = self.getFCD("mixinparent");            
            self["hasMixinParent"] = True

            if self.getFCD("mixinheader") != "":
                self["MixinHeader"] = self.getFCD("mixinheader");
            else:
                self["MixinHeader"] = "OSG" + self["nsFilePrefix"] + self["MixinParent"] + ".h"
        else:
            self["MixinParent"] = ""
            self["hasMixinParent"] = False

        decorateeFieldFlags = self.getFCD("decorateeFieldFlags");
        if decorateeFieldFlags == "":
            self["DecorateeFieldFlags"] = "Field::SFDefaultFlags";
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
        
        includesList = self.getFCD("additionalIncludes").split(",");
        self["AdditionalIncludes"] = [];
        for include in includesList:
            include = include.strip();
            if include != "":
                self["AdditionalIncludes"].append(include);

        includesList = self.getFCD("additionalPriorityIncludes").split(",");
        self["AdditionalPriorityIncludes"] = [];
        for include in includesList:
            include = include.strip();
            if include != "":
                self["AdditionalPriorityIncludes"].append(include);

    def setFCDContents(self, fcdContents):
        self.setFCD("fcdFileLines", fcdContents, True);
        if fcdContents == []:
            self["Fcdxml"] = "\"\"";
        else:
            self["Fcdxml"] = self._formatXML(fcdContents, 4);
    
    def _dumpValues(self):
        self.m_log.info("FieldContainer dumpValues:");
        super(FieldContainer, self)._dumpValues(self.m_log);
        
        for field in self.m_fields:
            field._dumpValues();
    
