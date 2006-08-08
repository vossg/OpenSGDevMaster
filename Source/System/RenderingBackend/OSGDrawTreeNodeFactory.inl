/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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
DrawTreeNode *DrawTreeNodeFactory::create(void)
{
    DrawTreeNode *returnValue = NULL;

    if(_currentFreeNode != _nodeStore.end())
    {
        returnValue = *_currentFreeNode;

        ++_currentFreeNode;

        returnValue->reset();

        ++_uiReused;
    }
    else
    {
        returnValue = new DrawTreeNode();

        _nodeStore.push_back(returnValue);

        _currentFreeNode = _nodeStore.end();

        ++_uiAllocated;
    }
    
    return returnValue;
}

inline
void DrawTreeNodeFactory::freeAll(void)
{
    _currentFreeNode = _nodeStore.begin();

    _uiAllocated = 0;
    _uiReused    = 0;
}


OSG_END_NAMESPACE

#define OSGDRAWTREENODEFACTORY_INLINE_CVSID "@(#)$Id: $"

