// OpenSG Tutorial Example: Lights
//
// This example shows how to create and manipulate light sources
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// new header: the light sources
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new header: the light sources
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSpotLight.h>
#endif

OSG::UInt32          nlights = 6;

OSG::TransformRefPtr lightBeacons[8];
OSG::LightRefPtr     lights      [8];

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// create the motion matrix for a light source at time t
void makeMatrix(OSG::Real32 t, OSG::Matrix &result)
{
    OSG::Matrix m;
    
    result.setTransform(OSG::Quaternion(OSG::Vec3f(0,0,1), -OSG::Pi / 2));    
    
    m.setTransform(OSG::Vec3f(1, 0, 0));
    result.multLeft(m);
    
    m.setTransform(OSG::Quaternion(OSG::Vec3f(0,1,0), t / 1000.f));    
    result.multLeft(m);

    m.setTransform(OSG::Vec3f(2, 0, 0));
    result.multLeft(m);
    
    m.setTransform(OSG::Quaternion(OSG::Vec3f(0,0,1), t / 3000.f));
    result.multLeft(m); 
}

// redraw the window
void display( void )
{
    // create the matrix
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // stagger the lights in time, so that they follow each other
    for(OSG::UInt16 i = 0; i < nlights; ++i)
    {
        OSG::Matrix m;
        
        makeMatrix(t - 2000 * i, m);

        lightBeacons[i]->setMatrix(m);
    }
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

    // Args given?
    if(argc > 1)
    {
        if(sscanf(argv[1], "%d", &nlights) != 1)
        {
            FWARNING(("Number of lights '%s' not understood.\n", argv[1]));
            nlights = 3;
        }
    }
    
    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
    
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        /*
            A Light defines a source of light in the scene. Generally, two types
            of information are of interest: The position of the light source
            (geometry), and what elements of the scene are lit (semantics). 
    
            Using the position of the light in the graph for geometry allows
            moving the Light just like any other node, by putting it below a
            OSG::Transform Node and changing the transformation. This consistency
            also simplifies attaching Lights to moving parts in the scene: just
            put them below the same Transform and they will move with the object.
    
            The semantic interpretation also makes sense, it lets you restrict the
            influence area of the light to a subgraph of the scene. This can be
            used for efficiency, as every active light increases the amount of
            calculations necessary per vertex, even if the light doesn't influence
            the vertex, because it is too far away. It can also be used to
            overcome the restrictions on the number of lights. OpenSG currently
            only allows 8 concurrently active lights.
    
            It is also not difficult to imagine situations where both
            interpretations are necessary at the same time. Take for example a car
            driving through a night scene. You'd want to headlights to be fixed to
            the car and move together with it. But at the same time they should
            light the houses you're driving by, and not the mountains in the
            distance. 
    
            Thus there should be a way to do both at the same time. OpenSG solves
            this by splitting the two tasks to two Nodes. The Light's Node is for
            the sematntic part, it defines which object are lit by the Light. FOr
            the geometrc part the Light keeps a SFNodePtr to a different Node, the
            so called beacon. The local coordinate system of the beacon provides
            the reference coordinate system for the light's position.
    
    
            Thus the typical setup of an OpenSG scenegraph starts with a set of
            lights, which light the whole scene, followed by the actual geometry.
    
            Tip: Using the beacon of the camera (see \ref PageSystemWindowCamera)
            as the beacon of a light source creates a headlight.


            Every light is closely related to OpenGL's light specification. It has
            a diffuse, specular and ambient color. Additionally it can be switched
            on and off using the on field.
        */
    
    
        // Create the scene 
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr group = OSG::Group::create();
        scene->setCore(group);
    
        // create the scene to be lit
    
        // a simple torus is fine for now.
        // You can add more Geometry here if you want to.
        OSG::NodeRefPtr lit_scene = OSG::makeTorus(.5, 2, 32, 64);
    
        // helper node to keep the lights on top of each other
        OSG::NodeRefPtr lastnode = lit_scene;
    
        // create the light sources    
        OSG::Color3f colors[] = 
        {
            OSG::Color3f(1,0,0), OSG::Color3f(0,1,0), OSG::Color3f(0,0,1), 
            OSG::Color3f(1,1,0), OSG::Color3f(0,1,1), OSG::Color3f(1,0,1), 
            OSG::Color3f(1,1,1), OSG::Color3f(1,1,1)
        };
        if(nlights > 8)
        {
            FWARNING(("Currently only 8 lights supported\n"));
            nlights = 8;
        }
        
        // scale the lights to not overexpose everything. Just a little.
        OSG::Real32 scale = OSG::osgMax(1., 1.5 / nlights);
        
        for(OSG::UInt16 i = 0; i < nlights; ++i)
        {        
            // create the light source
            OSG::NodeRefPtr     light = OSG::Node::create();
            OSG::LightRefPtr    light_core;
            OSG::NodeRefPtr     geo_node;
            
            switch((i % 3) + 0)
            {
                /*
                    The PointLight has a position to define its location. In
                    addition, as it really is located in the scene, it has
                    attenuation parameters to change the light's intensity
                    depending on the distance to the light.
    
                    Point lights are more expesinve to compute than directional
                    lights, but not quite as expesive as spot lights. If you need
                    to see the localized effects of the light, a point light is a
                    good compromise between speed and quality.
                */
                case 0:
                {
                    OSG::PointLightRefPtr l = OSG::PointLight::create();
                    
                    l->setPosition             (0, 0, 0);
                    l->setConstantAttenuation  (1);
                    l->setLinearAttenuation    (0);
                    l->setQuadraticAttenuation (3);
                    
                    // a little sphere to show where the light is
                    geo_node = OSG::makeLatLongSphere(8, 8, 0.1f);
    
                    OSG::GeometryRefPtr       geo =
                        dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = 
                        OSG::SimpleMaterial::create();
    
                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f( colors[i][0], 
                                                 colors[i][1],
                                                 colors[i][2] ));
    
                    geo->setMaterial(sm);
    
                    light_core = l;
                }
                break;
                
                
                /*
                    The DirectionalLight just has a direction. 
    
                    To use it as a headlight use (0,0,-1) as a direction. it is
                    the computationally cheapest light source. Thus for the
                    fastest lit rendering, just a single directional light source.
                    The osg::SimpleSceneManager's headlight is a directional light
                    source.
    
                */
                case 1:
                {
                    OSG::DirectionalLightRefPtr l = 
                        OSG::DirectionalLight::create();
                    
                    l->setDirection(0, 0, 1);
                    
                    // a little cylinder to show where the light is
                    geo_node = OSG::makeCylinder(.1f, .03f, 8, true, true, true);
    
                    OSG::GeometryRefPtr       geo =
                        dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = 
                        OSG::SimpleMaterial::create();
    
                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f( colors[i][0], 
                                                 colors[i][1],
                                                 colors[i][2] ));
    
                    geo->setMaterial(sm);
    
                    light_core = l;
                }
                break;
                
                /*
                    The SpotLight adds a direction to the PointLight and a
                    spotCutOff angle to define the area that's lit. To define the
                    light intensity fallof within that area the spotExponent field
                    is used.
    
                    Spot lights are very expensive to compute, use them sparingly.
                */
                case 2:
                {
                    OSG::SpotLightRefPtr l = OSG::SpotLight::create();
                    
                    l->setPosition             (OSG::Pnt3f(0,  0, 0));
                    l->setDirection            (OSG::Vec3f(0, -1, 0));
                    l->setSpotExponent         (2);
                    l->setSpotCutOff           (OSG::osgDegree2Rad(45));
                    l->setConstantAttenuation  (1);
                    l->setLinearAttenuation    (0);
                    l->setQuadraticAttenuation (3);
                    
                    // a little cone to show where the light is
                    geo_node = OSG::makeCone(.2f, .2f, 8, true, true);
    
                    OSG::GeometryRefPtr       geo =
                        dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = 
                        OSG::SimpleMaterial::create();
    
                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f( colors[i][0], 
                                                 colors[i][1],
                                                 colors[i][2] ));
    
                    geo->setMaterial(sm);
    
                    light_core = l;
                }
                break;
            }
            
            // create the beacon and attach it to the scene
            OSG::NodeRefPtr         beacon      = OSG::Node::create();
            OSG::TransformRefPtr    beacon_core = OSG::Transform::create();
            
            lightBeacons[i] = beacon_core;
            
            beacon->setCore(beacon_core);
            beacon->addChild(geo_node);
        
            scene->addChild(beacon);
                
            light_core->setAmbient (colors[i][0] / scale,
                                    colors[i][1] / scale,
                                    colors[i][2] / scale,
                                    1);
            light_core->setDiffuse (colors[i][0] / scale,
                                    colors[i][1] / scale,
                                    colors[i][2] / scale,
                                    1);
            light_core->setSpecular(1 / scale,
                                    1 / scale,
                                    1 / scale,
                                    1);
            light_core->setBeacon  (beacon);
    
            light->setCore(light_core);
            light->addChild(lastnode);
            
            lights[i] = light_core;
            lastnode = light;
        }
    
        scene->addChild(lastnode);
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        
        // switch the headlight off, we have enough lights as is
        mgr->setHeadlight(false);
    
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
            delete mgr;
            
            OSG::osgExit();
            exit(1);
        }
        break;
        
        case 'a':   // activate all lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                lights[i]->setOn(true);
            }
        }
        break;
         
        case 's':   // deactivate all but the spot lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() != OSG::SpotLight::getClassTypeId())
                {
                    lights[i]->setOn(false);
                }
                else
                {
                    lights[i]->setOn(true);
                }
            }
            OSG::commitChanges();
        }
        break;
         
        case 'd':   // deactivate all but the directional lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() != 
                                      OSG::DirectionalLight::getClassTypeId())
                {
                    lights[i]->setOn(false);
                }
                else
                {
                    lights[i]->setOn(true);
                }
            }
            OSG::commitChanges();
        }
        break;
         
        case 'p':   // deactivate all but the point lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() != OSG::PointLight::getClassTypeId())
                {
                    lights[i]->setOn(false);
                }
                else
                {
                    lights[i]->setOn(true);
                }
            }
            OSG::commitChanges();
        }
        break;

        case 'S':
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
