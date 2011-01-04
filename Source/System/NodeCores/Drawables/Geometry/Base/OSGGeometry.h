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
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGGEOMETRY_H_
#define _OSGGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <string>

#include "OSGGeometryBase.h"

#include "OSGTypedGeoVectorProperty.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGGeoPumpGroup.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

class GeoPumpGroup;

class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;
class LineIterator;
class EdgeIterator;
class PointIterator;

class DrawEnv;

/*! \brief Geometry class. See \ref
           PageWindowGLUTGeometry for a description.
    \ingroup GrpDrawablesGeometryObj
    \ingroup GrpLibOSGDrawables
    \includebasedoc
*/

class OSG_DRAWABLE_DLLMAPPING Geometry : public GeometryBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeometryBase                             Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name               Simplification Constants                       */
    /*! \{                                                                 */

    // Maximum number of possible attributes
    static const UInt16 MaxAttribs = 16;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                IndexMapping Constants
      These are the constants used for mapping the excpliit get/set functions
      to the generic attribute data buffers used by OpenGL.
    */
    /*! \{                                                                 */

    static const UInt16 PositionsIndex       = 0;
    static const UInt16 NormalsIndex         = 2;
    static const UInt16 ColorsIndex          = 3;
    static const UInt16 SecondaryColorsIndex = 4;
    static const UInt16 TexCoordsIndex       = 8;
    static const UInt16 TexCoords1Index      = 9;
    static const UInt16 TexCoords2Index      = 10;
    static const UInt16 TexCoords3Index      = 11;
    static const UInt16 TexCoords4Index      = 12;
    static const UInt16 TexCoords5Index      = 13;
    static const UInt16 TexCoords6Index      = 14;
    static const UInt16 TexCoords7Index      = 15;

    static const UInt16 LastIndex            = 15;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Property Access                             */
    /*! \{                                                                 */

    inline GeoIntegralProperty *getTypes          (void) const;
    inline GeoIntegralProperty *getLengths        (void) const;
    inline GeoVectorProperty   *getPositions      (void) const;
    inline GeoVectorProperty   *getNormals        (void) const;
    inline GeoVectorProperty   *getColors         (void) const;
    inline GeoVectorProperty   *getSecondaryColors(void) const;
    inline GeoVectorProperty   *getTexCoords      (void) const;
    inline GeoVectorProperty   *getTexCoords1     (void) const;
    inline GeoVectorProperty   *getTexCoords2     (void) const;
    inline GeoVectorProperty   *getTexCoords3     (void) const;
    inline GeoVectorProperty   *getTexCoords4     (void) const;
    inline GeoVectorProperty   *getTexCoords5     (void) const;
    inline GeoVectorProperty   *getTexCoords6     (void) const;
    inline GeoVectorProperty   *getTexCoords7     (void) const;


    inline void setPositions      (GeoVectorProperty   * const   value);
    inline void setNormals        (GeoVectorProperty   * const   value);
    inline void setColors         (GeoVectorProperty   * const   value);
    inline void setSecondaryColors(GeoVectorProperty   * const   value);
    inline void setTexCoords      (GeoVectorProperty   * const   value);
    inline void setTexCoords1     (GeoVectorProperty   * const   value);
    inline void setTexCoords2     (GeoVectorProperty   * const   value);
    inline void setTexCoords3     (GeoVectorProperty   * const   value);
    inline void setTexCoords4     (GeoVectorProperty   * const   value);
    inline void setTexCoords5     (GeoVectorProperty   * const   value);
    inline void setTexCoords6     (GeoVectorProperty   * const   value);
    inline void setTexCoords7     (GeoVectorProperty   * const   value);

           void setMaterial       (Material            * const   value);


    inline void setProperty       (GeoVectorProperty   * const   value, 
                                   UInt16                      index);

    inline void setIndex          (GeoIntegralProperty * const value,
                                   UInt16                      index);

          Int32 getClassicGLId    (void) const;
          Int32 getAttGLId        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name           Property/Index MField Changes                      */
    /*! \{                                                                 */

    inline GeoVectorProperty   *getProperty(UInt16 index) const;

    inline GeoIntegralProperty *getIndex   (UInt16 index) const;

    static const char          *mapType    (UInt8 type  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name           Property/Index MField Changes                      */
    /*! \{                                                                 */

    inline void resizeProperties(size_t newsize);
    inline void reserveProperties(size_t newsize);

    inline void resizePropIndices(size_t newsize);
    inline void reservePropIndices(size_t newsize);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name          Backwards Compatibility Helpers                     */
    /*! \{                                                                 */

    inline void setIndices(GeoIntegralProperty * const value);

    inline GeoIntegralProperty *getIndices(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name          Backwards Compatibility Helpers                     */
    /*! \{                                                                 */

    UInt32 indexOccurrence(GeoIntegralProperty * const value) const;
    bool   isSingleIndex  (void                             ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Iterator Access                        */
    /*! \{                                                                 */

    TriangleIterator   beginTriangles   (void) const;
    TriangleIterator   endTriangles     (void) const;

    PrimitiveIterator  beginPrimitives  (void) const;
    PrimitiveIterator  endPrimitives    (void) const;

    FaceIterator       beginFaces       (void) const;
    FaceIterator       endFaces         (void) const;

    LineIterator       beginLines       (void) const;
    LineIterator       endLines         (void) const;

    EdgeIterator       beginEdges       (void) const;
    EdgeIterator       endEdges         (void) const;

    PointIterator      beginPoints      (void) const;
    PointIterator      endPoints        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    virtual void            drawPrimitives      (DrawEnv        *pEnv  );

            Action::ResultE intersect           (Action         *action);

            void            invalidateDlistCache(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */

    void               adjustVolume     (Volume & volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Pump Handling                             */
    /*! \{                                                                 */

    typedef std::vector<std::pair<GeoIntegralProperty *,
                                  std::vector<UInt16>  > > IndexBag;

    IndexBag getUniqueIndexBag(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Pump Handling                             */
    /*! \{                                                                 */

//    GeoPumpGroup::PropertyCharacteristics
//                            calcPropertyCharacteristics(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Stats                                    */
    /*! \{                                                                 */

    virtual void fill(DrawableStatsAttachment *pStat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Global Pump Group Handling                      */
    /*! \{                                                                 */


    typedef std::vector<GeoPumpGroup*> PumpGroupStorage;

    static PumpGroupStorage &getPumpGroupStorage(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GeometryBase.

    BoxVolume   _volumeCache;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Geometry(void);
    Geometry(const Geometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Geometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

           UInt32 handleClassicGL       (DrawEnv                 *pEnv, 
                                         UInt32                   id, 
                                         Window::GLObjectStatusE  mode,
                                         UInt32                   uiOptions);

    static void   handleClassicDestroyGL(DrawEnv                 *pEnv, 
                                         UInt32                   id, 
                                         Window::GLObjectStatusE  mode    );

           UInt32 handleAttGL           (DrawEnv                 *pEnv, 
                                         UInt32                   id, 
                                         Window::GLObjectStatusE  mode,
                                         UInt32                   uiOption);
    static void   handleAttDestroyGL    (DrawEnv                 *pEnv, 
                                         UInt32                   id, 
                                         Window::GLObjectStatusE  mode    );

    void onCreate(const Geometry *source = NULL);
    void onDestroy(UInt32 id);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Init                                       */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeometryBase;

    static PumpGroupStorage _pumps;
    
    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Geometry &source);
};

typedef Geometry                 *GeometryP;

OSG_END_NAMESPACE

#include "OSGGeometryBase.inl"
#include "OSGGeometry.inl"

#endif /* _OSGGEOMETRY_H_ */
