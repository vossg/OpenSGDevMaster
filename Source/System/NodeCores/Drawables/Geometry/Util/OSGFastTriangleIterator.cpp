/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGFastTriangleIterator.h"

OSG_BEGIN_NAMESPACE

FastTriangleIterator::FastTriangleIterator(void) :
    Inherited    (),
    _triIndex    (0),
    _actPrimIndex(0),
    _triPntIndex ()
{
    _triPntIndex[0] = 0;
    _triPntIndex[1] = 0;
    _triPntIndex[2] = 0;
}

FastTriangleIterator::FastTriangleIterator(const FastTriangleIterator &source) :
    Inherited    (source              ),
    _triIndex    (source._triIndex    ),
    _actPrimIndex(source._actPrimIndex),
    _triPntIndex ()
{
    _triPntIndex[0] = source._triPntIndex[0];
    _triPntIndex[1] = source._triPntIndex[1];
    _triPntIndex[2] = source._triPntIndex[2];
}

FastTriangleIterator::FastTriangleIterator(const Geometry *geo) :
    Inherited    (),
    _triIndex    (0),
    _actPrimIndex(0),
    _triPntIndex ()
{
    _triPntIndex[0] = 0;
    _triPntIndex[1] = 0;
    _triPntIndex[2] = 0;

    setGeo(geo);
}

FastTriangleIterator::FastTriangleIterator(const Node *node) :
    Inherited    (),
    _triIndex    (0),
    _actPrimIndex(0),
    _triPntIndex ()
{
    _triPntIndex[0] = 0;
    _triPntIndex[1] = 0;
    _triPntIndex[2] = 0;

    setGeo(node);
}

/* virtual */
FastTriangleIterator::~FastTriangleIterator(void)
{
}

/* virtual */ void
FastTriangleIterator::setToBegin(void)
{
    Inherited::setToBegin();
    _triIndex = 0;

    startPrim();
}

/* virtual */ void
FastTriangleIterator::setToEnd(void)
{
    Inherited::setToEnd();
    _actPrimIndex = 0;
}

FastTriangleIterator &
FastTriangleIterator::operator++(void)
{
    if(isAtEnd())
        return *this;

    ++_triIndex;

    if(_actPrimIndex >= getLength())
    {
        ++(static_cast<Inherited&>(*this));
        startPrim();

        return *this;
    }

    switch(getType())
    {
    case GL_TRIANGLES:
        _triPntIndex[0] = _actPrimIndex++;
        _triPntIndex[1] = _actPrimIndex++;
        _triPntIndex[2] = _actPrimIndex++;
        break;

    case GL_QUAD_STRIP:
    case GL_TRIANGLE_STRIP:
    {
        if(_actPrimIndex & 1)
        {
            _triPntIndex[0] = _triPntIndex[2];
        }
        else
        {
            _triPntIndex[1] = _triPntIndex[2];
        }
        _triPntIndex[2] = _actPrimIndex++;
    }
    break;

    case GL_POLYGON:
    case GL_TRIANGLE_FAN:
        _triPntIndex[1] = _triPntIndex[2];
        _triPntIndex[2] = _actPrimIndex++;
        break;

    case GL_QUADS:
        if(_actPrimIndex & 1)
        {
            _triPntIndex[1] = _triPntIndex[2];
            _triPntIndex[2] = _actPrimIndex++;
        }
        else
        {
            _triPntIndex[0] = _actPrimIndex++;
            _triPntIndex[1] = _actPrimIndex++;
            _triPntIndex[2] = _actPrimIndex++;
        }
        break;

    default:
    {
        SWARNING << "TriangleIterator::++: encountered " 
                 << "unknown primitive type " 
                 << getType() << ", ignoring!" << std::endl;
        startPrim();
    }
    break;
    }

    return *this;
}

FastTriangleIterator &
FastTriangleIterator::seek(Int32 index)
{
    if(index < getIndex())
        setToBegin();

    if(index > getIndex())
    {
        UInt32 tri      = getTriInActPrim ();
        UInt32 numTris  = getTrisInActPrim();

        if(tri >= numTris)
        {
            ++(static_cast<Inherited&>(*this));
            startPrim();

            tri     = getTriInActPrim ();
            numTris = getTrisInActPrim();
        }

        Int32 leftTris = numTris - tri - 1;

        // skip whole primitives
        while(index > _triIndex + leftTris)
        {
            _triIndex += leftTris + 1;
            ++(static_cast<Inherited&>(*this));
            startPrim();

            tri      = 0;
            leftTris = getTrisInActPrim() - 1;
        }

        tri       += index - getIndex();
        _triIndex =  index;

        // setup members
        if(!isAtEnd() && tri > 0)
        {
            switch(getType())
            {
            case GL_TRIANGLES:
                _actPrimIndex  = 3 * tri + 3;
                _triPntIndex[0] = _actPrimIndex - 3;
                _triPntIndex[1] = _actPrimIndex - 2;
                _triPntIndex[2] = _actPrimIndex - 1;
                break;

            case GL_QUADS:
                if(tri % 2)
                {
                    _actPrimIndex  = 2 * tri + 2;
                    _triPntIndex[0] = _actPrimIndex - 4;
                    _triPntIndex[1] = _actPrimIndex - 2;
                    _triPntIndex[2] = _actPrimIndex - 1;
                }
                else
                {
                    _actPrimIndex  = 2 * tri + 3;
                    _triPntIndex[0] = _actPrimIndex - 3;
                    _triPntIndex[1] = _actPrimIndex - 2;
                    _triPntIndex[2] = _actPrimIndex - 1;
                }
                break;

            case GL_QUAD_STRIP:
            case GL_TRIANGLE_STRIP:
                if(tri % 2)
                {
                    _actPrimIndex  = tri + 3;
                    _triPntIndex[0] = _actPrimIndex - 2;
                    _triPntIndex[1] = _actPrimIndex - 3;
                    _triPntIndex[2] = _actPrimIndex - 1;
                }
                else
                {
                    _actPrimIndex  = tri + 3;
                    _triPntIndex[0] = _actPrimIndex - 3;
                    _triPntIndex[1] = _actPrimIndex - 2;
                    _triPntIndex[2] = _actPrimIndex - 1;
                }
                break;

            case GL_TRIANGLE_FAN:
            case GL_POLYGON:
                _actPrimIndex  = tri + 3;
                _triPntIndex[0] = 0;
                _triPntIndex[1] = _actPrimIndex - 2;
                _triPntIndex[2] = _actPrimIndex - 1;
                break;

            default:
            {
                SWARNING << "FastTriangleIterator::seek: "
                         << "encountered unknown primitive type " 
                         << getType() << ", ignoring!"
                         << std::endl;
            }
            break;
            }
        }
    }

    return *this;
}

void
FastTriangleIterator::startPrim(void)
{
    if(isAtEnd())
        return;

    _triPntIndex[0] = 0;
    _triPntIndex[1] = 1;
    _triPntIndex[2] = 2;
    _actPrimIndex   = 3;

    while(! isAtEnd())
    {
        switch(getType())
        {
        case GL_POINTS:         // non-polygon types: ignored
        case GL_LINES:
        case GL_LINE_STRIP: 
        case GL_LINE_LOOP:  
            break;

        case GL_TRIANGLES:      // polygon types
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
        case GL_QUADS:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            if(getLength() >= 3)
                return;
            break;

        default:
        {
            SWARNING << "FastTriangleIterator::startPrim: "
                     << "encountered unknown primitive type " 
                     << getType() << ", ignoring!"
                     << std::endl;
        }
        break;
        }

        ++(static_cast<Inherited&>(*this));
    }
}

UInt32
FastTriangleIterator::getTrisInActPrim(void) const
{
    UInt32 returnValue = 0;

    switch(getType())
    {
    case GL_TRIANGLES:
        assert(getLength() % 3 == 0);
        returnValue = getLength() / 3;
        break;

    case GL_QUADS:
        assert(getLength() % 4 == 0);
        returnValue = getLength() / 2;
        break;

    case GL_QUAD_STRIP:
    case GL_TRIANGLE_STRIP:
    case GL_TRIANGLE_FAN:
    case GL_POLYGON:
        assert(getLength() >= 3);
        returnValue = getLength() - 2;
        break;

    default:
    {
        SWARNING << "FastTriangleIterator::getTrisInActPrim: "
                 << "encountered unknown primitive type " 
                 << getType() << ", ignoring!"
                 << std::endl;
    }
    break;
    }

    return returnValue;
}

UInt32
FastTriangleIterator::getTriInActPrim(void) const
{
    UInt32 returnValue = 0;

    switch(getType())
    {
    case GL_TRIANGLES:
        assert(_actPrimIndex % 3 == 0);
        returnValue = _actPrimIndex / 3 - 1;
        break;

    case GL_QUADS:
        if(_actPrimIndex % 1)
        {
            returnValue = (_actPrimIndex - 3) / 2;
        }
        else
        {
            returnValue = (_actPrimIndex - 2) / 2;
        }
        break;

    case GL_QUAD_STRIP:
    case GL_TRIANGLE_STRIP:
    case GL_TRIANGLE_FAN:
    case GL_POLYGON:
        returnValue = _actPrimIndex - 3;
        break;

    default:
    {
        SWARNING << "FastTriangleIterator::getTriInActPrim: "
                 << "encountered unknown primitive type " 
                 << getType() << ", ignoring!"
                 << std::endl;
    }
    break;
    }

    return returnValue;
}

OSG_END_NAMESPACE
