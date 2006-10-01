# Simple OpenSG Benchmark
from osgbench import *

# Load the scene
print "Loading Beetle..."
scene=loadScene("/igd/a4/opensg/siggraph/mybeetle/BeetleAlles_opt.fhs")

# Define the Window's parameters
win=TestWindow()
win.open()
win.setFullscreen()

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setScene(scene)
test.setNFrames(500)

test.clear()
test.addFov(42)
test.addFromOri("-2191.82 -1100.77 1722.85, -1300.51 -2792.8 890.801, 1039.72 -3752.02 589.886, 1126.16 -1396.48 520.712, 2013.53 -1023.08 936.491, 3950.44 -1110.91 1398.72, 4236.92 18.9668 1118.02, 1985.81 3001.34 806.649, -1082.25 2142.65 747.017, -2800.93 -75.5585 505.049", \
                "0.619884 -0.479794 -0.62092 1.65974, 0.865916 -0.248026 -0.434364 1.6686, 0.999546 -0.00861513 -0.0288809 1.54227, 0.999546 -0.00861513 -0.0288809 1.54227, 0.84729 0.273698 0.45518 1.41943, 0.653772 0.49471 0.572577 1.6211, 0.531041 0.534708 0.65733 1.98363, 0.0649892 0.671099 0.738513 2.89454, -0.289388 0.641949 0.710039 3.70718, 0.578083 -0.583372 -0.570524 2.06364")

test.run()
print "Beetle path took %f seconds: %f fps" % (test.getTime(), test.getFPS())

win.close()

