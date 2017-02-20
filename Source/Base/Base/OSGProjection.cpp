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
#include "OSGProjection.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Projection
    abstracts the projection type of a camera.
*/
Projection::Projection()
: _zNear(0.f)
, _zFar (0.f)
{
}

Projection::Projection(Real32 zNear, Real32 zFar)
: _zNear(zNear)
, _zFar (zFar)
{
}

Projection::Projection(const Projection& rhs)
: _zNear(rhs._zNear)
, _zFar (rhs._zFar)
{
}

Projection::~Projection()
{
}

Projection& Projection::operator=(const Projection& rhs)
{
    if (&rhs == this) return *this;

    _zNear = rhs._zNear;
    _zFar  = rhs._zFar;

    return *this;
}

OSG_END_NAMESPACE
