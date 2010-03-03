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
#include "OSGStateSorter.h"
#include "OSGBaseFunctions.h"
#include "OSGStateOverride.h"

//#define OSG_DUMP_SORTING

OSG_USING_NAMESPACE

/*! \class OSG::StateSorter
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


StateSorter::StateSorter(void) :
    _pNodePool      (NULL    ),
    _pRoot          (NULL    ),
    _oSorter        (        ),
    _eSortMode      (StateKey),
    _mFallbackSorter(        )
{
}

StateSorter::~StateSorter(void)
{
}


void StateSorter::add(RenderTreeNode *pNode,
                      State          *pState,
                      StateOverride  *pStateOverride,
                      UInt32          uiKeyGen      )
{
    if(_pRoot == NULL)
    {
        _pRoot = _pNodePool->create();

        _pRoot->addChild(_oSorter.setupLevel1Root(_pNodePool));
    }

    if(_eSortMode == StateKey)
    {
        UInt32 uiSortKey = pState->getSortKey(uiKeyGen);

        if(pStateOverride != NULL)
        {
            pStateOverride->updateSortKey(uiSortKey, uiKeyGen);
        }

        // Default Mat Id sorting
        if(uiSortKey > State::DefaultKeyMask)
        {
            MapSorterIt msIt = _mFallbackSorter.lower_bound(uiSortKey);

            RenderTreeNode *pMatElem = NULL;

            if(msIt == _mFallbackSorter.end() || msIt->first != uiSortKey)
            {
                pMatElem = _pNodePool->create();
        
                pMatElem->setState        (pState        );
                pMatElem->setStateOverride(pStateOverride);
                
                _mFallbackSorter.insert(msIt, std::make_pair(uiSortKey, 
                                                             pMatElem ));

                _pRoot->addChild(pMatElem);
            }
            else
            {
                pMatElem = msIt->second;
            }

            
            pMatElem->addChild(pNode);
        }
        else
        {
#ifdef OSG_DUMP_SORTING
            fprintf(stderr, "Sort by chunk\n");
#endif

            UInt32 uiKey1 =  uiSortKey & State::Key1Mask;
            UInt32 uiKey2 = (uiSortKey & State::Key2Mask) >> 10;
            UInt32 uiKey3 = (uiSortKey & State::Key3Mask) >> 20;
            
#ifdef OSG_DUMP_SORTING
            fprintf(stderr, "Got Keys %d %d %d\n", uiKey1, uiKey2, uiKey3);
#endif

            RenderTreeNode *pMatElem = _oSorter.find(uiKey1,
                                                     uiKey2,
                                                     uiKey3);

#ifdef OSG_DUMP_SORTING
            fprintf(stderr, "got %p\n", pMatElem);
#endif

            if(pMatElem == NULL)
            {
                pMatElem = _pNodePool->create();
        
//                pMatElem->setState        (pState        );
//                pMatElem->setStateOverride(pStateOverride);
                
                _oSorter.insert( uiKey1,
                                 uiKey2,
                                 uiKey3,
                                 pMatElem,
                                _pNodePool);

#ifdef OSG_DUMP_SORTING
                fprintf(stderr, "Insert %p\n", pMatElem);
#endif
            }

            pMatElem->addChild(pNode);

            pNode->setState        (pState        );
            pNode->setStateOverride(pStateOverride);
        }
    }
    else if(_eSortMode == ScalarKey)
    {
        if(_pRoot->getFirstChild() == NULL)
        {
            _pRoot->addChild(pNode);
        }
        else
        {
            RenderTreeNode *pCurrent = _pRoot->getFirstChild();
        
            RenderTreeNode *pLast    = NULL;
            bool            bFound   = false;
        
            do
            {
                if(pNode->getScalar() > pCurrent->getScalar())
                {
                    pLast    = pCurrent;
                    pCurrent = pCurrent->getBrother();
                }
                else
                {
                    bFound = true;
                }
                
            } while(bFound   == false && 
                    pCurrent != NULL    );

            if(bFound == true)
            {
                if(pLast == NULL)
                {
                    _pRoot->insertFirstChild(pNode);
                }
                else
                {
                    _pRoot->insertChildAfter(pLast, pNode);
                }
            }
            else
            {
                _pRoot->addChild(pNode);
            }
        }
    }
    else
    {
        FFATAL(("StateSorter::add: unknown sort mode: %d!\n", _eSortMode));
    }
}

