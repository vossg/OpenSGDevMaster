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

#include "OSGConfig.h"

// Forget everything if we're not doing a Mac OS X compile
#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include <AGL/agl.h>

#include "OSGCarbonWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCarbonWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCarbonWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CarbonWindow::initMethod(InitPhase ePhase)
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

CarbonWindow::CarbonWindow(void) :
    Inherited()
{
}

CarbonWindow::CarbonWindow(const CarbonWindow &source) :
    Inherited(source)
{
}

CarbonWindow::~CarbonWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CarbonWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CarbonWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CarbonWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! Init the window: create the context and setup the OpenGL.
*/
void CarbonWindow::init(GLInitFunctor oFunc)
{
    Inherited::init(oFunc);
}

void CarbonWindow::terminate(void)
{
}

// activate the window: bind the OGL context
void CarbonWindow::doActivate( void )
{
    aglSetCurrentContext(getContext());
}

// activate the window: bind the OGL context
void CarbonWindow::doDeactivate( void )
{
    aglSetCurrentContext(0);
}

// swap front and back buffers
bool CarbonWindow::doSwap( void )
{
    aglSwapBuffers(getContext());
    return true;
}

bool CarbonWindow::hasContext(void)
{
    return (this->getContext() != NULL);
}

OSG_END_NAMESPACE

#endif // __APPLE__
