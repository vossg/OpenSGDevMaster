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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGVoidPAttachments.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include "OSGBaseTypes.h"
#include "OSGSimpleAttachment.h"
#include "OSGSysSFields.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
    \hideinhierarchy
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
        return "FieldContainerAttachment";    
    }

    static InitContainerF     getInitMethod(void) { return NULL;  }
};

/*! \ingroup GrpSystemFieldContainer
 */

typedef SimpleAttachment<VoidPAttachmentDesc> VoidP;

/*! \ingroup GrpSystemFieldContainer
 */

typedef VoidP::ObjPtr VoidPPtr;

#ifdef WIN32
template <> OSG_SYSTEM_DLLMAPPING
SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getType(void);

template <> OSG_SYSTEM_DLLMAPPING
const SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
   SimpleAttachment<VoidPAttachmentDesc>::getType(void) const;

template <> OSG_SYSTEM_DLLMAPPING
SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getClassType(void);
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEM_DLLMAPPING
void *getVoidP(AttachmentContainerPtrConstArg  container);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEM_DLLMAPPING
void  setVoidP(AttachmentContainerPtrConstArg  container, 
               void                           *pData,
               bool                            bInternal = false);

OSG_END_NAMESPACE

#endif /* _OSGNAMEATTACHMENT_H_ */
