// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodeRecPtr          scene;
TransformRecPtr     planetTransform;
TransformRecPtr     moonTransform;

int setupGLUT(int *argc, char *argv[]);

NodeTransitPtr createScenegraph(void)
{
    //create sun, planet & moon geometry

    GeometryRecPtr sun    = makeSphereGeo(3, 6);
    NodeRecPtr     planet = makeSphere   (3, 3);
    NodeRecPtr     moon   = makeSphere   (2, 1);
    
    //the root node will be the sun
    NodeRecPtr root = Node::create();
    root->setCore(sun);
    
    NodeRecPtr planetTransformNode = Node::create();
    NodeRecPtr moonTransformNode   = Node::create();

    // these were declared globally
    planetTransform = Transform::create();
    moonTransform   = Transform::create();
    
    // Now we need to fill it with live
    // We want to have the planet some distance away from the sun, 
    // but initial with no rotation. The same aplies to the moon
    Matrix m,n;
    m.setIdentity();
    n.setIdentity();
    
    m.setTranslate(20, 0, 0);
    n.setTranslate( 8, 0, 0);
    
    planetTransform->setMatrix(m);
    moonTransform  ->setMatrix(n);
    
    //Insert the cores into the apropiate nodes and add the geometry
    planetTransformNode->setCore (planetTransform);
    planetTransformNode->addChild(planet         );

    moonTransformNode->setCore (moonTransform);
    moonTransformNode->addChild(moon         );
    
    //add the planet to the sun
    root->addChild(planetTransformNode);
    
    //add the moon to the planet
    planet->addChild(moonTransformNode);
    
    //now we are done
    return NodeTransitPtr(root);
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        GLUTWindowRecPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        scene = createScenegraph();
    
        mgr = new SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        commitChanges();
    }
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    Real32 time = glutGet(GLUT_ELAPSED_TIME );
    
    //create the Quaternion the describes the rotation of
    //the planet around the sun
    Quaternion planetRot = Quaternion(Vec3f(0,1,0), time/float(1000));
    
    //now the rotation of the moon around the planet
    //the division by 12 speeds up the rotation by 12 compared to the
    //planet rotation
    Quaternion moonRot = Quaternion(Vec3f(0,1,0), time/float(1000/12));
    
    //generate the Matrices
    Matrix p,m,t,r;
    
    t.setTransform(Vec3f(20,0,0));
    r.setTransform(planetRot);
    r.mult(t);
    p.setValue(r);
    
    t.setTransform(Vec3f(8,0,0));
    r.setTransform(moonRot);
    r.mult(t);
    m.setValue(r);

    planetTransform->setMatrix(p);
    moonTransform  ->setMatrix(m);
    
    mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    
    return winid;
}
