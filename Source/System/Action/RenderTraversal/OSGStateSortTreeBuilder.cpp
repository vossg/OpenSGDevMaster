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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_CLEANED_RENDERACTION

#include "OSGRenderTreeNodePool.h"
#include "OSGStateSortTreeBuilder.h"
#include "OSGBaseFunctions.h"
#include "OSGRenderPartition.h"

//#define OSG_DUMP_SORTING

OSG_USING_NAMESPACE

/*! \class OSG::StateSortTreeBuilder
    \ingroup 
 */

StateSortTreeBuilder StateSortTreeBuilder::Proto;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


StateSortTreeBuilder::StateSortTreeBuilder(void) :
    _oSorter(),
    _mFallbackSorter()
{
}

StateSortTreeBuilder::~StateSortTreeBuilder(void)
{
}


void StateSortTreeBuilder::reset(void)
{
    TreeBuilderBase::reset();

    _mFallbackSorter.clear();

    _oSorter.reset();
}


void StateSortTreeBuilder::add(DrawEnv &denv, 
                               RenderPartition *part,
                               RenderTreeNode *pNode,
                               State          *pState,
                               StateOverride  *pStateOverride,
                               UInt32          uiKeyGen      )
{
    if(_pRoot == NULL)
    {
        _pRoot = _pNodePool->create();

        _pRoot->addChild(_oSorter.setupLevel1Root(_pNodePool));
    }

    UInt32 uiSortKey = pState->getSortKey(uiKeyGen);

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

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGStateSortTreeBuilder.cpp 142 2006-09-18 08:49:39Z vossg $";
    static Char8 cvsid_hpp[] = OSGSTATESORTTREEBUILDER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATESORTTREEBUILDER_INLINE_CVSID;
}

#endif
