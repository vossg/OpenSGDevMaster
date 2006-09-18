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


OSG_BEGIN_NAMESPACE

inline
void DrawEnv::setAction(RAction *pAction)
{
    _pRAction = pAction;
}

inline
void DrawEnv::setAction(RTAction *pAction)
{
    _pRTAction = pAction;
}

inline
void DrawEnv::setViewport(Viewport *pViewport)
{
    _pViewport = pViewport;
}

inline
void DrawEnv::setWindow(Window *pWindow)
{
    _pWindow = pWindow;
}

inline
void DrawEnv::setupProjection(const Matrixr &projection,
                              const Matrixr &translation)
{
    _cameraProjection      = projection;
    _cameraProjectionTrans = translation;

    _cameraFullProjection  = projection;
    _cameraFullProjection.mult(translation);
}

inline
void DrawEnv::setupViewing(const Matrixr &matrix)
{
    _cameraViewing = matrix;
    
    _cameraToWorld.invertFrom(matrix);
}

inline
void DrawEnv::setObjectToWorld(const Matrixr &matrix)
{
    _objectToWorld = matrix;
}

inline
void DrawEnv::setCameraNear(const Real &camNear)
{
    _cameraNear = camNear;
}

inline
void DrawEnv::setCameraFar(const Real &camFar)
{
    _cameraFar = camFar;
}

inline 
void DrawEnv::setActiveTexTarget(UInt32    uiSlot,
                                 GLenum    uiTarget)
{
    _aActiveTexTargets[uiSlot] = uiTarget;
}

inline
const Matrixr &DrawEnv::getCameraFullProjection(void) const
{
    return _cameraFullProjection;
}

inline
const Matrixr &DrawEnv::getCameraProjection(void) const
{
    return _cameraProjection;
}

inline
const Matrixr &DrawEnv::getCameraProjectionTrans(void) const
{
    return _cameraProjectionTrans;
}

inline
const Matrixr &DrawEnv::getCameraViewing(void) const
{
    return _cameraViewing;
}

inline
const Matrixr &DrawEnv::getCameraToWorld(void) const
{
    return _cameraToWorld;
}

inline
const Matrixr &DrawEnv::getObjectToWorld(void) const
{
    return _objectToWorld;
}

inline
Real DrawEnv::getCameraNear(void) const
{
    return _cameraNear;
}

inline
Real DrawEnv::getCameraFar(void) const
{
    return _cameraFar;
}

inline
DrawEnv::RAction *DrawEnv::getRAction(void) const
{
    return _pRAction;
}

inline
DrawEnv::RTAction *DrawEnv::getRTAction(void) const
{
    return _pRTAction;
}

inline
Viewport *DrawEnv::getViewport(void) const
{
    return _pViewport;
}

inline
Window *DrawEnv::getWindow(void) const
{
    return _pWindow;
}

inline
GLenum DrawEnv::getActiveTexTarget(UInt32 uiSlot) const
{
    return _aActiveTexTargets[uiSlot];
}

inline
void DrawEnv::clearState(void)
{
    _pActiveState         = NULL;
    _pActiveStateOverride = NULL;
}

inline
void DrawEnv::deactivateState(void)
{
    deactivate(_pActiveState, _pActiveStateOverride);
}

inline
void DrawEnv::activateState(State         *pNewState,
                            StateOverride *pNewStateOverride)
{
    if(pNewState != NULL)
    {
        if(_pActiveState != NULL)
        {
            if(pNewState         != _pActiveState        || 
               pNewStateOverride != _pActiveStateOverride )
            {
                changeTo( pNewState,
                          pNewStateOverride, 
                         _pActiveState,
                         _pActiveStateOverride);
                
                _pActiveState         = pNewState;
                _pActiveStateOverride = pNewStateOverride;
            }
        }
        else
        {
            activate(pNewState, pNewStateOverride);
            
            _pActiveState         = pNewState;
            _pActiveStateOverride = pNewStateOverride;
        }
    }
}

OSG_END_NAMESPACE

#define OSGDRAWENV_INLINE_CVSID "@(#)$Id$"
