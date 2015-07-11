/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include <vector>
#include <algorithm>
#include <set>

#include "OSGConfig.h"
#include "OSGDgram.h"

OSG_USING_NAMESPACE

/** \class OSG::Dgram
 *  \brief Datagram used for reliable multicast
 *
 **/

/*-------------------------------------------------------------------------*/
/*             rivate constructor, destructor                              */

/*! constructor. Use Dgram::create to get dgrams
 */

Dgram::Dgram():
#ifdef OSG_DEBUG
    _uiUsageCounter(    0),
#endif
    _earlySend     (false),
    _size          (    0),
    _buffer        (NULL )
{
    _buffer = new DgramBuffer;

    memset(_buffer, 0, sizeof(DgramBuffer));
}

/*! destructor. Use Dgram::release to free dgrams
 */

Dgram::~Dgram()
{
    delete _buffer;
}
