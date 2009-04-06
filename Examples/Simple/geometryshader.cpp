// OpenSG GLSL shader example: Geometry Shader
//
// Demonstrates the use of the SHLChunk
// Implements a geometry shader which creates for each triangle an
// extra triangle showing the face normal.

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
#include <OSGGLEXT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGSHLChunk.h>
#else
// Headers
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLEXT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGBaseFunctions.h>

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPointLight.h>

#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGSHLChunk.h>
#endif



// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
SimpleSceneManager *_mgr;
// The scene
NodeRefPtr          _scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

static std::string _vertex_shader =
"void main(void)\n"
"{\n"
"    gl_Position = gl_Vertex;\n"
"    gl_TexCoord[0] = vec4(abs(gl_Normal), 0.0);\n"
"}\n"
"\n";

static std::string _fragment_shader =
"void main (void)\n"
"{\n"
"    gl_FragColor = gl_Color;\n"
"\n"
"}\n";

// ok we create some triangles to draw the face normals.
static std::string _geometry_shader =
"#version 120\n"
"#extension GL_EXT_geometry_shader4 : enable\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 v1 = gl_PositionIn[0];\n"
"    vec4 v2 = gl_PositionIn[1];\n"
"    vec4 v3 = gl_PositionIn[2];\n"
"\n"
"    vec4 l1 = v2 - v1;\n"
"    vec4 l2 = v3 - v1;\n"
"\n"
"    // create the original triangle.\n"
"    gl_Position = gl_ModelViewProjectionMatrix * v1;\n"
"    gl_FrontColor = vec4(0.0, 1.0, 0.0, 0.0);\n"
"    EmitVertex();\n"
"    gl_Position = gl_ModelViewProjectionMatrix * v2;\n"
"    gl_FrontColor = vec4(0.0, 1.0, 0.0, 0.0);\n"
"    EmitVertex();\n"
"    gl_Position = gl_ModelViewProjectionMatrix * v3;\n"
"    gl_FrontColor = vec4(0.0, 1.0, 0.0, 0.0);\n"
"    EmitVertex();\n"
"    EndPrimitive();\n"
"\n"
"    vec3 l1n = l1.xyz;\n"
"    vec3 l2n = l2.xyz;\n"
"\n"
"    vec3 N = cross(l1n.xyz, l2n.xyz);\n"
"    N = normalize(N);\n"
"    vec4 middle = v1 + 0.333 * l1 + 0.333 * l2;\n"
"    // create the face normal triangle.\n"
"    gl_Position = gl_ModelViewProjectionMatrix * middle;\n"
"    gl_FrontColor = gl_TexCoordIn[0][0];\n"
"    EmitVertex();\n"
"    gl_FrontColor = gl_TexCoordIn[0][0];\n"
"    gl_Position = gl_ModelViewProjectionMatrix * (middle + 0.1 * vec4(N, 0.0));\n"
"    EmitVertex();\n"
"    gl_FrontColor = gl_TexCoordIn[0][0];\n"
"    gl_Position = gl_ModelViewProjectionMatrix * (middle + vec4(0.01,0.01,0.01,0.0));\n"
"    EmitVertex();\n"
"    EndPrimitive();\n"
"\n"
"}\n";

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        GLUTWindowRefPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->setSize( 800, 800 );
        gwin->init();
    
        // Create the shader material
        ChunkMaterialRefPtr cmat = ChunkMaterial::create();
    
        SHLChunkRefPtr shl = SHLChunk::create();
        shl->setProgramParameter(GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES_ADJACENCY_EXT);
        shl->setProgramParameter(GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLES);
        // ok we create a maximum of 6 vertices.
        shl->setProgramParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 6);

        shl->setVertexProgram(_vertex_shader);
        shl->setFragmentProgram(_fragment_shader);
        shl->setGeometryProgram(_geometry_shader);
    
        cmat->addChunk(shl);
    
        // create root node
        _scene = Node::create();
    
        // create torus
        GeometryRefPtr geo = makeTorusGeo(.8, 1.8, 32, 32);
        geo->setMaterial(cmat);
    
        NodeRefPtr torus = Node::create();
        torus->setCore(geo);
    
        // add torus to scene
        GroupRefPtr group = Group::create();
        _scene->setCore(group);
        _scene->addChild(torus);
    
        // create the SimpleSceneManager helper
        _mgr = new SimpleSceneManager;
    
        // tell the manager what to manage
        _mgr->setWindow(gwin );
        _mgr->setRoot(_scene);
    
        // show the whole scene
        _mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
  // render scene
  _mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q':
            // clean up global variables
            delete _mgr;
            _scene = NULL;
            
            osgExit();
            exit(1);
        break;
        case 'w':
            SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG GLSL Geometry Shader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}


