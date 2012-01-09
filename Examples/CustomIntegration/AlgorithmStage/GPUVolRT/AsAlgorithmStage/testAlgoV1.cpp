#include "OSGConfig.h"

#include <iostream>

#include "OSGGLUT.h"

#include "OSGChunkOverrideGroup.h"
#include "OSGGLUTWindow.h"
#include "OSGTrackball.h"
#include "OSGPolygonChunk.h"
#include "OSGSceneFileHandler.h"
#include "OSGRenderAction.h"
#include "OSGMultiCore.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGDirectionalLight.h"
#include "OSGTransform.h"
#include "OSGSimpleGeometry.h"

#include "OSGAlgorithmStage.h"
#include "OSGGPUVolRTV1.h"

OSG::RenderActionRefPtr       rentravact;

OSG::WindowRecPtr             win;

OSG::TransformRecPtr          cam_trans;

OSG::PolygonChunkRecPtr       pPoly;
OSG::ChunkOverrideGroupRecPtr pCOver;

OSG::GPUVolRTV1UnrecPtr       pAlgo;

bool                          bPolyActive = false;

OSG::Trackball                tball;

int                           mouseb = 0;
int                           lastx  = 0;
int                           lasty  = 0;

void display(void)
{
    OSG::Matrix m1;
    
    m1 = tball.getFullTrackballMatrix();

    cam_trans->editSFMatrix()->setValue(m1);

    OSG::commitChanges();

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
    

    OSG::Real32  a = -2. * ( lastx / w - .5 ),
                 b = -2. * ( .5 - lasty / h ),
                 c = -2. * ( x / w - .5 ),
                 d = -2. * ( .5 - y / h );

    if(mouseb & (1 << GLUT_LEFT_BUTTON))
    {
        tball.updateRotation(a, b, c, d);
    }
    else if(mouseb & (1 << GLUT_MIDDLE_BUTTON))
    {
        tball.updatePosition(a, b, c, d);
    }
    else if(mouseb & (1 << GLUT_RIGHT_BUTTON))
    {
        tball.updatePositionNeg(a, b, c, d);  
    }

    lastx = x;
    lasty = y;
}

void mouse(int button, int state, int x, int y)
{
    if(state == 0)
    {
        switch(button)
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
    else if(state == 1)
    {
        switch(button)
        {
            case GLUT_LEFT_BUTTON:  
                break;
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
            win         = NULL;
            cam_trans   = NULL;
            pPoly       = NULL;
            pCOver      = NULL;
            pAlgo       = NULL;

            rentravact  = NULL;

            OSG::osgExit(); 

            exit(0);

        case 'v':
            rentravact->setVolumeDrawing(!rentravact->getVolumeDrawing());
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

		case 'w':
			pAlgo->setStepsize(pAlgo->getStepsize() + (1.0/2048.0));

			if(pAlgo->getStepsize() > 0.25) 
                pAlgo->setStepsize(0.25);

			break;

		case 'e':
			pAlgo->setStepsize(pAlgo->getStepsize() - (1.0/2048.0));
            
			if(pAlgo->getStepsize() <= 1.0/200.0) 
                pAlgo->setStepsize(1.0/200.0);
			break;

        case 'd':
            pAlgo->setToggleVisuals(!pAlgo->getToggleVisuals());
            break;

        default:
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

    // OSG
    OSG::SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    OSG::NodeUnrecPtr b1n = OSG::Node::create();
    OSG::GroupUnrecPtr b1 = OSG::Group::create();

    b1n->setCore(b1);

    // transformation
    OSG::NodeUnrecPtr      t1n = OSG::Node::create();
    OSG::TransformUnrecPtr t1  = OSG::Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    cam_trans = t1;

    // light
    OSG::NodeUnrecPtr             dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl     = OSG::DirectionalLight::create();

    dlight->setCore(dl);
    
    dl->setAmbient  (0.0, 0.0, 0.0, 1.0);
    dl->setDiffuse  (0.8, 0.8, 0.8, 1.0);
    dl->setDirection(0.0, 0.0, 1.0     );
    dl->setBeacon   (b1n               );

    // root
    OSG::NodeUnrecPtr  root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1  = OSG::Group::create();

    root->setCore (gr1   );
    root->addChild(t1n   );
    root->addChild(dlight);

    // Load the file
    OSG::NodeUnrecPtr file = NULL;
    
    if(argc > 1)
    {
        file = OSG::SceneFileHandler::the()->read(argv[1], NULL);
    }

    if(file == NULL)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

        //file = OSG::makeSphere(4, 2.0);

        file = OSG::Node::create();
        OSG::AlgorithmStageUnrecPtr pStage = OSG::AlgorithmStage::create();

        file->setCore(pStage);

        pAlgo = OSG::GPUVolRTV1::create();

        pStage->setAlgorithm(pAlgo);

        // fix/freeze the node volume
        file->editVolume().setStatic(true);
        file->editVolume().setBounds( 0.f,   0.f,   0.f,
                                      1.f,   1.f,   1.f);
        
   }
   
    OSG::commitChanges();

    file->updateVolume();


    OSG::Vec3f min,max;
    file->getVolume().getBounds( min, max );
    

    std::cout << "Volume: from " << min << " to " << max << std::endl;



    OSG::MultiCoreUnrecPtr pMCore = OSG::MultiCore::create();

                         pCOver      = OSG::ChunkOverrideGroup::create();
    OSG::TransformRecPtr scene_trans = OSG::Transform::create();

    pMCore->addCore(scene_trans);
    pMCore->addCore(pCOver     );

    pPoly = OSG::PolygonChunk::create();

    OSG::NodeUnrecPtr sceneTrN = OSG::Node::create();

    sceneTrN->setCore (pMCore);
    sceneTrN->addChild(file  );

    dlight->addChild(sceneTrN);


    // Camera
    
    OSG::PerspectiveCameraRecPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon(b1n                   );
    cam->setFov   (OSG::osgDegree2Rad(60));
    cam->setNear  (0.1                   );
    cam->setFar   (400                   );

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(0,0,0));
    
    // Viewport
    OSG::ViewportRecPtr vp = OSG::Viewport::create();

    vp->setCamera    (cam       );
    vp->setBackground(bkgnd     );
    vp->setRoot      (root      );
    vp->setSize      (0, 0, 1, 1);


    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLint glvp[4];

    glGetIntegerv(GL_VIEWPORT, glvp);

    OSG::GLUTWindowUnrecPtr gwin = OSG::GLUTWindow::create();

    gwin->setGlutId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort(vp);

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

    tball.setMode            (OSG::Trackball::OSGObject);
    tball.setStartPosition   (pos, true                );
    tball.setSum             (true                     );
    tball.setTranslationMode (OSG::Trackball::OSGFree  );
    tball.setTranslationScale(scale                    );
    tball.setRotationCenter  (tCenter                  );

    // run...


    return 0;
}

int main (int argc, char **argv)
{
    init(argc, argv);

    glutMainLoop();
    
    return 0;
}

