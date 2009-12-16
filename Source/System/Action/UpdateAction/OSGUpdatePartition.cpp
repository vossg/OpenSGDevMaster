/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2009 by the OpenSG Forum                   *
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

#include "OSGUpdatePartition.h"
#include "OSGRenderPartitionBase.h"

OSG_BEGIN_NAMESPACE

void
UpdatePartition::setupProjection(const Matrix &matProj,
                                 const Matrix &matProjTrans)
{
    _drawEnv.setupProjection(matProj, matProjTrans);
}

void
UpdatePartition::setupViewing(const Matrix &matView)
{
    _drawEnv.setupViewing(matView);

    _modelViewMatrix.second = matView;
    _modelMatrixValid       = false;
}

void
UpdatePartition::reset(void)
{
    _updateAction     = NULL;
    _matrixId         = 1;
    _modelMatrixValid = false;
    _modelMatrix         .setIdentity();
    _modelViewMatrix     .first = 1;
    _modelViewMatrix     .second.setIdentity();
    _modelViewMatrixStack.clear();
    _drawEnv             .clearState();
}

void
UpdatePartition::initFrom(UpdatePartition *sourcePart,
                          UInt32           copyOnPush )
{
    if(0x0000 != (copyOnPush & RenderPartitionBase::CopyViewing))
    {
        _drawEnv.setupViewing(sourcePart->getDrawEnv().getCameraViewing());
    }

    if(0x0000 != (copyOnPush & RenderPartitionBase::CopyMatrix))
    {
        pushMatrix(sourcePart->getModelMatrix());
    }

    if(0x0000 != (copyOnPush & RenderPartitionBase::CopyProjection))
    {
        _drawEnv.setupProjection(
            sourcePart->getDrawEnv().getCameraProjection     (),
            sourcePart->getDrawEnv().getCameraProjectionTrans() );
    }

    if(0x0000 != (copyOnPush & RenderPartitionBase::CopyWindow))
    {
        _drawEnv.setWindow(sourcePart->getDrawEnv().getWindow());
    }

    if(0x0000 != (copyOnPush & RenderPartitionBase::CopyViewportSize))
    {
        _drawEnv.setViewportDimension(
            sourcePart->getDrawEnv().getPixelLeft  (),
            sourcePart->getDrawEnv().getPixelBottom(),
            sourcePart->getDrawEnv().getPixelRight (),
            sourcePart->getDrawEnv().getPixelTop   (),
            sourcePart->getDrawEnv().getFull       () );
    }

    if(0x0000 != (copyOnPush & RenderPartitionBase::CopyNearFar))
    {
        _drawEnv.setCameraNear(sourcePart->getDrawEnv().getCameraNear());
        _drawEnv.setCameraFar (sourcePart->getDrawEnv().getCameraFar ());
    }
}

void
UpdatePartition::updateModelMatrix(void) const
{
    if(_modelMatrixValid == false)
    {
        _modelMatrixValid = true;
        _modelMatrix      = _drawEnv.getCameraToWorld();
        _modelMatrix.mult(_modelViewMatrix.second);
    }
}

OSG_END_NAMESPACE
