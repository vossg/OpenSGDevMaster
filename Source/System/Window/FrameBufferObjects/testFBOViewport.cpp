#include "OSGConfig.h"

#include <iostream>

#include "OSGGLUT.h"

#include "OSGFieldContainerFactory.h"
#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGBoxVolume.h"
#include "OSGLine.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGThread.h"
#include "OSGTransform.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGSimpleGeometry.h"
#include "OSGSceneFileHandler.h"
#include "OSGChunkOverrideGroup.h"
#include "OSGPolygonChunk.h"
#include "OSGDirectionalLight.h"

#include "OSGTextureEnvChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGSimpleMaterial.h"
#include "OSGPolygonForeground.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGUniformBackground.h"
#include "OSGOSGWriter.h"
#include "OSGChangeList.h"
#include "OSGIOStream.h"
#include "OSGGeoFunctions.h"
#include "OSGGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGMultiCore.h"

#include "OSGFBOViewport.h"
#include "OSGTextureBuffer.h"
#include "OSGRenderBuffer.h"

#include "OSGTrackball.h"

OSG::RenderAction *rentravact;

OSG::NodeRecPtr  root;

OSG::NodeRecPtr  file;

OSG::PerspectiveCameraRecPtr cam;
OSG::ViewportRecPtr vp;
OSG::WindowRecPtr win;

OSG::TransformRecPtr cam_trans;
OSG::TransformRecPtr scene_trans;

OSG::PolygonChunkRecPtr       pPoly;
bool                          bPolyActive = false;
OSG::ChunkOverrideGroupRecPtr pCOver;

OSG::GLUTWindowUnrecPtr gwin;

OSG::TextureObjChunkUnrecPtr tx1o;
OSG::TextureEnvChunkUnrecPtr tx1e;
OSG::FBOViewportUnrecPtr     vpFBO;
OSG::FBOViewportUnrecPtr     vpFBO_RB;
OSG::TextureBufferUnrecPtr   pTexBuffer;
OSG::RenderBufferUnrecPtr    pRenBuffer;
OSG::ImageUnrecPtr           pImg;

OSG::Trackball tball;

bool move_obj = false;

int mouseb = 0;
int lastx=0, lasty=0;

OSG::Quaternion oldq;
OSG::Vec3f      oldv;

OSG::UInt32 oldTravMask;
bool dumpImg = false;

OSG::UInt32 oldTravMask_RB;
bool dumpImg_RB = false;

void display(void)
{
    OSG::Matrix m1, m2, m3;
    OSG::Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
//    std::cout << "TBROT" << std::endl << tball.getRotation() << endl;
//    std::cout << "M3" << std::endl << m3 << std::endl;
//    std::cout << "Q1" << std::endl << q1 << std::endl;
//    std::cout << "M1" << std::endl << m1 << std::endl;

//  m1.setRotate( tball.getRotation() );
    m2.setTranslate( tball.getPosition() );
    
//std::cout << "Pos: " << tball.getPosition() << ", Rot: " << tball.getRotation() << std::endl;

//    std::cout << tball.getRotation() << std::endl;

    m1.mult( m2 );

//    std::cerr << m1 << std::endl;
    
    m1 = tball.getFullTrackballMatrix();

    if(move_obj == true)
    {
        scene_trans->editSFMatrix()->setValue( m1 );
    }
    else
    {
        cam_trans->editSFMatrix()->setValue( m1 );
    }

    OSG::commitChangesAndClear();

    win->render(rentravact);

    if(dumpImg == true)
    {
        vpFBO->setTravMask(oldTravMask);

        pTexBuffer                   ->setReadBack               (false);
        vpFBO->getFrameBufferObject()->setPostProcessOnDeactivate(false);

        pImg->write("/tmp/test.png");

        dumpImg = false;
    }

    if(dumpImg_RB == true)
    {
        pRenBuffer->getImage()->write("/tmp/test1.png");

        dumpImg_RB = false;

        win->subPortByObj(vpFBO_RB);

        vpFBO_RB   = NULL;
        pRenBuffer = NULL;

        win->runFrameExit();

//        OSG::FieldContainerFactory::the()->dump();
    }


//    win->render(renact);

//    std::cerr << "------------- AR START --------------" << std::endl;

//    Thread::getCurrentChangeList()->dump();
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
    

    OSG::Real32  a = -2. * ( lastx / w - .5 ),
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
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(true);
                                break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(true);
                                break;
        }
        mouseb |= 1 << button;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(false);
                                break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(false);
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
            root        = NULL;
            file        = NULL;
            cam         = NULL;
            vp          = NULL;
            win         = NULL;
            cam_trans   = NULL;
            scene_trans = NULL;
            pPoly       = NULL;
            pCOver      = NULL;
            gwin        = NULL;

            tx1o        = NULL;
            tx1e        = NULL;

            vpFBO       = NULL;
            vpFBO_RB    = NULL;
            pTexBuffer  = NULL;
            pRenBuffer  = NULL;
            pImg        = NULL;

            delete rentravact;

            OSG::osgExit(); 

            exit(0);
        case 'f':
            vpFBO->setTravMask(~vpFBO->getTravMask());
            break;
        case 'd':
            oldTravMask = vpFBO->getTravMask();

            if(oldTravMask == 0x0000)
            {
                vpFBO->setTravMask(~vpFBO->getTravMask());
            }

            dumpImg = true;

            pTexBuffer                   ->setReadBack               (true);
            vpFBO->getFrameBufferObject()->setPostProcessOnDeactivate(true);

            break;

        case 'r':
        {
//            OSG::FieldContainerFactory::the()->dump();
            //RenderBuffer Readback
            // Background
            OSG::SolidBackgroundUnrecPtr bkgndFBO_RB = 
                OSG::SolidBackground::create();

            bkgndFBO_RB->setColor(OSG::Color3f(0.5,1.0,0.5));
    
            // Viewport

            vpFBO_RB = OSG::FBOViewport::create();

            vpFBO_RB->setCamera    (cam        );
            vpFBO_RB->setBackground(bkgndFBO_RB);
            vpFBO_RB->setRoot      (root       );
            vpFBO_RB->setSize      (0, 0, 1, 1 );
            
            OSG::FrameBufferObjectUnrecPtr pFBO_RB = 
                OSG::FrameBufferObject::create();
            
            pRenBuffer = OSG::RenderBuffer::create();

            OSG::RenderBufferUnrecPtr  pDepthBuffer_RB = 
                OSG::RenderBuffer::create();

            pDepthBuffer_RB->setInternalFormat(GL_DEPTH_COMPONENT24   );
            pRenBuffer->setInternalFormat(GL_RGBA);
            
            OSG::ImageUnrecPtr pImg_RB = OSG::Image::create();
    
            OSG::UInt32 uiImgSize = 4096;

            pImg_RB->set(OSG::Image::OSG_RGB_PF, uiImgSize, uiImgSize);

            fprintf(stderr, "Image data : %p\n", pImg_RB->getData());

            pRenBuffer->setImage(pImg_RB);

            pFBO_RB->setSize(uiImgSize, uiImgSize);
    
            pFBO_RB->setColorAttachment(pRenBuffer,     0);
            pFBO_RB->setDepthAttachment(pDepthBuffer_RB  );

            pFBO_RB->editMFDrawBuffers()->clear();
            pFBO_RB->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

            vpFBO_RB->setFrameBufferObject(pFBO_RB);

            pRenBuffer                      ->setReadBack               (true);
            vpFBO_RB->getFrameBufferObject()->setPostProcessOnDeactivate(true);

            win->addPort(vpFBO_RB);

            dumpImg_RB = true;
        }
        break;

        case 'v':
            rentravact->setVolumeDrawing(!rentravact->getVolumeDrawing());
            break;
        case 'a':   
            glDisable( GL_LIGHTING );
            std::cerr << "Lighting disabled." << std::endl;
            break;
        case 's':   
            glEnable( GL_LIGHTING );
            std::cerr << "Lighting enabled." << std::endl;
            break;
        case 'z':   
            pPoly->setFrontMode(GL_POINT);
            pPoly->setBackMode(GL_POINT);
            std::cerr << "PolygonMode: Point." << std::endl;
            break;
        case 'x':   
            pPoly->setFrontMode(GL_LINE);
            pPoly->setBackMode(GL_LINE);
            std::cerr << "PolygonMode: Line." << std::endl;
            break;
        case 'c':   
            pPoly->setFrontMode(GL_FILL);
            pPoly->setBackMode(GL_FILL);
            std::cerr << "PolygonMode: Fill." << std::endl;
            break;
        case 'p':
        {
            if(bPolyActive == true)
            {
                OSG_ASSERT(pCOver->subChunk(pPoly) == true);
                bPolyActive = false;
            }
            else
            {
                OSG_ASSERT(pCOver->addChunk(pPoly) == true);
                bPolyActive = true;
            }
            break;
        }

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
//                m = scene_trans->getSFMatrix()->getValue();
                tball.setMode( OSG::Trackball::OSGCamera );

            }
            else
            {
                puts("moving camera");
//                m = cam_trans->getSFMatrix()->getValue();
                tball.setMode( OSG::Trackball::OSGObject );
            }
            
//            q.setValue(m);
            tball.setStartPosition( v, true );
            tball.setStartRotation( q, true );

//            std::cout << q << std::endl;
//            std::cout << v << std::endl;

//            std::cout << " " << m[3][0] << " " << m[3][1] << " " << m[3][2] << std::endl;
            
        }
        break;
    }
}


int init(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    glutIdleFunc(display);  

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
//    glEnable( GL_DEPTH_TEST );
//    glEnable( GL_LIGHTING );
//    glEnable( GL_LIGHT0 );
//    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);

    // OSG

    OSG::SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    OSG::NodeUnrecPtr b1n = OSG::Node::create();
    OSG::GroupUnrecPtr b1 = OSG::Group::create();

    b1n->setCore( b1 );

    // transformation
    OSG::NodeUnrecPtr t1n = OSG::Node::create();
    OSG::TransformUnrecPtr t1 = OSG::Transform::create();

    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light
    
    OSG::NodeUnrecPtr dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl = OSG::DirectionalLight::create();

    dlight->setCore( dl );
//    dlight->setCore( Group::create() );
    
    dl->setAmbient( .0, .0, .0, 1 );
    dl->setDiffuse( .8f, .8f, .8f, 1.f );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1 = OSG::Group::create();

    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file

    OSG::NodeUnrecPtr file = NULL;
    
    if(argc > 1)
        file = OSG::SceneFileHandler::the()->read(argv[1], NULL);
    
    if ( file == NULL )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

        file = OSG::makeSphere(4, 2.0);

    }

#if 0
    OSG::GeometryPtr pGeo = cast_dynamic<OSG::GeometryPtr>(file->getCore());
    
    if(pGeo == NULL && file->getNChildren() != 0)
    {
        pGeo = cast_dynamic<OSG::GeometryPtr>(file->getChild(0)->getCore());
    }

    if(pGeo == NULL)
    {
        fprintf(stderr, "no geo\n");
    }
#endif

//    OSG::GraphOpRefPtr op = OSG::GraphOpFactory::the()->create("Stripe");

//    op->traverse(file);
//    createOptimizedPrimitives(pGeo);
//    createSharedIndex(pGeo);
    
    OSG::Thread::getCurrentChangeList()->commitChanges();

//    file->dump();
    file->updateVolume();

#if 0
    const char *outFileName = "/tmp/foo1.osg";

    OSG::IndentFileOutStream outFileStream(outFileName);

    if( !outFileStream )
    {
        std::cerr << "Can not open output stream to file: "
                  << outFileName << std::endl;
        return -1;
    }

    std::cerr << "STARTING PRINTOUT:" << std::endl;
    OSGWriter writer( outFileStream, 4 );

    writer.write( file );

    outFileStream.close();

    OSG::SceneFileHandler::the()->write(file, "/tmp/foo.osb");
#endif    


//    return 0;


    OSG::Vec3f min,max;
    file->getVolume().getBounds( min, max );
    

    std::cout << "Volume: from " << min << " to " << max << std::endl;


    OSG::MultiCoreUnrecPtr pMCore = OSG::MultiCore::create();

    pCOver      = OSG::ChunkOverrideGroup::create();
    scene_trans = OSG::Transform::create();

    pMCore->addCore(scene_trans);
    pMCore->addCore(pCOver     );

    OSG::NodeUnrecPtr sceneTrN = OSG::Node::create();

    sceneTrN->setCore(pMCore);
    sceneTrN->addChild(file);


    dlight->addChild(sceneTrN);

    std::cerr << "Tree: " << std::endl;
//  root->dump();

    // Camera
    
    cam = OSG::PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( OSG::osgDegree2Rad( 90 ) );
    cam->setNear( 0.1f );
    cam->setFar( 100000 );

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(1,0,0));
    
    // Viewport

    vp = OSG::Viewport::create();

    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

#if 0
    OSG::UInt8 imgdata[] =
    {  
        64,64,64, 128,128,128, 192,192,192, 255,255,255 
    };
#endif

    pImg = OSG::Image::create();

    pImg->set(OSG::Image::OSG_RGB_PF, 128, 128); //, 1, 1, 1, 0.0, imgdata);

    tx1o = OSG::TextureObjChunk::create();
    tx1e = OSG::TextureEnvChunk::create();

    tx1o->setImage    (pImg      ); 
    tx1o->setMinFilter(GL_LINEAR );
    tx1o->setMagFilter(GL_LINEAR );
    tx1o->setWrapS    (GL_CLAMP );
    tx1o->setWrapT    (GL_CLAMP );
    tx1e->setEnvMode  (GL_REPLACE);

    OSG::SimpleMaterialUnrecPtr mat = OSG::SimpleMaterial::create();
    
    mat->setDiffuse(OSG::Color3f(1,1,1));
    mat->setLit    (false              );
    mat->addChunk  (tx1o               );
    mat->addChunk  (tx1e               );

    OSG::PolygonForegroundUnrecPtr pFG =  OSG::PolygonForeground::create();

    pFG->setMaterial(mat);

    OSG::MFPnt2f *pPos = pFG->editMFPositions();
    OSG::MFVec3f *pTex = pFG->editMFTexCoords();

    pPos->push_back(OSG::Pnt2f(0.0f, 0.0f));
    pPos->push_back(OSG::Pnt2f(0.3f, 0.0f));
    pPos->push_back(OSG::Pnt2f(0.3f, 0.3f));
    pPos->push_back(OSG::Pnt2f(0.0f, 0.3f));

    pTex->push_back(OSG::Vec3f(0.0f, 1.0f, 0.0f));
    pTex->push_back(OSG::Vec3f(1.0f, 1.0f, 0.0f));
    pTex->push_back(OSG::Vec3f(1.0f, 0.0f, 0.0f));
    pTex->push_back(OSG::Vec3f(0.0f, 0.0f, 0.0f));

    vp->addForeground(pFG);



    OSG::SimpleMaterialUnrecPtr matFgCheck = OSG::SimpleMaterial::create();
    
    matFgCheck->setDiffuse(OSG::Color3f(0,1,0));
    matFgCheck->setLit    (false              );

    OSG::PolygonForegroundUnrecPtr pFGCheck =  OSG::PolygonForeground::create();

    pFGCheck->setMaterial(matFgCheck);

    pPos = pFGCheck->editMFPositions();

    pPos->push_back(OSG::Pnt2f(0.6f, 0.0f));
    pPos->push_back(OSG::Pnt2f(0.9f, 0.0f));
    pPos->push_back(OSG::Pnt2f(0.9f, 0.3f));
    pPos->push_back(OSG::Pnt2f(0.6f, 0.3f));


    vp->addForeground(pFG);
    vp->addForeground(pFGCheck);
//    vp->dump();


    // Background
    OSG::SolidBackgroundUnrecPtr bkgndFBO = OSG::SolidBackground::create();

    bkgndFBO->setColor(OSG::Color3f(1.0,0.5,0.5));
    
    // Viewport

    vpFBO = OSG::FBOViewport::create();

    vpFBO->setCamera    (cam       );
    vpFBO->setBackground(bkgndFBO  );
    vpFBO->setRoot      (root      );
    vpFBO->setSize      (0, 0, 1, 1);

    vpFBO->addForeground(pFGCheck);

    OSG::FrameBufferObjectUnrecPtr pFBO = OSG::FrameBufferObject::create();

                               pTexBuffer   = OSG::TextureBuffer::create();
    OSG::RenderBufferUnrecPtr  pDepthBuffer = OSG::RenderBuffer ::create();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

    pTexBuffer->setTexture(tx1o);

    pFBO->setSize(128, 128);
    
    pFBO->setColorAttachment(pTexBuffer, 0);
    pFBO->setDepthAttachment(pDepthBuffer );

    pFBO->editMFDrawBuffers()->clear();
    pFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);


    vpFBO->setFrameBufferObject(pFBO);



    // Window
    std::cout << "GLUT winid: " << winid << std::endl;


    GLint glvp[4];

    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort(vpFBO   );
    win->addPort(vp      );

    win->init();

    // Action
    
    rentravact = OSG::RenderAction::create();
//    renact->setFrustumCulling(false);


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

    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(tCenter);

    // run...
    
    pPoly = OSG::PolygonChunk::create();

    pCOver->subChunk(pPoly);

    return 0;
}

int main (int argc, char **argv)
{
    init(argc, argv);

    glutMainLoop();
    
    return 0;
}

