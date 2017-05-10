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

#include <sstream>
#include <fstream>

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGGLFuncProtos.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGDrawEnv.h"
#include "OSGComputeShaderAlgorithm.h"

#include "OSGTextureImageChunk.h"
#include "OSGComputeShaderChunk.h"
#include "OSGChunkMaterial.h"

#include "OSGShaderStorageBufferObjChunk.h"
#include "OSGShaderStorageBufferObjRefChunk.h"
#include "OSGShaderStorageBufferObjStdLayoutChunk.h"
#include "OSGUniformBufferObjChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGComputeShaderAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGComputeShaderAlgorithm.fcd)
// and regenerate the base file.

UInt32 ComputeShaderAlgorithm::_arbComputeShader = 
    Window::invalidExtensionID;

UInt32 ComputeShaderAlgorithm::_arbComputeVariableGroupSize = 
    Window::invalidExtensionID;

UInt32 ComputeShaderAlgorithm::_arbShaderImageLoadStore = 
    Window::invalidExtensionID;

UInt32 ComputeShaderAlgorithm:: FuncIdDispatchCompute = 
    Window::invalidFunctionID;

UInt32 ComputeShaderAlgorithm:: FuncIdDispatchComputeGroupSize = 
    Window::invalidFunctionID;

UInt32 ComputeShaderAlgorithm:: FuncIdMemoryBarrier = 
    Window::invalidFunctionID;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void ComputeShaderAlgorithm::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void ComputeShaderAlgorithm::dump(
          UInt32    OSG_CHECK_ARG(uiIndent), 
    const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump ComputeShaderAlgorithm NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ComputeShaderAlgorithm::ComputeShaderAlgorithm(void) :
    Inherited()
{
}

ComputeShaderAlgorithm::ComputeShaderAlgorithm(
    const ComputeShaderAlgorithm &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ComputeShaderAlgorithm::~ComputeShaderAlgorithm(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

Action::ResultE ComputeShaderAlgorithm::renderEnter(Action *pAction)
{
    return Action::Continue;
}

Action::ResultE ComputeShaderAlgorithm::renderLeave(Action *pAction)
{
    return Action::Continue;
}

void ComputeShaderAlgorithm::execute(HardwareContext *pContext, 
                                     DrawEnv         *pEnv    )
{
    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_arbComputeShader, 0x0403, 0xFFFF))
    {
        FWARNING(("OpenGL compute shader is not supported, couldn't find "
                  "extension 'GL_ARB_compute_shader'!\n"));

        return;
    }

    if(_sfUseVariableWorkGroupSize.getValue() == true &&
       !pWin->hasExtOrVersion(_arbComputeVariableGroupSize, 0x0403, 0xFFFF))
    {
        FWARNING(("OpenGL variable group size is not supported, couldn't find "
                    "extension 'GL_ARB_compute_variable_group_size'!\n"));

        return;
    }

    if(_sfUseMemoryBarrier.getValue() == true &&
       !pWin->hasExtOrVersion(_arbShaderImageLoadStore, 0x0402))
    {
        FWARNING(("OpenGL memory barrier is not supported, couldn't find "
                    "extension 'GL_ARB_shader_image_load_store'!\n"));

        return;
    }

    if(_sfComputeShader.getValue() == NULL)
    {
        return;
    }

    MFTextureImagesType::const_iterator tIt  = _mfTextureImages.begin();
    MFTextureImagesType::const_iterator tEnd = _mfTextureImages.end  ();

    UInt32 uiSlot = 0;

    for(; tIt != tEnd; ++tIt, ++uiSlot)
    {
        if((*tIt) != NULL)
        {
            (*tIt)->activate(pEnv, uiSlot);
        }
    }

    _sfComputeShader.getValue()->activate(pEnv, 0);

    //
    // Buffer objects might introspect the shader code. Therefore their activation must
    // happen after the activation of the shader itself.
    //
    if (_sfChunkMaterial.getValue() != NULL)
    {
        const MFUnrecStateChunkPtr *chunks = _sfChunkMaterial.getValue()->getMFChunks();
        const MFInt32              *slots  = _sfChunkMaterial.getValue()->getMFSlots ();

        for(SizeT i = 0; i < chunks->size(); ++i)
        {
            StateChunk* chunk = (*chunks)[i];
            if (chunk != NULL)
            {
                UInt32 slot = (*slots)[i];

                if ( chunk->getType().isDerivedFrom(ShaderStorageBufferObjChunk::getClassType())
                  || chunk->getType().isDerivedFrom(ShaderStorageBufferObjRefChunk::getClassType())
                  || chunk->getType().isDerivedFrom(ShaderStorageBufferObjStdLayoutChunk::getClassType())
                  || chunk->getType().isDerivedFrom(UniformBufferObjChunk::getClassType())
                  || chunk->getType().isDerivedFrom(UniformBufferObjStd140Chunk::getClassType())
                  || chunk->getType().isDerivedFrom(TextureImageChunk::getClassType())
                    )
                {
                    chunk->activate(pEnv, slot);
                }
            }
        }
    }

    if (_sfUseVariableWorkGroupSize.getValue() == true)
    {
        OSGGETGLFUNCBYID_GL4(glDispatchComputeGroupSizeARB,
                             osgGlDispatchComputeGroupSizeARB,
                             ComputeShaderAlgorithm::FuncIdDispatchComputeGroupSize,
                             pWin);

        osgGlDispatchComputeGroupSizeARB(_sfDispatchConfig.getValue()[0],
                                         _sfDispatchConfig.getValue()[1],
                                         _sfDispatchConfig.getValue()[2],
                                         _sfWorkGroupSize.getValue()[0],
                                         _sfWorkGroupSize.getValue()[1],
                                         _sfWorkGroupSize.getValue()[2]);
    }
    else
    {
        OSGGETGLFUNCBYID_GL4(glDispatchCompute,
                             osgGlDispatchCompute,
                             ComputeShaderAlgorithm::FuncIdDispatchCompute,
                             pWin);

        osgGlDispatchCompute(_sfDispatchConfig.getValue()[0],
                             _sfDispatchConfig.getValue()[1],
                             _sfDispatchConfig.getValue()[2]);
    }

    if (_sfUseMemoryBarrier.getValue() == true)
    {
        OSGGETGLFUNCBYID_GL4(glMemoryBarrier,
                        osgGlMemoryBarrier,
                        ComputeShaderAlgorithm::FuncIdMemoryBarrier,
                        pWin);

        osgGlMemoryBarrier(_sfMemoryBarrier.getValue());
    }

    _sfComputeShader.getValue()->deactivate(pEnv, 0);

    if (_sfChunkMaterial.getValue() != NULL)
    {
        const MFUnrecStateChunkPtr *chunks = _sfChunkMaterial.getValue()->getMFChunks();
        const MFInt32              *slots  = _sfChunkMaterial.getValue()->getMFSlots ();

        for(SizeT i = 0; i < chunks->size(); ++i)
        {
            StateChunk* chunk = (*chunks)[i];
            if (chunk != NULL)
            {
                UInt32 slot = (*slots)[i];

                if ( chunk->getType().isDerivedFrom(ShaderStorageBufferObjChunk::getClassType())
                  || chunk->getType().isDerivedFrom(ShaderStorageBufferObjRefChunk::getClassType())
                  || chunk->getType().isDerivedFrom(ShaderStorageBufferObjStdLayoutChunk::getClassType())
                  || chunk->getType().isDerivedFrom(UniformBufferObjChunk::getClassType())
                  || chunk->getType().isDerivedFrom(UniformBufferObjStd140Chunk::getClassType())
                  || chunk->getType().isDerivedFrom(TextureImageChunk::getClassType())
                    )
                {
                    chunk->deactivate(pEnv, slot);
                }
            }
        }
    }

    tIt    = _mfTextureImages.begin();
    uiSlot = 0;
 
    for(; tIt != tEnd; ++tIt, ++uiSlot)
    {
        if((*tIt) != NULL)
        {
            (*tIt)->deactivate(pEnv, uiSlot);
        }
    }


}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ComputeShaderAlgorithm::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbComputeShader = 
            Window::registerExtension("GL_ARB_compute_shader");

        _arbComputeVariableGroupSize = 
            Window::registerExtension("GL_ARB_compute_variable_group_size");

        _arbShaderImageLoadStore = 
            Window::registerExtension("GL_ARB_shader_image_load_store");

        FuncIdDispatchCompute = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDispatchCompute",
             _arbComputeShader);

        FuncIdDispatchComputeGroupSize = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDispatchComputeGroupSizeARB",
             _arbComputeVariableGroupSize);

        FuncIdMemoryBarrier = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glMemoryBarrier",
             _arbShaderImageLoadStore);
    }
}

OSG_END_NAMESPACE
