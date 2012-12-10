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

#define GL_GLEXT_PROTOTYPES 1

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLFuncProtos.h"

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGPassiveBackground.h"

OSG_BEGIN_NAMESPACE

UInt32 PassiveBackground::_uiFramebufferObjectExt  = 
    Window::invalidExtensionID;

UInt32 PassiveBackground::_uiFramebufferBlitExt    = 
    Window::invalidExtensionID;

UInt32 PassiveBackground::_uiFuncBindFramebuffer   = 
    Window::invalidFunctionID;

UInt32 PassiveBackground::_uiFuncBlitFramebuffer   =
    Window::invalidFunctionID;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PassiveBackground
    \ingroup GrpSystemWindowBackgrounds

A passive background, see \ref PageSystemWindowBackgroundPassive for a
description.

*/
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void PassiveBackground::initMethod (InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _uiFramebufferObjectExt   = 
            Window::registerExtension("GL_EXT_framebuffer_object");
        _uiFramebufferBlitExt   = 
            Window::registerExtension("GL_EXT_framebuffer_blit");

        _uiFuncBindFramebuffer          = 
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBindFramebufferEXT", 
                _uiFramebufferObjectExt);

        _uiFuncBlitFramebuffer  =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBlitFramebufferEXT", 
                _uiFramebufferBlitExt);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

PassiveBackground::PassiveBackground(void) :
    Inherited()
{
}

PassiveBackground::PassiveBackground(const PassiveBackground &source) :
    Inherited(source)
{
}

PassiveBackground::~PassiveBackground(void)
{
}

void PassiveBackground::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/

void PassiveBackground::clear(DrawEnv *pEnv)
{
    if(_sfClearFrameBufferObject.getValue() == true &&
        pEnv->getActiveFBO()                != 0     )
    {
        if(_sfClearCallback.getValue()._func)
        {
            _sfClearCallback.getValue()._func(pEnv);
        }
        else
        {
            Window *win = pEnv->getWindow();

            OSGGETGLFUNCBYID_GL3_ES( glBindFramebuffer,
                                     osgGlBindFramebuffer,
                                    _uiFuncBindFramebuffer,
                                     win                  );

            OSGGETGLFUNCBYID_GL3( glBlitFramebuffer,
                                  osgGlBlitFramebuffer,
                                 _uiFuncBlitFramebuffer,
                                  win                  );

            osgGlBindFramebuffer(GL_READ_FRAMEBUFFER_EXT, 
                                 0);

            // FixMe breaks if source size != target size
            osgGlBlitFramebuffer(pEnv->getPixelLeft  (), 
                                 pEnv->getPixelBottom(), 
                                 pEnv->getPixelRight (), 
                                 pEnv->getPixelTop   (),
                             
                                 pEnv->getPixelLeft  (), 
                                 pEnv->getPixelBottom(), 
                                 pEnv->getPixelRight (), 
                                 pEnv->getPixelTop   (),
                                 
                                 (GL_COLOR_BUFFER_BIT  |
                                  GL_DEPTH_BUFFER_BIT  |
                                  GL_STENCIL_BUFFER_BIT),
                                 GL_NEAREST); 
        }
    }
}

void PassiveBackground::setClearCallback(RenderFunctor func,
                                         std::string   createSymbol)
{
    RenderFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _sfClearCallback.setValue(oTmp);
}


/*------------------------------- dump ----------------------------------*/

void PassiveBackground::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                             const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump PassiveBackground NI" << std::endl;
}

OSG_END_NAMESPACE
