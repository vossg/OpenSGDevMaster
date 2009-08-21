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

#include "OSGVRMLPositionInterpolator.h"
#include "OSGInterpolationHelper.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVRMLPositionInterpolatorBase.cpp file.
// To modify it, please change the .fcd file (OSGVRMLPositionInterpolator.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VRMLPositionInterpolator::initMethod(InitPhase ePhase)
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

VRMLPositionInterpolator::VRMLPositionInterpolator(void) : 
    Inherited()
{
}

VRMLPositionInterpolator::VRMLPositionInterpolator(
    const VRMLPositionInterpolator &source) : 
    
    Inherited(source)
{
}

VRMLPositionInterpolator::~VRMLPositionInterpolator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VRMLPositionInterpolator::changed(ConstFieldMaskArg whichField, 
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
                                MFVec3f, 
                                SFVec3f>::resortKeyValues(
                                    _mfKey.size(),
                                     uiNumRes,
                                    *(this->editMFKeyValue()),
                                    _mfResortIndex);

            InterpolationHelper<MFReal32, 
                                MFVec3f, 
                                SFVec3f>::interpolate(  
                                    _sfInValue.getValue(),
                                    _mfKey,
                                    _mfKeyValue,
                                    *(this->editSFOutValue()));
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
                            MFVec3f, 
                            SFVec3f>::interpolate(  
                                  _sfInValue.getValue(),
                                  _mfKey,
                                  _mfKeyValue,
                                *(this->editSFOutValue()));
    }

    Inherited::changed(whichField, origin, details);
}

void VRMLPositionInterpolator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VRMLPositionInterpolator NI" << std::endl;
}

void VRMLPositionInterpolator::evaluate(void)
{
    InterpolationHelper<MFReal32, MFVec3f, SFVec3f>::interpolate(
        _sfInValue.getValue(),
        _mfKey,
        _mfKeyValue,
        *(this->editSFOutValue()));
}

OSG_END_NAMESPACE
