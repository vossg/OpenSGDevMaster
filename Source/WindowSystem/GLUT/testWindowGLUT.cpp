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
#include "OSGFrameHandler.h"

#include "OSGTrackball.h"

OSG::RenderActionRefPtr rentravact = NULL;

OSG::NodeRecPtr  root;

//OSG::NodeRecPtr  file;

OSG::PerspectiveCameraRecPtr cam;
OSG::ViewportRecPtr vp;
OSG::WindowRecPtr win;

OSG::TransformRecPtr cam_trans;
OSG::TransformRecPtr scene_trans;

OSG::PolygonChunkRecPtr       pPoly;
bool                     bPolyActive = false;
OSG::ChunkOverrideGroupRecPtr pCOver;

OSG::GLUTWindowUnrecPtr gwin;

OSG::Trackball tball;

bool move_obj = false;

int mouseb = 0;
int lastx=0, lasty=0;

OSG::Quaternion oldq;
OSG::Vec3f      oldv;

void 
display(void)
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

    OSG::FrameHandler::the()->frame();

    OSG::commitChanges();

    win->render(rentravact);

//    win->render(renact);

//    std::cerr << "------------- AR START --------------" << std::endl;

//    Thread::getCurrentChangeList()->dump();
}

void reshape( int w, int h )
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize( w, h );
}


void
animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void
motion(int x, int y)
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

void
mouse(int button, int state, int x, int y)
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

void
vis(int visible)
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
            OSG::FrameHandler::the()->shutdown();

            root        = NULL;
//            file        = NULL;
            cam         = NULL;
            vp          = NULL;
            win         = NULL;
            cam_trans   = NULL;
            scene_trans = NULL;
            pPoly       = NULL;
            pCOver      = NULL;
            gwin        = NULL;

            rentravact  = NULL;

            OSG::osgExit(); 

            exit(0);
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

    OSG::setVBOUsageOnPropertyProtos(true);

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
//    glEnable(GL_CULL_FACE);

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
        file = OSG::SceneFileHandler::the()->read(argv[1], NULL, NULL);
    
    if ( file == NULL )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

        file = OSG::makeSphere(4, 2.0);

    }

    OSG::Thread::getCurrentChangeList()->commitChanges();

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

    OSG::GraphOpRefPtr op = OSG::GraphOpFactory::the()->create("Stripe");

//    op->traverse(file);
//   createOptimizedPrimitives(pGeo);
//    createSharedIndex(pGeo);
    

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
    OSG::OSGWriter writer( outFileStream, 4 );

    writer.write( file );

    outFileStream.close();

    OSG::SceneFileHandler::the()->write(file, "/tmp/foo.osb");
#endif    


//    return 0;


    OSG::Vec3f min,max;
    file->getVolume().getBounds( min, max );
    

    std::cout << "Volume: from " << min << " to " << max << std::endl;


//    NodePtr pChunkOverNode = Node::create();
  

//    pChunkOverNode->setCore(pCOver);
//    pChunkOverNode->addChild(file);

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
    cam->setFar( 10000 );

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(0.1,0.1,0.1));
    
    // Viewport

    vp = OSG::Viewport::create();

    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

//    vp->dump();

    // Window
    std::cout << "GLUT winid: " << winid << std::endl;


    GLint glvp[4];

    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort( vp );

    win->init();

    // Action
    
    rentravact = OSG::RenderAction::create();
//    renact->setFrustumCulling(false);

    rentravact->setCorrectTwoSidedLighting(true);

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

    fprintf(stderr, "%d\n", 
            OSG::MFUnrecNodePtr          ::getClassType().getId());
    fprintf(stderr, "%d\n", 
            OSG::MFUnrecFieldContainerPtr::getClassType().getId());

//    MFNodePtr          ::getClassType().dump();
//    MFFieldContainerPtr::getClassType().dump();

    // run...
    
    pPoly = OSG::PolygonChunk::create();

    pCOver->subChunk(pPoly);

#if 0
    GroupNodePtr pGr = GroupNodePtr::create();

    NodePtr  pN;
    GroupPtr pG;

    fprintf(stderr, "A\n");

    if(pGr == NULL)
    {
    }

    fprintf(stderr, "B\n");

    if(pGr == pN)
    {
    }

    fprintf(stderr, "C\n");

    if(pGr == pG)
    {
    }

    pGr = NULL;
#endif

    OSG::FrameHandler::the()->init();

    return 0;
}

int main (int argc, char **argv)
{
    init(argc, argv);

    glutMainLoop();
    
    return 0;
}

