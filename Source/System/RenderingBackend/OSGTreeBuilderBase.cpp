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
#include "OSGTreeBuilderBase.h"
#include "OSGBaseFunctions.h"
#include "OSGRenderPartitionBase.h"

//#define OSG_DUMP_SORTING

OSG_BEGIN_NAMESPACE

/*! \class OSG::TreeBuilderBase
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


TreeBuilderBase::TreeBuilderBase(void) :
    _pNodePool      (NULL),
    _uiNodePoolIdx  (0   ),
    _uiActiveMatrix (0   ),
    _uiMatrixId     (0   ),
    _currMatrix     (    ),
    _accMatrix      (    )
{
}

TreeBuilderBase::~TreeBuilderBase(void)
{
}

void TreeBuilderBase::setNodePool(RenderTreeNodePool *pNodePool)
{
    _pNodePool = pNodePool;
}

RenderTreeNodePool *TreeBuilderBase::getNodePool(void)
{
    return _pNodePool;
}

void TreeBuilderBase::reset(void)
{
    _uiMatrixId = 0;
}

void TreeBuilderBase::drawNode(RenderTreeNode      *pNode,
                               DrawEnv             &denv,
                               RenderPartitionBase *part)
{
    while (pNode != NULL)
    {
        UInt32 uiNextMatrix = pNode->getMatrixStore().first;

        if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
        {
            glLoadMatrixf(pNode->getMatrixStore().second.getValues());

            _uiActiveMatrix = uiNextMatrix;

            _currMatrix.second = pNode->getMatrixStore().second;

            updateTopMatrix(denv);

            denv.setObjectToWorld(_accMatrix);

            ++part->_uiNumMatrixChanges;

            // Negative scaled matrices in conjunction with double sided
            // lighting
            // gives wrong render results cause the lighting itselfs gets
            // inverted. This corrects this behavior.

            if(part->_bCorrectNegScale)
            {
                const Matrix &m = _currMatrix.second;

                // test for a "flipped" matrix
                // glFrontFace can give conflicts with the polygon chunk ...

                if(m[0].cross(m[1]).dot(m[2]) < 0.0)
                {
                    glFrontFace(GL_CW);
                }
                else
                {
                    glFrontFace(GL_CCW);
                }
            }
        }

        State         *pNewState         = pNode->getState();
        StateOverride *pNewStateOverride = pNode->getStateOverride();

        denv.setLightState(pNode->getLightState());

        denv.activateState(pNewState, pNewStateOverride);

        if(pNode->hasFunctor() == true)
        {
            pNode->getFunctor()(&denv);
        }

        if(pNode->getFirstChild() != NULL)
        {
            drawNode(pNode->getFirstChild(), denv, part);
        }

        pNode = pNode->getBrother();
    }
}

void TreeBuilderBase::updateTopMatrix(DrawEnv &denv)
{
    _accMatrix = denv.getCameraToWorld();
    _accMatrix.mult(_currMatrix.second);
}

const Matrix &TreeBuilderBase::topMatrix(void)
{
    return _accMatrix;
}

OSG_END_NAMESPACE
