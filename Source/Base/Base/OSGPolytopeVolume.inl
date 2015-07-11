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

/*! Default constructor - leaves box totally empty
*/

inline
PolytopeVolume::PolytopeVolume() :
     Volume   (    ),
    _numPlanes(0   ),
    _planes   (NULL)
{
}

/// Constructor given bounds

inline
PolytopeVolume::PolytopeVolume ( const UInt16& s ) :
     Volume   (    ), 
    _numPlanes(s   ),
    _planes   (NULL)
{
    _planes = new Plane[_numPlanes];
}

/// Copy Constructor
inline
PolytopeVolume::PolytopeVolume(const PolytopeVolume &obj) :
     Volume   (obj           ),
    _numPlanes(obj._numPlanes),
    _planes   (NULL          )
{
    _planes=new Plane[_numPlanes];
    for(UInt16 i=0; i<_numPlanes; i++)
        _planes[i]=obj._planes[i];
}

/// Destructor
inline
PolytopeVolume::~PolytopeVolume()
{
    delete[] _planes;
}

/*------------------------------ feature ----------------------------------*/

/// Returns the near plane
inline
const Plane &PolytopeVolume::getNear   (void) const
{
    return _planes[0];
}

/// get method
inline
const Plane *PolytopeVolume::getPlanes(void) 
{
    return _planes;
}

/// get method
inline
const Plane *PolytopeVolume::getPlanes(void) const
{
    return _planes;
}

/*-------------------------- extending ------------------------------------*/

inline
void PolytopeVolume::extendBy(const Volume &volume)
{
    // not implemented
}

inline
void PolytopeVolume::extendBy(const PolytopeVolume &volume)
{
    // not implemented
}

/*-------------------------- intersection ---------------------------------*/

inline
bool PolytopeVolume::intersect (const Volume &volume) const
{
    // not implemented
    return(1);
}

inline
bool PolytopeVolume::intersect(const PolytopeVolume &volume) const
{
    // not implemented
    return(1);
}


/*-------------------------- operators ------------------------------------*/

/*! Inequality comparisons
 */

inline 
bool PolytopeVolume::operator != (const PolytopeVolume &rhs) const
{
    return !(*this == rhs);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_END_NAMESPACE
