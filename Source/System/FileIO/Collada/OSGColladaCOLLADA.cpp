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

#include "OSGColladaCOLLADA.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaScene.h"

#include <dom/domCOLLADA.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaCOLLADA::_regHelper(
    &ColladaCOLLADA::create, "COLLADA");


ColladaElementTransitPtr
ColladaCOLLADA::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaCOLLADA(elem, global));
}

void
ColladaCOLLADA::read(void)
{
    OSG_COLLADA_LOG(("ColladaCOLLADA::read\n"));

    domCOLLADARef collada  = getDOMElementAs<domCOLLADA>();
    domAssetRef   docAsset = collada->getAsset();

    if(docAsset != NULL)
    {
        domAsset::domContributor_Array &domContrA =
            docAsset->getContributor_array();

        for(UInt32 i = 0; i < domContrA.getCount(); ++i)
        {
            domAsset::domContributor::domAuthoring_toolRef docAuthTool =
                domContrA.get(i)->getAuthoring_tool();

            if(osgStringNCaseCmp(docAuthTool->getValue(),
                                 "Google SketchUp",
                                 15                     ) == 0)
            {
                SINFO << "ColladaCOLLADA::read: Detected Google SketchUp file "
                      << "enabling transparency workaround." << std::endl;

                getGlobal()->getOptions()->setInvertTransparency(true);
                break;
            }
        }
    }

    domCOLLADA::domSceneRef scene    = collada->getScene();
    ColladaSceneRefPtr      colScene = getUserDataAs<ColladaScene>(scene);

    if(colScene == NULL)
    {
        colScene = dynamic_pointer_cast<ColladaScene>(
            ColladaElementFactory::the()->create(scene, getGlobal()));

        colScene->read();
    }

    colScene->process();
}

ColladaCOLLADA::ColladaCOLLADA(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaCOLLADA::~ColladaCOLLADA(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
