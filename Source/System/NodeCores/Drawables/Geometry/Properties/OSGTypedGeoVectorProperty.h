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

    typedef          GeoPropertyDesc                         Desc;

    typedef typename Inherited ::TypeObject                  TypeObject;
    typedef typename TypeObject::InitPhase                   InitPhase;

    typedef          TypedGeoVectorProperty<GeoPropertyDesc> Self;

    typedef typename PointerBuilder<Self>::ObjPtr            ObjPtr;
    typedef typename PointerBuilder<Self>::ObjConstPtr       ObjConstPtr;
    typedef typename PointerBuilder<Self>::ObjPtrConst       ObjPtrConst;

    typedef typename PointerBuilder<Self>::ObjPtrArg         ObjPtrArg;
    typedef typename PointerBuilder<Self>::ObjConstPtrArg    ObjConstPtrArg;
    typedef typename PointerBuilder<Self>::ObjPtrConstArg    ObjPtrConstArg;

    typedef typename GeoPropertyDesc::StoredType             StoredType;
    typedef typename GeoPropertyDesc::StoredFieldType        StoredFieldType;
    typedef typename GeoPropertyDesc::Converter              Converter;

    typedef typename StoredFieldType::reference              reference;
    typedef typename StoredFieldType::const_reference        const_reference;

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

#ifdef OSG_1_COMPAT
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

    virtual GeoVectorPropertyPtr clone(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assigment                               */
    /*! \{                                                                 */

    virtual       UInt32  getFormat    (void) const;
    virtual       UInt32  getFormatSize(void) const;
    virtual       UInt32  getStride    (void) const;
    virtual       UInt32  getDimension (void) const;
    virtual       UInt32  size         (void) const;
    virtual const UInt8  *getData      (void) const;

            const StoredFieldType &operator->(void) const { return _field; }

            StoredType  getValue(const UInt32 index) const;

            void        getValue(      StoredType &val,
                                 const UInt32      index) const;

            void        setValue(const StoredType &val,
                                 const UInt32      index);

            void        addValue(const StoredType &val);

    virtual void        clear();

    virtual void        resize(size_t newsize);

    virtual bool        getNormalize(void) const;

    virtual void        push_back(const StoredType &val);

    template <class ExternalType>
    ExternalType getValue (const UInt32 index)
    {
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
    void setValue (ExternalType val, const UInt32 index)
    {
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

    virtual void getValue(MaxTypeT &val, const UInt32 index) const
    {
        Converter::convertOut(val, 
                              _field[index], 
                              GeoPropertyDesc::scale, 
                              GeoPropertyDesc::offset);  
    }

    virtual void setValue(const MaxTypeT &val, const UInt32 index)
    {
        editMField(GeoPropDataFieldMask, _field);

        Converter::convertIn(_field[index], val, 
                             GeoPropertyDesc::scale, 
                             GeoPropertyDesc::offset);  
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

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;
 
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
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjPtr createAspectCopy(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */
    
#ifdef OSG_MT_FIELDCONTAINERPTR
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);

            void execSync (      Self              *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);
#endif
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
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

#if 0
    virtual void execBeginEditV(ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);

            void execBeginEdit (ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual void changed        (ConstFieldMaskArg whichField, 
                                 UInt32            origin    );
            
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

    static const ObjPtr NullPtr;

    static TypeObject  _type;
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

    static void initMethod(InitPhase ePhase) {}

    static UInt32             getStride    (void) { return 0;               }

    static const Char8 *getTypeName (void) { return "GeoVectorProperty"; }

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

    static void initMethod(InitPhase ePhase) {}

    static UInt32             getStride    (void) { return 0;               }

    static const Char8 *getTypeName (void) { return "GeoVectorProperty"; }

    /* Normalize */
    typedef GeoConvertNormalize     Converter;        
    static const bool normalize = true;
    static const int offset = 0;
};


// Helper Macro to define Properties

#undef makeProp

#if !defined(OSG_DO_DOC)

#define makeProp(typename, gltypename, gltype)                               \
struct Geo##typename##PropertyDesc :                                      \
    public TypedGeoVectorPropertyDescBase                                 \
{                                                                            \
    /*---------------------------------------------------------------------*/\
    /*! \name                          Get                                 */\
    /*! \{                                                                 */\
                                                                             \
    static const Char8 *getTypeName (void)                                   \
    {                                                                        \
        return "Geo" #typename "Property";                                \
    }                                                                        \
                                                                             \
    static UInt32             getFormat    (void) { return gltypename;      }\
    static UInt32             getFormatSize(void) { return sizeof(gltype);  }\
    static UInt32             getDimension (void) { return typename::_uiSize;}\
                                                                             \
    typedef typename          StoredType;                                    \
    typedef MF##typename      StoredFieldType;                               \
    /*! \}                                                                 */\
};                                                                           \
                                                                             \
typedef TypedGeoVectorProperty<Geo##typename##PropertyDesc>                 \
        Geo##typename##Property;                                          \
                                                                            \
typedef Geo##typename##Property::ObjPtr                                     \
    Geo##typename##PropertyPtr;                                             \
typedef Geo##typename##Property::ObjPtrConst                                \
    Geo##typename##PropertyPtrConst;                                        \
typedef Geo##typename##Property::ObjPtrConstArg                             \
    Geo##typename##PropertyPtrConstArg


#define makeNormProp(typename, propname, nscale, gltypename, gltype)         \
struct Geo##propname##PropertyDesc :                                      \
    public TypedNormGeoVectorPropertyDescBase                             \
{                                                                            \
    /*---------------------------------------------------------------------*/\
    /*! \name                          Get                                 */\
    /*! \{                                                                 */\
                                                                             \
    static const Char8 *getTypeName (void)                                   \
    {                                                                        \
        return "Geo" #propname "Property";                                \
    }                                                                        \
                                                                             \
    static UInt32             getFormat    (void) { return gltypename;      }\
    static UInt32             getFormatSize(void) { return sizeof(gltype);  }\
    static UInt32             getDimension (void) { return typename::_uiSize;}\
                                                                             \
    typedef typename          StoredType;                                    \
    typedef MF##typename      StoredFieldType;                               \
                                                                             \
    static const int scale = nscale;                                         \
    /*! \}                                                                 */\
};                                                                           \
                                                                             \
typedef TypedGeoVectorProperty<Geo##propname##PropertyDesc>            \
        Geo##propname##Property;                                          \
                                                                            \
typedef Geo##propname##Property::ObjPtr                                     \
    Geo##propname##PropertyPtr;                                             \
typedef Geo##propname##Property::ObjPtrConst                                \
    Geo##propname##PropertyPtrConst;                                        \
typedef Geo##propname##Property::ObjPtrConstArg                             \
    Geo##propname##PropertyPtrConstArg

#else // !defined(OSG_DO_DOC)

#define makeProp(typename, gltypename, gltype)                               \
struct Geo##typename##PropertyDesc :                                      \
    public TypedGeoVectorPropertyDescBase                                 \
{                                                                            \
    /*---------------------------------------------------------------------*/\
    /*! \name                          Get                                 */\
    /*! \{                                                                 */\
                                                                             \
    static const Char8 *getTypeName (void)                                   \
    {                                                                        \
        return "Geo" #typename "Property";                                \
    }                                                                        \
                                                                             \
    static UInt32             getFormat    (void) { return gltypename;      }\
    static UInt32             getFormatSize(void) { return sizeof(gltype);  }\
    static UInt32             getDimension (void) { return typename::_uiSize;}\
                                                                             \
    typedef typename          StoredType;                                    \
    typedef MF##typename      StoredFieldType;                               \
    /*! \}                                                                 */\
}

#define makeNormProp(typename, propname, nscale, gltypename, gltype)         \
struct Geo##propname##PropertyDesc :                                      \
    public TypedNormGeoVectorPropertyDescBase                             \
{                                                                            \
    /*---------------------------------------------------------------------*/\
    /*! \name                          Get                                 */\
    /*! \{                                                                 */\
                                                                             \
    static const Char8 *getTypeName (void)                                   \
    {                                                                        \
        return "Geo" #propname "Property";                                \
    }                                                                        \
                                                                             \
    static UInt32             getFormat    (void) { return gltypename;      }\
    static UInt32             getFormatSize(void) { return sizeof(gltype);  }\
    static UInt32             getDimension (void) { return typename::_uiSize;}\
                                                                             \
    typedef typename          StoredType;                                    \
    typedef MF##typename      StoredFieldType;                               \
                                                                             \
    static const int scale = nscale;                                         \
    /*! \}                                                                 */\
}

#endif


// Meta-Macros

#define make1to4dprop(tbase, ttype, gltypename, gltype)                     \
makeProp(tbase##1##ttype, gltypename, gltype);                              \
makeProp(tbase##2##ttype, gltypename, gltype);                              \
makeProp(tbase##3##ttype, gltypename, gltype);                              \
makeProp(tbase##4##ttype, gltypename, gltype)

#define maketypesprop(ttype, gltypename, gltype)                            \
make1to4dprop(Vec, ttype, gltypename, gltype);                              \
make1to4dprop(Pnt, ttype, gltypename, gltype);                              \

#define make1to4dnprop(tbase, ttype, scale, gltypename, gltype)             \
makeNormProp(tbase##1##ttype, tbase##1N##ttype, scale, gltypename, gltype); \
makeNormProp(tbase##2##ttype, tbase##2N##ttype, scale, gltypename, gltype); \
makeNormProp(tbase##3##ttype, tbase##3N##ttype, scale, gltypename, gltype); \
makeNormProp(tbase##4##ttype, tbase##4N##ttype, scale, gltypename, gltype)

#define maketypesnprop(ttype, scale, gltypename, gltype)                    \
make1to4dnprop(Vec, ttype, scale, gltypename, gltype);                      \
make1to4dnprop(Pnt, ttype, scale, gltypename, gltype);                      \
make1to4dprop(Vec, ttype, gltypename, gltype);                              \
make1to4dprop(Pnt, ttype, gltypename, gltype)

#define makecolorprop(ttype, scale, gltypename, gltype)                     \
makeProp(Color3##ttype, gltypename, gltype);                                \
makeProp(Color4##ttype, gltypename, gltype);                                \
makeNormProp(Color3##ttype, Color3N##ttype, scale, gltypename, gltype);     \
makeNormProp(Color4##ttype, Color4N##ttype, scale, gltypename, gltype)

// Now create all the necessary properties

maketypesnprop(ub,         255, GL_UNSIGNED_BYTE,  GLubyte);
maketypesnprop( b,         127, GL_BYTE,           GLbyte);
maketypesnprop(us,       65535, GL_UNSIGNED_SHORT, GLushort);
maketypesnprop( s,       32767, GL_SHORT,          GLshort);
// Does anybody need those? *DR*
//maketypesnprop(ui, 4294967295U, GL_UNSIGNED_INT,   GLuint);
//maketypesnprop( i, 2147483647U, GL_INT,            GLint);

#ifndef OSG_WINCE
maketypesprop(f, GL_FLOAT,  GLfloat);
#endif

#ifdef OSG_WINCE
maketypesprop(fx, GL_FIXED, GLfixed);
#endif

#ifndef OSG_WINCE
maketypesprop(d, GL_DOUBLE, GLdouble);
#endif

makecolorprop(ub,         255, GL_UNSIGNED_BYTE,  GLubyte);
makeProp(Color3f, GL_FLOAT,  GLfloat);
makeProp(Color4f, GL_FLOAT,  GLfloat);

       
#ifdef OSG_DEPRECIATED_PROPS
/*! \brief Backwards Compatibility Typedefs
*/

// Positions
typedef GeoVectorPropertyPtr         GeoPositionsPtr;
typedef GeoVectorPropertyConstPtr    GeoPositionsConstPtr;
typedef GeoVectorPropertyPtrConst    GeoPositionsPtrConst;
typedef GeoVectorPropertyPtrConstArg GeoPositionsPtrConstArg;

typedef GeoPnt2sProperty    GeoPositions2s;
typedef GeoPnt3sProperty    GeoPositions3s;
typedef GeoPnt4sProperty    GeoPositions4s;
typedef GeoPnt2sPropertyPtr GeoPositions2sPtr;
typedef GeoPnt3sPropertyPtr GeoPositions3sPtr;
typedef GeoPnt4sPropertyPtr GeoPositions4sPtr;

typedef GeoPnt2fProperty    GeoPositions2f;
typedef GeoPnt3fProperty    GeoPositions3f;
typedef GeoPnt4fProperty    GeoPositions4f;
typedef GeoPnt2fPropertyPtr GeoPositions2fPtr;
typedef GeoPnt3fPropertyPtr GeoPositions3fPtr;
typedef GeoPnt4fPropertyPtr GeoPositions4fPtr;

typedef GeoPnt2dProperty    GeoPositions2d;
typedef GeoPnt3dProperty    GeoPositions3d;
typedef GeoPnt4dProperty    GeoPositions4d;
typedef GeoPnt2dPropertyPtr GeoPositions2dPtr;
typedef GeoPnt3dPropertyPtr GeoPositions3dPtr;
typedef GeoPnt4dPropertyPtr GeoPositions4dPtr;


// Normals
typedef GeoVectorPropertyPtr         GeoNormalsPtr;
typedef GeoVectorPropertyConstPtr    GeoNormalsConstPtr;
typedef GeoVectorPropertyPtrConst    GeoNormalsPtrConst;
typedef GeoVectorPropertyPtrConstArg GeoNormalsPtrConstArg;

typedef GeoVec3fProperty    GeoNormals3f;
typedef GeoVec3sProperty    GeoNormals3s;
typedef GeoVec3bProperty    GeoNormals3b;
typedef GeoVec3fPropertyPtr GeoNormals3fPtr;
typedef GeoVec3sPropertyPtr GeoNormals3sPtr;
typedef GeoVec3bPropertyPtr GeoNormals3bPtr;
 
// Colors
typedef GeoVectorPropertyPtr         GeoColorsPtr;
typedef GeoVectorPropertyConstPtr    GeoColorsConstPtr;
typedef GeoVectorPropertyPtrConst    GeoColorsPtrConst;
typedef GeoVectorPropertyPtrConstArg GeoColorsPtrConstArg;

typedef GeoColor3fProperty     GeoColors3f;
typedef GeoColor4fProperty     GeoColors4f;
typedef GeoColor3ubProperty    GeoColors3ub;
typedef GeoColor4ubProperty    GeoColors4ub;
typedef GeoColor3fPropertyPtr  GeoColors3fPtr;
typedef GeoColor4fPropertyPtr  GeoColors4fPtr;
typedef GeoColor3ubPropertyPtr GeoColors3ubPtr;
typedef GeoColor4ubPropertyPtr GeoColors4ubPtr;

// TexCoords
typedef GeoVectorPropertyPtr         GeoTexCoordsPtr;
typedef GeoVectorPropertyConstPtr    GeoTexCoordsConstPtr;
typedef GeoVectorPropertyPtrConst    GeoTexCoordsPtrConst;
typedef GeoVectorPropertyPtrConstArg GeoTexCoordsPtrConstArg;

typedef GeoVec1fProperty     GeoTexCoords1f;
typedef GeoVec2fProperty     GeoTexCoords2f;
typedef GeoVec3fProperty     GeoTexCoords3f;
typedef GeoVec4fProperty     GeoTexCoords4f;

typedef GeoVec1fPropertyPtr  GeoTexCoords1fPtr;
typedef GeoVec2fPropertyPtr  GeoTexCoords2fPtr;
typedef GeoVec3fPropertyPtr  GeoTexCoords3fPtr;
typedef GeoVec4fPropertyPtr  GeoTexCoords4fPtr;

typedef GeoVec1dProperty     GeoTexCoords1d;
typedef GeoVec2dProperty     GeoTexCoords2d;
typedef GeoVec3dProperty     GeoTexCoords3d;
typedef GeoVec4dProperty     GeoTexCoords4d;

typedef GeoVec1dPropertyPtr  GeoTexCoords1dPtr;
typedef GeoVec2dPropertyPtr  GeoTexCoords2dPtr;
typedef GeoVec3dPropertyPtr  GeoTexCoords3dPtr;
typedef GeoVec4dPropertyPtr  GeoTexCoords4dPtr;
#endif

OSG_END_NAMESPACE

#include "OSGTypedGeoVectorProperty.inl"


#endif /* _OSGTYPEDGEOVECTORPROPERTY_H_ */

