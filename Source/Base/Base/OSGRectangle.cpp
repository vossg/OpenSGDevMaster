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

#include "OSGRectangle.h"
#include <algorithm>

OSG_BEGIN_NAMESPACE

template<typename T> 
Rectangle2<T>::Rectangle2(T x0, T y0, T x1, T y1) 
{
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
}


template<typename T> 
Rectangle2<T>::Rectangle2(const PointType &p, 
                                T          width, 
                                T          height)
{
    x0 = p[0];
    y0 = p[1];

    x1 = x0 + width;
    y1 = y0 + height;
}


template<typename T> 
Rectangle2<T>::Rectangle2(const PointType& p, 
                          const PointType& s)
{
    x0 = p[0];
    y0 = p[1];

    x1 = x0 + s[0];
    y1 = y0 + s[1];
}


template<typename T>
T Rectangle2<T>::getWidth(void) const
{
    if(x1 >= x0)
    {
        return x1 - x0;
    }
    else
    {
        return 0;
    }
}


template<typename T>
T Rectangle2<T>::getHeight(void) const
{
    if(y1 >= y0)
    {
        return y1 - y0;
    }
    else
    {
        return 0;
    }
}


template<typename T>  
void Rectangle2<T>::add(T x, T y)
{
    x0  += x;
    x1  += x;
    
    y0  += y;
    y1  += y;
}


template<typename T>  
void Rectangle2<T>::add(const PointType &p)
{
    add(p[0], p[1]);
}



template<typename T>
bool Rectangle2<T>::contains(T x, T y) const
{
    return (x >= x0) && (x < x1) && (y >= y0) && (y < y1);
}


template<typename T>  
bool Rectangle2<T>::contains(const PointType &p) const
{
    return contains(p[0], p[1]);
}


template<typename T>
bool Rectangle2<T>::intersects(const Rectangle2 &r) const
{
    return !getIntersection(*this, r).isEmpty();
}


template<typename T>
bool Rectangle2<T>::isEmpty(void) const
{
    return (x0 >= x1) || (y0 >= y1);
}


template<typename T>
void Rectangle2<T>::grow(T x)
{
    x0  -= x;
    y0  -= x;
    x1  += x;
    y1  += x;
}


template<typename T> 
void Rectangle2<T>::shrink(T x)
{
    x0 += x;
    y0 += x;
    x1 -= x;
    y1 -= x;
}


template<typename T> 
void Rectangle2<T>::crop(const Rectangle2<T> &boundary, 
                         const T             &borderSize)
{
    x0 = std::max(x0, boundary.x0 + borderSize);
    x1 = std::min(x1, boundary.x1 - borderSize);      
    y0 = std::max(y0, boundary.y0 + borderSize);
    y1 = std::min(y1, boundary.y1 - borderSize);
    
    if(isEmpty() == true)
    {
        clear();
    }
}


template<typename T> 
typename Rectangle2<T>::PointType Rectangle2<T>::getTopLeft(void) const
{
    return PointType(x0, y0);
}


template<typename T> 
typename Rectangle2<T>::PointType Rectangle2<T>::getTopRight(void) const
{
    return PointType(x1, y0);
}


template<typename T> 
typename Rectangle2<T>::PointType Rectangle2<T>::getBottomLeft(void) const
{
    return PointType(x0, y1);
}


template<typename T> 
typename Rectangle2<T>::PointType Rectangle2<T>::getBottomRight(void) const
{
    return PointType(x1, y1);
}


template<typename T> 
void Rectangle2<T>::clear(void)
{
    x0 = 0;
    x1 = 0;
    y0 = 0;
    y1 = 0;
}



template<typename T>  
void Rectangle2<T>::setBounds(T x, T y, T width, T height)
{
    x0 = x;
    y0 = y;
    x1 = x + width;
    y1 = y + height;
}


template<typename T> 
void Rectangle2<T>::setBounds(const PointType &p, T width, T height)
{
    setBounds(p[0], p[1], width, height);
}



template<typename T>  
void Rectangle2<T>::setBounds(const PointType &p, const PointType &s)
{
    setBounds(p[0], p[1], s[0], s[1]);
}


template<typename T>  
void Rectangle2<T>::setValues(T x0, T y0, T x1, T y1)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
}


template<typename T>  
void Rectangle2<T>::setOrigin(T x, T y)
{
    setBounds(x, y, getWidth(), getHeight());
}


template<typename T>  
void Rectangle2<T>::setOrigin(const PointType &p)
{
    setOrigin(p[0], p[1]);
}


template<typename T> 
typename Rectangle2<T>::PointType Rectangle2<T>::getOrigin(void) const
{
    return PointType(x0, y0);
}


template<typename T>  
void Rectangle2<T>::setSize(T width, T height)
{
    setBounds(x0, y0, width, height);
}


template<typename T>  
void Rectangle2<T>::setSize(const PointType &p)
{
    setSize(p[0], p[1]);
}



template<typename T> 
typename Rectangle2<T>::PointType Rectangle2<T>::getSize(void) const
{
    return PointType(getWidth(), getHeight());
}



template<typename T>  
bool Rectangle2<T>::operator ==(const Rectangle2 &rhs) const
{
    if(fabsf(x0 - rhs.x0) > Eps)
    {
        return false;
    }
    if(fabsf(y0 - rhs.y0) > Eps)
    {
        return false;
    }
    if(fabsf(x1 - rhs.x1) > Eps)
    {
        return false;
    }
    if(fabsf(y1 - rhs.y1) > Eps)
    {
        return false;
    }

    return true;
}


template<typename T>  
bool Rectangle2<T>::operator !=(const Rectangle2 &rhs) const
{
    return !(*this == rhs);
}



template<typename T> 
Rectangle2<T> getIntersection(const Rectangle2<T> &lhs, 
                              const Rectangle2<T> &rhs)
{
    Rectangle2<T> result;
    
    result.x0 = std::max(lhs.x0, rhs.x0);
    result.y0 = std::max(lhs.y0, rhs.y0);
    result.x1 = std::min(lhs.x1, rhs.x1);
    result.y1 = std::min(lhs.y1, rhs.y1);
    
    if((result.x0 > result.x1) || (result.y0 > result.y1))
    {
        // No Intersection..
        result.clear();
    }
    
    return result;
}



template<typename T> 
Rectangle2<T> getUnion(const Rectangle2<T> &lhs, 
                       const Rectangle2<T> &rhs)
{
    Rectangle2<T> result;
    
    result.x0 = std::min(lhs.x0, rhs.x0);
    result.y0 = std::min(lhs.y0, rhs.x0);
    result.x1 = std::max(lhs.x1, rhs.x1);
    result.y1 = std::max(lhs.y1, rhs.y1);

    return result;  
}


template class Rectangle2<Real32>;
template class Rectangle2<Real64>;
template class Rectangle2<Int32 >;


template Rectangle2<Real32> getIntersection(const Rectangle2<Real32> &lhs, 
                                            const Rectangle2<Real32> &rhs);
template Rectangle2<Real32> getUnion       (const Rectangle2<Real32> &lhs, 
                                            const Rectangle2<Real32> &rhs);

template Rectangle2<Real64> getIntersection(const Rectangle2<Real64> &lhs,
                                            const Rectangle2<Real64> &rhs);
template Rectangle2<Real64> getUnion       (const Rectangle2<Real64> &lhs, 
                                            const Rectangle2<Real64> &rhs);

template Rectangle2<Int32 > getIntersection(const Rectangle2<Int32 > &lhs, 
                                            const Rectangle2<Int32 > &rhs);
template Rectangle2<Int32 > getUnion       (const Rectangle2<Int32 > &lhs, 
                                            const Rectangle2<Int32 > &rhs);

OSG_END_NAMESPACE
