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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGShaderVariables.h"
#include "OSGShaderProgram.h"
#include "OSGGLFuncProtos.h"

OSG_BEGIN_NAMESPACE

void osgUniformShaderVariableSwitch(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    switch(pVar->getTypeId())
    {
    case ShaderVariable::SHVTypeBool:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableBool    (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeInt:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableInt     (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeReal:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableReal    (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeVec2f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableVec2f   (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeVec3f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableVec3f   (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeVec4f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableVec4f   (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypePnt2f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariablePnt2f   (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypePnt3f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariablePnt3f   (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMatrix:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMatrix  (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMInt:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMInt    (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMReal:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMReal   (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMVec2f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMVec2f  (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMVec3f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMVec3f  (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMVec4f:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMVec4f  (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeMMatrix:
        osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
        osgUniformShaderVariableMMatrix (pEnv, pVar, loc, uiProgram, warnUnknown);
        break;

    case ShaderVariable::SHVTypeOSG:
        // not handled here
        break;

    default:
        SWARNING << "Variable '" << pVar->getName() << "' has unknown type '"
                 << pVar->getTypeId() << "'."
                 << std::endl;
        break;
    }
}

void osgUniformShaderVariableLocation(
    DrawEnv *pEnv, ShaderVariable *pVar, Int32 &loc, UInt32 uiProgram)
{
    if(loc == -1)
    {
        OSGGETGLFUNC(OSGglGetUniformLocationProc,
                     osgGlGetUniformLocation,
                     ShaderProgram::getFuncIdGetUniformLocation());

        loc = osgGlGetUniformLocation(uiProgram, pVar->getName().c_str());
    }
}

void osgUniformShaderVariableBool(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableBool *p = dynamic_cast<ShaderVariableBool *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform1iProc,
                     osgGlUniform1i,
                     ShaderProgram::getFuncIdUniform1i());

        osgGlUniform1i(loc, GLint(p->getValue()));
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'bool' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableInt(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableInt *p = dynamic_cast<ShaderVariableInt *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform1iProc,
                     osgGlUniform1i,
                     ShaderProgram::getFuncIdUniform1i());

        osgGlUniform1i(loc, p->getValue());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'int' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableReal(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableReal *p = dynamic_cast<ShaderVariableReal *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform1fProc,
                     osgGlUniform1f,
                     ShaderProgram::getFuncIdUniform1f());

        osgGlUniform1f(loc, p->getValue());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'float' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableVec2f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableVec2f *p = dynamic_cast<ShaderVariableVec2f *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform2fvProc,
                     osgGlUniform2fv,
                     ShaderProgram::getFuncIdUniform2fv());

        osgGlUniform2fv(loc, 1, p->getValue().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec2f' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableVec3f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,               
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableVec3f *p = dynamic_cast<ShaderVariableVec3f *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform3fvProc,
                     osgGlUniform3fv,
                     ShaderProgram::getFuncIdUniform3fv());

        osgGlUniform3fv(loc, 1, p->getValue().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec3f' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableVec4f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableVec4f *p = dynamic_cast<ShaderVariableVec4f *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform4fvProc,
                     osgGlUniform4fv,
                     ShaderProgram::getFuncIdUniform4fv());

        osgGlUniform4fv(loc, 1, p->getValue().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec4f' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariablePnt2f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariablePnt2f *p = dynamic_cast<ShaderVariablePnt2f *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform2fvProc,
                     osgGlUniform2fv,
                     ShaderProgram::getFuncIdUniform2fv());

        osgGlUniform2fv(loc, 1, p->getValue().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'pnt2f' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariablePnt3f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariablePnt3f *p = dynamic_cast<ShaderVariablePnt3f *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniform3fvProc,
                     osgGlUniform3fv,
                     ShaderProgram::getFuncIdUniform3fv());

        osgGlUniform3fv(loc, 1, p->getValue().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'pnt3f' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMatrix(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMatrix *p = dynamic_cast<ShaderVariableMatrix *>(pVar);

    if(loc != -1)
    {
        OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                     osgGlUniformMatrix4fv,
                     ShaderProgram::getFuncIdUniformMatrix4fv());

        osgGlUniformMatrix4fv(loc,
                              1,
                              GL_FALSE,
                              p->getValue().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'matrix' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMInt(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMInt *p = dynamic_cast<ShaderVariableMInt *>(pVar);

    if(loc != -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC(OSGglUniform1ivProc,
                     osgGlUniform1iv,
                     ShaderProgram::getFuncIdUniform1iv());

        osgGlUniform1iv(  loc,
                          p->getMFValue()->size (),
                        &(p->getMFValue()->front()));
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'int []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMReal(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMReal *p = dynamic_cast<ShaderVariableMReal *>(pVar);

    if(loc != -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC(OSGglUniform1fvProc,
                     osgGlUniform1fv,
                     ShaderProgram::getFuncIdUniform1fv());

        osgGlUniform1fv(  loc,
                          p->getMFValue()->size (),
                        &(p->getMFValue()->front()));
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'real []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMVec2f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMVec2f *p = dynamic_cast<ShaderVariableMVec2f *>(pVar);

    if(loc != -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC(OSGglUniform2fvProc,
                     osgGlUniform2fv,
                     ShaderProgram::getFuncIdUniform2fv());

        osgGlUniform2fv(loc,
                        p->getMFValue()->size (),
                        p->getMFValue()->front().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec2f []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMVec3f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMVec3f *p = dynamic_cast<ShaderVariableMVec3f *>(pVar);

    if(loc != -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC(OSGglUniform3fvProc,
                     osgGlUniform3fv,
                     ShaderProgram::getFuncIdUniform3fv());

        osgGlUniform3fv(loc,
                        p->getMFValue()->size (),
                        p->getMFValue()->front().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec3f []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMVec4f(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMVec4f *p = dynamic_cast<ShaderVariableMVec4f *>(pVar);

    if(loc != -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC(OSGglUniform4fvProc,
                     osgGlUniform4fv,
                     ShaderProgram::getFuncIdUniform4fv());

        osgGlUniform4fv(loc,
                        p->getMFValue()->size (),
                        p->getMFValue()->front().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec4f []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

void osgUniformShaderVariableMMatrix(
    DrawEnv *pEnv,      ShaderVariable *pVar,       Int32 &loc,
    UInt32   uiProgram, bool            warnUnknown            )
{
    ShaderVariableMMatrix *p = dynamic_cast<ShaderVariableMMatrix *>(pVar);

    if(loc != -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                     osgGlUniformMatrix4fv,
                     ShaderProgram::getFuncIdUniformMatrix4fv());

        osgGlUniformMatrix4fv(loc,
                              p->getMFValue()->size (),
                              GL_FALSE,
                              p->getMFValue()->front().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'matrix []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

OSG_END_NAMESPACE
