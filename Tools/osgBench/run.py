import sys
from osgbench import *

def usage():
    print "usage."
    return -1

def main(argv=sys.argv):
    if len(argv) != 2:
        return usage()

    filename = argv[1]

    print "Loading %s..." % filename,
    scene = loadScene(filename)
    print "done"

    g = createGraphOp("GeoType")
    g.traverse(scene)

    win = TestWindow()
    win.open()

    test = Test()
    test.setWindow(win)
    test.setScene(scene)
    test.setNFrames(1000)

    test.clear()
    test.addFov(42)
    test.makeOrbit(0, 1, 0)

    test.run()

    print "FPS:", test.getFPS()
    win.close()

if __name__ == '__main__':
    sys.exit(main() or 0)
