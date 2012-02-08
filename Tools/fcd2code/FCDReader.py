
import xml.sax.handler;
import logging;

from ListStack import ListStack;
from FieldContainer import FieldContainer;
from Field import Field;

class FCDContentHandler(xml.sax.handler.ContentHandler):
    """A SAX-parser content handler class for .fcd files
    """
    
    def __init__(self, reader):
        self.m_log        = logging.getLogger("FCDContentHandler");
        self.m_reader     = reader;
        self.m_container  = None;
        self.m_elemStack  = ListStack();
        self.m_parseField = False;

    def startDocument(self):
        self.m_log.debug("startDocument");
        self.m_elemStack.clear();
    
    def endDocument(self):
        self.m_log.debug("endDocument");
        self.m_container.finalize();
        self.m_reader.setFieldContainer(self.m_container);
    
    def startElement(self, name, attr):
        self.m_log.debug("startElement: %s", name);
        if name == "FieldContainer":
            container = FieldContainer();
            self.m_container = container;
            self.m_elemStack.push(container);
        elif name == "Field":
            field = Field();
            self.m_elemStack.top().addField(field);
            self.m_elemStack.push(field);
            self.m_parseField = True;
        else:
            self.m_log.error("startElement: unknown element: %s", name);
            return;
        
        for i, attrName in enumerate(attr.getNames()):
            self.m_log.debug("%s attr: %d - %s - %s", name, i, attrName, attr[attrName]);
            self.m_elemStack.top().setFCD(attrName, attr[attrName]);
        
    def endElement(self, name):
        self.m_log.debug("endElement: %s", name);
        
        if(self.m_parseField == True):

          if(self.m_elemStack.top().getFCD("osg2Ignore") == "true"):
            field = self.m_elemStack.top()
            self.m_elemStack.pop();
            self.m_elemStack.top().subField(field)
          else:
            self.m_elemStack.pop();

          self.m_parseField = False;
        else:
          self.m_elemStack.pop();
    
    def characters(self, content):
        self.m_log.debug("characters: |%s|", content);
        
        currDesc = self.m_elemStack.top().getFCD("description");
        if currDesc == None:
            self.m_elemStack.top().setFCD("description", content.lstrip(" \t"));
        else:
            currDesc += content.lstrip(" \t");
            self.m_elemStack.top().setFCD("description", currDesc);
        

class FCDReader:
    """Reader for .fcd files - calls a SAX parser with the FCDContentHandler
    """
    
    def read(self, fileName):
        
        self.m_container = None;
        
        self.m_fcdCH = FCDContentHandler(self);
        self.m_parser = xml.sax.make_parser();
        self.m_parser.setContentHandler(self.m_fcdCH);
        
        self.m_parser.parse(fileName);
        
        fcdFile     = open(fileName, "r");
        fcdContents = fcdFile.readlines();
        fcdFile.close();
        
        self.m_container.setFCDContents(fcdContents);
    
    def setFieldContainer(self, fc):
        self.m_container = fc;
    
    def getFieldContainer(self):
        return self.m_container;
    
