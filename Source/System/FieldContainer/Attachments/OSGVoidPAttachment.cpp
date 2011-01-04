/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGAttachmentContainer.h"
#include "OSGVoidPAttachment.h"

OSG_BEGIN_NAMESPACE

template <>
SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getType(void)
{
    return _type;
}

template <>
const SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getType(void) const
{
    return _type;
}

template <>
SimpleAttachment<VoidPAttachmentDesc>::TypeObject &
    SimpleAttachment<VoidPAttachmentDesc>::getClassType(void)
{
    return _type;
}

OSG_SIMPLEATTACHMENT_INST(VoidPAttachmentDesc);


/*-------------------------------------------------------------------------*/
/*                   Name Attachment Utility Functions                     */

/*! 
  Return the void * attached to the container, NULL if none attached or
  container is NULL.
 */

void *getVoidP(AttachmentContainer * const pContainer)
{
    if(pContainer == NULL)
        return NULL;
   
    // Get attachment pointer
    Attachment *att = 
        pContainer->findAttachment(
            VoidPAttachment::getClassType().getGroupId());

    if(att == NULL)
        return NULL;
   
    // Cast to name pointer                           

    VoidPAttachment *voidP = dynamic_cast<VoidPAttachment *>(att);

    if(voidP == NULL)
        return NULL;
   
    return voidP->getFieldPtr()->getValue();
}


/*! Set the name attached to the container. If the container doesn't have a
    name attachement yet one is created. 
 */

void setVoidP(AttachmentContainer * const  pContainer, 
              void                *        pData,
              bool                         bInternal)
{
    if(pContainer == NULL)
    {
        FFATAL(("setVoidP: no container?!?"));
        return;
    }
   
    // Get attachment pointer

    VoidPAttachmentUnrecPtr  voidP = NULL;
    Attachment              *att   = 
        pContainer->findAttachment(
            VoidPAttachment::getClassType().getGroupId());
    
    if(att == NULL)
    {
        voidP = VoidPAttachment::create();

        pContainer->addAttachment(voidP);
    }
    else
    {   
        voidP = dynamic_cast<VoidPAttachment *>(att);

        if(voidP == NULL)
        {
            FFATAL(("setVoidP: VoidP Attachment is not castable to Name?!?"));
            return;
        }
    }
     
    voidP->editFieldPtr()->setValue(pData);
    voidP->setInternal(bInternal);
}

OSG_END_NAMESPACE
