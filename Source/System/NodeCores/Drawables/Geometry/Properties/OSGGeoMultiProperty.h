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

#ifndef _OSGGEOMULTIPROPERTYDATAPROPERTY_H_
#define _OSGGEOMULTIPROPERTYDATAPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoMultiPropertyData.h"
#include "OSGGeoMultiPropertyBase.h"
#include "OSGGeoVectorPropertyConversion.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoMultiProperty class. See \ref
           PageWindowGLUTGeoMultiProperty for a description.
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING GeoMultiProperty :
    public GeoMultiPropertyBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoMultiPropertyBase                             Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                     Access                                   */
    /*! \{                                                                 */

    virtual       UInt32    getFormat    (      void             ) const;
    virtual       UInt32    getFormatSize(      void             ) const;
    virtual       UInt32    getVectorType(      void             ) const;
    virtual       UInt32    getStride    (      void             ) const;
    virtual       UInt32    getDimension (      void             ) const;
    virtual       UInt32    getSize      (      void             ) const;
    virtual       UInt32    size         (      void             ) const;
    virtual       bool      getNormalize (      void             ) const;
    virtual const UInt8    *getData      (      void             ) const;
    virtual       UInt8    *editData     (      void             );
                  MaxTypeT  getValue     (const UInt32    index  ) const;
                  void      getValue     (      MaxTypeT &val,
                                          const UInt32    index  ) const;

    virtual       void      clear        (      void             );
    virtual       void      resize       (      size_t    newsize);

    virtual       void      setFormat    (      UInt32    val    );
    virtual       void      setStride    (      UInt32    val    );
    virtual       void      setDimension (      UInt32    val    );
    virtual       void      setSize      (      UInt32    val    );
    virtual       void      setNormalize (      bool      val    );
                  void      setValue     (const MaxTypeT &val,
                                          const UInt32    index  );

    virtual GeoPropertyTransitPtr clone(void);
                                          
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass * getClass         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32            getStaticClassId (void);
    inline static  const StateChunkClass * getStaticClass   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void activate      (DrawEnv    *pEnv,
                                UInt32      index = 0);

    virtual void changeFrom    (DrawEnv    *pEnv,
                                StateChunk *old,
                                UInt32      index = 0);

    virtual void deactivate    (DrawEnv    *pEnv,
                                UInt32      index = 0);

    virtual bool isTransparent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoMultiPropertyBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoMultiProperty(void);
    GeoMultiProperty(const GeoMultiProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoMultiProperty(void);

    /*! \}                                                                 */

    virtual void getGenericValue(      MaxTypeT &val,
                                 const UInt32    index) const;
    virtual void setGenericValue(const MaxTypeT &val,
                                 const UInt32    index);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoMultiPropertyBase;

    static void initMethod(InitPhase ePhase);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoMultiProperty &source);
};

typedef GeoMultiProperty *GeoMultiPropertyP;

OSG_END_NAMESPACE

#include "OSGGeoMultiPropertyBase.inl"
#include "OSGGeoMultiProperty.inl"

#endif /* _OSGGEOMULTIPROPERTYDATAPROPERTY_H_ */
