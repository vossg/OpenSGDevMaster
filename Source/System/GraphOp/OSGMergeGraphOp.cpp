/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <boost/bind.hpp>

#include "OSGMergeGraphOp.h"
#include "OSGDirectionalLight.h"
#include "OSGSpotLight.h"
#include "OSGLight.h"
#include "OSGPointLight.h"
#include "OSGSwitch.h"
#include "OSGDistanceLOD.h"
#include "OSGBillboard.h"
#include "OSGMaterialGroup.h"
#include "OSGComponentTransform.h"
#include "OSGPrimitiveIterator.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGGraphOpFactory.h"

// need to implement the merge methods amz
#define OSG2_MERGE_MISSING

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MergeGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A class used to optimize geometries a bit.

*/

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpRefPtr newOp = MergeGraphOp::create();

    GraphOpFactory::the()->registerOp(newOp);
    return true;
}
static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

MergeGraphOp::MergeGraphOp(const char* name): GraphOp(name),
    _secondary_color_is_vector(false),
    _texcoord0_is_vector(false),
    _texcoord1_is_vector(false),
    _texcoord2_is_vector(false),
    _texcoord3_is_vector(false)
{
}

MergeGraphOp::~MergeGraphOp(void)
{
}

MergeGraphOpTransitPtr
MergeGraphOp::create(void)
{
    return MergeGraphOpTransitPtr(new MergeGraphOp);
}

GraphOpTransitPtr MergeGraphOp::clone(void)
{
    return GraphOpTransitPtr(new MergeGraphOp);
}

UInt32 countNodes(Node * const node)
{
    if (node == NULL)
        return 0;

    UInt32 total = 1;
    for (UInt32 i = 0; i < node->getNChildren(); ++i)
        total += countNodes(node->getChild(i));
    return total;
}

bool MergeGraphOp::traverse(Node * node)
{
    // This is a hack and should be treated as such.
    // The fact that it helps means there is something wrong with
    // the merger. FIXME!!!
    UInt32 next = countNodes(node);
    SINFO << "MergeGraphOp::traverse: Number of nodes before merge: " 
          << next << endLog;
    bool result = true;
    UInt32 current;
    do {
        current = next;
        result &= mergeOnce(node);
        if (!result)
            break;
        next = countNodes(node);
    } while (next < current);

    SINFO << "MergeGraphOp::traverse: Number of nodes after merge: " 
          << current << endLog;

    return result;
}

void MergeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   

    ps("color_is_vector", _color_is_vector);
    ps("secondary_color_is_vector", _secondary_color_is_vector);
    ps("texcoord_is_vector", _texcoord0_is_vector);
    ps("texcoord0_is_vector", _texcoord0_is_vector);
    ps("texcoord1_is_vector", _texcoord1_is_vector);
    ps("texcoord2_is_vector", _texcoord2_is_vector);
    ps("texcoord3_is_vector", _texcoord3_is_vector);

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("MergeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string MergeGraphOp::usage(void)
{
    return 
    "Merge: merge all geometries in a subtree\n"
    "  Tries to merge all Geometries in a subtree into the minimal number.\n"
    "  of Nodes. Flattens Transformations and transforms indices on the way.\n"
    "Params: name (type, default)\n"
    " (The following params are useful for transforming tangent space vectors.)\n"
    "  color_is_vector  (bool, false): transform color as if it were a normal\n"
    "  secondary_color_is_vector  (bool, false): transform secondary color as if it were a normal\n"
    "  texcoord_is_vector  (bool, false): transform texcoord0 as if it were a normal\n"
    "  texcoord0_is_vector  (bool, false): transform texcoord0 as if it were a normal\n"
    "  texcoord1_is_vector  (bool, false): transform texcoord1 as if it were a normal\n"
    "  texcoord2_is_vector  (bool, false): transform texcoord2 as if it were a normal\n"
    "  texcoord3_is_vector  (bool, false): transform texcoord3 as if it were a normal\n"
    ;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool MergeGraphOp::mergeOnce(Node * node)
{
    std::list<Node const *> tempList;
    tempList.clear();
    tempList.splice(tempList.end(),_excludeListNodes);
    makeExcludeList(node);
    bool result = GraphOp::traverse(node);
    _excludeListNodes.clear();    
    _excludeListNodes.splice(_excludeListNodes.end(),tempList);
    return result;
}

void MergeGraphOp::makeExcludeList(Node * node)
{
    /*
    ::traverse(node,
        osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
        MergeGraphOp,
        NodePtr>(this,&MergeGraphOp::excludeListEnter),
        osgTypedMethodFunctor2ObjPtrCPtrRef<Action::ResultE,
        MergeGraphOp,
        NodePtr,
        Action::ResultE>(this,&MergeGraphOp::excludeListLeave));
    */
    ::traverse(node, 
               boost::bind(&MergeGraphOp::excludeListEnter, this, _1    ),
               boost::bind(&MergeGraphOp::excludeListLeave, this, _1, _2) );
}


Action::ResultE MergeGraphOp::excludeListEnter(Node * const node)
{
//    if (node==NULL) ; else ;    
    return Action::Continue;
}

Action::ResultE MergeGraphOp::excludeListLeave(Node * const node, Action::ResultE res)
{
    DirectionalLight *dlight = dynamic_cast<DirectionalLight *>(node->getCore());
    if (dlight!=NULL)
        addToExcludeList(dlight->getBeacon());
    
    Light *light = dynamic_cast<Light *>(node->getCore());
    if (light!=NULL)
        addToExcludeList(light->getBeacon());    
    
    PointLight *plight = dynamic_cast<PointLight *>(node->getCore());
    if (plight!=NULL)
        addToExcludeList(plight->getBeacon());
    
    SpotLight *slight = dynamic_cast<SpotLight *>(node->getCore());
    if (slight!=NULL)
        addToExcludeList(slight->getBeacon());    
    
    return res;
}

Action::ResultE MergeGraphOp::traverseEnter(Node * const node)
{
    Switch *switch_ = dynamic_cast<Switch *>(node->getCore());
    if (switch_!=NULL) return Action::Skip;
    
    DistanceLOD *dlod = dynamic_cast<DistanceLOD *>(node->getCore());
    if (dlod!=NULL) return Action::Skip;
    
    //leaf, don't enter, cause no job here
    if (isLeaf(node)) return Action::Skip;
    
    return Action::Continue;    
}

Action::ResultE MergeGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
    processGroups(node);
    processTransformations(node);
    processGeometries(node);
    return res;
}

bool MergeGraphOp::isLeaf(Node * const node)
{
    if (node->getMFChildren()->begin() ==
        node->getMFChildren()->end  ()) return true;
    else return false;    
}

/*! checks whether a node is a group and nothing else
*/
bool MergeGraphOp::isGroup(Node * const node)
{
    if(  node->getCore()->getType().isDerivedFrom( Group::getClassType()              ) &&
        !node->getCore()->getType().isDerivedFrom( Transform::getClassType()          ) &&
        !node->getCore()->getType().isDerivedFrom( ComponentTransform::getClassType() ) &&
        !node->getCore()->getType().isDerivedFrom( Switch::getClassType()             ) &&
        !node->getCore()->getType().isDerivedFrom( MaterialGroup::getClassType()      ) &&
        !node->getCore()->getType().isDerivedFrom( DistanceLOD::getClassType()        ) &&
        !node->getCore()->getType().isDerivedFrom( Billboard::getClassType()          )) 
        return true;
    else return false;
}

void MergeGraphOp::processGroups(Node * const node)
{
    MFUnrecChildNodePtr::const_iterator mfit = node->getMFChildren()->begin();
    MFUnrecChildNodePtr::const_iterator mfen = node->getMFChildren()->end  ();
    std::vector<Node *> toAdd;
    std::vector<Node *> toSub;
    
    for ( ; mfit != mfen; ++mfit )
    {
        bool special=isInExcludeList(*mfit);
        bool leaf=isLeaf(*mfit);
        
        if (isGroup(*mfit))
        {
            if (!leaf && !special)
            {
                MFUnrecChildNodePtr::const_iterator it2 = 
                    (*mfit)->getMFChildren()->begin();
                MFUnrecChildNodePtr::const_iterator en2 = 
                    (*mfit)->getMFChildren()->end  ();
                
                for ( ; it2 != en2; ++it2 )
                {
                    toAdd.push_back(*it2);
                }                
            }
            
            if (!special)
            {
                toSub.push_back(*mfit);
                continue;
            }
            
            if (leaf && special)
            {
                //what to do?
            }
            if (!leaf && special)
            {
                //what to do?
            }
            continue;
        }
        else if ((*mfit)->getCore()->getType().isDerivedFrom( 
                     MaterialGroup::getClassType() ))
        {
            MaterialGroup *mg = 
                dynamic_cast<MaterialGroup *>((*mfit)->getCore());
            
            MFUnrecChildNodePtr::const_iterator it2 = 
                (*mfit)->getMFChildren()->begin();
            MFUnrecChildNodePtr::const_iterator en2 = 
                (*mfit)->getMFChildren()->end  ();
            
            bool empty=true;
            
            for ( ; it2 != en2; ++it2 )
            {
                if (!isInExcludeList(*it2))
                {
                    //check if geometry
                    if ((*it2)->getCore()->getType().isDerivedFrom(
                            Geometry::getClassType()))
                    {
                        if(!isLeaf(*it2))
                        {
                            //hmm...bad tree...
                            empty=false;
                        }
                        else
                        {                                
                            //it is a leaf geometry, so apply the transformation
                            Geometry *geo = 
                                dynamic_cast<Geometry *>((*it2)->getCore());

                            geo->setMaterial(mg->getMaterial());

                            toAdd.push_back(*it2);                            
                        }
                    } 
                    else 
                    {
                        empty=false;
                    }
                } 
                else 
                {
                    empty=false;                
                }
            }
            
            if (empty) 
                toSub.push_back(*mfit);
        }
    }
    
    std::vector<Node *>::const_iterator vit = toAdd.begin();
    std::vector<Node *>::const_iterator ven = toAdd.end  ();
    
    for ( ; vit != ven; ++vit )
    {
        node->addChild(*vit);
    }
    
    vit = toSub.begin();
    ven = toSub.end  ();
    
    for ( ; vit != ven; ++vit )
    {
        node->subChild(*vit);
    }
}

void MergeGraphOp::processTransformations(Node * const node)
{
    MFUnrecChildNodePtr::const_iterator mfit = node->getMFChildren()->begin();
    MFUnrecChildNodePtr::const_iterator mfen = node->getMFChildren()->end  ();
    std::vector<Node *> toAdd;
    std::vector<Node *> toSub;
    
    for ( ; mfit != mfen; ++mfit )
    {
        bool special=isInExcludeList(*mfit);
        bool leaf=isLeaf(*mfit);
        bool empty=true;
        
        //if a transformation:
        if ((*mfit)->getCore()->getType().isDerivedFrom(
                Transform::getClassType()))
        {        
            if (!leaf && !special)
            {
                //try to apply it to children geometries
                //move all "moveable" children one level up
                //if empty after that, delete it
                MFUnrecChildNodePtr::const_iterator it2 = 
                    (*mfit)->getMFChildren()->begin();
                MFUnrecChildNodePtr::const_iterator en2 = 
                    (*mfit)->getMFChildren()->end  ();
                
                for ( ; it2 != en2; ++it2 )
                {
                    if (!isInExcludeList(*it2))
                    {
                        //check if geometry
                        if ((*it2)->getCore()->getType().isDerivedFrom(
                                Geometry::getClassType()))
                        {
                            if(!isLeaf(*it2))
                            {
                                //hmm...bad tree...
                                empty=false;
                            }
                            else
                            {                                
                                //it is a leaf geometry, so apply the transformation
                                Geometry *geo_old = 
                                    dynamic_cast<Geometry *>(
                                        (*it2)->getCore());
                                //GeometryPtr geo = geo_old->clone();
                                GeometryUnrecPtr geo = 
                                    dynamic_pointer_cast<Geometry>(
                                        OSG::deepClone(geo_old, "Material"));

                                Transform *t = 
                                    dynamic_cast<Transform *>(
                                        (*mfit)->getCore());

                                GeoPnt3fProperty *pos  = dynamic_cast<GeoPnt3fProperty *>(geo->getPositions());
                                GeoVec3fProperty *norm = dynamic_cast<GeoVec3fProperty *>(geo->getNormals());
                                GeoColor3fProperty *color = dynamic_cast<GeoColor3fProperty *>(geo->getColors());
                                GeoColor3fProperty *scolor = dynamic_cast<GeoColor3fProperty *>(geo->getSecondaryColors());
                                GeoVec3fProperty *texcoord0 = dynamic_cast<GeoVec3fProperty *>(geo->getTexCoords());
                                GeoVec3fProperty *texcoord1 = dynamic_cast<GeoVec3fProperty *>(geo->getTexCoords1());
                                GeoVec3fProperty *texcoord2 = dynamic_cast<GeoVec3fProperty *>(geo->getTexCoords2());
                                GeoVec3fProperty * texcoord3 = dynamic_cast<GeoVec3fProperty *>(geo->getTexCoords3());

                                Matrix m=t->getMatrix();

                                if (pos!=NULL) 
                                {
                                    for (UInt32 i=0; i<pos->getSize(); i++)
                                    {
                                        Pnt3f p=pos->getValue(i);
                                        m.multFull(p, p);
                                        pos->setValue(p,i);
                                    }
                                }
                                
                                if (norm!=NULL)
                                {
                                    for (UInt32 i=0; i<norm->getSize(); i++)
                                    {
                                        Vec3f n=norm->getValue(i);
                                        m.mult(n, n);
                                        n.normalize();
                                        norm->setValue(n,i);
                                    }
                                }

                                if (color!=NULL && _color_is_vector)
                                {
                                    for (UInt32 i=0; i<color->getSize(); i++)
                                    {
                                        Color3f c = color->getValue(i);
                                        Vec3f v;
                                        v.setValue(c.getValuesRGB());
                                        m.mult(v, v);
                                        v.normalize();
                                        c.setValuesRGB(v[0], v[1], v[2]);
                                        color->setValue(c,i);
                                    }
                                }

                                if (scolor!=NULL && _secondary_color_is_vector)
                                {
                                    for (UInt32 i=0; i<scolor->getSize(); i++)
                                    {
                                        Color3f c = scolor->getValue(i);
                                        Vec3f v;
                                        v.setValue(c.getValuesRGB());
                                        m.mult(v, v);
                                        v.normalize();
                                        c.setValuesRGB(v[0], v[1], v[2]);
                                        scolor->setValue(c,i);
                                    }
                                }

                                if (texcoord0!=NULL && _texcoord0_is_vector)
                                {
                                    for (UInt32 i=0; i<texcoord0->getSize(); i++)
                                    {
                                        Vec3f v=texcoord0->getValue(i);
                                        m.mult(v, v);
                                        v.normalize();
                                        texcoord0->setValue(v,i);
                                    }
                                }

                                if (texcoord1!=NULL && _texcoord1_is_vector)
                                {
                                    for (UInt32 i=0; i<texcoord1->getSize(); i++)
                                    {
                                        Vec3f v=texcoord1->getValue(i);
                                        m.mult(v, v);
                                        v.normalize();
                                        texcoord1->setValue(v,i);
                                    }
                                }

                                if (texcoord2!=NULL && _texcoord2_is_vector)
                                {
                                    for (UInt32 i=0; i<texcoord2->getSize(); i++)
                                    {
                                        Vec3f v=texcoord2->getValue(i);
                                        m.mult(v, v);
                                        v.normalize();
                                        texcoord2->setValue(v,i);
                                    }
                                }

                                if (texcoord3!=NULL && _texcoord3_is_vector)
                                {
                                    for (UInt32 i=0; i<texcoord3->getSize(); i++)
                                    {
                                        Vec3f v=texcoord3->getValue(i);
                                        m.mult(v, v);
                                        v.normalize();
                                        texcoord3->setValue(v,i);
                                    }
                                }
                                (*it2)->setCore(geo);
                                toAdd.push_back(*it2);
                            }
                        } else empty=false;
                    } else empty=false;
                }                
            }
            
            //now check whether we have to remove it
            if ((empty||leaf) && !special)
            {
                toSub.push_back(*mfit);
                continue;
            }
            
            if (leaf && special)
            {
                //what to do?
            }
            if (!leaf && special)
            {
                //what to do?
            }
            continue;
        }
    }
    
    std::vector<Node *>::const_iterator vit = toAdd.begin();
    std::vector<Node *>::const_iterator ven = toAdd.end  ();
    
    for ( ; vit != ven; ++vit )
    {
        node->addChild(*vit);
    }
    
    vit = toSub.begin();
    ven = toSub.end  ();
    
    for ( ; vit != ven; ++vit )
    {
        node->subChild(*vit);
    }
}

void MergeGraphOp::processGeometries(Node * const node)
{
    MFUnrecChildNodePtr::const_iterator mfit = node->getMFChildren()->begin();
    MFUnrecChildNodePtr::const_iterator mfen = node->getMFChildren()->end  ();

    std::vector<Node        *> toSub;
    std::vector<NodeUnrecPtr > toAdd;
    
    for ( ; mfit != mfen; ++mfit )
    {
        bool special=isInExcludeList(*mfit);
        
        if ((*mfit)->getCore()->getType().isDerivedFrom(
                Geometry::getClassType()))
        {
#ifndef OSG2_MERGE_MISSING
            Geometry *geo = dynamic_cast<Geometry *>((*mfit)->getCore());
#endif
            //if a geometry, try to merge it in another geometry
            //if successfull, delete it.
            //check also if it is added for exclusion

            bool inSubList=false;

            std::vector<Node *>::const_iterator it3=toSub.begin();
            std::vector<Node *>::const_iterator en3=toSub.end();

            for ( ; it3 != en3; ++it3 ) 
                if (*it3==*mfit) { inSubList=true; break; }

            if (!special && !inSubList)
            {
                //ok, try
                MFUnrecChildNodePtr::const_iterator it2=mfit+1;
                Geometry *new_geo=NULL;
                for ( ; it2!=mfen; ++it2)
                {
                    if (!isInExcludeList(*it2) && (*it2)->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
                    {
#ifndef OSG2_MERGE_MISSING
                        Geometry *geo2 = dynamic_cast<Geometry *>((*it2)->getCore());
                        if (geo->isMergeable(geo2))
                        {
                            // HACK merge crashes when indices == NULL!
                            if(geo->getIndices() == NULL)
                                OSG::createSharedIndex(geo);
                            if(geo2->getIndices() == NULL)
                                OSG::createSharedIndex(geo2);
                            if (new_geo==NULL)
                            {
                                new_geo=Geometry::create();
                                if (new_geo->merge(geo))
                                    toSub.push_back(*it);
                                else FWARNING(("MergeGraphOp: processGeometries problem 1\n"));

                                if (new_geo->merge(geo2))
                                    toSub.push_back(*it2);
                                else FWARNING(("MergeGraphOp: processGeometries problem 2\n"));
                            }
                            else
                            {
                                if (new_geo->merge(geo2))
                                    toSub.push_back(*it2);
                            }
                        }
#endif
                    }
                }
                if (new_geo!=NULL)
                {
                    NodeUnrecPtr new_node=Node::create();
                    new_node->setCore(new_geo);

                    toAdd.push_back(new_node);
                }
            }
            else
            {
                //hmm...have to skip it
            }
        }
    }
    
    std::vector<NodeUnrecPtr>::const_iterator ait = toAdd.begin();
    std::vector<NodeUnrecPtr>::const_iterator aen = toAdd.end  ();
    
    for ( ; ait != aen; ++ait )
    {
        node->addChild(*ait);
    }

    std::vector<Node *>::const_iterator sit = toSub.begin();
    std::vector<Node *>::const_iterator sen = toSub.end  ();
    
    for ( ; sit != sen; ++sit )
    {
        node->subChild(*sit);
    }
}
