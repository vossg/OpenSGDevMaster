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

#include "OSGShaderProgramVariableChunk.h"

#include "OSGShaderVariables.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderProgramVariableChunkBase.cpp file.
// To modify it, please change the .fcd file 
// (OSGShaderProgramVariableChunk.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShaderProgramVariableChunk::_class("ShaderProgramVariable", 
                                                   1, 
                                                   5);

volatile UInt16 ShaderProgramVariableChunk::_uiChunkCounter = 1;

ShaderProgramVariableChunk::VarIdPool *
    ShaderProgramVariableChunk::_pVarIdPool = NULL;

template<> inline
void SimpleReusePool<Int32, 
                     ShaderProgramVariableChunk::VariableIdPoolTag, 
                     SingleLockPolicy                >::initializeValue(void)
{
    _currentValue = 1;
}

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProgramVariableChunk::initMethod(InitPhase ePhase)
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

ShaderProgramVariableChunk::ShaderProgramVariableChunk(void) :
     Inherited( ),
    _uiVarId  (0)
{
}

ShaderProgramVariableChunk::ShaderProgramVariableChunk(
    const ShaderProgramVariableChunk &source) :

     Inherited(source),
    _uiVarId  (0     )
{
}

ShaderProgramVariableChunk::~ShaderProgramVariableChunk(void)
{
}

void ShaderProgramVariableChunk::onCreate(
    const ShaderProgramVariableChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
    {
        _pVarIdPool = new VarIdPool;

        return;
    }

    _uiChunkId = _uiChunkCounter++;
    _uiVarId   = _pVarIdPool->create();

    markFieldsClusterLocal(ParentsFieldMask);
}

void ShaderProgramVariableChunk::onCreateAspect(
    const ShaderProgramVariableChunk *createAspect,
    const ShaderProgramVariableChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
    _uiVarId   = createAspect->_uiVarId;

    markFieldsClusterLocal(ParentsFieldMask);
}

void ShaderProgramVariableChunk::onDestroy(UInt32 uiId)
{
    Inherited::onDestroy(uiId);

    if(GlobalSystemState == OSG::Running)
    {
        _pVarIdPool->release(_uiVarId);
    }
    else if(GlobalSystemState == OSG::Shutdown)
    {
        delete _pVarIdPool;

        _pVarIdPool = NULL;
    }
}

const StateChunkClass *ShaderProgramVariableChunk::getClass(void) const
{
    return &_class;
}

UInt16 ShaderProgramVariableChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void ShaderProgramVariableChunk::changed(ConstFieldMaskArg whichField, 
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
                MFParentFieldContainerPtr::const_iterator parentsIt  = 
                    this->_mfParents.begin();
        
                MFParentFieldContainerPtr::const_iterator parentsEnd = 
                    this->_mfParents.end();
            
                for(; parentsIt != parentsEnd; ++parentsIt)
                {
                    (*parentsIt)->changed(
                        TypeTraits<BitVector>::One << 
                                               parentsIt.getParentFieldPos(),
                        ChangedOrigin::Child,
                        VariablesFieldMask);
                
                }
            }
        }
    }

    Inherited::changed(whichField, origin, details);
}


void ShaderProgramVariableChunk::addParent(
    FieldContainer * const pParent,
    UInt16                 uiParentFieldId)
{
    editMField(ParentsFieldMask, _mfParents);
    
    OSG_ASSERT(pParent != NULL);

    _mfParents.push_back(pParent, uiParentFieldId);
}

void ShaderProgramVariableChunk::subParent(FieldContainer * const pParent)
{
    Int32 iParentIdx = _mfParents.findIndex(pParent);

    if(iParentIdx != -1)
    {
        editMField(ParentsFieldMask, _mfParents);

        _mfParents.erase(iParentIdx);
    }
}

void ShaderProgramVariableChunk::dump(      UInt32    ,
                                      const BitVector ) const
{
    SLOG << "Dump ShaderProgramVariableChunk NI" << std::endl;
}

bool ShaderProgramVariableChunk::subUniformVariable(const Char8 *name)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->subUniformVariable(name, NULL, NULL);
    }
    else
    {
        return false;
    }
}

void ShaderProgramVariableChunk::clearUniformVariables(void)
{
    if(_sfVariables.getValue() == NULL)
    {
        _sfVariables.getValue()->clearUniformVariables();
    }
}

void ShaderProgramVariableChunk::activate(DrawEnv *pEnv, UInt32)
{
    fprintf(stderr, "ShaderProgramVariableChunk::activate\n");
}

void ShaderProgramVariableChunk::changeFrom(DrawEnv    *pEnv, 
                                            StateChunk *pOther, 
                                            UInt32            )
{
    fprintf(stderr, "ShaderProgramVariableChunk::changeFrom\n");
}

void ShaderProgramVariableChunk::deactivate(DrawEnv*, UInt32)
{
    fprintf(stderr, "ShaderProgramVariableChunk::deactivate\n");
}

void ShaderProgramVariableChunk::resolveLinks(void)
{
    MFChangedFunctorCallback::iterator       cfIt = 
        _mfDestroyedFunctors.begin();

    MFChangedFunctorCallback::const_iterator cfEnd= 
        _mfDestroyedFunctors.end();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func)
            (cfIt->_func)(this, 0x0000);
    }

    Inherited::resolveLinks();
}

OSG_END_NAMESPACE
