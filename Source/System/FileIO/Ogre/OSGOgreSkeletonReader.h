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

#ifndef _OSGOGRESKELETONREADER_H_
#define _OSGOGRESKELETONREADER_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGOgreSkeletonreader.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGOgreChunkReader.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING OgreSkeletonReader : public OgreChunkReader
{
   /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OgreChunkReader  Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    explicit  OgreSkeletonReader(std::istream& is);
    virtual  ~OgreSkeletonReader(void            );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    enum ChunkIds
    {
        CHUNK_HEADER                   = 0x1000,
        CHUNK_BONE                     = 0x2000,
        CHUNK_BONE_PARENT              = 0x3000,

        CHUNK_ANIMATION                = 0x4000,
        CHUNK_ANIMATION_TRACK          = 0x4100,
        CHUNK_ANIMATION_TRACK_KEYFRAME = 0x4110,
        CHUNK_ANIMATION_LINK           = 0x5000
    };
};

OSG_END_NAMESPACE

#endif // _OSGOGRESKELETONREADER_H_
