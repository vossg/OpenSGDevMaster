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


#include <OSGBlendChunk.h>
#include <OSGMakeTransparentGraphOp.h>
#include <OSGPolygonChunk.h>
#include <OSGSimpleMaterial.h>
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpFactory::the()->registerOp(new MakeTransparentGraphOp);
    return true;
}
static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

MakeTransparentGraphOp::MakeTransparentGraphOp(const char* name)
    : GraphOp(name),
      _transparency(0.5)
{
}

MakeTransparentGraphOp::~MakeTransparentGraphOp(void)
{
}

GraphOp* MakeTransparentGraphOp::create()
{
    return new MakeTransparentGraphOp();
}


// Similar to boost's next iterator function.  (I think it's from
// boost, at least.)
template<typename T>
T next(T t) // Iterator passed by value.
{
    return ++t;
}


bool MakeTransparentGraphOp::traverse(NodePtr& node)
{
    // Find the materials.
    if (!GraphOp::traverse(node)) {
        return false;
    }

    // Now do the merge.
    MaterialObjectMap::iterator itr = _materialObjects.begin();
    for (; itr != _materialObjects.end(); ++itr)
    {
        MaterialPtr oldMaterial = itr->first;
        MaterialPtr newMaterial = dynamic_cast<MaterialPtr>(deepClone(oldMaterial));
        if (newMaterial != NullFC)
        {
            std::cout << "Applying transparency:  ";

            applyTransparency(newMaterial);

            // Put the new material in the objects in this subtree.
            MaterialObjectList& currentList = itr->second;
            MaterialObjectList::iterator i = currentList.begin();
            for (; i != currentList.end(); ++i)
            {
                i->setMaterial(newMaterial);
            }
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

Action::ResultE MakeTransparentGraphOp::traverseEnter(NodePtrConstArg node)
{
    GeometryPtr geo = dynamic_cast<GeometryPtr>(node->getCore());
    if (geo != NullFC)
    {
        addObject(MaterialObject(geo));
        return Action::Continue;
    }

    MaterialGroupPtr mg = dynamic_cast<MaterialGroupPtr>(node->getCore());
    if (mg != NullFC)
    {
        addObject(MaterialObject(mg));
        return Action::Continue;
    }

    // Otherwise, keep looking.
    return Action::Continue;
}

Action::ResultE MakeTransparentGraphOp::traverseLeave(NodePtrConstArg node, Action::ResultE res)
{
    return res;
}

void MakeTransparentGraphOp::addObject(MaterialObject m)
{
    MaterialPtr mat = m.getMaterial();
    if (mat == NullFC)
        return;

    _materialObjects[mat].push_back(m);
}


// Generally used to prevent templated functions from resolving to the
// same signature.
template<typename T>
struct Type2Type {
    typedef T Original;
};


template<typename Chunk>
typename Chunk::ObjPtr getOrAddChunk(ChunkMaterialPtr cm,
                                     Type2Type<Chunk> = Type2Type<Chunk>()) {
    OSG::StateChunkPtr stateChunk = cm->find(Chunk::getClassType());

    typename Chunk::ObjPtr chunk = dynamic_cast<typename Chunk::ObjPtr>(stateChunk);

    if (!chunk) {
        chunk = Chunk::create();
        cm->addChunk(chunk);
    }
    return chunk;
}


void MakeTransparentGraphOp::applyTransparency(MaterialPtr m) {
 
    SimpleMaterialPtr sm = dynamic_cast<SimpleMaterialPtr>(m);
    if (sm != NullFC) {
        std::cout << "SimpleMaterial" << std::endl;
        sm->setTransparency(1.0f - (1.0f - sm->getTransparency()) * 
                            _transparency);
        sm->setColorMaterial(GL_NONE);

        PolygonChunkPtr polygonChunk = getOrAddChunk<PolygonChunk>(sm);
        polygonChunk->setCullFace(GL_BACK);
        return;
    }

    ChunkMaterialPtr cm = dynamic_cast<ChunkMaterialPtr>(m);
    if (cm != NullFC) {
        std::cout << "ChunkMaterial" << std::endl;
        BlendChunkPtr blendChunk = getOrAddChunk<BlendChunk>(cm);
        blendChunk->setColor(Color4f(1, 1, 1, _transparency));
        blendChunk->setSrcFactor(GL_SRC_ALPHA);
        blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        return;
    }
}
