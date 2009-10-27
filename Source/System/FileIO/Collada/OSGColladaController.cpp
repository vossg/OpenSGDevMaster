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

#include "OSGColladaController.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domController.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaController::_regHelper(
    &ColladaController::create, "controller");


ColladaElementTransitPtr
ColladaController::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaController(elem, global));
}

void
ColladaController::read(void)
{
    OSG_COLLADA_LOG(("ColladaController::read\n"));

    domControllerRef controller = getDOMElementAs<domController>();
    domSkinRef       skin       = controller->getSkin();

    if(skin == NULL)
    {
        SWARNING << "ColladaController::read: No <skin>" << std::endl;
        return;
    }

    readSkin(skin);
}

Node *
ColladaController::createInstance(ColladaInstanceElement *colladaInstElem)
{
    OSG_COLLADA_LOG(("ColladaController::createInstance\n"));

    SWARNING << "ColladaController::createInstance: NIY" << std::endl;

    return NULL;
}

ColladaController::ColladaController(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaController::~ColladaController(void)
{
}

void
ColladaController::readSkin(domSkin *skin)
{
    SWARNING << "ColladaController::readSkin: NIY" << std::endl;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
