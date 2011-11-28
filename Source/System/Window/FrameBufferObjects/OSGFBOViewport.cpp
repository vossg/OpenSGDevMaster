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

#include "OSGFBOViewport.h"
#include "OSGFrameBufferObject.h"
#include "OSGDrawEnv.h"

#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGWindow.h"
#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGFBOViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGFBOViewport.fcd) and
// regenerate the base file.

Int32 FBOViewport::computePixelLeft(void) const
{
    if(getLeft() > 1)
        return Int32(getLeft());
    
    if(getFrameBufferObject() == NULL)
        return Int32(getLeft());

    return Int32(getFrameBufferObject()->getWidth() * getLeft());
}

Int32 FBOViewport::computePixelRight(void) const
{
    // >1: pixel
    if(getRight() > 1)
        return Int32(getRight());
 
    if(getFrameBufferObject() == NULL)
        return Int32(getRight());
   
    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getFrameBufferObject()->getWidth() * getRight() - 1);
}

Int32 FBOViewport::computePixelBottom(void) const
{
    if(getBottom() > 1)
        return Int32(getBottom());
    
    if(getFrameBufferObject() == NULL)
        return Int32(getBottom());

    return Int32(getFrameBufferObject()->getHeight() * getBottom());
}

Int32 FBOViewport::computePixelTop(void) const
{
    // >1: pixel
    if(getTop() > 1)
        return Int32(getTop());
 
    if(getFrameBufferObject() == NULL)
        return Int32(getTop());
   
    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getFrameBufferObject()->getHeight() * getTop() - 1);
}

bool FBOViewport::computeIsFullWindow(void) const
{
    if(getFrameBufferObject() == NULL)
        return true;

    return  
        computePixelBottom() == 0 &&
        computePixelLeft()   == 0 &&
        computePixelTop()    == getFrameBufferObject()->getHeight() - 1 &&
        computePixelRight()  == getFrameBufferObject()->getWidth () - 1;
}

/*----------------------- constructors & destructors ----------------------*/

FBOViewport::FBOViewport(void) :
    Inherited()
{
}

FBOViewport::FBOViewport(const FBOViewport &source) :
    Inherited(source)
{
}

FBOViewport::~FBOViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FBOViewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void FBOViewport::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FBOViewport::dump(      UInt32    , 
                       const BitVector ) const
{
    SLOG << "Dump DBOViewport NI" << std::endl;
}


FrameBufferObject *FBOViewport::getTarget(void)
{
    return this->getFrameBufferObject();
}

#ifdef OSG_OLD_RENDER_ACTION
void FBOViewport::render(DrawActionBase *action)
{
    if(getFrameBufferObject() != NULL)
    {
        DrawEnv oEnv;
        oEnv.setWindow(action->getWindow());

        getFrameBufferObject()->activate(&oEnv);

        Inherited::render(action);

        getFrameBufferObject()->deactivate(&oEnv);
    }
    else
    {
        Inherited::render(action);
    }
}
#endif
