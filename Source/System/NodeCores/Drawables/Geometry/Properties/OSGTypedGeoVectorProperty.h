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

/*! \ingroup GrpWINDOWGLUTDrawablesGeometryProperties
    \hideinhierarchy
    \brief GeoProperty is a specialized form of Attachment, used to
    define the properties of the geometry node. See \ref
    PageWINDOWGLUTGeoProperties for a description.
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
    virtual       UInt32                 getStride    (void) const;
    virtual       UInt32                 getDimension (void) const;
    virtual       UInt32                 size         (void) const;
    virtual const UInt8                 *getData      (void) const;

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
    /*! \name                      Assigment                               */
    /*! \{                                                                 */

    TypedGeoVectorProperty &operator =(const TypedGeoVectorProperty &source);

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
    virtual ObjCPtr createAspectCopy(void) const;
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

    static void classDescInserter(TypeObject &oType);

    static void initMethod(InitPhase ePhase);
    static void exitMethod(InitPhase ePhase);

    static TypeObject  _type;
    
           void onCreate  (const Self *source = NULL);
};


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

#if !defined(OSG_DO_DOC)

/*! Helper macro for auto building geo property header information.
*/
#define OSG_MAKE_PROP(typename, gltypename, gltype, OSG_USAGE)                \
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


#define OSG_MAKE_NORM_PROP(typename, propname, nscale, gltypename, gltype, OSG_USAGE) \
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

#else // !defined(OSG_DO_DOC)

#define OSG_MAKE_PROP(typename, gltypename, gltype, USAGE)                    \
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
    static UInt32       getDimension   (void) { return typename::_uiSize; }   \
    static UInt32       getDefaultUsage(void)                                 \
    {                                                                         \
        return GeoProperty::USAGE | GeoProperty::UsageSystemSet;          \
    }                                                                         \
                                                                              \
    typedef typename          StoredType;                                     \
    typedef MF##typename      StoredFieldType;                                \
    /*! \}                                                                 */ \
}

#define OSG_MAKE_NORM_PROP(typename, propname, nscale, gltypename, gltype, USAGE) \
struct Geo##propname##PropertyDesc :                                          \
    public TypedNormGeoVectorPropertyDescBase                                 \
{                                                                             \
    /*---------------------------------------------------------------------*/ \
    /*! \name                          Get                                 */ \
    /*! \{                                                                 */ \
                                                                              \
    static const Char8 *getTypeName    (void)                                 \
    {                                                                         \
        return "Geo" #propname "Property";                                    \
    }                                                                         \
                                                                              \
    static UInt32       getFormat      (void) { return gltypename;        }   \
    static UInt32       getFormatSize  (void) { return sizeof(gltype);    }   \
    static UInt32       getDimension   (void) { return typename::_uiSize; }   \
    static UInt32       getDefaultUsage(void)                                 \
    {                                                                         \
        return GeoProperty::USAGE | GeoProperty::UsageSystemSet;          \
    }                                                                         \
                                                                              \
    typedef typename          StoredType;                                     \
    typedef MF##typename      StoredFieldType;                                \
                                                                              \
    static const int scale = nscale;                                          \
    /*! \}                                                                 */ \
}

#endif


// Meta-Macros

#define OSG_MAKE_1D_TO_4D_PROP(TBASE, TTYPE, GLTYPENAME, GLTYPE, USAGE)     \
OSG_MAKE_PROP(TBASE##1##TTYPE, GLTYPENAME, GLTYPE, USAGE);                  \
OSG_MAKE_PROP(TBASE##2##TTYPE, GLTYPENAME, GLTYPE, USAGE);                  \
OSG_MAKE_PROP(TBASE##3##TTYPE, GLTYPENAME, GLTYPE, USAGE);                  \
OSG_MAKE_PROP(TBASE##4##TTYPE, GLTYPENAME, GLTYPE, USAGE)

#define OSG_MAKE_1D_TO_4D_NORM_PROP(TBASE, TTYPE, SCALE, GLTYPENAME, GLTYPE, USAGE)         \
OSG_MAKE_NORM_PROP(TBASE##1##TTYPE, TBASE##1N##TTYPE, SCALE, GLTYPENAME, GLTYPE, USAGE);    \
OSG_MAKE_NORM_PROP(TBASE##2##TTYPE, TBASE##2N##TTYPE, SCALE, GLTYPENAME, GLTYPE, USAGE);    \
OSG_MAKE_NORM_PROP(TBASE##3##TTYPE, TBASE##3N##TTYPE, SCALE, GLTYPENAME, GLTYPE, USAGE);    \
OSG_MAKE_NORM_PROP(TBASE##4##TTYPE, TBASE##4N##TTYPE, SCALE, GLTYPENAME, GLTYPE, USAGE)

#define OSG_MAKE_COLOR_PROP(TTYPE, SCALE, GLTYPENAME, GLTYPE)                                  \
OSG_MAKE_PROP(Color3##TTYPE, GLTYPENAME, GLTYPE, UsageColorSpace);                             \
OSG_MAKE_PROP(Color4##TTYPE, GLTYPENAME, GLTYPE, UsageColorSpace);                             \
OSG_MAKE_NORM_PROP(Color3##TTYPE, Color3N##TTYPE, SCALE, GLTYPENAME, GLTYPE, UsageColorSpace); \
OSG_MAKE_NORM_PROP(Color4##TTYPE, Color4N##TTYPE, SCALE, GLTYPENAME, GLTYPE, UsageColorSpace)

// Now create all the necessary properties
OSG_MAKE_1D_TO_4D_NORM_PROP(Vec, ub,         255, GL_UNSIGNED_BYTE,  GLubyte,  UsageUnspecified);
OSG_MAKE_1D_TO_4D_NORM_PROP(Pnt, ub,         255, GL_UNSIGNED_BYTE,  GLubyte,  UsageObjectSpace);
OSG_MAKE_1D_TO_4D_NORM_PROP(Vec,  b,         127, GL_BYTE,           GLbyte,   UsageUnspecified);
OSG_MAKE_1D_TO_4D_NORM_PROP(Pnt,  b,         127, GL_BYTE,           GLbyte,   UsageObjectSpace);
OSG_MAKE_1D_TO_4D_NORM_PROP(Vec, us,       65535, GL_UNSIGNED_SHORT, GLushort, UsageUnspecified);
OSG_MAKE_1D_TO_4D_NORM_PROP(Pnt, us,       65535, GL_UNSIGNED_SHORT, GLushort, UsageObjectSpace);
OSG_MAKE_1D_TO_4D_NORM_PROP(Vec,  s,       32767, GL_SHORT,          GLshort,  UsageUnspecified);
OSG_MAKE_1D_TO_4D_NORM_PROP(Pnt,  s,       32767, GL_SHORT,          GLshort,  UsageObjectSpace);

// Does anybody need those? *DR*
// OSG_MAKE_1D_TO_4D_NORM_PROP(Vec, ui, 4294967295U, GL_UNSIGNED_INT,   GLuint,   UsageUnspecified);
// OSG_MAKE_1D_TO_4D_NORM_PROP(Pnt, ui, 4294967295U, GL_UNSIGNED_INT,   GLuint,   UsageObjectSpace);
// OSG_MAKE_1D_TO_4D_NORM_PROP(Vec,  i, 2147483647U, GL_INT,            GLint,    UsageUnspecified);
// OSG_MAKE_1D_TO_4D_NORM_PROP(Pnt,  i, 2147483647U, GL_INT,            GLint,    UsageObjectSpace);

OSG_MAKE_1D_TO_4D_PROP(Vec, ub, GL_UNSIGNED_BYTE,  GLubyte,  UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt, ub, GL_UNSIGNED_BYTE,  GLubyte,  UsageObjectSpace);
OSG_MAKE_1D_TO_4D_PROP(Vec,  b, GL_BYTE,           GLbyte,   UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt,  b, GL_BYTE,           GLbyte,   UsageObjectSpace);
OSG_MAKE_1D_TO_4D_PROP(Vec, us, GL_UNSIGNED_SHORT, GLushort, UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt, us, GL_UNSIGNED_SHORT, GLushort, UsageObjectSpace);
OSG_MAKE_1D_TO_4D_PROP(Vec,  s, GL_SHORT,          GLshort,  UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt,  s, GL_SHORT,          GLshort,  UsageObjectSpace);

// Does anybody need those? *DR*
// OSG_MAKE_1D_TO_4D_PROP(Vec, ui, GL_UNSIGNED_INT,   GLuint,   UsageUnspecified);
// OSG_MAKE_1D_TO_4D_PROP(Pnt, ui, GL_UNSIGNED_INT,   GLuint,   UsageObjectSpace);
// OSG_MAKE_1D_TO_4D_PROP(Vec,  i, GL_INT,            GLint,    UsageUnspecified);
// OSG_MAKE_1D_TO_4D_PROP(Pnt,  i, GL_INT,            GLint,    UsageObjectSpace);

#ifndef OSG_WINCE
OSG_MAKE_1D_TO_4D_PROP(Vec, f, GL_FLOAT, GLfloat, UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt, f, GL_FLOAT, GLfloat, UsageObjectSpace);
#endif

#ifdef OSG_WINCE
OSG_MAKE_1D_TO_4D_PROP(Vec, fx, GL_FIXED, GLfixed, UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt, fx, GL_FIXED, GLfixed, UsageObjectSpace);
#endif

#ifndef OSG_WINCE
OSG_MAKE_1D_TO_4D_PROP(Vec, d, GL_DOUBLE, GLdouble, UsageUnspecified);
OSG_MAKE_1D_TO_4D_PROP(Pnt, d, GL_DOUBLE, GLdouble, UsageObjectSpace);
#endif

OSG_MAKE_COLOR_PROP(ub, 255, GL_UNSIGNED_BYTE, GLubyte);

OSG_MAKE_PROP(Color3f, GL_FLOAT,  GLfloat, UsageColorSpace);
OSG_MAKE_PROP(Color4f, GL_FLOAT,  GLfloat, UsageColorSpace);

#ifdef OSG_WINCE
OSG_MAKE_PROP(Color3fx, GL_FIXED,  GLfixed, UsageColorSpace);
OSG_MAKE_PROP(Color4fx, GL_FIXED,  GLfixed, UsageColorSpace);
#endif


#ifdef OSG_DEPRECIATED_PROPS
/*! \brief Backwards Compatibility Typedefs
*/

// Positions

typedef GeoPnt2sProperty    GeoPositions2s;
typedef GeoPnt3sProperty    GeoPositions3s;
typedef GeoPnt4sProperty    GeoPositions4s;

#ifndef OSG_WINCE
typedef GeoPnt2fProperty    GeoPositions2f;
typedef GeoPnt3fProperty    GeoPositions3f;
typedef GeoPnt4fProperty    GeoPositions4f;

typedef GeoPnt2dProperty    GeoPositions2d;
typedef GeoPnt3dProperty    GeoPositions3d;
typedef GeoPnt4dProperty    GeoPositions4d;
#endif

// Normals

#ifndef OSG_WINCE
typedef GeoVec3fProperty    GeoNormals3f;
#endif
typedef GeoVec3sProperty    GeoNormals3s;
typedef GeoVec3bProperty    GeoNormals3b;

// Colors

#ifndef OSG_WINCE
typedef GeoColor3fProperty     GeoColors3f;
typedef GeoColor4fProperty     GeoColors4f;
#endif
typedef GeoColor3ubProperty    GeoColors3ub;
typedef GeoColor4ubProperty    GeoColors4ub;

// TexCoords

#ifndef OSG_WINCE
typedef GeoVec1fProperty     GeoTexCoords1f;
typedef GeoVec2fProperty     GeoTexCoords2f;
typedef GeoVec3fProperty     GeoTexCoords3f;
typedef GeoVec4fProperty     GeoTexCoords4f;

typedef GeoVec1dProperty     GeoTexCoords1d;
typedef GeoVec2dProperty     GeoTexCoords2d;
typedef GeoVec3dProperty     GeoTexCoords3d;
typedef GeoVec4dProperty     GeoTexCoords4d;
#endif

#endif // OSG_DEPRECIATED_PROPS

#ifdef OSG_GLES
#ifdef OSG_FLOAT_PROFILE
#else
typedef GeoPnt3fxProperty     GeoPnt3rProperty;
typedef GeoVec2fxProperty     GeoVec2rProperty;
typedef GeoVec3fxProperty     GeoVec3rProperty;

#endif
#else
typedef GeoPnt3fProperty      GeoPnt3rProperty;
typedef GeoVec2fProperty      GeoVec2rProperty;
typedef GeoVec3fProperty      GeoVec3rProperty;

typedef GeoPnt3fPropertyUnrecPtr   GeoPnt3rPropertyUnrecPtr;
typedef GeoVec2fPropertyUnrecPtr   GeoVec2rPropertyUnrecPtr;
typedef GeoVec3fPropertyUnrecPtr   GeoVec3rPropertyUnrecPtr;

typedef GeoPnt3fPropertyRecPtr   GeoPnt3rPropertyRecPtr;
typedef GeoVec2fPropertyRecPtr   GeoVec2rPropertyRecPtr;
typedef GeoVec3fPropertyRecPtr   GeoVec3rPropertyRecPtr;
#endif


#undef OSG_MAKE_PROP
#undef OSG_MAKE_NORM_PROP

#undef OSG_MAKE_1D_TO_4D_PROP
#undef OSG_MAKE_1D_TO_4D_NORM_PROP
#undef OSG_MAKE_COLOR_PROP

OSG_END_NAMESPACE

#include "OSGTypedGeoVectorProperty.inl"


#endif /* _OSGTYPEDGEOVECTORPROPERTY_H_ */

