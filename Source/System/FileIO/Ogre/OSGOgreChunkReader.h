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

#ifndef _OSGOGRECHUNKREADER_H_
#define _OSGOGRECHUNKREADER_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGOgreChunkreader.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING OgreChunkReader
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    explicit  OgreChunkReader(std::istream& is);
    virtual  ~OgreChunkReader(void            ) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    struct ChunkHeader
    {
        UInt16 chunkId;
        UInt32 chunkSize;
    };

    void readChunkHeader(std::istream& is);

    void skip(std::istream& is, Int32 offset);

    std::string readString (std::istream& is);

    bool   readBool  (std::istream& is);
    void   readBool  (std::istream& is, bool* values, UInt32 count);

    Int16  readInt16 (std::istream& is);
    void   readInt16 (std::istream& is, Int16* values, UInt32 count);

    UInt16 readUInt16(std::istream& is);
    void   readUInt16(std::istream& is, UInt16* values, UInt32 count);

    UInt32 readUInt32(std::istream& is);
    void   readUInt32(std::istream& is, UInt32* values, UInt32 count);

    Real32 readReal32(std::istream& is);
    void   readReal32(std::istream& is, Real32* values, UInt32 count);

    static const UInt32 _chunkHeaderSize;

    ChunkHeader         _header;
    std::istream&       _is;
};

OSG_END_NAMESPACE

#endif // _OSGOGRECHUNKREADER_H_
