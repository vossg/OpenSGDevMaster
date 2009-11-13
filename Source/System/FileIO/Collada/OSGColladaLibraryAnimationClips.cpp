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

#include "OSGColladaLibraryAnimationClips.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaAnimationClip.h"

#include <dom/domLibrary_animation_clips.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaLibraryAnimationClips::_regHelper(
    &ColladaLibraryAnimationClips::create, "library_animation_clips");


ColladaElementTransitPtr
ColladaLibraryAnimationClips::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(
        new ColladaLibraryAnimationClips(elem, global));
}

void
ColladaLibraryAnimationClips::read(ColladaElement *colElemParent)
{
    domLibrary_animation_clipsRef  libAnimClips =
        getDOMElementAs<domLibrary_animation_clips>();
    const domAnimation_clip_Array &animClips    =
        libAnimClips->getAnimation_clip_array();

    for(UInt32 i = 0; i < animClips.getCount(); ++i)
    {
        ColladaAnimationClipRefPtr colAnimClip =
            getUserDataAs<ColladaAnimationClip>(animClips[i]);

        if(colAnimClip == NULL)
        {
            colAnimClip = dynamic_pointer_cast<ColladaAnimationClip>(
                ColladaElementFactory::the()->create(
                    animClips[i], getGlobal()));

            colAnimClip->read(this);
        }
    }
}

ColladaLibraryAnimationClips::ColladaLibraryAnimationClips(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaLibraryAnimationClips::~ColladaLibraryAnimationClips(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
