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

OSG_BEGIN_NAMESPACE

inline void
IntersectKDTreeNode::setLeaf(UInt32 triCount, UInt32 triOffset)
{
    _flags     = Leaf;
    _count     = triCount;
    _triOffset = triOffset;
}

inline void
IntersectKDTreeNode::setInterior(FlagsE axis, UInt32 childOffset, Real32 split)
{
    _flags = axis;
    _count = childOffset;
    _split = split;
}

inline bool
IntersectKDTreeNode::isLeaf(void) const
{
    return (_flags == Leaf);
}

inline UInt32
IntersectKDTreeNode::getChildOffset(void) const
{
    return _count;
}

inline UInt32
IntersectKDTreeNode::getSplitAxis(void) const
{
    return _flags;
}

inline Real32
IntersectKDTreeNode::getSplit(void) const
{
    return _split;
}

inline UInt32
IntersectKDTreeNode::getTriCount(void) const
{
    return _count;
}

inline UInt32
IntersectKDTreeNode::getTriOffset(void) const
{
    return _triOffset;
}

inline bool
operator==(const IntersectKDTreeNode &lhs, const IntersectKDTreeNode &rhs)
{
    bool result = false;

    if(lhs.isLeaf() == rhs.isLeaf())
    {
        if(lhs.getTriOffset() == rhs.getTriOffset())
        {
            result = (lhs.getTriCount() == rhs.getTriCount());
        }
    }
    else
    {
        if(lhs.getChildOffset() == rhs.getChildOffset())
        {
            if(lhs.getSplitAxis() == rhs.getSplitAxis())
            {
                result = (lhs.getSplit() == rhs.getSplit());
            }
        }
    }

    return result;
}

OSG_END_NAMESPACE
