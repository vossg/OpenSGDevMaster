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
#include "OSGColladaNode.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGSkinnedGeometry.h"
#include "OSGSkeletonJoint.h"
#include "OSGNameAttachment.h"
#include "OSGFieldContainerUtils.h"

#include <dom/domController.h>
#include <dom/domGeometry.h>

#include <set>

OSG_BEGIN_NAMESPACE

ColladaInstInfoTransitPtr
ColladaController::ColladaControllerInstInfo::create(
    ColladaNode *colInstParent, ColladaInstanceController *colInst,
    Node        *parentN                                           )
{
    return ColladaInstInfoTransitPtr(
        new ColladaControllerInstInfo(colInstParent, colInst, parentN));
}

void
ColladaController::ColladaControllerInstInfo::process(void)
{
     Node *ctrlInstN = dynamic_cast<Node *>(
        getColInst()->getTargetElem()->createInstance(this));

    getParentNode()->addChild(ctrlInstN);
}

ColladaController::ColladaControllerInstInfo::ColladaControllerInstInfo(
    ColladaNode *colInstParent, ColladaInstanceController *colInst,
    Node        *parentN                                           )

    : Inherited(colInstParent, colInst)
    , _parentN (parentN               )
{
}

ColladaController::ColladaControllerInstInfo::~ColladaControllerInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaController::_regHelper(
    &ColladaController::create, "controller");


ColladaElementTransitPtr
ColladaController::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaController(elem, global));
}

void
ColladaController::read(ColladaElement *colElemParent)
{
    domControllerRef ctrl = getDOMElementAs<domController>();
    domSkinRef       skin = ctrl->getSkin();

    OSG_COLLADA_LOG(("ColladaController::read id [%s]\n", ctrl->getId()));

    if(skin == NULL)
    {
        SWARNING << "ColladaController::read: No <skin>" << std::endl;
        return;
    }

    readSkin(skin);
}

Node *
ColladaController::createInstance(ColladaInstInfo *colInstInfo)
{
    typedef ColladaInstanceController::MaterialMap        MaterialMap;
    typedef ColladaInstanceController::MaterialMapConstIt MaterialMapConstIt;

    domControllerRef ctrl = getDOMElementAs<domController>();

    OSG_COLLADA_LOG(("ColladaController::createInstance id [%s]\n",
                     ctrl->getId()));

    domSkinRef                      skin        = ctrl->getSkin();
    NodeUnrecPtr                    groupN      = makeCoredNode<Group>();
    ColladaInstanceControllerRefPtr colInstCtrl =
        dynamic_cast<ColladaInstanceController *>(colInstInfo->getColInst());

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
       ctrl->getName()                                       != NULL   )
    {
        setName(groupN, ctrl->getName());
    }

    // create Skeleton

    // find all joints and store them in jointStore
    JointInfoStore jointStore;
    JointIdMap     jointIdMap;
    resolveJoints(skin, colInstCtrl, jointStore, jointIdMap);
    remapJointIds(skin, colInstCtrl, jointStore, jointIdMap);

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

        getGlobal()->getStatCollector()->getElem(
            ColladaGlobal::statNGeometryCreated)->inc();

        geo->setLengths(gsIt->_lengths);
        geo->setTypes  (gsIt->_types  );

        Inherited::handleBindMaterial(*gsIt, geo, colInstCtrl);

        geo->setSkeleton       (_skeleton                    );
        geo->setBindShapeMatrix(_matBindShape                );
        geo->setRenderMode     (SkinnedGeometry::RMSkinnedGPU);

        PropStoreConstIt psIt  = (*gsIt)._propStore .begin();
        PropStoreConstIt psEnd = (*gsIt)._propStore .end  ();

        for(; psIt != psEnd; ++psIt)
        {
            if((*psIt)._semantic == "JOINT_INDEX")
            {
                for(UInt16 i = 0; i < geo->getMFProperties()->size(); ++i)
                {
                    if((*psIt)._prop == geo->getProperty(i))
                    {
                        geo->setJointIndexProperty(i);
                        break;
                    }
                }
            }

            if((*psIt)._semantic == "JOINT_WEIGHT")
            {
                for(UInt16 i = 0; i < geo->getMFProperties()->size(); ++i)
                {
                    if((*psIt)._prop == geo->getProperty(i))
                    {
                        geo->setJointWeightProperty(i);
                        break;
                    }
                }
            }
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
    , _skeleton    (NULL)
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

    readBindShapeMatrix(skin);

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

#if 0
            OSG_COLLADA_LOG(("ColladaController::readSkin: vert [%d] "
                             "jIndex [%f %f %f %f] jWeight [%f %f %f %f]\n",
                             i, jIndex[0], jIndex[1], jIndex[2], jIndex[3],
                             jWeight[0], jWeight[1], jWeight[2], jWeight[3]));
#endif

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
ColladaController::readBindShapeMatrix(domSkin *skin)
{
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

    if(_matBindShape.equals(Matrix::identity(), Eps) == true)
        return;

#if 0
    // transform the properties by the bind shape matrix

    Matrix matBindShapeIT(_matBindShape);
    matBindShapeIT.invert   ();
    matBindShapeIT.transpose();

    typedef std::set<GeoVectorProperty *> PropertySet;
    PropertySet xformedProps;

    GeoStore::iterator gsIt  = _geoStore.begin();
    GeoStore::iterator gsEnd = _geoStore.end  ();

    for(; gsIt != gsEnd; ++gsIt)
    {
        PropStoreIt psIt  = gsIt->_propStore.begin();
        PropStoreIt psEnd = gsIt->_propStore.end  ();

        for(; psIt != psEnd; ++psIt)
        {
            if(psIt->_prop == NULL)
                continue;

            // only transform once
            if(xformedProps.count(psIt->_prop) > 0)
                continue;

            if(psIt->_semantic == "POSITION")
            {
                for(UInt32 i = 0; i < psIt->_prop->size(); ++i)
                {
                    Pnt4f pnt;

                    psIt->_prop->getValue(pnt, i);
                    _matBindShape.mult(pnt, pnt);
                    psIt->_prop->setValue(pnt, i);
                }

                OSG_COLLADA_LOG(("ColladaController::readBindShapeMatrix: "
                                 "Transformed property with semantic [%s]\n",
                                 psIt->_semantic.c_str()));
            }
            else if(psIt->_semantic == "NORMAL")
            {
                for(UInt32 i = 0; i < psIt->_prop->size(); ++i)
                {
                    Vec4f vec;

                    psIt->_prop->getValue(vec, i);
                    matBindShapeIT.mult(vec, vec);
                    psIt->_prop->setValue(vec, i);
                }

                OSG_COLLADA_LOG(("ColladaController::readBindShapeMatrix: "
                                 "Transformed property with semantic [%s]\n",
                                 psIt->_semantic.c_str()));
            }
            else
            {
                OSG_COLLADA_LOG(("ColladaController::readBindShapeMatrix: "
                                 "Skipped property with semantic [%s]\n",
                                 psIt->_semantic.c_str()));
            }

            xformedProps.insert(psIt->_prop);
        }
    }
#endif
}

void
ColladaController::resolveJoints(
    domSkin        *skin,       ColladaInstanceController *colInstCtrl,
    JointInfoStore &jointStore, JointIdMap                &jointIdMap  )
{
    domControllerRef      ctrl   = getDOMElementAs<domController>();
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

    _skeleton = NULL;

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
            JointInfo jointInfo;
            // joint names are relative to the <skeleton> tags in the
            // <instance_controller> element

            domNode *jointNode = colInstCtrl->findJointNode(jointNames[i]);

            if(jointNode == NULL)
            {
                SWARNING << "ColladaController::resolveJoints: Could not "
                         << "find <node> for joint name ["
                         << jointNames[i] << "] - <controller> ["
                         << (ctrl->getId() != NULL ? ctrl->getId() : "")
                         << "]. Ignored." << std::endl;
                continue;
            }

            if(jointNode->getType() != NODETYPE_JOINT)
            {
                SWARNING << "ColladaController::resolveJoints: <node> for "
                         << "joint name [" << jointNames[i] << "] does not "
                         << "have node type JOINT. Ignored." << std::endl;
                continue;
            }

            ColladaNode *colJointNode = getUserDataAs<ColladaNode>(jointNode);
            OSG_ASSERT(colJointNode != NULL);

            // store skeleton and ensure all joints belong to the same one
            if(_skeleton != NULL)
            {
                if(_skeleton != colJointNode->getSkeleton())
                {
                    SWARNING << "ColladaController::resolveJoints: joint ["
                             << i << "] name [" << jointNames[i]
                             << "] belongs to differente skeleton. Ignoring."
                             << std::endl;
                    continue;
                }
            }
            else
            {
                _skeleton = colJointNode->getSkeleton();
            }

            if(colJointNode->getInstStore().size() > 1)
            {
                SWARNING << "ColladaController::resolveJoints: joint ["
                         << i << "] name [" << jointNames[i]
                         << "] has multiple instances. Using instance 0."
                         << std::endl;
            }

            SkeletonJoint *joint = dynamic_cast<SkeletonJoint *>(
                colJointNode->getBottomNode(0)->getCore());

            if(joint->getInvBindMatrix().equals(Matrix::identity(), Eps) == true)
            {
                joint->setInvBindMatrix(invBindMats[i]);
            }
            else if(joint->getInvBindMatrix().equals(invBindMats[i], Eps) == false)
            {
                SWARNING << "ColladaController::resolveJoints: joint ["
                         << i << "] name [" << jointNames[i]
                         << "] already has a different inv bind matrix."
                         << std::endl;
            }

            jointInfo.jointNode     = jointNode;
            jointInfo.colJointNode  = colJointNode;
            jointInfo.jointId       = joint->getJointId();
            jointInfo.invBindMatrix = invBindMats[i];

            jointStore.push_back(jointInfo);

            // remember joint id mapping
            jointIdMap.push_back(joint->getJointId());

            OSG_COLLADA_LOG(("ColladaController::resolveJoints: Resolved "
                             "joint [%d] name [%s] jointId [%d]\n",
                             i, jointNames[i].c_str(), joint->getJointId() ));
        }
    }
    else
    {
        SWARNING << "ColladaController::resolveJoints: Can only handle "
                 << "<joints> with JOINT and INV_BIND_MATRIX <input>s."
                 << std::endl;
    }
}

void
ColladaController::remapJointIds(
    domSkin                   *skin, 
    ColladaInstanceController *colInstCtrl,
    const JointInfoStore      &jointStore,
    const JointIdMap          &jointIdMap  )
{
    typedef std::set<GeoVectorProperty *> PropertySet;
    PropertySet mappedProps;

    GeoStore::iterator gsIt  = _geoStore.begin();
    GeoStore::iterator gsEnd = _geoStore.end  ();

    for(; gsIt != gsEnd; ++gsIt)
    {
        PropStoreIt psIt  = gsIt->_propStore.begin();
        PropStoreIt psEnd = gsIt->_propStore.end  ();

        for(; psIt != psEnd; ++psIt)
        {
            if(psIt->_prop == NULL)
                continue;

            if(mappedProps.count(psIt->_prop) > 0)
                continue;

            if(psIt->_semantic != "JOINT_INDEX")
                continue;

            GeoVec4fPropertyUnrecPtr jIndexProp =
                dynamic_pointer_cast<GeoVec4fProperty>(psIt->_prop);

            GeoVec4fProperty::StoredFieldType *jIndexPropF =
                jIndexProp->editFieldPtr();

            for(UInt32 i = 0; i < jIndexPropF->size(); ++i)
            {
                Vec4f jIdx = (*jIndexPropF)[i];
                
                jIdx[0] = jointIdMap[UInt32(jIdx[0])];
                jIdx[1] = jointIdMap[UInt32(jIdx[1])];
                jIdx[2] = jointIdMap[UInt32(jIdx[2])];
                jIdx[3] = jointIdMap[UInt32(jIdx[3])];

                (*jIndexPropF)[i] = jIdx;
            }

            mappedProps.insert(jIndexProp);
        }
    }
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
