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
/* ParentPointerSField<PtrTypeT,                                             */
/*                     NamespaceI  >                                         */
/*---------------------------------------------------------------------------*/

template <class    PtrTypeT,
          typename RefCountPolicy,
          Int32    NamespaceI  = 0>
class ParentPointerSField : 
    public PointerSFieldCommon<PointerAccessHandler<RefCountPolicy>, 
                               NamespaceI                          >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
        
    typedef PointerSFieldCommon<
                PointerAccessHandler<RefCountPolicy>, 
                NamespaceI                               > Inherited;

    typedef ParentPointerSField                            Self;
                                             
    typedef PtrTypeT                                       value_type;
    typedef PtrTypeT const                                 const_value;

    
    typedef FieldTraits        <UInt16                   > PosSFieldTraits;
    
    typedef FieldTraits        <value_type,
                                NamespaceI               > PtrSFieldTraits;
    typedef PtrSFieldTraits                                SFieldTraits;

    typedef FieldDescription   <PtrSFieldTraits,
                                FieldType::SingleField,
                                NoRefCountPolicy,
                                FieldType::ParentPtrField> Description;

    // handles
    typedef void                                          EditHandle;
    typedef boost::shared_ptr    <EditHandle            > EditHandlePtr;

    typedef GetFCPtrSFieldHandle <Self                  > GetHandle;
    typedef boost::shared_ptr    <GetHandle             > GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditParentPointerSFieldHandle<Self> DynamicEditHandle;
//    typedef typename EditParentPointerSFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetParentPointerSFieldHandle <Self>   DynamicGetHandle;
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

    static const FieldType &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    ParentPointerSField(const_value value,
                        UInt16      uiParentFieldPos = 0xFFFF);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~ParentPointerSField(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    const_value getValue         (void) const;
    UInt16      getParentFieldPos(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name IdStore Interface                                            */
    /*! \{                                                                 */

    void setValue(const_value  value,
                  UInt16       uiParentFieldPos);

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

#ifdef OSG_MT_CPTR_ASPECT
    void  syncWith(Self &source);
#endif
   
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    ParentPointerSField(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType _fieldType;
           UInt16    _uiParentFieldPos;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template<class    DescT, 
             enum     FieldType::Cardinality eFieldCard, 
             typename RefCountPolicyT,                    
             enum     FieldType::Class       eFieldClass>
    friend class FieldDescription;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ParentPointerSField(const ParentPointerSField &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ParentPointerSField &rhs);
};

OSG_END_NAMESPACE

#include "OSGParentPointerSField.inl"

#endif // _OSGPARENTPOINTERSFIELD_H_
