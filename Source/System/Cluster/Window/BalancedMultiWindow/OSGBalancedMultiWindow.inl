/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

/*! calculate the load for a given group rendered into the given rectangle
 */

inline 
Real32 BalancedMultiWindow::getVisibleLoad(Int32 const (&rect)[4],
                                           BBox      &bbox)
{
    LoadGroup &group=_cluster.loadGroups[bbox.groupId];
    // invisible
    if(bbox.rect[LEFT]   > rect[RIGHT] ||
       bbox.rect[RIGHT]  < rect[LEFT] ||
       bbox.rect[BOTTOM] > rect[TOP] ||
       bbox.rect[TOP]    < rect[BOTTOM])
        return 0;
    Int32 l = osgMax(rect[0],bbox.rect[0]);
    Int32 b = osgMax(rect[1],bbox.rect[1]);
    Int32 r = osgMin(rect[2],bbox.rect[2]);
    Int32 t = osgMin(rect[3],bbox.rect[3]);
    Real32 visibleArea = (r-l+1) * (t-b+1);
    Real32 area = (bbox.rect[2] - bbox.rect[0] + 1) *
                  (bbox.rect[3] - bbox.rect[1] + 1);
    // constant
    Real32 load = group.constant;
    // pixel
    load += visibleArea * group.pixel;
    // relative
    if(area)
        load += group.ratio * visibleArea / area;
    return load;
}

OSG_END_NAMESPACE
