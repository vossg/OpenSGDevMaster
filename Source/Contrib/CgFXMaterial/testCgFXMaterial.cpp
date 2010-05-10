// OpenSG example: testCGShader
//
// Demonstrates the use of the CGChunk
// Implements a simple bumpmapping via vertex and fragment cg shader.

// Headers
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUT.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGBaseFunctions.h"
#include "OSGGradientBackground.h"
#include "OSGGeoFunctions.h"

#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGPointLight.h"

#include "OSGImage.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGCgFXMaterial.h"

void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char k, int x, int y);


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static OSG::SimpleSceneManager  *_mgr = NULL;

static OSG::GLUTWindowUnrecPtr   _gwin = NULL;

// The scene
static OSG::NodeUnrecPtr         _scene   = NULL;
static OSG::CgFXMaterialUnrecPtr _cgfxmat = NULL;

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc, argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG CGFX Shader");

    // the connection between GLUT and OpenSG
    _gwin = OSG::GLUTWindow::create();

    _gwin->setGlutId(winid);
    _gwin->setSize( 800, 800 );
    _gwin->init();

    // init callbacks
    glutSetWindow(winid);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    const char *effectFile = "blinn_bump_reflect.vinstruct.cgfx";

    if(argc > 1)
    {
        effectFile = argv[1];
    }

    _cgfxmat = OSG::CgFXMaterial::create();

    _cgfxmat->setEffectFile(effectFile);

    // this multipass technique leads to a render bug, 
    // I have no idea what's wrong :-(
    //_cgfxmat->setTechnique(1);

    OSG::ChunkMaterialUnrecPtr mat2 = OSG::ChunkMaterial::create();
    OSG::MaterialChunkUnrecPtr matc = OSG::MaterialChunk::create();

    matc->setDiffuse(OSG::Color4f(1, 0, 0, 1));
    mat2->addChunk(matc);
    //mat2->addChunk(texc);

    // create root node
    _scene = OSG::Node::create();

    OSG::GeometryUnrecPtr geo1 = OSG::makeLatLongSphereGeo(50, 50, 2.0f);
    
    OSG::calcVertexTangents(geo1, 
                            0, 
                            OSG::Geometry::TexCoords6Index, 
                            OSG::Geometry::TexCoords7Index);

    geo1->setMaterial(_cgfxmat);

    OSG::NodeUnrecPtr sphere1 = OSG::Node::create();

    sphere1->setCore(geo1);

    OSG::TransformUnrecPtr trans1 = OSG::Transform::create();

    trans1->editMatrix().setTranslate(-2 , 0, 0);

    OSG::NodeUnrecPtr transn1 = OSG::Node::create();

    transn1->setCore(trans1);
    transn1->addChild(sphere1);

    //
    OSG::GeometryUnrecPtr geo2 = OSG::makeLatLongSphereGeo(50, 50, 1.0f);
    
    geo2->setMaterial(mat2);


    OSG::NodeUnrecPtr sphere2 = OSG::Node::create();

    sphere2->setCore(geo2);

    OSG::TransformUnrecPtr trans2 = OSG::Transform::create();

    trans2->editMatrix().setTranslate(2 , 0, 0);


    OSG::NodeUnrecPtr transn2 = OSG::Node::create();

    transn2->setCore(trans2);
    transn2->addChild(sphere2);

    _scene->setCore (OSG::Group::create());
    _scene->addChild(transn1             );
    _scene->addChild(transn2             );

    // create the SimpleSceneManager
    _mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(_gwin);

    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

    // create a gradient background.
    OSG::GradientBackgroundUnrecPtr gback = OSG::GradientBackground::create();

    gback->clearLines();
    gback->addLine(OSG::Color3f(0.7, 0.7, 0.8), 0);
    gback->addLine(OSG::Color3f(0.0, 0.1, 0.3), 1);

    OSG::Window *win = _mgr->getWindow();

    for(OSG::UInt32 i = 0; i < win->getMFPort()->size(); ++i)
    {
        OSG::Viewport *vp = win->getPort(i);

        vp->setBackground(gback);
    }

    return 0;
}

int main(int argc, char **argv)
{
    doMain(argc, argv);

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
#ifdef CHECK
    OSG::Real32 bumpHeight;
#endif

    switch(k)
    {
        case 27:
        case 'q':
        
            glutDestroyWindow(glutGetWindow());

            _gwin    = NULL;
            _scene   = NULL;
            _cgfxmat = NULL;

            delete _mgr;
            
            OSG::osgExit();
            exit(0);

        break;

        case 'R':
            if(_cgfxmat != NULL)
            {
                // reload cgfx material.
                _cgfxmat->setEffectFile(_cgfxmat->getEffectFile());
            }
        break;

        case 'w':
            OSG::SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;

        case 'e':
            OSG::SceneFileHandler::the()->write(_scene, "scene.osg");
            printf("wrote scene.osg\n");
        break;

        case 'r':
        {
            OSG::Vec3f fCol(1.f, 0.f, 0.f);

            fprintf(stderr, "red\n");

            _cgfxmat->updateUniformVariable("Color", fCol);
        }
        break;
        case 'g':
        {
            OSG::Vec3f fCol(0.f, 1.f, 0.f);

            fprintf(stderr, "green\n");

            _cgfxmat->updateUniformVariable("Color", fCol);
        }
        break;
        case 'b':
        {
            OSG::Vec3f fCol(0.f, 0.f, 1.f);

            fprintf(stderr, "blue\n");

            _cgfxmat->updateUniformVariable("Color", fCol);
        }
        break;
#ifdef CHECK
        case 'b':
            if(_cgfxmat != NULL && 
               _cgfxmat->getParameter("bumpHeight", bumpHeight))
            {
                bumpHeight += 0.1;

                _cgfxmat->setParameter("bumpHeight", bumpHeight);

                glutPostRedisplay();
            }
            break;

        case 'n':
            if(_cgfxmat != NULL && 
               _cgfxmat->getParameter("bumpHeight", bumpHeight))
            {
                bumpHeight -= 0.1;

                _cgfxmat->setParameter("bumpHeight", bumpHeight);

                glutPostRedisplay();
            }
        break;
#endif

        case 't':
            if(_cgfxmat != NULL)
            {
#ifdef CHECK
                OSG::Int32 technique = _cgfxmat->getTechnique();
                technique = 1 - technique;

                printf("setting technique to '%s'\n", 
                       _cgfxmat->getTechniqueString(technique).c_str());

                _cgfxmat->setTechnique(technique);
#endif

                glutPostRedisplay();
            }
        break;
    }

    glutPostRedisplay();
}
