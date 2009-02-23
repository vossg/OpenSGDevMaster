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

#include "OSGMouseDataInterfaceSensor.h"
#include "OSGMouseDataDeviceInterface.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMouseDataInterfaceSensorBase.cpp file.
// To modify it, please change the .fcd file
// (OSGMouseDataInterfaceSensor.fcd) and 
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MouseDataInterfaceSensor::initMethod(InitPhase ePhase)
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

MouseDataInterfaceSensor::MouseDataInterfaceSensor(void) :
     Inherited(    ),
    _pMDDevice(NULL)
{
}

MouseDataInterfaceSensor::MouseDataInterfaceSensor(
    const MouseDataInterfaceSensor &source) :

     Inherited(source),
    _pMDDevice(NULL  )
{
}

MouseDataInterfaceSensor::~MouseDataInterfaceSensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MouseDataInterfaceSensor::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MouseDataInterfaceSensor::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump MouseDataInterfaceSensor NI" << std::endl;
}


void MouseDataInterfaceSensor::frame(Time tTime, UInt32 uiFrame)
{
    if(_pMDDevice == NULL)
        return;

    _pMDDevice->lock();

    if(_pMDDevice->hasNewData() == true)
    {
        MouseDataDeviceInterface::MouseDataBuffer::const_iterator mIt  =
            _pMDDevice->getDataBuffer().begin();
        MouseDataDeviceInterface::MouseDataBuffer::const_iterator mEnd =
            _pMDDevice->getDataBuffer().end();

        for(; mIt != mEnd; ++mIt)
        {
            editSField(MouseDataFieldMask);

            _sfMouseData.getValue() = *mIt;

            commitChanges();
        }

        _pMDDevice->clearNewData();
    }

    _pMDDevice->unlock();
}

bool MouseDataInterfaceSensor::init(void)
{
    bool returnValue = Inherited::init();

    if(returnValue == true)
    {
        _pMDDevice = 
            dynamic_cast<MouseDataDeviceInterface *>(_pDevice.get());

        if(_pMDDevice == NULL)
        {
            returnValue = false;
            
            FWARNING(("device is not a mousedata device\n"));
        }
    }

    return returnValue;
}

void MouseDataInterfaceSensor::shutdown(void)
{
    Inherited::shutdown();

    _pMDDevice = NULL;
}

OSG_END_NAMESPACE
