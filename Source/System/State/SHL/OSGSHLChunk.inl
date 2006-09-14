/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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
UInt32 SHLChunk::getFuncUniform1i(void)
{
    return _funcUniform1i;
}

inline
UInt32 SHLChunk::getFuncUniform2iv(void)
{
    return _funcUniform2iv;
}

inline
UInt32 SHLChunk::getFuncUniform3iv(void)
{
    return _funcUniform3iv;
}

inline
UInt32 SHLChunk::getFuncUniform4iv(void)
{
    return _funcUniform4iv;
}

inline
UInt32 SHLChunk::getFuncUniform1f(void)
{
    return _funcUniform1f;
}

inline
UInt32 SHLChunk::getFuncUniform2fv(void)
{
    return _funcUniform2fv;
}

inline
UInt32 SHLChunk::getFuncUniform3fv(void)
{
    return _funcUniform3fv;
}

inline
UInt32 SHLChunk::getFuncUniform4fv(void)
{
    return _funcUniform4fv;
}

inline
UInt32 SHLChunk::getFuncUniformMatrix4fv(void)
{
    return _funcUniformMatrix4fv;
}

inline
UInt32 SHLChunk::getFuncGetUniformiv(void)
{
    return _funcGetUniformiv;
}

inline
UInt32 SHLChunk::getFuncGetUniformfv(void)
{
    return _funcGetUniformfv;
}

inline
const StateChunkClass *SHLChunk::getStaticClass(void)
{
    return &SHLChunk::_class;
}

inline
UInt32 SHLChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

OSG_END_NAMESPACE

#define OSGSHLCHUNK_INLINE_CVSID "@(#)$Id$"
