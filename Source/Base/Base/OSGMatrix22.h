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

#ifndef _OSGMATRIX22_H_
#define _OSGMATRIX22_H_
#ifdef __sgi
#pragma once
#endif

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <iomanip>

#include "OSGLog.h"
#include "OSGVector.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class FloatTypeT>
class Matrix22
{
  public:

    typedef Vector<Real32, 2> VectorType;
    typedef Point <Real32, 2> PointType;


    Matrix22(FloatTypeT a11, FloatTypeT a12, FloatTypeT a21, FloatTypeT a22);
    

    FloatTypeT            det       (      void           ) const;
    
    Matrix22<FloatTypeT > inverse   (      void           ) const;
    
    VectorType            mult      (const VectorType &src) const;
    
    VectorType            operator *(const VectorType &src) const;
    PointType             operator *(const PointType  &src) const;

  private:
    
    FloatTypeT _Values[4];
};

/*---------------------------------------------------------------------*/
/*! \name Matrix Types                                                */
/*! \{                                                                 */

/*! \var typedef Matrix22<Real32> Matrix22f;
    \brief Matrix2f
    \ingroup GrpBaseBaseMathObj
 */

typedef Matrix22<Real32> Matrix22f;

/*! \var typedef Matrix22<Real64> Matrix22d;
    \brief Matrix2d
    \ingroup GrpBaseBaseMathObj
 */

typedef Matrix22<Real64> Matrix22d;

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGMatrix22.inl"

#endif /* _OSGMATRIX22_H_ */

