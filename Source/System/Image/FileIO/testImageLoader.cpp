#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGBaseFunctions.h"
#include "OSGTransform.h"
#include "OSGGroup.h"
#include "OSGSimpleStatisticsForeground.h"
#include "OSGSolidBackground.h"
#include "OSGImage.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGSolidBackground.h"
#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"

#include "OSGImage.h"
#include "OSGImageFileHandler.h"
#include "OSGSceneFileHandler.h"

#include <sstream>

using namespace std;

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManagerRefPtr mgr;

OSG::NodeRecPtr scene;

OSG::SimpleStatisticsForegroundRecPtr statfg;
OSG::StatElemDesc<OSG::StatStringElem> textureFormatDesc("textureFormat", "The format of the texture");
OSG::StatElemDesc<OSG::StatStringElem> textureDataTypeDesc("textureDataType", "The data type of the texture");
OSG::StatElemDesc<OSG::StatStringElem> textureSizeDesc("textureSize", "The size of the texture");
OSG::StatElemDesc<OSG::StatIntElem> textureDimensionDesc("textureDimension", "The dimension of the texture");
OSG::StatElemDesc<OSG::StatIntElem> textureBPPDesc("textureBPP", "The bytes per pixel of the texture");
OSG::StatElemDesc<OSG::StatIntElem> textureMipMapCountDesc("textureMipMapCount", "The mipmap count of the texture");
OSG::StatElemDesc<OSG::StatIntElem> textureFrameCountDesc("textureFrameCount", "The frame count of the texture");

std::string szFilename;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void updateScene(const std::string &filename, OSG::Image::PixelFormat compressTo = OSG::Image::OSG_INVALID_PF)
{
    // Try to create the new image
    OSG::ImageRecPtr imagePtr = 
        OSG::ImageFileHandler::the()->read(filename.c_str());

    if (imagePtr == NULL)
        return;

    if(compressTo != OSG::Image::OSG_INVALID_PF)
    {
        imagePtr->reformat(compressTo);
    }

    // Update information on the screen
    OSG::StatStringElem *statElem = 
        statfg->editCollector()->getElem(textureFormatDesc);

    switch (imagePtr->getPixelFormat())
    {
        case OSG::Image::OSG_A_PF:
            statElem->set("OSG_A_PF");
            break;
        case OSG::Image::OSG_I_PF:
            statElem->set("OSG_I_PF");
            break;
        case OSG::Image::OSG_L_PF:
            statElem->set("OSG_L_PF");
            break;
        case OSG::Image::OSG_LA_PF:
            statElem->set("OSG_LA_PF");
            break;
        case OSG::Image::OSG_RGB_PF:
            statElem->set("OSG_RGB_PF");
            break;
        case OSG::Image::OSG_RGBA_PF:
            statElem->set("OSG_RGBA_PF");
            break;
        case OSG::Image::OSG_BGR_PF:
            statElem->set("OSG_BGRA_PF");
            break;
        case OSG::Image::OSG_BGRA_PF:
            statElem->set("OSG_BGRA_PF");
            break;
        case OSG::Image::OSG_RGB_DXT1:
            statElem->set("OSG_RGB_DXT1");
            break;
        case OSG::Image::OSG_RGBA_DXT1:
            statElem->set("OSG_RGBA_DXT1");
            break;
        case OSG::Image::OSG_RGBA_DXT3:
            statElem->set("OSG_RGBA_DXT3");
            break;
        case OSG::Image::OSG_RGBA_DXT5:
            statElem->set("OSG_RGBA_DXT5");
            break;
        default:
            statElem->set("???");
            break;
    }
    statElem = statfg->editCollector()->getElem(textureDataTypeDesc);
    switch (imagePtr->getDataType())
    {
        case OSG::Image::OSG_UINT8_IMAGEDATA:
            statElem->set("OSG_UINT8_IMAGEDATA");
            break;
        case OSG::Image::OSG_UINT16_IMAGEDATA:
            statElem->set("OSG_UINT16_IMAGEDATA");
            break;
        case OSG::Image::OSG_UINT32_IMAGEDATA:
            statElem->set("OSG_UINT32_IMAGEDATA");
            break;
        case OSG::Image::OSG_FLOAT16_IMAGEDATA:
            statElem->set("OSG_FLOAT16_IMAGEDATA");
            break;
        case OSG::Image::OSG_FLOAT32_IMAGEDATA:
            statElem->set("OSG_FLOAT32_IMAGEDATA");
            break;
        case OSG::Image::OSG_INT16_IMAGEDATA:
            statElem->set("OSG_INT16_IMAGEDATA");
            break;
        case OSG::Image::OSG_INT32_IMAGEDATA:
            statElem->set("OSG_INT32_IMAGEDATA");
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
    OSG::GeometryRecPtr geo = OSG::makePlaneGeo(imagePtr->getWidth(), imagePtr->getHeight(), 1, 1);
    OSG::NodeRecPtr imageNode = OSG::Node::create();
    imageNode->setCore(geo);
    OSG::NodeRecPtr transNodePtr = OSG::Node::create();
    OSG::TransformRecPtr transPtr = OSG::Transform::create();
    OSG::Matrix transMatrix;
    transMatrix.setTranslate(0.f, 0.f, -1.f);
    transPtr->setMatrix(transMatrix);
    transNodePtr->setCore(transPtr);
    transNodePtr->addChild(imageNode);

    OSG::TextureObjChunkRecPtr texObjChunk = OSG::TextureObjChunk::create();
    texObjChunk->setImage(imagePtr);
    texObjChunk->setWrapS(GL_CLAMP);
    texObjChunk->setWrapT(GL_CLAMP);
    texObjChunk->setMagFilter(GL_NEAREST);
    texObjChunk->setMinFilter(GL_NEAREST);
    OSG::TextureEnvChunkRecPtr texEnvChunk = OSG::TextureEnvChunk::create();
    texEnvChunk->setEnvMode(GL_MODULATE);

    OSG::MaterialChunkRecPtr matChunk = OSG::MaterialChunk::create();
    matChunk->setAmbient(OSG::Color4f(1.f, 1.f, 1.f, 1.f));
    matChunk->setDiffuse(OSG::Color4f(1.f, 1.f, 1.f, 1.f));
    matChunk->setEmission(OSG::Color4f(0.f, 0.f, 0.f, 1.f));
    matChunk->setSpecular(OSG::Color4f(0.f, 0.f, 0.f, 1.f));
    matChunk->setShininess(0);

    OSG::ChunkMaterialRecPtr m = OSG::ChunkMaterial::create();
    m->addChunk(texObjChunk);
    m->addChunk(texEnvChunk);
    m->addChunk(matChunk);

    geo->setMaterial(m);

    scene->clearChildren();
    scene->addChild(transNodePtr);

    if(compressTo != OSG::Image::OSG_INVALID_PF)
    {
        OSG::SceneFileHandler::the()->write(scene->getChild(0), 
                                            "/tmp/comp.osb");
        OSG::SceneFileHandler::the()->write(scene->getChild(0), 
                                            "/tmp/comp.osg");
    }

}

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowRecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    // put the geometry core into a node
    scene = OSG::Node::create();
    OSG::GroupRecPtr groupPtr = OSG::Group::create();
    scene->setCore(groupPtr);

    statfg = OSG::SimpleStatisticsForeground::create();
    statfg->setSize(25);
    statfg->setColor(OSG::Color4f(0,1,0,0.9f));
    statfg->addElement(textureFormatDesc, "Pixel Format: %s");
    statfg->addElement(textureDataTypeDesc, "Data Type: %s");
    statfg->addElement(textureSizeDesc, "Texture Size: %s");
    statfg->addElement(textureDimensionDesc, "Dimension: %i");
    statfg->addElement(textureBPPDesc, "BPP: %i");
    statfg->addElement(textureMipMapCountDesc, "MipMapCount: %i");
    statfg->addElement(textureFrameCountDesc, "FrameCount: %i");

    // Create the background
    OSG::SolidBackgroundRecPtr bg = OSG::SolidBackground::create();
    bg->setColor(OSG::Color3f(0.1f, 0.1f, 0.5f));

    if (argc < 2)
    {
        std::cerr << "Usage: testImageLoader <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    updateScene(argv[1]);

    szFilename = argv[1];

    // create the SimpleSceneManager helper
    mgr = OSG::SimpleSceneManager::create();

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    // add the statistics forground
    gwin->getPort(0)->addForeground(statfg);
    gwin->getPort(0)->setBackground(bg);


    return 0;
}

int main(int argc, char **argv)
{
    doMain(argc, argv);

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
            mgr    = NULL;
            scene  = NULL;
            statfg = NULL;

            OSG::osgExit();
            exit(0);
        }
        case '0':
            updateScene(szFilename);
            break;
        case '1':
            updateScene(szFilename, OSG::Image::OSG_RGB_DXT1);
            break;
        case '2':
            updateScene(szFilename, OSG::Image::OSG_RGBA_DXT1);
            break;
        case '3':
            updateScene(szFilename, OSG::Image::OSG_RGBA_DXT3);
            break;
        case '5':
            updateScene(szFilename, OSG::Image::OSG_RGBA_DXT5);
            break;
                
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
