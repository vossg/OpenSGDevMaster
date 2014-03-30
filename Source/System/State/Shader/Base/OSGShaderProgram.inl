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
void ShaderProgram::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(getGLId(), pEnv);
}

inline
bool ShaderProgram::hasParameter(void)
{
    return _mfParameter.size() != 0;
}

inline
bool ShaderProgram::hasAttributes(void)
{
    return _mfAttributes.size() != 0;
}

template<class ValueT> inline
bool ShaderProgram::addUniformVariable(const Char8 *name, const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

#if 0
    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        editMFVariableLocations          (),
        editMFProceduralVariableLocations());
#else
    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        NULL,
        NULL);
#endif
}

template<class ValueT> inline
bool ShaderProgram::updateUniformVariable(const Char8  *name, 
                                          const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateUniformVariable(name, value);
}

template<class ValueT> inline
bool ShaderProgram::getUniformVariable(const Char8  *name,
                                             ValueT &value)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->getUniformVariable(name, value);
    }

    return false;
}

inline
bool ShaderProgram::addUniformBlock(const Char8 *name, UInt32 value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

#if 0
    return _sfVariables.getValue()->addUniformBlock(
        name, 
        value,
        editMFVariableLocations          (),
        editMFProceduralVariableLocations());
#else
    return _sfVariables.getValue()->addUniformBlock(
        name, 
        value,
        NULL,
        NULL);
#endif
}

inline
bool ShaderProgram::updateUniformBlock(const Char8  *name, UInt32 value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateUniformBlock(name, value);
}

inline
bool ShaderProgram::getUniformBlock(const Char8  *name, UInt32 &value)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->getUniformBlock(name, value);
    }

    return false;
}

inline
void ShaderProgram::addDestroyedFunctor(ChangedFunctor func,
                                        std::string    createSymbol)
{
    ChangedFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _mfDestroyedFunctors.push_back(oTmp);
}

template<class FunctorT> inline
void ShaderProgram::subDestroyedFunctor(FunctorT func)
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
bool ShaderProgram::hasDestroyedFunctor(FunctorT func)
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
UInt32 ShaderProgram::getNumDestroyedFunctors(void) const
{
    return _mfDestroyedFunctors.size32();
}

inline 
void ShaderProgram::clearDestroyedFunctors(void)
{
    _mfDestroyedFunctors.clear();
}

inline
UInt32 ShaderProgram::getExtIdSHL(void)
{
    return _extSHL;
}

inline
UInt32 ShaderProgram::getExtIdCgShader(void)
{
    return _extCG;
}

inline
UInt32 ShaderProgram::getExtIdGeometryShader4(void)
{
    return _extGeoShader4;
}

inline
UInt32 ShaderProgram::getExtIdGPUShader4(void)
{
    return _extGPUShader4;
}

inline
UInt32 ShaderProgram::getExtIdTransformFeedback2(void)
{
    return _extTransformFeedback2;
}

inline
UInt32 ShaderProgram::getExtIdUniformBufferObject(void)
{
    return _extUniformBufferObject;
}

inline
UInt32 ShaderProgram::getFuncIdCreateShader(void)
{
    return FuncIdCreateShader;
}

inline
UInt32 ShaderProgram::getFuncIdDeleteShader(void)
{
    return FuncIdDeleteShader;
}

inline
UInt32 ShaderProgram::getFuncIdShaderSource(void)
{
    return FuncIdShaderSource;
}

inline
UInt32 ShaderProgram::getFuncIdCompileShader(void)
{
    return FuncIdCompileShader;
}

inline
UInt32 ShaderProgram::getFuncIdAttachShader(void)
{
    return FuncIdAttachShader;
}

inline
UInt32 ShaderProgram::getFuncIdGetShaderiv(void)
{
    return FuncIdGetShaderiv;
}

inline
UInt32 ShaderProgram::getFuncIdGetShaderInfoLog(void)
{
    return FuncIdGetShaderInfoLog;
}

inline
UInt32 ShaderProgram::getFuncIdCreateProgram(void)
{
    return FuncIdCreateProgram;
}

inline
UInt32 ShaderProgram::getFuncIdDeleteProgram(void)
{
    return FuncIdDeleteProgram;
}

inline
UInt32 ShaderProgram::getFuncIdLinkProgram(void)
{
    return FuncIdLinkProgram;
}

inline
UInt32 ShaderProgram::getFuncIdGetProgramiv(void)
{
    return FuncIdGetProgramiv;
}

inline
UInt32 ShaderProgram::getFuncIdGetProgramInfoLog(void)
{
    return FuncIdGetProgramInfoLog;
}

inline
UInt32 ShaderProgram::getFuncIdUseProgram(void)
{
    return FuncIdUseProgram;
}


inline
UInt32 ShaderProgram::getFuncIdGetUniformLocation(void)
{
    return FuncIdGetUniformLocation;
}

inline
UInt32 ShaderProgram::getFuncIdUniform1i(void)
{
    return FuncIdUniform1i;
}

inline
UInt32 ShaderProgram::getFuncIdUniform2i(void)
{
    return FuncIdUniform2i;
}

inline
UInt32 ShaderProgram::getFuncIdUniform3i(void)
{
    return FuncIdUniform3i;
}

inline
UInt32 ShaderProgram::getFuncIdUniform4i(void)
{
    return FuncIdUniform4i;
}


inline
UInt32 ShaderProgram::getFuncIdUniform1ui(void)
{
    return FuncIdUniform1ui;
}

inline
UInt32 ShaderProgram::getFuncIdUniform2ui(void)
{
    return FuncIdUniform2ui;
}

inline
UInt32 ShaderProgram::getFuncIdUniform3ui(void)
{
    return FuncIdUniform3ui;
}

inline
UInt32 ShaderProgram::getFuncIdUniform4ui(void)
{
    return FuncIdUniform4ui;
}


inline
UInt32 ShaderProgram::getFuncIdUniform1f(void)
{
    return FuncIdUniform1f;
}

inline
UInt32 ShaderProgram::getFuncIdUniform2f(void)
{
    return FuncIdUniform2f;
}

inline
UInt32 ShaderProgram::getFuncIdUniform3f(void)
{
    return FuncIdUniform3f;
}

inline
UInt32 ShaderProgram::getFuncIdUniform4f(void)
{
    return FuncIdUniform4f;
}


inline
UInt32 ShaderProgram::getFuncIdUniform1iv(void)
{
    return FuncIdUniform1iv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform2iv(void)
{
    return FuncIdUniform2iv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform3iv(void)
{
    return FuncIdUniform3iv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform4iv(void)
{
    return FuncIdUniform4iv;
}


inline
UInt32 ShaderProgram::getFuncIdUniform1uiv(void)
{
    return FuncIdUniform1uiv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform2uiv(void)
{
    return FuncIdUniform2uiv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform3uiv(void)
{
    return FuncIdUniform3uiv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform4uiv(void)
{
    return FuncIdUniform4uiv;
}


inline
UInt32 ShaderProgram::getFuncIdUniform1fv(void)
{
    return FuncIdUniform1fv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform2fv(void)
{
    return FuncIdUniform2fv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform3fv(void)
{
    return FuncIdUniform3fv;
}

inline
UInt32 ShaderProgram::getFuncIdUniform4fv(void)
{
    return FuncIdUniform4fv;
}

inline
UInt32 ShaderProgram::getFuncIdUniformMatrix2fv(void)
{
    return FuncIdUniformMatrix2fv;
}

inline
UInt32 ShaderProgram::getFuncIdUniformMatrix3fv(void)
{
    return FuncIdUniformMatrix3fv;
}

inline
UInt32 ShaderProgram::getFuncIdUniformMatrix4fv(void)
{
    return FuncIdUniformMatrix4fv;
}

inline
UInt32 ShaderProgram::getFuncIdGetUniformiv(void)
{
    return FuncIdGetUniformiv;
}

inline
UInt32 ShaderProgram::getFuncIdGetUniformfv(void)
{
    return FuncIdGetUniformfv;
}

inline
UInt32 ShaderProgram::getFuncIdProgramParameteri(void)
{
    return FuncIdProgramParameteri;
}

inline
UInt32 ShaderProgram::getFuncIdBindAttribLocation(void)
{
    return FuncIdBindAttribLocation;
}

inline 
UInt32 ShaderProgram::getFuncIdBindBufferBase(void)
{
    return FuncIdBindBufferBase;
}

inline
UInt32 ShaderProgram::getFuncIdTransformFeedbackVaryings(void)
{
    return FuncIdTransformFeedbackVaryings;
}

inline
UInt32 ShaderProgram::getFuncIdBeginTransformFeedback(void)
{
    return FuncIdBeginTransformFeedback;
}

inline
UInt32 ShaderProgram::getFuncIdEndTransformFeedback(void)
{
    return FuncIdEndTransformFeedback;
}

inline
UInt32 ShaderProgram::getFuncIdPauseTransformFeedback(void)
{
    return FuncIdPauseTransformFeedback;
}

inline
UInt32 ShaderProgram::getFuncIdResumeTransformFeedback(void)
{
    return FuncIdResumeTransformFeedback;
}

inline
UInt32 ShaderProgram::getFuncIdGetUniformBlockIndex(void)
{
    return FuncIdGetUniformBlockIndex;
}

inline
UInt32 ShaderProgram::getFuncIdUniformBlockBinding(void)
{
    return FuncIdUniformBlockBinding;
}

inline
UInt16 ShaderProgram::getProgramId(void)
{
    return _uiProgId;
}

OSG_END_NAMESPACE
