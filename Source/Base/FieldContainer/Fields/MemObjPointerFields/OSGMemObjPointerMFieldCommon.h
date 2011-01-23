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

#ifndef _OSGMEMOBJPOINTERMFIELDCOMMON_H_
#define _OSGMEMOBJPOINTERMFIELDCOMMON_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGMemObjPointerMFieldBase.h"
#include "OSGBinaryDataHandler.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseMemoryObjectsFields
    \ingroup GrpLibOSGBase
 */

template <class AccessHandlerT,
          Int32 NamespaceI     = 0>
class MemObjPointerMFieldCommon : public MemObjPointerMFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          AccessHandlerT                      AccessHandler;
    typedef          MemObjPointerMFieldBase             Inherited;

    typedef typename Inherited::StorageIt                PtrStoreItType;
    typedef typename Inherited::StorageConstIt           PtrStoreConstItType;

    typedef typename Inherited::StoredType               StoredType;
    typedef typename Inherited::StorageType              PtrStoreType;

    typedef typename Inherited::const_value              const_value;
    typedef typename Inherited::value_type               value_type;

    typedef typename Inherited::size_type                size_type;
    typedef typename Inherited::difference_type          difference_type;

  protected:

    typedef          MemObjPointerMFieldCommon           Self;

    typedef          FieldTraitsFCPtrBase<
                         FieldContainer *, 
                         NamespaceI       >              PtrBaseTraitsType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static Int32 const Namespace = NamespaceI;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             MemObjPointerMFieldCommon(void                );
             MemObjPointerMFieldCommon(const Self   &source);
    explicit MemObjPointerMFieldCommon(const UInt32  size  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~MemObjPointerMFieldCommon(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Store Interface                                              */
    /*! \{                                                                 */

    // reading values
    value_type ptrStoreGet(const UInt32             index) const;
    value_type ptrStoreGet(      PtrStoreItType      pos  ) const;
    value_type ptrStoreGet(      PtrStoreConstItType pos  ) const;

    /*---------------------------------------------------------------------*/
    // adding values

    void           ptrStoreAppend (      const_value    pNewObj);

    template <class InputIteratorT>
    void           ptrStoreAssign (      InputIteratorT first,
                                         InputIteratorT last   );

    void           ptrStoreInsert (const UInt32         index,
                                         const_value    pNewObj);
    void           ptrStoreInsert (      PtrStoreItType pos,
                                         size_type      n,
                                         const_value    pNewObj);
    PtrStoreItType ptrStoreInsert (      PtrStoreItType pos,
                                         const_value    pNewObj);

    template <class InputIteratorT>
    void           ptrStoreInsert (      PtrStoreItType pos,
                                         InputIteratorT first,
                                         InputIteratorT last   );


    /*---------------------------------------------------------------------*/
    // changing values

    void ptrStoreReplace(const UInt32         index,
                               const_value    pNewObj);
    void ptrStoreReplace(      PtrStoreItType pos,
                               const_value    pNewObj);

    /*---------------------------------------------------------------------*/
    // removing values

    void           ptrStoreErase  (const UInt32         index     );
    void           ptrStoreErase  (const UInt32         beginIndex,
                                   const UInt32         endIndex  );

    PtrStoreItType ptrStoreErase  (      PtrStoreItType pos       );
    PtrStoreItType ptrStoreErase  (      PtrStoreItType begin,
                                         PtrStoreItType end       );

    void           ptrStoreClear  (      void                     );

    /*---------------------------------------------------------------------*/
    // resizing

    void ptrStoreResize(const UInt32      newSize,
                              const_value pNewObj);

    /*---------------------------------------------------------------------*/
    // finding values

    PtrStoreItType      ptrStoreFind(const_value pObj);
    PtrStoreConstItType ptrStoreFind(const_value pObj) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std library interface                                        */
    /*! \{                                                                 */
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    void copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

    void syncWith(Self               &source,
                  ConstFieldMaskArg   syncMode,
                  UInt32              uiSyncInfo,
                  AspectOffsetStore  &oOffsets  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    void operator =(const Self &other);
};

OSG_END_NAMESPACE

#include "OSGMemObjPointerMFieldCommon.inl"

#endif // _OSGMEMOBJPOINTERMFIELDCOMMON_H_
