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

#include "OSGConfig.h"
#include "OSGShaderCache.h"
#include "OSGShaderProgramVariableChunk.h"

#include "boost/bind.hpp"


OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ShaderCache::ShaderCache(void) :
#ifdef OSG_SHC_USE_REF
    _vShaderStore   (),
    _vShaderVarStore(),
#endif
    _oExeTree       (),
    _oVarTree       ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ShaderCache::~ShaderCache(void)
{
    clear();
}

#if defined(OSG_SHC_USE_REF) && !defined(OSG_SHC_MODE_0)
bool operator < (const ShaderCache::StoreElement    &rhs,
                 const ShaderCache::IdStore         &lhs)
{
    return rhs.first < lhs;
}

bool operator < (const ShaderCache::StoreVarElement &rhs,
                 const ShaderCache::IdStore         &lhs)
{
    return rhs.first < lhs;
}
#endif

ShaderExecutableChunk *ShaderCache::findShader(const IdStore &vIds)
{
#ifdef OSG_SHC_USE_REF
    ShaderStore::const_iterator sIt = std::lower_bound(_vShaderStore.begin(),
                                                       _vShaderStore.end  (),
                                                        vIds);
#endif

    ShaderExecutableChunk *returnValue = _oExeTree.find(vIds);

#ifdef OSG_SHC_USE_REF
    if(sIt == _vShaderStore.end())
    {
#ifdef OSG_ASSERT_TREE
        OSG_ASSERT(returnValue == NULL);
#endif

        return NULL;
    }
#endif

#ifdef OSG_SHC_USE_REF
    if(sIt->first != vIds)
    {
#ifdef OSG_ASSERT_TREE
        OSG_ASSERT(returnValue == NULL);
#endif

        return NULL;
    }
#endif

#ifdef OSG_SHC_USE_REF
#ifdef OSG_ASSERT_TREE
    OSG_ASSERT(returnValue == sIt->second);
#endif
#endif

#ifdef OSG_SHC_USE_REF
    return sIt->second;
#else
    return returnValue;
#endif
}

ShaderExecutableVarChunk *ShaderCache::findShaderVar(const IdStore &vIds)
{
#ifdef OSG_SHC_USE_REF
    ShaderVarStore::const_iterator vIt = 
        std::lower_bound(_vShaderVarStore.begin(),
                         _vShaderVarStore.end  (),
                          vIds                   );
#endif

    ShaderExecutableVarChunk *returnValue = _oVarTree.find(vIds);

#ifdef OSG_SHC_USE_REF
    if(vIt == _vShaderVarStore.end())
    {
#ifdef OSG_ASSERT_TREE
        OSG_ASSERT(returnValue == NULL);
#endif

        return NULL;
    }
#endif

#ifdef OSG_SHC_USE_REF
    if(vIt->first != vIds)
    {
#ifdef OSG_ASSERT_TREE
        OSG_ASSERT(returnValue == NULL);
#endif

        return NULL;
    }
#endif

#ifdef OSG_SHC_USE_REF
#ifdef OSG_ASSERT_TREE
    OSG_ASSERT(returnValue == vIt->second);
#endif
#endif

#ifdef OSG_SHC_USE_REF
    return vIt->second;
#else
    return returnValue;
#endif
}

void ShaderCache::addShader (const IdStore               &vIds,
                                   ShaderExecutableChunk *pShader)
{
#ifdef OSG_SHC_USE_REF
    ShaderStore::iterator sIt = std::lower_bound(_vShaderStore.begin(),
                                                 _vShaderStore.end  (),
                                                  vIds                );

#ifdef OSG_ASSERT_TREE
    bool bAdded = false;
#endif

    if(sIt == _vShaderStore.end())
    {
        _vShaderStore.push_back(StoreElement(vIds, pShader));

#ifdef OSG_SHC_REF_CLEANUP
        updateRemoveCallback(pShader);
#endif

#ifdef OSG_ASSERT_TREE
        bAdded = true;
#endif
    }
    else if(sIt->first != vIds)
    {
        _vShaderStore.insert(sIt, StoreElement(vIds, pShader));

#ifdef OSG_SHC_REF_CLEANUP
        updateRemoveCallback(pShader);
#endif

#ifdef OSG_ASSERT_TREE
        bAdded = true;
#endif
    }
#ifdef OSG_ASSERT_TREE
    else
    {
        OSG_ASSERT(sIt->second == pShader);
    }
#endif
#endif

    if(_oExeTree.add(vIds, pShader) == true)
    {
#ifdef OSG_SHC_USE_REF
#ifdef OSG_ASSERT_TREE
        OSG_ASSERT(bAdded == true);
#endif
#endif

#ifndef OSG_SHC_REF_CLEANUP
        updateRemoveCallback(pShader);
#endif
    }
}

void ShaderCache::addShaderVar(const IdStore                  &vIds,
                                     ShaderExecutableVarChunk *pVar)
{
#ifdef OSG_SHC_USE_REF
    ShaderVarStore::iterator vIt = 
        std::lower_bound(_vShaderVarStore.begin(),
                         _vShaderVarStore.end  (),
                          vIds                   );

#ifdef OSG_ASSERT_TREE
    bool bAdded = false;
#endif

    if(vIt == _vShaderVarStore.end())
    {
        _vShaderVarStore.push_back(StoreVarElement(vIds, pVar));

#ifdef OSG_SHC_REF_CLEANUP
        updateRemoveCallback(pVar);
#endif

#ifdef OSG_ASSERT_TREE
        bAdded = true;
#endif
    }
    else if(vIt->first != vIds)
    {
        _vShaderVarStore.insert(vIt, StoreVarElement(vIds, pVar));

#ifdef OSG_SHC_REF_CLEANUP
        updateRemoveCallback(pVar);
#endif

#ifdef OSG_ASSERT_TREE
        bAdded = true;
#endif
    }
#ifdef OSG_ASSERT_TREE
    else
    {
        OSG_ASSERT(vIt->second == pVar);
    }
#endif
#endif

    if(_oVarTree.add(vIds, pVar) == true)
    {
#ifdef OSG_SHC_USE_REF
#ifdef OSG_ASSERT_TREE
        OSG_ASSERT(bAdded == true);
#endif
#endif

#ifndef OSG_SHC_REF_CLEANUP
        updateRemoveCallback(pVar);
#endif
    }
}

void ShaderCache::clear(void)
{
#ifdef OSG_SHC_USE_REF
    ShaderStore::const_iterator sIt  = _vShaderStore.begin();
    ShaderStore::const_iterator sEnd = _vShaderStore.end  ();

#ifdef OSG_SHC_REF_CLEANUP
    for(; sIt != sEnd; ++sIt)
    {
        clearShRemoveCallback(sIt->second);
    }
#endif
#endif

    _oExeTree.destroy(boost::bind(&ShaderCache::clearShRemoveCallback,
                                   this,
                                  _1));

#ifdef OSG_SHC_USE_REF
    ShaderVarStore::const_iterator vIt  = _vShaderVarStore.begin();
    ShaderVarStore::const_iterator vEnd = _vShaderVarStore.end  ();

#ifdef OSG_SHC_REF_CLEANUP
    for(; vIt != vEnd; ++vIt)
    {
        clearVaRemoveCallback(vIt->second);
    }
#endif
#endif

    _oVarTree.destroy(boost::bind(&ShaderCache::clearVaRemoveCallback,
                                   this,
                                  _1));
}

void ShaderCache::dump(void)
{
#ifdef OSG_SHC_USE_REF
    fprintf(stderr, "Dump shader cache \n");

    ShaderStore::const_iterator sIt  = _vShaderStore.begin();
    ShaderStore::const_iterator sEnd = _vShaderStore.end  ();


    for(; sIt != sEnd; ++sIt)
    {
        IdStore::const_iterator idIt  = sIt->first.begin();
        IdStore::const_iterator idEnd = sIt->first.end  ();

        fprintf(stderr, " ");

        for(; idIt != idEnd; ++idIt)
        {
            fprintf(stderr, "%d ", *idIt);
        }
        
        fprintf(stderr, ": %p\n", sIt->second.get());
    }


    ShaderVarStore::const_iterator vIt  = _vShaderVarStore.begin();
    ShaderVarStore::const_iterator vEnd = _vShaderVarStore.end  ();


    for(; vIt != vEnd; ++vIt)
    {
        IdStore::const_iterator idIt  = vIt->first.begin();
        IdStore::const_iterator idEnd = vIt->first.end  ();

        fprintf(stderr, " ");

        for(; idIt != idEnd; ++idIt)
        {
            fprintf(stderr, "%d ", *idIt);
        }
        
        fprintf(stderr, ": %p\n", vIt->second.get());
    }
#endif

    _oExeTree.dumpDot("/tmp/exetree.dot");
    _oVarTree.dumpDot("/tmp/vartree.dot");
}

void ShaderCache::updateRemoveCallback(ShaderExecutableChunk *pShader)
{
    if(pShader == NULL)
        return;

    ShaderExecutableChunk::FragmentShaderIt fIt  = 
        pShader->getMFFragmentShader()->begin();
    ShaderExecutableChunk::FragmentShaderIt fEnd = 
        pShader->getMFFragmentShader()->end  ();

    for(; fIt != fEnd; ++fIt)
    {
        if(*fIt == NULL)
            continue;

        if((*fIt)->hasDestroyedFunctor(
               boost::bind(&ShaderCache::removeShaderProgram,
                           this,
                           _1,
                           _2)) == false)
        {
            (*fIt)->addDestroyedFunctor(
                boost::bind(&ShaderCache::removeShaderProgram,
                            this,
                            _1,
                            _2),
                "");
        }
    }

    ShaderExecutableChunk::GeometryShaderIt gIt  = 
        pShader->getMFGeometryShader()->begin();
    ShaderExecutableChunk::GeometryShaderIt gEnd = 
        pShader->getMFGeometryShader()->end  ();

    for(; gIt != gEnd; ++gIt)
    {
        if(*gIt == NULL)
            continue;

        if((*gIt)->hasDestroyedFunctor(
               boost::bind(&ShaderCache::removeShaderProgram,
                           this,
                           _1,
                           _2)) == false)
        {
            (*gIt)->addDestroyedFunctor(
                boost::bind(&ShaderCache::removeShaderProgram,
                            this,
                            _1,
                            _2),
                "");
        }
    }


    ShaderExecutableChunk::VertexShaderIt vIt  = 
        pShader->getMFVertexShader()->begin();
    ShaderExecutableChunk::FragmentShaderIt vEnd = 
        pShader->getMFVertexShader()->end  ();

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt == NULL)
            continue;

        if((*vIt)->hasDestroyedFunctor(
               boost::bind(&ShaderCache::removeShaderProgram,
                           this,
                           _1,
                           _2)) == false)
        {
            (*vIt)->addDestroyedFunctor(
                boost::bind(&ShaderCache::removeShaderProgram,
                            this,
                            _1,
                            _2),
                "");
        }
    }
}

void ShaderCache::clearShRemoveCallback(ShaderExecutableChunk *pShader)
{
    if(pShader == NULL)
        return;

    ShaderExecutableChunk::FragmentShaderIt fIt  = 
        pShader->getMFFragmentShader()->begin();
    ShaderExecutableChunk::FragmentShaderIt fEnd = 
        pShader->getMFFragmentShader()->end  ();

    for(; fIt != fEnd; ++fIt)
    {
        if(*fIt == NULL)
            continue;

        (*fIt)->subDestroyedFunctor(
            boost::bind(&ShaderCache::removeShaderProgram,
                        this,
                        _1,
                        _2));
    }

    ShaderExecutableChunk::GeometryShaderIt gIt  = 
        pShader->getMFGeometryShader()->begin();
    ShaderExecutableChunk::GeometryShaderIt gEnd = 
        pShader->getMFGeometryShader()->end  ();

    for(; gIt != gEnd; ++gIt)
    {
        if(*gIt == NULL)
            continue;

        (*gIt)->subDestroyedFunctor(
            boost::bind(&ShaderCache::removeShaderProgram,
                        this,
                        _1,
                        _2));
    }


    ShaderExecutableChunk::VertexShaderIt vIt  = 
        pShader->getMFVertexShader()->begin();
    ShaderExecutableChunk::FragmentShaderIt vEnd = 
        pShader->getMFVertexShader()->end  ();

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt == NULL)
            continue;

        (*vIt)->subDestroyedFunctor(
            boost::bind(&ShaderCache::removeShaderProgram,
                        this,
                        _1,
                        _2));
    }
}



void ShaderCache::updateRemoveCallback(ShaderExecutableVarChunk *pVar)
{
    if(pVar == NULL)
        return;

    ShaderExecutableVarChunk::VarChunksIt vIt  = 
        pVar->getMFProgramVarChunks()->begin();
    ShaderExecutableVarChunk::VarChunksIt vEnd = 
        pVar->getMFProgramVarChunks()->end  ();

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt == NULL)
            continue;

        if((*vIt)->hasDestroyedFunctor(
               boost::bind(&ShaderCache::removeShaderVar,
                           this,
                           _1,
                           _2)) == false)
        {
            (*vIt)->addDestroyedFunctor(
                boost::bind(&ShaderCache::removeShaderVar,
                            this,
                            _1,
                            _2),
                "");
        }
    }
}

void ShaderCache::clearVaRemoveCallback(ShaderExecutableVarChunk *pVar)
{
    if(pVar == NULL)
        return;

    ShaderExecutableVarChunk::VarChunksIt vIt  = 
        pVar->getMFProgramVarChunks()->begin();
    ShaderExecutableVarChunk::VarChunksIt vEnd = 
        pVar->getMFProgramVarChunks()->end  ();

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt == NULL)
            continue;

        (*vIt)->subDestroyedFunctor(
            boost::bind(&ShaderCache::removeShaderVar,
                        this,
                        _1,
                        _2));
    }
}


void ShaderCache::removeShaderProgram(FieldContainer    *pContainer, 
                                      ConstFieldMaskArg  whichField)
{
    ShaderProgram *pShaderProg = dynamic_cast<ShaderProgram *>(pContainer);

    if(pShaderProg == NULL)
        return;

    UInt16 uiShaderId = pShaderProg->getProgramId();

#ifdef OSG_SHC_USE_REF
    ShaderStore::      iterator sIt  = _vShaderStore.begin();
    ShaderStore::const_iterator sEnd = _vShaderStore.end  ();


    while(sIt != sEnd)
    {
        IdStore::const_iterator idIt  = std::find(sIt->first.begin(),
                                                  sIt->first.end  (),
                                                  uiShaderId);

        if(idIt != sIt->first.end())
        {
            sIt  = _vShaderStore.erase(sIt);
            sEnd = _vShaderStore.end();
        }
        else
        {
            ++sIt;
        }
    }
#endif

    _oExeTree.sub(uiShaderId);
}


void ShaderCache::removeShaderVar(FieldContainer    *pContainer, 
                                  ConstFieldMaskArg  whichField)
{
    ShaderProgramVariableChunk *pShaderVar = 
        dynamic_cast<ShaderProgramVariableChunk *>(pContainer);

    if(pShaderVar == NULL)
        return;

    UInt16 uiVarId = pShaderVar->getVariableId();

#ifdef OSG_SHC_USE_REF
    ShaderVarStore::      iterator vIt  = _vShaderVarStore.begin();
    ShaderVarStore::const_iterator vEnd = _vShaderVarStore.end  ();

    while(vIt != vEnd)
    {
        IdStore::const_iterator idIt  = std::find(vIt->first.begin(),
                                                  vIt->first.end  (),
                                                  uiVarId);

        if(idIt != vIt->first.end())
        {
            vIt  = _vShaderVarStore.erase(vIt);
            vEnd = _vShaderVarStore.end();
        }
        else
        {
            ++vIt;
        }
    }
#endif

    _oVarTree.sub(uiVarId);
}

OSG_END_NAMESPACE
