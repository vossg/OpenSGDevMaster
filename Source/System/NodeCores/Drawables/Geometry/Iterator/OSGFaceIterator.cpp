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
#include "OSGFaceIterator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FaceIterator
    \ingroup GrpSystemDrawablesGeometryIterators
        
The FaceIterator iterates through the geometry one face at a
time. See \ref PageSystemFaceIterator for a description.

\sa PrimitiveIterator FaceIterator

*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \var OSG::FaceIterator::_faceIndex

    Simple runing face count. Returned by getIndex() and can be used as the
    input to seek();
*/

/*! \var OSG::FaceIterator::_actPrimIndex

    The next unused point in the current primitive. Starts at 0 and indicates
    that the primitive is exhausted when it goes over the length of the
    primitive.
*/

/*! \var OSG::FaceIterator::_facePntIndex

    Keeps the indices of the currently active face vertices. If the face is a
    tri the fourth index is -1. 
    
    This variable is accessed via the getIndexIndex() method. 
*/

#endif // only include in dev docs


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char FaceIterator::cvsid[] = "@(#)$Id$";

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

FaceIterator::FaceIterator(void) :  PrimitiveIterator(),
    _faceIndex(0), _actPrimIndex(), _facePntIndex()
{
}

FaceIterator::FaceIterator(const FaceIterator &source) :
    PrimitiveIterator(source),
    _faceIndex(source._faceIndex),
    _actPrimIndex(source._actPrimIndex),
    _facePntIndex()
{
    _facePntIndex[0] = source._facePntIndex[0];
    _facePntIndex[1] = source._facePntIndex[1];
    _facePntIndex[2] = source._facePntIndex[2];
    _facePntIndex[3] = source._facePntIndex[3];
}

/*! This constructor creates an iterator for the given node. It is useful to
    create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use Geometry::beginFaces() resp. Geometry::endFaces() to create
    an iterator.
*/
FaceIterator::FaceIterator(const NodePtr& geo) : PrimitiveIterator(),
    _faceIndex(0), _actPrimIndex(), _facePntIndex()
{
    setGeo(geo);
}

/*! This constructor creates an iterator for the given geometry. It is useful
    to create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use Geometry::beginFaces() resp. Geometry::endFaces() to create
    an iterator.
*/
FaceIterator::FaceIterator(GeometryConstPtrArg geo) : 
    PrimitiveIterator(),
    _faceIndex(0), _actPrimIndex(), _facePntIndex()
{
    setGeo(geo);
}


FaceIterator::~FaceIterator(void)
{
}

/*---------------------------- Operators -----------------------------------*/

/*! The increment operator steps the iterator to the next face. If it is
    already beyond the last face it does not change.
    
    \dev This is the central function of the whole iterator. It changes 
    _facePntIndex to contain the data for the next face, depending on the type
    of the currently active primitive and steps to the next primitive if the
    current one is exhausted. The only tricky part is the left/right swap for
    triangle strips, the rest is pretty simple. \enddev
*/
void FaceIterator::operator++()
{
    // already at end?
    if(isAtEnd())
        return;
    
    ++_faceIndex;

    // at end of primitive?
    if(_actPrimIndex >= PrimitiveIterator::getLength())
    {
        ++(static_cast<PrimitiveIterator&>(*this));
        
        startPrim();
        
        return;
    }

    switch(getType())
    {
    case GL_TRIANGLES:      _facePntIndex[0] = _actPrimIndex++;
                            _facePntIndex[1] = _actPrimIndex++;
                            _facePntIndex[2] = _actPrimIndex++;
                            _facePntIndex[3] = -1;
                            break;
    case GL_QUAD_STRIP:     _facePntIndex[0] = _facePntIndex[3];
                            _facePntIndex[1] = _facePntIndex[2];
                            _facePntIndex[3] = _actPrimIndex++;
                            _facePntIndex[2] = _actPrimIndex++;
                            break;
    case GL_TRIANGLE_STRIP: if(_actPrimIndex & 1)
                            {
                                _facePntIndex[0] = _facePntIndex[2];
                            }
                            else
                            {
                                _facePntIndex[1] = _facePntIndex[2];
                            }                           
                            _facePntIndex[2] = _actPrimIndex++;
                            
                            if(getPositionIndex(0) == getPositionIndex(1) ||
                               getPositionIndex(0) == getPositionIndex(2) ||
                               getPositionIndex(1) == getPositionIndex(2))
                            {
                                --_faceIndex;
                                ++(*this);
                            }
                               
                            break;
    case GL_POLYGON:
    case GL_TRIANGLE_FAN:   _facePntIndex[1] = _facePntIndex[2];
                            _facePntIndex[2] = _actPrimIndex++;
                            break;
    case GL_QUADS:          _facePntIndex[0] = _actPrimIndex++;
                            _facePntIndex[1] = _actPrimIndex++;
                            _facePntIndex[2] = _actPrimIndex++;
                            _facePntIndex[3] = _actPrimIndex++;
                            break;
    default:                SWARNING << "FaceIterator::++: encountered " 
                                      << "unknown primitive type " 
                                      << getType()
                                      << ", ignoring!" << std::endl;
                            startPrim();
                            break;
    }           
}


/*! Helper function to reset all state to the beginning of a new primitive.
    Also skips non-polygonal primitives(lines, points) and primtiives with less
    than 3 points.
*/
void FaceIterator::startPrim(void)
{
    // already at end?
    if(isAtEnd())
        return;

    _facePntIndex[0] = 0;
    _facePntIndex[1] = 1;
    _facePntIndex[2] = 2;
    _facePntIndex[3] = -1;
    _actPrimIndex = 3;
    
    // loop until you find a useful primitive or run out
    while(! isAtEnd())
    {
        switch(getType())
        {
        case GL_POINTS:     // non-polygon types: ignored
        case GL_LINES:
        case GL_LINE_STRIP: 
        case GL_LINE_LOOP:  
                            break;
        case GL_TRIANGLES: 
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:   
                                if(PrimitiveIterator::getLength() >= 3)
                                    return;
                                break;
        case GL_POLYGON:        switch(PrimitiveIterator::getLength())
                                {
                                case 0: 
                                case 1: 
                                case 2: 
                                            break;
                                case 4:
                                            _facePntIndex[3] = _actPrimIndex++;     
                                            return;
                                default:
                                            return;
                                }
                                break;
        case GL_QUADS:          if(PrimitiveIterator::getLength() >= 4)
                                {
                                    _facePntIndex[3] = _actPrimIndex++;                         
                                    return;
                                }
                                break;
        case GL_QUAD_STRIP:         if(PrimitiveIterator::getLength() >= 4)
                                {
                                    _facePntIndex[3] = _facePntIndex[2];                        
                                    _facePntIndex[2] = _actPrimIndex++;                         
                                    return;
                                }
                                break;
        default:            SWARNING << "FaceIterator::startPrim: encountered " 
                                     << "unknown primitive type " 
                                     << getType()
                                     << ", ignoring!" << std::endl;
                            break;
        }   
        
        ++(static_cast<PrimitiveIterator&>(*this));   
    }       
}

/*! Seek the iterator to a specific face indicated by its index. 

    This is primarily used in conjunction with 
    OSG::FaceIterator::getIndex to record a position in the iteration and
    later return to it.
*/
void FaceIterator::seek(Int32 index)
{
    setToBegin();
    
    while(getIndex() != index)
        ++(*this);
}

/*! Set the iterator to the beginning of the geometry. Is primarily used by
    OSG::Geometry::beginFaces, but can also be used to quickly recycle an
    iterator.
*/
void FaceIterator::setToBegin(void)
{
    PrimitiveIterator::setToBegin();
    _faceIndex = 0;
    startPrim();
}

/*! Set the iterator to the end of the geometry. Is primarily used by
    OSG::Geometry::endFaces, but can also be used to quickly recycle an
    iterator.
*/
void FaceIterator::setToEnd(void)
{
    PrimitiveIterator::setToEnd();
    _actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

FaceIterator& FaceIterator::operator =(const FaceIterator &source)
{
    if(this == &source)
        return *this;
    
    *static_cast<Inherited *>(this) = source;

    this->_faceIndex            = source._faceIndex;
    this->_actPrimIndex         = source._actPrimIndex;
    this->_facePntIndex[0]      = source._facePntIndex[0];
    this->_facePntIndex[1]      = source._facePntIndex[1];
    this->_facePntIndex[2]      = source._facePntIndex[2];
    this->_facePntIndex[3]      = source._facePntIndex[3];

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool FaceIterator::operator <(const FaceIterator &other) const
{
    return 
          (*static_cast<const Inherited *>(this) <  other) ||
        ( (*static_cast<const Inherited *>(this) == other)             &&
          _actPrimIndex                          <  other._actPrimIndex);
}

bool FaceIterator::operator ==(const FaceIterator &other) const
{
    if(isAtEnd() && other.isAtEnd())
        return true;

    if(isAtEnd() || other.isAtEnd())
        return false;

    return 
        (*static_cast<const Inherited *>(this) == other              ) &&
        _actPrimIndex                          == other._actPrimIndex;
}

bool FaceIterator::operator !=(const FaceIterator &other) const
{
    return !(*this == other);
}
