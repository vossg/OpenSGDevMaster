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

// Forget everything if we're not doing a windows compile
#ifdef WIN32

#include "OSGWIN32Window.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGWIN32WindowBase.cpp file.
// To modify it, please change the .fcd file (OSGWIN32Window.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

WIN32Window::WIN32Window(void) :
    Inherited()
{
}

//! Copy Constructor

WIN32Window::WIN32Window(const WIN32Window &source) :
    Inherited(source)
{
}

//! Destructor

WIN32Window::~WIN32Window(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void WIN32Window::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes

void WIN32Window::changed(BitVector whichField, 
                          UInt32    origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes

void WIN32Window::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump WIN32Window NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! init the window: create the HDC and HGLRC
*/
void WIN32Window::init(GLInitFunctor oFunc)
{
    if(getHwnd() != NULL)
    {   
        setHdc(GetDC(getHwnd()));
    }

    if(getHglrc() == NULL)
    {
        setHglrc(wglCreateContext(getHdc()));
        
        if(getHglrc() == NULL)
        {
            std::cerr << "WIN32Window::init: failed: "
                      << GetLastError() 
                      << std::endl;        
        }
    }

    Inherited::init(oFunc);
    
    if(getHdc() != NULL && getHwnd() != NULL) 
    {
        ReleaseDC(getHwnd(), getHdc());

        setHdc(NULL);
    }
}

void WIN32Window::terminate(void)
{
    Inherited::doTerminate();

     if(getHglrc() != NULL)
     {
         this->doDeactivate();

         wglDeleteContext(getHglrc());

         setHglrc(NULL);
     }
}


/*! activate the window: set the HDC and bind the OGL context
*/
void WIN32Window::doActivate( void )
{    
    if(getHdc() == NULL)
        setHdc(GetDC(getHwnd()));

    if(!wglMakeCurrent(getHdc(), getHglrc()))
    {
        std::cerr << "WIN32Window::activate: failed: "
                  << GetLastError() 
                  << std::endl;        
    }
}

void WIN32Window::doDeactivate ( void )
{
    // unbind the context
    wglMakeCurrent(NULL, NULL);

    // release the hardware device context
    if(getHdc() != NULL && getHwnd() != NULL) 
    {
        ReleaseDC(getHwnd(), getHdc());
        setHdc(NULL);
    }
}

// swap front and back buffers
bool WIN32Window::doSwap(void)
{
    if(getHdc() == NULL)
        setHdc(GetDC(getHwnd()));

    return SwapBuffers(getHdc()) != 0;
}

bool WIN32Window::hasContext(void)
{
    return (this->getHglrc() != NULL);
}

#endif // WIN32
