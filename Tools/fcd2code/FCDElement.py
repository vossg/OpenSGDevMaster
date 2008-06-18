
import logging;
import re;

class FCDElement(object):
    """Base class for elements in a .fcd file.
       
       Defines two dictionaries, m_fcdDict holds entries read from the .fcd
       file, while m_tmplDict is filled during a call to finalize() with values
       that can be accessed through the [] operator.
    """
    
    def __init__(self):
        """Create new instance of FCDElement and initialize both dictionaries.
        """
        self.m_log      = logging.getLogger("FCDElement");
        self.m_fcdDict  = {};
        self.m_tmplDict = {};
    
    def getFCD(self, key):
        """Returns the <key> entry from m_fcdDict.
        """
        return self.m_fcdDict[key];
    
    def setFCD(self, key, value, allowNew = False):
        """Sets the <key> entry of m_fcdDict to <value>.
        """
        if allowNew:
            self.m_fcdDict[key] = value;
        else:
            if self.m_fcdDict.has_key(key):
                self.m_fcdDict[key] = value;
            else:
                self.m_log.warning("setFCD: Unknown key [%s]." % key);
    
    def _getFCDDict(self):
        """Returns m_fcdDict.
        """
        return self.m_fcdDict;
    
    def getTmpl(self, key):
        """Returns the <key> entry from m_tmplDict.
        """
        return self.m_tmplDict[key];
    
    def setTmpl(self, key, value):
        """Sets the <key> entry  of m_tmplDict to <value>.
        """
        self.m_tmplDict[key] = value;
    
    def _getTmplDict(self):
        """Returns m_tmplDict.
        """
        return self.m_tmplDict;
    
    def has_key(self, key):
        """Returns if m_tmplDict contains <key>.
        """
        return self.m_tmplDict.has_key(key);
    
    def __getitem__(self, key):
        """Emulate a mapping type, same as getTmpl(key).
        """
        return self.getTmpl(key);
    
    def __setitem__(self, key, value):
        """Emulate a mapping type, same as setTmpl(key, value).
        """
        self.setTmpl(key, value);
    
    def __contains__(self, key):
        """Emulate a mapping type, returns if m_tmplDict contains <key>.
        """
        return key in self.m_tmplDict;

    def _upcaseFirst(self, textValue):
        """Returns a copy of textValue with the first character converted to
           upper case.
        """
        if len(textValue) > 1:
            return textValue[0].upper() + textValue[1:];
        else:
            return textValue.upper();
      
    def _extractParagraphs(self, descText):
        """Splits descText into a list of paragraphs.
        """
        start     = 0;
        end       = 0;
        paraList  = [];
        paraEndRE = re.compile(r"\n[ \t]*\n");
         
        for paraEndMatch in paraEndRE.finditer(descText):
            end   = paraEndMatch.start();
            para  = descText[start:end];
            start = paraEndMatch.end();
            
            # ignore empty paragraphs.
            if para.strip() != "":
                paraList.append(para);
        
        if (len(paraList) == 0) and (descText.strip != ""):
            paraList.append(descText);
        
        return paraList;
    
    def _formatString(self, descText, indent):
        """Formats the description string.
        """
        indentStr   = " " * indent;
        paraList    = self._extractParagraphs(descText);
        paraListLen = len(paraList);
        
        for paraNum in range(paraListLen):
            lineList    = paraList[paraNum].split("\n");
            lineListLen = len(lineList);
            
            while lineListLen > 0 and lineList[0].strip() == "":
                lineList     = lineList[1:];
                lineListLen -= 1;
            
            while lineListLen > 0 and lineList[-1].strip() == "":
                lineList     = lineList[0:-1];
                lineListLen -= 1;
            
            for lineNum in range(lineListLen):
                if paraNum > 0 or lineNum > 0:
                    lineList[lineNum] = indentStr + lineList[lineNum];
            
            paraList[paraNum] = "\n".join(lineList);
        
        return "\n\n".join(paraList);
    
    def _formatSafeString(self, descText, indent):
        """Formats the safe description string.
        """
        indentStr   = " " * indent;
        lineList    = descText.split("\n");
        lineListLen = len(lineList);
        
        while lineListLen > 0 and lineList[0].strip() == "":
            lineList     = lineList[1:];
            lineListLen -= 1;
        
        while lineListLen > 0 and lineList[lineListLen-1].strip() == "":
            lineList     = lineList[0:lineListLen-1];
            lineListLen -= 1;
        
        for lineNum, lineText in enumerate(lineList):
            lineText = lineText.replace("\\",  "\\\\");
            lineText = lineText.replace("\t",  "\\t");
            lineText = lineText.replace("\n",  "\\n");
            lineText = lineText.replace("\"",  "\\\"");
            
            if lineNum == 0:
                lineText =             "\"" + lineText + "\\n\"";
            else:
                lineText = indentStr + "\"" + lineText + "\\n\"";
            
            if lineNum < lineListLen - 1:
                lineText += "\n";
            
            lineList[lineNum] = lineText;
        
        return "".join(lineList);
    
    def _formatXML(self, lines, indent):
        """Formats the .fcd XML contents.
        """
        linesLen  = len(lines);
        indentStr = " " * indent;
        output    = [];
        
        for lineNum, line in enumerate(lines):
            line = line.replace("\\",  "\\\\");
            line = line.replace("\t",  "\\t");
            line = line.replace("\n",  "");
            line = line.replace("\r",  "");
            line = line.replace("\"",  "\\\"");
            
            if lineNum == 0:
                output.append(            "\"" + line + "\\n\"");
            else:
                output.append(indentStr + "\"" + line + "\\n\"");
            
            if lineNum < linesLen - 1:
                output[lineNum] += "\n";
        
        return "".join(output);
    
    def _dumpValues(self, log):
        """Prints the contents of m_fcdDict and m_tmplDict to <log>
        """
        sortFCDKeys = self._getFCDDict().keys();
        sortFCDKeys.sort();
        for key in sortFCDKeys:
            log.info(key + " >" + str(self._getFCDDict()[key]) + "<");
        
        sortTmplKeys = self._getTmplDict().keys();
        sortTmplKeys.sort();
        for key in sortTmplKeys:
            log.info("\t" + key + " >" + str(self._getTmplDict()[key]) + "<");
    
