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

OSG_BEGIN_NAMESPACE

template <class ParentT> inline
void AttachmentMixin<ParentT>::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);

    FieldDescriptionBase *pDesc;

    typedef typename ParentField::Description SFDesc;

	pDesc = new SFDesc(
        ParentField::getClassType(),
        "parents",
        OSG_RC_FIELD_DESC(Self::Parents),
        true,
        Field::MFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&Self::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&Self::getMFParents),
        NULL);

    oType.addInitialDesc(pDesc);


	pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "internal",
        OSG_RC_FIELD_DESC(Self::Internal),
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&Self::editSFInternal),
        reinterpret_cast<FieldGetMethodSig >(&Self::getSFInternal),
        NULL);
 
    oType.addInitialDesc(pDesc);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
AttachmentMixin<ParentT>::AttachmentMixin(void) :
     Inherited (     ),
    _mfParents (     ),
    _sfInternal(false)
{
}

template <class ParentT> inline
AttachmentMixin<ParentT>::AttachmentMixin(
    const AttachmentMixin &source) :
    
     Inherited(source             ),
    _mfParents(source._mfParents  ),
    _sfInternal(source._sfInternal)
{
}

template <class ParentT> inline
AttachmentMixin<ParentT>::~AttachmentMixin(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ParentT> inline
SFBool &AttachmentMixin<ParentT>::editInternal(void)
{
    Self::editSField(Self::InternalFieldMask);

    return _sfInternal;
}

template <class ParentT> inline
const SFBool &AttachmentMixin<ParentT>::getInternal(void) const
{
    return _sfInternal;
}

template <class ParentT> inline
SFBool *AttachmentMixin<ParentT>::editSFInternal(void)
{
    Self::editSField(Self::InternalFieldMask);

    return &_sfInternal;
}

template <class ParentT> inline
const SFBool *AttachmentMixin<ParentT>::getSFInternal(void) const
{
    return &_sfInternal;
}

template <class ParentT> inline
const typename AttachmentMixin<ParentT>::ParentField &
    AttachmentMixin<ParentT>::getParents(void) const
{
    return _mfParents;
}

template <class ParentT> inline
const typename AttachmentMixin<ParentT>::ParentField *
    AttachmentMixin<ParentT>::getMFParents(void) const
{
    return &_mfParents;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ParentT> inline
void AttachmentMixin<ParentT>::setInternal(bool bVal)
{
    Self::editSField(Self::InternalFieldMask);

    _sfInternal.setValue(bVal);
}

template <class ParentT> inline
void AttachmentMixin<ParentT>::addParent(
          ParentPtrConst &parent,
    const UInt16          uiStoredInFieldId)
{
    Self::editMField(Self::ParentsFieldMask, _mfParents);

    _mfParents.push_back(parent);
    _mfParents.back().setParentFieldPos(uiStoredInFieldId);
}

template <class ParentT> inline
void AttachmentMixin<ParentT>::subParent(ParentPtrConst &parent)
{
    Int32 iParentIdx = _mfParents.findIndex(parent);

    if(iParentIdx != -1)
    {
        Self::editMField(Self::ParentsFieldMask, _mfParents);

        ParentFieldIt parentIt = _mfParents.begin();

        parentIt += iParentIdx;

        _mfParents.erase(parentIt);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

#define OSGATTACHMENTMIXIN_INLINE_CVSID "@(#)$Id: $"

