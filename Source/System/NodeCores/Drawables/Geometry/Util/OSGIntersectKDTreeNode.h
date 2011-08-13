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

#ifndef _OSGINTERSECTKDTREENODE_H_
#define _OSGINTERSECTKDTREENODE_H_

#include "OSGConfig.h"
#include "OSGDrawableDef.h"
#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_DRAWABLE_DLLMAPPING IntersectKDTreeNode
{
  public:
    enum FlagsE
    {
        AxisX = 0x00,
        AxisY = 0x01,
        AxisZ = 0x02,
        Leaf  = 0x03
    };

    void   setLeaf    (UInt32 triCount, UInt32 triOffset                );
    void   setInterior(FlagsE axis,     UInt32 childOffset, Real32 split);

    bool   isLeaf        (void) const;

    UInt32 getChildOffset(void) const;
    UInt32 getSplitAxis  (void) const;
    Real32 getSplit      (void) const;

    UInt32 getTriCount   (void) const;
    UInt32 getTriOffset  (void) const;
 
  private:

    UInt32 _flags :  2;     // both
    UInt32 _count : 30;     // child offset / tri count

    union
    {
        UInt32 _triOffset;  // leaf,     triangle indices start
        Real32 _split;      // interior, split position
    };
};

OSG_DRAWABLE_DLLMAPPING bool
operator==(const IntersectKDTreeNode &lhs, const IntersectKDTreeNode &rhs);

OSG_END_NAMESPACE

#include "OSGIntersectKDTreeNode.inl"

#endif /* _OSGINTERSECTKDTREENODE_H_ */
