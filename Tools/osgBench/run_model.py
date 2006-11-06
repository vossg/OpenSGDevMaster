# Simple OpenSG Benchmark
from osgbench import *
from sys import argv, exit
import getopt
from string import atof, atoi

# options

ups="0,0,1"
frames=100

# command line handling
try:                                
    opts, args = getopt.getopt(argv[1:], "u:f:h", ["up=", "frames=", "help"]) 
except getopt.GetoptError:           
    exit(2)

for opt, arg in opts:                
    if opt in ("-h", "--help"):      
        sys.exit()                  
    elif opt == '-u':                
        ups=arg
        print "Up set to ", ups
    elif opt == '-f':                
        frames=atoi(arg)
        print "Frames set to ", frames


# Load the scene
print "Loading " + args[0] + "..."
scene=loadScene(args[0])

# Define the Window's parameters
win=TestWindow()
win.setSize(900, 900)
win.open()

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setScene(scene)
test.setNFrames(frames)

test.clear()
test.addFov(60)
up=ups.split(',')
test.makeOrbit(atof(up[0]),atof(up[1]),atof(up[2]))
#test.setIgnoreGeometry(True)
test.useRenderTraversal(True)

test.run()
print "Path took %f seconds: %f fps" % (test.getTime(), test.getFPS())

win.close()

