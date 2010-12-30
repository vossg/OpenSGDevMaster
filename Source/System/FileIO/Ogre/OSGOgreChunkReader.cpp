/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#include "OSGOgreChunkReader.h"
#include "OSGOgreLog.h"

#include <sstream>

OSG_BEGIN_NAMESPACE

const UInt32 OgreChunkReader::_chunkHeaderSize(sizeof(UInt16) + sizeof(UInt32));

/* explicit */
OgreChunkReader::OgreChunkReader(std::istream& is)
    : _header(),
      _is    (is)
{
}

/* virtual */
OgreChunkReader::~OgreChunkReader(void)
{
}

void
OgreChunkReader::readChunkHeader(std::istream& is)
{
    _header.chunkId   = readUInt16(is);
    _header.chunkSize = readUInt32(is);
}

void
OgreChunkReader::skip(std::istream& is, Int32 offset)
{
    is.seekg(offset, std::ios_base::cur);
}

std::string
OgreChunkReader::readString(std::istream& is)
{
    std::string        result;
    std::ostringstream oss;

    is.get(*oss.rdbuf(), '\n');
    is.get();                   // remove '\n'

    result = oss.str();

    if(result.empty() == false && result[result.length() - 1] == '\r')
    {
        result.erase(result.length() - 1);
    }

    return result;
}

bool
OgreChunkReader::readBool(std::istream& is)
{
    bool retVal;

    readBool(is, &retVal, 1);

    return retVal;
}

void
OgreChunkReader::readBool(std::istream& is, bool* values, UInt32 count)
{
    for(; count > 0; --count)
    {
        *values = is.get() != 0 ? true : false;
        ++values;
    }
}

Int16
OgreChunkReader::readInt16(std::istream& is)
{
    Int16 retVal;

    readInt16(is, &retVal, 1);

    return retVal;
}

void
OgreChunkReader::readInt16(std::istream& is, Int16* values, UInt32 count)
{
    is.read(reinterpret_cast<Char8 *>(values), count * sizeof(Int16));
}

UInt16
OgreChunkReader::readUInt16(std::istream& is)
{
    UInt16 retVal;

    readUInt16(is, &retVal, 1);

    return retVal;
}

void
OgreChunkReader::readUInt16(std::istream& is, UInt16* values, UInt32 count)
{
    is.read(reinterpret_cast<Char8 *>(values), count * sizeof(UInt16));
}

UInt32
OgreChunkReader::readUInt32(std::istream& is)
{
    UInt32 retVal;

    readUInt32(is, &retVal, 1);

    return retVal;
}

void
OgreChunkReader::readUInt32(std::istream& is, UInt32* values, UInt32 count)
{
    is.read(reinterpret_cast<Char8 *>(values), count * sizeof(UInt32));
}

Real32
OgreChunkReader::readReal32(std::istream& is)
{
    Real32 retVal;

    readReal32(is, &retVal, 1);

    return retVal;
}

void
OgreChunkReader::readReal32(std::istream& is, Real32* values, UInt32 count)
{
    is.read(reinterpret_cast<Char8 *>(values), count * sizeof(Real32));
}

OSG_END_NAMESPACE
