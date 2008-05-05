#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGSimpleStatisticsForeground.h>
#include <OSGSolidBackground.h>
#include <OSGImage.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGSolidBackground.h>
#include <OSGGeometry.h>
#include <OSGTypedGeoIntegralProperty.h>

#include <OSGImage.h>
#include <OSGImageFileHandler.h>

#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE
using namespace std;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

NodeRecPtr scene;

SimpleStatisticsForegroundRecPtr statfg;
StatElemDesc<OSG::StatStringElem> textureFormatDesc("textureFormat", "The format of the texture");
StatElemDesc<OSG::StatStringElem> textureDataTypeDesc("textureDataType", "The data type of the texture");
StatElemDesc<OSG::StatStringElem> textureSizeDesc("textureSize", "The size of the texture");
StatElemDesc<OSG::StatIntElem> textureDimensionDesc("textureDimension", "The dimension of the texture");
StatElemDesc<OSG::StatIntElem> textureBPPDesc("textureBPP", "The bytes per pixel of the texture");
StatElemDesc<OSG::StatIntElem> textureMipMapCountDesc("textureMipMapCount", "The mipmap count of the texture");
StatElemDesc<OSG::StatIntElem> textureFrameCountDesc("textureFrameCount", "The frame count of the texture");

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void updateScene(const std::string &filename)
{
    // Try to create the new image
    ImageRecPtr imagePtr = ImageFileHandler::the()->read(filename.c_str());
    if (imagePtr == NULL)
        return;

    // Update information on the screen
    StatStringElem *statElem = statfg->editCollector()->getElem(textureFormatDesc);
    switch (imagePtr->getPixelFormat())
    {
        case Image::OSG_A_PF:
            statElem->set("OSG_A_PF");
            break;
        case Image::OSG_I_PF:
            statElem->set("OSG_I_PF");
            break;
        case Image::OSG_L_PF:
            statElem->set("OSG_L_PF");
            break;
        case Image::OSG_LA_PF:
            statElem->set("OSG_LA_PF");
            break;
        case Image::OSG_RGB_PF:
            statElem->set("OSG_RGB_PF");
            break;
        case Image::OSG_RGBA_PF:
            statElem->set("OSG_RGBA_PF");
            break;
        case Image::OSG_BGR_PF:
            statElem->set("OSG_BGRA_PF");
            break;
        case Image::OSG_BGRA_PF:
            statElem->set("OSG_BGRA_PF");
            break;
        case Image::OSG_RGB_DXT1:
            statElem->set("OSG_RGB_DXT1");
            break;
        case Image::OSG_RGBA_DXT1:
            statElem->set("OSG_RGBA_DXT1");
            break;
        case Image::OSG_RGBA_DXT3:
            statElem->set("OSG_RGBA_DXT3");
            break;
        case Image::OSG_RGBA_DXT5:
            statElem->set("OSG_RGBA_DXT5");
            break;
        default:
            statElem->set("???");
            break;
    }
    statElem = statfg->editCollector()->getElem(textureDataTypeDesc);
    switch (imagePtr->getDataType())
    {
        case Image::OSG_UINT8_IMAGEDATA:
            statElem->set("OSG_UINT8_IMAGEDATA");
            break;
        case Image::OSG_UINT16_IMAGEDATA:
            statElem->set("OSG_UINT16_IMAGEDATA");
            break;
        case Image::OSG_UINT32_IMAGEDATA:
            statElem->set("OSG_UINT32_IMAGEDATA");
            break;
        case Image::OSG_FLOAT16_IMAGEDATA:
            statElem->set("OSG_FLOAT16_IMAGEDATA");
            break;
        case Image::OSG_FLOAT32_IMAGEDATA:
            statElem->set("OSG_FLOAT32_IMAGEDATA");
            break;
        default:
            statElem->set("???");
            break;
    }
    ostringstream os;
    os << imagePtr->getWidth() << 'x' << imagePtr->getHeight() << 'x' << imagePtr->getDepth();
    statfg->editCollector()->getElem(textureSizeDesc)->set(os.str());
    statfg->editCollector()->getElem(textureDimensionDesc)->set(imagePtr->getDimension());
    statfg->editCollector()->getElem(textureBPPDesc)->set(imagePtr->getBpp());
    statfg->editCollector()->getElem(textureMipMapCountDesc)->set(imagePtr->getMipMapCount());
    statfg->editCollector()->getElem(textureFrameCountDesc)->set(imagePtr->getFrameCount());

    // Put it all together into a Geometry NodeCore.
    GeometryRecPtr geo = makePlaneGeo(imagePtr->getWidth(), imagePtr->getHeight(), 1, 1);
    NodeRecPtr imageNode = Node::create();
    imageNode->setCore(geo);
    NodeRecPtr transNodePtr = Node::create();
    TransformRecPtr transPtr = Transform::create();
    Matrix transMatrix;
    transMatrix.setTranslate(0.f, 0.f, -1.f);
    transPtr->setMatrix(transMatrix);
    transNodePtr->setCore(transPtr);
    transNodePtr->addChild(imageNode);

    TextureObjChunkRecPtr texObjChunk = TextureObjChunk::create();
    texObjChunk->setImage(imagePtr);
    texObjChunk->setWrapS(GL_CLAMP);
    texObjChunk->setWrapT(GL_CLAMP);
    texObjChunk->setMagFilter(GL_NEAREST);
    texObjChunk->setMinFilter(GL_NEAREST);
    TextureEnvChunkRecPtr texEnvChunk = TextureEnvChunk::create();
    texEnvChunk->setEnvMode(GL_MODULATE);

    MaterialChunkRecPtr matChunk = MaterialChunk::create();
    matChunk->setAmbient(Color4f(1.f, 1.f, 1.f, 1.f));
    matChunk->setDiffuse(Color4f(1.f, 1.f, 1.f, 1.f));
    matChunk->setEmission(Color4f(0.f, 0.f, 0.f, 1.f));
    matChunk->setSpecular(Color4f(0.f, 0.f, 0.f, 1.f));
    matChunk->setShininess(0);

    ChunkMaterialRecPtr m = ChunkMaterial::create();
    m->addChunk(texObjChunk);
    m->addChunk(texEnvChunk);
    m->addChunk(matChunk);

    geo->setMaterial(m);

    scene->clearChildren();
    scene->addChild(transNodePtr);
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowRecPtr gwin= GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    // put the geometry core into a node
    scene = Node::create();
    GroupRecPtr groupPtr = Group::create();
    scene->setCore(groupPtr);

    statfg = SimpleStatisticsForeground::create();
    statfg->setSize(25);
    statfg->setColor(Color4f(0,1,0,0.9));
    statfg->addElement(textureFormatDesc, "Pixel Format: %s");
    statfg->addElement(textureDataTypeDesc, "Data Type: %s");
    statfg->addElement(textureSizeDesc, "Texture Size: %s");
    statfg->addElement(textureDimensionDesc, "Dimension: %i");
    statfg->addElement(textureBPPDesc, "BPP: %i");
    statfg->addElement(textureMipMapCountDesc, "MipMapCount: %i");
    statfg->addElement(textureFrameCountDesc, "FrameCount: %i");

    // Create the background
    SolidBackgroundRecPtr bg = SolidBackground::create();
    bg->setColor(Color3f(0.1, 0.1, 0.5));

    if (argc < 2)
    {
        std::cerr << "Usage: testImageLoader <filename>" << std::endl;
        return EXIT_FAILURE;
    }
    updateScene(argv[1]);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    // add the statistics forground
    gwin->getPort(0)->addForeground(statfg);
    gwin->getPort(0)->setBackground(bg);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display( void )
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    mgr->redraw();
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            delete mgr;
            scene  = NULL;
            statfg = NULL;
            osgExit();
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

    return winid;
}
