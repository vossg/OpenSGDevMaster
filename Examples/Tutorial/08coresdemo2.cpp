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
#include <OpenSG/OSGNameAttachment.h>

OSG::SimpleSceneManager *mgr;
OSG::NodeRecPtr          scene;

int setupGLUT( int *argc, char *argv[] );

// this function will return the node named "FACESET_Woman"
// if there is no such node NullFC will be returned
OSG::Node *checkName(OSG::Node *n)
{
    OSG::UInt32 children = n->getNChildren();
    
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
        OSG::Node *r = checkName(n->getChild(i));
        if(r != NULL)
            // if it is not NULL it is the node we are looking for
            // so just pass it through
            return r;
    }
    
    // no children's name matches or there are no more childs
    // so return NULL, indicating that the node was not found yet
    return NULL;
}

OSG::NodeTransitPtr createScenegraph(void)
{
    // At first we load all needed models from file
    OSG::NodeRecPtr w_high   = 
        OSG::SceneFileHandler::the()->read("Data/woman_high.wrl");

    OSG::NodeRecPtr w_medium = 
        OSG::SceneFileHandler::the()->read("Data/woman_medium.wrl");

    OSG::NodeRecPtr w_low    = 
        OSG::SceneFileHandler::the()->read("Data/woman_low.wrl");
    
    // we check the result
    if((w_high == NULL) || (w_medium == NULL)|| (w_low == NULL))
    {
        std::cout << "It was not possible to load all needed models from file"
                << std::endl;
        return OSG::NodeTransitPtr();
    }
    
    // now the LOD core
    OSG::DistanceLODRecPtr lod = OSG::DistanceLOD::create();
    lod->editSFCenter()->setValue(OSG::Pnt3f(0,0,0));
    lod->editMFRange()->push_back(200);
    lod->editMFRange()->push_back(500);
    
    // the node containing the LOD core. The three models will be
    // added as its children
    OSG::NodeRecPtr lodNode = OSG::Node::create();
    lodNode->setCore(lod);
    lodNode->addChild(w_high);
    lodNode->addChild(w_medium);
    lodNode->addChild(w_low);
    
    // create the node with switch core ********************
    OSG::SwitchRecPtr sw = OSG::Switch::create();
    //Notice: the first choice is 0
    sw->setChoice(0);
    
    OSG::NodeRecPtr switchNode = OSG::Node::create();
    switchNode->setCore(sw);
    switchNode->addChild(lodNode);
    
    //end switch creation **********************************
    
    OSG::NodeRecPtr root = OSG::Node::create();
    root->setCore(OSG::Group::create());
    root->addChild(switchNode);
    
    // we know want to extract the mesh geometry out of the graph
    // it is sufficent to pass the model only as root for searching
    OSG::NodeRecPtr     womanGeometry = checkName(w_high);
    OSG::GeometryRecPtr geo;
    if(womanGeometry !=NULL)
    {
        geo = dynamic_cast<OSG::Geometry *>(womanGeometry->getCore());
        if (geo == NULL)
            std::cout << "Casting failed!" << std::endl;
    }
    else
    {
        std::cout << "No correct geometry node found!" << std::endl;
        //create a dummy object
        geo = OSG::makeBoxGeo(0.5,0.5,0.5,1,1,1);
    }
    
    // generating a material *********************************
    
    OSG::SimpleMaterialRecPtr mat = OSG::SimpleMaterial::create();
    mat->setAmbient(OSG::Color3f(0.2,0.2,0.2));
    mat->setDiffuse(OSG::Color3f(0.6,0.3,0.1));
    mat->setSpecular(OSG::Color3f(1,1,1));
    mat->setShininess(0.8);
    
    geo->setMaterial(mat);
    
    // end material generation *******************************
    
    //new node with "old" geometry core referenced
    OSG::NodeRecPtr woman = OSG::Node::create();
    woman->setCore(geo);
    
    //translate it a bit to see both women
    OSG::NodeRecPtr      womanTrans = OSG::Node::create();
    OSG::TransformRecPtr t          = OSG::Transform::create();
    
    OSG::Matrix m;
    m.setIdentity();
    m.setTranslate(OSG::Vec3f(0,0,200));
    t->setMatrix(m);

    womanTrans->setCore(t);
    womanTrans->addChild(woman);
    
    //add it to the root
    root->addChild(womanTrans);
    
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
