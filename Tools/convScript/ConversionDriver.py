
import difflib;
import logging;
import os;
import os.path;
import re;
import time;

from OptionHandler import OptionHandler;
from OperationBundle import OperationBundle;

class ConversionDriver:
    """ Driver for the operations
    """
    
    #### member
    #  fileRegEx  -- reg ex object for the file pattern
    #  diffFile  -- file object for the diff file
    #  opBundle  -- bundle of operations to apply
    #  currFileName -- current file name
    #  currFilePath -- current file path
    #  currFileContent -- current file contents
    #  currFileOrigContent -- current file original contents
    #  logName -- name of logger used
    
    def __init__(self):
        self.fileRegEx = None;
        self.diffFile = None;
        self.opBundle = OperationBundle();
        
        self.currFileName = None;
        self.currFilePath = None;
        self.currFileContent = None;
        self.currFileOrigContent = None;
        
        self.logName = "ConversionDriver";
        
        consoleLogLevel = logging.ERROR;
        
        # setup console log
        if OptionHandler.getOptionActive("verbose"):
            if OptionHandler.getOptionArg("verbose") == 1:
                consoleLogLevel = logging.WARNING;
            elif OptionHandler.getOptionArg("verbose") == 2:
                consoleLogLevel = logging.INFO;
            elif OptionHandler.getOptionArg("verbose") >= 3:
                consoleLogLevel = logging.DEBUG;
                
        logging.basicConfig(level = consoleLogLevel);
        
        # setup log file
        if OptionHandler.getOptionActive("logFile"):
            fileLogName = OptionHandler.getOptionArg("logFile");
            fileLogHandler = logging.FileHandler(fileLogName, "w");
            fileLogFormatter = logging.Formatter(
                "%(asctime)s %(name)-12s %(levelname)-8s %(message)s");
            
            fileLogHandler.setLevel(logging.DEBUG);
            fileLogHandler.setFormatter(fileLogFormatter);
            
            logging.getLogger("").addHandler(fileLogHandler);
    
    def getDiffFile(self):
        """ Return the file object for the diff file.
        """
        return self.diffFile;
    
    def getCurrFilePath(self):
        """ Return the path to the current file.
        """
        return self.currFilePath;
    
    def getCurrFileName(self):
        """ Return the name of the current file.
        """
        return self.currFileName;
    
    def getCurrFileContent(self):
        """ Return a string containing the contents of the current file,
            including modificatins be alreay applied operations.
        """
        return self.currFileContent;
    
    def setCurrFileContent(self, fileContent):
        """ Set the current files contents to the string fileContent.
        """
        self.currFileContent = fileContent;
    
    def getCurrFileOrigContent(self):
        """ Return a string containing the original contetns of the current file.
        """
        return self.currFileOrigContent;
    
    # call operations for files/directories given on commandline
    def processFiles(self):
        log = logging.getLogger(self.logName);
        log.debug(">> process");
        
        for path in OptionHandler.getArgList()[1:]:
            log.info("path: \"%s\"." % path);
            if not OptionHandler.getOptionActive("followSymlink") and os.path.islink(path):
                log.info("skipping path - is symlink and followSymlink is off.");
                continue;
            
            if os.path.isdir(path):
                for root, dirs, files in os.walk(path):
                    if not OptionHandler.getOptionActive("followSymlink"):
                        filter(lambda d: not os.path.islink(d), dirs);
                        filter(lambda f: not os.path.islink(f), files);
                    
                    for file in files:
                        self.processFile(root, file);
                    
            elif os.path.isfile(path):
                self.processFile("./", path);
        log.debug("<< process");
    
    def testFileRegEx(self, filePath, fileName):
        if self.fileRegEx != None:
            return self.fileRegEx.match(fileName);
    
        return True;
    
    def testFileAccess(self, filePath, fileName):
        fullFilePath = os.path.join(filePath, fileName);
        return os.access(fullFilePath, os.F_OK) and os.access(fullFilePath, os.R_OK | os.W_OK);
    
    # call operations for single file
    def processFile(self, filePath, fileName):
        log = logging.getLogger(self.logName);
        log.debug(">> processFile");
        
        self.currFilePath = filePath;
        self.currFileName = fileName;
        fullFilePath = os.path.join(filePath, fileName);
        
        log.info("  File: \"%s\"." % fullFilePath);
        
        fileLastMTime = time.ctime(os.stat(fullFilePath).st_mtime);
        fileNewMTime = time.ctime();
        
        if not self.testFileRegEx(filePath, fileName):
            log.info("File ignored - pattern does not match.")
            log.debug("<< processing file.");
            return;
         
        if not self.testFileAccess(filePath, fileName):
            log.warning("File ignored - insufficient file permissions.");
            log.debug("<< processing file.");
            return;
        
        log.info("reading file \"%s\"." % fullFilePath);
        currFile = open(fullFilePath, "r");
        self.currFileContent = currFile.read();
        self.currFileOrigContent = self.currFileContent[:];
        currFile.close();
        
        log.debug("applying bundle");
        self.opBundle.applyBundle(self);
        
        udiff = difflib.unified_diff(self.currFileOrigContent.split("\n"),
                                     self.currFileContent.split("\n"),
                                     fullFilePath, fullFilePath,
                                     fileLastMTime, fileNewMTime, lineterm="");
                                     
        if OptionHandler.getOptionActive("diffFile"):
            for line in udiff:
                log.info(line);
                self.diffFile.write(line);
                self.diffFile.write("\n");
        else:
            for line in udiff:
                log.info(line);
                
        if OptionHandler.getOptionActive("noOp"):
            log.info("Changes NOT written.");
            log.debug("<< processing file.");
            return;
        
        log.info("writing modified file \"%s\"." % fullFilePath);
        currFile = open(fullFilePath, "w");
        currFile.write(self.currFileContent);
        currFile.flush();
        currFile.close();
        log.debug("<< processing file.");
            
    def preProcess(self):
        log = logging.getLogger(self.logName);
        log.debug(">> preprocess");
        if OptionHandler.getOptionActive("filePattern"):
            log.debug("Creating filePattern reg ex.");
            self.fileRegEx = re.compile(OptionHandler.getOptionArg("filePattern"));
            
        if OptionHandler.getOptionActive("diffFile"):
            diffFileName = OptionHandler.getOptionArg("diffFile");
            log.debug("Opening diff file \"%s\"." % diffFileName);
            self.diffFile = open(diffFileName, "w+");
        
        if OptionHandler.getOptionActive("operations"):
            log.debug("Populating operation bundle.");
            
            # must split -o "Op1:Op2:Op3" at the ":" and -o may have appeared
            # more than once on the command line
            opNameArgList = OptionHandler.getOptionArg("operations");
            for opNameArg in opNameArgList:
                opNameList = opNameArg.split(":");
                
                for opName in opNameList:
                    log.debug("adding operation \"%s\"." % opName);
                    self.opBundle.addOp(opName);
        log.debug("<< preprocess");
    
    def postProcess(self):
        log = logging.getLogger(self.logName);
        log.debug(">> postprocess");
        if OptionHandler.getOptionActive("diffFile"):
            log.debug("Closing diff file \"%s\"." % self.diffFile.name);
            self.diffFile.flush();
            self.diffFile.close();
        log.debug("<< postprocess");
    
    def run(self):
        self.preProcess();
        self.processFiles();
        self.postProcess();