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

#include "OSGKeySensor.h"
#include "OSGComplexSceneManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKeySensorBase.cpp file.
// To modify it, please change the .fcd file (OSGKeySensor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeySensor::initMethod(InitPhase ePhase)
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

KeySensor::KeySensor(void) :
    Inherited()
{
}

KeySensor::KeySensor(const KeySensor &source) :
    Inherited(source)
{
}

KeySensor::~KeySensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeySensor::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    if(0x0000 != (whichField & KeyFieldMask))
    {
        ComplexSceneManager::the()->updateKeySensor(this);
    }

    Inherited::changed(whichField, origin, details);
}

void KeySensor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump KeySensor NI" << std::endl;
}

void KeySensor::onDestroy(UInt32 uiContainerId)
{
    if(GlobalSystemState != Shutdown)
    {
        ComplexSceneManager::the()->removeKeySensor(this);
    }
}

void KeySensor::update(Int32 x, 
                       Int32 y,
                       Int32 iState)
{
    if(iState == CSMKeyData::ButtonDown)
    {
        editSField(SignalPressedFieldMask);

        setStateRaw     (true               );
        setStateFlipFlop(!getStateFlipFlop());
    }
    else if(iState == CSMKeyData::ButtonUp)
    {
        editSField(SignalReleasedFieldMask);

        setStateRaw     (false            );
    }
}

OSG_END_NAMESPACE
