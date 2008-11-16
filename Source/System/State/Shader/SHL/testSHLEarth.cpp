// OpenSG example: testSHL
//
// Demonstrates the use of the SHLChunk
// Earth Shader Demo

// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGSimpleSHLChunk.h>
#include <OSGOSGSceneFileType.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static SimpleSceneManager *_mgr;
// The scene
static NodeRecPtr _scene;

static SimpleSHLChunkRecPtr _shl       = NULL;
static Int32                _animation = 1;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowUnrecPtr gwin= GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( 800, 800 );
    gwin->init();

    // Create the shader material
    ChunkMaterialUnrecPtr cmat = ChunkMaterial::create();

    // Read the image for the normal texture
    ImageUnrecPtr earth_map_img = Image::create();
    if(!earth_map_img->read("Earth.jpg"))
    {
        fprintf(stderr, "Couldn't read texture 'Earth.jpg'\n");
        return 1;
    }
    TextureObjChunkUnrecPtr tex_earth     = TextureObjChunk::create();
    TextureEnvChunkUnrecPtr tex_earth_env = TextureEnvChunk::create();

    tex_earth->setImage(earth_map_img);
    tex_earth->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_earth->setMagFilter(GL_LINEAR);
    tex_earth->setWrapS(GL_REPEAT);
    tex_earth->setWrapT(GL_REPEAT);

    tex_earth_env->setEnvMode(GL_MODULATE);

    // Read the image for the normal texture
    ImageUnrecPtr earth_night_map_img = Image::create();
    if(!earth_night_map_img->read("EarthNight.jpg"))
    {
        fprintf(stderr, "Couldn't read texture 'EarthNight.jpg'\n");
        return 1;
    }

    TextureObjChunkUnrecPtr tex_earth_night     = TextureObjChunk::create();
    TextureEnvChunkUnrecPtr tex_earth_night_env = TextureEnvChunk::create();

    tex_earth_night->setImage(earth_night_map_img);
    tex_earth_night->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_earth_night->setMagFilter(GL_LINEAR);
    tex_earth_night->setWrapS(GL_REPEAT);
    tex_earth_night->setWrapT(GL_REPEAT);

    tex_earth_night_env->setEnvMode(GL_MODULATE);
    
    // Read the image for the normal texture
    ImageUnrecPtr earth_clouds_map_img = Image::create();
    if(!earth_clouds_map_img->read("EarthClouds.jpg"))
    {
        fprintf(stderr, "Couldn't read texture 'EarthClouds.jpg'\n");
        return 1;
    }

    TextureObjChunkUnrecPtr tex_earth_clouds     = TextureObjChunk::create();
    TextureEnvChunkUnrecPtr tex_earth_clouds_env = TextureEnvChunk::create();

    tex_earth_clouds->setImage(earth_clouds_map_img);
    tex_earth_clouds->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_earth_clouds->setMagFilter(GL_LINEAR);
    tex_earth_clouds->setWrapS(GL_REPEAT);
    tex_earth_clouds->setWrapT(GL_REPEAT);

    tex_earth_clouds_env->setEnvMode(GL_MODULATE);


    _shl = SimpleSHLChunk::create();

    if(!_shl->readVertexProgram("Earth.vp"))
        fprintf(stderr, "Couldn't read vertex program 'Earth.vp'\n");
    if(!_shl->readFragmentProgram("Earth.fp"))
        fprintf(stderr, "Couldn't read fragment program 'Earth.fp'\n");

    _shl->addUniformVariable("EarthDay", 0);
    _shl->addUniformVariable("EarthNight", 1);
    _shl->addUniformVariable("EarthCloudGloss", 2);
    _shl->addUniformVariable("season", 0.0f);
    _shl->addUniformVariable("cos_time_0_2PI", -0.406652f);
    _shl->addUniformVariable("sin_time_0_2PI", -0.913583f);
//    _shl->setUniformParameter("foo", -0.913583f);

    
    cmat->addChunk(_shl);
    cmat->addChunk(tex_earth);
    cmat->addChunk(tex_earth_env);
    cmat->addChunk(tex_earth_night);
    cmat->addChunk(tex_earth_night_env);
    cmat->addChunk(tex_earth_clouds);
    cmat->addChunk(tex_earth_clouds_env);


    // create root node
    _scene = Node::create();

    GeometryUnrecPtr geo = makeLatLongSphereGeo (100, 100, 1.0);

    geo->setMaterial(cmat);


    NodeUnrecPtr torus = Node::create();
    
    torus->setCore(geo);


    // add torus to scene
    GroupUnrecPtr group = Group::create();

    _scene->setCore(group);
    _scene->addChild(torus);


    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

    return 0;
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    if(doMain(argc, argv) != 0)
        return 1;
    
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

        _shl->updateUniformVariable("cos_time_0_2PI", osgCos(t2));
        _shl->updateUniformVariable("sin_time_0_2PI", osgSin(t2));
    }

    Thread::getCurrentChangeList()->commitChanges();

    // render scene
    _mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    static Real32 season = 0.0f; 
    switch(k)
    {
        case 27:
        case 'q':
            delete _mgr;

            _scene = NULL; 
            _shl   = NULL;

            osgExit();
            exit(1);
        break;
        case 'w':
            SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;
        case 's':
            if(season < 0.435)
                season += 0.01;

            _shl->updateUniformVariable("season", season);

        break;
        case 'S':
            if(season > -0.435)
                season -= 0.01;

            _shl->updateUniformVariable("season", season);
        break;
        case 'd':
            _animation = 1 - _animation;
        break;

        case 'b':
            if(!_shl->readFragmentProgram("Earth.fp"))
                fprintf(stderr, "Couldn't read fragment program 'Earth.fp'\n");
            else
                fprintf(stderr, "blue loaded\n");
            break;
        case 'r':
            if(!_shl->readFragmentProgram("Earth_red.fp"))
                fprintf(stderr, "Couldn't read fragment program 'Earth.fp'\n");
            else
                fprintf(stderr, "red loaded\n");
            break;

        case 'A':
            _shl->subUniformVariable("season");
            //OSGSceneFileType::the().writeContainer(_shl, "/tmp/rem.osg");
            break;
        case 'a':
            _shl->addUniformVariable("season", season);
            //OSGSceneFileType::the().writeContainer(_shl, "/tmp/add.osg");
            break;
            
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG SHL Shader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutIdleFunc(display);

    return winid;
}


