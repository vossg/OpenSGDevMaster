/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include "OSGPerspectiveProjection.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Projection
    abstracts the projection type of a camera.
*/
PerspectiveProjection::PerspectiveProjection()
: Inherited()
, _fov   (0.f)
, _aspect(1.f)
{
}

PerspectiveProjection::PerspectiveProjection(const PerspectiveProjection& rhs)
: Inherited()
, _fov   (rhs._fov)
, _aspect(rhs._aspect)
{
}

PerspectiveProjection::PerspectiveProjection(
    Real32 fov,
    Real32 aspect,
    Real32 zNear,
    Real32 zFar)
: Projection(zNear, zFar)
, _fov      (fov)
, _aspect   (aspect)
{
}

PerspectiveProjection::~PerspectiveProjection()
{
}

PerspectiveProjection& PerspectiveProjection::operator=(const PerspectiveProjection& rhs)
{
    if (&rhs == this) return *this;

    Projection::operator=(rhs);

    _fov    = rhs._fov;
    _aspect = rhs._aspect;

    return *this;
}

Projection::Type PerspectiveProjection::getType() const
{
    return Projection::PERSPECTIVE;
}

OSG_END_NAMESPACE
