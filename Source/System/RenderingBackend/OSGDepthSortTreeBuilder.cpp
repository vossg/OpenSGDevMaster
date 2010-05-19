/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                    Copyright (C) 2010 by the OpenSG Forum                 *
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

#include "OSGDepthSortTreeBuilder.h"
#include "OSGRenderActionBase.h"
#include "OSGRenderPartition.h"

OSG_BEGIN_NAMESPACE

DepthSortTreeBuilder::DepthSortTreeBuilder(void) :
    Inherited()
{
}

DepthSortTreeBuilder::~DepthSortTreeBuilder(void)
{
}

void
DepthSortTreeBuilder::add(RenderActionBase    *pAction,
                          RenderPartitionBase *pPart,
                          DrawFunctor         &drawFunc,
                          State               *pState,
                          StateOverride       *pStateOverride)
{
    RenderPartition *pRPart = dynamic_cast<RenderPartition *>(pPart);
    RenderTreeNode  *pNode  = _pNodePool->create<RenderTreeNode>(_uiNodePoolIdx);

    OSG::Node *pActNode = pAction->getActNode();
    Pnt3f      objPos;

    pActNode->getVolume().getCenter(objPos);

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
    pRPart->getModelViewMatrix().mult(objPos, objPos);

    pNode->setScalar     (objPos[2]                 );
    pNode->setMatrixStore(pRPart->getMatrixStackTop());
#else
    Pnt3d tmpPos(objPos[0], objPos[1], objPos[2]);
    pRPart->getModelViewMatrix().mult(tmpPos, tmpPos);

    Matrix4f tmpMat;
    tmpMat.convertFrom(pRPart->getModelViewMatrix());
    MatrixStore tmpMS(pRPart->getMatrixStackTop().first, tmpMat);

    pNode->setScalar     (tmpPos[2]);
    pNode->setMatrixStore(tmpMS    );
#endif

    pNode->setState        (pState                 );
    pNode->setStateOverride(pStateOverride         );
    pNode->setLightState   (pRPart->getLightState());

    pNode->setNode   (pActNode);
    pNode->setFunctor(drawFunc);


    Inherited::addNode(pNode);
}

OSG_END_NAMESPACE
