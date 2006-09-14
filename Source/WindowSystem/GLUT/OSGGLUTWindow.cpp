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

#ifdef OSG_WITH_GLUT

#define OSG_COMPILEWINDOWGLUTINST

#include "OSGGLUTWindow.h"

#include <OSGGLUT.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGGLUTWindow.h"

OSG_USING_NAMESPACE

/*! \class OSG::GLUTWindow

  The class for GLUT-based windows. See \ref PageWindowGlut for a description.

 */

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
GLUTWindow::GLUTWindow(void) :
    Inherited()
{
}

//! Copy Constructor
GLUTWindow::GLUTWindow(const GLUTWindow &source) :
    Inherited(source)
{
}

//! Destructor
GLUTWindow::~GLUTWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void GLUTWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes
void GLUTWindow::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void GLUTWindow::dump(      UInt32    , 
                      const BitVector ) const
{
    SLOG << "Dump GLUTWindow NI" << std::endl;
}
    
/* ------------- Window functions -----------------------*/    
    
// init the window: create the context  
void GLUTWindow::init(void)
{
    activate();
    setupGL ();
}
    
// activate the window: bind the OGL context    
void GLUTWindow::activate(void)
{
    if(glutGetWindow() != getId())
        glutSetWindow(getId());
}
    
// deactivate the window  
void GLUTWindow::deactivate(void)
{
}
    
// swap front and back buffers  
bool GLUTWindow::swap(void)
{
    glutSwapBuffers();

    return true;
}

#endif // OSG_WITH_GLUT


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id$";
    static char cvsid_hpp[] = OSGGLUTWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGGLUTWINDOW_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGLUTWINDOWFIELDS_HEADER_CVSID;
}
