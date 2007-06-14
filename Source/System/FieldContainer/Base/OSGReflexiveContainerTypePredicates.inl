/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2006 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE

/*! Tests if any of the types in the sequence [\a begin, \a end) is in the
    same group as \a type. The sequence elements must be of type
    <tt>const ReflexiveContainerType*</tt> (or a derived type, const is
    optional).

    \param[in] begin Start of sequence.
    \param[in] end End of sequence.
    \param[in] type Type object whose group id specifies the group to test.
    \return true, if any of the types in [\a begin, \a end) is in the same
        group as \a type, false otherwise.
 */
template <class InIteratorTypeT>
inline bool
TypePredicates::typeInGroups(      InIteratorTypeT         begin,
                                   InIteratorTypeT         end,
                             const ReflexiveContainerType &type   )
{
    return (std::find_if(begin, end,
                         TypePredicates::IsSameGroupAs(type)) != end);
}

/*! Tests if any of the group ids in the sequence [\a begin, \a end) is the
    same as the group id of \a type. The sequence elements must be of type
    <tt>UInt16</tt>.

    \param[in] begin Start of sequence.
    \param[in] end End of sequence.
    \param[in] type Type object whose group id specifies the group to test.
    \return true, if any of the group ids in [\a begin, \a end) is the same
        as the group id of \a type, false otherwise.
 */
template <class InIteratorTypeT>
inline bool
TypePredicates::typeInGroupIds(      InIteratorTypeT         begin,
                                     InIteratorTypeT         end,
                               const ReflexiveContainerType &type  )
{
    return (std::find_if(begin, end,
                         TypePredicates::IsSameGroupIdAs(type)) != end);
}

OSG_END_NAMESPACE
