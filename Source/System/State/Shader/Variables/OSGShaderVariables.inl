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

OSG_BEGIN_NAMESPACE

inline
void osgUniformShaderVariableLocation(DrawEnv        *pEnv, 
                                      ShaderVariable *pVar, 
                                      Int32          &loc, 
                                      UInt32          uiProgram)
{
    if(loc == -1)
    {
        OSGGETGLFUNC_GL3_ES(glGetUniformLocation,
                            osgGlGetUniformLocation,
                            ShaderProgram::getFuncIdGetUniformLocation());

        loc = osgGlGetUniformLocation(uiProgram, pVar->getName().c_str());
#ifdef OSG_MULTISHADER_VARCHUNK
        if(loc == -1)
            loc = -2;
#endif
     }
}

inline
void osgUniformShaderVariableBool(DrawEnv        *pEnv,      
                                  ShaderVariable *pVar,       
                                  Int32          &loc,
                                  UInt32          uiProgram, 
                                  bool            warnUnknown)
{
    ShaderVariableBool *p = dynamic_cast<ShaderVariableBool *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform1i,
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

inline
void osgUniformShaderVariableInt(DrawEnv        *pEnv,      
                                 ShaderVariable *pVar,       
                                 Int32          &loc,
                                 UInt32          uiProgram, 
                                 bool            warnUnknown)
{
    ShaderVariableInt *p = dynamic_cast<ShaderVariableInt *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform1i,
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

inline
void osgUniformShaderVariableUInt(DrawEnv        *pEnv,
                                  ShaderVariable *pVar,
                                  Int32          &loc,
                                  UInt32          uiProgram,
                                  bool            warnUnknown)
{
    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdGPUShader4(), 0x0303, 0x0200))
    {
        SWARNING << "Uniforms of type 'uint' are not supported, could not "
                 << "find extension 'EXT_gpu_shader4'!"
                 << std::endl;
        return;
    }

    ShaderVariableUInt *p = dynamic_cast<ShaderVariableUInt *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform1ui,
                            osgGlUniform1ui,
                            ShaderProgram::getFuncIdUniform1ui());

        osgGlUniform1ui(loc, p->getValue());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'uint' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableReal(DrawEnv        *pEnv,      
                                  ShaderVariable *pVar,       
                                  Int32          &loc,
                                  UInt32          uiProgram, 
                                  bool            warnUnknown)
{
    ShaderVariableReal *p = dynamic_cast<ShaderVariableReal *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform1f,
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

inline
void osgUniformShaderVariableVec2f(DrawEnv        *pEnv,      
                                   ShaderVariable *pVar,       
                                   Int32          &loc,
                                   UInt32          uiProgram, 
                                   bool            warnUnknown)
{
    ShaderVariableVec2f *p = dynamic_cast<ShaderVariableVec2f *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform2fv,
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

inline
void osgUniformShaderVariableVec3f(DrawEnv        *pEnv,      
                                   ShaderVariable *pVar,       
                                   Int32          &loc,               
                                   UInt32          uiProgram, 
                                   bool            warnUnknown)
{
    ShaderVariableVec3f *p = dynamic_cast<ShaderVariableVec3f *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform3fv,
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

inline
void osgUniformShaderVariableVec4f(DrawEnv        *pEnv,      
                                   ShaderVariable *pVar,       
                                   Int32          &loc,
                                   UInt32          uiProgram, 
                                   bool            warnUnknown)
{
    ShaderVariableVec4f *p = dynamic_cast<ShaderVariableVec4f *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform4fv,
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

inline
void osgUniformShaderVariablePnt2f(DrawEnv        *pEnv,      
                                   ShaderVariable *pVar,       
                                   Int32          &loc,
                                   UInt32          uiProgram, 
                                   bool            warnUnknown)
{
    ShaderVariablePnt2f *p = dynamic_cast<ShaderVariablePnt2f *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform2fv,
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

inline
void osgUniformShaderVariablePnt3f(DrawEnv        *pEnv,      
                                   ShaderVariable *pVar,       
                                   Int32          &loc,
                                   UInt32          uiProgram, 
                                   bool            warnUnknown)
{
    ShaderVariablePnt3f *p = dynamic_cast<ShaderVariablePnt3f *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniform3fv,
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

inline
void osgUniformShaderVariableMatrix(DrawEnv        *pEnv,      
                                    ShaderVariable *pVar,       
                                    Int32          &loc,
                                    UInt32          uiProgram, 
                                    bool            warnUnknown)
{
    ShaderVariableMatrix *p = dynamic_cast<ShaderVariableMatrix *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniformMatrix4fv,
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

inline
void osgUniformShaderVariableMInt(DrawEnv        *pEnv,      
                                  ShaderVariable *pVar,       
                                  Int32          &loc,
                                  UInt32          uiProgram, 
                                  bool            warnUnknown)
{
    ShaderVariableMInt *p = dynamic_cast<ShaderVariableMInt *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniform1iv,
                            osgGlUniform1iv,
                            ShaderProgram::getFuncIdUniform1iv());
        
        osgGlUniform1iv(  loc,
                          p->getMFValue()->size32(),
                        &(p->getMFValue()->front ()));
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'int []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableMUInt(DrawEnv        *pEnv,
                                   ShaderVariable *pVar,
                                   Int32          &loc,
                                   UInt32          uiProgram,
                                   bool            warnUnknown)
{
    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdGPUShader4(), 0x0303, 0x0200))
    {
        SWARNING << "Uniforms of type 'uint' are not supported, could not "
                 << "find extension 'EXT_gpu_shader4'!"
                 << std::endl;
        return;
    }

    ShaderVariableMUInt *p = dynamic_cast<ShaderVariableMUInt *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniform1uiv,
                            osgGlUniform1uiv,
                            ShaderProgram::getFuncIdUniform1uiv());

        osgGlUniform1uiv(  loc,
                           p->getMFValue()->size32(),
                         &(p->getMFValue()->front ()));
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'uint []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableMReal(DrawEnv        *pEnv,      
                                   ShaderVariable *pVar,       
                                   Int32          &loc,
                                   UInt32          uiProgram, 
                                   bool            warnUnknown)
{
    ShaderVariableMReal *p = dynamic_cast<ShaderVariableMReal *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniform1fv,
                            osgGlUniform1fv,
                            ShaderProgram::getFuncIdUniform1fv());

        osgGlUniform1fv(  loc,
                          p->getMFValue()->size32(),
                        &(p->getMFValue()->front ()));
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'real []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableMVec2f(DrawEnv        *pEnv,      
                                    ShaderVariable *pVar,       
                                    Int32          &loc,
                                    UInt32          uiProgram, 
                                    bool            warnUnknown)
{
    ShaderVariableMVec2f *p = dynamic_cast<ShaderVariableMVec2f *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniform2fv,
                            osgGlUniform2fv,
                            ShaderProgram::getFuncIdUniform2fv());

        osgGlUniform2fv(loc,
                        p->getMFValue()->size32(),
                        p->getMFValue()->front ().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec2f []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableMVec3f(DrawEnv        *pEnv,      
                                    ShaderVariable *pVar,       
                                    Int32          &loc,
                                    UInt32          uiProgram, 
                                    bool            warnUnknown)
{
    ShaderVariableMVec3f *p = dynamic_cast<ShaderVariableMVec3f *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniform3fv,
                            osgGlUniform3fv,
                            ShaderProgram::getFuncIdUniform3fv());

        osgGlUniform3fv(loc,
                        p->getMFValue()->size32(),
                        p->getMFValue()->front ().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec3f []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableMVec4f(DrawEnv        *pEnv,      
                                    ShaderVariable *pVar,       
                                    Int32          &loc,
                                    UInt32          uiProgram, 
                                    bool            warnUnknown)
{
    ShaderVariableMVec4f *p = dynamic_cast<ShaderVariableMVec4f *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniform4fv,
                            osgGlUniform4fv,
                            ShaderProgram::getFuncIdUniform4fv());

        osgGlUniform4fv(loc,
                        p->getMFValue()->size32(),
                        p->getMFValue()->front ().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'vec4f []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderVariableMMatrix(DrawEnv        *pEnv,      
                                     ShaderVariable *pVar,       
                                     Int32          &loc,
                                     UInt32          uiProgram, 
                                     bool            warnUnknown)
{
    ShaderVariableMMatrix *p = dynamic_cast<ShaderVariableMMatrix *>(pVar);

    if(loc > -1 && !p->getMFValue()->empty())
    {
        OSGGETGLFUNC_GL3_ES(glUniformMatrix4fv,
                            osgGlUniformMatrix4fv,
                            ShaderProgram::getFuncIdUniformMatrix4fv());

        osgGlUniformMatrix4fv(loc,
                              p->getMFValue()->size32(),
                              GL_FALSE,
                              p->getMFValue()->front ().getValues());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Variable '" << p->getName() << "' type 'matrix []' "
                 << "not found in active uniform "
                 << "variables of shader program '" << uiProgram << "'"
                 << std::endl;
    }
}

inline
void osgUniformShaderUniformBlockLocation(DrawEnv        *pEnv, 
                                          ShaderVariable *pVar, 
                                          Int32          &loc, 
                                          UInt32          uiProgram)
{
    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdUniformBufferObject(), 0x0201, 0x0200))
    {
        SWARNING << "Uniform blocks are not supported, could not "
                 << "find extension 'GL_ARB_uniform_buffer_object'!"
                 << std::endl;
        return;
    }

    if(loc == -1)
    {
        OSGGETGLFUNC_GL3_ES(glGetUniformBlockIndex,
                            osgGlGetUniformBlockIndex,
                            ShaderProgram::getFuncIdGetUniformBlockIndex());

        loc = osgGlGetUniformBlockIndex(uiProgram, pVar->getName().c_str());
#ifdef OSG_MULTISHADER_VARCHUNK
        if(loc == -1)
            loc = -2;
#endif
     }
}

inline
void osgUniformShaderUniformBlockBinding(DrawEnv        *pEnv,
                                         ShaderVariable *pVar,
                                         Int32          &loc,
                                         UInt32          uiProgram,
                                         bool            warnUnknown)
{
    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdUniformBufferObject(), 0x0201, 0x0200))
    {
        SWARNING << "Uniform blocks are not supported, could not "
                 << "find extension 'GL_ARB_uniform_buffer_object'!"
                 << std::endl;
        return;
    }

    ShaderVariableUniformBlock *p = dynamic_cast<ShaderVariableUniformBlock *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glUniformBlockBinding,
                            osgGlUniformBlockBinding,
                            ShaderProgram::getFuncIdUniformBlockBinding());

        osgGlUniformBlockBinding(uiProgram, loc, p->getValue());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Block '" << p->getName() << "'" 
                 << "not found in active shader program '" << uiProgram << "'" 
                 << std::endl;
    }
}

inline
void osgUniformShaderStorageBlockLocation(DrawEnv        *pEnv, 
                                          ShaderVariable *pVar, 
                                          Int32          &loc, 
                                          UInt32          uiProgram)
{
    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdProgramInterfaceQuery(), 0x0402))
    {
        SWARNING << "Shader Storage are not supported, could not "
                 << "find extension 'GL_ARB_program_interface_query'!"
                 << std::endl;
        return;
    }

    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdShaderStorageBufferObject(), 0x0403))
    {
        SWARNING << "Shader Storage are not supported, could not "
                 << "find extension 'GL_ARB_shader_storage_buffer_object'!"
                 << std::endl;
        return;
    }

    if(loc == -1)
    {
        OSGGETGLFUNC_GL3_ES(glGetProgramResourceIndex,
                            osgGlGetProgramResourceIndex,
                            ShaderProgram::getFuncIdGetProgramResourceIndex());

        loc = osgGlGetProgramResourceIndex(uiProgram, GL_SHADER_STORAGE_BLOCK, pVar->getName().c_str());
#ifdef OSG_MULTISHADER_VARCHUNK
        if(loc == -1)
            loc = -2;
#endif
     }
}

inline
void osgUniformShaderStorageBlockBinding(DrawEnv        *pEnv,
                                         ShaderVariable *pVar,
                                         Int32          &loc,
                                         UInt32          uiProgram,
                                         bool            warnUnknown)
{
    if(!pEnv->getWindow()->hasExtOrVersion(
        ShaderProgram::getExtIdShaderStorageBufferObject(), 0x0403))
    {
        SWARNING << "Shader Storage blocks are not supported, could not "
                 << "find extension 'GL_ARB_shader_storage_buffer_object'!"
                 << std::endl;
        return;
    }

    ShaderVariableShaderStorageBlock *p = dynamic_cast<ShaderVariableShaderStorageBlock *>(pVar);

    if(loc > -1)
    {
        OSGGETGLFUNC_GL3_ES(glShaderStorageBlockBinding,
                            osgGlShaderStorageBlockBinding,
                            ShaderProgram::getFuncIdShaderStorageBlockBinding());

        osgGlShaderStorageBlockBinding(uiProgram, loc, p->getValue());
    }
    else if(warnUnknown == true)
    {
        SWARNING << "Block '" << p->getName() << "'" 
                 << "not found in active shader program '" << uiProgram << "'" 
                 << std::endl;
    }
}

OSG_END_NAMESPACE
