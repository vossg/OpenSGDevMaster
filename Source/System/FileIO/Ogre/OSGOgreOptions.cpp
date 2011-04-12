/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGOgreOptions.h"
#include "OSGOgreLog.h"

OSG_BEGIN_NAMESPACE

OgreOptions::OgreOptions(void) :
    _loadAnimations(true),
    _loadSkeleton  (true)
{
}

OgreOptions::OgreOptions(const OptionSet &optSet) :
    _loadAnimations(true),
    _loadSkeleton  (true)
{
    parseOptions(optSet);
}

OgreOptions::~OgreOptions(void)
{
}

void OgreOptions::parseOptions(const OptionSet &optSet)
{
    OSG_OGRE_LOG(("OgreOptions::parseOptions\n"));

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "loadAnimations", _loadAnimations);
    IOFileTypeBase::getOptionAs<bool>(
        optSet, "loadSkeleton", _loadSkeleton);
}

bool OgreOptions::getLoadAnimations(void) const
{
    return _loadAnimations;
}

void OgreOptions::setLoadAnimations(bool value)
{
    _loadAnimations = value;
}

bool OgreOptions::getLoadSkeleton(void) const
{
    return _loadSkeleton;
}

void OgreOptions::setLoadSkeleton(bool value)
{
    _loadSkeleton = value;
}

OSG_END_NAMESPACE
