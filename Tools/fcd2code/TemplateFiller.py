
import copy;
import logging;
import re;

from ListStack import ListStack;

class TemplateFiller:
    """Fill in a template.
    """

    def __init__(self, templateLines):
        """Create a new TemplateFiller, that fills the template given in
           templateLines, which is a list of strings, as produced by readlines.
        """
        self.m_log      = logging.getLogger("TemplateFiller");
        self.m_inLines  = templateLines;
        self.m_outLines = [];
        
        self.m_varRE                  = re.compile(r"@!([^!@]*)!@");
        self.m_ifRE                   = re.compile(r"@@if[ \t]+(!|)([A-Za-z\.]*)");
        self.m_elseRE                 = re.compile(r"@@else");
        self.m_endifRE                = re.compile(r"@@endif");
        self.m_BeginFieldLoopRE       = re.compile(r"@@BeginFieldLoop");
        self.m_EndFieldLoopRE         = re.compile(r"@@EndFieldLoop");
        self.m_BeginSFFieldLoopRE     = re.compile(r"@@BeginSFFieldLoop");
        self.m_EndSFFieldLoopRE       = re.compile(r"@@EndSFFieldLoop");
        self.m_BeginMFFieldLoopRE     = re.compile(r"@@BeginMFFieldLoop");
        self.m_EndMFFieldLoopRE       = re.compile(r"@@EndMFFieldLoop");
        self.m_AdditionIncludesRE     = re.compile(r"@@AdditionalIncludes");
        self.m_AdditionPrioIncludesRE = re.compile(r"@@AdditionalPriorityIncludes");

    def fill(self, dictList):
        """Fill in a template using the contents of the dictionaries in
           dictList.
        """
        self.m_outLines = [];
        
        skipStack   = ListStack();
        skipCurrent = False;
        inLoop      = False;
        loopLines   = [];
        
        # Go through template and find loops, collect their lines in loopLines.
        # call _processLoop for the loopLines.
        
        context = [d for d in dictList];
        
        for lineNum, line in enumerate(self.m_inLines):
            # handle @@BeginFieldLoop
            matchBeginFieldLoop = self.m_BeginFieldLoopRE.search(line);
            if (not skipCurrent) and (matchBeginFieldLoop != None):
                #self.m_log.debug("fill: line %d -> BeginFieldLoop", lineNum);
                inLoop = True;
                continue;
            
            # handle @@BeginSFFieldLoop
            matchBeginSFFieldLoop = self.m_BeginSFFieldLoopRE.search(line);
            if (not skipCurrent) and (matchBeginSFFieldLoop != None):
                #self.m_log.debug("fill: line %d -> BeginSFFieldLoop", lineNum);
                inLoop = True;
                continue;
            
            # handle @@BeginMFFieldLoop
            matchBeginMFFieldLoop = self.m_BeginMFFieldLoopRE.search(line);
            if (not skipCurrent) and (matchBeginMFFieldLoop != None):
                #self.m_log.debug("fill: line %d -> BeginMFFieldLoop", lineNum);
                inLoop = True;
                continue;
            
            # handle loops - do not bother with conditionals they are handled in
            # _processLoop
            if (not skipCurrent) and (inLoop == True):
                # handle @@EndFieldLoop
                matchEndFieldLoop = self.m_EndFieldLoopRE.search(line);
                if matchEndFieldLoop != None:
                    #self.m_log.debug("fill: line %d -> EndFieldLoop", lineNum);
                    self._processLoop("Fields", loopLines, context);
                    inLoop    = False;
                    loopLines = [];
                    continue;
                
                # handle @@EndSFFieldLoop
                matchEndSFFieldLoop = self.m_EndSFFieldLoopRE.search(line);
                if matchEndSFFieldLoop != None:
                    #self.m_log.debug("fill: line %d -> EndSFFieldLoop", lineNum);
                    self._processLoop("SFields", loopLines, context);
                    inLoop    = False;
                    loopLines = [];
                    continue;
                
                # handle @@EndMFFieldLoop
                matchEndMFFieldLoop = self.m_EndMFFieldLoopRE.search(line);
                if matchEndMFFieldLoop != None:
                    #self.m_log.debug("fill: line %d -> EndMFFieldLoop", lineNum);
                    self._processLoop("MFields", loopLines, context);
                    inLoop    = False;
                    loopLines = [];
                    continue;
                
                loopLines.append(line);
                continue;
            
            # handle @@AdditionalIncludes
            matchAdditionalIncludes = self.m_AdditionIncludesRE.search(line);
            if matchAdditionalIncludes != None:
                self._processAdditionalIncludes(dictList);
                continue;

            # handle @@AdditionalIncludes
            matchAdditionalPrioIncludes = self.m_AdditionPrioIncludesRE.search(line);
            if matchAdditionalPrioIncludes != None:
                self._processAdditionalPrioIncludes(dictList);
                continue;
            
            # conditionals outside of loops must be treated here
            
            # handle @@if
            matchIf = self.m_ifRE.search(line);
            if matchIf != None:
                #self.m_log.debug("fill: line %d -> if", lineNum);
                skipStack.push(copy.copy(skipCurrent));
                
                if skipStack.top() == False:
                    if self._lookup(matchIf.group(2), dictList) == True:
                        skipCurrent = False;
                    else:
                        skipCurrent = True;
                    
                    if matchIf.group(1) == "!":
                        skipCurrent = not skipCurrent;
                continue;
            
            # handle @@else
            matchElse = self.m_elseRE.search(line);
            if matchElse != None:
                #self.m_log.debug("fill: line %d -> else", lineNum);
                if skipStack.top() == False:
                    skipCurrent = not skipCurrent;
                continue;
                
            # handle @@endif
            matchEndif = self.m_endifRE.search(line);
            if matchEndif != None:
                #self.m_log.debug("fill: line %d -> endif", lineNum);
                skipCurrent = skipStack.top();
                skipStack.pop();
                continue;
            
            if skipCurrent == True:
                continue;
            
            # a line with regular text - substitute variables and add to output
            self.m_outLines.append(self._substituteVariables(line, context));
        
        return self.m_outLines;
    
    def _processAdditionalIncludes(self, context):
        includeList = self._lookup("AdditionalIncludes", context);
        
        for include in includeList:
            self.m_outLines.append("#include <" + include + ">\n");

    def _processAdditionalPrioIncludes(self, context):
        includeList = self._lookup("AdditionalPriorityIncludes", context);
        
        for include in includeList:
            self.m_outLines.append("#include <" + include + ">\n");
    
    def _processLoop(self, loopType, loopLines, context):
        """For loopType == "Fields"  repeat lines in loopLines for all fields
           for loopType == "SFields" repeat lines in loopLines for all sfields
           for loopType == "MFields" repeat lines in loopLines for all mfields
        """
        if loopType == "Fields" or loopType == "SFields" or loopType == "MFields":
            fields = self._lookup(loopType, context);
        else:
            self.m_log.error("_processLoop: unknown loopType \"%s\"." % loopType);
            return;
        
        localDict = dict([("field", None)]);
        loopContext = [localDict];
        for c in context:
            loopContext.append(c);
        
        for field in fields:
            localDict["field"] = field;
            
            skipStack   = ListStack();
            skipCurrent = False;
            
            for line in loopLines:
                # handle @@if
                matchIf = self.m_ifRE.search(line);
                if matchIf != None:
                    skipStack.push(copy.copy(skipCurrent));
                    
                    if skipStack.top() == False:
                        if self._lookup(matchIf.group(2), loopContext) == True:
                            skipCurrent = False;
                        else:
                            skipCurrent = True;
                        
                        if matchIf.group(1) == "!":
                            skipCurrent = not skipCurrent;
                    continue;
                
                # handle @@else
                matchElse = self.m_elseRE.search(line);
                if matchElse != None:
                    if skipStack.top() == False:
                        skipCurrent = not skipCurrent;
                    continue;
                    
                # handle @@endif
                matchEndif = self.m_endifRE.search(line);
                if matchEndif != None:
                    skipCurrent = skipStack.top();
                    skipStack.pop();
                    continue;
                
                if skipCurrent == True:
                    continue;
                
                # a line with regular text - substitute variables and add to output
                self.m_outLines.append(self._substituteVariables(line, loopContext));
    
    def _substituteVariables(self, inLine, context):
        """Replace all variables in inLine and return the resulting line.
        """
        indexOffset = 0;
        outLine = inLine[:];
        for matchVar in self.m_varRE.finditer(inLine):
            varString = matchVar.group(1);
            varLen    = len(varString) + 4;
            
            if varString.find(":") != -1:
                varName     = varString.split(":")[0];
                varFieldLen = int(varString.split(":")[1]);
            else:
                varName     = varString;
                varFieldLen = 0;
            
            varValue = self._lookup(varName, context);
            varValue = varValue.ljust(varFieldLen);
            repLen   = len(varValue);
            
            outLine = outLine[:matchVar.start()+indexOffset] + varValue + \
                      outLine[matchVar.end()+indexOffset:];
            indexOffset = indexOffset + (repLen - varLen);
        
        return outLine;
    
    def _lookup(self, var, context):
        """Determine the value of var in the given context, which is a dict or
           a list of dicts.
           var may consist of multiple parts separated by dots, i.e.
           field.prevField.Name
           In that case the first part is looked up in the given context, the
           next part in the context returned by the first lookup and so forth.
        """
        #self.m_log.debug("_lookup: var: %s" % var);
        
        varParts = var.split(".");
        value    = None;
        
        for part in varParts:
            if isinstance(context, list):
                for elem in context:
                    if elem.has_key(part):
                        value = elem[part];
                        break;
            elif context.has_key(part):
                value = context[part];
            else:
                value = context;
            
            if value == None:
                self.m_log.warning("_lookup: value is None for var: %s part: %s",
                    var, part);
                break;
            
            context = value;
        return value;
    
