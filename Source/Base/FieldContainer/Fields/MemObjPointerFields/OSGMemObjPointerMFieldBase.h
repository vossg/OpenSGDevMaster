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

#ifndef _OSGMEMOBJPOINTERMFIELDBASE_H_
#define _OSGMEMOBJPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"
#include "OSGMField.h"
#include "OSGMemoryObjectFieldTraits.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseMemoryObjectsFields
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING MemObjPointerMFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef Field                                       Inherited;
    typedef MemObjPointerMFieldBase                     Self;
    
    // storage
    typedef MemoryObject                        *       StoredType;
    typedef MFieldVector<StoredType>                    StorageType;

    typedef StorageType::const_iterator                 const_iterator;
    typedef StorageType::const_reverse_iterator         const_reverse_iterator;

    typedef StorageType::const_iterator                 StorageConstIt;

    typedef MemoryObject                        * const const_value;
    typedef MemoryObject                        *       value_type;

    typedef StorageType::size_type                      size_type;
    typedef StorageType::difference_type                difference_type;


    typedef FieldTraits<MemoryObject *, 0>              MFieldTraits;


    // handles
    typedef EditMFieldHandle <Self      >               EditHandle;
    typedef boost::shared_ptr<EditHandle>               EditHandlePtr;

    typedef GetMFieldHandle  <Self     >                GetHandle;
    typedef boost::shared_ptr<GetHandle>                GetHandlePtr;
    
    /*---------------------------------------------------------------------*/

    static const bool isSField       = false;
    static const bool isMField       = true;

    static const bool isPointerField = true;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize(void                   ) const;
    
    void   copyToBin (BinaryDataHandler &pMem) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Const Interface                                  */
    /*! \{                                                                 */
    
    const_iterator         begin    (void             ) const;
    const_iterator         end      (void             ) const;
    
    const_reverse_iterator rbegin   (void             ) const;
    const_reverse_iterator rend     (void             ) const;
    
    value_type             front    (void             ) const;
    value_type             back     (void             ) const;

    bool                   empty    (void             ) const;
    size_type              size     (void             ) const;
    size_type              max_size (void             ) const;
    size_type              capacity (void             ) const;
    
    difference_type        findIndex(const_value value) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    value_type operator[](const UInt32 index) const;
    value_type at        (const UInt32 index) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw Store Access                                             */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

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

#ifdef OSG_MT_CPTR_ASPECT
    void beginEdit      (UInt32              uiAspect,
                         AspectOffsetStore  &oOffsets    );

    Self *resolveShare  (UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    void  terminateShare(UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    bool  isShared      (void                            );
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef StorageType::iterator iterator;
    typedef StorageType::iterator StorageIt;

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType   _fieldType;
           StorageType _ptrStore;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    MemObjPointerMFieldBase(void);
             
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~MemObjPointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void reserve(size_type size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void operator =(const Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Cast Store Access                                            */
    /*! \{                                                                 */
    
    /*! \nohierarchy */
    template <class TargetStoredTypeT>
    struct rebindStore
    {
        typedef MFieldVector<TargetStoredTypeT> type;
    };

    template <class TargetStoredTypeT>
    typename rebindStore<TargetStoredTypeT>::type       &editStore(void);
    
    template <class TargetStoredTypeT>
    typename rebindStore<TargetStoredTypeT>::type const &getStore (void) const;

    StorageType       &editRawStore(void);
    StorageType const &getRawStore (void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    MemObjPointerMFieldBase(const Self &obj);
};

typedef MemObjPointerMFieldBase MemoryObjectPtrMFieldBase;

OSG_END_NAMESPACE

#include "OSGMemObjPointerMFieldBase.inl"

#endif // _OSGMEMOBJPOINTERMFIELDBASE_H_
