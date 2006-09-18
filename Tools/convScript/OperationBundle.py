
from OperationRegistry import OperationRegistry

class OperationBundle:
    """ Bundles a bunch of operations to be applied together.
    """
    
    #### member
    #  opList -- list of operations
    
    def __init__(self):
        self.opList = [];
    
    # add an operation
    def addOp(self, opName):
        op = OperationRegistry.getRegisteredOp(opName);
        
        if op == None:
            print "ERROR: addOp called with unknown op \"%s\"" % opName;
        
        op.addSelf(self);
    
    # remove an operation
    def subOp(self, opName):
        op = OperationRegistry.getRegisteredOp(opName);
        
        if op == None:
            print "ERROR: subOp called with unknown op \"%s\"" % opName;
        
        op.subSelf(self);
        
    def applyBundle(self, driver):
        for op in self.opList:
            op.applyOp(driver);
        
    ###############################
    # Internal
    
    # add op to the list of enabled ones (unless it already is in it)
    def internal_addOp(self, op):
        if op not in self.opList:
            self.opList.append(op);
    
    # remove op from the list of enables ones
    def internal_subOp(self, op):
        if op in self.opList:
            self.opList.remove(op);
