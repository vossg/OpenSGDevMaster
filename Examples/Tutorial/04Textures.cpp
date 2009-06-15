// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// these headers are need for textures and images
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGImage.h>

OSG::SimpleSceneManager *mgr;
OSG::NodeRecPtr          scene;

int setupGLUT( int *argc, char *argv[] );

OSG::NodeRecPtr createScenegraph(void)
{
    // the scene must be created here
    
    //create the geometry which we will assign a texture to
    OSG::GeometryRecPtr boxGeo = OSG::makeBoxGeo(10,10,10,1,1,1);
    
    //Load the image we want to use as a texture
    OSG::ImageRecPtr image = OSG::Image::create();
    image->read("Data/bricks.jpg");
    
    //now we create the texture that will hold the image
    OSG::SimpleTexturedMaterialRecPtr tex = 
        OSG::SimpleTexturedMaterial::create();

    tex->setImage(image);
    
    //now assign the fresh texture to the geometry
    boxGeo->setMaterial(tex);
    
    // Create the node that will hold our geometry
    OSG::NodeRecPtr n = OSG::Node::create();
    n->setCore(boxGeo);
    
    return OSG::NodeTransitPtr(n);
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
