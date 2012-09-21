/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: Alexander Lang                                                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include "OSGConfig.h"
#include "OSGChunkMaterial.h"
#include "OSGChunkOverrideGroup.h"
#include "OSGDepthPeelingStage.h"
#include "OSGGLUT.h"
#include "OSGGLUTWindow.h"
#include "OSGShaderProgram.h"
#include "OSGShaderProgramChunk.h"
#include "OSGShaderProgramVariableChunk.h"
#include "OSGSimpleGeometry.h"
#include "OSGSimpleSceneManager.h"
#include "OSGTransform.h"

namespace
{
    const OSG::UInt32 NUM_PASSES    = 4;
    const OSG::Int32 DEPTH_TEX_UNIT = 3;
    const OSG::UInt32 NUM_BOXES     = 3;
    const OSG::Real32 WIDTH         = 0.5f;
    const OSG::Real32 HEIGHT        = 3.f;
    const OSG::Real32 DIST          = 1.f;
    const OSG::Real32 BORDER        = 0.1f;

    const OSG::Color4f COLOR1(0.f, 1.f, 1.f, 0.4f);
    const OSG::Color4f COLOR2(1.f, 1.f, 0.f, 0.5f);
    const OSG::Color4f COLOR3(1.f, 1.f, 1.f, 0.3f);

} // namespace

OSG::SimpleSceneManagerRefPtr  mgr;
OSG::GLUTWindowRecPtr          gwin;

void initialize(int argc, char* argv[]);
void shutdown  (void                  );

std::string                       getVertexShaderCode  (void);
std::string                       getFragmentShaderCode(void);
OSG::ShaderProgramChunkTransitPtr createShader         (void);

int  setupGLUT   (int* argc, char* argv[]);

// GLUT callbacks
void resize           (int w,      int h                  );
void display          (void                               );
void mousePressRelease(int button, int state, int x, int y);
void mouseMove        (int x,      int y                  );
void keyboardPress    (unsigned char k,       int x, int y);


int main(int argc, char* argv[])
{
    initialize(argc, argv);

    glutMainLoop();

    shutdown();

    return 0;
}


void initialize(int argc, char* argv[])
{
    OSG::osgInit(argc, argv);

    // create window
    int winId = setupGLUT(&argc, argv);
    gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winId);
    gwin->init     ();

    // create scene manager
    mgr = OSG::SimpleSceneManager::create();
    mgr->setWindow(gwin);

    // create root
    OSG::DepthPeelingStageUnrecPtr dp;
    OSG::NodeUnrecPtr              root =
        OSG::makeCoredNode<OSG::DepthPeelingStage>(&dp);
    dp->setNumPasses   (NUM_PASSES);
    dp->setDepthTexUnit(DEPTH_TEX_UNIT);

    // create material
    OSG::ChunkMaterialRecPtr      material = OSG::ChunkMaterial::create();
    OSG::ShaderProgramChunkRecPtr shader   = createShader();
    if (!shader)
        return;
    else
        material->addChunk(shader);

    // create scene
    OSG::ChunkOverrideGroupRecPtr         cog1 = OSG::ChunkOverrideGroup::create();
    OSG::ShaderProgramVariableChunkRecPtr spv1 = OSG::ShaderProgramVariableChunk::create();
    spv1->addUniformVariable("uObjColor", COLOR1);
    cog1->addChunk(spv1);
    OSG::NodeRecPtr cog1N = OSG::makeNodeFor(cog1);

    OSG::ChunkOverrideGroupRecPtr         cog2 = OSG::ChunkOverrideGroup::create();
    OSG::ShaderProgramVariableChunkRecPtr spv2 = OSG::ShaderProgramVariableChunk::create();
    spv2->addUniformVariable("uObjColor", COLOR2);
    cog2->addChunk(spv2); 
    OSG::NodeRecPtr cog2N = OSG::makeNodeFor(cog2);

    OSG::ChunkOverrideGroupRecPtr cog3 = OSG::ChunkOverrideGroup::create();
    OSG::ShaderProgramVariableChunkRecPtr spv3 = OSG::ShaderProgramVariableChunk::create();
    spv3->addUniformVariable("uObjColor", COLOR3);
    cog3->addChunk(spv3);
    OSG::NodeRecPtr cog3N = OSG::makeNodeFor(cog3);

    OSG::Real32         groundWidth = (NUM_BOXES-1) * DIST + WIDTH + 2 * BORDER;
    OSG::GeometryRecPtr groundGeo   = OSG::makePlaneGeo(groundWidth, groundWidth, 4, 4);
    groundGeo->setMaterial(material);
    OSG::NodeRecPtr groundGeoN = OSG::makeNodeFor(groundGeo);

    OSG::TransformRecPtr groundTransform = OSG::Transform::create();
    OSG::NodeRecPtr      groundNode      = OSG::makeNodeFor(groundTransform);
    OSG::Matrix     groundMatrix;
    OSG::Quaternion groundOrientation(OSG::Vec3f(1,0,0), (-90.f/180)*OSG::Pi);
    groundMatrix.setRotate(groundOrientation);

    groundTransform->setMatrix(groundMatrix);
    cog1N->addChild(groundGeoN);
    groundNode->addChild(cog1N);

    root->addChild(groundNode);
    root->addChild(cog2N);
    root->addChild(cog3N);

    for(OSG::UInt32 i = 0; i < NUM_BOXES; ++i)
    {
        OSG::TransformRecPtr transform  = OSG::Transform::create();
        OSG::NodeRecPtr      transformN = makeNodeFor(transform);

        OSG::Matrix m;
        m.setTranslate(OSG::Vec3f(DIST*i - 0.5f*(NUM_BOXES-1), 0.f, 0.f));

        transform->setMatrix(m);

        cog2N->addChild(transformN);

        OSG::GeometryRecPtr boxGeo = OSG::makeBoxGeo(WIDTH, HEIGHT, WIDTH, 1, 1, 1);
        boxGeo->setMaterial(material);
        OSG::NodeRecPtr boxN = OSG::makeNodeFor(boxGeo);
        transformN->addChild(boxN);
    }

    OSG::GeometryRecPtr hullGeo = OSG::makeBoxGeo(groundWidth, HEIGHT+2*BORDER, groundWidth, 1, 1, 1);
    OSG::NodeRecPtr     hullN   = OSG::makeNodeFor(hullGeo);
    hullGeo->setMaterial(material);
    cog3N->addChild(hullN);

    mgr->setRoot(root);

    OSG::commitChanges();
    mgr->showAll();
}

void shutdown(void)
{
    gwin = NULL;
    mgr  = NULL;

    OSG::osgExit();
}

std::string
getVertexShaderCode(void)
{
    return std::string(
        "#version 330 compatibility\n"
        "\n"
        "uniform mat4 OSGWorldMatrix;\n"
        "uniform mat4 OSGViewMatrix;\n"
        "in vec3 vertexPos;\n"
        "in vec3 vertexNormal;\n"
        "in vec2 vertexTexCoords;\n"
        "out float vIntensity;\n"
        "const vec3 LIGHTPOS = vec3(0.0, 10.0, 0.0);\n"
        "\n"
        "void main()\n"
        "{\n"
        "    vec4 lightPos4 = OSGViewMatrix * vec4(LIGHTPOS, 1.0);\n"
        "    vec4 pos4      = OSGViewMatrix * OSGWorldMatrix * vec4(vertexPos, 1.0);\n"
        "    vec3 ecLight  = normalize((lightPos4 - pos4).xyz);\n"
        "    vec3 ecNormal = normalize((OSGViewMatrix * OSGWorldMatrix * vec4(vertexNormal, 0.0)).xyz);\n"
        "    vIntensity    = abs(dot(ecLight, ecNormal));\n"
        "    gl_Position = gl_ProjectionMatrix * pos4;\n"
        "}\n");
}

std::string
getFragmentShaderCode(void)
{
    return std::string(
        "#version 330 compatibility\n"
        "\n"
        "uniform bool uIsPeelPass;\n"
        "uniform sampler2D uSamplerDepth;\n"
        "uniform vec4 uObjColor;\n"
        "in float vIntensity;\n"
        "const float SHADING_FACTOR = 0.3;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    //Reduce intensity of shading effect\n"
        "    vec3 shaded = uObjColor.rgb - SHADING_FACTOR + vIntensity * SHADING_FACTOR;\n"
        "    vec4 color = vec4(shaded, uObjColor.a);\n"
        "\n"
        "    //Compare depth from depth texture\n"
        "    if (uIsPeelPass)\n"
        "    {\n"
        "        vec4 depth = texelFetch(uSamplerDepth, ivec2(gl_FragCoord.xy),0);\n"
        "        if (gl_FragCoord.z <= depth.r)\n"
        "                discard;\n"
        "        gl_FragColor = vec4(color.xyz * color.a, color.a);\n"
        "    }\n"
        "    else\n"
        "    {\n"
        "        gl_FragColor  = vec4(color.xyz * color.a, 1.0 - color.a);\n"
        "    }\n"
        "}\n");
}

OSG::ShaderProgramChunkTransitPtr
createShader(void)
{
    OSG::ShaderProgramChunkRecPtr program = OSG::ShaderProgramChunk::create();

    OSG::ShaderProgramRecPtr vert = OSG::ShaderProgram::createVertexShader();
    vert->setProgramAttribute(OSG::ShaderConstants::PositionsIndex, "vertexPos");
    vert->setProgramAttribute(OSG::ShaderConstants::NormalsIndex,   "vertexNormal");
    vert->setProgramAttribute(OSG::ShaderConstants::TexCoordsIndex, "vertexTexCoord");
    vert->setProgram(getVertexShaderCode());

    OSG::ShaderProgramRecPtr frag = OSG::ShaderProgram::createFragmentShader();
    frag->setProgram(getFragmentShaderCode());

    program->addVertexShader  (vert);
    program->addFragmentShader(frag);

    vert->addOSGVariable("OSGWorldMatrix");
    vert->addOSGVariable("OSGViewMatrix");

    frag->addUniformVariable("uIsPeelPass",   false);
    frag->addUniformVariable("uSamplerDepth", DEPTH_TEX_UNIT);
    frag->addUniformVariable("uObjColor",     OSG::Color4f());

    return OSG::ShaderProgramChunkTransitPtr(program);
}

int setupGLUT(int* argc, char* argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winId = glutCreateWindow("OpenSG: DepthPeelingStage Demo");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mousePressRelease);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboardPress);

    return winId;
}

// GLUT callbacks

void resize(int w, int h)
{
    mgr->resize(w, h);

    glutPostRedisplay();
}

void display(void)
{
    mgr->idle  ();
    mgr->redraw();

    OSG::Thread::getCurrentChangeList()->clear();
}

void mousePressRelease(int button, int state, int x, int y)
{
    if(state)
    {
        mgr->mouseButtonRelease(button, x, y);
    }
    else
    {
        mgr->mouseButtonPress(button, x, y);
    }

    glutPostRedisplay();
}

void mouseMove(int x, int y)
{
    mgr->mouseMove(x, y);

    glutPostRedisplay();
}

void keyboardPress(unsigned char k, int, int)
{
    switch(k)
    {
        case 27:
        case 'q':
        {
            shutdown();
            exit(0);
        }
        break;
    }

    glutPostRedisplay();
}
