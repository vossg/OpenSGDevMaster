
import logging;
import re;
import textwrap;

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
    
    def setFCD(self, key, value):
        """Sets the <key> entry of m_fcdDict to <value>.
        """
        self.m_fcdDict[key] = value;
    
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
        paraList    = self._extractParagraphs(descText);
        paraListLen = len(paraList);
        self.m_log.debug("paraList: %s", str(paraList));
        
        # reformat the paragraphs
        wrapper = textwrap.TextWrapper();
        wrapper.width             = 79 - indent;
        wrapper.initial_indent    = " " * indent;
        wrapper.subsequent_indent = " " * indent;
        wrapper.break_long_words  = False;
        
        for paraNum, paraText in enumerate(paraList):
            paraList[paraNum] = wrapper.fill(paraText);
            
            if paraNum == 0:
                paraList[paraNum] = paraList[paraNum].lstrip();
        
        self.m_log.debug("paraList reformatted: %s", str(paraList));
        return "\n\n".join(paraList);
    
    def _formatSafeString(self, descText, indent):
        """Formats the safe description string.
        """
        indentStr   = " " * indent;
        skipLines   = 0;
        lineList    = descText.split("\n");
        lineListLen = len(lineList);
        self.m_log.debug("lineList: %s", str(lineList));
        
        for lineNum, lineText in enumerate(lineList):
            if lineText.strip() == "":
                skipLines = skipLines + 1;
                continue;
            
            lineText = lineText.replace("\\",  "\\\\");
            lineText = lineText.replace("\t",  "\\t");
            lineText = lineText.replace("\n",  "\\n");
            lineText = lineText.replace("\"",  "\\\"");
            
            if lineNum - skipLines == 0:
                lineText = "\"" + lineText + "\\n\"\n";
            else:
                lineText = indentStr + "\"" + lineText + "\\n\"\n";
            
            lineList[lineNum - skipLines] = lineText;
        
        lastLine = lineListLen - skipLines - 1;
        
        if lineList[lastLine].endswith("\n"):
            lineList[lastLine] = lineList[lastLine][:-1];
        
        self.m_log.debug("lineList reformatted: %s", str(lineList));
        return "".join(lineList[:(lineListLen - skipLines)]);
    
    def _formatXML(self, lines, indent):
        """Formats the .fcd XML contents.
        """
        numLines  = len(lines);
        indentStr = " " * indent;
        output    = [];
        
        for i, line in enumerate(lines):
            line = line.replace("\\",  "\\\\");
            line = line.replace("\t",  "\\t");
            line = line.replace("\n",  "");
            line = line.replace("\"",  "\\\"");
            
            if i == 0:
                output.append("\"" + line + "\\n\"");
            else:
                output.append(indentStr + "\"" + line + "\\n\"");
            
            if i < numLines - 1:
                output[i] = output[i] + "\n";
        
        return "".join(output);
    
    def _dumpValues(self, log):
        """Prints the contents of m_fcdDict and m_tmplDict to <log>
        """
        for key, value in self._getFCDDict().iteritems():
            log.info(key + " >" + str(value) + "<");
        
        for key, value in self._getTmplDict().iteritems():
            log.info("\t" + key + " >" + str(value) + "<");
    
