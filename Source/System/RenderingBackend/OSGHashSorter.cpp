/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGRenderTreeNodePool.h"
#include "OSGHashSorter.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/*! \class OSG::HashSorter
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


HashSorter::HashSorter(void) :
    _oLevel3Pool  (),
    _oLevel2Pool  (),
    _oLevel1Sorter()
{
    _oLevel1Sorter.init();
    _oLevel1Sorter._pRoot = NULL;
}

HashSorter::~HashSorter(void)
{
}

RenderTreeNode *HashSorter::find(UInt16 uiKey1,
                                 UInt16 uiKey2,
                                 UInt16 uiKey3)
{
    RenderTreeNode *returnValue = NULL;

    Level1Sorter::It  l1It = _oLevel1Sorter._mLevelMap.find(uiKey1);

    Level2Sorter     *pL2  = 
        (l1It != _oLevel1Sorter._mLevelMap.end()) ? l1It->second : NULL;
    
    if(pL2 != NULL)
    {
        Level2Sorter::It  l2It = pL2->_mLevelMap.find(uiKey2);

        Level3Sorter     *pL3  = 
            (l2It != pL2->_mLevelMap.end()) ? l2It->second : NULL;

        if(pL3 != NULL)
        {
            Level3Sorter::It l3It = pL3->_mLevelMap.find(uiKey3);

            returnValue = 
                (l3It != pL3->_mLevelMap.end()) ? l3It->second : NULL;
        }
    }

    return returnValue;
}

void HashSorter::insert(UInt16              uiKey1,
                        UInt16              uiKey2,
                        UInt16              uiKey3,
                        RenderTreeNode     *pNode,
                        RenderTreeNodePool *pPool )
{
    Level1Sorter::It  l1It = _oLevel1Sorter._mLevelMap.find(uiKey1);

    Level2Sorter     *pL2  = 
        (l1It != _oLevel1Sorter._mLevelMap.end()) ? l1It->second : NULL;

    Level3Sorter   *pL3  = NULL;

    if(pL2 == NULL)
    {
        pL2 = _oLevel2Pool.create();

        if(pL2->_pRoot == NULL)
            pL2->_pRoot = pNode;

        pL2->_pRoot = pPool->create();
        
        _oLevel1Sorter._pRoot->addChild(pL2->_pRoot);
        
        _oLevel1Sorter._mLevelMap[uiKey1] = pL2;
    }
    else
    {
        Level2Sorter::It  l2It = pL2->_mLevelMap.find(uiKey2);

        pL3 = (l2It != pL2->_mLevelMap.end()) ? l2It->second : NULL; 
    }

    if(pL3 == NULL)
    {
        pL3 = _oLevel3Pool.create();
        
        pL2->_mLevelMap[uiKey2] = pL3;

        pL3->_pRoot = pNode;        

        pL2->_pRoot->insertFirstChild(pL3->_pRoot);
    }
    else
    {
        pL3->_pRoot->insertBrother(pNode);
    }

    pL3->_mLevelMap[uiKey3] = pNode;
}

