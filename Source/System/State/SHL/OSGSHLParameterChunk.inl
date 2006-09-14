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
const StateChunkClass *SHLParameterChunk::getStaticClass(void)
{
    return &SHLParameterChunk::_class;
}

inline
UInt32 SHLParameterChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

inline
void SHLParameterChunk::updateParameters(Window *win)
{
    SHLChunkPtr shl = getSHLChunk();

    if(shl == NullFC)
    {
        FWARNING(("SHLParameterChunk: SHLChunk == NullFC, call "
                  "setSHLChunk()\n"));

        return;
    }

    shl->updateParameters(win, getParameters(), true, true, true);
}

OSG_END_NAMESPACE

#define OSGSHLPARAMETERCHUNK_INLINE_CVSID "@(#)$Id$"
