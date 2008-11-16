/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
const StateChunkClass *ShaderProgramVariableChunk::getStaticClass(void)
{
    return &ShaderProgramVariableChunk::_class;
}

inline
UInt32 ShaderProgramVariableChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

template<class ValueT> inline
bool ShaderProgramVariableChunk::addUniformVariable(const Char8  *name, 
                                                    const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

#if 0
    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        editMFVariableLocations(),
        NULL                     );
#else
    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        NULL,
        NULL);
#endif
}

template<class ValueT> inline
bool ShaderProgramVariableChunk::updateUniformVariable(const Char8  *name, 
                                                       const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateUniformVariable(name, value);
}

template<class ValueT>
bool ShaderProgramVariableChunk::getUniformVariable(const Char8  *name, 
                                                          ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        return _sfVariables.getValue()->getUniformVariable(name, value);
    }

    return false;
}

inline
UInt16 ShaderProgramVariableChunk::getVariableId(void)
{
    return _uiVarId;
}

inline
void ShaderProgramVariableChunk::addDestroyedFunctor(
    ChangedFunctor func,
    std::string    createSymbol)
{
    ChangedFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _mfDestroyedFunctors.push_back(oTmp);
}

template<class FunctorT> inline
void ShaderProgramVariableChunk::subDestroyedFunctor(FunctorT func)
{
    MFChangedFunctorCallback::iterator       cfIt = 
        _mfDestroyedFunctors.begin();

    MFChangedFunctorCallback::const_iterator cfEnd= 
        _mfDestroyedFunctors.end();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func == func)
            break;
    }

    if(cfIt != cfEnd)
        _mfDestroyedFunctors.erase(cfIt);
}

template<class FunctorT> inline
bool ShaderProgramVariableChunk::hasDestroyedFunctor(FunctorT func)
{
    bool returnValue = false;

    MFChangedFunctorCallback::iterator       cfIt = 
        _mfDestroyedFunctors.begin();

    MFChangedFunctorCallback::const_iterator cfEnd= 
        _mfDestroyedFunctors.end();


    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func == func)
        {
            returnValue = true;
            break;
        }
    }
    
    return returnValue;
}

inline 
void ShaderProgramVariableChunk::clearDestroyedFunctors(void)
{
    _mfDestroyedFunctors.clear();
}

OSG_END_NAMESPACE
