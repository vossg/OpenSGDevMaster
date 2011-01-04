/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "OSGConfig.h"

#include "OSGWindow.h"
#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGBaseFields.h"
#include "OSGRenderTreeNodePool.h"
#include "OSGOcclusionCullingTreeBuilder.h"
#include "OSGOCRenderTreeNode.h"
#include "OSGBaseFunctions.h"
#include "OSGBaseInitFunctions.h"
#include "OSGRenderPartitionBase.h"
#include "OSGRenderAction.h"
#include "OSGVolumeDraw.h"

#include "OSGDepthChunk.h"
#include "OSGColorMaskChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGDrawableStatsAttachment.h"

//#define OSG_DUMP_SORTING

OSG_USING_NAMESPACE

/*! \class OSG::OcclusionCullingTreeBuilder
    \ingroup GrpSystemRenderingBackend
 */

UInt32 OcclusionCullingTreeBuilder::_extOcclusionQuery        =
    Window::invalidExtensionID;
UInt32 OcclusionCullingTreeBuilder::_funcGenQueriesARB        =
    Window::invalidFunctionID;
UInt32 OcclusionCullingTreeBuilder::_funcGetQueryObjectuivARB =
    Window::invalidFunctionID;
UInt32 OcclusionCullingTreeBuilder::_funcBeginQueryARB        =
    Window::invalidFunctionID;
UInt32 OcclusionCullingTreeBuilder::_funcEndQueryARB          =
    Window::invalidFunctionID;


StatElemDesc<StatIntElem>  OcclusionCullingTreeBuilder::statNOccNodes(
    "OC-Nodes",
    "total number of nodes tested for occlusion");

StatElemDesc<StatIntElem>  OcclusionCullingTreeBuilder::statNOccTests(
    "OC-Tests",
    "number of occlusion tests");
StatElemDesc<StatIntElem>  OcclusionCullingTreeBuilder::statNOccInvisible(
    "OC-Invisible",
    "number of nodes found invisible through occlusion");

StatElemDesc<StatRealElem> OcclusionCullingTreeBuilder::statNOccSuccessTestPer(
    "OC-Sucess",
    "percentage of successful tests for occlusion");

StatElemDesc<StatIntElem>  OcclusionCullingTreeBuilder::statNOccTriangles(
    "OC-Triangles",
    "number of triangles culled");



bool           OcclusionCullingTreeBuilder::_isOccStateCreated = false;
StateMTRecPtr  OcclusionCullingTreeBuilder::_testingStatePtr;
State         *OcclusionCullingTreeBuilder::_testingState;


OcclusionCullingTreeBuilder::SortModeE OcclusionCullingTreeBuilder::_sortMode =
    OcclusionCullingTreeBuilder::ModeAdaptiveBucket;
UInt32 OcclusionCullingTreeBuilder::_numBuckets = 1000;


// Some typedefs to clean up OpenGL extension handling

typedef void (OSG_APIENTRY *GenQueryT)(GLuint n, GLuint* ids);
typedef void (OSG_APIENTRY *GetQueryObjectuivT)(GLuint id, GLenum pname,
                                               GLuint* param);
typedef void (OSG_APIENTRY *BeginQueryT)(GLenum target, GLuint id);
typedef void (OSG_APIENTRY *EndQueryT)(GLenum target);


//! Register the GraphOp with the factory
static bool initOccTreeBuilder(void)
{
    addPostFactoryInitFunction(&OcclusionCullingTreeBuilder::staticInit);

    return true;
}

static OSG::StaticInitFuncWrapper registerOccTreeInitWrapper(
    initOccTreeBuilder);

bool OcclusionCullingTreeBuilder::staticInit(void)
{
    _extOcclusionQuery = Window::registerExtension("GL_ARB_occlusion_query");

    _funcGenQueriesARB = Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glGenQueriesARB",        _extOcclusionQuery);
    _funcBeginQueryARB = Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glBeginQueryARB",        _extOcclusionQuery);
    _funcEndQueryARB = Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glEndQueryARB",          _extOcclusionQuery);
    _funcGetQueryObjectuivARB = Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glGetQueryObjectuivARB", _extOcclusionQuery);

    return true;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


OcclusionCullingTreeBuilder::OcclusionCullingTreeBuilder(void) :
    Inherited            (),
    _pRoot               (NULL),
    _testSamples         (),
    _numTestSamples      (),
    _occInitialized      (false),
    _currSample          (0),
    _testedNodes         (0),
    _inTesting           (false),
    _buckets             (_numBuckets),
    _bucketsWork         (_numBuckets),
    _bucketLow           (0.f),
    _bucketHigh          (0.f),
    _bucketScale         (0.f),
    _testNodes           (),
    _testPendingNodes    (),
    _worldToScreen       (),
    _vpWidth             (),
    _vpHeight            (),
    _ract                (NULL),
    _minFeatureSize      (0),
    _visPixelThreshold   (0),
    _coveredProbThreshold(0.f),
    _minTriangleCount    (0)
{
}

OcclusionCullingTreeBuilder::~OcclusionCullingTreeBuilder(void)
{
    // Should delete queries here, but those need GL context...
}

/*! Set the sorting mode for the front to back sorter.
*/
OcclusionCullingTreeBuilder::SortModeE
    OcclusionCullingTreeBuilder::setSortMode(SortModeE mode)
{
    SortModeE o = _sortMode;
    _sortMode = _sortMode;

    return o;
}

/*! Set the numberof buckets to use for the bucket sorters.
*/
UInt32 OcclusionCullingTreeBuilder::setNBuckets(UInt32 nbuckets)
{
    UInt32 o = _numBuckets;
    _numBuckets = nbuckets;

    return o;
}

void OcclusionCullingTreeBuilder::setNodePool(RenderTreeNodePool *pNodePool)
{
    _pNodePool     = pNodePool;
    _uiNodePoolIdx = pNodePool->registerType<OCRenderTreeNode>();
}

void OcclusionCullingTreeBuilder::reset(void)
{
    Inherited::reset();

    _numNodes = 0;
    _pRoot    = NULL;

    if(_buckets.size() != _numBuckets)
    {
        _buckets    .resize(_numBuckets);
        _bucketsWork.resize(_numBuckets);
    }

    std::vector<OCRenderTreeNode*>::iterator it, e;

    for(it = _buckets.begin(), e = _buckets.end(); it != e; ++it)
    {
        *it = NULL;
    }

    for(it = _bucketsWork.begin(), e = _bucketsWork.end(); it != e; ++it)
    {
        *it = NULL;
    }

    _bucketLow   = 0.f;
    _bucketHigh  = 0.f;
    _bucketScale = 0.f;

    _ract = NULL;
}

void OcclusionCullingTreeBuilder::add(RenderActionBase    *pAction,
                                      RenderPartitionBase *pPart,
                                      DrawFunctor         &drawFunc,
                                      State               *pState,
                                      StateOverride       *pStateOverride)
{
    OSG_ASSERT((_ract == NULL) || (_ract == pAction));

    _ract = dynamic_cast<RenderAction *>(pAction);

    OSG_ASSERT(_ract != NULL);

    OCRenderTreeNode *pNode = createNode(pAction, pPart, drawFunc,
                                         pState,  pStateOverride);

    addNode(pNode);
}

void OcclusionCullingTreeBuilder::draw(DrawEnv             &denv,
                                       RenderPartitionBase *part)
{
#if 1 //CHECK_ENV_ACTION
    //std::cout << "Frame Start" << std::endl;
    Window* win = denv.getWindow();

    if(_sortMode == ModeAdaptiveBucket)
    {
        // Merge all the buckets to a tree
        for(UInt32 i = 0; i < _numBuckets; ++i)
        {
            if(_buckets[i] != NULL)
            {
                _pRoot->addChild(_buckets[i]);
            }
        }
    }

    if(!win->hasExtension(_extOcclusionQuery))
    {
        // Don't have it, just draw the whole tree.
        SLOG << "Missing OCC GL extensions!!" << endLog;

        _uiActiveMatrix = 0;
        Inherited::drawNode(_pRoot, denv, part);

        return;
    }

//SETUP
// done in add, action should never change
//    _ract = dynamic_cast<RenderAction*>(denv.getAction());

    if(!_ract)
    {
        FFATAL(("OcclusionCullingTreeBuilder::draw: Action in denv is not a "
                "RenderAction!\n"));
        return;
    }

    _uiActiveMatrix = 0;
    Real32 screenCoveredPercentage = 0.f;
    if(_ract->getOcclusionCullingQueryBufferSize() != _numTestSamples || !_occInitialized)
    {
        _numTestSamples = _ract->getOcclusionCullingQueryBufferSize();
        //std::cout << "Buf size: " << _numTestSamples << std::endl;
        _testSamples.resize(_numTestSamples);
        //std::cout << "Performing OCC on " << _numNodes << " nodes." << std::endl;

        GenQueryT genquer = reinterpret_cast<GenQueryT>(
            win->getFunction(_funcGenQueriesARB));
        genquer(_numTestSamples, &(_testSamples.front()));
        _occInitialized = true;
    }

    if(!_isOccStateCreated)
    {
        _isOccStateCreated = true;

        // register an exit function to clean up the State object
        addPreFactoryExitFunction(&releaseTestingState);

        // Create an empty state to render test nodes.
        _testingStatePtr = State::create();

        DepthChunkUnrecPtr dc = DepthChunk::create();
        dc->setReadOnly(true);
        _testingStatePtr->addChunk(dc);

        ColorMaskChunkUnrecPtr cc = ColorMaskChunk::create();
        cc->setMaskR(false);
        cc->setMaskG(false);
        cc->setMaskB(false);
        cc->setMaskA(false);
        _testingStatePtr->addChunk(cc);

        PolygonChunkUnrecPtr pc = PolygonChunk::create();
        pc->setCullFace(GL_BACK);
        _testingStatePtr->addChunk(pc);

        commitChanges();
    }

    //glGenQueriesARB(_numNodes, queries);
    //std::cout << "Calculated Pixels" << std::endl;

    _vpWidth  = denv.getPixelWidth();
    _vpHeight = denv.getPixelHeight();

    _worldToScreen = denv.getVPWorldToScreen();

    _testingState = &*_testingStatePtr;


    _minFeatureSize = _ract->getOcclusionCullingMinimumFeatureSize();
    _visPixelThreshold = _ract->getOcclusionCullingVisibilityThreshold();
    _coveredProbThreshold = _ract->getOcclusionCullingCoveredThreshold();
    _minTriangleCount = _ract->getOcclusionCullingMinimumTriangleCount();
    _inTesting = false;

    _currSample = 0;
//DRAW / TEST / RE-DRAW ON BUFFER FULL
    testNode(_pRoot, denv, part, screenCoveredPercentage);

    StatCollector *sc = _ract->getStatCollector();
    if(sc != NULL)
        sc->getElem(statNOccNodes)->add(_numNodes);
    _numNodes=0;
    _uiActiveMatrix = 0;

    leaveTesting(denv, part);

//RESULTS / RE-DRAW
    while( !_testPendingNodes.empty() )
    {
        drawTestResults(denv, part);
    }

    //std::cout << "Calc Pixels" << std::endl;


    if(sc != NULL)
    {
        Real32 percentage =
            Real32(sc->getElem(statNOccInvisible)->get()) /
            Real32(sc->getElem(statNOccTests)->get());
        sc->getElem(statNOccSuccessTestPer)->set(percentage);
    }

    //std::cout << "Real pixels " << std::endl;
    //std::cout << std::endl;

   // screen_covered_percentage = 1.0;
   // drawNode(_pRoot, denv, part, screen_covered_percentage);
    _numNodes=0;
    _currSample = 0;
    //std::cout << "Frame End" << std::endl;
#endif
}

void OcclusionCullingTreeBuilder::testNode(OCRenderTreeNode   *pNode,
                                           DrawEnv             &denv,
                                           RenderPartitionBase *part,
                                           Real32              &scr_percent)
{
    while (pNode != NULL)
    {
    //MATRIX SETUP
        UInt32 uiNextMatrix = pNode->getMatrixStore().first;

        if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
        {
            glLoadMatrixf(pNode->getMatrixStore().second.getValues());

            _uiActiveMatrix = uiNextMatrix;

            _currMatrix.second = pNode->getMatrixStore().second;

            updateTopMatrix(denv);

            denv.setObjectToWorld(_accMatrix);

            ++part->_uiNumMatrixChanges;
        }

        const BoxVolume &volume = pNode->getVolume();
        Pnt3f min,max;

        volume.getBounds(min, max);
        Pnt3f p[8];
        p[0].setValues(min[0],min[1],min[2]);
        p[1].setValues(max[0],min[1],min[2]);
        p[2].setValues(min[0],max[1],min[2]);
        p[3].setValues(min[0],min[1],max[2]);
        p[4].setValues(max[0],max[1],min[2]);
        p[5].setValues(max[0],min[1],max[2]);
        p[6].setValues(min[0],max[1],max[2]);
        p[7].setValues(max[0],max[1],max[2]);

        //std::cout << "OtoW:" << std::endl;
        //std::cout << denv.getObjectToWorld() << std::endl;
        //std::cout << "WtoC:" << std::endl;
        //std::cout << worldToCam << std::endl;
        for(UInt32 i = 0; i<8;i++)
        {
           // std::cout << p[i] << "=>";
            denv.getObjectToWorld().mult    (p[i], p[i]);
            _worldToScreen         .multFull(p[i], p[i]);
            //std::cout << p[i] << "  ";
        }
        min=p[0];
        max=p[0];
        for(UInt32 i = 0; i<8; i++)
        {
           for(UInt32 j=0; j<2; j++)
           {
              if(p[i][j] < min[j])
              {
                min[j] = p[i][j];
              }
              if(p[i][j] > max[j])
              {
                max[j] = p[i][j];
              }
           }
        }
        max[0] = osgClamp(-1.f, max[0], 1.f);
        max[1] = osgClamp(-1.f, max[1], 1.f);
        min[0] = osgClamp(-1.f, min[0], 1.f);
        min[1] = osgClamp(-1.f, min[1], 1.f);

        // cbb is the percent of the screen real estate this would cover
        Real32 cbb = (max[0] - min[0]) * (max[1] - min[1]) / 4.f;

        //std::cout << cur_node << ":" << pix << " ";
        //std::cout << pNode->getScalar() << std::endl;

//Make decision

        if(pNode->hasFunctor() == false) //Nothing to do
        {
            //renderNode
            drawNode(pNode, denv, part);
        }
        else
        {
            //make decision
            //if(0 > 1)
            if(cbb > scr_percent) // Rendering major occluders
            {
                drawNode(pNode, denv, part);
                //scr_percent+=cbb;
            }
            else
            {

                Real32 pcov;
                pcov = sqrt(scr_percent) - sqrt(cbb);
                pcov *= pcov;
                //std::cout << "cbb:" << cbb << " scr_percent:" << scr_percent <<" pcov:" << pcov << std::endl;
                //if(scr_percent - pcov > 0.001)
                if(pcov > _coveredProbThreshold || cbb < 0.001) // If within threshold or reall small
                {
                    //Get triangles
                    DrawableStatsAttachment *st =
                        DrawableStatsAttachment::get(pNode->getNode()->getCore());
                    st->validate();
                    UInt32 triangles = st->getTriangles();

                    if(cbb * _vpWidth * _vpHeight < _minFeatureSize) //small feature culling
                    {
                        StatCollector *sc = _ract->getStatCollector();
                        if(sc != NULL)
                            sc->getElem(statNOccTriangles)->
                                add(triangles);
                        if(_ract->getOcclusionCullingDebug() && pNode->getNode())
                        {
                            pNode->getNode()->setTravMask(
                                pNode->getNode()->getTravMask() |
                                _ract->getOcclusionCulledDebugMask()
                                );
                        }
                        pNode->setIsRendered(true);
                    }
                    else if( triangles <= _minTriangleCount )
                    {
                        drawNode(pNode, denv, part);
                    }
                    else if((_testPendingNodes.size() == _numTestSamples - 1)) // Make sure we have room to draw a test
                    {
                        drawTestResults(denv, part);
                        if(_testPendingNodes.size() == _numTestSamples - 1) // If we are waiting on a result, draw a node
                        {
                            drawNode(pNode, denv, part);
                        }
                        else
                        {
                            drawTestNode(pNode, denv, part); // Made room, go ahead and draw a test node
                        }
                    }
                    else
                    {
                        drawTestNode(pNode, denv, part); //Plenty of room in buffer to draw a test node
                    }
                }
                else
                {
                    drawNode(pNode, denv, part); // Probably not being covered up...draw the real node
                    //scr_percent+=cbb;
                }
            }
            scr_percent += ((1.0 - scr_percent) * cbb);
        }

//DRAW CHILDREN OR GO TO TOP AND DO IT AGAIN
        if(pNode->getFirstChild() != NULL)
        {
            OCRenderTreeNode *child =
                static_cast<OCRenderTreeNode *>(pNode->getFirstChild());

            testNode(child, denv, part, scr_percent);
        }

        pNode = static_cast<OCRenderTreeNode *>(pNode->getBrother());
    }
}

void OcclusionCullingTreeBuilder::drawTestNode(OCRenderTreeNode    *pNode,
                                               DrawEnv             &denv,
                                               RenderPartitionBase *part)
{

    //std::cout << "Front: " << _currSample << " Back: " << _currSampleBack << std::endl;
    while(_testPendingNodes.size() == _numTestSamples - 1)
    {
        drawTestResults(denv, part);
        //std::cout << "NOW:  Front: " << _currSample << " Back: " << _currSampleBack << std::endl;
    }

    //DRAW DRAW DRAW
    Window* win = denv.getWindow();
    pNode->setIsRendered(false);


    if(_ract->getOcclusionCullingDebug() && pNode->getNode())
    {
        pNode->getNode()->setTravMask(
            pNode->getNode()->getTravMask() |
            _ract->getOcclusionTestedDebugMask()
            );
    }

    const BoxVolume &volume = pNode->getVolume();
    Pnt3f min,max;
    volume.getBounds(min, max);
    static GLfloat n[6][3] = {
    {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] = {
    { 0, 1, 2, 3}, { 3, 2, 6, 7}, { 7, 6, 5, 4},
    { 4, 5, 1, 0}, { 5, 6, 2, 1}, { 7, 4, 0, 3}
    };

    GLfloat v[8][3];
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = min[0];
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = max[0];
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = min[1];
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = max[1];
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = min[2];
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = max[2];


    if(_currSample == _numTestSamples - 1)
    {
        _currSample = 0;
    }
    _currSample++;

    StatCollector *sc = _ract->getStatCollector();
    if(sc != NULL)
        sc->getElem(statNOccTests    )->inc();

    enterTesting(denv, part);
    BeginQueryT beginq = reinterpret_cast<BeginQueryT>(
        win->getFunction(_funcBeginQueryARB));
    //std::cout << "Push: " << _currSample << std::endl;
    pNode->setResultNum(_currSample);
    beginq(GL_SAMPLES_PASSED_ARB, _testSamples[_currSample]);
    glBegin(GL_QUADS);
    for(UInt32 i = 0; i<6; i++)
    {
           glNormal3fv(&n[i][0]);
           glVertex3fv(&v[faces[i][0]][0]);
           glNormal3fv(&n[i][0]);
           glVertex3fv(&v[faces[i][1]][0]);
           glNormal3fv(&n[i][0]);
           glVertex3fv(&v[faces[i][2]][0]);
           glNormal3fv(&n[i][0]);
           glVertex3fv(&v[faces[i][3]][0]);
    }
    glEnd();

    EndQueryT endq = reinterpret_cast<EndQueryT>(
        win->getFunction(_funcEndQueryARB));

    endq(GL_SAMPLES_PASSED_ARB);
    _testPendingNodes.push(pNode);
}

void OcclusionCullingTreeBuilder::drawNode(OCRenderTreeNode   *pNode,
                                           DrawEnv             &denv,
                                           RenderPartitionBase *part)
{
    leaveTesting(denv, part);

    UInt32 uiNextMatrix = pNode->getMatrixStore().first;

    if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
    {
        glLoadMatrixf(pNode->getMatrixStore().second.getValues());

        _uiActiveMatrix = uiNextMatrix;

        _currMatrix.second = pNode->getMatrixStore().second;

        updateTopMatrix(denv);

        denv.setObjectToWorld(_accMatrix);

        ++part->_uiNumMatrixChanges;
    }

    //STATE ACTIVATION
    State         *pNewState         = pNode->getState();
    StateOverride *pNewStateOverride = pNode->getStateOverride();

    denv.setLightState(pNode->getLightState());

    denv.activateState(pNewState, pNewStateOverride);

    pNode->setIsRendered(true);

    if(_ract->getOcclusionCullingDebug() && pNode->getNode())
    {
        pNode->getNode()->setTravMask(
            pNode->getNode()->getTravMask() |
            _ract->getOcclusionVisibleDebugMask()
            );
    }

    //DRAW DRAW DRAW

    if(pNode->hasFunctor() == true)
    {
        if(part->_bCorrectNegScale)
        {
            const Matrix &m = _currMatrix.second;

            // test for a "flipped" matrix
            // glFrontFace can give conflicts with the polygon chunk ...

            if(m[0].cross(m[1]).dot(m[2]) < 0.0)
            {
                glFrontFace(GL_CW);
            }
            else
            {
                glFrontFace(GL_CCW);
            }
        }

        //BoxVolume volume = pNode->getVol();
        //drawVolume(volume);
        pNode->getFunctor()(&denv);
    }
}

void OcclusionCullingTreeBuilder::drawTestResults(DrawEnv             &denv,
                                                  RenderPartitionBase *part)
{
    OCRenderTreeNode* pNode;
    while (!_testPendingNodes.empty())
    {
        pNode = _testPendingNodes.front();
        //DRAW DRAW DRAW
        if(pNode->hasFunctor() == true && !pNode->getIsRendered())
        {
            Window* win = denv.getWindow();
            GetQueryObjectuivT getquiv =
                reinterpret_cast<GetQueryObjectuivT>(
                    win->getFunction(_funcGetQueryObjectuivARB));
            GLuint available = 0;
            getquiv(_testSamples[pNode->getResultNum()], GL_QUERY_RESULT_AVAILABLE_ARB, &available);
            if (!available)
            {
                //std::cout << "Waiting on " << pNode->getResultNum() << " buf size:" << _testPendingNodes.size() << std::endl;
                return;
            }
            GLuint sampleCount = 1;  //XXX: Set to what it should be from calc above.
            getquiv(_testSamples[pNode->getResultNum()], GL_QUERY_RESULT_ARB, &sampleCount);

            if(sampleCount > _visPixelThreshold)
            {
                drawNode(pNode, denv, part);
            }
            else
            {
                StatCollector *sc = _ract->getStatCollector();
                if(sc != NULL)
                    sc->getElem(statNOccInvisible)->inc();

                DrawableStatsAttachment *st =
                    DrawableStatsAttachment::get(pNode->getNode()->getCore());

                st->validate();

                if(sc != NULL)
                    sc->getElem(statNOccTriangles)->
                        add(st->getTriangles());

                if(_ract->getOcclusionCullingDebug() && pNode->getNode())
                {
                    pNode->getNode()->setTravMask(
                        pNode->getNode()->getTravMask() |
                        _ract->getOcclusionCulledDebugMask()
                        );
                }
            }
        }
        //std::cout << "Popped: " << pNode->getResultNum() << " buf size now: " << _testPendingNodes.size() - 1 <<  std::endl;
        _testPendingNodes.pop();
    }
}

OCRenderTreeNode *
OcclusionCullingTreeBuilder::createNode(RenderActionBase    *pAction,
                                        RenderPartitionBase *pPart,
                                        DrawFunctor         &drawFunc,
                                        State               *pState,
                                        StateOverride       *pStateOverride)
{
    RenderPartition  *pRPart = dynamic_cast<RenderPartition *>(pPart);
    OCRenderTreeNode *pNode  = _pNodePool->create<OCRenderTreeNode>(_uiNodePoolIdx);

    Node            *actNode = _ract->getActNode();
    const BoxVolume &objVol  = actNode->getVolume();

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
    Pnt3f objPos(TypeTraits<Real32>::getMax(),
                 TypeTraits<Real32>::getMax(),
                 TypeTraits<Real32>::getMax() );
    Pnt3f volVert[8];
#else
    Pnt3d objPos(TypeTraits<Real64>::getMax(),
                 TypeTraits<Real64>::getMax(),
                 TypeTraits<Real64>::getMax() );
    Pnt3f volVert[8];
#endif

    Pnt3f volMin;
    Pnt3f volMax;

    objVol.getBounds(volMin, volMax);

    volVert[0].setValues(volMin[0], volMin[1], volMin[2]);
    volVert[1].setValues(volMax[0], volMin[1], volMin[2]);
    volVert[2].setValues(volMin[0], volMax[1], volMin[2]);
    volVert[3].setValues(volMin[0], volMin[1], volMax[2]);
    volVert[4].setValues(volMax[0], volMax[1], volMin[2]);
    volVert[5].setValues(volMax[0], volMin[1], volMax[2]);
    volVert[6].setValues(volMin[0], volMax[1], volMax[2]);
    volVert[7].setValues(volMax[0], volMax[1], volMax[2]);

    for(UInt32 i = 0; i < 8; ++i)
    {
        pRPart->getModelViewMatrix().mult(volVert[i], volVert[i]);

        if(volVert[i][2] < objPos[2])
            objPos = volVert[i];
    }

    pNode->setScalar( (-objPos[2]       - pRPart->getNear()) /
                      (pRPart->getFar() - pRPart->getNear())  );

    pNode->setFunctor      (drawFunc               );
    pNode->setState        (pState                 );
    pNode->setStateOverride(pStateOverride         );
    pNode->setLightState   (pRPart->getLightState());
    pNode->setNode         (_ract->getActNode()    );
    pNode->setVolume       (objVol                 );

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
    pNode->setMatrixStore  (pRPart->getMatrixStackTop());
#else
    Matrix4f tmpMat;
    tmpMat.convertFrom(pRPart->getModelViewMatrix());
    MatrixStore tmpMS (pRPart->getMatrixStackTop().first, tmpMat);

    pNode->setMatrixStore(tmpMS);
#endif

    return pNode;
}

void OcclusionCullingTreeBuilder::addNode(OCRenderTreeNode *pNode)
{
    Real32 val = pNode->getScalar();

    if(_pRoot == NULL)
    {
        _pRoot = _pNodePool->create<OCRenderTreeNode>(_uiNodePoolIdx);

        _bucketLow   = val;
        _bucketHigh  = val + 0.1;
        _bucketScale = (_numBuckets + 1) / (_bucketHigh - _bucketLow);
    }

    switch(_sortMode)
    {
    case ModeAdaptiveBucket:
        addNodeAdaptiveBucketMode(pNode);
        break;

    case ModeBucket:
        addNodeBucketMode(pNode);
        break;

    case ModeScalar:
        addNodeScalarMode(pNode);
        break;

    default:
        SFATAL << "OcclusionCullingTreeBuilder::addNode: Unknown sort mode '"
               << _sortMode << "'." << std::endl;
        break;
    }

}

void
OcclusionCullingTreeBuilder::addNodeAdaptiveBucketMode(OCRenderTreeNode *pNode)
{
    Real32 val       = pNode->getScalar();
    Int32  bucketIdx = static_cast<Int32>((val - _bucketLow) * _bucketScale);

    bucketIdx = osgClamp<Int32>(0, bucketIdx, _numBuckets - 1);

    // XXX with the above osgClamp this never triggers... ?? --cneumann
    if(bucketIdx < 0 || bucketIdx >= Int32(_numBuckets))
    {
        Real32 newLow   = osgMin(val, _bucketLow );
        Real32 newHigh  = osgMax(val, _bucketHigh);
        Real32 newScale = (_numBuckets + 1) / (newHigh - newLow);

        // only rescale in exponential steps to reduce the
        // number of rescales
        Real32 rescale  = _bucketScale / newScale;
        UInt32 step     = osgNextPower2(static_cast<UInt32>(osgCeil(rescale)));

        SLOG <<   "OCTB::addABM: old: " << _bucketLow << " - " << _bucketHigh << " - " << _bucketScale
             << "\n              new: " << newLow     << " - " << newHigh     << " - " << newScale
             << "\n rescale " << rescale << " step " << step
             << std::endl;

        newScale = _bucketScale / step;
        Real32 d = (_numBuckets - 1) / newScale;
        newLow  = osgMax(newLow - d / 2.f, 0.f);
        newHigh = osgMin(newLow + d,       1.f);

        // move bucket contents
        Real32 iter  = _bucketLow;
        Real32 istep = 1.f / _bucketScale;

        for(UInt32 i = 0; i < _numBuckets; ++i, iter += istep)
        {
            if(_buckets[i] == NULL)
                continue;

            UInt32 index = static_cast<UInt32>((iter - newLow) * newScale);

            if(_bucketsWork[index] == NULL)
            {
                _bucketsWork[index] = _buckets[i];
            }
            else
            {
                _bucketsWork[index]->addChild(_buckets[i]);
            }

            _buckets[i] = NULL;
        }

        _buckets.swap(_bucketsWork);

        _bucketLow   = newLow;
        _bucketHigh  = newHigh;
        _bucketScale = newScale;

        bucketIdx = osgClamp<Int32>(
            0,
            static_cast<Int32>((val - _bucketLow) * _bucketScale),
            _numBuckets - 1);
    }

    if(_buckets[bucketIdx] == NULL)
    {
        _buckets[bucketIdx] = pNode;
    }
    else
    {
        _buckets[bucketIdx]->addChild(pNode);
    }

    ++_numNodes;
}

void OcclusionCullingTreeBuilder::addNodeBucketMode(OCRenderTreeNode *pNode)
{
    Real32 val       = pNode->getScalar();
    Int32  bucketIdx = osgClamp<Int32>(0,
                                       static_cast<Int32>(val * _numBuckets),
                                       _numBuckets - 1);

    if(_buckets[bucketIdx] == NULL)
    {
        _pRoot->addChild(pNode);
        _buckets[bucketIdx] = pNode;
    }
    else
    {
        _buckets[bucketIdx]->addChild(pNode);
    }

    ++_numNodes;
}

void OcclusionCullingTreeBuilder::addNodeScalarMode(OCRenderTreeNode *pNode)
{
    if(_pRoot->getFirstChild() == NULL)
    {
        _pRoot->addChild(pNode);
        ++_numNodes;
    }
    else
    {
        RenderTreeNode *pCurrent = _pRoot->getFirstChild();
        RenderTreeNode *pLast    = NULL;
        bool            found    = false;

        do
        {
            if(pNode->getScalar() > pCurrent->getScalar())
            {
                pLast    = pCurrent;
                pCurrent = pCurrent->getBrother();
            }
            else
            {
                found = true;
            }
        }
        while(found == false && pCurrent != NULL);

        if(found == true)
        {
            if(pLast == NULL)
            {
                _pRoot->insertFirstChild(pNode);
            }
            else
            {
                _pRoot->insertChildAfter(pLast, pNode);
            }

            ++_numNodes;
        }
        else
        {
            _pRoot->addChild(pNode);
            ++_numNodes;
        }
    }
}

bool OcclusionCullingTreeBuilder::releaseTestingState(void)
{
    _isOccStateCreated = false;
    _testingStatePtr   = NULL;
    _testingState      = NULL;

    return true;
}
