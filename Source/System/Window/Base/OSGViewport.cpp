/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGField.h>
#include <OSGFieldContainer.h>
#include <OSGAction.h>
#include <OSGDrawActionBase.h>

#ifdef OSG_CLEANED_RENDERACTION
#include <OSGRenderTraversalActionBase.h>
#endif

#include <OSGDrawEnv.h>

#include "OSGBackground.h"
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGCamera.h"
#include "OSGForeground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Viewport
    \ingroup GrpSystemWindowsViewports

  A Viewport is a part of the Window it is attached to used for rendering. See
  \ref PageSystemWindowViewports for a description.
  
  The size of the viewport is defined by the _sfLeft, _sfRight, _sfBottom and
  _sfTop Fields. The Window this Viewport is attached is stored in _sfWindow.
  _sfBackground defines the background clearing method, the
  _sfRoot and _sfCamera Fields the scene being rendered and the camera used to
  view it. The optional _mfForegrounds define which information are added or
  actions are executed after the Viewport has been rendered.
  
  \ext
  
  To create a new Viewport the draw and render methods should be overridden. 
  
  \endext
  
  \dev
  
  When adding fields to the Viewport, make sure to add the code to copy them to
  all the different CLusterWindows! 
  
  \enddev
  
 */

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void Viewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

Viewport::Viewport(void) :
    Inherited()
{
}

Viewport::Viewport(const Viewport &source) :
    Inherited(source)
{
}

Viewport::~Viewport(void)
{
}

void Viewport::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*---------------------------- properties ---------------------------------*/

/*! Calculate the positon of the left border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelLeft(void) const
{
    if(getLeft() > 1)
        return Int32(getLeft());
    
    return Int32(getParent()->getWidth() * getLeft());
}

/*! Calculate the positon of the right border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelRight(void) const
{
    // >1: pixel
    if(getRight() > 1)
        return Int32(getRight());
    
    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getParent()->getWidth() * getRight() - 1);
}

/*! Calculate the positon of the bottom border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelBottom(void) const
{
    if(getBottom() > 1)
        return Int32(getBottom());
    
    return Int32(getParent()->getHeight() * getBottom());
}

/*! Calculate the positon of the top border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelTop(void) const
{
    // >1: pixel
    if(getTop() > 1)
        return Int32(getTop());
    
    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getParent()->getHeight() * getTop() - 1);
}

/*! Checks if the viewport fills the whole window. Needs a valid
  _sfParent value.
 */
bool Viewport::isFullWindow(void) const
{
    return  
        getPixelBottom() == 0 &&
        getPixelLeft()   == 0 &&
        getPixelTop()    == getParent()->getHeight() - 1 &&
        getPixelRight()  == getParent()->getWidth () - 1;
}

WindowPtrConst Viewport::getParent(void) const
{
    return cast_dynamic<WindowPtrConst>(_sfParent.getValue());
}

/*-------------------------- your_category---------------------------------*/

/*! Draw the viewport. Restrict the OpenGL rendering to the given part of the
  window, clear it, draw it using the given DrawAction and add the Foregrounds.
  
  The _sfCamera, _sfBackground and _sfRoot Fields need to be valid, otherwise
  drawing will fail.
  
  \dev
  
  Activates scissoring only if the viewport doesn't fill the wholw window, as it
  significantly slows down some OpenGL implementations.
  
  \enddev
  
 */


#ifdef OSG_OLD_RENDER_ACTION
void Viewport::render(DrawActionBase *action)
{
    if(getCamera() == NullFC)
    {
        SWARNING << "Viewport::render: no camera!" << std::endl;
        return;
    }
    if(getBackground() == NullFC)
    {
        SWARNING << "Viewport::render: no Background!" << std::endl;
        return;
    }
    if(getRoot() == NullFC)
    {
        SWARNING << "Viewport::render: no root!" << std::endl;
        return;
    }

    action->setCamera    (getCPtr(getCamera    ()));
    action->setBackground(getCPtr(getBackground()));
    action->setViewport  (this                     );
    action->setTravMask  (getTravMask()            );

    action->apply(getRoot());

    DrawEnv oEnv;
    
    oEnv.setWindow(action->getWindow());
    
    for(UInt16 i=0; i < getForegrounds().size(); i++)
        getForegrounds(i)->draw(&oEnv, this);
}
#endif

#ifdef OSG_CLEANED_RENDERACTION
void Viewport::render(RenderTraversalActionBase *action)
{
    if(getCamera() == NullFC)
    {
        SWARNING << "Viewport::render: no camera!" << std::endl;
        return;
    }
    if(getBackground() == NullFC)
    {
        SWARNING << "Viewport::render: no Background!" << std::endl;
        return;
    }
    if(getRoot() == NullFC)
    {
        SWARNING << "Viewport::render: no root!" << std::endl;
        return;
    }

    action->setCamera    (getCPtr(getCamera    ()));
    action->setBackground(getCPtr(getBackground()));
    action->setViewport  (this                     );
    action->setTravMask  (getTravMask()            );

    action->apply(getRoot());

    DrawEnv oEnv;

    oEnv.setWindow(action->getWindow());

    for(UInt16 i=0; i < getForegrounds().size(); i++)
        getForegrounds(i)->draw(&oEnv, this);
}
#endif

/*------------------------------- dump ----------------------------------*/

void Viewport::dump(     UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump Viewport NI" << std::endl;

    fprintf(stderr, "%p %p %p\n", 
            this, 
            getCPtr(_sfCamera.getValue()),
            getCPtr(getCamera()));
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
    static Char8 cvsid_hpp       [] = OSGVIEWPORT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGVIEWPORT_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

