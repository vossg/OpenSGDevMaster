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


#ifndef _OSGLINEITERATOR_H_
#define _OSGLINEITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGNodeCore.h"
#include "OSGGeoProperty.h"
#include "OSGPrimitiveIterator.h"

OSG_BEGIN_NAMESPACE

/*! \brief Geometry Iterator for triangles. See \ref 
           PageSystemGeometryIterators for a description.

    \ingroup GrpDrawablesGeometryIterators
    \ingroup GrpLibOSGDrawables
 */

class OSG_DRAWABLE_DLLMAPPING LineIterator : public PrimitiveIterator
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "LineIterator"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LineIterator(void);
    LineIterator(LineIterator   const &source);
    LineIterator(Geometry       const *geo   );
    LineIterator(Node         * const  geo   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LineIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */
    
    inline Int32        getIndex                (void       ) const;
    
    inline Int32        getPositionIndex        (Int32 which) const;
    inline Pnt3f        getPosition             (Int32 which) const;

    inline Int32        getNormalIndex          (Int32 which) const;
    inline Vec3f        getNormal               (Int32 which) const;

    inline Int32        getColorIndex           (Int32 which) const;
    inline Color3f      getColor                (Int32 which) const;

    inline Int32        getSecondaryColorIndex  (Int32 which) const;
    inline Color3f      getSecondaryColor       (Int32 which) const;

    inline Int32        getTexCoordsIndex       (Int32 which) const;
    inline Vec2f        getTexCoords            (Int32 which) const;
    inline Int32        getTexCoordsIndex1      (Int32 which) const;
    inline Vec2f        getTexCoords1           (Int32 which) const;
    inline Int32        getTexCoordsIndex2      (Int32 which) const;
    inline Vec2f        getTexCoords2           (Int32 which) const;
    inline Int32        getTexCoordsIndex3      (Int32 which) const;
    inline Vec2f        getTexCoords3           (Int32 which) const;
    inline Int32        getTexCoordsIndex4      (Int32 which) const;
    inline Vec2f        getTexCoords4           (Int32 which) const;
    inline Int32        getTexCoordsIndex5      (Int32 which) const;
    inline Vec2f        getTexCoords5           (Int32 which) const;
    inline Int32        getTexCoordsIndex6      (Int32 which) const;
    inline Vec2f        getTexCoords6           (Int32 which) const;
    inline Int32        getTexCoordsIndex7      (Int32 which) const;
    inline Vec2f        getTexCoords7           (Int32 which) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Operators                              */
    /*! \{                                                                 */

    void operator ++(void);
    void seek(Int32 index);

    LineIterator & operator =(const LineIterator &source);
    bool operator < (const LineIterator &other) const;
    bool operator == (const LineIterator &other) const;
    bool operator != (const LineIterator &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef PrimitiveIterator Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */
          
    void setToBegin(void);
    void setToEnd(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class Geometry;

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    Int32           _lineIndex;
    UInt32          _actPrimIndex;
    Int32           _linePntIndex[2];

    /*! \}                                                                 */
    
    void startPrim(void);
};

typedef LineIterator *LineIteratorP;

OSG_END_NAMESPACE

#include "OSGLineIterator.inl"

#endif /* _OSGLINEITERATOR_H_ */
