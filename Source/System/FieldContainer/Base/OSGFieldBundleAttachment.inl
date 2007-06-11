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


inline
SFBool &FieldBundleAttachment::editInternal(void)
{
    Inherited::editSField(InternalFieldMask);

    return _sfInternal;
}

inline
const SFBool &FieldBundleAttachment::getInternal(void) const
{
    return _sfInternal;
}

inline
SFBool *FieldBundleAttachment::editSFInternal(void)
{
    Inherited::editSField(InternalFieldMask);

    return &_sfInternal;
}

inline
const SFBool *FieldBundleAttachment::getSFInternal(void) const
{
    return &_sfInternal;
}

inline
const MFParentFieldBundleP &FieldBundleAttachment::getParents(void) const
{
    return _mfParents;
}

inline
const MFParentFieldBundleP *FieldBundleAttachment::getMFParents(void) const
{
    return &_mfParents;
}

inline
void FieldBundleAttachment::setInternal(bool bVal)
{
    Inherited::editSField(InternalFieldMask);

    _sfInternal.setValue(bVal);
}

inline
void FieldBundleAttachment::addParent(
          FieldBundlePConst parent,
    const UInt16            uiStoredInFieldId)
{
    Inherited::editMField(ParentsFieldMask, _mfParents);

    _mfParents.push_back(parent);
    _mfParents.back().setParentFieldPos(uiStoredInFieldId);
}

inline
void FieldBundleAttachment::subParent(FieldBundlePConst parent)
{
    Int32 iParentIdx = _mfParents.findIndex(parent);

    if(iParentIdx != -1)
    {
        Inherited::editMField(ParentsFieldMask, _mfParents);

        MFParentFieldBundleP::iterator parentIt = _mfParents.begin();

        parentIt += iParentIdx;

        _mfParents.erase(parentIt);
    }
}

OSG_END_NAMESPACE
