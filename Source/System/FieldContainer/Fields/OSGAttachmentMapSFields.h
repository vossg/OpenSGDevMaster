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

#ifndef _OSGATTACHMENTMAPSFIELDS_H_
#define _OSGATTACHMENTMAPSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGAttachmentMapFieldTraits.h"
#include "OSGTypeBasePredicates.h"
#include "OSGReflexiveContainerTypePredicates.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<FieldContainerAttachmentMap> SFFieldContainerAttachmentPtrMap;
#endif

template<>
class OSG_SYSTEM_DLLMAPPING GetSFieldHandle<SFFieldContainerAttachmentPtrMap> : 
    public GetFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetFieldHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle                  &source);
    GetSFieldHandle(const SFFieldContainerAttachmentPtrMap *pField, 
                    const FieldDescriptionBase             *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs);

    /*---------------------------------------------------------------------*/

    SFFieldContainerAttachmentPtrMap const * operator ->(void);
    SFFieldContainerAttachmentPtrMap const & operator * (void);
};

template<>
class OSG_SYSTEM_DLLMAPPING 
    EditSFieldHandle<SFFieldContainerAttachmentPtrMap> : public EditFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditFieldHandle Inherited;

    typedef boost::function<void(FieldContainerAttachmentPtrConstArg,
                                 UInt32                           )> AddMethod;

    /*==========================  PUBLIC  =================================*/

    FieldContainerPtr _pContainer;
    AddMethod         _fAddMethod;

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle                 &source      );
    EditSFieldHandle(      SFFieldContainerAttachmentPtrMap *pField, 
                     const FieldDescriptionBase             *pDescription);

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void add(FieldContainerPtrConstArg rhs,
                     UInt32                    uiBindings);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    void         setAddMethod(AddMethod      fMethod);

    virtual bool equal       (Inherited::Ptr rhs    );

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

#if 0
template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<SFFieldContainerAttachmentPtrMap::SFieldTraits,
                 SingleField                                    >::cloneValues(
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
FieldDescription<SFFieldContainerAttachmentPtrMap::SFieldTraits,
                 SingleField                                    >::shareValues(
        const Field                                  *pSrc,
        const UInt32                                  fieldId,
              FieldContainerPtrConstArg               pDst,
        const std::vector<const FieldContainerType*> &cloneTypes,
        const std::vector<const FieldContainerType*> &ignoreTypes,
        const std::vector<UInt16>                    &cloneGroupIds,
        const std::vector<UInt16>                    &ignoreGroupIds) const;
#endif

OSG_END_NAMESPACE

#ifndef OSG_COMPILEATTACHMENTMAPFIELDINST
#include "OSGAttachmentMapSFields.inl"
#endif

#endif /* _OSGATTACHMENTMAPSFIELDS_H_ */
