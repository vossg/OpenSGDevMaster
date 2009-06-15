// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGMaterialGroup.h>

OSG::SimpleSceneManager *mgr;
OSG::NodeRecPtr          scene;

int setupGLUT(int *argc, char *argv[]);

OSG::NodeTransitPtr createScenegraph(void)
{
    OSG::SimpleMaterialRecPtr simpleMaterial = OSG::SimpleMaterial::create();
    simpleMaterial->setDiffuse(OSG::Color3f(1,0,0));
    simpleMaterial->setAmbient(OSG::Color3f(0.2, 0.2, 0.2));
    simpleMaterial->setTransparency(0.5);
    
    OSG::NodeRecPtr simpleMaterialNode = OSG::Node::create();
    OSG::NodeRecPtr sphere = OSG::makeSphere(2,6);
    
    OSG::MaterialGroupRecPtr mg = OSG::MaterialGroup::create();
    mg->setMaterial(simpleMaterial);
    
    simpleMaterialNode->setCore(mg);
    simpleMaterialNode->addChild(sphere);
    
    OSG::NodeRecPtr root = OSG::Node::create();
    
    root->setCore(OSG::Group::create());
    root->addChild(simpleMaterialNode);
    
    return OSG::NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
        
        scene = createScenegraph();
        
        mgr = new OSG::SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        OSG::commitChanges();
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
