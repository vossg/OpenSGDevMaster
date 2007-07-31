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

#ifndef _OSGFIELDCONTAINERSFIELDS_H_
#define _OSGFIELDCONTAINERSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGFieldContainerFieldTraits.h"

#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup  */

typedef SField<FieldContainerPtr> SFFieldContainerPtr;
#endif

#ifndef OSG_COMPILECONTAINERFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField,
//                          FieldContainerPtr,
//                          OSG_SYSTEM_DLLTMPLMAPPING)
#endif
#if 0
template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 SingleField                    >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;

template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 SingleField                    >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;
#endif

#ifdef OSG_MT_CPTR_ASPECT
template<> inline
void SField<FieldContainerPtr, 
            0                >::syncWith(SField<FieldContainerPtr, 0> &source)
{
    setValue(convertToCurrentAspect(source.getValue()));
}
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup  */

typedef SField<ParentFieldContainerPtr> SFParentFieldContainerPtr;

#endif

#ifndef OSG_COMPILECONTAINERFIELDINST
//OSG_FIELD_DLLEXPORT_DECL2(SField,
//                          ParentFieldContainerPtr,
//                          1,
//                          OSG_SYSTEM_DLLTMPLMAPPING)
#endif

template<>
class OSG_SYSTEM_DLLMAPPING EditSFieldHandle<SFFieldContainerPtr> : 
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

    FieldContainerPtr _pContainer;

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle     &source);
    EditSFieldHandle(      SFFieldContainerPtr  *pField, 
                     const FieldDescriptionBase *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void setValue(FieldContainerPtrConstArg rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source);
    virtual void shareValues         (      GetFieldHandlePtr  source);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;

};

template<>
class OSG_SYSTEM_DLLMAPPING GetSFieldHandle<SFFieldContainerPtr> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle      &source);
    GetSFieldHandle(const SFFieldContainerPtr  *pField, 
                    const FieldDescriptionBase *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    SFFieldContainerPtr const * operator ->(void);
    SFFieldContainerPtr const & operator * (void);
};


template<class FieldT>
class GetFCPtrSFieldHandle : public  GetSFieldHandle<SFFieldContainerPtr>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetSFieldHandle<SFFieldContainerPtr> Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    GetFCPtrSFieldHandle(const GetFCPtrSFieldHandle &source);
    GetFCPtrSFieldHandle(const FieldT               *pField, 
                         const FieldDescriptionBase *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

//    virtual bool equal(Ptr rhs);

    /*---------------------------------------------------------------------*/

    FieldT const * operator ->(void);
    FieldT const & operator * (void);
};

class Node;

template<class FieldT>
class EditFCPtrSFieldHandle : public EditSFieldHandle<SFFieldContainerPtr>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditSFieldHandle<SFFieldContainerPtr> Inherited;

    /*==========================  PUBLIC  =================================*/

    typedef boost::function<void (typename FieldT::ArgumentType)> SetMethod;

    SetMethod _fSetMethod;

  public:

    EditFCPtrSFieldHandle(const EditFCPtrSFieldHandle &source);
    EditFCPtrSFieldHandle(      FieldT                *pField, 
                          const FieldDescriptionBase  *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType(void) const;

    /*---------------------------------------------------------------------*/

    virtual void setValue(FieldContainerPtrConstArg rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void setSetMethod(SetMethod fMethod);

//    virtual bool equal(Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source);
    virtual void shareValues         (      GetFieldHandlePtr  source);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;
};

template<>
class OSG_SYSTEM_DLLMAPPING EditSFieldHandle<SFParentFieldContainerPtr> : 
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle           &source);
    EditSFieldHandle(      SFParentFieldContainerPtr  *pField, 
                     const FieldDescriptionBase       *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

//    virtual void setValue(ParentFieldContainerPtrConstArg rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source);
    virtual void shareValues         (      GetFieldHandlePtr  source);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;
};

template<>
class OSG_SYSTEM_DLLMAPPING GetSFieldHandle<SFParentFieldContainerPtr> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle            &source);
    GetSFieldHandle(const SFParentFieldContainerPtr  *pField, 
                    const FieldDescriptionBase       *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    SFParentFieldContainerPtr const * operator ->(void);
    SFParentFieldContainerPtr const & operator * (void);
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerSFields.inl"
#endif

#endif /* _OSGFIELDCONTAINERSFIELDS_H_ */
