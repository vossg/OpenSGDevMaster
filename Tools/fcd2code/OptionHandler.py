
import optparse;

class OptionHandler:
    """ Support for command line options.
    """
    
    #### class member
    #  m_options -- option object (returned by optparse.parse_args)
    #  m_args    -- arguments list (returned by optparse.parse_args)
    #  m_parser  -- option parser
    
    m_options = None;
    m_args = None;
    m_parser = None;
    
    def getOptionActive(optionName):
        """ Returns true if the given option is active
        """
        if optionName in OptionHandler.m_options.__dict__:
            optionVal = OptionHandler.m_options.__dict__[optionName];
            
            if (optionVal != None) and (optionVal != False):
                return True;
            
        return False;
        
    getOptionActive = staticmethod(getOptionActive);
    
    def getOptionArg(optionName):
        """ Returns the argument of an option
        """
        if optionName in OptionHandler.m_options.__dict__:
            return OptionHandler.m_options.__dict__[optionName];
        
        return None;
    
    getOptionArg = staticmethod(getOptionArg);
            
    def getOptionList():
        """ Low level access to the options dictionary.
        """
        return OptionHandler.m_options;
    
    getOptionList = staticmethod(getOptionList);
    
    def getArgList():
        """ Low level access to the arguments list.
        """
        return OptionHandler.m_args;
    
    getArgList = staticmethod(getArgList);
    
    def setup():
        """ Setup option parser
        """
        if OptionHandler.m_parser != None:
            print "WARNING: OptionHandler.setup: Called twice.";
            return;
        
        OptionHandler.m_parser = optparse.OptionParser();
        
        OptionHandler.m_parser.add_option(
            "-d", "--fcd-file",
            action="store",
            type="string",
            dest="fcdFile",
            help="FieldContainer description file.",
            metavar="file.fcd");
        
        OptionHandler.m_parser.add_option(
            "-b", "--write-base",
            action="store_true",
            dest="writeBase",
            help="write the FieldContainerBase files. [default: false].");
        
        OptionHandler.m_parser.add_option(
            "-f", "--write-fc",
            action="store_true",
            dest="writeFC",
            help="write the FieldContainer files. [default: false].");
        
        OptionHandler.m_parser.add_option(
            "-p", "--out-path",
            action="store",
            type="string",
            dest="outPath",
            help="destination path for files.",
            metavar="PATH");
        
        OptionHandler.m_parser.add_option(
            "-r", "--root-path",
            action="store",
            type="string",
            dest="rootPath",
            help="root of the OpenSG source tree.",
            metavar="PATH");

        OptionHandler.m_parser.add_option(
            "-t", "--template-path",
            action="store",
            type="string",
            dest="templatePath",
            help="path to where the fcd2code templates are stored.",
            metavar="PATH");
        
        OptionHandler.m_parser.add_option(
            "-v", "--verbose",
            action="store_true",
            dest="verbose",
            help="print diagnostic messages. [default: false].");
        
        OptionHandler.m_parser.add_option(
            "-c", "--compat-mode",
            action="store_true",
            dest="compatMode",
            help="enable 1.x compatibility mode. [default: false].");

        OptionHandler.m_parser.add_option(
            "-B", "--bundle",
            action="store_true",
            dest="bundleMode",
            help="create field bundle. [default: false].");

        OptionHandler.m_parser.set_defaults(writeBase=False);
        OptionHandler.m_parser.set_defaults(writeFC=False);
        OptionHandler.m_parser.set_defaults(verbose=False);
    
    setup = staticmethod(setup);
    
    def parse(args):
        """ Parse command line arguments.
        """
        if OptionHandler.m_parser == None:
            print "WARNING: OptionHandler.parse: no parser, run setup first.";
            return;
        
        (options, args) = OptionHandler.m_parser.parse_args(args);
        
        OptionHandler.m_options = options;
        OptionHandler.m_args    = args;
    
    parse = staticmethod(parse);
