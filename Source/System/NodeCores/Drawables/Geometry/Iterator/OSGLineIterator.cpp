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
#include "OSGLineIterator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LineIterator
    \ingroup GrpSystemDrawablesGeometryIterators
    
The LineIterator iterates through the geometry one line at a
time. See \ref PageSystemLineIterator for details.

\sa PrimitiveIterator FaceIterator

*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \var OSG::LineIterator::_lineIndex

    Running index of the lines iterated.
*/

/*! \var OSG::LineIterator::_actPrimIndex

    Index of the next point to use in the current primitive.
*/

/*! \var OSG::LineIterator::_linePntIndex

    The vertex indices of the current line.
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

LineIterator::LineIterator(void) : PrimitiveIterator(),
    _lineIndex(0), _actPrimIndex(0), _linePntIndex()
{
}

LineIterator::LineIterator(const LineIterator &source) : 
    PrimitiveIterator(source),
    _lineIndex(source._lineIndex), _actPrimIndex(source._actPrimIndex),
    _linePntIndex()
{
    _linePntIndex[0] = source._linePntIndex[0];
    _linePntIndex[1] = source._linePntIndex[1];
}


/*! This constructor creates an iterator for the given geometry. It is useful
    to create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use OSG::Geometry::beginTriangles() resp. 
    OSG::Geometry::endTriangles() to create an iterator.
*/
LineIterator::LineIterator(ConstGeometryPtr geo) :
    PrimitiveIterator(),
    _lineIndex(0), _actPrimIndex(0), _linePntIndex()
{
    setGeo(geo);
}


/*! This constructor creates an iterator for the given node. It is useful to
    create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use OSG::Geometry::beginTriangles() resp. 
    OSG::Geometry::endTriangles() to create an iterator.
*/

LineIterator::LineIterator(const NodePtr geo) : 
    PrimitiveIterator(),
    _lineIndex(0), _actPrimIndex(0), _linePntIndex()
{
    setGeo(geo);
}


LineIterator::~LineIterator(void)
{
}

/*--------------------------- Operators ----------------------------------*/

/*! The increment operator steps the iterator to the next triangle. If it is
    already beyond the last triangle it does not change.
*/
void LineIterator::operator++()
{
    // already at end?
    if(isAtEnd())
        return;
    
    ++_lineIndex;

    // at end of primitive?
    if((_actPrimIndex >  getLength())                           ||
	   (_actPrimIndex == getLength() && getType() != GL_LINE_LOOP))
    {
        ++(static_cast<PrimitiveIterator&>(*this));      
        startPrim();
        
        return;
    }


    switch(getType())
    {
    case GL_LINES:          _linePntIndex[0] = _actPrimIndex++;
                            _linePntIndex[1] = _actPrimIndex++;
                            break;                           
    case GL_LINE_STRIP:     _linePntIndex[0] = _linePntIndex[1];
                            _linePntIndex[1] = _actPrimIndex++;
                            break;
    case GL_LINE_LOOP:      _linePntIndex[0] = _linePntIndex[1];
                            if(_actPrimIndex < getLength())
                            {
                                _linePntIndex[1] = _actPrimIndex++;
                            }
                            else
                            {
                                _linePntIndex[1] = 0;
                                _actPrimIndex++;    
                            }
                            break;
    default:                SWARNING << "LineIterator::++: encountered " 
                                      << "unknown primitive type " 
                                      << getType()
                                      << ", ignoring!" << std::endl;
                            startPrim();
                            break;
    }           
}


/*! Helper function to reset all state to the beginning of a new primitive.
    Also skips non-line primitives(triangles, quads, polygons, points) and
    primitives with less than 2 points.
*/
void LineIterator::startPrim(void)
{
    // already at end?
    if(isAtEnd())
        return;
        
    _linePntIndex[0] = 0;
    _linePntIndex[1] = 1;
    _actPrimIndex = 2;
    
    // loop until you find a useful primitive or run out
    while(! isAtEnd())
    {
        switch(getType())
        {
        case GL_POINTS:         // non-line types: ignored
        case GL_TRIANGLES:      
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
        case GL_QUADS:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
                                break;
        case GL_LINES:          // line types
        case GL_LINE_STRIP: 
        case GL_LINE_LOOP:      if(getLength() >= 2)
                                    return;
                                break;
        default:                SWARNING << "LineIterator::startPrim: "
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
    OSG::LineIterator::getIndex to record a position in the iteration and
    later return to it.
*/
void LineIterator::seek(Int32 index)
{
    setToBegin();
    
    while(getIndex() != index)
        ++(*this);
}


/*! Set the iterator to the beginning of the attached Geometry. Is primarily
    used by OSG::Geometry::beginTriangles, but can also be used to quickly
    recycle an iterator.
*/
void LineIterator::setToBegin(void)
{
    PrimitiveIterator::setToBegin();
    _lineIndex = 0;
    startPrim();
}

/*! Set the iterator to the end of the attached Geometry. Is primarily used by
    OSG::Geometry::endTriangles, but can also be used to quickly recycle an
    iterator.
*/
void LineIterator::setToEnd(void)
{
    PrimitiveIterator::setToEnd();
    _actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

LineIterator& LineIterator::operator =(const LineIterator &source)
{
    if(this == &source)
        return *this;

    *static_cast<Inherited *>(this) = source;
    
    this->_lineIndex        = source._lineIndex;
    this->_actPrimIndex     = source._actPrimIndex;
    this->_linePntIndex[0]  = source._linePntIndex[0];
    this->_linePntIndex[1]  = source._linePntIndex[1];

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool LineIterator::operator <(const LineIterator &other) const
{
    return 
          (*static_cast<const Inherited *>(this) <  other) ||
        ( (*static_cast<const Inherited *>(this) == other)             &&
          _actPrimIndex                          <  other._actPrimIndex);
}

bool LineIterator::operator ==(const LineIterator &other) const
{
    if(isAtEnd() && other.isAtEnd())
        return true;

    if(isAtEnd() || other.isAtEnd())
        return false;

    return 
        (*static_cast<const Inherited *>(this) == other              ) &&
        _actPrimIndex                          == other._actPrimIndex;
}

bool LineIterator::operator !=(const LineIterator &other) const
{
    return !(*this == other);
}
