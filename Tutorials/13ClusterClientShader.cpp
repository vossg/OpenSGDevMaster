// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG cluster client program
// 
// To test it, run 
//   ./12ClusterServer -geometry 300x300+200+100 -m -w test1 &
//   ./12ClusterServer -geometry 300x300+500+100 -m -w test2 &
//   ./13ClusterClient -m -fData/tie.wrl test1 test2
//
// If you have trouble with multicasting, you can alternatively try
//   ./12ClusterServer -geometry 300x300+200+100 -w 127.0.0.1:30000 &
//   ./12ClusterServer -geometry 300x300+500+100 -w 127.0.0.1:30001 &
//   ./13ClusterClient -m -fData/tie.wrl 127.0.0.1:30000 127.0.0.1:30001
// 
// The client will open an emoty window that you can use to navigate. The
// display is shown in the server windows.
//
// This will run all three on the same machine, but you can also start the 
// servers anywhere else, as long as you can reach them via multicast.
//
// Note: This will run two VERY active OpenGL programs on one screen. Not all
// OpenGL drivers are happy with that, so if it crashes your X, it's not our
// fault! ;)
//
// Libs: Cluster

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGMultiDisplayWindow.h>

// Scene file handler for loading geometry files
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGSHLChunk.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

using namespace std;
// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

static SHLChunkPtr _shl = NullFC;
static Int32 _animation = 1;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


NodePtr createScene(void)
{
    NodePtr _scene;

    // Create the shader material
    ChunkMaterialPtr cmat = ChunkMaterial::create();

    // Read the image for the normal texture
    ImagePtr earth_map_img = Image::create();
    if(!earth_map_img->read("Earth.jpg"))
    {
        fprintf(stderr, "Couldn't read texture 'Earth.jpg'\n");
        return NullFC;
    }
    TextureObjChunkPtr tex_earth     = TextureObjChunk::create();
    TextureEnvChunkPtr tex_earth_env = TextureEnvChunk::create();

    tex_earth->setImage(earth_map_img);
    tex_earth->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_earth->setMagFilter(GL_LINEAR);
    tex_earth->setWrapS(GL_REPEAT);
    tex_earth->setWrapT(GL_REPEAT);

    tex_earth_env->setEnvMode(GL_MODULATE);

    // Read the image for the normal texture
    ImagePtr earth_night_map_img = Image::create();
    if(!earth_night_map_img->read("EarthNight.jpg"))
    {
        fprintf(stderr, "Couldn't read texture 'EarthNight.jpg'\n");
        return NullFC;
    }

    TextureObjChunkPtr tex_earth_night     = TextureObjChunk::create();
    TextureEnvChunkPtr tex_earth_night_env = TextureEnvChunk::create();

    tex_earth_night->setImage(earth_night_map_img);
    tex_earth_night->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_earth_night->setMagFilter(GL_LINEAR);
    tex_earth_night->setWrapS(GL_REPEAT);
    tex_earth_night->setWrapT(GL_REPEAT);

    tex_earth_night_env->setEnvMode(GL_MODULATE);
    
    // Read the image for the normal texture
    ImagePtr earth_clouds_map_img = Image::create();
    if(!earth_clouds_map_img->read("EarthClouds.jpg"))
    {
        fprintf(stderr, "Couldn't read texture 'EarthClouds.jpg'\n");
        return NullFC;
    }

    TextureObjChunkPtr tex_earth_clouds     = TextureObjChunk::create();
    TextureEnvChunkPtr tex_earth_clouds_env = TextureEnvChunk::create();

    tex_earth_clouds->setImage(earth_clouds_map_img);
    tex_earth_clouds->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_earth_clouds->setMagFilter(GL_LINEAR);
    tex_earth_clouds->setWrapS(GL_REPEAT);
    tex_earth_clouds->setWrapT(GL_REPEAT);

    tex_earth_clouds_env->setEnvMode(GL_MODULATE);


    _shl = SHLChunk::create();

    if(!_shl->readVertexProgram("Earth.vp"))
        fprintf(stderr, "Couldn't read vertex program 'Earth.vp'\n");
    if(!_shl->readFragmentProgram("Earth.fp"))
        fprintf(stderr, "Couldn't read fragment program 'Earth.fp'\n");

    _shl->setUniformParameter("EarthDay", 0);
    _shl->setUniformParameter("EarthNight", 1);
    _shl->setUniformParameter("EarthCloudGloss", 2);
    _shl->setUniformParameter("season", 0.0f);
    _shl->setUniformParameter("cos_time_0_2PI", -0.406652f);
    _shl->setUniformParameter("sin_time_0_2PI", -0.913583f);
    _shl->setUniformParameter("foo", -0.913583f);

    
    cmat->addChunk(_shl);
    cmat->addChunk(tex_earth);
    cmat->addChunk(tex_earth_env);
    cmat->addChunk(tex_earth_night);
    cmat->addChunk(tex_earth_night_env);
    cmat->addChunk(tex_earth_clouds);
    cmat->addChunk(tex_earth_clouds_env);


    // create root node
    _scene = Node::create();

    GeometryPtr geo = makeLatLongSphereGeo (100, 100, 1.0);

    geo->setMaterial(cmat);


    NodePtr torus = Node::create();
    
    torus->setCore(geo);


    // add torus to scene
    GroupPtr group = Group::create();

    _scene->setCore(group);
    _scene->addChild(torus);

    return _scene;
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    char     *opt;
    NodePtr   scene=NullFC;

    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between this client and the servers
    MultiDisplayWindowPtr mwin= MultiDisplayWindow::create();

    // evaluate params
    for(int a=1 ; a<argc ; ++a)
    {
        if(argv[a][0] == '-')
        {
            switch(argv[a][1])
            {
                case 'm': mwin->setConnectionType("Multicast");
cout << "Connection type set to Multicast" << endl;
                          break;
                case 'p': mwin->setConnectionType("SockPipeline");
cout << "Connection type set to SockPipeline" << endl;
                          break;
                case 'i': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              mwin->setConnectionInterface(opt);
                          break;
                case 'a': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              mwin->setServiceAddress(opt);
                          break;
                case 'f': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              scene = SceneFileHandler::the()->read(
                                  opt,0);
                          break;
                case 'x': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              mwin->setHServers(atoi(opt));
                          break;
                case 'y': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              mwin->setVServers(atoi(opt));
                          break;
                default:  std::cout << argv[0]  
                                    << " -m"
                                    << " -p"
                                    << " -i interface"
                                    << " -f file"
                                    << " -x horizontal server cnt"
                                    << " -y vertical server cnt"
                                    << endLog;
                          return 0;
            }
        }
        else
        {
            printf("%s\n",argv[a]);
            mwin->editServers().push_back(argv[a]);
        }
    }

    // dummy size for navigator
    mwin->setSize(300,300);

    // create default scene
    if(scene == NullFC)
        scene = createScene();

    if(scene == NullFC)
        scene = makeTorus(.5, 2, 16, 16);

    commitChanges();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(mwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
    // initialize window
    mwin->init();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    static Real32 speed = 10000.0f;
    static Real32 t = glutGet(GLUT_ELAPSED_TIME);
    static Real32 t2 = 0.0;
    
    Real32 td = glutGet(GLUT_ELAPSED_TIME) - t;

    if(td > speed)
        t = glutGet(GLUT_ELAPSED_TIME);

    if(_animation)
    {
        t2 = (2 * OSG::Pi / speed) * td;

        _shl->setUniformParameter("cos_time_0_2PI", osgCos(t2));
        _shl->setUniformParameter("sin_time_0_2PI", osgSin(t2));
    }

    Thread::getCurrentChangeList()->commitChanges();

    // redraw the cluster window
    mgr->redraw();
    // clear change list. If you don't clear the changelist,
    // then the same changes will be transmitted a second time
    // in the next frame. 
    OSG::Thread::getCurrentChangeList()->clear();
    // clear local navigation window
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
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
    static Real32 season = 0.0f; 

    switch(k)
    {
        case 27:    
        {
            OSG::osgExit();
            exit(0);
        }
        break;
        case 's':
            if(season < 0.435)
                season += 0.01;

            _shl->setUniformParameter("season", season);

        break;
        case 'S':
            if(season > -0.435)
                season -= 0.01;

            _shl->setUniformParameter("season", season);
        break;
        case 'a':
            _animation = 1 - _animation;
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

    glutIdleFunc(display);

    return winid;
}
