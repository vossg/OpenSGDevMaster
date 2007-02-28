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

#include <OSGConfig.h>
#include <OSGGL.h>

#include "OSGStereoBufferViewport.h"

#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGStereoBufferViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGStereoBufferViewport.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

StereoBufferViewport::StereoBufferViewport(void) :
    Inherited()
{
}

StereoBufferViewport::StereoBufferViewport(
    const StereoBufferViewport &source) :

    Inherited(source)
{
}

StereoBufferViewport::~StereoBufferViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StereoBufferViewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void StereoBufferViewport::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StereoBufferViewport::dump(      UInt32    , 
                                const BitVector ) const
{
    SLOG << "Dump StereoBufferViewport NI" << std::endl;
}


#ifdef OSG_OLD_RENDER_ACTION
void StereoBufferViewport::render(DrawActionBase *action)
{
    if(getLeftBuffer())
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK);
        }
        else
        {
            glDrawBuffer(GL_BACK_LEFT);
        }
    }
    else
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK_RIGHT);
        }
        else
        {
            glDrawBuffer(GL_NONE);
        }
    }

    Inherited::render(action);

    glDrawBuffer(GL_BACK);
}
#endif

#ifdef OSG_CLEANED_RENDERACTION
void StereoBufferViewport::render(RenderTraversalActionBase *action)
{
    if(getLeftBuffer())
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK);
        }
        else
        {
            glDrawBuffer(GL_BACK_LEFT);
        }
    }
    else
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK_RIGHT);
        }
        else
        {
            glDrawBuffer(GL_NONE);
        }
    }

    Inherited::render(action);

    glDrawBuffer(GL_BACK);
}
#endif

