// what follows here is probably the smallest OpenSG programm possible
// most things used here are explained now or on the next few pages, so don't 
// worry if not everythings clear right at the beginning...

// Some needed inlcude files - these will become more, believe me ;)
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// The SimpleSceneManager is a little usefull class which helps us to 
// manage simple configurations. It will be discussed in detail later on
OSG::SimpleSceneManager *mgr;

// we have a forward declarion here, just to sort the code 
int setupGLUT( int *argc, char *argv[] );

int main(int argc, char **argv)
{
    // Init the OpenSG subsystem
    OSG::osgInit(argc,argv);
    
    {
        // We create a GLUT Window (that is almost the same for most applications)
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // That will be our whole scene for now : an incredible Torus
        OSG::NodeRecPtr scene = OSG::makeTorus(.5, 2, 16, 16);
    
        // Create and setup our little friend - the SSM
        mgr = new OSG::SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        OSG::commitChanges();
    }

    // Give Control to the GLUT Main Loop
    glutMainLoop();

    return 0;
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// just redraw our scene if this GLUT callback is invoked
void display(void)
{
    mgr->redraw();
}

//The GLUT subsystem is set up here. This is very similar to other GLUT
//applications If you have worked with GLUT before, you may have the feeling
//of meeting old friends again, if you have not used GLUT before that is no
//problem. GLUT will be introduced briefly in the next section.


int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG First Application");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    return winid;
}
