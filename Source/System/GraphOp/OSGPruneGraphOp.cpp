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

#include <OSGPruneGraphOp.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PruneGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
Removes nodes of size smaller than a given threshold from the scene.
*/

PruneGraphOp::PruneGraphOp(float size, Method method, const char* name)
    : GraphOp(name)
    , _size(size)
    , _method(method)
{
}

GraphOp* PruneGraphOp::create()
{
    return new PruneGraphOp(_size, _method);
}

void PruneGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("size",  _size);

    std::string m;
    ps("method", m);
    
    if(m.length())
    {
        if(m.find("volume") || m.find("VOLUME"))
        {
            _method = VOLUME;
        }
        else if(m.find("sum_of_dimensions") || m.find("SUM_OF_DIMENSIONS") ||
                m.find("sum"))
        {
            _method = SUM_OF_DIMENSIONS;
        }
        else
        {
            FWARNING(("GeoTypeGraphOp: method '%s' unknown.\n", m.c_str()));
        }
    }
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("PruneGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string PruneGraphOp::usage(void)
{
    return 
    "Prune: Remove small objects\n"
    "  Removes nodes of size smaller than a given threshold from the scene\n"
    "Params: name (type, default)\n"
    "  method (string, SUM_OF_DIMENSIONS): \n"
    "                    VOLUME: measure volume of Node\n"
    "                    SUM_OF_DIMENSIONS: add upp the individual dims\n"
    "  size   (Real32, 1.0f): \n"
    "                    threshold value. Nodes smaller than this will be\n"
    "                    removed\n";
}

Action::ResultE PruneGraphOp::traverseEnter(NodePtrConstArg node)
{
    return isTooSmall(node) ? Action::Skip : Action::Continue;
}

Action::ResultE PruneGraphOp::traverseLeave(NodePtrConstArg node, Action::ResultE res)
{
    for (UInt32 i = 0; i < node->getNChildren(); ++i) {
        if (isTooSmall(node->getChild(i))) {
            node->subChild(i);
            --i;
        }
    }

    return res;
}

bool PruneGraphOp::isTooSmall(const NodePtr& node) {
    return getSize(node) < _size;
}

float PruneGraphOp::getSize(const NodePtr& node) {
    const DynamicVolume& dv = node->editVolume(true);
    if (_method == VOLUME) {
        return dv.getScalarVolume();
    } else if (_method == SUM_OF_DIMENSIONS) {
        Pnt3f min, max;
        dv.getBounds(min, max);
        Vec3f diff = max - min;
        return diff[0] + diff[1] + diff[2];
    } else {
        SWARNING << "Unknown size calculation method" << std::endl;
        return 0;
    }
}
