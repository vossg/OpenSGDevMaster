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

#define OSG_COMPILEWINDOWXINST

#include <OSGGLU.h>
#include "OSGXWindow.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGXWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGXWindow.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
XWindow::XWindow(void) :
    Inherited()
{
}

//! Copy Constructor
XWindow::XWindow(const XWindow &source) :
    Inherited(source)
{
}

//! Destructor
XWindow::~XWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void XWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes
void XWindow::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void XWindow::dump(      UInt32    , 
                   const BitVector ) const
{
    SLOG << "Dump XWindow NI" << std::endl;
}



/*! Init the window: create the context and setup the OpenGL.
*/
void XWindow::init(void)
{    
    XVisualInfo       *vi, visInfo;
    XWindowAttributes winAttr;

    XGetWindowAttributes(getDisplay(), getWindow(), &winAttr);

    // get the existing glWidget's visual-id
    memset(&visInfo, 0, sizeof(XVisualInfo));

    visInfo.visualid = XVisualIDFromVisual(winAttr.visual);

    // get new display-variable
    if(getDisplay() == NULL)
    {
        setDisplay(XOpenDisplay(DisplayString(getDisplay())));  
    }

    // get a visual for the glx context
    int nvis;

    vi = XGetVisualInfo(getDisplay(), VisualIDMask, &visInfo, &nvis);

    // is the visual GL-capable ?
    int useGL;
    glXGetConfig(getDisplay(), 
                 vi, 
                 GLX_USE_GL, 
                 &useGL );
    if (!useGL)
    {
        SFATAL << "Visual is not OpenGL-capable!" << std::endl;
    }    
  
    // create the new context
    this->setContext(glXCreateContext(getDisplay(), vi, None, GL_TRUE));

    XFree(vi);

    glXMakeCurrent(getDisplay(), getWindow(), getContext());

    setupGL();
}
    
void XWindow::terminate(void)
{
    if(getDisplay() != NULL && getContext() != NULL)
    {
        deactivate();
        
        glXDestroyContext(getDisplay(), getContext());
    }
}

// activate the window: bind the OGL context    
void XWindow::activate(void)
{
    Bool res;
    res = glXMakeCurrent(getDisplay(), getWindow(), getContext());
    
    if(res != True)
    {
        FWARNING(("XWindow::activate: makeCurrent failed!\n"));
        glErr("XWindow::activate");
        glErr("XWindow::activate");
        glErr("XWindow::activate");
    }
}
    
// activate the window: bind the OGL context    
void XWindow::deactivate(void)
{
    glXMakeCurrent(getDisplay(), None, NULL);
}
    
// swap front and back buffers  
bool XWindow::swap(void)
{
    glXSwapBuffers(getDisplay(), getWindow());
    return true;
}

#include <OSGSField.ins>
#include <OSGMField.ins>

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

// doxygen can't find these
#ifndef OSG_DO_DOC 

DataType FieldTraits<DisplayP     >::_type("DisplayP",   NULL);
DataType FieldTraits<X11Window    >::_type("X11Window",  NULL);
DataType FieldTraits<GLXContext, 1>::_type("GLXContext", NULL);

#endif

OSG_FIELD_DLLEXPORT_DEF1(SField, DisplayP     );
OSG_FIELD_DLLEXPORT_DEF1(MField, DisplayP     );
OSG_FIELD_DLLEXPORT_DEF1(SField, X11Window    );
OSG_FIELD_DLLEXPORT_DEF1(MField, X11Window    );
OSG_FIELD_DLLEXPORT_DEF2(SField, GLXContext, 1);
OSG_FIELD_DLLEXPORT_DEF2(MField, GLXContext, 1);

OSG_END_NAMESPACE

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
    static char cvsid_hpp[] = OSGXWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGXWINDOW_INLINE_CVSID;

    static char cvsid_fields_hpp[] = OSGWINDOWXFIELDS_HEADER_CVSID;
}

