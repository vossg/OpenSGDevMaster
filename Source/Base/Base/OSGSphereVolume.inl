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

#ifndef _OSGSPHEREVOLUME_INL_
#define _OSGSPHEREVOLUME_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------- constructor ----------------------------------*/

inline
SphereVolume::SphereVolume(void) : 
     Inherited(             ),
    _center   (0.f, 0.f, 0.f),
    _radius   (0.f          ) 
{
}

inline
SphereVolume::SphereVolume(const SphereVolume &obj) :
     Inherited(           ),    
    _center   (obj._center), 
    _radius   (obj._radius) 
{
    setEmpty(false);
}

inline
SphereVolume::SphereVolume(const Pnt3f &c, Real32 r) :
     Inherited( ), 
    _center   (c), 
    _radius   (r)
{
    setEmpty(false);
}

inline
SphereVolume::~SphereVolume() 
{
}

/*------------------------- set values -------------------------------*/

/*! Change the center and radius */

inline
void SphereVolume::setValue(const Pnt3f &c, Real32 r)
{
    setEmpty(false);

    _center = c;
    _radius = r;
}


/*! set just the center */

inline
void SphereVolume::setCenter(const Pnt3f &c)
{
    _center = c;
}

/*! set just the radius */

inline
void SphereVolume::setRadius(Real32 r)
{
    _radius = r;
}

/*------------------------- get values -------------------------------*/

/*! Returns the center */

inline
const Pnt3f &SphereVolume::getCenter(void) const
{
    return _center;
}

/*! Returns the radius */

inline
Real32 SphereVolume::getRadius(void) const
{
    return _radius;
}

/*-------------------------- extending ------------------------------------*/

inline
void SphereVolume::extendBy(const SphereVolume &volume)
{
    OSG::extend(*this, volume);
}

/*-------------------------- intersection ---------------------------------*/

inline
bool SphereVolume::intersect(const SphereVolume &volume) const
{
    return OSG::intersect(*this, volume);
}


inline
bool SphereVolume::operator !=(const SphereVolume &rhs) const
{
    return !(*this == rhs);
}

OSG_END_NAMESPACE

#endif // SPHEREVOLUME_CLASS_DECLARATIONS
