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

#include "OSGAddOnsConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGDrawEnv.h"
#include "OSGComputeShaderAlgorithm.h"

#include "OSGTextureImageChunk.h"
#include "OSGComputeShaderChunk.h"

#include "OSGGLFuncProtos.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGComputeShaderAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGComputeShaderAlgorithm.fcd)
// and regenerate the base file.

UInt32 ComputeShaderAlgorithm::_arbComputeShader      = 
    Window::invalidExtensionID;

UInt32 ComputeShaderAlgorithm:: FuncIdDispatchCompute = 
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

    OSGGETGLFUNCBYID_GL4(glDispatchCompute,
                         osgGlDispatchCompute,
                         ComputeShaderAlgorithm::FuncIdDispatchCompute,
                         pWin);

    osgGlDispatchCompute(_sfDispatchConfig.getValue()[0],
                         _sfDispatchConfig.getValue()[1],
                         _sfDispatchConfig.getValue()[2]);

    _sfComputeShader.getValue()->deactivate(pEnv, 0);

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

        FuncIdDispatchCompute =
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDispatchCompute",
             _arbComputeShader);

    }
}

OSG_END_NAMESPACE
