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

#if 0
    _mfParents.push_back(parent);
    _mfParents.back().setParentFieldPos(uiStoredInFieldId);
#endif

    _mfParents.push_back(parent, uiStoredInFieldId);
}

inline
void NodeCore::subParent(FieldContainerPtrConst &parent)
{
    Int32 iParentIdx = _mfParents.findIndex(parent);

    if(iParentIdx != -1)
    {
        editMField(ParentsFieldMask, _mfParents);

#if 0
        MFParentFieldContainerPtr::iterator parentIt = _mfParents.begin();

        parentIt += iParentIdx;

        _mfParents.erase(parentIt);
#endif

        _mfParents.erase(iParentIdx);
    }
}

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
