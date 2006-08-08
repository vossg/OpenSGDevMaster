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
const StateChunkClass *ColorMaskChunk::getStaticClass(void)
{
    return &ColorMaskChunk::_class;
}

inline
UInt32 ColorMaskChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}


inline
void ColorMaskChunk::setMask(const bool &r,
                             const bool &g, 
                             const bool &b, 
                             const bool &a)
{
    editSField((MaskRFieldMask |
                MaskGFieldMask |
                MaskBFieldMask |
                MaskAFieldMask ));

    _sfMaskR.setValue(r);
    _sfMaskG.setValue(g);
    _sfMaskB.setValue(b);
    _sfMaskA.setValue(a);
}

OSG_END_NAMESPACE

#define OSGCOLORMASKCHUNK_INLINE_CVSID "@(#)$Id: $"

