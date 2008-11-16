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

#include "OSGSimpleSHLVariableChunk.h"

#include "OSGShaderVariables.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSimpleSHLVariableChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleSHLVariableChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SimpleSHLVariableChunk::_class("SimpleSHLVariable", 1, 31);

volatile UInt16 SimpleSHLVariableChunk::_uiChunkCounter = 1;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SimpleSHLVariableChunk::initMethod(InitPhase ePhase)
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

SimpleSHLVariableChunk::SimpleSHLVariableChunk(void) :
    Inherited()
{
}

SimpleSHLVariableChunk::SimpleSHLVariableChunk(
    const SimpleSHLVariableChunk &source) :

    Inherited(source)
{
}

SimpleSHLVariableChunk::~SimpleSHLVariableChunk(void)
{
}

void SimpleSHLVariableChunk::onCreate(const SimpleSHLVariableChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void SimpleSHLVariableChunk::onCreateAspect(
    const SimpleSHLVariableChunk *createAspect,
    const SimpleSHLVariableChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

const StateChunkClass *SimpleSHLVariableChunk::getClass(void) const
{
    return &_class;
}

UInt16 SimpleSHLVariableChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void SimpleSHLVariableChunk::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         details)
{
    if(0x0000 != (whichField & VariablesFieldMask))
    {
        ShaderProgramVariables *pVars = _sfVariables.getValue();

        if(pVars != NULL)
        {
            if(details == 0x0001)
            {
                // be save reset all locations

                if(pVars->getMFVariables()->size() == 0)
                {
                    editMFVariableLocations()->clear();
                }
                else
                {
                    editMFVariableLocations()->resize(
                        pVars->getMFVariables()->size(), 
                        -1);

                    std::fill(editMFVariableLocations()->begin(),
                              editMFVariableLocations()->end  (),
                              -1);
                }
            }
        }
    }

    Inherited::changed(whichField, origin, details);
}

void SimpleSHLVariableChunk::dump(      UInt32    ,
                                  const BitVector ) const
{
    SLOG << "Dump SimpleSHLVariableChunk NI" << std::endl;
}

void SimpleSHLVariableChunk::activate(DrawEnv *pEnv, UInt32)
{
    updateVariables(pEnv);
}

void SimpleSHLVariableChunk::changeFrom(DrawEnv    *pEnv, 
                                        StateChunk *pOther, 
                                        UInt32            )
{
    SimpleSHLVariableChunk *pOld = 
        dynamic_cast<SimpleSHLVariableChunk *>(pOther);

    if(pOld == NULL)
    {
        FWARNING(( "SimpleSHLChunk::changeFrom: caught non-SHLChunk!\n"));
        return;
    }

    // SimpleSHLChunk didn't change so do nothing.
    if(pOld == this)
        return;

    updateVariables(pEnv);
}

void SimpleSHLVariableChunk::deactivate(DrawEnv *, UInt32)
{
}

void SimpleSHLVariableChunk::updateVariables(DrawEnv *pEnv)
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

        OSG_SHLVARIABLE_SWITCH
    }
}

OSG_END_NAMESPACE
