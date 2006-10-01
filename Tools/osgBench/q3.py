from osgbench import *
t=TestWindow()
t.setSize(300,300)
t.open()

test=Test()
test.setWindow(t)
test.setHeadlight(1)
test.setNFrames(100)

nc=1

images = []

for res in (1,2,4,8,16):
    scene=Group()
    for i in range(-nc,nc):
        for j in range(-nc,nc):
            geo=makeBox(.8,.8,.8,res,res,res)
            geo.setDlistCache(0)
            geo.translate(i*2, j*2, 0)
            scene.addChild(geo)
    addRef(scene)

    test=Test()
    test.setWindow(t)
    test.setScene(scene)
    test.setHeadlight(1)
    test.setNFrames(100)

    test.clear()
    test.addFov(90)
    test.makeOrbit(0,1,0)

    print "%d res" % res
    test.run()
    
    images = images + [test.snapshot(25+res)]

diff = images[0].clone()
diff.diff(images[3])
diff.write("difftest.png")
images[0].write("difftest2.png")
