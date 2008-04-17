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

#ifndef _OSGFIELDHANDLE_H_
#define _OSGFIELDHANDLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGField.h"
#include "OSGFieldDescriptionBase.h"
#include "OSGLog.h"

#include "boost/shared_ptr.hpp"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! FieldDescriptionBase point less than
    \ingroup GrpSystemFieldContainerFuncs
    \hideinhierarchy
 */

class OSG_SYSTEM_DLLMAPPING FieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:

    void operator =(const FieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    const FieldDescriptionBase *_pDescription;

    /*---------------------------------------------------------------------*/

    typedef std::vector<const ReflexiveContainerType *> TypePtrVector;
    typedef std::vector<      UInt16                  > TypeIdVector;

    /*==========================  PUBLIC  =================================*/

  public:

    FieldHandle(const FieldHandle          &source);

    FieldHandle(const FieldDescriptionBase *pDescription);

    virtual ~FieldHandle(void);

    /*---------------------------------------------------------------------*/

    bool                    isInternal    (void) const;

    FieldType::Cardinality  getCardinality(void) const;

    std::string             getName       (void) const;

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const = 0;

    virtual       bool       isPointerField(void) const = 0;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const = 0;
    virtual void pushSizeToStream (OutStream &str) const = 0;
};


class EditFieldHandle;

class OSG_SYSTEM_DLLMAPPING GetFieldHandle : public FieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const GetFieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class EditFieldHandle;

    typedef FieldHandle Inherited;

    /*---------------------------------------------------------------------*/

    const Field *_pField;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetFieldHandle > Ptr;

    /*---------------------------------------------------------------------*/

    GetFieldHandle(const GetFieldHandle      &source);
    GetFieldHandle(const Field                *pField, 
                   const FieldDescriptionBase *pDescription);


    virtual ~GetFieldHandle(void);

    /*---------------------------------------------------------------------*/

    bool isValid(void) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Ptr rhs) const = 0;

    bool operator ==(const EditFieldHandle &rhs);
    bool operator ==(const GetFieldHandle  &rhs);
};

typedef boost::shared_ptr<GetFieldHandle > GetFieldHandlePtr;




class OSG_SYSTEM_DLLMAPPING EditFieldHandle : public FieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const EditFieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class GetFieldHandle;

    typedef FieldHandle Inherited;

    /*---------------------------------------------------------------------*/

    Field *_pField;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditFieldHandle(const EditFieldHandle      &source);
    EditFieldHandle(      Field                *pField, 
                    const FieldDescriptionBase *pDescription);


    virtual ~EditFieldHandle(void);

    /*---------------------------------------------------------------------*/

    bool isValid(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueFromCString(const Char8             *str   ) = 0;

    virtual void copyValues          (      GetFieldHandlePtr  source) const= 0;
    virtual void shareValues         (      GetFieldHandlePtr  source) const= 0;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Ptr rhs) const = 0;

    bool operator ==(const EditFieldHandle &rhs);
    bool operator ==(const GetFieldHandle  &rhs);

    /*---------------------------------------------------------------------*/

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const = 0;
};

typedef boost::shared_ptr<EditFieldHandle> EditFieldHandlePtr;



template<class FieldT>
class EditSFieldHandle : public EditFieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const EditSFieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle     &source);
    EditSFieldHandle(      FieldT               *pField, 
                     const FieldDescriptionBase *pDescription);


    virtual ~EditSFieldHandle(void);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

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

    /*---------------------------------------------------------------------*/

    FieldT *getField(void);

    /*---------------------------------------------------------------------*/

    FieldT * operator ->(void);
    FieldT & operator * (void);
};



template<class FieldT>
class EditMFieldHandle : public EditFieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const EditMFieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

    typedef EditFieldHandle Inherited;

  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditMFieldHandle(const EditMFieldHandle     &source);
    EditMFieldHandle(      FieldT               *pField, 
                     const FieldDescriptionBase *pDescription);


    virtual ~EditMFieldHandle(void);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

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

    /*---------------------------------------------------------------------*/

    FieldT *getField(void);

    /*---------------------------------------------------------------------*/

    FieldT * operator ->(void);
    FieldT & operator * (void);
};

template<class FieldT>
class GetSFieldHandle : public GetFieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const GetSFieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle      &source);
    GetSFieldHandle(const FieldT               *pField, 
                    const FieldDescriptionBase *pDescription);

    virtual ~GetSFieldHandle(void);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    FieldT const *getField(void);

    /*---------------------------------------------------------------------*/

    FieldT const * operator ->(void);
    FieldT const & operator * (void);
};

template<class FieldT>
class GetMFieldHandle : public GetFieldHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const GetMFieldHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetMFieldHandle(const GetMFieldHandle      &source);
    GetMFieldHandle(const FieldT               *pField, 
                    const FieldDescriptionBase *pDescription);


    virtual ~GetMFieldHandle(void);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    FieldT const *getField(void);

    /*---------------------------------------------------------------------*/

    FieldT const * operator ->(void);
    FieldT const & operator * (void);
};


template<class FieldT>
class EditFCPtrSFieldHandle;

template<class FieldT>
class EditFCPtrMFieldHandle;

template<class FieldT>
class GetFCPtrSFieldHandle;

template<class FieldT>
class GetFCPtrMFieldHandle;



OSG_END_NAMESPACE

#include "OSGFieldHandle.inl"

#endif /* _OSGFIELDHANDLE_H_ */
