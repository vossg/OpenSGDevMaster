// OpenSG Tutorial Example: Shader
//
// This example shows how to use GLSL shaders.
// It creates a bouncing ball animation (completely calculated on the GPU).
// You need a graphics card supporting the GL_ARB_shading_language_100 extension
// to run this tutorial.

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSHLChunk.h>
//#include <OpenSG/OSGShadowMapViewport.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *_mgr = NULL;
NodePtr _scene = NullFC;
SHLChunkPtr _shl = NullFC;

// vertex shader program.
static std::string _vp_program =
"uniform float groundHeight;\n"
"uniform float bounceMin;\n"
"uniform float bounceHeight;\n"
"uniform float bounceSpeed;\n"
"uniform float time;\n"
"uniform float squeezeHeight;\n"
"\n"
"// output variables to the fragment program.\n"
"varying vec3 vNormal;\n"
"varying vec3 vViewVec;\n"
"\n"
"void main(void)\n"
"{\n"
"   // Normalize and scale, just because the source\n"
"   // model is not a perfect sphere around origin\n"
"   vec3 pos = 5.0 * normalize(vec3(gl_Vertex));\n"
"\n"
"   // Basic Bounce\n"
"   float t = fract( time * bounceSpeed )  ;\n"
"   float center = bounceHeight * t * (1.0 - t);\n"
"\n"
"   pos.y += center + bounceMin;\n"
"\n"
"   // Squeeze\n"
"   if (pos.y < groundHeight)\n"
"   {\n"
"      // Squeeze in Z direction\n"
"      float squeeze = (1.0 - exp2(1.0 * (pos.y - groundHeight)));\n"
"      pos.y = groundHeight - squeeze * squeezeHeight;\n"
"\n"
"      // Flatten in XZ direcion\n"
"      vec2 xyNorm = vec2(normalize(vec3(gl_Normal.xy,1.0)));\n"
"      pos.xz += squeeze * xyNorm * squeezeHeight;\n"
"\n"
"   }\n"
"\n"
"   gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);\n"
"\n"
"   // gl_NormalMatrix the inverse of the upper 3x3 of the view matrix.\n"
"   vNormal   =  gl_NormalMatrix  * gl_Normal;\n"
"\n"
"   vViewVec   = -vec3((gl_ModelViewMatrix * vec4(pos, 1.0)));\n"
"}\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"uniform vec3 ballColor;\n"
"const vec4 lightDir = vec4(0.43644,-0.43644,-0.87287,1.0);\n"
"\n"
"// input variables from the vertex program.\n"
"varying vec3 vNormal;\n"
"varying vec3 vViewVec;\n"
"\n"
"void main(void)\n"
"{\n"
"   vec3 nLightVec = normalize(vec3(lightDir.x, lightDir.y, -lightDir.z));\n"
"   // Simple diffuse and specular\n"
"   vec3 nNormal = normalize(vNormal);  // nNormal = normalized normal\n"
"\n"
"   float diffuse = clamp( (dot(vNormal, nLightVec)) ,0.0 ,1.0 );\n"
"   vec3  reflectVec = reflect(-normalize(vViewVec), nNormal);\n"
"\n"
"   float specular = pow(clamp( dot(reflectVec, vec3(nLightVec)) ,0.0 ,1.0 ),32.0);\n"
"\n"
"\n"
"   gl_FragColor = vec4(ballColor, 1.0) * diffuse + 0.8 * specular;\n"
"}\n";

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// redraw the window
void display(void)
{
    static Real32 t = glutGet(GLUT_ELAPSED_TIME);

    Real32 td = (glutGet(GLUT_ELAPSED_TIME) - t) / 100.0f;
    _shl->setUniformParameter("time", td);

    _mgr->redraw();
}


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // create the scene
    _scene = makeCoredNode<Group>();

    // create light
    TransformPtr point1_trans;
    PointLightPtr point1_core;
    NodePtr point1 = makeCoredNode<PointLight>(&point1_core);
    NodePtr point1_beacon = makeCoredNode<Transform>(&point1_trans);
    point1_trans->editMatrix().setTranslate(0.0, 100.0, 0.0);

    point1_core->setAmbient(0.15,0.15,0.15,1);
    point1_core->setDiffuse(0.8,0.8,0.8,1);
    point1_core->setSpecular(0.0,0.0,0.0,1);
    point1_core->setBeacon(point1_beacon);
    point1_core->setOn(true);

    // create bottom
    NodePtr bottom = makePlane(50.0, 50.0, 128, 128);
    
    UChar8 imgdata[] =
        {  255,0,0,  0,255,0,  0,0,255, 255,255,0 };
    ImagePtr bottom_img = Image::create();
    bottom_img->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata);

    TextureChunkPtr bottom_tex = TextureChunk::create();
    bottom_tex->setImage(bottom_img);
    bottom_tex->setMinFilter(GL_LINEAR);
    bottom_tex->setMagFilter(GL_LINEAR);
    bottom_tex->setWrapS(GL_REPEAT);
    bottom_tex->setWrapT(GL_REPEAT);
    bottom_tex->setEnvMode(GL_MODULATE);

    SimpleMaterialPtr bottom_mat = SimpleMaterial::create();
    bottom_mat->setAmbient(Color3f(0.3,0.3,0.3));
    bottom_mat->setDiffuse(Color3f(1.0,1.0,1.0));
    bottom_mat->addChunk(bottom_tex);
    
    GeometryPtr bottom_geo = cast_dynamic<GeometryPtr>(bottom->getCore());
    bottom_geo->setMaterial(bottom_mat);
    
    // rotate the bottom about 90 degree.
    TransformPtr bottom_trans_core;
    NodePtr bottom_trans = makeCoredNode<Transform>(&bottom_trans_core);
    Quaternion q;
    q.setValueAsAxisDeg(1, 0, 0, -90);
    bottom_trans_core->editMatrix().setRotate(q);
    bottom_trans->addChild(bottom);

    // create a sphere.
    NodePtr sphere = makeLatLongSphere(50, 50, 1.0);
    
    // create the shader material
    ChunkMaterialPtr cmat = ChunkMaterial::create();
    _shl = SHLChunk::create();
    _shl->setVertexProgram(_vp_program);
    _shl->setFragmentProgram(_fp_program);
    _shl->setUniformParameter("groundHeight", 1.0f);
    _shl->setUniformParameter("bounceMin", -0.1f);
    _shl->setUniformParameter("bounceHeight", 75.0f);
    _shl->setUniformParameter("bounceSpeed", 0.05f);
    _shl->setUniformParameter("time", 0.0f);
    _shl->setUniformParameter("squeezeHeight", 1.0f);
    _shl->setUniformParameter("ballColor", Vec3f(1.0f, 0.0f, 0.0f));

    cmat->addChunk(_shl);

    GeometryPtr spheregeo = cast_dynamic<GeometryPtr>(sphere->getCore());
    spheregeo->setMaterial(cmat);

    point1->addChild(bottom_trans);
    point1->addChild(sphere);

    _scene->addChild(point1_beacon);
    _scene->addChild(point1);

    // create ShadowViewport with a gradient background.
    //ShadowMapViewportPtr svp = ShadowMapViewport::create();
    GradientBackgroundPtr gbg = GradientBackground::create();

    gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
    gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);

    // Shadow viewport
    //svp->setBackground(gbg);
    //svp->setRoot(_scene);
    //svp->setSize(0,0,1,1);
    //svp->setOffFactor(10.0);
    //svp->setOffBias(4.0);
    //svp->setShadowColor(Color4f(0.1, 0.1, 0.1, 1.0));
    //svp->setMapSize(1024);
    // you can add the light sources here, as default all light source in
    // the scenegraph are used.
    //svp->getLightNodes().push_back(point1);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    //gwin->addPort(svp);
    gwin->init();

    commitChanges();

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot  (_scene);

    //svp->setCamera(_mgr->getCamera());

    _mgr->turnHeadlightOff();

    // show the whole scene
    _mgr->showAll();
    _mgr->getNavigator()->setFrom(Pnt3f(0.0, 31, 47));

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
            OSG::osgExit();
            exit(0);
        break;
        case 'w':
            SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.\n");
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
    glutIdleFunc(display);

    return winid;
}
