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

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGSolidBackground.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSolidBackgroundBase.cpp file.
// To modify it, please change the .fcd file (OSGSolidBackground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SolidBackground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

SolidBackground::SolidBackground(void) :
    Inherited()
{
}

SolidBackground::SolidBackground(const SolidBackground &source) :
    Inherited(source)
{
}

SolidBackground::~SolidBackground(void)
{
}


void SolidBackground::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/

void SolidBackground::clear(DrawEnv *)
{
    Int32      stencilBit = getClearStencilBit();   // 0x0
    GLbitfield clearMask  = 0;

    if(getClearColor() == true)
    {
        clearMask |= GL_COLOR_BUFFER_BIT;

        const Color3f &col = getColor();

        glClearColor(col[0], col[1], col[2], getAlpha());
    }

    if(getClearDepth() == true)
    {
        clearMask |= GL_DEPTH_BUFFER_BIT;
        
        glClearDepth(getDepth());
    }

    if(stencilBit >= 0)
    {
        clearMask |= GL_STENCIL_BUFFER_BIT;
        
        glClearStencil(stencilBit);
    }
    
    if(clearMask != 0)
    {
        glClear(clearMask);
    }
}

/*------------------------------- dump ----------------------------------*/

void SolidBackground::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump SolidBackground NI" << std::endl;
}

