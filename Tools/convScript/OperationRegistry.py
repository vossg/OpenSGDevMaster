class OperationRegistry:
    """ Registry of available operations.
    """
    
    #### member
    #  regOpMap  -- map opName to opInstance
    
    # list of registered operations
    regOpMap = {};
     
    # adds an operation to the system
    @staticmethod
    def registerOp(opInstance):
        #print "OperationRegistry.registerOp(%s)" % opInstance.getName();
        
        opName = opInstance.getName();
        if not OperationRegistry.regOpMap.has_key(opName):
            OperationRegistry.regOpMap[opName] = opInstance;
    
    # removes an operation from the system
    @staticmethod
    def unregisterOp(opInstance):
        #print "OperationRegistry.unregisterOp(%s)" % opInstance.getName();
        
        opName = opInstance.getName();
        if OperationRegistry.regOpMap.has_key(opName):
            OperationRegistry.regOpMap.pop(opName);
    
    # get operation instance with given name
    @staticmethod
    def getRegisteredOp(opName):
        #print "OperationRegistry.getRegisteredOp(%s)" % opName;
        
        if OperationRegistry.regOpMap.has_key(opName):
            return OperationRegistry.regOpMap[opName];
        
        return None;
    
    # get list of registered operations
    @staticmethod
    def getRegisteredOpList():
        return OperationRegistry.regOpMap.values();

def registerOperation(opInstance, group = None):
    """ Helper for operation registration, if group is not None, the operation
        opInstance is also added to the given group.
    """
    OperationRegistry.registerOp(opInstance);
    if group != None:
        group.addOp(opInstance.getName());