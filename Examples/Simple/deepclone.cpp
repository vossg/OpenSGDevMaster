// OpenSG Tutorial Example: Deep Clones of scenes
//
// This tutorial demonstrates how to create independent (deep) copies of a
// scene and how to control what types should be shared.

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGComponentTransform.h>
#include <OSGBaseFunctions.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#endif

OSG::SimpleSceneManagerRefPtr mgr;

OSG::GeometryRefPtr           _geo;
OSG::GeoPnt3fPropertyRefPtr   _pos;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

OSG::Action::ResultE changeGeo(OSG::Node *node)
{   
    OSG::Geometry *geo = dynamic_cast<OSG::Geometry *>(node->getCore());
    
    if(geo == NULL)
        return OSG::Action::Continue;


    OSG::GeoColor3fPropertyRefPtr col = dynamic_cast<OSG::GeoColor3fProperty *>(geo->getColors());
    if(col == NULL)
    {
        col = OSG::GeoColor3fProperty::create();

        col->resize(geo->getPositions()->size());
        
        // Change the geometry to use the new colors
        geo->setColors(col);
        // If multi-indexed, make the colors use the same index as
        // the geometry
        if(geo->getIndex(OSG::Geometry::PositionsIndex) != NULL)
        {
            geo->setIndex(geo->getIndex(OSG::Geometry::PositionsIndex),
                          OSG::Geometry::ColorsIndex                   );
        }
    }
    
    OSG::Real32 size = col->size();
    for(OSG::UInt32 i = 0; i < size; ++i)
    {
        OSG::Color3f c;
        c[0] = 0.0f;
        c[1] = static_cast<OSG::Real32>(i) / size;
        c[2] = 0.0f;
        col->setValue(c, i);
    }
    
    return OSG::Action::Continue; 
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // load the scene
        OSG::NodeRefPtr scene;
        
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
            
            std::list<const char*> suffixes;
            OSG::SceneFileHandler::the()->getSuffixList(suffixes, OSG::SceneFileType::OSG_READ_SUPPORTED);
            
            for(std::list<const char*>::iterator it  = suffixes.begin();
                                                 it != suffixes.end();
                                               ++it)
            {
                FWARNING(("%s\n", *it));
            }
    
            scene = OSG::makeTorus(.5, 2, 16, 16);
        }
        else
        {
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
            scene = OSG::SceneFileHandler::the()->read(argv[1]);
        }
        
        OSG::commitChanges();
        
        // calc size of the scene
        OSG::Vec3f min, max;
        OSG::BoxVolume vol;
        scene->getWorldVolume(vol);
        vol.getBounds(min, max);
    
        OSG::Vec3f  d      = max - min;
        OSG::Real32 offset = d.length() / 2.0f;
        
        // now create a deep clone
        OSG::NodeRefPtr sceneClone = OSG::deepCloneTree(scene);
        
        // this clones all nodes but the cores of type Material and Transform are shared.
        //NodePtr sceneClone = deepCloneTree(scene, "Material, Transform");
        
        // now change all geometries from the cloned scene just to show
        // that it is a real deep copy.
        traverse(sceneClone, &changeGeo);
        
        // create a small scene graph with two transformation nodes.
        OSG::NodeRefPtr               root = OSG::makeCoredNode<OSG::Group>();
        OSG::ComponentTransformRefPtr t1;
        OSG::NodeRefPtr               tn1 = 
            OSG::makeCoredNode<OSG::ComponentTransform>(&t1);
        OSG::ComponentTransformRefPtr t2;
        OSG::NodeRefPtr               tn2 = 
            OSG::makeCoredNode<OSG::ComponentTransform>(&t2);
        
        t1->setTranslation(OSG::Vec3f(- offset, 0.0f, 0.0f));
        t2->setTranslation(OSG::Vec3f(offset, 0.0f, 0.0f));
        
        tn1->addChild(scene);
        tn2->addChild(sceneClone);
        
        root->addChild(tn1);
        root->addChild(tn2);
        
        OSG::commitChanges();
        
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (root);
    
        // show the whole scene
        mgr->showAll();
    }
    
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            _geo = NULL;
            _pos = NULL;
            mgr  = NULL;
            
            OSG::osgExit();
            exit(0);
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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
