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

#include "OSGColladaInstanceVisualScene.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaVisualScene.h"
#include "OSGColladaGlobal.h"

#include <dom/domInstanceWithExtra.h>
#include <dom/domVisual_scene.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceVisualScene::_regHelper(
    &ColladaInstanceVisualScene::create,
    "instance_visual_scene");

ColladaElementTransitPtr
ColladaInstanceVisualScene::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(
        new ColladaInstanceVisualScene(elem, global));
}

void
ColladaInstanceVisualScene::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceVisualScene::read\n"));

    ColladaVisualSceneRefPtr colVisScene = getTargetElem();

    if(colVisScene == NULL)
    {
        colVisScene = dynamic_pointer_cast<ColladaVisualScene>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colVisScene->read();
    }
}

FieldContainer *
ColladaInstanceVisualScene::process(ColladaElement *parent)
{
    ColladaVisualSceneRefPtr colVisScene = getTargetElem();

    getGlobal()->setRoot(colVisScene->createInstance(this));

    return NULL;
}

ColladaVisualScene *
ColladaInstanceVisualScene::getTargetElem(void) const
{
    ColladaVisualScene *retVal     = NULL;
    daeElementRef       targetElem = getTargetDOMElem();
 
    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaVisualScene>(targetElem);
    }

    return retVal;
}

domVisual_scene *
ColladaInstanceVisualScene::getTargetDOMElem(void) const
{
    domVisual_sceneRef      retVal       = NULL;
    domInstanceWithExtraRef instVisScene =
        getDOMElementAs<domInstanceWithExtra>();

    if(instVisScene->getUrl().getElement() != NULL)
    {
        retVal =
            daeSafeCast<domVisual_scene>(instVisScene->getUrl().getElement());
    }

    return retVal;
}

ColladaInstanceVisualScene::ColladaInstanceVisualScene(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceVisualScene::~ColladaInstanceVisualScene(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
