#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGGroup.h"
#include "OSGSimpleMaterial.h"
#include "OSGTransform.h"
#include "OSGSimpleGeometry.h"
#include "OSGBaseFunctions.h"
#include "OSGSceneFileHandler.h"
#include "OSGTypedGeoIntegralProperty.h"

#include "OSGManipulatorManager.h"


OSG::NodeRefPtr         scene   = NULL;
OSG::TransformRefPtr    interTC = NULL;
OSG::NodeRefPtr         interN  = NULL;
OSG::NodeRefPtr         maniN   = NULL;

OSG::ManipulatorManager       *mama;
OSG::SimpleSceneManagerRefPtr  mgr;

int setupGLUT( int *argc, char *argv[] );
OSG::NodeTransitPtr makeCoordAxes(void);

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    int winid = setupGLUT(&argc, argv);

    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    mgr  = OSG::SimpleSceneManager::create();
    mama = new OSG::ManipulatorManager;

    OSG::GroupUnrecPtr g = OSG::Group::create();
    scene = OSG::Node::create();

    OSG::TransformUnrecPtr offsetTC   = OSG::Transform::create();
    OSG::NodeUnrecPtr      offsetN    = OSG::Node::create();

    OSG::Matrix m;
    m.setIdentity();
    m.setTransform( OSG::Vec3f(2,1,0), 
                    OSG::Quaternion(OSG::Vec3f(1,0,0), OSG::osgDegree2Rad(0)),
                    OSG::Vec3f(1,1,1) );
    offsetTC->setMatrix(m);
    offsetN->setCore(offsetTC);
   
    interTC = OSG::Transform::create();
    interN    = OSG::Node::create();

    m.setIdentity();
    m.setTransform( OSG::Vec3f(1.0f, 1.0f, 1.0f) );
    interTC->setMatrix(m);

    interN->setCore(interTC);
    interN->addChild(OSG::makeBox(1, 0.2f, 0.2f, 1, 1, 1));

    scene->setCore(g);
    scene->addChild(makeCoordAxes());
    scene->addChild(offsetN);
    offsetN->addChild(interN);

    maniN = mama->createManipulator(OSG::ManipulatorManager::TRANSLATE);

    interN->addChild(maniN);

    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->setClickCenter( false );
    mgr->showAll();

    mama->setTarget( interN );
    mama->setViewport( mgr->getWindow()->getPort(0) );

    OSG::commitChanges();

    glutReshapeWindow(600, 600);
    glutMainLoop();

    return 0;
}


void display(void)
{
    mgr->redraw();
}


void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
    if (state)
    {
        if( mama->isActive() )
        {
            mama->mouseButtonRelease(button, x, y);
        }

        mgr->mouseButtonRelease(button, x, y);
    }
    else
    {
        OSG::Line l;

        l = mgr->calcViewRay(x, y);

        OSG::IntersectActionRefPtr act = OSG::IntersectAction::create();

        act->setLine( l );
        act->apply( scene );

        if ( (act->didHit()) && (mama->activate( act->getHitObject()) ) )
        {
            mama->mouseButtonPress(button, x, y);
        }

        act = NULL;

        mgr->mouseButtonPress(button, x, y);
    }

    glutPostRedisplay();
}


void motion(int x, int y)
{
    if( mama->isActive() )
    {
        mama->mouseMove(x, y);
    }
    else
    {
        mgr->mouseMove(x, y);
    }

    glutPostRedisplay();
}


void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    
        delete mama;
        mgr     = NULL;
        scene   = NULL;
        interTC = NULL;
        interN  = NULL;
        maniN   = NULL;
        OSG::osgExit();
        exit(1);
    case ' ':
    {
        maniN->setTravMask(OSG::TypeTraits<OSG::UInt32>::getZeroElement());
        glutPostRedisplay();
        break;
    }
    case 'r':
    case 't':
    case 's':
    case 'p':
    case 'P':
    {
        maniN->setTravMask(OSG::TypeTraits<OSG::UInt32>::getMax());
        if (k == 't')
        {
            mama->changeManipulator(OSG::ManipulatorManager::TRANSLATE);
        }
        else if (k == 'r')
        {
            mama->changeManipulator(OSG::ManipulatorManager::ROTATE);
        }
        else if (k == 's')
        {
            mama->changeManipulator(OSG::ManipulatorManager::SCALE);
        }
        else if (k == 'p')
        {
            mama->changeManipulator(OSG::ManipulatorManager::PLANE);
        }
        else if (k == 'P')
        {
            mama->changeEnablePivot(! mama->getCurrentEnablePivot());
        }
        glutPostRedisplay();
        break;
    }
    case 'w':
        OSG::SceneFileHandler::the()->write(scene, "scene.osb");
    break;
    }
}


int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("Manipulator Demo");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

OSG::GeometryTransitPtr makeCoordAxesGeo(void)
{
    OSG::GeometryTransitPtr axesG = OSG::Geometry::create();

    OSG::GeoUInt8PropertyUnrecPtr type = OSG::GeoUInt8Property::create();
    type->addValue(GL_LINES    );
    type->addValue(GL_TRIANGLES);

    OSG::GeoUInt32PropertyUnrecPtr lens = OSG::GeoUInt32Property::create();
    lens->addValue(6);
    lens->addValue(9);

    OSG::GeoPnt3fPropertyUnrecPtr pnts = OSG::GeoPnt3fProperty::create();
    // the 6 points of the three Lines
    pnts->addValue(OSG::Pnt3f(0, 0, 0));
    pnts->addValue(OSG::Pnt3f(1, 0, 0));

    pnts->addValue(OSG::Pnt3f(0, 0, 0));
    pnts->addValue(OSG::Pnt3f(0, 1, 0));

    pnts->addValue(OSG::Pnt3f(0, 0, 0));
    pnts->addValue(OSG::Pnt3f(0, 0, 1));

    // the 9 points of the three Triangles
    pnts->addValue(OSG::Pnt3f(  1,    0,    0));
    pnts->addValue(OSG::Pnt3f(0.8f,  0.2f,  0.2f));
    pnts->addValue(OSG::Pnt3f(0.8f, -0.2f, -0.2f));

    pnts->addValue(OSG::Pnt3f(   0,   1,    0));
    pnts->addValue(OSG::Pnt3f( 0.2f, 0.8f,  0.2f));
    pnts->addValue(OSG::Pnt3f(-0.2f, 0.8f, -0.2f));

    pnts->addValue(OSG::Pnt3f(   0,    0,   1));
    pnts->addValue(OSG::Pnt3f( 0.2f,  0.2f, 0.8f));
    pnts->addValue(OSG::Pnt3f(-0.2f, -0.2f, 0.8f));

    OSG::GeoColor3fPropertyUnrecPtr colors = OSG::GeoColor3fProperty::create();
    colors->addValue(OSG::Color3f(1, 0, 0));
    colors->addValue(OSG::Color3f(1, 0, 0));

    colors->addValue(OSG::Color3f(0, 1, 0));
    colors->addValue(OSG::Color3f(0, 1, 0));

    colors->addValue(OSG::Color3f(0, 0, 1));
    colors->addValue(OSG::Color3f(0, 0, 1));

    colors->addValue(OSG::Color3f(1, 0, 0));
    colors->addValue(OSG::Color3f(1, 0, 0));
    colors->addValue(OSG::Color3f(1, 0, 0));

    colors->addValue(OSG::Color3f(0, 1, 0));
    colors->addValue(OSG::Color3f(0, 1, 0));
    colors->addValue(OSG::Color3f(0, 1, 0));

    colors->addValue(OSG::Color3f(0, 0, 1));
    colors->addValue(OSG::Color3f(0, 0, 1));
    colors->addValue(OSG::Color3f(0, 0, 1));

    axesG->setTypes    (type);
    axesG->setLengths  (lens);
    axesG->setPositions(pnts);
    axesG->setColors   (colors);
    axesG->setMaterial (OSG::getDefaultUnlitMaterial());

    return axesG;
}

OSG::NodeTransitPtr makeCoordAxes(void)
{
    OSG::NodeTransitPtr axesN = OSG::Node::create();

    axesN->setCore(makeCoordAxesGeo());

    return axesN;
}
