/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGDeviceInterface.h"
#include "OSGInterfaceOptions.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void DeviceInterface::setOptions(InterfaceOptions *pOptions)
{
    if(pOptions == NULL)
        return;

    _uiNapTime = pOptions->getNapTime();
}

DeviceInterface::DeviceInterface(const Char8 *szName, UInt32 uiId) :
     Inherited  (szName, 
                 uiId  ),
    _pDataLock  (NULL  ),
    _bRunning   (false ),
    _bHasNewData(false ),
    _uiNapTime  (10    )
{
}

DeviceInterface::~DeviceInterface(void)
{
}

bool DeviceInterface::start(void)
{
    if(_pDataLock == NULL)
    {
        _pDataLock = Lock::create();
    }

    OSG_ASSERT(_bRunning  == false);
    OSG_ASSERT(_pDataLock != NULL );

    _bRunning = true;

    return true;
}

void DeviceInterface::stop(void)
{
    if(_bRunning == true)
    {
        _bRunning = false;
    }
}

void DeviceInterface::shutdown(void)
{
}

OSG_END_NAMESPACE
