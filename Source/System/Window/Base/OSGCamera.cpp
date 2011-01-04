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
#include "OSGLog.h"

#include "OSGGL.h"

#include "OSGNode.h"
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGLine.h"

#include "OSGCamera.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGCameraBase.cpp file.
// To modify it, please change the .fcd file (OSGCamera.fcd) and
// regenerate the base file.

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

void Camera::changed(ConstFieldMaskArg whichField, 
                     UInt32            origin,
                     BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


#ifdef OSG_OLD_RENDER_ACTION
/*-------------------------- your_category---------------------------------*/

/*! Setup OpenGL for rendering, call all the necessary commands to start
    rendering with this camera.
 */

void Camera::setup(      DrawActionBase *OSG_CHECK_ARG(action),
                   const Viewport       &port                 )
{
    Matrix m, t;

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
    Matrix m, t;

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

#endif

/*! Get/calculate the projection matrix for this camera.
 */

void Camera::getProjection(Matrix  &OSG_CHECK_ARG(result),
                           UInt32   OSG_CHECK_ARG(width ),
                           UInt32   OSG_CHECK_ARG(height))
{
    SFATAL << "Camera::getProjection: NIY" << std::endl;
}

/*! Get/calculate the projection translation matrix for this camera. The
    default is identity.
 */

void Camera::getProjectionTranslation(Matrix &result,
                                      UInt32  OSG_CHECK_ARG(width ),
                                      UInt32  OSG_CHECK_ARG(height))
{
    result.setIdentity();
}

/*! Get/calculate the viewing matrix for this camera. This is the inverse
    of the beacon's toWorld transformation.
 */

void Camera::getViewing(Matrix &result,
                        UInt32  OSG_CHECK_ARG(width ),
                        UInt32  OSG_CHECK_ARG(height))
{
    if (getBeacon() == NULL)
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
    Matrix mv,prt,pr;

    getProjection           (pr , p.getPixelWidth(), p.getPixelHeight());
    getProjectionTranslation(prt, p.getPixelWidth(), p.getPixelHeight());
    getViewing              (mv , p.getPixelWidth(), p.getPixelHeight());

    pr.mult(prt);
    pr.mult(mv );

    result.setPlanes(pr);
}

/*! Calculate the frustum of this camera's visible area (w,h instead port). 
*/
void Camera::getFrustum(FrustumVolume& result, 
                        UInt32  width, UInt32  height)
{
    Matrix mv,prt,pr;
    
    getProjection           (pr , width, height);
    getProjectionTranslation(prt, width, height);
    getViewing              (mv , width, height);

    pr.mult(prt);
    pr.mult(mv );
    
    result.setPlanes(pr);
}

/*! Calculate the matrix that transforms world coordinates into the screen
    coordinate system for this camera.
 */

void Camera::getWorldToScreen(Matrix &result, const Viewport& p)
{
    Matrix mv,prt,pr;

    getProjection           (result, p.getPixelWidth(), p.getPixelHeight());
    getProjectionTranslation(prt   , p.getPixelWidth(), p.getPixelHeight());
    getViewing              (mv    , p.getPixelWidth(), p.getPixelHeight());

    result.mult(prt);
    result.mult(mv );
}

/*! Get/calculate the decoration matrix for this camera. 
  The default is identity.
*/

void Camera::getDecoration(Matrix &result, UInt32 width, UInt32 height)
{
    result.setIdentity();
}


Matrix Camera::getProjectionVal(UInt32         width,
                                UInt32         height)
{
   Matrix temp_mat;
   this->getProjection(temp_mat, width,height);
   return temp_mat;
}

Matrix Camera::getProjectionTranslationVal(UInt32         width,
                                           UInt32         height)
{
   Matrix temp_mat;
   this->getProjectionTranslation(temp_mat, width, height);
   return temp_mat;
}

Matrix Camera::getViewingVal(UInt32         width,
                             UInt32         height)
{
   Matrix temp_mat;
   this->getViewing(temp_mat, width, height);
   return temp_mat;
}

FrustumVolume Camera::getFrustumVal        (  const Viewport      &port  )
{
   FrustumVolume vol;
   this->getFrustum(vol, port);
   return vol;
}

Matrix Camera::getWorldToScreenVal        ( const Viewport      &port  )
{
   Matrix temp_mat;
   this->getWorldToScreen(temp_mat, port);
   return temp_mat;
}

Matrix Camera::getDecorationVal(UInt32 width, UInt32 height)
{
   Matrix temp_mat;
   this->getDecoration(temp_mat, width, height);
   return temp_mat;
}

Vec2u Camera::tileGetFullSize(void) const
{
    return Vec2u(0u, 0u);
}

Vec4f Camera::tileGetRegion(void) const
{
    return Vec4f(0.f, 1.f, 0.f, 1.f);
}

/*! Calculate a ray that starts at the camera position and goes through the
  pixel \a x, \a y in the viewport \a port. \a x and \a y are relative to the
  viewport's upper left corner. \a t is the length of the viewing ray.
*/

bool Camera::calcViewRay(      Line    &line, 
                               Int32     x, 
                               Int32     y, 
                         const Viewport &port,
                               Real32   *t   )
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

    Real32 rx(0.f), ry(0.f);
    port.getNormalizedCoordinates(rx, ry, x, y);

    Pnt3f from, at;

    cctowc.multFull(Pnt3f(rx, ry, -1), from);
    cctowc.multFull(Pnt3f(rx, ry,  1), at  );

	Vec3f dir = at - from;
	
	if(t != NULL)
	{
		*t = dir.length();
	}

    line.setValue(from, dir);

    return true;
}

/*------------------------------- dump ----------------------------------*/

void Camera::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Camera NI" << std::endl;
}
