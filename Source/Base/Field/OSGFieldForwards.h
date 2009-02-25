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

#ifndef _OSGFIELDFORWARDS_H_
#define _OSGFIELDFORWARDS_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/function.hpp>

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGBinaryDataHandler.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

class Field;

template<class ValueT, Int32 iNamespace>
class SField;

template<class ValueT, Int32 iNamespace, class AllocT>
class MField;

template<class    ValueT, 
         typename RefCountPolicy,
         Int32    iNamespace>
class PointerSField;

template<class    ValueT, 
         typename RefCountPolicy,
         Int32    iNamespace>
class PointerMField;

template<class    ValueT, 
         typename RefCountPolicy,
         Int32    iNamespace>
class ParentPointerSField;

template<class    ValueT, 
         typename RefCountPolicy,
         Int32    iNamespace>
class ParentPointerMField;

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    >
class ChildPointerSField;

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    >
class ChildPointerMField;

class FieldDescriptionBase;
class ReflexiveContainer;


#if 0
#ifdef FDESC_USE_BOOST
typedef boost::function<Field *(ReflexiveContainer *)> FieldEditMethod;
typedef boost::function<const Field *(const ReflexiveContainer *)> FieldGetMethod;
#else
typedef       Field *(ReflexiveContainer::*FieldEditMethod     )(void  );
typedef const Field *(ReflexiveContainer::*FieldGetMethod      )(void  ) const;
#endif

#ifdef FDESC_USE_BOOST
typedef boost::function<
          Field *(ReflexiveContainer *, int)>             FieldIndexEditMethod;
typedef boost::function<
          const Field *(const ReflexiveContainer *, int)> FieldIndexGetMethod;
#else
typedef       Field *(ReflexiveContainer::*FieldIndexEditMethod)(UInt32);
typedef const Field *(ReflexiveContainer::*FieldIndexGetMethod )(UInt32) const;
#endif

typedef Field * (ReflexiveContainer::*FieldIndexAccessMethod)(UInt32);
#endif

struct NoRefCounts;

#endif //DOXYGEN_SHOULD_SKIP_THIS

OSG_END_NAMESPACE

#endif /* _OSGFIELDFORWARDS_H_ */
