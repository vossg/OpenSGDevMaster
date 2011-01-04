/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
 //  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"


#include "OSGGeometry.h"
#include "OSGPrimitiveIterator.h"
#include "OSGPointIterator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PointIterator
    \ingroup GrpSystemDrawablesGeometryIterators
    
The PointIterator iterates through the geometry one point at a
time. See \ref PageSystemPointIterator for details.

\sa PrimitiveIterator FaceIterator

*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \var OSG::PointIterator::_pointIndex

    Running index of the points iterated.
*/

/*! \var OSG::PointIterator::_actPrimIndex

    Index of the next point to use in the current primitive.
*/

/*! \var OSG::PointIterator::_pointPntIndex

    The vertex index of the current point.
*/

#endif // only include in dev docs


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

PointIterator::PointIterator(void) : PrimitiveIterator(),
    _pointIndex(0), _actPrimIndex(0), _pointPntIndex(0)
{
}

PointIterator::PointIterator(const PointIterator &source) : 
    PrimitiveIterator(source),
    _pointIndex(source._pointIndex), _actPrimIndex(source._actPrimIndex),
    _pointPntIndex(source._pointPntIndex)
{
}


/*! This constructor creates an iterator for the given geometry. It is useful
    to create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use OSG::Geometry::beginTriangles() resp. 
    OSG::Geometry::endTriangles() to create an iterator.
*/
PointIterator::PointIterator(Geometry const * geo) :
    PrimitiveIterator(),
    _pointIndex(0), _actPrimIndex(0), _pointPntIndex(0)
{
    setGeo(geo);
}


/*! This constructor creates an iterator for the given node. It is useful to
    create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use OSG::Geometry::beginTriangles() resp. 
    OSG::Geometry::endTriangles() to create an iterator.
*/

PointIterator::PointIterator(Node * const geo) : 
    PrimitiveIterator(),
    _pointIndex(0), _actPrimIndex(0), _pointPntIndex(0)
{
    setGeo(geo);
}


PointIterator::~PointIterator(void)
{
}

/*--------------------------- Operators ----------------------------------*/

/*! The increment operator steps the iterator to the next triangle. If it is
    already beyond the last point it does not change.
*/
void PointIterator::operator++()
{
    // already at end?
    if(isAtEnd())
        return;
    
    ++_pointIndex;

    // at end of primitive?
    if((_actPrimIndex >  getLength()))
    {
        ++(static_cast<PrimitiveIterator&>(*this));      
        startPrim();
        
        return;
    }


    switch(getType())
    {
    case GL_POINTS:         _pointPntIndex = _actPrimIndex++;
                            break;                           
    default:                SWARNING << "PointIterator::++: encountered " 
                                      << "unknown primitive type " 
                                      << getType()
                                      << ", ignoring!" << std::endl;
                            startPrim();
                            break;
    }           
}


/*! Helper function to reset all state to the beginning of a new primitive.
    Also skips non-point primitives(triangles, quads, polygons, lines).
*/
void PointIterator::startPrim(void)
{
    // already at end?
    if(isAtEnd())
        return;
        
    _pointPntIndex = 0;
    _actPrimIndex  = 1;
    
    // loop until you find a useful primitive or run out
    while(! isAtEnd())
    {
        switch(getType())
        {
        case GL_POINTS:         return; // point type
        case GL_TRIANGLES:      
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
        case GL_QUADS:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
        case GL_LINES:
        case GL_LINE_STRIP: 
        case GL_LINE_LOOP:      break; // non-point type: ignored
        default:                SWARNING << "PointIterator::startPrim: "
                                          << "encountered " 
                                          << "unknown primitive type " 
                                          << getType()
                                          << ", ignoring!" << std::endl;
                                break;
        }
        
        ++(static_cast<PrimitiveIterator&>(*this));
    }
}


/*! Seek the iterator to a specific triangle indicated by its index. 

    This is primarily used in conjunction with 
    OSG::PointIterator::getIndex to record a position in the iteration and
    later return to it.
*/
void PointIterator::seek(Int32 index)
{
    setToBegin();
    
    while(getIndex() != index)
        ++(*this);
}


/*! Set the iterator to the beginning of the attached Geometry. Is primarily
    used by OSG::Geometry::beginTriangles, but can also be used to quickly
    recycle an iterator.
*/
void PointIterator::setToBegin(void)
{
    PrimitiveIterator::setToBegin();
    _pointIndex = 0;
    startPrim();
}

/*! Set the iterator to the end of the attached Geometry. Is primarily used by
    OSG::Geometry::endTriangles, but can also be used to quickly recycle an
    iterator.
*/
void PointIterator::setToEnd(void)
{
    PrimitiveIterator::setToEnd();
    _actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

PointIterator& PointIterator::operator =(const PointIterator &source)
{
    if(this == &source)
        return *this;

    *static_cast<Inherited *>(this) = source;
    
    this->_pointIndex    = source._pointIndex;
    this->_actPrimIndex  = source._actPrimIndex;
    this->_pointPntIndex = source._pointPntIndex;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool PointIterator::operator <(const PointIterator &other) const
{
    return 
          (*static_cast<const Inherited *>(this) <  other) ||
        ( (*static_cast<const Inherited *>(this) == other)             &&
          _actPrimIndex                          <  other._actPrimIndex);
}

bool PointIterator::operator ==(const PointIterator &other) const
{
    if(isAtEnd() && other.isAtEnd())
        return true;

    if(isAtEnd() || other.isAtEnd())
        return false;

    return 
        (*static_cast<const Inherited *>(this) == other              ) &&
        _actPrimIndex                          == other._actPrimIndex;
}

bool PointIterator::operator !=(const PointIterator &other) const
{
    return !(*this == other);
}

