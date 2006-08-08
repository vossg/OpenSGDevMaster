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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGGL.h>

#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

/*! \class osg::FrameBufferAttachment
    \ingroup GrpSystemWindowViewports

 */

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
                                    UInt32            origin    )
{
    Inherited::changed(whichField, origin);
}

void FrameBufferAttachment::dump(      UInt32    , 
                                 const BitVector ) const
{
    SLOG << "Dump FrameBufferAttachment NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = 
                                   OSGFRAMEBUFFERATTACHMENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = 
                                   OSGFRAMEBUFFERATTACHMENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = 
                                   OSGFRAMEBUFFERATTACHMENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

