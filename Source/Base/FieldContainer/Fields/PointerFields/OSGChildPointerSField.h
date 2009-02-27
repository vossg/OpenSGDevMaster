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

#ifndef _OSGCHILDPOINTERSFIELD_H_
#define _OSGCHILDPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGChildPointerSFieldBase.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

/*---------------------------------------------------------------------------*/
/* ChildPointerSField<FieldConfigT>                                          */
/*---------------------------------------------------------------------------*/

template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI  = 0>
class ChildPointerSField : 
    public ChildPointerSFieldBase<ChildAccessHandler<RefCountPolicy>,
                                  NamespaceI                       >
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef ChildPointerSFieldBase<
                ChildAccessHandler<RefCountPolicy>,
                NamespaceI                        >          Inherited;
    
    typedef ChildPointerSField                               Self;
                                   
    typedef PtrTypeT                                         value_type;
    typedef PtrTypeT const                                   const_value;
         
    typedef value_type                                       StoredType;
    
    typedef FieldTraits           <value_type,
                                   NamespaceI              > SFieldTraits;

    typedef FieldDescription      <SFieldTraits,
                                   FieldType::SingleField,
                                   RefCountPolicy,
                                   FieldType::ChildPtrField> Description;

    // handles
    typedef EditFCPtrSFieldHandle<Self                  > EditHandle;
    typedef boost::shared_ptr    <EditHandle            > EditHandlePtr;

    typedef GetFCPtrSFieldHandle <Self                  > GetHandle;
    typedef boost::shared_ptr    <GetHandle             > GetHandlePtr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
        
    static FieldType::Cardinality const fieldCard  = FieldType::SingleField;
    static FieldType::Class       const Class      = FieldType::ChildPtrField;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    ChildPointerSField(FieldContainer * const pParent,
                       UInt16                 usChildFieldId,
                       UInt16                 usParentFieldId); 

    ChildPointerSField(const_value            value,
                       FieldContainer * const pParent,
                       UInt16                 usChildFieldId,
                       UInt16                 usParentFieldId); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerSField(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    const_value getValue (      void               ) const;
    
    void        setValue (      const_value  value );
    void        setValue (const Self        &source);
    
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
   
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType _fieldType;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChildPointerSField(const Self &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const Self &source);
};

OSG_END_NAMESPACE

#include "OSGChildPointerSField.inl"

#endif // _OSGCHILDPOINTERSFIELD_H_
