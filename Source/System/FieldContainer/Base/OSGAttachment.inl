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

OSG_ABSTR_FIELD_CONTAINER_INL_DEF(Attachment)

inline
SFBool &Attachment::editInternal(void)
{
    Inherited::editSField(InternalFieldMask);

    return _sfInternal;
}

inline
const SFBool &Attachment::getInternal(void) const
{
    return _sfInternal;
}

inline
SFBool *Attachment::editSFInternal(void)
{
    Inherited::editSField(InternalFieldMask);

    return &_sfInternal;
}

inline
const SFBool *Attachment::getSFInternal(void) const
{
    return &_sfInternal;
}

inline
const MFParentFieldContainerPtr &Attachment::getParents(void) const
{
    return _mfParents;
}

inline
const MFParentFieldContainerPtr *Attachment::getMFParents(void) const
{
    return &_mfParents;
}

inline
void Attachment::setInternal(bool bVal)
{
    Inherited::editSField(InternalFieldMask);

    _sfInternal.setValue(bVal);
}

inline
FieldContainer *Attachment::getParent(UInt32 uiIdx) const
{
    if(uiIdx < _mfParents.size())
    {
        return _mfParents[uiIdx];
    }
    else
    {
        return NULL;
    }
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void Attachment::execSync (      
          Attachment        *pFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.syncWith(pFrom->_sfInternal);
    }

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.syncWith(pFrom->_mfParents, 
                            syncMode, 
                            uiSyncInfo,
                            oOffsets);
    }
}
#endif

OSG_END_NAMESPACE

