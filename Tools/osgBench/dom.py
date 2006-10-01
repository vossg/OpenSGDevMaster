# Simple OpenSG Benchmark
import sys
from osgbench import *

# Load the scene
print "Loading Siena (high)...",
sys.stdout.flush()
scene=loadScene("/home/reiners/models/dvs_it.osb.gz")
addRef(scene)
print "done"

# Define the Window's parameters
win=TestWindow()
win.setSize(900, 900)
win.open()

# Define the Test(s)
test=Test()
test.setWindow(win)
test.setScene(scene)
test.setNFrames(500)

test.clear()
test.addFov(42)
test.addFromOri("741.578 519.589 1142.12, 2908.69 487.111 1138.9, 3714.28 275.308 1210.75, 5298.96 627.737 1203.53, 5664.89 388.819 1199.76, 6950.98 578.585 1213.98, 7812.37 367.858 1573.92, 6493.8 273.369 449.805, 5059.9 192.505 307.866, 2406.6 405.903 278.08, 1408.12 299.447 394.344, 1718.56 189.378 1191.73", \
                "-0.00257027 -0.999978 -0.00607656 1.62204, -0.00366052 -0.999989 -0.00288173 1.60537, 0.259089 -0.926873 0.271622 1.63725, 0.489076 -0.711702 0.504266 1.8698, 0.0729655 -0.994716 0.0722218 1.58704, 0.0729655 -0.994716 0.0722218 1.58704, 0.0796696 -0.996268 0.0331984 0.263057, -0.0644151 0.995522 0.0691811 0.980327, 0.00502409 0.999414 0.0338626 1.48934, 0.00502409 0.999414 0.0338626 1.48934, -0.00446509 0.999935 -0.0104851 3.13763, -0.00947675 -0.999891 -0.0113335 1.56978")

test.setStatistics(1)
test.run()
print "Siena path took %.2f seconds: %.2f fps" % (test.getTime(), test.getFPS())

win.close()

culled=0
culltested=0

for i in range(0,test.getNRenderedFrames()):
    culled += test.getStatValue("culledNodes", i)
    culltested += test.getStatValue("cullTestedNodes", i)

print "%d nodes culled, %d nodes culltested" % (culled, culltested)

