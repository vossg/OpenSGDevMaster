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
#include "OSGEdgeIterator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::EdgeIterator
    \ingroup GrpSystemDrawablesGeometryIterators
        
The EdgeIterator iterates through the geometry one edge at a
time. See \ref PageSystemEdgeIterator for a description.

\sa PrimitiveIterator EdgeIterator

*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \var OSG::EdgeIterator::_edgeIndex

    Simple running edge count. Returned by getIndex() and can be used as the
    input to seek();
*/

/*! \var OSG::EdgeIterator::_actPrimIndex

    The next unused point in the current primitive. Starts at 0 and indicates
    that the primitive is exhausted when it goes over the length of the
    primitive.
*/

/*! \var OSG::EdgeIterator::_edgePntIndex

    Keeps the indices of the currently active line vertices for GL_LINES
    primitives. Unused otherwise.
    
    This variable is accessed via the getIndexIndex() method. 
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

EdgeIterator::EdgeIterator(void) :  PrimitiveIterator(),
    _edgeIndex(0), _actPrimIndex()
{
    _edgePntIndex[0] = 0;
    _edgePntIndex[1] = 0;
}

EdgeIterator::EdgeIterator(const EdgeIterator &source) :
    PrimitiveIterator(source),
    _edgeIndex(source._edgeIndex),
    _actPrimIndex(source._actPrimIndex)
{
    _edgePntIndex[0] = source._edgePntIndex[0];
    _edgePntIndex[1] = source._edgePntIndex[1];
}

/*! This constructor creates an iterator for the given node. It is useful to
    create an iterator to be used to seek() to a specific indexed edge. 
    Otherwise, use Geometry::beginEdges() resp. Geometry::endEdges() to create
    an iterator.
*/
EdgeIterator::EdgeIterator(Node * const geo) : PrimitiveIterator(),
    _edgeIndex(0), _actPrimIndex()
{
    _edgePntIndex[0] = 0;
    _edgePntIndex[1] = 0;

    setGeo(geo);
}

/*! This constructor creates an iterator for the given geometry. It is useful
    to create an iterator to be used to seek() to a specific indexed edge. 
    Otherwise, use Geometry::beginEdges() resp. Geometry::endEdges() to create
    an iterator.
*/
EdgeIterator::EdgeIterator(Geometry const * geo) : 
    PrimitiveIterator(),
    _edgeIndex(0), _actPrimIndex()
{
    _edgePntIndex[0] = 0;
    _edgePntIndex[1] = 0;

    setGeo(geo);
}


EdgeIterator::~EdgeIterator(void)
{
}

/*---------------------------- Operators -----------------------------------*/

/*! The increment operator steps the iterator to the next edge. If it is
    already beyond the last edge it does not change.
    
    \dev This is the central function of the whole iterator. It changes 
    _edgePntIndex to contain the data for the next edge, depending on the type
    of the currently active primitive and steps to the next primitive if the
    current one is exhausted. The only tricky part is the left/right swap for
    triangle strips, the rest is pretty simple. \enddev
*/

const EdgeIterator &EdgeIterator::operator++()
{
    // already at end?
    if(isAtEnd())
        return *this;
    
    ++_edgeIndex;

    // at end of primitive?
    if(_actPrimIndex >= PrimitiveIterator::getLength() ||
	   getType() == GL_LINE_STRIP ||
	   getType() == GL_LINE_LOOP    )  // TODO: add GL_POLYLINE here ?!?!
    {
        ++(static_cast<PrimitiveIterator&>(*this));
        
        startPrim();
        
        return *this;
    }

    switch(getType())
    {
    case GL_LINES:          _edgePntIndex[0] = _actPrimIndex++;
                            _edgePntIndex[1] = _actPrimIndex++;
                            break;
#if 0 // probably to be implemented
                            
    case GL_POLYGON:        TODO
                            break;  
    case GL_TRIANGLES:      TODO
                            break;
    case GL_QUAD_STRIP:     TODO
                            break;
    case GL_TRIANGLE_STRIP: TODO
                            break;
    case GL_TRIANGLE_FAN:   TODO
                            break;
    case GL_QUADS:          TODO
                            break;
#endif // probably to be implemented
    default:                SWARNING << "EdgeIterator::++: encountered " 
                                      << "unknown primitive type " 
                                      << getType()
                                      << ", ignoring!" << std::endl;
                            startPrim();
                            break;
    }           

    return *this;
}


/*! Helper function to reset all state to the beginning of a new primitive.
    Also skips non-polygonal primitives(lines, points) and primtiives with less
    than 3 points.
*/
void EdgeIterator::startPrim(void)
{
    // already at end?
    if(isAtEnd())
        return;

    _edgePntIndex[0] = 0;
    _edgePntIndex[1] = 1;
    _actPrimIndex = 2;
    
    // loop until you find a useful primitive or run out
    while(! isAtEnd())
    {
        switch(getType())
        {           
        case GL_LINES:                              
        case GL_LINE_STRIP: 
        case GL_LINE_LOOP:      if(PrimitiveIterator::getLength() >= 2)
                                   return;
                                break; 
        case GL_POINTS:         // non-line types: (currently) ignored
        case GL_TRIANGLES: 
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:   
        case GL_POLYGON:        
        case GL_QUADS:
        case GL_QUAD_STRIP:
                                break;
        default:            SWARNING << "EdgeIterator::startPrim: encountered " 
                                     << "unknown primitive type " 
                                     << getType()
                                     << ", ignoring!" << std::endl;
                            break;
        }   
        
        ++(static_cast<PrimitiveIterator&>(*this));   
    }       
}

/*! Seek the iterator to a specific edge indicated by its index. 

    This is primarily used in conjunction with 
    OSG::EdgeIterator::getIndex to record a position in the iteration and
    later return to it.
*/
void EdgeIterator::seek(Int32 index)
{
    setToBegin();
    
    while(getIndex() != index)
        ++(*this);
}

/*! Set the iterator to the beginning of the geometry. Is primarily used by
    OSG::Geometry::beginEdges, but can also be used to quickly recycle an
    iterator.
*/
void EdgeIterator::setToBegin(void)
{
    PrimitiveIterator::setToBegin();
    _edgeIndex = 0;
    startPrim();
}

/*! Set the iterator to the end of the geometry. Is primarily used by
    OSG::Geometry::endEdges, but can also be used to quickly recycle an
    iterator.
*/
void EdgeIterator::setToEnd(void)
{
    PrimitiveIterator::setToEnd();
    _actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

const EdgeIterator& EdgeIterator::operator =(const EdgeIterator &source)
{
    if(this == &source)
        return *this;
    
    *static_cast<Inherited *>(this) = source;

    this->_edgeIndex            = source._edgeIndex;
    this->_actPrimIndex         = source._actPrimIndex;
    this->_edgePntIndex[0]      = source._edgePntIndex[0];
    this->_edgePntIndex[1]      = source._edgePntIndex[1];

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool EdgeIterator::operator <(const EdgeIterator &other) const
{
    return 
          (*static_cast<const Inherited *>(this) <  other) ||
        ( (*static_cast<const Inherited *>(this) == other)             &&
          _actPrimIndex                          <  other._actPrimIndex);
}

bool EdgeIterator::operator ==(const EdgeIterator &other) const
{
    if(isAtEnd() && other.isAtEnd())
        return true;

    if(isAtEnd() || other.isAtEnd())
        return false;

    return 
        (*static_cast<const Inherited *>(this) == other              ) &&
        _actPrimIndex                          == other._actPrimIndex;
}

bool EdgeIterator::operator !=(const EdgeIterator &other) const
{
    return !(*this == other);
}
