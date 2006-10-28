/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#include "OSGReflexiveContainerTypePredicates.h"
#include "OSGReflexiveContainerType.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------
/*! \class TypePredicates::IsSameGroupIdAs

    \brief A predicate to test if a group id is the same as that of a fixed type.
 */

/*! Constructor. Initializes the predicate with the \a groupId to compare
    against.

    \param[in] groupId Group id to compare against.
 */
TypePredicates::IsSameGroupIdAs::IsSameGroupIdAs(const UInt16 groupId)
    : _groupId(groupId)
{
}

/*! Constructor. Initializes the predicate with the group id of the given
    \a type.

    \param[in] type Group id of type is used to compare against.
 */
TypePredicates::IsSameGroupIdAs::IsSameGroupIdAs(
    const ReflexiveContainerType &type)
    : _groupId(type.getGroupId())
{
}

/*! Compare the given \a testGroupId against the one stored in the predicate.

    \param[in] testGroupId Group id to compare with the stored one.
    \return true, if both group ids are the same, false otherwise.
 */
bool
TypePredicates::IsSameGroupIdAs::operator()(const UInt16 testGroupId)
{
    return _groupId == testGroupId;
}

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class TypePredicates::IsSameGroupAs

    \brief A predicate to test if the group id of a type is the same as that of
    a fixed type.
 */

/*! Constructor. Initializes the predicate with the \a groupId to compare
    against.

    \param[in] groupId Group id to compare against.
 */
TypePredicates::IsSameGroupAs::IsSameGroupAs(const UInt16 groupId)
    : _groupId(groupId)
{
}

/*! Constructor. Initializes the predicate with the group id of the given
    \a type.

    \param[in] type Group id of type is used to compare against.
 */
TypePredicates::IsSameGroupAs::IsSameGroupAs(
    const ReflexiveContainerType &type)
    : _groupId(type.getGroupId())
{
}

/*! Compare the group id of \a pTestType against the one stored in the predicate.

    \param[in] pTestType Type whose Group id is compared with the stored one.
    \return true, if both group ids are the same, false otherwise.
 */
bool
TypePredicates::IsSameGroupAs::operator()(
    const ReflexiveContainerType *pTestType)
{
    return _groupId == pTestType->getGroupId();
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGREFLEXIVECONTAINERTYPEPREDICATES_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGREFLEXIVECONTAINERTYPEPREDICATES_INLINE_CVSID;
}
