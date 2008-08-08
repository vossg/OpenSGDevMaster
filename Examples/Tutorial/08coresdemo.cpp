// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

//additional headder files
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDistanceLOD.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodeRecPtr          scene;

int setupGLUT(int *argc, char *argv[]);

NodeTransitPtr createScenegraph(void)
{
    //At first we load all needed models from file
    NodeRecPtr w_high   = SceneFileHandler::the()->read("Data/woman_high.wrl");
    NodeRecPtr w_medium = SceneFileHandler::the()->read("Data/woman_medium.wrl");
    NodeRecPtr w_low    = SceneFileHandler::the()->read("Data/woman_low.wrl");
    
    //we check the result
    if((w_high == NULL) || (w_medium == NULL)|| (w_low == NULL))
    {
        std::cout << "It was not possible to load all needed models from file"
                  << std::endl;
        return NodeTransitPtr();
    }
    
    //now the LOD core
    DistanceLODRecPtr lod = DistanceLOD::create();
    lod->editSFCenter()->setValue(Pnt3f(0,0,0));
    lod->editMFRange()->push_back(200);
    lod->editMFRange()->push_back(500);
    
    //the node containing the LOD core. The three models will be
    //added as its children
    NodeRecPtr lodNode = Node::create();
    lodNode->setCore(lod);
    lodNode->addChild(w_high);
    lodNode->addChild(w_medium);
    lodNode->addChild(w_low);
    
    NodeRecPtr root = Node::create();
    root->setCore (Group::create());
    root->addChild(lodNode);
    
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
