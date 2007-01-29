// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>

// New Headers

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#include <boost/bind.hpp>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// helper class to find a named node
// names are handled as simple attachments, get the header for that
#include <OpenSG/OSGSimpleAttachments.h>

// There are two convenience functions for name access: getName() and
// setName(). For details about general attachment handling see the 
// attachments tutorial

class NamedNodeFinder
{
  public:
  
    NamedNodeFinder(void) : _name(), _found() {}

    NodePtr operator() (NodePtr root, std::string name)
    {
        _name=&name;
        _found=NullFC;
        
        TraverseEnterFunctor enter =
            boost::bind(&NamedNodeFinder::check, this, _1);
        traverse(root, enter);
        
        return _found;
    }
 
    static NodePtr find(NodePtr root, std::string name)
    {
        NamedNodeFinder f;      
        
        return f(root,name);
    }
   
  private:
     
    Action::ResultE check(NodePtr node)
    {
        if(getName(node) && *_name == getName(node))
        {
            _found = node;
            return Action::Quit;
        }

        return Action::Continue;        
    }
 
    NodePtr  _found;
    std::string  *_name;
};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // load the scene

    NodePtr scene;
    
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        
        std::list<const char*> suffixes;
        SceneFileHandler::the()->getSuffixList(suffixes);
        //SceneFileHandler::the()->print();
        
        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        scene = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        /*
            All scene file loading is handled via the SceneFileHandler.
        */
        scene = SceneFileHandler::the()->read(argv[1]);
    }

    
    NodePtr found;
    
    NamedNodeFinder f;
    
    // Try to find the Scene object. As it hasn't been named yet, 
    // it's not expected to be found.
    found = f(scene, "Scene");  
    if(found == NullFC)
    {
        SLOG << "Found no object named Scene." << endLog;
    }
    else
    {
        SLOG << "Found object " << found << " named Scene. How did that happen?" 
             << endLog;
    }   
    
    // Try to find the TF_DETAIL object. An object in Data/tie.wrl is called
    // TF_DETAIL, so we might find it.
    found = NamedNodeFinder::find(scene, "TF_DETAIL"); 
    if(found == NullFC)
    {
        SLOG << "Found no object named TF_DETAIL (did you load the tie?)." 
             << endLog;
    }
    else
    {
        SLOG << "Found object " << found << " named TF_DETAIL." << endLog;
    }   

    commitChanges();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->idle();
    mgr->redraw();
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
            OSG::osgExit();
            exit(0);
        }
        break;
        
        case 'f': 
        {  
            mgr->setNavigationMode(Navigator::FLY);
        }
        break;
        
        case 't':   
        {
            mgr->setNavigationMode(Navigator::TRACKBALL);
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
