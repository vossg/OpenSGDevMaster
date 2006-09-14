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
void NodeCore::addParent(      FieldContainerPtrConst &parent,
                         const UInt16                  uiStoredInFieldId)
{
    editMField(ParentsFieldMask, _mfParents);

    _mfParents.push_back(parent);
    _mfParents.back().setParentFieldPos(uiStoredInFieldId);
}

inline
void NodeCore::subParent(FieldContainerPtrConst &parent)
{
    Int32 iParentIdx = _mfParents.findIndex(parent);

    if(iParentIdx != -1)
    {
        editMField(ParentsFieldMask, _mfParents);

        MFParentFieldContainerPtr::iterator parentIt = _mfParents.begin();

        parentIt += iParentIdx;

        _mfParents.erase(parentIt);
    }
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void NodeCore::execSync(      NodeCore          *pFrom,
                              ConstFieldMaskArg  whichField,
                              ConstFieldMaskArg  syncMode  ,
                        const UInt32             uiSyncInfo,
                              UInt32             uiCopyOffset)
{
    Inherited::execSync(pFrom, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.syncWith(pFrom->_mfParents, 
                            syncMode, 
                            uiSyncInfo, 
                            uiCopyOffset);
    }
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void NodeCore::execSync (      NodeCore          *pFrom,
                               ConstFieldMaskArg  whichField,
                               AspectOffsetStore &oOffsets,
                               ConstFieldMaskArg  syncMode  ,
                         const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.syncWith(pFrom->_mfParents, 
                            syncMode, 
                            uiSyncInfo, 
                            oOffsets);
    }
}
#endif

#if 0
inline
void NodeCore::execBeginEdit(ConstFieldMaskArg whichField, 
                             UInt32            uiAspect,
                             UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.beginEdit(uiAspect, uiContainerSize);
    }
}
#endif

inline
void NodeCore::resolveLinks(void)
{
    Inherited::resolveLinks();
}

inline
Char8 *NodeCore::getClassname(void)
{
    return "NodeCore";
}

OSG_ABSTR_FIELD_CONTAINER_INL_DEF(NodeCore)

OSG_END_NAMESPACE

#define OSGNODECORE_INLINE_CVSID "@(#)$Id$"

