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

#ifndef _OSGFIELDCONTAINERMFIELDS_H_
#define _OSGFIELDCONTAINERMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGFieldContainerFieldTraits.h"

#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

template<>
class MField<FieldContainerPtr, 0> : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MFieldVector<FieldContainerPtr>     StorageType;
    typedef StorageType::Inherited              StorageTypeParent;

    typedef StorageType::iterator               iterator;
    typedef StorageType::const_iterator         const_iterator;

    typedef StorageType::reverse_iterator       reverse_iterator;
    typedef StorageType::const_reverse_iterator const_reverse_iterator;


    typedef StorageType::reference              reference;
    typedef StorageType::const_reference        const_reference;

    typedef FieldTraits<FieldContainerPtr, 0>   MFieldTraits;
 
    typedef MField     <FieldContainerPtr, 0>   Self;

    typedef FieldContainerPtr                   StoredType;

    typedef MFieldTraits::ArgumentType          ArgumentType;

    typedef FieldDescription<MFieldTraits,
                             MultiField     >   Description;

    typedef EditMFieldHandle <Self      >       EditHandle;
    typedef boost::shared_ptr<EditHandle>       EditHandlePtr;

    typedef GetMFieldHandle  <Self     >        GetHandle;
    typedef boost::shared_ptr<GetHandle>        GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32 Namespace = 0;

    static const bool isSField = false;
    static const bool isMField = true;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             MField(void);
             MField(const MField  &obj);
    explicit MField(const UInt32   size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~MField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          StorageType &getValues(void);
    const StorageType &getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setValues          (const StorageType       &value);
    void setValues          (const StorageTypeParent &value);
    void setValues          (const Self              &obj  );
    
#if 0
    void addValueFromCString(const Char8             *str  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Push                                    */
    /*! \{                                                                 */

    void pushValuesToString  (std::string  &str) const;
    void pushValuesFromStream(std::istream &str);
    void pushValuesToStream  (OutStream    &str) const;
    void pushSizeToStream    (OutStream    &str) const;
#endif
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    
    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    iterator               begin    (void                              );
    iterator               end      (void                              );

    reverse_iterator       rbegin   (void                              );
    reverse_iterator       rend     (void                              );

    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
    const_reverse_iterator rbegin   (void                              ) const;
    const_reverse_iterator rend     (void                              ) const;

    reference              front    (void                              );
    const_reference        front    (void                              ) const;

    reference              back     (void                              );
    const_reference        back     (void                              ) const;
    
    void                   clear    (void                              );
    
    iterator               insert   (iterator     pos, 
                                     ArgumentType value                );
#ifdef __STL_MEMBER_TEMPLATES
    template <class InputIterator>
    void                   insert   (iterator      pos, 
                                     InputIterator first, 
                                     InputIterator last                );
#else
    void                   insert   (iterator      pos, 
                                     iterator      first,
                                     iterator      last                );
#endif /* __STL_MEMBER_TEMPLATES */
 
    iterator               erase    (iterator     pos                  );
    
    iterator               find     (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;
    Int32                  findIndex(ArgumentType value                ) const;

    void                   push_back(ArgumentType value                );

    void                   resize   (size_t       newsize, 
                                     StoredType   t      = StoredType());
    void                   reserve  (size_t       newsize              );

    UInt32                 size     (void                              ) const;
    UInt32                 capacity (void                              ) const;
    bool                   empty    (void                              ) const;
    void                   swap     (MField                      &right);

#ifdef OSG_1_COMPAT
    void                   addValue (ArgumentType value                );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

          reference operator [](UInt32 index);
    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

    bool operator ==(const MField &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void operator =(const MField &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith       (Self               &source, 
                         ConstFieldMaskArg   syncMode,
                         UInt32              uiSyncInfo,
                         AspectOffsetStore  &oOffsets    );

    void beginEdit      (UInt32              uiAspect,
                         AspectOffsetStore  &oOffsets    );


    Self *resolveShare  (UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    void  terminateShare(UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    bool  isShared      (void                            );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    void dump(      UInt32    uiIndent = 0, 
              const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef Field Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType   _fieldType;

           StorageType _values;

#ifdef OSG_MT_CPTR_ASPECT
           UInt32      _uiSharedWith;
#endif

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup  */

typedef MField<FieldContainerPtr> MFFieldContainerPtr;
#endif


#if 0
template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 MultiField                     >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;

template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 MultiField                   >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;
#endif


template<>
class MField<ParentFieldContainerPtr, 0> : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MFieldVector<ParentFieldContainerPtr>     StorageType;
    typedef StorageType::Inherited                    StorageTypeParent;

    typedef StorageType::iterator                     iterator;
    typedef StorageType::const_iterator               const_iterator;

    typedef StorageType::reverse_iterator             reverse_iterator;
    typedef StorageType::const_reverse_iterator       const_reverse_iterator;


    typedef StorageType::reference                    reference;
    typedef StorageType::const_reference              const_reference;

    typedef FieldTraits<ParentFieldContainerPtr, 0>   MFieldTraits;
 
    typedef MField     <ParentFieldContainerPtr, 0>   Self;

    typedef ParentFieldContainerPtr                   StoredType;

    typedef MFieldTraits::ArgumentType                ArgumentType;

    typedef FieldDescription<MFieldTraits,
                             MultiField     >         Description;

    typedef EditMFieldHandle <Self      >             EditHandle;
    typedef boost::shared_ptr<EditHandle>             EditHandlePtr;

    typedef GetMFieldHandle  <Self     >              GetHandle;
    typedef boost::shared_ptr<GetHandle>              GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32 Namespace = 0;

    static const bool isSField = false;
    static const bool isMField = true;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             MField(void);
             MField(const MField  &obj);
    explicit MField(const UInt32   size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~MField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          StorageType &getValues(void);
    const StorageType &getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setValues          (const StorageType       &value);
    void setValues          (const StorageTypeParent &value);
    void setValues          (const Self              &obj  );
    
#if 0
    void addValueFromCString(const Char8             *str  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Push                                    */
    /*! \{                                                                 */

    void pushValuesToString  (std::string  &str) const;
    void pushValuesFromStream(std::istream &str);
    void pushValuesToStream  (OutStream    &str) const;
    void pushSizeToStream    (OutStream    &str) const;
#endif
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    
    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    iterator               begin    (void                              );
    iterator               end      (void                              );

    reverse_iterator       rbegin   (void                              );
    reverse_iterator       rend     (void                              );

    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
    const_reverse_iterator rbegin   (void                              ) const;
    const_reverse_iterator rend     (void                              ) const;

    reference              front    (void                              );
    const_reference        front    (void                              ) const;

    reference              back     (void                              );
    const_reference        back     (void                              ) const;
    
    void                   clear    (void                              );
    
    iterator               insert   (iterator     pos, 
                                     ArgumentType value                );
#ifdef __STL_MEMBER_TEMPLATES
    template <class InputIterator>
    void                   insert   (iterator      pos, 
                                     InputIterator first, 
                                     InputIterator last                );
#else
    void                   insert   (iterator      pos, 
                                     iterator      first,
                                     iterator      last                );
#endif /* __STL_MEMBER_TEMPLATES */
 
    iterator               erase    (iterator     pos                  );
    
    iterator               find     (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;
    Int32                  findIndex(ArgumentType value                ) const;

    void                   push_back(ArgumentType value                );

    void                   resize   (size_t       newsize, 
                                     StoredType   t      = StoredType());
    void                   reserve  (size_t       newsize              );

    UInt32                 size     (void                              ) const;
    UInt32                 capacity (void                              ) const;
    bool                   empty    (void                              ) const;
    void                   swap     (MField                      &right);

#ifdef OSG_1_COMPAT
    void                   addValue (ArgumentType value                );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

          reference operator [](UInt32 index);
    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

    bool operator ==(const MField &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void operator =(const MField &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith       (Self               &source, 
                         ConstFieldMaskArg   syncMode,
                         UInt32              uiSyncInfo,
                         AspectOffsetStore  &oOffsets    );

    void beginEdit      (UInt32              uiAspect,
                         AspectOffsetStore  &oOffsets    );


    Self *resolveShare  (UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    void  terminateShare(UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    bool  isShared      (void                            );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    void dump(      UInt32    uiIndent = 0, 
              const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef Field Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType   _fieldType;

           StorageType _values;

#ifdef OSG_MT_CPTR_ASPECT
           UInt32      _uiSharedWith;
#endif

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup  */

typedef MField<ParentFieldContainerPtr> MFParentFieldContainerPtr;
#endif

template<>
class OSG_SYSTEM_DLLMAPPING EditMFieldHandle<MFFieldContainerPtr> :
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;


    typedef boost::function<void(MFFieldContainerPtr::ArgumentType)> AddMethod;

    AddMethod _fAddMethod;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditMFieldHandle(const EditMFieldHandle     &source);
    EditMFieldHandle(      MFFieldContainerPtr  *pField, 
                     const FieldDescriptionBase *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void add    (      FieldContainerPtrConstArg pNewElement);
    virtual void replace(const UInt32                    uiIndex,
                               FieldContainerPtrConstArg pNewElement);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void setAddMethod(AddMethod fMethod);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source);
    virtual void shareValues         (      GetFieldHandlePtr  source);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;

};

template<>
class OSG_SYSTEM_DLLMAPPING GetMFieldHandle<MFFieldContainerPtr> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetMFieldHandle(const GetMFieldHandle      &source);
    GetMFieldHandle(const MFFieldContainerPtr  *pField, 
                    const FieldDescriptionBase *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    MFFieldContainerPtr const * operator ->(void);
    MFFieldContainerPtr const & operator * (void);
};




template<class FieldT>
class GetFCPtrMFieldHandle : public GetMFieldHandle<MFFieldContainerPtr>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetMFieldHandle<MFFieldContainerPtr> Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    GetFCPtrMFieldHandle(const GetFCPtrMFieldHandle &source);
    GetFCPtrMFieldHandle(const FieldT               *pField, 
                         const FieldDescriptionBase *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

//    virtual bool equal(Ptr rhs);

    /*---------------------------------------------------------------------*/

    FieldT const * operator ->(void);
    FieldT const & operator * (void);
};

template<class FieldT>
class EditFCPtrMFieldHandle : public EditMFieldHandle<MFFieldContainerPtr>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditMFieldHandle<MFFieldContainerPtr> Inherited;


    typedef boost::function<void (typename FieldT::ArgumentType)> AddMethod;

    AddMethod _fAddMethod;

    /*==========================  PUBLIC  =================================*/

  public:

    EditFCPtrMFieldHandle(const EditFCPtrMFieldHandle &source);
    EditFCPtrMFieldHandle(      FieldT                *pField, 
                          const FieldDescriptionBase  *pDescription);

    /*---------------------------------------------------------------------*/

    virtual void add    (      FieldContainerPtrConstArg pNewElement);
    virtual void replace(const UInt32                    uiIndex,
                               FieldContainerPtrConstArg pNewElement);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void setAddMethod(AddMethod fMethod);

//    virtual bool equal(Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source);
    virtual void shareValues         (      GetFieldHandlePtr  source);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;
};



template<>
class OSG_SYSTEM_DLLMAPPING EditMFieldHandle<MFParentFieldContainerPtr> :
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditMFieldHandle(const EditMFieldHandle          &source);
    EditMFieldHandle(      MFParentFieldContainerPtr *pField, 
                     const FieldDescriptionBase      *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

/*
    virtual void replace(const UInt32                    uiIndex,
                               FieldContainerPtrConstArg pNewElement);
 */

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source);
    virtual void shareValues         (      GetFieldHandlePtr  source);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;

};

template<>
class OSG_SYSTEM_DLLMAPPING GetMFieldHandle<MFParentFieldContainerPtr> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetMFieldHandle(const GetMFieldHandle           &source);
    GetMFieldHandle(const MFParentFieldContainerPtr *pField, 
                    const FieldDescriptionBase      *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    MFParentFieldContainerPtr const * operator ->(void);
    MFParentFieldContainerPtr const & operator * (void);
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerMFields.inl"
#endif

#endif /* _OSGFIELDCONTAINERMFIELDS_H_ */
