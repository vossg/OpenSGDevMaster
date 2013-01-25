/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGCONCEPTPROPERTYCHECKS_H_
#define _OSGCONCEPTPROPERTYCHECKS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseHelper
 */

template <class TypeT>
void osgSinkUnusedWarning(TypeT) { }

/*! \ingroup GrpBaseBaseHelper
 */

#define OSG_PROPERTY_DECL(OSGPROP)                              \
    enum OSG##OSGPROP##Prop { osg##OSGPROP##Prop }

/*! \ingroup GrpBaseBaseHelper
 */

#define OSG_PROPERTY_SPEC(OSGPROPERTYNAMESPACE, OSGPROP)        \
template<class T1>                                              \
struct _OSG_##OSGPROP##_Property_Spec                           \
{                                                               \
    static void _OSG_##OSGPROP##_Property_violation(T1 t1)      \
    {                                                           \
        OSGPROPERTYNAMESPACE::                                  \
           __OSG_##OSGPROP##_Property_violation(t1);            \
    }                                                           \
}

/*! \ingroup GrpBaseBaseHelper
 */

#define OSG_PROPERTY_VIOLATION(OSGPROP)                                  \
template<class T1>                                                       \
static void __OSG_##OSGPROP##_Property_violation(T1)                     \
{                                                                        \
    while(0)                                                             \
    {                                                                    \
        typename T1::OSG##OSGPROP##Prop v1 = T1::osg##OSGPROP##Prop;     \
                                                                         \
        osgSinkUnusedWarning(v1);                                        \
    }                                                                    \
}

#ifdef OSG_NO_CONCEPT_CHECKS
#define OSG_PROPERTY_REQUIREMENT(OSGCLASS, OSGPROP)
#else

/*! \ingroup GrpBaseBaseHelper
 */

#define OSG_PROPERTY_REQUIREMENT(OSGCLASS, OSGPROP)                      \
typedef void (* _OSG##OSGPROP##PropReqDummyFuncFor##OSGCLASS)(OSGCLASS); \
                                                                         \
template<_OSG##OSGPROP##PropReqDummyFuncFor##OSGCLASS FuncTypeT>         \
struct _OSG##OSGPROP##PropReqDummyStructFor##OSGCLASS                    \
{                                                                        \
};                                                                       \
                                                                         \
static _OSG##OSGPROP##PropReqDummyStructFor##OSGCLASS<                   \
    _OSG_##OSGPROP##_Property_Spec<OSGCLASS>::                           \
        _OSG_##OSGPROP##_Property_violation>                             \
            _OSG##OSGPROP##PropReqDummyStructInstFor##OSGCLASS
#endif

OSG_END_NAMESPACE

#endif /* _OSGCONCEPTPROPERTYCHECKS_H_ */
