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

#include "OSGSplitGraphOp.h"
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
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SplitGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    A class used to optimize geometries a bit.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = SplitGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

SplitGraphOp::SplitGraphOp(UInt16 max_polygons, const char* name) :
    Inherited    (name        ),
    _max_polygons(max_polygons)
{
}

SplitGraphOp::~SplitGraphOp(void)
{
}

SplitGraphOpTransitPtr
SplitGraphOp::create(UInt16 maxPolygons)
{
    return SplitGraphOpTransitPtr(new SplitGraphOp(maxPolygons));
}

GraphOpTransitPtr SplitGraphOp::clone(void)
{
    return GraphOpTransitPtr(new SplitGraphOp());
}

bool SplitGraphOp::traverse(Node *root)
{
    // If the root node is not a Group, make it one
    if(isLeaf(root))
    {
        NodeUnrecPtr n = makeNodeFor(root->getCore());
        
        root->setCore(Group::create());
        root->addChild(n);
    }  

    return GraphOp::traverse(root);
}

void SplitGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("max_polygons", _max_polygons);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("SplitGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string SplitGraphOp::usage(void)
{
    return 
    "Split: Split large geometries into smaller ones\n"
    "Params: name (type, default)\n"
    "  max_polygons (UInt32, 1000): maximum number of polygons allowed per Geo\n";
}

void SplitGraphOp::setMaxPolygons(UInt16 max_polygons)
{
    _max_polygons = max_polygons;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE SplitGraphOp::traverseEnter(Node * const node)
{
    if (isLeaf(node)) return Action::Skip;

    Switch *switch_ = dynamic_cast<Switch *>(node->getCore());
    if (switch_!=NULL) return Action::Skip;
    
    DistanceLOD *dlod = dynamic_cast<DistanceLOD *>(node->getCore());
    if (dlod!=NULL) return Action::Skip;   
    
    return Action::Continue;    
}

#define addPoints( INDEX , LENGTH )                                     \
for (UInt32 k=0; k<LENGTH; k++)                                         \
{                                                                       \
    int posInd=it.getPositionIndex(k+INDEX);                            \
    if (pni[geoIndex])                                                  \
    {                                                                   \
        if (pni[geoIndex][posInd]==-1)                                  \
        {                                                               \
            pnts[geoIndex]->push_back(it.getPosition(k+INDEX));         \
            pni[geoIndex][posInd]=pnts[geoIndex]->size()-1;             \
        }                                                               \
        }                                                               \
    int normInd=it.getNormalIndex(k+INDEX);                             \
    if (nni[geoIndex])                                                  \
    {                                                                   \
        if (nni[geoIndex][normInd]==-1)                                 \
        {                                                               \
            normals[geoIndex]->push_back(it.getNormal(k+INDEX));        \
            nni[geoIndex][normInd]=normals[geoIndex]->size()-1;         \
        }                                                               \
    }                                                                   \
    int colInd=it.getColorIndex(k+INDEX);                               \
    if (cni[geoIndex])                                                  \
    {                                                                   \
        if (cni[geoIndex][colInd]==-1)                                  \
        {                                                               \
            colors[geoIndex]->push_back(it.getColor(k+INDEX));          \
            cni[geoIndex][colInd]=colors[geoIndex]->size()-1;           \
        }                                                               \
    }                                                                   \
    int scolInd=it.getSecondaryColorIndex(k+INDEX);                     \
    if (sni[geoIndex])                                                  \
    {                                                                   \
        if (sni[geoIndex][scolInd]==-1)                                 \
        {                                                               \
            scolors[geoIndex]->push_back(it.getSecondaryColor(k+INDEX));\
            sni[geoIndex][scolInd]=scolors[geoIndex]->size()-1;         \
        }                                                               \
    }                                                                   \
    int texInd=it.getTexCoordsIndex(k+INDEX);                           \
    if (tni[geoIndex])                                                  \
    {                                                                   \
        if (tni[geoIndex][texInd]==-1)                                  \
        {                                                               \
            tex[geoIndex]->push_back(it.getTexCoords(k+INDEX));         \
            tni[geoIndex][texInd]=tex[geoIndex]->size()-1;              \
        }                                                               \
    }                                                                   \
    int tex1Ind=it.getTexCoordsIndex1(k+INDEX);                         \
    if (t1ni[geoIndex])                                                 \
    {                                                                   \
        if (t1ni[geoIndex][tex1Ind]==-1)                                \
        {                                                               \
            tex1[geoIndex]->push_back(it.getTexCoords1(k+INDEX));       \
            t1ni[geoIndex][tex1Ind]=tex1[geoIndex]->size()-1;           \
        }                                                               \
    }                                                                   \
    int tex2Ind=it.getTexCoordsIndex2(k+INDEX);                         \
    if (t2ni[geoIndex])                                                 \
    {                                                                   \
        if (t2ni[geoIndex][tex2Ind]==-1)                                \
        {                                                               \
            tex2[geoIndex]->push_back(it.getTexCoords2(k+INDEX));       \
            t2ni[geoIndex][tex2Ind]=tex2[geoIndex]->size()-1;           \
        }                                                               \
    }                                                                   \
    int tex3Ind=it.getTexCoordsIndex3(k+INDEX);                         \
    if (t3ni[geoIndex])                                                 \
    {                                                                   \
        if (t3ni[geoIndex][tex3Ind]==-1)                                \
        {                                                               \
            tex3[geoIndex]->push_back(it.getTexCoords3(k+INDEX));       \
            t3ni[geoIndex][tex3Ind]=tex3[geoIndex]->size()-1;           \
        }                                                               \
    }                                                                   \
    if (indices[geoIndex]!=NULL)                                        \
    {                                                                   \
        if (geos[geoIndex]->getIndexMapping().size()<2)                 \
        {                                                               \
            indices[geoIndex]->push_back(pni[geoIndex][posInd]);        \
        }                                                               \
        else                                                            \
        {                                                               \
            UInt32 * offsets = new UInt32 [ geos[geoIndex]->getIndexMapping().size() ];            \
            Int16 mind;                                                                            \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapPosition ) ) >= 0 )       \
                offsets[ mind ] = pni[geoIndex][posInd];                                           \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapNormal ) ) >= 0 )         \
                offsets[ mind ] = nni[geoIndex][normInd];                                          \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapColor ) ) >= 0 )          \
                offsets[ mind ] = cni[geoIndex][colInd];                                           \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapSecondaryColor ) ) >= 0 ) \
                offsets[ mind ] = sni[geoIndex][scolInd];                                          \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapTexCoords ) ) >= 0 )      \
                offsets[ mind ] = tni[geoIndex][texInd];                                           \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapTexCoords1 ) ) >= 0 )     \
                offsets[ mind ] = t1ni[geoIndex][tex1Ind];                                         \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapTexCoords2 ) ) >= 0 )     \
                offsets[ mind ] = t2ni[geoIndex][tex2Ind];                                         \
            if ( ( mind = geos[geoIndex]->calcMappingIndex( Geometry::MapTexCoords3 ) ) >= 0 )     \
                offsets[ mind ] = t3ni[geoIndex][tex3Ind];                                         \
            for (UInt32 j=0; j<geos[geoIndex]->getIndexMapping().size(); j++)                      \
                indices[geoIndex]->push_back(offsets[j]);                                          \
            delete [] offsets;                                                                     \
        }                                                                                          \
    }                                                                                              \
}

#define setupAttr( type , arr1 , arr2 , getmethod )                                 \
if (geo->getmethod()!=NULL && geo->getmethod()->size()>0)                         \
{                                                                                   \
    arr1[i]    = dynamic_cast<type>(geo->getmethod()->getType().createFieldContainer());   \
    arr2[i]    = new int[geo->getmethod()->size()];                                 \
    for (UInt32 j=0; j<geo->getmethod()->size(); j++)                               \
        arr2[i][j]=-1;                                                              \
} else { arr2[i]=0; arr1[i]=NULL; }

Action::ResultE SplitGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
    MFUnrecChildNodePtr::const_iterator mfit = node->getMFChildren()->begin();
    MFUnrecChildNodePtr::const_iterator mfen = node->getMFChildren()->end  ();

    std::vector<NodeUnrecPtr  > toAdd;
    std::vector<Node         *> toSub;

    for ( ; mfit != mfen; ++mfit )
    {
        bool special=isInExcludeList(*mfit);
        bool leaf=isLeaf(*mfit);
        
        if (!special && leaf)
        {
            if (splitNode(*mfit, toAdd))
                toSub.push_back(*mfit);
        }
    }

    std::vector<NodeUnrecPtr>::const_iterator vait = toAdd.begin();
    std::vector<NodeUnrecPtr>::const_iterator vaen = toAdd.end  ();
    
    for ( ; vait != vaen; ++vait )
    {
        node->addChild(*vait);
    }
    
    std::vector<Node *>::const_iterator vsit = toSub.begin();
    std::vector<Node *>::const_iterator vsen = toSub.end  ();
    
    for ( ; vsit != vsen; ++vsit )
    {
        node->subChild(*vsit);
    }
    return res;
}

bool SplitGraphOp::splitNode(Node * const node, std::vector<NodeUnrecPtr> &split)
{
    // PORTME
    return false;
#if 0
    //split it only if it is a non special geometry leaf
    if (!isLeaf(node) || isInExcludeList(node) ||
        !node->getCore()->getType().isDerivedFrom(Geometry::getClassType())) return false;

    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());

    if ( geo->getPositions() == NULL || geo->getPositions()->size() == 0 ||
         geo->getLengths()   == NULL || geo->getLengths()->size() == 0 ||
         geo->getTypes()     == NULL || geo->getTypes()->size() == 0 ) return false;

    //get all center points
    std::vector<Pnt3f> centers;
    int ind;

    PrimitiveIterator it(geo);

    while (!it.isAtEnd())
    {
        switch(it.getType())
        {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            {
                Pnt3f center(0,0,0);
                for (UInt32 i=0; i<it.getLength(); i++)
                    center+=(Vec3f)it.getPosition(i);
                center/=Real32(it.getLength());
                centers.push_back(center);                
            } 
            break;
            
        case GL_TRIANGLES:
            ind=0;
            while(it.getLength()-ind>=3)
            {
                Pnt3f center(0,0,0);
                for (UInt32 i=0; i<3; i++, ind++)
                    center+=(Vec3f)it.getPosition(ind);
                center/=3;
                centers.push_back(center);
            } 
            break;
            
        case GL_QUADS:
            ind=0;
            while(it.getLength()-ind>=4)
            {
                Pnt3f center(0,0,0);
                for (UInt32 i=0; i<4; i++, ind++)
                    center+=(Vec3f)it.getPosition(ind);
                center/=4;
                centers.push_back(center);
            } 
            break;

            
        default:
            SWARNING << "SplitGraphOp::splitLeave: encountered " 
                     << "unknown primitive type " 
                     << it.getType()
                     << ", ignoring!" << std::endl;
            break;
        }   
        
        ++it;        
    }    
    
    std::vector<int> order;    
    for (UInt32 i=0; i<centers.size(); i++)
        order.push_back(i);

    Pnt3fComparator comp(centers);
    std::sort(order.begin(), order.end(), comp);

    //now we need (centers.size()/_max_polygons) amount of new geometries
    int ngeos=int(ceil((double)centers.size()/(double)_max_polygons));

    if (ngeos<=1) return false;

    Geometry       **geos    = new Geometry *[ngeos];
    GeoPTypes      **types   = new GeoPTypes *[ngeos];
    GeoPLengths    **lens    = new GeoPLengths *[ngeos];
    GeoPositions   **pnts    = new GeoPositions *[ngeos];
    GeoNormals     **normals = new GeoNormals *[ngeos];
    GeoColors      **colors  = new GeoColors *[ngeos];
    GeoColors      **scolors = new GeoColors *[ngeos];
    GeoTexCoords   **tex     = new GeoTexCoords *[ngeos];
    GeoTexCoords   **tex1    = new GeoTexCoords *[ngeos];
    GeoTexCoords   **tex2    = new GeoTexCoords *[ngeos];
    GeoTexCoords   **tex3    = new GeoTexCoords *[ngeos];
    GeoIndices     **indices = new GeoIndices *[ngeos];

    int **pni  = new int*[ngeos];
    int **nni  = new int*[ngeos];
    int **cni  = new int*[ngeos];
    int **sni  = new int*[ngeos];
    int **tni  = new int*[ngeos];
    int **t1ni = new int*[ngeos];
    int **t2ni = new int*[ngeos];
    int **t3ni = new int*[ngeos];

    for (Int32 i=0; i<ngeos; i++)
    {
        geos[i]  = Geometry::create();

        geos[i]->setMaterial(geo->getMaterial());

        if(geo->getMFIndexMapping() != NULL)
            geos[i]->getMFIndexMapping()->setValues(*(geo->getMFIndexMapping()));

        types[i]   = dynamic_cast<GeoPTypes *>(geo->getTypes()->getType().createFieldContainer());
        lens[i]    = dynamic_cast<GeoPLengths *>(geo->getLengths()->getType().createFieldContainer());

        if (geo->getIndices()!=NULL)
        {
            indices[i]  = dynamic_cast<GeoIndices *>(geo->getIndices()->getType().createFieldContainer());
        }
        else
            indices[i]  = NULL;

        setupAttr( GeoPositions * , pnts    , pni  , getPositions       );
        setupAttr( GeoNormals *   , normals , nni  , getNormals         );
        setupAttr( GeoColors *    , colors  , cni  , getColors          );
        setupAttr( GeoColors *    , scolors , sni  , getSecondaryColors );
        setupAttr( GeoTexCoords * , tex     , tni  , getTexCoords       );        
        setupAttr( GeoTexCoords * , tex1    , t1ni , getTexCoords1      );
        setupAttr( GeoTexCoords * , tex2    , t2ni , getTexCoords2      );
        setupAttr( GeoTexCoords * , tex3    , t3ni , getTexCoords3      );
    }

    ind=0;
    it.setToBegin();

    while (!it.isAtEnd())
    {
        switch(it.getType())
        {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            {
                int geoIndex=order[ind]/_max_polygons;

                types[geoIndex]->push_back(it.getType());
                lens[geoIndex]->push_back(it.getLength());

                addPoints( 0 , it.getLength() );
                ++ind;
            } break;
            
        case GL_TRIANGLES:
            {
                UInt32 i=0;                
                while(it.getLength()-i>=3)
                {                    
                    i+=3;
                    ++ind;
                }
            } break;
            
        case GL_QUADS:
            {
                UInt32 i=0;
                while(it.getLength()-i>=4)
                {
                    i+=4;
                    ++ind;
                }
            } break;

            
        default:
            SWARNING << "SplitGraphOp::splitLeave: encountered " 
                     << "unknown primitive type " 
                     << it.getType()
                     << ", ignoring!" << std::endl;
            break;
        }
        ++it;        
    }

    ind=0;
    it.setToBegin();

    while (!it.isAtEnd())
    {
        switch(it.getType())
        {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            {
                ++ind;
            } break;
            
        case GL_TRIANGLES:
            {
                UInt32 i=0;
                int geoIndex;
                while(it.getLength()-i>=3)
                {                    
                    geoIndex = order[ind]/_max_polygons;
                    if (types[geoIndex]->size()>0 && types[geoIndex]->getValue(types[geoIndex]->size()-1) == GL_TRIANGLES)
                    {
                        int lind;
                        if ((lind=lens[geoIndex]->size()-1)>=0)
                            lens[geoIndex]->setValue(lens[geoIndex]->getValue(lind)+3, lind);
                        else
                            lens[geoIndex]->push_back(3);
                    }
                    else
                    {
                        types[geoIndex]->push_back(GL_TRIANGLES);
                        lens[geoIndex]->push_back(3);
                    }

                    addPoints( i ,3 );
                    i+=3;
                    ++ind;
                }
            } break;
            
        case GL_QUADS:
            {
                UInt32 i=0;
                while(it.getLength()-i>=4)
                {
                    i+=4;
                    ++ind;
                }
            } break;

            
        default:
            SWARNING << "SplitGraphOp::splitLeave: encountered " 
                     << "unknown primitive type " 
                     << it.getType()
                     << ", ignoring!" << std::endl;
            break;
        }        
        ++it;        
    }

    ind=0;
    it.setToBegin();

    while (!it.isAtEnd())
    {
        switch(it.getType())
        {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            {
                ++ind;
            } break;
            
        case GL_TRIANGLES:
            {
                UInt32 i=0;
                while(it.getLength()-i>=3)
                {
                    i+=3;
                    ++ind;
                }
            } break;
            
        case GL_QUADS:
            {
                UInt32 i=0;
                int geoIndex;
                while(it.getLength()-i>=4)
                {                    
                    geoIndex = order[ind]/_max_polygons;
                    if (types[geoIndex]->size()>0 && types[geoIndex]->getValue(types[geoIndex]->size()-1) == GL_QUADS)
                    {
                        int lind;
                        if ((lind=lens[geoIndex]->size()-1)>=0)
                            lens[geoIndex]->setValue(lens[geoIndex]->getValue(lind)+4, lind);
                        else
                            lens[geoIndex]->push_back(4);
                    }
                    else
                    {
                        types[geoIndex]->push_back(GL_QUADS);
                        lens[geoIndex]->push_back(4);
                    }

                    addPoints( i , 4 );
                    i+=4;
                    ++ind;
                }
            } break;
            
        default:
            SWARNING << "SplitGraphOp::splitLeave: encountered " 
                     << "unknown primitive type " 
                     << it.getType()
                     << ", ignoring!" << std::endl;
            break;
        }        
        ++it;        
    }

    for (Int32 i=0; i<ngeos; i++)
    {
        geos[i]->setTypes(types[i]);
        geos[i]->setLengths(lens[i]);
        geos[i]->setPositions(pnts[i]);

        // Now close the open FCs

        if (indices[i]!=NULL)
        {
            geos[i]->setIndices(indices[i]);
        }

        if (normals[i]!=NULL)
        {
            geos[i]->setNormals(normals[i]);
        }

        if (colors[i]!=NULL)
        {
            geos[i]->setColors(colors[i]);
        }
        
        if (scolors[i]!=NULL)
        {
            geos[i]->setSecondaryColors(scolors[i]);
        }
        
        if (tex[i]!=NULL)
        {
            geos[i]->setTexCoords(tex[i]);
        }
       
        if (tex1[i]!=NULL)
        {
            geos[i]->setTexCoords1(tex1[i]);
        }
        
        if (tex2[i]!=NULL)
        {
            geos[i]->setTexCoords2(tex2[i]);
        }
        
        if (tex3[i]!=NULL)
        {
            geos[i]->setTexCoords3(tex3[i]);
        }

        if (node->getParent()!=NULL)
        {
            Node *n=Node::create();
            n->setCore(geos[i]);
            split.push_back(n);
        }
    }

    for (Int32 i=0; i<ngeos; i++)
    {
        if (pni[i]) delete [] pni[i];
        if (nni[i]) delete [] nni[i];
        if (cni[i]) delete [] cni[i];
        if (sni[i]) delete [] sni[i];
        if (tni[i]) delete [] tni[i];
        if (t1ni[i]) delete [] t1ni[i];
        if (t2ni[i]) delete [] t2ni[i];
        if (t3ni[i]) delete [] t3ni[i];
    }

    delete [] pni;
    delete [] nni;
    delete [] cni;
    delete [] sni;
    delete [] tni;
    delete [] t1ni;
    delete [] t2ni;
    delete [] t3ni;

    return true;
#endif
}

bool SplitGraphOp::isLeaf(Node * const node)
{
    if (node->getMFChildren()->begin()==
        node->getMFChildren()->end()) return true;
    else return false;    
}

/*! checks whether a node is a group and nothing else
*/
bool SplitGraphOp::isGroup(Node * const node)
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
