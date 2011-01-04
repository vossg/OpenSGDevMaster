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

#include "OSGVerifyGraphOp.h"
#include "OSGGroup.h"
#include "OSGNameAttachment.h"
#include "OSGPrimitiveIterator.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpRefPtr newOp = VerifyGraphOp::create();

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

VerifyGraphOp::VerifyGraphOp(bool repair, bool verbose, const char* name): 
    GraphOp(name), _repair(repair), _verbose(verbose)
{
}

VerifyGraphOp::~VerifyGraphOp(void)
{
}

VerifyGraphOpTransitPtr
VerifyGraphOp::create(bool repair, bool verbose)
{
    return VerifyGraphOpTransitPtr(new VerifyGraphOp(repair, verbose));
}

GraphOpTransitPtr VerifyGraphOp::clone(void)
{
    return GraphOpTransitPtr(new VerifyGraphOp);
}

void VerifyGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("repair",  _repair);
    ps("verbose",  _verbose);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("VerifyGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string VerifyGraphOp::usage(void)
{
    return 
    "Verify: Test validity of Geometries\n"
    "  Run some validity tests on Geometries, makes sure indices are\n"
    "  in the valid range etc.\n"
    "Params: name (type, default)\n"
    "  repair  (bool, true): try to repair consistency errors\n"
    "  verbose (bool, false): print information during traversal\n";
}

void VerifyGraphOp::setRepair(bool repair)
{
    _repair = repair;
}

void VerifyGraphOp::setVerbose(bool verbose)
{
    _verbose = verbose;
}

bool VerifyGraphOp::traverse(Node *node)
{
    // Clean up
    
    _numErrors = 0;
    _corruptedGeos.clear();
    _corruptedNodes.clear();
    
    // Find the bad nodes.
    if(!GraphOp::traverse(node))
        return false;

    if(_repair)
    {
        repairGeometry();      // Repair any corrupted geometry nodes
    }

    if(_verbose)
    {
        SINFO << "Verifier completed. Errors found:" << _numErrors << endLog;
    }

     

    return true;
}

Action::ResultE VerifyGraphOp::traverseEnter(Node * const node)
{
    if(NULL == node)
    {
        FWARNING(("VerifyGraphOp::travNodeEnter: called with NULL node, "
                  "skipping."));
        return Action::Continue;
    }

    // Verify basic node structure
    std::string node_name;
    if(OSG::getName(node) != NULL)
    { 
        node_name = std::string(OSG::getName(node)); 
    }

    NodeCore *node_core = node->getCore();
    if(NULL == node_core)
    {
        _corruptedNodes.push_back(node);
        _numErrors += 1;
        if(_verbose)
        { 
            SINFO << "Node: [" << node_name << "] has NULL core." 
                  << endLog; 
        }
        if(_repair)
        {
            if(_verbose) 
                SINFO << "  Repairing node.  Adding group core." << endLog;
            node->setCore(Group::create());
            std::string new_name = node_name + "_FIXED";
            OSG::setName(node, new_name);
        }
    }

    // Check based on core types
    if(NULL != node_core)
    {
        if(dynamic_cast<Geometry *>(node_core) != NULL)
        {
            return verifyGeometry(node);
        }
    }

    return Action::Continue;
}

Action::ResultE VerifyGraphOp::traverseLeave(Node * const, 
                                             Action::ResultE res)
{
    return Action::Continue;
}


/** Verify geometry method. */
Action::ResultE VerifyGraphOp::verifyGeometry(Node * const node)
{
    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());

    if(geo == NULL)
        return Action::Continue;

    if(geo->getPositions() == NULL)
        return Action::Continue;

    UInt32 start_errors = _numErrors;

    Int32 positions_size = geo->getPositions()->getSize();

    Int32 normals_size = 0;
    if(geo->getNormals() != NULL)
        normals_size = geo->getNormals()->getSize();

    Int32 colors_size = 0;
    if(geo->getColors() != NULL)
        colors_size = geo->getColors()->getSize();

    Int32 secondary_colors_size = 0;
    if(geo->getSecondaryColors() != NULL)
        secondary_colors_size = geo->getSecondaryColors()->getSize();

    Int32 texccords_size = 0;
    if(geo->getTexCoords() != NULL)
        texccords_size = geo->getTexCoords()->getSize();

    Int32 texccords1_size = 0;
    if(geo->getTexCoords1() != NULL)
        texccords1_size = geo->getTexCoords1()->getSize();

    Int32 texccords2_size = 0;
    if(geo->getTexCoords2() != NULL)
        texccords2_size = geo->getTexCoords2()->getSize();

    Int32 texccords3_size = 0;
    if(geo->getTexCoords3() != NULL)
        texccords3_size = geo->getTexCoords3()->getSize();

    UInt32 pos_errors = 0;
    UInt32 norm_errors = 0;
    UInt32 col_errors = 0;
    UInt32 col2_errors = 0;
    UInt32 tex0_errors = 0;
    UInt32 tex1_errors = 0;
    UInt32 tex2_errors = 0;
    UInt32 tex3_errors = 0;

    PrimitiveIterator it;
    for(it = geo->beginPrimitives(); it != geo->endPrimitives(); ++it)
    {
        for(UInt32 v=0; v < it.getLength(); ++v)
        {
            if(it.getPositionIndex(v) >= positions_size)
                ++pos_errors;
            if(it.getNormalIndex(v) >= normals_size)
                ++norm_errors;
            if(it.getColorIndex(v) >= colors_size)
                ++col_errors;
            if(it.getSecondaryColorIndex(v) >= secondary_colors_size)
                ++col2_errors;
            if(it.getTexCoordsIndex(v) >= texccords_size)
                ++tex0_errors;
            if(it.getTexCoordsIndex1(v) >= texccords1_size)
                ++tex1_errors;
            if(it.getTexCoordsIndex2(v) >= texccords2_size)
                ++tex2_errors;
            if(it.getTexCoordsIndex3(v) >= texccords3_size)
                ++tex3_errors;
        }
    }

    if(norm_errors > 0)
    {
        norm_errors = 0;
        if(_verbose) SINFO << "removed corrupted normals!\n";
        geo->setNormals(NULL);
    }

    if(col_errors > 0)
    {
        col_errors = 0;
        if(_verbose) SINFO << "removed corrupted colors!\n";
        geo->setColors(NULL);
    }

    if(tex0_errors > 0)
    {
        tex0_errors = 0;
        if(_verbose) SINFO << "removed corrupted tex coords0!\n";
        geo->setTexCoords(NULL);
    }

    _numErrors += (pos_errors + norm_errors + col_errors +
                   col2_errors + tex0_errors + tex1_errors +
                   tex2_errors + tex3_errors);

    // found some errors.
    if(_numErrors > start_errors)
    {
        _corruptedGeos.push_back(geo); 
    }

    // ok we found no errors now check for missing index map.
    bool need_repair(false);
    if(!verifyIndexMap(geo, need_repair))
    {
        if(need_repair)
        { 
            SINFO << "verifyGeometry : added missing index map!" << endLog; 
        }
        else
        { 
            SINFO << "verifyGeometry : couldn't add missing index map!\n" 
                  << endLog; 
        }
    }

    return Action::Continue;
}


bool VerifyGraphOp::verifyIndexMap(Geometry *geo, bool &repair)
{
    repair = false;
    return true;

#if 0
    if(geo == NULL)
        return true;

    if(geo->getIndices() == NULL)
        return true;

    if(!geo->getIndexMapping().empty())
        return true;

    if(geo->getPositions() == NULL)
        return true;

    UInt32 positions_size = geo->getPositions()->getSize();

    UInt32 normals_size = 0;
    if(geo->getNormals() != NullFC)
        normals_size = geo->getNormals()->getSize();

    UInt32 colors_size = 0;
    if(geo->getColors() != NullFC)
        colors_size = geo->getColors()->getSize();

    UInt32 secondary_colors_size = 0;
    if(geo->getSecondaryColors() != NullFC)
        secondary_colors_size = geo->getSecondaryColors()->getSize();

    UInt32 texccords_size = 0;
    if(geo->getTexCoords() != NullFC)
        texccords_size = geo->getTexCoords()->getSize();

    UInt32 texccords1_size = 0;
    if(geo->getTexCoords1() != NullFC)
        texccords1_size = geo->getTexCoords1()->getSize();

    UInt32 texccords2_size = 0;
    if(geo->getTexCoords2() != NullFC)
        texccords2_size = geo->getTexCoords2()->getSize();

    UInt32 texccords3_size = 0;
    if(geo->getTexCoords3() != NullFC)
        texccords3_size = geo->getTexCoords3()->getSize();

    /*
    printf("sizes: %u %u %u %u %u %u %u %u\n", positions_size, normals_size,
    colors_size, secondary_colors_size,
    texccords_size, texccords1_size,
    texccords2_size, texccords3_size);
    */
    if((positions_size == normals_size || normals_size == 0) &&
       (positions_size == colors_size || colors_size == 0) &&
       (positions_size == secondary_colors_size || secondary_colors_size == 0) &&
       (positions_size == texccords_size || texccords_size == 0) &&
       (positions_size == texccords1_size || texccords1_size == 0) &&
       (positions_size == texccords2_size || texccords2_size == 0) &&
       (positions_size == texccords3_size || texccords3_size == 0)
      )
    {
        UInt16 indexmap = 0;
        if(positions_size > 0)
            indexmap |= Geometry::MapPosition;
        if(normals_size > 0)
            indexmap |= Geometry::MapNormal;
        if(colors_size > 0)
            indexmap |= Geometry::MapColor;
        if(secondary_colors_size > 0)
            indexmap |= Geometry::MapSecondaryColor;
        if(texccords_size > 0)
            indexmap |= Geometry::MapTexCoords;
        if(texccords1_size > 0)
            indexmap |= Geometry::MapTexCoords1;
        if(texccords2_size > 0)
            indexmap |= Geometry::MapTexCoords2;
        if(texccords3_size > 0)
            indexmap |= Geometry::MapTexCoords3;

        geo->getIndexMapping().push_back(indexmap);
        repair = true;
        return false;
    }
    else
    {
        return false;
    }
#endif
}


/*!
* \brief Replaces corrupted geometrie nodes with group nodes.
* \return true if something was repaired.
*/
bool VerifyGraphOp::repairGeometry(void)
{
    if (!_corruptedGeos.empty())
    {
        if (_verbose)
        { 
            SINFO << "Repairing corrupted geos:" << endLog; 
        }

        for (UInt32 i=0;i<_corruptedGeos.size();++i)
        {
            // now replace corrupted geometry core with a group core.
            for (UInt32 j=0;j<_corruptedGeos[i]->getParents().size();++j)
            {
                Node *parent = dynamic_cast<Node *>(
                    _corruptedGeos[i]->getParents()[j]);
                if (parent != NULL)
                {
                    std::string nname;
                    if(OSG::getName(parent) != NULL)
                    { 
                        nname = OSG::getName(parent); 
                    }
                    if (_verbose)
                    {
                        SINFO << "Removing corrupted geom from node: " 
                              << nname << endLog; 
                    }
                    nname += "_CORRUPTED";
                    OSG::setName(parent, nname.c_str());
                    parent->setCore(Group::create());
                }
            }
        }
        return true;
    }

    return false;
}
