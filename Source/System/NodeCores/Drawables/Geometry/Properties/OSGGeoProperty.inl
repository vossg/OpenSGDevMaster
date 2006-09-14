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


inline UInt32 GeoProperty::getSize(void) const
{
    return size();
}

inline
UInt32 GeoProperty::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

inline
const StateChunkClass *GeoProperty::getStaticClass(void)
{
    return &GeoProperty::_class;
}


inline
UInt32 GeoProperty::MapFormatToSize(GLenum format)
{
    static UInt32 sizes[] = { 1, 1, 2, 2, 4, 4, 4, 2, 3, 4, 8, 2};
    
    UInt32 ind = format - GL_BYTE;
    
    if (ind >= sizeof(sizes)/sizeof(UInt32))
    {
        return 0x12345678;
    }
    
    return sizes[ind];
}

OSG_END_NAMESPACE

#define OSGGEOPROPERTY_INLINE_CVSID "@(#)$Id$"

