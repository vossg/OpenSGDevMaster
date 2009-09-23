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

#include <sstream>

#include "OSGMaterialMergeGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGFieldContainerUtils.h"

#include <boost/next_prior.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MaterialMergeGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry

    Merges equivalent materials in a scene.
*/

namespace
{

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpRefPtr newOp = MaterialMergeGraphOp::create();

    GraphOpFactory::the()->registerOp(newOp);
    return true;
}

static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace

MaterialMergeGraphOp::MaterialMergeGraphOp(const char* name)
    : GraphOp(name)
{
}

MaterialMergeGraphOp::~MaterialMergeGraphOp(void)
{
}

MaterialMergeGraphOpTransitPtr
MaterialMergeGraphOp::create(void)
{
    return MaterialMergeGraphOpTransitPtr(new MaterialMergeGraphOp);
}

GraphOpTransitPtr MaterialMergeGraphOp::clone(void)
{
    return GraphOpTransitPtr(new MaterialMergeGraphOp);
}

bool MaterialMergeGraphOp::traverse(Node *node)
{
    // Find the materials.
    if(!GraphOp::traverse(node))
    {
        return false;
    }

    SINFO << "Number of materials before merge: " 
          << _materialMap.size() << std::endl;

    // Now do the merge.
    MaterialObjectMap::iterator mmIt = _materialMap.begin();
    
    for (; mmIt != _materialMap.end(); ++mmIt)
    {
        Material                    *currentMat  = mmIt->first;
        MaterialObjectList          &currentList = mmIt->second;
        MaterialObjectMap::iterator  mmWalker    = boost::next(mmIt);
        
        while(mmWalker != _materialMap.end())
        {
            // Store the next iterator in case we have to delete
            // 'walker' from the map.
            MaterialObjectMap::iterator nextStep = boost::next(mmWalker);

            if(compareContainerEqual(currentMat, mmWalker->first))
            {
                // Set the new objects to have the current material,
                // and move the objects to the current list.
                MaterialObjectList::iterator mlIt  = mmWalker->second.begin();
                MaterialObjectList::iterator mlEnd = mmWalker->second.end  ();
                
                for (; mlIt != mlEnd; ++mlIt)
                {
                    mlIt->setMaterial(currentMat);
                    currentList.push_back(*mlIt);
                }
                
                _materialMap.erase(mmWalker);
            }

            mmWalker = nextStep;
        }
    }

    SINFO << "Number of materials after merge: " << _materialMap.size() << std::endl;
    return true;
}


void MaterialMergeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("MaterialMergeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string MaterialMergeGraphOp::usage(void)
{
    return 
    "MaterialMerge: merge Materials in given subtree\n"
    "  Tries to find and merge equiavlent Materials to reduce the number\n"
    "  of Materials used.\n"
    ;
}

Action::ResultE MaterialMergeGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;
    
    if(isInPreserveList(node))
        return Action::Continue;
    
    MaterialDrawable *md = dynamic_cast<MaterialDrawable *>(node->getCore());
    if(md != NULL)
    {
        addObject(MaterialObject(md));
        return Action::Continue;
    }
    
    MaterialGroup *mg = dynamic_cast<MaterialGroup *>(node->getCore());
    if(mg != NULL)
    {
        addObject(MaterialObject(mg));
        return Action::Continue;
    }

    // Otherwise, keep looking.
    return Action::Continue;
}

Action::ResultE MaterialMergeGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
    return res;
}

void MaterialMergeGraphOp::addObject(MaterialObject m)
{
    Material *mat = m.getMaterial();
    if (mat == NULL)
        return;

    _materialMap[mat].push_back(m);
}

OSG_END_NAMESPACE
