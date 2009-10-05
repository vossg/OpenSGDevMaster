// OpenSG example: testSHL
//
// Demonstrates the use of the SHLChunk
// Implements a simple bumpmapping via vertex and fragment shader.

// Headers
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUT.h"
#include "OSGGLEXT.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGBaseFunctions.h"

#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGPointLight.h"

#include "OSGImage.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGSHLChunk.h"



// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static OSG::SimpleSceneManager *_mgr;
// The scene
static OSG::NodeRecPtr _scene;

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
int doMain(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( 800, 800 );
    gwin->init();

    // Create the shader material
    OSG::ChunkMaterialUnrecPtr cmat = OSG::ChunkMaterial::create();

    OSG::SHLChunkUnrecPtr shl = OSG::SHLChunk::create();

    shl->setProgramParameter(GL_GEOMETRY_INPUT_TYPE_EXT, 
                             GL_TRIANGLES);
    shl->setProgramParameter(GL_GEOMETRY_OUTPUT_TYPE_EXT, 
                             GL_TRIANGLE_STRIP);
    shl->setProgramParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 6);

    shl->setVertexProgram(_vertex_shader);
    shl->setFragmentProgram(_fragment_shader);
    shl->setGeometryProgram(_geometry_shader);

    cmat->addChunk(shl);

    // create root node
    _scene = OSG::Node::create();

    // create torus
    OSG::GeometryUnrecPtr geo = OSG::makeTorusGeo(.8, 1.8, 128, 128);

    geo->setMaterial(cmat);

    OSG::NodeUnrecPtr torus = OSG::Node::create();

    torus->setCore(geo);

    // add torus to scene
    OSG::GroupUnrecPtr group = OSG::Group::create();

    _scene->setCore(group);
    _scene->addChild(torus);

    // create the SimpleSceneManager helper
    _mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

    return 0;
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    if(doMain(argc, argv) != 0)
        return 1;
    
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

            _scene = NULL;
            delete _mgr;

            exit(1);
        break;
        case 'w':
            OSG::SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
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


