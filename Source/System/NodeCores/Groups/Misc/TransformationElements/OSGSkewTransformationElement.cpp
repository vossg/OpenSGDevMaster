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

#include "OSGSkewTransformationElement.h"
#include "OSGMatrixUtility.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkewTransformationElementBase.cpp file.
// To modify it, please change the .fcd file
// (OSGSkewTransformationElement.fcd) and 
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkewTransformationElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SkewTransformationElement::calcMatrix(Matrix &result) const
{
    MatrixSkew(result, getRotationAxis(), getTranslationAxis(), getAngle());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkewTransformationElement::SkewTransformationElement(void) :
    Inherited()
{
}

SkewTransformationElement::SkewTransformationElement(
    const SkewTransformationElement &source) :

    Inherited(source)
{
}

SkewTransformationElement::~SkewTransformationElement(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkewTransformationElement::changed(ConstFieldMaskArg whichField, 
                                        UInt32            origin,
                                        BitVector         details   )
{
    Inherited::changed(whichField, origin, details);

    if(whichField & (RotationAxisFieldMask    | 
                     TranslationAxisFieldMask | 
                     AngleFieldMask           ))
    {
        updateParentTransform();
    }
}

void SkewTransformationElement::dump(      UInt32    ,
                                     const BitVector ) const
{
    SLOG << "Dump SkewTransformationElement NI" << std::endl;
}

OSG_END_NAMESPACE
