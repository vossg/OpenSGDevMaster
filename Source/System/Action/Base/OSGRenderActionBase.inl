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
Camera *RenderActionBase::getCamera(void) const
{
    return _pCamera;
}

inline
Background *RenderActionBase::getBackground(void) const
{
    return _pBackground;
}
    
inline
Window *RenderActionBase::getWindow(void) const
{
    return _pWindow;
}
    
inline
Viewport *RenderActionBase::getViewport(void) const
{
    return _pViewport;
}
    
inline
bool RenderActionBase::getFrustumCulling(void) const
{
    return _bFrustumCulling;
}
    
inline
bool RenderActionBase::getVolumeDrawing(void) const
{
    return _bVolumeDrawing;
}

inline
bool RenderActionBase::getZWriteTrans(void) const
{
    return _bZWriteTrans;
}
    
inline
bool RenderActionBase::getAutoFrustum(void) const
{
    return _bAutoFrustum;
}
    
inline
const FrustumVolume& RenderActionBase::getFrustum(void) const
{
    return _oFrustum;
}
    
inline
bool RenderActionBase::getCorrectTwoSidedLighting(void) const
{
    return _bCorrectTwoSidedLighting;
}

inline
StatCollector* RenderActionBase::getStatCollector(void) const
{
    return _pStatistics;
}

inline
Material *RenderActionBase::getGlobalOverride(void) const
{
    return _pGlobalOverride;
}

inline
TraversalValidator *RenderActionBase::getTravValidator(void)
{
    return _pTravValidator;
}

inline
UInt16 RenderActionBase::getFrameTravCount(void)
{
    return _uiFrameTravCount;
}

inline
void RenderActionBase::setDrawerId(Int32 iId)
{
    _iDrawerId = iId;
}

inline
Int32 RenderActionBase::getDrawerId(void)
{
    return _iDrawerId;
}

inline
void RenderActionBase::setDrawableId(Int32 iId)
{
    _iDrawableId = iId;
}

inline
Int32 RenderActionBase::getDrawableId(void)
{
    return _iDrawableId;
}

inline
RenderActionBase::RenderPropType RenderActionBase::getRenderProperties(void)
{
    return _oCurrentRenderProp;
}

inline
void RenderActionBase::setRenderProperties(RenderPropType oProp)
{
    _oCurrentRenderProp = oProp;
}

inline
void RenderActionBase::resetRenderProperties(void)
{
    _oCurrentRenderProp = 0x0000;
}

inline
void RenderActionBase::setDrawPartPar(bool bVal)
{
    _bDrawPartPar = bVal;
}

inline
bool RenderActionBase::getDrawPartPar(void)
{
    return _bDrawPartPar;
}

inline
void RenderActionBase::setUseGLFinish(bool bVal)
{
    _bUseGLFinish = bVal;
}

inline
bool RenderActionBase::getUseGLFinish(void)
{
    return _bUseGLFinish;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
