
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
    
    def _formatString(self, text, indent):
        """Formats the description string.
        """
        wrapper = textwrap.TextWrapper();
        wrapper.initial_indent    = "";
        wrapper.subsequent_indent = " " * indent;
        wrapper.break_long_words  = False;
        wrapper.width             = 79 - indent;
        
        return wrapper.fill(text);
    
    def _formatSafeString(self, text, indent):
        """Formats the safe description string.
        """
        wrapper = textwrap.TextWrapper();
        wrapper.break_long_words  = False;
        wrapper.width             = 79 - 3 - indent;
        
        text = text.replace("\\", "\\\\");
        text = text.replace("\t", "\\t");
        text = text.replace(" \n", " ");
        text = text.replace("\n", " ");
        text = text.replace("\"", "\\\"");
        
        lines     = wrapper.wrap(text);
        indentStr = " " * indent;
        numLines  = len(lines);
        text      = "";
        
        for i, line in enumerate(lines):
            if i == 0:
                lines[i] = "\"" + line + "\\n\"";
            else:
                lines[i] = indentStr + "\"" + line + "\\n\"";
            
            if i < numLines - 1:
                lines[i] = lines[i] + "\n";
        
        return "".join(lines);
    
    def _formatXML(self, lines, indent):
        """Formats the .fcd XML contents.
        """
        numLines  = len(lines);
        indentStr = " " * indent;
        output    = [];
        
        for i, line in enumerate(lines):
            line = line.replace("\\", "\\\\");
            line = line.replace("\t", "\\t");
            line = line.replace("\n", "");
            line = line.replace("\"", "\\\"");
            
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
    
