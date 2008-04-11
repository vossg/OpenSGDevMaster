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

#ifndef _OSGPARENTPOINTERSFIELD_H_
#define _OSGPARENTPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGPointerSFieldCommon.h"
#include "OSGPointerAccessHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerSField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/* ParentPointerSField<ObjectTypeT,                                          */
/*                     NamespaceI  >                                         */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class ParentPointerSField : 
    public PointerSFieldCommon<NoRefCountAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          ObjectTypeT                           ObjectType;
        
    typedef          PointerSFieldCommon    <NoRefCountAccessHandler,
                                             NamespaceI  > Inherited;
    typedef          ParentPointerSField    <ObjectTypeT,
                                             NamespaceI  > Self;
                                             
    typedef ObjectTypeT * ValueType;
    typedef ObjectTypeT * const ArgumentType;
    typedef ObjectTypeT * value_type;

    typedef ArgumentType *const_pointer;
    typedef ValueType const                             &const_reference; 
    
    typedef UInt16                                  IdStoredType;
    typedef UInt16                                 &IdStoredTypeRef;
    typedef UInt16 const                           &IdStoredTypeConstRef;
    
    typedef FieldTraits<IdStoredType >              IdBaseTraitsType;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                     >  SFieldTraits;
    typedef FieldDescription<SFieldTraits,
                             FieldType::SingleField,
                             NoRefCountPolicy,
                             FieldType::ParentPtrField  >  Description;
  protected:
    
    // handles
//    typedef          EditParentPointerSFieldHandle<Self>      EditHandle;
//    typedef typename EditParentPointerSFieldHandle<Self>::Ptr EditHandlePtr;
    
//    typedef          GetParentPointerSFieldHandle <Self>      GetHandle;
//    typedef typename GetParentPointerSFieldHandle <Self>::Ptr GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditParentPointerSFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditParentPointerSFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetParentPointerSFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetParentPointerSFieldHandle <Self>::Ptr DynamicGetHandlePtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
        
    static FieldType::Cardinality const fieldCard  = FieldType::SingleField;
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

    ParentPointerSField(void                          );
    ParentPointerSField(Self const   &other           );
    ParentPointerSField(ValueType     ptrValue,
                        IdStoredType  idValue = 0x0000);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~ParentPointerSField(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name IdStore Interface                                            */
    /*! \{                                                                 */
    
    // reading values
    UInt16 const idStoreGet(void) const;
    
    // changing values
    void idStoreSet  (UInt16 const newId);
    void idStoreClear(void              );

     /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw IdStore Access                                           */
    /*! \{                                                                 */
    
    IdStoredTypeRef      editRawIdStore(void);
    IdStoredTypeConstRef getRawIdStore (void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

    void  syncWith(Self &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    const_reference getValue(void) const;
        
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType    _fieldType;
           IdStoredType _childIdValue;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include "OSGParentPointerSField.inl"

#endif // _OSGPARENTPOINTERSFIELD_H_
