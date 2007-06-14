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

#ifndef _OSGTYPEBASEPREDICATES_H_
#define _OSGTYPEBASEPREDICATES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"

#include <algorithm>
#include <functional>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward declarations
//---------------------------------------------------------------------------

class TypeBase;

//---------------------------------------------------------------------------
//  Namespace
//---------------------------------------------------------------------------

namespace TypePredicates
{

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

    class OSG_BASE_DLLMAPPING IsBaseOf
    {
    public:
        /*! Standard library compatibility typedef */
        typedef const TypeBase* argument_type;

        /*! Standard library compatibility typedef */
        typedef       bool      result_type;

        explicit IsBaseOf(const TypeBase& derivType);

        bool operator()(const TypeBase* pTestType) const;

    private:
        const TypeBase& _derivType;
    };

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

    class OSG_BASE_DLLMAPPING IsDerivedFrom
    {
    public:
        /*! Standard library compatibility typedef */
        typedef const TypeBase* argument_type;

        /*! Standard library compatibility typedef */
        typedef       bool      result_type;

        explicit IsDerivedFrom(const TypeBase& baseType);

        bool operator()(const TypeBase* pTestType) const;

    private:
        const TypeBase& _baseType;
    };

//---------------------------------------------------------------------------
//  Functions
//---------------------------------------------------------------------------

    template <class InIteratorTypeT>
    inline bool
    typeDerivedFrom   (      InIteratorTypeT  begin, InIteratorTypeT  end,
                       const TypeBase        &type  );

    template <class InIteratorTypeT>
    inline bool
    typeDerivedFromAll(      InIteratorTypeT  begin, InIteratorTypeT  end,
                       const TypeBase        &type  );

    template <class InIteratorTypeT>
    inline bool
    typeBaseOf        (      InIteratorTypeT  begin, InIteratorTypeT  end,
                       const TypeBase        &type  );

    template <class InIteratorTypeT>
    inline bool
    typeBaseOfAll     (      InIteratorTypeT  begin, InIteratorTypeT  end,
                       const TypeBase        &type  );

} // namespace TypePredicates

OSG_END_NAMESPACE

#include "OSGTypeBasePredicates.inl"

#endif /* _OSGTYPEBASEPREDICATES_H_ */
