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
    _pRenderAction = pAction;
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
    _worldToScreen.setValue(_cameraProjection);
    _worldToScreen.mult(_cameraProjectionTrans);
    _worldToScreen.mult(_cameraViewing);
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
void DrawEnv::setActiveShader(UInt32 uiActiveShader)
{
    _uiActiveShader = uiActiveShader;
}

inline
UInt32 DrawEnv::getActiveShader(void)
{
    return _uiActiveShader;
}

inline
const Matrixr &DrawEnv::getWorldToScreen(void) const
{
    return _worldToScreen;
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
const Matrixr &DrawEnv::getCameraDecoration(void) const
{
    return _cameraDecoration;
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
DrawEnv::RAction *DrawEnv::getAction(void) const
{
    return _pRenderAction;
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
const Matrixr &DrawEnv::getVPCameraFullProjection(void) const
{
    return _vpCameraFullProjection;
}

inline
const Matrixr &DrawEnv::getVPCameraProjection(void) const
{
    return _vpCameraProjection;
}


inline
const Matrixr &DrawEnv::getVPCameraProjectionTrans(void) const
{
    return _vpCameraProjectionTrans;
}


inline
const Matrixr &DrawEnv::getVPCameraViewing(void) const
{
    return _vpCameraViewing;
}

inline
const Matrixr &DrawEnv::getVPCameraToWorld(void) const
{
    return _vpCameraToWorld;
}

inline
const Matrixr &DrawEnv::getVPWorldToScreen(void) const
{
    return _vpWorldToScreen;
}

inline
void DrawEnv::setVPCameraMatrices(const Matrixr &mFullprojection,
                                  const Matrixr &mProjection,
                                  const Matrixr &mProjectionTrans,
                                  const Matrixr &mViewing,
                                  const Matrixr &mToWorld,
                                  const Matrixr &mWorldToScreen  )
{
    _vpCameraFullProjection  = mFullprojection;
    _vpCameraProjection      = mProjection;
    _vpCameraProjectionTrans = mProjectionTrans;
    _vpCameraViewing         = mViewing;
    _vpCameraToWorld         = mToWorld;
    _vpWorldToScreen         = mWorldToScreen;
}


inline
void DrawEnv::initVPMatricesFromCamera(void) 
{
    _vpCameraFullProjection  = _cameraFullProjection;
    _vpCameraProjection      = _cameraProjection;
    _vpCameraProjectionTrans = _cameraProjectionTrans;
    _vpCameraViewing         = _cameraViewing;
    _vpCameraToWorld         = _cameraToWorld;
    _vpWorldToScreen         = _worldToScreen;
}

inline
UInt32 DrawEnv::getNumStateChanges(void) const
{
    return _uiNumStateChanges;
}

inline
UInt32 DrawEnv::getNumShaderChanges(void) const
{
    return _uiNumShaderChanges;
}

inline
UInt32 DrawEnv::getNumShaderParamChanges(void) const
{
    return _uiNumShaderParamChanges;
}

inline
void DrawEnv::incNumShaderChanges(void)
{
    ++_uiNumShaderChanges;
}

inline
void DrawEnv::incNumShaderParamChanges(void)
{
    ++_uiNumShaderParamChanges;
}

inline
void DrawEnv::setStatCollector(StatCollector *pStatCollector)
{
    OSG::setRefd(_pStatCollector, pStatCollector);
}

inline
StatCollector* DrawEnv::getStatCollector(void)
{
    return _pStatCollector;
}

inline
void DrawEnv::clearState(void)
{
    _pActiveState            = NULL;
    _pActiveStateOverride    = NULL;
    _uiNumStateChanges       = 0;
    _uiNumShaderChanges      = 0;
    _uiNumShaderParamChanges = 0;


    _cameraDecoration .setIdentity();

    _iPixelLeft              = 0;
    _iPixelRight             = 1;
    _iPixelBottom            = 0;
    _iPixelTop               = 1;

    _bFull                   = true;

    _uiLightState            = 0;
}

inline
void DrawEnv::deactivateState(void)
{
    if(_pActiveStateOverride != NULL)
    {
        deactivate(_pActiveState, _pActiveStateOverride);
    }
    else
    {
        deactivate(_pActiveState);
    }

    _pActiveState         = NULL;
    _pActiveStateOverride = NULL;
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
                if(pNewStateOverride != NULL)
                {
                    if(_pActiveStateOverride != NULL)
                    {
                        changeTo( pNewState,     pNewStateOverride,
                                 _pActiveState, _pActiveStateOverride);
                    }
                    else
                    {
                        changeTo( pNewState,     pNewStateOverride,
                                 _pActiveState                    );
                    }
                }
                else if(_pActiveStateOverride != NULL)
                {
                    changeTo(pNewState, _pActiveState, _pActiveStateOverride);
                }
                else
                {
                    changeTo(pNewState, _pActiveState);
                }

                _pActiveState         = pNewState;
                _pActiveStateOverride = pNewStateOverride;
            }
            else
            {
                if(_pActiveStateOverride != NULL)
                {
                    updateChunk(_pActiveState, 
                                _pActiveStateOverride);
                }
                else
                {
                    updateChunk(_pActiveState);
                }
            }
        }
        else
        {
            if(pNewStateOverride != NULL)
            {
                activate(pNewState, pNewStateOverride);
            }
            else
            {
                activate(pNewState);
            }

            _pActiveState         = pNewState;
            _pActiveStateOverride = pNewStateOverride;
        }
    }
}


inline
void DrawEnv::setViewportDimension (Int32  iPixelLeft,
                                    Int32  iPixelBottom,
                                    Int32  iPixelRight,
                                    Int32  iPixelTop,
                                    bool   bFull        )
{
    _iPixelLeft   = iPixelLeft;
    _iPixelRight  = iPixelRight;
    _iPixelBottom = iPixelBottom;
    _iPixelTop    = iPixelTop;
    _bFull        = bFull;
}

inline
Int32 DrawEnv::getPixelLeft(void) const
{
    return _iPixelLeft;
}

inline
Int32 DrawEnv::getPixelRight(void) const
{
    return _iPixelRight;
}

inline
Int32 DrawEnv::getPixelBottom(void) const
{
    return _iPixelBottom;
}

inline
Int32 DrawEnv::getPixelTop(void) const
{
    return _iPixelTop;
}

inline
Int32 DrawEnv::getPixelWidth(void) const
{
    return _iPixelRight - _iPixelLeft + 1;
}

inline
Int32 DrawEnv::getPixelHeight(void) const
{
    return _iPixelTop - _iPixelBottom + 1;
}

inline
bool DrawEnv::getFull(void) const
{
    return _bFull;
}

inline
void DrawEnv::setTileFullSize(const Vec2u &uiTileFullSize)
{
    _uiTileFullSize = uiTileFullSize;
}

inline
void DrawEnv::setTileRegion(const Vec4f &vTileRegion)
{
    _vTileRegion = vTileRegion;
}

inline
const Vec2u &DrawEnv::getTileFullSize(void) const
{
    return _uiTileFullSize;
}

inline
const Vec4f &DrawEnv::getTileRegion(void) const
{
    return _vTileRegion;
}

inline
void DrawEnv::setLightState(UInt32 uiState)
{
    _uiLightState = uiState;
}

inline
UInt32 DrawEnv::getLightState(void)
{
    return _uiLightState;
}

template<class Action, class Result> inline
Result DrawEnv::doGetData(Action *pAction, UInt32 iSlotId)
{
    return pAction->template getData<Result>(iSlotId);
}

template<class ValuePtr> inline
ValuePtr DrawEnv::getData(Int32 iSlotId) const
{
    OSG_ASSERT(_pRenderAction != NULL);

    return doGetData<RenderActionBase, ValuePtr>(_pRenderAction, iSlotId);
}

OSG_END_NAMESPACE
