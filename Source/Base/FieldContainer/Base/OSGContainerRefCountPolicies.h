/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *              Copyright (C) 2010 by the OpenSG Forum                       *
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

#ifndef _OSGCONTAINERREFCOUNTPOLICIES_H_
#define _OSGCONTAINERREFCOUNTPOLICIES_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGContainerRefCountPoliciesFwd.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING RecordedRefCountPolicy
{
    static const bool NotCounting = false;

    static inline void addRef(FieldContainer * const pObject);
    static inline void subRef(FieldContainer * const pObject);

    template <class DestT, class SourceT>
    static inline void setRefd(DestT   *&pDest, SourceT *pSource);

    template <class ObjT>
    static inline ObjT *validate(ObjT *pObject);

    template <class ObjT>
    static inline ObjT &dereference(ObjT *pObject);

    template <class DestT, class SourceT>
    static inline void convertTransitPtr(DestT *&pDest, SourceT *&pSource);
};


/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING UnrecordedRefCountPolicy
{
    static const bool NotCounting = false;

    static inline void addRef(FieldContainer * const pObject);
    static inline void subRef(FieldContainer * const pObject);

    template <class DestT, class SourceT>
    static inline void setRefd(DestT   *&pDest, SourceT *pSource);

    template <class ObjT>
    static inline ObjT *validate(ObjT *pObject);

    template <class ObjT>
    static inline ObjT &dereference(ObjT *pObject);

    template <class DestT, class SourceT>
    static inline void convertTransitPtr(DestT *&pDest, SourceT *&pSource);
};


/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING WeakRefCountPolicy
{
    static const bool NotCounting = false;

    static inline void addRef(FieldContainer * const pObject);
    static inline void subRef(FieldContainer * const pObject);

    template <class DestT, class SourceT>
    static inline void setRefd(DestT   *&pDest, SourceT *pSource);

    template <class ObjT>
    static inline ObjT *validate(ObjT *pObject);

    template <class ObjT>
    static inline ObjT &dereference(ObjT *pObject);

    template <class DestT, class SourceT>
    static inline void convertTransitPtr(DestT *&pDest, SourceT *&pSource);
};

OSG_END_NAMESPACE

#include "OSGContainerRefCountPolicies.inl"

#endif // _OSGCONTAINERREFCOUNTPOLICIES_H_
