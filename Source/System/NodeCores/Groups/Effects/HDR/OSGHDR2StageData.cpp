/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGHDR2StageData.h"
#include "OSGFrameBufferObject.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHDR2StageDataBase.cpp file.
// To modify it, please change the .fcd file (OSGHDR2StageData.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HDR2StageData::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HDR2StageData::HDR2StageData(void) :
    Inherited()
{
}

HDR2StageData::HDR2StageData(const HDR2StageData &source) :
    Inherited(source)
{
}

HDR2StageData::~HDR2StageData(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HDR2StageData::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HDR2StageData::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump HDR2StageData NI" << std::endl;
}

/*----------------------------- Convenience -------------------------------*/

TextureObjChunk* HDR2StageData::getSceneTexObjChunk() const
{
    FrameBufferObject* pFBO = getSceneRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getDepthTexObjChunk() const
{
    FrameBufferObject* pFBO = getSceneRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getDepthAttachment());
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getLuminanceTexObjChunk() const
{
    FrameBufferObject* pFBO = getLuminanceRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getAdaptLuminanceTexObjChunk(UInt32 idx) const
{
    if (idx >= 2)
        return NULL;

    FrameBufferObject* pFBO = getAdaptLuminanceRenderTarget(idx);

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getThresholdTexObjChunk() const
{
    FrameBufferObject* pFBO = getThresholdRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getScaleTexObjChunk(UInt32 idx) const
{
    if (idx >= 3)
        return NULL;

    FrameBufferObject* pFBO = getScaleRenderTarget(idx);

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getBlurHorizTexObjChunk() const
{
    FrameBufferObject* pFBO = getBlurHorizRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getBlurVertTexObjChunk() const
{
    FrameBufferObject* pFBO = getBlurVertRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getCompositeTexObjChunk() const
{
    FrameBufferObject* pFBO = getCompositeRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

TextureObjChunk* HDR2StageData::getExposureTexObjChunk() const
{
    FrameBufferObject* pFBO = getCompositeRenderTarget();

    TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(1));
    if (!pTexBuffer)
        return NULL;

    return pTexBuffer->getTexture();
}

Real32 HDR2StageData::getTimeDeltaInSeconds() const
{
    Real64 timeDelta = getCurrentTime() - getLastTime();

    return static_cast<Real32>(timeDelta/1000.0);
}

OSG_END_NAMESPACE
