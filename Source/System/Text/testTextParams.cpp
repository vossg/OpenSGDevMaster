#if 0
// Test for UI code
//
// Just use simple scene manager and create a ui
// to display locally.
//
// Thanks to Allen Bierbaum for the code

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGTextTXFFace.h>
#include <OSGTextTXFGlyph.h>
#include <OSGTextFaceFactory.h>
#include <OSGTextLayoutParam.h>
#include <OSGTextLayoutResult.h>

#include <OSGChunkMaterial.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGBlendChunk.h>
#include <OSGImage.h>
#include <OSGBaseFunctions.h>

#include <sstream>


OSG::SimpleSceneManager* mgr;

int setupGLUT(int* argc, char* argv[]);

/** Little wrapper for holding text data. */
class TextStuff
{
public:
   TextStuff()
      : mFace(NULL),
        mFamilyName("SANS"),
        mNextFamily(0),
        mStyle(OSG::TextFace::STYLE_PLAIN),
        mTextGap(1),
        mTextureWidth(1024),
        mFaceSize(46),
        mLineSpacing(1.0f),
        mMaxExtent(0.0f),
        mGeoScale(1.0f),
        mOffset(0.0, 0.0)
   {;}

   // Initialize the scene structures and get everything going
   void initialize()
   {
      OSG::TextFaceFactory::the()->getFontFamilies(mFamilies);  // Get list of all families

      mRootNode = OSG::Node::create();
      mTextGeom = OSG::Geometry::create();
      mTextMat = OSG::ChunkMaterial::create();
      mTextureObjChunk = OSG::TextureObjChunk::create();
      mTextureEnvChunk = OSG::TextureEnvChunk::create();
      mBlendChunk = OSG::BlendChunk::create();

      // XXX: Setup a default face to use

      // Setup defaults for the texture
      OSG::ImagePtr img = OSG::Image::create();         // Temporary image for now
      OSG::UChar8 data[] = {0,0,0, 50,50,50, 100,100,100, 255,255,255};

      img->set( OSG::Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, data);

      // -- Setup texture and materials -- //
      mTextureObjChunk->setImage(img);
      mTextureObjChunk->setWrapS(GL_CLAMP);
      mTextureObjChunk->setWrapT(GL_CLAMP);
      mTextureObjChunk->setMagFilter(GL_LINEAR);
      mTextureObjChunk->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
      mTextureEnvChunk->setEnvMode(GL_MODULATE);

      OSG::MaterialChunkPtr mat_chunk = OSG::MaterialChunk::create();
      mat_chunk->setAmbient (OSG::Color4f(1.f, 1.f, 1.f, 1.f));
      mat_chunk->setDiffuse (OSG::Color4f(1.f, 1.f, 1.f, 1.f));
      mat_chunk->setEmission(OSG::Color4f(0.f, 0.f, 0.f, 1.f));
      mat_chunk->setSpecular(OSG::Color4f(0.f, 0.f, 0.f, 1.f));
      mat_chunk->setShininess(0);
      mat_chunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

      mBlendChunk->setSrcFactor(GL_SRC_ALPHA);
      mBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
      
      mTextMat->addChunk(mTextureObjChunk);
      mTextMat->addChunk(mTextureEnvChunk);
      mTextMat->addChunk(mBlendChunk);
      mTextMat->addChunk(mat_chunk);

      mTextGeom->setMaterial(mTextMat);
      mRootNode->setCore(mTextGeom);
   }

   void updateScene()
   {
      std::vector<std::string> lines;
      lines.push_back("Hello");
      lines.push_back("World");

      OSG::TextLayoutResult layout_result;
      OSG::TextLayoutParam layout_param;
      layout_param.maxExtend = mMaxExtent;
      layout_param.setLength(mMaxExtent);
      layout_param.spacing = mLineSpacing;

      mFace->layout(lines, layout_param, layout_result);
      OSG::GeometryPtr geom_ptr = mTextGeom.get();

      OSG::Vec2f bounds = layout_result.textBounds;
      //std::cout << "Text bounds: " << bounds << std::endl;
      mFace->fillGeo(geom_ptr, layout_result, mGeoScale, mOffset, OSG::Color3f(0,1,0));

      lines.clear();
      lines.push_back("OpenSG");
      lines.push_back("was");
      lines.push_back("here");

      OSG::Vec2f local_offset(3,4);
      mFace->layout(lines, layout_param, layout_result);
      mFace->addToGeom(geom_ptr, layout_result, mGeoScale, local_offset, OSG::Color3f(0, 0.5, 0.7));


      const float rand_range(10.0f);

      for(unsigned i=0;i<100;++i)
      {
         std::stringstream str;
         str << i;
         OSG::Vec2f rand_offset(OSG::osgRand()*rand_range, OSG::osgRand()*rand_range);
         mFace->layout(str.str(), layout_param, layout_result);
         mFace->addToGeom(geom_ptr, layout_result, mGeoScale, rand_offset, 
                          OSG::Color3f(OSG::osgRand(), OSG::osgRand(), OSG::osgRand()));
      }
   }

   void updateFace()
   {
      // Try to create new face
       OSG::TextTXFParam param;
       param.textureWidth = mTextureWidth;
       param.gap = mTextGap;
       param.size = mFaceSize;

       OSG::TextTXFFace* new_face = OSG::TextTXFFace::create(mFamilyName, mStyle, param);
       if (NULL == new_face)
       {
          std::cerr << "ERROR: Failed to allocate face." << std::endl;
       }
       OSG::subRef(mFace);
       mFace = new_face;
       OSG::addRef(mFace);

       OSG::ImagePtr face_image = mFace->getTexture();
       mTextureObjChunk->setImage(face_image);
   }

   /** Increment/decrement current texture size and regen face. */
   void incTextureSize(bool dec=false)
   {
      switch (mTextureWidth)
      {
      case 0:  mTextureWidth = (dec?0:16);  break;
      case 16:  mTextureWidth = (dec?0:32);  break;
      case 32:  mTextureWidth = (dec?16:64);  break;
      case 64:  mTextureWidth = (dec?32:128);  break;
      case 128:  mTextureWidth = (dec?64:256);  break;
      case 256:  mTextureWidth = (dec?128:512);  break;
      case 512:  mTextureWidth = (dec?256:1024);  break;
      case 1024:  mTextureWidth = (dec?512:1024);  break;
      }

      std::cout << "Setting mTextureWidth: " << mTextureWidth << std::endl;

      updateFace();
      updateScene();
   }

   void incFaceSize(bool inc=true)
   {
      if(inc)
         mFaceSize += 1;
      else if(0 != mFaceSize)
         mFaceSize -= 1;

      std::cout << "Set face size to: " << mFaceSize << std::endl;
      updateFace();
      updateScene();
   }

   /** Cycle to the next family in the set of available font families. */
   void goToNextFamily()
   {
      mFamilyName = mFamilies[mNextFamily];
      mNextFamily += 1;
      if(mNextFamily >= mFamilies.size())
      { mNextFamily = 0; }

      std::cout << "New family: " << mFamilyName << std::endl;
      updateFace();
      updateScene();
   }

   void incLineSpacing(bool inc=true)
   {
      float increment(0.05f);
      if(!inc)
      { increment *= -1.0f; }

      mLineSpacing += increment;

      if(mLineSpacing < 0.0f)
      {  mLineSpacing = 0.0f; }

      std::cout << "Set line spacing to: " << mLineSpacing << std::endl;
      updateScene();
   }

   void incMaxExtent(bool inc=true)
   {
      float increment(0.5f);
      if(!inc)
      { increment *= -1.0f; }

      mMaxExtent += increment;

      if(mMaxExtent < 0.0f)
      { mMaxExtent = 0.0f; }

      std::cout << "Set max extent to: " << mMaxExtent << std::endl;
      updateScene();
   }

   void incGeoScale(bool inc=true)
   {
      float increment(0.05f);
      if(!inc)
      { increment *= -1.0f; }

      mGeoScale += increment;

      if(mGeoScale < 0.0f)
      { mGeoScale = 0.0f; }

      std::cout << "Set geo scale to: " << mGeoScale << std::endl;
      updateScene();
   }

   void incOffset(float xInc, float yInc)
   {
      mOffset[0] += xInc;
      mOffset[1] += yInc;
      std::cout << "Offset: " << mOffset << std::endl;
      updateScene();
   }


public:
   OSG::NodeRefPtr            mRootNode;        /**< Root node for text geom. */
   OSG::GeometryRefPtr        mTextGeom;        /**< Geom core for the text. */
   OSG::ChunkMaterialRefPtr   mTextMat;         /**< Material for the text geom. */
   OSG::TextureObjChunkRefPtr mTextureObjChunk; /**< Texture object chunk for the text material. */
   OSG::TextureEnvChunkRefPtr mTextureEnvChunk; /**< Texture environment chunk for the text material. */
   OSG::BlendChunkRefPtr      mBlendChunk;      /**< Blend chunk for the text material. */

   OSG::TextTXFFace*          mFace;
   std::string                mFamilyName;      /**< The name of the font family. */
   std::vector<std::string>   mFamilies;
   unsigned                   mNextFamily;      /**< Next text family to use. */
   OSG::TextFace::Style       mStyle;

   unsigned                   mTextGap;         /**< The gap between glyphs in pixels */
   unsigned                   mTextureWidth;    /**< The width of the texture in pixels */
   unsigned                   mFaceSize;        /**< The "size" param of the face. */

   float                      mLineSpacing;     /**< Spacing to use in the layout. */
   float                      mMaxExtent;       /**< Maximum extent to use. */

   float                      mGeoScale;        /**< Scale for geometry. */
   OSG::Vec2f                 mOffset;          /**< Offset of text when building. */
};

TextStuff  gTextStuff;

void printFontFamilies()
{
   std::vector<std::string> families;
   OSG::TextFaceFactory::the()->getFontFamilies(families);  // Get list of all families

   std::cout << "--- Font Families ---\n";
   for(unsigned i=0; i<families.size(); ++i)
   {
      std::cout << families[i] << std::endl;
   }
   std::cout << "---------------------\n";
}

int main(int argc, char* argv[])
{
    std::cerr << argv[0] << ". Press 'h' for keys" << std::endl;
    
    // Init OSG and glut.
    OSG::osgInit(argc,argv);
    int winid = setupGLUT(&argc, argv);
    OSG::GLUTWindowPtr gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    printFontFamilies();

    // load the scene
    OSG::NodePtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());

    // Setup text sample
    gTextStuff.initialize();
    gTextStuff.updateFace();
    gTextStuff.updateScene();
    scene->addChild(gTextStuff.mRootNode);

    mgr = new OSG::SimpleSceneManager;

    // Tell the manager about the window and scene
    mgr->setWindow(gwin );
    mgr->setRoot(scene);

   // Start it up
    mgr->showAll();
    glutMainLoop();

    return 0;
}

// ----- GLUT callback functions ---- //

// redraw the window
void display(void)
{
    mgr->idle();
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
    {   mgr->mouseButtonRelease(button, x, y); }
    else
    {   mgr->mouseButtonPress(button, x, y); }

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
   switch (k)
   {
   case 27:
      {
         OSG::osgExit();
         exit(0);
      }
      break;

   case '-':
      gTextStuff.incFaceSize(false);
      break;
   case '=':
      gTextStuff.incFaceSize(true);
      break;

   case '[':
      gTextStuff.incTextureSize(false);
      break;
   case ']':
      gTextStuff.incTextureSize(true);
      break;

   case '<':
      gTextStuff.incMaxExtent(false);
      break;
   case '>':
      gTextStuff.incMaxExtent(true);
      break;

   case ',':
      gTextStuff.incLineSpacing(false);
      break;
   case '.':
      gTextStuff.incLineSpacing(true);
      break;

   case '{':
      gTextStuff.incGeoScale(false);
      break;
   case '}':
      gTextStuff.incGeoScale(true);
      break;


   case 'f':
      gTextStuff.goToNextFamily();
      break;

   case 'd':
      OSG::SceneFileHandler::the()->write(mgr->getRoot(),"dump_scene.osb");
      std::cout << "Wrote out scene: dump_scene.osb" << std::endl;
      break;

   case 't':
      mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
      break;

   case 'l':
      mgr->setHeadlight(!mgr->getHeadlightState());
      std::cout << "Set headlight: " << mgr->getHeadlightState() << std::endl;
      break;
   case 'z':
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
      std::cerr << "PolygonMode: Point." << std::endl;
      break;
   case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
      std::cerr << "PolygonMode: Line." << std::endl;
      break;
   case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
      std::cerr << "PolygonMode: Fill." << std::endl;
      break;
      
   case 'h':
      std::cerr << "Keys:" << std::endl;
      std::cerr << "- =: change face size" << std::endl;
      std::cerr << "{ }: change geo scale" << std::endl;
      std::cerr << "[ ]: change texture size" << std::endl;
      std::cerr << "< >: change max extend for 1st line" << std::endl;
      std::cerr << ", .: change line spacing" << std::endl;
      std::cerr << "f  : next font family" << std::endl;
      std::cerr << "d  : dump scene" << std::endl;
   }
}

void keyboard_special(int k, int , int )
{
   const float offset_inc(0.025f);

   switch(k)
   {
   case GLUT_KEY_LEFT:
      gTextStuff.incOffset(-offset_inc,0);
      break;
   case GLUT_KEY_RIGHT:
      gTextStuff.incOffset(offset_inc,0);
      break;
   case GLUT_KEY_UP:
      gTextStuff.incOffset(0,offset_inc);
      break;
   case GLUT_KEY_DOWN:
      gTextStuff.incOffset(0,-offset_inc);
      break;
   }

}

void initgl(void)
{
   glClearColor(0.1, 0.0, 0.1, 0.0);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("IOV UI Test");

    initgl();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_special);

    return winid;
}
#else
int main(void)
{
    return 0;
}
#endif
