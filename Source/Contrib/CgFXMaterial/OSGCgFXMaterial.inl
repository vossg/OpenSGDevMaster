/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

template<class ValueT> inline
bool CgFXMaterial::addUniformVariable(const Char8 *name, const ValueT &value)
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
        NULL,
        NULL);
}

inline
void CgFXMaterial::addVariable(ShaderVariable *pVar)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

    _sfVariables.getValue()->addVariable(pVar);
}

inline
const ShaderVariable *CgFXMaterial::getVariable(const Char8 *name) const
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->getVariable(name);
    }

    return NULL;
}

template<class ValueT> inline
bool CgFXMaterial::updateUniformVariable(const Char8  *name, 
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
bool CgFXMaterial::getUniformVariable(const Char8  *name,
                                            ValueT &value)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->getUniformVariable(name, value);
    }

    return false;
}

inline
CGeffect CgFXMaterial::getEffect(void) const
{
    return _pCGeffect;
}

inline
const std::string *CgFXMaterial::getStateVarNames(void) const
{
    return _vStateVarNames;
}

OSG_END_NAMESPACE

