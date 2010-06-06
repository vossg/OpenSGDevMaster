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
#include <boost/type_traits.hpp>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/* GetMFieldHandle<FieldContainerPtrMFieldBase>                              */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template<>
class OSG_BASE_DLLMAPPING GetMFieldHandle<FieldContainerPtrMFieldBase> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    GetMFieldHandle(const GetMFieldHandle             &source);
    GetMFieldHandle(const FieldContainerPtrMFieldBase *pField, 
                    const FieldDescriptionBase        *pDescription,
                          FieldContainer              *pContainer  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Field Type Query                                             */
    /*! \{                                                                 */

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Stream/String IO                                             */
    /*! \{                                                                 */

    virtual void pushValueToStream       (OutStream &str  ) const;
    virtual void pushIndexedValueToStream(OutStream &str, 
                                          UInt32     index) const;
    virtual void pushSizeToStream        (OutStream &str  ) const;
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Comparison                                                   */
    /*! \{                                                                 */

    virtual bool equal(Inherited::Ptr rhs) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    virtual FieldContainer *get    (UInt32          index     ) const = 0;
    virtual Int32           find   (FieldContainer *existingFC) const = 0;

    const FieldContainerPtrMFieldBase *getField   (void);
    
    const FieldContainerPtrMFieldBase *operator ->(void);
    const FieldContainerPtrMFieldBase &operator * (void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};


/*---------------------------------------------------------------------------*/
/* EditMFieldHandle<FieldContainerPtrMFieldBase>                             */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template<>
class OSG_BASE_DLLMAPPING EditMFieldHandle<FieldContainerPtrMFieldBase> :
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle                                Inherited;

    typedef GetMFieldHandle<FieldContainerPtrMFieldBase>   GetMFHandle;
    typedef boost::shared_ptr<GetMFHandle>                 GetMFHandlePtr;
    
    bool    _bStoreless;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
  
    typedef boost::shared_ptr<EditMFieldHandle> Ptr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    EditMFieldHandle(const EditMFieldHandle            &source);
    EditMFieldHandle(      FieldContainerPtrMFieldBase *pField, 
                     const FieldDescriptionBase        *pDescription,
                           FieldContainer              *pContainer  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Field Type Query                                             */
    /*! \{                                                                 */

    virtual bool isValid(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Field Type Query                                             */
    /*! \{                                                                 */

    void setStoreless(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Field Type Query                                             */
    /*! \{                                                                 */

    virtual const FieldType &getType              (void) const;
    virtual       bool       isPointerField       (void) const;

    virtual       bool       supportsAdd          (void) const = 0;
    virtual       bool       supportsRemove       (void) const = 0;
    virtual       bool       supportsRemoveObject (void) const = 0;
    virtual       bool       supportsInsert       (void) const = 0;
    virtual       bool       supportsReplace      (void) const = 0;
    virtual       bool       supportsReplaceObject(void) const = 0;
    virtual       bool       supportsClear        (void) const = 0;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual FieldContainer *get (UInt32          index     ) const = 0;
    virtual Int32           find(FieldContainer *existingFC) const = 0;
    
    virtual bool add          (FieldContainer *newFC      ) const = 0;
    virtual bool remove       (UInt32          index      ) const = 0;
    virtual bool removeObject (FieldContainer *existingFC ) const = 0;
    virtual bool insert       (UInt32          index,
                               FieldContainer *newFC      ) const = 0;
    virtual bool replace      (UInt32          index,
                               FieldContainer *newFC      ) const = 0;
    virtual bool replaceObject(FieldContainer *existingFC,
                               FieldContainer *newFC      ) const = 0;
    virtual bool clear        (void                       ) const = 0;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Stream/String IO                                             */
    /*! \{                                                                 */

    virtual void pushValueToStream          (      OutStream &str  ) const;
    virtual void pushIndexedValueToStream   (      OutStream &str, 
                                                   UInt32     index) const;
    virtual void pushSizeToStream           (      OutStream &str  ) const;
    
    virtual void pushValueFromCString       (const Char8     *str  );
    virtual void pushIndexedValueFromCString(const Char8     *str  , 
                                                   UInt32     index);
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Comparison                                                   */
    /*! \{                                                                 */

    virtual bool equal(Inherited::Ptr rhs) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Copy/Share/Clone                                             */
    /*! \{                                                                 */
    
    virtual void copyValues (GetFieldHandlePtr source) const;
    virtual void shareValues(GetFieldHandlePtr source) const;

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};


/*---------------------------------------------------------------------------*/
/* GetFCPtrMFieldHandle<FieldT>                                              */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template <class FieldT>
class GetFCPtrMFieldHandle : public GetMFieldHandle<FieldContainerPtrMFieldBase>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef FieldT                                       HandledField;
    typedef GetMFieldHandle<FieldContainerPtrMFieldBase> Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    GetFCPtrMFieldHandle(const GetFCPtrMFieldHandle &source);
    GetFCPtrMFieldHandle(const FieldT               *pField, 
                         const FieldDescriptionBase *pDescription,
                               FieldContainer       *pContainer  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Field Type Query                                             */
    /*! \{                                                                 */

    virtual const FieldType &getType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Stream/String IO                                             */
    /*! \{                                                                 */

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual FieldContainer *get (UInt32          index     ) const;
    virtual UInt32          size(void                      ) const;
    virtual Int32           find(FieldContainer *existingFC) const;
    
    const FieldT *getField   (void);
    
    const FieldT *operator ->(void);
    const FieldT &operator * (void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    const HandledField *dcast_const(void) const;
};


/*---------------------------------------------------------------------------*/
/* EditFCPtrMFieldHandle<FieldT>                                             */
/*---------------------------------------------------------------------------*/

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template <class FieldT>
class EditFCPtrMFieldHandle : 
    public EditMFieldHandle<FieldContainerPtrMFieldBase>
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Protected Types                                              */
    /*! \{                                                                 */

    typedef FieldT                                              HandledField;
    typedef EditMFieldHandle<FieldContainerPtrMFieldBase>       Inherited;
    typedef EditFCPtrMFieldHandle                               Self;

    typedef typename FieldT::value_type                         StoredPtrType;

    typedef typename boost::remove_pointer<StoredPtrType>::type StoredType;

    typedef          RefCountPtr<StoredType,
                                 UnrecordedRefCountPolicy>      StoredUnrecPtr;


    typedef 
        boost::function<void (typename FieldT::const_value)>   AddMethod;
    typedef 
        boost::function<void (UInt32)                      >   RemoveMethod;
    typedef 
        boost::function<void (typename FieldT::const_value)>   RemoveObjMethod;
    typedef 
        boost::function<void (UInt32,
                              typename FieldT::const_value)>   InsertMethod;
    typedef 
        boost::function<void (UInt32,
                              typename FieldT::const_value)>   ReplaceMethod;
    typedef 
        boost::function<void (typename FieldT::const_value, 
                              typename FieldT::const_value)>   ReplaceObjMethod;
    typedef 
        boost::function<void (void)                        >   ClearMethod;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Member                                                       */
    /*! \{                                                                 */
    
    AddMethod        _fAddMethod;
    RemoveMethod     _fRemoveMethod;
    RemoveObjMethod  _fRemoveObjMethod;
    InsertMethod     _fInsertMethod;
    ReplaceMethod    _fReplaceMethod;
    ReplaceObjMethod _fReplaceObjMethod;
    ClearMethod      _fClearMethod;

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    EditFCPtrMFieldHandle(const EditFCPtrMFieldHandle &source);
    EditFCPtrMFieldHandle(      FieldT                *pField, 
                          const FieldDescriptionBase  *pDescription,
                                FieldContainer        *pContainer  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Field Type Query                                             */
    /*! \{                                                                 */
                          
    virtual const FieldType &getType              (void) const;
                          
    virtual       bool       supportsAdd          (void) const;
    virtual       bool       supportsRemove       (void) const;
    virtual       bool       supportsRemoveObject (void) const;
    virtual       bool       supportsInsert       (void) const;
    virtual       bool       supportsReplace      (void) const;
    virtual       bool       supportsReplaceObject(void) const;
    virtual       bool       supportsClear        (void) const;
                          
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual FieldContainer *get (UInt32          index     ) const;
    virtual UInt32          size(void                      ) const;
    virtual Int32           find(FieldContainer *existingFC) const;
    
    virtual bool add          (FieldContainer *newFC      ) const;
    virtual bool remove       (UInt32          index      ) const;
    virtual bool removeObject (FieldContainer *existingFC ) const;
    virtual bool insert       (UInt32          index,
                               FieldContainer *newFC      ) const;
    virtual bool replace      (UInt32          index,
                               FieldContainer *newFC      ) const;
    virtual bool replaceObject(FieldContainer *existingFC,
                               FieldContainer *newFC      ) const;
    virtual bool clear        (void                       ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Stream/String IO                                             */
    /*! \{                                                                 */

    virtual void pushValueToStream   (      OutStream &str) const;
    virtual void pushSizeToStream    (      OutStream &str) const;

    virtual void pushValueFromCString(const Char8     *str);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Callback Setup                                               */
    /*! \{                                                                 */

    void setAddMethod       (AddMethod        fMethod);
    void setRemoveMethod    (RemoveMethod     fMethod);
    void setRemoveObjMethod (RemoveObjMethod  fMethod);
    void setInsertMethod    (InsertMethod     fMethod);
    void setReplaceMethod   (ReplaceMethod    fMethod);
    void setReplaceObjMethod(ReplaceObjMethod fMethod);
    void setClearMethod     (ClearMethod      fMethod);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Copy/Share/Clone                                             */
    /*! \{                                                                 */

    virtual void copyValues (GetFieldHandlePtr  source) const;
    virtual void shareValues(GetFieldHandlePtr  source) const;

    virtual void cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes     = TypePtrVector(),
        const TypePtrVector     &ignoreTypes    = TypePtrVector(),
        const TypeIdVector      &shareGroupIds  = TypeIdVector (),
        const TypeIdVector      &ignoreGroupIds = TypeIdVector ()) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
          HandledField *dcast      (void) const;
    const HandledField *dcast_const(void) const;
};

OSG_END_NAMESPACE

#include "OSGFieldContainerMFieldHandle.inl"

#endif /* _OSGFIELDCONTAINERMFIELDHANDLE_H_ */
