/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include "OSGGL.h"

#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGFrameBufferAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGFrameBufferAttachment.fcd) and
// regenerate the base file.

/*
void FrameBufferAttachment::bind(Window *pWindow, 
                                 UInt32  index  )
{
}

void FrameBufferAttachment::deactivate(DrawActionBase *action, 
                                       UInt32          index )
{
}
*/

void FrameBufferAttachment::resize(UInt32 uiWidth, UInt32 uiHeight)
{
    if(getWidth() != uiWidth)
    {
        setWidth(uiWidth);
    }

    if(getHeight() != uiHeight)
    {
        setHeight(uiHeight);
    }
}

/*----------------------- constructors & destructors ----------------------*/

FrameBufferAttachment::FrameBufferAttachment(void) :
    Inherited()
{
}

FrameBufferAttachment::FrameBufferAttachment(
    const FrameBufferAttachment &source) :

    Inherited(source)
{
}

FrameBufferAttachment::~FrameBufferAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FrameBufferAttachment::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void FrameBufferAttachment::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FrameBufferAttachment::dump(      UInt32    , 
                                 const BitVector ) const
{
    SLOG << "Dump FrameBufferAttachment NI" << std::endl;
}

