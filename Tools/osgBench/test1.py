# Simple OpenSG benchmark
from osgbench import *

# Define the Window's parameters
win=TestWindow()
win.setSize(300,300)
win.open()

# Create the scene
scene=Group()

nc=12

for i in range(-nc,nc):
    for j in range(-nc,nc):
        for k in range(-nc,nc):
            trans=Transform()
            scene.addChild(trans)            
            trans.setTranslation(i*2, j*2, k*2)
            geo=makeBox(1,1,1, 1,1,1)
            trans.addChild(geo)

scene.addChild(makeBox(1,1,1, 1,1,1))

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setNFrames(100)
test.setScene(scene)

test.addFov(90)
test.makeOrbit(0,1,0)

test.run()

print "%d transformed cubes took %f seconds: %f fps" % ((nc*2)*(nc*2)*(nc*2), test.getTime(), test.getFPS())

# Second test scene

scene=Group()

for i in range(-nc,nc):
    for j in range(-nc,nc):
        for k in range(-nc,nc):
            geo=makeBox(1,1,1, 1,1,1)
            geo.translate(i*2, j*2, k*2)
            scene.addChild(geo)

scene.addChild(makeBox(1,1,1, 1,1,1))

test.setScene(scene)
test.run()

print "%d cubes took %f seconds: %f fps" % ((nc*2)*(nc*2)*(nc*2), test.getTime(), test.getFPS())

# Third test scene

scene=makeBox(1,1,1, 1,1,1)

for i in range(-nc,nc):
    for j in range(-nc,nc):
        for k in range(-nc,nc):
            geo=makeBox(1,1,1, 1,1,1)
            geo.translate(i*2, j*2, k*2)
            scene.merge(geo)

test.setScene(scene)
test.run()

print "%d merged cubes took %f seconds: %f fps" % ((nc*2)*(nc*2)*(nc*2), test.getTime(), test.getFPS())
