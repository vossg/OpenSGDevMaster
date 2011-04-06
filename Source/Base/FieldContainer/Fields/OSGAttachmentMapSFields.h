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

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef SField<AttachmentMap> SFAttachmentPtrMap;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFAttachmentPtrMap : public SField<AttachmentMap> {};

#endif // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template<>
class OSG_BASE_DLLMAPPING GetSFieldHandle<SFAttachmentPtrMap> : 
    public GetMapFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetMapFieldHandle Inherited;
    typedef GetFieldHandle    Base;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetSFieldHandle(const GetSFieldHandle       &source);
    GetSFieldHandle(const SFAttachmentPtrMap    *pField, 
                    const FieldDescriptionBase  *pDescription,
                          FieldContainer        *pContainer  );

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void traverse(TraverseCallback oCallBack);

    /*---------------------------------------------------------------------*/

    virtual bool empty  (void                );
    virtual void flatten(MapList       &vList);
    virtual void flatten(ContainerList &vList);

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

    virtual bool equal(Base::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    SFAttachmentPtrMap const * operator ->(void);
    SFAttachmentPtrMap const & operator * (void);
};

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template<>
class OSG_BASE_DLLMAPPING 
    EditSFieldHandle<SFAttachmentPtrMap> : public EditMapFieldHandle
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditMapFieldHandle Inherited;
    typedef EditFieldHandle    Base;

    typedef boost::function<void(Attachment * const,
                                 UInt32            )> AddMethod;
    
    typedef boost::function<void(Attachment * const,
                                 Attachment * const)> ReplaceMethod;
    
    /*==========================  PUBLIC  =================================*/

    FieldContainer *_pContainer;
    AddMethod       _fAddMethod;
    ReplaceMethod   _fReplaceMethod;

  public:

    typedef boost::shared_ptr<EditSFieldHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditSFieldHandle(const EditSFieldHandle     &source      );
    EditSFieldHandle(      SFAttachmentPtrMap   *pField, 
                     const FieldDescriptionBase *pDescription,
                           FieldContainer       *pContainer  );

    /*---------------------------------------------------------------------*/

    virtual const FieldType &getType       (void) const;
    virtual       bool       isPointerField(void) const;

    /*---------------------------------------------------------------------*/

    virtual void add         (      FieldContainer *       rhs,
                              const std::string    &       szBindings);

    virtual void replaceByObj(      Attachment     * const pOld,
                                    Attachment     * const pNew      );

    /*---------------------------------------------------------------------*/

    virtual void traverse(TraverseCallback oCallBack);

    /*---------------------------------------------------------------------*/

    virtual bool empty  (void                );
    virtual void flatten(MapList       &vList);
    virtual void flatten(ContainerList &vList);

    /*---------------------------------------------------------------------*/

    virtual bool loadFromBin(      BinaryDataHandler        *pMem,
                                   UInt32                    uiNumElements,
                                   bool                      hasBindingInfo,
                                   std::vector<UInt16>      &vBindings,
                                   std::vector<UInt32>      &vIds          );

    virtual void fillFrom   (const std::vector<UInt16>      &vBindings,
                             const std::vector<UInt32>      &vIds,
                             const std::map<UInt32, UInt32> &vIdMap        );

    /*---------------------------------------------------------------------*/

    virtual void pushValueToStream(OutStream &str) const;
    virtual void pushSizeToStream (OutStream &str) const;

    /*---------------------------------------------------------------------*/

            void setAddMethod    (AddMethod     fMethod);
            void setReplaceMethod(ReplaceMethod fMethod);

    virtual bool equal           (Base::Ptr     rhs    ) const;

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

#include "OSGAttachmentMapSFields.inl"

#endif /* _OSGATTACHMENTMAPSFIELDS_H_ */
