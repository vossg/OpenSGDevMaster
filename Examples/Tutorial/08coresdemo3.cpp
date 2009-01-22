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
#include <OpenSG/OSGComponentTransform.h>

OSG_USING_NAMESPACE

SimpleSceneManager      *mgr;
NodeRecPtr               scene;
ComponentTransformRecPtr ct;
UInt32 frame = 0;
// 0 = translation
// 1 = rotation
// 2 = scalation
UInt8 mode = 0;

int setupGLUT(int *argc, char *argv[]);


const char *getNodeName(Node const *node)
{
    if(node == NULL)
        return NULL;

    // get node name
    NameRecPtr nodename = dynamic_cast<Name *>(node->findAttachment(Name::getClassType()));

    // no node name, try core name
    if(nodename == NULL && node->getCore() != NULL)
        nodename = dynamic_cast<Name *>(node->getCore()->findAttachment(Name::getClassType()));

    if(nodename != NULL)
        return nodename->getFieldPtr()->getValue().c_str();
    else
    {
        if(node->getCore() != NULL)
            return node->getCore()->getType().getName().str();
    }

    return NULL;
}

// this function will return the node named "FACESET_Woman"
// if there is no such node NullFC will be returned
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
    
    //end witch creation **********************************
    
    NodeRecPtr root = Node::create();
    root->setCore(Group::create());
    root->addChild(switchNode);
    
    // we know want to extract the mesh geometry out of the graph
    // it is sufficent to pass the model only as root for searching
    NodeRecPtr womanGeometry = checkName(w_high);
    if(womanGeometry == NULL)
    {
        std::cout << "Couldn't find geometry node 'FACESET_Woman'!"
                  << std::endl;
        return NodeTransitPtr();
    }

    GeometryRecPtr geo = dynamic_cast<Geometry *>(womanGeometry->getCore());

    if(geo == NULL)
    {
        std::cout << "Node 'FACESET_Woman' is not a geometry node!"
                  << std::endl;
        return NodeTransitPtr();
    }

    // generating a material *********************************
    
    SimpleMaterialRecPtr mat = SimpleMaterial::create();
    mat->setAmbient(Color3f(0.2,0.2,0.2));
    mat->setDiffuse(Color3f(0.6,0.3,0.1));
    mat->setSpecular(Color3f(1,1,1));
    mat->setShininess(0.8);
    
    geo->setMaterial(mat);
    
    // end material generation *******************************
    
    //new node with "old" geometry core referenced
    NodeRecPtr woman = Node::create();
    woman->setCore(geo);
    
    /* the old transformation is not needed any longer
    //translate it a bit to see both women
    NodeRecPtr      womanTrans = Node::create();
    TransformRecPtr t          = Transform::create();
    Matrix m;
    m.setIdentity();
    m.setTranslate(Vec3f(0,0,200));
    t->setMatrix(m);

    womanTrans->setCore(t);
    womanTrans->addChild(woman);
    */
    
    // component transform ************************************
    NodeRecPtr ctNode = Node::create();
    
    //this one is declared globally
    ct = ComponentTransform::create();

    ct->setTranslation(Vec3f(0,0,200));
    ct->setScale(Vec3f(1,1,1));
    ct->setRotation(Quaternion(Vec3f(0,1,0),0));
    
    ctNode->setCore(ct);
    ctNode->addChild(woman);
    // end component transform ********************************
    
    //add it to the root
    root->addChild(ctNode);
    
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
        
        if(scene == NULL)
            return 1;
    
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
    frame++;
    Real32 time = glutGet(GLUT_ELAPSED_TIME);
    
    switch(mode)
    {
    case 0 :
        ct->setTranslation(Vec3f(0,cos(time/2000.f)*100,200));
        break;
    case 1 :
        ct->setRotation(Quaternion(Vec3f(0,1,0), time/2000));
        break;
    case 2 :
        ct->setScale(Vec3f(cos(time/2000), sin(time/2000), tan(time/2000)));
        break;
    }

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

void keyboard(unsigned char k, int x, int y){
    switch (k)
    {
    case 't' : mode = 0; break;
    case 'r' : mode = 1; break;
    case 's' : mode = 2; break;
    }
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
    glutKeyboardFunc(keyboard);
    
    return winid;
}
