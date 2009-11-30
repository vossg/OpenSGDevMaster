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
#include "OSGGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#if 0
#include "OSGGeoPumpGroup.h"
#endif

#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

#if 0
class GeoPumpGroup;
#endif

class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;
class LineIterator;
class EdgeIterator;

class DrawEnv;

/*! \brief Geometry class. See \ref 
           PageWindowGLUTGeometry for a description.
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
    /*! \name                IndexMapping Constants                        */
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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Property Access                             */
    /*! \{                                                                 */

    inline GeoIntegralPropertyPtr getTypes          (void) const;
    inline GeoIntegralPropertyPtr getLengths        (void) const;
    inline GeoVectorPropertyPtr   getPositions      (void) const;
    inline GeoVectorPropertyPtr   getNormals        (void) const;
    inline GeoVectorPropertyPtr   getColors         (void) const;
    inline GeoVectorPropertyPtr   getSecondaryColors(void) const;
    inline GeoVectorPropertyPtr   getTexCoords      (void) const;
    inline GeoVectorPropertyPtr   getTexCoords1     (void) const;
    inline GeoVectorPropertyPtr   getTexCoords2     (void) const;
    inline GeoVectorPropertyPtr   getTexCoords3     (void) const;
    inline GeoVectorPropertyPtr   getTexCoords4     (void) const;
    inline GeoVectorPropertyPtr   getTexCoords5     (void) const;
    inline GeoVectorPropertyPtr   getTexCoords6     (void) const;
    inline GeoVectorPropertyPtr   getTexCoords7     (void) const;
   

    inline void setTypes          (GeoIntegralPropertyPtrConstArg value);
    inline void setLengths        (GeoIntegralPropertyPtrConstArg value);
    inline void setPositions      (GeoVectorPropertyPtrConstArg   value);
    inline void setNormals        (GeoVectorPropertyPtrConstArg   value);
    inline void setColors         (GeoVectorPropertyPtrConstArg   value);
    inline void setSecondaryColors(GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords      (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords1     (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords2     (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords3     (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords4     (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords5     (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords6     (GeoVectorPropertyPtrConstArg   value);
    inline void setTexCoords7     (GeoVectorPropertyPtrConstArg   value);
   
    void setMaterial       (const MaterialPtr               &value);

    inline void setProperty (GeoVectorPropertyPtrConstArg value, UInt16 index);

    inline void setIndex     (GeoIntegralPropertyPtrConstArg value, 
                              UInt16 index);

    inline GeoVectorPropertyPtr   getProperty(UInt16 index) const;

    inline GeoIntegralPropertyPtr getIndex(UInt16 index) const;
#if 0
    static const char *mapType          (UInt8 type);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name           Property/Index MField Changes                      */
    /*! \{                                                                 */

#if 0
    inline void resizeProperties(size_t newsize);
    inline void reserveProperties(size_t newsize);

    inline void resizePropIndices(size_t newsize);
    inline void reservePropIndices(size_t newsize);
#endif
    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name          Backwards Compatibility Helpers                     */
    /*! \{                                                                 */

#if 0
    inline void setIndices(GeoIntegralPropertyPtrConstArg value);  
    
    inline GeoIntegralPropertyPtr getIndices(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Iterator Access                        */
    /*! \{                                                                 */

    TriangleIterator   beginTriangles   (void) const;
    TriangleIterator   endTriangles     (void) const;

    PrimitiveIterator  beginPrimitives  (void) const;
    PrimitiveIterator  endPrimitives    (void) const;
#if 0
    FaceIterator       beginFaces       (void) const;
    FaceIterator       endFaces         (void) const;

    LineIterator       beginLines       (void) const;
    LineIterator       endLines         (void) const;

    EdgeIterator       beginEdges       (void) const;
    EdgeIterator       endEdges         (void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    virtual Action::ResultE drawPrimitives      (DrawEnv        *pEnv  );

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

#if 0
//    GeoPumpGroup::PropertyCharacteristics 
//                            calcPropertyCharacteristics(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Stats                                    */
    /*! \{                                                                 */

    virtual void fill(DrawableStatsAttachmentPtrArg pStat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Global Pump Group Handling                      */
    /*! \{                                                                 */
    
    
#if 0
    typedef std::vector<GeoPumpGroup*> PumpGroupStorage;
    
    static PumpGroupStorage &getPumpGroupStorage(void);
#endif

    /*! \}                                                                 */ 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeometryBase.

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

           void handleClassicGL       (DrawEnv                 *pEnv, 
                                       UInt32                   id,
                                       Window::GLObjectStatusE  mode);

    static void handleClassicDestroyGL(DrawEnv                 *pEnv, 
                                       UInt32                   id, 
                                       Window::GLObjectStatusE  mode);

           void handleAttGL           (DrawEnv                 *pEnv, 
                                       UInt32                   id,
                                       Window::GLObjectStatusE  mode);
    
    static void handleAttDestroyGL    (DrawEnv                 *pEnv, 
                                       UInt32                   id, 
                                       Window::GLObjectStatusE  mode);

    void onCreate (const Geometry *source = NULL);
    void onDestroy(UInt32 id);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeometryBase;

    static void initMethod(InitPhase ePhase);

#if 0
    static PumpGroupStorage _pumps;
#endif

    inline 
    void fixParents(FieldContainerAttachmentPtrConstArg oldvalue,
                    FieldContainerAttachmentPtrConstArg newvalue, 
                    FieldContainerPtr                   obj,
                    UInt32                              fieldId);

    void freeParent(FieldContainerAttachmentPtr  value,
                    FieldContainerPtr            obj);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Geometry &source);
};

typedef Geometry                 *GeometryP;

OSG_END_NAMESPACE

#include "OSGGeometryBase.inl"
#include "OSGGeometry.inl"

#endif /* _OSGGEOMETRY_H_ */
