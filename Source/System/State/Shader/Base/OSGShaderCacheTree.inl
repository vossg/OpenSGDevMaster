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

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template<class ObjectT> inline
ObjectT *ShaderVectorCache<ObjectT>::find(const IdStore &vIds)
{
    typename ObjectStore::const_iterator sIt = 
        std::lower_bound(_vObjectStore.begin(),
                         _vObjectStore.end  (),
                          vIds);

    if(sIt == _vObjectStore.end())
    {
        return NULL;
    }

    if(sIt->first != vIds)
    {
        return NULL;
    }

    return sIt->second;
}

template<class ObjectT> inline
bool ShaderVectorCache<ObjectT>::add (const IdStore &vIds,
                                            ObjectT *pObject)
{
    bool returnValue = false;

    typename ObjectStore::iterator sIt = std::lower_bound(_vObjectStore.begin(),
                                                          _vObjectStore.end  (),
                                                           vIds               );


    if(sIt == _vObjectStore.end())
    {
        _vObjectStore.push_back(StoreElement(vIds, pObject));

        returnValue = true;
    }
    else if(sIt->first != vIds)
    {
        _vObjectStore.insert(sIt, StoreElement(vIds, pObject));

        returnValue = true;
    }

    return returnValue;
}

template<class ObjectT> inline
void ShaderVectorCache<ObjectT>::sub(UInt32 uiIdx)
{
    typename ObjectStore::      iterator sIt  = _vObjectStore.begin();
    typename ObjectStore::const_iterator sEnd = _vObjectStore.end  ();


    while(sIt != sEnd)
    {
        IdStore::const_iterator idIt  = std::find(sIt->first.begin(),
                                                  sIt->first.end  (),
                                                  uiIdx);

        if(idIt != sIt->first.end())
        {
            sIt  = _vObjectStore.erase(sIt);
            sEnd = _vObjectStore.end();
        }
        else
        {
            ++sIt;
        }
    }
}

template<class ObjectT> inline
void ShaderVectorCache<ObjectT>::dumpDot(const Char8 *szFilename)
{
}

template<class ObjectT> 
template <typename ElemDestFunc> inline
void ShaderVectorCache<ObjectT>::destroy(ElemDestFunc destFunc)
{
#ifndef OSG_SHC_REF_CLEANUP
    typename ObjectStore::      iterator sIt  = _vObjectStore.begin();
    typename ObjectStore::const_iterator sEnd = _vObjectStore.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (destFunc)(sIt->second);

        sIt->second = NULL;
    }
#endif

}

template<class ObjectT> inline
ShaderVectorCache<ObjectT>::ShaderVectorCache(void) :
    _vObjectStore()
{
}

template<class ObjectT> inline
ShaderVectorCache<ObjectT>::~ShaderVectorCache(void)
{
}



/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template<class ObjectT> inline
ObjectT *ShaderMapCache<ObjectT>::find(const IdStore &vIds)
{
    typename ObjectStore::const_iterator sIt = _vObjectStore.find(vIds);

    if(sIt == _vObjectStore.end())
    {
        return NULL;
    }

    return sIt->second;
}

template<class ObjectT> inline
bool ShaderMapCache<ObjectT>::add (const IdStore &vIds,
                                         ObjectT *pObject)
{
    bool returnValue = false;

    typename ObjectStore::iterator sIt = _vObjectStore.lower_bound(vIds);


    if(sIt == _vObjectStore.end() || sIt->first != vIds)
    {
        _vObjectStore.insert(sIt, std::make_pair(vIds, pObject));

        returnValue = true;
    }

    return returnValue;
}

template<class ObjectT> inline
void ShaderMapCache<ObjectT>::sub(UInt32 uiIdx)
{
    typename ObjectStore::      iterator sIt  = _vObjectStore.begin();
    typename ObjectStore::const_iterator sEnd = _vObjectStore.end  ();

    std::vector<IdStore> vDestKeys;

    while(sIt != sEnd)
    {
        IdStore::const_iterator idIt  = std::find(sIt->first.begin(),
                                                  sIt->first.end  (),
                                                  uiIdx);

        if(idIt != sIt->first.end())
        {
            vDestKeys.push_back(sIt->first);
        }

        ++sIt;
    }

    std::vector<IdStore>::const_iterator kIt  = vDestKeys.begin();
    std::vector<IdStore>::const_iterator kEnd = vDestKeys.end  ();

    for(; kIt != kEnd; ++kIt)
    {
        _vObjectStore.erase(*kIt);
    }
}

template<class ObjectT> inline
void ShaderMapCache<ObjectT>::dumpDot(const Char8 *szFilename)
{
}

template<class ObjectT> 
template <typename ElemDestFunc> inline
void ShaderMapCache<ObjectT>::destroy(ElemDestFunc destFunc)
{
#ifndef OSG_SHC_REF_CLEANUP
    typename ObjectStore::      iterator sIt  = _vObjectStore.begin();
    typename ObjectStore::const_iterator sEnd = _vObjectStore.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (destFunc)(sIt->second);

        sIt->second = NULL;
    }
#endif

}

template<class ObjectT> inline
ShaderMapCache<ObjectT>::ShaderMapCache(void) :
    _vObjectStore()
{
}

template<class ObjectT> inline
ShaderMapCache<ObjectT>::~ShaderMapCache(void)
{
}



/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


#if defined(WIN32) || defined(__APPLE__) || \
    defined(__GXX_EXPERIMENTAL_CXX0X__)
template<class ObjectT, UInt32 LevelBits> 
const Real32 ShaderCacheTreeV0<ObjectT, LevelBits>::LevelFactor = 
                                                           1.f / (LevelBits);
#endif

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV0<ObjectT, LevelBits>::TreeNode::TreeNode(void) :
#ifdef OSG_DEBUG
    _uiNodeId(0   ),
#endif
    _pObject (NULL),
    _pPrev   (NULL),
    _pNext   (NULL)
{
    memset(&(_vChildren[0]), 0, LevelSize * sizeof(TreeNode *));
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV0<ObjectT, LevelBits>::TreeNode::~TreeNode(void)
{
    _pObject  = NULL;
    _pPrev    = NULL;
    _pNext    = NULL;
}
        
template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::TreeNode::clear(void)
{
    _pObject  = NULL;
    _pPrev    = NULL;
    _pNext    = NULL;
    
    memset(&(_vChildren[0]), 0, LevelSize * sizeof(TreeNode *));
}


static UInt16 IdxToBits[9] = 
{
    0x0000,

    0x0001,
    0x0002,
    0x0004,
    0x0008,

    0x0010,
    0x0020,
    0x0040,
    0x0080
};

template<class ObjectT, UInt32 LevelBits> inline
ObjectT *ShaderCacheTreeV0<ObjectT, LevelBits>::find(const IdStore &vIds)
{
    if(vIds.size() < 1)
        return NULL;

    ObjectT *returnValue = NULL;

    IdType uiStartId     = vIds[0] - 1;
    IdType uiStartLevel  = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId      = 0;
    UInt32 uiLastId      = vIds.size();
  

    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }


    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrBits = 0x0000;
    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

    if(pCurrNode == NULL)
        return NULL;

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
           
            continue;
        }
        else
        {
            pCurrNode = pCurrNode->_vChildren[uiCurrBits];

            if(pCurrNode == NULL)
            {
                break;
            }

            uiCurrBits  = 0x0000;

            uiLevelSub += LevelBits;
            uiCurrIdx  -= LevelBits;

            while(uiCurrIdx > LevelBits)
            {
                pCurrNode = pCurrNode->_vChildren[0];

                if(pCurrNode == NULL)
                {
                    break;
                }
                uiLevelSub += LevelBits;
                uiCurrIdx  -= LevelBits;
            }

            if(pCurrNode == NULL)
            {
                break;
            }

            uiCurrBits |= IdxToBits[uiCurrIdx]; 
        }
    }

    if(pCurrNode != NULL)
    {
        pCurrNode = pCurrNode->_vChildren[uiCurrBits];
        
        if(pCurrNode != NULL)
        {
            returnValue = pCurrNode->_pObject;
        }
    }

    return returnValue;
}


template<class ObjectT, UInt32 LevelBits> inline
bool ShaderCacheTreeV0<ObjectT, LevelBits>::add(const IdStore &vIds,
                                                      ObjectT *pObject)
{
    bool returnValue = false;

    if(vIds.size() < 1)
        return returnValue;

    IdType uiStartId    = vIds[0] - 1;

    IdType uiStartLevel = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId     = 0;
    UInt32 uiLastId     = vIds.size();

    
    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }

    UInt32 uiLevelSub   = (uiStartLevel * LevelBits);
   
    TreeNode *pCurrNode = _vLevelEntries[uiStartLevel];
    TreeNode *pNextNode = NULL;

    UInt32 uiCurrBits = 0x0000;

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
            
            continue;
        }
        else
        {
            pNextNode = pCurrNode->_vChildren[uiCurrBits];

            if(pNextNode == NULL)
            {
                pNextNode = allocateNode();

                pCurrNode->_vChildren[uiCurrBits] = pNextNode;

                if(uiStartLevel == _vLevelEntries.size() - 1)
                {
                    if(_vLevelEntries.back()->_vChildren[0] == NULL)
                    {
                        TreeNode *pTmpNode = allocateNode();
                        
                        _vLevelEntries.back()->_vChildren[0] = pTmpNode;

                        _vLevelEntries.push_back(pTmpNode);
                        
                        pTmpNode->_pNext  = pNextNode;
                        pNextNode->_pPrev = pTmpNode;
                    }
                    else
                    {
                        _vLevelEntries.push_back(pNextNode);
                    }
                }
                else
                {
                    pNextNode->_pNext = 
                        _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext;

                    if(pNextNode->_pNext != NULL)
                    {
                        pNextNode->_pNext->_pPrev = pNextNode;
                    }

                    _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext = 
                        pNextNode;

                    pNextNode->_pPrev = 
                        _vLevelEntries[uiStartLevel]->_vChildren[0];
                }
            }

            ++uiStartLevel;

            uiCurrBits  = 0x0000;

            pCurrNode   = pNextNode;

            uiLevelSub += LevelBits;
            uiCurrIdx  -= LevelBits;

            while(uiCurrIdx > LevelBits)
            {
                if(pCurrNode->_vChildren[0] == NULL)
                {
                    pNextNode = allocateNode();

                    pCurrNode->_vChildren[0] = pNextNode;

                    if(uiStartLevel == _vLevelEntries.size() - 1)
                    {
                        if(_vLevelEntries.back()->_vChildren[0] == NULL)
                        {
                            TreeNode *pTmpNode = allocateNode();
                            
                            _vLevelEntries.back()->_vChildren[0] = pTmpNode;
                            
                            _vLevelEntries.push_back(pTmpNode);
                            
                            pTmpNode->_pNext  = pNextNode;
                            pNextNode->_pPrev = pTmpNode;
                        }
                        else
                        {
                            _vLevelEntries.push_back(pNextNode);
                        }
                    }
                    else
                    {
                        pNextNode->_pNext = 
                            _vLevelEntries[uiStartLevel]->
                                _vChildren[0]->_pNext;

                        if(pNextNode->_pNext != NULL)
                        {
                            pNextNode->_pNext->_pPrev = pNextNode;
                        }
                
                        _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext= 
                            pNextNode;

                        pNextNode->_pPrev = 
                            _vLevelEntries[uiStartLevel]->_vChildren[0];
                    }
                }

                pCurrNode = pCurrNode->_vChildren[0];

                uiLevelSub += LevelBits;
                uiCurrIdx  -= LevelBits;
                ++uiStartLevel;
            }



            uiCurrBits |= IdxToBits[uiCurrIdx]; 
       }
    }
    
    if(pCurrNode != NULL)
    {
        pNextNode = pCurrNode->_vChildren[uiCurrBits];
        
        if(pNextNode != NULL)
        {
            if(pNextNode->_pObject == NULL)
            {
                pNextNode->_pObject = pObject;
                
                returnValue = true;
            }
            else
            {
                OSG_ASSERT(pNextNode->_pObject == pObject);
            }
        }
        else
        {
            pNextNode = allocateNode();

            pCurrNode->_vChildren[uiCurrBits] = pNextNode;

            if(uiStartLevel == _vLevelEntries.size() - 1)
            {
                if(uiCurrBits == 0)
                {
                    OSG_ASSERT(false);
                    _vLevelEntries.push_back(pNextNode);
                }
                else
                {
                    TreeNode *pTmpNode = allocateNode();
                    
                    _vLevelEntries.back()->_vChildren[0] = pTmpNode;

                    _vLevelEntries.push_back(pTmpNode);
                    
                    pTmpNode->_pNext  = pNextNode;
                    pNextNode->_pPrev = pTmpNode;
                }
            }
            else
            {
                pNextNode->_pNext = 
                    _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext;

                if(pNextNode->_pNext != NULL)
                {
                    pNextNode->_pNext->_pPrev = pNextNode;
                }
                
                _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext = 
                    pNextNode;

                pNextNode->_pPrev = 
                    _vLevelEntries[uiStartLevel]->_vChildren[0];
            }

            pNextNode->_pObject = pObject;
                
            returnValue = true;
        }
    }

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::sub(UInt32 uiIdx)
{
    IdType uiStartLevel  = IdType((uiIdx - 1) * LevelFactor);

    if(uiStartLevel >= _vLevelEntries.size())
    {
        return;
    }

    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrIdx  = uiIdx - uiLevelSub;
    UInt32    uiCurrBits = IdxToBits[uiCurrIdx];

    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

    for(; pCurrNode != NULL; pCurrNode = pCurrNode->_pNext)
    {
        for(UInt32 i = 0; i < LevelSize; ++i)
        {
            TreeNode *pChild = pCurrNode->_vChildren[i];

            if(0x0000 != (i & uiCurrBits) && pChild != NULL)
            {
                if(pChild->_pNext == NULL)
                {
                    pChild->_pPrev->_pNext = NULL;
                }
                else
                {
                    pChild->_pPrev->_pNext = pChild->_pNext;
                    pChild->_pNext->_pPrev = pChild->_pPrev;
                }
                
                pChild->_pPrev = NULL;
                pChild->_pNext = NULL;

                eraseNode(pCurrNode->_vChildren[i]);
                pCurrNode->_vChildren[i] = NULL;
            }
        }
    }
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::dumpDot(const Char8 *szFilename)
{
    FILE *pOut = fopen(szFilename, "w");

    if(pOut != NULL)
    {
        fprintf(pOut, "digraph structs\n");
        fprintf(pOut, "{\n");
        fprintf(pOut, "node [shape=record];\n");

        std::vector<std::vector<TreeNode *> > vLevelStore;

        dumpDotNode(_pRoot, pOut, vLevelStore, 0);

#ifdef OSG_DEBUG
        fprintf(pOut, "struct%d\n", 0);
        fprintf(pOut, "[\n");
        fprintf(pOut, "    label=\"");

        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, "<l%d> %d", i, i);
            }
            else
            {
                fprintf(pOut, "<l%d> NIL", i);
            }
            
            if(i == _vLevelEntries.size() - 1)
            {
                fprintf(pOut, "\"\n");
            }
            else
            {
                fprintf(pOut, "|");
            }
        }
        
        fprintf(pOut, "]\n");

   
        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, "struct%d:l%d -> struct%d:l%d;\n",
                        0, i,
                        _vLevelEntries[i]->_uiNodeId, 0);
            }
        }

        for(UInt32 i = 0; i < vLevelStore.size(); ++i)
        {
            fprintf(pOut, "{ rank=same;");

            for(UInt32 j = 0; j < vLevelStore[i].size(); ++j)
            {
                TreeNode *pChild = vLevelStore[i][j];

                if(pChild != NULL)
                {           
                    fprintf(pOut, "\"struct%d\";",
                            pChild->_uiNodeId);
                }
            }

            fprintf(pOut, "}\n");
        }
#endif
        
        fprintf(pOut, "}\n");
        fclose(pOut);
    }
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::dumpDotNode(
    TreeNode                              *pNode, 
    FILE                                  *pOut ,
    std::vector<std::vector<TreeNode *> > &vLevelStore,
    UInt32                                 uiLevel    )
{
#ifdef OSG_DEBUG
    if(pNode == NULL)
        return;

    if(uiLevel == vLevelStore.size())
    {
        vLevelStore.push_back(std::vector<TreeNode *>());
    }

    fprintf(pOut, "struct%d\n", pNode->_uiNodeId);
    fprintf(pOut, "[\n");
    fprintf(pOut, "    label=\"");

    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "<prev> P|");
    }
    else
    {
        fprintf(pOut, "<prev> P:NIL|");
    }

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i] != NULL)
        {
            fprintf(pOut, "<l%d> %d|", i, i);
        }
        else
        {
            fprintf(pOut, "<l%d> NIL|", i);
        }
    }

    if(pNode->_pObject != NULL)
    {
        fprintf(pOut, "<val> VAL:Obj|");
    }
    else
    {
        fprintf(pOut, "<val> VAL:NIL|");
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "<next> N\"\n");
    }
    else
    {
        fprintf(pOut, "<next> N:NIL\"\n");
    }

    fprintf(pOut, "]\n");

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        TreeNode *pChild = pNode->_vChildren[i];

        if(pChild != NULL)
        {
            dumpDotNode(pChild, pOut, vLevelStore, uiLevel + 1);
            
            fprintf(pOut, "struct%d:l%d -> struct%d:l%d;\n",
                    pNode ->_uiNodeId, i,
                    pChild->_uiNodeId, UInt32(LevelSize/2));
        }
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "struct%d:next -> struct%d:prev;\n",
                pNode ->_uiNodeId,
                pNode->_pNext->_uiNodeId);
    }
    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "struct%d:prev -> struct%d:next;\n",
                pNode ->_uiNodeId,
                pNode->_pPrev->_uiNodeId);
    }

#if 0
    fprintf(pOut, "{ rank=same;");

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        TreeNode *pChild = pNode->_vChildren[i];

        if(pChild != NULL)
        {           
            fprintf(pOut, "\"struct%d\";",
                    pChild->_uiNodeId);
        }

    }

     fprintf(pOut, "}\n");
#endif

     vLevelStore[uiLevel].push_back(pNode);

#endif
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV0<ObjectT, LevelBits>::ShaderCacheTreeV0(void) :
#ifdef OSG_DEBUG
    _uiNodeCount  (0   ),
#endif
    _pRoot        (NULL),
    _vLevelEntries(    ),
    _qFreeElements(    )
{
    _pRoot = allocateNode();

    _vLevelEntries.push_back(_pRoot);
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV0<ObjectT, LevelBits>::~ShaderCacheTreeV0(void)
{
    typename std::deque <TreeNode *>::const_iterator qIt  = 
        _qFreeElements.begin();

    typename std::deque <TreeNode *>::const_iterator qEnd = 
        _qFreeElements.end();
    
    for(; qIt != qEnd; ++qIt)
    {
        delete (*qIt);
    }
}

template<class ObjectT, UInt32 LevelBits> inline
typename ShaderCacheTreeV0<ObjectT, LevelBits>::TreeNode *
    ShaderCacheTreeV0<ObjectT, LevelBits>::allocateNode(void)
{
    TreeNode *returnValue = NULL;

    if(_qFreeElements.empty() == false)
    {
        returnValue = _qFreeElements.back();

        _qFreeElements.pop_back();

        returnValue->clear();
    }
    else
    {
        returnValue = new TreeNode();

#ifdef OSG_DEBUG
        returnValue->_uiNodeId = ++_uiNodeCount;
#endif
    }

#ifdef OSG_DEBUG
    UInt64 rU = reinterpret_cast<UInt64>(returnValue);

    OSG_ASSERT((rU & 0x0001) == 0x0000);
#endif

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::eraseNode(TreeNode *pNode)
{
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i] != NULL)
        {
            eraseNode(pNode->_vChildren[i]);
        }
    }

    pNode->_pObject = NULL;

    _qFreeElements.push_back(pNode);
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::destroyNode(TreeNode     *pNode,
                                                        ElemDestFunc  destFunc)
{
    if(pNode == NULL)
        return;

    UInt32 uiChildStart = 0;

    if(pNode->_pPrev == NULL)
        uiChildStart = 1;

    for(UInt32 i = uiChildStart; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i] != NULL)
        {
            destroyNode(pNode->_vChildren[i], destFunc);
        }
    }

    if(pNode->_pObject != NULL)
    {
#ifndef OSG_SHC_REF_CLEANUP
        (destFunc)(pNode->_pObject);
#endif
        pNode->_pObject = NULL;
    }

    delete pNode;
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV0<ObjectT, LevelBits>::destroy(ElemDestFunc destFunc)
{
    destroyNode(_pRoot, destFunc);

    _vLevelEntries[0] = NULL;

    _pRoot = NULL;
}





/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
VariantPtr<Object1T, RefCountPol1,
           Object2T, RefCountPol2>::VariantPtr(void) :
    _val()
{
    _val._pObj1 = NULL;
}

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
VariantPtr<Object1T, RefCountPol1,
           Object2T, RefCountPol2>::~VariantPtr(void)
{
    if(_val._uiIntVal & UIMaskChoice)  //isObj1
    {
        _val._uiIntVal &= UIMaskPtr;

        RefCountPol1::subRef(_val._pObj1);
    }
}

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
Object1T *VariantPtr<Object1T, RefCountPol1,
                     Object2T, RefCountPol2>::asT1(void) const
{

    if(_val._uiIntVal & UIMaskChoice) //isObj1 
    {
        MemberU returnValue = { _val._uiIntVal & UIMaskPtr };

        return returnValue._pObj1;
    }
 
    return NULL;
}

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
Object2T *VariantPtr<Object1T, RefCountPol1,
                     Object2T, RefCountPol2>::asT2(void) const
{

    if(!(_val._uiIntVal & UIMaskChoice)) //!isObj1
        return _val._pObj2;

    return NULL;
}

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
void VariantPtr<Object1T, RefCountPol1,
                Object2T, RefCountPol2>::setAsT1(Object1T * const rhs)
{
    if(_val._uiIntVal & UIMaskChoice) //isObj1 
    {
        _val._uiIntVal &= UIMaskPtr;

        RefCountPol1::setRefd(_val._pObj1, rhs);
    }
    else
    {
        RefCountPol1::addRef(rhs);

        _val._pObj1 = rhs;
    }

    //isObj1
    _val._uiIntVal |= UIMaskChoice;

}

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
void VariantPtr<Object1T, RefCountPol1,
                Object2T, RefCountPol2>::setAsT2(Object2T * const rhs)
{
    if(_val._uiIntVal & UIMaskChoice) //isObj1
    {
        _val._uiIntVal &= UIMaskPtr;

        RefCountPol1::subRef(_val._pObj1);
    }

    _val._pObj2 = rhs;
}


template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
const VariantPtr<Object1T, RefCountPol1,
                 Object2T, RefCountPol2> &
    VariantPtr<Object1T, RefCountPol1,
               Object2T, RefCountPol2>::operator =(Object1T * const rhs)
{
    setAsT1(rhs);

    return *this;
}

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
const VariantPtr<Object1T, RefCountPol1,
                 Object2T, RefCountPol2> &
    VariantPtr<Object1T, RefCountPol1,
               Object2T, RefCountPol2>::operator =(Object2T * const rhs)
{
    setAsT2(rhs);

    return *this;
}


template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2> inline
Object2T *VariantPtr<Object1T, RefCountPol1,
                     Object2T, RefCountPol2>::operator ->(void) const
{
    return this->asT2();
}




/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(WIN32) || defined(__APPLE__) || \
    defined(__GXX_EXPERIMENTAL_CXX0X__)
template<class ObjectT, UInt32 LevelBits> 
const Real32 ShaderCacheTreeV1<ObjectT, LevelBits>::LevelFactor = 
                                                            1.f / (LevelBits);
#endif

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV1<ObjectT, LevelBits>::TreeNode::TreeNode(void) :
#ifdef OSG_DEBUG
    _uiNodeId(0   ),
#endif
    _pObject (NULL),
    _pPrev   (NULL),
    _pNext   (NULL)
{
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV1<ObjectT, LevelBits>::TreeNode::~TreeNode(void)
{
    _pObject = NULL;
    _pPrev   = NULL;
    _pNext   = NULL;

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        _vChildren[i].setAsT1(NULL);
    }
}
        
template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::TreeNode::clear(void)
{
    _pObject = NULL;
    _pPrev   = NULL;
    _pNext   = NULL;
    
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        _vChildren[i].setAsT1(NULL);
    }
}



template<class ObjectT, UInt32 LevelBits> inline
ObjectT *ShaderCacheTreeV1<ObjectT, LevelBits>::find(const IdStore &vIds)
{
    if(vIds.size() < 1)
        return NULL;

    ObjectT *returnValue = NULL;

    IdType uiStartId     = vIds[0] - 1;
    IdType uiStartLevel  = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId      = 0;
    UInt32 uiLastId      = vIds.size();
  

    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }


    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrBits = 0x0000;
    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

    if(pCurrNode == NULL)
        return nullptr;

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
           
            continue;
        }
        else
        {
            pCurrNode = pCurrNode->_vChildren[uiCurrBits].asT2();

            if(pCurrNode == NULL)
            {
                break;
            }

            uiCurrBits  = 0x0000;

            uiLevelSub += LevelBits;
            uiCurrIdx  -= LevelBits;

            while(uiCurrIdx > LevelBits)
            {
                pCurrNode = pCurrNode->_vChildren[0].asT2();

                if(pCurrNode == NULL)
                {
                    break;
                }
                uiLevelSub += LevelBits;
                uiCurrIdx  -= LevelBits;
            }

            if(pCurrNode == NULL)
            {
                break;
            }

            uiCurrBits |= IdxToBits[uiCurrIdx]; 
        }
    }

    if(pCurrNode != NULL)
    {
        TreeNode *pNext = pCurrNode->_vChildren[uiCurrBits].asT2();
        
        if(pNext != NULL)
        {
            returnValue = pNext->_pObject;
        }
        else
        {
            returnValue = pCurrNode->_vChildren[uiCurrBits].asT1();
        }
    }

    return returnValue;
}


template<class ObjectT, UInt32 LevelBits> inline
bool ShaderCacheTreeV1<ObjectT, LevelBits>::add(const IdStore &vIds,
                                                      ObjectT *pObject)
{
    bool returnValue = false;

    if(vIds.size() < 1)
        return returnValue;

    IdType uiStartId    = vIds[0] - 1;

    IdType uiStartLevel = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId     = 0;
    UInt32 uiLastId     = vIds.size();

    
    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }

    UInt32 uiLevelSub   = (uiStartLevel * LevelBits);
   
    TreeNode *pCurrNode = _vLevelEntries[uiStartLevel];
    TreeNode *pNextNode = NULL;

    UInt32 uiCurrBits = 0x0000;

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
            
            continue;
        }
        else
        {
            pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();

            if(pNextNode == NULL)
            {
                pNextNode = allocateNode();

                if(pCurrNode->_vChildren[uiCurrBits].asT1() != NULL)
                {
                    pNextNode->_pObject = 
                        pCurrNode->_vChildren[uiCurrBits].asT1();
                }

                pCurrNode->_vChildren[uiCurrBits] = pNextNode;

                if(uiStartLevel == _vLevelEntries.size() - 1)
                {
                    if(_vLevelEntries.back()->_vChildren[0].asT2() == NULL)
                    {
                        TreeNode *pTmpNode = allocateNode();
                        
                        _vLevelEntries.back()->_vChildren[0] = pTmpNode;

                        _vLevelEntries.push_back(pTmpNode);
                        
                        pTmpNode->_pNext  = pNextNode;
                        pNextNode->_pPrev = pTmpNode;
                    }
                    else
                    {
                        _vLevelEntries.push_back(pNextNode);
                    }
                }
                else
                {
                    pNextNode->_pNext = 
                        _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext;

                    if(pNextNode->_pNext != NULL)
                    {
                        pNextNode->_pNext->_pPrev = pNextNode;
                    }

                    _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext = 
                        pNextNode;

                    pNextNode->_pPrev = 
                        _vLevelEntries[uiStartLevel]->_vChildren[0].asT2();
                }
            }

            ++uiStartLevel;

            uiCurrBits  = 0x0000;

            pCurrNode   = pNextNode;

            uiLevelSub += LevelBits;
            uiCurrIdx  -= LevelBits;

            while(uiCurrIdx > LevelBits)
            {
                if(pCurrNode->_vChildren[0].asT2() == NULL)
                {
                    pNextNode = allocateNode();

                    pCurrNode->_vChildren[0] = pNextNode;

                    if(uiStartLevel == _vLevelEntries.size() - 1)
                    {
                        if(_vLevelEntries.back()->_vChildren[0].asT2() == NULL)
                        {
                            TreeNode *pTmpNode = allocateNode();
                            
                            _vLevelEntries.back()->_vChildren[0] = pTmpNode;
                            
                            _vLevelEntries.push_back(pTmpNode);
                            
                            pTmpNode->_pNext  = pNextNode;
                            pNextNode->_pPrev = pTmpNode;
                        }
                        else
                        {
                            _vLevelEntries.push_back(pNextNode);
                        }
                    }
                    else
                    {
                        pNextNode->_pNext = 
                            _vLevelEntries[uiStartLevel]->
                                _vChildren[0]->_pNext;

                        if(pNextNode->_pNext != NULL)
                        {
                            pNextNode->_pNext->_pPrev = pNextNode;
                        }
                
                        _vLevelEntries[uiStartLevel]->_vChildren[0]->_pNext= 
                            pNextNode;

                        pNextNode->_pPrev = 
                            _vLevelEntries[uiStartLevel]->_vChildren[0].asT2();
                    }
                }

                pCurrNode = pCurrNode->_vChildren[0].asT2();

                uiLevelSub += LevelBits;
                uiCurrIdx  -= LevelBits;
                ++uiStartLevel;
            }



            uiCurrBits |= IdxToBits[uiCurrIdx]; 
       }
    }
    
    if(pCurrNode != NULL)
    {
        pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();
        
        if(pNextNode != NULL)
        {
            if(pNextNode->_pObject == NULL)
            {
                pNextNode->_pObject = pObject;
                
                returnValue = true;
            }
            else
            {
                OSG_ASSERT(pNextNode->_pObject == pObject);
            }
        }
        else
        {
            pCurrNode->_vChildren[uiCurrBits] = pObject;
                
            returnValue = true;
        }
    }

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::sub(UInt32 uiIdx)
{
    IdType uiStartLevel  = IdType((uiIdx - 1) * LevelFactor);

    if(uiStartLevel >= _vLevelEntries.size())
    {
        return;
    }

    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrIdx  = uiIdx - uiLevelSub;
    UInt32    uiCurrBits = IdxToBits[uiCurrIdx];

    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

    for(; pCurrNode != NULL; pCurrNode = pCurrNode->_pNext)
    {
        for(UInt32 i = 0; i < LevelSize; ++i)
        {
            TreeNode *pChild = pCurrNode->_vChildren[i].asT2();

            if(0x0000 != (i & uiCurrBits) && pChild != NULL)
            {
                if(pChild->_pNext == NULL)
                {
                    pChild->_pPrev->_pNext = NULL;
                }
                else
                {
                    pChild->_pPrev->_pNext = pChild->_pNext;
                    pChild->_pNext->_pPrev = pChild->_pPrev;
                }
                
                pChild->_pPrev = NULL;
                pChild->_pNext = NULL;

                eraseNode(pCurrNode->_vChildren[i].asT2());
                pCurrNode->_vChildren[i].setAsT2(NULL);
            }
            else if(pCurrNode->_vChildren[i].asT1() != NULL)
            {
                pCurrNode->_vChildren[i].setAsT1(NULL);
            }
        }
    }
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::dumpDot(const Char8 *szFilename)
{
    FILE *pOut = fopen(szFilename, "w");

    if(pOut != NULL)
    {
        fprintf(pOut, "digraph structs\n");
        fprintf(pOut, "{\n");
        fprintf(pOut, "rankdir = LR;\n");
        fprintf(pOut, "splines=false\n");

        fprintf(pOut, "node [shape=record];\n");

        fprintf(pOut, "struct%d\n", 0);
        fprintf(pOut, "[\n");
        fprintf(pOut, "    label=\"");

        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, "<l%d> %d", i, i);
            }
            else
            {
                fprintf(pOut, "<l%d> NIL", i);
            }
            
            if(i == _vLevelEntries.size() - 1)
            {
                fprintf(pOut, "\"\n");
            }
            else
            {
                fprintf(pOut, "|");
            }
        }
        
        fprintf(pOut, "]\n");

        fprintf(pOut, "node [width = 1.5];\n");

        std::vector<std::vector<TreeNode *> > vLevelStore;

        dumpDotNode(_pRoot, pOut, vLevelStore, 0);

#ifdef OSG_DEBUG
        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, 
                        "struct%d:l%d -> struct%d:prev [color=\"green\"];\n",
                        0, i,
                        _vLevelEntries[i]->_uiNodeId);
            }
        }
#if 0
        for(UInt32 i = 0; i < vLevelStore.size(); ++i)
        {
            fprintf(pOut, "{ rank=same;");

            for(UInt32 j = 0; j < vLevelStore[i].size(); ++j)
            {
                TreeNode *pChild = vLevelStore[i][j];

                if(pChild != NULL)
                {           
                    fprintf(pOut, "\"struct%d\";",
                            pChild->_uiNodeId);
                }
            }

            fprintf(pOut, "}\n");
        }
#endif
#endif
        
        fprintf(pOut, "}\n");
        fclose(pOut);
    }
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::dumpDotNode(
    TreeNode                              *pNode, 
    FILE                                  *pOut ,
    std::vector<std::vector<TreeNode *> > &vLevelStore,
    UInt32                                 uiLevel    )
{
#ifdef OSG_DEBUG
    if(pNode == NULL)
        return;

    if(uiLevel == vLevelStore.size())
    {
        vLevelStore.push_back(std::vector<TreeNode *>());
    }

    fprintf(pOut, "struct%d\n", pNode->_uiNodeId);
    fprintf(pOut, "[\n");
    fprintf(pOut, "    label=\"{");

    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "<prev> P|");
    }
    else
    {
        fprintf(pOut, "<prev> P:NIL|");
    }

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT1() != NULL)
        {
            fprintf(pOut, "<l%d> O:%d|", i, i);
        }
        else if(pNode->_vChildren[i].asT2() != NULL)
        {
            fprintf(pOut, "<l%d> C:%d|", i, i);
        }
        else
        {
            fprintf(pOut, "<l%d> NIL|", i);
        }
    }

    if(pNode->_pObject != NULL)
    {
        fprintf(pOut, "<val> VAL:Obj|");
    }
    else
    {
        fprintf(pOut, "<val> VAL:NIL|");
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "<next> N}\"\n");
    }
    else
    {
        fprintf(pOut, "<next> N:NIL}\"\n");
    }

    fprintf(pOut, "]\n");

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        TreeNode *pChild = pNode->_vChildren[i].asT2();

        if(pChild != NULL)
        {
            dumpDotNode(pChild, pOut, vLevelStore, uiLevel + 1);
            
            fprintf(pOut, 
                    "struct%d:l%d -> struct%d:l%d [constraint=\"false\"];\n",
                    pNode ->_uiNodeId, i,
                    pChild->_uiNodeId, i);
        }
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "struct%d:next -> struct%d:prev;\n",
                pNode ->_uiNodeId,
                pNode->_pNext->_uiNodeId);
    }
    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "struct%d:prev -> struct%d:next;\n",
                pNode ->_uiNodeId,
                pNode->_pPrev->_uiNodeId);
    }

     vLevelStore[uiLevel].push_back(pNode);
#endif
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV1<ObjectT, LevelBits>::ShaderCacheTreeV1(void) :
#ifdef OSG_DEBUG
    _uiNodeCount  (0   ),
#endif
    _pRoot        (NULL),
    _vLevelEntries(    ),
    _qFreeElements(    )
{
    _pRoot = allocateNode();

    _vLevelEntries.push_back(_pRoot);
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV1<ObjectT, LevelBits>::~ShaderCacheTreeV1(void)
{
    typename std::deque <TreeNode *>::const_iterator qIt  = 
        _qFreeElements.begin();

    typename std::deque <TreeNode *>::const_iterator qEnd = 
        _qFreeElements.end();
    
    for(; qIt != qEnd; ++qIt)
    {
        delete (*qIt);
    }
}

template<class ObjectT, UInt32 LevelBits> inline
typename ShaderCacheTreeV1<ObjectT, LevelBits>::TreeNode *
    ShaderCacheTreeV1<ObjectT, LevelBits>::allocateNode(void)
{
    TreeNode *returnValue = NULL;

    if(_qFreeElements.empty() == false)
    {
        returnValue = _qFreeElements.back();

        _qFreeElements.pop_back();

        returnValue->clear();
    }
    else
    {
        returnValue = new TreeNode();

#ifdef OSG_DEBUG
        returnValue->_uiNodeId = ++_uiNodeCount;
#endif
    }

#ifdef OSG_DEBUG
    UIntPointer rU = reinterpret_cast<UIntPointer>(returnValue);

    OSG_ASSERT((rU & 0x0001) == 0x0000);
#endif

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::eraseNode(TreeNode *pNode)
{
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT2() != NULL)
        {
            eraseNode(pNode->_vChildren[i].asT2());
        }
        else
        {
            pNode->_vChildren[i].setAsT1(NULL);
        }
    }

    pNode->_pObject = NULL;

    _qFreeElements.push_back(pNode);
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::destroyNode(TreeNode     *pNode,
                                                        ElemDestFunc  destFunc)
{
    if(pNode == NULL)
        return;

    UInt32 uiChildStart = 0;

    if(pNode->_pPrev == NULL)
        uiChildStart = 1;

    for(UInt32 i = uiChildStart; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT2() != NULL)
        {
            destroyNode(pNode->_vChildren[i].asT2(), destFunc);
        }
        else if(pNode->_vChildren[i].asT1() != NULL)
        {
#ifndef OSG_SHC_REF_CLEANUP
            ObjectT *pObj = pNode->_vChildren[i].asT1();
            (destFunc)(pObj);
#endif
            pNode->_vChildren[i].setAsT1(NULL);
        }
    }

    if(pNode->_pObject != NULL)
    {
#ifndef OSG_SHC_REF_CLEANUP
        (destFunc)(pNode->_pObject);
#endif
        pNode->_pObject = NULL;
    }

    delete pNode;
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV1<ObjectT, LevelBits>::destroy(ElemDestFunc destFunc)
{
    destroyNode(_pRoot, destFunc);

    _vLevelEntries[0] = NULL;

    _pRoot = NULL;
}






/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(WIN32) || defined(__APPLE__) || \
    defined(__GXX_EXPERIMENTAL_CXX0X__)
template<class ObjectT, UInt32 LevelBits> 
const Real32 ShaderCacheTreeV2<ObjectT, LevelBits>::LevelFactor = 
                                                            1.f / (LevelBits);
#endif

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV2<ObjectT, LevelBits>::TreeNode::TreeNode(void) :
#ifdef OSG_DEBUG
    _uiNodeId(0   ),
#endif
    _pObject (NULL),
    _pPrev   (NULL),
    _pNext   (NULL)
{
    memset(&(_vJumps[0]), 0, LevelSize * sizeof(UInt16));
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV2<ObjectT, LevelBits>::TreeNode::~TreeNode(void)
{
    _pObject = NULL;
    _pPrev   = NULL;
    _pNext   = NULL;

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        _vChildren[i].setAsT1(NULL);
    }
}
        
template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::TreeNode::clear(void)
{
    _pObject = NULL;
    _pPrev   = NULL;
    _pNext   = NULL;
    
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        _vChildren[i].setAsT1(NULL);
    }

    memset(&(_vJumps[0]), 0, LevelSize * sizeof(UInt16));
}



template<class ObjectT, UInt32 LevelBits> inline
ObjectT *ShaderCacheTreeV2<ObjectT, LevelBits>::find(const IdStore &vIds)
{
    if(vIds.size() < 1)
        return NULL;

    ObjectT *returnValue = NULL;

    IdType uiStartId     = vIds[0] - 1;
    IdType uiStartLevel  = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId      = 0;
    UInt32 uiLastId      = vIds.size();
  

    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }


    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrBits = 0x0000;
    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];
    TreeNode *pNextNode  = NULL;

    if(pCurrNode == NULL)
        return NULL;

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;
        UInt16 uiJumpDist = 1;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
           
            continue;
        }
        else
        {
            pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();

            if(pNextNode == NULL)
            {
                pCurrNode = pNextNode;
                break;
            }

            uiJumpDist = UInt16((uiCurrIdx - 1) * LevelFactor);
            UInt32 uiTargetLevel = uiStartLevel + uiJumpDist;

            if(uiJumpDist < pCurrNode->_vJumps[uiCurrBits])
            {
                pCurrNode = NULL;
                break;
            }

            if(uiJumpDist > pCurrNode->_vJumps[uiCurrBits])
            {
                uiLevelSub += LevelBits * pCurrNode->_vJumps[uiCurrBits];
                uiCurrIdx  -= LevelBits * pCurrNode->_vJumps[uiCurrBits];
                uiJumpDist -= pCurrNode->_vJumps[uiCurrBits];
                
                pCurrNode = pNextNode;
                pNextNode = pCurrNode->_vChildren[0].asT2();
                
                uiCurrBits  = 0x0000;

                while(1)
                {
                    if(uiCurrIdx <= LevelBits)
                    {
                        break;
                    }

                    if(uiJumpDist == pCurrNode->_vJumps[0])
                    {
                        break;
                    }

                    if(uiJumpDist < pCurrNode->_vJumps[0])
                    {
                        pNextNode = NULL;
                        break;
                    }
                    
                    if(pNextNode == NULL)
                    {
                        break;
                    }
                    
                    uiLevelSub += 
                        LevelBits * pCurrNode->_vJumps[0];
                    
                    uiCurrIdx  -= 
                        LevelBits * pCurrNode->_vJumps[0];
                    
                    uiJumpDist -= pCurrNode->_vJumps[0];
                    
                    pCurrNode = pNextNode;
                    pNextNode = pCurrNode->_vChildren[0].asT2();
                }
            }

            pCurrNode = pNextNode;

            if(pCurrNode == NULL)
            {
                break;
            }

            uiCurrBits  = 0x0000;

            uiStartLevel = uiTargetLevel;
            uiLevelSub   = (uiStartLevel * LevelBits);

            uiCurrIdx  -= uiJumpDist * LevelBits;


            uiCurrBits |= IdxToBits[uiCurrIdx]; 
        }
    }

    if(pCurrNode != NULL)
    {
        TreeNode *pNext = pCurrNode->_vChildren[uiCurrBits].asT2();
        
        if(pNext != NULL)
        {
            returnValue = pNext->_pObject;
        }
        else
        {
            returnValue = pCurrNode->_vChildren[uiCurrBits].asT1();
        }
    }

    return returnValue;
}


template<class ObjectT, UInt32 LevelBits> inline
bool ShaderCacheTreeV2<ObjectT, LevelBits>::add(const IdStore &vIds,
                                                      ObjectT *pObject)
{
    bool returnValue = false;

    if(vIds.size() < 1)
        return returnValue;

    IdType uiStartId    = vIds[0] - 1;

    IdType uiStartLevel = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId     = 0;
    UInt32 uiLastId     = vIds.size();

    
    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }

   
    TreeNode *pCurrNode = _vLevelEntries[uiStartLevel];
    TreeNode *pNextNode = NULL;

    UInt32 uiCurrBits = 0x0000;

    if(pCurrNode == NULL)
    {
        UInt32 uiLastValidLE = 0;
        
        for(Int32 i = uiStartLevel; i >= 0; --i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                uiLastValidLE = i;
                break;
            }
        } 

        uiStartLevel = uiLastValidLE;
        pCurrNode    = _vLevelEntries[uiStartLevel];
    }

    UInt32 uiLevelSub   = (uiStartLevel * LevelBits);

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;
        UInt16 uiJumpDist = 1;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
            
            continue;
        }
        else
        {
            pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();

            uiJumpDist           = UInt16((uiCurrIdx - 1) * LevelFactor);
            UInt32 uiTargetLevel = uiStartLevel + uiJumpDist;
           
            if(pNextNode != NULL)
            {
                if(uiJumpDist > pCurrNode->_vJumps[uiCurrBits])
                {
                    uiLevelSub += LevelBits * pCurrNode->_vJumps[uiCurrBits];
                    uiCurrIdx  -= LevelBits * pCurrNode->_vJumps[uiCurrBits];
                    uiJumpDist -= pCurrNode->_vJumps[uiCurrBits];

                    pCurrNode = pNextNode;
                    pNextNode = pCurrNode->_vChildren[0].asT2();

                    uiCurrBits  = 0x0000;

                    while(1)
                    {
                        if(uiCurrIdx <= LevelBits)
                        {
                            break;
                        }

                        if(pNextNode == NULL)
                        {
                            break;
                        }

                        if(uiJumpDist <= pCurrNode->_vJumps[0])
                        {
                            break;
                        }

                        uiLevelSub += 
                            LevelBits * pCurrNode->_vJumps[0];

                        uiCurrIdx  -= 
                            LevelBits * pCurrNode->_vJumps[0];

                        uiJumpDist -= pCurrNode->_vJumps[0];

                        pCurrNode = pNextNode;
                        pNextNode = pCurrNode->_vChildren[0].asT2();
                    }
                }

                if(uiJumpDist < pCurrNode->_vJumps[uiCurrBits])
                {
                    pNextNode = allocateNode();

                    pNextNode->_vJumps[0] = 
                        pCurrNode->_vJumps   [uiCurrBits] - uiJumpDist;

                    pNextNode->_vChildren[0] = 
                        pCurrNode->_vChildren[uiCurrBits].asT2();

                    pNextNode->_pObject = 
                        pCurrNode->_vChildren[uiCurrBits].asT2()->_pObject;

                    pCurrNode->_vChildren[uiCurrBits].asT2()->_pObject = NULL;

                    pCurrNode->_vJumps   [uiCurrBits] = uiJumpDist;
                    pCurrNode->_vChildren[uiCurrBits] = pNextNode;

                    if(_vLevelEntries[uiTargetLevel] == NULL)
                    {
                        UInt32 uiLastValidLE = 0;

                        for(Int32 i = uiTargetLevel; i >= 0; --i)
                        {
                            if(_vLevelEntries[i] != NULL)
                            {
                                uiLastValidLE = i;
                                break;
                            }
                        } 

                        if(_vLevelEntries[uiLastValidLE] == pCurrNode &&
                            uiCurrBits                   == 0          )
                        {
                            _vLevelEntries[uiTargetLevel] = pNextNode;
                        }
                        else
                        {
                            TreeNode *pTmpNode = allocateNode();

                            if(_vLevelEntries[
                                   uiLastValidLE]->_vChildren[0].asT2() != NULL)
                            {
                                pTmpNode->_vChildren[0] = 
                                    _vLevelEntries[
                                        uiLastValidLE]->_vChildren[0].asT2();

                                pTmpNode->_vJumps[0] =
                                    _vLevelEntries[
                                        uiLastValidLE]->_vJumps[0] - 
                                    (uiTargetLevel - uiLastValidLE);
                            }
                            
                            _vLevelEntries[uiLastValidLE]->_vChildren[0] = 
                                pTmpNode;
                            _vLevelEntries[uiLastValidLE]->_vJumps   [0] = 
                                uiTargetLevel - uiLastValidLE;
                            
                            _vLevelEntries[uiTargetLevel] = pTmpNode;
                            
                            pTmpNode ->_pNext = pNextNode;
                            pNextNode->_pPrev = pTmpNode;
                        }
                    }
                    else
                    {
                        pNextNode->_pNext = 
                            _vLevelEntries[uiTargetLevel]->_pNext;

                        if(pNextNode->_pNext != NULL)
                        {
                            pNextNode->_pNext->_pPrev = pNextNode;
                        }

                        _vLevelEntries[uiTargetLevel]->_pNext = pNextNode;
                        
                        pNextNode->_pPrev = _vLevelEntries[uiTargetLevel];
                    }
                }
            }

            if(pNextNode == NULL)
            {
                pNextNode = allocateNode();

                pCurrNode->_vJumps   [uiCurrBits] = uiJumpDist;

                if(pCurrNode->_vChildren[uiCurrBits].asT1() != NULL)
                {
                    pNextNode->_pObject = 
                        pCurrNode->_vChildren[uiCurrBits].asT1();
                }

                pCurrNode->_vChildren[uiCurrBits] = pNextNode;

                if(uiTargetLevel >= _vLevelEntries.size())
                {
                    _vLevelEntries.resize(uiTargetLevel + 1, NULL);

                    UInt32 uiLastValidLE = 0;

                    for(Int32 i = uiTargetLevel; i >= 0; --i)
                    {
                        if(_vLevelEntries[i] != NULL)
                        {
                            uiLastValidLE = i;
                            break;
                        }
                    } 

                    if(_vLevelEntries[uiLastValidLE] == pCurrNode &&
                        uiCurrBits                   == 0          )
                    {
                        _vLevelEntries[uiTargetLevel] = pNextNode;
                    }
                    else
                    {
                        TreeNode *pTmpNode = allocateNode();
                        
                        _vLevelEntries[uiLastValidLE]->_vChildren[0] = pTmpNode;
                        _vLevelEntries[uiLastValidLE]->_vJumps   [0] = 
                            uiTargetLevel - uiLastValidLE;

                        _vLevelEntries[uiTargetLevel] = pTmpNode;
                        
                        pTmpNode ->_pNext = pNextNode;
                        pNextNode->_pPrev = pTmpNode;
                    }
                }
                else
                {
                    if(_vLevelEntries[uiTargetLevel] == NULL)
                    {
                        UInt32 uiLastValidLE = 0;

                        for(Int32 i = uiTargetLevel; i >= 0; --i)
                        {
                            if(_vLevelEntries[i] != NULL)
                            {
                                uiLastValidLE = i;
                                break;
                            }
                        } 

                        TreeNode *pTmpNode = allocateNode();

                        if(_vLevelEntries[
                               uiLastValidLE]->_vChildren[0].asT2() != NULL)
                        {
                            pTmpNode->_vChildren[0] = 
                                _vLevelEntries[
                                    uiLastValidLE]->_vChildren[0].asT2();

                            pTmpNode->_vJumps[0] =
                                _vLevelEntries[uiLastValidLE]->_vJumps[0] - 
                                (uiTargetLevel - uiLastValidLE);
                        }

                        _vLevelEntries[uiLastValidLE]->_vChildren[0] = pTmpNode;
                        _vLevelEntries[uiLastValidLE]->_vJumps   [0] = 
                            uiTargetLevel - uiLastValidLE;

                        _vLevelEntries[uiTargetLevel] = pTmpNode;
                        
                        pTmpNode ->_pNext = pNextNode;
                        pNextNode->_pPrev = pTmpNode;
                    }
                    else
                    {
                        pNextNode->_pNext = 
                            _vLevelEntries[uiTargetLevel]->_pNext;

                        if(pNextNode->_pNext != NULL)
                        {
                            pNextNode->_pNext->_pPrev = pNextNode;
                        }

                        _vLevelEntries[uiTargetLevel]->_pNext = pNextNode;
                        
                        pNextNode->_pPrev = _vLevelEntries[uiTargetLevel];
                    }
                }
            }


            pCurrNode   = pNextNode;
            
            uiCurrBits  = 0x0000;

            uiStartLevel = uiTargetLevel;
            uiLevelSub   = (uiStartLevel * LevelBits);

            uiCurrIdx  -= uiJumpDist * LevelBits;

            uiCurrBits |= IdxToBits[uiCurrIdx]; 
        }
    }
    
    if(pCurrNode != NULL)
    {
        pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();
        
        if(pNextNode != NULL)
        {
            if(pNextNode->_pObject == NULL)
            {
                pNextNode->_pObject = pObject;
                
                returnValue = true;
            }
            else
            {
                OSG_ASSERT(pNextNode->_pObject == pObject);
            }
        }
        else
        {
            pCurrNode->_vChildren[uiCurrBits] = pObject;
                
            returnValue = true;
        }
    }

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::sub(UInt32 uiIdx)
{
    IdType uiStartLevel  = IdType((uiIdx - 1) * LevelFactor);

    if(uiStartLevel >= _vLevelEntries.size())
    {
        return;
    }

    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrIdx  = uiIdx - uiLevelSub;
    UInt32    uiCurrBits = IdxToBits[uiCurrIdx];

    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

    for(; pCurrNode != NULL; pCurrNode = pCurrNode->_pNext)
    {
        for(UInt32 i = 0; i < LevelSize; ++i)
        {
            TreeNode *pChild = pCurrNode->_vChildren[i].asT2();

            if(0x0000 != (i & uiCurrBits) && pChild != NULL)
            {
                if(pChild->_pNext == NULL)
                {
                    pChild->_pPrev->_pNext = NULL;
                }
                else
                {
                    pChild->_pPrev->_pNext = pChild->_pNext;
                    pChild->_pNext->_pPrev = pChild->_pPrev;
                }
                
                pChild->_pPrev = NULL;
                pChild->_pNext = NULL;

                eraseNode(pCurrNode->_vChildren[i].asT2());
                pCurrNode->_vJumps   [i] = 0;
                pCurrNode->_vChildren[i].setAsT2(NULL);
            }
            else if(pCurrNode->_vChildren[i].asT1() != NULL)
            {
                pCurrNode->_vChildren[i].setAsT1(NULL);
                pCurrNode->_vJumps   [i] = 0;
            }
        }
    }
}

#define OSG_DUMP_LEVELENTRIES

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::dumpDot(const Char8 *szFilename)
{
    FILE *pOut = fopen(szFilename, "w");

    if(pOut != NULL)
    {
        fprintf(pOut, "digraph structs\n");
        fprintf(pOut, "{\n");
        fprintf(pOut, "rankdir = LR;\n");
        fprintf(pOut, "splines=false\n");

        fprintf(pOut, "node [shape=record];\n");

        fprintf(pOut, "struct%d\n", 0);
        fprintf(pOut, "[\n");
        fprintf(pOut, "    label=\"");

        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, "<l%d> %d", i, i);
            }
            else
            {
                fprintf(pOut, "<l%d> NIL", i);
            }
            
            if(i == _vLevelEntries.size() - 1)
            {
                fprintf(pOut, "\"\n");
            }
            else
            {
                fprintf(pOut, "|");
            }
        }
        
        fprintf(pOut, "]\n");

        fprintf(pOut, "node [width = 1.5];\n");

        std::vector<std::vector<TreeNode *> > vLevelStore;

        dumpDotNode(_pRoot, pOut, vLevelStore, 0);

#ifdef OSG_DEBUG
#ifdef OSG_DUMP_LEVELENTRIES
        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, 
                        "struct%d:l%d -> struct%d:prev [color=\"green\"];\n",
                        0, i,
                        _vLevelEntries[i]->_uiNodeId);
            }
        }
#endif

#if 0
        for(UInt32 i = 0; i < vLevelStore.size(); ++i)
        {
            fprintf(pOut, "{ rank=same;");

            for(UInt32 j = 0; j < vLevelStore[i].size(); ++j)
            {
                TreeNode *pChild = vLevelStore[i][j];

                if(pChild != NULL)
                {           
                    fprintf(pOut, "\"struct%d\";",
                            pChild->_uiNodeId);
                }
            }

            fprintf(pOut, "}\n");
        }
#endif
#endif
        
        fprintf(pOut, "}\n");
        fclose(pOut);
    }
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::dumpDotNode(
    TreeNode                              *pNode, 
    FILE                                  *pOut ,
    std::vector<std::vector<TreeNode *> > &vLevelStore,
    UInt32                                 uiLevel    )
{
#ifdef OSG_DEBUG
    if(pNode == NULL)
        return;

    if(uiLevel == vLevelStore.size())
    {
        vLevelStore.push_back(std::vector<TreeNode *>());
    }

    fprintf(pOut, "struct%d\n", pNode->_uiNodeId);
    fprintf(pOut, "[\n");
    fprintf(pOut, "    label=\"{");

    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "<prev> P|");
    }
    else
    {
        fprintf(pOut, "<prev> P:NIL|");
    }

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT1() != NULL)
        {
            if(osgIsPower2(i) == true)
            {
                fprintf(pOut, "<l%d> _O:%d|", i, i);
            }
            else
            {
                fprintf(pOut, "<l%d> O:%d|", i, i);
            }
        }
        else if(pNode->_vChildren[i].asT2() != NULL)
        {
            if(osgIsPower2(i) == true)
            {
                fprintf(pOut, "<l%d> _C:%d (%d)|", i, i, pNode->_vJumps[i]);
            }
            else
            {
                fprintf(pOut, "<l%d> C:%d (%d)|", i, i, pNode->_vJumps[i]);
            }
        }
        else
        {
            if(osgIsPower2(i) == true)
            {
                fprintf(pOut, "<l%d> _NIL|", i);
            }
            else
            {
                fprintf(pOut, "<l%d> NIL|", i);
            }
        }
    }

    if(pNode->_pObject != NULL)
    {
        fprintf(pOut, "<val> VAL:Obj|");
    }
    else
    {
        fprintf(pOut, "<val> VAL:NIL|");
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "<next> N}\"\n");
    }
    else
    {
        fprintf(pOut, "<next> N:NIL}\"\n");
    }

    fprintf(pOut, "]\n");

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        TreeNode *pChild = pNode->_vChildren[i].asT2();

        if(pChild != NULL)
        {
            dumpDotNode(pChild, pOut, vLevelStore, uiLevel + 1);
            
            fprintf(pOut, 
                    "struct%d:l%d -> struct%d:l%d [constraint=\"false\"];\n",
                    pNode ->_uiNodeId, i,
                    pChild->_uiNodeId, i);
        }
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "struct%d:next -> struct%d:prev;\n",
                pNode ->_uiNodeId,
                pNode->_pNext->_uiNodeId);
    }
    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "struct%d:prev -> struct%d:next;\n",
                pNode ->_uiNodeId,
                pNode->_pPrev->_uiNodeId);
    }

     vLevelStore[uiLevel].push_back(pNode);
#endif
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV2<ObjectT, LevelBits>::ShaderCacheTreeV2(void) :
#ifdef OSG_DEBUG
    _uiNodeCount  (0   ),
#endif
    _pRoot        (NULL),
    _vLevelEntries(    ),
    _qFreeElements(    )
{
    _pRoot = allocateNode();

    _vLevelEntries.push_back(_pRoot);
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV2<ObjectT, LevelBits>::~ShaderCacheTreeV2(void)
{
    typename std::deque <TreeNode *>::iterator qIt  = 
        _qFreeElements.begin();

    typename std::deque <TreeNode *>::const_iterator qEnd = 
        _qFreeElements.end();
    
    for(; qIt != qEnd; ++qIt)
    {
        delete (*qIt);

        *qIt = NULL;
    }

    typename std::vector<TreeNode *>::iterator vIt  = _vLevelEntries.begin();
    typename std::vector<TreeNode *>::iterator vEnd = _vLevelEntries.end  ();
    
    for(; vIt != vEnd; ++vIt)
    {
        delete (*vIt);

        *vIt = NULL;
    }
}

template<class ObjectT, UInt32 LevelBits> inline
typename ShaderCacheTreeV2<ObjectT, LevelBits>::TreeNode *
    ShaderCacheTreeV2<ObjectT, LevelBits>::allocateNode(void)
{
    TreeNode *returnValue = NULL;

    if(_qFreeElements.empty() == false)
    {
        returnValue = _qFreeElements.back();

        _qFreeElements.pop_back();

        returnValue->clear();
    }
    else
    {
        returnValue = new TreeNode();

#ifdef OSG_DEBUG
        returnValue->_uiNodeId = ++_uiNodeCount;
#endif
    }

#ifdef OSG_DEBUG
    UIntPointer rU = reinterpret_cast<UIntPointer>(returnValue);

    OSG_ASSERT((rU & 0x0001) == 0x0000);
#endif

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::eraseNode(TreeNode *pNode)
{
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT2() != NULL)
        {
            eraseNode(pNode->_vChildren[i].asT2());

            pNode->_vChildren[i].setAsT2(NULL);
        }
        else
        {
            pNode->_vChildren[i].setAsT1(NULL);
        }
    }

    pNode->_pObject = NULL;

    _qFreeElements.push_back(pNode);
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::destroyNode(TreeNode     *pNode,
                                                        ElemDestFunc  destFunc)
{
    if(pNode == NULL)
        return;

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT2() != NULL)
        {
            destroyNode(pNode->_vChildren[i].asT2(), destFunc);
        }
        else if(pNode->_vChildren[i].asT1() != NULL)
        {
#ifndef OSG_SHC_REF_CLEANUP
            ObjectT *pObj = pNode->_vChildren[i].asT1();
            (destFunc)(pObj);
#endif
            pNode->_vChildren[i].setAsT1(NULL);
        }
    }

    if(pNode->_pObject != NULL)
    {
#ifndef OSG_SHC_REF_CLEANUP
        (destFunc)(pNode->_pObject);
#endif
        pNode->_pObject = NULL;
    }

    delete pNode;
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV2<ObjectT, LevelBits>::destroy(ElemDestFunc destFunc)
{
    destroyNode(_pRoot, destFunc);

    _vLevelEntries[0] = NULL;

    _pRoot = NULL;
}






/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(WIN32) || defined(__APPLE__) || \
    defined(__GXX_EXPERIMENTAL_CXX0X__)
template<class ObjectT, UInt32 LevelBits> 
const Real32 ShaderCacheTreeV3<ObjectT, LevelBits>::LevelFactor = 
                                                            1.f / (LevelBits);
#endif

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV3<ObjectT, LevelBits>::TreeNode::TreeNode(void) :
#ifdef OSG_DEBUG
    _uiNodeId(0   ),
#endif
    _pObject (NULL),
    _pPrev   (NULL),
    _pNext   (NULL)
{
    memset(&(_vJumps[0]), 0, LevelSize * sizeof(UInt16));
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV3<ObjectT, LevelBits>::TreeNode::~TreeNode(void)
{
    _pObject = NULL;
    _pPrev   = NULL;
    _pNext   = NULL;

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        _vChildren[i].setAsT1(NULL);
    }
}
        
template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV3<ObjectT, LevelBits>::TreeNode::clear(void)
{
    _pObject = NULL;
    _pPrev   = NULL;
    _pNext   = NULL;
    
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        _vChildren[i].setAsT1(NULL);
    }

    memset(&(_vJumps[0]), 0, LevelSize * sizeof(UInt16));
}



template<class ObjectT, UInt32 LevelBits> inline
ObjectT *ShaderCacheTreeV3<ObjectT, LevelBits>::find(const IdStore &vIds)
{
    if(vIds.size() < 1 || _pRoot == NULL)
        return NULL;

    ObjectT *returnValue = NULL;

    IdType uiStartId     = vIds[0] - 1;
    IdType uiStartLevel  = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId      = 0;
    UInt32 uiLastId      = UInt32(vIds.size());
  

    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = IdType(_vLevelEntries.size() - 1);
    }


    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrBits = 0x0000;
    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];
    TreeNode *pNextNode  = NULL;

    if(pCurrNode == NULL)
        return NULL;

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;
        UInt16 uiJumpDist = 1;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
           
            continue;
        }
        else
        {
            pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();

            if(pNextNode == NULL)
            {
                pCurrNode = pNextNode;
                break;
            }

            uiJumpDist = UInt16((uiCurrIdx - 1) * LevelFactor);
            UInt32 uiTargetLevel = uiStartLevel + uiJumpDist;

            if(uiJumpDist < pCurrNode->_vJumps[uiCurrBits])
            {
                pCurrNode = NULL;
                break;
            }

            if(uiJumpDist > pCurrNode->_vJumps[uiCurrBits])
            {
                uiLevelSub += LevelBits * pCurrNode->_vJumps[uiCurrBits];
                uiCurrIdx  -= LevelBits * pCurrNode->_vJumps[uiCurrBits];
                uiJumpDist -= pCurrNode->_vJumps[uiCurrBits];
                
                pCurrNode = pNextNode;
                pNextNode = pCurrNode->_vChildren[0].asT2();
                
                uiCurrBits  = 0x0000;

                while(1)
                {
                    if(uiCurrIdx <= LevelBits)
                    {
                        break;
                    }

                    if(uiJumpDist == pCurrNode->_vJumps[0])
                    {
                        break;
                    }

                    if(uiJumpDist < pCurrNode->_vJumps[0])
                    {
                        pNextNode = NULL;
                        break;
                    }
                    
                    if(pNextNode == NULL)
                    {
                        break;
                    }
                    
                    uiLevelSub += 
                        LevelBits * pCurrNode->_vJumps[0];
                    
                    uiCurrIdx  -= 
                        LevelBits * pCurrNode->_vJumps[0];
                    
                    uiJumpDist -= pCurrNode->_vJumps[0];
                    
                    pCurrNode = pNextNode;
                    pNextNode = pCurrNode->_vChildren[0].asT2();
                }
            }

            pCurrNode = pNextNode;

            if(pCurrNode == NULL)
            {
                break;
            }

            uiCurrBits  = 0x0000;

            uiStartLevel = uiTargetLevel;
            uiLevelSub   = (uiStartLevel * LevelBits);

            uiCurrIdx  -= uiJumpDist * LevelBits;


            uiCurrBits |= IdxToBits[uiCurrIdx]; 
        }
    }

    if(pCurrNode != NULL)
    {
        TreeNode *pNext = pCurrNode->_vChildren[uiCurrBits].asT2();
        
        if(pNext != NULL)
        {
            returnValue = pNext->_pObject;
        }
        else
        {
            returnValue = pCurrNode->_vChildren[uiCurrBits].asT1();
        }
    }

    return returnValue;
}


template<class ObjectT, UInt32 LevelBits> inline
bool ShaderCacheTreeV3<ObjectT, LevelBits>::add(const IdStore &vIds,
                                                      ObjectT *pObject)
{
    bool returnValue = false;

    if(vIds.size() < 1)
        return returnValue;

    IdType uiStartId    = vIds[0] - 1;

    IdType uiStartLevel = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId     = 0;
    UInt32 uiLastId     = UInt32(vIds.size());

#ifdef OSG_DEBUG    
    FDEBUG(("scv3::add : "));
    for(UInt32 i = 0; i < uiLastId; ++i)
    {
        FDEBUG(("%d ", vIds[i]));
    }
    FDEBUG(("\n"));
#endif

    if(_pRoot == NULL)
    {
        _pRoot = allocateNode();

        OSG_ASSERT(_vLevelEntries.size() == 0);

        _vLevelEntries.push_back(_pRoot);
    }

    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = IdType(_vLevelEntries.size() - 1);
    }

   
    TreeNode *pCurrNode = _vLevelEntries[uiStartLevel];
    TreeNode *pNextNode = NULL;

    UInt32 uiCurrBits = 0x0000;

    if(pCurrNode == NULL)
    {
        UInt32 uiLastValidLE = 0;
        
        for(Int32 i = uiStartLevel; i >= 0; --i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                uiLastValidLE = i;
                break;
            }
        } 

        uiStartLevel = uiLastValidLE;
        pCurrNode    = _vLevelEntries[uiStartLevel];
    }

    UInt32 uiLevelSub   = (uiStartLevel * LevelBits);

    for(; uiCurrId < uiLastId; ++uiCurrId)
    {
        UInt32 uiCurrIdx  = vIds[uiCurrId] - uiLevelSub;
        UInt16 uiJumpDist = 1;

        if(uiCurrIdx <= LevelBits)
        {
            uiCurrBits |= IdxToBits[uiCurrIdx]; 
            
            continue;
        }
        else
        {
            pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();

            uiJumpDist           = UInt16((uiCurrIdx - 1) * LevelFactor);
            UInt32 uiTargetLevel = uiStartLevel + uiJumpDist;
           
            if(pNextNode != NULL)
            {
                if(uiJumpDist > pCurrNode->_vJumps[uiCurrBits])
                {
                    uiLevelSub += LevelBits * pCurrNode->_vJumps[uiCurrBits];
                    uiCurrIdx  -= LevelBits * pCurrNode->_vJumps[uiCurrBits];
                    uiJumpDist -= pCurrNode->_vJumps[uiCurrBits];

                    pCurrNode = pNextNode;
                    pNextNode = pCurrNode->_vChildren[0].asT2();

                    uiCurrBits  = 0x0000;

                    while(1)
                    {
                        if(uiCurrIdx <= LevelBits)
                        {
                            break;
                        }

                        if(pNextNode == NULL)
                        {
                            break;
                        }

                        if(uiJumpDist <= pCurrNode->_vJumps[0])
                        {
                            break;
                        }

                        uiLevelSub += 
                            LevelBits * pCurrNode->_vJumps[0];

                        uiCurrIdx  -= 
                            LevelBits * pCurrNode->_vJumps[0];

                        uiJumpDist -= pCurrNode->_vJumps[0];

                        pCurrNode = pNextNode;
                        pNextNode = pCurrNode->_vChildren[0].asT2();
                    }
                }

                if(uiJumpDist < pCurrNode->_vJumps[uiCurrBits])
                {
                    pNextNode = allocateNode();

                    pNextNode->_vJumps[0] = 
                        pCurrNode->_vJumps   [uiCurrBits] - uiJumpDist;

                    pNextNode->_vChildren[0] = 
                        pCurrNode->_vChildren[uiCurrBits].asT2();

                    pNextNode->_pObject = 
                        pCurrNode->_vChildren[uiCurrBits].asT2()->_pObject;

                    pCurrNode->_vChildren[uiCurrBits].asT2()->_pObject = NULL;

                    pCurrNode->_vJumps   [uiCurrBits] = uiJumpDist;
                    pCurrNode->_vChildren[uiCurrBits] = pNextNode;

                    if(_vLevelEntries[uiTargetLevel] == NULL)
                    {
                        UInt32 uiLastValidLE = 0;

                        for(Int32 i = uiTargetLevel; i >= 0; --i)
                        {
                            if(_vLevelEntries[i] != NULL)
                            {
                                uiLastValidLE = i;
                                break;
                            }
                        } 

                        if(_vLevelEntries[uiLastValidLE] == pCurrNode &&
                            uiCurrBits                   == 0          )
                        {
                            _vLevelEntries[uiTargetLevel] = pNextNode;
                        }
                        else
                        {
                            TreeNode *pTmpNode = allocateNode();

                            if(_vLevelEntries[
                                   uiLastValidLE]->_vChildren[0].asT2() != NULL)
                            {
                                pTmpNode->_vChildren[0] = 
                                    _vLevelEntries[
                                        uiLastValidLE]->_vChildren[0].asT2();

                                pTmpNode->_vJumps[0] =
                                    _vLevelEntries[
                                        uiLastValidLE]->_vJumps[0] - 
                                    (uiTargetLevel - uiLastValidLE);
                            }
                            
                            _vLevelEntries[uiLastValidLE]->_vChildren[0] = 
                                pTmpNode;
                            _vLevelEntries[uiLastValidLE]->_vJumps   [0] = 
                                uiTargetLevel - uiLastValidLE;
                            
                            _vLevelEntries[uiTargetLevel] = pTmpNode;
                            
                            pTmpNode ->_pNext = pNextNode;
                            pNextNode->_pPrev = pTmpNode;
                        }
                    }
                    else
                    {
                        pNextNode->_pNext = 
                            _vLevelEntries[uiTargetLevel]->_pNext;

                        if(pNextNode->_pNext != NULL)
                        {
                            pNextNode->_pNext->_pPrev = pNextNode;
                        }

                        _vLevelEntries[uiTargetLevel]->_pNext = pNextNode;
                        
                        pNextNode->_pPrev = _vLevelEntries[uiTargetLevel];
                    }
                }
            }

            if(pNextNode == NULL)
            {
                pNextNode = allocateNode();

                pCurrNode->_vJumps   [uiCurrBits] = uiJumpDist;

                if(pCurrNode->_vChildren[uiCurrBits].asT1() != NULL)
                {
                    pNextNode->_pObject = 
                        pCurrNode->_vChildren[uiCurrBits].asT1();
                }

                pCurrNode->_vChildren[uiCurrBits] = pNextNode;

                if(uiTargetLevel >= _vLevelEntries.size())
                {
                    _vLevelEntries.resize(uiTargetLevel + 1, NULL);

                    UInt32 uiLastValidLE = 0;

                    for(Int32 i = uiTargetLevel; i >= 0; --i)
                    {
                        if(_vLevelEntries[i] != NULL)
                        {
                            uiLastValidLE = i;
                            break;
                        }
                    } 

                    if(_vLevelEntries[uiLastValidLE] == pCurrNode &&
                        uiCurrBits                   == 0          )
                    {
                        _vLevelEntries[uiTargetLevel] = pNextNode;
                    }
                    else
                    {
                        TreeNode *pTmpNode = allocateNode();
                        
                        _vLevelEntries[uiLastValidLE]->_vChildren[0] = pTmpNode;
                        _vLevelEntries[uiLastValidLE]->_vJumps   [0] = 
                            uiTargetLevel - uiLastValidLE;

                        _vLevelEntries[uiTargetLevel] = pTmpNode;
                        
                        pTmpNode ->_pNext = pNextNode;
                        pNextNode->_pPrev = pTmpNode;
                    }
                }
                else
                {
                    if(_vLevelEntries[uiTargetLevel] == NULL)
                    {
                        UInt32 uiLastValidLE = 0;

                        for(Int32 i = uiTargetLevel; i >= 0; --i)
                        {
                            if(_vLevelEntries[i] != NULL)
                            {
                                uiLastValidLE = i;
                                break;
                            }
                        } 

                        TreeNode *pTmpNode = allocateNode();

                        if(_vLevelEntries[
                               uiLastValidLE]->_vChildren[0].asT2() != NULL)
                        {
                            pTmpNode->_vChildren[0] = 
                                _vLevelEntries[
                                    uiLastValidLE]->_vChildren[0].asT2();

                            pTmpNode->_vJumps[0] =
                                _vLevelEntries[uiLastValidLE]->_vJumps[0] - 
                                (uiTargetLevel - uiLastValidLE);

                        }

                        _vLevelEntries[uiLastValidLE]->_vChildren[0] = pTmpNode;
                        _vLevelEntries[uiLastValidLE]->_vJumps   [0] = 
                            uiTargetLevel - uiLastValidLE;

                        _vLevelEntries[uiTargetLevel] = pTmpNode;
                        
                        pTmpNode ->_pNext = pNextNode;
                        pNextNode->_pPrev = pTmpNode;
                    }
                    else
                    {
                        pNextNode->_pNext = 
                            _vLevelEntries[uiTargetLevel]->_pNext;

                        if(pNextNode->_pNext != NULL)
                        {
                            pNextNode->_pNext->_pPrev = pNextNode;
                        }

                        _vLevelEntries[uiTargetLevel]->_pNext = pNextNode;
                        
                        pNextNode->_pPrev = _vLevelEntries[uiTargetLevel];
                    }
                }
            }


            pCurrNode   = pNextNode;
            
            uiCurrBits  = 0x0000;

            uiStartLevel = uiTargetLevel;
            uiLevelSub   = (uiStartLevel * LevelBits);

            uiCurrIdx  -= uiJumpDist * LevelBits;

            uiCurrBits |= IdxToBits[uiCurrIdx]; 
        }
    }
    
    if(pCurrNode != NULL)
    {
        pNextNode = pCurrNode->_vChildren[uiCurrBits].asT2();
        
        if(pNextNode != NULL)
        {
            if(pNextNode->_pObject == NULL)
            {
                pNextNode->_pObject = pObject;
                
                returnValue = true;
            }
            else
            {
                OSG_ASSERT(pNextNode->_pObject == pObject);
            }
        }
        else
        {
            pCurrNode->_vChildren[uiCurrBits] = pObject;
                
            returnValue = true;
        }
    }

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV3<ObjectT, LevelBits>::sub(UInt32 uiIdx)
{
#ifdef OSG_DEBUG    
    FDEBUG(("scv3::sub : %d\n", uiIdx));
#endif

    IdType uiStartLevel  = IdType((uiIdx - 1) * LevelFactor);

    if(uiStartLevel >= _vLevelEntries.size())
    {
        return;
    }

    UInt32    uiLevelSub = (uiStartLevel * LevelBits);
    UInt32    uiCurrIdx  = uiIdx - uiLevelSub;
    UInt32    uiCurrBits = IdxToBits[uiCurrIdx];

    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

    for(; pCurrNode != NULL; pCurrNode = pCurrNode->_pNext)
    {
        for(UInt32 i = 0; i < LevelSize; ++i)
        {
            if(0x0000 != (i & uiCurrBits))
            {
                TreeNode *pChild = pCurrNode->_vChildren[i].asT2();

                if(pChild != NULL)
                {
                    if(pChild->_pNext == NULL)
                    {
                        pChild->_pPrev->_pNext = NULL;
                    }
                    else
                    {
                        pChild->_pPrev->_pNext = pChild->_pNext;
                        pChild->_pNext->_pPrev = pChild->_pPrev;
                    }
                    
                    pChild->_pPrev = NULL;
                    pChild->_pNext = NULL;

                    eraseNode(pCurrNode->_vChildren[i].asT2());
                    pCurrNode->_vJumps   [i] = 0;
                    pCurrNode->_vChildren[i].setAsT2(NULL);
                }
                else if(pCurrNode->_vChildren[i].asT1() != NULL)
                {
                    pCurrNode->_vChildren[i].setAsT1(NULL);
                    pCurrNode->_vJumps   [i] = 0;
                }
            }
        }
    }
}

#define OSG_DUMP_LEVELENTRIES

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV3<ObjectT, 
                       LevelBits>::dumpDot(const Char8 *szFilename, 
                                                 bool   dumpEmptyLevelEntries)
{
    FILE *pOut = fopen(szFilename, "w");

    if(pOut != NULL)
    {
        fprintf(pOut, "digraph structs\n");
        fprintf(pOut, "{\n");
        fprintf(pOut, "rankdir = LR;\n");
        fprintf(pOut, "splines=false\n");

        fprintf(pOut, "node [shape=record];\n");

        fprintf(pOut, "struct%d\n", 0);
        fprintf(pOut, "[\n");
        fprintf(pOut, "    label=\"");

        if(_vLevelEntries.empty())
            fprintf(pOut, "\"\n");

        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, "<l%d> %d", i, i);
            }
            else
            {
                if(dumpEmptyLevelEntries == true)
                    fprintf(pOut, "<l%d> NIL", i);
            }
            
            if(i == _vLevelEntries.size() - 1)
            {
                fprintf(pOut, "\"\n");
            }
            else
            {
                if(_vLevelEntries[i] != NULL || dumpEmptyLevelEntries == true)
                    fprintf(pOut, "|");
            }
        }
        
        fprintf(pOut, "]\n");

        fprintf(pOut, "node [width = 1.5];\n");

        std::vector<std::vector<TreeNode *> > vLevelStore;

        dumpDotNode(_pRoot, pOut, vLevelStore, 0);

#ifdef OSG_DEBUG
#ifdef OSG_DUMP_LEVELENTRIES
        for(UInt32 i = 0; i < _vLevelEntries.size(); ++i)
        {
            if(_vLevelEntries[i] != NULL)
            {
                fprintf(pOut, 
                        "struct%d:l%d -> struct%d:prev [color=\"green\"];\n",
                        0, i,
                        _vLevelEntries[i]->_uiNodeId);
            }
        }
#endif

#if 0
        for(UInt32 i = 0; i < vLevelStore.size(); ++i)
        {
            fprintf(pOut, "{ rank=same;");

            for(UInt32 j = 0; j < vLevelStore[i].size(); ++j)
            {
                TreeNode *pChild = vLevelStore[i][j];

                if(pChild != NULL)
                {           
                    fprintf(pOut, "\"struct%d\";",
                            pChild->_uiNodeId);
                }
            }

            fprintf(pOut, "}\n");
        }
#endif
#endif
        
        fprintf(pOut, "}\n");
        fclose(pOut);
    }
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV3<ObjectT, LevelBits>::dumpDotNode(
    TreeNode                              *pNode, 
    FILE                                  *pOut ,
    std::vector<std::vector<TreeNode *> > &vLevelStore,
    UInt32                                 uiLevel    )
{
#ifdef OSG_DEBUG
    if(pNode == NULL)
        return;

    if(uiLevel == vLevelStore.size())
    {
        vLevelStore.push_back(std::vector<TreeNode *>());
    }

    fprintf(pOut, "struct%d\n", pNode->_uiNodeId);
    fprintf(pOut, "[\n");
    fprintf(pOut, "    label=\"{");

    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "<prev> P|");
    }
    else
    {
        fprintf(pOut, "<prev> P:NIL|");
    }

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT1() != NULL)
        {
            if(osgIsPower2(i) == true)
            {
                fprintf(pOut, "<l%d> _O:%d|", i, i);
            }
            else
            {
                fprintf(pOut, "<l%d> O:%d|", i, i);
            }
        }
        else if(pNode->_vChildren[i].asT2() != NULL)
        {
            if(osgIsPower2(i) == true)
            {
                fprintf(pOut, "<l%d> _C:%d (%d)|", i, i, pNode->_vJumps[i]);
            }
            else
            {
                fprintf(pOut, "<l%d> C:%d (%d)|", i, i, pNode->_vJumps[i]);
            }
        }
        else
        {
            if(osgIsPower2(i) == true)
            {
                fprintf(pOut, "<l%d> _NIL|", i);
            }
            else
            {
                fprintf(pOut, "<l%d> NIL|", i);
            }
        }
    }

    if(pNode->_pObject != NULL)
    {
        fprintf(pOut, "<val> VAL:Obj|");
    }
    else
    {
        fprintf(pOut, "<val> VAL:NIL|");
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "<next> N}\"\n");
    }
    else
    {
        fprintf(pOut, "<next> N:NIL}\"\n");
    }

    fprintf(pOut, "]\n");

    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        TreeNode *pChild = pNode->_vChildren[i].asT2();

        if(pChild != NULL)
        {
            dumpDotNode(pChild, pOut, vLevelStore, uiLevel + 1);
            
            fprintf(pOut, 
                    "struct%d:l%d -> struct%d:l%d [constraint=\"false\"];\n",
                    pNode ->_uiNodeId, i,
                    pChild->_uiNodeId, i);
        }
    }

    if(pNode->_pNext != NULL)
    {
        fprintf(pOut, "struct%d:next -> struct%d:prev;\n",
                pNode ->_uiNodeId,
                pNode->_pNext->_uiNodeId);
    }
    if(pNode->_pPrev != NULL)
    {
        fprintf(pOut, "struct%d:prev -> struct%d:next;\n",
                pNode ->_uiNodeId,
                pNode->_pPrev->_uiNodeId);
    }

     vLevelStore[uiLevel].push_back(pNode);
#endif
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV3<ObjectT, LevelBits>::ShaderCacheTreeV3(void) :
#ifdef OSG_DEBUG
    _uiNodeCount  (0   ),
#endif
    _pRoot        (NULL),
    _vLevelEntries(    ),
    _qFreeElements(    )
{
    _pRoot = allocateNode();

    _vLevelEntries.push_back(_pRoot);
}

template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTreeV3<ObjectT, LevelBits>::~ShaderCacheTreeV3(void)
{
    typename std::deque <TreeNode *>::iterator qIt  = 
        _qFreeElements.begin();

    typename std::deque <TreeNode *>::const_iterator qEnd = 
        _qFreeElements.end();
    
    for(; qIt != qEnd; ++qIt)
    {
        delete (*qIt);

        *qIt = NULL;
    }

    typename std::vector<TreeNode *>::iterator vIt  = _vLevelEntries.begin();
    typename std::vector<TreeNode *>::iterator vEnd = _vLevelEntries.end  ();
    
    for(; vIt != vEnd; ++vIt)
    {
        delete (*vIt);

        *vIt = NULL;
    }
}

template<class ObjectT, UInt32 LevelBits> inline
typename ShaderCacheTreeV3<ObjectT, LevelBits>::TreeNode *
    ShaderCacheTreeV3<ObjectT, LevelBits>::allocateNode(void)
{
    TreeNode *returnValue = NULL;

    if(_qFreeElements.empty() == false)
    {
        returnValue = _qFreeElements.back();

        _qFreeElements.pop_back();

        returnValue->clear();
    }
    else
    {
        returnValue = new TreeNode();

#ifdef OSG_DEBUG
        returnValue->_uiNodeId = ++_uiNodeCount;
#endif
    }

#ifdef OSG_DEBUG
    UIntPointer rU = reinterpret_cast<UIntPointer>(returnValue);

    OSG_ASSERT((rU & 0x0001) == 0x0000);
#endif

    return returnValue;
}

template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTreeV3<ObjectT, LevelBits>::eraseNode(TreeNode *pNode)
{
    for(UInt32 i = 0; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT2() != NULL)
        {
            eraseNode(pNode->_vChildren[i].asT2());

            pNode->_vChildren[i].setAsT2(NULL);
        }
        else
        {
            pNode->_vChildren[i].setAsT1(NULL);
        }
    }

    pNode->_pObject = NULL;

    _qFreeElements.push_back(pNode);
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV3<ObjectT, LevelBits>::destroyNode(TreeNode     *pNode,
                                                        ElemDestFunc  destFunc)
{
    if(pNode == NULL)
        return;

    UInt32 uiChildStart = 0;

    for(UInt32 i = uiChildStart; i < LevelSize; ++i)
    {
        if(pNode->_vChildren[i].asT2() != NULL)
        {
            destroyNode(pNode->_vChildren[i].asT2(), destFunc);
        }
        else if(pNode->_vChildren[i].asT1() != NULL)
        {
#ifndef OSG_SHC_REF_CLEANUP
            ObjectT *pObj = pNode->_vChildren[i].asT1();
            (destFunc)(pObj);
#endif
            pNode->_vChildren[i].setAsT1(NULL);
        }
    }

    if(pNode->_pObject != NULL)
    {
#ifndef OSG_SHC_REF_CLEANUP
        (destFunc)(pNode->_pObject);
#endif
        pNode->_pObject = NULL;
    }

    delete pNode;
}

template<class ObjectT, UInt32 LevelBits> 
template <typename ElemDestFunc> inline
void ShaderCacheTreeV3<ObjectT, LevelBits>::destroy(ElemDestFunc destFunc)
{
    destroyNode(_pRoot, destFunc);

    TreeNodeVecIt      leIt  = _vLevelEntries.begin();
    TreeNodeVecConstIt leEnd = _vLevelEntries.end  ();
    
    for(; leIt != leEnd; ++leIt)
    {
        *leIt = NULL;
    }

    _vLevelEntries.clear();

    _pRoot = NULL;
}

OSG_END_NAMESPACE
