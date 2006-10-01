# Simple OpenSG benchmark
from osgbench import *

# Define the Window's parameters
win=TestWindow()
win.setSize(300,300)
win.open()

# Create the scene
scene=Group()

nc=4

scene=Group()

for i in range(-nc,nc):
    for j in range(-nc,nc):
        for k in range(-nc,nc):
            geo=makeBox(1,1,1, 1,1,1)
            geo.translate(i*2, j*2, k*2)
            scene.addChild(geo)

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setNFrames(100)
test.setScene(scene)

test.addFov(90)
test.makeOrbit(0,1,0)

test.run()
fps=test.getFPS()
time=test.getTime()

# Statistics collection frame
test.setStatistics(2)
test.setNFrames(2)
test.run()

print "%d transformed cubes took %f seconds: %f fps" % \
    (test.getStatValue("NGeometries", 0) , time, fps)
