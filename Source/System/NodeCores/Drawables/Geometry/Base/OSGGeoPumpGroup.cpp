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
 *                                                                           *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLEXT.h"

#include "OSGLog.h"

#include "OSGGeometry.h"
#include "OSGDrawEnv.h"

#include "OSGMaterial.h"

#include "OSGGeoPumpGroup.h"
#include "OSGGeoImmediatePumpGroup.h"
#include "OSGGeoVertexArrayPumpGroup.h"
#include "OSGGeoSplitVertexArrayPumpGroup.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/* \class OSG::GeoPumpGroup
   \ingroup GrpSystemNodeCoresDrawablesGeometry

The PumpGroup is responsible for selecting the most appropriate pump
function to send the geometry's data to OpenGL in the most efficient manner.

The pump is selected inside the rendering function and should not be accessed
from the outside.

\dev The pump factory chooses the pump based on the used properties. For
non- and single-indexed geometry OpenGL VertexArrays are used, for
multi-indexed geometry an immediate mode pump has to be used. Specialized Pumps
for all combinations of properties are created to optimizie this case as much
as possible.
*/


std::vector<GeoPumpGroup*> *GeoPumpGroup::_activeGroups;

/*! Initialize the _activeGroups at startup.
*/
InitFuncWrapper GeoPumpGroup::actInit(GeoPumpGroup::initActiveGroups);

bool GeoPumpGroup::initActiveGroups(void)
{
    _activeGroups = new std::vector<GeoPumpGroup*>;

    _activeGroups->push_back(new GeoVertexArrayPumpGroup);
    _activeGroups->push_back(new GeoSplitVertexArrayPumpGroup);
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    _activeGroups->push_back(new GeoImmediatePumpGroup);
#endif

    addPostFactoryExitFunction(&GeoPumpGroup::terminateActiveGroups);

    return true;
}

bool GeoPumpGroup::terminateActiveGroups(void)
{
    for(UInt32 i = 0; i < _activeGroups->size(); ++i)
    {
        delete (*_activeGroups)[i];
    }

    delete _activeGroups;

    return true;
}

/*! PropertyCharacteristics handling.
*/

std::string GeoPumpGroup::describePropertyCharacteristics(
                                        PropertyCharacteristics ac)
{
    std::string result;

    if(ac & GeoPumpGroup::NonIndexed)    result += "NonIndexed,";
    if(ac & GeoPumpGroup::SingleIndexed) result += "SingleIndexed,";
    if(ac & GeoPumpGroup::MultiIndexed)  result += "MultiIndexed,";
    if(ac & GeoPumpGroup::NonTraditionalProperties)
        result += "NonTraditionalProperties,";

    if(result.empty() == true)
        result += "unknown,";

    result.resize(result.length()-1);

    return result;
}

GeoPumpGroup::PropertyCharacteristics
GeoPumpGroup::characterizeGeometry(Geometry* geo)
{
    return characterizeGeometry(geo->getMFProperties(),
                                geo->getMFPropIndices());
}

GeoPumpGroup::PropertyCharacteristics
GeoPumpGroup::characterizeGeometry(const Geometry::MFPropertiesType  *prop,
                                   const Geometry::MFPropIndicesType *propIdx)
{
    PropertyCharacteristics retVal = 0;

    Int16 natt = prop   ->size32();
    Int16 nind = propIdx->size32();

    // Check for single- and multi-indexed
    GeoIntegralProperty *ind = NULL;

    bool single     = true;
    bool multi      = true;
    bool nonind     = true;
    bool allPropVAO = true;
    bool allIdxVAO  = true;

    for(Int16 i = 0; i < natt; ++i)
    {
        // Only count actual attributes
        if((*prop)[i] != NULL && (*prop)[i]->getDivisor() == 0)
        {
            if((*prop)[i]->getUseVBO() == false)
            {
                allPropVAO = false;
            }

            if(i < nind)
            {
                if((*propIdx)[i] == NULL)
                {
                    if((*prop)[i]->size() != 1)
                    {
                        single = false;
                        multi  = false;
                    }
                }
                else
                {
                    if((*propIdx)[i]->getUseVBO() == false)
                    {
                        allIdxVAO = false;
                    }

                    nonind = false;

                    if(ind == NULL)
                        ind = (*propIdx)[i];

                    if((*propIdx)[i] != ind && (*prop)[i]->size() != 1)
                        single = false;
                }
            }
            else
            {
                single = false;
                multi  = false;
            }
        }
    }

    if(nonind)  
        retVal |= GeoPumpGroup::NonIndexed;
    else if(single)  
        retVal |= GeoPumpGroup::SingleIndexed;
    else if(multi)   
        retVal |= GeoPumpGroup::MultiIndexed;

    if(allPropVAO == true)
    {
        retVal |= AllPropsVAO;
    }

    if(allIdxVAO == true)
    {
        retVal |= AllPropIdxVAO;
    }

#if 0
    // check double single + multi char
    fprintf(stderr, 
            "single %d | no %d | multi %d | prop vao %d | idx vao %d\n",
            UInt32(single),
            UInt32(nonind),
            UInt32(multi),
            UInt32(allPropVAO),
            UInt32(allIdxVAO));
#endif

    // Check for non-traditional properties.
    // Right now just check existence of attribs 6&7
    // To be complete this would also have to check
    // type compatibility! *DR*

    if(natt > 6 && (*prop)[6] != NULL)
        retVal |= GeoPumpGroup::NonTraditionalProperties;
    if(natt > 7 && (*prop)[7] != NULL)
        retVal |= GeoPumpGroup::NonTraditionalProperties;

    return retVal;
}

/*! Find the actual pumps for the given Window/Geometry.
*/

GeoPumpGroup::GeoPump GeoPumpGroup::findGeoPump(DrawEnv                 *pEnv,
                                                PropertyCharacteristics  acset)
{
    GeoPump  pump = NULL;
    Window  *win  = pEnv->getWindow();

    for(std::vector<GeoPumpGroup*>::iterator it = _activeGroups->begin();
        it != _activeGroups->end() && pump == NULL;
        ++it)
    {
        pump = (*it)->getGeoPump(pEnv,acset);
    }

    if(pump == NULL)
    {
        FWARNING(("GeoPumpGroup::findGeoPump: Couldn't find pump for"
                  "Window %p and characteristics %s!\n", 
                  static_cast<void *>(win),
                  describePropertyCharacteristics(acset).c_str() ));
    }

    return pump;
}

GeoPumpGroup::SplitGeoPump GeoPumpGroup::findSplitGeoPump(
    DrawEnv                 *pEnv,
    PropertyCharacteristics  acset)
{
    SplitGeoPump  pump = { NULL, NULL, NULL };
    Window       *win  = pEnv->getWindow();

    std::vector<GeoPumpGroup*>::const_iterator pIt  = _activeGroups->begin();
    std::vector<GeoPumpGroup*>::const_iterator pEnd = _activeGroups->end  ();

    for(; pIt != pEnd && pump.setupPump == NULL; ++pIt)
    {
        pump = (*pIt)->getSplitGeoPump(pEnv, acset);
    }

    if(pump.setupPump == NULL)
    {
        FWARNING(("GeoPumpGroup::findSplitGeoPump: Couldn't find pump for"
                  "Window %p and characteristics %s!\n", 
                  static_cast<void *>(win),
                  describePropertyCharacteristics(acset).c_str() ));
    }

    return pump;
}

GeoPumpGroup::SplitGeoPump GeoPumpGroup::getSplitGeoPump(
    DrawEnv                 *,
    PropertyCharacteristics  )
{
    SplitGeoPump  pump = { NULL, NULL, NULL };

    return pump;
}

GeoPumpGroup::~GeoPumpGroup()
{
}
