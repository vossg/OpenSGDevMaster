/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#ifndef _OSGFIELDCONTAINERATTACHMENTFIELDTRAITS_H_
#define _OSGFIELDCONTAINERATTACHMENTFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerFieldTraits.h"
#include "OSGDataType.h"

#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file 
    \ingroup 
    \ingroup 
*/
#endif

/*! \ingroup 
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<FieldContainerAttachmentPtr>
    : public FieldTraitsFCPtrBase<FieldContainerAttachmentPtr>
{
  private:

    static  DataType                                  _type;

  public:

    typedef FieldTraits<FieldContainerAttachmentPtr>  Self;


    enum             { Convertible = Self::NotConvertible              };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName(void);
};


template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getSName<RecordedRefCounts>(void)
{
    return "SFFieldContainerAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getSName<UnrecordedRefCounts>(void)
{
    return "SFUnrecFieldContainerAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getSName<WeakRefCounts>(void)
{
    return "SFWeakFieldContainerAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getSName<NoRefCounts>(void)
{
    return "SFUnrefdFieldContainerAttachmentPtr"; 
}



template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0               >::getMName<RecordedRefCounts>(void)
{
    return "MFFieldContainerAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getMName<UnrecordedRefCounts>(void)
{
    return "MFUnrecFieldContainerAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getMName<WeakRefCounts>(void)
{
    return "MFWeakFieldContainerAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainerAttachmentPtr, 
                         0                >::getMName<NoRefCounts>(void)
{
    return "MFUnrefdFieldContainerAttachmentPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<FieldContainerAttachmentPtr>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERATTACHMENTFIELDTRAITS_H_ */
