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

#include "OSGVRMLCoordinateInterpolator.h"
#include "OSGInterpolationHelper.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVRMLCoordinateInterpolatorBase.cpp file.
// To modify it, please change the .fcd file
// (OSGVRMLCoordinateInterpolator.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VRMLCoordinateInterpolator::initMethod(InitPhase ePhase)
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

VRMLCoordinateInterpolator::VRMLCoordinateInterpolator(void) :
    Inherited()
{
}

VRMLCoordinateInterpolator::VRMLCoordinateInterpolator(
    const VRMLCoordinateInterpolator &source) :

    Inherited(source)
{
}

VRMLCoordinateInterpolator::~VRMLCoordinateInterpolator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VRMLCoordinateInterpolator::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    if(0x0000 != (whichField & ResortIndexFieldMask))
    {
        fprintf(stderr, "resort triggert\n");        

        SizeT uiNumRes = _mfKeyValue.size() / _mfKey.size();

        if(uiNumRes == _mfResortIndex.size())
        {
            InterpolationHelper<MFReal32, 
                                MFPnt3f, 
                                MFPnt3f>::resortKeyValues(
                                    _mfKey.size(),
                                     uiNumRes,
                                    *(this->editMFKeyValue()),
                                    _mfResortIndex);

            InterpolationHelper<MFReal32, 
                                MFPnt3f, 
                                MFPnt3f>::interpolate(  
                                    _sfInValue.getValue(),
                                    _mfKey,
                                    _mfKeyValue,
                                    *(this->editMFOutValue()));
        }
        else
        {
            fprintf(stderr, 
                    "interpol resort : sizes don't match %"PRISize" | %d\n",
                    uiNumRes, _mfResortIndex.size());
        }
    }

    if(0x0000 != (whichField & InValueFieldMask))
    {
        InterpolationHelper<MFReal32, 
                            MFPnt3f, 
                            MFPnt3f>::interpolate(  
                                  _sfInValue.getValue(),
                                  _mfKey,
                                  _mfKeyValue,
                                *(this->editMFOutValue()));
    }

    Inherited::changed(whichField, origin, details);
}

void VRMLCoordinateInterpolator::dump(      UInt32    ,
                                      const BitVector ) const
{
    SLOG << "Dump VRMLCoordinateInterpolator NI" << std::endl;
}

void VRMLCoordinateInterpolator::evaluate(void)
{
    InterpolationHelper<MFReal32, MFPnt3f, MFPnt3f>::interpolate(
        _sfInValue.getValue(),
        _mfKey,
        _mfKeyValue,
        *(this->editMFOutValue()));
}

OSG_END_NAMESPACE
