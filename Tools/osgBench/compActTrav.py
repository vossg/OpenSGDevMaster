# Simple OpenSG Benchmark
from osgbench import *
from sys import argv

# Load the scene
print "Loading " + argv[1] + "..."
scene=loadScene(argv[1])

# Define the Window's parameters
win=TestWindow()
win.setSize(900, 900)
win.open()

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setScene(scene)
test.setNFrames(100)

test.clear()
test.addFov(60)
test.makeOrbit(0,0,1)

test.run()
print "RenderAction    took %f seconds: %f fps" % (test.getTime(), test.getFPS())

test.useRenderTraversal(True)
test.run()
print "RenderTraversal took %f seconds: %f fps" % (test.getTime(), test.getFPS())

win.close()

