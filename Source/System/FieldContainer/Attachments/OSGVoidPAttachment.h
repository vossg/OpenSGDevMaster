/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2005 by the OpenSG Forum                          *
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

#ifndef _OSGVOIDPATTACHMENT_H_
#define _OSGVOIDPATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGSimpleAttachment.h"
#include "OSGSysSFields.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerAttachments
    \nohierarchy
 */

struct VoidPAttachmentDesc
{
    typedef SFVoidP           FieldTypeT;

    static const Char8         *getTypeName  (void) 
    {
        return "VoidPAttachment";          
    }

    static const Char8         *getFieldName (void) 
    {
        return "data";          
    }

    static const Char8         *getGroupName (void) 
    { 
        return "voidp";          
    }

    static const Char8         *getParentTypeName(void) 
    {
        return "Attachment";    
    }

    static InitContainerF     getInitMethod(void) { return NULL;  }
};


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemFieldContainerAttachments
 */
typedef SimpleAttachment<VoidPAttachmentDesc> VoidPAttachment;
#else
/*! \ingroup GrpSystemFieldContainerAttachments
 */
class VoidPAttachment : public SimpleAttachment<VoidPAttachmentDesc> {};
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
OSG_GEN_CONTAINERPTR(VoidPAttachment)  
#endif

#ifdef WIN32
/*! \ingroup GrpSystemFieldContainerAttachments
 */

template <> OSG_SYSTEM_DLLMAPPING
SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getType(void);

/*! \ingroup GrpSystemFieldContainerAttachments
 */

template <> OSG_SYSTEM_DLLMAPPING
const SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
   SimpleAttachment<VoidPAttachmentDesc>::getType(void) const;

/*! \ingroup GrpSystemFieldContainerAttachments
 */

template <> OSG_SYSTEM_DLLMAPPING
SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getClassType(void);
#endif


/*! \ingroup GrpSystemFieldContainerAttachments
 */

OSG_SYSTEM_DLLMAPPING
void *getVoidP(AttachmentContainer * const container);

/*! \ingroup GrpSystemFieldContainerAttachments
 */

OSG_SYSTEM_DLLMAPPING
void  setVoidP(AttachmentContainer * const container, 
               void                *       pData,
               bool                        bInternal = false);

OSG_END_NAMESPACE

#endif /* _OSGNAMEATTACHMENT_H_ */
