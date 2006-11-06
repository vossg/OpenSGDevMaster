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
    _iPixelLeft   = iPixelLeft;
    _iPixelRight  = iPixelRight;
    _iPixelBottom = iPixelBottom;
    _iPixelTop    = iPixelTop;
    _bFull        = bFull;
}

inline
Int32 RenderPartition::getViewportWidth(void)
{
    return _iPixelRight - _iPixelLeft + 1;
}

inline
Int32 RenderPartition::getViewportHeight(void)
{
    return _iPixelTop - _iPixelBottom + 1;
}

inline
void RenderPartition::setSetupMode(SetupMode eSetupMode)
{
    _eSetupMode = eSetupMode;
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
void RenderPartition::setViewport(Viewport *pViewport)
{
    _oDrawEnv.setViewport(pViewport);
}

inline
Viewport *RenderPartition::getViewport(void)
{
    return _oDrawEnv.getViewport();
}


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
void RenderPartition::setupProjection(const Matrix4f &projection,
                                      const Matrix4f &translation)
{
    _oDrawEnv.setupProjection(projection, translation);
}

inline
const Matrix4f &RenderPartition::getFullProjection(void)
{
    return _oDrawEnv.getCameraFullProjection();
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
void RenderPartition::setupViewing(const Matrix4f &matrix)
{
    _oDrawEnv.setupViewing(matrix);

    _currMatrix.second = matrix;

    updateTopMatrix();
}

inline 
const Matrix4f &RenderPartition::getViewing(void)
{
    return _oDrawEnv.getCameraViewing();
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
void RenderPartition::setKeyGen(UInt32 uiKeyGen)
{
    _uiKeyGen = uiKeyGen;
}

inline
void RenderPartition::overrideMaterial(Material        *pMaterial,
                                       NodePtrConstArg  pNode    )
{
    if(_pMaterialNode == NullFC)
    {
        _pMaterial     = pMaterial;
        _pMaterialNode = pNode;
    }
    else if(_pMaterialNode == pNode)
    {
        if(pMaterial == NULL)
        {
            _pMaterial     = NULL;
            _pMaterialNode = NullFC;
        }
        else
        {
            fprintf(stderr, "strange reset with non null mat\n");
        }
    }
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

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE

#define OSGRENDERPARTITION_INLINE_CVSID "@(#)$Id$"
