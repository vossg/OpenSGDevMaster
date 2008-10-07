/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

inline
void ShadowStageData::setRunning(bool bVal)
{
    _bRunning = bVal;
}

inline
bool ShadowStageData::getRunning(void)
{
    return _bRunning;
}

inline
void ShadowStageData::setTreeHandler(ShadowTreeHandler *pHandler)
{
    _pTreeHandler = pHandler;
}

inline
ShadowTreeHandler *ShadowStageData::getTreeHandler(void)
{
    return _pTreeHandler;
}

inline
ShadowStageData::ShadowMapStore &ShadowStageData::getShadowMaps(void)
{
    return _vShadowMaps;
}

inline
ShadowStageData::NodeStore  &ShadowStageData::getTransparents(void)
{
    return _vTransparents;
}

inline
ShadowStageData::LightStore &ShadowStageData::getLights(void)
{
    return _vLights;
}

inline
ShadowStageData::LightStore &ShadowStageData::getOldLights(void)
{
    return _vOldLights;
}

inline
ShadowStageData::CamStore &ShadowStageData::getLightCameras(void)
{
    return _vLightCameras;
}

inline
ShadowStageData::TransStore &ShadowStageData::getLightCamTrans(void)
{
    return _vLightCamTrans;
}

inline
ShadowStageData::NodeStore &ShadowStageData::getLightCamBeacons(void)
{
    return _vLightCamBeacons;
}

inline
ShadowStageData::LStateStore &ShadowStageData::getLightStates(void)
{
    return _vLightStates;
}

inline
ShadowStageData::StatusStore &ShadowStageData::getExcludeNodeActive(void)
{
    return _vExcludeNodeActive;
}

inline
ShadowStageData::StatusStore &ShadowStageData::getRealPointLight(void)
{
    return _vRealPointLight;
}

inline
Node *ShadowStageData::getLightRoot(UInt32 index)
{
    return _vLights[index].first;
}

OSG_END_NAMESPACE
