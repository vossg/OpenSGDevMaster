/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGGEOVECTORPROPERTY_H_
#define _OSGGEOVECTORPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVector.h"
#include "OSGGeoVectorPropertyBase.h"
#include "OSGGeoVectorPropertyConversion.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;

/*! \brief GeoVectorProperty class. See \ref
           PageWindowGLUTGeoVectorProperty for a description.
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING GeoVectorProperty :
    public GeoVectorPropertyBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoVectorPropertyBase                             Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name        Arbitrary Type Interface Methods                      */
    /*! \{                                                                 */

    typedef Vec4d MaxTypeT;

    // MSVC 7.0 is a little weird about template member methods, that's why
    // the code has to be here...

    template <class ExternalType>
    ExternalType getValue(const UInt32 index) const
    {
        ExternalType eval;
        MaxTypeT     ival;
        getGenericValue(ival, index);
        if(getNormalize() &&
           TypeTraits<typename  ExternalType::ValueType>::MathProp ==
               IntValue)
        {
            GeoConvertNormalize::convertOut(eval, ival,
                TypeTraits<typename  ExternalType::ValueType>::getMax(), 0);
        }
        else
        {
            GeoConvert::convertOut(eval, ival);
        }
        return eval;
    }

    template <class ExternalType>
    void getValue(ExternalType &eval, const UInt32 index) const
    {
        MaxTypeT ival;
        getGenericValue(ival, index);
        if(getNormalize() &&
           TypeTraits<typename  ExternalType::ValueType>::MathProp ==
               IntValue)
        {
            GeoConvertNormalize::convertOut(eval, ival,
                TypeTraits<typename  ExternalType::ValueType>::getMax(), 0);
        }
        else
        {
            GeoConvert::convertOut(eval, ival);
        }
    }

    template <class ExternalType>
    void setValue(const ExternalType &val, const UInt32 index)
    {
        MaxTypeT ival;
        if(getNormalize() &&
           TypeTraits<typename  ExternalType::ValueType>::MathProp ==
               IntValue)
        {
            GeoConvertNormalize::convertIn(ival, val,
                TypeTraits<typename  ExternalType::ValueType>::getMax(), 0);
        }
        else
        {
            GeoConvert::convertIn(ival, val);
        }
        setGenericValue(ival, index);
    }

    template <class ExternalType>
    void addValue(const ExternalType &val)
    {
         push_back(val);
    }

    template <class ExternalType>
    void push_back(const ExternalType &val)
    {
        resize(size() + 1);
        setValue(val, size() - 1);
    }

    virtual bool   getNormalize(void          ) const = 0;
    virtual void   clear       (void          )       = 0;
    virtual void   resize      (size_t newsize)       = 0;
    virtual UInt32 size        (void          ) const = 0;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void *mapBuffer  (GLenum eAccess, DrawEnv *pEnv);
    virtual bool  unmapBuffer(                DrawEnv *pEnv);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoVectorPropertyBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoVectorProperty(void);
    GeoVectorProperty(const GeoVectorProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoVectorProperty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Generic Access                             */
    /*! \{                                                                 */

    // This is the fallback, it has to be implemented by the concrete Props!
    virtual void getGenericValue(      MaxTypeT &val,
                                 const UInt32 index  ) const = 0;
    virtual void setGenericValue(const MaxTypeT &val,
                                 const UInt32 index  )       = 0;

    /*! \}                                                                 */

    virtual GLenum getBufferType(void); // buffer type for VBOs


    // extension indices for used extensions;
    static UInt32 _extSecondaryColor;
    static UInt32 _extMultitexture;

    // extension indices for used fucntions;
    static UInt32 _funcglSecondaryColorPointer;
    static UInt32 _funcglClientActiveTextureARB;

    static void initMethod(InitPhase ePhase);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GeoVectorPropertyBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoVectorProperty &source);
};

typedef GeoVectorProperty *GeoVectorPropertyP;

//typedef GeoVectorProperty::ObjPtr         GeoVectorPropertyPtr;
//typedef GeoVectorProperty::ConstObjPtr    ConstGeoVectorPropertyPtr;

OSG_END_NAMESPACE

#include "OSGGeoVectorPropertyBase.inl"
#include "OSGGeoVectorProperty.inl"

#endif /* _OSGGEOVECTORPROPERTY_H_ */
