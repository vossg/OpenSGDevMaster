/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2010 by the OpenSG Forum                   *
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

#ifndef _OSGBASEREFCOUNTPOLICIES_H_
#define _OSGBASEREFCOUNTPOLICIES_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGBaseRefCountPoliciesFwd.h"
#include "OSGMemoryObject.h"

OSG_BEGIN_NAMESPACE

class FieldContainer;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMemory
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING NoRefCountPolicy
{
    static const bool NotCounting = true;

    template <class ObjT>
    static void addRef(ObjT           * const pObject);
    static void addRef(FieldContainer * const pObject);

    template <class ObjT>
    static void subRef(ObjT           * const pObject);
    static void subRef(FieldContainer * const pObject);

    template <class DestT, class SourceT>
    static void setRefd(DestT   *&pDest,
                        SourceT * pSource );

    template <class ObjT>
    static ObjT *validate(ObjT * const pObject);

    template <class ObjT>
    static ObjT &dereference(ObjT * const pObject);

    template <class DestT, class SourceT>
    static void convertTransitPtr(DestT *&pDest, SourceT *&pSource);
};

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMemory
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING MemObjRefCountPolicy
{
    static const bool NotCounting = false;

    template <class ObjT>
    static void addRef(ObjT         * const pObject);
    static void addRef(MemoryObject * const pObject);

    template <class ObjT>
    static void subRef(ObjT         * const pObject);
    static void subRef(MemoryObject * const pObject);

    template <class DestT, class SourceT>
    static void setRefd(DestT   *&pDest,
                        SourceT * pSource );

    template <class ObjT>
    static ObjT *validate(ObjT * const pObject);

    template <class ObjT>
    static ObjT &dereference(ObjT * const pObject);

    template <class DestT, class SourceT>
    static void convertTransitPtr(DestT *&pDest, SourceT *&pSource);
};

OSG_END_NAMESPACE

#include "OSGBaseRefCountPolicies.inl"

#endif // _OSGBASEREFCOUNTPOLICIES_H_
