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

#ifndef _OSGMEMOBJPOINTERSFIELD_H_
#define _OSGMEMOBJPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGMemObjPointerSFieldCommon.h"
#include "OSGMemObjPointerAccessHandler.h"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/* WeakMemObjPointerSField<FieldConfigT>                                     */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseMemoryObjectsFields
    \ingroup GrpLibOSGBase
 */

template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI  = 0>
class MemObjPointerSField : 
    public MemObjPointerSFieldCommon<
             MemObjPointerAccessHandler<RefCountPolicy>, 
                                        NamespaceI     >
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef MemObjPointerSFieldCommon<
                MemObjPointerAccessHandler<RefCountPolicy>, 
                NamespaceI                                >  Inherited;

    
    typedef MemObjPointerSField                              Self;

    typedef PtrTypeT                                         value_type;
    typedef PtrTypeT const                                   const_value;

    typedef value_type                                       StoredType;

    typedef FieldTraits          <value_type,
                                  NamespaceI            >    SFieldTraits;

    typedef FieldDescription     <SFieldTraits,
                                  FieldType::SingleField,
                                  RefCountPolicy,
                                  FieldType::PtrField   >    Description;
 

    // handles

    typedef EditFCPtrSFieldHandle<Self                  >   EditHandle;
    typedef boost::shared_ptr    <EditHandle            >   EditHandlePtr;

    typedef GetFCPtrSFieldHandle <Self                  >   GetHandle;
    typedef boost::shared_ptr    <GetHandle             >   GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditPointerSFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditPointerSFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetPointerSFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetPointerSFieldHandle <Self>::Ptr DynamicGetHandlePtr;

   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static FieldType::Cardinality const Card  = FieldType::SingleField;
    static FieldType::Class       const Class = FieldType::PtrField;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

             MemObjPointerSField(      void               );
             MemObjPointerSField(const Self        &source);

    explicit MemObjPointerSField(      const_value  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~MemObjPointerSField(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    const_value getValue(      void               ) const;
    
    void        setValue(      const_value  value );
    void        setValue(const Self        &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    void copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith(Self &source);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */

    void operator = (const Self &source);
    
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

#include "OSGMemObjPointerSField.inl"

#endif // _OSGMEMOBJPOINTERSFIELD_H_
