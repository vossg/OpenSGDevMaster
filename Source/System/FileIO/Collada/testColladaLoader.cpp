// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

// Headers
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"

// New Headers

// the general scene file loading handler
#include "OSGSceneFileHandler.h"

#include "OSGFieldContainerUtils.h"
#include "OSGChunkOverrideGroup.h"
#include "OSGPolygonChunk.h"
#include "OSGGeoFunctions.h"

#include "OSGSkinnedGeometry.h"
#include "OSGShaderProgram.h"
#include "OSGShaderProgramChunk.h"

#include "OSGAnimation.h"
#include "OSGAnimBindAction.h"
#include "OSGAnimKeyFrameTemplate.h"
#include "OSGGlobalsAttachment.h"
#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGSkeletonJoint.h"

typedef std::vector<OSG::NodeUnrecPtr    > NodeStore;
typedef std::vector<OSG::MaterialUnrecPtr> MaterialStore;

struct AnimInfo
{
    OSG::AnimationUnrecPtr anim;
    bool                   on;
};

typedef std::vector<AnimInfo>              AnimStore;

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager           *mgr = NULL;
OSG::NodeUnrecPtr                  sceneN;   // scene from file
OSG::NodeUnrecPtr                  rootN;    // root
OSG::ChunkOverrideGroupUnrecPtr    root;
OSG::PolygonChunkUnrecPtr          polyChunk;

NodeStore     normalsGeoN;
NodeStore     geoN;
NodeStore     skinnedGeoN;
MaterialStore skinnedGeoMat;
AnimStore     anims;
bool          normalsActive = false;
OSG::Real32   normalsLen    = 1.f;
OSG::Int32    currAnim      = 0;


OSG::ShaderProgramUnrecPtr      vpSkin;
OSG::ShaderProgramUnrecPtr      fpSkin;
OSG::ShaderProgramChunkUnrecPtr shSkin;
OSG::ChunkMaterialUnrecPtr      matSkin;

const std::string vpCode(
    "#version 120"
    "\n"
    "// forward decl\n"
    "void calcSkin(inout vec4 pos,    inout vec3 norm,\n"
    "              in    vec4 matIdx, in    vec4 weight);\n"
    "\n"
    "varying vec4 position;\n"
    "varying vec3 normal;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    vec4 pos    = gl_Vertex;\n"
    "    vec3 norm   = gl_Normal;\n"
    "    vec4 matIdx = gl_MultiTexCoord2;\n"
    "    vec4 weight = gl_MultiTexCoord3;\n"
    "\n"
    "    calcSkin(pos, norm, matIdx, weight);\n"
    "\n"
    "    gl_Position = gl_ModelViewProjectionMatrix * pos;\n"
    "    position    = gl_Position;\n"
    "    normal      = gl_NormalMatrix * norm;\n"
    "}\n"
    );

const std::string fpCode(
    "#version 120"
    "\n"
    "varying vec4 position;\n"
    "varying vec3 normal;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    vec3  pos      = position.xyz / position.w;\n"
    "    vec3  norm     = normalize(normal);\n"
    "    vec3  lightDir = normalize(vec3(1,1,1));\n"
    "    float NdotL    = max(0, dot(norm, lightDir));\n"
    "    vec3  diffCol  = vec3(0.4, 0.4, 0.6);\n"
    "    diffCol *= NdotL;\n"
    "    gl_FragColor = vec4(diffCol, 1.);\n"
    "}\n"
    );

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void init     (int argc, char *argv[]);
void cleanup  (void);
void printHelp(void);
void collectGeometry    (OSG::Node *node );
void constructNormalsGeo(OSG::Node *rootN);

void processAnim        (OSG::Node *node);


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char *argv[])
{
    init(argc, argv);

    // GLUT main loop
    glutMainLoop();

    cleanup();
    OSG::osgExit();

    return 0;
}

void init(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);

    int glutWinId = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(glutWinId);
    gwin->init();
    
    // load the scene
    root  = OSG::ChunkOverrideGroup::create();
    rootN = OSG::makeNodeFor(root);
        
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
            
        OSG::SceneFileHandler::the()->print();
        sceneN = OSG::makeTorus(.5, 2, 16, 16);
    }
    else
    {
        /*
          All scene file loading is handled via the SceneFileHandler.
        */
        sceneN = OSG::SceneFileHandler::the()->read(argv[1]);
    }

    OSG::TransformUnrecPtr xform  = OSG::Transform::create();
    OSG::NodeUnrecPtr      xformN = OSG::makeNodeFor(xform);

    // xform->editMatrix().setTranslate(OSG::Vec3f(100.f, 0.f, 0.f));
    // xform->editMatrix().setRotate(OSG::Quaternion(OSG::Vec3f(0.f, 1.f, 0.f), 0.3f * OSG::Pi));

    OSG::NodeUnrecPtr     boxN    = OSG::makeBox(1.f, 1.f, 5.f, 1, 1, 1);

    xformN->addChild(sceneN);
    rootN ->addChild(xformN);
    rootN ->addChild(boxN  );

    OSG::commitChanges();
    
    // collect geometries in the scene
    collectGeometry(rootN);

    // construct skin shader
    vpSkin = OSG::ShaderProgram::createVertexShader  ();
    vpSkin->setProgram(vpCode);

    fpSkin = OSG::ShaderProgram::createFragmentShader();
    fpSkin->setProgram(fpCode);

    shSkin = OSG::ShaderProgramChunk::create();
    shSkin->addShader(vpSkin);
    shSkin->addShader(fpSkin);

    matSkin = OSG::ChunkMaterial::create();
    matSkin->addChunk(shSkin);

    // process animations
    processAnim(sceneN);

    // create the SimpleSceneManager helper
    mgr = new OSG::SimpleSceneManager;
    
    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (rootN);
    
    // show the whole scene
    mgr->showAll();
}

void cleanup(void)
{
    delete mgr;
    mgr = NULL;

    sceneN    = NULL;
    rootN     = NULL;
    root      = NULL;
    polyChunk = NULL;

    vpSkin    = NULL;
    fpSkin    = NULL;
    shSkin    = NULL;
    matSkin   = NULL;

    normalsGeoN  .clear();
    geoN         .clear();
    skinnedGeoN  .clear();
    skinnedGeoMat.clear();
    anims        .clear();
}

void printHelp(void)
{
    std::cout << "Keys:\n"
              << "  ESC      exit\n"
              << "  f        fly mode\n"
              << "  t        trackball mode\n"
              << "  q        toggle statistics\n"
              << "  h        toggle headlight\n"
              << "  b        toggle backface culling\n"
              << "  w        toggle wireframe\n"
              << "  n        toggle normals\n"
              << "  m/M      de/increase normals length\n"
              << "  v        toggle bounding volumes\n"
              << "  p        print scene graph\n"
              << "  d        toggle skinned geo draw mode\n"
              << std::flush;
}

OSG::Action::ResultE doCollectGeometry(OSG::Node *node)
{
    if(node == NULL)
    {
        std::cerr << "WARNING: collectGeometry called with node == NULL"
                  << std::endl;
        return OSG::Action::Continue;
    }

    OSG::NodeCore *core = node->getCore();

    if(core == NULL)
    {
        std::cerr << "WARNING: collectGeometry called with core == NULL"
                  << std::endl;
        return OSG::Action::Continue;
    }

    if(core->getType().isDerivedFrom(OSG::Geometry::getClassType()))
    {
        geoN.push_back(node);
    }

    if(core->getType().isDerivedFrom(OSG::SkinnedGeometry::getClassType()))
    {
        skinnedGeoN.push_back(node);

        OSG::SkinnedGeometry *sgeo =
            dynamic_cast<OSG::SkinnedGeometry *>(core);
        skinnedGeoMat.push_back(sgeo->getMaterial());

        sgeo->setRenderMode(OSG::SkinnedGeometry::RMUnskinned);
    }

    return OSG::Action::Continue;
}

void collectGeometry(OSG::Node *rootN)
{
    OSG::traverse(rootN, &doCollectGeometry);

    std::cout << "collectGeometry: num geo [" << geoN.size()
              << "] num skinned geo [" << skinnedGeoN.size()
              << "]" << std::endl;
}


void constructNormalsGeo(OSG::Node *rootN)
{
    NodeStore::const_iterator nIt  = normalsGeoN.begin();
    NodeStore::const_iterator nEnd = normalsGeoN.end  ();

    // remove existing normals
    for(; nIt != nEnd; ++nIt)
        (*nIt)->getParent()->subChild(*nIt);

    normalsGeoN.clear();

    // construct and add new normals
    nIt  = geoN.begin();
    nEnd = geoN.end  ();

    for(; nIt != nEnd; ++nIt)
    {
        OSG::Geometry     *geo      =
            dynamic_cast<OSG::Geometry *>((*nIt)->getCore());
        OSG::NodeUnrecPtr  normGeoN =
            OSG::calcVertexNormalsGeo(geo, normalsLen);

        normalsGeoN.push_back(normGeoN);

        (*nIt)->addChild(normGeoN);
    }
}

void processAnim(OSG::Node *node)
{
    OSG::commitChangesAndClear();

    // register AnimBindAction callbacks -- temporarily done here
    OSG::AnimBindAction::registerEnterDefault(
        OSG::ComponentTransform::getClassType(),
        &OSG::bindEnterDefault                  );
    OSG::AnimBindAction::registerEnterDefault(
        OSG::Transform::getClassType(),
        &OSG::bindEnterDefault                  );


    OSG::GlobalsAttachment *ga = dynamic_cast<OSG::GlobalsAttachment *>(
        node->findAttachment(OSG::GlobalsAttachment::getClassType()));

    if(ga == NULL)
    {
        std::cerr << "WARNING: processAnim: no GlobalsAttachment found"
                  << std::endl;
        return;
    }

    OSG::GlobalsAttachment::MFElementsType::const_iterator eIt  =
        ga->getMFElements()->begin();
    OSG::GlobalsAttachment::MFElementsType::const_iterator eEnd =
        ga->getMFElements()->end  ();

    for(; eIt != eEnd; ++eIt)
    {
        OSG::AnimKeyFrameTemplate *animTmpl =
            dynamic_cast<OSG::AnimKeyFrameTemplate *>(*eIt);

        if(animTmpl == NULL)
            continue;

        std::cout << "instantiating anim template [" << animTmpl->getName()
                  << "] with [" << animTmpl->getMFSources()->size()
                  << "] sources [" << animTmpl->getMFTargetIds()->size() 
                  << "] targetIds" << std::endl;

        AnimInfo ai;
        ai.on   = false;
        ai.anim = animTmpl->instantiate(node);
        ai.anim->setEnabled(false);

        anims.push_back(ai);
    }
}

void toggleAnim(OSG::UInt32 index, bool loop)
{
    if(anims[index].on == true)
    {
        std::cout << "STOP anim " << index << std::endl;
        anims[index].anim->stop ();
        anims[index].anim->reset();
        anims[index].anim->setEnabled(false);
        anims[index].on = false;
    }
    else
    {
        if(loop == true)
        {
            std::cout << "START LOOP anim " << index << std::endl;
            anims[index].anim->startLoop(OSG::FrameHandler::the()->getTimeStamp());
        }
        else
        {
            std::cout << "START anim " << index << std::endl;
            anims[index].anim->start(OSG::FrameHandler::the()->getTimeStamp());
        }

        anims[index].anim->setEnabled(true);
        anims[index].on = true;
    }
}

void printXForm(OSG::SceneGraphPrinter *sgp, OSG::NodeCore *core)
{
    OSG::Transform *xform = dynamic_cast<OSG::Transform *>(core);

    sgp->indentStream() << "matrix:\n" << xform->getMatrix();
}

void printJoint(OSG::SceneGraphPrinter *sgp, OSG::NodeCore *core)
{
    OSG::SkeletonJoint *joint = dynamic_cast<OSG::SkeletonJoint *>(core);

    sgp->indentStream() << "matrix:\n" << joint->getMatrix();
}

void printVolume(OSG::SceneGraphPrinter *sgp, OSG::NodeCore *core)
{
    sgp->indentStream() << "  volume " << sgp->getCurrNode()->getVolume()
                        << "\n";
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
//     std::cout << ">> FRAME START" << std::endl;

    static OSG::Time   tAcc = 0;
    static OSG::UInt32 fc   = 0;

    OSG::Time t0 = OSG::getSystemTime();

    OSG::FrameHandler::the()->frame();

    OSG::commitChangesAndClear();

    mgr->idle();
    mgr->redraw();

    OSG::Time t1 = OSG::getSystemTime();

    tAcc += (t1 - t0);
    fc   += 1;

    if(tAcc >= 1)
    {
        std::cout << "frame count [" << fc
                  << "] fc/tAcc [" << (fc/tAcc)
                  << "] tAcc/fc [" << (1000.f * (tAcc/fc))
                  << "] ms tAcc [" << tAcc << "] s" << std::endl;

        tAcc = 0;
        fc   = 0;
    }

//     std::cout << "<< FRAME END" << std::endl;

//     mgr->getWindow()->registerConstant(GL_MAX_VERTEX_UNIFORM_COMPONENTS  );
//     mgr->getWindow()->registerConstant(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);

//     OSG::Real32 maxVPUniforms =
//         mgr->getWindow()->getConstantValue(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
//     OSG::Real32 maxFPUniforms =
//         mgr->getWindow()->getConstantValue(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);

//     std::cout << "GL_MAX_VERTEX_UNIFORM_COMPONENTS [" << maxVPUniforms
//               << "] GL_MAX_FRAGMENT_UNIFORM_COMPONENTS [" << maxFPUniforms
//               << "]" << std::endl;
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
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:
    {
        cleanup();

        OSG::osgExit();
        std::exit(0);
    }
    break;
    case 'f':
    {
        mgr->setNavigationMode(OSG::Navigator::FLY);
        std::cout << "Fly mode" << std::endl;
    }
    break;
    case 't':
    {
        mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        std::cout << "Trackball mode" << std::endl;
    }
    break;
    case 'q':
    {
        mgr->setStatistics(!mgr->getStatistics());
        std::cout << "Statistics " 
                  << (mgr->getStatistics() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'h':
    {
        mgr->setHeadlight(!mgr->getHeadlightState());
        std::cout << "Headlight "
                  << (mgr->getHeadlightState() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'b':
    {
        if(polyChunk == NULL)
        {
            polyChunk = OSG::PolygonChunk::create();
            root->addChunk(polyChunk);
        }
  
        if(polyChunk->getCullFace() == GL_NONE)
        {
            polyChunk->setCullFace(GL_BACK);
            std::cout << "Backface culling enabled" << std::endl;
        }
        else
        {
            polyChunk->setCullFace(GL_NONE);
            std::cout << "Backface culling disabled" << std::endl;
        }
    }
    break;
    case 'w':
    {
        if(polyChunk == NULL)
        {
            polyChunk = OSG::PolygonChunk::create();
            root->addChunk(polyChunk);
        }

        if(polyChunk->getFrontMode() == GL_FILL)
        {
            polyChunk->setFrontMode(GL_LINE);
            polyChunk->setBackMode (GL_LINE);
            std::cout << "Wireframe enabled" << std::endl;
        }
        else
        {
            polyChunk->setFrontMode(GL_FILL);
            polyChunk->setBackMode (GL_FILL);
            std::cout << "Wireframe disabled" << std::endl;
        }
    }
    break;
    case 'n':
    {
        if(normalsActive == true)
        {
            normalsActive = false;

            NodeStore::const_iterator ngIt  = normalsGeoN.begin();
            NodeStore::const_iterator ngEnd = normalsGeoN.end  ();

            for(; ngIt != ngEnd; ++ngIt)
            {
                (*ngIt)->setTravMask(0);
            }
            
            std::cout << "Normals disabled" << std::endl;
        }
        else
        {
            normalsActive = true;

            if(normalsGeoN.empty() == true)
                constructNormalsGeo(sceneN);

            NodeStore::const_iterator ngIt  = normalsGeoN.begin();
            NodeStore::const_iterator ngEnd = normalsGeoN.end  ();

            for(; ngIt != ngEnd; ++ngIt)
            {
                (*ngIt)->setTravMask(OSG::TypeTraits<OSG::UInt32>::BitsSet);
            }

            std::cout << "Normals enabled" << std::endl;
        }
    }
    break;
    case 'm':
    {
        normalsLen /= 1.25f;
        constructNormalsGeo(sceneN);
        std::cout << "Normals length " << normalsLen << std::endl;
    }
    break;
    case 'M':
    {
        normalsLen *= 1.25f;
        constructNormalsGeo(sceneN);
        std::cout << "Normals length " << normalsLen << std::endl;
    }
    break;
    case 'v':
    {
        mgr->getRenderAction()->setVolumeDrawing(
            !mgr->getRenderAction()->getVolumeDrawing());
        std::cout << "Volume drawing: "
                  << (mgr->getRenderAction()->getVolumeDrawing() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'p':
    {
        OSG::SceneGraphPrinter sgp(mgr->getRoot());
        sgp.addPrintFunc(OSG::SkinnedGeometry::getClassType(),
                         &printVolume                         );
        sgp.printDownTree(std::cout);

        NodeStore::const_iterator nIt  = skinnedGeoN.begin();
        NodeStore::const_iterator nEnd = skinnedGeoN.end  ();

        for(OSG::UInt32 i = 0; nIt != nEnd; ++nIt, ++i)
        {
            OSG::SkinnedGeometry *sgeo = dynamic_cast<OSG::SkinnedGeometry *>(
                (*nIt)->getCore());

            std::cout << "Skeleton:\n";
            OSG::SceneGraphPrinter skelPrinter(sgeo->getSkeleton()->getRoots(0));
            skelPrinter.addPrintFunc(OSG::Transform    ::getClassType(),
                                     &printXForm                        );
            //skelPrinter.addPrintFunc(OSG::SkeletonJoint::getClassType(),
            //                         &printJoint                        );
            skelPrinter.printDownTree(std::cout);
        }
    }
    break;

    case 'a':
    {
        mgr->showAll();

        std::cout << "Showing all of scene." << std::endl;
    }
    break;

    case '[':
    {
        if(anims.empty() == false)
        {
            currAnim -= 1;
            if(currAnim < 0)
                currAnim = anims.size() - 1;

            std::cout << "Current anim [" << currAnim << "] - ["
                      << anims[currAnim].anim->getTemplate()->getName()
                      << "]" << std::endl;
        }
    }
    break;
    case ']':
    {
        if(anims.empty() == false)
        {
            currAnim += 1;
            if(currAnim >= OSG::Int32(anims.size()))
                currAnim = 0;

            std::cout << "Current anim [" << currAnim << "] - ["
                      << anims[currAnim].anim->getTemplate()->getName()
                      << "]" << std::endl;
        }
    }
    break;

    case 'L':
    {
        toggleAnim(currAnim, false);
    }
    break;

    case 'l':
    {
        toggleAnim(currAnim, true);
    }
    break;
    case 'd':
    {
        NodeStore::const_iterator nIt  = skinnedGeoN.begin();
        NodeStore::const_iterator nEnd = skinnedGeoN.end  ();

        for(OSG::UInt32 i = 0; nIt != nEnd; ++nIt, ++i)
        {
            OSG::SkinnedGeometry *sgeo = dynamic_cast<OSG::SkinnedGeometry *>(
                (*nIt)->getCore());

            if(sgeo->getRenderMode() == OSG::SkinnedGeometry::RMSkinnedCPU)
            {
                std::cout << "Enabling SkinnedGeo GPU mode ["
                          << sgeo << "]" << std::endl;

                sgeo->setRenderMode(OSG::SkinnedGeometry::RMSkinnedGPU);
                sgeo->setMaterial  (matSkin);
            }
            else if(sgeo->getRenderMode() == OSG::SkinnedGeometry::RMSkinnedGPU)
            {
                std::cout << "Enabling SkinnedGeo SKELETON mode ["
                          << sgeo << "]" << std::endl;

                sgeo->setRenderMode(OSG::SkinnedGeometry::RMSkeleton);
                sgeo->setMaterial  (skinnedGeoMat[i]);
            }
            else if(sgeo->getRenderMode() == OSG::SkinnedGeometry::RMSkeleton)
            {
               std::cout << "Enabling SkinnedGeo UNSKINNED mode ["
                         << sgeo << "]" << std::endl;

               sgeo->setRenderMode(OSG::SkinnedGeometry::RMUnskinned);
               sgeo->setMaterial  (skinnedGeoMat[i]);
            }
            else
            {
                std::cout << "Enabling SkinnedGeo CPU mode ["
                          << sgeo << "]" << std::endl;

                sgeo->setRenderMode(OSG::SkinnedGeometry::RMSkinnedCPU);
                sgeo->setMaterial(skinnedGeoMat[i]);
            }
        }
    }
    break;
    case 'c':
    {
        mgr->getRenderAction()->setFrustumCulling(
            !mgr->getRenderAction()->getFrustumCulling());

        std::cout << "Frustum culling: "
                  << (mgr->getRenderAction()->getFrustumCulling() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 's':
    {
        NodeStore::const_iterator nIt  = skinnedGeoN.begin();
        NodeStore::const_iterator nEnd = skinnedGeoN.end  ();

        for(OSG::UInt32 i = 0; nIt != nEnd; ++nIt, ++i)
        {
           OSG::SkinnedGeometry *sgeo = dynamic_cast<OSG::SkinnedGeometry *>(
                (*nIt)->getCore());

           OSG::Skeleton        *skel = sgeo->getSkeleton();

           OSG::Skeleton::MFRootsType::const_iterator rIt  =
               skel->getMFRoots()->begin();
           OSG::Skeleton::MFRootsType::const_iterator rEnd =
               skel->getMFRoots()->end  ();

           for(OSG::UInt32 j = 0; rIt != rEnd; ++rIt, ++j)
           {
               std::cout << "Skeleton [" << i << "] @ [" << skel
                         << "] root [" << j << "]\n";

               OSG::SceneGraphPrinter sgp(*rIt);
               sgp.printDownTree(std::cout);

               std::cout << std::endl;
           }
        }
    }
    break;

    default:
    {
        printHelp();
    }
    break;
    }

    glutPostRedisplay();
}

void idle(void)
{
  glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
