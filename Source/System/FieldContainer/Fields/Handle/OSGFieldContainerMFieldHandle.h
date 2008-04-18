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

#ifndef _OSGFIELDCONTAINERMFIELDHANDLE_H_
#define _OSGFIELDCONTAINERMFIELDHANDLE_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

template<>
class OSG_SYSTEM_DLLMAPPING EditMFieldHandle<FieldContainerPtrMFieldBase> :
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    typedef boost::function<void(const FieldContainerPtr)> AddMethod;

    AddMethod _fAddMethod;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditMFieldHandle(const EditMFieldHandle            &source);
    EditMFieldHandle(      FieldContainerPtrMFieldBase *pField, 
                     const FieldDescriptionBase        *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void add    (const FieldContainerPtr pNewElement);
    virtual void replace(const UInt32            uiIndex,
                         const FieldContainerPtr pNewElement);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void setAddMethod(AddMethod fMethod);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source) const;
    virtual void shareValues         (      GetFieldHandlePtr  source) const;

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;

};

template<>
class OSG_SYSTEM_DLLMAPPING GetMFieldHandle<FieldContainerPtrMFieldBase> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetMFieldHandle(const GetMFieldHandle             &source);
    GetMFieldHandle(const FieldContainerPtrMFieldBase *pField, 
                    const FieldDescriptionBase        *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    FieldContainerPtrMFieldBase const * operator ->(void);
    FieldContainerPtrMFieldBase const & operator * (void);
};




template<class FieldT>
class GetFCPtrMFieldHandle : public GetMFieldHandle<FieldContainerPtrMFieldBase>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetMFieldHandle<FieldContainerPtrMFieldBase> Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    GetFCPtrMFieldHandle(const GetFCPtrMFieldHandle &source);
    GetFCPtrMFieldHandle(const FieldT               *pField, 
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

template<class FieldT>
class EditFCPtrMFieldHandle : 
    public EditMFieldHandle<FieldContainerPtrMFieldBase>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditMFieldHandle<FieldContainerPtrMFieldBase> Inherited;


    typedef boost::function<void (typename FieldT::const_value)> AddMethod;

    AddMethod _fAddMethod;

    /*==========================  PUBLIC  =================================*/

  public:

    EditFCPtrMFieldHandle(const EditFCPtrMFieldHandle &source);
    EditFCPtrMFieldHandle(      FieldT                *pField, 
                          const FieldDescriptionBase  *pDescription);

    /*---------------------------------------------------------------------*/

    virtual void add    (const FieldContainerPtr pNewElement);
    virtual void replace(const UInt32            uiIndex,
                         const FieldContainerPtr pNewElement);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void setAddMethod(AddMethod fMethod);

//    virtual bool equal(Ptr rhs);

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   );

    virtual void copyValues          (      GetFieldHandlePtr  source) const;
    virtual void shareValues         (      GetFieldHandlePtr  source) const;

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;
};

OSG_END_NAMESPACE

#include "OSGFieldContainerMFieldHandle.inl"

#endif /* _OSGFIELDCONTAINERMFIELDHANDLE_H_ */
