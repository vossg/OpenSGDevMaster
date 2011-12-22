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
#define _OSGATTACHMENTMAPFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGContainerForwards.h"

#include "map"

OSG_BEGIN_NAMESPACE

class Attachment;

/*! \ingroup GrpBaseFieldContainerFields
 */

typedef std::map<UInt32, Attachment *>  AttachmentMap;

/*! \ingroup GrpBaseFieldContainerFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<AttachmentMap> : 
    public FieldTraitsTemplateBase<AttachmentMap>
{
  private:

    static  DataType                                 _type;

  public:

    typedef FieldTraits<AttachmentMap>  Self;


    enum             { Convertible = Self::NotConvertible                  };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) 
    {
        return "SFAttachmentPtrMap"; 
    }

    static const Char8    *getMName     (void)
    {
        return "MFAttachmentPtrMap"; 
    }
    
    static SizeT  getBinSize(const AttachmentMap &aMap);

    static SizeT  getBinSize(const AttachmentMap *aMaps,
                                   SizeT          numObjects)
    {
        SizeT size = 0;

        // defaut: individual field sizes
        for(SizeT i = 0; i < numObjects; ++i)
        {
            size += getBinSize(aMaps[i]);
        }

        return size;
    }
    
    static void copyToBin(      BinaryDataHandler &pMem,
                          const AttachmentMap     &aMap );
    
    static void copyToBin(      BinaryDataHandler &pMem,
                          const AttachmentMap     *aMaps,
                                SizeT              numObjects)
    {
        for(SizeT i = 0; i < numObjects; ++i)
        {
            copyToBin(pMem, aMaps[i]);
        }
    }
    
    static void copyFromBin(BinaryDataHandler &pMem,
                            AttachmentMap     &aMap );

    static void copyFromBin(BinaryDataHandler &pMem,
                            AttachmentMap     *aMaps,
                            SizeT              numObjects)
    {
        for(SizeT i = 0; i < numObjects; ++i)
        {
            copyFromBin(pMem, aMaps[i]);
        }
    }
};

OSG_END_NAMESPACE

#endif /* _OSGATTACHMENTMAPFIELDTRAITS_H_ */
