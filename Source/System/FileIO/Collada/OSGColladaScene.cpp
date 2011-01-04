/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
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

#include "OSGColladaScene.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaInstanceVisualScene.h"

#include <dom/domCOLLADA.h>
#include <dom/domInstanceWithExtra.h>

/*! \class OSG::ColladaScene
    Handles the &lt;scene&gt; tag.
 */

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaScene::_regHelper(
    &ColladaScene::create, "scene");


ColladaElementTransitPtr
ColladaScene::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaScene(elem, global));
}

void
ColladaScene::read(void)
{
    OSG_COLLADA_LOG(("ColladaScene::read\n"));

    domCOLLADA::domSceneRef scene = getDOMElementAs<domCOLLADA::domScene>();

    OSG_ASSERT(scene != NULL);

    domInstanceWithExtraRef instVisScene = scene->getInstance_visual_scene();

    if(instVisScene != NULL)
    {
        _colInstVisScene = dynamic_pointer_cast<ColladaInstanceVisualScene>(
            ColladaElementFactory::the()->create(instVisScene, getGlobal()));

        _colInstVisScene->read();
    }
    else
    {
        SWARNING << "ColladaScene::read: No <instance_visual_scene> tag."
                 << std::endl;
    }
}

void
ColladaScene::process(void)
{
    _colInstVisScene->process(this);
}

ColladaScene::ColladaScene(daeElement *elem, ColladaGlobal *global)
    : Inherited       (elem, global)
    , _colInstVisScene(NULL        )
{
}

ColladaScene::~ColladaScene(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
