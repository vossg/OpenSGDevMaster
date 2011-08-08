

#ifdef OSG_BUILD_ACTIVE

// Headers
#include <OSGConfig.h>
#include <OSGAnimation.h>
#include <OSGAnimBindAction.h>
#include <OSGAnimKeyFrameTemplate.h>
#include <OSGGlobalsAttachment.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGImageFileHandler.h>
#include <OSGNameAttachment.h>
#include <OSGSceneFileHandler.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramChunk.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSkinnedGeometry.h>
#include <OSGSkyBackground.h>
#include <OSGTextureObjChunk.h>

#else // OSG_BUILD_ACTIVE

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGAnimation.h>
#include <OpenSG/OSGAnimBindAction.h>
#include <OpenSG/OSGAnimKeyFrameTemplate.h>
#include <OpenSG/OSGGlobalsAttachment.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSkinnedGeometry.h>
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/OSGTextureObjChunk.h>

#endif // OSG_BUILD_ACTIVE

#include <boost/array.hpp>
#include <map>
#include <set>

typedef std::set<OSG::SkinnedGeometry *>                   SkinnedGeoStore;
typedef std::set<OSG::Material *>                          MaterialStore;
typedef std::map<std::string, OSG::TextureObjChunkRefPtr>  TextureMap;

enum AnimIdE
{
    AnimIdWalkUB,
    AnimIdWalkLB,

    AnimIdRunUB,
    AnimIdRunLB,

    AnimIdIdleUB,
    AnimIdIdleLB,

    AnimIdMAX
};

enum AnimStateE
{
    AnimOff,
    AnimFadeIn,
    AnimFadeOut,
    AnimOn
};

enum CharacterStateE
{
    CharStop,
    CharWalk,
    CharRun
};

struct GlobalVars
{
    OSG::SimpleSceneManager *mgr;
    OSG::GLUTWindowRefPtr    win;

    OSG::NodeRefPtr          rootN;
    OSG::TransformRefPtr     xform;

    CharacterStateE          charState;
    AnimStateE               animState[AnimIdMAX];
    OSG::AnimationRefPtr     anims    [AnimIdMAX];

    SkinnedGeoStore          skinGeos;
    MaterialStore            materials;
    TextureMap               texMap;

    OSG::SkinnedGeometry::RenderModeE renderMode;
    OSG::ShaderProgramChunkRefPtr     skinShader;
};

boost::array<const std::string, AnimIdMAX> animNames = {
    {
        "UB_walk",
        "LB_walk",
        "UB_newRun",
        "LB_newRun",
        "UB_idle",
        "LB_idle"
    }
};

GlobalVars *g = NULL;

void init   (int argc, char *argv[]);
void cleanup(void);

void loadCharacter (void);
void loadTextures  (void);
void initAnimations(void);
void loadBackground(void);
void initShader    (void);
void enableRenderMode(OSG::SkinnedGeometry::RenderModeE rm);

void reshapeCB (int w, int h);
void displayCB (void);
void mouseCB   (int button, int state, int mouseX, int mouseY);
void motionCB  (int mouseX, int mouseY);
void keyboardCB(unsigned char k, int mouseX, int mouseY);
void idleCB    (void);
int  setupGLUT (int *argc, char *argv[]);

int main(int argc, char *argv[])
{
    init(argc, argv);

    glutMainLoop();

    cleanup();

    return 0;
}


// ============================================================================

void init(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);

    g = new GlobalVars;

    int glutWinId = setupGLUT(&argc, argv);

    g->win = OSG::GLUTWindow::create();
    g->win->setGlutId(glutWinId);
    g->win->init();

    g->mgr = new OSG::SimpleSceneManager;
    g->mgr->setWindow(g->win);

    g->rootN = OSG::makeCoredNode<OSG::Group>();
    g->mgr->setRoot(g->rootN);

    g->renderMode = OSG::SkinnedGeometry::RMSkinnedCPU;

    loadCharacter ();
    loadTextures  ();
    initAnimations();

    loadBackground();
    initShader    ();

    g->mgr->showAll();
}

// ============================================================================

void cleanup(void)
{
    if(g == NULL)
        return;

    delete g->mgr;
    g->mgr = NULL;

    delete g;
    g = NULL;

    OSG::osgExit();
}

// ============================================================================

class ObjectCollector
{
  public:
    void operator()(OSG::Node *root);

  private:
    OSG::Action::ResultE enterFunc(OSG::Node *node);
};

void
ObjectCollector::operator()(OSG::Node *root)
{
    g->skinGeos .clear();
    g->materials.clear();

    OSG::traverse(root, boost::bind(&ObjectCollector::enterFunc, this, _1));
}

OSG::Action::ResultE
ObjectCollector::enterFunc(OSG::Node *node)
{
    OSG::NodeCore *core = node->getCore();

    if(core->getType().isDerivedFrom(OSG::SkinnedGeometry::getClassType()))
    {
        OSG::SkinnedGeometry *skinGeo = dynamic_cast<OSG::SkinnedGeometry*>(core);

        g->skinGeos .insert(skinGeo               );
        g->materials.insert(skinGeo->getMaterial());
    }

    return OSG::Action::Continue;
}

// ============================================================================

void loadCharacter(void)
{
    OSG::NodeUnrecPtr modelN = OSG::SceneFileHandler::the()->read("western.male01.mesh", NULL);
    g->charState = CharStop;

    ObjectCollector()(modelN);

    SkinnedGeoStore::iterator sIt  = g->skinGeos.begin();
    SkinnedGeoStore::iterator sEnd = g->skinGeos.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->setRenderMode(g->renderMode);
    }

    g->xform = OSG::Transform::create();
    OSG::NodeUnrecPtr xformN = OSG::makeNodeFor(g->xform);

    xformN->addChild(modelN);
    g->rootN->addChild(xformN);
}

// ============================================================================

void loadTextures(void)
{
    MaterialStore::iterator mIt  = g->materials.begin();
    MaterialStore::iterator mEnd = g->materials.end  ();

    for(; mIt != mEnd; ++mIt)
    {
        if(OSG::getName(*mIt) != NULL)
        {
            FLOG(("mat name '%s'\n", OSG::getName(*mIt)));

            std::string matName = OSG::getName(*mIt);
            TextureMap::iterator tIt = g->texMap.find(matName);
            
            if(tIt == g->texMap.end())
            {
                std::string::size_type pos     = matName.find("_");
                std::string            texName = matName.substr(0, pos) + "_diffuse.tga";

                OSG::ImageUnrecPtr           texImg = OSG::ImageFileHandler::the()->read(texName.c_str());
                OSG::TextureObjChunkUnrecPtr texObj = OSG::TextureObjChunk::create();

                texObj->setImage(texImg);

                g->texMap.insert(TextureMap::value_type(matName, texObj));

                tIt = g->texMap.find(matName);
            }

            OSG_ASSERT(tIt != g->texMap.end());

            OSG::ChunkMaterial *chunkMat = dynamic_cast<OSG::ChunkMaterial*>(*mIt);

            if(chunkMat != NULL)
            {
                FLOG(("adding texture chunk\n"));
                chunkMat->addChunk((*tIt).second);
            }
        }
    }
}

// ============================================================================

OSG::Action::ResultE
initAnimationsEnterFunc(OSG::Node *node)
{
    OSG::Action::ResultE    retVal  = OSG::Action::Continue;
    OSG::GlobalsAttachment *globals = dynamic_cast<OSG::GlobalsAttachment *>(
        node->findAttachment(OSG::GlobalsAttachment::getClassType()));

    if(globals == NULL)
        return retVal;

    OSG::GlobalsAttachment::MFElementsType::const_iterator eIt  = globals->getMFElements()->begin();
    OSG::GlobalsAttachment::MFElementsType::const_iterator eEnd = globals->getMFElements()->end  ();

    for(; eIt != eEnd; ++eIt)
    {
        OSG::AnimTemplate *animTmpl = dynamic_cast<OSG::AnimTemplate *>(*eIt);

        if(animTmpl == NULL)
            continue;

        for(OSG::UInt32 i = 0; i < animNames.size(); ++i)
        {
            if(animNames[i] == animTmpl->getName())
            {
                FLOG(("instantiating anim %s\n", animNames[i].c_str()));
                g->anims    [i] = animTmpl->instantiate(node);
                g->anims    [i]->setWeight(0.f);
                g->animState[i] = AnimOff;
            }
        }
    }
}

void initAnimations(void)
{
    OSG::traverse(g->rootN, &initAnimationsEnterFunc);

    g->animState[AnimIdIdleUB] = AnimFadeIn;
    g->animState[AnimIdIdleLB] = AnimFadeIn;
}

// ============================================================================

void updateAnimations(OSG::Time currT, OSG::Time deltaT)
{
    for(OSG::UInt32 i = 0; i < AnimIdMAX; ++i)
    {
        switch(g->animState[i])
        {
        case AnimOff:
        {
            if(g->anims[i]->getEnabled() == true)
            {
                FLOG(("AnimOff: disabling anim %d %s\n",
                      i, g->anims[i]->getName().c_str()));

                g->anims[i]->stop      ();
                g->anims[i]->setEnabled(false);
                g->anims[i]->setWeight (0.f);
            }
        }
        break;

        case AnimFadeIn:
        {
            OSG::Real32 oldW = g->anims[i]->getWeight();
            OSG::Real32 newW = OSG::osgMin<OSG::Real32>(1.f, oldW + deltaT);
            if(oldW < 1.f)
            {
                FLOG(("AnimFadeIn: new weight %f - %d %s\n",
                      newW, i, g->anims[i]->getName().c_str()));
                g->anims[i]->setWeight(newW);
            }

            if(newW >= 1.f)
            {
                FLOG(("AnimFadeIn: new state AnimOn %d %s\n",
                      i, g->anims[i]->getName().c_str()));
                g->animState[i] = AnimOn;
                g->anims    [i]->setWeight(1.f);
            }

            if(g->anims[i]->getEnabled() == false)
            {
                FLOG(("AnimFadeIn: enabling anim %d %s\n",
                      i, g->anims[i]->getName().c_str()));

                g->anims[i]->reset     ();
                g->anims[i]->setEnabled(true);
                g->anims[i]->startLoop (OSG::FrameHandler::the()->getTimeStamp());
            }
        }
        break;

        case AnimFadeOut:
        {
            OSG::Real32 oldW = g->anims[i]->getWeight();
            OSG::Real32 newW = OSG::osgMax<OSG::Real32>(0.f, oldW - deltaT);
            if(oldW > 0.f)
            {
                FLOG(("AnimFadeOut: new weight %f - %d %s\n",
                      newW, i, g->anims[i]->getName().c_str()));
                g->anims[i]->setWeight(newW);
            }

            if(newW <= 0.f)
            {
                FLOG(("AnimFadeOut: new state AnimOff %d %s\n",
                      i, g->anims[i]->getName().c_str()));
                g->animState[i] = AnimOff;
                g->anims    [i]->setWeight(0.f);
            }
        }
        break;

        case AnimOn:
        {
            if(g->anims[i]->getEnabled() == false)
            {
                FLOG(("AnimOn: enabling anim %d %s\n",
                      i, g->anims[i]->getName().c_str()));

                g->anims[i]->reset     ();
                g->anims[i]->setEnabled(true);
                g->anims[i]->startLoop (OSG::FrameHandler::the()->getTimeStamp());
                g->anims[i]->setWeight (1.f);
            }
        }
        break;
        }
    }
}

// ============================================================================

void loadBackground(void)
{
    OSG::ImageUnrecPtr           imgFront  = OSG::ImageFileHandler::the()->read("skyBoxFront.jpg");
    OSG::TextureObjChunkUnrecPtr texFront  = OSG::TextureObjChunk::create();
    texFront->setImage(imgFront);

    OSG::ImageUnrecPtr           imgBack   = OSG::ImageFileHandler::the()->read("skyBoxBack.jpg");
    OSG::TextureObjChunkUnrecPtr texBack   = OSG::TextureObjChunk::create();
    texBack->setImage(imgBack);

    OSG::ImageUnrecPtr           imgLeft   = OSG::ImageFileHandler::the()->read("skyBoxLeft.jpg");
    OSG::TextureObjChunkUnrecPtr texLeft   = OSG::TextureObjChunk::create();
    texLeft->setImage(imgLeft);

    OSG::ImageUnrecPtr           imgRight  = OSG::ImageFileHandler::the()->read("skyBoxRight.jpg");
    OSG::TextureObjChunkUnrecPtr texRight  = OSG::TextureObjChunk::create();
    texRight->setImage(imgRight);

    OSG::ImageUnrecPtr           imgTop    = OSG::ImageFileHandler::the()->read("skyBoxTop.jpg");
    OSG::TextureObjChunkUnrecPtr texTop    = OSG::TextureObjChunk::create();
    texTop->setImage(imgTop);

    OSG::ImageUnrecPtr           imgBottom = OSG::ImageFileHandler::the()->read("skyBoxBottom.jpg");
    OSG::TextureObjChunkUnrecPtr texBottom = OSG::TextureObjChunk::create();
    texBottom->setImage(imgBottom);

    OSG::SkyBackgroundUnrecPtr skyBG = OSG::SkyBackground::create();
    skyBG->setFrontTexture (texFront);
    skyBG->setBackTexture  (texBack );
    skyBG->setLeftTexture  (texLeft );
    skyBG->setRightTexture (texRight);
    skyBG->setTopTexture   (texTop  );
    skyBG->setBottomTexture(texBottom);

    g->mgr->setBackground(skyBG);
}

// ============================================================================

void initShader(void)
{
    OSG::ShaderProgramUnrecPtr vp = OSG::ShaderProgram::createVertexShader();
    vp->readProgram("vertex_skinned.vp.glsl");

    OSG::ShaderProgramUnrecPtr fp = OSG::ShaderProgram::createFragmentShader();
    fp->readProgram("vertex_skinned.fp.glsl");

    fp->addUniformVariable("diffuseMap", 0);
    fp->addOSGVariable    ("OSGLight0Active");

    g->skinShader = OSG::ShaderProgramChunk::create();
    g->skinShader->addShader(vp);
    g->skinShader->addShader(fp);
}

void enableRenderMode(OSG::SkinnedGeometry::RenderModeE rm)
{
    if(g->renderMode == rm)
        return;

    if(g->renderMode == OSG::SkinnedGeometry::RMSkinnedGPU)
    {
        // remove shader chunk
        MaterialStore::iterator mIt  = g->materials.begin();
        MaterialStore::iterator mEnd = g->materials.end  ();

        for(; mIt != mEnd; ++mIt)
        {
            OSG::ChunkMaterial *chunkMat = dynamic_cast<OSG::ChunkMaterial *>((*mIt));

            if(chunkMat != NULL)
                chunkMat->subChunk(g->skinShader);
        }
    }

    if(rm == OSG::SkinnedGeometry::RMSkinnedGPU)
    {
        // add shader chunk
        MaterialStore::iterator mIt  = g->materials.begin();
        MaterialStore::iterator mEnd = g->materials.end  ();

        for(; mIt != mEnd; ++mIt)
        {
            OSG::ChunkMaterial *chunkMat = dynamic_cast<OSG::ChunkMaterial *>((*mIt));

            if(chunkMat != NULL)
                chunkMat->addChunk(g->skinShader);
        }
    }

    SkinnedGeoStore::iterator sIt  = g->skinGeos.begin();
    SkinnedGeoStore::iterator sEnd = g->skinGeos.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->setRenderMode(rm);
    }

    FLOG(("enable render mode %d\n", rm));

    g->renderMode = rm;
}

// ============================================================================
// GLUT callback functions
//

void reshapeCB(int w, int h)
{
    g->mgr->resize(w, h);
    glutPostRedisplay();
}

void displayCB(void)
{
    static OSG::Time prevT  = OSG::getSystemTime();
    OSG::Time        currT  = OSG::getSystemTime();
    OSG::Time        deltaT = currT - prevT;

    updateAnimations(currT, deltaT);

    OSG::FrameHandler::the()->frame(currT);

    OSG::commitChangesAndClear();
    g->mgr->idle  ();
    g->mgr->redraw();

    prevT = currT;
}

void mouseCB(int button, int state, int mouseX, int mouseY)
{
    if(state)
        g->mgr->mouseButtonRelease(button, mouseX, mouseY);
    else
        g->mgr->mouseButtonPress(button, mouseX, mouseY);

    glutPostRedisplay();
}

void motionCB(int mouseX, int mouseY)
{
    g->mgr->mouseMove(mouseX, mouseY);
    glutPostRedisplay();
}

void keyboardCB(unsigned char k, int mouseX, int mouseY)
{
    switch(k)
    {
    case 27:
    case 'q':
    case 'Q':
        cleanup();
        OSG::osgExit();
        std::exit(0);
        break;

    case '1':
    {
        // fade in walk
        if(g->animState[AnimIdWalkUB] != AnimOn)
            g->animState[AnimIdWalkUB] = AnimFadeIn;
        if(g->animState[AnimIdWalkLB] != AnimOn)
            g->animState[AnimIdWalkLB] = AnimFadeIn;
        
        // fade out other
        if(g->animState[AnimIdRunUB] != AnimOff)
            g->animState[AnimIdRunUB] = AnimFadeOut;
        if(g->animState[AnimIdRunLB] != AnimOff)
            g->animState[AnimIdRunLB] = AnimFadeOut;

        if(g->animState[AnimIdIdleUB] != AnimOff)
            g->animState[AnimIdIdleUB] = AnimFadeOut;
        if(g->animState[AnimIdIdleLB] != AnimOff)
            g->animState[AnimIdIdleLB] = AnimFadeOut;

        g->charState = CharWalk;
    }
    break;

    case '2':
    {
        // fade in run
        if(g->animState[AnimIdRunUB] != AnimOn)
            g->animState[AnimIdRunUB] = AnimFadeIn;
        if(g->animState[AnimIdRunLB] != AnimOn)
            g->animState[AnimIdRunLB] = AnimFadeIn;

        // fade out other
        if(g->animState[AnimIdWalkUB] != AnimOff)
            g->animState[AnimIdWalkUB] = AnimFadeOut;
        if(g->animState[AnimIdWalkLB] != AnimOff)
            g->animState[AnimIdWalkLB] = AnimFadeOut;

        if(g->animState[AnimIdIdleUB] != AnimOff)
            g->animState[AnimIdIdleUB] = AnimFadeOut;
        if(g->animState[AnimIdIdleLB] != AnimOff)
            g->animState[AnimIdIdleLB] = AnimFadeOut;
        
        g->charState = CharRun;
    }
    break;

    case '3':
    {
        // fade in idle
        if(g->animState[AnimIdIdleUB] != AnimOn)
            g->animState[AnimIdIdleUB] = AnimFadeIn;
        if(g->animState[AnimIdIdleLB] != AnimOn)
            g->animState[AnimIdIdleLB] = AnimFadeIn;
        
        // fade out other
        if(g->animState[AnimIdRunUB] != AnimOff)
            g->animState[AnimIdRunUB] = AnimFadeOut;
        if(g->animState[AnimIdRunLB] != AnimOff)
            g->animState[AnimIdRunLB] = AnimFadeOut;

        if(g->animState[AnimIdWalkUB] != AnimOff)
            g->animState[AnimIdWalkUB] = AnimFadeOut;
        if(g->animState[AnimIdWalkLB] != AnimOff)
            g->animState[AnimIdWalkLB] = AnimFadeOut;

        g->charState = CharStop;
    }
    break;

    case 'r':
    {
        OSG::SkinnedGeometry::RenderModeE newRM =
            static_cast<OSG::SkinnedGeometry::RenderModeE>((g->renderMode + 1) % 4);

        enableRenderMode(newRM);
    }
    break;
    }

    glutPostRedisplay();
}

void idleCB(void)
{
    glutPostRedisplay();
}

int setupGLUT (int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winId = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshapeCB);
    glutDisplayFunc(displayCB);
    glutIdleFunc(idleCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(motionCB);
    glutKeyboardFunc(keyboardCB);

    return winId;
}
