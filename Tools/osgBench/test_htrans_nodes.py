# Simple OpenSG benchmark
from osgbench import *

# Define the Window's parameters
win=TestWindow()
win.setSize(300,300)
win.open()

# Create the scene
scene=Group()

nc=6

for i in range(-nc,nc):
    inode=Group()
    scene.addChild(inode)
    for j in range(-nc,nc):
        jnode=Group()
        inode.addChild(jnode)
        for k in range(-nc,nc):
            trans=Transform()
            jnode.addChild(trans)            
            trans.setTranslation(i*2, j*2, k*2)
            geo=makeBox(1,1,1, 1,1,1)
            trans.addChild(geo)

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setNFrames(100)
test.setScene(scene)

test.addFov(90)
test.makeOrbit(0,1,0)

test.run()

print "%d transformed cubes took %.2f seconds: %.2f fps" % ((nc*2)*(nc*2)*(nc*2), test.getTime(), test.getFPS())
