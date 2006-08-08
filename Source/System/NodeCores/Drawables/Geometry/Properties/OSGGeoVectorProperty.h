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

#ifndef _OSGGEOVECTORPROPERTY_H_
#define _OSGGEOVECTORPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVector.h"
#include "OSGGeoVectorPropertyBase.h"

OSG_BEGIN_NAMESPACE


/* Helper classes for vector type conversions */

// Converter class for vector conversion
struct GeoConvert
{
    template <class ExternalType, class StoredType>
    inline static void convertIn(StoredType& dest, const ExternalType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(ExternalType::_uiSize >= StoredType::_uiSize)
        {
            int i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(src[i]);
        }
        else
        {
            int i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(src[i]);
            for(; i < StoredType::_uiSize; ++i)
                dest[i] = StoredType::Null[i];
        }
    }
    
    template <class ExternalType, class StoredType>
    inline static void convertOut(ExternalType& dest, const StoredType& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            int i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(src[i]);
        }
        else
        {
            int i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(src[i]);
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = ExternalType::Null[i];
        }
    }

    template <class ExternalType, class StoredType>
    inline static void convertCustomOut(      ExternalType &dest, 
                                        const StoredType   &src,
                                              Real64        scale = 1, 
                                              Real64        offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            int i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
            {
                dest[i] = 
                    static_cast<typename ExternalType::ValueType>(
                        src[i].getValue());
            }
        }
        else
        {
            int i;
            for(i = 0; i < StoredType::_uiSize; ++i)
            {
                dest[i] = 
                    static_cast<typename ExternalType::ValueType>(
                        src[i].getValue());
            }
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = ExternalType::Null[i];
        }
    }

    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec1fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec2fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }

    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt1fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt2fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
};

struct GeoConvertNormalize
{
    template <class ExternalType, class StoredType>
    static void convertIn(StoredType& dest, const ExternalType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(ExternalType::_uiSize >= StoredType::_uiSize)
        {
            int i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            src[i] * scale + offset);
        }
        else
        {
            int i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            src[i] * scale + offset);
            for(; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            StoredType::Null[i] * scale + offset);
         }
    }
    
    template <class ExternalType, class StoredType>
    static void convertOut(ExternalType& dest, const StoredType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            int i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (src[i] - offset) / scale);
        }
        else
        {
            int i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (src[i] - offset) / scale);
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (StoredType::Null[i] - offset) / scale);
         }
    }
};

/*! \brief GeoVectorProperty class. See \ref 
           PageWindowGLUTGeoVectorProperty for a description.
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

#ifndef OSG_WINCE
    typedef Vec4ld MaxTypeT;
#else
    typedef Vec4f  MaxTypeT;
#endif    
    // MSVC 7.0 is a little weird about template member methods, that's why
    // the code has to be here...

    template <class ExternalType>
    ExternalType getValue (const UInt32 index) const
    {
        ExternalType eval;
        MaxTypeT ival;
        getValue(ival, index);
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
    void getValue (ExternalType &eval, const UInt32 index) const
    {
        MaxTypeT ival;
        getValue(ival, index);
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
    void setValue (const ExternalType &val, const UInt32 index)
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
        setValue(ival, index);
    }
    
    template <class ExternalType>
    void addValue (const ExternalType &val)
    {
         push_back(val);
    }
    
    template <class ExternalType>
    void push_back(const ExternalType &val)
    {
        resize(size() + 1);
        setValue(val, size() - 1);
    }

    virtual bool getNormalize(void) const = 0;
    virtual void clear(void) = 0;
    virtual void resize(size_t newsize) = 0;

    virtual UInt32 size(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name       Some special case methods for efficiency               */
    /*! \{                                                                 */

    virtual void getValue(      Vec3f    &val, const UInt32 index ) const;
    virtual void setValue(const Vec3f    &val, const UInt32 index );

    // This is the fallback, it has to be implemented by the concrete Props!
    virtual void getValue(      MaxTypeT &val, const UInt32 index ) const = 0;
    virtual void setValue(const MaxTypeT &val, const UInt32 index )       = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

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

    friend class GeoVectorPropertyBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;


    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GeoVectorProperty &source);
};

typedef GeoVectorProperty *GeoVectorPropertyP;

typedef GeoVectorProperty::ObjPtr         GeoVectorPropertyPtr;
typedef GeoVectorProperty::ObjConstPtr    GeoVectorPropertyConstPtr;
typedef GeoVectorProperty::ObjPtrConst    GeoVectorPropertyPtrConst;
typedef GeoVectorProperty::ObjPtrConstArg GeoVectorPropertyPtrConstArg;

OSG_END_NAMESPACE

#include "OSGGeoVectorPropertyBase.inl"
#include "OSGGeoVectorProperty.inl"

#define OSGGEOVECTORPROPERTY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGGEOVECTORPROPERTY_H_ */
