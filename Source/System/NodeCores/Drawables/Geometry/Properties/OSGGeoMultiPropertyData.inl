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
UInt32 GeoMultiPropertyData::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

inline
const StateChunkClass *GeoMultiPropertyData::getStaticClass(void)
{
    return &GeoMultiPropertyData::_class;
}

inline
const UInt8 *GeoMultiPropertyData::getData(void) const
{
    return &_mfIData[0];
}

inline
UInt8 *GeoMultiPropertyData::editData(void)
{
    return &editIData(0);
}

inline 
void GeoMultiPropertyData::setSize(UInt32 size)
{
    editMFIData()->resize(size);
}

inline 
UInt32 GeoMultiPropertyData::getSize(void) const
{
    return getMFIData()->size();
}


OSG_END_NAMESPACE
