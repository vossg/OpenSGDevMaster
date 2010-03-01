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

#include "OSGConfig.h"
#include "OSGVolume.h"

#include <ostream>

//! helper functions to dump a volume. Useful for debugger.

OSG_BEGIN_NAMESPACE

void volDump(Volume *vol)
{
    vol->dump();
}

bool Volume::operator ==(const Volume &other) const
{
    return _state == other._state;
}

bool Volume::operator !=(const Volume &other) const
{
    return !(*this == other);
}

void Volume::printState(std::ostream &os) const
{
    os << "("
       << ((_state & OSGVALID)    ? "V" : "_")
       << ((_state & OSGEMPTY)    ? "E" : "_")
       << ((_state & OSGSTATIC)   ? "S" : "_")
       << ((_state & OSGINFINITE) ? "I" : "_")
       << ")";
}

std::ostream &operator<<(std::ostream &os, const Volume& vol)
{
    vol.print(os);

    return os;
}

OSG_END_NAMESPACE
