/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGIntersectKDTreeNodeFields.h"

#include "OSGExportDefines.h"
#include "OSGFieldContainer.h"
#include "OSGMField.ins"
#include "OSGSField.ins"

OSG_BEGIN_NAMESPACE

DataType FieldTraits<IntersectKDTreeNode>::_type("IntersectKDTreeNode", NULL);

OSG_FIELD_DLLEXPORT_DEF1(SField, IntersectKDTreeNode);
OSG_FIELD_DLLEXPORT_DEF1(MField, IntersectKDTreeNode);

OSG_FIELDTRAITS_GETTYPE(IntersectKDTreeNode);

/* static */ const Char8 *
FieldTraits<IntersectKDTreeNode>::getSName(void)
{
    return "SFIntersectKDTreeNode";
}

/* static */ const Char8 *
FieldTraits<IntersectKDTreeNode>::getMName(void)
{
    return "MFIntersectKDTreeNode";
}

/* static */ UInt32
FieldTraits<IntersectKDTreeNode>::getBinSize(const IntersectKDTreeNode &)
{
    return 2 * sizeof(UInt32);
}

/* static */ UInt32
FieldTraits<IntersectKDTreeNode>::getBinSize(
    const IntersectKDTreeNode *pObjectStore,
          UInt32               uiNumObjects)
{
    return uiNumObjects * 2 * sizeof(UInt32);
}

/* static */ void
FieldTraits<IntersectKDTreeNode>::copyToBin(
          BinaryDataHandler   &pMem,
    const IntersectKDTreeNode &oObject)
{
    if(oObject.isLeaf())
    {
        UInt32 count = oObject.getTriCount() << 2;
        count |= IntersectKDTreeNode::Leaf;

        UInt32 triOffset = oObject.getTriOffset();
     
        pMem.putValue(count    );
        pMem.putValue(triOffset);
    }
    else
    {
        UInt32 childOffset = oObject.getChildOffset() << 2;
        childOffset |= oObject.getSplitAxis();

        Real32 split = oObject.getSplit();

        pMem.putValue(childOffset);
        pMem.putValue(split      );
    }
}

/* static */ void
FieldTraits<IntersectKDTreeNode>::copyToBin(
          BinaryDataHandler   &pMem,
    const IntersectKDTreeNode *pObjectStore,
          UInt32               uiNumObjects)
{
    for(UInt32 i = 0; i < uiNumObjects; ++i)
    {
        copyToBin(pMem, pObjectStore[i]);
    }
}

/* static */ void
FieldTraits<IntersectKDTreeNode>::copyFromBin(
    BinaryDataHandler   &pMem,
    IntersectKDTreeNode &oObject)
{
    UInt32 count;

    pMem.getValue(count);

    UInt32 flags = count & 0x03;
    count >>= 2;

    if(flags == IntersectKDTreeNode::Leaf)
    {
        UInt32 triOffset;
        pMem.getValue(triOffset);

        oObject.setLeaf(count, triOffset);
    }
    else
    {
        Real32 split;
        pMem.getValue(split);

        oObject.setInterior(static_cast<IntersectKDTreeNode::FlagsE>(flags),
                            count, split);
    }
}

/* static */ void
FieldTraits<IntersectKDTreeNode>::copyFromBin(
    BinaryDataHandler   &pMem,
    IntersectKDTreeNode *pObjectStore,
    UInt32               uiNumObjects )
{
    for(UInt32 i = 0; i < uiNumObjects; ++i)
    {
        copyFromBin(pMem, pObjectStore[i]);
    }
}

OSG_END_NAMESPACE
