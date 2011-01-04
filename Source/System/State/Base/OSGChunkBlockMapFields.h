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

#ifndef _OSGCHUNKBLOCKMAPFIELDS_H_
#define _OSGCHUNKBLOCKMAPFIELDS_H_
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

class ChunkBlock;

/*! \ingroup GrpSystemStateFieldTraits
 */

typedef RenderPropertiesPool::Singleton::ValueType ChunkBlockMapKey;

/*! \ingroup GrpSystemStateFieldTraits
 */
typedef std::map<ChunkBlockMapKey, ChunkBlock *>  ChunkBlockMap;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemStateFieldSFields
 */
typedef SField<ChunkBlockMapKey> SFChunkBlockMapKey;

/*! \ingroup GrpSystemStateFieldMFields
 */
typedef MField<ChunkBlockMapKey> MFChunkBlockMapKey;
#else
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem
 */
struct SFChunkBlockMapKey : public SField<ChunkBlockMapKey> {};

/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem
 */
struct MFChunkBlockMapKey : public MField<ChunkBlockMapKey> {};
#endif

/*! \ingroup GrpSystemStateFieldTraits
    \ingroup GrpLibOSGSystem
 */

template <>
struct FieldTraits<ChunkBlockMap> : 
    public FieldTraitsTemplateBase<ChunkBlockMap>
{
  private:

    static  DataType                                 _type;

  public:

    typedef FieldTraits<ChunkBlockMap>  Self;

    typedef RenderPropertiesPool        KeyPool;

    enum             { Convertible = Self::NotConvertible                  };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) 
    {
        return "SFChunkBlockPtrMap"; 
    }

    static const Char8    *getMName     (void)
    {
        return "MFChunkBlockPtrMap"; 
    }
    
    static OSG_SYSTEM_DLLMAPPING UInt32 getBinSize(const ChunkBlockMap &aMap);

    static UInt32 getBinSize(const ChunkBlockMap *aMaps,
                                   UInt32         numObjects)
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
                                                const ChunkBlockMap     &aMap);
    
    static void copyToBin(      BinaryDataHandler &pMem,
                          const ChunkBlockMap     *aMaps,
                                UInt32             numObjects)
    {
        for(UInt32 i = 0; i < numObjects; ++i)
        {
            copyToBin(pMem, aMaps[i]);
        }
    }
    
    static OSG_SYSTEM_DLLMAPPING void copyFromBin(BinaryDataHandler &pMem,
                                                  ChunkBlockMap     &aMap );

    static void copyFromBin(BinaryDataHandler &pMem,
                            ChunkBlockMap     *aMaps,
                            UInt32             numObjects)
    {
        for(UInt32 i = 0; i < numObjects; ++i)
        {
            copyFromBin(pMem, aMaps[i]);
        }
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemStateFieldSFields
 */
typedef SField<ChunkBlockMap> SFChunkBlockPtrMap;
#else
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem
 */
struct SFChunkBlockPtrMap : public SField<ChunkBlockMap> {};
#endif

/*! \ingroup GrpSystemStateFieldHandle
 */

template<>
class OSG_SYSTEM_DLLMAPPING GetSFieldHandle<SFChunkBlockPtrMap> : 
    public GetMapFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetMapFieldHandle Inherited;
    typedef GetFieldHandle    Base;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;
    typedef FieldTraits<ChunkBlockMap>         MapFieldTraits;
    typedef MapFieldTraits::KeyPool            KeyPool;
    typedef KeyPool::Singleton::ValueType      KeyType;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle       &source);
    GetSFieldHandle(const SFChunkBlockPtrMap    *pField, 
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

    SFChunkBlockPtrMap const * operator ->(void);
    SFChunkBlockPtrMap const & operator * (void);
};

/*! \ingroup GrpSystemStateFieldHandle
 */

template<>
class OSG_SYSTEM_DLLMAPPING 
    EditSFieldHandle<SFChunkBlockPtrMap> : public EditMapFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditMapFieldHandle Inherited;
    typedef EditFieldHandle    Base;

    typedef boost::function<void(ChunkBlock       * const,
                                 ChunkBlockMapKey        )> AddMethod;

    /*==========================  PUBLIC  =================================*/

    FieldContainer *_pContainer;
    AddMethod       _fAddMethod;

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;
    typedef FieldTraits<ChunkBlockMap>          MapFieldTraits;
    typedef MapFieldTraits::KeyPool             KeyPool;
    typedef KeyPool::Singleton::ValueType       KeyType;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle     &source      );
    EditSFieldHandle(      SFChunkBlockPtrMap   *pField, 
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

#include "OSGChunkBlockMapFields.inl"

#endif /* _OSGCHUNKBLOCKMAPFIELDS_H_ */
