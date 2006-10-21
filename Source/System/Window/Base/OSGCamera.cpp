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
#include "OSGLog.h"

#include <OSGGL.h>

#include "OSGNode.h"
#include "OSGFieldContainerPtr.h"
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGLine.h"

#include "OSGCamera.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Camera
    \ingroup GrpSystemWindowCameras

  The Camera base class, see \ref PageSystemWindowCamera for a description.

  The only common fields are _sfNear and _sfFar.
 */

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Camera::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Camera::Camera(void) :
    Inherited()
{
}

Camera::Camera(const Camera &source) :
    Inherited(source)
{
}

Camera::~Camera(void)
{
}

void Camera::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


/*-------------------------- your_category---------------------------------*/

/*! Setup OpenGL for rendering, call all the necessary commands to start
    rendering with this camera.
 */

void Camera::setup(      DrawActionBase *OSG_CHECK_ARG(action),
                   const Viewport       &port                 )
{
    Matrixr m, t;

    // set the projection

    getProjection           (m, port.getPixelWidth(), port.getPixelHeight());
    getProjectionTranslation(t, port.getPixelWidth(), port.getPixelHeight());

    m.mult(t);

    //SDEBUG << "Projection matrix: " << m << std::endl;

    glMatrixMode (GL_PROJECTION);
    GLP::glLoadMatrixf(m.getValues());

    // set the viewing

    getViewing(m, port.getPixelWidth(), port.getPixelHeight());

    //SDEBUG << "Viewing matrix: " << m << std::endl;

    glMatrixMode (GL_MODELVIEW );
    GLP::glLoadMatrixf(m.getValues());
}

/*! Setup OpenGL projection for rendering.
 */

void Camera::setupProjection(      DrawActionBase *OSG_CHECK_ARG(action),
                             const Viewport       &port                 )
{
    Matrixr m, t;

    // set the projection

    getProjection           (m, port.getPixelWidth(), port.getPixelHeight());
    getProjectionTranslation(t, port.getPixelWidth(), port.getPixelHeight());

    m.mult(t);

    //SDEBUG << "Projection matrix: " << m << std::endl;

    glMatrixMode (GL_PROJECTION);
    GLP::glLoadMatrixf(m.getValues());
}

/*! Draw the camera's geometry (if any). Usually there is none.
 */



/*! Get/calculate the projection matrix for this camera.
 */

void Camera::getProjection(Matrixr &OSG_CHECK_ARG(result),
                           UInt32   OSG_CHECK_ARG(width ),
                           UInt32   OSG_CHECK_ARG(height))
{
    SFATAL << "Camera::getProjection: NIY" << std::endl;
}

/*! Get/calculate the projection translation matrix for this camera. The
    default is identity.
 */

void Camera::getProjectionTranslation(Matrixr &result,
                                      UInt32   OSG_CHECK_ARG(width ),
                                      UInt32   OSG_CHECK_ARG(height))
{
    result.setIdentity();
}

/*! Get/calculate the viewing matrix for this camera. This is the inverse
    of the beacon's toWorld transformation.
 */

void Camera::getViewing(Matrixr &result,
                        UInt32   OSG_CHECK_ARG(width ),
                        UInt32   OSG_CHECK_ARG(height))
{
    if (getBeacon() == NullFC)
    {
        SWARNING << "Camera::setup: no beacon!" << std::endl;
        return;
    }

    getBeacon()->getToWorld(result);
    result.invert();
}

/*! Calculate the frustum of this camera's visible area.
 */

void Camera::getFrustum(FrustumVolume& result, const Viewport& p)
{
    Matrixr mv,prt,pr;

    getProjection           (pr , p.getPixelWidth(), p.getPixelHeight());
    getProjectionTranslation(prt, p.getPixelWidth(), p.getPixelHeight());
    getViewing              (mv , p.getPixelWidth(), p.getPixelHeight());

    pr.mult(prt);
    pr.mult(mv );

    result.setPlanes(pr);
}

/*! Calculate the matrix that transforms world coordinates into the screen
    coordinate system for this camera.
 */

void Camera::getWorldToScreen(Matrixr &result, const Viewport& p)
{
    Matrixr mv,prt,pr;

    getProjection           (result, p.getPixelWidth(), p.getPixelHeight());
    getProjectionTranslation(prt   , p.getPixelWidth(), p.getPixelHeight());
    getViewing              (mv    , p.getPixelWidth(), p.getPixelHeight());

    result.mult(prt);
    result.mult(mv );
}

Matrixr Camera::getProjectionVal           (   UInt32         width,
                                          UInt32         height)
{
   Matrixr temp_mat;
   this->getProjection(temp_mat, width,height);
   return temp_mat;
}

Matrixr Camera::getProjectionTranslationVal(   UInt32         width,
                                          UInt32         height)
{
   Matrixr temp_mat;
   this->getProjectionTranslation(temp_mat, width, height);
   return temp_mat;
}

Matrixr Camera::getViewingVal              ( UInt32         width,
                                          UInt32         height)
{
   Matrixr temp_mat;
   this->getViewing(temp_mat, width, height);
   return temp_mat;
}

FrustumVolume Camera::getFrustumVal        (  const Viewport      &port  )
{
   FrustumVolume vol;
   this->getFrustum(vol, port);
   return vol;
}

Matrixr Camera::getWorldToScreenVal        ( const Viewport      &port  )
{
   Matrixr temp_mat;
   this->getWorldToScreen(temp_mat, port);
   return temp_mat;
}


#ifndef OSG_WINCE
/*! Calculate a ray that starts at the camera position and goes through the
  pixel \a x, \a y in the viewport \a port. \a x and \a y are relative to the
  viewport's upper left corner.
*/

bool Camera::calcViewRay(Line &line, Int32 x, Int32 y, const Viewport &port)
{
    if(port.getPixelWidth() <= 0 || port.getPixelHeight() <= 0)
    {
        return false;
    }

    Matrix proj, projtrans, view;

    getProjection(proj,
                  port.getPixelWidth(),
                  port.getPixelHeight());

    getProjectionTranslation(projtrans,
                             port.getPixelWidth(),
                             port.getPixelHeight());

    getViewing(view,
               port.getPixelWidth(),
               port.getPixelHeight());

    Matrix wctocc = proj;

    wctocc.mult(projtrans);
    wctocc.mult(view);

    Matrix cctowc;

    cctowc.invertFrom(wctocc);

    Real32  rx =
        (x - port.getPixelLeft()) /
        (Real32) port.getPixelWidth() * 2.f - 1.f;

    Real32 ry = 1.f - (
        ( y - (port.getParent()->getHeight() - port.getPixelTop()) ) /
        (Real32) port.getPixelHeight()) * 2.f;

    Pnt3f from, at;

    cctowc.multFullMatrixPnt(Pnt3f(rx, ry, -1), from);
    cctowc.multFullMatrixPnt(Pnt3f(rx, ry,  1), at);

    line.setValue(from, at-from);

    return true;
}
#endif

/*------------------------------- dump ----------------------------------*/

void Camera::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Camera NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGCAMERA_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCAMERA_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCAMERAFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

