
import logging;
from sys import platform as _platform

openMode = "w"

if _platform == "linux" or _platform == "linux2":
   # linux
   openMode = "w"  
elif _platform == "darwin":
   # MAC OS X
   openMode = "w"  
elif _platform == "win32":
   # Windows
   openMode = "wb"  

class TemplateWriter:
    """Simple helper for writing a filled template.
    """
    
    def __init__(self, fileName, filledTemplate):
        """Creates a new TemplateWriter to write filledTemplate to fileName.
        """
        self.m_log            = logging.getLogger("TemplateWriter");
        self.m_fileName       = fileName;
        self.m_filledTemplate = filledTemplate;
    
    def write(self):
        """Writes the filled template to the file (both specified in the
           constructor.
        """
        self.m_log.debug("write: Opening file \"%s\"." % self.m_fileName);
        fileObj = open(self.m_fileName, openMode);
        
        self.m_log.debug("write: writing template.");
        fileObj.writelines(map(lambda (x): x.encode("UTF-8"), self.m_filledTemplate));
        
        self.m_log.debug("write: closing file.");
        fileObj.close();
    
