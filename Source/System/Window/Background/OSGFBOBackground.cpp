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

#include "OSGGL.h"
#include "OSGGLFuncProtos.h"

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGFBOBackground.h"
#include "OSGFrameBufferObject.h"

OSG_BEGIN_NAMESPACE

UInt32 FBOBackground::_uiFramebufferObjectExt  =
    Window::invalidExtensionID;

UInt32 FBOBackground::_uiFramebufferBlitExt    =
    Window::invalidExtensionID;

UInt32 FBOBackground::_uiFuncBindFramebuffer   =
    Window::invalidFunctionID;

UInt32 FBOBackground::_uiFuncBlitFramebuffer   =
    Window::invalidFunctionID;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FBOBackground
    \ingroup GrpSystemWindowBackgrounds

A FBO background, see \ref PageSystemWindowBackgroundFBO for a
description.

*/
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void FBOBackground::initMethod (InitPhase ePhase)
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

FBOBackground::FBOBackground(void) :
    Inherited()
{
}

FBOBackground::FBOBackground(const FBOBackground &source) :
    Inherited(source)
{
}

FBOBackground::~FBOBackground(void)
{
}

void FBOBackground::changed(ConstFieldMaskArg whichField,
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/

void FBOBackground::clear(DrawEnv *pEnv)
{
    if(_sfFrameBufferObject.getValue() != NULL)
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

        osgGlBindFramebuffer(
            GL_READ_FRAMEBUFFER_EXT,
            win->getGLObjectId(_sfFrameBufferObject.getValue()->getGLId()));

        osgGlBlitFramebuffer(
             0,
             0,
            _sfFrameBufferObject.getValue()->getWidth (),
            _sfFrameBufferObject.getValue()->getHeight(),

            pEnv->getPixelLeft  (),
            pEnv->getPixelBottom(),
            pEnv->getPixelRight () + 1,
            pEnv->getPixelTop   () + 1,

            (GL_COLOR_BUFFER_BIT  |
             GL_DEPTH_BUFFER_BIT  |
             GL_STENCIL_BUFFER_BIT),
            GL_NEAREST);

        if(pEnv->getActiveFBO() != 0)
        {
            osgGlBindFramebuffer(GL_READ_FRAMEBUFFER_EXT,
                                 win->getGLObjectId(pEnv->getActiveFBO()));
        }
        else
        {
            osgGlBindFramebuffer(GL_READ_FRAMEBUFFER_EXT,
                                 0                      );
        }
    }
}

/*------------------------------- dump ----------------------------------*/

void FBOBackground::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump FBOBackground NI" << std::endl;
}

OSG_END_NAMESPACE
