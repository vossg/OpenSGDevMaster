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

#include "OSGSensor.h"
#include "OSGComplexSceneManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSensorBase.cpp file.
// To modify it, please change the .fcd file (OSGSensor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Sensor::initMethod(InitPhase ePhase)
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

Sensor::Sensor(void) :
    Inherited()
{
}

Sensor::Sensor(const Sensor &source) :
    Inherited(source)
{
}

Sensor::~Sensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Sensor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Sensor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Sensor NI" << std::endl;
}

void Sensor::onCreate (const Sensor *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running || ComplexSceneManager::the() == NULL)
        return;

    SensorTask *pSensorTask = ComplexSceneManager::the()->getSensorTask();

    if(pSensorTask == NULL)
    {
        fprintf(stderr, "Strange no sensor task\n");
        return;
    }

    pSensorTask->pushToSensors(this);
}

void Sensor::onDestroy(UInt32 uiContainerId)
{
    // Don't add the prototype instances to the list
    if(GlobalSystemState != Shutdown && ComplexSceneManager::the() != NULL)
    {
        SensorTask *pSensorTask = ComplexSceneManager::the()->getSensorTask();

        if(pSensorTask == NULL)
        {
            fprintf(stderr, "Strange no sensor task\n");
            return;
        }

        pSensorTask->removeObjFromSensors(this);
    }

    Inherited::onDestroy(uiContainerId);
}

bool Sensor::init(void)
{
    return true;
}

void Sensor::shutdown(void)
{
}

OSG_END_NAMESPACE
