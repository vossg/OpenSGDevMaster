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
const StateChunkClass *ComputeShaderChunk::getStaticClass(void)
{
    return &ComputeShaderChunk::_class;
}

inline
UInt32 ComputeShaderChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

template<class ValueT> inline
bool ComputeShaderChunk::addUniformVariable(const Char8  *name, 
                                            const ValueT &value)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->addUniformVariable(
        name, 
        value,
        editMFVariableLocations          (),
        editMFProceduralVariableLocations());
}

template<class ValueT> inline
bool ComputeShaderChunk::updateUniformVariable(const Char8  *name, 
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

template<class ValueT>
bool ComputeShaderChunk::getUniformVariable(const Char8 *name, ValueT &value)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->getUniformVariable(name, value);
    }

    return false;
}

OSG_END_NAMESPACE
