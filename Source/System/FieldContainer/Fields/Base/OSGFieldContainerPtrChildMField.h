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

#ifndef _OSGFIELDCONTAINERPTRCHILDMFIELD_H_
#define _OSGFIELDCONTAINERPTRCHILDMFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerPtrMFieldBase.h"

#include "OSGRefCountPolicies.h"

#include <boost/function.hpp>  
#include <boost/mpl/if.hpp>

OSG_BEGIN_NAMESPACE

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace     = 0>
class FieldContainerPtrChildMField : public FieldContainerPtrMFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

#ifndef OSG_CLEAN_FCFIELDS
    class                                                     ReferenceProxy;
#endif

    typedef          MFieldVector <ValueT>                    StorageType;
    typedef typename StorageType::Inherited                   StorageTypeParent;

#ifndef OSG_CLEAN_FCFIELDS
    typedef          ReferenceProxy                           reference;
#endif

    typedef          ValueT                                   const_reference;

    typedef          FieldTraits              <ValueT, 
                                               iNamespace   > MFieldTraits;
 
    typedef          FieldContainerPtrChildMField<
                         ValueT, 
                         RefCountPolicy,
                         iNamespace                         > Self;

    typedef          ValueT                                   StoredType;
    typedef typename MFieldTraits::ParentType                 ParentT;

    typedef const    ValueT                                   ArgumentType;

    typedef          FieldDescription       <
                         MFieldTraits,
                         FieldType::MultiField,
                         RefCountPolicy,
                         FieldType::ChildPtrField           > Description;

    typedef          EditFCPtrMFieldHandle  <Self           > EditHandle;
    typedef          boost::shared_ptr      <EditHandle     > EditHandlePtr;

    typedef          GetFCPtrMFieldHandle   <Self           > GetHandle;
    typedef          boost::shared_ptr      <GetHandle      > GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32            Namespace = iNamespace;

    static const FieldType::Class Class     = FieldType::ChildPtrField;

    /*---------------------------------------------------------------------*/

    template<class    StorageTypeT, 
             typename ItRefCountPolicy,
             typename Value,
             Int32    INamespace>
    class ptrfield_iterator;

    template<class    StorageTypeT, 
             typename ItRefCountPolicy,
             class    Value,
             Int32    INamespace>
    class const_ptrfield_iterator : protected StorageTypeT::const_iterator
    {
        typedef           FieldContainerPtrChildMField<Value, 
                                                       RefCountPolicy,
                                                       INamespace   > PtrMField;


        typedef typename StorageTypeT::const_iterator  Inherited;
        typedef typename StorageTypeT::difference_type difference_type;
        typedef typename PtrMField   ::const_reference const_reference;


        friend class ptrfield_iterator<StorageTypeT, 
                                       ItRefCountPolicy,
                                       Value,
                                       INamespace>;

        friend class FieldContainerPtrChildMField<Value, 
                                                  RefCountPolicy,
                                                  INamespace>;

      public:

        const_ptrfield_iterator(void) : 
            Inherited()
        {
        }

        const_ptrfield_iterator(const Inherited &i) : 
            Inherited(i)
        {
        }

        const_ptrfield_iterator(
            const ptrfield_iterator<StorageTypeT, 
                                    ItRefCountPolicy,
                                    Value,
                                    INamespace> &i) : 

            Inherited(i)
        {
        }

        const_ptrfield_iterator(const const_ptrfield_iterator &source) :
            Inherited(source)
        {
        }

        const_reference operator*() const
        { 
#ifndef WIN32
            return ItRefCountPolicy::validate(*Inherited::_M_current); 
#else
            return ItRefCountPolicy::validate(*Inherited::_Myptr); 
#endif
        }

        bool operator ==(const const_ptrfield_iterator &rhs) const
        {
            return *(static_cast<const Inherited *>(this)) == rhs;
        }

        bool operator !=(const const_ptrfield_iterator &rhs) const
        {
            return ! (*this == rhs);
        }

        const_ptrfield_iterator &operator ++(void)
        {
            Inherited::operator ++();

            return *this;
        }

        const_ptrfield_iterator operator +(const difference_type dOff)
        {
            const_ptrfield_iterator returnValue(*this);

            returnValue += dOff;

            return returnValue;
        }

        void operator =(const const_ptrfield_iterator &rhs)
        {
            if(this != &rhs)
            {
                Inherited::operator =(rhs);
            }
        }

      protected:
    };

    template<class    StorageTypeT, 
             typename ItRefCountPolicy,
             class    Value,
             Int32    INamespace>
    class ptrfield_iterator : protected StorageTypeT::iterator
    {
        typedef           FieldContainerPtrChildMField<Value, 
                                                  ItRefCountPolicy,
                                                  INamespace    > PtrMField;

        typedef typename StorageTypeT::iterator        Inherited;
        typedef typename StorageTypeT::difference_type difference_type;
        typedef typename PtrMField   ::const_reference const_reference;

        friend class FieldContainerPtrChildMField<Value, 
                                                  ItRefCountPolicy,
                                                  INamespace>;

      public:

        ptrfield_iterator(void) : 
             Inherited(    ), 
            _pField   (NULL)
        {
        }

        ptrfield_iterator(const Inherited &i,
                                PtrMField *pField) : 
             Inherited(i     ), 
            _pField   (pField)
        {
        }
           
        ptrfield_iterator(const ptrfield_iterator &source) :
             Inherited(source        ), 
            _pField   (source._pField)
        {
        }

#ifndef OSG_CLEAN_FCFIELDS
        reference operator*() const
        { 
            return ReferenceProxy(this, _pField);
        }
#else
        const_reference operator*() const
        { 
#ifndef WIN32
            return ItRefCountPolicy::validate(*Inherited::_M_current); 
#else
            return ItRefCountPolicy::validate(*Inherited::_Myptr); 
#endif
        }
#endif

        bool operator ==(const ptrfield_iterator &rhs) const
        {
            return *(static_cast<const Inherited *>(this)) == rhs;
        }

        bool operator !=(const ptrfield_iterator &rhs) const
        {
            return ! (*this == rhs);
        }

        bool operator ==(
            const const_ptrfield_iterator<StorageTypeT,
                                          ItRefCountPolicy,
                                          Value,
                                          INamespace> &rhs) const
        {
            return *(static_cast<const Inherited *>(this)) == rhs;
        }

        bool operator !=(
            const const_ptrfield_iterator<StorageTypeT,
                                          ItRefCountPolicy,
                                          Value,
                                          INamespace> &rhs) const
        {
            return ! (*this == rhs);
        }

        ptrfield_iterator &operator ++(void)
        {
            Inherited::operator ++();

            return *this;
        }

        ptrfield_iterator &operator +=(const difference_type dOff)
        {
            Inherited::operator +=(dOff);

            return *this;
        }

        ptrfield_iterator operator +(const difference_type dOff)
        {
            ptrfield_iterator returnValue(*this);

            returnValue += dOff;

            return returnValue;
        }

        const_reference deref(void) const
        { 
#ifndef WIN32
            return ItRefCountPolicy::validate(*Inherited::_M_current); 
#else
            return ItRefCountPolicy::validate(*Inherited::_Myptr); 
#endif
        }

        void operator =(const ptrfield_iterator &rhs)
        {
            if(this != &rhs)
            {
                Inherited::operator =(rhs);
                
                _pField = rhs._pField;
            }
        }

      protected:

        PtrMField *_pField;
    };

    typedef       ptrfield_iterator<StorageType, 
                                    RefCountPolicy,
                                    ValueT,
                                    iNamespace>       iterator;
    typedef const_ptrfield_iterator<StorageType,
                                    RefCountPolicy,
                                    ValueT,
                                    iNamespace> const_iterator;
#ifndef OSG_CLEAN_FCFIELDS
    class ReferenceProxy
    {
      public:

        typedef ReferenceProxy                               Self;

        typedef iterator                                     StorageIt;
        typedef StoredType                                   ValueType;

        typedef FieldContainerPtrChildMField<ValueT, 
                                             RefCountPolicy,
                                             iNamespace    > PtrMField;

        typedef RefCountPolicy                               RefCountPolicyT;

        ReferenceProxy(StorageIt  iIt,
                       PtrMField *pField) : _storeIt(iIt), _pField(pField)
        {
        }

        ReferenceProxy(const ReferenceProxy &source) :
            _storeIt(source._storeIt),
            _pField (source._pField )
        {
        }

        ~ReferenceProxy(void)
        {
        }        

        operator typename Self::ValueType (void) const
        {
            return RefCountPolicyT::validate(_storeIt.deref());
        }
        
        typename Self::ValueType operator->(void) const
        {
            return RefCountPolicyT::validate(_storeIt.deref());
        }

        void operator =(Self::ValueType pNewElement)
        {
            if(pNewElement != *_storeIt)
            {
                _pField->replace(_storeIt, pNewElement);
            }
        }

      protected:

        StorageIt  _storeIt;
        PtrMField *_pField;
    };
#endif
   
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtrChildMField(ParentT pParent,
                                 UInt16  usChildFieldId,
                                 UInt16  usParentFieldId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrChildMField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

#if 0
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

    iterator               begin_nc (void                              );
    iterator               end_nc   (void                              );

    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
#ifndef OSG_CLEAN_FCFIELDS
    reference              front_nc (void                              );
    reference              back_nc  (void                              );
#endif

    const_reference        front    (void                              ) const;
    const_reference        back     (void                              ) const;
   
    iterator               insert   (iterator     pos, 
                                     ArgumentType value                );

#if 0
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
#endif

    void                   clear    (void                              );

    iterator               erase    (iterator     pos                  );

    iterator               erase    (iterator     first,
                                     iterator     last                 );
    
    iterator               find_nc  (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;

    void                   push_back(ArgumentType value                );

    void                   resize   (size_t       newsize, 
                                     StoredType   t      = NullFC      );

    void                   reserve  (size_t       newsize              );

#ifdef OSG_1_COMPAT
    void                   addValue (ArgumentType value                );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    void replace(UInt32       uiIdx, 
                 ArgumentType value);

    void replace(iterator     pos, 
                 ArgumentType value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

#ifndef OSG_CLEAN_FCFIELDS
          reference operator [](UInt32 index);
#endif
    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

#if 0
    bool operator ==(const Self &source) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith       (Self               &source, 
                         ConstFieldMaskArg   syncMode,
                         UInt32              uiSyncInfo,
                         AspectOffsetStore  &oOffsets    );
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

#if 0
    struct SingleParentHandler
    {
        static void updateParentLinking(ArgumentType value,
                                        ParentT      pParent,
                                        UInt16       usParentFieldPos)
        {
            // already somebody else's child?
            if(value != NULL)
            {
                if(value->getParent() != NullFC)
                {
                    value->getParent()->subChildPointer(value, 
                                                        usParentFieldPos);
                }

                value->setParent(pParent, usParentFieldPos);
            }
        }

        static void clearParentLinking(ArgumentType value,
                                       ParentT      ,
                                       UInt16       usParentFieldPos)
        {
            if(value != NullFC)
                value->setParent(NullFC, usParentFieldPos);
        }
    };

    struct MultiParentHandler
    {
        static void updateParentLinking(ArgumentType value,
                                        ParentT      pParent,
                                        UInt16       usParentFieldPos)
        {
            // already somebody else's child?
            if(value != NULL)
            {
                value->addParent(pParent, usParentFieldPos);
            }
        }
 
        static void clearParentLinking(ArgumentType value,
                                       ParentT      pParent,
                                       UInt16              )
        {
            if(value != NullFC)
                value->subParent(pParent);
        }
    };

    typedef typename
      boost::mpl::if_<
        boost::mpl::bool_<
                  (MFieldTraits::eParentCard == FieldType::SingleField)>,
        SingleParentHandler,
        MultiParentHandler>::type ParentHandler;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef FieldContainerPtrMFieldBase Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

    template<class To>
          To &dcast(void);

    template<class To>
    const To &dcast(void) const;

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ParentT _pParent;
    UInt16  _usChildFieldId;
    UInt16  _usParentFieldId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType   _fieldType;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    void operator =(const Self &source);
};

OSG_END_NAMESPACE

#include "OSGFieldContainerPtrChildMField.inl"

#endif /* _OSGFIELDCONTAINERPTRCHILDMFIELD_H_ */
