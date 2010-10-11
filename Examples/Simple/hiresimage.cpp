// OpenSG example: HiResImage.cpp
//
// This example shows how to create a high resolution screen shot from an OpenSG
// window.
// Two independent solutions are provided. The first one uses a GrabForeground
// object and the second one a FrameBufferObject (FBO) for image generation.
//
// This example installs a tiled rendering mechanism which allows the generation
// of really huge images. The resulting hires image is not stored in the main
// memory but is written to disk in blocks.
//
// Specifically demonstrated is the use of the following classes:
//      - GrabForeground
//      - FrameBufferObject,
//      - RenderBuffer
//      - SimpleStage
//      - TileCameraDecorator
//      - TileableBackground
//      - VisitSubTree
//
// This examples a model file provided on the command line or a torus if no file
// is provided.
//
// User interface:
//  a) mouse    => standard navigator
//  b) keyboard =>
//      '1': take a high resolution snapshot with the GrabForeground class
//      '2': take a high resolution snapshot using the FBO technique
//

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/tuple/tuple.hpp>

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGGradientBackground.h>
#include <OSGGrabForeground.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGAction.h>
#include <OSGFrameBufferObject.h>
#include <OSGRenderBuffer.h>
#include <OSGSimpleStage.h>
#include <OSGPassiveViewport.h>
#include <OSGTileCameraDecorator.h>
#include <OSGTileableBackground.h>
#include <OSGVisitSubTree.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGGrabForeground.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGFrameBufferObject.h>
#include <OpenSG/OSGRenderBuffer.h>
#include <OpenSG/OSGSimpleStage.h>
#include <OpenSG/OSGPassiveViewport.h>
#include <OpenSG/OSGTileCameraDecorator.h>
#include <OpenSG/OSGTileableBackground.h>
#include <OpenSG/OSGVisitSubTree.h>
#endif

OSG_USING_NAMESPACE; // just for convenience but not recommended

//
// function forward declarations
//
static void cleanup(void);
static void display(void);
static void reshape(int w, int h);
static void mouse(int button, int state, int x, int y);
static void motion(int x, int y);
static void keyboard(unsigned char k, int, int);
static void writeHiResScreenShot(const char* name, UInt32 width, UInt32 height);
static void writeHiResScreenShotFBO(const char* name, UInt32 width, UInt32 height);
static bool writePNMImagesHeader(const std::vector<ImageUnrecPtr>& vecImages, UInt32 width, UInt32 height, std::ostream& out);
static bool writePNMImagesData(const std::vector<ImageUnrecPtr>& vecImages, std::ostream& out);
static int  setupGLUT(int *argc, char *argv[]);
static int  doMain(int argc, char *argv[]);

//
// global state of example
//
SimpleSceneManager* mgr;
NodeRefPtr          scene;
GLUTWindowRefPtr    win;
const char* output_file     = "grabforeground_image.ppm";
const char* output_file_fbo = "fbo_image.ppm";

//
// Size factors of the output image with respect to the window dimensions.
// The actual image size does account for the aspect ratio of the window.
//
float fw = 2.5f;   // multiplication factor for the window width
float fh = 2.3f;   // multiplication factor for the window height

static void cleanup(void)
{
    delete mgr;
    mgr   = NULL;

    scene = NULL;
    win   = NULL;
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
    UInt32 winWidth  = win->getWidth();
    UInt32 winHeight = win->getHeight();

    UInt32 width  = fw * winWidth;
    UInt32 height = fh * winHeight;

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
        std::cout << "Creating screenshot (Grab FG) "
                  << width << "x" << height << " in '" << output_file
                  << std::endl;
        writeHiResScreenShot(output_file, width, height);
    }
    break;
    case '2':
    {
        std::cout << "Creating screenshot (FBO) "
                  << width << "x" << height << " in '" << output_file_fbo
                  << std::endl;
        writeHiResScreenShotFBO(output_file_fbo, width, height);
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

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

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

        scene = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        scene = SceneFileHandler::the()->read(argv[1]);
    }

    commitChanges();

    mgr = new SimpleSceneManager;

    mgr->setWindow(win);
    mgr->setRoot  (scene);

    GradientBackgroundUnrecPtr background = GradientBackground::create();
    background->addLine(Color3f(0,0,0), 0);
    background->addLine(Color3f(1,1,1), 1);

    Viewport* viewport = win->getPort(0);
    viewport->setBackground(background);

    mgr->showAll();

    return 0;
}

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

//
// scan for root node
//
static Node* rootNode(Node* node)
{
    Node* root = NULL;
    while (node) {
        root = node;
        node = node->getParent();
    }
    return root;
}

//
// GrabForeground based solution
//
static void writeHiResScreenShot(
    const char* name,
    UInt32 width,
    UInt32 height)
{
    size_t num_ports = win->getMFPort()->size();
    if (num_ports == 0)
        return;
    //
    // calc image dimensions
    //
    UInt32 winWidth  = win->getWidth();
    UInt32 winHeight = win->getHeight();

    if (width  < winWidth ) width  = winWidth;
    if (height < winHeight) height = winHeight;

    Real32 a = Real32(winWidth) / Real32(winHeight);
    width = UInt32(a*height);

    //
    // output stream for writing the final image
    //
    std::ofstream stream(name, std::ios::binary);

    if (stream.good() == false)
        return;

    //
    // Tile image used for foreground grabbing
    //
    ImageUnrecPtr grab_image = Image::create();

    GrabForegroundUnrecPtr grabber = GrabForeground::create();
    grabber->setImage     (grab_image);
    grabber->setActive    (true);
    grabber->setAutoResize(false);

    //
    // We tile the final image and render each tile with the screen resolution
    // into the window. The more tiles we use the bigger the resolution of the
    // final image gets with respect to a provided measure of length.
    //
    typedef boost::tuple<TileCameraDecoratorUnrecPtr, bool> TupleT;
    std::vector<TupleT> decorators;
    decorators.resize(num_ports);

    //
    // Setup the tile camera decorators for each viewport of the window and
    // disable the tile property of tileable viewport backgrounds.
    //
    for (size_t i = 0; i < num_ports; ++i) {
        Viewport* vp = win->getPort(i);

        TileCameraDecoratorUnrecPtr decorator = TileCameraDecorator::create();

        decorator->setFullSize (width, height);
        decorator->setDecoratee(vp->getCamera());

        vp->setCamera(decorator);

        bool bTiled = false;
        TileableBackground* tbg = dynamic_cast<TileableBackground*>(vp->getBackground());
        if (tbg) {
            bTiled = tbg->getTile();
            tbg->setTile(false);
        }

        //
        // remember the decorator and the background tile prop setting
        //
        decorators[i] = boost::make_tuple(decorator, bTiled);
    }

    //
    // Add the grabber to the forgrounds of the first viewport
    //
    Viewport* vp0 = win->getPort(0);
    vp0->addForeground(grabber);

    //
    // We write the image in simple ppm format. This one starts with a description
    // header which we output once on first write.
    //
    bool write_header = true;

    //
    // Calc the max y start position (width). We process the tiles from bottom
    // up and from left tp right as determined by the image format.
    //
    Int32 yPosLast = 0;
    for (; yPosLast < height-winHeight; yPosLast += winHeight);

    //
    // Process from bottom to top
    //
    for (Int32 yPos = yPosLast; yPos >= 0; yPos -= winHeight)
    {
        UInt32 ySize = std::min(winHeight, height - yPos);

        //
        // Collect the tile images for each row, i.e. we write the
        // image in row manner to disk. This way the main memory is
        // only moderately stressed.
        //
        std::vector<ImageUnrecPtr> vecColImages;

        //
        // Process from left to right
        //
        for (UInt32 xPos = 0; xPos < width; xPos += winWidth)
        {
            UInt32 xSize = std::min(winWidth, width - xPos);
            //
            // The current tile image
            //
            ImageUnrecPtr col_image = Image::create();
            col_image->set(Image::OSG_RGBA_PF, xSize, ySize);
            //
            // Adapt the tile camera decorator boxes to the current tile
            //
            for (size_t i = 0; i < num_ports; ++i) {
                Viewport* vp = win->getPort(i);
                vp->setSize(0, 0, xSize, ySize);

                TileCameraDecorator* decorator = decorators[i].get<0>();

                decorator->setSize( xPos / float(width),
                                    yPos / float(height),
                          (xPos + xSize) / float(width),
                          (yPos + ySize) / float(height) );
            }
            //
            // Adapt the grabber image size to the current tile dimension
            //
            grab_image->set(Image::OSG_RGBA_PF, xSize, ySize);
            //
            // render the tile
            //
            mgr->redraw();
            //
            // Copy the image into the tile image stored for later processing
            //
            col_image->setSubData(0, 0, 0, xSize, ySize, 1, grabber->getImage()->getData());

            vecColImages.push_back(col_image);
        }

        //
        // Write the image format header once
        //
        if (write_header) {
            write_header = false;
            if (!writePNMImagesHeader(vecColImages, width, height, stream)) break;
        }
        //
        // Write the current column
        //
        if (!writePNMImagesData(vecColImages, stream)) break;
        //
        // Forget the current column images
        //
        vecColImages.clear();
    }

    //
    // restore window and cleanup
    //
    vp0->removeObjFromForegrounds(grabber);

    for (size_t i = 0; i < num_ports; ++i) {
        Viewport* vp = win->getPort(i);

        vp->setCamera(decorators[i].get<0>()->getDecoratee());
        vp->setSize(0, 0, 1, 1);

        TileableBackground* tbg = dynamic_cast<TileableBackground*>(vp->getBackground());
        if (tbg)
            tbg->setTile(decorators[i].get<1>());
    }
}

//
// FBO solution
//
static void writeHiResScreenShotFBO(const char* name, UInt32 width, UInt32 height)
{
    size_t num_ports = win->getMFPort()->size();
    if (num_ports == 0)
        return;
    //
    // calc image dimensions
    //
    UInt32 winWidth  = win->getWidth();
    UInt32 winHeight = win->getHeight();

    if (width  < winWidth ) width  = winWidth;
    if (height < winHeight) height = winHeight;

    Real32 a = Real32(winWidth) / Real32(winHeight);
    width = UInt32(a*height);

    //
    // output stream for writing the final image
    //
    std::ofstream stream(name, std::ios::binary);
    if (stream.good() == false)
        return;

    //
    // Setup the FBO
    //
    FrameBufferObjectUnrecPtr fbo = FrameBufferObject::create();
    //
    // We use two render buffers. One for the color buffer and one for the depth and
    // stencil buffer. This example does not take credit of the stencil buffer. There-
    // fore a depth buffer would suffice. However, the use of the combined depth and
    // stencil buffer is useful in other contextes and hence used.
    //
    RenderBufferUnrecPtr colBuf = RenderBuffer::create();
    RenderBufferUnrecPtr  dsBuf = RenderBuffer::create();
    //
    // As we would like to read back the FBO color buffer, we must provide a fitting
    // image.
    //
    ImageUnrecPtr buffer_image = Image::create();
    buffer_image->set(Image::OSG_RGBA_PF, winWidth, winHeight);
    colBuf->setImage(buffer_image);
    //
    // We must setup the internal image formats of the two render buffers accordingly.
    //
    colBuf->setInternalFormat(GL_RGBA);
    dsBuf ->setInternalFormat(GL_DEPTH24_STENCIL8_EXT);
    //
    // we must inform the FBO about the actual used color render buffers.
    //
    fbo->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    //
    // The FBO takes responsibility of the render buffers. Notice, that the shared
    // depth/stencil buffer is provided twice. As the depth render buffer and as the
    // stencil render buffer.
    //
    fbo->setColorAttachment  (colBuf, 0);
    fbo->setDepthAttachment  (dsBuf);
    fbo->setStencilAttachment(dsBuf);
    //
    // Also the FBO must be sized correctly.
    //
    fbo->setWidth (winWidth );
    fbo->setHeight(winHeight);
    //
    // In order to read the color buffer back next two statements are necessary.
    //
    fbo->setPostProcessOnDeactivate(true);
    fbo->getColorAttachments(0)->setReadBack(true);

    //
    // We tile the final image and render each tile with the screen resolution
    // into the FBO. The more tiles we use the bigger the resolution of the
    // final image gets with respect to a provided measure of length.
    //
    typedef boost::tuple<TileCameraDecoratorUnrecPtr, bool, SimpleStageUnrecPtr, ViewportUnrecPtr> TupleT;
    std::vector<TupleT> decorators;
    decorators.resize(num_ports);

    //
    // Remember the stage viewports for later cleanup
    //
    std::stack<ViewportUnrecPtr> stage_viewports;

    //
    // Setup the tile camera decorators for each viewport of the window and
    // disable the tile property of tileable viewport backgrounds.
    //
    for (size_t i = 0; i < num_ports; ++i) {
        Viewport* vp = win->getPort(i);

        TileCameraDecoratorUnrecPtr decorator = TileCameraDecorator::create();

        decorator->setFullSize (width, height);
        decorator->setDecoratee(vp->getCamera());

        vp->setCamera(decorator);

        bool bTiled = false;
        TileableBackground* tbg = dynamic_cast<TileableBackground*>(vp->getBackground());
        if (tbg) {
            bTiled = tbg->getTile();
            tbg->setTile(false);
        }

        //
        // The scene manager root node does not provide the illumination of the
        // scene. This is governed internally by the manager. However, to take
        // credit of the illumination we scan to the final parent of the scene
        // graph.
        //
        Node* internalRoot = rootNode(mgr->getRoot());
        //
        // We would like to render the scene but won't detach it from its parent.
        // The VisitSubTree allows just that.
        //
        VisitSubTreeUnrecPtr visitor = VisitSubTree::create();
        visitor->setSubTreeRoot(internalRoot);
        NodeUnrecPtr visit_node = makeNodeFor(visitor);
        //
        // We clone the camera of the first viewport and do not swap the buffer on later
        // rendering. This way the image generation process is not noticable in the
        // window.
        //
        CameraUnrecPtr camera = dynamic_pointer_cast<Camera>(vp->getCamera()->shallowCopy());
        //
        // The stage object does provide a render target for the frame buffer attachment.
        // SimpleStage has a camera, a background and the left, right, top, bottom
        // fields to let you restrict rendering to a sub-rectangle of your FBO, i.e.
        // they give you a viewport.
        //
        SimpleStageUnrecPtr stage = SimpleStage::create();
        stage->setRenderTarget(fbo);
        stage->setCamera      (decorator);
        stage->setBackground  (vp->getBackground());
        //
        // Give the stage core a place to live
        //
        NodeUnrecPtr stage_node = makeNodeFor(stage);
        stage_node->addChild(visit_node);
        //
        //   root
        //    |
        //    +- SimpleStage
        //            |
        //            +- VisitSubTree -> ApplicationScene
        //
        NodeUnrecPtr root = makeCoredNode<Group>();
        root->addChild(stage_node);
        //
        // Give the root node a place to live, i.e. create a passive
        // viewport and add it to the window.
        //
        ViewportUnrecPtr stage_viewport = PassiveViewport::create();
        stage_viewport->setRoot      (root);
        stage_viewport->setBackground(vp->getBackground());
        stage_viewport->setCamera    (camera);

        win->addPort(stage_viewport);

        //
        // remember the decorator, the background tile prop setting and the stage setup
        //
        decorators[i] = boost::make_tuple(decorator, bTiled, stage, stage_viewport);
    }

    //
    // We write the image in simple ppm format. This one starts with a description
    // header which we output once on first write.
    //
    bool write_header = true;

    //
    // Calc the max y start position (width). We process the tiles from bottom
    // up and from left tp right as determined by the image format.
    //
    Int32 yPosLast = 0;
    for (; yPosLast < height-winHeight; yPosLast += winHeight);

    //
    // Process from bottom to top
    //
    for (Int32 yPos = yPosLast; yPos >= 0; yPos -= winHeight)
    {
        UInt32 ySize = std::min(winHeight, height - yPos);

        //
        // Collect the tile images for each row, i.e. we write the
        // image in row manner to disk. This way the main memory is
        // only moderately stressed.
        //
        std::vector<ImageUnrecPtr> vecColImages;

        //
        // Process from left to right
        //
        for (UInt32 xPos = 0; xPos < width; xPos += winWidth)
        {
            UInt32 xSize = std::min(winWidth, width - xPos);
            //
            // The current tile image
            //
            ImageUnrecPtr col_image = Image::create();
            col_image->set(Image::OSG_RGBA_PF, xSize, ySize);
            //
            // Adapt the tile camera decorator boxes to the current tile
            //
            for (size_t i = 0; i < num_ports; ++i)
            {
                //
                // this tile does not fill the whole FBO - adjust to only render
                // to a part of it
                //
                decorators[i].get<2>()->setLeft  (0.f);
                decorators[i].get<2>()->setRight (xSize / float(winWidth));
                decorators[i].get<2>()->setBottom(0.f);
                decorators[i].get<2>()->setTop   (ySize / float(winHeight));

                TileCameraDecorator* decorator = decorators[i].get<0>();

                decorator->setSize( xPos / float(width),
                                    yPos / float(height),
                          (xPos + xSize) / float(width),
                          (yPos + ySize) / float(height) );

            }
            //
            // render the tile
            //
            mgr->update();
            win->renderNoFinish(mgr->getRenderAction());
            win->frameExit();
            win->deactivate ();

            //
            // Copy the image into the tile image stored for later processing
            //
            if(fbo)
            {
                RenderBuffer* grabber = dynamic_cast<RenderBuffer*>(fbo->getColorAttachments(0));

                if(grabber)
                {
                    grabber->getImage()->subImage(0, 0, 0, xSize, ySize, 1, col_image);
                }
            }

            vecColImages.push_back(col_image);
        }

        //
        // Write the image format header once
        //
        if (write_header) {
            write_header = false;
            if (!writePNMImagesHeader(vecColImages, width, height, stream)) break;
        }
        //
        // Write the current column
        //
        if (!writePNMImagesData(vecColImages, stream)) break;
        //
        // Forget the current column images
        //
        vecColImages.clear();
    }

    //
    // restore window and cleanup
    //
    for (size_t i = 0; i < num_ports; ++i) {
        win->subPortByObj(decorators[i].get<3>());

        Viewport* vp = win->getPort(i);
        vp->setCamera(decorators[i].get<0>()->getDecoratee());
        vp->setSize(0, 0, 1, 1);

        TileableBackground* tbg = dynamic_cast<TileableBackground*>(vp->getBackground());
        if (tbg)
            tbg->setTile(decorators[i].get<1>());
    }
}

//
// We write the image in PNM format (Portable Any Map).
// see http://netpbm.sourceforge.net/doc/ppm.html
// or  http://en.wikipedia.org/wiki/Netpbm_format
//
static bool writePNMImagesHeader(
    const std::vector<ImageUnrecPtr>& vecImages,
    UInt32 width, UInt32 height,
    std::ostream  &out)
{
    if (vecImages.empty()) return false;

    ImageUnrecPtr col_image = vecImages[0];

    UInt16   bpp = col_image->getBpp();

    switch(bpp)
    {
        case 1:
        case 2:
            return false;
        case 3:
        case 4:
            out << "P6" << std::endl;
            break;
    }

    out << "# PNMImageFileType write" << std::endl;
    out << width << " " << height << std::endl;
    out << "255" << std::endl;

    return true;
}

//
// Write tile images column wise
//
static bool writePNMImagesData(
    const std::vector<ImageUnrecPtr>& vecImages,
    std::ostream  &out)
{
    if (vecImages.empty()) return false;

    ImageUnrecPtr first = vecImages[0];

    UInt16 bpp   = first->getBpp();
    Int16 width  = first->getWidth();
    Int16 height = first->getHeight();

    std::size_t num_images = vecImages.size();

    for(Int16 y = height - 1; y >= 0; y--)
    {
        for (std::size_t img_idx = 0; img_idx < num_images; img_idx++)
        {
            ImageUnrecPtr image = vecImages[img_idx];

            width  = image->getWidth();
            height = image->getHeight();

            Int16 lineSize = bpp * width;

            const UInt8* data = (image->getData() + (lineSize * y));

            for(Int16 x = 0; x < width; x++)
            {
                for(Int16 p = bpp - 1; p--;)
                    out << *data++;

                data++;
            }
        }
    }
    return true;
}

