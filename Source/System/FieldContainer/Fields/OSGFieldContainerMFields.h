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

#ifndef _OSGFIELDCONTAINERMFIELDS_H_
#define _OSGFIELDCONTAINERMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGFieldContainerFieldTraits.h"

#include "OSGFieldContainerPtrMField.h"
#include "OSGFieldContainerPtrParentMField.h"

#include "OSGFieldContainerMFieldHandle.h"  

OSG_BEGIN_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup  */

typedef FieldContainerPtrMField<FieldContainerPtr> MFFieldContainerPtr;
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup  */

typedef 
    FieldContainerPtrParentMField<FieldContainerPtr, 
                                  NoRefCounts,
                                  1                > MFParentFieldContainerPtr;
#endif




template<>
class OSG_SYSTEM_DLLMAPPING EditMFieldHandle<MFParentFieldContainerPtr> :
    public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditMFieldHandle(const EditMFieldHandle          &source);
    EditMFieldHandle(      MFParentFieldContainerPtr *pField, 
                     const FieldDescriptionBase      *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

/*
    virtual void replace(const UInt32                    uiIndex,
                               FieldContainerPtrConstArg pNewElement);
 */

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
class OSG_SYSTEM_DLLMAPPING GetMFieldHandle<MFParentFieldContainerPtr> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetMFieldHandle(const GetMFieldHandle           &source);
    GetMFieldHandle(const MFParentFieldContainerPtr *pField, 
                    const FieldDescriptionBase      *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    MFParentFieldContainerPtr const * operator ->(void);
    MFParentFieldContainerPtr const & operator * (void);
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerMFields.inl"
#endif

#endif /* _OSGFIELDCONTAINERMFIELDS_H_ */
