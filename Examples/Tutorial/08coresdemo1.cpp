// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

//additional headder files
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDistanceLOD.h>
#include <OpenSG/OSGSwitch.h>
#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodeRecPtr          scene;

int setupGLUT(int *argc, char *argv[]);

// this function will return the node named "FACESET_Woman"
// if there is no such node NULL will be returned
Node *checkName(Node *n)
{
    UInt32 children = n->getNChildren();
    
    //make sure a name existes
    if (getName(n))
    {
        //check if it is the name we are looking for
        if (getName(n)== std::string("FACESET_Woman"))
            // We got the node!
            return n;
    }
    
    //check all children
    for(int i = 0; i < children; i++)
    {
        Node *r = checkName(n->getChild(i));
        if(r != NULL)
            // if it is not NULL it is the node we are looking for
            // so just pass it through
            return r;
    }
    
    // no children's name matches or there are no more childs
    // so return NULL, indicating that the node was not found yet
    return NULL;
}

NodeTransitPtr createScenegraph(void)
{
    // At first we load all needed models from file
    NodeRecPtr w_high   = SceneFileHandler::the()->read("Data/woman_high.wrl");
    NodeRecPtr w_medium = SceneFileHandler::the()->read("Data/woman_medium.wrl");
    NodeRecPtr w_low    = SceneFileHandler::the()->read("Data/woman_low.wrl");
    
    // we check the result
    if((w_high == NULL) || (w_medium == NULL)|| (w_low == NULL))
    {
        std::cout << "It was not possible to load all needed models from file"
                << std::endl;
        return NodeTransitPtr();
    }
    
    // now the LOD core
    DistanceLODRecPtr lod = DistanceLOD::create();
    lod->editSFCenter()->setValue(Pnt3f(0,0,0));
    lod->editMFRange()->push_back(200);
    lod->editMFRange()->push_back(500);
    
    // the node containing the LOD core. The three models will be
    // added as its children
    NodeRecPtr lodNode = Node::create();
    lodNode->setCore(lod);
    lodNode->addChild(w_high);
    lodNode->addChild(w_medium);
    lodNode->addChild(w_low);
    
    // create the node with switch core ********************
    SwitchRecPtr sw = Switch::create();
    //Notice: the first choice is 0
    sw->setChoice(0);
    
    NodeRecPtr switchNode = Node::create();
    switchNode->setCore(sw);
    switchNode->addChild(lodNode);
    
    //end switch creation **********************************
    
    NodeRecPtr root = Node::create();
    root->setCore(Group::create());
    root->addChild(switchNode);
    
    // we know want to extract the mesh geometry out of the graph
    // it is sufficent to pass the model only as root for searching
    NodeRecPtr     womanGeometry = checkName(w_high);
    GeometryRecPtr geo = dynamic_cast<Geometry *>(womanGeometry->getCore());
    
    //new node with "old" geometry core referenced
    NodeRecPtr woman = Node::create();
    woman->setCore(geo);
    
    //translate it a bit to see both women
    NodeRecPtr      womanTrans = Node     ::create();
    TransformRecPtr t          = Transform::create();
    Matrix m;
    m.setIdentity();
    m.setTranslate(Vec3f(0,0,200));
    t->setMatrix(m);
        
    womanTrans->setCore(t);
    womanTrans->addChild(woman);
    
    //add it to the root
    root->addChild(womanTrans);
    
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
