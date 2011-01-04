/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifndef _OSGTYPEDGEOVECTORPROPERTY_H_
#define _OSGTYPEDGEOVECTORPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGL.h"

#include "OSGDrawableDef.h"
#include "OSGVecMFields.h"
#include "OSGBaseMFields.h"
#include "OSGGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoProperty is a specialized form of Attachment, used to
    define the properties of the geometry node. See \ref
    PageWINDOWGLUTGeoProperties for a description.

    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
 */

template <class GeoPropertyDesc>
class TypedGeoVectorProperty : public GeoVectorProperty
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          GeoVectorProperty                       Inherited;
    typedef          GeoVectorProperty                       ParentContainer;

    typedef          GeoPropertyDesc                         PropDesc;

    typedef typename Inherited ::TypeObject                  TypeObject;
    typedef typename TypeObject::InitPhase                   InitPhase;

    typedef          TypedGeoVectorProperty<GeoPropertyDesc> Self;

    OSG_GEN_INTERNALPTR(Self);

    typedef typename GeoPropertyDesc::StoredType      StoredType;
    typedef typename GeoPropertyDesc::StoredFieldType StoredFieldType;
    typedef typename StoredFieldType::EditHandle      StoredEditHandle;
    typedef typename StoredFieldType::EditHandlePtr   StoredEditHandlePtr;
    typedef typename StoredFieldType::GetHandle       StoredGetHandle;
    typedef typename StoredFieldType::GetHandlePtr    StoredGetHandlePtr;
    typedef typename GeoPropertyDesc::Converter       Converter;

    typedef typename StoredFieldType::reference       reference;
    typedef typename StoredFieldType::const_reference const_reference;

    enum
    {
        GeoPropDataFieldId = GeoVectorProperty::NextFieldId,

        NextFieldId        = GeoPropDataFieldId + 1
    };

    static const BitVector GeoPropDataFieldMask =
                           1 << static_cast<Int32>(GeoPropDataFieldId);


    OSG_FIELD_CONTAINER_TMPL_DECL;

    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

#ifdef OSG_1_GET_COMPAT
          StoredFieldType *getFieldPtr (void);
          StoredFieldType &getField    (void);
#endif

          StoredFieldType *editFieldPtr(void);
    const StoredFieldType *getFieldPtr (void) const;

          StoredFieldType &editField   (void);
    const StoredFieldType &getField    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    inline reference       operator [](UInt32 index);
    inline const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assigment                               */
    /*! \{                                                                 */

    virtual       UInt32                 getFormat    (void) const;
    virtual       UInt32                 getFormatSize(void) const;
    virtual       UInt32                 getVectorType(void) const;
    virtual       UInt32                 getStride    (void) const;
    virtual       UInt32                 getDimension (void) const;
    virtual       UInt32                 size         (void) const;
    virtual const UInt8                 *getData      (void) const;
    virtual       UInt8                 *editData     (void);

    virtual       GeoPropertyTransitPtr  clone        (void);
    
            const StoredFieldType &operator->  (       void              ) const;

            StoredType             getValue    (const UInt32      index  ) const;
            void                   getValue    (      StoredType &val,
                                                const UInt32      index  ) const;

            void                   setValue    (const StoredType &val,
                                                const UInt32      index  );

            void                   addValue    (const StoredType &val    );

    virtual void                   clear       (      void               );
    virtual void                   resize      (      size_t      newsize);
    virtual bool                   getNormalize(      void               ) const;
    virtual void                   push_back   (const StoredType &val    );

    template <class ExternalType>
    ExternalType getValue(const UInt32 index) const
    {
        FDEBUG(("TypedGeoVectorProperty<>::getValue<>(%d)\n", index));

        ExternalType val;

        if(GeoPropertyDesc::normalize)
        {
            if(TypeTraits<typename  ExternalType::ValueType>::MathProp ==
               IntValue)
            {
                GeoConvertNormalize::convertOut(val, _field[index],
                    static_cast<Real64>(GeoPropertyDesc::scale) /
                    TypeTraits<typename  ExternalType::ValueType>::getMax(), 0);
            }
            else
            {
                GeoConvertNormalize::convertOut(val, _field[index],
                    static_cast<Real64>(GeoPropertyDesc::scale), 0);
            }
        }
        else
        {
            GeoConvert::convertOut(val, _field[index]);
        }

        return val;
    }

    template <class ExternalType>
    void getValue(ExternalType &eval, const UInt32 index) const
    {
        FDEBUG(("TypedGeoVectorProperty<>::getValue<>(eval, %d)\n", index));

        if(GeoPropertyDesc::normalize)
        {
            if(TypeTraits<typename ExternalType::ValueType>::MathProp ==
               IntValue)
            {
                GeoConvertNormalize::convertOut(
                    eval,
                    _field[index],
                    static_cast<Real64>(GeoPropertyDesc::scale) /
                        TypeTraits<typename ExternalType::ValueType>::getMax(),
                    0);
            }
            else
            {
                GeoConvertNormalize::convertOut(
                    eval,
                    _field[index],
                    static_cast<Real64>(GeoPropertyDesc::scale),
                    0);
            }
        }
        else
        {
            GeoConvert::convertOut(eval, _field[index]);
        }
    }

    template <class ExternalType>
    void setValue (ExternalType val, const UInt32 index)
    {
        FDEBUG(("TypedGeoVectorProperty<>::setValue<>(val, %d)\n", index));

        StoredType ival;

        if(GeoPropertyDesc::normalize)
        {
            if(TypeTraits<typename  ExternalType::ValueType>::MathProp ==
               IntValue)
            {
                GeoConvertNormalize::convertIn(ival, val,
                    static_cast<Real64>(GeoPropertyDesc::scale) /
                    TypeTraits<typename  ExternalType::ValueType>::getMax(), 0);
            }
            else
            {
                GeoConvertNormalize::convertIn(ival, val,
                    static_cast<Real64>(GeoPropertyDesc::scale), 0);
            }
        }
        else
        {
            GeoConvert::convertIn(ival, val);
        }

        setValue(ival, index);
    }

    // These are copied from OSGGeoVectorProperty.h
    // They need to be replicated as C++ name lookup won't find them

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class FieldContainer;

    StoredFieldType _field;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedGeoVectorProperty(void);
    TypedGeoVectorProperty(const TypedGeoVectorProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TypedGeoVectorProperty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Generic Access                               */
    /*! \{                                                                 */

    virtual void getGenericValue(      MaxTypeT &val, const UInt32 index) const;
    virtual void setGenericValue(const MaxTypeT &val, const UInt32 index);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjCPtr createAspectCopy(const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      Self              *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    EditFieldHandlePtr editHandleField(void);
    GetFieldHandlePtr  getHandleField (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual void changed        (ConstFieldMaskArg whichField,
                                 UInt32            origin,
                                 BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate(const Self                 *p = NULL);
    void onDestroy(     UInt32 uiContainerId          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Binary Operations                       */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */  
    Self &operator =(const Self &source);

    static void classDescInserter(TypeObject &oType);

    static void initMethod(InitPhase ePhase);
    static void exitMethod(InitPhase ePhase);

    static TypeObject  _type;
};


/*! \ingroup GrpDrawablesGeometryProperties
 */

struct TypedGeoVectorPropertyDescBase
{
    typedef GeoVectorProperty       PropertParent;

    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void)
    {
        return "TypedGeoVectorProperty";
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static UInt32       getStride      (void) { return 0;                   }
    static const Char8 *getTypeName    (void) { return "GeoVectorProperty"; }
    static UInt32       getDefaultUsage(void)
    { 
        return GeoProperty::UsageObjectSpace;
    }

    /* Don't normalize */
    typedef GeoConvert Converter;

    static const bool normalize = false;
    static const int  scale     = 1;
    static const int  offset    = 0;
};


/*! \ingroup GrpDrawablesGeometryProperties
 */

struct TypedNormGeoVectorPropertyDescBase
{
    typedef GeoVectorProperty       PropertParent;

    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void)
    {
        return "TypedNormGeoVectorProperty";
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static UInt32       getStride      (void) { return 0;                   }
    static const Char8 *getTypeName    (void) { return "GeoVectorProperty"; }
    static UInt32       getDefaultUsage(void)
    {
        return GeoProperty::UsageTangentSpace;
    }


    /* Normalize */
    typedef GeoConvertNormalize     Converter;
    
    static const bool normalize = true;
    static const int  offset    = 0;
};


// Helper Macro to define Properties

#undef OSG_MAKE_PROP
#undef OSG_MAKE_NORM_PROP

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! Helper macro for auto building geo property header information.
 */
#define OSG_MAKE_PROP(typename, gltypename, gltype, OSG_VECTORTYPE, OSG_USAGE) \
struct Geo##typename##PropertyDesc :                                          \
    public TypedGeoVectorPropertyDescBase                                     \
{                                                                             \
    /*---------------------------------------------------------------------*/ \
    /*! \name                          Get                                 */ \
    /*! \{                                                                 */ \
                                                                              \
    static const Char8 *getTypeName    (void)                                 \
    {                                                                         \
        return "Geo" #typename "Property";                                    \
    }                                                                         \
                                                                              \
    static UInt32       getFormat      (void) { return gltypename;        }   \
    static UInt32       getFormatSize  (void) { return sizeof(gltype);    }   \
    static UInt32       getVectorType  (void)                                 \
    {                                                                         \
        return GeoProperty::OSG_VECTORTYPE;                                   \
    }                                                                         \
    static UInt32       getDimension   (void) { return typename::_uiSize; }   \
    static UInt32       getDefaultUsage(void)                                 \
    {                                                                         \
        return GeoProperty::OSG_USAGE | GeoProperty::UsageSystemSet;          \
    }                                                                         \
                                                                              \
    typedef typename          StoredType;                                     \
    typedef MF##typename      StoredFieldType;                                \
    /*! \}                                                                 */ \
};                                                                            \
                                                                              \
typedef TypedGeoVectorProperty<Geo##typename##PropertyDesc>                   \
        Geo##typename##Property;                                              \
                                                                              \
OSG_GEN_CONTAINERPTR(Geo##typename##Property)


#define OSG_MAKE_NORM_PROP(typename, propname, nscale, gltypename, gltype, OSG_VECTORTYPE, OSG_USAGE) \
struct Geo##propname##PropertyDesc :                                          \
    public TypedNormGeoVectorPropertyDescBase                                 \
{                                                                             \
    /*---------------------------------------------------------------------*/ \
    /*! \name                          Get                                 */ \
    /*! \{                                                                 */ \
                                                                              \
    static const Char8 *getTypeName (void)                                    \
    {                                                                         \
        return "Geo" #propname "Property";                                    \
    }                                                                         \
                                                                              \
    static UInt32       getFormat      (void) { return gltypename;        }   \
    static UInt32       getFormatSize  (void) { return sizeof(gltype);    }   \
    static UInt32       getVectorType  (void)                                 \
    {                                                                         \
        return GeoProperty::OSG_VECTORTYPE;                                   \
    }                                                                         \
    static UInt32       getDimension   (void) { return typename::_uiSize; }   \
    static UInt32       getDefaultUsage(void)                                 \
    {                                                                         \
        return GeoProperty::OSG_USAGE | GeoProperty::UsageSystemSet;          \
    }                                                                         \
                                                                              \
    typedef typename          StoredType;                                     \
    typedef MF##typename      StoredFieldType;                                \
                                                                              \
    static const int scale = nscale;                                          \
    /*! \}                                                                 */ \
};                                                                            \
                                                                              \
typedef TypedGeoVectorProperty<Geo##propname##PropertyDesc>                   \
        Geo##propname##Property;                                              \
                                                                              \
OSG_GEN_CONTAINERPTR(Geo##propname##Property)

#else

/*! Helper macro for auto building geo property header information.
 */
#define OSG_MAKE_PROP(typename, gltypename, gltype, OSG_VECTORTYPE, OSG_USAGE) \
/*! \ingroup GrpDrawablesGeometryProperties */                                \
struct Geo##typename##PropertyDesc :                                          \
    public TypedGeoVectorPropertyDescBase                                     \
{                                                                             \
    /*---------------------------------------------------------------------*/ \
    /*! \name                          Get                                 */ \
    /*! \{                                                                 */ \
                                                                              \
    static const Char8 *getTypeName    (void)                                 \
    {                                                                         \
        return "Geo" #typename "Property";                                    \
    }                                                                         \
                                                                              \
    static UInt32       getFormat      (void) { return gltypename;        }   \
    static UInt32       getFormatSize  (void) { return sizeof(gltype);    }   \
    static UInt32       getVectorType  (void)                                 \
    {                                                                         \
        return GeoProperty::OSG_VECTORTYPE;                                   \
    }                                                                         \
    static UInt32       getDimension   (void) { return typename::_uiSize; }   \
    static UInt32       getDefaultUsage(void)                                 \
    {                                                                         \
        return GeoProperty::OSG_USAGE | GeoProperty::UsageSystemSet;          \
    }                                                                         \
                                                                              \
    typedef typename          StoredType;                                     \
    typedef MF##typename      StoredFieldType;                                \
    /*! \}                                                                 */ \
};                                                                            \
                                                                              \
/*! \ingroup GrpDrawablesGeometryProperties \ingroup GrpLibOSGDrawables */    \
struct Geo##typename##Property :                                              \
    public TypedGeoVectorProperty<Geo##typename##PropertyDesc> {};            \
                                                                              \
OSG_GEN_CONTAINERPTR(Geo##typename##Property)


#define OSG_MAKE_NORM_PROP(typename, propname, nscale, gltypename, gltype, OSG_VECTORTYPE, OSG_USAGE) \
/*! \ingroup GrpDrawablesGeometryProperties */                                \
struct Geo##propname##PropertyDesc :                                          \
    public TypedNormGeoVectorPropertyDescBase                                 \
{                                                                             \
    /*---------------------------------------------------------------------*/ \
    /*! \name                          Get                                 */ \
    /*! \{                                                                 */ \
                                                                              \
    static const Char8 *getTypeName (void)                                    \
    {                                                                         \
        return "Geo" #propname "Property";                                    \
    }                                                                         \
                                                                              \
    static UInt32       getFormat      (void) { return gltypename;        }   \
    static UInt32       getFormatSize  (void) { return sizeof(gltype);    }   \
    static UInt32       getVectorType  (void)                                 \
    {                                                                         \
        return GeoProperty::OSG_VECTORTYPE;                                   \
    }                                                                         \
    static UInt32       getDimension   (void) { return typename::_uiSize; }   \
    static UInt32       getDefaultUsage(void)                                 \
    {                                                                         \
        return GeoProperty::OSG_USAGE | GeoProperty::UsageSystemSet;          \
    }                                                                         \
                                                                              \
    typedef typename          StoredType;                                     \
    typedef MF##typename      StoredFieldType;                                \
                                                                              \
    static const int scale = nscale;                                          \
    /*! \}                                                                 */ \
};                                                                            \
                                                                              \
/*! \ingroup GrpDrawablesGeometryProperties \ingroup GrpLibOSGDrawables */    \
struct Geo##propname##Property :                                              \
    public TypedGeoVectorProperty<Geo##propname##PropertyDesc>  {};           \
                                                                              \
OSG_GEN_CONTAINERPTR(Geo##propname##Property)

#endif


//********************************
// Vec/Pnt ub
//********************************
OSG_MAKE_PROP(Pnt1ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt2ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt3ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt4ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_NORM_PROP(Pnt1ub, Pnt1Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt2ub, Pnt2Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt3ub, Pnt3Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt4ub, Pnt4Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_PROP(Vec1ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec2ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec3ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec4ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);

OSG_MAKE_NORM_PROP(Vec1ub, Vec1Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec2ub, Vec2Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec3ub, Vec3Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec4ub, Vec4Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypeVector, UsageUnspecified);


//********************************
// Vec/Pnt b
//********************************
OSG_MAKE_PROP(Pnt1b, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt2b, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt3b, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt4b, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_NORM_PROP(Pnt1b, Pnt1Nb, 127, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt2b, Pnt2Nb, 127, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt3b, Pnt3Nb, 127, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt4b, Pnt4Nb, 127, GL_BYTE, GLbyte, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_PROP(Vec1b, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec2b, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec3b, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec4b, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);

OSG_MAKE_NORM_PROP(Vec1b, Vec1Nb, 127, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec2b, Vec2Nb, 127, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec3b, Vec3Nb, 127, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec4b, Vec4Nb, 127, GL_BYTE, GLbyte, VectorTypeVector, UsageUnspecified);


//********************************
// Vec/Pnt us
//********************************
OSG_MAKE_PROP(Pnt1us, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt2us, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt3us, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt4us, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_NORM_PROP(Pnt1us, Pnt1Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt2us, Pnt2Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt3us, Pnt3Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt4us, Pnt4Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_PROP(Vec1us, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec2us, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec3us, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec4us, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);

OSG_MAKE_NORM_PROP(Vec1us, Vec1Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec2us, Vec2Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec3us, Vec3Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec4us, Vec4Nus, 65535, GL_UNSIGNED_SHORT, GLushort, VectorTypeVector, UsageUnspecified);


//********************************
// Vec/Pnt s
//********************************
OSG_MAKE_PROP(Pnt1s, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt2s, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt3s, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt4s, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_NORM_PROP(Pnt1s, Pnt1Ns, 32767, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt2s, Pnt2Ns, 32767, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt3s, Pnt3Ns, 32767, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_NORM_PROP(Pnt4s, Pnt4Ns, 32767, GL_SHORT, GLshort, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_PROP(Vec1s, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec2s, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec3s, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec4s, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);

OSG_MAKE_NORM_PROP(Vec1s, Vec1Ns, 32767, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec2s, Vec2Ns, 32767, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec3s, Vec3Ns, 32767, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);
OSG_MAKE_NORM_PROP(Vec4s, Vec4Ns, 32767, GL_SHORT, GLshort, VectorTypeVector, UsageUnspecified);


//********************************
// Vec/Pnt ui
//********************************
// Does anybody need those? *DR*
//********************************
// Vec/Pnt i
//********************************
// Does anybody need those? *DR*


//********************************
// Vec/Pnt f
//********************************
OSG_MAKE_PROP(Pnt1f, GL_FLOAT, GLfloat, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt2f, GL_FLOAT, GLfloat, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt3f, GL_FLOAT, GLfloat, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt4f, GL_FLOAT, GLfloat, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_PROP(Vec1f, GL_FLOAT, GLfloat, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec2f, GL_FLOAT, GLfloat, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec3f, GL_FLOAT, GLfloat, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec4f, GL_FLOAT, GLfloat, VectorTypeVector, UsageUnspecified);


//********************************
// Vec/Pnt d
//********************************
OSG_MAKE_PROP(Pnt1d, GL_DOUBLE, GLdouble, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt2d, GL_DOUBLE, GLdouble, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt3d, GL_DOUBLE, GLdouble, VectorTypePoint, UsageObjectSpace);
OSG_MAKE_PROP(Pnt4d, GL_DOUBLE, GLdouble, VectorTypePoint, UsageObjectSpace);

OSG_MAKE_PROP(Vec1d, GL_DOUBLE, GLdouble, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec2d, GL_DOUBLE, GLdouble, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec3d, GL_DOUBLE, GLdouble, VectorTypeVector, UsageUnspecified);
OSG_MAKE_PROP(Vec4d, GL_DOUBLE, GLdouble, VectorTypeVector, UsageUnspecified);


//********************************
// Color ub
//********************************
OSG_MAKE_PROP(Color3ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypeColor, UsageColorSpace);                             
OSG_MAKE_PROP(Color4ub, GL_UNSIGNED_BYTE, GLubyte, VectorTypeColor, UsageColorSpace);
OSG_MAKE_NORM_PROP(Color3ub, Color3Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypeColor, UsageColorSpace);
OSG_MAKE_NORM_PROP(Color4ub, Color4Nub, 255, GL_UNSIGNED_BYTE, GLubyte, VectorTypeColor, UsageColorSpace);

//********************************
// Color f
//********************************
OSG_MAKE_PROP(Color3f, GL_FLOAT,  GLfloat, VectorTypeColor, UsageColorSpace);

//********************************
// Color d
//********************************
OSG_MAKE_PROP(Color4f, GL_FLOAT,  GLfloat, VectorTypeColor, UsageColorSpace);


#ifdef OSG_DEPRECATED_PROPS
/*! \brief Backwards Compatibility Typedefs
*/

typedef GeoVectorProperty       GeoPositions;
typedef GeoVectorProperty       GeoNormals;
typedef GeoVectorProperty       GeoTexCoords;
typedef GeoVectorProperty       GeoColors;

typedef GeoVectorPropertyRecPtr GeoPositionsPtr;
typedef GeoVectorPropertyRecPtr GeoNormalsPtr;
typedef GeoVectorPropertyRecPtr GeoTexCoordsPtr;
typedef GeoVectorPropertyRecPtr GeoColorsPtr;

// Positions

typedef GeoPnt2sProperty    GeoPositions2s;
typedef GeoPnt3sProperty    GeoPositions3s;
typedef GeoPnt4sProperty    GeoPositions4s;

typedef GeoPnt2fProperty           GeoPositions2f;
typedef GeoPnt2fPropertyRecPtr     GeoPositions2fPtr;
typedef GeoPnt3fProperty           GeoPositions3f;
typedef GeoPnt3fPropertyRecPtr     GeoPositions3fPtr;
typedef GeoPnt4fProperty           GeoPositions4f;
typedef GeoPnt4fPropertyRecPtr     GeoPositions4fPtr;

typedef GeoPnt2dProperty           GeoPositions2d;
typedef GeoPnt2dPropertyRecPtr     GeoPositions2dPtr;
typedef GeoPnt3dProperty           GeoPositions3d;
typedef GeoPnt3dPropertyRecPtr     GeoPositions3dPtr;
typedef GeoPnt4dProperty           GeoPositions4d;
typedef GeoPnt4dPropertyRecPtr     GeoPositions4dPtr;

// Normals

typedef GeoVec3fProperty           GeoNormals3f;
typedef GeoVec3fPropertyRecPtr     GeoNormals3fPtr;
typedef GeoVec3sProperty    GeoNormals3s;
typedef GeoVec3bProperty    GeoNormals3b;

// Colors

typedef GeoColor3fProperty         GeoColors3f;
typedef GeoColor3fPropertyRecPtr   GeoColors3fPtr;
typedef GeoColor4fProperty         GeoColors4f;
typedef GeoColor4fPropertyRecPtr   GeoColors4fPtr;
typedef GeoColor3ubProperty    GeoColors3ub;
typedef GeoColor4ubProperty    GeoColors4ub;

// TexCoords

typedef GeoVec1fProperty           GeoTexCoords1f;
typedef GeoVec1fPropertyRecPtr     GeoTexCoords1fPtr;
typedef GeoVec2fProperty           GeoTexCoords2f;
typedef GeoVec2fPropertyRecPtr     GeoTexCoords2fPtr;
typedef GeoVec3fProperty           GeoTexCoords3f;
typedef GeoVec3fPropertyRecPtr     GeoTexCoords3fPtr;
typedef GeoVec4fProperty           GeoTexCoords4f;
typedef GeoVec4fPropertyRecPtr     GeoTexCoords4fPtr;

typedef GeoVec1dProperty           GeoTexCoords1d;
typedef GeoVec2dProperty           GeoTexCoords2d;
typedef GeoVec3dProperty           GeoTexCoords3d;
typedef GeoVec4dProperty           GeoTexCoords4d;

#endif // OSG_DEPRECATED_PROPS

#undef OSG_MAKE_PROP
#undef OSG_MAKE_NORM_PROP

#undef OSG_MAKE_1D_TO_4D_PROP
#undef OSG_MAKE_1D_TO_4D_NORM_PROP
#undef OSG_MAKE_COLOR_PROP

OSG_END_NAMESPACE

#include "OSGTypedGeoVectorProperty.inl"


#endif /* _OSGTYPEDGEOVECTORPROPERTY_H_ */

