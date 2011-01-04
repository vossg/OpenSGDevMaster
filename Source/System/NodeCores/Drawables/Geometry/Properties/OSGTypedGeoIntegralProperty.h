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

#ifndef _OSGTYPEDGEOINTEGRALPROPERTY_H_
#define _OSGTYPEDGEOINTEGRALPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGL.h"

#include "OSGDrawableDef.h"
#include "OSGVecMFields.h"
#include "OSGGeoIntegralProperty.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoProperty is a specialized form of Attachment, used to
    define the properties of the geometry node. See \ref 
    PageWINDOWGLUTGeoProperties for a description.

    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
 */

template <class GeoPropertyDesc>
class TypedGeoIntegralProperty : public GeoIntegralProperty
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          GeoIntegralProperty                       Inherited;
    typedef          GeoIntegralProperty                       ParentContainer;
    
    typedef          GeoPropertyDesc                           PropDesc;

    typedef typename Inherited::TypeObject                     TypeObject;
    typedef typename TypeObject::InitPhase                     InitPhase;

    typedef          TypedGeoIntegralProperty<GeoPropertyDesc> Self;

    OSG_GEN_INTERNALPTR(Self);

    typedef typename GeoPropertyDesc::StoredType      StoredType;
    typedef typename GeoPropertyDesc::StoredFieldType StoredFieldType;

    typedef typename StoredFieldType::EditHandle      StoredEditHandle;
    typedef typename StoredFieldType::EditHandlePtr   StoredEditHandlePtr;
    typedef typename StoredFieldType::GetHandle       StoredGetHandle;
    typedef typename StoredFieldType::GetHandlePtr    StoredGetHandlePtr;

    typedef typename StoredFieldType::reference       reference;
    typedef typename StoredFieldType::const_reference const_reference;

    enum
    {
        GeoPropDataFieldId = GeoIntegralProperty::NextFieldId,

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

    virtual       UInt32                 getFormat    (void) const;
    virtual       UInt32                 getFormatSize(void) const;
    virtual       UInt32                 getStride    (void) const;
    virtual       UInt32                 getDimension (void) const;
    virtual const UInt8                 *getData      (void) const;
    virtual       UInt32                 size         (void) const;

    virtual       GeoPropertyTransitPtr  clone        (void);
    
            const StoredFieldType &operator->(      void               ) const;

                  StoredType       getValue  (const UInt32      index  ) const;
            void                   getValue  (      StoredType &val,
                                              const UInt32      index  ) const;

            void                   setValue  (const StoredType &val,
                                              const UInt32      index  );

            void                   addValue  (const StoredType &val    );

    virtual void                   clear     (      void               );
    virtual void                   resize    (      size_t      newsize);
    virtual void                   push_back (const StoredType &val    );

    template <class ExternalType>
    ExternalType getValue(const UInt32 index)
    {
        return static_cast<ExternalType>(_field[index]);
    }

    template <class ExternalType>
    void setValue(ExternalType val, const UInt32 index)
    {
        editMField(GeoPropDataFieldMask, _field);

        _field[index] = static_cast<StoredType>(val);
    }

    // These are copied from OSGGeoIntegralProperty.h
    // They need to be replicated as C++ name lookup won't find them
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
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    inline reference       operator [](UInt32 index);
    inline const_reference operator [](UInt32 index) const;
    
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

    TypedGeoIntegralProperty(void);
    TypedGeoIntegralProperty(const TypedGeoIntegralProperty &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~TypedGeoIntegralProperty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
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

//    static const ObjPtr NullPtr;

    static TypeObject  _type;
};

/*! \ingroup GrpDrawablesGeometryProperties
 */
struct TypedGeoIntegralPropertyDescBase
{
    typedef GeoIntegralProperty       PropertParent;
    
    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void) 
    {
        return "TypedGeoIntegralProperty";  
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static UInt32         getStride      (void) { return 0; }

    static UInt32         getDimension   (void) { return 1; }
    
    static UInt32         getDefaultUsage(void)
    {
        return GeoProperty::UsageUnspecified | GeoProperty::UsageSystemSet;
    }
};


/*! \brief The descriptor trait for OSG::GeoPositionsUInt8.
    \ingroup GrpDrawablesGeometryProperties
 */

struct GeoUInt8PropertyDesc : public TypedGeoIntegralPropertyDescBase
{    
    static const Char8 *getTypeName (void) { return "GeoUInt8Property";  }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_BYTE;}
    static UInt32             getFormatSize(void) { return sizeof(GLubyte); }
    
    typedef UInt8             StoredType;
    typedef MFUInt8           StoredFieldType;
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef TypedGeoIntegralProperty<GeoUInt8PropertyDesc> GeoUInt8Property;

OSG_GEN_CONTAINERPTR(GeoUInt8Property);

#else
/*! \ingroup GrpDrawablesGeometryProperties \ingroup GrpLibOSGDrawables */
struct GeoUInt8Property : 
    public TypedGeoIntegralProperty<GeoUInt8PropertyDesc> {};
#endif



/*! \brief The descriptor trait for OSG::GeoPositionsUInt16.
    \ingroup GrpDrawablesGeometryProperties
 */

struct GeoUInt16PropertyDesc : public TypedGeoIntegralPropertyDescBase
{    
    static const Char8 *getTypeName (void) { return "GeoUInt16Property";  }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_SHORT;}
    static UInt32             getFormatSize(void) { return sizeof(GLushort); }
    
    typedef UInt16            StoredType;
    typedef MFUInt16          StoredFieldType;
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef TypedGeoIntegralProperty<GeoUInt16PropertyDesc> GeoUInt16Property;

OSG_GEN_CONTAINERPTR(GeoUInt16Property);

#else
/*! \ingroup GrpDrawablesGeometryProperties \ingroup GrpLibOSGDrawables */
struct GeoUInt16Property : 
    public TypedGeoIntegralProperty<GeoUInt16PropertyDesc> {};
#endif


/*! \brief The descriptor trait for OSG::GeoPositionsUInt32.
    \ingroup GrpDrawablesGeometryProperties
 */

struct GeoUInt32PropertyDesc : public TypedGeoIntegralPropertyDescBase
{    
    static const Char8 *getTypeName (void) { return "GeoUInt32Property";  }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_INT;}
    static UInt32             getFormatSize(void) { return sizeof(GLuint); }
    
    typedef UInt32            StoredType;
    typedef MFUInt32          StoredFieldType;
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef TypedGeoIntegralProperty<GeoUInt32PropertyDesc> GeoUInt32Property;

OSG_GEN_CONTAINERPTR(GeoUInt32Property);

#else
/*! \ingroup GrpDrawablesGeometryProperties \ingroup GrpLibOSGDrawables */
struct GeoUInt32Property : 
    public TypedGeoIntegralProperty<GeoUInt32PropertyDesc> {};
#endif

#ifdef OSG_DEPRECATED_PROPS
/*! \brief Backwards Compatibility Typedefs
*/

typedef GeoIntegralProperty       GeoPTypes;
typedef GeoIntegralProperty       GeoPLengths;
typedef GeoIntegralProperty       GeoIndices;

typedef GeoIntegralPropertyRecPtr GeoPTypesPtr;
typedef GeoIntegralPropertyRecPtr GeoPLengthsPtr;
typedef GeoIntegralPropertyRecPtr GeoIndicesPtr;

//typedef ConstGeoIntegralPropertyPtr    ConstGeoIndicesPtr;

typedef GeoUInt8Property          GeoPTypesUI8;
typedef GeoUInt8Property          GeoPLengthsUI8;
typedef GeoUInt8Property          GeoIndicesUI8;
typedef GeoUInt8PropertyRecPtr    GeoPTypesUI8Ptr;
//typedef GeoUInt8PropertyPtr    GeoPLengthsUI8Ptr;
//typedef GeoUInt8PropertyPtr    GeoIndicesUI8Ptr;

typedef GeoUInt16Property         GeoPTypesUI16;
typedef GeoUInt16Property         GeoPLengthsUI16;
typedef GeoUInt16Property         GeoIndicesUI16;
//typedef GeoUInt16PropertyPtr   GeoPTypesUI16Ptr;
//typedef GeoUInt16PropertyPtr   GeoPLengthsUI16Ptr;
//typedef GeoUInt16PropertyPtr   GeoIndicesUI16Ptr;

typedef GeoUInt32Property         GeoPTypesUI32;
typedef GeoUInt32Property         GeoPLengthsUI32;
typedef GeoUInt32Property         GeoIndicesUI32;
//typedef GeoUInt32PropertyPtr   GeoPTypesUI32Ptr;
typedef GeoUInt32PropertyRecPtr   GeoPLengthsUI32Ptr;
typedef GeoUInt32PropertyRecPtr   GeoIndicesUI32Ptr;

#endif

OSG_END_NAMESPACE

#include "OSGTypedGeoIntegralProperty.inl"

#endif /* _OSGTYPEDGEOINTEGRALPROPERTY_H_ */

