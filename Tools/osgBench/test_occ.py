# Simple OpenSG Benchmark
from osgbench import *
from sys import argv, exit, stdout
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
        print "Usage: test_occ up=0,1,0 frames=100 <model file>"     
        sys.exit()                  
    elif opt == '-u':                
        ups=arg
        print "Up set to ", ups
    elif opt == '-f':                
        frames=atoi(arg)
        print "Frames set to ", frames


# Load the scene
scene=Group()

for i in args:
    print "Loading %s..." % i,
    stdout.flush()
    scene.addChild(loadScene(i))
    print "done"


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

test.setStatistics(1)

test.run()
print "Path took %f seconds: %f fps" % (test.getTime(), test.getFPS())

culled = 0
culltested = 0

for i in range(0,test.getNRenderedFrames()):
    culltested += test.getStatValue("OC-Tests", i)
    culled += test.getStatValue("OC-Invisible", i)

print "%d nodes oc-tested, %d nodes invisible.\n" % (culltested, culled)

win.close()

