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
UInt32 ShaderProgram::getFuncIdUniform1i(void)
{
    return SHLChunk::getFuncUniform1i();
}

inline
UInt32 ShaderProgram::getFuncIdUniform1f(void)
{
    return SHLChunk::getFuncUniform1f();
}

inline
UInt32 ShaderProgram::getFuncIdUniform1iv(void)
{
    return SHLChunk::getFuncUniform1iv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform2iv(void)
{
    return SHLChunk::getFuncUniform2iv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform3iv(void)
{
    return SHLChunk::getFuncUniform3iv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform4iv(void)
{
    return SHLChunk::getFuncUniform4iv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform1fv(void)
{
    return SHLChunk::getFuncUniform1fv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform2fv(void)
{
    return SHLChunk::getFuncUniform2fv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform3fv(void)
{
    return SHLChunk::getFuncUniform3fv();
}

inline
UInt32 ShaderProgram::getFuncIdUniform4fv(void)
{
    return SHLChunk::getFuncUniform4fv();
}

inline
UInt32 ShaderProgram::getFuncIdUniformMatrix4fv(void)
{
    return SHLChunk::getFuncUniformMatrix4fv();
}

inline
UInt32 ShaderProgram::getFuncIdGetUniformiv(void)
{
    return SHLChunk::getFuncGetUniformiv();
}

inline
UInt32 ShaderProgram::getFuncIdGetUniformfv(void)
{
    return SHLChunk::getFuncGetUniformfv();
}

OSG_END_NAMESPACE
