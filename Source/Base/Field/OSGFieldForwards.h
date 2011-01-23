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

class GetFieldHandle;
class EditFieldHandle;

typedef boost::shared_ptr<GetFieldHandle > GetFieldHandlePtr;
typedef boost::shared_ptr<EditFieldHandle> EditFieldHandlePtr;

typedef EditFieldHandlePtr(ReflexiveContainer::*FieldEditMethod)(void  );
typedef GetFieldHandlePtr (ReflexiveContainer::*FieldGetMethod )(void) const;

typedef EditFieldHandlePtr(ReflexiveContainer::*FieldIndexEditMethod)(UInt32);
typedef GetFieldHandlePtr (ReflexiveContainer::*FieldIndexGetMethod )(
    UInt32) const;

/*! \ingroup GrpBaseFieldContainerBase
 */
typedef 
  EditFieldHandlePtr(OSG::ReflexiveContainer::*FieldEditMethodSig)(void);

/*! \ingroup GrpBaseFieldContainerBase
 */
typedef 
  GetFieldHandlePtr (OSG::ReflexiveContainer::*FieldGetMethodSig )(void) const;


/*! \ingroup GrpBaseFieldContainerBase
 */
typedef EditFieldHandlePtr (OSG::ReflexiveContainer::*FieldIndexEditMethodSig)(
    OSG::UInt32);

/*! \ingroup GrpBaseFieldContainerBase
 */
typedef GetFieldHandlePtr  (OSG::ReflexiveContainer::*FieldIndexGetMethodSig )(
    OSG::UInt32) const;

/*! \ingroup GrpBaseFieldContainerBase
 */
#ifdef FDESC_USE_BOOST
typedef boost::function<Field *(OSG::ReflexiveContainer *)> FieldEditMethod;
#else
typedef EditFieldHandlePtr (OSG::ReflexiveContainer::*FieldEditMethod)(void  );
#endif


/*! \ingroup GrpBaseFieldContainerBase
 */
#ifdef FDESC_USE_BOOST
typedef boost::function<
          const Field *(const OSG::ReflexiveContainer *)> FieldGetMethod;
#else
typedef GetFieldHandlePtr(OSG::ReflexiveContainer::*FieldGetMethod)(void) const;
#endif


/*! \ingroup GrpBaseFieldContainerBase
 */
#ifdef FDESC_USE_BOOST
typedef boost::function<
          Field *(OSG::ReflexiveContainer *, int)>        FieldIndexEditMethod;
#else
typedef EditFieldHandlePtr (OSG::ReflexiveContainer::*FieldIndexEditMethod)(
    OSG::UInt32);
#endif


/*! \ingroup GrpBaseFieldContainerBase
 */
#ifdef FDESC_USE_BOOST
typedef boost::function<
          const Field *(const OSG::ReflexiveContainer *, 
                              int                      )> FieldIndexGetMethod;
#else
typedef GetFieldHandlePtr (OSG::ReflexiveContainer::*FieldIndexGetMethod)(
    OSG::UInt32) const;
#endif

typedef boost::function<
    FieldDescriptionBase * (
        const Char8           *szFieldname,
              UInt32           uiFieldFlags,
              FieldEditMethod  fEditMethod,
              FieldGetMethod   fGetMethod) > FieldDescCreator;

typedef boost::function<
    FieldDescriptionBase * (
        const Char8               *szFieldname,
              UInt32               uiFieldFlags,
              FieldIndexEditMethod fEditMethod,
              FieldIndexGetMethod  fGetMethod ) > IndexedFieldDescCreator;

struct NoRefCounts;

#endif //DOXYGEN_SHOULD_SKIP_THIS

OSG_END_NAMESPACE

#endif /* _OSGFIELDFORWARDS_H_ */
