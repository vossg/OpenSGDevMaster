/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGSHADERVARIABLES_H_
#define _OSGSHADERVARIABLES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableBool.h"
#include "OSGShaderVariableInt.h"
#include "OSGShaderVariableReal.h"

#include "OSGShaderVariableVec2f.h"
#include "OSGShaderVariableVec3f.h"
#include "OSGShaderVariableVec4f.h"

#include "OSGShaderVariablePnt2f.h"
#include "OSGShaderVariablePnt3f.h"

#include "OSGShaderVariableMatrix.h"

#include "OSGShaderVariableMInt.h"
#include "OSGShaderVariableMReal.h"

#include "OSGShaderVariableMVec2f.h"
#include "OSGShaderVariableMVec3f.h"
#include "OSGShaderVariableMVec4f.h"

#include "OSGShaderVariableMMatrix.h"

#include "OSGShaderVariableOSG.h"

#define OSG_SHLVARIABLE_SWITCH                                          \
switch(pVar->getTypeId())                                               \
{                                                                       \
    case ShaderVariable::SHVTypeBool:                                   \
    {                                                                   \
        ShaderVariableBool *p =                                         \
            dynamic_cast<ShaderVariableBool *>(pVar);                   \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
                                                                        \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform1iProc,                            \
                         osgGlUniform1i,                                \
                         ShaderProgram::getFuncIdUniform1i());          \
                                                                        \
            osgGlUniform1i(*mLocIt, GLint(p->getValue()));              \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Variable '%s' not found in active uniform "      \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeInt:                                    \
    {                                                                   \
        ShaderVariableInt *p =                                          \
            dynamic_cast<ShaderVariableInt *>(pVar);                    \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
                                                                        \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform1iProc,                            \
                         osgGlUniform1i,                                \
                         ShaderProgram::getFuncIdUniform1i());          \
                                                                        \
            osgGlUniform1i(*mLocIt, p->getValue());                     \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Variable '%s' not found in active uniform "      \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeReal:                                   \
    {                                                                   \
        ShaderVariableReal *p =                                         \
            dynamic_cast<ShaderVariableReal *>(pVar);                   \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
                                                                        \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform1fProc,                            \
                         osgGlUniform1f,                                \
                         ShaderProgram::getFuncIdUniform1f());          \
                                                                        \
            osgGlUniform1f(*mLocIt, p->getValue());                     \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Variable '%s' not found in active uniform "      \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeVec2f:                                  \
    {                                                                   \
        ShaderVariableVec2f *p =                                        \
            dynamic_cast<ShaderVariableVec2f *>(pVar);                  \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform2fvProc,                           \
                         osgGlUniform2fv,                               \
                         ShaderProgram::getFuncIdUniform2fv());         \
                                                                        \
            osgGlUniform2fv(                                            \
                *mLocIt,                                                \
                1,                                                      \
                p->getValue().getValues());                             \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Variable '%s' not found in active uniform "      \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeVec3f:                                  \
    {                                                                   \
        ShaderVariableVec3f *p =                                        \
            dynamic_cast<ShaderVariableVec3f *>(pVar);                  \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform3fvProc,                           \
                         osgGlUniform3fv,                               \
                         ShaderProgram::getFuncIdUniform3fv());         \
                                                                        \
            osgGlUniform3fv(                                            \
                *mLocIt,                                                \
                1,                                                      \
                const_cast<Real32 *>(p->getValue().getValues()));       \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Variable '%s' not found in active uniform "      \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeVec4f:                                  \
    {                                                                   \
        ShaderVariableVec4f *p =                                        \
            dynamic_cast<ShaderVariableVec4f *>(pVar);                  \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform4fvProc,                           \
                         osgGlUniform4fv,                               \
                         ShaderProgram::getFuncIdUniform4fv());         \
                                                                        \
            osgGlUniform4fv(                                            \
                *mLocIt,                                                \
                1,                                                      \
                const_cast<Real32 *>(p->getValue().getValues()));       \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Parameter '%s' not found in active uniform "     \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypePnt2f:                                  \
    {                                                                   \
        ShaderVariablePnt2f *p =                                        \
            dynamic_cast<ShaderVariablePnt2f *>(pVar);                  \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform2fvProc,                           \
                         osgGlUniform2fv,                               \
                         ShaderProgram::getFuncIdUniform2fv());         \
                                                                        \
            osgGlUniform2fv(                                            \
                *mLocIt,                                                \
                1,                                                      \
                const_cast<Real32 *>(p->getValue().getValues()));       \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Parameter '%s' not found in active uniform "     \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypePnt3f:                                  \
    {                                                                   \
        ShaderVariablePnt3f *p =                                        \
            dynamic_cast<ShaderVariablePnt3f *>(pVar);                  \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
                                                                        \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform3fvProc,                           \
                         osgGlUniform3fv,                               \
                         ShaderProgram::getFuncIdUniform3fv());         \
                                                                        \
            osgGlUniform3fv(                                            \
                *mLocIt,                                                \
                1,                                                      \
                const_cast<Real32 *>(p->getValue().getValues()));       \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Parameter '%s' not found in active uniform "     \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMatrix:                                 \
    {                                                                   \
        ShaderVariableMatrix *p =                                       \
            dynamic_cast<ShaderVariableMatrix *>(pVar);                 \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglUniformMatrix4fvProc,                     \
                         osgGlUniformMatrix4fv,                         \
                         ShaderProgram::getFuncIdUniformMatrix4fv());   \
                                                                        \
            osgGlUniformMatrix4fv(                                      \
                *mLocIt,                                                \
                1,                                                      \
                GL_FALSE,                                               \
                const_cast<Real32 *>(p->getValue().getValues()));       \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Parameter '%s' not found in active uniform "     \
                      "variables of the shader!\n",                     \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMInt:                                   \
    {                                                                   \
        ShaderVariableMInt *p =                                         \
            dynamic_cast<ShaderVariableMInt *>(pVar);                   \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1 && !p->getMFValue()->empty())                  \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform1ivProc,                           \
                         osgGlUniform1iv,                               \
                         ShaderProgram::getFuncIdUniform1iv());         \
                                                                        \
            osgGlUniform1iv(*mLocIt,                                    \
                          p->getMFValue()->size(),                      \
                         &(p->getMFValue()->front()));                  \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Unknown parameter '%s'!\n",                      \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMReal:                                  \
    {                                                                   \
        ShaderVariableMReal *p =                                        \
            dynamic_cast<ShaderVariableMReal *>(pVar);                  \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1 && !p->getMFValue()->empty())                  \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform1fvProc,                           \
                         osgGlUniform1fv,                               \
                         ShaderProgram::getFuncIdUniform1fv());         \
                                                                        \
            osgGlUniform1fv(*mLocIt,                                    \
                         p->getMFValue()->size(),                       \
                         const_cast<Real32 *>(                          \
                             &(p->getMFValue()->front())));             \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Unknown parameter '%s'!\n",                      \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMVec2f:                                 \
    {                                                                   \
        ShaderVariableMVec2f *p =                                       \
            dynamic_cast<ShaderVariableMVec2f *>(pVar);                 \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1 && !p->getMFValue()->empty())                  \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform2fvProc,                           \
                         osgGlUniform2fv,                               \
                         ShaderProgram::getFuncIdUniform2fv());         \
                                                                        \
            osgGlUniform2fv(*mLocIt,                                    \
                         p->getMFValue()->size(),                       \
                         const_cast<Real32 *>(                          \
                             p->getMFValue()->front().getValues()));    \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Unknown parameter '%s'!\n",                      \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMVec3f:                                 \
    {                                                                   \
        ShaderVariableMVec3f *p =                                       \
            dynamic_cast<ShaderVariableMVec3f *>(pVar);                 \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1 && !p->getMFValue()->empty())                  \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform3fvProc,                           \
                         osgGlUniform3fv,                               \
                         ShaderProgram::getFuncIdUniform3fv());         \
                                                                        \
            osgGlUniform3fv(*mLocIt,                                    \
                         p->getMFValue()->size(),                       \
                         const_cast<Real32 *>(                          \
                             p->getMFValue()->front().getValues()));    \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Unknown parameter '%s'!\n",                      \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMVec4f:                                 \
    {                                                                   \
        ShaderVariableMVec4f *p =                                       \
            dynamic_cast<ShaderVariableMVec4f *>(pVar);                 \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1 && !p->getMFValue()->empty())                  \
        {                                                               \
            OSGGETGLFUNC(OSGglUniform4fvProc,                           \
                         osgGlUniform4fv,                               \
                         ShaderProgram::getFuncIdUniform4fv());         \
                                                                        \
            osgGlUniform4fv(*mLocIt,                                    \
                         p->getMFValue()->size(),                       \
                         const_cast<Real32 *>(                          \
                             p->getMFValue()->front().getValues()));    \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Unknown parameter '%s'!\n",                      \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeMMatrix:                                \
    {                                                                   \
        ShaderVariableMMatrix *p =                                      \
            dynamic_cast<ShaderVariableMMatrix *>(pVar);                \
                                                                        \
        if(*mLocIt == -1)                                               \
        {                                                               \
            OSGGETGLFUNC(OSGglGetUniformLocationProc,                   \
                         osgGlGetUniformLocation,                       \
                         ShaderProgram::getFuncIdGetUniformLocation()); \
                                                                        \
            *mLocIt = osgGlGetUniformLocation(uiProgram,                \
                                              p->getName().c_str());    \
        }                                                               \
        if(*mLocIt != -1 && !p->getMFValue()->empty())                  \
        {                                                               \
            OSGGETGLFUNC(OSGglUniformMatrix4fvProc,                     \
                         osgGlUniformMatrix4fv,                         \
                         ShaderProgram::getFuncIdUniformMatrix4fv());   \
                                                                        \
            osgGlUniformMatrix4fv(                                      \
                *mLocIt,                                                \
                p->getMFValue()->size(),                                \
                GL_FALSE,                                               \
                const_cast<Real32 *>(                                   \
                    p->getMFValue()->front().getValues()));             \
        }                                                               \
        else if(warnUnknown == true)                                    \
        {                                                               \
            FWARNING(("Unknown parameter '%s'!\n",                      \
                      p->getName().c_str()));                           \
        }                                                               \
    }                                                                   \
    break;                                                              \
                                                                        \
    case ShaderVariable::SHVTypeOSG:                                    \
    {                                                                   \
    }                                                                   \
                                                                        \
    default:                                                            \
        FWARNING(("Variable '%s' has unknown tpye %d!\n",               \
                  pVar->getName().c_str(),                              \
                  pVar->getTypeId()));                                  \
        break;                                                          \
}


#endif

