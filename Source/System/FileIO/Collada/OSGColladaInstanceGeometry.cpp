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

#include "OSGColladaInstanceGeometry.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"

#include <dom/domInstance_geometry.h>
#include <dom/domInstance_material.h>
#include <dom/domBind_material.h>
#include <dom/domParam.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceGeometry::_regHelper(
    &ColladaInstanceGeometry::create, "instance_geometry");


ColladaElementTransitPtr
ColladaInstanceGeometry::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceGeometry(elem, global));
}

void
ColladaInstanceGeometry::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read\n"));

    ColladaGeometryRefPtr colGeo = getTargetElem();

    if(colGeo == NULL)
    {
        colGeo = dynamic_pointer_cast<ColladaGeometry>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colGeo->read();
    }

    domInstance_geometryRef instGeo = getDOMElementAs<domInstance_geometry>();
    domBind_materialRef     bindMat = instGeo->getBind_material            ();

    if(bindMat == NULL)
    {
        SWARNING << "ColladaInstanceGeometry::read: No <bind_material> found."
                 << std::endl;
        return;
    }

    domBind_material::domTechnique_commonRef  techCom      =
        bindMat->getTechnique_common();
    const domInstance_material_Array         &instMatArray =
        techCom->getInstance_material_array();

    for(UInt32 i = 0; i < instMatArray.getCount(); ++i)
    {
        ColladaInstanceMaterialRefPtr colInstMat =
            getUserDataAs<ColladaInstanceMaterial>(instMatArray[i]);

        if(colInstMat == NULL)
        {
            colInstMat = dynamic_pointer_cast<ColladaInstanceMaterial>(
                ColladaElementFactory::the()->create(
                    instMatArray[i], getGlobal()));

            colInstMat->read();
        }

        _matMap[colInstMat->getSymbol()] = colInstMat;

        OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: binding symbol [%s] "
                         "to target [%s]\n",
                         colInstMat->getSymbol().c_str(),
                         instMatArray[i]->getTarget().getURI()));
    }

    const domParam_Array &params = bindMat->getParam_array();

    if(params.getCount() > 0)
    {
        SWARNING << "ColladaInstanceGeometry::read: Ignoring ["
                 << params.getCount() << "] <param> elements."
                 << std::endl;
    }
}

Node *
ColladaInstanceGeometry::process(ColladaElement *parent)
{
    OSG_COLLADA_LOG(("ColladaInstanceGeometry::process\n"));

    ColladaGeometryRefPtr colGeo = getTargetElem();

    return colGeo->createInstance(this);
}

ColladaGeometry *
ColladaInstanceGeometry::getTargetElem(void) const
{
    ColladaGeometry *retVal     = NULL;
    daeElementRef    targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaGeometry>(targetElem);
    }

    return retVal;
}

daeElement *
ColladaInstanceGeometry::getTargetDOMElem(void) const
{
    domGeometryRef          retVal  = NULL;
    domInstance_geometryRef instGeo = getDOMElementAs<domInstance_geometry>();

    if(instGeo->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domGeometry>(instGeo->getUrl().getElement());
    }

    return retVal;
}

const ColladaInstanceGeometry::MaterialMap &
ColladaInstanceGeometry::getMaterialMap(void) const
{
    return _matMap;
}

ColladaInstanceGeometry::ColladaInstanceGeometry(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
    , _matMap  ()
{
}

ColladaInstanceGeometry::~ColladaInstanceGeometry(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
