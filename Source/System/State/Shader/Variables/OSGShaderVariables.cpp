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

OSG_BEGIN_NAMESPACE

void osgUniformShaderVariableSwitch(DrawEnv        *pEnv,      
                                    ShaderVariable *pVar,       
                                    Int32          &loc,
                                    UInt32          uiProgram, 
                                    bool            warnUnknown)
{
    switch(pVar->getTypeId())
    {
        case ShaderVariable::SHVTypeBool:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableBool    (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeInt:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableInt     (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeUInt:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableUInt    (pEnv, pVar, loc, uiProgram,
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeReal:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableReal    (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeVec2f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableVec2f   (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeVec3f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableVec3f   (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;
        
        case ShaderVariable::SHVTypeVec4f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableVec4f   (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypePnt2f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariablePnt2f   (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypePnt3f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariablePnt3f   (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
        break;

        case ShaderVariable::SHVTypeMatrix:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMatrix  (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeMInt:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMInt    (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

       case ShaderVariable::SHVTypeMUInt:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMUInt   (pEnv, pVar, loc, uiProgram,
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeMReal:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMReal   (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeMVec2f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMVec2f  (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeMVec3f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMVec3f  (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeMVec4f:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMVec4f  (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeMMatrix:
            osgUniformShaderVariableLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderVariableMMatrix (pEnv, pVar, loc, uiProgram, 
                                             warnUnknown               );
            break;

        case ShaderVariable::SHVTypeUniformBlock:
            osgUniformShaderUniformBlockLocation(pEnv, pVar, loc, uiProgram);
            osgUniformShaderUniformBlockBinding (pEnv, pVar, loc, uiProgram, 
                                                 warnUnknown               );
            break;

        case ShaderVariable::SHVTypeOSG:
            // not handled here
            break;

        default:
            SWARNING << "Variable '" 
                     << pVar->getName()   << "' has unknown type '"
                     << pVar->getTypeId() << "'."
                     << std::endl;
            break;
    }
}

OSG_END_NAMESPACE
