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

#include <OSGConfig.h>

#include "OSGDeviceInterfaceSensor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDeviceInterfaceSensorBase.cpp file.
// To modify it, please change the .fcd file (OSGDeviceInterfaceSensor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DeviceInterfaceSensor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DeviceInterfaceSensor::DeviceInterfaceSensor(void) :
     Inherited(    ),
    _pDevice  (NULL)
{
}

DeviceInterfaceSensor::DeviceInterfaceSensor(
    const DeviceInterfaceSensor &source) :

     Inherited(source),
    _pDevice  (NULL  )
{
}

DeviceInterfaceSensor::~DeviceInterfaceSensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeviceInterfaceSensor::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DeviceInterfaceSensor::dump(      UInt32    ,
                                 const BitVector ) const
{
    SLOG << "Dump DeviceInterfaceSensor NI" << std::endl;
}

bool DeviceInterfaceSensor::init(void)
{
    bool returnValue = false;

    if(_sfInterfaceName.getValue().empty() == true)
        return returnValue;

    OSG_ASSERT(_pDevice == NULL);

    _pDevice = dynamic_cast<DeviceInterface *>(
        ThreadManager::the()->getThread(NULL, 
                                        _sfInterfaceName.getValue().c_str()));
    
    if(_pDevice != NULL)
    {
        _pDevice->setOptions(_sfOptions.getValue());

        returnValue = _pDevice->start();
        
        if(returnValue == true)
        {
            _pDevice->run(0);
        }
        else
        {
            _pDevice = NULL;
        }
    }
    else
    {
        FWARNING(("Could new create device %s\n", 
                  _sfInterfaceName.getValue().c_str()));
    }

    return returnValue;
}

void DeviceInterfaceSensor::shutdown(void)
{
    if(_pDevice != NULL && _pDevice->isRunning() == true)
    {
        _pDevice->stop();

        DeviceInterface::join(_pDevice);

        _pDevice->shutdown();
    }
}

OSG_END_NAMESPACE
