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

#ifndef _OSGATTACHMENTMAPFIELDTRAITS_H_
#define _OSTATTACHMENTMAPFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGContainerForwards.h"

#include "map"

OSG_BEGIN_NAMESPACE

typedef std::map<UInt32, 
                 FieldBundleAttachmentP     >  FieldBundleAttachmentMap;
typedef std::map<UInt32, 
                 FieldContainerAttachmentPtr>  FieldContainerAttachmentMap;

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGBaseFieldTraits.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<FieldBundleAttachmentMap> : 
    public FieldTraitsTemplateBase<FieldBundleAttachmentMap>
{
    static  DataType                              _type;
    typedef FieldTraits<FieldBundleAttachmentMap>  Self;


    enum             { Convertible = Self::NotConvertible };

    static       DataType &getType      (void) 
    {
        return _type;             
    }

    static const Char8    *getSName     (void) 
    {
        return "SFBundeAttachmentMap"; 
    }

    static const Char8    *getMName     (void) 
    {
        return "MFBundleAttachmentMap"; 
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<BundleAttachmentMap> */
/*! \hideinhierarchy                               */
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<FieldContainerAttachmentMap> : 
    public FieldTraitsTemplateBase<FieldContainerAttachmentMap>
{
    static  DataType                                 _type;
    typedef FieldTraits<FieldContainerAttachmentMap>  Self;


    enum             { Convertible = Self::NotConvertible                  };

    static       DataType &getType      (void) { return _type;             }

    static const Char8    *getSName     (void) 
    {
        return "SFFieldContainerAttachmentPtrMap"; 
    }

    static const Char8    *getMName     (void)
    {
        return "MFFieldContainerAttachmentPtrMap"; 
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ContainerAttachmentMap> */
/*! \hideinhierarchy                               */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGATTACHMENTMAPFIELDTRAITS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTMAPFIELDTRAITS_H_ */
