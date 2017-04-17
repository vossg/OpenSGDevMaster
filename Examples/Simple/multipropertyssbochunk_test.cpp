// OpenSG Test Example: MultiPropertySSBOChunk test
//
// This example test the MultiPropertySSBOChunk
//
// Outcome on running this example:
//  1. animated green cylinder and torus
//      => your platform provides all GLSL capabilities used in this
//         example. Congratulations :-)
//
//  2. animated red cylinder and torus
//      => the shader is actively working but some detail is not
//         working properly. E.g.:
//          - On ATI/AMD the usage of double fails at the time
//            writing the example on the authors Radeon 5700 series
//            platform.
//  3. animated gold or black looking cylinder and torus
//      => the shader is not working at all. Something is miserabely
//         wrong on your platform.
//
// The example uses the following shader storage block named 'ExampleBlock' 
// which is declared in the shader code below.
//
// layout (shared) buffer ExampleBlock {
//     float  f1;
//     vec3   v31;
//     vec3   v32;
//     float  f2;
//     int    i1;
//     int    i2;
//     vec3   v33;
//     mat4   m41;
//     uint   u1;
//     bool   b1;
//     vec4   v41;
//     mat4   m42;
// #ifdef HAS_FP64_EXTENSION
//     double d1;
// #endif
//     float  f3;
// } example;
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// new headers: 
#include <OSGGLEXT.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGMultiPropertySSBOChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>

#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 
#include <OpenSG/OSGGLEXT.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGMultiPropertySSBOChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#endif

#define HAS_FP64_EXTENSION

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// Create a OpenSG MultiPropertySSBOChunk object which does
// perform the shader storage buffer object abstraction.
//

OSG::UInt32 f1_id, v31_id, v32_id, f2_id, i1_id, i2_id,
            v33_id, m41_id, u1_id, b1_id, v41_id, m42_id,
#ifdef HAS_FP64_EXTENSION
            d1_id,
#endif
            f3_id;

OSG::MultiPropertySSBOChunkTransitPtr create_example_block_state()
{
    OSG::MultiPropertySSBOChunkRefPtr mpChunk = OSG::MultiPropertySSBOChunk::create();

    OSG::UInt32 float_id, double_id,  int_id, uint_id, bool_id, vec3_id, vec4_id, mat4_id;

      float_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::  FLOAT_T, 1);  f1_id =  float_id;
       vec3_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   VEC3_T, 2); v31_id =   vec3_id++; v32_id = vec3_id;
      float_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::  FLOAT_T, 1);  f2_id =  float_id;
        int_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::    INT_T, 2);  i1_id =    int_id++;  i2_id =  int_id;
       vec3_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   VEC3_T, 1); v33_id =   vec3_id;
       mat4_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   MAT4_T, 1); m41_id =   mat4_id;
       uint_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   UINT_T, 1);  u1_id =   uint_id;
       bool_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   BOOL_T, 1);  b1_id =   bool_id;
       vec4_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   VEC4_T, 1); v41_id =   vec4_id;
       mat4_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::   MAT4_T, 1); m42_id =   mat4_id;
#ifdef HAS_FP64_EXTENSION
     double_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk:: DOUBLE_T, 1);  d1_id = double_id;
#endif
      float_id = mpChunk->addMember(OSG::MultiPropertySSBOChunk::  FLOAT_T, 1);  f3_id =  float_id;

    mpChunk->setUsage(GL_STREAM_DRAW);

    OSG::UInt32 idx0 = mpChunk->addProperty();
    OSG::UInt32 idx1 = mpChunk->addProperty();
    OSG::UInt32 idx2 = mpChunk->addProperty();

    OSG::Real32 f1_0 = 10.7f, f1_1 = -14.9f, f1_2 = 0.34f;
    OSG::Vec3f v31_0(10.1f, 20.2f, 30.3f), v31_1(11.1f, 21.2f, 31.3f), v31_2(12.1f, 22.2f, 32.3f);
    OSG::Vec3f v32_0(-0.1f, -0.2f, -0.3f), v32_1(-1.1f, -1.2f, -1.3f), v32_2(-2.1f, -2.2f, -2.3f); 
    OSG::Real32 f2_0 = 1210.7f, f2_1 = -1214.9f, f2_2 = 12.34f;
    OSG::Int32  i1_0 = 15, i1_1 = -16, i1_2 = 17;
    OSG::Int32  i2_0 = 18, i2_1 = -19, i2_2 =-27;
    OSG::Vec3f v33_0(-0.01f, -0.02f, -0.03f), v33_1(-1.01f, -1.02f, -1.03f), v33_2(-2.01f, -2.02f, -2.03f); 
    OSG::Matrix m41_0( 1.f, 2.f, 3.f, 4.f,
                       5.f, 6.f, 7.f, 8.f,
                       9.f,10.f,11.f,12.f,
                      13.f,14.f,15.f,16.f),

                m41_1( -1.f, -2.f, -3.f, -4.f,
                       -5.f, -6.f, -7.f, -8.f,
                       -9.f,-10.f,-11.f,-12.f,
                      -13.f,-14.f,-15.f,-16.f),

                m41_2( -109.f, -209.f, -309.f, -409.f,
                       -509.f, -609.f, -709.f, -809.f,
                       -909.f,-1009.f,-1109.f,-1209.f,
                      -1309.f,-1409.f,-1509.f,-1609.f);

    OSG::UInt32  u1_0 = 100,  u1_1 = 200,  u1_2 = 300;
    bool         b1_0 = true, b1_1 = true, b1_2 = false;

    OSG::Vec4f v41_0(-270.1f, -270.2f, -270.3f, -270.4f), v41_1(-127.1f, -127.2f, -127.3f, -127.4f), v41_2(-227.1f, -227.2f, -227.3f, -227.4f); 
    OSG::Matrix m42_0( 91.f, 92.f, 93.f, 94.f,
                       95.f, 96.f, 97.f, 98.f,
                       99.f,910.f,911.f,912.f,
                      913.f,914.f,915.f,916.f),

                m42_1( -91.f, -92.f, -93.f, -94.f,
                       -95.f, -96.f, -97.f, -98.f,
                       -99.f,-910.f,-911.f,-912.f,
                      -913.f,-914.f,-915.f,-916.f),

                m42_2( -9109.f, -9209.f, -9309.f, -9409.f,
                       -9509.f, -9609.f, -9709.f, -9809.f,
                       -9909.f,-91009.f,-91109.f,-91209.f,
                      -91309.f,-91409.f,-91509.f,-91609.f);

#ifdef HAS_FP64_EXTENSION
    OSG::Real64 d1_0 = 1253.8, d1_1 = 2253.6, d1_2 = 3253.4;
#endif
    OSG::Real32 f3_0 = 6510.3f, f3_1 = -6514.4f, f3_2 = 650.54f;

    mpChunk->setFloatProperty (idx0,  f1_id,  f1_0);
    mpChunk->setVec3Property  (idx0, v31_id, v31_0);
    mpChunk->setVec3Property  (idx0, v32_id, v32_0);
    mpChunk->setFloatProperty (idx0,  f2_id,  f2_0);
    mpChunk->setIntProperty   (idx0,  i1_id,  i1_0);
    mpChunk->setIntProperty   (idx0,  i2_id,  i2_0);
    mpChunk->setVec3Property  (idx0, v33_id, v33_0);
    mpChunk->setMat4Property  (idx0, m41_id, m41_0);
    mpChunk->setUIntProperty  (idx0,  u1_id,  u1_0);
    mpChunk->setBoolProperty  (idx0,  b1_id,  b1_0);
    mpChunk->setVec4Property  (idx0, v41_id, v41_0);
    mpChunk->setMat4Property  (idx0, m42_id, m42_0);
#ifdef HAS_FP64_EXTENSION
    mpChunk->setDoubleProperty(idx0,  d1_id,  d1_0);
#endif
    mpChunk->setFloatProperty (idx0,  f3_id,  f3_0);


    mpChunk->setFloatProperty (idx1,  f1_id,  f1_1);
    mpChunk->setVec3Property  (idx1, v31_id, v31_1);
    mpChunk->setVec3Property  (idx1, v32_id, v32_1);
    mpChunk->setFloatProperty (idx1,  f2_id,  f2_1);
    mpChunk->setIntProperty   (idx1,  i1_id,  i1_1);
    mpChunk->setIntProperty   (idx1,  i2_id,  i2_1);
    mpChunk->setVec3Property  (idx1, v33_id, v33_1);
    mpChunk->setMat4Property  (idx1, m41_id, m41_1);
    mpChunk->setUIntProperty  (idx1,  u1_id,  u1_1);
    mpChunk->setBoolProperty  (idx1,  b1_id,  b1_1);
    mpChunk->setVec4Property  (idx1, v41_id, v41_1);
    mpChunk->setMat4Property  (idx1, m42_id, m42_1);
#ifdef HAS_FP64_EXTENSION
    mpChunk->setDoubleProperty(idx1,  d1_id,  d1_1);
#endif
    mpChunk->setFloatProperty (idx1,  f3_id,  f3_1);


    mpChunk->setFloatProperty (idx2,  f1_id,  f1_2);
    mpChunk->setVec3Property  (idx2, v31_id, v31_2);
    mpChunk->setVec3Property  (idx2, v32_id, v32_2);
    mpChunk->setFloatProperty (idx2,  f2_id,  f2_2);
    mpChunk->setIntProperty   (idx2,  i1_id,  i1_2);
    mpChunk->setIntProperty   (idx2,  i2_id,  i2_2);
    mpChunk->setVec3Property  (idx2, v33_id, v33_2);
    mpChunk->setMat4Property  (idx2, m41_id, m41_2);
    mpChunk->setUIntProperty  (idx2,  u1_id,  u1_2);
    mpChunk->setBoolProperty  (idx2,  b1_id,  b1_2);
    mpChunk->setVec4Property  (idx2, v41_id, v41_2);
    mpChunk->setMat4Property  (idx2, m42_id, m42_2);
#ifdef HAS_FP64_EXTENSION
    mpChunk->setDoubleProperty(idx2,  d1_id,  d1_2);
#endif
    mpChunk->setFloatProperty (idx2,  f3_id,  f3_2);

    return OSG::MultiPropertySSBOChunkTransitPtr(mpChunk);
}

//
// vertex shader program.
//
std::string get_vp_program();

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program();

//
// a separate transformation for every object
//
OSG::TransformRefPtr cyltrans, tortrans;

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

//
// redraw the window
//
void display(void)
{
    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // set the transforms' matrices
    m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                   OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

    cyltrans->setMatrix(m);
    
    m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                   OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

    tortrans->setMatrix(m);

    OSG::commitChanges();
    
    mgr->redraw();
}

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        
        // The cylinder and its transformation
        OSG::NodeRefPtr     cyl    = OSG::Node::create();
        OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 24, 
                                                           true, true, true );
        
        cyl->setCore(cylgeo);
    
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();
        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr     torus    = OSG::Node::create();
        OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 24, 36 );
        
        torus->setCore(torusgeo);
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);

        //
        // create the shader program
        //
        OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
        OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
        OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

        vertShader->setProgram(get_vp_program());
        fragShader->setProgram(get_fp_program());

        //
        // binding the shader storage block to a buffer binding point can be performed 
        // either by calling the shaders's addShaderStorageBlock method or by
        // adding a 'buffer block' variable to a ShaderProgramVariableChunk.
        // In the following we use both variants for illustration.
        //
        fragShader->addShaderStorageBlock("ExampleBlock", 1); // block binding point

        prog_chunk->addShader(vertShader);
        prog_chunk->addShader(fragShader);

        //
        // create shader storage buffer object for block 'ExampleBlock'
        //
        OSG::MultiPropertySSBOChunkRefPtr ssbo_example_block = create_example_block_state();

        OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
        polygon_chunk->setFrontMode(GL_FILL);
        polygon_chunk->setBackMode(GL_FILL);
        polygon_chunk->setCullFace(GL_NONE);

        OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
        depth_chunk->setEnable(true);

        OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
        prog_state->addChunk(ssbo_example_block, 1);      // buffer binding point 1
        prog_state->addChunk(prog_chunk);
        prog_state->addChunk(polygon_chunk);
        prog_state->addChunk(depth_chunk);

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(prog_state);
        scene->setCore(mgrp);

        OSG::commitChanges();
    
        mgr->setRoot(scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

//
// react to mouse button presses
//
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            cyltrans = NULL;
            tortrans = NULL;
            mgr      = NULL;
        
            OSG::osgExit();
            exit(0);
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;
    }
}

//
// setup the GLUT library which handles the windows for us
//
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

//
// vertex shader program.
//
std::string get_vp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    gl_Position = ftransform();"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 440 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:      enable"
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << ""
#ifdef HAS_FP64_EXTENSION
    << endl << "#extension GL_ARB_gpu_shader_fp64:              enable"
#endif
    << endl << ""
    << endl << "double eps = 1.0e-6;"
    << endl << "const int numEntries = 3;"
    << endl << ""
    << endl << "struct Example"
    << endl << "{"
    << endl << "    float  f1;"
    << endl << "    vec3   v31;"
    << endl << "    vec3   v32;"
    << endl << "    float  f2;"
    << endl << "    int    i1;"
    << endl << "    int    i2;"
    << endl << "    vec3   v33;"
    << endl << "    mat4   m41;"
    << endl << "    uint   u1;"
    << endl << "    bool   b1;"
    << endl << "    vec4   v41;"
    << endl << "    mat4   m42;"
#ifdef HAS_FP64_EXTENSION
    << endl << "    double d1;"
#endif
    << endl << "    float  f3;"
    << endl << "} example;"
    << endl << ""
    << endl << "layout (std430) buffer ExampleBlock"
    << endl << "{"
    << endl << "    Example example[numEntries];"
    << endl << "} examples;"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << ""
    << endl << "    vec4 error = vec4(1.0, 0.0, 0.0, 1.0);"
    << endl << "    vec4 color = vec4(0.0, 1.0, 0.0, 1.0);"
    << endl << ""
    << endl << "    float f1_0 = 10.7f;"
    << endl << "    float f1_1 = -14.9f;"
    << endl << "    float f1_2 = 0.34f;"
    << endl << ""
    << endl << "    vec3 v31_0 = vec3(10.1f, 20.2f, 30.3f);"
    << endl << "    vec3 v31_1 = vec3(11.1f, 21.2f, 31.3f);"
    << endl << "    vec3 v31_2 = vec3(12.1f, 22.2f, 32.3f);"
    << endl << ""
    << endl << "    vec3 v32_0 = vec3(-0.1f, -0.2f, -0.3f);"
    << endl << "    vec3 v32_1 = vec3(-1.1f, -1.2f, -1.3f);"
    << endl << "    vec3 v32_2 = vec3(-2.1f, -2.2f, -2.3f);"
    << endl << ""
    << endl << "    float f2_0 = 1210.7f;"
    << endl << "    float f2_1 = -1214.9f;"
    << endl << "    float f2_2 = 12.34f;"
    << endl << ""
    << endl << "    int i1_0 = 15;"
    << endl << "    int i1_1 = -16;"
    << endl << "    int i1_2 = 17;"
    << endl << ""
    << endl << "    int i2_0 = 18;"
    << endl << "    int i2_1 = -19;"
    << endl << "    int i2_2 =-27;"
    << endl << ""
    << endl << "    vec3 v33_0 = vec3(-0.01f, -0.02f, -0.03f);"
    << endl << "    vec3 v33_1 = vec3(-1.01f, -1.02f, -1.03f);"
    << endl << "    vec3 v33_2 = vec3(-2.01f, -2.02f, -2.03f);"
    << endl << ""
    << endl << "    //"
    << endl << "    // The matrix elements are expected to be column-major layout."
    << endl << "    // The OpenSG element wise contructor expects the elements in"
    << endl << "    // row-major layout. Therefore we have to transpose all matrices"
    << endl << "    // of the example once!"
    << endl << "    //"
    << endl << "    mat4 m41_0 = mat4( 1.f, 2.f, 3.f, 4.f,"
    << endl << "                       5.f, 6.f, 7.f, 8.f,"
    << endl << "                       9.f,10.f,11.f,12.f,"
    << endl << "                      13.f,14.f,15.f,16.f);"
    << endl << "    m41_0 = transpose(m41_0);"
    << endl << ""
    << endl << "    mat4 m41_1 = mat4( -1.f, -2.f, -3.f, -4.f,"
    << endl << "                       -5.f, -6.f, -7.f, -8.f,"
    << endl << "                       -9.f,-10.f,-11.f,-12.f,"
    << endl << "                      -13.f,-14.f,-15.f,-16.f);"
    << endl << "    m41_1 = transpose(m41_1);"
    << endl << ""
    << endl << "    mat4 m41_2 = mat4( -109.f, -209.f, -309.f, -409.f,"
    << endl << "                       -509.f, -609.f, -709.f, -809.f,"
    << endl << "                       -909.f,-1009.f,-1109.f,-1209.f,"
    << endl << "                      -1309.f,-1409.f,-1509.f,-1609.f);"
    << endl << "    m41_2 = transpose(m41_2);"
    << endl << ""
    << endl << "    uint u1_0 = 100;"
    << endl << "    uint u1_1 = 200;"
    << endl << "    uint u1_2 = 300;"
    << endl << ""
    << endl << "    bool b1_0 = true;"
    << endl << "    bool b1_1 = true;"
    << endl << "    bool b1_2 = false;"
    << endl << ""
    << endl << "    vec4 v41_0 = vec4(-270.1f, -270.2f, -270.3f, -270.4f);"
    << endl << "    vec4 v41_1 = vec4(-127.1f, -127.2f, -127.3f, -127.4f);"
    << endl << "    vec4 v41_2 = vec4(-227.1f, -227.2f, -227.3f, -227.4f);"
    << endl << ""
    << endl << "    mat4 m42_0 = mat4( 91.f, 92.f, 93.f, 94.f,"
    << endl << "                       95.f, 96.f, 97.f, 98.f,"
    << endl << "                       99.f,910.f,911.f,912.f,"
    << endl << "                      913.f,914.f,915.f,916.f);"
    << endl << "    m42_0 = transpose(m42_0);"
    << endl << ""
    << endl << "    mat4 m42_1 = mat4( -91.f, -92.f, -93.f, -94.f,"
    << endl << "                       -95.f, -96.f, -97.f, -98.f,"
    << endl << "                       -99.f,-910.f,-911.f,-912.f,"
    << endl << "                      -913.f,-914.f,-915.f,-916.f);"
    << endl << "    m42_1 = transpose(m42_1);"
    << endl << ""
    << endl << "    mat4 m42_2 = mat4( -9109.f, -9209.f, -9309.f, -9409.f,"
    << endl << "                       -9509.f, -9609.f, -9709.f, -9809.f,"
    << endl << "                       -9909.f,-91009.f,-91109.f,-91209.f,"
    << endl << "                      -91309.f,-91409.f,-91509.f,-91609.f);"
    << endl << "    m42_2 = transpose(m42_2);"
    << endl << ""
#ifdef HAS_FP64_EXTENSION
    << endl << "    double d1_0 = 1253.8;"
    << endl << "    double d1_1 = 2253.6;"
    << endl << "    double d1_2 = 3253.4;"
#endif
    << endl << ""
    << endl << "    float f3_0 = 6510.3f;"
    << endl << "    float f3_1 = -6514.4f;"
    << endl << "    float f3_2 = 650.54f;"
    << endl << ""
    << endl << "    if (examples.example[0].f1  !=  f1_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].v31 != v31_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].v32 != v32_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].f2  !=  f2_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].i1  !=  i1_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].i2  !=  i2_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].v33 != v33_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].m41 != m41_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].u1  !=  u1_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].b1  !=  b1_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].v41 != v41_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[0].m42 != m42_0)"
    << endl << "        color = error;"
#ifdef HAS_FP64_EXTENSION
    << endl << "    if (abs(examples.example[0].d1 - d1_0) < eps)"
    << endl << "        color = error;"
#endif
    << endl << "    if (examples.example[0].f3  !=  f3_0)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].f1  !=  f1_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].v31 != v31_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].v32 != v32_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].f2  !=  f2_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].i1  !=  i1_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].i2  !=  i2_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].v33 != v33_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].m41 != m41_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].u1  !=  u1_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].b1  !=  b1_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].v41 != v41_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[1].m42 != m42_1)"
    << endl << "        color = error;"
#ifdef HAS_FP64_EXTENSION
    << endl << "    if (abs(examples.example[1].d1 - d1_1) < eps)"
    << endl << "        color = error;"
#endif
    << endl << "    if (examples.example[1].f3  !=  f3_1)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].f1  !=  f1_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].v31 != v31_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].v32 != v32_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].f2  !=  f2_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].i1  !=  i1_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].i2  !=  i2_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].v33 != v33_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].m41 != m41_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].u1  !=  u1_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].b1  !=  b1_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].v41 != v41_2)"
    << endl << "        color = error;"
    << endl << "    if (examples.example[2].m42 != m42_2)"
    << endl << "        color = error;"
#ifdef HAS_FP64_EXTENSION
    << endl << "    if (abs(examples.example[2].d1 - d1_2) < eps)"
    << endl << "        color = error;"
#endif
    << endl << "    if (examples.example[2].f3  !=  f3_2)"
    << endl << "        color = error;"
    << endl << ""
    << endl << "    vFragColor = color;"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}
