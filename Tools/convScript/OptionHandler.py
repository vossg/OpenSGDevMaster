
import optparse;
import sys;
from OperationRegistry import OperationRegistry;
from Operations import OperationBase;
from Operations import GroupingOperation;

class OptionHandler:
    """ Support for command line options.
    """
    
    #### member
    #  options -- option object (returned by optparse.parse_args)
    #  args -- arguments list (returned by optparse.parse_args)
    
    options = None;
    args = None;
    
    @staticmethod
    def getOptionActive(optionName):
        """ Returns true if the given option is active
        """
        #print "getOptionActive: %s" % optionName;
        if optionName in OptionHandler.options.__dict__:
            optionVal = OptionHandler.options.__dict__[optionName];
            
            if (optionVal != None) and (optionVal != False):
                return True;
            
        return False;
        
    @staticmethod
    def getOptionArg(optionName):
        """ Returns the argument of an option
        """
        if optionName in OptionHandler.options.__dict__:
            return OptionHandler.options.__dict__[optionName];
        
        return None;
            
    @staticmethod
    def getOptionList():
        """ Low level access to the options dictionary.
        """
        return OptionHandler.options;
    
    @staticmethod
    def getArgList():
        """ Low level access to the arguments list.
        """
        return OptionHandler.args;
    
    @staticmethod
    def showOpsCallback(option, opt, value, parser, *args):
        """ Callback that prints the names of all registered operations.
        """
        ## begin local function for recursion
        def printOpList(opList, indent):
            opList.sort(key=lambda op : op.getName().lower());
            for op in opList:
                if isinstance(op, GroupingOperation):
                    opNameList = op.getOpNameList();
                    subOpList = [OperationRegistry.getRegisteredOp(subOp)
                         for subOp in opNameList];
                    print indent * " " + "\"" + op.getName() + "\" <group>:";
                    printOpList(subOpList, indent + 2);
                else:
                    print indent * " " + "\"" + op.getName() + "\"";
                
        print "Registered operations are:";
        ## end local function
        
        printOpList(OperationRegistry.getRegisteredOpList(), 2);
        sys.exit(0);
    
    @staticmethod
    def setup(args):
        """ Setup option parser and parse arguments
        """
        parser = optparse.OptionParser();
        
        # setup the option parser
        parser.add_option(
            "-d", "--diff",
            action="store",
            type="string",
            dest="diffFile",
            help="write a unified diff to DIFFFILE. [default: write no diff].",
            metavar="DIFFFILE");
        
        parser.add_option(
            "-f", "--followsymlink",
            action="store_true",
            dest="followSymlink",
            help="follow symbolic links to directories. [default: false].");
        
        parser.add_option(
            "-l", "--logfile",
            action="store",
            type="string",
            dest="logFile",
            help="write a log to LOGFILE. [default: write no log].",
            metavar="LOGFILE");
        
        parser.add_option(
            "-n", "--noop",
            action="store_true",
            dest="noOp",
            help="do not modify files on disk. [default: false].");
        
        parser.add_option(
            "-o", "--operations",
            action="append",
            type="string",
            dest="operations",
            help="only perform the listed operations \"OP1:OP2:...\". [default: all].",
            metavar="\"OP1:OP2:...\"");
        
        parser.add_option(
            "-p", "--pattern",
            action="store",
            type="string",
            dest="filePattern",
            help="only operate on files matching the REGEX. [default: operate on all files].",
            metavar="REGEX");
        
        parser.add_option(
            "-s", "--show-ops",
            action="callback",
            callback=OptionHandler.showOpsCallback,
            help="display a list of operation names for use with the -o option and exit.");
            
        parser.add_option(
            "-v", "--verbose",
            action="count",
            dest="verbose",
            help="print verbose log, can be used multiple times to increase verbosity.");
        
        parser.set_defaults(followsymlink=False);
        parser.set_defaults(noop=False);
        parser.set_defaults(verbose=0);
        
        (options, args) = parser.parse_args(args);
        
        OptionHandler.options = options;
        OptionHandler.args = args;