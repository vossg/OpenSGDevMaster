import sys
from osgbench import *

def usage():
    print "usage."
    return -1

def main(argv=sys.argv):
    if len(argv) != 2:
        return usage()

    filename = argv[1]

    print "Loading %s..." % filename
    scene = loadScene(filename)

    print "Traversing..."
    travscene = scene.clone()
    g = createGraphOpSeq("GeoType() Stripe(stitch=false)")
    g.traverseSeq(travscene)

    print "Running test..."
    win = TestWindow()
    win.open()

    test = Test()
    test.setWindow(win)
    test.setScene(travscene)
    test.setNFrames(200)

    test.clear()
    test.addFov(42)
    test.makeOrbit(0, 1, 0)

    test.run()
    print "trav FPS:", test.getFPS()   
    print "Snapshot"
    timage = test.snapshot(100)
    print "done"
    
    test.setScene(scene)
    test.run()
    print "Non-Trav FPS:", test.getFPS()    
    print "Snapshot"
    image = test.snapshot(100)
    print "done"
    
    dimage = image.clone()
    dimage.diff(timage)
    dimage.write("diffimage.png")
    image.write("image1.png")
    timage.write("image2.png")
    
    win.close()

if __name__ == '__main__':
    sys.exit(main() or 0)
