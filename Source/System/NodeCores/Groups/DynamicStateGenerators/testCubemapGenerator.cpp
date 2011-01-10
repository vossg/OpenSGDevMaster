#include "OSGConfig.h"

#include <iostream>

#include "OSGGLUT.h"
#include "OSGNode.h"

#include "OSGTrackball.h"
#include "OSGLine.h"
#include "OSGPerspectiveCamera.h"
#include "OSGTransform.h"
#include "OSGComponentTransform.h"
#include "OSGRenderAction.h"
#include "OSGWindow.h"
#include "OSGSceneFileHandler.h"
#include "OSGSolidBackground.h"
#include "OSGSkyBackground.h"
#include "OSGGLUTWindow.h"
#include "OSGDirectionalLight.h"
#include "OSGSimpleGeometry.h"
#include "OSGSimpleMaterial.h"
#include "OSGCubeMapGenerator.h"
#include "OSGImageFileHandler.h"
#include "OSGVisitSubTree.h"

OSG::RenderAction *rentravact = NULL;

OSG::NodeRecPtr  hdrroot = NULL;
OSG::NodeRecPtr  root    = NULL;
OSG::NodeRecPtr  file    = NULL;

OSG::PerspectiveCameraRecPtr cam = NULL;
OSG::ViewportRecPtr          vp  = NULL;
OSG::WindowRecPtr            win = NULL;

OSG::TransformRecPtr cam_trans   = NULL;
OSG::TransformRecPtr scene_trans = NULL;

OSG::ComponentTransformRecPtr pAnimTrs[6] = 
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

OSG::Trackball tball;

bool move_obj = false;

int mouseb = 0;
int lastx  = 0;
int lasty  = 0;

OSG::Quaternion oldq;
OSG::Vec3f      oldv;

void display(void)
{
#if 0
    Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
    m2.setTranslate( tball.getPosition() );
    
    m1.mult( m2 );

    if(move_obj == true)
    {
        scene_trans->editSFMatrix()->setValue( m1 );
    }
    else
    {
        cam_trans->editSFMatrix()->setValue( m1 );
    }
#endif

    cam_trans->editSFMatrix()->setValue(tball.getFullTrackballMatrix());

#if 0
    fprintf(stderr, "%f %f %f\n", 
            cam_trans->getMatrix()[3][0],
            cam_trans->getMatrix()[3][1],
            cam_trans->getMatrix()[3][2]);
#endif

    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME);

    for(OSG::UInt32 i = 0; i < 6; ++i)
    {
        if(pAnimTrs[i] != NULL)
        {
            pAnimTrs[i]->editRotation().setValueAsAxisDeg(
                0.f, 1.f, 0.f, 
                t / 50.f);
        }
    }

    OSG::commitChanges();

//    fprintf(stderr, "Frame start\n");
//    fprintf(stderr, "============================================\n");
    

    win->render(rentravact);
}

void reshape( int w, int h )
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize( w, h );
}


void animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void motion(int x, int y)
{   
    OSG::Real32 w = win->getWidth(), h = win->getHeight();
    

    OSG::Real32  
        a = -2. * ( lastx / w - .5 ),
        b = -2. * ( .5 - lasty / h ),
        c = -2. * ( x / w - .5 ),
        d = -2. * ( .5 - y / h );
    
    if ( mouseb & ( 1 << GLUT_LEFT_BUTTON ) )
    {
        tball.updateRotation( a, b, c, d );     
    }
    else if ( mouseb & ( 1 << GLUT_MIDDLE_BUTTON ) )
    {
        tball.updatePosition( a, b, c, d );     
    }
    else if ( mouseb & ( 1 << GLUT_RIGHT_BUTTON ) )
    {
        tball.updatePositionNeg( a, b, c, d );  
    }

    lastx = x;
    lasty = y;
}

void mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
            case GLUT_LEFT_BUTTON:  
                break;

            case GLUT_MIDDLE_BUTTON:
                tball.setAutoPosition(true);
                break;

            case GLUT_RIGHT_BUTTON:     
                tball.setAutoPositionNeg(true);
                break;
        }

        mouseb |= 1 << button;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
            case GLUT_LEFT_BUTTON:  break;

            case GLUT_MIDDLE_BUTTON:
                tball.setAutoPosition(false);
                break;

            case GLUT_RIGHT_BUTTON:     
                tball.setAutoPositionNeg(false);
                break;
        }       

        mouseb &= ~(1 << button);
    }
    lastx = x;
    lasty = y;
}

void vis(int visible)
{
    if (visible == GLUT_VISIBLE) 
    {
        glutIdleFunc(animate);
    } 
    else 
    {
        glutIdleFunc(NULL);
    }
}

void key(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 27:    

            fprintf(stderr, "Start Destruction\n\n");

            delete rentravact;

            hdrroot = NULL;
            root    = NULL;
            file    = NULL;

            cam = NULL;
            vp  = NULL;
            win = NULL;

            cam_trans   = NULL;
            scene_trans = NULL;

            pAnimTrs[0] = NULL;
            pAnimTrs[1] = NULL;
            pAnimTrs[2] = NULL;
            pAnimTrs[3] = NULL;
            pAnimTrs[4] = NULL;
            pAnimTrs[5] = NULL;
            

            OSG::osgExit(); 
            exit(0);
        case 'a':   
            glDisable( GL_LIGHTING );
            std::cerr << "Lighting disabled." << std::endl;
            break;
        case 's':   
            glEnable( GL_LIGHTING );
            std::cerr << "Lighting enabled." << std::endl;
            break;
        case 'r':   
        {
            std::cerr << "Sending ray through " << x << "," << y << std::endl;
            OSG::Line l;
            cam->calcViewRay( l, x, y, *vp );
            std::cerr << "From " << l.getPosition() << ", dir " 
                      << l.getDirection()
                      << std::endl;
        }
        break;

        case 'd':
            OSG::ActionDataSlotPool::the()->dumpState();
            OSG::StageIdPool       ::the()->dumpState();
            rentravact->dumpStore();
            break;
        case ' ':
        {
            OSG::Matrix     m;
            OSG::Quaternion q;
            OSG::Vec3f      v;

            q = oldq;
            v = oldv;

            oldq = tball.getRotation();
            oldv = tball.getPosition();

            move_obj = ! move_obj;
            if ( move_obj )
            {
                puts("moving object");
                tball.setMode( OSG::Trackball::OSGCamera );

            }
            else
            {
                puts("moving camera");
                tball.setMode( OSG::Trackball::OSGObject );
            }
            
            tball.setStartPosition( v, true );
            tball.setStartRotation( q, true );
        }
        break;
    }
}


OSG::NodeTransitPtr setupAnim(void)
{
    OSG::NodeTransitPtr returnValue = OSG::Node::create();

    returnValue->setCore(OSG::Group::create());

    static const OSG::Real32 aOffsets[6][3] = 
    {
        { -5.5,  0.0,  0.0 },
        {  5.5,  0.0,  0.0 },
        {  0.0, -5.5,  0.0 },
        {  0.0,  5.5,  0.0 },
        {  0.0,  0.0, -5.5 },
        {  0.0,  0.0,  5.5 }
    };

    static const OSG::Real32 aDiffuse[6][3] =
    {
        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f },
        { 1.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f },
        { 0.f, 1.f, 1.f }
    };

    for(OSG::UInt32 i = 0; i < 6; ++i)
    {
        OSG::NodeUnrecPtr pTN                = OSG::Node::create();
        
        pAnimTrs[i] = OSG::ComponentTransform::create();
        
        OSG::GeometryUnrecPtr pGeo     = OSG::makeBoxGeo(1.f, 1.f, 1.f, 
                                                         2,   2,   2);
        OSG::NodeUnrecPtr     pGeoNode = OSG::Node::create();
        
        pGeoNode->setCore(pGeo);

        OSG::SimpleMaterialUnrecPtr pMat = OSG::SimpleMaterial::create();
        
        pMat->setDiffuse(OSG::Color3f(aDiffuse[i][0],
                                      aDiffuse[i][1],
                                      aDiffuse[i][2]));
        pMat->setAmbient(OSG::Color3f(aDiffuse[i][0],
                                      aDiffuse[i][1],
                                      aDiffuse[i][2]));

        pGeo->setMaterial(pMat);

        pAnimTrs[i]->editTranslation().setValues(aOffsets[i][0],
                                                 aOffsets[i][1],
                                                 aOffsets[i][2]);
        
        pTN->setCore (pAnimTrs[i]);
        pTN->addChild(pGeoNode   );
        
        returnValue->addChild(pTN);
    }


    return returnValue;
}

int doMain (int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    

    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    glutIdleFunc(display);  

    // OSG

    OSG::SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    OSG::NodeUnrecPtr  b1n = OSG::Node::create();
    OSG::GroupUnrecPtr b1  = OSG::Group::create();

    fprintf(stderr, "Create b1n %p %d %d \n",
            b1n.get(),
            b1n->getRefCount(),
            b1n->getWeakRefCount());

    b1n->setCore( b1 );

    // transformation
    OSG::NodeUnrecPtr      t1n = OSG::Node::create();
    OSG::TransformUnrecPtr t1  = OSG::Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    fprintf(stderr, "Create t1n %p %d %d \n",
            t1n.get(),
            t1n->getRefCount(),
            t1n->getWeakRefCount());

    cam_trans = t1;

    // light
    
    OSG::NodeUnrecPtr             dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl     = OSG::DirectionalLight::create();

    {
        dlight->setCore(dl);
        
        dl->setAmbient( .3f, .3f, .3f, 1 );
        dl->setDiffuse( .8f, .8f, .8f, .8f );
        dl->setDirection(0,0,1);
        dl->setBeacon( b1n);
    }

    fprintf(stderr, "Create dlight %p %d %d \n",
            dlight.get(),
            dlight->getRefCount(),
            dlight->getWeakRefCount());

    hdrroot = OSG::Node::create();
    
    hdrroot->editVolume().setInfinite();
    hdrroot->editVolume().setStatic  ();

    hdrroot->setCore(OSG::Group::create());

    // root
    root         = OSG::Node:: create();

    OSG::GroupUnrecPtr gr1 = OSG::Group::create();

    root->setCore(gr1);

    
    hdrroot->addChild(root);

    root->addChild(t1n   );
    root->addChild(dlight);

    fprintf(stderr, "Create root %p %d %d \n",
            root.get(),
            root->getRefCount(),
            root->getWeakRefCount());

    // Load the file

    OSG::NodeUnrecPtr file = NULL;
    
    if(argc > 1)
    {
        file = OSG::SceneFileHandler::the()->read(argv[1], NULL);
    }

    if(file == NULL)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

//        file = makeBox(2.f, 2.f, 2.f, 2, 2, 2);
        file = OSG::makeSphere(4, 2.0);
    }

    OSG::NodeUnrecPtr pCubeRoot            = OSG::Node::create();
    OSG::CubeMapGeneratorUnrecPtr pCubeGen = OSG::CubeMapGenerator::create();

    pCubeRoot->addChild(file);
    pCubeRoot->setCore(pCubeGen);
//    pCubeRoot->setCore(Group::create());

    OSG::NodeUnrecPtr         pCubeSceneRoot = OSG::Node::create();
    OSG::VisitSubTreeUnrecPtr pCubeVisit     = OSG::VisitSubTree::create();

    pCubeSceneRoot->setCore(pCubeVisit);
    pCubeVisit->setSubTreeRoot(root);

    pCubeGen->setRoot         (pCubeSceneRoot);
    pCubeGen->setTextureFormat(GL_RGB32F_ARB );
    pCubeGen->setSize         (512, 
                               512           );
    pCubeGen->setTexUnit      (3);

    // Cubemap Background
    OSG::SolidBackgroundUnrecPtr cubeBkgnd = OSG::SolidBackground::create();
    {
        cubeBkgnd->setColor(OSG::Color3f(0.5f, 0.3f, 0.3f));
    }

    pCubeGen->setBackground(cubeBkgnd);


    OSG::NodeUnrecPtr pAnimRoot = setupAnim();

            scene_trans = OSG::Transform::create();
    OSG::NodeUnrecPtr sceneTrN    = OSG::Node::create();

    scene_trans->editMatrix()[3][2] = -50.f;

    sceneTrN->setCore (scene_trans);
    sceneTrN->addChild(pCubeRoot  );
    sceneTrN->addChild(pAnimRoot  );

    OSG::Thread::getCurrentChangeList()->commitChanges();

    OSG::Vec3f min,max;
    sceneTrN->updateVolume();
    sceneTrN->getVolume().getBounds(min, max);
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;


    dlight->addChild(sceneTrN);

    // Camera
    
    cam = OSG::PerspectiveCamera::create();
    {
        cam->setBeacon( b1n );
        cam->setFov( OSG::osgDegree2Rad( 90 ) );
        cam->setNear( 0.1f );
        cam->setFar( 100000 );
    }

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();
    {
        bkgnd->setColor(OSG::Color3f(0.3f, 0.3f, 0.3f));
    }

    // Viewport
    vp = OSG::Viewport::create();
    {
        vp->setCamera( cam );
        vp->setBackground( bkgnd );
        vp->setRoot( hdrroot );
//        vp->setRoot( root );
        vp->setSize( 0,0, 1,1 );
    }


    // Window
    OSG::GLUTWindowUnrecPtr gwin;

    GLint glvp[4];

    glGetIntegerv(GL_VIEWPORT, glvp);

    gwin = OSG::GLUTWindow::create();
    {
        gwin->setGlutId(winid);
        gwin->setSize( glvp[2], glvp[3] );
        
        win = gwin;

        win->addPort( vp );

        win->init();
    }

    // Action
    rentravact = OSG::RenderAction::create();

    rentravact->setVolumeDrawing(true);
//    rentravact->setFrustumCulling(false);

    // tball
    OSG::Vec3f pos;

    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    OSG::Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                       min[1] + (max[1] - min[1]) / 2,
                       min[2] + (max[2] - min[2]) / 2);

    fprintf(stderr, "Startpos : %f %f %f\n", pos[0], pos[1], pos[2]);

    tball.setMode            (OSG::Trackball::OSGObject);
    tball.setStartPosition   (pos, true                );
    tball.setSum             (true                     );
    tball.setTranslationMode (OSG::Trackball::OSGFree  );
    tball.setTranslationScale(scale                    );
    tball.setRotationCenter  (tCenter                  );

    fprintf(stderr, "Create b1n %p %d %d \n",
            b1n.get(),
            b1n->getRefCount(),
            b1n->getWeakRefCount());

    fprintf(stderr, "Create t1n %p %d %d \n",
            t1n.get(),
            t1n->getRefCount(),
            t1n->getWeakRefCount());

    fprintf(stderr, "Create dlight %p %d %d \n",
            dlight.get(),
            dlight->getRefCount(),
            dlight->getWeakRefCount());

    fprintf(stderr, "Create hdrroot %p %d %d \n",
            hdrroot.get(),
            hdrroot->getRefCount(),
            hdrroot->getWeakRefCount());

    fprintf(stderr, "Create root %p %d %d \n",
            root.get(),
            root->getRefCount(),
            root->getWeakRefCount());

    return 0;
}

int main (int argc, char **argv)
{
    doMain(argc, argv);

    fprintf(stderr, "Create hdrroot %p %d %d \n",
            hdrroot.get(),
            hdrroot->getRefCount(),
            hdrroot->getWeakRefCount());

    fprintf(stderr, "Create root %p %d %d \n",
            root.get(),
            root->getRefCount(),
            root->getWeakRefCount());

    // run...
    glutMainLoop();

    return 0;
}
