#include "OSGConfig.h"
#include "OSGGLUT.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGComponentTransform.h"
#include "OSGGroup.h"

#include "OSGSkeleton.h"
#include "OSGSkeletonJoint.h"
#include "OSGSkinnedGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGShaderProgram.h"
#include "OSGShaderProgramChunk.h"

#if 0
#include "OSGAnimation.h"
#include "OSGAnimBindAction.h"
#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimVec3fChannel.h"
#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimQuaternionDataSource.h"
#include "OSGAnimTargetAttachment.h"
#include "OSGTimeSensor.h"
#endif

OSG_USING_NAMESPACE

typedef std::vector<SkeletonJoint *> JointStore;

namespace {

    SimpleSceneManager *mgr    = NULL;
    NodeUnrecPtr        sceneN = NULL;
    SkeletonUnrecPtr    skel   = NULL;

    const std::string vpCode(
        "#version 120"
        "\n"
        "// forward decl\n"
        "void calcSkin(inout vec4 pos,    inout vec3 norm,\n"
        "              in    vec4 matIdx, in    vec4 weight);\n"
        "\n"
        "varying vec4 position;\n"
        "varying vec3 normal;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    vec4 pos    = gl_Vertex;\n"
        "    vec3 norm   = gl_Normal;\n"
        "    vec4 matIdx = gl_MultiTexCoord0;\n"
        "    vec4 weight = gl_MultiTexCoord1;\n"
        "\n"
        "    calcSkin(pos, norm, matIdx, weight);\n"
        "\n"
        "    gl_Position = gl_ModelViewProjectionMatrix * pos;\n"
        "    position    = gl_Position;\n"
        "    normal      = norm;\n"
        "}\n"
        );

    const std::string fpCode(
        "#version 120"
        "\n"
        "varying vec4 position;\n"
        "varying vec3 normal;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    vec3 pos = position.xyz / position.w;\n"
        "    //pos *= 0.25;\n"
        "    //pos += vec3(0.25, 0.25, 0.25);\n"
        "    gl_FragColor = vec4(pos.y, pos.y, pos.y, 1.);\n"
        "}\n"
        );

    UInt32     actJoint;
    JointStore jointStore;
}


int setupGLUT(int *argc, char *argv[]);

void init   (int argc, char *argv[]);
void cleanup(void                  );

void buildScene(void);


int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    init(argc, argv);

    glutMainLoop();

    cleanup();

    return 0;
}


void init(int argc, char *argv[])
{
    int winId = setupGLUT(&argc, argv);

    GLUTWindowUnrecPtr gwin = GLUTWindow::create();
    gwin->setGlutId(winId);
    gwin->init     (     );

    buildScene();

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin  );
    mgr->setRoot  (sceneN);

    mgr->showAll();
}


void cleanup(void)
{
    delete mgr;
    mgr    = NULL;

    sceneN = NULL;
}

void buildScene(void)
{
    // construct joints hierarchy
    SkeletonJointUnrecPtr jointC0  = SkeletonJoint::create();
    NodeUnrecPtr          jointC0N = makeNodeFor(jointC0);
    SkeletonJointUnrecPtr jointC1  = SkeletonJoint::create();
    NodeUnrecPtr          jointC1N = makeNodeFor(jointC1);

    SkeletonJointUnrecPtr jointR0  = SkeletonJoint::create();
    NodeUnrecPtr          jointR0N = makeNodeFor(jointR0);
    SkeletonJointUnrecPtr jointR1  = SkeletonJoint::create();
    NodeUnrecPtr          jointR1N = makeNodeFor(jointR1);

    SkeletonJointUnrecPtr jointL0  = SkeletonJoint::create();
    NodeUnrecPtr          jointL0N = makeNodeFor(jointL0);
    SkeletonJointUnrecPtr jointL1  = SkeletonJoint::create();
    NodeUnrecPtr          jointL1N = makeNodeFor(jointL1);

    jointC0->setJointId(0);
    jointC1->setJointId(3);

    jointR0->setJointId(1);
    jointR1->setJointId(4);

    jointL0->setJointId(2);
    jointL1->setJointId(5);

    jointC0N->addChild(jointC1N);
    jointC0N->addChild(jointR0N);
    jointC0N->addChild(jointL0N);

    jointC1N->addChild(jointR1N);
    jointC1N->addChild(jointL1N);

    jointStore.push_back(jointC0); // 0
    jointStore.push_back(jointR0); // 1
    jointStore.push_back(jointL0); // 2
    jointStore.push_back(jointC1); // 3
    jointStore.push_back(jointR1); // 4
    jointStore.push_back(jointL1); // 5

    Matrix matBind;
    Matrix matJoint;
    
    matBind .setTranslate(Vec3f(0.f, 0.f, -1.f));
    matBind .invert();
    matJoint.setTranslate(Vec3f(0.f, 1.f, -1.f));

    jointC1->setInvBindMatrix(matBind );
    jointC1->setMatrix       (matJoint);

    matBind .setIdentity();
    matBind .setTranslate(Vec3f(1.f, 0.f, 1.f));
    matBind .invert();
    matJoint.setIdentity();
    matJoint.setTranslate(Vec3f(1.f, 0.f, 1.f));

    jointR0->setInvBindMatrix(matBind );
    jointR0->setMatrix       (matJoint);

    matBind .setIdentity();
    matBind .setTranslate(Vec3f(-1.f, 0.f, 1.f));
    matBind .invert();
    matJoint.setIdentity();
    matJoint.setTranslate(Vec3f(-1.f, 0.f, 1.f));

    jointL0->setInvBindMatrix(matBind );
    jointL0->setMatrix       (matJoint);

    matBind .setIdentity();
    matBind .setTranslate(Vec3f(1.f, 0.f, 0.f));
    matBind .invert();
    matJoint.setIdentity();
    matJoint.setTranslate(Vec3f(1.f, 0.f, 0.f));

    jointR1->setInvBindMatrix(matBind );
    jointR1->setMatrix       (matJoint);

    matBind .setIdentity();
    matBind .setTranslate(Vec3f(-1.f, 0.f, 0.f));
    matBind .invert();
    matJoint.setIdentity();
    matJoint.setTranslate(Vec3f(-1.f, 0.f, 0.f));

    jointL1->setInvBindMatrix(matBind );
    jointL1->setMatrix       (matJoint);

    // construct skeleton
    SkeletonUnrecPtr skel = Skeleton::create();

    skel->pushToRoots(jointC0N);

    // construct skinned geometry
    SkinnedGeometryUnrecPtr skin = SkinnedGeometry::create();
    sceneN                       = makeNodeFor(skin);

    GeoPnt3fPropertyUnrecPtr            pos     = GeoPnt3fProperty::create();
    GeoPnt3fProperty::StoredFieldType  *posF    = pos->editFieldPtr();

    GeoUInt32PropertyUnrecPtr           idxP    = GeoUInt32Property::create();
    GeoUInt32Property::StoredFieldType *idxPF   = idxP->editFieldPtr();

    GeoVec3fPropertyUnrecPtr            norm    = GeoVec3fProperty::create();
    GeoVec3fProperty::StoredFieldType  *normF   = norm->editFieldPtr();

    GeoUInt32PropertyUnrecPtr           idxN    = GeoUInt32Property::create();
    GeoUInt32Property::StoredFieldType *idxNF   = idxN->editFieldPtr();

    GeoVec4fPropertyUnrecPtr            matIdx  = GeoVec4fProperty::create();
    GeoVec4fProperty::StoredFieldType  *matIdxF = matIdx->editFieldPtr();

    GeoVec4fPropertyUnrecPtr            weight  = GeoVec4fProperty::create();
    GeoVec4fProperty::StoredFieldType  *weightF = weight->editFieldPtr();

    GeoUInt32PropertyUnrecPtr           lens    = GeoUInt32Property::create();
    GeoUInt32Property::StoredFieldType *lensF   = lens->editFieldPtr();

    GeoUInt8PropertyUnrecPtr            types   = GeoUInt8Property::create();
    GeoUInt8Property::StoredFieldType  *typesF  = types->editFieldPtr();

    posF->push_back(Vec3f(-1.f,  0.f,  1.f));
    posF->push_back(Vec3f( 0.f,  0.f,  1.f));
    posF->push_back(Vec3f( 1.f,  0.f,  1.f));
    posF->push_back(Vec3f(-1.f,  0.f,  0.f));
    posF->push_back(Vec3f( 0.f,  0.f,  0.f));
    posF->push_back(Vec3f( 1.f,  0.f,  0.f));
    posF->push_back(Vec3f(-1.f,  0.f, -1.f));
    posF->push_back(Vec3f( 0.f,  0.f, -1.f));
    posF->push_back(Vec3f( 1.f,  0.f, -1.f));

    normF->push_back(Vec3f(0.f, 1.f, 0.f));

    matIdxF->push_back(Vec4f(2.f, 0.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));
    matIdxF->push_back(Vec4f(1.f, 2.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 1.f, 0.f, 0.f));
    matIdxF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));
    matIdxF->push_back(Vec4f(2.f, 5.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 1.f, 1.f, 0.f));
    matIdxF->push_back(Vec4f(0.f, 0.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));
    matIdxF->push_back(Vec4f(1.f, 4.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 1.f, 1.f, 0.f));
    matIdxF->push_back(Vec4f(5.f, 0.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));
    matIdxF->push_back(Vec4f(3.f, 0.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));
    matIdxF->push_back(Vec4f(4.f, 0.f, 0.f, 0.f));  weightF->push_back(Vec4f(1.f, 0.f, 0.f, 0.f));

    idxPF->push_back(0);  idxPF->push_back(1);  idxPF->push_back(3);
    idxPF->push_back(4);  idxPF->push_back(6);  idxPF->push_back(7);
    idxPF->push_back(1);  idxPF->push_back(2);  idxPF->push_back(4);
    idxPF->push_back(5);  idxPF->push_back(7);  idxPF->push_back(8);

    idxNF->push_back(0);  idxNF->push_back(0);  idxNF->push_back(0);
    idxNF->push_back(0);  idxNF->push_back(0);  idxNF->push_back(0);
    idxNF->push_back(0);  idxNF->push_back(0);  idxNF->push_back(0);
    idxNF->push_back(0);  idxNF->push_back(0);  idxNF->push_back(0);

    typesF->push_back(GL_TRIANGLE_STRIP);  lensF->push_back(6);
    typesF->push_back(GL_TRIANGLE_STRIP);  lensF->push_back(6);

    skin->setSkeleton(skel);
    skin->setTypes  (types);
    skin->setLengths(lens );
    skin->setProperty(pos,    SkinnedGeometry::PositionsIndex );
    skin->setIndex   (idxP,   SkinnedGeometry::PositionsIndex );
    skin->setProperty(norm,   SkinnedGeometry::NormalsIndex   );
    skin->setIndex   (idxN,   SkinnedGeometry::NormalsIndex   );
    skin->setProperty(matIdx, SkinnedGeometry::TexCoordsIndex );
    skin->setIndex   (idxP,   SkinnedGeometry::TexCoordsIndex );
    skin->setProperty(weight, SkinnedGeometry::TexCoords1Index);
    skin->setIndex   (idxP,   SkinnedGeometry::TexCoords1Index);

    skin->setJointIndexProperty (SkinnedGeometry::TexCoordsIndex );
    skin->setJointWeightProperty(SkinnedGeometry::TexCoords1Index);

//     skin->setRenderMode(SkinnedGeometry::RMSkeleton       );
    skin->setRenderMode(SkinnedGeometry::RMSkinnedGPU);
    
    ShaderProgramUnrecPtr vp = ShaderProgram::createVertexShader();
    vp->setProgram(vpCode);

    ShaderProgramUnrecPtr fp = ShaderProgram::createFragmentShader();
    fp->setProgram(fpCode);

    ShaderProgramChunkUnrecPtr sh = ShaderProgramChunk::create();
    sh->addShader(vp);
    sh->addShader(fp);

    ChunkMaterialUnrecPtr mat = ChunkMaterial::create();
    mat->addChunk(sh);

    skin->setMaterial(mat);

    actJoint = 0;
}


void display(void)
{
    commitChanges();

    mgr->redraw();
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void idle(void)
{
    mgr->idle();
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{

    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:
    {
        cleanup();
        osgExit();

        exit(0);
    }
    break;

    case ',':
    {
        if(actJoint == 0)
        {
            actJoint = jointStore.size() - 1;
        }
        else
        {
            actJoint -= 1;
        }

        std::cout << "actJoint: " << actJoint << std::endl;
    }
    break;

    case '.':
    {
        if(actJoint == jointStore.size() - 1)
        {
            actJoint = 0;
        }
        else
        {
            actJoint += 1;
        }

        std::cout << "actJoint: " << actJoint << std::endl;
    }
    break;

    case 'w':
    {
        Matrix mat;
        mat.setTranslate(Vec3f(0.f, 0.f, -0.5f));

        jointStore[actJoint]->editMatrix().mult(mat);

        std::cout << "actJoint: " << actJoint 
                  << " matrix:\n" << jointStore[actJoint]->getMatrix()
                  << std::endl;
    }
    break;

    case 'a':
    {
        Matrix mat;
        mat.setTranslate(Vec3f(-0.5f, 0.f, 0.f));

        jointStore[actJoint]->editMatrix().mult(mat);

        std::cout << "actJoint: " << actJoint 
                  << " matrix:\n" << jointStore[actJoint]->getMatrix()
                  << std::endl;
    }
    break;

    case 's':
    {
        Matrix mat;
        mat.setTranslate(Vec3f(0.f, 0.f, 0.5f));

        jointStore[actJoint]->editMatrix().mult(mat);

        std::cout << "actJoint: " << actJoint 
                  << " matrix:\n" << jointStore[actJoint]->getMatrix()
                  << std::endl;
    }
    break;

    case 'd':
    {
        Matrix mat;
        mat.setTranslate(Vec3f(0.5f, 0.f, 0.f));

        jointStore[actJoint]->editMatrix().mult(mat);

        std::cout << "actJoint: " << actJoint 
                  << " matrix:\n" << jointStore[actJoint]->getMatrix()
                  << std::endl;
    }
    break;

    case 'r':
    {
        Matrix mat;
        mat.setTranslate(Vec3f(0.f, 0.5f, 0.f));

        jointStore[actJoint]->editMatrix().mult(mat);

        std::cout << "actJoint: " << actJoint 
                  << " matrix:\n" << jointStore[actJoint]->getMatrix()
                  << std::endl;
    }
    break;

    case 'f':
    {
        Matrix mat;
        mat.setTranslate(Vec3f(0.f, -0.5f, 0.f));

        jointStore[actJoint]->editMatrix().mult(mat);

        std::cout << "actJoint: " << actJoint 
                  << " matrix:\n" << jointStore[actJoint]->getMatrix()
                  << std::endl;
    }
    break;
    }

    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG - testSkinnedGeometry");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
