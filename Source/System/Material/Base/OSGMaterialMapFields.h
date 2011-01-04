/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGMATERIALMAPFIELDS_H_
#define _OSGMATERIALMAPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGSField.h"
#include "OSGFieldTraits.h"
#include "OSGContainerForwards.h"
#include "OSGRenderPropertiesPool.h"

#include "map"

OSG_BEGIN_NAMESPACE

class PrimeMaterial;

/*! \ingroup GrpSystemMaterialFieldTraits
 */

typedef RenderPropertiesPool::Singleton::ValueType MaterialMapKey;

/*! \ingroup GrpSystemMaterialFieldTraits
 */

typedef std::map<MaterialMapKey, PrimeMaterial *>  MaterialMap;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemMaterialFieldSFields
 */

typedef SField<MaterialMapKey> SFMaterialMapKey;

/*! \ingroup GrpSystemMaterialFieldMFields
 */
typedef MField<MaterialMapKey> MFMaterialMapKey;
#else
/*! \ingroup GrpSystemMaterialFieldSFields \ingroup GrpLibOSGSystem
 */

struct SFMaterialMapKey : public SField<MaterialMapKey> {};

/*! \ingroup GrpSystemMaterialFieldMFields \ingroup GrpLibOSGSystem
 */
struct MFMaterialMapKey : public MField<MaterialMapKey> {};
#endif

/*! \ingroup GrpSystemMaterialFieldTraits
    \ingroup GrpLibOSGSystem
 */

template <>
struct FieldTraits<MaterialMap> : 
    public FieldTraitsTemplateBase<MaterialMap>
{
  private:

    static  DataType                                 _type;

  public:

    typedef FieldTraits<MaterialMap>  Self;

    typedef RenderPropertiesPool      KeyPool;

    enum             { Convertible = Self::NotConvertible                  };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) 
    {
        return "SFMaterialPtrMap"; 
    }

    static const Char8    *getMName     (void)
    {
        return "MFMaterialPtrMap"; 
    }
    
    static OSG_SYSTEM_DLLMAPPING UInt32 getBinSize(const MaterialMap &aMap);

    static UInt32 getBinSize(const MaterialMap *aMaps,
                                   UInt32       numObjects)
    {
        UInt32 size = 0;

        // defaut: individual field sizes
        for(UInt32 i = 0; i < numObjects; ++i)
        {
            size += getBinSize(aMaps[i]);
        }

        return size;
    }
    
    static OSG_SYSTEM_DLLMAPPING void copyToBin(      BinaryDataHandler &pMem,
                                                const MaterialMap       &aMap);
    
    static void copyToBin(      BinaryDataHandler &pMem,
                          const MaterialMap       *aMaps,
                                UInt32             numObjects)
    {
        for(UInt32 i = 0; i < numObjects; ++i)
        {
            copyToBin(pMem, aMaps[i]);
        }
    }
    
    static OSG_SYSTEM_DLLMAPPING void copyFromBin(BinaryDataHandler &pMem,
                                                  MaterialMap       &aMap );

    static void copyFromBin(BinaryDataHandler &pMem,
                            MaterialMap       *aMaps,
                            UInt32             numObjects)
    {
        for(UInt32 i = 0; i < numObjects; ++i)
        {
            copyFromBin(pMem, aMaps[i]);
        }
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemMaterialFieldSFields
 */

typedef SField<MaterialMap> SFMaterialPtrMap;
#else
/*! \ingroup GrpSystemMaterialFieldSFields \ingroup GrpLibOSGSystem
 */

struct SFMaterialPtrMap : public SField<MaterialMap> {};
#endif

/*! \ingroup GrpSystemMaterialFieldHandle
    \ingroup GrpLibOSGSystem
 */

template<>
class OSG_SYSTEM_DLLMAPPING GetSFieldHandle<SFMaterialPtrMap> : 
    public GetMapFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetMapFieldHandle Inherited;
    typedef GetFieldHandle    Base;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;
    typedef FieldTraits<MaterialMap>           MapFieldTraits;
    typedef MapFieldTraits::KeyPool            KeyPool;
    typedef KeyPool::Singleton::ValueType      KeyType;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle       &source);
    GetSFieldHandle(const SFMaterialPtrMap      *pField, 
                    const FieldDescriptionBase  *pDescription,
                          FieldContainer        *pContainer  );

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void traverse(TraverseCallback oCallBack);

    /*---------------------------------------------------------------------*/

    virtual bool empty  (void                );
    virtual void flatten(MapList       &vList);
    virtual void flatten(ContainerList &vList);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Base::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    SFMaterialPtrMap const * operator ->(void);
    SFMaterialPtrMap const & operator * (void);
};

/*! \ingroup GrpSystemMaterialFieldHandle
    \ingroup GrpLibOSGSystem
 */

template<>
class OSG_SYSTEM_DLLMAPPING 
    EditSFieldHandle<SFMaterialPtrMap> : public EditMapFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditMapFieldHandle Inherited;
    typedef EditFieldHandle    Base;

    typedef boost::function<void(PrimeMaterial  * const,
                                 MaterialMapKey        )> AddMethod;

    /*==========================  PUBLIC  =================================*/

    FieldContainer *_pContainer;
    AddMethod       _fAddMethod;

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;
    typedef FieldTraits<MaterialMap>            MapFieldTraits;
    typedef MapFieldTraits::KeyPool             KeyPool;
    typedef KeyPool::Singleton::ValueType       KeyType;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle     &source      );
    EditSFieldHandle(      SFMaterialPtrMap     *pField, 
                     const FieldDescriptionBase *pDescription,
                           FieldContainer       *pContainer  );

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void add(      FieldContainer *rhs,
                     const std::string    &szBindings);

    /*---------------------------------------------------------------------*/

    virtual void traverse(TraverseCallback oCallBack);

    /*---------------------------------------------------------------------*/

    virtual bool empty  (void                );
    virtual void flatten(MapList       &vList);
    virtual void flatten(ContainerList &vList);

    /*---------------------------------------------------------------------*/

    virtual bool loadFromBin(      BinaryDataHandler        *pMem,
                                   UInt32                    uiNumElements,
                                   bool                      hasBindingInfo,
                                   std::vector<UInt16>      &vBindings,
                                   std::vector<UInt32>      &vIds          );

    virtual void fillFrom   (const std::vector<UInt16>      &vBindings,
                             const std::vector<UInt32>      &vIds,
                             const std::map<UInt32, UInt32> &vIdMap       );

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void         setAddMethod(AddMethod      fMethod);

    virtual bool equal       (Base::Ptr rhs    ) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source) const;
    virtual void shareValues         (      GetFieldHandlePtr  source) const;

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;

};

OSG_END_NAMESPACE

#include "OSGMaterialMapFields.inl"

#endif /* _OSGMATERIALMAPFIELDS_H_ */
