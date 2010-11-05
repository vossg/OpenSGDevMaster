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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

inline
DrawEnv &RenderPartition::getDrawEnv(void)
{
    return _oDrawEnv;
}

inline UInt32
RenderPartition::getKeyGen(void) const
{
    return _uiKeyGen;
}

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

inline
void RenderPartition::setViewportDimension(Int32 iPixelLeft,
                                           Int32 iPixelBottom,
                                           Int32 iPixelRight,
                                           Int32 iPixelTop,
                                           bool  bFull       )
{
    _oDrawEnv.setViewportDimension(iPixelLeft,
                                   iPixelBottom,
                                   iPixelRight,
                                   iPixelTop,
                                   bFull);
}

inline
Int32 RenderPartition::getViewportWidth(void)
{
    return _oDrawEnv.getPixelWidth();
}

inline
Int32 RenderPartition::getViewportHeight(void)
{
    return _oDrawEnv.getPixelHeight();
}

inline
void RenderPartition::setSetupMode(UInt32 uiSetupMode)
{
    _uiSetupMode = uiSetupMode;
}

inline
void RenderPartition::addSetupModeBit(UInt32 uiSetupModeBit)
{
    _uiSetupMode |= uiSetupModeBit;
}

inline
void RenderPartition::subSetupMode(UInt32 uiSetupModeBit)
{
    _uiSetupMode &= ~uiSetupModeBit;
}

inline
void RenderPartition::setNodePool(RenderTreeNodePool *pNodePool)
{
    _pNodePool = pNodePool;
}

inline
void RenderPartition::setStatePool(StateOverridePool *pStatePool)
{
    _pStatePool = pStatePool;
}

inline 
void RenderPartition::setTreeBuilderPool(TreeBuilderPool *pTreeBuilderPool)
{
    _pTreeBuilderPool = pTreeBuilderPool;
}

inline
void RenderPartition::setStatCollector(StatCollectorP pStatCollector)
{
    _oDrawEnv.setStatCollector(pStatCollector);
}

inline
StatCollectorP RenderPartition::getStatCollector(void)
{
    return _oDrawEnv.getStatCollector();
}

#if 0
inline
void RenderPartition::setViewport(Viewport *pViewport)
{
    _oDrawEnv.setViewport(pViewport);
}

inline
Viewport *RenderPartition::getViewport(void)
{
    return _oDrawEnv.getViewport();
}
#endif

inline
void RenderPartition::setWindow(Window *pWindow)
{
    _oDrawEnv.setWindow(pWindow);
}

inline
Window *RenderPartition::getWindow(void)
{
    return _oDrawEnv.getWindow();
}

inline
void RenderPartition::setBackground(Background *pBackground)
{
    _pBackground = pBackground;
}

inline
void RenderPartition::pushToForegrounds(Foreground *pForeground)
{
    _vpForegrounds.push_back(pForeground);
}

inline
void RenderPartition::clearForegrounds(void)
{
    _vpForegrounds.clear();
}

inline
void RenderPartition::setupProjection(const Matrix4f &projection,
                                      const Matrix4f &translation)
{
    _oDrawEnv.setupProjection(projection, translation);
}

inline
const Matrix4f &RenderPartition::getFullProjection(void)
{
    return _oDrawEnv._openGLState.getProjection();
}

inline
const Matrix4f &RenderPartition::getProjection(void)
{
    return _oDrawEnv.getCameraProjection();
}

inline
const Matrix4f &RenderPartition::getProjectionTrans(void)
{
    return _oDrawEnv.getCameraProjectionTrans();
}

inline
const Matrix4f &RenderPartition::getVPFullProjection(void)
{
    return _oDrawEnv.getVPCameraFullProjection();
}

inline
const Matrix4f &RenderPartition::getVPProjection(void)
{
    return _oDrawEnv.getVPCameraProjection();
}

inline
const Matrix4f &RenderPartition::getVPProjectionTrans(void)
{
    return _oDrawEnv.getVPCameraProjectionTrans();
}

inline
void RenderPartition::setupViewing(const Matrix4f &matrix)
{
    _oDrawEnv.setupViewing(matrix);

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
    _modelViewMatrix.second = matrix;
#else
    Matrix4d temp;
    temp.convertFrom(matrix);
    _modelViewMatrix.second = temp;
#endif

    _modelMatrix.setIdentity();
    _modelMatrixValid = true;
}

template<class MatrixType> inline
void RenderPartition::pushMatrix(const MatrixType &matrix)
{
    _modelViewMatrixStack.push_back(_modelViewMatrix);
    
    _modelViewMatrix.first = ++_uiMatrixId;
    _modelViewMatrix.second.mult(matrix);
   
    _modelMatrixValid = false;
}

inline
const Matrix &RenderPartition::getModelMatrix(void) const
{
    updateModelMatrix();

    return _modelMatrix;
}

inline
const Matrix &RenderPartition::getModelViewMatrix(void) const
{
    return _modelViewMatrix.second;
}

inline const RenderPartition::MatrixStore &
RenderPartition::getMatrixStackTop(void) const
{
    return _modelViewMatrix;
}

inline 
const Matrix4f &RenderPartition::getViewing(void)
{
    return _oDrawEnv.getCameraViewing();
}

inline
const Matrix4f &RenderPartition::getCameraToWorld(void)
{
    return _oDrawEnv.getCameraToWorld();
}

inline 
const Matrix4f &RenderPartition::getVPViewing(void)
{
    return _oDrawEnv.getVPCameraViewing();
}

inline
const Matrix4f &RenderPartition::getVPCameraToWorld(void)
{
    return _oDrawEnv.getCameraToWorld();
}

inline
void RenderPartition::addPartition(RenderPartition *pPart)
{
    _vGroupStore.push_back(pPart);
}

inline 
void RenderPartition::setNear(Real32 camNear)
{
    _oDrawEnv.setCameraNear(camNear);
}

inline 
void RenderPartition::setFar (Real32 camFar)
{
    _oDrawEnv.setCameraFar(camFar);
}

inline 
Real32 RenderPartition::getNear(void)
{
    return _oDrawEnv.getCameraNear();
}

inline 
Real32 RenderPartition::getFar(void)
{
    return _oDrawEnv.getCameraFar();
}

inline
UInt32 RenderPartition::getLightState(void) const
{
    return _uiLightState;
}

inline
void RenderPartition::setKeyGen(UInt32 uiKeyGen)
{
    _uiKeyGen = uiKeyGen;
}


inline
Material *RenderPartition::getMaterial(void)
{
    return _pMaterial;
}

inline
void RenderPartition::setRenderTarget(FrameBufferObject *pTarget)
{
    _pRenderTarget = pTarget;
}

inline
FrameBufferObject *RenderPartition::getRenderTarget(void)
{
    return _pRenderTarget;
}

inline
void RenderPartition::setDrawBuffer(GLenum eBuffer)
{
    _eDrawBuffer = eBuffer;
}

inline
bool RenderPartition::getFrustumCulling(void) const
{
    return _bFrustumCulling;
}

inline
void RenderPartition::setFrustumCulling(bool val)
{
    _bFrustumCulling = val;
}
    
inline
bool RenderPartition::getVolumeDrawing(void) const
{
    return _bVolumeDrawing;
}

inline
void RenderPartition::setVolumeDrawing(bool val)
{
    _bVolumeDrawing = val;
}
    
inline
const FrustumVolume &RenderPartition::getFrustum(void) const
{
    return _oFrustum;
}

inline
void RenderPartition::setFrustum(FrustumVolume &frust)
{
    _oFrustum = frust;
}

inline
void RenderPartition::disable(void)
{
    _bDone = true;
}

inline
void RenderPartition::dropFunctor(SimpleDrawCallback &oSimpleCallback)
{
    _oSimpleDrawCallback = oSimpleCallback;
}

inline
UInt32 RenderPartition::getNumMatrixChanges(void)
{
    return _uiNumMatrixChanges;
}

inline
UInt32 RenderPartition::getNumStateChanges(void)
{
    return _oDrawEnv.getNumStateChanges();
}

inline
UInt32 RenderPartition::getNumShaderChanges(void)
{
    return _oDrawEnv.getNumShaderChanges();
}

inline
UInt32 RenderPartition::getNumShaderParamChanges(void)
{
    return _oDrawEnv.getNumShaderParamChanges();
}

inline
UInt32 RenderPartition::getNumTriangles(void)
{
    return _uiNumTriangles;
}

inline
void RenderPartition::addPreRenderCallback (const RenderFunctor &oCallback)
{
    _vPreRenderCallbacks.push_back(oCallback);
}

inline
void RenderPartition::addPostRenderCallback(const RenderFunctor &oCallback)
{
    _vPostRenderCallbacks.push_back(oCallback);
}

/*-------------------------- your_category---------------------------------*/

#ifdef OSG_DEBUG
inline
void RenderPartition::setDebugString(std::string szDebugString)
{
    _szDebugString = szDebugString;
}
#endif

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

inline
void  RenderPartition::setNode(Node *pNode)
{
    _pNode = pNode;
}

inline
Node *RenderPartition::getNode(void)
{
    return _pNode;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
