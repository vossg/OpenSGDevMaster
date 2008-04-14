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

#ifndef _OSGPOINTERMFIELDBASE_H_
#define _OSGPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGMField.h"
#include "OSGFieldContainerFieldTraits.h"

#define OSG_CLEAN_FCFIELDS

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING PointerMFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef       Field                               Inherited;
    typedef       PointerMFieldBase                   Self;
    
    // storage
    typedef       FieldContainerPtr                   StoredType;
    typedef       MFieldVector<StoredType>            StorageType;

    typedef       StorageType::const_iterator         const_iterator;
    typedef       StorageType::const_reverse_iterator const_reverse_iterator;

    typedef       StorageType::const_iterator         StorageConstIt;

    typedef const FieldContainerPtr                   const_value;

    typedef       StorageType::size_type              size_type;
    typedef       StorageType::difference_type        difference_type;


    typedef       FieldTraits<FieldContainerPtr, 0>   MFieldTraits;


    // handles
    typedef       EditMFieldHandle <Self      >       EditHandle;
    typedef       boost::shared_ptr<EditHandle>       EditHandlePtr;

    typedef       GetMFieldHandle  <Self     >        GetHandle;
    typedef       boost::shared_ptr<GetHandle>        GetHandlePtr;
    
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
    
    const_value            front    (void             ) const;
    const_value            back     (void             ) const;

    bool                   empty    (void             ) const;
    size_type              size     (void             ) const;
    size_type              max_size (void             ) const;
    size_type              capacity (void             ) const;
    
    difference_type        findIndex(const_value value) const;

    void                   reserve  (size_type   size );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    const_value operator[](const UInt32 index) const;
    const_value at        (const UInt32 index) const;
    
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
    
    PointerMFieldBase(void);
             
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~PointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void operator =(const Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Cast Store Access                                            */
    /*! \{                                                                 */
    
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

    PointerMFieldBase(const Self &obj);
};

typedef PointerMFieldBase FieldContainerPtrMFieldBase;

OSG_END_NAMESPACE

#include "OSGPointerMFieldBase.inl"

#endif // _OSGPOINTERMFIELDBASE_H_
