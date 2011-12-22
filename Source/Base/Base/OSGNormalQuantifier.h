/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2000-2003 by the OpenSG Forum                *
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

#ifndef _OSGNORMALQUANTIFIER_H_
#define _OSGNORMALQUANTIFIER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGVector.h"

#include <vector>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING NormalQuantifier 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NormalQuantifier(UInt32 numberSubdivisions = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NormalQuantifier(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
 
          UInt32  getIndex      (Vec3f  &normal, 
                                 UInt32  numberSubdivisions = 0) const;

    const Vec3f  &getNormal     (UInt32  index                 ) const;

          SizeT   getNormalCount(void                          ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    void build(UInt32 numberSubdivisions = 4);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32             _numberSubdivisions;

    std::vector<Vec3f> _normalTable;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    void   subdivide  (Vec3f   point1, 
                       Vec3f   point2, 
                       Vec3f   point3, 
                       UInt32  number, 
                       UInt32 &index );

    bool rayTriangle ( const Vec3f & dir, 
                       const Vec3f & vert0, 
                       const Vec3f & vert1, 
                       const Vec3f & vert2) const;
    
    UInt32 getSubIndex(Vec3f   point, 
                       Vec3f   point1, 
                       Vec3f   point2, 
                       Vec3f   point3, 
                       UInt32  number) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

 private:
    
    /*!\brief prohibit default function (move to 'public' if needed) */
    NormalQuantifier(const NormalQuantifier &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    NormalQuantifier &operator =(const NormalQuantifier &source);
};

OSG_END_NAMESPACE

#include "OSGNormalQuantifier.inl"

#endif /* _OSGNORMALQUANTIFIER_H_ */
