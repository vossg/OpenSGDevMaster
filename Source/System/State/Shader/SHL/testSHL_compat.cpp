// OpenSG example: testSHL
//
// Demonstrates the use of the SHLChunk
// Implements a simple bumpmapping via vertex and fragment shader.

// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>

#ifdef OSG_1_COMPAT

#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
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
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGSHLChunk.h>



// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static OSG::SimpleSceneManager *_mgr;
// The scene
static OSG::NodeRecPtr _scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    printf("Usage: testCGShader <filename.vp> <filename.fp>\n");

    if( argc < 3 )
        return 0;
    
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( 800, 800 );
    gwin->init();

    // Create the shader material
    OSG::ChunkMaterialUnrecPtr cmat = OSG::ChunkMaterial::create();

    OSG::MaterialChunkUnrecPtr matc = OSG::MaterialChunk::create();

    matc->setAmbient(OSG::Color4f(0.1, 0.1, 0.1, 1.0));
    matc->setDiffuse(OSG::Color4f(0.3, 0.3, 0.3, 1.0));
    matc->setSpecular(OSG::Color4f(0.8, 0.8, 0.8, 1.0));
    matc->setShininess(100);
    matc->setLit(true);

    OSG::SHLChunkUnrecPtr shl = OSG::SHLChunk::create();

    shl->readVertexProgram(argv[1]);
    shl->readFragmentProgram(argv[2]);

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

    /*
    // create point headlight
    _mgr->turnHeadlightOff();
    NodePtr headlight = _mgr->getHighlight();
    PointLightPtr light    = PointLight::create();
    beginEditCP(light);
        light->setAmbient  (.3, .3, .3, 1);
        light->setDiffuse  ( 1,  1,  1, 1);
        light->setSpecular ( 1,  1,  1, 1);
        light->setBeacon   (_mgr->getCamera()->getBeacon());
    endEditCP(light);
    beginEditCP(_scene);
        _scene->setCore(light);
    endEditCP(_scene);
    */

    // show the whole scene
    _mgr->showAll();

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
            delete _mgr;

            _scene = NULL;

            OSG::osgExit();
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

    int winid = glutCreateWindow("OpenSG CG Shader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

#else

int main(void)
{
    return 0;
}

#endif
