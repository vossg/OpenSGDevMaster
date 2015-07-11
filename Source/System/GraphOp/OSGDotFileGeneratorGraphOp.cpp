/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#include <sstream>
#include <boost/foreach.hpp>

#include "OSGDotFileGeneratorGraphOp.h"
#include "OSGContainerCollection.h"
#include "OSGGraphOpFactory.h"
#include "OSGGroup.h"
#include "OSGMaterialGroup.h"
#include "OSGMaterialChunkOverrideGroup.h"
#include "OSGNameAttachment.h"
#include "OSGDistanceLOD.h"
#include "OSGScreenLOD.h"
#include "OSGLight.h"
#include "OSGSwitch.h"
#include "OSGMultiCore.h"
#include "OSGVisitSubTree.h"
#include "OSGTransform.h"
#include "OSGTextureObjChunk.h"
#include "OSGClipPlaneChunk.h"
#include "OSGLightChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGSwitchMaterial.h"
#include "OSGMultiPassMaterial.h"
#include "OSGGeometry.h"

/*! \class OSG::DotFileGeneratorGraphOp
    \ingroup GrpContribDataSolidGraphOp

    Writes a Graphviz dot file representation of the graph.
*/

OSG_BEGIN_NAMESPACE

namespace
{
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = DotFileGeneratorGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }

    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
} // namespace


DotFileGeneratorGraphOp::Info::Info(void) :
    cnt      (    0),
    label    (     ),
    name     (     ),
    id       (     ),
    fontcolor(     ),
    obj_id   (NULL ),
    finished (false)
{
}

DotFileGeneratorGraphOp::Info::Info(const Info &other) :
    cnt      (other.cnt      ),
    label    (other.label    ),
    name     (other.name     ),
    id       (other.id       ),
    fontcolor(other.fontcolor),
    obj_id   (other.obj_id   ),
    finished (other.finished )
{
}

DotFileGeneratorGraphOp::Info::~Info(void)
{
}

DotFileGeneratorGraphOp::BrewerColor::BrewerColor(const std::string &scheme,
                                                  const std::string &number) :
  scheme(scheme),
  number(number)
{
}

DotFileGeneratorGraphOp::BrewerColor::~BrewerColor(void)
{
}

const DotFileGeneratorGraphOp::BrewerColor &
    DotFileGeneratorGraphOp::Colors::color(void) const
{
    if (_current >= _colors.size())
        _current = 0;

    if (_current >= _colors.size())
        throw std::out_of_range("no color available");

    return _colors[_current++];
}

void DotFileGeneratorGraphOp::Colors::add(const std::string &scheme,
                                                UInt32       start,
                                                UInt32       end   )
{
    for (UInt32 i = start; i <= end; ++i)
    {
        std::stringstream number;
        number << i;
        _colors.push_back(BrewerColor(scheme, number.str()));
    }
}

DotFileGeneratorGraphOp::Colors::Colors(void) :
    _colors ( ),
    _current(0)
{
}

DotFileGeneratorGraphOp::Colors::~Colors(void)
{
}

const char *DotFileGeneratorGraphOp::getClassname(void)
{
    return "DotFileGeneratorGraphOp";
}

DotFileGeneratorGraphOp::DotFileGeneratorGraphOp(const char* name) :
    Inherited(name),
    _filename("out.dot"),
    _include_attachment(true),
    _no_name_attachments(true),
    _no_ranks(false),
    _max_node_children(-1),
    _size(""),
    _ranksep("2.5"),
    _nodesep("1.0"),
    _graph_attributes(""),
    _spStream(),
    _mapInfo(),
    _node_cnt(0),
    _core_cnt(0),
    _attachment_cnt(0),
    _material_cnt(0),
    _matrix_cnt(0),
    _image_cnt(0),
    _chunk_cnt(0),
    _integral_prop_cnt(0),
    _vector_prop_cnt(0),
    _space(0),
    _colors(),
    _usedColors(),
    _suppressed(),
    _suppressed_derived(),
    _dotted_edges(),
    _edges()
{
    // nothing to do
}

DotFileGeneratorGraphOpTransitPtr
    DotFileGeneratorGraphOp::create(void)
{
    return DotFileGeneratorGraphOpTransitPtr(new DotFileGeneratorGraphOp);
}

GraphOpTransitPtr DotFileGeneratorGraphOp::clone(void)
{
    return GraphOpTransitPtr(new DotFileGeneratorGraphOp);
}

void DotFileGeneratorGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);

    ps("filename",              _filename);
    ps("include_attachment",    _include_attachment);
    ps("no_name_attachments",   _no_name_attachments);
    ps("no_ranks",              _no_ranks);
    ps("max_node_children",     _max_node_children);
    ps("size",                  _size);
    ps("ranksep",               _ranksep);
    ps("nodesep",               _nodesep);
    ps("graph_attributes",      _graph_attributes);

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("DotFileGeneratorGraphOp doesn't have parameters '%s'\n.",
                out.c_str()));
    }
}

std::string DotFileGeneratorGraphOp::usage(void)
{
    return
    "DotFileGenerator: Writes Graphiz dot file of graph\n"
    "Params: name (type, default)\n"
    "  filename                 (std::string, \"out.dot\"): output file name\n"
    "  include_attachment       (bool, true): include attachments in graph\n"
    "  no_name_attachments      (bool, true): include attachments in graph\n"
    "  no_ranks                 (bool, true): do not use rank statement in graph\n"
    "  max_node_children        (Int32,  -1): maximum number of children added to graph\n"
    "  size                     (std::string, \"\"): size attribute of graph\n"
    "  ranksep                  (std::string, \"1.5\"): ranksep attribute of graph\n"
    "  nodesep                  (std::string, \"1.0\"): nodesep attribute of graph\n"
    "  graph_attributes         (std::string, \"\"): arbitrary graph attribute entry\n";
}

void DotFileGeneratorGraphOp::insert(const TypeBase* t, bool derived_from)
{
    if(derived_from)
    {
        _suppressed_derived.push_back(t);
    }
    else
    {
        _suppressed.push_back(t);
    }
}

bool DotFileGeneratorGraphOp::isSuppressed(const TypeBase& t)
{
    VecTypesT::const_iterator iter, end;

    iter = _suppressed.begin();
    end  = _suppressed.end();

    for(; iter != end; ++iter)
    {
        if ((*iter)->getId() == t.getId())
            return true;
    }

    iter = _suppressed_derived.begin();
    end  = _suppressed_derived.end();

    for (; iter != end; ++iter)
    {
        const TypeBase& other = *(*iter);

        if (t.isDerivedFrom(other))
            return true;
    }

    return false;
}

DotFileGeneratorGraphOp::~DotFileGeneratorGraphOp(void)
{
    deinitialize();
}

Action::ResultE DotFileGeneratorGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;

    Node*     parent = node->getParent();
    NodeCore* core   = node->getCore();

    if(_max_node_children > 0 &&
       parent                 &&
       _node_cnt > 0          &&
       parent->findChild(node) >= Int32(_max_node_children))
    {
        Info& parent_info = NodeInfo(parent);

        if(!parent_info.finished)
        {
            parent_info.finished = true;

            Info node_info =
                EtceteraInfo(parent->getNChildren() - _max_node_children);

            DefineEtceteraNode(node_info);
            DefineNodeEdge(parent_info, node_info);
        }

        return Action::Skip;
    }

    const Info &node_info = NodeInfo(node);
    const Info &core_info = CoreInfo(core);

    bool suppressed = isSuppressed(core->getType());

    if (!suppressed)
        OpenGroup(true);

    DefineNode(node_info);

    if(!suppressed)
    {
        DefineCore(core_info);
        DefineCoreEdge(node_info, core_info);
    }

    if(!suppressed)
    {
        CloseGroup();

        HandleMaterial    (core, core_info);
        HandleLight       (core, core_info);
        HandleVisitSubTree(core, core_info);
        HandleTransform   (core, core_info);
        HandleGeometry    (core, core_info);
        HandleAttachment  (core, core_info);
    }

    HandleAttachment(node, node_info);

    if(parent)
    {
        DefineNodeEdge(NodeInfo(parent), node_info);
    }

    return Action::Continue;
}

void DotFileGeneratorGraphOp::HandleMaterial(      NodeCore * const core,
                                             const Info     &       info)
{
    Material      *mat  = NULL;
    MaterialGroup *mgrp = dynamic_cast<MaterialGroup*>(core);

    if(mgrp)
    {
        mat = mgrp->getMaterial();
    }
    else
    {
        MaterialChunkOverrideGroup *mcogrp =
            dynamic_cast<MaterialChunkOverrideGroup*>(core);

        if(mcogrp)
        {
            mat = mcogrp->getMaterial();
        }
        else
        {
            Geometry *geom = dynamic_cast<Geometry*>(core);

            if(geom)
            {
                mat = geom->getMaterial();
            }
        }
    }

    if(mat)
    {
        bool suppressed = isSuppressed(mat->getType());

        if(suppressed)
            return;

        OpenGroup(true);

        const Info &mat_info = MaterialInfo(mat);

        DefineMaterial(mat_info);
        DefineSimpleEdge(info, mat_info);

        CloseGroup();

        HandleChunkMaterial    (mat, mat_info);
        HandleSwitchMaterial   (mat, mat_info);
        HandleMultiPassMaterial(mat, mat_info);
    }
}

void DotFileGeneratorGraphOp::HandleTransform(      NodeCore * const core,
                                              const Info     &       info)
{
    Transform *trafo = dynamic_cast<Transform*>(core);

    if(trafo)
    {
        void *handler = &const_cast<Matrix&>(trafo->getMatrix());

        if(!hasInfo(handler))
        {
            OpenGroup(true);

            Info mat_info = MatrixInfo(trafo->getMatrix(), handler);

            DefineMatrix(mat_info);
            DefineSimpleEdge(info, mat_info);

            CloseGroup();
        }
    }
}

void DotFileGeneratorGraphOp::HandleGeometry(      NodeCore * const core,
                                             const Info     &       info)
{
    Geometry *geom = dynamic_cast<Geometry*>(core);

    if(geom)
    {
        OpenGroup(false);

        GeoIntegralProperty *types       = geom->getTypes();
        GeoIntegralProperty *length      = geom->getLengths();
        GeoVectorProperty   *vertices    = geom->getPositions();
        GeoVectorProperty   *normales    = geom->getNormals();
        GeoVectorProperty   *colors      = geom->getColors();
        GeoVectorProperty   *sec_colors  = geom->getSecondaryColors();
        GeoVectorProperty   *tex_coords  = geom->getTexCoords();
        GeoVectorProperty   *tex1_coords = geom->getTexCoords1();
        GeoVectorProperty   *tex2_coords = geom->getTexCoords2();
        GeoVectorProperty   *tex3_coords = geom->getTexCoords3();
        GeoVectorProperty   *tex4_coords = geom->getTexCoords4();
        GeoVectorProperty   *tex5_coords = geom->getTexCoords5();
        GeoVectorProperty   *tex6_coords = geom->getTexCoords6();
        GeoVectorProperty   *tex7_coords = geom->getTexCoords7();

        if(types && types->size() > 0)
        {
            Info prop_info = IntegralPropInfo(types, "types");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(length && length->size() > 0)
        {
            Info prop_info = IntegralPropInfo(length, "length");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(vertices && vertices->size() > 0)
        {
            Info prop_info = VectorPropInfo(vertices, "vertices");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(normales && normales->size() > 0)
        {
            Info prop_info = VectorPropInfo(normales, "normales");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(colors && colors->size() > 0)
        {
            Info prop_info = VectorPropInfo(colors, "colors");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(sec_colors && sec_colors->size() > 0)
        {
            Info prop_info = VectorPropInfo(sec_colors, "sec_colors");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex_coords && tex_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex_coords, "tex_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex1_coords && tex1_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex1_coords, "tex1_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex2_coords && tex2_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex2_coords, "tex2_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex3_coords && tex3_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex3_coords, "tex3_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex4_coords && tex4_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex4_coords, "tex4_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex5_coords && tex5_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex5_coords, "tex5_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex6_coords && tex6_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex6_coords, "tex6_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        if(tex7_coords && tex7_coords->size() > 0)
        {
            Info prop_info = VectorPropInfo(tex7_coords, "tex7_coords");
            DefineProperty(prop_info);
            DefineSimpleEdge(info, prop_info);
        }

        CloseGroup();
    }
}

void DotFileGeneratorGraphOp::HandleTextureChunk(
          StateChunk * const chunk,
    const Info       &       info)
{
    TextureObjChunk *textureobjchunk = dynamic_cast<TextureObjChunk*>(chunk);

    if(textureobjchunk)
    {
        Image *image = textureobjchunk->getImage();

        if(image)
        {
            bool suppressed = isSuppressed(image->getType());

            if(suppressed)
                return;

            OpenGroup(true);

            const Info &image_info = ImageInfo(image);

            DefineMatrix(image_info);
            DefineSimpleEdge(info, image_info);

            CloseGroup();
        }
    }
}

void DotFileGeneratorGraphOp::HandleLight(      NodeCore * const core,
                                          const Info     &       info)
{
    Light *light = dynamic_cast<Light*>(core);

    if(light)
    {
        Node *beacon = light->getBeacon();

        if(beacon)
        {
            const Info& light_info  = CoreInfo(light);
            const Info& beacon_info = NodeInfo(beacon);

            _dotted_edges.push_back(std::make_pair(light_info, beacon_info));
        }
    }
}

void DotFileGeneratorGraphOp::HandleVisitSubTree(      NodeCore * const core,
                                                 const Info     &       info)
{
    VisitSubTree *visitSubTree = dynamic_cast<VisitSubTree*>(core);

    if(visitSubTree)
    {
        Node *subTreeRoot = visitSubTree->getSubTreeRoot();

        if(subTreeRoot)
        {
            OpenGroup(true);

            const Info& visit_sub_tree_info = CoreInfo(visitSubTree);
            const Info& sub_tree_root_info  = NodeInfo(subTreeRoot);

            DefineSimpleEdge(visit_sub_tree_info, sub_tree_root_info);

            CloseGroup();

            traverse(subTreeRoot);
        }
    }
}


void DotFileGeneratorGraphOp::HandleBeaconedChunk(
          StateChunk * const chunk,
    const Info       &       info )
{
    ClipPlaneChunk *clippl = dynamic_cast<ClipPlaneChunk*>(chunk);

    if(clippl)
    {
        Node *beacon = clippl->getBeacon();

        if(beacon)
        {
            const Info& clippl_info = StateChunkInfo(clippl);
            const Info& beacon_info = NodeInfo(beacon);

            _dotted_edges.push_back(std::make_pair(clippl_info, beacon_info));
        }
    }

    LightChunk *light = dynamic_cast<LightChunk*>(chunk);

    if(light)
    {
        Node *beacon = light->getBeacon();

        if(beacon)
        {
            const Info& light_info = StateChunkInfo(light);
            const Info& beacon_info = NodeInfo(beacon);

            _dotted_edges.push_back(std::make_pair(light_info, beacon_info));
        }
    }
}

void DotFileGeneratorGraphOp::HandleSwitchMaterial(
          Material * const material,
    const Info     &       info    )
{
    SwitchMaterial *switchMat = dynamic_cast<SwitchMaterial*>(material);

    if(switchMat)
    {
        UInt32 num = switchMat->editMFMaterials()->size();

        for(UInt32 i = 0; i < num; ++i)
        {
            Material *mat = switchMat->getMaterial(i);

            if(mat)
            {
                bool suppressed = isSuppressed(mat->getType());

                if(suppressed)
                    continue;

                OpenGroup(true);

                std::stringstream label;
                label << "label=" << i;

                const Info &mat_info = MaterialInfo(mat);

                DefineMaterial(mat_info);
                DefineSimpleEdge(info, mat_info, true, label.str());

                CloseGroup();

                HandleChunkMaterial    (mat, mat_info);
                HandleSwitchMaterial   (mat, mat_info);
                HandleMultiPassMaterial(mat, mat_info);
            }
        }
    }
}

void DotFileGeneratorGraphOp::HandleChunkMaterial(
          Material * const material,
    const Info     &       info    )
{
    ChunkMaterial *chunkMat = dynamic_cast<ChunkMaterial*>(material);

    if(chunkMat)
    {
        OpenGroup(false);
        {
            const MFUnrecStateChunkPtr *chunks = chunkMat->getMFChunks();

            MFUnrecStateChunkPtr::const_iterator iter = chunks->begin();
            MFUnrecStateChunkPtr::const_iterator end  = chunks->end();

            for(; iter != end; ++iter)
            {
                StateChunkUnrecPtr statechunk = *iter;

                if(!statechunk)
                    continue;

                bool suppressed = isSuppressed(statechunk->getType());

                if(suppressed)
                    continue;

                const Info &chunk_info = StateChunkInfo(statechunk);

                DefineStateChunk(chunk_info);
                DefineSimpleEdge(info, chunk_info);

                HandleTextureChunk(statechunk, chunk_info);
                HandleBeaconedChunk(statechunk, chunk_info);
            }
        }
        CloseGroup();
    }
}

void DotFileGeneratorGraphOp::HandleMultiPassMaterial(
          Material * const material,
    const Info     &       info    )
{
    MultiPassMaterial *multiPassMat =
      dynamic_cast<MultiPassMaterial*>(material);

    if(multiPassMat)
    {
        UInt32 num = multiPassMat->editMFMaterials()->size();

        for(UInt32 i = 0; i < num; ++i)
        {
            Material *mat = multiPassMat->getMaterials(i);

            if(mat)
            {
                bool suppressed = isSuppressed(mat->getType());

                if(suppressed)
                    continue;

                OpenGroup(true);

                std::stringstream label;
                label << "label=" << i;

                const Info &mat_info = MaterialInfo(mat);

                DefineMaterial(mat_info);
                DefineSimpleEdge(info, mat_info, true, label.str());

                CloseGroup();

                HandleChunkMaterial(mat, mat_info);
                HandleSwitchMaterial(mat, mat_info);
                HandleMultiPassMaterial(mat, mat_info);
            }
        }
    }
}


void DotFileGeneratorGraphOp::HandleAttachment(
          AttachmentContainer * const fc,
    const Info                &       info)
{
    if(_include_attachment)
    {
        if(!fc->getSFAttachments()->getValue().empty())
        {
            const SFAttachmentPtrMap* pAttMap = fc->getSFAttachments();

            AttachmentMap::const_iterator mapIt;
            AttachmentMap::const_iterator mapEnd;

            bool flag = false;

            mapIt  = pAttMap->getValue().begin();
            mapEnd = pAttMap->getValue().end();

            for(; mapIt != mapEnd; ++mapIt)
            {
                AttachmentUnrecPtr att = mapIt->second;

                if(att != NULL)
                {
                    if (_no_name_attachments &&
                        Name::getClassType().getGroupId() == att->getGroupId())
                    {
                        continue;
                    }

                    if(ContainerCollection::getClassType().getGroupId() ==
                       att->getGroupId()                                   )
                    {
                        ContainerCollectionUnrecPtr cc =
                            dynamic_pointer_cast<ContainerCollection>(att);
                        OSG_ASSERT(cc != NULL);

                        const MFUnrecFieldContainerPtr* field =
                          cc->getMFContainers();
                        MFUnrecFieldContainerPtr::const_iterator fIt  =
                            field->begin();
                        MFUnrecFieldContainerPtr::const_iterator fEnd =
                            field->end  ();

                        for(; fIt != fEnd; ++fIt)
                        {
                            // ToDo: Currently only Nodes are handled!
                            // Note: Endless loop might be possible?
                            Node* node = dynamic_cast<Node*>(*fIt);
                            if(node)
                                traverse(node);
                        }
                    }

                    flag = true;
                }
            }

            if(!flag)
                return;

            OpenGroup(true);

            mapIt  = pAttMap->getValue().begin();
            mapEnd = pAttMap->getValue().end();

            for(; mapIt != mapEnd; ++mapIt)
            {
                AttachmentUnrecPtr att = mapIt->second;
                if(att != NULL)
                {
                    if(_no_name_attachments &&
                       Name::getClassType().getGroupId() == att->getGroupId())
                    {
                        continue;
                    }

                    const Info &attachment_info = AttachmentInfo(att);

                    DefineAttachment(attachment_info);
                    DefineAttachmentEdge(info, attachment_info);

                    if(ContainerCollection::getClassType().getGroupId() ==
                       att->getGroupId()                                   )
                    {
                        ContainerCollectionUnrecPtr cc =
                            dynamic_pointer_cast<ContainerCollection>(att);
                        OSG_ASSERT(cc != NULL);

                        const MFUnrecFieldContainerPtr* field =
                          cc->getMFContainers();
                        MFUnrecFieldContainerPtr::const_iterator fIt  =
                            field->begin();
                        MFUnrecFieldContainerPtr::const_iterator fEnd =
                            field->end  ();

                        for(; fIt != fEnd; ++fIt)
                        {
                            // ToDo: Currently only Nodes are handled!
                            // Note: Endless loop might be possible?
                            Node* node = dynamic_cast<Node*>(*fIt);
                            if(node)
                            {
                                const Info& node_info = NodeInfo(node);
                                DefineHoldingEdge(attachment_info, node_info);
                            }
                        }
                    }
                }
            }

            CloseGroup();
        }
    }
}

Action::ResultE DotFileGeneratorGraphOp::traverseLeave(
    Node            * const node,
    Action::ResultE         res )
{
    return res;
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::NodeInfo(
    Node * const node)
{
    MapInfoT::iterator iter = _mapInfo.find(node);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _node_cnt++;

        std::stringstream name, label;

        name  << "Node_" << _node_cnt;
        label << "Node " << _node_cnt;

        if(OSG::getName(node))
            label << "\\n" << OSG::getName(node);

        Info info;

        info.cnt     = _node_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = node->getTypeName();
        info.obj_id  = node;

        return _mapInfo.insert(
            MapInfoT::value_type(node, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::CoreInfo(
    NodeCore * const core)
{
    MapInfoT::iterator iter = _mapInfo.find(core);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _core_cnt++;

        std::string core_name = core->getTypeName();

        std::stringstream name, label;

        name  << "Core_" << _core_cnt;
        label << core_name << " " << _core_cnt;

        if(OSG::getName(core))
            label << "\\n" << OSG::getName(core);

        Info info;

        info.cnt     = _core_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = core_name;
        info.obj_id  = core;

        Light *light = dynamic_cast<Light*>(core);

        if(light && light->getOn())
            info.fontcolor="0.000 1.000 1.000";

        return _mapInfo.insert(
            MapInfoT::value_type(core, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::AttachmentInfo(
    Attachment * const att)
{
    MapInfoT::iterator iter = _mapInfo.find(att);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _attachment_cnt++;

        std::string attachment_name = att->getTypeName();

        std::stringstream name, label;

        name  << "Attachment_" << _attachment_cnt;
        label << attachment_name << " " << _attachment_cnt;

        Name* attName = dynamic_cast<Name*>(att);
        if(attName)
            label << "\\n" << attName->getFieldPtr()->getValue().c_str();

        Info info;

        info.cnt     = _attachment_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = attachment_name;
        info.obj_id  = att;

        return _mapInfo.insert(
            MapInfoT::value_type(att, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::MaterialInfo(
    Material * const material)
{
    MapInfoT::iterator iter = _mapInfo.find(material);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _material_cnt++;

        std::string material_name = material->getTypeName();

        std::stringstream name, label;

        name  << "Material_" << _material_cnt;
        label << material_name << " " << _material_cnt;

        if(OSG::getName(material))
            label << "\\n" << OSG::getName(material);

        Info info;

        info.cnt     = _material_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = material_name;
        info.obj_id  = material;

        return _mapInfo.insert(
            MapInfoT::value_type(material, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info DotFileGeneratorGraphOp::MatrixInfo(
    const Matrix & matrix,
          void   * handler)
{
    MapInfoT::iterator iter = _mapInfo.find(handler);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _matrix_cnt++;

        std::stringstream name, label;

        name  << "Matrix_" << _matrix_cnt;
        label << "Matrix" << " " << _matrix_cnt;

        Info info;

        info.cnt     = _matrix_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = "Matrix";
        info.obj_id  = handler;

        return _mapInfo.insert(
            MapInfoT::value_type(handler, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info DotFileGeneratorGraphOp::EtceteraInfo(
    UInt32 number)
{
    std::stringstream name, label;

    name  << "Etcetera";
    label << "Etcetera";
    label << "\\n" << "number = " << number;

    Info info;

    info.cnt     = 0;
    info.name    = name.str();
    info.label   = label.str();
    info.id      = "Etcetera";
    info.obj_id  = 0;

    return info;
}

DotFileGeneratorGraphOp::Info& DotFileGeneratorGraphOp::ImageInfo(
    Image * const image)
{
    MapInfoT::iterator iter = _mapInfo.find(image);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _image_cnt++;

        std::string image_name = image->getName();

        std::stringstream name, label;

        name  << "Image_" << _image_cnt;
        label << "Image"  << " " << _image_cnt;

        Info info;

        info.cnt     = _image_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = "Image";
        info.obj_id  = image;

        return _mapInfo.insert(
            MapInfoT::value_type(image, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::StateChunkInfo(
    StateChunk * const chunk)
{
    MapInfoT::iterator iter = _mapInfo.find(chunk);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _chunk_cnt++;

        std::string chunk_name = chunk->getTypeName();

        std::stringstream name, label;

        name  << "StateChunk_" << _chunk_cnt;
        label << chunk_name << " " << _chunk_cnt;

        if(OSG::getName(chunk))
            label << "\\n" << OSG::getName(chunk);

        Info info;

        info.cnt     = _chunk_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = chunk_name;
        info.obj_id  = chunk;

        return _mapInfo.insert(
            MapInfoT::value_type(chunk, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::IntegralPropInfo(
          GeoIntegralProperty * const property,
    const char                *       context )
{
    MapInfoT::iterator iter = _mapInfo.find(property);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _integral_prop_cnt++;

        std::string property_name = property->getTypeName();

        std::stringstream name, label;

        name  << "GeoIntegralProperty_" << _integral_prop_cnt;
        label << context;
        label << "\\n" << property_name << " " << _integral_prop_cnt;
        label << "\\n" << "size = " << property->size();

        Info info;

        info.cnt     = _integral_prop_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = property_name+context;
        info.obj_id  = property;

        return _mapInfo.insert(
            MapInfoT::value_type(property, info)).first->second;
    }
}

DotFileGeneratorGraphOp::Info &DotFileGeneratorGraphOp::VectorPropInfo(
          GeoVectorProperty * const property,
    const char              *       context )
{
    MapInfoT::iterator iter = _mapInfo.find(property);

    if(iter != _mapInfo.end())
    {
        return iter->second;
    }
    else
    {
        _vector_prop_cnt++;

        std::string property_name = property->getTypeName();

        std::stringstream name, label;

        name  << "GeoVectorProperty_" << _vector_prop_cnt;
        label << context;
        label << "\\n" << property_name << " " << _vector_prop_cnt;
        label << "\\n" << "size = " << property->size();

        Info info;

        info.cnt     = _vector_prop_cnt;
        info.name    = name.str();
        info.label   = label.str();
        info.id      = property_name+context;
        info.obj_id  = property;

        return _mapInfo.insert(
            MapInfoT::value_type(property, info)).first->second;
    }
}

bool DotFileGeneratorGraphOp::hasInfo(void * handler) const
{
    MapInfoT::const_iterator iter = _mapInfo.find(handler);

    return iter != _mapInfo.end();
}

bool DotFileGeneratorGraphOp::hasEdge(const Info& src, const Info& dst) const
{
    PairObjIdsT edge = std::make_pair(src.obj_id, dst.obj_id);

    return _edges.find(edge) != _edges.end();
}

bool DotFileGeneratorGraphOp::makeEdge(const Info& src, const Info& dst)
{
    PairObjIdsT edge = std::make_pair(src.obj_id, dst.obj_id);

    return !_edges.insert(edge).second;
}

std::ofstream &DotFileGeneratorGraphOp::initialize()
{
    if(!_spStream)
    {
        _spStream.reset(new std::ofstream(_filename.c_str()));

        std::ofstream& stream = *_spStream;

        Colors core_colors, attachment_colors, material_colors;
        Colors state_chunk_colors, property_colors;

        core_colors       .add("set312", 1, 12);
        core_colors       .add("spectral11", 1, 11);
        attachment_colors .add("blues9", 3, 6);
        material_colors   .add("purd9", 5, 7);
        state_chunk_colors.add("greens9", 1, 8);
        property_colors   .add("oranges9", 1, 9);

        _colors["Core"]       = core_colors;
        _colors["Attachment"] = attachment_colors;
        _colors["Material"]   = material_colors;
        _colors["StateChunk"] = state_chunk_colors;
        _colors["Property"]   = property_colors;

        stream << "digraph G {" << std::endl;

        _space++;

        if(_size.length() > 0)
            stream << space() << "Size=" << "\"" << _size << "\";" << std::endl;

        if(_ranksep.length() > 0)
            stream << space() << "ranksep=" << _ranksep << ";" << std::endl;

        if(_nodesep.length() > 0)
            stream << space() << "nodesep=" << _nodesep << ";" << std::endl;

        if(_graph_attributes.length() > 0)
            stream << space() << _graph_attributes << std::endl;
    }

    return *_spStream;
}

void DotFileGeneratorGraphOp::deinitialize(void)
{
    BOOST_FOREACH(const PairInfoT& edge, _dotted_edges)
    {
        DefineDottedEdge(edge.first, edge.second, false);
    }

    if(_spStream)
    {
        std::ofstream& stream = *_spStream;

        stream << "}" << std::endl;
        stream << std::flush;
        stream.close();
    }
}

std::string DotFileGeneratorGraphOp::space(void)
{
    std::string sp("");

    for(UInt32 i = 0; i < _space; ++i)
        sp += "    ";

    return sp;
}

const DotFileGeneratorGraphOp::BrewerColor& DotFileGeneratorGraphOp::getColor(
    const std::string &domain,
    const std::string &name)
{
    MapUsedColorsT::const_iterator iter = _usedColors.find(name);

    if(iter != _usedColors.end())
    {
        return iter->second;
    }
    else
    {
        return
            _usedColors.insert(
                MapUsedColorsT::value_type(
                    name,
                    _colors[domain].color())).first->second;
    }
}

void DotFileGeneratorGraphOp::OpenGroup(bool rank)
{
    std::ofstream &stream = initialize();

    stream << space()
           << "{" << std::endl;

    _space++;

    if(!_no_ranks && rank)
    {
        stream << space()
               << "rank = same;"
               << std::endl;
    }
}

void DotFileGeneratorGraphOp::CloseGroup(void)
{
    std::ofstream& stream = initialize();

    _space--;

    stream << space()
           << "}" << std::endl;
}

void DotFileGeneratorGraphOp::DefineNode(const Info &info)
{
    std::ofstream &stream = initialize();

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=box" << ","
           << "style=filled" << ","
           << "color=black" << ","
           << "fillcolor=gold1" << ","
           << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineCore(const Info &info)
{
    std::ofstream &stream = initialize();

    const BrewerColor &color = getColor("Core", info.id);

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=octagon" << ","
           << "style=filled" << ","
           << "colorscheme=" << color.scheme << ","
           << "color=black" << ","
           << "fillcolor=" << color.number << ",";

    if(!info.fontcolor.empty())
        stream << "fontcolor=\"" << info.fontcolor << "\"" << ",";

    stream << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineAttachment(const Info &info)
{
    std::ofstream &stream = initialize();

    const BrewerColor &color = getColor("Attachment", info.id);

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=ellipse" << ","
           << "style=filled" << ","
           << "colorscheme=" << color.scheme << ","
           << "color=black" << ","
           << "fillcolor=" << color.number << ","
           << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineMaterial(const Info &info)
{
    std::ofstream &stream = initialize();

    const BrewerColor &color = getColor("Material", info.id);

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=hexagon" << ","
           << "style=filled" << ","
           << "colorscheme=" << color.scheme << ","
           << "color=black" << ","
           << "fillcolor=" << color.number << ","
           << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineMatrix(const Info &info)
{
    std::ofstream &stream = initialize();

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=Mcircle" << ","
           << "style=filled" << ","
           << "color=black" << ","
           << "fillcolor=dodgerblue" << ","
           << "width=0.8,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineImage(const Info &info)
{
    std::ofstream &stream = initialize();

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=Msquare" << ","
           << "style=filled" << ","
           << "color=black" << ","
           << "fillcolor=yellow" << ","
           << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineStateChunk(const Info &info)
{
    std::ofstream &stream = initialize();

    const BrewerColor &color = getColor("StateChunk", info.id);

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=parallelogram" << ","
           << "style=filled" << ","
           << "colorscheme=" << color.scheme << ","
           << "color=black" << ","
           << "fillcolor=" << color.number << ","
           << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineProperty(const Info &info)
{
    std::ofstream &stream = initialize();

    const BrewerColor &color = getColor("Property", info.id);

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=Mdiamond" << ","
           << "style=filled" << ","
           << "colorscheme=" << color.scheme << ","
           << "color=black" << ","
           << "fillcolor=" << color.number << ","
           << "width=2.0,height=1.5"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineEtceteraNode(const Info &info)
{
    std::ofstream &stream = initialize();

    stream << space()
           << info.name << " "
           << "["
           << "label=\"" << info.label << "\"" << ","
           << "shape=box" << ","
           << "style=filled" << ","
           << "color=black" << ","
           << "fillcolor=firebrick1" << ","
           << "width=2.0,height=0.8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineHoldingEdge(const Info &src_info,
                                                const Info &dst_info)
{
    if(makeEdge(src_info, dst_info))
        return;

    std::ofstream &stream = initialize();

    stream << space()
           << src_info.name << " "
           << "->" << " "
           << dst_info.name << " "
           << "["
           << "dir=both" << ","
           << "arrowtail=diamond" << ","
           << "weight=2"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineNodeEdge(const Info &parent_info,
                                             const Info &node_info  )
{
    if(makeEdge(parent_info, node_info))
        return;

    std::ofstream &stream = initialize();

    stream << space()
           << parent_info.name << " "
           << "->" << " "
           << node_info.name << " "
           << "["
           << "penwidth=3.0" << ","
           << "arrowsize=2.0" << ","
           << "weight=8"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineCoreEdge(const Info &node_info,
                                             const Info &core_info)
{
    if(makeEdge(node_info, core_info))
        return;

    std::ofstream &stream = initialize();

    stream << space()
           << node_info.name << " "
           << "->" << " "
           << core_info.name << " "
           << "["
           << "dir=both" << ","
           << "arrowtail=diamond" << ","
           << "weight=4"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineAttachmentEdge(const Info &node_info,
                                                   const Info &att_info)
{
    if(makeEdge(node_info, att_info))
        return;

    std::ofstream &stream = initialize();

    stream << space()
           << node_info.name << " "
           << "->" << " "
           << att_info.name << " "
           << "["
           << "style=dotted" << ","
           << "arrowhead=vee" << ","
           << "weight=2"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineSimpleEdge(
    const Info        &src_info,
    const Info        &dst_info,
          bool         constraint,
          std::string  attribute )
{
    if(makeEdge(src_info, dst_info))
        return;

    std::ofstream &stream = initialize();

    stream << space()
           << src_info.name << " "
           << "->" << " "
           << dst_info.name << " "
           << "["
           << "arrowhead=vee" << ",";

    if(!constraint)
        stream << "constraint=false" << ",";

    if(!attribute.empty())
        stream << attribute << ",";

    stream << "weight=1"
           << "];"
           << std::endl;
}

void DotFileGeneratorGraphOp::DefineDottedEdge(
    const Info        &src_info,
    const Info        &dst_info,
          bool         constraint,
          std::string  attribute )
{
    if(makeEdge(src_info, dst_info))
        return;

    std::ofstream &stream = initialize();

    stream << space()
           << src_info.name << " "
           << "->" << " "
           << dst_info.name << " "
           << "["
           << "style=dotted" << ","
           << "arrowhead=vee" << ",";

    if(!constraint)
        stream << "constraint=false" << ",";

    if(!attribute.empty())
        stream << attribute << ",";

    stream << "weight=1"
           << "];"
           << std::endl;
}

OSG_END_NAMESPACE
