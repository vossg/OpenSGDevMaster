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
#include "OSGColladaSource.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGSkinnedGeometry.h"
#include "OSGSkeletonJoint.h"
#include "OSGNameAttachment.h"

#include <dom/domController.h>
#include <dom/domGeometry.h>
#include <dom/domLookat.h>
#include <dom/domMatrix.h>
#include <dom/domRotate.h>
#include <dom/domScale.h>
#include <dom/domSkew.h>
#include <dom/domTranslate.h>

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

    domControllerRef ctrl = getDOMElementAs<domController>();
    domSkinRef       skin = ctrl->getSkin();

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

    domControllerRef                ctrl        =
        getDOMElementAs<domController>();
    domSkinRef                      skin        = ctrl->getSkin();
    TransformUnrecPtr               xform       = Transform::create();
    NodeUnrecPtr                    xformN      = makeNodeFor(xform);
    ColladaInstanceControllerRefPtr colInstCtrl =
        dynamic_cast<ColladaInstanceController *>(colInstElem);

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
       ctrl->getName()                                       != NULL   )
    {
        setName(xformN, ctrl->getName());
    }

    // set bind shape matrix 
    xform->setMatrix(_matBindShape);

    // create Skeleton

    // find all joints and store them in jointStore
    JointInfoStore jointStore;
    resolveJoints(skin, colInstCtrl, jointStore);

    // construct hierarchy of joints
    SkeletonUnrecPtr skel = buildSkeleton(jointStore);

    // create SkinnedGeometry

    const MaterialMap &matMap = colInstCtrl->getMaterialMap();

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

        // can't reuse SkinnedGeometry, it may be instantiated with
        // a different Skeleton

        // create new geometry
        SkinnedGeometryUnrecPtr geo = SkinnedGeometry::create();
        geo->setSkeleton(skel);
        geo->addFlag(SkinnedGeometry::SGFlagHardware);

        getGlobal()->getStatCollector()->getElem(
            ColladaGlobal::statNGeometryCreated)->inc();

        geo->setLengths(gsIt->_lengths);
        geo->setTypes  (gsIt->_types  );

        Inherited::handleBindMaterial(*gsIt, geo, colInstCtrl);

        NodeUnrecPtr geoN = makeNodeFor(geo);

        xformN->addChild(geoN);
    }

    // store the generated group node
    editInstStore().push_back(xformN);

    return xformN;
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

    Inherited::readSources(skin->getSource_array());

    // evaluate <vertex_weights>
    domSkin::domVertex_weightsRef    vweights = skin->getVertex_weights();
    const domInputLocalOffset_Array &inputs   = vweights->getInput_array();

    UInt32              jointIdx  = inputs.getCount();
    ColladaSourceRefPtr weightSrc = NULL;

    for(UInt32 i = 0; i < inputs.getCount(); ++i)
    {
        std::string      semantic = inputs[i]->getSemantic();
        std::string      sourceId = inputs[i]->getSource  ().id();
        UInt32           offset   = inputs[i]->getOffset  ();

        SourceMapConstIt smIt     = _sourceMap.find(sourceId);

        if(smIt == _sourceMap.end())
        {
            SWARNING << "ColladaController::readSkin: Could not find "
                     << "<source> with id [" << sourceId << "] used by "
                     << "<input> [" << i << "] with semantic ["
                     << semantic << "]. Ignored." << std::endl;
            continue;
        }

        if(semantic == "JOINT")
        {
            // which item of the index tuples in <v> hold the joint
            jointIdx = offset;
        }
        else if(semantic == "WEIGHT")
        {
            weightSrc = smIt->second;
        }
    }

    // test if the file has the "usual" form, and only handle that
    //    this means there is an <input> with semantic "JOINT" and
    //    one with semantic "WEIGHT"
    if(jointIdx          <  inputs.getCount() && weightSrc != NULL &&
       inputs.getCount() == 2                                        )
    {
        GeoVec4fPropertyUnrecPtr jIndexProp  = GeoVec4fProperty::create();
        GeoVec4fPropertyUnrecPtr jWeightProp = GeoVec4fProperty::create();

        GeoVec4fProperty::StoredFieldType *jIndexPropF  =
            jIndexProp ->editFieldPtr();
        GeoVec4fProperty::StoredFieldType *jWeightPropF =
            jWeightProp->editFieldPtr();

        const domListOfUInts &vcount = vweights->getVcount()->getValue();
        const domListOfInts  &v      = vweights->getV     ()->getValue();

        UInt32 vIdx = 0;

        for(UInt32 i = 0; i < vcount.getCount(); ++i)
        {
            Vec4f jIndex;
            Vec4f jWeight;

            if(vcount[i] > 4)
            {
                SWARNING << "ColladaController::readSkin: Vertex [" << i
                         << "] has [" << vcount[i] << "] > 4 weights."
                         << std::endl;
            }

            UInt32 j;

            // the current vertex i is influenced by vcount[i] many joints
            for(j = 0; j < osgMin<UInt32>(4, vcount[i]); ++j)
            {
                jIndex [j] = v[vIdx];
                jWeight[j] = weightSrc->getFloatValue(v[vIdx + 1]);

                vIdx += 2;
            }

            OSG_COLLADA_LOG(("ColladaController::readSkin: vert [%d] "
                             "jIndex [%f %f %f %f] jWeight [%f %f %f %f]\n",
                             i, jIndex[0], jIndex[1], jIndex[2], jIndex[3],
                             jWeight[0], jWeight[1], jWeight[2], jWeight[3]));

            jIndexPropF ->push_back(jIndex );
            jWeightPropF->push_back(jWeight);

            // skip joint/weight indices we can not store (if any)
            for(j = osgMin<UInt32>(4, vcount[i]); j < vcount[i]; ++j)
            {
                vIdx += 2;
            }
        }

        OSG_COLLADA_LOG(("ColladaController::readSkin: "
                         "jIndexProp.size() [%d] jWeightProp.size() [%d]\n",
                         jIndexProp->size(), jWeightProp->size()));

        // add jIndexProp and jWeightProp to geoInfos
        GeoStore::iterator gsIt  = _geoStore.begin();
        GeoStore::iterator gsEnd = _geoStore.end  ();

        for(UInt32 i = 0; gsIt != gsEnd; ++gsIt, ++i)
        {
            // add joint index property
            UInt16 propSlot = Inherited::findFreePropertyIndex(i);
            gsIt->_propStore.resize (
                osgMax<UInt16>(gsIt->_propStore .size(), propSlot + 1), PropInfo());
            gsIt->_indexStore.resize(
                osgMax<UInt16>(gsIt->_indexStore.size(), propSlot + 1), NULL      );

            gsIt->_propStore [propSlot]._prop     = jIndexProp;
            gsIt->_propStore [propSlot]._semantic = "JOINT_INDEX";
            gsIt->_propStore [propSlot]._set      = 0;
            gsIt->_indexStore[propSlot]           = gsIt->_indexStore[0];

            // add weight property
            propSlot = Inherited::findFreePropertyIndex(i);
            gsIt->_propStore.resize (
                osgMax<UInt16>(gsIt->_propStore .size(), propSlot + 1), PropInfo());
            gsIt->_indexStore.resize(
                osgMax<UInt16>(gsIt->_indexStore.size(), propSlot + 1), NULL      );

            gsIt->_propStore [propSlot]._prop     = jWeightProp;
            gsIt->_propStore [propSlot]._semantic = "JOINT_WEIGHT";
            gsIt->_propStore [propSlot]._set      = 0;
            gsIt->_indexStore[propSlot]           = gsIt->_indexStore[0];
        }
    }
    else
    {
        SWARNING << "ColladaController::readSkin: Can only handle "
                 << "<vertex_weights> with JOINT and WEIGHT <input>s."
                 << std::endl;
    }
}

void
ColladaController::resolveJoints(
    domSkin        *skin, ColladaInstanceController *colInstCtrl,
    JointInfoStore &jointStore)
{
    domSkin::domJointsRef joints = skin->getJoints();

    // find <input>s with handled semantics (JOINT and INV_BIND_MATRIX)
    // everything else is ignored/warned about

    ColladaSourceRefPtr jointSrc = NULL;
    ColladaSourceRefPtr ibmSrc   = NULL;

    const domInputLocal_Array &jointInputs = joints->getInput_array();
    
    for(UInt32 i = 0; i < jointInputs.getCount(); ++i)
    {
        std::string      semantic = jointInputs[i]->getSemantic();
        std::string      sourceId = jointInputs[i]->getSource  ().id();

        SourceMapConstIt smIt     = _sourceMap.find(sourceId);

        if(smIt == _sourceMap.end())
        {
            SWARNING << "ColladaController::resolveJoints: Could not find "
                     << "<source> with id [" << sourceId << "] used by "
                     << "<input> [" << i << "] with semantic ["
                     << semantic << "]. Ignored." << std::endl;
            continue;
        }

        if(semantic == "JOINT")
        {
            jointSrc = smIt->second;
        }
        else if(semantic == "INV_BIND_MATRIX")
        {
            ibmSrc = smIt->second;
        }
        else
        {
            SWARNING << "ColladaController::resolveJoints: Unknown semantic ["
                     << semantic << "] on <input> [" << i << "]"
                     << std::endl;
        }
    }

    // resolve joint names to <node>s and fill jointStore

    if(jointSrc != NULL && ibmSrc != NULL)
    {
        const ColladaSource::NameStore   &jointNames  =
            jointSrc->getNameStore  ();
        const ColladaSource::MatrixStore &invBindMats =
            ibmSrc  ->getMatrixStore();

        OSG_ASSERT(jointNames.size() == invBindMats.size());

        for(UInt32 i = 0; i < jointNames.size(); ++i)
        {
            jointStore.push_back(JointInfo());

            // joint names are relative to the <skeleton> tags in the
            // <instance_controller> element

            domNode *jointNode = colInstCtrl->findJointNode(jointNames[i]);

            if(jointNode == NULL)
            {
                SWARNING << "ColladaController::resolveJoints: Could not "
                         << "find <node> for joint name ["
                         << jointNames[i] << "]. Ignored." << std::endl;
                continue;
            }

            if(jointNode->getType() != NODETYPE_JOINT)
            {
                SWARNING << "ColladaController::resolveJoints: <node> for "
                         << "joint name [" << jointNames[i] << "] does not "
                         << "have node type JOINT. Ignored." << std::endl;
                continue;
            }

            jointStore.back().jointNode   = jointNode;

            SkeletonJointRefPtr skelJoint = SkeletonJoint::create();
            skelJoint->setJointId       (i);
            skelJoint->editInvBindMatrix( ).setValue   (invBindMats[i]);
            skelJoint->editMatrix       ( ).setIdentity(              );

            jointStore.back().invBindMatrix = invBindMats[i];
            jointStore.back().bottomN       = makeNodeFor(skelJoint);
            jointStore.back().topN          = jointStore.back().bottomN;

            OSG_COLLADA_LOG(("ColladaController::resolveJoints: Resolved "
                             "joint name [%s]\n", jointNames[i].c_str()));
        }
    }
    else
    {
        SWARNING << "ColladaController::resolveJoints: Can only handle "
                 << "<joints> with JOINT and INV_BIND_MATRIX <input>s."
                 << std::endl;
    }
}

SkeletonTransitPtr
ColladaController::buildSkeleton(JointInfoStore &jointStore)
{
    SkeletonUnrecPtr skel = Skeleton::create();

    JointInfoStoreIt jIt  = jointStore.begin();
    JointInfoStoreIt jEnd = jointStore.end  ();

    for(UInt32 i = 0; jIt != jEnd; ++jIt, ++i)
    {
        // this can never happen - there is at least the <COLLADA> tag around
        // everything ?? -- cneumann
        if(jIt->jointNode->getParentElement() == NULL)
            continue;

        // evaluate transform elements, building a chain of OpenSG Nodes
        buildTransforms(*jIt);

        // find the nearest parent domNode to construct the hierarchy
        domNode *jointNode  = jIt->jointNode;
        domNode *parentNode = NULL;

        do
        {
            parentNode = daeSafeCast<domNode>(jointNode->getParentElement());

            if(parentNode != NULL)
            {
                Int32 parentIdx = findJoint(jointStore, parentNode);

                if(parentIdx != -1)
                {
                    OSG_COLLADA_LOG(("ColladaController::buildSkeleton: "
                                     "adding joint [%s][%d] as child of [%s][%d]\n",
                                     jIt->jointNode->getSid(), i,
                                     jointStore[parentIdx].jointNode->getSid(),
                                     parentIdx));

                    jointStore[parentIdx].bottomN->addChild(jIt->topN);
                    break;
                }
            }
            else
            {
                // no parent <node> found, make this a root joint
                OSG_COLLADA_LOG(("ColladaController::buildSkeleton: "
                                 "joint [%s][%d] is a root joint.\n",
                                 jIt->jointNode->getSid(), i));

                skel->editMFRoots()->push_back(jIt->topN);
                break;
            }

            jointNode = parentNode;
        }
        while(true);
    }

    return SkeletonTransitPtr(skel);
}

void
ColladaController::buildTransforms(JointInfo &jointInfo)
{
    // build the transform elements bottom up (starting at the joint itself)

    const daeElementRefArray &contents = jointInfo.jointNode->getContents();

    for(Int32 i = contents.getCount() - 1; i >= 0; --i)
    {
        switch(contents[i]->getElementType())
        {
        case COLLADA_TYPE::LOOKAT:
            buildLookAt(daeSafeCast<domLookat>(contents[i]), jointInfo);
            break;

        case COLLADA_TYPE::MATRIX:
            buildMatrix(daeSafeCast<domMatrix>(contents[i]), jointInfo);
            break;

        case COLLADA_TYPE::ROTATE:
            buildRotate(daeSafeCast<domRotate>(contents[i]), jointInfo);
            break;

        case COLLADA_TYPE::SCALE:
            buildScale(daeSafeCast<domScale>(contents[i]), jointInfo);
            break;

        case COLLADA_TYPE::SKEW:
            buildSkew(daeSafeCast<domSkew>(contents[i]), jointInfo);
            break;

        case COLLADA_TYPE::TRANSLATE:
            buildTranslate(daeSafeCast<domTranslate>(contents[i]), jointInfo);
            break;
        }
    }
}

void
ColladaController::buildLookAt(domLookat *lookAt, JointInfo &jointInfo)
{
    if(lookAt == NULL)
        return;

    SWARNING << "ColladaController::buildLookAt: NIY" << std::endl;
}

void
ColladaController::buildMatrix(domMatrix *matrix, JointInfo &jointInfo)
{
    if(matrix == NULL)
        return;

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    Matrix m(matrix->getValue()[0],      // rVal00
             matrix->getValue()[1],      // rVal10
             matrix->getValue()[2],      // rVal20
             matrix->getValue()[3],      // rVal30
             matrix->getValue()[4],      // rVal01
             matrix->getValue()[5],      // rVal11
             matrix->getValue()[6],      // rVal21
             matrix->getValue()[7],      // rVal31
             matrix->getValue()[8],      // rVal02
             matrix->getValue()[9],      // rVal12
             matrix->getValue()[10],     // rVal22
             matrix->getValue()[11],     // rVal32
             matrix->getValue()[12],     // rVal03
             matrix->getValue()[13],     // rVal13
             matrix->getValue()[14],     // rVal23
             matrix->getValue()[15] );   // rVal33

    xform->setMatrix(m);

    prependXForm(xformN, jointInfo);
}

void
ColladaController::buildRotate(domRotate *rotate, JointInfo &jointInfo)
{
    if(rotate == NULL)
        return;

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    Quaternion q;
    q.setValueAsAxisDeg(rotate->getValue()[0],
                        rotate->getValue()[1],
                        rotate->getValue()[2],
                        rotate->getValue()[3] );

    xform->editMatrix().setRotate(q);

    prependXForm(xformN, jointInfo);
}

void
ColladaController::buildScale(domScale *scale, JointInfo &jointInfo)
{
    if(scale == NULL)
        return;

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setScale(scale->getValue()[0],
                                 scale->getValue()[1],
                                 scale->getValue()[2] );

    prependXForm(xformN, jointInfo);
}

void
ColladaController::buildSkew(domSkew *skew, JointInfo &jointInfo)
{
    if(skew == NULL)
        return;

    SWARNING << "ColladaController::buildSkew: NIY" << std::endl;
}

void
ColladaController::buildTranslate(
    domTranslate *translate, JointInfo &jointInfo)
{
    if(translate == NULL)
        return;

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setTranslate(translate->getValue()[0],
                                     translate->getValue()[1],
                                     translate->getValue()[2] );

    prependXForm(xformN, jointInfo);
}

void
ColladaController::prependXForm(Node *node, JointInfo &jointInfo)
{
    node->addChild(jointInfo.topN);
    jointInfo.topN = node;
}

void
ColladaController::appendXForm(Node *node, JointInfo &jointInfo)
{
    jointInfo.bottomN->addChild(node);
    jointInfo.bottomN = node;
}

Int32
ColladaController::findJoint(
    const JointInfoStore &jointStore, domNode *joint)
{
    Int32                 retVal = -1;
    JointInfoStoreConstIt jIt    = jointStore.begin();
    JointInfoStoreConstIt jEnd   = jointStore.end  ();

    for(Int32 i = 0; jIt != jEnd; ++jIt, ++i)
    {
        if(jIt->jointNode == joint)
        {
            retVal = i;
            break;
        }
    }

    return retVal;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
