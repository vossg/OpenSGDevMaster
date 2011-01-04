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
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

template <>
SimpleAttachment<NameAttachmentDesc>::TypeObject &
    SimpleAttachment<NameAttachmentDesc>::getType(void)
{
    return _type;
}

template <>
const SimpleAttachment<NameAttachmentDesc>::TypeObject &
    SimpleAttachment<NameAttachmentDesc>::getType(void) const
{
    return _type;
}

template <>
SimpleAttachment<NameAttachmentDesc>::TypeObject &
    SimpleAttachment<NameAttachmentDesc>::getClassType(void)
{
    return _type;
}

OSG_SIMPLEATTACHMENT_INST(NameAttachmentDesc);

/*-------------------------------------------------------------------------*/
/*                   Name Attachment Utility Functions                     */

/*! 
  Return the name attached to the container, NULL if none attached or
  container is NULL.
 */

const Char8 *getName(AttachmentContainer * const pContainer)
{
    if(pContainer == NULL)
        return NULL;
   
    // Get attachment pointer
    Attachment *att = 
        pContainer->findAttachment(Name::getClassType().getGroupId());

    if(att == NULL)
        return NULL;
   
    // Cast to name pointer                           

    Name *name = dynamic_cast<Name *>(att);

    if(name == NULL)
        return NULL;
   
    return name->getFieldPtr()->getValue().c_str();
}

/*! Set the name attached to the container. If the container doesn't have a
    name attachement yet one is created. 
 */

void setName(AttachmentContainer * const  pContainer, 
             std::string           const &namestring)
{
    if(pContainer == NULL)
    {
        FFATAL(("setName: no container?!?"));
        return;
    }
   
    // Get attachment pointer

    NameUnrecPtr  name = NULL;
    Attachment   *att  = 
        pContainer->findAttachment(Name::getClassType().getGroupId());
    
    if(att == NULL)
    {
        name = Name::createDependent(
            pContainer->getFieldFlags()->_bNamespaceMask);

        pContainer->addAttachment(name);
    }
    else
    {   
        name = dynamic_cast<Name *>(att);

        if(name == NULL)
        {
            FFATAL(("setName: Name Attachment is not castable to Name?!?"));
            return;
        }
    }
    
  
    name->editFieldPtr()->getValue().assign(namestring);   
}

/*! 
  Set the name attached to the container. If the container doesn't have 
  name attachement yet one is created. If the name is NULL, an attached
  name is removed.
 */

void setName(AttachmentContainer * const pContainer, const Char8 *name)
{
    if(name == NULL)
    {
        Attachment *att = 
            pContainer->findAttachment(Name::getClassType().getGroupId());
 
        if(att != NULL)
        {
            pContainer->subAttachment(att);
        }       
    }
    else
    {
        setName(pContainer, std::string(name));
    }
}

OSG_END_NAMESPACE
