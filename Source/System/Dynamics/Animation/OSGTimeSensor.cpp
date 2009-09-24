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

#include "OSGTimeSensor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTimeSensorBase.cpp file.
// To modify it, please change the .fcd file (OSGTimeSensor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TimeSensor::initMethod(InitPhase ePhase)
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

TimeSensor::TimeSensor(void) :
    Inherited()
{
}

TimeSensor::TimeSensor(const TimeSensor &source) :
    Inherited(source)
{
}

TimeSensor::~TimeSensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TimeSensor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TimeSensor::dump(      UInt32    uiIndent,
                      const BitVector bvFlags  ) const
{
    SLOG;
    indentLog(uiIndent, PLOG);
    PLOG << "TimeSensor (" << this->getId()
         << " - "          << this
         << ")\n";

    SLOG;
    indentLog(uiIndent + 4, PLOG);
    PLOG <<   "enabled [" << _sfEnabled.getValue()
         << "] active [" << _sfIsActive.getValue()
         << "] loop [" << _sfLoop.getValue()
         << "]\n";
    
    SLOG;
    indentLog(uiIndent + 4, PLOG);
    PLOG <<   "fraction [" << _sfFraction.getValue()
         << "] startTime [" << _sfStartTime.getValue()
         << "] stopTime [" << _sfStopTime.getValue()
         << "] cycleInterval [" << _sfCycleInterval.getValue()
         << "] cycleTime [" << _sfCycleTime.getValue()
         << "] time [" << _sfTime.getValue()
         << "]" << std::endl;
}

void TimeSensor::frame(Time tTime, UInt32 uiFrame)
{
    Real64 dFraction;

    bool bDoTimeRange = bool(_sfStartTime.getValue() < 
                             _sfStopTime .getValue());

    bool bDoCycle      = false;

    if(bDoTimeRange)
    {
        dFraction = 
            Real64( tTime                 - _sfStartTime.getValue()) / 
            Real64(_sfStopTime.getValue() - _sfStartTime.getValue());
    }
    else
    {
        if(_sfCycleTime.getValue() > 0.0)
        {
            dFraction = 
                Real64(tTime - _sfCycleTime.getValue()) / 
                Real64(_sfCycleInterval.getValue());

            bDoCycle = true;
        }
        else
        {
            dFraction = 
                Real64(tTime - _sfStartTime.getValue()) / 
                Real64(_sfCycleInterval.getValue());
        }
    }

    if(_sfEnabled.getValue() == false)
    {
        if(_sfIsActive.getValue() == true) 
        {
            setTime    (tTime);
            setIsActive(false);
            setFraction(Real32(dFraction));
        }
    }
    else
    {
        if(dFraction < 0.0) // before start
        {
            if(bDoCycle == true)
            {
                if(_sfIsActive.getValue() == true) 
                {
                    if(_sfLoop.getValue() == false)
                    {
                        setIsActive (false);
                        setTime     (tTime);
                        setFraction (1.0  );
                        setCycleTime(tTime);
                    }
                    else
                    {
                        setCycleTime(_sfCycleTime    .getValue() - 
                                     _sfCycleInterval.getValue());
                            
                        setTime     (tTime);
                        setFraction (dFraction + 1.0);
                    }
                }
                else
                {
                }
            }
        }
        else if(dFraction > 1.0) // after end time
        {
            if(_sfIsActive.getValue() == true) 
            {
                if(_sfLoop.getValue() == false)
                {
                    setIsActive (false);
                    setTime     (0.f  );
                    setFraction (1.0  );
                    setCycleTime(0.f  );
                    setEnabled  (false);
                }
                else
                {
                    setCycleTime(_sfCycleTime    .getValue() +
                                 _sfCycleInterval.getValue());
                    
                    setTime     (tTime);
                    setFraction (dFraction - 1.0);
                }
            }
            else
            {
                if(bDoTimeRange == false)
                {
                    setFraction (0.f);
                    setCycleTime(tTime - 
                                 (_sfFraction     .getValue() *
                                  _sfCycleInterval.getValue() ));

                    setIsActive (true);
                    setTime     (tTime);
                }
            }
        }
        else  // within cycle
        {
            if (_sfIsActive.getValue() == false) 
            {
                if(bDoTimeRange      == true)
                {
                    setCycleTime(_sfStartTime.getValue());
                    setIsActive (true);
                    setTime     (tTime);
                    setFraction (dFraction);
                }
                else
                {
                    setCycleTime(tTime - 
                                 (_sfFraction     .getValue() *
                                  _sfCycleInterval.getValue() ));
                    
                    if(_sfCycleTime.getValue() >
                       TypeTraits<Time>::getDefaultEps())
                    {
                        setIsActive(true);
                    }
                    
                    setTime(tTime);
                }
            }
            else
            {
                if(tTime        >= _sfStopTime.getValue() && 
                   bDoTimeRange == true                     ) 
                {
                    setIsActive(false);
                }
                else
                {
                    if(tTime >= _sfStartTime.getValue())
                    {
                        setTime    (tTime    );
                        setFraction(dFraction);
                    }
                }
            }
        }
    }
}

OSG_END_NAMESPACE
