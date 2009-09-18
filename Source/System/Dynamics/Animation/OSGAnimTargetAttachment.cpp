/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGAnimTargetAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimTargetAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimTargetAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimTargetAttachment::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnimTargetAttachment::AnimTargetAttachment(void) :
    Inherited()
{
}

AnimTargetAttachment::AnimTargetAttachment(const AnimTargetAttachment &source) :
    Inherited(source)
{
}

AnimTargetAttachment::~AnimTargetAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimTargetAttachment::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AnimTargetAttachment::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimTargetAttachment NI" << std::endl;
}

/*---------------------------------------------------------------------------*\
 * Free Functions                                                            *
\*---------------------------------------------------------------------------*/

AnimTargetAttachment *getTargetAtt(AttachmentContainer *container)
{
    if(container == NULL)
        return NULL;

    Attachment *att = container->findAttachment(
        AnimTargetAttachment::getClassType().getGroupId());

    if(att == NULL)
        return NULL;

    return dynamic_cast<AnimTargetAttachment *>(att);
}

/*! Obtains the target id of \a container and stores it in \a targetId.
    Returns true if succesful, false otherwise (including errors), in
    that case targetId is not modified.
 */
bool getTargetId(AttachmentContainer *container, std::string &targetId)
{
    if(container == NULL)
        return false;

    Attachment *att = container->findAttachment(
        AnimTargetAttachment::getClassType().getGroupId());

    if(att == NULL)
        return false;

    AnimTargetAttachment *targetAtt = dynamic_cast<AnimTargetAttachment *>(att);

    if(targetAtt == NULL)
        return false;

    targetId = targetAtt->getTargetId();

    return true;
}

/*! Sets the target id of \a container to \a targetId. If necessary a
    AnimTargetAttachment is created otherwise the value of an existing
    attachment is modified.
    Returns true if a new attachment was created, false otherwise (including
    errors).
 */
bool setTargetId(AttachmentContainer *container, const std::string &targetId)
{
    bool retVal = false;

    if(container == NULL)
    {
        SWARNING << "setTargetId: container is NULL." << std::endl;
        return false;
    }

    AnimTargetAttachmentUnrecPtr  targetAtt = NULL;
    Attachment                   *att       =
        container->findAttachment(
            AnimTargetAttachment::getClassType().getGroupId());

    if(att == NULL)
    {
        targetAtt = AnimTargetAttachment::createDependent(
            container->getFieldFlags()->_bNamespaceMask);

        container->addAttachment(targetAtt);

        retVal = true;
    }
    else
    {
        targetAtt = dynamic_cast<AnimTargetAttachment *>(att);

        if(targetAtt == NULL)
        {
            SWARNING << "setTargetId: AnimTargetAttachment has wrong type."
                     << std::endl;
            return false;
        }
    }

    targetAtt->setTargetId(targetId);

    return retVal;
}

OSG_END_NAMESPACE
