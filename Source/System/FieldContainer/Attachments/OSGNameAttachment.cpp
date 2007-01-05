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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSimpleAttachments.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#define OSG_COMPILESIMPLEATTACHMENTSINST

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGAttachmentContainer.h"
#include "OSGNameAttachment.h"

#include "OSGSimpleAttachment.ins"

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



/*-------------------------------------------------------------------------*/
/*                   Name Attachment Utility Functions                     */

/*! 
  Return the name attached to the container, NULL if none attached or
  container is NULL.
 */

const Char8 *getName(AttachmentContainerPtrConstArg pContainer)
{
    if(pContainer == NullFC)
        return NULL;
   
    // Get attachment pointer
    FieldContainerAttachmentPtr att = 
        pContainer->findAttachment(Name::getClassType().getGroupId());

    if(att == NullFC)
        return NULL;
   
    // Cast to name pointer                           

    NamePtr name = cast_dynamic<NamePtr>(att);

    if(name == NullFC)
        return NULL;
   
    return name->getFieldPtr()->getValue().c_str();
}

/*! Set the name attached to the container. If the container doesn't have a
    name attachement yet one is created. 
 */

void setName(      AttachmentContainerPtrConstArg  pContainer, 
             const std::string                    &namestring)
{
    if(pContainer == NullFC)
    {
        FFATAL(("setName: no container?!?"));
        return;
    }
   
    // Get attachment pointer

    NamePtr                     name = NullFC;
    FieldContainerAttachmentPtr att  = 
        pContainer->findAttachment(Name::getClassType().getGroupId());
    
    if(att == NullFC)
    {
        name = Name::create();

        pContainer->addAttachment(name);
    }
    else
    {   
        name = cast_dynamic<NamePtr>(att);

        if(name == NullFC)
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

void setName(AttachmentContainerPtrConstArg pContainer, const Char8 *name)
{
    if(name == NULL)
    {
        FieldContainerAttachmentPtr att = 
            pContainer->findAttachment(Name::getClassType().getGroupId());
 
        if(att != NullFC)
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
