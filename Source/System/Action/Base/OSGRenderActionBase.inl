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
StatCollector* RenderActionBase::getStatCollector(void) const
{
    return _pStatistics;
}

inline
StageValidator *RenderActionBase::getStageValidator(void)
{
    return _pStageValidator;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
