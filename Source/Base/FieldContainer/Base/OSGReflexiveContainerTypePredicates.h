/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *              Copyright (C) 2006 by the OpenSG Forum                       *
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

#ifndef _OSGREFLEXIVECONTAINERTYPEPREDICATES_H_
#define _OSGREFLEXIVECONTAINERTYPEPREDICATES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"
#include "OSGBaseTypes.h"

#include <algorithm>
#include <vector>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward declarations
//---------------------------------------------------------------------------

class ReflexiveContainerType;

//---------------------------------------------------------------------------
//  Namespace
//---------------------------------------------------------------------------

namespace TypePredicates
{

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

    /*! \ingroup GrpBaseBaseTypeSystem
        \ingroup GrpBaseFieldContainerHelper
        \nohierarchy
     */
    class OSG_BASE_DLLMAPPING IsSameGroupIdAs
    {
      public:
        /*! Standard library compatibility typedef */
        typedef UInt16 argument_type;

        /*! Standard library compatibility typedef */
        typedef bool   result_type;

        explicit IsSameGroupIdAs(const UInt16                  groupId);
        explicit IsSameGroupIdAs(const ReflexiveContainerType& type   );

        bool operator()(const UInt16 testGroupId);

      private:
        UInt16 _groupId;
    };

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

    /*! \ingroup GrpBaseBaseTypeSystem
        \ingroup GrpBaseFieldContainerHelper
        \nohierarchy
     */
    class OSG_BASE_DLLMAPPING IsSameGroupAs
    {
      public:
        /*! Standard library compatibility typedef */
        typedef const ReflexiveContainerType* argument_type;

        /*! Standard library compatibility typedef */
        typedef       bool                    result_type;

        explicit IsSameGroupAs(const UInt16                  groupId);
        explicit IsSameGroupAs(const ReflexiveContainerType& type   );

        bool operator()(const ReflexiveContainerType *pTestType);

      private:
        UInt16 _groupId;
    };

//---------------------------------------------------------------------------
//  Functions
//---------------------------------------------------------------------------

    /*! \ingroup GrpBaseBaseTypeSystem
     */
    template <class InIteratorTypeT> inline 
    bool typeInGroups(      InIteratorTypeT              begin, 
                            InIteratorTypeT              end,
                      const OSG::ReflexiveContainerType &type   );

    /*! \ingroup GrpBaseBaseTypeSystem
     */
    template <class InIteratorTypeT> inline 
    bool typeInGroupIds(      InIteratorTypeT              begin, 
                              InIteratorTypeT              end,
                        const OSG::ReflexiveContainerType &type );

} // namespace TypePredicates

OSG_END_NAMESPACE

#include "OSGReflexiveContainerTypePredicates.inl"

#endif /* _OSGREFLEXIVECONTAINERTYPEPREDICATES_H_ */
