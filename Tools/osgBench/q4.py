# Start as
# valgrind --tool=callgrind --instr-atstart=no python q4.py ~/DeereModels/models4dirk/planterHeavy/planter_lod.osb


import sys
import os
import time
from osgbench import *

def usage():
    print "usage."
    return -1

def main(argv=sys.argv):
    if len(argv) < 2:
        return usage()
   
    scene=Group()

    for i in argv[1:]:
        print "Loading %s..." % i,
        sys.stdout.flush()
        scene.addChild(loadScene(i))
        print "done"

    #g = createGraphOp("GeoType")
    #g.traverse(scene)

    win = TestWindow()
    win.setSize(1000,1000)
    win.open()

    test = Test()
    test.setWindow(win)
    test.setScene(scene)
    test.setNFrames(200)

    test.clear()
    test.addFov(60)
    test.makeOrbit(0, 0, 1)
    #test.setIgnoreGeometry(True)
    test.useRenderTraversal(True)

    print "Turning on profiling..."
    os.spawnlp(os.P_NOWAIT,"callgrind_control","callgrind_control","-i","on")
    time.sleep(4)
    
    print "Running test..."
    test.run()

    print "Turning off profiling..."
    os.spawnlp(os.P_NOWAIT,"callgrind_control","callgrind_control","-i","off")
    time.sleep(4)

    print "FPS:", test.getFPS()
    win.close()

if __name__ == '__main__':
    sys.exit(main() or 0)
