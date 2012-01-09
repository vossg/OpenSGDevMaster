
#include "OSGAction.h"
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"
#include "OSGGeoOptimization.h"

#include <deque>

OSG::SimpleSceneManagerRefPtr mgr;
OSG::NodeUnrecPtr             scene;
std::string                   fileName;
OSG::Time                     startT;
OSG::Time                     endT;
std::deque<OSG::Time>         timeHistory;
OSG::Time                     avgT = 0.0;
bool                          showFrameTime = false;

int setupGLUT(int *argc, char *argv[]);
void doInit(int argc, char *argv[]);

void doPrintGeoInfo           (OSG::Node *scene);
void doMakeSingleIndexed      (OSG::Node *scene);
void doMakeIndexedTriangles   (OSG::Node *scene);
void doMakeOptimizedIndex     (OSG::Node *scene);
void doMakeOptimizedProperties(OSG::Node *scene);

std::ostream &
printTypes(std::ostream &os, OSG::GeoIntegralProperty *types);
std::ostream &
printGeoInfo(std::ostream &os, OSG::Geometry *geo);


int main(int argc, char *argv[])
{
    doInit(argc, argv);

    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    startT = OSG::getSystemTime();

    mgr->idle();
    mgr->redraw();
    OSG::Thread::getCurrentChangeList()->clear();

    endT = OSG::getSystemTime();

    avgT -= timeHistory.front();
    while(timeHistory.size() > 20)
        timeHistory.pop_front();

    timeHistory.push_back(endT - startT);
    avgT += timeHistory.back();

    if(showFrameTime == true)
    {
        SLOG << "frame time " << (avgT / timeHistory.size())
             << std::endl;
    }
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
        mgr   = NULL;
        scene = NULL;

        OSG::osgExit();
        exit(0);
        break;

    case '1':
        std::cout << "printGeoInfo" << std::endl;
        doPrintGeoInfo(scene);
        break;

    case '2':
        std::cout << "makeSingleIndexed" << std::endl;
        doMakeSingleIndexed(scene);
        //doPrintGeoInfo(scene);
        break;

    case '3':
        std::cout << "makeIndexedTrianles" << std::endl;
        doMakeIndexedTriangles(scene);
        //doPrintGeoInfo(scene);
        break;

    case '4':
        std::cout << "makeOptimizedIndex" << std::endl;
        doMakeOptimizedIndex(scene);
        //doPrintGeoInfo(scene);
        break;

    case '5':
        std::cout << "makeOptimizedProperties" << std::endl;
        doMakeOptimizedProperties(scene);
        //doPrintGeoInfo(scene);
        break;

    case 'a':
        std::cout << "makeSphere(5, 5.f)" << std::endl;
        scene = OSG::makeSphere(5, 5.f);
        mgr->setRoot(scene);
        break;
    case 'b':
        std::cout << "makeTorus(2.f, 4.f, 16, 16)" << std::endl;
        scene = OSG::makeTorus(2.f, 4.f, 16, 16);
        mgr->setRoot(scene);
        break;
    case 'c':
        std::cout << "makeBox(2.f, 2.f, 2.f, 5, 5, 5)" << std::endl;
        scene = OSG::makeBox(2.f, 2.f, 2.f, 5, 5, 5);
        mgr->setRoot(scene);
        break;
    case 'd':
        std::cout << "file '" << fileName << "'" << std::endl;
        scene = OSG::SceneFileHandler::the()->read(fileName.c_str(), NULL);
        mgr->setRoot(scene);
        break;
    case 'e':
      std::cout << "file '" << fileName << "' with GraphOps" << std::endl;
      scene = OSG::SceneFileHandler::the()->read(fileName.c_str());
      mgr->setRoot(scene);
      break;

    case '.':
        std::cout << "mgr->showAll" << std::endl;
        mgr->showAll();
        break;

    case ',':
        showFrameTime = !showFrameTime;
        std::cout << "showFrameTime " << showFrameTime
                  << std::endl;
        break;
    }

    glutPostRedisplay();
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

void
doInit(int argc, char *argv[])
{
    OSG::osgInit(argc,argv);

    int winid = setupGLUT(&argc, argv);

    OSG::GLUTWindowUnrecPtr gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        OSG::SceneFileHandler::the()->print();

        std::cout << "makeSphere(5, 5.f)" << std::endl;
        scene = OSG::makeSphere(5, 5.f);
    }
    else
    {
        fileName = argv[1];

        scene = OSG::SceneFileHandler::the()->read(fileName.c_str(), NULL);
    }

    OSG::commitChanges();

    mgr = OSG::SimpleSceneManager::create();
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    mgr->showAll();

    timeHistory.push_back(0.0);
}

OSG::Action::ResultE
doPrintGeoInfoFunc(OSG::Node *node)
{
    OSG::NodeCore *core = node->getCore();
    OSG::Geometry *geo  = dynamic_cast<OSG::Geometry *>(core);

    if(geo != NULL)
    {
        std::cout << "== geo info ==" << std::endl;
        printGeoInfo(std::cout, geo) << std::endl;
    }

    return OSG::Action::Continue;
}

void
doPrintGeoInfo(OSG::Node *scene)
{
    OSG::traverse(scene,
                  boost::bind(&doPrintGeoInfoFunc, _1));
}

OSG::Action::ResultE
doMakeSingleIndexedFunc(OSG::Node *node)
{
    OSG::NodeCore *core = node->getCore();
    OSG::Geometry *geo  = dynamic_cast<OSG::Geometry *>(core);

    if(geo != NULL)
    {
        std::cout << "== geo make single idx ==" << std::endl;
        OSG::makeSingleIndexed(geo);
    }

    return OSG::Action::Continue;
}

void
doMakeSingleIndexed(OSG::Node *scene)
{
    OSG::Time start = OSG::getSystemTime();

    OSG::traverse(scene,
                  boost::bind(&doMakeSingleIndexedFunc, _1));

    std::cout << "time for doMakeSingleIndexed on scene: " << (OSG::getSystemTime() - start)
              << std::endl;
}

OSG::Action::ResultE
doMakeIndexedTrianglesFunc(OSG::Node *node)
{
    OSG::NodeCore *core = node->getCore();
    OSG::Geometry *geo  = dynamic_cast<OSG::Geometry *>(core);

    if(geo != NULL)
    {
        std::cout << "== geo make indexed tris ==" << std::endl;
        OSG::makeIndexedTriangles(geo);
    }

    return OSG::Action::Continue;
}

void
doMakeIndexedTriangles(OSG::Node *scene)
{
    OSG::Time start = OSG::getSystemTime();

    OSG::traverse(scene,
                  boost::bind(&doMakeIndexedTrianglesFunc, _1));

    std::cout << "time for doMakeIndexedTriangles on scene: " << (OSG::getSystemTime() - start)
              << std::endl;
}

OSG::Action::ResultE
doMakeOptimizedIndexFunc(OSG::Node *node)
{
    OSG::NodeCore *core = node->getCore();
    OSG::Geometry *geo  = dynamic_cast<OSG::Geometry *>(core);

    if(geo != NULL)
    {
        std::cout << "== geo make optimized index  ==" << std::endl;
        OSG::makeOptimizedIndex(geo);
    }

    return OSG::Action::Continue;
}

void
doMakeOptimizedIndex(OSG::Node *scene)
{
    OSG::Time start = OSG::getSystemTime();

    OSG::traverse(scene,
                  boost::bind(&doMakeOptimizedIndexFunc, _1));

    std::cout << "time for doMakeOptimizedIndex on scene: " << (OSG::getSystemTime() - start)
              << std::endl;
}

OSG::Action::ResultE
doMakeOptimizedPropertiesFunc(OSG::Node *node)
{
    OSG::NodeCore *core = node->getCore();
    OSG::Geometry *geo  = dynamic_cast<OSG::Geometry *>(core);

    if(geo != NULL)
    {
        std::cout << "== geo make optimized properties  ==" << std::endl;
        OSG::makeOptimizedProperties(geo);
    }

    return OSG::Action::Continue;
}

void
doMakeOptimizedProperties(OSG::Node *scene)
{
    OSG::Time start = OSG::getSystemTime();

    OSG::traverse(scene,
                  boost::bind(&doMakeOptimizedPropertiesFunc, _1));

    std::cout << "time for doMakeOptimizedProperties on scene: " << (OSG::getSystemTime() - start)
              << std::endl;
}

std::ostream &
printTypes(std::ostream &os, OSG::GeoIntegralProperty *types)
{
    os << "#types " << types->size();

    for(OSG::UInt32 i = 0; i < types->size(); ++i)
    {
        OSG::UInt32 val;
        types->getValue(val, i);

        os << " (" << i << ": ";
        switch(val)
        {
        case GL_TRIANGLES:      os << "GL_TRIANGLES";      break;
        case GL_TRIANGLE_STRIP: os << "GL_TRIANGLE_STRIP"; break;
        case GL_TRIANGLE_FAN:   os << "GL_TRIANGLE_FAN";   break;
        case GL_QUADS:          os << "GL_QUADS";          break;
        case GL_QUAD_STRIP:     os << "GL_QUAD_STRIP";     break;
        case GL_LINES:          os << "GL_LINES";          break;
        case GL_LINE_STRIP:     os << "GL_LINE_STRIP";     break;
        case GL_POINTS:         os << "GL_POINTS";         break;
        case GL_POLYGON:        os << "GL_POLYGON";        break;
        default:                os << "?? " << val;        break;
        }
        os << ")";
    }

    return os;
}

std::ostream &
printGeoInfo(std::ostream &os, OSG::Geometry *geo)
{
    if(geo->getTypes() != NULL)
        printTypes(os, geo->getTypes()) << std::endl;

    if(geo->getLengths() != NULL)
    {
        os << "#lengths " << geo->getLengths()->size()
           << std::endl;
    }

    OSG::Geometry::IndexBag ib = geo->getUniqueIndexBag();

    for(OSG::UInt32 i = 0; i < ib.size(); ++i)
    {
        os << "ib " << i << ": ";

        for(OSG::UInt32 j = 0; j < ib[i].second.size(); ++j)
        {
            os << ib[i].second[j] << ", ";
        }

        os << std::endl;
    }

    for(OSG::UInt16 i = 0; i <= OSG::Geometry::LastIndex; ++i)
    {
        OSG::GeoVectorProperty   *prop = geo->getProperty(i);
        OSG::GeoIntegralProperty *idx  = geo->getIndex   (i);

        if(prop != NULL)
        {
            os << "prop "  << i
               << " @"     << prop
               << " size " << prop->size()
               << " type " << prop->getType().getName();

            if(idx != NULL)
            {
                os << " idx @" << idx
                   << " size " << idx->size()
                   << " type " << idx->getType().getName();
            }

            os << std::endl;
        }
        else if(idx != NULL)
        {
            os << "prop "  << i << " NULL idx @" << idx
               << " size " << idx->size()
               << " type " << idx->getType().getName()
               << std::endl;
        }
    }

    os << "single indexed? " << (geo->isSingleIndex() ? "yes" : "no")
       << std::endl;

    return os;
}
