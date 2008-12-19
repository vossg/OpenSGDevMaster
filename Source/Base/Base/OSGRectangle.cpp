/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------* \
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
 * Implementation based on the original thesis work by Julien Koenen         *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include "OSGRectangle.h"
#include <algorithm>

OSG_BEGIN_NAMESPACE

#if 0
template class Rectangle2<Real32>;
template class Rectangle2<Real64>;
template class Rectangle2<Int32 >;


template Rectangle2<Real32> getIntersection(const Rectangle2<Real32> &lhs, 
                                            const Rectangle2<Real32> &rhs);
template Rectangle2<Real32> getUnion       (const Rectangle2<Real32> &lhs, 
                                            const Rectangle2<Real32> &rhs);

template Rectangle2<Real64> getIntersection(const Rectangle2<Real64> &lhs,
                                            const Rectangle2<Real64> &rhs);
template Rectangle2<Real64> getUnion       (const Rectangle2<Real64> &lhs, 
                                            const Rectangle2<Real64> &rhs);

template Rectangle2<Int32 > getIntersection(const Rectangle2<Int32 > &lhs, 
                                            const Rectangle2<Int32 > &rhs);
template Rectangle2<Int32 > getUnion       (const Rectangle2<Int32 > &lhs, 
                                            const Rectangle2<Int32 > &rhs);

#endif

OSG_END_NAMESPACE
