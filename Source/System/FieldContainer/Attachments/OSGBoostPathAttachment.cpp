/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGConfig.h"

#include "OSGBoostPathAttachment.h"

#include <boost/filesystem/operations.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBoostPathAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGBoostPathAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BoostPathAttachment::initMethod(InitPhase ePhase)
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

BoostPathAttachment::BoostPathAttachment(void) :
    Inherited()
{
}

BoostPathAttachment::BoostPathAttachment(const BoostPathAttachment &source) :
    Inherited(source)
{
}

BoostPathAttachment::~BoostPathAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BoostPathAttachment::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BoostPathAttachment::dump(      UInt32    ,
                               const BitVector ) const
{
    SLOG << "Dump BoostPathAttachment NI" << std::endl;
}


const BoostPath *getBoostPath(const AttachmentContainer *pContainer)
{
    if(pContainer == NULL)
        return NULL;

    // Get attachment pointer
    Attachment *pAtt = 
        pContainer->findAttachment(
            BoostPathAttachment::getClassType().getGroupId());

    if(pAtt == NULL)
        return NULL;

    // Cast to name pointer                           
    BoostPathAttachment *pPathAttachment = 
        dynamic_cast<BoostPathAttachment *>(pAtt);

    if(pPathAttachment == NULL)
        return NULL;

    return &(pPathAttachment->getPath());
}

void setBoostPath(      AttachmentContainer *pContainer, 
                  const BoostPath            &oPath     )
{
    if(pContainer == NULL)
    {
        FFATAL(("setBoostPath: no container?!?\n"));
        return;
    }

    // Get attachment pointer

    Attachment *pAtt  = 
        pContainer->findAttachment(
            BoostPathAttachment::getClassType().getGroupId());

    if(pAtt != NULL)
    {
        pContainer->subAttachment(pAtt);
    }

    BoostPathAttachmentUnrecPtr pPathAttachment = BoostPathAttachment::create();

    pPathAttachment->setPath(oPath);   

    pContainer->addAttachment(pPathAttachment);
}

OSG_END_NAMESPACE
