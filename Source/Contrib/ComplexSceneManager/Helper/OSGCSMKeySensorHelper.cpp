/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#include "OSGCSMKeySensorHelper.h"

#include "algorithm"

OSG_BEGIN_NAMESPACE

CSMKeySensorHelper::CSMKeySensorHelper(void) :
    _oKeyMap(256)
{
}


CSMKeySensorHelper::~CSMKeySensorHelper(void)
{
}

void CSMKeySensorHelper::update(Int32      x,
                                Int32      y,
                                Int32      iState,
                                Char8      cKey   )
{
    KeyStoreIt kIt  = _oKeyMap[cKey].begin();
    KeyStoreIt kEnd = _oKeyMap[cKey].end  ();

    for(; kIt != kEnd; ++kIt)
    {
        (*kIt)->update(x, y, iState);
    }
    
    commitChanges();
}

void CSMKeySensorHelper::updateSensors(KeySensor *pSensor)
{
    if(pSensor == NULL || pSensor->getKey() == '\0')
        return;

    bool bFound = false;

    for(UInt32 i = 0; i < _oKeyMap.size(); ++i)
    {
        KeyStoreIt kIt = std::find(_oKeyMap[i].begin(),
                                   _oKeyMap[i].end  (),
                                    pSensor           );

        if(kIt != _oKeyMap[i].end())
        {
            if(pSensor->getKey() != i)
            {
                _oKeyMap[i].erase(kIt);

                break;
            }
            else
            {
                bFound = true;
                break;
            }
        }
    }

    if(bFound == false)
    {
        _oKeyMap[pSensor->getKey()].push_back(pSensor);
    }
}

void CSMKeySensorHelper::removeSensor (KeySensor *pSensor)
{
    if(pSensor == NULL || pSensor->getKey() == '\0')
        return;

    KeyStoreIt kIt = std::find(_oKeyMap[pSensor->getKey()].begin(),
                               _oKeyMap[pSensor->getKey()].end  (),
                                pSensor                           );

    if(kIt != _oKeyMap[pSensor->getKey()].end())
    {
        _oKeyMap[pSensor->getKey()].erase(kIt);
    }
}

OSG_END_NAMESPACE
