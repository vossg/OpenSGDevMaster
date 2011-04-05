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

#include "OSGTypedGeoIntegralProperty.h"

#include "OSGVerifyGeoGraphOp.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VerifyGeoGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

namespace
{
    
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = VerifyGeoGraphOp::create();

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

VerifyGeoGraphOp::VerifyGeoGraphOp(const char *name) :
    Inherited  (name),
    _errorCount(0)
{
}

VerifyGeoGraphOp::~VerifyGeoGraphOp(void)
{
}

VerifyGeoGraphOpTransitPtr
VerifyGeoGraphOp::create(void)
{
    return VerifyGeoGraphOpTransitPtr(new VerifyGeoGraphOp());
}

GraphOpTransitPtr VerifyGeoGraphOp::clone(void)
{
    return GraphOpTransitPtr(new VerifyGeoGraphOp);
}

bool VerifyGeoGraphOp::traverse(Node *node)
{
    _errorCount = 0;
    
    Inherited::traverse(node);
    
    if(_errorCount > 0)
    {
        FWARNING(("VerifyGeoGraphOp::traverse: Found [%d] errors.\n",
                  _errorCount));
    }

    return true;
}

void VerifyGeoGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("VerifyGeoGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string VerifyGeoGraphOp::usage(void)
{
    return 
    "VerifyGeo: Test validity of Geometries\n"
    "  Run some validity tests on Geometries, makes sure indices are\n"
    "  in the valid range etc.\n";
}

bool VerifyGeoGraphOp::travNodeEnter(Node *node)
{
    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());
    
    if(geo->getTypes() == NULL || geo->getTypes()->size() == 0)
    {
        FINFO(("VerifyGeoGraphOp::travNodeEnter: No or empty types.\n"));
        ++_errorCount;
        return false;
    }
    
    if(geo->getLengths() == NULL || geo->getLengths()->size() == 0)
    {
        FINFO(("VerifyGeoGraphOp::travNodeEnter: No or empty lengths.\n"));
        ++_errorCount;
        return false;
    }
    
    if(geo->getTypes()->size() != geo->getLengths()->size())
    {
        FINFO(("VerifyGeoGraphOp::travNodeEnter: Types and lengths have "
               "different sizes [%d] vs [%d]",
               geo->getTypes()->size(), geo->getLengths()->size()));
        ++_errorCount;
        return false;
    }
    
    // get number of indices/properties used
    UInt32 sumLengths = 0;
    
    for(UInt32 i = 0; i < geo->getSFLengths()->getValue()->size(); ++i)
        sumLengths += geo->getSFLengths()->getValue()->getValue<UInt32>(i);
    
    const Geometry::MFPropIndicesType *mfInd  = geo->getMFPropIndices();
    
    bool indexed = false;
    
    if(!mfInd->empty())
    {
        for(UInt32 i = 0; i < mfInd->size(); ++i)
        {
            if((*mfInd)[i] != NULL)
            {
                indexed = true;
                break;
            }
        }
    }

    if(indexed)
    {
        return checkIndexedGeo(geo, sumLengths);
    }
    else
    {
        return checkNonindexedGeo(geo, sumLengths);
    }
}

bool VerifyGeoGraphOp::checkIndexedGeo(Geometry *geo, UInt32 sumLengths)
{
    const Geometry::MFPropertiesType  *mfProp = geo->getMFProperties ();
    const Geometry::MFPropIndicesType *mfInd  = geo->getMFPropIndices();
    
    UInt32 numProp = mfProp->size();
    UInt32 numInd  = mfInd ->size();
    
    // properties that are present must have an index
    if(numProp < numInd)
    {
        for(UInt32 i = 0; i < numProp; ++i)
        {
            if((*mfProp)[i] != NULL && (*mfInd)[i] == NULL)
            {
                FINFO(("VerifyGeoGraphOp::checkIndexedGeo: "
                       "Property [%d] present, but no index.\n", i));
                ++_errorCount;
                return false;
            }
        }
    }
    else
    {
        for(UInt32 i = 0; i < numInd; ++i)
        {
            if((*mfProp)[i] != NULL && (*mfInd)[i] == NULL)
            {
                FINFO(("VerifyGeoGraphOp::checkIndexedGeo: "
                       "Property [%d] present, but no index.\n", i));
                ++_errorCount;
                return false;
            }
        }
        
        for(UInt32 i = numInd; i < numProp; ++i)
        {
            if((*mfProp)[i] != NULL)
            {
                FINFO(("VerifyGeoGraphOp::checkIndexedGeo: "
                       "Property [%d] present, but no index.\n", i));
                ++_errorCount;
                return false;
            }
        }
    }
    
    for(UInt32 i = 0; i < numInd; ++i)
    {
        if((*mfInd)[i] != NULL)
        {
            if((*mfInd)[i]->size() < sumLengths)
            {
                FINFO(("VerifyGeoGraphOp::checkIndexedGeo: "
                       "Index [%d] has too few elements.\n", i));
                ++_errorCount;
                return false;
            }
        }
    }
    
    // find largest indices
    std::vector<UInt32> indexMax (Geometry::MaxAttribs, 0);
    Geometry::IndexBag  ibag = geo->getUniqueIndexBag();
    
    for(UInt32 i = 0; i < ibag.size(); ++i)
    {
        UInt32 imax = 0;
        
        for(UInt32 j = 0; j < sumLengths; ++j)
            imax = osgMax(imax, ibag[i].first->getValue<UInt32>(j));
        
        for(UInt32 j = 0; j < ibag[i].second.size(); ++j)
            indexMax[ibag[i].second[j]] = imax;
    }
    
    // largest indices must be less than prop size
    for(UInt32 i = 0; i < numProp; ++i)
    {
        if((*mfProp)[i] != NULL && (*mfProp)[i]->size() <= indexMax[i])
        {
            FINFO(("VerifyGeoGraphOp::checkIndexedGeo: "
                   "Property [%d] has fewer elements than "
                   "referenced by the index.\n", i));
            ++_errorCount;
            return false;
        }
    }
    
    return true;
}

bool VerifyGeoGraphOp::checkNonindexedGeo(Geometry *geo, UInt32 sumLengths)
{
    const Geometry::MFPropertiesType  *mfProp = geo->getMFProperties ();
    
    UInt32 numProp = mfProp->size();
    
    for(UInt32 i = 0; i < numProp; ++i)
    {
        if((*mfProp)[i] != NULL)
        {
            if((*mfProp)[i]->size() < sumLengths)
            {
                FINFO(("VerifyGeoGraphOp::checkNonindexedGeo: "
                        "Property [%d] has too few elements.\n", i));
                ++_errorCount;
                return false;
            }
        }
    }
    
    return true;
}

bool VerifyGeoGraphOp::travNodeLeave(Node *)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/
