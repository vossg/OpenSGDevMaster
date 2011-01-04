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
#include "OSGStateSortTreeBuilder.h"
#include "OSGBaseFunctions.h"
#include "OSGRenderActionBase.h"
#include "OSGRenderPartition.h"
#include "OSGStateOverride.h"

//#define OSG_DUMP_SORTING

OSG_BEGIN_NAMESPACE

/*! \class OSG::StateSortTreeBuilder
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


StateSortTreeBuilder::StateSortTreeBuilder(void) :
     _pRoot          (NULL),
     _oSorter        (),
     _mFallbackSorter()
{
}

StateSortTreeBuilder::~StateSortTreeBuilder(void)
{
}

void
StateSortTreeBuilder::setNodePool(RenderTreeNodePool *pNodePool)
{
    _pNodePool     = pNodePool;
    _uiNodePoolIdx = pNodePool->registerType<RenderTreeNode>();
}

void StateSortTreeBuilder::reset(void)
{
    TreeBuilderBase::reset();

    _pRoot = NULL;

    _oSorter        .reset();
    _mFallbackSorter.clear();
}

void StateSortTreeBuilder::add(RenderActionBase    *pAction,
                               RenderPartitionBase *pPart,
                               DrawFunctor         &drawFunc,
                               State               *pState,
                               StateOverride       *pStateOverride)
{
    if(_pRoot == NULL)
    {
        _pRoot = _pNodePool->create<RenderTreeNode>(_uiNodePoolIdx);

        RenderTreeNode *pL1Root =
            _pNodePool->create<RenderTreeNode>(_uiNodePoolIdx);

        _oSorter.setupLevel1Root(pL1Root);
        _pRoot->addChild        (pL1Root);
    }

    RenderPartition *pRPart = dynamic_cast<RenderPartition *>(pPart);
    RenderTreeNode  *pNode  = _pNodePool->create<RenderTreeNode>(_uiNodePoolIdx);

    pNode->setNode         (pAction->getActNode()  );
    pNode->setFunctor      (drawFunc               );
    pNode->setState        (pState                 );
    pNode->setStateOverride(pStateOverride         );
    pNode->setLightState   (pRPart->getLightState());

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
    pNode->setMatrixStore(pRPart->getMatrixStackTop());
#else
    Matrix4f tmpMat;
    tmpMat.convertFrom(pRPart->getModelViewMatrix());
    
    MatrixStore tmpMS (pRPart->getMatrixStackTop().first, tmpMat);

    pNode->setMatrixStore(tmpMS);
#endif

    UInt32 keyGen  = pRPart->getKeyGen();
    UInt32 sortKey = pState->getSortKey(keyGen);

    if(pStateOverride != NULL)
    {
        pStateOverride->updateSortKey(sortKey, keyGen);
    }

    if(sortKey > State::DefaultKeyMask)
    {
        MapSorterIt     msIt     = _mFallbackSorter.lower_bound(sortKey);
        RenderTreeNode *pMatRoot = NULL;

        if(msIt == _mFallbackSorter.end() || msIt->first != sortKey)
        {
            pMatRoot = _pNodePool->create<RenderTreeNode>(_uiNodePoolIdx);

            pMatRoot->setState        (pState        );
            pMatRoot->setStateOverride(pStateOverride);

            _mFallbackSorter.insert(msIt,
                                    MapSorter::value_type(sortKey, pMatRoot));

            _pRoot->addChild(pMatRoot);
        }
        else
        {
            pMatRoot = msIt->second;
        }

        pMatRoot->addChild(pNode);
    }
    else
    {
        UInt32 key1 =  sortKey & State::Key1Mask;
        UInt32 key2 = (sortKey & State::Key2Mask) >> 10;
        UInt32 key3 = (sortKey & State::Key3Mask) >> 20;

        RenderTreeNode *pMatRoot = _oSorter.find(key1,
                                                 key2,
                                                 key3);

        if(pMatRoot == NULL)
        {
            pMatRoot = _pNodePool->create<RenderTreeNode>(_uiNodePoolIdx);

            _oSorter.insert( key1,
                             key2,
                             key3,
                             pMatRoot,
                            _pNodePool);
        }

        pMatRoot->addChild(pNode);
    }
}

void StateSortTreeBuilder::draw(DrawEnv &denv, RenderPartitionBase *pPart)
{
    _uiActiveMatrix = 0;

    Inherited::drawNode(_pRoot, denv, pPart);
}

OSG_END_NAMESPACE
