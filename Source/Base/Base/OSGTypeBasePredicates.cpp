/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2006 by the OpenSG Forum                    *
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

#include "OSGTypeBasePredicates.h"
#include "OSGTypeBase.h"
#include "OSGTypeFactory.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::TypePredicates::IsBaseOf

    \brief A predicate to test if a type is a base type of a fixed type.

    Using the OpenSG type system, this predicate tests if an argument to
    its operator() is a base type of the type specified at construction time.
 */

/*! Constructor. Creates a new predicate that will test if a type is a
    base type of \a derivType.

    \param[in] derivType Type object agains which other types are tested.
 */
TypePredicates::IsBaseOf::IsBaseOf(const TypeBase &derivType)
    : _derivType(derivType)
{
}

/*! Tests if \a pTestType is a base type of the type specified upon
    construction. 

    \param[in] pTestType Type object that is tested.
    \return true, if \a testType is a base type of the type specified at
        construction time, false otherwise.
 */
bool TypePredicates::IsBaseOf::operator()(const TypeBase *pTestType) const
{
    return _derivType.isDerivedFrom(*pTestType);
}

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::TypePredicates::IsDerivedFrom

    \brief A predicate to test if a type is derived from of a fixed type.

    Using the OpenSG type system, this predicate tests if an argument to
    its operator() is a derived from the type specified at construction time.
 */

/*! Constructor. Creates a new predicate that will test if a type is a
    derived from \a baseType.

    \param[in] baseType Type object agains which other types are tested.
 */
TypePredicates::IsDerivedFrom::IsDerivedFrom(const TypeBase &baseType) :
    _baseType(baseType)
{
}

/*! Tests if \a pTestType is derived from the type specified upon construction.

    \param[in] pTestType Type object that is tested.
    \return true, if \a testType is derived from the type specified at
        construction time, false otherwise.
 */
bool TypePredicates::IsDerivedFrom::operator()(const TypeBase *pTestType) const
{
    return pTestType->isDerivedFrom(_baseType);
}

OSG_END_NAMESPACE
