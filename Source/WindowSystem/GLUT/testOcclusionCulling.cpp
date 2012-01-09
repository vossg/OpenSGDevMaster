
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGConfigured.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"

#include "OSGDrawable.h"
#include "OSGSimpleStatisticsForeground.h"
#include "OSGStatElemTypes.h"
#include "OSGStatCollector.h"

#include <boost/bind.hpp>

#include "OSGTextureBaseChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGSimpleSHLChunk.h"

#include "OSGStatStringElem.h"
#include "OSGSimplePool.h"
#include "OSGRenderTreeNode.h"
#include "OSGOcclusionCullingTreeBuilder.h"

#ifdef OSG_WITH_NVPERFSDK
#include <NVPerfSDK.h>


OSG::StatElemDesc<OSG::StatStringElem> GPUIdleStat("GPUIdle","GPUIdle",
            OSG::StatElemDescBase::RESET_NEVER);
OSG::StatElemDesc<OSG::StatStringElem> PSBusyStat("PSBusyStat","PSBusyStat",
            OSG::StatElemDescBase::RESET_NEVER);
OSG::StatElemDesc<OSG::StatStringElem> VSBusyStat("VSBusyStat","VSBusyStat",
            OSG::StatElemDescBase::RESET_NEVER);
OSG::StatElemDesc<OSG::StatStringElem> TextureWaitStat("TextureWait","TextureWait",
            OSG::StatElemDescBase::RESET_NEVER);
OSG::StatElemDesc<OSG::StatStringElem> OGLFPSStat("OGL FPS","OGL FPS",
            OSG::StatElemDescBase::RESET_NEVER);

OSG::StatElemDesc<OSG::StatStringElem> *nvStatElems[] = 
    { &GPUIdleStat, &PSBusyStat, &VSBusyStat, &TextureWaitStat, &OGLFPSStat,
      NULL };

#endif

OSG::SimpleSceneManagerRefPtr mgr;
OSG::RenderActionRefPtr       tact = NULL;
OSG::RenderActionRefPtr       debugact = NULL;

// create the scene
OSG::NodeRecPtr scene;

OSG::GLUTWindowRecPtr mainwin;
OSG::GLUTWindowRecPtr debugwin;
int mainwinid = -1, debugwinid = -1;

OSG::SimpleStatisticsForegroundRecPtr statfg;
OSG::StatCollector         *collector;

bool show = true;
bool debug = false;
bool bGLFinish = false;



#ifdef OSG_WITH_NVPERFSDK
const GLuint counterEntryCount = 10;
const GLuint bufferEntryCount = 100;

// A simple class to manage counters, sampling, and display of the information
class NVDataProvider
{
    public:
        NVDataProvider()
            {
                // We're averaging these, so we'll need to initialize to zero
                for (GLuint i = 0; i < counterEntryCount; i++) {
                    for (GLuint j = 0; j < bufferEntryCount; j++) {
                        m_counterValues[i][j] = 0.0f;
                    }
                }
                m_counterIndexArrayCount = 0;
                m_counterValuesRRIndex = 0;
            }
        
        virtual size_t nCounters() const
            {
                return m_counterIndexArrayCount;
            }

        virtual bool add(GLuint counterIndex)
            {
                if (NVPMAddCounter(counterIndex) == NVPM_OK) {
                    m_counterIndexArray[m_counterIndexArrayCount++] = counterIndex;
                    return true;
                } else {
                    return false;
                }
            }
            
        virtual bool add(const char *counterName)
            {
                GLuint counterIndex;
                if (NVPMGetCounterIndex(const_cast<char *>(counterName), &counterIndex) == NVPM_OK) {
                    return add(counterIndex);
                } else {
                    return false;
                }
            }

        virtual bool removeAllCounters()
            {
                NVPMRemoveAllCounters();

                while (m_counterIndexArrayCount) {
                    m_counterIndexArray[--m_counterIndexArrayCount] = 0;
                }
                
                return true;
            }

        virtual bool sample()
            {
                GLuint counterIndex, unused;
                UINT64 events, cycles;

                // Sample the GPU counters
                NVPMSample(NULL, &unused);

                // Retrieve the current sample values
                for (counterIndex = 0;
                     counterIndex < m_counterIndexArrayCount;
                     counterIndex++) 
                {
                    NVPMGetCounterValue(m_counterIndexArray[counterIndex], 0, &events, &cycles);
                    
                    m_counterValues[counterIndex][m_counterValuesRRIndex] =
                        100.0f * float(events) / float(cycles);
                }
                m_counterValuesRRIndex++;
                if (m_counterValuesRRIndex >= bufferEntryCount) {
                    m_counterValuesRRIndex = 0;
                }
                
                return true;
            }
            
        virtual float value(const GLuint counterIndex) const
            {
                GLuint entryIndex;
                GLfloat runningTotal = 0.0f;
                for (entryIndex = 0; entryIndex < bufferEntryCount; entryIndex++) {
                    runningTotal += 
                        m_counterValues[counterIndex][entryIndex] / float(bufferEntryCount);
                }
                return runningTotal;
            }

    protected:
        GLuint m_counterIndexArray[counterEntryCount];
        GLuint m_counterIndexArrayCount;

        // Maintain a round-robin style buffer and display the average of the
        // the last bufferEntryCount samples.
        GLfloat m_counterValues[counterEntryCount][bufferEntryCount];
        GLuint  m_counterValuesRRIndex;

} g_nvDataProvider;    

NVDataProvider *nvDataProvider = &g_nvDataProvider;

bool runExperiment = false;

#endif

// redraw the window
void display(void)
{   
    if(glutGetWindow() == mainwinid)
    {
#ifdef OSG_WITH_NVPERFSDK
        if(nvDataProvider->nCounters())
        {
            nvDataProvider->sample();

            OSG::Char8 str[40];
            
            for(int i = 0; nvStatElems[i] != NULL; ++i)
            {
                if(collector != NULL)
                {
                    sprintf(str, "%s: %f", nvStatElems[i]->getDescription().c_str(),
                            nvDataProvider->value(i)); 

                    OSG::StatStringElem *e = dynamic_cast<OSG::StatStringElem*>(
                        collector->getElem(*nvStatElems[i]));  

                    e->set(str);
                }
            }
        }
        
        if(runExperiment)
        {
            int nCount;
            
            const char *expCounters[] = { 
                "2D Bottleneck", "2D SOL", 
                "IDX Bottleneck", "IDX SOL", 
                "GEOM Bottleneck", "GEOM SOL", 
                "ZCULL Bottleneck", "ZCULL SOL", 
                "TEX Bottleneck", "TEX SOL", 
                "ROP Bottleneck", "ROP SOL", 
                "SHD Bottleneck", "SHD SOL", 
                "FB Bottleneck", "FB SOL", 
                "GPU Bottleneck", // Needs to be last 
                NULL };
            
            for(int i = 0; expCounters[i] != NULL; ++i)
            {
                NVPMAddCounterByName(const_cast<char *>(expCounters[i]));
            }
            
            NVPMBeginExperiment(&nCount);
            
            FLOG(("NVPerfKitSDK: Running %d passes\n", nCount));
            
            for(int i = 0; i < nCount; i++)
            {
                NVPMBeginPass(i);
                mgr->redraw();
                NVPMEndPass(i);
            }
            NVPMEndExperiment();
            
            UINT64 value, cycles;
            
            for(int i = 0; expCounters[i] != NULL; ++i)
            {
                NVPMGetCounterValueByName(const_cast<char *>(expCounters[i]), 0, &value, &cycles);
                FLOG(("%s: %lld value, %lld cycles (%.4f%%)\n", 
                        expCounters[i], value, cycles, value * 100. / cycles));
            }
            
            char buffer[1000] = "";
            
            NVPMGetGPUBottleneckName(value, buffer);

            FLOG(("GPU Bottleneck: '%s'\n", buffer));

            for(int i = 0; expCounters[i] != NULL; ++i)
            {
                //NVPMRemoveCounterByName(expCounters[i]);               
            }
            
            runExperiment = false;
        }
#endif
        mgr->redraw();
    }
    else if(glutGetWindow() == debugwinid)
    {
        // Use RenderAction to prevent new occlusion culling on debug output
        debugwin->render(debugact);
    }
}

// Redisplay both windows, if active
void redisplay(void)
{
    glutSetWindow(mainwinid);
    glutPostRedisplay();
    if(debugwinid > 0)
    {
        glutSetWindow(debugwinid);
        glutPostRedisplay();
    }
}

void idle(void)
{   
    redisplay();
}

// react to size changes
void reshape(int w, int h)
{
    if(glutGetWindow() == mainwinid)
    {
        mgr->resize(w,h);
        glutPostRedisplay();
    }
    else if(glutGetWindow() == debugwinid)
    {
        debugwin->resize(w,h);
        glutPostRedisplay();       
    }
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    redisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);

    redisplay();
}

void initElements(void)
{
    if(collector != NULL)
    {
        collector->clearElems();
    }

    // add optional elements
//    collector->getElem(Drawable::statNTriangles);
}


// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
        case 27:    
        {
#ifdef OSG_WITH_NVPERFSDK
            NVPMShutdown();
#endif
            mgr      = NULL;

            tact     = NULL;
            debugact = NULL;
            
            scene    = NULL;
            mainwin  = NULL;
            debugwin = NULL;
            statfg   = NULL;

            OSG::osgExit();
            exit(0);
        }
        
#ifdef OSG_OLD_RENDER_ACTION
        case 'v':
        {
            mgr->getAction()->setVolumeDrawing(
                                    !mgr->getAction()->getVolumeDrawing());
		    std::cerr << "Volume Drawing: " 
                      << (mgr->getAction()->getVolumeDrawing()?"on":"off") 
                      << std::endl;
        }
        
        case 'z':
        {
            OSG::RenderAction *ract = 
                dynamic_cast<OSG::RenderAction *>(mgr->getAction());

            ract->setZWriteTrans(!ract->getZWriteTrans());

		    std::cerr << "Switch TransZWrite to " 
                      << (ract->getZWriteTrans()?"on":"off") 
                      << std::endl;
             
        }
        break;
#endif

        case 'r':
        {
            initElements();
            bool buseTrav = mgr->getUseTraversalAction();
            buseTrav = !buseTrav;
            mgr->setUseTraversalAction(buseTrav);
         }
         break;

#ifdef OSG_OLD_RENDER_ACTION
        case 'n':
            fprintf(stderr, "1) set s sorting to %d\n", act->getStateSorting());
            act->setStateSorting(!act->getStateSorting());
            fprintf(stderr, "2) set s sorting to %d\n", act->getStateSorting());
            break;
#endif

        case 'k':
            tact->setKeyGen(0);
            break;

        case 's':
        {
            OSG::UInt32 uiSId = OSG::SimpleSHLChunk  ::getStaticClassId() & 0x000003FF;
            OSG::UInt32 uiTId = OSG::TextureBaseChunk::getStaticClassId() & 0x000003FF;
            OSG::UInt32 uiMId = OSG::MaterialChunk   ::getStaticClassId() & 0x000003FF;
            
  
            OSG::UInt32 uiKeyGen = (uiSId) | (uiTId << 10) | (uiMId << 20);

            tact->setKeyGen(uiKeyGen);
        }
        break;

        case 'g':
            bGLFinish = !bGLFinish;
            tact->setUseGLFinish(bGLFinish);
#ifdef OSG_OLD_RENDER_ACTION
            act->setUseGLFinish(bGLFinish);
#endif
            break;


        case 'C':
        {
            OSG::Real32 cov = tact->getOcclusionCullingCoveredThreshold();
            cov+=0.1f;
            tact->setOcclusionCullingCoveredThreshold(cov);
            std::cout << "Covered Threshold now: " << cov << std::endl;
        }
        break;
            
        case 'c':
        {
            OSG::Real32 cov1 = tact->getOcclusionCullingCoveredThreshold();
            cov1-=0.1f;
            tact->setOcclusionCullingCoveredThreshold(cov1);
            std::cout << "Covered Threshold now: " << cov1 << std::endl;
        }
            break;

        case 'M':
        {
            OSG::UInt32 minFSize = tact->getOcclusionCullingMinimumFeatureSize();
            minFSize+=1;
            tact->setOcclusionCullingMinimumFeatureSize(minFSize);
            std::cout << "Minimum Feature Size now: " << minFSize << std::endl;
        }
        break;
            
        case 'm':
        {
            OSG::UInt32 small1 = tact->getOcclusionCullingMinimumFeatureSize();
            small1-=1;
            tact->setOcclusionCullingMinimumFeatureSize(small1);
            std::cout << "Minimum Feature Size now: " << small1 << std::endl;
        }
        break;
        
        case 'I':
        {
            OSG::UInt32 visT = tact->getOcclusionCullingVisibilityThreshold();
            visT+=1;
            tact->setOcclusionCullingVisibilityThreshold(visT);
            std::cout << "Visibility Threshold now: " << visT << std::endl;
        }
        break;

        case 'i':
        {
            OSG::UInt32 visTa = tact->getOcclusionCullingVisibilityThreshold();
            visTa-=1;
            tact->setOcclusionCullingVisibilityThreshold(visTa);
            std::cout << "Visibility Threshold now: " << visTa << std::endl;
        }
        break;

        case 'l':
        {
            OSG::UInt32 numLev = tact->getScreenLODNumLevels();
            numLev-=1;
            tact->setScreenLODNumLevels(numLev);
            std::cout << "LOD's in use now: " << numLev << std::endl;
        }
        break;

        case 'L':
        {
            OSG::UInt32 numLeva = tact->getScreenLODNumLevels();
            numLeva+=1;
            tact->setScreenLODNumLevels(numLeva);
            std::cout << "LOD's in use now: " << numLeva << std::endl;
        }
        break;

        case 'B':
        {
            OSG::UInt32 bfsz = tact->getOcclusionCullingQueryBufferSize();
            bfsz+=200;
            tact->setOcclusionCullingQueryBufferSize(bfsz);
            std::cout << "Query Buffer Size now: " << bfsz << std::endl;
        }
        break;

        case 'b':
        {
            OSG::UInt32 bfsza = tact->getOcclusionCullingQueryBufferSize();
            bfsza-=200;
            tact->setOcclusionCullingQueryBufferSize(bfsza);
            std::cout << "Query Buffer Size now: " << bfsza << std::endl;
        }
        break;

        case 't':
        {
            OSG::UInt32 tcount = tact->getOcclusionCullingMinimumTriangleCount();
            tcount-=50;
            tact->setOcclusionCullingMinimumTriangleCount(tcount);
            std::cout << "Minimum Triangle Count now: " << tcount << std::endl;
        }
        break;

        case 'T':
        {
            OSG::UInt32 tcounta = tact->getOcclusionCullingMinimumTriangleCount();
            tcounta+=50;
            tact->setOcclusionCullingMinimumTriangleCount(tcounta);
            std::cout << "Minimum Triangle Count now: " << tcounta << std::endl;
        }
        break;

        case 'H':
        {
            OSG::UInt32 mfsa = 0;
            OSG::Real32 sfta = 0.0f;
            tact->setOcclusionCullingMinimumFeatureSize(mfsa);
            tact->setOcclusionCullingVisibilityThreshold(mfsa);
            tact->setScreenLODCoverageThreshold(sfta);
            std::cout << "High Resolution Mode" << std::endl;
        }
        break;

        case 'h':
        {
            OSG::UInt32 mfs = 1000;
            OSG::Real32 sft = 0.15f;
            tact->setOcclusionCullingMinimumFeatureSize(mfs);
            tact->setOcclusionCullingVisibilityThreshold(mfs);
            tact->setScreenLODCoverageThreshold(sft);
            std::cout << "Low Resolution Mode" << std::endl;
        }
        break;

        case 'P':
        {
            OSG::Real32 cover = tact->getScreenLODCoverageThreshold();
            cover+=0.001f;
            tact->setScreenLODCoverageThreshold(cover);
            std::cout << "ScreenLOD Coverage Threshold now: " << cover << std::endl;
        }
        break;
            
        case 'p':
        {
            OSG::Real32 covera = tact->getScreenLODCoverageThreshold();
            covera-=0.001f;
            tact->setScreenLODCoverageThreshold(covera);
            std::cout << "ScreenLOD Coverage Threshold now: " << covera << std::endl;
        }
        break;

        case 'D':
        {
            OSG::Real32 user_dega = tact->getScreenLODDegradationFactor();
            user_dega+=0.01f;
            tact->setScreenLODDegradationFactor(user_dega);
            std::cout << "ScreenLOD User Degradation Factor now: " << user_dega << std::endl;
        }
        break;

        case 'd':
        {
            OSG::Real32 user_deg = tact->getScreenLODDegradationFactor();
            user_deg-=0.01f;
            tact->setScreenLODDegradationFactor(user_deg);
            std::cout << "ScreenLOD User Degradation Factor now: " << user_deg << std::endl;
        }
        break;
        
        case 'N':
        {
            OSG::Real32 coverb = tact->getScreenLODCoverageThreshold();
            coverb=0.0;
            tact->setScreenLODCoverageThreshold(coverb);
            std::cout << "ScreenLOD Coverage Threshold now: " << coverb << std::endl;
        }
        break;

        case 'o':
        {
            tact->setOcclusionCulling(false);
            std::cout << "OCC Off" << std::endl;
        }
        break;

        case 'O':
        {
            tact->setOcclusionCulling(true);
            std::cout << "OCC On" << std::endl;
        }
        break;

        case 'f':
        {
            std::cout << "Freeze Occlusion result" << std::endl;
            
            //initElements();
            mgr->setUseTraversalAction(false);
            
            // Render stuff that is visible and tested
            mgr->getWindow()->getPort(0)->setTravMask(0x5);
        }
        break;
        
        case 'F':
        {
            std::cout << "Unfreeze Occlusion result" << std::endl;
            
            //initElements();
            mgr->setUseTraversalAction(true);
            
            mgr->getWindow()->getPort(0)->setTravMask(0xffffffff);
        }
        break;

        case 'W':
        {
            std::string sss = "out.osb";
            OSG::SceneFileHandler::the()->write(scene, sss.c_str());
        }
        break;

#ifdef OSG_WITH_NVPERFSDK
        case 'e':
            runExperiment = true;
            break;
#endif
    }

    redisplay();
}

OSG::Action::ResultE initMask(OSG::Node *n)
{
    // Make Geometries render in main window, but nowhere else.
    if(n->getCore()->getType().isDerivedFrom(OSG::Geometry::getClassType()))
        n->setTravMask(0x800000); 
    
    return OSG::Action::Continue;
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    if(argc > 1 && !strcmp(argv[1],"-s"))
    {
        show = false;
        argv++;
        argc--;
    }
    
    if(argc > 1 && !strcmp(argv[1],"-d"))
    {
        debug = true;
        argv++;
        argc--;
    }

    
    if(argc > 1)
    {
        scene = OSG::Node::create();
        OSG::GroupUnrecPtr g = OSG::Group::create();
        
        scene->setCore(g);
        
        for(OSG::UInt16 i = 1; i < argc; ++i)
            scene->addChild(OSG::SceneFileHandler::the()->read(argv[i]));
    }
    else
    {
        scene = OSG::makeTorus(.5, 3, 16, 16);
    }

    // GLUT init
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1024, 768);
    mainwinid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    OSG::GLUTWindowUnrecPtr mainwin=OSG::GLUTWindow::create();
    mainwin->setGlutId(mainwinid);
    mainwin->init();
    
    // create the SimpleSceneManager helper
    mgr = OSG::SimpleSceneManager::create();

    // create the window and initial camera/viewport
    mgr->setWindow(mainwin);
    // tell the manager what to manage
    mgr->setRoot  (scene);

    OSG::commitChanges();

    // show the whole scene
    mgr->showAll();

    mgr->setUseTraversalAction(true);

    tact      = OSG::RenderAction::create();
#ifdef OSG_OLD_RENDER_ACTION
    act       = OSG::RenderAction::create();
#endif
    debugact  = OSG::RenderAction::create();
    tact->setOcclusionCulling(true);


    // Open the debug window
    if(debug)
    {
        OSG::traverse(scene, initMask);

        glutInitWindowSize(800, 400);
        debugwinid = glutCreateWindow("OpenSG Occlusion Debugging");

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutKeyboardFunc(keyboard);

        debugwin=OSG::GLUTWindow::create();
        debugwin->setGlutId(debugwinid);
        debugwin->init();       
        
        OSG::ViewportUnrecPtr vp = mainwin->getPort(0);
        
        OSG::ViewportUnrecPtr newvp = OSG::Viewport::create();        
        newvp->setLeft(0);
        newvp->setRight(0.5);
        newvp->setBottom(0);
        newvp->setTop(1);
        newvp->setRoot(vp->getRoot());
        newvp->setCamera(vp->getCamera());
        newvp->setBackground(vp->getBackground());
        newvp->setTravMask(0x1);
        debugwin->addPort(newvp);
        
        newvp = OSG::Viewport::create();        
        newvp->setLeft(0.5);
        newvp->setRight(1);
        newvp->setBottom(0);
        newvp->setTop(1);
        newvp->setRoot(vp->getRoot());
        newvp->setCamera(vp->getCamera());
        newvp->setBackground(vp->getBackground());
        newvp->setTravMask(0x2);
        debugwin->addPort(newvp);
        
        tact->setOcclusionCullingDebug(true);
        tact->setOcclusionDebugMasks(0x1, 0x2, 0x4);
    }

    // add the statistics forground
    
    statfg = OSG::SimpleStatisticsForeground::create();
    
    statfg->setSize(25);
    statfg->setColor(OSG::Color4f(0,1,0,0.7f));

    statfg->addElement(OSG::RenderAction::statDrawTime, 
                       "Draw FPS: %r.3f");
    statfg->addElement(OSG::RenderAction::statNMatrices, 
                       "Matrix Changes: %d");
    //statfg->addElement(RenderAction::statNGeometries, 
    //                   "Geometries drawn: %d");
    statfg->addElement(OSG::RenderAction::statNStates, 
                       "State Changes: %d");
    //statfg->addElement(RenderAction::statNShaders, 
    //                   "Shader Changes: %d");
    //statfg->addElement(RenderAction::statNShaderParams, 
    //                   "Shader Param Changes: %d");
                       
    statfg->addElement(OSG::RenderPartition::statCullTestedNodes, 
                       "Cull-tested Nodes: %d");
    statfg->addElement(OSG::RenderPartition::statCulledNodes, 
                       "Culled Nodes: %d");

    statfg->addElement(OSG::OcclusionCullingTreeBuilder::statNOccNodes, 
                       "Nodes in DrawTree: %d");
    statfg->addElement(OSG::OcclusionCullingTreeBuilder::statNOccTests, 
                       "Occ Tests: %d");
    statfg->addElement(OSG::OcclusionCullingTreeBuilder::statNOccInvisible, 
                       "Invisible Nodes: %d");
    statfg->addElement(OSG::OcclusionCullingTreeBuilder::statNOccSuccessTestPer, 
                       "OCC Success rate: %per%%");

    statfg->addElement(OSG::RenderAction::statNTriangles, 
                       "Triangles:        %d");
    statfg->addElement(OSG::OcclusionCullingTreeBuilder::statNOccTriangles, 
                       "Triangles culled: %d");
   
    collector = statfg->getCollector();

    tact->setStatCollector(collector);
#ifdef OSG_OLD_RENDER_ACTION
    act ->setStatCollector(collector);
#endif

    mgr->setAction(tact);
#ifdef OSG_OLD_RENDER_ACTION
    mgr->setAction( act);
#endif

    //tact->setOcclusionCullingMinimumFeatureSize(15);
    //tact->setOcclusionCullingVisibilityThreshold(15);
    //tact->setScreenLODCoverageThreshold(0.005);
    
    if(show)
    {
        mainwin->getPort(0)->addForeground(statfg);
    }

#ifdef OSG_WITH_NVPERFSDK
    NVPMRESULT status;

    status = NVPMInit();
    if (status != NVPM_OK) {
        FFATAL(("NVPerfSDK failed to initialize - no GPU data will be available"));
    }
    else
    {
        nvDataProvider->add("gpu_idle");
        nvDataProvider->add("pixel_shader_busy");
        nvDataProvider->add("vertex_shader_busy");
        nvDataProvider->add("shader_waits_for_texture");
        if (!nvDataProvider->add("OGL FPS")) 
            FLOG(("nvDataProvider::add: 'OGL FPS' failed!\n"));
        
        statfg->addElement(GPUIdleStat);
        statfg->addElement(PSBusyStat);
        statfg->addElement(VSBusyStat);
        statfg->addElement(TextureWaitStat);
        statfg->addElement(OGLFPSStat);        
    }
#endif
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
