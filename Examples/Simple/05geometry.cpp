// OpenSG Tutorial Example: Simple Geometry
//
// This example shows how to built a simple Geometry NodeCore.
//
// It also shows how to manipulate the geometry and what to watch out for. This
// is done in the display() function.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGeoProperties.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// New headers: 

// the geometry node core
#include <OSGGeometry.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoProperties.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// New headers: 

// the geometry node core
#include <OpenSG/OSGGeometry.h>
#endif

// The pointer to the transformation
OSG::TransformRefPtr trans;

// The pointer to the geometry core
OSG::GeometryRefPtr geo;


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

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
    
        // create the scene
        
        /*
            Geometry data in OpenSG is stored in several separate vectors.
            
            These vectors are not a direct part of the Geometry Core but
            rather split up into multiple separate classes.
            
            These classes, the GeoProperties, contain a single field containg
            their values, which can be accessed directly, see the docs for
            GeoProperty for the whole interface.
        */
        
        /*
            The first part: the primtive types.
            These are taken from OpenGL, any values that can be passed to
            glBegin(); are legal. Different types can be freely mixed.
        */
        OSG::GeoUInt8PropertyRefPtr type = OSG::GeoUInt8Property::create();
        type->addValue(GL_POLYGON  );
        type->addValue(GL_TRIANGLES);
        type->addValue(GL_QUADS    );
        
        /*
            The second part: the primtive lengths.
            These define the number of vertices to be passed to OpenGL for each
            primitive. Thus there have to be at least as many entries as in the
            types property.
        */
        OSG::GeoUInt32PropertyRefPtr lens = OSG::GeoUInt32Property::create();
        lens->addValue(4);
        lens->addValue(6);
        lens->addValue(8);
        
        /*
            The third part: the vertex positions.
            
            OpenSG uses different types for vectors and points.
            
            Points (e.g. Pnt3f) are just positions in space, they have a limited
            set of operations they can handle. Vectors (e.g. Vec3f) are the more
            general kind.
        */
        OSG::GeoPnt3fPropertyRefPtr  pnts = OSG::GeoPnt3fProperty::create();
        // the 4 points of the polygon
        pnts->addValue(OSG::Pnt3f(-1, -1, -1));
        pnts->addValue(OSG::Pnt3f(-1, -1,  1));
        pnts->addValue(OSG::Pnt3f( 1, -1,  1));
        pnts->addValue(OSG::Pnt3f( 1, -1, -1));
    
        // the 6 points of the two triangles
        pnts->addValue(OSG::Pnt3f( 1,  0, -1));
        pnts->addValue(OSG::Pnt3f(-1,  0, -1));
        pnts->addValue(OSG::Pnt3f( 0,  1, -1));
    
        pnts->addValue(OSG::Pnt3f(-1,  0,  1));
        pnts->addValue(OSG::Pnt3f( 1,  0,  1));
        pnts->addValue(OSG::Pnt3f( 0,  1,  1));
    
        // the 8 points of the two quads
        pnts->addValue(OSG::Pnt3f(-1,  -1,  1));    
        pnts->addValue(OSG::Pnt3f( 1,  -1,  1));    
        pnts->addValue(OSG::Pnt3f( 1,   0,  1));    
        pnts->addValue(OSG::Pnt3f(-1,   0,  1));    
    
        pnts->addValue(OSG::Pnt3f( 1,  -1, -1));    
        pnts->addValue(OSG::Pnt3f(-1,  -1, -1));    
        pnts->addValue(OSG::Pnt3f(-1,   0, -1));    
        pnts->addValue(OSG::Pnt3f( 1,   0, -1));    
    
        /*
        Put it all together into a Geometry NodeCore.
        */
        geo = OSG::Geometry::create();
        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setPositions(pnts);
    
        // assign a material to the geometry to make it visible. The details
        // of materials are defined later.
        geo->setMaterial(OSG::getDefaultUnlitMaterial());   
        
        // put the geometry core into a node
        OSG::NodeRefPtr n = OSG::Node::create();
        n->setCore(geo);
        
        // add a transformation to make it move     
        OSG::NodeRefPtr scene = OSG::Node::create();  
        trans = OSG::Transform::create();
        scene->setCore(trans);
        scene->addChild(n);
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
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
void display( void )
{
    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(OSG::Quaternion( OSG::Vec3f(0,1,0), 
                                    t / 1000.f));
    
    // set the transform's matrix
    trans->setMatrix(m);
   
    /*
        Manipulate the geometry.
        
        The OpenSG geometry structure is pretty flexible.
        
        The disadvantage of all this flexibility is that it can be hard to
        write generic tools, as pretty much all the used types can be one of a
        number of variants.
        
        To simplify that, every kind of GeoProperty has a generic type, e.g.
        the generic type for positions is Pnt3f, for colors it's Color3f.
        
        No matter the internal data representation looks like, all
        GeoProperties have the generic interface. As does the abstract parent
        class of every kind of property. Thus it's possible to access the data
        of an arbitrary geometry using the generic interface.
    */
    
    // note that this is the abstract parent class, it doesn't have a specific
    // type
    OSG::GeoVectorProperty *pos = geo->getPositions();
    
    for(OSG::UInt32 i = 0; i < pos->size(); i++)
    {
        OSG::Pnt3f p;      
        pos->getValue(p, i);
        
        p[0] += OSG::osgSin(t / 3000) * p[0] / 100;
        p[1] += OSG::osgSin(t / 3000) * p[1] / 100;
        p[2] += OSG::osgSin(t / 3000) * p[2] / 100;
        
        pos->setValue(p, i);
    }

    OSG::commitChanges();
    
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
            geo   = NULL;
            trans = NULL;
            delete mgr;
        
            OSG::osgExit();
            exit(0);
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
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

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
