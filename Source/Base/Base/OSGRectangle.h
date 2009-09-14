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
 * Implementation based on the original thesis work by Julien Koenen         *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGRECTANGLE_H_
#define _OSGRECTANGLE_H_

#include "OSGVector.h"
#include <ostream>

//-----------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template< typename T > class Rectangle2
{
    /*==========================  PUBLIC  =================================*/

  public:
    
    typedef Point< T, 2 > PointType;

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */
    
    explicit Rectangle2(      T          x0 = 0, 
                              T          y0 = 0, 
                              T          x1 = 0, 
                              T          y1 = 0);

    explicit Rectangle2(const PointType &p, 
                              T          width, 
                              T          height );

    explicit Rectangle2(const PointType &p, 
                        const PointType &s );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    T    getWidth  (      void         ) const;
    T    getHeight (      void         ) const;
    
    void add       (      T           x, 
                          T           y);
    void add       (const PointType  &p);


    void extendBy  (    T             x, 
                        T             y);
    void extendBy  (const PointType  &p);
    
    bool contains  (      T           x, 
                          T           y) const;
    bool contains  (const PointType  &p) const;
    bool intersects(const Rectangle2 &r) const;
    
    bool isEmpty   (      void         ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    void grow  (      T           x             );
    void shrink(      T           x             );
    
    void crop  (const Rectangle2 &boundary, 
                const T          &borderSize = 0);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */
    
    PointType getTopLeft    (void) const;
    PointType getTopRight   (void) const;
    PointType getBottomLeft (void) const;
    PointType getBottomRight(void) const;

    T getLeft  (void) const;
    T getRight (void) const;
    T getBottom(void) const;
    T getTop   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */
    
    void clear    (      void             );
    
    void setBounds(      T          x, 
                         T          y, 
                         T          width, 
                         T          height);
    void setBounds(const PointType &p, 
                         T          width, 
                         T          height);
    void setBounds(const PointType &p, 
                   const PointType &size  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */
    
    void      setValues(      T          x0, 
                              T          y0, 
                              T          x1, 
                              T          y1    );
    
    void      setOrigin(      T          x,
                              T          y     );
    void      setOrigin(const PointType& p     );
    PointType getOrigin(      void             ) const;
    
    void      setSize  (      T          width, 
                              T          height);
    void      setSize  (const PointType &s     );
    PointType getSize  (      void             ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */
    
    bool operator==(const Rectangle2 &rhs) const;
    bool operator!=(const Rectangle2 &rhs) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    // the rect encloses all points (x,y) with x in [x0,x1[ and y in [y0,y1[

    T x0;
    T y0;
    T x1;
    T y1;

    /*! \}                                                                 */
    /*==========================  PROTECTRED  =============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};

/*! \relates Rectangle2
 */
template<typename T> inline 
std::ostream &operator<<(      std::ostream       &out, 
                         const OSG::Rectangle2<T> &rect)
{
    return out << rect.x0 << "," 
               << rect.y0 << "," 
               << rect.x1 << "," 
               << rect.y1;          
}


/*! \relates Rectangle2
 */
template<typename T> inline 
OSG::Rectangle2<T> alignRectangle (
    const          OSG::Rectangle2<T>            &rect, 
    const typename OSG::Rectangle2<T>::PointType &alignment);

/*! \relates Rectangle2
 */
template<typename T> inline 
OSG::Rectangle2<T> getIntersection(const OSG::Rectangle2<T> &lhs, 
                                   const OSG::Rectangle2<T> &rhs);

/*! \relates Rectangle2
 */
template<typename T> inline 
OSG::Rectangle2<T> getUnion       (const OSG::Rectangle2<T> &lhs, 
                                   const OSG::Rectangle2<T> &rhs);

/*---------------------------------------------------------------------*/
/*! \name Rectangle Types                                              */
/*! \{                                                                 */

/*! \var typedef OSG::Rectangle2<OSG::Real32> Rectangle2f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Rectangle2
 */
typedef OSG::Rectangle2<OSG::Real32> Rectangle2f;


/*! \var typedef OSG::Rectangle2<OSG::Real64> Rectangle2d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Rectangle2
 */
typedef OSG::Rectangle2<OSG::Real64> Rectangle2d;


/*! \var typedef OSG::Rectangle2<OSG::Int32 > Rectangle2i;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Rectangle2
 */
typedef OSG::Rectangle2<OSG::Int32 > Rectangle2i;

/*! \} */

OSG_END_NAMESPACE

#include "OSGRectangle.inl"

#endif // #ifdef _OSGRECTANGLE_H_

