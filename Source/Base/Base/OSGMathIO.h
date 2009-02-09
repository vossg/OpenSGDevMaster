/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGMATHIO_H_
#define _OSGMATHIO_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseTypes.h"

#include <iostream>
#include <sstream>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseMathIOFn
    \nohierarchy
 */
template <class  VecTypeT,
          class  ValueTypeT = typename VecTypeT::ValueType,
          UInt32 SizeI      =          VecTypeT::_uiSize   >
struct VecToStreamWriter
{
    static void apply(std::ostream &os, const VecTypeT &vec);
};


/*! \ingroup GrpBaseBaseMathIOFn
    \nohierarchy
 */
template <class  VecTypeT,
          UInt32 SizeI    >
struct VecToStreamWriter<VecTypeT, Int8, SizeI>
{
    static void apply(std::ostream &os, const VecTypeT &vec);
};


/*! \ingroup GrpBaseBaseMathIOFn
    \nohierarchy
 */
template <class  VecTypeT,
          UInt32 SizeI    >
struct VecToStreamWriter<VecTypeT, UInt8, SizeI>
{
    static void apply(std::ostream &os, const VecTypeT &vec);
};


/*! \ingroup GrpBaseBaseMathIOFn
    \nohierarchy
 */
template <class  VecTypeT,
          class  ValueTypeT = typename VecTypeT::ValueType,
          UInt32 SizeI      =          VecTypeT::_uiSize   >
struct VecFromStreamReader
{
    static void apply(std::istream &is, VecTypeT &vec);
};


/*! \ingroup GrpBaseBaseMathIOFn
    \nohierarchy
 */
template <class  VecTypeT,
          UInt32 SizeI    >
struct VecFromStreamReader<VecTypeT, Int8, SizeI>
{
    static void apply(std::istream &is, VecTypeT &vec);
};


/*! \ingroup GrpBaseBaseMathIOFn
    \nohierarchy
 */
template <class  VecTypeT,
          UInt32 SizeI    >
struct VecFromStreamReader<VecTypeT, UInt8, SizeI>
{
    static void apply(std::istream &is, VecTypeT &vec);
};

OSG_END_NAMESPACE

#include "OSGMathIO.inl"

#endif // _OSGMATHIO_H_
