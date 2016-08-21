// OpenSG example: dyndrawing2.cpp
//
// User interface:
//  a) mouse    => standard navigator
//  b) keyboard =>
//      '1': toggle between static and dynamic mode
//

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/random.hpp>
#include <boost/random/lagged_fibonacci.hpp>

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGGradientBackground.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGAction.h>
#include <OSGFrameBufferObject.h>
#include <OSGRenderBuffer.h>
#include <OSGTextureBuffer.h>
#include <OSGSimpleStage.h>
#include <OSGPassiveViewport.h>
#include <OSGVisitSubTree.h>
#include <OSGImage.h>
#include <OSGTextureObjChunk.h>
#include <OSGFBOBackground.h>
#include <OSGFBOGrabForeground.h>

#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGFrameBufferObject.h>
#include <OpenSG/OSGRenderBuffer.h>
#include <OpenSG/OSGTextureBuffer.h>
#include <OpenSG/OSGSimpleStage.h>
#include <OpenSG/OSGPassiveViewport.h>
#include <OpenSG/OSGVisitSubTree.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGFBOBackground.h>

#endif

OSG_USING_NAMESPACE // just for convenience but not recommended

//#define USE_MULTISAMPLING

//
// The number of tori to render
// ============================
//
#ifdef _DEBUG
const int max_tori =  500;
#else
const int max_tori = 10000;
#endif

//
// Helper class for building FBO used by SimpleFBO see below
// =========================================================
//
class FBOBuilder
{
public:
    struct TextureData {
        TextureData()
            : enable(true)
            , pixel_format(Image::OSG_RGBA_PF)
            , type(Image::OSG_UINT8_IMAGEDATA)
            , main_memory(true)
            , texObj(NULL)
            , image(NULL) {}
       ~TextureData() {texObj = NULL; image = NULL; }

        bool enable;
        UInt32 pixel_format;
        Int32 type;
        bool main_memory;
        TextureObjChunkUnrecPtr texObj;
        ImageUnrecPtr image;
    };

    typedef std::vector<TextureData> VecTextureDataT;

public:
            FBOBuilder(const VecTextureDataT& buffers, bool depth,  bool stencil, const TextureData& ds_buffer) 
                : _buffers(buffers) , _depth(depth) , _stencil(stencil) , _ds_buffer(ds_buffer) {}
           ~FBOBuilder() {}

public:
    FrameBufferObjectTransitPtr    operator()(UInt32 width, UInt32 height) const;

private:
    VecTextureDataT _buffers;
    bool            _depth;
    bool            _stencil;
    TextureData     _ds_buffer;
};

FrameBufferObjectTransitPtr FBOBuilder::operator()(
    UInt32 width, 
    UInt32 height) const
{
    //
    // Setup the FBO
    //
    FrameBufferObjectUnrecPtr fbo = FrameBufferObject::create();
    //
    // multiple color buffers
    //
    for (UInt32 idx = 0; idx < _buffers.size(); ++idx) {
        //
        // use textures?
        //
        if (_buffers[idx].enable) {
            ImageUnrecPtr           texImg = (_buffers[idx].image  == NULL ? Image::create()           : _buffers[idx].image);
            TextureObjChunkUnrecPtr texObj = (_buffers[idx].texObj == NULL ? TextureObjChunk::create() : _buffers[idx].texObj);
            TextureBufferUnrecPtr   texBuf = TextureBuffer::create();

            if (_buffers[idx].image == NULL)
                texImg->set(_buffers[idx].pixel_format, 
                            width, height, 1, 1, 1, 0.f, NULL,
                            _buffers[idx].type, 
                            _buffers[idx].main_memory);

            texObj->setImage(texImg);
            texBuf->setTexture(texObj);

            fbo->setColorAttachment(texBuf, idx);
        } else 
        //
        // no, then use simple render buffer
        //
        {
            RenderBufferUnrecPtr renBuf = RenderBuffer::create();
            renBuf->setInternalFormat(_buffers[idx].pixel_format);
            fbo->setColorAttachment(renBuf, idx);
        }
        fbo->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT + idx);
    }
    //
    // a sole depth buffer
    //
    if (_depth && !_stencil) {
        //
        // use textures?
        //
        if (_ds_buffer.enable) {
            ImageUnrecPtr           texImg = (_ds_buffer.image  == NULL ? Image::create()           : _ds_buffer.image);
            TextureObjChunkUnrecPtr texObj = (_ds_buffer.texObj == NULL ? TextureObjChunk::create() : _ds_buffer.texObj);
            TextureBufferUnrecPtr   texBuf = TextureBuffer::create();

            if (_ds_buffer.image == NULL)
                texImg->set(_ds_buffer.pixel_format, 
                            width, height, 1, 1, 1, 0.f, NULL,
                            _ds_buffer.type, 
                            _ds_buffer.main_memory);

            texObj->setImage(texImg);

            if (_ds_buffer.texObj == NULL) {
                texObj->setInternalFormat(GL_DEPTH_COMPONENT24);
                texObj->setExternalFormat(GL_DEPTH_COMPONENT24);
            }
            texBuf->setTexture(texObj);

            fbo->setDepthAttachment(texBuf);
        } else 
        //
        // no, then use simple render buffer
        //
        {
            RenderBufferUnrecPtr renBuf = RenderBuffer::create();
            renBuf->setInternalFormat(GL_DEPTH_COMPONENT24);
            fbo->setDepthAttachment(renBuf);
        }
    } else
    //
    // or a combined depth/stencil buffer
    //
    if (_depth && _stencil) {
        //
        // use textures?
        //
        if (_ds_buffer.enable) {
            ImageUnrecPtr           texImg = (_ds_buffer.image  == NULL ? Image::create()           : _ds_buffer.image);
            TextureObjChunkUnrecPtr texObj = (_ds_buffer.texObj == NULL ? TextureObjChunk::create() : _ds_buffer.texObj);
            TextureBufferUnrecPtr   texBuf = TextureBuffer::create();

            if (_ds_buffer.image == NULL)
                texImg->set(GL_DEPTH_STENCIL_EXT, 
                            width, height, 1, 1, 1, 0.f, NULL,
                            GL_UNSIGNED_INT_24_8, 
                            _ds_buffer.main_memory);

            texObj->setImage(texImg);
            texObj->setInternalFormat(GL_DEPTH24_STENCIL8_EXT);
            texObj->setExternalFormat(GL_DEPTH_STENCIL_EXT);
            texBuf->setTexture(texObj);

            fbo->setDepthAttachment(texBuf);
            fbo->setStencilAttachment(texBuf);
        } else 
        //
        // no, then use simple render buffer
        //
        {
            RenderBufferUnrecPtr renBuf = RenderBuffer::create();
            renBuf->setInternalFormat(GL_DEPTH24_STENCIL8);
            fbo->setDepthAttachment(renBuf);
            fbo->setStencilAttachment(renBuf);
        }
    }

    fbo->setWidth (width );
    fbo->setHeight(height);

    return FrameBufferObjectTransitPtr(fbo);
}

//
// Convenience helper object wrapping the FBO uses FBOBuilder internally
// =====================================================================
//
class SimpleFBO
{
public:
                SimpleFBO(UInt32 width, 
                          UInt32 height,
                          bool color_textured,
                          bool depth_stencil_textured,
                          bool read_back_color = true,
                          bool read_back_depth_stencil = false);

                SimpleFBO(UInt32 width,
                          UInt32 height,
                          const std::vector<FBOBuilder::TextureData>& buffers,
                          bool depth, 
                          bool stencil, 
                          const FBOBuilder::TextureData& ds_buffer);

               ~SimpleFBO() { _fbo = NULL; }

public:
    FrameBufferObject*     fbo             () const { return _fbo; }

    FrameBufferAttachment* colorBuffer     (UInt32 idx = 0) const { return _fbo ? _fbo->getColorAttachments(idx) : NULL; }
    FrameBufferAttachment* depthBuffer     () const               { return _fbo ? _fbo->getDepthAttachment()     : NULL; }
    FrameBufferAttachment* stencilBuffer   () const               { return _fbo ? _fbo->getStencilAttachment()   : NULL;}

    TextureObjChunk*       colorTexObj     (UInt32 idx = 0) const;
    TextureObjChunk*       depthTexObj     () const;
    TextureObjChunk*       stencilTexObj   () const;

private:
    FrameBufferObjectRecPtr     _fbo;
};

SimpleFBO::SimpleFBO(
    UInt32 width, 
    UInt32 height,
    bool color_textured, 
    bool depth_stencil_textured,
    bool read_back_color,
    bool read_back_depth_stencil)
: _fbo(NULL)
{
    FBOBuilder::TextureData color_data;
    color_data.enable = color_textured;
    color_data.main_memory = read_back_color;

    FBOBuilder::TextureData depth_stencil_data;
    depth_stencil_data.enable = depth_stencil_textured;
    depth_stencil_data.main_memory = read_back_depth_stencil;

    FBOBuilder::VecTextureDataT color_vec;
    color_vec.push_back(color_data);

    FBOBuilder fbo_builder(color_vec, true, true, depth_stencil_data);

    _fbo = fbo_builder(width, height);
}

SimpleFBO::SimpleFBO(
    UInt32 width,
    UInt32 height,
    const std::vector<FBOBuilder::TextureData>& buffers,
    bool depth, 
    bool stencil, 
    const FBOBuilder::TextureData& ds_buffer)
: _fbo(NULL)
{
    FBOBuilder fbo_builder(buffers, depth, stencil, ds_buffer);

    _fbo = fbo_builder(width, height);
}

TextureObjChunk* SimpleFBO::colorTexObj(UInt32 idx) const
{
    TextureBuffer* texBuf = dynamic_cast<TextureBuffer*>(colorBuffer(idx));
    if (texBuf)
        return texBuf->getTexture();

    return NULL;
}

TextureObjChunk* SimpleFBO::depthTexObj() const
{
    TextureBuffer* texBuf = dynamic_cast<TextureBuffer*>(depthBuffer());
    if (texBuf)
        return texBuf->getTexture();

    return NULL;
}

TextureObjChunk* SimpleFBO::stencilTexObj() const
{
    TextureBuffer* texBuf = dynamic_cast<TextureBuffer*>(stencilBuffer());
    if (texBuf)
        return texBuf->getTexture();

    return NULL;
}

//
// function forward declarations
// =============================
//
static void cleanup(void);
static void display(void);
static void reshape(int w, int h);
static void mouse(int button, int state, int x, int y);
static void motion(int x, int y);
static void keyboard(unsigned char k, int, int);
static int  setupGLUT(int *argc, char *argv[]);
static int  doMain(int argc, char *argv[]);


static NodeTransitPtr   createStaticScene();
static NodeTransitPtr   createDynamicScene();

static void             applyRenderMode();
static void             enableStaticRendering();
static void             enableDynamicRendering();

#if 0
static Node*            rootNode(Node* node);
#endif

//
// global state of example
// =======================
//
bool                     static_render_mode;
SimpleSceneManagerRefPtr mgr;
NodeRefPtr               staticScene;
NodeRefPtr               dynamicScene;
GLUTWindowRefPtr         win;
ViewportRefPtr           viewport;
GradientBackgroundRefPtr background;

boost::scoped_ptr<SimpleFBO> spSimpleFBO;

//
// functions implementation
// ========================
//

static void cleanup(void)
{
    mgr   = NULL;
    staticScene = NULL;
    dynamicScene = NULL;
    win   = NULL;
    viewport = NULL;
    background = NULL;
    spSimpleFBO.reset();
}

static void display(void)
{
    commitChanges();
    mgr->redraw();
}

static void reshape(int w, int h)
{
    mgr->resize(w,h);
    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

static void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

static void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:
    case 'q':
    case 'Q':
    {
        cleanup();
        osgExit();

        std::exit(EXIT_SUCCESS);
    }
    break;

    case '1':
    {
        static_render_mode = !static_render_mode;
        applyRenderMode();
    }
    break;
    }
    glutPostRedisplay();
}

//
// initialize GLUT
//
static int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);

    glutInitDisplayMode(
        GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE 
#ifdef USE_MULTISAMPLING
      | GLUT_MULTISAMPLE
#endif
    );

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

//
// setup scene
//
static int doMain(int argc, char *argv[])
{
    preloadSharedObject("OSGFileIO");
    preloadSharedObject("OSGImageFileIO");

    osgInit(argc,argv);

    int winid = setupGLUT(&argc, argv);

    win = GLUTWindow::create();
    win->setGlutId(winid);
    win->init();

    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));

        std::list<const char*> suffixes;
        SceneFileHandler::the()->getSuffixList(suffixes);

        for(std::list<const char*>::iterator it  = suffixes.begin();
                                            it != suffixes.end();
                                        ++it)
        {
            FWARNING(("%s\n", *it));
        }

        staticScene = createStaticScene();
    }
    else
    {
        staticScene = SceneFileHandler::the()->read(argv[1]);
    }

    dynamicScene = createDynamicScene();

    spSimpleFBO.reset(new SimpleFBO(2, 2, true, true, true, false));

    commitChanges();

    NodeUnrecPtr root = makeCoredNode<Group>();

    mgr = SimpleSceneManager::create();
    mgr->setWindow(win);
    mgr->setRoot  (root);

    background = GradientBackground::create();
    background->addLine(Color3f(0,0,0), 0);
    background->addLine(Color3f(1,1,1), 1);

    viewport = win->getPort(0);
    viewport->setBackground(background);

    static_render_mode = true;
    applyRenderMode();

    mgr->showAll();

    return 0;
}

//
// create an arbitrarly complex render scene
//
static NodeTransitPtr createStaticScene()
{
    NodeUnrecPtr root = makeCoredNode<Group>();

    typedef boost::mt19937 base_generator_type;
    static base_generator_type generator(0);
    static boost::uniform_01<float> value;
    static boost::variate_generator< base_generator_type, boost::uniform_01<float> > die(generator, value);

    for (int i = 0; i < max_tori; ++i) {
        NodeUnrecPtr scene = makeTorus(.5, 2, 32, 32);

        TransformUnrecPtr transformCore = Transform::create();
        Matrix mat;

        mat.setIdentity();

        float x = 500.f * die();
        float y = 500.f * die();
        float z = 500.f * die();

        float e1 = die();
        float e2 = die();
        float e3 = die();

        Vec3f v(e1,e2,e3);
        v.normalize();

        float a = TwoPi * die();

        Quaternion q(v, a);

        mat.setTranslate(x,y,z);
        mat.setRotate(q);

        transformCore->setMatrix(mat);

        NodeUnrecPtr trafo = makeNodeFor(transformCore);

        trafo->addChild(scene);

        root->addChild(trafo);
    }
    
    return NodeTransitPtr(root);
}

static NodeTransitPtr createDynamicScene()
{
    NodeUnrecPtr scene = makeCylinder(30, 100, 16, true, true, true);
    return NodeTransitPtr(scene);
}

static void applyRenderMode()
{
    if (static_render_mode)
    {
        enableStaticRendering();
    } 
    else
    {
        enableDynamicRendering();
    }
}

static void enableStaticRendering()
{
//    UInt32 width  = win->getWidth();
//    UInt32 height = win->getHeight();

    FBOGrabForegroundUnrecPtr fboGrabForeground = FBOGrabForeground::create();
    fboGrabForeground->setFrameBufferObject(spSimpleFBO->fbo());
    fboGrabForeground->setAutoResize(true);

    viewport->addForeground(fboGrabForeground);
    viewport->setBackground(background);

    NodeUnrecPtr root = makeCoredNode<Group>();
    root->addChild(staticScene);
    mgr->setRoot(root);
}

static void enableDynamicRendering()
{
    FBOBackgroundUnrecPtr fboBckgnd = FBOBackground::create();
    fboBckgnd->setFrameBufferObject(spSimpleFBO->fbo());

    viewport->clearForegrounds();
    viewport->setBackground(fboBckgnd);

    NodeUnrecPtr root = makeCoredNode<Group>();
    root->addChild(dynamicScene);
    mgr->setRoot(root);
}

#if 0
static Node* rootNode(Node* node)
{
    Node* root = NULL;
    while (node) {
        root = node;
        node = node->getParent();
    }
    return root;
}
#endif

//
// main entry point
//
int main(int argc, char *argv[])
{
    int ret = doMain(argc, argv);

    glutMainLoop();

    cleanup();

    osgExit();

    return ret;
}

