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

#include "OSGResolutionDisplayFilter.h"
#include "OSGDisplayFilterStageData.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGResolutionDisplayFilterBase.cpp file.
// To modify it, please change the .fcd file (OSGResolutionDisplayFilter.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ResolutionDisplayFilter::initMethod(InitPhase ePhase)
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

ResolutionDisplayFilter::ResolutionDisplayFilter(void) :
    Inherited()
{
}

ResolutionDisplayFilter::ResolutionDisplayFilter(
    const ResolutionDisplayFilter &source) :

    Inherited(source)
{
}

ResolutionDisplayFilter::~ResolutionDisplayFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ResolutionDisplayFilter::changed(ConstFieldMaskArg whichField, 
                                      UInt32            origin,
                                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & DownScaleFieldMask))
    {
        if(getDownScale() < 0.f)
            this->setDownScale(0.f);

        if(getDownScale() > 1.f)
            this->setDownScale(1.f);
    }
}

void ResolutionDisplayFilter::dump(      UInt32    ,
                                   const BitVector ) const
{
    SLOG << "Dump ResolutionDisplayFilter NI" << std::endl;
}

void ResolutionDisplayFilter::process(DisplayFilterStageData *pData)
{
}

OSG_END_NAMESPACE
