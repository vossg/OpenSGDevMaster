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


inline    
Camera *DrawActionBase::getCamera(void) const
{
    return _camera;
}

inline
const Matrixr &DrawActionBase::getCameraToWorld(void)
{
    return _mCameraToWorld;
}
    
inline
Background *DrawActionBase::getBackground(void) const
{
    return _background;
}
    
inline
Window *DrawActionBase::getWindow(void) const
{
    return _window;
}
    
inline
Viewport *DrawActionBase::getViewport(void) const
{
    return _viewport;
}
    
inline
bool DrawActionBase::getFrustumCulling(void) const
{
    return _frustumCulling;
}
    
inline
bool DrawActionBase::getVolumeDrawing(void) const
{
    return _volumeDrawing;
}
    
inline
bool DrawActionBase::getAutoFrustum(void) const
{
    return _autoFrustum;
}
    
inline
const FrustumVolume& DrawActionBase::getFrustum(void) const
{
    return _frustum;
}
    
inline
StatCollector* DrawActionBase::getStatistics(void) 
{
    if(_statistics == NULL)
    {
        _statistics = StatCollector::create();
        _ownStat = true;
    }

    return _statistics;
}

inline
bool DrawActionBase::hasOwnStat(void)
{
    return _ownStat;
}

inline 
Material *DrawActionBase::getMaterial(void) const
{
    return _pMaterial;
}

inline 
NodePtr DrawActionBase::getMaterialNode(void) const
{
    return _pMaterialNode;
}

inline
DrawEnv *DrawActionBase::getDrawEnv(void) const
{
    return _pDrawEnv;
}

/*---------------------------- properties ---------------------------------*/

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

#define OSGDRAWACTIONBASE_INLINE_CVSID "@(#)$Id$"
