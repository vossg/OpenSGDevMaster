/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#include <OSGColladaInstanceGeometry.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaEffect.h>

#include <OSGChunkMaterial.h>
#include <OSGGroup.h>
#include <OSGMaterialGroup.h>
#include <OSGNameAttachment.h>

#include <1.4/dom/domEffect.h>
#include <1.4/dom/domMaterial.h>
#include <1.4/dom/domGeometry.h>
#include <1.4/dom/domInstance_geometry.h>

OSG_BEGIN_NAMESPACE

void ColladaInstanceGeometry::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read:\n"));
    
    domInstance_geometryRef  instGeo = getDOMElementAs<domInstance_geometry>();
    
    daeURI                   geoUri  = instGeo->getUrl();
    domGeometryRef           geo     =
        daeSafeCast<domGeometry>(geoUri.getElement());
    
    setInstDOMElement(geo);
    
    ColladaGeometryRefPtr    colGeo  = getUserDataAs<ColladaGeometry>(geo);
    
    if(colGeo == NULL)
    {
        colGeo = ColladaGeometry::create(geo, getGlobal());
        addElement(colGeo);
        
        colGeo->read();
    }
    
    _node = Node::create();
    _node->setCore(Group::create());
    
    if(geo->getName() != NULL)
        setName(_node, geo->getName());
    
    const domBind_materialRef matBindings = instGeo->getBind_material();

    if(matBindings != NULL)
    {
        domTechnique_Array &techniques = matBindings->getTechnique_array();
        bool                matHandled = false;

        OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: Num <technique> [%d]\n",
                         techniques.getCount()));

        // process <technique> elements -- currently none are handled
        for(UInt32 i = 0; i < techniques.getCount(); ++i)
        {
            daeElementRefArray &techniqueCont =
                techniques[i]->getContents();

            for(UInt32 j = 0; j < techniqueCont.getCount(); ++j)
            {
                daeElement *elem = techniqueCont[j];

                OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: techniqueCont [%u] [%s] [%s]\n",
                                 j, elem->getTypeName(), elem->getElementName()));
            }
        }
        
        // process <technique_common> element
        if(!matHandled)
        {
            domBind_material::domTechnique_commonRef technique =
                matBindings->getTechnique_common();

            const domInstance_material_Array &instMats =
                technique->getInstance_material_array();

            OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: "
                             "<technique_common> has [%u] <instance_materials>\n",
                             instMats.getCount()));

            for(UInt32 i = 0; i < instMats.getCount(); ++i)
            {
                OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: "
                                 "symbol [%s] target [%s]\n",
                                 instMats[i]->getSymbol(),
                                 instMats[i]->getTarget().getURI()));

                daeElementRef  elem = instMats[i]->getTarget().getElement();
                domMaterialRef mat  = daeSafeCast<domMaterial>(elem);

                if(mat == NULL)
                    continue;

                const domInstance_effectRef instEffect =
                    mat->getInstance_effect();

                xsAnyURI effectUri = instEffect->getUrl();

                OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: "
                                 "effectUri [%s] [%d]\n",
                                 effectUri.getURI(),
                                 effectUri.getState()));

                daeElementRef effectElem = effectUri.getElement();
                domEffectRef  effect     = daeSafeCast<domEffect>(effectElem);

                OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: "
                                 "effect [%s] [%s]\n",
                                 effect->getTypeName(),
                                 effect->getElementName()));

                ColladaEffectRefPtr colEffect =
                    getUserDataAs<ColladaEffect>(effect);

                if(colEffect == NULL)
                {
                    colEffect = ColladaEffect::create(effect, getGlobal());
                    addElement(colEffect);
                    
                    colEffect->read();
                }

                std::string effectKey = instMats[i]->getSymbol();

                _matMap[effectKey] = colEffect->getMaterial();

                const domInstance_material::domBind_Array &binds =
                    instMats[i]->getBind_array();
                
                OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: "
                                 "[%u] bindings\n", binds.getCount()));
                
                for(UInt32 j = 0; j < binds.getCount(); ++j)
                {
                    std::string target = binds[j]->getTarget();

                    if(target[0] == '#')
                        target.erase(0, 1);

                    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: Bind: [%s] [%s]\n",
                                     binds[j]->getSemantic(), target.c_str()));

                    UInt32 texIdx =
                        colEffect->getTexBinding(binds[j]->getSemantic());

                    _texBindingsMap[target].push_back(texIdx);

                    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: Bound: [%s] -> [%u]\n",
                                     target.c_str(), texIdx));
                }

                const domInstance_material::domBind_vertex_input_Array &vertBinds =
                    instMats[i]->getBind_vertex_input_array();
                
                OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: [%u] vertex bindings\n",
                                 vertBinds.getCount()));

                for(UInt32 j = 0; j < vertBinds.getCount(); ++j)
                {
                    std::string target = vertBinds[j]->getInput_semantic();

                    if(target[0] == '#')
                        target.erase(0, 1);

                    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: Bind: [%s] [%s]\n",
                                     vertBinds[j]->getSemantic(), target.c_str()));

                    UInt32 texIdx =
                        colEffect->getTexBinding(vertBinds[j]->getSemantic());

                    if(texIdx != 0xFFFF)
                        _texBindingsMap[target].push_back(texIdx);

                    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read: Bound: [%s] -> [%u]\n",
                                     target.c_str(), texIdx));
                }
            }
        }
    }
    
    ColladaGeometry::MatGeoMapIt geoIt  = colGeo->beginGeo();
    ColladaGeometry::MatGeoMapIt geoEnd = colGeo->endGeo  ();
    
    for(; geoIt != geoEnd; ++geoIt)
    {
        for(UInt32 i = 0; i < geoIt->second.size(); ++i)
        {
            MaterialGroupUnrecPtr matGroup     = MaterialGroup::create();
            NodeUnrecPtr          matGroupNode = Node         ::create();
            
            NodeUnrecPtr          geoNode      = Node         ::create();
            
            MaterialMapIt matIt = _matMap.find(geoIt->first);

            ChunkMaterial *cm = NULL;
            
            if(matIt != _matMap.end())
                cm = matIt->second;
            
            updateGeoTexBindings(geoIt->second[i]);

            geoNode     ->setCore    (geoIt->second[i]->geo);

            matGroup    ->setMaterial(cm                   );
            matGroupNode->setCore    (matGroup             );
            matGroupNode->addChild   (geoNode              );
            
            _node       ->addChild   (matGroupNode         );
        }
    }
}

NodeTransitPtr ColladaInstanceGeometry::createInstance(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceGeometry::createInstance:\n"));
    
    NodeTransitPtr retVal(_node.get());
    
    ++_instCount;
    
    return retVal;
}

ColladaInstanceGeometry::ColladaInstanceGeometry(
    domInstance_geometry *instGeo, ColladaGlobal *global)
    
    : Inherited(instGeo, global)
{
    // nothing to do
}

ColladaInstanceGeometry::~ColladaInstanceGeometry(void)
{
    // nothing to do
}

void ColladaInstanceGeometry::updateGeoTexBindings(
    ColladaGeometry::GeometryInfo *geoInfo)
{
    OSG_COLLADA_LOG(("ColladaInstanceGeometry::updateGeoTexBindings:\n"));
    
    TexBindingsMap::iterator texIt  = _texBindingsMap.begin();
    TexBindingsMap::iterator texEnd = _texBindingsMap.end  ();

    for(; texIt != texEnd; ++texIt)
    {
        for(UInt32 i = 0; i < texIt->second.size(); ++i)
        {
            OSG_COLLADA_LOG(("ColladaInstanceGeometry::updateGeoTexBindings: "
                             "Bind [%s] -> [%d]\n",
                             texIt->first.c_str(), texIt->second[i]));
            
            ColladaGeometry::PropIndexPair  propIdxPair(NULL, NULL);
            
            ColladaGeometry::PropIndexMapIt propIt =
                geoInfo->propIndexMap.find(texIt->first);

            if(propIt != geoInfo->propIndexMap.end())
                propIdxPair = propIt->second;
            
            if(propIdxPair.first != NULL && propIdxPair.second != NULL)
            {
                OSG_COLLADA_LOG(("ColladaInstanceGeometry::updateGeoTexBindings: "
                                 "Idx: [%s] Val: [%s]\n",
                                 propIdxPair.second->getType().getCName(),
                                 propIdxPair.first ->getType().getCName() ));
                
                geoInfo->geo->setProperty(
                    propIdxPair.first,
                    Geometry::TexCoordsIndex + texIt->second[i]);
                geoInfo->geo->setIndex   (
                    propIdxPair.second,
                    Geometry::TexCoordsIndex + texIt->second[i]);
            }
        }
    }
}


OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
