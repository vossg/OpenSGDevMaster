/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaOptions.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGIOFileTypeBase.h"

OSG_BEGIN_NAMESPACE

void
ColladaOptions::parseOptions(const OptionSet &optSet)
{
    OSG_COLLADA_LOG(("ColladaOptions::parseOptions\n"));

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "invertTransparency", _invertTransparency);
    IOFileTypeBase::getOptionAs<bool>(
        optSet, "mergeTransforms", _mergeTransforms);
    IOFileTypeBase::getOptionAs<bool>(
        optSet, "createNameAttachments", _createNameAttachments);
    IOFileTypeBase::getOptionAs<bool>(
        optSet, "loadAnimations", _loadAnimations);
}

/*! Return \c true if transparency values should be inverted, \c false
    otherwise. Option name: "invertTransparency".
    Some tools store transparency values inverted, use this to ensure correct
    display.
 */
bool
ColladaOptions::getInvertTransparency(void) const
{
    return _invertTransparency;
}

/*! Set transparency value inversion. Option name: "invertTransparency".
    Some tools store transparency values inverted, use this to ensure correct
    display.
 */
void
ColladaOptions::setInvertTransparency(bool value)
{
    _invertTransparency = value;
}

/*! Return \c true if transform tags within a single collada <node> tag
    should be merge, \c false if they should be preserved as individual
    Nodes in OpenSG.
 */
bool
ColladaOptions::getMergeTransforms(void) const
{
    return _mergeTransforms;
}

/*! Set if transform tags should be merged.
    Options name: "mergeTransforms".
 */
void
ColladaOptions::setMergeTransforms(bool value)
{
    _mergeTransforms = value;
}

/*! Return \c true if NameAttachments should be created, \c false otherwise.
    Option name: "createNameAttachments".
 */
bool
ColladaOptions::getCreateNameAttachments(void) const
{
    return _createNameAttachments;
}

/*! Set if NameAttachments should be created.
    Option name: "createNameAttachments".
 */
void
ColladaOptions::setCreateNameAttachments(bool value)
{
    _createNameAttachments = value;
}

bool
ColladaOptions::getLoadAnimations(void) const
{
    return _loadAnimations;
}

void
ColladaOptions::setLoadAnimations(bool value)
{
    _loadAnimations = value;
}

ColladaOptions::ColladaOptions(void)
    : Inherited             ()
    , _invertTransparency   (false)
    , _mergeTransforms      (true)
    , _createNameAttachments(true)
    , _loadAnimations       (true)
{
}

ColladaOptions::~ColladaOptions(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
