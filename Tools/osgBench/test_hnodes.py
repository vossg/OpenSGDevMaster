# Simple OpenSG benchmark
from osgbench import *

# Define the Window's parameters
win=TestWindow()
win.setSize(300,300)
win.open()

# Create the scene
scene=Group()

nc=8

scene=Group()

for i in range(-nc,nc):
    inode=Group()
    scene.addChild(inode)
    for j in range(-nc,nc):
        jnode=Group()
        inode.addChild(jnode)
        for k in range(-nc,nc):
            geo=makeBox(1,1,1, 1,1,1)
            geo.translate(i*2, j*2, k*2)
            jnode.addChild(geo)

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setNFrames(100)
test.setMinTime(5)
test.setScene(scene)
test.setStatistics(1)

test.addFov(90)
test.makeOrbit(0,1,0)

test.run()

print "%d transformed cubes took %f seconds: %f fps" % ((nc*2)*(nc*2)*(nc*2), test.getTime(), test.getFPS())

culled=0
culltested=0

for i in range(0,test.getNRenderedFrames()):
    culled += test.getStatValue("culledNodes", i)
    culltested += test.getStatValue("cullTestedNodes", i)

print "%d nodes culled, %d nodes culltested" % (culled, culltested)

    
    
