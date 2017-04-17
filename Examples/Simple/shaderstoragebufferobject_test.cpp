// OpenSG Test Example: ShaderStorageBufferObject_Test
//
// This example allows to research the capabilities of the shader
// storage buffer object extension on your graphics platform.
//
// This example is similar to the ShaderStorageBufferObject_Test_1
// example. This one uses a non array block layout, whereas the
// test_1 example uses an even more complex setup with an array
// block layout.
//
// The example does use the ShaderStorageObjChunk which allows the
// host application to provide the shader storage block member values 
// directly to the chunk. The layout of the shader storage block is determined 
// by the shader code. Any of the layout values of the specification (shared, 
// packed, std140, std430) are allowed.
//
// Outcome on running this example:
//  1. animated green cylinder and torus
//      => your platform provides all GLSL capabilities used in this
//         example. Congratulations :-)
//
//  2. animated red cylinder and torus
//      => the shader is actively working but some detail is not
//         working properly. E.g.:
//          - On ATI/AMD the usage of bvec2 fails at the time of writing
//            the example on the authors Radeon 5700 series 
//            platform, iff the 'std140' layout is used.
//          - On ATI/AMD the usage of double and dvec2 fails at the time
//            writing the example on the authors Radeon 5700 series
//            platform.
//
//  3. animated gold looking cylinder and torus
//      => the shader is not working at all. Something is miserabely
//         wrong on your platform.
//
// The example uses the following shader storage block named 'ExampleBlock' 
// which is declared in the shader code below.
//
// struct Test
// {
//     float t;
//     ivec3 v[3];
//     int w;
// };
//
// layout(shared) buffer ExampleBlock {
//     float a;
//     vec2 b;
//     vec3 c;
//     struct {
//         int d;
//         bvec2 e;
//     } f;
//     float g;
//     float h[2];
//     mat2x3 i;
//     struct {
//         uvec3 j;
//         vec2 k;
//         float l[2];
//         vec2 m;
//         mat3 n[2];
//     } o[2];
//     double p;
//     bool q;
//     struct {
//         dvec2 r;
//         int s;
//         Test x[4];       // structs can not explicitely be nested but implicit nesting is fine
//     } y;
// } example;
//
// For this example the values must be provided for the following data slots:
//
// "ExampleBlock.a"
// "ExampleBlock.b"
// "ExampleBlock.c"
// "ExampleBlock.f.d"
// "ExampleBlock.f.e"
// "ExampleBlock.g"
// "ExampleBlock.h[0]"
// "ExampleBlock.h[1]"
// "ExampleBlock.i"
// "ExampleBlock.o[0].j"
// "ExampleBlock.o[0].k"
// "ExampleBlock.o[0].l[0]"
// "ExampleBlock.o[0].l[1]"
// "ExampleBlock.o[0].m"
// "ExampleBlock.o[0].n[0]"
// "ExampleBlock.o[0].n[1]"
// "ExampleBlock.o[1].j"
// "ExampleBlock.o[1].k"
// "ExampleBlock.o[1].l[0]"
// "ExampleBlock.o[1].l[1]"
// "ExampleBlock.o[1].m"
// "ExampleBlock.o[1].n[0]"
// "ExampleBlock.o[1].n[1]"
// "ExampleBlock.p"
// "ExampleBlock.q"
// "ExampleBlock.y.r"
// "ExampleBlock.y.s"
// "ExampleBlock.y.x[0].t"
// "ExampleBlock.y.x[0].v[0]"
// "ExampleBlock.y.x[0].v[1]"
// "ExampleBlock.y.x[0].v[2]"
// "ExampleBlock.y.x[0].w"
// "ExampleBlock.y.x[1].t"
// "ExampleBlock.y.x[1].v[0]"
// "ExampleBlock.y.x[1].v[1]"
// "ExampleBlock.y.x[1].v[2]"
// "ExampleBlock.y.x[1].w"
// "ExampleBlock.y.x[2].t"
// "ExampleBlock.y.x[2].v[0]"
// "ExampleBlock.y.x[2].v[1]"
// "ExampleBlock.y.x[2].v[2]"
// "ExampleBlock.y.x[2].w"
// "ExampleBlock.y.x[3].t"
// "ExampleBlock.y.x[3].v[0]"
// "ExampleBlock.y.x[3].v[1]"
// "ExampleBlock.y.x[3].v[2]"
// "ExampleBlock.y.x[3].w"
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
#include <OSGShaderStorageBufferObjChunk.h>
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
#include <OpenSG/OSGShaderStorageBufferObjChunk.h>
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
// Create a OpenSG ShaderStorageBufferObjChunk object which does
// perform the shader storage buffer object abstraction.
// For each block member entry (declared in the shader) a
// corresponding addXXX call is to be performed on the
// ssbo chunk. The cardinality for arrays must be provided
// to the function calls (defaults to 1). 
// The matrix functions are defined in column-major order
// matching the default definition of GLSL. I.e. a addMat2x3(2)
// call would request space and layout for an array of two
// matrices with two columns and three rows.
//
OSG::ShaderStorageBufferObjChunkTransitPtr create_example_block_state()
{
    OSG::ShaderStorageBufferObjChunkRefPtr ssbo = OSG::ShaderStorageBufferObjChunk::create();

    ssbo->setBlockName("ExampleBlock");
    ssbo->setUsage(GL_STREAM_DRAW);

    ssbo->addFloat   ("ExampleBlock.a");
    ssbo->addVec2    ("ExampleBlock.b");
    ssbo->addVec3    ("ExampleBlock.c");
    ssbo->addInt     ("ExampleBlock.f.d");
    ssbo->addBVec2   ("ExampleBlock.f.e");
    ssbo->addFloat   ("ExampleBlock.g");
    ssbo->addFloat   ("ExampleBlock.h", 2);
    ssbo->addMat2x3  ("ExampleBlock.i");     // 2 columns and 3 rows
    ssbo->addUVec3   ("ExampleBlock.o[0].j");
    ssbo->addVec2    ("ExampleBlock.o[0].k");
    ssbo->addFloat   ("ExampleBlock.o[0].l", 2);
    ssbo->addVec2    ("ExampleBlock.o[0].m");
    ssbo->addMat3    ("ExampleBlock.o[0].n", 2);

    ssbo->addUVec3   ("ExampleBlock.o[1].j");
    ssbo->addVec2    ("ExampleBlock.o[1].k");
    ssbo->addFloat   ("ExampleBlock.o[1].l", 2);
    ssbo->addVec2    ("ExampleBlock.o[1].m");
    ssbo->addMat3    ("ExampleBlock.o[1].n", 2);

#ifdef HAS_FP64_EXTENSION
    ssbo->addDouble  ("ExampleBlock.p");
#endif
    ssbo->addBool    ("ExampleBlock.q");

#ifdef HAS_FP64_EXTENSION
    ssbo->addDVec2   ("ExampleBlock.y.r");
#endif
    ssbo->addInt     ("ExampleBlock.y.s");

    ssbo->addFloat   ("ExampleBlock.y.x[0].t");
    ssbo->addIVec3   ("ExampleBlock.y.x[0].v", 3);
    ssbo->addInt     ("ExampleBlock.y.x[0].w");

    ssbo->addFloat   ("ExampleBlock.y.x[1].t");
    ssbo->addIVec3   ("ExampleBlock.y.x[1].v", 3);
    ssbo->addInt     ("ExampleBlock.y.x[1].w");

    ssbo->addFloat   ("ExampleBlock.y.x[2].t");
    ssbo->addIVec3   ("ExampleBlock.y.x[2].v", 3);
    ssbo->addInt     ("ExampleBlock.y.x[2].w");

    ssbo->addFloat   ("ExampleBlock.y.x[3].t");
    ssbo->addIVec3   ("ExampleBlock.y.x[3].v", 3);
    ssbo->addInt     ("ExampleBlock.y.x[3].w");

    return OSG::ShaderStorageBufferObjChunkTransitPtr(ssbo);
}

//
// Fill the ssbo chunk with values.
//
void update_example_block_state(OSG::ShaderStorageBufferObjChunk* ssbo)
{
    ssbo->setFloat ("ExampleBlock.a", 23.7f);
    ssbo->setVec2  ("ExampleBlock.b", OSG::Vec2f(1.4f, 8.6f));
    ssbo->setVec3  ("ExampleBlock.c", OSG::Vec3f(0.1f, 0.2f, 0.3f));

    ssbo->setInt   ("ExampleBlock.f.d", 14);
    ssbo->setBVec2 ("ExampleBlock.f.e", OSG::Vec2b(true, false));
    ssbo->setFloat ("ExampleBlock.g", 15.3f);
    ssbo->setFloat ("ExampleBlock.h", 17.6f, 0);
    ssbo->setFloat ("ExampleBlock.h", 19.3f, 1);

    // Matrix mxn (m rows and n columns): 
    // ----------------------------------
    // test_mat = a11 a12 a13 a14
    //            a21 a22 a23 a24
    //            a31 a32 a33 a34
    //            a41 a42 a43 a44
    // OpenSG takes rows...
    OSG::Matrix4f mat1( 11,12,13,14,    // row 1
                        21,22,23,24,    // row 2
                        31,32,33,34,    // row 3
                        41,42,43,44 );  // row 4

    // ... and provides elements in column-major order
    //    OSG::Real32* storage = mat1.getValues();
    OSG::Vec4f   column1 = mat1[1];
    OSG::Vec4f   column2 = mat1[2];
    OSG::Vec4f   column3 = mat1[3];
    OSG::Vec4f   column4 = mat1[4];

    // GLSL uses column-major layout, i.e. mat2x3 is a matrix with 2 colums and 3 rows
    //
    // mat2x3   = a11 a12
    //            a21 a22
    //            a31 a32

    ssbo->setMat2x3("ExampleBlock.i", mat1);

    ssbo->setUVec3 ("ExampleBlock.o[0].j", OSG::Vec3u(1, 2, 3));
    ssbo->setVec2  ("ExampleBlock.o[0].k", OSG::Vec2f(1.1f, 2.2f));
    ssbo->setFloat ("ExampleBlock.o[0].l", 11.1f, 0);
    ssbo->setFloat ("ExampleBlock.o[0].l", 22.2f, 1);
    ssbo->setVec2  ("ExampleBlock.o[0].m", OSG::Vec2f(22.2f, 33.3f));

    OSG::Matrix4f mat2( 1.1f, 1.2f, 1.3f, 1.4f,     // row 1
                        2.1f, 2.2f, 2.3f, 2.4f,     // row 2
                        3.1f, 3.2f, 3.3f, 3.4f,     // row 3
                        4.1f, 4.2f, 4.3f, 4.4f );   // row 4

    ssbo->setMat3  ("ExampleBlock.o[0].n", mat2, 0);

    OSG::Matrix4f mat3( 10.1f, 10.2f, 10.3f, 10.4f,     // row 1
                        20.1f, 20.2f, 20.3f, 20.4f,     // row 2
                        30.1f, 30.2f, 30.3f, 30.4f,     // row 3
                        40.1f, 40.2f, 40.3f, 40.4f );   // row 4

    ssbo->setMat3  ("ExampleBlock.o[0].n", mat3, 1);

    ssbo->setUVec3 ("ExampleBlock.o[1].j", OSG::Vec3u(7, 8, 9));
    ssbo->setVec2  ("ExampleBlock.o[1].k", OSG::Vec2f(7.7f, 8.8f));
    ssbo->setFloat ("ExampleBlock.o[1].l", 77.7f, 0);
    ssbo->setFloat ("ExampleBlock.o[1].l", 88.8f, 1);
    ssbo->setVec2  ("ExampleBlock.o[1].m", OSG::Vec2f(88.8f, 99.9f));

    OSG::Matrix4f mat4( 100.1f, 100.2f, 100.3f, 100.4f,     // row 1
                        200.1f, 200.2f, 200.3f, 200.4f,     // row 2
                        300.1f, 300.2f, 300.3f, 300.4f,     // row 3
                        400.1f, 400.2f, 400.3f, 400.4f );   // row 4

    ssbo->setMat3  ("ExampleBlock.o[1].n", mat4, 0);

    OSG::Matrix4f mat5( 1000.1f, 1000.2f, 1000.3f, 1000.4f,     // row 1
                        2000.1f, 2000.2f, 2000.3f, 2000.4f,     // row 2
                        3000.1f, 3000.2f, 3000.3f, 3000.4f,     // row 3
                        4000.1f, 4000.2f, 4000.3f, 4000.4f );   // row 4

    ssbo->setMat3  ("ExampleBlock.o[1].n", mat5, 1);

#ifdef HAS_FP64_EXTENSION
    ssbo->setDouble("ExampleBlock.p", 17856.23456);
#endif
    ssbo->setBool  ("ExampleBlock.q", true);

#ifdef HAS_FP64_EXTENSION
    ssbo->setDVec2 ("ExampleBlock.y.r", OSG::Vec2d(9567.123, 2345.63456));
#endif
    ssbo->setInt   ("ExampleBlock.y.s", 123);

    ssbo->setFloat ("ExampleBlock.y.x[0].t", 1.001f);
    ssbo->setIVec3 ("ExampleBlock.y.x[0].v", OSG::Vec3i(1,0,1), 0);
    ssbo->setIVec3 ("ExampleBlock.y.x[0].v", OSG::Vec3i(2,0,2), 1);
    ssbo->setIVec3 ("ExampleBlock.y.x[0].v", OSG::Vec3i(3,0,3), 2);
    ssbo->setInt   ("ExampleBlock.y.x[0].w", 1);

    ssbo->setFloat ("ExampleBlock.y.x[1].t", 2.002f);
    ssbo->setIVec3 ("ExampleBlock.y.x[1].v", OSG::Vec3i(4,0,4), 0);
    ssbo->setIVec3 ("ExampleBlock.y.x[1].v", OSG::Vec3i(5,0,5), 1);
    ssbo->setIVec3 ("ExampleBlock.y.x[1].v", OSG::Vec3i(6,0,6), 2);
    ssbo->setInt   ("ExampleBlock.y.x[1].w", 2);

    ssbo->setFloat ("ExampleBlock.y.x[2].t", 3.003f);
    ssbo->setIVec3 ("ExampleBlock.y.x[2].v", OSG::Vec3i(7,0,7), 0);
    ssbo->setIVec3 ("ExampleBlock.y.x[2].v", OSG::Vec3i(8,0,8), 1);
    ssbo->setIVec3 ("ExampleBlock.y.x[2].v", OSG::Vec3i(9,0,9), 2);
    ssbo->setInt   ("ExampleBlock.y.x[2].w", 3);

    ssbo->setFloat ("ExampleBlock.y.x[3].t", 4.004f);
    ssbo->setIVec3 ("ExampleBlock.y.x[3].v", OSG::Vec3i(1,4,6), 0);
    ssbo->setIVec3 ("ExampleBlock.y.x[3].v", OSG::Vec3i(2,5,7), 1);
    ssbo->setIVec3 ("ExampleBlock.y.x[3].v", OSG::Vec3i(3,6,8), 2);
    ssbo->setInt   ("ExampleBlock.y.x[3].w", 4);
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
        OSG::ShaderStorageBufferObjChunkRefPtr ssbo_example_block = create_example_block_state();

        update_example_block_state(ssbo_example_block);

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
        std::string vp_program =
            "\n"
            "#version 330 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects: enable\n"
            "#extension GL_ARB_uniform_buffer_object:   enable\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = ftransform();\n"
            "}\n"
            "\n"
            ;

    return vp_program;
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    std::string fp_program =
            "\n"
            "#version 440 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects:      enable\n"
            "#extension GL_ARB_shader_storage_buffer_object: enable\n"
            "\n"
#ifdef HAS_FP64_EXTENSION
            "#extension GL_ARB_gpu_shader_fp64:         enable\n"
#endif
            "\n"
            "struct Test\n"
            "{\n"
            "    float t;\n"
            "    ivec3 v[3];\n"
            "    int w;\n"
            "};\n"
            "\n"
            "layout (shared) buffer ExampleBlock\n"
            "{\n"
            "     float a;\n"
            "     vec2 b;\n"
            "     vec3 c;\n"
            "     struct {\n"
            "         int d;\n"
            "         bvec2 e;\n"
            "     } f;\n"
            "     float g;\n"
            "     float h[2];\n"
            "     mat2x3 i;\n"
            "     struct {\n"
            "         uvec3 j;\n"
            "         vec2 k;\n"
            "         float l[2];\n"
            "         vec2 m;\n"
            "         mat3 n[2];\n"
            "     } o[2];\n"
#ifdef HAS_FP64_EXTENSION
            "     double p;\n"
#endif
            "     bool q;\n"
            "     struct {\n"
#ifdef HAS_FP64_EXTENSION
            "         dvec2 r;\n"
#endif
            "         int s;\n"
            "         Test x[4];       // structs can not explicitely be nested but implicit nesting is fine\n"
            "     } y;\n"
            " } example;\n"
            "\n"
            "layout(location = 0) out vec4 vFragColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "\n"
            "    vec4 error = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "    vec4 color = vec4(0.0, 1.0, 0.0, 1.0);\n"
            "\n"
            "\n"
            "     float  a   = example.a;\n"
            "     vec2   b   = example.b;\n"
            "     vec3   c   = example.c;\n"
            "     int    d   = example.f.d;\n"
            "     bvec2  e   = example.f.e;\n"
            "     float  g   = example.g;\n"
            "     float  h0  = example.h[0];\n"
            "     float  h1  = example.h[1];\n"
            "     mat2x3 i   = example.i;\n"
            "     uvec3  j0  = example.o[0].j;\n"
            "     vec2   k0  = example.o[0].k;\n"
            "     float  l00 = example.o[0].l[0];\n"
            "     float  l01 = example.o[0].l[1];\n"
            "     vec2   m0  = example.o[0].m;\n"
            "     mat3   n00 = example.o[0].n[0];\n"
            "     mat3   n01 = example.o[0].n[1];\n"
            "     uvec3  j1  = example.o[1].j;\n"
            "     vec2   k1  = example.o[1].k;\n"
            "     float  l10 = example.o[1].l[0];\n"
            "     float  l11 = example.o[1].l[1];\n"
            "     vec2   m1  = example.o[1].m;\n"
            "     mat3   n10 = example.o[1].n[0];\n"
            "     mat3   n11 = example.o[1].n[1];\n"
#ifdef HAS_FP64_EXTENSION
            "     double p   = example.p;\n"
#endif
            "     bool   q   = example.q;\n"
#ifdef HAS_FP64_EXTENSION
            "     dvec2  r   = example.y.r;\n"
#endif
            "     int    s   = example.y.s;\n"
            "     float  t0  = example.y.x[0].t;\n"
            "     ivec3  v00 = example.y.x[0].v[0];\n"
            "     ivec3  v01 = example.y.x[0].v[1];\n"
            "     ivec3  v02 = example.y.x[0].v[2];\n"
            "     int    w0  = example.y.x[0].w;\n"
            "     float  t1  = example.y.x[1].t;\n"
            "     ivec3  v10 = example.y.x[1].v[0];\n"
            "     ivec3  v11 = example.y.x[1].v[1];\n"
            "     ivec3  v12 = example.y.x[1].v[2];\n"
            "     int    w1  = example.y.x[1].w;\n"
            "     float  t2  = example.y.x[2].t;\n"
            "     ivec3  v20 = example.y.x[2].v[0];\n"
            "     ivec3  v21 = example.y.x[2].v[1];\n"
            "     ivec3  v22 = example.y.x[2].v[2];\n"
            "     int    w2  = example.y.x[2].w;\n"
            "     float  t3  = example.y.x[3].t;\n"
            "     ivec3  v30 = example.y.x[3].v[0];\n"
            "     ivec3  v31 = example.y.x[3].v[1];\n"
            "     ivec3  v32 = example.y.x[3].v[2];\n"
            "     int    w3  = example.y.x[3].w;\n"
            "\n"
            "\n"
            "    if (a != 23.7)\n"
            "        color = error;\n"
            "\n"
            "    if (b != vec2(1.4, 8.6))\n"
            "        color = error;\n"
            "\n"
            "    if (c != vec3(0.1, 0.2, 0.3))\n"
            "        color = error;\n"
            "\n"
            "    if (d != 14)\n"
            "        color = error;\n"
            "\n"
            "    if (e != bvec2(true, false))\n"
            "        color = error;\n"
            "\n"
            "    if (g != 15.3)\n"
            "        color = error;\n"
            "\n"
            "    if (h0 != 17.6)\n"
            "        color = error;\n"
            "\n"
            "    if (h1 != 19.3)\n"
            "        color = error;\n"
            "\n"
            "    if (i[0][0] != 11)\n"
            "        color = error;\n"
            "\n"
            "    if (i[0][1] != 21)\n"
            "        color = error;\n"
            "\n"
            "    if (i[0][2] != 31)\n"
            "        color = error;\n"
            "\n"
            "    if (i[1][0] != 12)\n"
            "        color = error;\n"
            "\n"
            "    if (i[1][1] != 22)\n"
            "        color = error;\n"
            "\n"
            "    if (i[1][2] != 32)\n"
            "        color = error;\n"
            "\n"
            "    if (j0 != uvec3(1, 2, 3))\n"
            "        color = error;\n"
            "\n"
            "    if (k0 != vec2(1.1, 2.2))\n"
            "        color = error;\n"
            "\n"
            "    if (l00 != 11.1)\n"
            "        color = error;\n"
            "\n"
            "    if (l01 != 22.2)\n"
            "        color = error;\n"
            "\n"
            "    if (m0 != vec2(22.2, 33.3))\n"
            "        color = error;\n"
            "\n"
            "    if (n00[0][0] != 1.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[0][1] != 2.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[0][2] != 3.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[1][0] != 1.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[1][1] != 2.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[1][2] != 3.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[2][0] != 1.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[2][1] != 2.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n00[2][2] != 3.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[0][0] != 10.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[0][1] != 20.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[0][2] != 30.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[1][0] != 10.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[1][1] != 20.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[1][2] != 30.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[2][0] != 10.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[2][1] != 20.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n01[2][2] != 30.3)\n"
            "        color = error;\n"
            "\n"
            "    if (j1 != uvec3(7, 8, 9))\n"
            "        color = error;\n"
            "\n"
            "    if (k1 != vec2(7.7, 8.8))\n"
            "        color = error;\n"
            "\n"
            "    if (l10 != 77.7)\n"
            "        color = error;\n"
            "\n"
            "    if (l11 != 88.8)\n"
            "        color = error;\n"
            "\n"
            "    if (m1 != vec2(88.8, 99.9))\n"
            "        color = error;\n"
            "\n"
            "    if (n10[0][0] != 100.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[0][1] != 200.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[0][2] != 300.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[1][0] != 100.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[1][1] != 200.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[1][2] != 300.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[2][0] != 100.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[2][1] != 200.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n10[2][2] != 300.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[0][0] != 1000.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[0][1] != 2000.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[0][2] != 3000.1)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[1][0] != 1000.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[1][1] != 2000.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[1][2] != 3000.2)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[2][0] != 1000.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[2][1] != 2000.3)\n"
            "        color = error;\n"
            "\n"
            "    if (n11[2][2] != 3000.3)\n"
            "        color = error;\n"
            "\n"
#ifdef HAS_FP64_EXTENSION
            "    if (p != 17856.23456LF)\n"
            "        color = error;\n"
#endif
            "\n"
            "    if (q != true)\n"
            "        color = error;\n"
            "\n"
#ifdef HAS_FP64_EXTENSION
            "    if (r != dvec2(9567.123LF, 2345.63456LF))\n"
            "        color = error;\n"
#endif
            "\n"
            "    if (s != 123)\n"
            "        color = error;\n"
            "\n"
            "    if (t0 != 1.001)\n"
            "        color = error;\n"
            "\n"
            "    if (v00 != ivec3(1,0,1))\n"
            "        color = error;\n"
            "\n"
            "    if (v01 != ivec3(2,0,2))\n"
            "        color = error;\n"
            "\n"
            "    if (v02 != ivec3(3,0,3))\n"
            "        color = error;\n"
            "\n"
            "    if (w0 != 1)\n"
            "        color = error;\n"
            "\n"
            "    if (t1 != 2.002)\n"
            "        color = error;\n"
            "\n"
            "    if (v10 != ivec3(4,0,4))\n"
            "        color = error;\n"
            "\n"
            "    if (v11 != ivec3(5,0,5))\n"
            "        color = error;\n"
            "\n"
            "    if (v12 != ivec3(6,0,6))\n"
            "        color = error;\n"
            "\n"
            "    if (w1 != 2)\n"
            "        color = error;\n"
            "\n"
            "    if (t2 != 3.003)\n"
            "        color = error;\n"
            "\n"
            "    if (v20 != ivec3(7,0,7))\n"
            "        color = error;\n"
            "\n"
            "    if (v21 != ivec3(8,0,8))\n"
            "        color = error;\n"
            "\n"
            "    if (v22 != ivec3(9,0,9))\n"
            "        color = error;\n"
            "\n"
            "    if (w2 != 3)\n"
            "        color = error;\n"
            "\n"
            "    if (t3 != 4.004)\n"
            "        color = error;\n"
            "\n"
            "    if (v30 != ivec3(1,4,6))\n"
            "        color = error;\n"
            "\n"
            "    if (v31 != ivec3(2,5,7))\n"
            "        color = error;\n"
            "\n"
            "    if (v32 != ivec3(3,6,8))\n"
            "        color = error;\n"
            "\n"
            "    if (w3 != 4)\n"
            "        color = error;\n"
            "\n"
            "\n"
            "    vFragColor = color;\n"
            "}\n"
            "\n"
            ;

    return fp_program;
}
