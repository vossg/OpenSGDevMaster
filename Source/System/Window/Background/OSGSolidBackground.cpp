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

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGAction.h>
#include <OSGDrawActionBase.h>
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGSolidBackground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SolidBackground
    \ingroup GrpSystemWindowBackgrounds

  A single colored background, see \ref PageSystemWindowBackgroundSolid for a
  description.    

  The color of the background is given by the _sfColor field.
 */

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


void SolidBackground::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------- your_category---------------------------------*/

void SolidBackground::clear(DrawEnv *, Viewport *)
{
	const Color3r &col = getColor();

	GLP::glClearColor(col[0], col[1], col[2], 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*------------------------------- dump ----------------------------------*/

void SolidBackground::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump SolidBackground NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSOLIDBACKGROUND_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSOLIDBACKGROUND_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSOLIDBACKGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


