// OpenSG Tutorial Example: Materials
//
// This example shows how to create a material. Materials define the surface
// properties of the geometry, and change how they look.
//
// This example shows the usage of SimpleMaterial and SimpleTexturedMaterial.
// Call it with an image filename as a parameter.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// new headers: 

// the headers for the SimpleMaterials
#include <OSGSimpleMaterial.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGImage.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 

// the headers for the SimpleMaterials
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGImage.h>
#endif

// a separate transformation for every object
OSG::TransformRefPtr cyltrans, tortrans;


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManagerRefPtr mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// redraw the window
void display(void)
{
    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // set the transforms' matrices
    m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                   OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

    cyltrans->setMatrix(m);
    
    m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                   OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

    tortrans->setMatrix(m);

    OSG::commitChanges();
    
    mgr->redraw();
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
    
        // create the scene
        
        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene group
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr g     = OSG::Group::create();
        
        scene->setCore(g);
        
        // The cylinder and its transformation
        OSG::NodeRefPtr     cyl    = OSG::Node::create();
        OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 8, 
                                                           true, true, true );
        
        cyl->setCore(cylgeo);
    
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();
        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr     torus    = OSG::Node::create();
        OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 8, 12 );
        
        torus->setCore(torusgeo);
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);
    
        // now create and assign the materials
    
        /*
            Materials in OpenSG are associated with the Geometry NodeCores, i.e.
            every Geometry knows its material.
            
            Right now there are two kinds of Materials: SimpleMaterial and
            SimpleTexturedMaterial.
            
            SimpleMaterial is a pretty direct wrapper of the OpenGL material
            characteristics. It has an ambient, diffuse, emission and specular
            color together with a shininess. It also defines the transparency of
            the material. Finally there are two flags. Lit defines if the material
            is influenced by light sources and the lighting calculation. If lit is
            false, only the diffuse color is used. ColorMaterial defines if and
            how the colors given in the object influence the lighting calculation.
            Possible values are GL_NONE, GL_EMISSION, GL_AMBIENT, GL_DIFFUSE,
            GL_SPECULAR and  GL_AMBIENT_AND_DIFFUSE. 
        */
        
        OSG::SimpleMaterialRefPtr m1 = OSG::SimpleMaterial::create();
        
        // when everything is changed, not setting the mask is ok
        m1->setAmbient      (OSG::Color3f(0.2f,0.2f,0.2f));
        m1->setDiffuse      (OSG::Color3f(0.8f,0.5f,0.2f));
        m1->setEmission     (OSG::Color3f(0.0f,0.0f,0.0f));
        m1->setSpecular     (OSG::Color3f(1.0f,1.0f,1.0f));
        m1->setShininess    (10);
        
        /*
            Transparent objects are rendered last and sorted from back to
            front, but only objectwise. Thus transparecy within an object is
            not handled correctly.
        */
        m1->setTransparency (0);
        
        /*
            The SimpleGeometry objects do not contain colors, turn
            ColorMaterial off.
        */
        m1->setColorMaterial(GL_NONE);
        
    
        // assign the material to the geometry
        cylgeo->setMaterial(m1);
        
        
        /*
            SimpleTexturedMaterial is a SimpleMaterial with a texture.
            
            The texture is specified using an Image, which can be created on the
            fly or loaded from a file. 
            
            Additionally the texture filters can be changed via the
            minFilter/magFilter fields. Possible values are taken from OpenGL's
            glTexParameter() function. MinFilter can be GL_NEAREST, GL_LINEAR, and
            the mipmap modes, the most common being GL_LINEAR_MIPMAP_LINEAR.
            MagFilter can be GL_NEAREST or GL_LINEAR.
            
            Textures are independent from the normal lighting calculations. How the
            texture is combined with the lighting color is define by the envMode.
            The possible values are taken from glTexEnv(). GL_MODULATE just
            multiplies the two, GL_REPLACE ignores the lighting color and just uses
            the texture.
            
            The option that the SimpleTexturedMaterial has is the ability to use
            spherical environment maps. These can be used to simulate reflective
            environments.
        */
        
        /*
            Images can be created directly from the data or loaded from disk.
            
            The Image can handle a variety of data formats, including 1, 2, 3 or 4
            component images, and 1, 2 or 3 dimensional data. It can load and save
            a variety of formats, exactly which depends on the configured
            libraries.
        */
        
        OSG::ImageRefPtr image = OSG::Image::create();
    
        if(argc > 1)
        {
            image->read(argv[1]);
        }
        else
        {
            OSG::UChar8 data[] = {  0xff, 0xff, 0xff,  0x80, 0x00, 0x00,
                                    0x80, 0x00, 0x00,  0xff, 0xff, 0xff };
    
            image->set( OSG::Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, data );
        }
        
        OSG::SimpleTexturedMaterialRefPtr m2 = 
            OSG::SimpleTexturedMaterial::create();
        
        m2->setAmbient      (OSG::Color3f(0.3f,0.3f,0.3f));
        m2->setDiffuse      (OSG::Color3f(0.2f,0.8f,0.8f));
        m2->setEmission     (OSG::Color3f(0.0f,0.0f,0.0f));
        m2->setSpecular     (OSG::Color3f(1.0f,1.0f,1.0f));
        m2->setShininess    (20);
        m2->setTransparency (0);
        m2->setColorMaterial(GL_NONE);
            
        m2->setImage        (image);
        m2->setMinFilter    (GL_LINEAR_MIPMAP_LINEAR);
        m2->setMagFilter    (GL_NEAREST);
        m2->setEnvMode      (GL_MODULATE);
        m2->setEnvMap       (false);
        
        // assign the material to the geometry
        torusgeo->setMaterial(m2);
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
    
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
            cyltrans = NULL;
            tortrans = NULL;
            mgr      = NULL;
        
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
