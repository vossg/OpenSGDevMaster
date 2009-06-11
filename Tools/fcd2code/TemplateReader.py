
import logging;

class TemplateReader:
    """Simple helper for loading a template file.
    """

    def __init__(self, fileName):
        """Creates a new TemplateReader for the given template file fileName.
        """
        self.m_log      = logging.getLogger("TemplateReader");
        self.m_fileName = fileName;
        self.m_lines    = [];
    
    def read(self):
        """Loads the template file specified in the constructor and returns a
           list of strings, each a line of the template file contents.
        """
        self.m_log.debug("read: Opening file \"%s\"." % self.m_fileName);
        fileObj = open(self.m_fileName, "rb");
        
        self.m_log.debug("read: reading template.");
        self.m_lines = fileObj.readlines();
        
        self.m_log.debug("read: closing file.");
        fileObj.close();
        
        return self.m_lines[:];
    
