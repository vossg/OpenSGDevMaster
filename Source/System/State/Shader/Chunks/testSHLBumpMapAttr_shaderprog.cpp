// OpenSG example: testSHL
//
// Demonstrates the use of the SHLChunk
// Implements a simple bumpmapping via vertex and fragment shader.

// Headers
#include "OSGGLUT.h"
#include "OSGConfig.h"

#include "OSGSimpleGeometry.h"
#include "OSGGLUT.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGBaseFunctions.h"

#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGPointLight.h"

#include "OSGImage.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGShaderProgramChunk.h"

// vertex shader program for bump mapping in surface local coordinates
static std::string _vp_program =
"varying vec3 lightDir;    // interpolated surface local coordinate light direction\n"
"varying vec3 viewDir;     // interpolated surface local coordinate view direction\n"
""
"attribute vec3 Normal;\n"
"attribute vec2 TexCoord0;\n"
"attribute vec3 Position;\n"
""
"void main(void)\n"
"{\n"
"    // Do standard vertex stuff\n"

"    gl_Position  = gl_ModelViewProjectionMatrix * vec4(Position, 1.0);\n"
"    gl_TexCoord[0] = vec4(TexCoord0, 0.0, 0.0);\n"

"    // Compute the binormal\n"

"    vec3 n = normalize(gl_NormalMatrix * Normal);\n"
"    //vec3 t = normalize(gl_NormalMatrix * vec3 (gl_Color));\n"
"    vec3 t = normalize(cross(vec3(1.141, 2.78, 3.14), n));\n"
"    vec3 b = cross(n, t);\n"

"    // Transform light position into surface local coordinates\n"

"    vec3 LightPosition = gl_LightSource[0].position.xyz;\n"

"    vec3 v;\n"
"    v.x = dot(LightPosition, t);\n"
"    v.y = dot(LightPosition, b);\n"
"    v.z = dot(LightPosition, n);\n"

"    lightDir = normalize(v);\n"

"    vec3 pos      = vec3 (gl_ModelViewMatrix * vec4(Position, 1.0));\n"

"    v.x = dot(pos, t);\n"
"    v.y = dot(pos, b);\n"
"    v.z = dot(pos, n);\n"

"    viewDir = normalize(v);\n"
"\n"
"}\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"uniform sampler2D sampler2d; // value of sampler2d = 3\n"
"varying vec3 lightDir;       // interpolated surface local coordinate light direction\n"
"varying vec3 viewDir;        // interpolated surface local coordinate view direction\n"

"const float diffuseFactor  = 0.7;\n"
"const float specularFactor = 0.7;\n"
"vec3 basecolor = vec3 (0.8, 0.7, 0.3);\n"

"void main (void)\n"
"{\n"
"    vec3 norm;\n"
"    vec3 r;\n"
"    vec3 color;\n"
"    float intensity;\n"
"    float spec;\n"
"    float d;\n"
"    // Fetch normal from normal map\n"
"    norm = vec3(texture2D(sampler2d, vec2 (gl_TexCoord[0])));\n"
"    norm = (norm - 0.5) * 2.0;\n"
"    norm.y = -norm.y;\n"
"    intensity = max(dot(lightDir, norm), 0.0) * diffuseFactor;\n"
"    // Compute specular reflection component\n"
"    d = 2.0 * dot(lightDir, norm);\n"
"    r = d * norm;\n"
"    r = lightDir - r;\n"
"    spec = pow(max(dot(r, viewDir), 0.0) , 6.0) * specularFactor;\n"
"    intensity += min (spec, 1.0);\n"
"     // Compute final color value\n"
"    color = clamp(basecolor * intensity, 0.0, 1.0);\n"
"    // Write out final fragment color\n"
"    gl_FragColor = vec4 (color, 1.0);\n"
"\n"
"}\n";



// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static OSG::SimpleSceneManager *_mgr;
// The scene
static OSG::NodeRecPtr _scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    printf("Usage: testCGShader [normal map filename]\n");
    const char *normal_map_img_name = "opensg_logoDOT3.png";

    OSG::Color4f tmp;

    if( argc > 1 )
        normal_map_img_name = argv[1];

    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( 800, 800 );
    gwin->init();

    // Create the shader material

    // Read the image for the normal texture
    OSG::ImageUnrecPtr normal_map_img = OSG::Image::create();
    if(!normal_map_img->read(normal_map_img_name))
    {
        fprintf(stderr, "Couldn't read normalmap texture '%s'!\n", normal_map_img_name);
        return 1;
    }

    OSG::ChunkMaterialUnrecPtr cmat = OSG::ChunkMaterial::create();

    OSG::MaterialChunkUnrecPtr matc = OSG::MaterialChunk::create();

    matc->setAmbient(OSG::Color4f(0.1, 0.1, 0.1, 1.0));
    matc->setDiffuse(OSG::Color4f(0.3, 0.3, 0.3, 1.0));
    matc->setSpecular(OSG::Color4f(0.8, 0.8, 0.8, 1.0));
    matc->setShininess(100);
    matc->setLit(true);

    OSG::ShaderProgramChunkUnrecPtr shl = OSG::ShaderProgramChunk::create();

    OSG::ShaderProgramUnrecPtr shl_vp = 
        OSG::ShaderProgram::createVertexShader();
    
    shl_vp->setProgram(_vp_program);
    shl_vp->setProgramAttribute(OSG::ShaderConstants::TexCoordsIndex, "TexCoord0");
    shl_vp->setProgramAttribute(OSG::ShaderConstants::NormalsIndex,   "Normal"  );
    shl_vp->setProgramAttribute(OSG::ShaderConstants::PositionsIndex, "Position");

    shl->addShader(shl_vp);

    OSG::ShaderProgramUnrecPtr shl_fp = 
        OSG::ShaderProgram::createFragmentShader();

    shl_fp->setProgram(_fp_program);

    shl->addShader(shl_fp);


    OSG::TextureObjChunkUnrecPtr tex_normal_map     = 
        OSG::TextureObjChunk::create();
    OSG::TextureEnvChunkUnrecPtr tex_normal_map_env = 
        OSG::TextureEnvChunk::create();

    tex_normal_map->setImage(normal_map_img);
    tex_normal_map->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    tex_normal_map->setMagFilter(GL_LINEAR);
    tex_normal_map->setWrapS(GL_REPEAT);
    tex_normal_map->setWrapT(GL_REPEAT);
    tex_normal_map_env->setEnvMode(GL_MODULATE);

        //cmat->addChunk(matc);
    cmat->addChunk(shl);
    cmat->addChunk(tex_normal_map);
    cmat->addChunk(tex_normal_map_env);


    // create root node
    _scene = OSG::Node::create();

    // create geometry
    //GeometryPtr geo = makeLatLongSphereGeo (100, 100, 1.0);
    OSG::GeometryUnrecPtr geo = OSG::makePlaneGeo(1.0, 1.0, 100, 100);

    geo->setMaterial(cmat);

    OSG::NodeUnrecPtr torus = OSG::Node::create();
    torus->setCore(geo);

    // add torus to scene
    OSG::GroupUnrecPtr group = OSG::Group::create();

    _scene->setCore(group);
    _scene->addChild(torus);

    // create the SimpleSceneManager helper
    _mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

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
void display(void)
{
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
    switch(k)
    {
        case 27:
        case 'q':
            delete _mgr;

            _scene = NULL;

            OSG::osgExit();
            exit(1);
        break;
        case 'w':
            OSG::SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG CG Shader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
