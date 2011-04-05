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
#include "OSGShaderProgramChunk.h"
#include "OSGGLFuncProtos.h"

// vertex shader program for bump mapping in surface local coordinates
static std::string _vp_program =
"uniform bool Light0Active;\n"
"uniform bool Light1Active;\n"
"uniform bool Light2Active;\n"
"vec4 Ambient;\n"
"vec4 Diffuse;\n"
"vec4 Specular;\n"
"\n"
"\n"
"    void pointLight(in int i, in vec3 normal, in vec3 eye, in vec3 ecPosition3)\n"
"    {\n"
"        float nDotVP;         // normal . light direction\n"
"        float nDotHV;         // normal . light half vector\n"
"        float pf;                   // power factor\n"
"        float attenuation;    // computed attenuation factor\n"
"        float d;                    // distance from surface to light source\n"
"        vec3  VP;               // direction from surface to light position\n"
"        vec3  halfVector;    // direction of maximum highlights\n"
"\n"
"        // Compute vector from surface to light position\n"
"        VP = vec3 (gl_LightSource[i].position) - ecPosition3;\n"
"\n"
"        // Compute distance between surface and light position\n"
"        d = length(VP);\n"
"\n"
"        // Normalize the vector from surface to light position\n"
"        VP = normalize(VP);\n"
"\n"
"        // Compute attenuation\n"
"        attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +\n"
"                      gl_LightSource[i].linearAttenuation * d +\n"
"                      gl_LightSource[i].quadraticAttenuation * d * d);\n"
"        halfVector = normalize(VP + eye);\n"
"        nDotVP = max(0.0, dot(normal, VP));\n"
"        nDotHV = max(0.0, dot(normal, halfVector));\n"
"\n"
"        if (nDotVP == 0.0)\n"
"            pf = 0.0;\n"
"        else\n"
"            pf = pow(nDotHV, gl_FrontMaterial.shininess);\n"
"\n"
"        Ambient  += gl_LightSource[i].ambient * attenuation;\n"
"        Diffuse  += gl_LightSource[i].diffuse * nDotVP * attenuation;\n"
"        Specular += gl_LightSource[i].specular * pf * attenuation;\n"
"    }\n"
"\n"
"    vec3 fnormal(void)\n"
"    {\n"
"        //Compute the normal\n"
"        vec3 normal = gl_NormalMatrix * gl_Normal;\n"
"        normal = normalize(normal);\n"
"        return normal;\n"
"    }\n"
"\n"
"    void flight(in vec3 normal, in vec4 ecPosition, float alphaFade)\n"
"    {\n"
"        vec4 color;\n"
"        vec3 ecPosition3;\n"
"        vec3 eye;\n"
"\n"
"        ecPosition3 = (vec3 (ecPosition)) / ecPosition.w;\n"
"        eye = vec3 (0.0, 0.0, 1.0);\n"
"\n"
"        // Clear the light intensity accumulators\n"
"        Ambient  = vec4 (0.0);\n"
"        Diffuse  = vec4 (0.0);\n"
"        Specular = vec4 (0.0);\n"
"\n"
"       if(Light0Active)\n"
"           pointLight(0, normal, eye, ecPosition3);\n"
"\n"
"       if(Light1Active)\n"
"           pointLight(1, normal, eye, ecPosition3);\n"
"\n"
"       if(Light2Active)\n"
"           pointLight(2, normal, eye, ecPosition3);\n"
"\n"
"        color = gl_FrontLightModelProduct.sceneColor +\n"
"                    Ambient  * gl_FrontMaterial.ambient +\n"
"                    Diffuse  * gl_FrontMaterial.diffuse;\n"
"        color += Specular * gl_FrontMaterial.specular;\n"
"        color = clamp( color, 0.0, 1.0 );\n"
"        gl_FrontColor = color;\n"
"        gl_FrontColor.a *= alphaFade;\n"
"\n"
"    }\n"
"\n"
"    void main(void)\n"
"    {\n"
"        vec3  transformedNormal;\n"
"        float alphaFade = 1.0;\n"
"\n"
"        // Eye-coordinate position of vertex, needed in various calculations\n"
"        vec4 ecPosition = gl_ModelViewMatrix * gl_Vertex;\n"
"\n"
"        // Do fixed functionality vertex transform\n"
"        gl_Position = ftransform();\n"
"        transformedNormal = fnormal();\n"
"        flight(transformedNormal, ecPosition, alphaFade);\n"
"    }\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"void main (void)\n"
"{\n"
"    vec4 color;\n"
"    color = gl_Color;\n"
"    gl_FragColor = color;\n"
"}\n";


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static OSG::SimpleSceneManager *_mgr;
// The scene
static OSG::NodeRecPtr       _scene;
static OSG::PointLightRecPtr _point1_core;
static OSG::PointLightRecPtr _point2_core;
static OSG::PointLightRecPtr _point3_core;

OSG::NodeUnrecPtr point1_beacon;
OSG::NodeUnrecPtr point2_beacon;
OSG::NodeUnrecPtr point3_beacon;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Shows how to add your own parameter callbacks.

static void light0Active(OSG::DrawEnv *pEnv, OSG::Int32 &iLoc)
{
    if(iLoc != -1)
    {
        OSGGETGLFUNC(OSG::OSGglUniform1iProc,
                     osgGlUniform1i,
                     OSG::ShaderProgram::getFuncIdUniform1i());

        osgGlUniform1i(iLoc, 
                       GLint(pEnv->getLightState() & 0x0001));
    }
}

static void light1Active(OSG::DrawEnv *pEnv, OSG::Int32 &iLoc)
{
    if(iLoc != -1)
    {
        OSGGETGLFUNC(OSG::OSGglUniform1iProc,
                     osgGlUniform1i,
                     OSG::ShaderProgram::getFuncIdUniform1i());

        osgGlUniform1i(iLoc, 
                       GLint(pEnv->getLightState() & 0x0002));
    }
}

static void light2Active(OSG::DrawEnv *pEnv, OSG::Int32 &iLoc, OSG::Node *pNode)
{
    if(iLoc != -1)
    {
        OSGGETGLFUNC(OSG::OSGglUniform1iProc,
                     osgGlUniform1i,
                     OSG::ShaderProgram::getFuncIdUniform1i());

        osgGlUniform1i(iLoc, 
                       GLint(pEnv->getLightState() & 0x0004));
    }
}

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    printf("Press key '1', '2', or '3' to toggle the light sources.\n");
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

    OSG::ChunkMaterialUnrecPtr cmat = OSG::ChunkMaterial::create();

    OSG::MaterialChunkUnrecPtr matc = OSG::MaterialChunk::create();

    matc->setAmbient(OSG::Color4f(0.1f, 0.1f, 0.1f, 1.0f));
    matc->setDiffuse(OSG::Color4f(0.3f, 0.3f, 0.3f, 1.0f));
    matc->setSpecular(OSG::Color4f(0.8f, 0.8f, 0.8f, 1.0f));
    matc->setShininess(100);
    matc->setLit(true);

    OSG::ShaderProgramChunkUnrecPtr shl = OSG::ShaderProgramChunk::create();

    OSG::ShaderProgramUnrecPtr shl_vp = 
        OSG::ShaderProgram::createVertexShader();

    shl_vp->setProgram(_vp_program);

    shl->addShader(shl_vp);

    OSG::ShaderProgramUnrecPtr shl_fp = 
        OSG::ShaderProgram::createFragmentShader();

    shl_fp->setProgram(_fp_program);

    shl->addShader(shl_fp);

    shl_vp->addProceduralVariable    ("Light0Active", &light0Active);
    shl_vp->addProceduralVariable    ("Light1Active", &light1Active);
    shl_vp->addNodeProceduralVariable("Light2Active", &light2Active);

    cmat->addChunk(matc);
    cmat->addChunk(shl);

    // create root node
    _scene = OSG::Node::create();

    // create two light sources.

    OSG::TransformUnrecPtr point1_trans;

    OSG::NodeUnrecPtr point1        = 
        OSG::makeCoredNode<OSG::PointLight>(&_point1_core);
    point1_beacon = OSG::makeCoredNode<OSG::Transform >(&point1_trans);

    point1_trans->editMatrix().setTranslate(-10.0, 5.0, 5.0);

    _point1_core->setAmbient(0.0f, 0.0f, 0.0f , 1.0f);
    _point1_core->setDiffuse(1.0f, 0.0f, 0.0f, 1.0f);
    _point1_core->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    _point1_core->setBeacon(point1_beacon);
    _point1_core->setOn(true);


    OSG::TransformUnrecPtr point2_trans;

    OSG::NodeUnrecPtr point2        =
        OSG::makeCoredNode<OSG::PointLight>(&_point2_core);
    point2_beacon = OSG::makeCoredNode<OSG::Transform >(&point2_trans);

    point2_trans->editMatrix().setTranslate(10.0, 5.0, 5.0);

    _point2_core->setAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    _point2_core->setDiffuse(0.0f, 1.0f, 0.0f, 1.0f);
    _point2_core->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    _point2_core->setBeacon(point2_beacon);
    _point2_core->setOn(true);

    point1->addChild(point2);
    
    OSG::TransformUnrecPtr point3_trans;

    OSG::NodeUnrecPtr point3        = 
        OSG::makeCoredNode<OSG::PointLight>(&_point3_core);
    
    point3_beacon = OSG::makeCoredNode<OSG::Transform >(&point3_trans);

    point3_trans->editMatrix().setTranslate(0.0, -12.0, 5.0);

    _point3_core->setAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    _point3_core->setDiffuse(0.5f, 0.0f, 1.0f, 1.0f);
    _point3_core->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    _point3_core->setBeacon(point3_beacon);
    _point3_core->setOn(true);

    point2->addChild(point3);


    // create a sphere.
    OSG::GeometryUnrecPtr geo = OSG::makeLatLongSphereGeo (100, 100, 1.0);

    geo->setMaterial(cmat);


    OSG::NodeUnrecPtr sphere = OSG::makeNodeFor(geo);

    point3->addChild(sphere);


    _scene->setCore(OSG::Group::create());
    _scene->addChild(point1);

    // create the SimpleSceneManager helper
    _mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    _mgr->turnHeadlightOff();

    // show the whole scene
    _mgr->showAll();

    // enable local lights.
//    OSG::RenderAction *ract = 
//        dynamic_cast<OSG::RenderAction *>(_mgr->getRenderAction());

//    ract->setLocalLights(true);

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
            _scene       = NULL;
            _point1_core = NULL;
            _point2_core = NULL;
            _point3_core = NULL;

            point1_beacon = NULL;
            point2_beacon = NULL;
            point3_beacon = NULL;

            delete _mgr;

            OSG::osgExit();

            exit(1);
        break;
        case 'w':
            OSG::SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;
        case '1':
        {
            if(_point1_core->getOn() == false)
                _point1_core->setOn(true);
            else
                _point1_core->setOn(false);
            break;
        }

        case '2':
        {
            if(_point2_core->getOn() == false)
                _point2_core->setOn(true);
            else
                _point2_core->setOn(false);
            break;
        }

        case '3':
        {
            if(_point3_core->getOn() == false)
                _point3_core->setOn(true);
            else
                _point3_core->setOn(false);
            break;
        }
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


