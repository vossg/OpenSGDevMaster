#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>
#include <OSGNode.h>

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
#include "OSGHDRStage.h"
#include "OSGVisitSubTree.h"

using namespace OSG;

RenderAction *rentravact = NullFC;

NodeRecPtr  hdrroot = NullFC;
NodeRecPtr  root    = NullFC;
NodeRecPtr  file    = NullFC;

PerspectiveCameraRecPtr cam = NullFC;
ViewportRecPtr          vp  = NullFC;
WindowRecPtr            win = NullFC;

TransformRecPtr cam_trans   = NullFC;
TransformRecPtr scene_trans = NullFC;

ComponentTransformRecPtr pAnimTrs[6] = 
{
    NullFC,
    NullFC,
    NullFC,
    NullFC,
    NullFC,
    NullFC
};

Trackball tball;

bool move_obj = false;

int mouseb = 0;
int lastx  = 0;
int lasty  = 0;

Quaternion oldq;
Vec3f      oldv;

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

    Real32 t = glutGet(GLUT_ELAPSED_TIME);

    for(UInt32 i = 0; i < 6; ++i)
    {
        if(pAnimTrs[i] != NullFC)
        {
            pAnimTrs[i]->editRotation().setValueAsAxisDeg(
                0.f, 1.f, 0.f, 
                t / 50.f);
        }
    }

    commitChanges();

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
    Real32 w = win->getWidth(), h = win->getHeight();
    

    Real32  
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

            hdrroot = NullFC;
            root    = NullFC;
            file    = NullFC;

            cam = NullFC;
            vp  = NullFC;
            win = NullFC;

            cam_trans   = NullFC;
            scene_trans = NullFC;

            pAnimTrs[0] = NullFC;
            pAnimTrs[1] = NullFC;
            pAnimTrs[2] = NullFC;
            pAnimTrs[3] = NullFC;
            pAnimTrs[4] = NullFC;
            pAnimTrs[5] = NullFC;
            

            osgExit(); 
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
            Line l;
            cam->calcViewRay( l, x, y, *vp );
            std::cerr << "From " << l.getPosition() << ", dir " 
                      << l.getDirection()
                      << std::endl;
        }
        break;

        case ' ':
        {
            Matrix     m;
            Quaternion q;
            Vec3f      v;

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


NodeTransitPtr setupAnim(void)
{
    NodeTransitPtr returnValue = Node::create();

    returnValue->setCore(Group::create());

    static const Real32 aOffsets[6][3] = 
    {
        { -5.5,  0.0,  0.0 },
        {  5.5,  0.0,  0.0 },
        {  0.0, -5.5,  0.0 },
        {  0.0,  5.5,  0.0 },
        {  0.0,  0.0, -5.5 },
        {  0.0,  0.0,  5.5 }
    };

    static const Real32 aDiffuse[6][3] =
    {
        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f },
        { 1.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f },
        { 0.f, 1.f, 1.f }
    };

    for(UInt32 i = 0; i < 6; ++i)
    {
        NodeUnrecPtr pTN                = Node::create();
        
        pAnimTrs[i] = ComponentTransform::create();
        
        GeometryUnrecPtr pGeo     = makeBoxGeo(1.f, 1.f, 1.f, 2, 2, 2);
        NodeUnrecPtr     pGeoNode = Node::create();
        
        pGeoNode->setCore(pGeo);

        SimpleMaterialUnrecPtr pMat = SimpleMaterial::create();
        
        pMat->setDiffuse(Color3r(aDiffuse[i][0],
                                 aDiffuse[i][1],
                                 aDiffuse[i][2]));
        pMat->setAmbient(Color3r(aDiffuse[i][0],
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
    osgInit(argc,argv);
    
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

    SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    NodeUnrecPtr  b1n = Node::create();
    GroupUnrecPtr b1  = Group::create();

    fprintf(stderr, "Create b1n %p %d %d \n",
            b1n.get(),
            b1n->getRefCount(),
            b1n->getWeakRefCount());

    b1n->setCore( b1 );

    // transformation
    NodeUnrecPtr      t1n = Node::create();
    TransformUnrecPtr t1  = Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    fprintf(stderr, "Create t1n %p %d %d \n",
            t1n.get(),
            t1n->getRefCount(),
            t1n->getWeakRefCount());

    cam_trans = t1;

    // light
    
    NodeUnrecPtr             dlight = Node::create();
    DirectionalLightUnrecPtr dl     = DirectionalLight::create();

    {
        dlight->setCore(dl);
        
        dl->setAmbient( .3, .3, .3, 1 );
        dl->setDiffuse( .8, .8, .8, .8 );
        dl->setDirection(0,0,1);
        dl->setBeacon( b1n);
    }

    fprintf(stderr, "Create dlight %p %d %d \n",
            dlight.get(),
            dlight->getRefCount(),
            dlight->getWeakRefCount());

    hdrroot = Node::create();

    hdrroot->editVolume().getInstance().setInfinite();
    hdrroot->editVolume().getInstance().setStatic  ();

    HDRStageUnrecPtr pHDR = HDRStage::create();

//    pHDR->setUpdateMode(HDRStage::PerVisit);
    pHDR->setEffectAmount(0.0);

    hdrroot->setCore (pHDR   );

    fprintf(stderr, "Create hdrroot %p %d %d \n",
            hdrroot.get(),
            hdrroot->getRefCount(),
            hdrroot->getWeakRefCount());

    // root
    root         = Node:: create();

    GroupUnrecPtr gr1 = Group::create();

    root->setCore(gr1);

    
    hdrroot->addChild(root);

    root->addChild(t1n   );
    root->addChild(dlight);

    fprintf(stderr, "Create root %p %d %d \n",
            root.get(),
            root->getRefCount(),
            root->getWeakRefCount());

    // Load the file

    NodeUnrecPtr file = NullFC;
    
    if(argc > 1)
    {
        file = SceneFileHandler::the()->read(argv[1], NULL);
    }

    if(file == NullFC)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

//        file = makeBox(2.f, 2.f, 2.f, 2, 2, 2);
        file = makeSphere(4, 2.0);
    }

    NodeUnrecPtr pCubeRoot            = Node::create();
    CubeMapGeneratorUnrecPtr pCubeGen = CubeMapGenerator::create();

    pCubeRoot->addChild(file);
    pCubeRoot->setCore(pCubeGen);
//    pCubeRoot->setCore(Group::create());

    NodeUnrecPtr         pCubeSceneRoot = Node::create();
    VisitSubTreeUnrecPtr pCubeVisit     = VisitSubTree::create();

    pCubeSceneRoot->setCore(pCubeVisit);
    pCubeVisit->setSubTreeRoot(root);

    pCubeGen->setRoot         (pCubeSceneRoot);
    pCubeGen->setTextureFormat(GL_RGB32F_ARB );
    pCubeGen->setSize         (512, 
                               512           );
    pCubeGen->setTexUnit      (3);

    NodeUnrecPtr pAnimRoot = setupAnim();

            scene_trans = Transform::create();
    NodeUnrecPtr sceneTrN    = Node::create();

    scene_trans->editMatrix()[3][2] = -50.f;

    sceneTrN->setCore (scene_trans);
    sceneTrN->addChild(pCubeRoot  );
    sceneTrN->addChild(pAnimRoot  );

    Thread::getCurrentChangeList()->commitChanges();

    Vec3f min,max;
    sceneTrN->updateVolume();
    sceneTrN->getVolume().getBounds(min, max);
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;


    dlight->addChild(sceneTrN);

    // Camera
    
    cam = PerspectiveCamera::create();
    {
        cam->setBeacon( b1n );
        cam->setFov( osgDegree2Rad( 90 ) );
        cam->setNear( 0.1 );
        cam->setFar( 100000 );
    }

    // Background
    SkyBackgroundUnrecPtr bkgnd = SkyBackground::create();
    {
        ImageUnrecPtr pBackImg = 
            ImageFileHandler::the()->read("grace_cross.chdr");

        TextureObjChunkUnrecPtr pBackTex = TextureObjChunk::create();

        pBackTex->setImage(pBackImg);
        pBackTex->setInternalFormat(GL_RGB32F_ARB);

        bkgnd->setBackTexture  (pBackTex);
        bkgnd->setFrontTexture (pBackTex);
        bkgnd->setLeftTexture  (pBackTex);
        bkgnd->setRightTexture (pBackTex);
        bkgnd->setTopTexture   (pBackTex);
        bkgnd->setBottomTexture(pBackTex);
    }

    // Viewport
    vp = Viewport::create();
    {
        vp->setCamera( cam );
        vp->setBackground( bkgnd );
        vp->setRoot( hdrroot );
//        vp->setRoot( root );
        vp->setSize( 0,0, 1,1 );
    }


    // Window
    GLUTWindowUnrecPtr gwin;

    GLint glvp[4];

    glGetIntegerv(GL_VIEWPORT, glvp);

    gwin = GLUTWindow::create();
    {
        gwin->setGlutId(winid);
        gwin->setSize( glvp[2], glvp[3] );
        
        win = gwin;

        win->addPort( vp );

        win->init();
    }

    // Action
    rentravact = RenderAction::create();

//    rentravact->setFrustumCulling(false);

    // tball
    Vec3f pos;

    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                  min[1] + (max[1] - min[1]) / 2,
                  min[2] + (max[2] - min[2]) / 2);

    fprintf(stderr, "Startpos : %f %f %f\n", pos[0], pos[1], pos[2]);

    tball.setMode            (Trackball::OSGObject);
    tball.setStartPosition   (pos, true           );
    tball.setSum             (true                );
    tball.setTranslationMode (Trackball::OSGFree  );
    tball.setTranslationScale(scale               );
    tball.setRotationCenter  (tCenter             );

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
