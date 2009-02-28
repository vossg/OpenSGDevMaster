// OpenSG Tutorial Example: Changing Texture on Background

// This example shows how to change the texture displayed on a
// TextureBackground in each frame. This could be used to play back a video.

#ifdef OSG_BUILD_ACTIVE

#include <OSGConfig.h>
#include <OSGGLUT.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTextureObjChunk.h>
#include <OSGBaseFunctions.h>

#include <OSGTextureBackground.h>

#else

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGBaseFunctions.h>

#include <OpenSG/OSGTextureBackground.h>

#endif // OSG_BUILD_ACTIVE

// Activate the OpenSG namespace

OSG_USING_NAMESPACE

// The pointer to the transformation

TransformRefPtr trans;

// The pointer to the dynamic image and the texture

ImageRefPtr           image;
TextureObjChunkRefPtr texObj;

// Some helper flags for different code pathes
// flag to indicate whether the images are power-of-two (POT) in size or not

bool isPOT = false;

// flag to indicate whether NPOT textures are available
// Purely informative, the code doesn't really care.

bool hasNPOT = false;


// flag to indicate that only a small part of the image should be changed
// per frame. The random image generation can get slow for large
// images.

bool changeOnlyPart = false;

// The SimpleSceneManager to manage simple applications

SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront

int  setupGLUT(int *argc, char *argv[]);
void cleanup  (void                   );

// Grab/update the image
// This just update the image's data and tells the texture that it changed.
// For a video this would grab the next frame

void grabImage(Image *img)
{
    UInt8* data = img->editData();

    // for this example, just fill it with random junk
    if(changeOnlyPart)
    {
        // Just change a small rectangular area
        UInt32 x = rand() % (img->getWidth() - 100);
        UInt32 y = rand() % (img->getHeight() - 100);
        UInt32 w = rand() % 100;
        UInt32 h = rand() % 100;
        UInt32 bpp = img->getBpp();
        UInt32 bpl = img->getWidth() * bpp;
        UInt32 bytes = w * bpp;

        data += y * bpl + x * bpp;

        UInt8 val = (rand() & 0x7f + 0x80);

        for(UInt32 i = h; i > 0; --i, data += bpl)
        {
            UInt8 *d = data;

            for(UInt32 j = bytes; j > 0; --j)
                *d++ = val;
        }

        // If only a part of the image changed, only that part needs to
        // be updated. The speed of the update operation is pretty
        // directly dependent on the amount of data changed.
        texObj->imageContentChanged(x, x + w, y, y + h);
    }
    else
    {

        // Fill the whole picture

        for(UInt32 i = img->getHeight(); i > 0; --i)
        {
            UInt8 val = (rand() & 0x3f + 0x80);

            for(UInt32 j = img->getWidth() * img->getBpp(); j > 0; --j)
                *data++ = val;
        }

        // Everything changed
        texObj->imageContentChanged();
    }
}



// redraw the window
void display( void )
{
    // update the geometry
    Matrix m;

    Real32 t = glutGet(GLUT_ELAPSED_TIME );

    m.setTransform(Vec3f(osgSin(t / 1000.f),
                         osgCos(t / 1000.f),
                         osgSin(t / 1000.f)),

                   Quaternion( Vec3f(0,1,0), t / 1000.f));

    trans->setMatrix(m);

    // update the image

    grabImage(image);

    // redraw the screen

    mgr->redraw();
}

void update(void)
{
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    {
        // the connection between GLUT and OpenSG
        GLUTWindowRefPtr gwin = GLUTWindow::create();

        gwin->setGlutId(winid);
        gwin->init();

        // create the scene
        NodeRefPtr torus = makeTorus( .5, 2, 16, 32 );
        NodeRefPtr scene = Node::create();

        trans = Transform::create();

        scene->setCore(trans);
        scene->addChild(torus);

        // Create the parts needed for the video background
        UInt32 width  = 640;
        UInt32 height = 480;

        // get the desired size from the command line
        if(argc >= 3)
        {
            width  = atoi(argv[1]);
            height = atoi(argv[2]);
        }

        // To check OpenGL extensions, the Window needs to have run through
        // frameInit at least once. This automatically happens when rendering,
        // but we can't wait for that here.

        gwin->activate ();
        gwin->frameInit();

        // Now we can check for OpenGL extensions
        hasNPOT = gwin->hasExtension("GL_ARB_texture_non_power_of_two");

        // Print what we've got
        SLOG << "Got " << (isPOT?"":"non-") << "power-of-two images and "
            << (hasNPOT?"can":"cannot") << " use NPOT textures, changing "
            << (changeOnlyPart?"part":"all")
            << " of the screen"
            << std::endl;

        // Ok, now for the meat of the code...
        // first we need an Image to hold the picture(s) to show
        image = Image::create();

        // set the image's size and type, and allocate memory
        // this example uses RGB. On some systems (e.g. Windows) BGR
        // or BGRA might be faster, it depends on how the images are
        // acquired

        image->set(Image::OSG_RGB_PF, width, height);



        // Now create the texture to be used for the background
        texObj = TextureObjChunk::create();

        // Associate image and texture
        texObj->setImage(image);

        // Set filtering modes. LINEAR is cheap and good if the image size
        // changes very little (i.e. the window is about the same size as
        // the images).

        texObj->setMinFilter(GL_LINEAR);
        texObj->setMagFilter(GL_LINEAR);

        // Set the wrapping modes. We don't need repetition, it might actually
        // introduce artifactes at the borders, so switch it off.

        texObj->setWrapS(GL_CLAMP_TO_EDGE);
        texObj->setWrapT(GL_CLAMP_TO_EDGE);

        // Newer versions of OpenGL can handle NPOT textures directly.
        // OpenSG will do that internally automatically.
        //
        // Older versions need POT textures. By default OpenSG
        // will scale an NPOT texture to POT while defining it.
        // For changing textures that's too slow.
        // So tell OpenSG not to scale the image and adjust the texture
        // coordinates used by the TextureBackground (see below).

        texObj->setScale(false);

        // Create the background

        TextureBackgroundRefPtr back = TextureBackground::create();

        // Set the texture to use
        back->setTexture(texObj);

        // if the image is NPOT and we don't have hardware support for it
        // adjust the texture coordinates.
        if(isPOT == false && hasNPOT == false)
        {
            UInt32 potWidth  = osgNextPower2(width );
            UInt32 potHeight = osgNextPower2(height);

            Real32 tcRight = Real32(width ) / Real32(potWidth );
            Real32 tcTop   = Real32(height) / Real32(potHeight);

            back->editMFTexCoords()->push_back(Vec2f(    0.f,   0.f));
            back->editMFTexCoords()->push_back(Vec2f(tcRight,   0.f));
            back->editMFTexCoords()->push_back(Vec2f(tcRight, tcTop));
            back->editMFTexCoords()->push_back(Vec2f(    0.f, tcTop));
        }

        commitChanges();

        // create the SimpleSceneManager helper
        mgr = new SimpleSceneManager;

        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->setStatistics(true);

        // replace the background
        // This has to be done after the viewport has been created, which the
        // SSM does in setRoot().

        ViewportRefPtr vp = gwin->getPort(0);

        vp->setBackground(back);
    }

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;

}

//
// GLUT callback functions
//

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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:
    {
        cleanup();
        OSG::osgExit();
        exit(0);
    }
    break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(update);

    return winid;
}

void cleanup(void)
{
    delete mgr;
    mgr = NULL;

    trans  = NULL;
    image  = NULL;
    texObj = NULL;

    commitChanges();
}
