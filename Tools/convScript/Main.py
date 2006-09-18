#! /usr/bin/python

import sys;
import ConversionDriver;
import OptionHandler;
import StandardOperation;

### BEGIN main ###

args = sys.argv;
if len(args) <= 1:
    args.append("-h");

# must come before creation of the driver instance. 
OptionHandler.OptionHandler.setup(args);

driver = ConversionDriver.ConversionDriver();
driver.run();

### END main   ###