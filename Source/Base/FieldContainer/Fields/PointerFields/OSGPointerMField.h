/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

#ifndef _OSGPOINTERMFIELD_H_
#define _OSGPOINTERMFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGPointerMFieldCommon.h"
#include "OSGPointerAccessHandler.h"

OSG_BEGIN_NAMESPACE

// forward declarations
template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI>
class PointerMField;

#ifndef OSG_CLEAN_FCFIELDS
template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI>
class PointerMFieldReferenceProxy;
#endif

template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI>
class PointerMFieldConstIterator;

/*---------------------------------------------------------------------------*/
/* PointerMFieldIterator<PtrTypeT>                                           */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
class PointerMFieldIterator :
    protected PointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::PtrStoreItType
{
    /*==========================  PUBLIC  =================================*/

    template <class AccessHandlerT, Int32 NI>
    friend class PointerMFieldCommon;

    template <class PT, typename RC, Int32 NI>
    friend class PointerMFieldConstIterator;

    template <class PT, typename RC, Int32 NI>
    friend class PointerMField;

    template <class PT, typename RC, Int32 NI>
    friend typename PointerMFieldIterator<PT, RC, NI>::difference_type
        operator-(PointerMFieldIterator     <PT, RC, NI> const &lhs,
                  PointerMFieldIterator     <PT, RC, NI> const &rhs );

    template <class PT, class RC, Int32 NI>
    friend typename PointerMFieldConstIterator<PT, RC, NI>::difference_type
        operator-(PointerMFieldIterator     <PT, RC, NI> const &lhs,
                  PointerMFieldConstIterator<PT, RC, NI> const &rhs );

    template <class PT, class RC, Int32 NI>
    friend typename PointerMFieldConstIterator<PT, RC, NI>::difference_type
        operator-(PointerMFieldConstIterator<PT, RC, NI> const &lhs,
                  PointerMFieldIterator     <PT, RC, NI> const &rhs );

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          PointerMFieldIterator                 Self;

    typedef          PointerMField<PtrTypeT,
                                   RefCountPolicy,
                                   NamespaceI    >      MFieldType;

    typedef typename MFieldType::PtrStoreItType         Inherited;

    typedef typename MFieldType::AccessHandler          AccessHandler;

    typedef          PtrTypeT const                     const_value;

    // store types
    typedef typename MFieldType::StoredType             StoredType;
    typedef typename MFieldType::PtrStoreType           PtrStoreType;
    typedef typename MFieldType::PtrStoreItType         PtrStoreItType;

    typedef typename MFieldType::const_iterator         const_iterator;

    // std library typedefs

    typedef typename Inherited::iterator_category       iterator_category;
    typedef typename Inherited::difference_type         difference_type;
    typedef          PtrTypeT                           value_type;
    typedef          PtrTypeT *                         pointer;

#ifndef OSG_CLEAN_FCFIELDS
    typedef          PointerMFieldReferenceProxy<
                         PtrTypeT,
                         RefCountPolicy,
                         NamespaceI                   > reference;
#else
    typedef typename Inherited::reference               reference;
#endif

#if defined(WIN32) && _SECURE_SCL == 1
    typedef typename Inherited::_Checked_iterator_base_type 
                                                   _Checked_iterator_base_type;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    PointerMFieldIterator(      void                     );
    PointerMFieldIterator(const Self           &source   );

    PointerMFieldIterator(const PtrStoreItType &storeIter,
                                MFieldType     *pField   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~PointerMFieldIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

#ifndef OSG_CLEAN_FCFIELDS
    reference   operator  *(      void                  ) const;
    reference   operator [](const difference_type offset) const;
#else
    const_value operator  *(      void                  ) const;
    const_value operator [](const difference_type offset) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

    Self &operator ++(      void                   );
    Self  operator ++(      int                    );

    Self &operator --(      void                   );
    Self  operator --(      int                    );

    Self &operator +=(const difference_type  offset);
    Self  operator + (const difference_type  offset) const;

    Self &operator -=(const difference_type  offset);
    Self  operator - (const difference_type  offset) const;


    bool operator == (const Self            &rhs   ) const;
    bool operator != (const Self            &rhs   ) const;

    bool operator == (const const_iterator  &rhs   ) const;
    bool operator != (const const_iterator  &rhs   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */

     const PtrStoreItType &base(void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    MFieldType  *_pField;
};

template <class PtrTypeT, class RefCountPolicyT, Int32 NamespaceI>
typename PointerMFieldIterator<PtrTypeT,
                               RefCountPolicyT,
                               NamespaceI      >::difference_type
    operator-(PointerMFieldIterator<PtrTypeT,
                                    RefCountPolicyT,
                                    NamespaceI      > const &lhs,

              PointerMFieldIterator<PtrTypeT,
                                    RefCountPolicyT,
                                    NamespaceI      > const &rhs );

template <class PtrTypeT, class RefCountPolicyT, Int32 NamespaceI>
PointerMFieldIterator<PtrTypeT,
                      RefCountPolicyT,
                      NamespaceI      >

    operator+(
        typename PointerMFieldIterator<
                   PtrTypeT,
                   RefCountPolicyT,
                   NamespaceI      >::differece_type const  offset,

                 PointerMFieldIterator<
                   PtrTypeT,
                   RefCountPolicyT,
                   NamespaceI      >                 const &rhs   );


/*---------------------------------------------------------------------------*/
/* PointerMFieldConstIterator<PtrTypeT>                                      */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
class PointerMFieldConstIterator :
    protected PointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::PtrStoreConstItType
{
    template <class AccessHandlerT, Int32 NI>
    friend class PointerMFieldCommon;

    template <class PT, typename RC, Int32 NI>
    friend class PointerMFieldIterator;

    template <class PT, typename RC, Int32 NI>
    friend class PointerMField;

    template <class PT, class RC, Int32 NI>
    friend typename PointerMFieldConstIterator<PT, RC, NI>::difference_type
        operator-(PointerMFieldConstIterator<PT, RC, NI> const &lhs,
                  PointerMFieldConstIterator<PT, RC, NI> const &rhs );

    template <class PT, class RC, Int32 NI>
    friend typename PointerMFieldConstIterator<PT, RC, NI>::difference_type
        operator-(PointerMFieldIterator     <PT, RC, NI> const &lhs,
                  PointerMFieldConstIterator<PT, RC, NI> const &rhs );

    template <class PT, class RC, Int32 NI>
    friend typename PointerMFieldConstIterator<PT, RC, NI>::difference_type
        operator-(PointerMFieldConstIterator<PT, RC, NI> const &lhs,
                  PointerMFieldIterator     <PT, RC, NI> const &rhs );

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          PointerMFieldConstIterator         Self;

    typedef          PointerMField<PtrTypeT,
                                   RefCountPolicy,
                                   NamespaceI       >   MFieldType;

    typedef typename MFieldType::PtrStoreConstItType    Inherited;

    typedef typename MFieldType::AccessHandler          AccessHandler;

    typedef          PtrTypeT const                     const_value;

    // store types
    typedef typename MFieldType::StoredType             StoredType;
    typedef typename MFieldType::PtrStoreType           PtrStoreType;
    typedef typename MFieldType::PtrStoreConstItType    PtrStoreConstItType;

    typedef typename MFieldType::iterator               iterator;

    // std library types
    typedef typename Inherited::iterator_category       iterator_category;
    typedef typename Inherited::difference_type         difference_type;
    typedef typename Inherited::value_type              value_type;
    typedef typename Inherited::pointer                 pointer;
    typedef typename Inherited::reference               reference;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

             PointerMFieldConstIterator(      void                          );
             PointerMFieldConstIterator(const Self                &source   );
             PointerMFieldConstIterator(const iterator            &fieldIter);
    explicit PointerMFieldConstIterator(const PtrStoreConstItType &storeIter);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~PointerMFieldConstIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

    const_value operator * (       void                 ) const;
    const_value operator [](const difference_type offset) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

    Self &operator ++(      void                   );
    Self  operator ++(      int                    );

    Self &operator --(      void                   );
    Self  operator --(      int                    );

    Self &operator +=(const difference_type  offset);
    Self  operator + (const difference_type  offset) const;

    Self &operator -=(const difference_type  offset);
    Self  operator - (const difference_type  offset) const;


    bool operator == (const Self            &rhs   ) const;
    bool operator != (const Self            &rhs   ) const;

    bool operator == (const iterator        &rhs   ) const;
    bool operator != (const iterator        &rhs   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */

    const PtrStoreConstItType &base(void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

};

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename PointerMFieldConstIterator<PtrTypeT,
                                    RefCountPolicyT,
                                    iNamespace      >::difference_type
    operator-(PointerMFieldConstIterator<PtrTypeT,
                                         RefCountPolicyT,
                                         iNamespace      > const &lhs,
              PointerMFieldConstIterator<PtrTypeT,
                                         RefCountPolicyT,
                                         iNamespace      > const &rhs );

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename PointerMFieldConstIterator<PtrTypeT,
                                    RefCountPolicyT,
                                    iNamespace      >::difference_type
    operator-(PointerMFieldIterator     <PtrTypeT,
                                         RefCountPolicyT,
                                         iNamespace      > const &lhs,
              PointerMFieldConstIterator<PtrTypeT,
                                         RefCountPolicyT,
                                         iNamespace      > const &rhs );

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename PointerMFieldConstIterator<PtrTypeT,
                                    RefCountPolicyT,
                                    iNamespace      >::difference_type
    operator-(PointerMFieldConstIterator<PtrTypeT,
                                         RefCountPolicyT,
                                         iNamespace      > const &lhs,
              PointerMFieldIterator     <PtrTypeT,
                                         RefCountPolicyT,
                                         iNamespace      > const &rhs );

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
PointerMFieldConstIterator<PtrTypeT, RefCountPolicyT, iNamespace>
    operator+(
        typename PointerMFieldConstIterator<
                   PtrTypeT,
                   RefCountPolicyT,
                   iNamespace      >::difference_type const   offset,

                 PointerMFieldConstIterator<
                   PtrTypeT,
                   RefCountPolicyT,
                   iNamespace      >                  const &rhs    );


#ifndef OSG_CLEAN_FCFIELDS
/*-------------------------------------------------------------------------*/
/* WeakMFieldReferenceProxy<PtrTypeT>                                      */
/*-------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
class PointerMFieldReferenceProxy
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          PointerMFieldReferenceProxy        Self;

    typedef          PointerMField<PtrTypeT,
                                   RefCountPolicy,
                                   NamespaceI    >      MFieldType;

    typedef typename MFieldType::AccessHandler          AccessHandler;

    // store types
    typedef typename MFieldType::StoredType             StoredType;
    typedef typename MFieldType::PtrStoreType           PtrStoreType;
    typedef typename MFieldType::PtrStoreItType         PtrStoreItType;
    typedef typename MFieldType::PtrStoreConstItType    PtrStoreConstItType;

    // std library types
    typedef          PtrTypeT                           value_type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    PointerMFieldReferenceProxy(const PtrStoreItType &storeIter,
                                      MFieldType     *pField   );

    PointerMFieldReferenceProxy(const Self           &source   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~PointerMFieldReferenceProxy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */

               operator value_type(void) const;
    value_type operator->         (void) const;

    void operator=(value_type newValue);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    PtrStoreItType  _storeIter;
    MFieldType     *_pField;
};
#endif

/*---------------------------------------------------------------------------*/
/* WeakPointerMField<FieldConfigT>                                           */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI  = 0>
class PointerMField :
    public PointerMFieldCommon<PointerAccessHandler<RefCountPolicy>,
                               NamespaceI                          >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef PointerMFieldCommon  <
                PointerAccessHandler<RefCountPolicy>,
                NamespaceI                           > Inherited;

    typedef PointerMField                              Self;

    typedef PtrTypeT const                             const_value;
    typedef PtrTypeT                                   value_type;
    typedef value_type                                 StoredType;

    typedef typename Inherited::size_type              size_type;
    typedef typename Inherited::difference_type        difference_type;

    typedef PointerMFieldIterator      <PtrTypeT,
                                        RefCountPolicy,
                                        NamespaceI    > iterator;

    typedef PointerMFieldConstIterator <PtrTypeT,
                                        RefCountPolicy,
                                        NamespaceI    > const_iterator;

    typedef std::reverse_iterator      <iterator      > reverse_iterator;
    typedef std::reverse_iterator      <const_iterator> const_reverse_iterator;


    typedef FieldTraits                <value_type,
                                        NamespaceI    > MFieldTraits;
    typedef FieldDescription           <
                MFieldTraits,
                FieldType::MultiField,
                RefCountPolicy,
                FieldType::PtrField                   > Description;

#ifndef OSG_CLEAN_FCFIELDS
    typedef PointerMFieldReferenceProxy<PtrTypeT,
                                        RefCountPolicy,
                                        NamespaceI    > reference;
#endif

    // handles
    typedef          EditFCPtrMFieldHandle  <Self          > EditHandle;
    typedef          boost::shared_ptr      <EditHandle    > EditHandlePtr;

    typedef          GetFCPtrMFieldHandle   <Self          > GetHandle;
    typedef          boost::shared_ptr      <GetHandle     > GetHandlePtr;

    // handles for dynamic fields -- XXX TODO
//    typedef          EditPointerMFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditPointerMFieldHandle<Self>::Ptr DynamicEditHandlePtr;

//    typedef          GetPointerMFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetPointerMFieldHandle <Self>::Ptr DynamicGetHandlePtr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */

    static FieldType::Cardinality const fieldCard = FieldType::MultiField;
    static FieldType::Class       const Class     = FieldType::PtrField;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

             PointerMField(      void         );
             PointerMField(const Self   &other);
    explicit PointerMField(const UInt32  size );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~PointerMField(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name String/Stream IO (Input)                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

#ifdef OSG_FIELD_TOCHECK
    void setValues(const StorageType       &value);
    void setValues(const StorageTypeParent &value);
    void setValues(const Self              &obj  );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    void copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    iterator  begin_nc(void             );
    iterator  end_nc  (void             );

#ifndef OSG_CLEAN_FCFIELDS
    reference front_nc(void             );
    reference back_nc (void             );
#endif

    iterator  find_nc (const_value value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Interface                                        */
    /*! \{                                                                 */

#ifndef OSG_CLEAN_FCFIELDS
    iterator               begin    (void                           );
    iterator               end      (void                           );

    reverse_iterator       rbegin   (void                           );
    reverse_iterator       rend     (void                           );
#endif

    const_iterator         begin    (void                           ) const;
    const_iterator         end      (void                           ) const;

    const_reverse_iterator rbegin   (void                           ) const;
    const_reverse_iterator rend     (void                           ) const;

#ifndef OSG_CLEAN_FCFIELDS
    reference              front    (void                           );
    reference              back     (void                           );
#endif

    const_value            front    (void                           ) const;
    const_value            back     (void                           ) const;

    iterator               insert   (iterator       pos,
                                     const_value    value           );

    void                   insert   (iterator       pos,
                                     size_type      n,
                                     const_value    value           );

    template <class InputIteratorT>
    void                   insert   (iterator       pos,
                                     InputIteratorT first,
                                     InputIteratorT last            );

    void                   erase    (size_type      index           );
#ifndef OSG_CLEAN_FCFIELDS
    iterator               erase    (iterator       pos             );
    iterator               erase    (iterator       first,
                                     iterator       last            );
#endif

#ifndef OSG_CLEAN_FCFIELDS
    iterator               find     (const_value    value           );
#endif
    const_iterator         find     (const_value    value           ) const;

    void                   push_back(const_value    value           );

    void                   resize   (size_t         newSize,
                                     const_value    value   = NULL  );

    void                   reserve  (size_type      size            );

    void                   clear    (void                           );

#ifdef OSG_1_COMPAT
    void                   addValue (const_value    value           );
#endif

    void                   assign   (size_type      newSize,
                                     const_value    value   = NULL  );

    template <class InputIteratorT>
    void                   assign   (InputIteratorT first,
                                     InputIteratorT last            );

    void                   replace  (UInt32         uiIdx,
                                     const_value    value           );

    void                   replace  (iterator       pos,
                                     const_value    value           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Index Operator                                               */
    /*! \{                                                                 */

#ifndef OSG_CLEAN_FCFIELDS
          reference operator [](UInt32 const index);
#endif
    const_value     operator [](UInt32 const index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */

    Self &operator =(Self const &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith(Self               &source,
                  ConstFieldMaskArg   syncMode,
                  UInt32              uiSyncInfo,
                  AspectOffsetStore  &oOffsets    );
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */

    static FieldType _fieldType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name FieldDesc creation                                           */
    /*! \{                                                                 */

    static FieldDescriptionBase *
        createFieldDescription   (const Char8                *szFieldname,
                                        UInt32                uiFieldFlags,
                                        FieldEditMethod       fEditMethod,
                                        FieldGetMethod        fGetMethod  );

    static FieldDescriptionBase *
        createIdxFieldDescription(const Char8                *szFieldname,
                                        UInt32                uiFieldFlags,
                                        FieldIndexEditMethod  fEditMethod,
                                        FieldIndexGetMethod   fGetMethod  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include "OSGPointerMField.inl"

#endif // _OSGPOINTERMFIELD_H_
