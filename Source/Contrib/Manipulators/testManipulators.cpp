#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGGroup.h>
#include <OSGSimpleMaterial.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>
#include <OSGBaseFunctions.h>
#include <OSGSceneFileHandler.h>
#include <OSGTypedGeoIntegralProperty.h>

#include "OSGManipulatorManager.h"

OSG_USING_NAMESPACE

NodePtr         scene   = NullFC;
TransformPtr    interTC = NullFC;
NodePtr         interN  = NullFC;
NodePtr         maniN   = NullFC;

ManipulatorManager *mama;
SimpleSceneManager *mgr;

int setupGLUT( int *argc, char *argv[] );
NodePtr makeCoordAxes(void);

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    int winid = setupGLUT(&argc, argv);

    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    mgr = new SimpleSceneManager;
    mama = new ManipulatorManager;

    GroupPtr g = Group::create();
    scene = Node::create();

    interTC = Transform::create();
    interN    = Node::create();

    Matrix m;
    m.setIdentity();
    m.setTransform( Vec3f(1.0f, 1.0f, 1.0f) );
    interTC->setMatrix(m);

    interN->setCore(interTC);
    interN->addChild(makeBox(1, 0.2, 0.2, 1, 1, 1));

    scene->setCore(g);
    scene->addChild(makeCoordAxes());
    scene->addChild(interN);

    maniN = mama->createManipulator(ManipulatorManager::TRANSLATE);

    interN->addChild(maniN);

    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->setClickCenter( false );
    mgr->showAll();

    mama->setTarget( interN );
    mama->setViewport( mgr->getWindow()->getPort()[0] );

    commitChanges();

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
        Line l;

        l = mgr->calcViewRay(x, y);

        IntersectAction *act = IntersectAction::create();

        act->setLine( l );
        act->apply( scene );

        if ( (act->didHit()) && (mama->activate( act->getHitObject()) ) )
        {
            mama->mouseButtonPress(button, x, y);
        }

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
    case 27:    exit(1);
    case ' ':
    {
        maniN->setTravMask(TypeTraits<UInt32>::getZeroElement());
        glutPostRedisplay();
        break;
    }
    case 'r':
    case 't':
    case 's':
    {
        maniN->setTravMask(TypeTraits<UInt32>::getMax());
        if (k == 't')
        {
            mama->changeManipulator(ManipulatorManager::TRANSLATE);
        }
        else if (k == 'r')
        {
            mama->changeManipulator(ManipulatorManager::ROTATE);
        }
        else if (k == 's')
        {
            mama->changeManipulator(ManipulatorManager::SCALE);
        }
        glutPostRedisplay();
        break;
    }
    case 'w':
        SceneFileHandler::the()->write(scene, "scene.osb");
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

GeometryPtr makeCoordAxesGeo(void)
{
    GeometryPtr axesG = Geometry::create();

    GeoUInt8PropertyPtr type = GeoUInt8Property::create();
    type->addValue(GL_LINES    );
    type->addValue(GL_TRIANGLES);

    GeoUInt32PropertyPtr lens = GeoUInt32Property::create();
    lens->addValue(6);
    lens->addValue(9);

    GeoPnt3fPropertyPtr pnts = GeoPnt3fProperty::create();
    // the 6 points of the three Lines
    pnts->addValue(Pnt3f(0, 0, 0));
    pnts->addValue(Pnt3f(1, 0, 0));

    pnts->addValue(Pnt3f(0, 0, 0));
    pnts->addValue(Pnt3f(0, 1, 0));

    pnts->addValue(Pnt3f(0, 0, 0));
    pnts->addValue(Pnt3f(0, 0, 1));

    // the 9 points of the three Triangles
    pnts->addValue(Pnt3f(  1,    0,    0));
    pnts->addValue(Pnt3f(0.8,  0.2,  0.2));
    pnts->addValue(Pnt3f(0.8, -0.2, -0.2));

    pnts->addValue(Pnt3f(   0,   1,    0));
    pnts->addValue(Pnt3f( 0.2, 0.8,  0.2));
    pnts->addValue(Pnt3f(-0.2, 0.8, -0.2));

    pnts->addValue(Pnt3f(   0,    0,   1));
    pnts->addValue(Pnt3f( 0.2,  0.2, 0.8));
    pnts->addValue(Pnt3f(-0.2, -0.2, 0.8));

    GeoColor3fPropertyPtr colors = GeoColor3fProperty::create();
    colors->addValue(Color3f(1, 0, 0));
    colors->addValue(Color3f(1, 0, 0));

    colors->addValue(Color3f(0, 1, 0));
    colors->addValue(Color3f(0, 1, 0));

    colors->addValue(Color3f(0, 0, 1));
    colors->addValue(Color3f(0, 0, 1));

    colors->addValue(Color3f(1, 0, 0));
    colors->addValue(Color3f(1, 0, 0));
    colors->addValue(Color3f(1, 0, 0));

    colors->addValue(Color3f(0, 1, 0));
    colors->addValue(Color3f(0, 1, 0));
    colors->addValue(Color3f(0, 1, 0));

    colors->addValue(Color3f(0, 0, 1));
    colors->addValue(Color3f(0, 0, 1));
    colors->addValue(Color3f(0, 0, 1));

    axesG->setTypes    (type);
    axesG->setLengths  (lens);
    axesG->setPositions(pnts);
    axesG->setColors   (colors);
    axesG->setMaterial (getDefaultUnlitMaterial());

    return axesG;
}

NodePtr makeCoordAxes(void)
{
    NodePtr axesN = Node::create();

    axesN->setCore(makeCoordAxesGeo());

    return axesN;
}
