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

OSG_BEGIN_NAMESPACE

/*-------------------------- constructor ----------------------------------*/

/*! Default constructor - leaves box empty
*/

inline
FrustumVolume::FrustumVolume() : 
    Inherited() 
{
}

/*! Constructor given bounds
 */

inline
FrustumVolume::FrustumVolume(const Plane &pnear, const Plane &pfar,
                             const Plane &left,  const Plane &right,
                             const Plane &top,   const Plane &bottom) :
    Inherited()
{
    _planeVec[0] = pnear;
    _planeVec[1] = pfar;
    _planeVec[2] = left;
    _planeVec[3] = right;
    _planeVec[4] = top;
    _planeVec[5] = bottom;
}

/*! Copy Constructor
 */

inline
FrustumVolume::FrustumVolume(const FrustumVolume &obj) :
    Inherited(obj)
{
    _planeVec[0] = obj._planeVec[0];
    _planeVec[1] = obj._planeVec[1];
    _planeVec[2] = obj._planeVec[2];
    _planeVec[3] = obj._planeVec[3];
    _planeVec[4] = obj._planeVec[4];
    _planeVec[5] = obj._planeVec[5];
}

/*! Destructor
 */

inline
FrustumVolume::~FrustumVolume() 
{
}

/*------------------------------ feature ----------------------------------*/

/*! Returns the near plane
 */

inline
const Plane &FrustumVolume::getNear(void) const
{
    return _planeVec[0];
}

/*! Returns the far plane
 */

inline
const Plane &FrustumVolume::getFar(void) const
{
    return _planeVec[1];
}

/*! Returns the left plane
 */

inline
const Plane &FrustumVolume::getLeft(void) const
{
    return _planeVec[2];
}

/*! Returns the right plane
 */

inline
const Plane &FrustumVolume::getRight(void) const
{
    return _planeVec[3];
}

/*! Returns the top plane
 */

inline
const Plane &FrustumVolume::getTop(void) const
{
    return _planeVec[4];
}

/*! Returns the bottom plane
 */

inline
const Plane &FrustumVolume::getBottom(void) const
{
    return _planeVec[5];
}


/*! get method
 */

inline
const Plane *FrustumVolume::getPlanes(void) const
{
    return _planeVec;
}

/*-------------------------- extending ------------------------------------*/

/*!
  \brief extend the volume to enclose the given frustum.
 */

inline
void FrustumVolume::extendBy(const FrustumVolume &volume)
{
    OSG::extend(*this, volume);
}

/*-------------------------- intersection ---------------------------------*/

inline
bool FrustumVolume::intersect(const FrustumVolume &volume) const
{
    return OSG::intersect(*this, volume);
}

/*-------------------------- operators ------------------------------------*/

/*! Inequality comparisons
 */

inline
bool operator !=(const FrustumVolume &b1, const FrustumVolume &b2)
{
    return !(b1 == b2);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_END_NAMESPACE

