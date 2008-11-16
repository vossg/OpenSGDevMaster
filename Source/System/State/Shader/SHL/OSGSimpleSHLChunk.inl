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
const StateChunkClass *SimpleSHLChunk::getStaticClass(void)
{
    return &SimpleSHLChunk::_class;
}

inline
UInt32 SimpleSHLChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

#ifdef OSG_1_COMPAT
template<class ValueT> inline
bool SimpleSHLChunk::setUniformParameter(const Char8 *name, const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        editMFVariableLocations          (),
        editMFProceduralVariableLocations());
}
#endif

template<class ValueT> inline
bool SimpleSHLChunk::addUniformVariable(const Char8 *name, const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        editMFVariableLocations          (),
        editMFProceduralVariableLocations());
}

template<class ValueT> inline
bool SimpleSHLChunk::updateUniformVariable(const Char8 *name, 
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
bool SimpleSHLChunk::getUniformVariable(const Char8 *name, ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        return _sfVariables.getValue()->getUniformVariable(name, value);
    }

    return false;
}


#ifdef OSG_1_COMPAT
inline
UInt32 SimpleSHLChunk::getFuncUniform1i(void)
{
    return ShaderProgram::getFuncIdUniform1i();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform1iv(void)
{
    return ShaderProgram::getFuncIdUniform1iv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform2iv(void)
{
    return ShaderProgram::getFuncIdUniform2iv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform3iv(void)
{
    return ShaderProgram::getFuncIdUniform3iv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform4iv(void)
{
    return ShaderProgram::getFuncIdUniform4iv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform1f(void)
{
    return ShaderProgram::getFuncIdUniform1f();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform1fv(void)
{
    return ShaderProgram::getFuncIdUniform1fv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform2fv(void)
{
    return ShaderProgram::getFuncIdUniform2fv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform3fv(void)
{
    return ShaderProgram::getFuncIdUniform3fv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniform4fv(void)
{
    return ShaderProgram::getFuncIdUniform4fv();
}

inline
UInt32 SimpleSHLChunk::getFuncUniformMatrix4fv(void)
{
    return ShaderProgram::getFuncIdUniformMatrix4fv();
}

inline
UInt32 SimpleSHLChunk::getFuncGetUniformiv(void)
{
    return ShaderProgram::getFuncIdGetUniformiv();
}

inline
UInt32 SimpleSHLChunk::getFuncGetUniformfv(void)
{
    return ShaderProgram::getFuncIdGetUniformfv();
}
#endif

OSG_END_NAMESPACE
