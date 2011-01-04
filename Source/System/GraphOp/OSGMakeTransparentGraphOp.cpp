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


#include "OSGBlendChunk.h"
#include "OSGMakeTransparentGraphOp.h"
#include "OSGPolygonChunk.h"
#include "OSGSimpleMaterial.h"
#include "OSGGLEXT.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

namespace
{

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpRefPtr newOp = MakeTransparentGraphOp::create();

    GraphOpFactory::the()->registerOp(newOp);
    return true;
}

static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace


MakeTransparentGraphOp::MakeTransparentGraphOp(const char* name)
    : GraphOp      (name),
      _transparency(0.5 )
{
}

MakeTransparentGraphOp::~MakeTransparentGraphOp(void)
{
}

MakeTransparentGraphOpTransitPtr
MakeTransparentGraphOp::create(void)
{
    return MakeTransparentGraphOpTransitPtr(new MakeTransparentGraphOp);
}

GraphOpTransitPtr MakeTransparentGraphOp::clone(void)
{
    return GraphOpTransitPtr(new MakeTransparentGraphOp);
}

bool MakeTransparentGraphOp::traverse(Node *node)
{
    // Find the materials.
    if(!GraphOp::traverse(node))
        return false;

    // Now do the merge.
    MaterialObjectMap::iterator mmIt = _materialMap.begin();
    for(; mmIt != _materialMap.end(); ++mmIt)
    {
        Material         *oldMaterial = mmIt->first;
        MaterialUnrecPtr  newMaterial =
            dynamic_pointer_cast<Material>(deepClone(oldMaterial));

        if(newMaterial != NULL)
        {
            std::cout << "Applying transparency:  ";

            applyTransparency(newMaterial);

            // Put the new material in the objects in this subtree.
            MaterialObjectList           &currentList = mmIt->second;
            MaterialObjectList::iterator i            = currentList.begin();
            
            for(; i != currentList.end(); ++i)
                i->setMaterial(newMaterial);
        }
    }

    return true;
}


void MakeTransparentGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   

    ps("transparency",  _transparency);
   
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("MakeTransparentGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string MakeTransparentGraphOp::usage(void)
{
    return 
    "MakeTransparent: make used Materials transparent\n"
    "  Based on MaterialMergeGraphOp, merges Materials and sets their\n"
    "  transparency.\n"
    "Params: name (type, default)\n"
    "  transparency (Real32, 0.5f): transparency value\n";    
}

Action::ResultE MakeTransparentGraphOp::traverseEnter(Node * const node)
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
    if (mg != NULL)
    {
        addObject(MaterialObject(mg));
        return Action::Continue;
    }

    // Otherwise, keep looking.
    return Action::Continue;
}

Action::ResultE MakeTransparentGraphOp::traverseLeave(
    Node * const    node,
    Action::ResultE res )
{
    return res;
}

void MakeTransparentGraphOp::addObject(MaterialObject m)
{
    Material *mat = m.getMaterial();
    if (mat == NULL)
        return;

    _materialMap[mat].push_back(m);
}


// Generally used to prevent templated functions from resolving to the
// same signature.
/*! \nohierarchy
 */

template<typename T>
struct Type2Type {
    typedef T Original;
};


template<typename Chunk>
typename Chunk::ObjUnrecPtr getOrAddChunk(
    ChunkMaterial *cm, Type2Type<Chunk> = Type2Type<Chunk>())
{
    OSG::StateChunk *stateChunk = cm->find(Chunk::getClassType());

    typename Chunk::ObjUnrecPtr chunk =
        dynamic_cast<typename Chunk::ObjCPtr>(stateChunk);

    if(!chunk)
    {
        chunk = Chunk::create();
        cm->addChunk(chunk);
    }
    return chunk;
}


void MakeTransparentGraphOp::applyTransparency(Material *m)
{
    SimpleMaterial *sm = dynamic_cast<SimpleMaterial *>(m);
    if (sm != NULL)
    {
        std::cout << "SimpleMaterial" << std::endl;
        sm->setTransparency(1.0f - (1.0f - sm->getTransparency()) * 
                            _transparency);
        sm->setColorMaterial(GL_NONE);

        PolygonChunk *polygonChunk = getOrAddChunk<PolygonChunk>(sm);
        polygonChunk->setCullFace(GL_BACK);
        return;
    }

    ChunkMaterial *cm = dynamic_cast<ChunkMaterial *>(m);
    if (cm != NULL)
    {
        std::cout << "ChunkMaterial" << std::endl;
        BlendChunk *blendChunk = getOrAddChunk<BlendChunk>(cm);
        blendChunk->setColor(Color4f(1.f, 1.f, 1.f, 1.f - _transparency));
        blendChunk->setSrcFactor(GL_CONSTANT_ALPHA);
        blendChunk->setDestFactor(GL_ONE_MINUS_CONSTANT_ALPHA);
        return;
    }
}
