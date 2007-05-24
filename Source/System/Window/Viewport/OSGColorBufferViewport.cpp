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

#include "OSGColorBufferViewport.h"

#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGColorBufferViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGColorBufferViewport.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

ColorBufferViewport::ColorBufferViewport(void) :
    Inherited()
{
}

ColorBufferViewport::ColorBufferViewport(const ColorBufferViewport &source) :
    Inherited(source)
{
}

ColorBufferViewport::~ColorBufferViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ColorBufferViewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void ColorBufferViewport::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ColorBufferViewport::dump(      UInt32    , 
                               const BitVector ) const
{
    SLOG << "Dump ColorBufferViewport NI" << std::endl;
}

#if 0 // Have to check GV
void ColorBufferViewport::activate(void)
{
    glColorMask(getRed(), getGreen(), getBlue(), getAlpha());
    Inherited::activate();
}

void ColorBufferViewport::deactivate(void)
{
    Inherited::deactivate();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}
#endif

#ifdef OSG_OLD_RENDER_ACTION
void ColorBufferViewport::render(DrawActionBase *action)
{
    glColorMask(getRed(), getGreen(), getBlue(), getAlpha());

    Inherited::render(action);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}
#endif

#ifdef OSG_CLEANED_RENDERACTION
void ColorBufferViewport::render(RenderTraversalActionBase *action)
{
    glColorMask(getRed(), getGreen(), getBlue(), getAlpha());

    Inherited::render(action);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}
#endif
