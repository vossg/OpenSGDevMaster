/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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
#include "OSGGLFuncProtos.h"

#include "OSGViewport.h"

#include "OSGFBOGrabForeground.h"

#include "OSGAction.h"
#include "OSGNode.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGDrawEnv.h"
#include "OSGFrameBufferObject.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFBOGrabForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGFBOGrabForeground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 FBOGrabForeground::_uiFramebufferObjectExt  =
    Window::invalidExtensionID;

UInt32 FBOGrabForeground::_uiFramebufferBlitExt    =
    Window::invalidExtensionID;

UInt32 FBOGrabForeground::_uiFuncBindFramebuffer   =
    Window::invalidFunctionID;

UInt32 FBOGrabForeground::_uiFuncBlitFramebuffer   =
    Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FBOGrabForeground::initMethod(InitPhase ePhase)
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FBOGrabForeground::FBOGrabForeground(void) :
    Inherited()
{
}

FBOGrabForeground::FBOGrabForeground(const FBOGrabForeground &source) :
    Inherited(source)
{
}

FBOGrabForeground::~FBOGrabForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FBOGrabForeground::changed(ConstFieldMaskArg whichField,
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FBOGrabForeground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FBOGrabForeground NI" << std::endl;
}


/*! Grab the image, if it is actually set.
*/

void FBOGrabForeground::draw(DrawEnv * pEnv)
{
    if(getActive() == false)
        return;

    FrameBufferObject* fbo = getFrameBufferObject();

    if(fbo == NULL)       // No FBO, no grab.
        return;

    Int32 w = osgMax(2, pEnv->getPixelWidth ());
    Int32 h = osgMax(2, pEnv->getPixelHeight());

    // If fbo is smaller than 2x2, resize it to vp size.
    // If autoResize then update img size if vp changed

    if( (fbo->getWidth() <= 1 || fbo->getHeight() <= 1) ||
         (getAutoResize() && (w != fbo->getWidth() || h != fbo->getHeight())) )
    {
        fbo->resizeAll(w, h);
    }

    Window *win = pEnv->getWindow();

    win->validateGLObject(fbo->getGLId(), pEnv);

    OSGGETGLFUNCBYID_GL3_ES( glBindFramebuffer,
                             osgGlBindFramebuffer,
                            _uiFuncBindFramebuffer,
                             win                  );

    OSGGETGLFUNCBYID_GL3( glBlitFramebuffer,
                          osgGlBlitFramebuffer,
                         _uiFuncBlitFramebuffer,
                          win                  );

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

    osgGlBindFramebuffer(
        GL_DRAW_FRAMEBUFFER_EXT,
        win->getGLObjectId(_sfFrameBufferObject.getValue()->getGLId()));

    // Fill FBO but only up to size of viewport. This will not scale the
    // captured image unless it is larger than the destination.
    w = osgMin(
        static_cast<Int32>(_sfFrameBufferObject.getValue()->getWidth ()),
        pEnv->getPixelWidth ());
    h = osgMin(
        static_cast<Int32>(_sfFrameBufferObject.getValue()->getHeight()),
        pEnv->getPixelHeight());

    osgGlBlitFramebuffer(
        pEnv->getPixelLeft  (),
        pEnv->getPixelBottom(),
        pEnv->getPixelRight ()+1,
        pEnv->getPixelTop   ()+1,

        0,
        0,
        w, h,

        (GL_COLOR_BUFFER_BIT  |
         GL_DEPTH_BUFFER_BIT  |
         GL_STENCIL_BUFFER_BIT),
        GL_NEAREST);

    if(pEnv->getActiveFBO() != 0)
    {
        osgGlBindFramebuffer(GL_DRAW_FRAMEBUFFER_EXT,
                             win->getGLObjectId(pEnv->getActiveFBO()));
    }
    else
    {
        osgGlBindFramebuffer(GL_DRAW_FRAMEBUFFER_EXT,
                             0                      );
    }
}

OSG_END_NAMESPACE
