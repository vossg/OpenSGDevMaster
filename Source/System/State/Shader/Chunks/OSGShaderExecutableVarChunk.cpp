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

#include "OSGConfig.h"

#include "OSGShaderExecutableVarChunk.h"

#include "OSGShaderVariables.h"
#include "OSGShaderProgramVariableChunk.h"

#include "OSGGLFuncProtos.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderExecutableVarChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderExecutableVarChunk.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShaderExecutableVarChunk::_class("ShaderExeVariable", 1, 8);

volatile UInt16 ShaderExecutableVarChunk::_uiChunkCounter = 1;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderExecutableVarChunk::initMethod(InitPhase ePhase)
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

ShaderExecutableVarChunk::ShaderExecutableVarChunk(void) :
    Inherited()
{
}

ShaderExecutableVarChunk::ShaderExecutableVarChunk(
    const ShaderExecutableVarChunk &source) :

    Inherited(source)
{
}

ShaderExecutableVarChunk::~ShaderExecutableVarChunk(void)
{
}

void ShaderExecutableVarChunk::onCreate(const ShaderExecutableVarChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void ShaderExecutableVarChunk::onCreateAspect(
    const ShaderExecutableVarChunk *createAspect,
    const ShaderExecutableVarChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

const StateChunkClass *ShaderExecutableVarChunk::getClass(void) const
{
    return &_class;
}

UInt16 ShaderExecutableVarChunk::getChunkId(void)
{
    return _uiChunkId;
}

void ShaderExecutableVarChunk::merge(ShaderProgramVariableChunk *pVar)
{
    if(pVar == NULL)
        return;

    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pVar);
    }

    _sfVariables.getValue()->merge(pVar->getVariables(),
                                   this->editMFVariableLocations(),
                                   NULL);


    editMField(ProgramVarChunksFieldMask, _mfProgramVarChunks);

    _mfProgramVarChunks.push_back(pVar);

    pVar->addParent(this, ProgramVarChunksFieldId);
}

/*----------------------------- class specific ----------------------------*/

void ShaderExecutableVarChunk::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    if(0x0000 != (whichField & ProgramVarChunksFieldMask))
    {
        if(origin == ChangedOrigin::Child)
        {
            this->remergeVariables();
        }
    }

    Inherited::changed(whichField, origin, details);
}

void ShaderExecutableVarChunk::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump ShaderExecutableVarChunk NI" << std::endl;
}

void ShaderExecutableVarChunk::activate(DrawEnv *pEnv, UInt32)
{
    updateVariables(pEnv);
}

void ShaderExecutableVarChunk::changeFrom(DrawEnv    *pEnv, 
                                          StateChunk *pOther, 
                                          UInt32            )
{
    ShaderExecutableVarChunk *pOld = 
        dynamic_cast<ShaderExecutableVarChunk *>(pOther);

    if(pOld == NULL)
    {
        FWARNING(( "ShaderExecutableVar::changeFrom: caught non-SHLChunk!\n"));
        return;
    }

    // SHLChunk didn't change so do nothing.
    if(pOld == this)
        return;

    updateVariables(pEnv);
}

void ShaderExecutableVarChunk::deactivate(DrawEnv *, UInt32)
{
}

void ShaderExecutableVarChunk::updateVariables(DrawEnv *pEnv)
{
    UInt32 uiProgram = pEnv->getActiveShader();

    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFVariablesType       *pMFVars   = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars   = _sfVariables.getValue()->getMFVariables();
    }

    if(pMFVars == NULL || pMFVars->size() == 0)
    {
        return;
    }

    MFInt32 &vVarLocations = *this->editMFVariableLocations();

    OSG_ASSERT(pMFVars->size() == vVarLocations.size());

    MFInt32::iterator mLocIt = vVarLocations.begin();

    ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
        pMFVars->begin();
    ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
        pMFVars->end  ();

    bool warnUnknown = true;

    for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
    {
        ShaderVariable *pVar = *mVarIt;

        if(pVar == NULL)
            continue;

        osgUniformShaderVariableSwitch(pEnv,    pVar,
                                       *mLocIt, uiProgram, warnUnknown);
    }
}

void ShaderExecutableVarChunk::remergeVariables(void)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pVar);
    }
    else
    {
        _sfVariables.getValue()->clearVariables();

        this->editMFVariableLocations()->clear();
    }

    MFProgramVarChunksType::const_iterator vIt  = _mfProgramVarChunks.begin();
    MFProgramVarChunksType::const_iterator vEnd = _mfProgramVarChunks.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        _sfVariables.getValue()->merge((*vIt)->getVariables(),
                                       this->editMFVariableLocations(),
                                       NULL);
    }
}

OSG_END_NAMESPACE
