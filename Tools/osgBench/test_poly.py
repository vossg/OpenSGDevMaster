from osgbench import *
t=TestWindow()
t.setSize(300,300)
t.open()


nc=1
scene=Group()
for i in range(-nc,nc):
    for j in range(-nc,nc):
        geo=makePlane(.8,.8,128,128)
        geo.setDlistCache(1)       
        geo.translate(i*2, j*2, 0)
        scene.addChild(geo)

test=Test()
test.setWindow(t)
test.setScene(scene)
test.setHeadlight(1)
test.setNFrames(100)

test.clear()
test.addFov(90)
test.makeOrbit(0,1,0)

test.run()
fps=test.getFPS()

for i in scene.geometries():
    i.setDlistCache(0)

test.run()
ncfps=test.getFPS()

# Statistics collection frame
test.setStatistics(2)
test.setNFrames(2)
test.run()

print "   cached: %d tri/frame at %.2f FPS: %.0f tri/sec" % \
    ( test.getStatValue("NTriangles", 0), fps,  \
      test.getStatValue("NTriangles", 0) * fps )

print "noncached: %d tri/frame at %.2f FPS: %.0f tri/sec" % \
    ( test.getStatValue("NTriangles", 0), ncfps,  \
      test.getStatValue("NTriangles", 0) * ncfps )
