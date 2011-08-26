
// This is not actually a special Rhino3D test program, as the Rhino3D loader
// integrated itself into the SceneFileHandler, but I needed an example program
// here. 

// It does show however, how to use the extra options that the Rhino3D loader
// supports.

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGDrawable.h>
#include <OSGSimpleStatisticsForeground.h>
#include <OSGStatElemTypes.h>
#include <OSGStatCollector.h>
#include <OSGGradientBackground.h>
#include <OSGRhinoSceneFileType.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

// redraw the window
void display(void)
{   
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
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
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
        case 27:    
        {
            delete mgr;

            osgExit();
            exit(0);
        }
        
        case 'v':
        {
            mgr->getRenderAction()->setVolumeDrawing(
                !mgr->getRenderAction()->getVolumeDrawing());
		    std::cerr << "Volume Drawing: " 
                      << (mgr->getRenderAction()->getVolumeDrawing()?"on":"off") 
                      << std::endl;
        }
        break;
        
        case 'w':
        {
            std::cerr << "Writing osb...";
            SceneFileHandler::the()->write(mgr->getRoot(), "test.osb");
            std::cerr << "done." << std::endl;

        }
        break;
        
        case 'W':
        {
            std::cerr << "Writing osg...";
            SceneFileHandler::the()->write(mgr->getRoot(), "test.osg");
            std::cerr << "done." << std::endl;

        }
        break;
    }
}


int doMain(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowUnrecPtr pwin=PassiveWindow::create();
    pwin->init();

    // we do want a tessellation
    SceneFileHandler::the()->setOption("3dm", "doTessellation", "1");
    // import rendermeshes too
    SceneFileHandler::the()->setOption("3dm", "importRenderMeshes", "0");
    // let's set the number of interpolation steps curves are approximated with
    SceneFileHandler::the()->setOption("3dm", "curveInterpolationSteps", "101");

    if(argc > 1 && !strncmp(argv[1], "-e=", 3))
    {
        // the user supplied a tessellation error, let's that too
        float tessError = strtof(argv[1] + 3, NULL);
        if(tessError > 0)
        {            
            SceneFileHandler::the()->setOption("3dm", 
                                               "tesselationError", 
                                               argv[1] + 3);
            
        }
        argc--;
        argv++;
    }

    // create the scene
    NodeUnrecPtr scene;
    
    if(argc > 1)
    {
        scene = Node::create();
        GroupUnrecPtr g = Group::create();
        
        scene->setCore(g);
        
        for(UInt16 i = 1; i < argc; ++i)
            scene->addChild(SceneFileHandler::the()->read(argv[i]));
    }
    else
    {
        scene = makeTorus(.5, 3, 16, 16);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);

    /* set twosided light model */
    glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );

    // Background
    GradientBackgroundUnrecPtr gbkgnd = GradientBackground::create();

    gbkgnd->addLine( Color3f(.7,.7,1.), 0.0 );
    gbkgnd->addLine( Color3f(0, 0, 1), 0.5 );
    gbkgnd->addLine( Color3f(0, 0, .2), 1.0 );
    
    mgr->getWindow()->getPort(0)->setBackground(gbkgnd);
    
    // show the whole scene
    mgr->showAll();
    
    mgr->setStatistics(true);
  
    return 0;
}

int main(int argc, char **argv)
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    return 0;
}
