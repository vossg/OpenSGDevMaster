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


#ifndef _OSGFACEITERATOR_H_
#define _OSGFACEITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGNodeCore.h"
#include "OSGDrawableDef.h"
#include "OSGGeoProperty.h"
#include "OSGPrimitiveIterator.h"

OSG_BEGIN_NAMESPACE

/*! \brief Geometry Iterator for faces (tris and quads). See \ref 
           PageSystemGeometryIterators for a description.

    \ingroup GrpDrawablesGeometryIterators
    \ingroup GrpLibOSGDrawables
 */

class OSG_DRAWABLE_DLLMAPPING FaceIterator : public PrimitiveIterator
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "FaceIterator"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */  

    FaceIterator(void);
    FaceIterator(FaceIterator   const &source);
    FaceIterator(Geometry       const *geo   );
    FaceIterator(Node         * const  geo   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~FaceIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */
    
    inline Int32        getIndex                (void       ) const;
    inline Int32        getIndex                (Int32 which) const;

    inline UInt32       getLength               (void       ) const;
    
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

    void           seek        (Int32 index);    
    void           operator ++ (void);
    FaceIterator & operator =  (const FaceIterator &source);
    bool           operator <  (const FaceIterator &other) const;
    bool           operator == (const FaceIterator &other) const;
    bool           operator != (const FaceIterator &other) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setToBegin(void);
    void setToEnd  (void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef PrimitiveIterator Inherited;
          
   /*==========================  PRIVATE  ================================*/    
  private:
  
    Int32             _faceIndex;
    UInt32            _actPrimIndex;
    Int32             _facePntIndex[4];
    
    void startPrim(void);
};

typedef FaceIterator *FaceIteratorP;

OSG_END_NAMESPACE

#include "OSGFaceIterator.inl"

#endif /* _OSGTRIANGLEITERATOR_H_ */
