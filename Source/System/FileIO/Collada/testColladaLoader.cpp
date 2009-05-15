// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>

// New Headers

// the general scene file loading handler
#include <OSGSceneFileHandler.h>

#include <OSGFieldContainerUtils.h>
#include <OSGChunkOverrideGroup.h>
#include <OSGPolygonChunk.h>
#include <OSGGeoFunctions.h>


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager           *mgr;
OSG::NodeUnrecPtr                  sceneN;
OSG::NodeUnrecPtr                  rootN;
OSG::ChunkOverrideGroupUnrecPtr    root;
OSG::PolygonChunkUnrecPtr          polyChunk;

std::vector<OSG::NodeUnrecPtr>   normalsGeoN;
std::vector<OSG::NodeUnrecPtr>   geoN;
bool                             normalsActive = false;
OSG::Real32                      normalsLen    = 1.f;


// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void init     (int argc, char *argv[]);
void cleanup  (void);
void printHelp(void);
void constructNormalsGeo(OSG::Node *rootN);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char *argv[])
{
    init(argc, argv);

    // GLUT main loop
    glutMainLoop();

    cleanup();
    OSG::osgExit();

    return 0;
}

void init(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);

    int glutWinId = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(glutWinId);
    gwin->init();
    
    // load the scene
    root  = OSG::ChunkOverrideGroup::create();
    rootN = OSG::makeNodeFor(root);
        
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
            
        OSG::SceneFileHandler::the()->print();
        sceneN = OSG::makeTorus(.5, 2, 16, 16);
    }
    else
    {
        /*
          All scene file loading is handled via the SceneFileHandler.
        */
        sceneN = OSG::SceneFileHandler::the()->read(argv[1]);
    }

    rootN->addChild(sceneN);

    OSG::commitChanges();
    
    // create the SimpleSceneManager helper
    mgr = new OSG::SimpleSceneManager;
    
    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (rootN);
    
    // show the whole scene
    mgr->showAll();  
}

void cleanup(void)
{
    delete mgr;
    mgr = NULL;

    sceneN    = NULL;
    rootN     = NULL;
    root      = NULL;
    polyChunk = NULL;

    normalsGeoN.clear();
    geoN       .clear();
}

void printHelp(void)
{
    std::cout << "Keys:\n"
              << "  ESC      exit\n"
              << "  f        fly mode\n"
              << "  t        trackball mode\n"
              << "  q        toggle statistics\n"
              << "  h        toggle headlight\n"
              << "  b        toggle backface culling\n"
              << "  w        toggle wireframe\n"
              << "  n        toggle normals\n"
              << "  m/M      de/increase normals length\n"
              << "  v        toggle bounding volumes\n"
              << "  p        print scene graph\n"
              << std::flush;
}

OSG::Action::ResultE doConstructNormals(OSG::Node *node)
{
    if(node == NULL)
    {
        std::cerr << "WARNING: doConstructNormals called with node == NULL"
                  << std::endl;
        return OSG::Action::Continue;
    }

    if(node->getCore() == NULL)
    {
        std::cerr << "WARNING: doConstructNormals called with core == NULL"
                  << std::endl;
        return OSG::Action::Continue;
    }
    
    if(node->getCore()->getType() == OSG::Geometry::getClassType())
    {
        OSG::Geometry *geo = dynamic_cast<OSG::Geometry *>(node->getCore());

        OSG::NodeUnrecPtr normN = OSG::calcVertexNormalsGeo(geo, normalsLen);

        normalsGeoN.push_back(normN);
        geoN       .push_back(node );
    }

    return OSG::Action::Continue;
}

void constructNormalsGeo(OSG::Node *rootN)
{
    std::vector<OSG::NodeUnrecPtr>::const_iterator nIt  = normalsGeoN.begin();
    std::vector<OSG::NodeUnrecPtr>::const_iterator nEnd = normalsGeoN.end  ();

    for(; nIt != nEnd; ++nIt)
        (*nIt)->getParent()->subChild(*nIt);

    normalsGeoN.clear();
    geoN       .clear();

    OSG::traverse(rootN, &doConstructNormals);

    nIt  = normalsGeoN.begin();
    nEnd = normalsGeoN.end  ();

    for(OSG::UInt32 i = 0; nIt != nEnd; ++nIt, ++i)
        geoN[i]->addChild(*nIt);
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->idle();
    mgr->redraw();
    OSG::Thread::getCurrentChangeList()->clear();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{

    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{

    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:
    {
        cleanup();

        OSG::osgExit();
        std::exit(0);
    }
    break;
    case 'f':
    {
        mgr->setNavigationMode(OSG::Navigator::FLY);
        std::cout << "Fly mode" << std::endl;
    }
    break;
    case 't':
    {
        mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        std::cout << "Trackball mode" << std::endl;
    }
    break;
    case 'q':
    {
        mgr->setStatistics(!mgr->getStatistics());
        std::cout << "Statistics " 
                  << (mgr->getStatistics() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'h':
    {
        mgr->setHeadlight(!mgr->getHeadlightState());
        std::cout << "Headlight "
                  << (mgr->getHeadlightState() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'b':
    {
        if(polyChunk == NULL)
        {
            polyChunk = OSG::PolygonChunk::create();
            root->addChunk(polyChunk);
        }
  
        if(polyChunk->getCullFace() == GL_NONE)
        {
            polyChunk->setCullFace(GL_BACK);
            std::cout << "Backface culling enabled" << std::endl;
        }
        else
        {
            polyChunk->setCullFace(GL_NONE);
            std::cout << "Backface culling disabled" << std::endl;
        }
    }
    break;
    case 'w':
    {
        if(polyChunk == NULL)
        {
            polyChunk = OSG::PolygonChunk::create();
            root->addChunk(polyChunk);
        }

        if(polyChunk->getFrontMode() == GL_FILL)
        {
            polyChunk->setFrontMode(GL_LINE);
            polyChunk->setBackMode (GL_LINE);
            std::cout << "Wireframe enabled" << std::endl;
        }
        else
        {
            polyChunk->setFrontMode(GL_FILL);
            polyChunk->setBackMode (GL_FILL);
            std::cout << "Wireframe disabled" << std::endl;
        }
    }
    break;
    case 'n':
    {
        if(normalsActive == true)
        {
            normalsActive = false;

            std::vector<OSG::NodeUnrecPtr>::const_iterator ngIt  =
                normalsGeoN.begin();
            std::vector<OSG::NodeUnrecPtr>::const_iterator ngEnd =
                normalsGeoN.end  ();

            for(; ngIt != ngEnd; ++ngIt)
            {
                (*ngIt)->setTravMask(0);
            }
            
            std::cout << "Normals disabled" << std::endl;
        }
        else
        {
            normalsActive = true;

            if(normalsGeoN.empty() == true)
                constructNormalsGeo(sceneN);

            std::vector<OSG::NodeUnrecPtr>::const_iterator ngIt  =
                normalsGeoN.begin();
            std::vector<OSG::NodeUnrecPtr>::const_iterator ngEnd =
                normalsGeoN.end  ();

            for(; ngIt != ngEnd; ++ngIt)
            {
                (*ngIt)->setTravMask(OSG::TypeTraits<OSG::UInt32>::BitsSet);
            }

            std::cout << "Normals enabled" << std::endl;
        }
    }
    break;
    case 'm':
    {
        normalsLen /= 1.25f;
        constructNormalsGeo(sceneN);
        std::cout << "Normals length " << normalsLen << std::endl;
    }
    break;
    case 'M':
    {
        normalsLen *= 1.25f;
        constructNormalsGeo(sceneN);
        std::cout << "Normals length " << normalsLen << std::endl;
    }
    break;
    case 'v':
    {
        mgr->getRenderAction()->setVolumeDrawing(
            !mgr->getRenderAction()->getVolumeDrawing());
        std::cout << "Volume drawing: "
                  << (mgr->getRenderAction()->getVolumeDrawing() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'p':
    {
        OSG::SceneGraphPrinter sgp(mgr->getRoot());
        sgp.printDownTree(std::cout);
    }
    break;

    default:
    {
        printHelp();
    }
    break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
