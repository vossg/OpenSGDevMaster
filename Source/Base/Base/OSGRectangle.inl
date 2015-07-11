/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------* \
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
 * Implementation based on the original thesis work by Julien Koenen         *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/


OSG_BEGIN_NAMESPACE

template<typename T> inline
Rectangle2<T>::Rectangle2(T x0, T y0, T x1, T y1) :
    _x0(x0),
    _y0(y0),
    _x1(x1),
    _y1(y1)
{
}


template<typename T> inline
Rectangle2<T>::Rectangle2(const PointType &p, 
                                T          width, 
                                T          height) :
    _x0(p[0]       ),
    _y0(p[1]       ),

    _x1(_x0 + width ),
    _y1(_y0 + height)
{
}


template<typename T> inline
Rectangle2<T>::Rectangle2(const PointType& p, 
                          const PointType& s) :
    _x0(p[0]     ),
    _y0(p[1]     ),

    _x1(_x0 + s[0]),
    _y1(_y0 + s[1])
{
}


template<typename T> inline
T Rectangle2<T>::getWidth(void) const
{
    if(_x1 >= _x0)
    {
        return _x1 - _x0;
    }
    else
    {
        return 0;
    }
}


template<typename T> inline
T Rectangle2<T>::getHeight(void) const
{
    if(_y1 >= _y0)
    {
        return _y1 - _y0;
    }
    else
    {
        return 0;
    }
}


template<typename T> inline
void Rectangle2<T>::add(T x, T y)
{
    _x0  += x;
    _x1  += x;
    
    _y0  += y;
    _y1  += y;
}


template<typename T> inline
void Rectangle2<T>::add(const PointType &p)
{
    add(p[0], p[1]);
}


template<typename T> inline  
void Rectangle2<T>::extendBy(T x, T y)
{
    if (isEmpty()) {
        // workaround for 'weak' isEmpty() function:
        if (_x0 == 0 && _x1==0) { _x0 = x; _x1 = x; }
        if (_y0 == 0 && _y1==0) { _y0 = y; _y1 = y; }
    }

    _x0  = (_x0 > x) ? x : _x0;
    _x1  = (_x1 < x) ? x : _x1;
    
    _y0  = (_y0 > y) ? y : _y0;
    _y1  = (_y1 < y) ? y : _y1;
}

template<typename T> inline  
void Rectangle2<T>::extendBy(const PointType &p)
{
    extendBy(p[0], p[1]);
}


template<typename T> inline
bool Rectangle2<T>::contains(T x, T y) const
{
    return (x >= _x0) && (x < _x1) && (y >= _y0) && (y < _y1);
}


template<typename T> inline  
bool Rectangle2<T>::contains(const PointType &p) const
{
    return contains(p[0], p[1]);
}


template<typename T> inline
bool Rectangle2<T>::intersects(const Rectangle2 &r) const
{
    return !getIntersection(*this, r).isEmpty();
}


template<typename T> inline
bool Rectangle2<T>::isEmpty(void) const
{
    return (_x0 >= _x1) || (_y0 >= _y1);
}


template<typename T> inline
void Rectangle2<T>::grow(T x)
{
    _x0  -= x;
    _y0  -= x;
    _x1  += x;
    _y1  += x;
}


template<typename T> inline 
void Rectangle2<T>::shrink(T x)
{
    _x0 += x;
    _y0 += x;
    _x1 -= x;
    _y1 -= x;
}


template<typename T> inline 
void Rectangle2<T>::crop(const Rectangle2<T> &boundary, 
                         const T             &borderSize)
{
    _x0 = std::max(_x0, boundary._x0 + borderSize);
    _x1 = std::min(_x1, boundary._x1 - borderSize);      
    _y0 = std::max(_y0, boundary._y0 + borderSize);
    _y1 = std::min(_y1, boundary._y1 - borderSize);
    
    if(isEmpty() == true)
    {
        clear();
    }
}


template<typename T> inline 
typename Rectangle2<T>::PointType Rectangle2<T>::getTopLeft(void) const
{
    return PointType(_x0, _y0);
}


template<typename T> inline 
typename Rectangle2<T>::PointType Rectangle2<T>::getTopRight(void) const
{
    return PointType(_x1, _y0);
}


template<typename T> inline 
typename Rectangle2<T>::PointType Rectangle2<T>::getBottomLeft(void) const
{
    return PointType(_x0, _y1);
}


template<typename T> inline 
typename Rectangle2<T>::PointType Rectangle2<T>::getBottomRight(void) const
{
    return PointType(_x1, _y1);
}

template<typename T> inline 
T Rectangle2<T>::getLeft(void) const
{
    return this->_x0;
}

template<typename T> inline 
T Rectangle2<T>::getRight(void) const
{
    return this->_x1;
}

template<typename T> inline 
T Rectangle2<T>::getBottom(void) const
{
    return this->_y1;
}

template<typename T> inline 
T Rectangle2<T>::getTop(void) const
{
    return this->_y0;
}


template<typename T> inline 
void Rectangle2<T>::clear(void)
{
    _x0 = 0;
    _x1 = 0;
    _y0 = 0;
    _y1 = 0;
}



template<typename T> inline  
void Rectangle2<T>::setBounds(T x, T y, T width, T height)
{
    _x0 = x;
    _y0 = y;
    _x1 = x + width;
    _y1 = y + height;
}


template<typename T> inline 
void Rectangle2<T>::setBounds(const PointType &p, T width, T height)
{
    setBounds(p[0], p[1], width, height);
}



template<typename T> inline  
void Rectangle2<T>::setBounds(const PointType &p, const PointType &s)
{
    setBounds(p[0], p[1], s[0], s[1]);
}


template<typename T> inline  
void Rectangle2<T>::setValues(T x0, T y0, T x1, T y1)
{
    this->_x0 = x0;
    this->_y0 = y0;
    this->_x1 = x1;
    this->_y1 = y1;
}


template<typename T> inline  
void Rectangle2<T>::setOrigin(T x, T y)
{
    setBounds(x, y, getWidth(), getHeight());
}


template<typename T> inline  
void Rectangle2<T>::setOrigin(const PointType &p)
{
    setOrigin(p[0], p[1]);
}


template<typename T> inline 
typename Rectangle2<T>::PointType Rectangle2<T>::getOrigin(void) const
{
    return PointType(_x0, _y0);
}


template<typename T> inline  
void Rectangle2<T>::setSize(T width, T height)
{
    setBounds(_x0, _y0, width, height);
}


template<typename T> inline  
void Rectangle2<T>::setSize(const PointType &p)
{
    setSize(p[0], p[1]);
}



template<typename T> inline 
typename Rectangle2<T>::PointType Rectangle2<T>::getSize(void) const
{
    return PointType(getWidth(), getHeight());
}



template<typename T> inline  
bool Rectangle2<T>::operator ==(const Rectangle2 &rhs) const
{
    if(fabsf(_x0 - rhs._x0) > TypeTraits<T>::getDefaultEps())
    {
        return false;
    }
    if(fabsf(_y0 - rhs._y0) > TypeTraits<T>::getDefaultEps())
    {
        return false;
    }
    if(fabsf(_x1 - rhs._x1) > TypeTraits<T>::getDefaultEps())
    {
        return false;
    }
    if(fabsf(_y1 - rhs._y1) > TypeTraits<T>::getDefaultEps())
    {
        return false;
    }

    return true;
}


template<typename T> inline  
bool Rectangle2<T>::operator !=(const Rectangle2 &rhs) const
{
    return !(*this == rhs);
}



template<typename T> inline 
Rectangle2<T> getIntersection(const Rectangle2<T> &lhs, 
                              const Rectangle2<T> &rhs)
{
    Rectangle2<T> result;
    
    result._x0 = std::max(lhs._x0, rhs._x0);
    result._y0 = std::max(lhs._y0, rhs._y0);
    result._x1 = std::min(lhs._x1, rhs._x1);
    result._y1 = std::min(lhs._y1, rhs._y1);
    
    if((result._x0 > result._x1) || (result._y0 > result._y1))
    {
        // No Intersection..
        result.clear();
    }
    
    return result;
}



template<typename T> inline 
Rectangle2<T> getUnion(const Rectangle2<T> &lhs, 
                       const Rectangle2<T> &rhs)
{
    Rectangle2<T> result;
    
    result._x0 = std::min(lhs._x0, rhs._x0);
    result._y0 = std::min(lhs._y0, rhs._x0);
    result._x1 = std::max(lhs._x1, rhs._x1);
    result._y1 = std::max(lhs._y1, rhs._y1);

    return result;  
}

OSG_END_NAMESPACE
