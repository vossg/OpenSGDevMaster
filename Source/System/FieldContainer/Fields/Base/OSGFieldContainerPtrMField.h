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

#ifndef _OSGFIELDCONTAINERPTRMFIELD_H_
#define _OSGFIELDCONTAINERPTRMFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerPtrMFieldBase.h"

#include "OSGRefCountPolicies.h"

#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

template<class    ValueT, 
         typename RefCountPolicy = RecordedRefCounts, 
         Int32    iNamespace     = 0>
class FieldContainerPtrMField : public FieldContainerPtrMFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          MFieldVector <ValueT>                 StorageType;
    typedef typename StorageType::Inherited                StorageTypeParent;

    typedef typename StorageType::reverse_iterator         reverse_iterator;
    typedef typename StorageType::const_reverse_iterator const_reverse_iterator;


    typedef typename StorageType::reference                reference;
    typedef          ValueT                                const_reference;

    typedef          FieldTraits            <ValueT, 
                                             iNamespace>   MFieldTraits;
 
    typedef          FieldContainerPtrMField<ValueT, 
                                             RefCountPolicy,
                                             iNamespace>   Self;

    typedef          ValueT                                StoredType;

    typedef typename MFieldTraits::ArgumentType            ArgumentType;

    typedef          FieldDescription       <MFieldTraits,
                                             MultiField,
                                             RefCountPolicy,
                                             PtrField    > Description;

    typedef          EditFCPtrMFieldHandle  <Self        > EditHandle;
    typedef          boost::shared_ptr      <EditHandle  > EditHandlePtr;

    typedef          GetFCPtrMFieldHandle   <Self        > GetHandle;
    typedef          boost::shared_ptr      <GetHandle   > GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32 Namespace     = iNamespace;

    static const bool isSField       = false;
    static const bool isMField       = true;

    static const bool isPointerField = true;

    /*---------------------------------------------------------------------*/

    template<class StorageTypeT, typename ItRefCountPolicy>
    class ptrfield_iterator;

    template<class StorageTypeT, typename ItRefCountPolicy>
    class const_ptrfield_iterator : protected StorageTypeT::const_iterator
    {
        typedef           FieldContainerPtrMField<ValueT, 
                                                  RefCountPolicy,
                                                  iNamespace    > PtrMField;


        typedef typename StorageTypeT::const_iterator  Inherited;
        typedef typename StorageTypeT::difference_type difference_type;
        typedef typename PtrMField   ::const_reference const_reference;


        friend class ptrfield_iterator<StorageTypeT, ItRefCountPolicy>;

        friend class FieldContainerPtrMField<ValueT, 
                                             RefCountPolicy,
                                             iNamespace>;

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
            const ptrfield_iterator<StorageTypeT, ItRefCountPolicy> &i) : 

            Inherited(i)
        {
        }

        const_reference operator*() const
        { 
            return ItRefCountPolicy::validate(*Inherited::_M_current); 
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

      protected:
    };

    template<class StorageTypeT, typename ItRefCountPolicy>
    class ptrfield_iterator : protected StorageTypeT::iterator
    {
        typedef           FieldContainerPtrMField<ValueT, 
                                                  RefCountPolicy,
                                                  iNamespace    > PtrMField;

        typedef typename StorageTypeT::iterator        Inherited;
        typedef typename StorageTypeT::difference_type difference_type;
        typedef typename PtrMField   ::const_reference const_reference;

        friend class FieldContainerPtrMField<ValueT, 
                                             RefCountPolicy,
                                             iNamespace>;

      public:

        ptrfield_iterator(void) : Inherited()
        {
        }

        ptrfield_iterator(const Inherited &i) : Inherited(i)
        {
        }

        const_reference operator*() const
        { 
            return ItRefCountPolicy::validate(*Inherited::_M_current); 
        }

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
                                          ItRefCountPolicy> &rhs) const
        {
            return *(static_cast<const Inherited *>(this)) == rhs;
        }

        bool operator !=(
            const const_ptrfield_iterator<StorageTypeT,
                                          ItRefCountPolicy> &rhs) const
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

      protected:
    };

    typedef       ptrfield_iterator<StorageType, 
                                    RefCountPolicy>       iterator;
    typedef const_ptrfield_iterator<StorageType,
                                    RefCountPolicy> const_iterator;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             FieldContainerPtrMField(void);
             FieldContainerPtrMField(const Self   &obj );
    explicit FieldContainerPtrMField(const UInt32  size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrMField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setValues(const StorageType       &value);
    void setValues(const StorageTypeParent &value);
    void setValues(const Self              &obj  );
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    void   copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    iterator               begin    (void                              );
    iterator               end      (void                              );

    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
#if 0
    reference              front    (void                              );
    const_reference        front    (void                              ) const;

    reference              back     (void                              );
    const_reference        back     (void                              ) const;
#endif
    
   
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
    
#if 0
    iterator               find     (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;
#endif

    void                   push_back(ArgumentType value                );

    void                   resize   (size_t       newsize, 
                                     StoredType   t      = NullFC      );

    void                   reserve  (size_t       newsize              );

#if 0
    void                   swap     (Self                        &right);

#ifdef OSG_1_COMPAT
    void                   addValue (ArgumentType value                );
#endif
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

#if 0
    void operator =(const Self &source);
#endif

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

    static FieldType   _fieldType;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerPtrMField.inl"
#endif

#endif /* _OSGFIELDCONTAINERPTRMFIELD_H_ */
