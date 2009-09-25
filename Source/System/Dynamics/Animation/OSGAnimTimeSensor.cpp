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

#include "OSGAnimTimeSensor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimTimeSensorBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimTimeSensor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimTimeSensor::initMethod(InitPhase ePhase)
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

AnimTimeSensor::AnimTimeSensor(void) :
    Inherited()
{
}

AnimTimeSensor::AnimTimeSensor(const AnimTimeSensor &source) :
    Inherited(source)
{
}

AnimTimeSensor::~AnimTimeSensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimTimeSensor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AnimTimeSensor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimTimeSensor NI" << std::endl;
}

void AnimTimeSensor::frame(Time oTime, UInt32 uiFrame)
{
    Time startT = _sfStartTime  .getValue();
    Time stopT  = _sfStopTime   .getValue();
    Time currT  = _sfTime       .getValue();

    Time length = _sfCycleLength.getValue();
    Time deltaT = 0.0;

    setTime(oTime);

    if(getEnabled() == false)
    {
        if(getIsActive() == true)
        {
            setIsActive(false);
        }

        return;
    }

    if(startT < stopT)
    {
        if(oTime < startT)
        {
            if(getIsActive() == true)
            {
                SLOG << "ATS: start < stop, BEFORE startT, deactivating" << std::endl;

                setFraction(0.f  );
                setAnimTime(0.f  );
                setIsActive(false);
            }

            return;
        }
        else if(oTime > stopT)
        {
            if(getIsActive() == true)
            {
                SLOG << "ATS: start < stop, AFTER stopT";

                setFraction(1.f   );
                setAnimTime(length);

                // only deactivate the second time oTime > stopT
                // to propagate the final state
                if(currT > stopT)
                {
                    PLOG << ", deactivating";

                    setIsActive(false);
                }

                PLOG << std::endl;
            }

            return;
        }
        else
        {
            if(currT <= 0.0)
            {
                deltaT = oTime - startT;
            }
            else
            {
                deltaT = oTime - currT;
            }
        }
    }
    else
    {
        if(oTime < startT)
        {
            if(getIsActive() == true)
            {
                SLOG << "ATS: start >= stop, BEFORE startT, deactivating" << std::endl;

                setFraction(0.f  );
                setAnimTime(0.f  );
                setIsActive(false);
            }

            return;
        }
        else
        {
            if(currT <= 0.0)
            {
                deltaT = oTime - startT;
            }
            else
            {
                deltaT = oTime - currT;
            }
        }
    }

    // use deltaT to update

    Real32 oldAnimT = getAnimTime();
    Real32 newAnimT = getAnimTime();

    if(getForward() == true)
    {
        newAnimT += getTimeScale() * deltaT;
    }
    else
    {
        newAnimT -= getTimeScale() * deltaT;
    }

    if(getLoop() == true)
    {
        newAnimT = osgMod<Real64>(newAnimT, length);
        
        while(newAnimT < 0.f)
            newAnimT += length;

        setAnimTime(newAnimT         );
        setFraction(newAnimT / length);

        if(getIsActive() == false)
            setIsActive(true);
    }
    else
    {
        if(newAnimT < 0.f)
        {
            if(getIsActive() == true)
            {
                SLOG << "ATS: start >= stop, newAnimT < 0";

                setAnimTime(0.f);
                setFraction(0.f);

                // only deactivate the second time newAnimT < 0.f
                // to propagate the final state
                if(oldAnimT <= 0.f)
                {
                    PLOG << ", deactivating";

                    setIsActive(false);
                }

                PLOG << std::endl;
            }
        }
        else if(newAnimT > length)
        {
            if(getIsActive() == true)
            {
                SLOG << "ATS: start >= stop, newAnimT > length";

                setAnimTime(length);
                setFraction(1.f   );

                // only deactivate the second time newAnimT > length
                // to propagate the final state
                if(oldAnimT >= length)
                {
                    PLOG << ", deactivating";

                    setIsActive(false);
                }

                PLOG << std::endl;
            }
        }
        else
        {
            setAnimTime(newAnimT         );
            setFraction(newAnimT / length);

            if(getIsActive() == false)
                setIsActive(true);
        }
    }
}

OSG_END_NAMESPACE
