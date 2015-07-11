/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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

OSG_BEGIN_NAMESPACE

inline BSplineTrimmedSurface::BSplineTrimmedSurface(void) :
    surf    (),
    trimming()
{
    // nothing to do
}

inline BSplineTrimmedSurface::~BSplineTrimmedSurface(void)
{
    // nothing to do
}

inline BSplineTensorSurface &BSplineTrimmedSurface::getSurface(void)
{
    return surf;
}

inline trimmingloop &BSplineTrimmedSurface::getTrimmingLoops(void)
{
    return trimming;
}

inline int BSplineTrimmedSurface::setSurface(BSplineTensorSurface &ts)
{
    surf = ts;

    return 0;
}

inline int BSplineTrimmedSurface::setTrimmingLoops(trimmingloop &t)
{
    trimming = t;

    return 0;
}

OSG_END_NAMESPACE
