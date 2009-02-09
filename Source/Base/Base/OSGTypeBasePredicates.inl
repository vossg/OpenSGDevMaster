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

/*! Tests if \a type is derived from any of the types in the sequence
    specified by [\a begin, \a end). The sequence must consist of pointers
    to TypeBase objects (or a derived class), e.g.
    std::vector\<const FieldContainerType *\>.

    \param[in] begin Start of sequence.
    \param[in] end End of sequence.
    \param[in] type Type that is tested.
    \return true, if \a type is derived from any of the types in
        [\a begin, \a end), false otherwise.
 */
template <class InIteratorTypeT> inline 
bool TypePredicates::typeDerivedFrom(      InIteratorTypeT  begin,
                                           InIteratorTypeT  end,
                                     const TypeBase        &type  )
{
    return (std::find_if(begin, end,
                         TypePredicates::IsBaseOf(type)) != end);
}

/*! Tests if \a type is derived from all of the types in the sequence
    [\a begin, \a end). The sequence must consist of pointers to TypeBase
    objects (or derived types), e.g. std::vector\<const FieldContainerType*\>.

    \param[in] begin Start of sequence.
    \param[in] end End of sequence.
    \param[in] type Type that is tested.
    \return true, if \a type is derived from all of the types in
        [\a begin, \a end), false otherwise.
 */
template <class InIteratorTypeT> inline 
bool TypePredicates::typeDerivedFromAll(      InIteratorTypeT  begin,
                                              InIteratorTypeT  end,
                                        const TypeBase        &type  )
{
    return (std::find_if(begin, end,
                         std::not1(TypePredicates::IsBaseOf(type))) == end);
}

/*! Tests if \a type is a base type any of the types in the sequence
    specified by [\a begin, \a end). The sequence must consist of pointers
    to TypeBase objects (or a derived class), e.g.
    std::vector\<const FieldContainerType *\>.

    \param[in] begin Start of sequence.
    \param[in] end End of sequence.
    \param[in] type Type that is tested.
    \return true, if \a type is a base type any of the types in
        [\a begin, \a end), false otherwise.
 */
template <class InIteratorTypeT> inline 
bool TypePredicates::typeBaseOf(      InIteratorTypeT  begin,
                                      InIteratorTypeT  end,
                                const TypeBase        &type  )
{
    return (std::find_if(begin, end,
                         TypePredicates::IsDerivedFrom(type)) != end);
}

/*! Tests if \a type is a base type of all of the types in the sequence
    [\a begin, \a end). The sequence must consist of pointers to TypeBase
    objects (or derived types), e.g. std::vector\<const FieldContainerType*\>.

    \param[in] begin Start of sequence.
    \param[in] end End of sequence.
    \param[in] type Type that is tested.
    \return true, if \a type is a base type of all of the types in
        [\a begin, \a end), false otherwise.
 */
template <class InIteratorTypeT> inline 
bool TypePredicates::typeBaseOfAll(      InIteratorTypeT  begin,
                                         InIteratorTypeT  end,
                                   const TypeBase        &type  )
{
    return (
        std::find_if(begin, end,
                     std::not1(TypePredicates::IsDerivedFrom(type))) == end);
}

OSG_END_NAMESPACE
