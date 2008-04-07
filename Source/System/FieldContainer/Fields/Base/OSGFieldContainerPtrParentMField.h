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

#ifndef _OSGFIELDCONTAINERPTRPARENTMFIELD_H_
#define _OSGFIELDCONTAINERPTRPARENTMFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerPtrMFieldBase.h"

#include "OSGFieldContainerFieldTraits.h"
#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace     = 0>
class FieldContainerPtrParentMField : public FieldContainerPtrMFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          MFieldVector <ValueT>                    StorageType;
    typedef typename StorageType::Inherited                   StorageTypeParent;

    typedef typename StorageType::reference                   reference;
    typedef const    ValueT                                   const_reference;

    typedef typename StorageType::size_type                   size_type;

    typedef          FieldTraits            <ValueT, 
                                             iNamespace>      PtrMFieldTraits;

    typedef          FieldTraits            <UInt16, 0>       PosMFieldTraits;
 
    typedef          FieldContainerPtrParentMField<
                         ValueT, 
                         RefCountPolicy,
                         iNamespace>   Self;

    typedef          ValueT                                   StoredType;

    typedef const    ValueT                                   ArgumentType;

    typedef          FieldDescription       <PtrMFieldTraits,
                                             MultiField,
                                             RefCountPolicy,
                                             ParentPtrField > Description;

    typedef          EditFCPtrMFieldHandle  <Self           > EditHandle;
    typedef          boost::shared_ptr      <EditHandle     > EditHandlePtr;

    typedef          GetFCPtrMFieldHandle   <Self           > GetHandle;
    typedef          boost::shared_ptr      <GetHandle      > GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32 Namespace     = iNamespace;

    /*---------------------------------------------------------------------*/

    template<class StorageTypeT>
    class ptrfield_iterator : protected StorageTypeT::iterator
    {
        typedef typename StorageTypeT::iterator Inherited;

        typedef std::vector<UInt16>           PosStorage;
        typedef std::vector<UInt16>::iterator PosStorageIt;

        PosStorageIt _posIt;

      public:

        ptrfield_iterator(void) : Inherited()
        {
        }

        ptrfield_iterator(const Inherited     &i,
                          const PosStorageIt &ip) : 
             Inherited( i),
            _posIt    (ip)
            
        {
        }

        ptrfield_iterator(const ptrfield_iterator &i) : 
             Inherited(i       ),
            _posIt    (i._posIt)
            
        {
        }

        const_reference operator*() const
        { 
#ifndef WIN32
            return *Inherited::_M_current; 
#else
            return *Inherited::_Myptr; 
#endif
        }

        UInt16 getParentFieldPos(void) const
        {
            return *_posIt;
        }

        bool operator ==(const ptrfield_iterator &rhs) const
        {
            return *(static_cast<const Inherited *>(this)) == rhs;
        }

        bool operator !=(const ptrfield_iterator &rhs) const
        {
            return ! (*this == rhs);
        }

        ptrfield_iterator &operator ++(void)
        {
            Inherited::operator ++();

            ++_posIt;

            return *this;
        }
             
        void operator =(const ptrfield_iterator &rhs)
        {
            if(this != &rhs)
            {
                Inherited::operator =(rhs);
                
                _posIt = rhs._posIt;
            }
        }

      protected:
    };

    template<class StorageTypeT>
    class const_ptrfield_iterator : protected StorageTypeT::const_iterator
    {
        typedef typename StorageTypeT::const_iterator Inherited;

        typedef std::vector<UInt16>                 PosStorage;
        typedef std::vector<UInt16>::const_iterator PosStorageIt;

        PosStorageIt _posIt;

      public:

        const_ptrfield_iterator(void) : Inherited()
        {
        }

        const_ptrfield_iterator(const Inherited     &i,
                                const PosStorageIt &ip) : 
             Inherited( i),
            _posIt    (ip)
            
        {
        }

        const_ptrfield_iterator(const const_ptrfield_iterator &i) : 
             Inherited(i       ),
            _posIt    (i._posIt)
            
        {
        }

        const_reference operator*() const
        { 
#ifndef WIN32
            return *Inherited::_M_current; 
#else
            return *Inherited::_Myptr; 
#endif
        }

        UInt16 getParentFieldPos(void) const
        {
            return *_posIt;
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

            ++_posIt;

            return *this;
        }
             
        void operator =(const const_ptrfield_iterator &rhs)
        {
            if(this != &rhs)
            {
                Inherited::operator =(rhs);
                
                _posIt = rhs._posIt;
            }
        }

      protected:
    };

    typedef       ptrfield_iterator<StorageType>       iterator;
    typedef const_ptrfield_iterator<StorageType> const_iterator;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtrParentMField(void);
    FieldContainerPtrParentMField(const Self   &obj );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrParentMField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

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

    iterator               begin_nc (void                              );
    iterator               end_nc   (void                              );

    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
    const_reference        front    (void                              ) const;
    const_reference        back     (void                              ) const;
    
    iterator               insert   (iterator     pos, 
                                     ArgumentType value,
                                     UInt16       parentFieldPos       );

    iterator               erase    (iterator     pos                  );
    void                   erase    (size_type    pos                  );
    
    iterator               find     (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;

    void                   push_back(ArgumentType value,
                                     UInt16       parentFieldPos       );

    void                   reserve  (size_t       newsize              );


#ifdef OSG_1_COMPAT
    void                   addValue (ArgumentType value,
                                     UInt16       parentFieldPos       );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

#if 0
    void replace(UInt32       uiIdx, 
                 ArgumentType value);

    void replace(iterator     pos, 
                 ArgumentType value);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

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

    std::vector<UInt16> _vParentPos;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType   _fieldType;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    void resize   (size_t       newsize, 
                   StoredType   t      = NullFC);

    void clear    (void                         );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef PtrMFieldTraits MFieldTraits;

    void operator =(const Self &source);
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerPtrParentMField.inl"
#endif

#endif /* _OSGFIELDCONTAINERPTRPARENTMFIELD_H_ */
