
To get it working:

CMAKE:
-----------------------------------------------------------------------------

add OSGExGPUVolRT to OSG_EXTRA_EXTERNAL_MODULES

activate OSG_LINK_EXTERNAL_MODULES_TO_CSM

configure

activate new OSGBUILD_OSGExGPUVolRT entry

configure

set new OSG_OSGExGPUVolRT_SOURCE_DIR entry to AsAlgorithmStage dir

configure

generate


BUILD:
-----------------------------------------------------------------------------

build OpenSG as usual


Variants:
-----------------------------------------------------------------------------


V0:
-----------------------------------------------------------------------------

Content:

just the original program implemented as an Algorithm. Only derives the
viewport size from OpenSG.

Running:

testAlgoV0 must be run from the directory that contains the shader files
(raycasting_shader.fp.cg and raycasting_shader.vp.cg). So either
run it from ../OrgProg or copy/link the files to your build directory
and run ./bin/testAlgoV0

Alternatively run testCSM AsAlgorithmStage/CSM0, again from a directory
that contains the shader files. E.g. assuming they are in the build dir
and the build is parallel to the main OpenSG dir, run

./bin/testCSM ../OpenSG/Examples/CustomIntegration/AlgorithmStage/InitialAlgorithm/CSM0/

Be sure OSG_LINK_EXTERNAL_MODULES_TO_CSM is active as suggested above, 
otherwise the example objects are not found automatically.


V1:
------------------------------------------------------------------------------

Content:

Use the OpenSG projection/modelview matrices. Minimum requirement to use
OpenSG clustering.

Running:

Same as above except the test app is testAlgoV1 and the CSM dir is CSM1.

Additionally there is the CSM1-Multi dir which containts the csm multi-window
cluster setup. For this you must use testClusterServerX (from CSM) as the
server and make sure the server finds the shader files. 

V2:
------------------------------------------------------------------------------

Content:

Implement toogleVisuals and Stepsize as OpenSG fields so they are transmitted
through the cluster.

Running:

Same as above except the test app is testAlgoV2 and the CSM dirs are CSM2
and CSM2-Multi.
