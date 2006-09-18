
import logging;

class OperationBase:
    """ Base class of the operations.
    """
    
    #### member
    #  opName -- name of the operation
    
    def __init__(self, opName):
        self.opName = opName;
    
    def getName(self):
        return self.opName;
    
    def applyOp(self, driver):
        """ Perform operation - intended for override in subclasses.
        """
        logging.getLogger("OperationBase").error(
            "OperationBase.applyOp called");
    
    def addSelf(self, opBundle):
        """ Helper callback for adding to a bundle.
        """
        opBundle.internal_addOp(self);
    
    def subSelf(self, opBundle):
        """ Helper callback for removing from a bundle.
        """
        opBundle.internal_subOp(self);

#
# ===========================================================================
#

class GroupingOperation(OperationBase):
    """ Group of operations.
        
        If a group is added to a bundle all the operations in that group
        will be added and likewise for removal.
        Watch out when using multiple groups that contain the same operation,
        there will only be one instance of the operation in the bundle and it
        is removed when the first group that contains it is removed.
    """
    
    #### member
    #  opNameList -- list of operation names
    
    def __init__(self, opName):
        OperationBase.__init__(self, opName);
        self.opNameList = [];
    
    def applyOp(self, driver):
        """ Do nothing -- all operations in this group were added individually.
        """
        logging.getLogger("GroupingOperation").error(
            "GroupingOperation.applyOp called.");
    
    def addOp(self, opName):
        """ Add an operation to this group
        """
        if opName not in self.opNameList:
            self.opNameList.append(opName);
    
    def subOp(self, opName):
        """ Remove an operation from this group
        """
        if opName in self.opNameList:
            self.opNameList.remove(opName);
    
    # returns list of grouped operations
    def getOpNameList(self):
        """ Get a list of operations in this group - names only
        """
        return self.opNameList;
    
    # add all ops in this group in opBundle
    def addSelf(self, opBundle):
        """ Helper callback for adding to a bundle - adds all op in this group.
        """
        for opName in self.opNameList:
            opBundle.addOp(opName);
    
    # remove all ops in this group from opBundle
    def subSelf(self, opBundle):
        """ Helper callback for removing from a bundle - removes all op 
            in this group.
        """
        for opName in self.opNameList:
            opBundle.subOp(opName);
        

#
# ===========================================================================
#

class SimpleReplaceOperation(OperationBase):
    """ Perform a simple replace of one string with another.
    """
    
    #### member
    #  replaceString -- string to replace
    #  replacementString -- string to replace with
    
    def __init__(self, opName, replace, replacement):
        OperationBase.__init__(self, opName);
        self.replaceString = replace;
        self.replacementString = replacement;
    
    def applyOp(self, driver):
        """ perform the replacement on the file currently loaded by the driver.
        """
        log = logging.getLogger("SimpleReplaceOperation");
        log.debug(">> apply");
        log.info("Replace \"%s\"  with  \"%s\"." % (self.replaceString, self.replacementString));
        fileContent = driver.getCurrFileContent();
        fileContent = fileContent.replace(self.replaceString, self.replacementString);
        driver.setCurrFileContent(fileContent);
        log.debug("<< apply");
        
    def getReplace(self):
        return self.replaceString;
        
    def getReplacement(self):
        return replacementString;
    