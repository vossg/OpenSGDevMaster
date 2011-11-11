/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGRotationTransformationElement.h"
#include "OSGQuaternion.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGRotationTransformationElementBase.cpp file.
// To modify it, please change the .fcd file
// (OSGRotationTransformationElement.fcd) and 
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RotationTransformationElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RotationTransformationElement::calcMatrix(Matrix &result) const
{
    result.setTransform(Quaternion(getAxis(), osgDegree2Rad(getAngle())));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RotationTransformationElement::RotationTransformationElement(void) :
    Inherited()
{
}

RotationTransformationElement::RotationTransformationElement(
    const RotationTransformationElement &source) :

    Inherited(source)
{
}

RotationTransformationElement::~RotationTransformationElement(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RotationTransformationElement::changed(ConstFieldMaskArg whichField, 
                                            UInt32            origin,
                                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & (AxisFieldMask |
                     AngleFieldMask))
    {
        updateParentTransform();
    }
}

void RotationTransformationElement::dump(      UInt32    ,
                                         const BitVector ) const
{
    SLOG << "Dump RotationTransformationElement NI" << std::endl;
}

OSG_END_NAMESPACE
