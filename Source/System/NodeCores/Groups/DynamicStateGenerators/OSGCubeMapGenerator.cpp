/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGCubeMapGenerator.h"
#include "OSGCubeMapGeneratorStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTexGenChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCubeMapGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGCubeMapGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CubeMapGenerator::initMethod(InitPhase ePhase)
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

CubeMapGenerator::CubeMapGenerator(void) :
    Inherited()
{
}

CubeMapGenerator::CubeMapGenerator(const CubeMapGenerator &source) :
    Inherited(source)
{
}

CubeMapGenerator::~CubeMapGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CubeMapGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CubeMapGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CubeMapGenerator NI" << std::endl;
}

CubeMapGeneratorStageDataP CubeMapGenerator::setupStageData(
    RenderTraversalActionBase *pAction)
{
    CubeMapGeneratorStageDataP returnValue = 
        CubeMapGeneratorStageData::create();
    
    if(returnValue == NULL)
        return returnValue;

    FrameBufferObjectPtr pCubeTarget  = FrameBufferObject::create();

    RenderBufferPtr      pDepthBuffer = RenderBuffer     ::create();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

    TextureObjChunkPtr pCubeTex     = NullFC;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexture))
    {
        pCubeTex = TextureObjChunk::create();

        ImagePtr           pImg         = Image          ::create();
    
        pImg->set(Image::OSG_RGB_PF, 
                  getWidth (), 
                  getHeight(),
                  1,
                  1,
                  1,
                  0.0,
                  0,
                  Image::OSG_UINT8_IMAGEDATA,
                  false,
                  6);
        
        pCubeTex   ->setImage         (pImg              ); 
        pCubeTex   ->setMinFilter     (GL_LINEAR         );
        pCubeTex   ->setMagFilter     (GL_LINEAR         );
        pCubeTex   ->setWrapS         (GL_REPEAT         );
        pCubeTex   ->setWrapT         (GL_REPEAT         );
        pCubeTex   ->setInternalFormat(getTextureFormat());
    }
    else
    {
        pCubeTex = _sfTexture.getValue();
    }

    TextureEnvChunkPtr pCubeTexEnv  = NullFC;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        pCubeTexEnv = TextureEnvChunk::create();
        
        pCubeTexEnv->setEnvMode       (GL_REPLACE       );
    }

    TexGenChunkPtr     pCubeTexGen  = NullFC;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        pCubeTexGen = TexGenChunk::create();

        pCubeTexGen->setGenFuncS(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncT(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncR(GL_REFLECTION_MAP);
        
        pCubeTexGen->setSBeacon(pAction->getActNode());
        pCubeTexGen->setTBeacon(pAction->getActNode());
        pCubeTexGen->setRBeacon(pAction->getActNode());
    }


    static GLenum targets[6] = 
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
    };

    for(UInt32 i = 0; i < 6; ++i)
    {
        TextureBufferPtr pCubeTexBuffer = TextureBuffer::create();
    
        pCubeTexBuffer->setTexture  (pCubeTex  );
        pCubeTexBuffer->setTexTarget(targets[i]);

        pCubeTarget->setSize           (getWidth (),
                                        getHeight());
        pCubeTarget->setColorAttachment(pCubeTexBuffer,    i);
        pCubeTarget->setDepthAttachment(pDepthBuffer        );
        
        setRenderTarget(pCubeTarget);
    }

    if(0x0000 != (_sfSetupMode.getValue() & OverrideTex))
    {
        this->addChunk(pCubeTex,
                       getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        this->addChunk(pCubeTexEnv,
                       getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        this->addChunk(pCubeTexGen,
                       getTexUnit());
    }

    return returnValue;
}

void CubeMapGenerator::initData(RenderTraversalActionBase *pAction)
{
    CubeMapGeneratorStageDataP pData = 
        pAction->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction);
        
        this->setData(pData, _iDataSlotId, pAction);
    }
}


OSG_END_NAMESPACE
