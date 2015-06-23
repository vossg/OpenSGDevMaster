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

#include "OSGPrepareESGraphOp.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGGeoFunctions.h"
#include "OSGGraphOpFactory.h"

OSG_BEGIN_NAMESPACE

namespace
{
    void adjustIndexTypeAndVBO(Geometry *pGeo, bool bUseVBO)
    {
        typedef std::vector<UInt16>::iterator IndexIt;

        if(pGeo == NULL)
            return;

        Geometry::IndexBag oGeoIndexBag = pGeo->getUniqueIndexBag();

        Geometry::IndexBag::iterator bIt  = oGeoIndexBag.begin();
        Geometry::IndexBag::iterator bEnd = oGeoIndexBag.end  ();

        for(; bIt != bEnd; ++bIt)
        {
            GeoIntegralProperty *pOldIdx = bIt->first;
            
            if(pOldIdx->getFormat() != GL_UNSIGNED_BYTE &&
               pOldIdx->getFormat() != GL_UNSIGNED_SHORT  )
            {
                GeoIndexPropertyUnrecPtr pNewIdx = GeoIndexProperty::create();
            
                pNewIdx->resize   (pOldIdx->size());
                pNewIdx->setUseVBO(bUseVBO        );

                for(UInt32 i = 0; i < pOldIdx->size(); ++i)
                {
                    pNewIdx->setValue(pOldIdx->getValue(i), i);
                }
            
                IndexIt pIt    = bIt->second.begin();
                IndexIt pEnd   = bIt->second.end  ();
  
                for(; pIt != pEnd; ++pIt)
                {
                    pGeo->setIndex(pNewIdx, *pIt);
                }
            }
            else
            {
                pOldIdx->setUseVBO(bUseVBO);
            }
        }
    }

    void updatePropVBO(Geometry *pGeo, bool bUseVBO)
    {
        if(pGeo == NULL)
            return;
        
        typedef Geometry::MFPropertiesType::const_iterator GeoPropIt;

        GeoPropIt propIt  = pGeo->getMFProperties()->begin();
        GeoPropIt propEnd = pGeo->getMFProperties()->end  ();

        for(; propIt != propEnd; ++propIt)
        {
            if(*propIt != NULL)
            {
                (*propIt)->setUseVBO(bUseVBO);
            }
        }
    }
}

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PrepareESGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = PrepareESGraphOp::create();

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

PrepareESGraphOp::PrepareESGraphOp(const char* name) :
    Inherited(name)
{
}

PrepareESGraphOp::~PrepareESGraphOp(void)
{
}

PrepareESGraphOpTransitPtr PrepareESGraphOp::create(void)
{
    return PrepareESGraphOpTransitPtr(new PrepareESGraphOp);
}

GraphOpTransitPtr PrepareESGraphOp::clone(void)
{
    return GraphOpTransitPtr(new PrepareESGraphOp);
}

void PrepareESGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    std::string out = ps.getUnusedParams();

    if(out.length())
    {
        FWARNING(("PrepareESGraphOp doesn't have parameters '%s'\n.",
                out.c_str()));
    }
}

std::string PrepareESGraphOp::usage(void)
{
    return 
        "PrepareES: Prepare Geometries for ES (==> UInt16 single index)\n";
}

bool PrepareESGraphOp::travNodeEnter(Node *node)
{
    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());

    fprintf(stderr, "tne esp : %p\n", static_cast<void *>(geo));

    if(geo != NULL)
    {
        createSharedIndex    (geo);
        createSingleIndex    (geo);
        adjustIndexTypeAndVBO(geo, true);
        updatePropVBO        (geo, true);
    }
    
    return true;
}

bool PrepareESGraphOp::travNodeLeave(Node *)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
