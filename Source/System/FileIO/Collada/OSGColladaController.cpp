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
#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceController.h"
#include "OSGGroup.h"
#include "OSGNameAttachment.h"

#include <dom/domController.h>
#include <dom/domGeometry.h>

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
ColladaController::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaController::createInstance\n"));

    typedef ColladaInstanceController::MaterialMap        MaterialMap;
    typedef ColladaInstanceController::MaterialMapConstIt MaterialMapConstIt;

    domControllerRef ctrl   = getDOMElementAs<domController>();
    NodeUnrecPtr     groupN = makeCoredNode<Group>();

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
       ctrl->getName()                                       != NULL   )
    {
        setName(groupN, ctrl->getName());
    }

    ColladaInstanceControllerRefPtr  colInstCtrl =
        dynamic_cast<ColladaInstanceController *>(colInstElem);
    const MaterialMap               &matMap      =
        colInstCtrl->getMaterialMap();


        // iterate over all parts of geometry
    GeoStoreIt gsIt   = _geoStore.begin();
    GeoStoreIt gsEnd  = _geoStore.end  ();

    for(; gsIt != gsEnd; ++gsIt)
    {
        OSG_ASSERT(gsIt->_propStore.size() == gsIt->_indexStore.size());

        // find the material associated with the geometry's material symbol
        MaterialMapConstIt mmIt       = matMap.find(gsIt->_matSymbol);
        std::string        matTarget;

        if(mmIt != matMap.end())
        {
            matTarget = mmIt->second->getTarget();
        }

        // check if the geometry was already used with that material

        GeometryUnrecPtr   geo    = NULL;
        InstanceMapConstIt instIt = gsIt->_instMap.find(matTarget);

        if(instIt != gsIt->_instMap.end())
        {
            // reuse geometry

            geo = dynamic_pointer_cast<Geometry>(
                getInstStore()[instIt->second]);

            getGlobal()->getStatCollector()->getElem(
                ColladaGlobal::statNGeometryUsed)->inc();
        }
        else
        {
            // create new geometry

            geo = Geometry::create();

            getGlobal()->getStatCollector()->getElem(
                ColladaGlobal::statNGeometryCreated)->inc();

            geo->setLengths(gsIt->_lengths);
            geo->setTypes  (gsIt->_types  );

            Inherited::handleBindMaterial(*gsIt, geo, colInstCtrl);

            // record the instantiation of the geometry with the
            // material for reuse
            gsIt->_instMap.insert(
                InstanceMap::value_type(matTarget, getInstStore().size()));

            editInstStore().push_back(geo);
        }

        NodeUnrecPtr geoN = makeNodeFor(geo);

        groupN->addChild(geoN);
    }

    // store the generated group node
    editInstStore().push_back(groupN);

    return groupN;
}

ColladaController::ColladaController(daeElement *elem, ColladaGlobal *global)
    : Inherited    (elem, global)
    , _matBindShape()
{
}

ColladaController::~ColladaController(void)
{
}

void
ColladaController::readSkin(domSkin *skin)
{
    SWARNING << "ColladaController::readSkin: NIY" << std::endl;

    daeURI         geoURI = skin->getSource();
    domGeometryRef geo    = daeSafeCast<domGeometry>(geoURI.getElement());

    if(geo == NULL)
    {
        SWARNING << "ColladaController::readSkin: Could not resolve source "
                 << "URI [" << geoURI.str() << "] to a <geometry>"
                 << std::endl;
        return;
    }

    domMeshRef mesh = geo->getMesh();

    if(mesh == NULL)
    {
        SWARNING << "ColladaController::readSkin: No <mesh> in <geometry>"
                 << std::endl;
        return;
    }

    Inherited::readMesh(mesh);

    domSkin::domBind_shape_matrixRef bsMat = skin->getBind_shape_matrix();

    if(bsMat != NULL)
    {
        _matBindShape.setValue(bsMat->getValue()[ 0], bsMat->getValue()[ 1],
                               bsMat->getValue()[ 2], bsMat->getValue()[ 3],
                               bsMat->getValue()[ 4], bsMat->getValue()[ 5],
                               bsMat->getValue()[ 6], bsMat->getValue()[ 7],
                               bsMat->getValue()[ 8], bsMat->getValue()[ 9],
                               bsMat->getValue()[10], bsMat->getValue()[11],
                               bsMat->getValue()[12], bsMat->getValue()[13],
                               bsMat->getValue()[14], bsMat->getValue()[15] );
    }
    else
    {
        _matBindShape.setIdentity();
    }

    domSkin::domJointsRef      joints      = skin  ->getJoints     ();
    const domInputLocal_Array &jointInputs = joints->getInput_array();

    for(UInt32 i = 0; i < jointInputs.getCount(); ++i)
    {
        OSG_COLLADA_LOG(("ColladaController::readSkin: "
                         "jointInputs[%d] semantic [%s]\n", i,
                         jointInputs[i]->getSemantic()        ));
    }

}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
