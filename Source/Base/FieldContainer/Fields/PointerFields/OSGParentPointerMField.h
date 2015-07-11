/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGPARENTPOINTERMFIELD_H_
#define _OSGPARENTPOINTERMFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointerMFieldCommon.h"
#include "OSGPointerAccessHandler.h"

OSG_BEGIN_NAMESPACE

// forward declarations
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
class ParentPointerMField;

template <class StorageTypeT>
class ParentMFieldIterator;

/*---------------------------------------------------------------------------*/
/* ParentMFieldConstIterator<PtrTypeT>                                    */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class StorageTypeT>
class ParentMFieldConstIterator : protected StorageTypeT::PtrStoreConstItType
{
    /*==========================  PUBLIC  =================================*/

    template <class ST>
    friend class ParentMFieldIterator;

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef typename StorageTypeT::PtrStoreConstItType   Inherited;
    
    typedef          ParentMFieldConstIterator           Self;
    
    typedef typename StorageTypeT::AccessHandler         AccessHandler;

    typedef          std::vector<UInt16>                 PosStorage;
    typedef          std::vector<UInt16>::const_iterator PosStorageIt;

    // std library types
    typedef typename Inherited::iterator_category        iterator_category;
    typedef typename Inherited::difference_type          difference_type;
    

    typedef typename StorageTypeT::const_value           const_value;
    typedef typename StorageTypeT::value_type            value_type;
    typedef typename StorageTypeT::iterator              iterator;
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ParentMFieldConstIterator(      void                   );
    ParentMFieldConstIterator(const Self         &source   );
    ParentMFieldConstIterator(const iterator     &fieldIter);
    ParentMFieldConstIterator(const Inherited    &storeIt,
                              const PosStorageIt &posIt    );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentMFieldConstIterator(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
    value_type operator  *(      void                  ) const;
    value_type operator [](const difference_type offset) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

    Self &operator ++(      void                  );
    Self  operator ++(      int                   );
    
    Self &operator --(      void                  );
    Self  operator --(      int                   );
    
    
    Self &operator +=(const difference_type offset);
    Self  operator + (const difference_type offset) const;
    
    Self &operator -=(const difference_type offset);
    Self  operator - (const difference_type offset) const;
 
    bool operator == (const Self            &rhs   ) const;
    bool operator != (const Self            &rhs   ) const;
    
    bool operator == (const iterator        &rhs   ) const;
    bool operator != (const iterator        &rhs   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
   
    value_type getPtr           (void) const;
    UInt16     getParentFieldPos(void) const;
    
    /*! \}                                                                 */
    /*========================  PROTECTED  ================================*/

  protected:

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */
    
    const Inherited    &ptrBase(void) const;
    const PosStorageIt &idBase (void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    PosStorageIt _posIt;
};


#if 0
template <class PtrTypeT>
typename ParentMFieldConstIterator<PtrTypeT>::difference_type
    operator-(ParentMFieldConstIterator<PtrTypeT> const &lhs,
              ParentMFieldConstIterator<PtrTypeT> const &rhs );

template <class PtrTypeT>
ParentMFieldConstIterator<PtrTypeT>
    operator+(typename ParentMFieldConstIterator<PtrTypeT>::differece_type const offset,
              ParentMFieldConstIterator<PtrTypeT>                          const &rhs   );
#endif

/*---------------------------------------------------------------------------*/
/* ParentMFieldIterator<PtrTypeT>                                    */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class StorageTypeT>
class ParentMFieldIterator : protected StorageTypeT::PtrStoreItType
{
    template <class ST>
    friend class ParentMFieldConstIterator;

    template <class PT, typename RC, Int32 NI>
    friend class ParentPointerMField;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    
    typedef typename StorageTypeT::PtrStoreItType  Inherited;

    typedef          ParentMFieldIterator          Self;
                                                            
    typedef typename StorageTypeT::AccessHandler   AccessHandler;

    typedef          std::vector<UInt16>           PosStorage;
    typedef          std::vector<UInt16>::iterator PosStorageIt;

    // std library types
    typedef typename Inherited::iterator_category  iterator_category;
    typedef typename Inherited::difference_type    difference_type;

    
    typedef typename StorageTypeT::const_value     const_value;
    typedef typename StorageTypeT::value_type      value_type;
    typedef typename StorageTypeT::const_iterator  const_iterator;

    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ParentMFieldIterator(      void                 );
    ParentMFieldIterator(const Self         &source );
    ParentMFieldIterator(const Inherited    &storeIt,
                         const PosStorageIt &posIt  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentMFieldIterator(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
    value_type operator  *(      void                  ) const;
    value_type operator [](const difference_type offset) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
    Self &operator ++(      void                  );
    Self  operator ++(      int                   );
    
    Self &operator --(      void                  );
    Self  operator --(      int                   );
    
    
    Self &operator +=(const difference_type offset);
    Self  operator + (const difference_type offset) const;
    
    Self &operator -=(const difference_type offset);
    Self  operator - (const difference_type offset) const;
    
    bool operator == (const Self            &rhs   ) const;
    bool operator != (const Self            &rhs   ) const;
    
    bool operator == (const const_iterator  &rhs   ) const;
    bool operator != (const const_iterator  &rhs   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

    value_type getPtr           (void) const;
    UInt16     getParentFieldPos(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */
    
    /*! \}                                                                 */
    /*========================  PROTECTED  ================================*/

  protected:

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */
    
    const Inherited    &ptrBase(void) const;
    const PosStorageIt &idBase (void) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    PosStorageIt _posIt;
};


/*---------------------------------------------------------------------------*/
/* ParentPointerMField<PtrTypeT,                                          */
/*                     NamespaceI  >                                         */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template <class    PtrTypeT,
          typename RefCountPolicy, 
          Int32    NamespaceI  = 0>
class ParentPointerMField :
    public PointerMFieldCommon<PointerAccessHandler<RefCountPolicy>,
                               NamespaceI                          >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          PointerMFieldCommon<
                         PointerAccessHandler<
                             RefCountPolicy>,
                         NamespaceI                   > Inherited;

    typedef          ParentPointerMField                Self;

    typedef          PtrTypeT const                     const_value;
    typedef          PtrTypeT                           value_type;

    typedef typename Inherited::size_type               size_type;
    typedef typename Inherited::difference_type         difference_type;

    typedef typename Inherited::PtrStoreItType          PtrStoreItType;
    typedef typename Inherited::PtrStoreConstItType     PtrStoreConstItType;

    typedef          ParentMFieldConstIterator<Self   > const_iterator;
    typedef          std::reverse_iterator    <
                         const_iterator               > const_reverse_iterator;

    typedef          ParentMFieldIterator     <Self   > iterator;

    typedef          std::reverse_iterator<iterator>    reverse_iterator;

    typedef          UInt16                             IdStoredType;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    typedef          MFieldVector<IdStoredType        > IdStoreType;
#else 
    typedef          vector      <IdStoredType        > IdStoreType;
#endif
    typedef typename IdStoreType::iterator              IdStoreItType;
    typedef typename IdStoreType::const_iterator        IdStoreConstItType;
    
    typedef          FieldTraits<IdStoredType         > PosMFieldTraits;
    
    
    typedef          FieldTraits     <value_type,
                                      NamespaceI      > PtrMFieldTraits;

    typedef          FieldDescription<PtrMFieldTraits,
                             FieldType::MultiField,
                             RefCountPolicy,
                             FieldType::ParentPtrField> Description;

    typedef          PointerAccessHandler<
                         RefCountPolicy               > AccessHandler;

    // handles
    typedef          void                                    EditHandle;
    typedef          boost::shared_ptr      <EditHandle    > EditHandlePtr;

    typedef          GetFCPtrMFieldHandle   <Self          > GetHandle;
    typedef          boost::shared_ptr      <GetHandle     > GetHandlePtr;

    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditParentPointerMFieldHandle<Self>      DynEditHandle;
//    typedef 
//        typename EditParentPointerMFieldHandle<Self>::Ptr DynEditHandlePtr;
    
//    typedef          GetParentPointerMFieldHandle <Self>      DynGetHandle;
//    typedef typename GetParentPointerMFieldHandle <Self>::Ptr DynGetHandlePtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
        
    static FieldType::Cardinality const fieldCard  = FieldType::MultiField;
    static FieldType::Class       const Class      = FieldType::ParentPtrField;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    ParentPointerMField(      void       );
    ParentPointerMField(const Self &other);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~ParentPointerMField(void); 
              
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    SizeT  getBinSize (void                   ) const;

    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Interface                                        */
    /*! \{                                                                 */
    
    const_iterator         begin (void) const;
    const_iterator         end   (void) const;
    
    const_reverse_iterator rbegin(void) const;
    const_reverse_iterator rend  (void) const;

    value_type             front (void) const;
    value_type             back  (void) const;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name IdStore Interface                                            */
    /*! \{                                                                 */

    iterator               begin_nc (void                       );
    iterator               end_nc   (void                       );
    
#ifndef OSG_CLEAN_FCFIELDS
    iterator               begin    (void                       );
    iterator               end      (void                       );

    reverse_iterator       rbegin   (void                       );
    reverse_iterator       rend     (void                       );
#endif
        
    iterator               insert   (iterator     pos, 
                                     const_value  value,
                                     UInt16       parentFieldPos);

#ifndef OSG_CLEAN_FCFIELDS
    iterator               erase    (iterator     pos           );
    iterator               erase    (iterator     first,
                                     iterator     last          );
#endif

    void                   erase    (size_type    pos           );

#ifndef OSG_CLEAN_FCFIELDS
    iterator               find     (const_value value          );
#endif
    iterator               find_nc  (const_value value          );

    const_iterator         find     (const_value value          ) const;

    void                   push_back(const_value value,
                                     UInt16      parentFieldPos );

    void                   reserve  (size_type   newsize        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw IdStore Access                                           */
    /*! \{                                                                 */

    void replace(UInt32      uiIdx, 
                 const_value value,
                 UInt16      parentFieldPos);

    void replace(iterator    pos, 
                 const_value value,
                 UInt16      parentFieldPos);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Index Operator                                               */
    /*! \{                                                                 */

    value_type operator [](const size_type index) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Index Operator                                               */
    /*! \{                                                                 */

    value_type ptrAt           (const size_type index) const;
    UInt16     parentFieldPosAt(const size_type index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void  syncWith      (Self               &source, 
                         ConstFieldMaskArg   syncMode,
                         UInt32              uiSyncInfo,
                         AspectOffsetStore  &oOffsets    );
#endif
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Index Operator                                               */
    /*! \{                                                                 */

    const Self &operator =(const Self &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType   _fieldType;
           IdStoreType _vParentPos;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    void resize(size_t       newsize, 
                const_value  t      = NULL);

    void clear (void                      );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef PtrMFieldTraits MFieldTraits;
};

OSG_END_NAMESPACE

#include "OSGParentPointerMField.inl"

#endif // _OSGPARENTPOINTERMFIELD_H_
