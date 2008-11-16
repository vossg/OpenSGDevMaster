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

#ifdef OSG_SHC_MODE_0
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
#endif






#ifdef OSG_SHC_MODE_1
template<class ObjectT, UInt32 LevelBits> inline
ShaderCacheTree<ObjectT, LevelBits>::TreeNode::TreeNode(void) :
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
ShaderCacheTree<ObjectT, LevelBits>::TreeNode::~TreeNode(void)
{
    _pObject  = NULL;
    _pPrev    = NULL;
    _pNext    = NULL;
}
        
template<class ObjectT, UInt32 LevelBits> inline
void ShaderCacheTree<ObjectT, LevelBits>::TreeNode::clear(void)
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
ObjectT *ShaderCacheTree<ObjectT, LevelBits>::find(const IdStore &vIds)
{
    if(vIds.size() < 1)
        return NULL;

    ObjectT *returnValue = NULL;

    IdType uiStartId     = vIds[0];
    IdType uiStartLevel  = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId      = 0;
    UInt32 uiLastId      = vIds.size();
  

    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }


    UInt32    uiLevelSub = uiStartLevel * LevelBits;
    UInt32    uiCurrBits = 0x0000;
    TreeNode *pCurrNode  = _vLevelEntries[uiStartLevel];

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
bool ShaderCacheTree<ObjectT, LevelBits>::add(const IdStore &vIds,
                                                    ObjectT *pObject)
{
    bool returnValue = false;

    if(vIds.size() < 1)
        return returnValue;

    IdType uiStartId    = vIds[0];

    IdType uiStartLevel = IdType(uiStartId * LevelFactor);

    UInt32 uiCurrId     = 0;
    UInt32 uiLastId     = vIds.size();

    
    if(uiStartLevel >= _vLevelEntries.size())
    {
        uiStartLevel = _vLevelEntries.size() - 1;
    }

    UInt32 uiLevelSub   = uiStartLevel * LevelBits;
   
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
                        _vLevelEntries.push_back(pNextNode);
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
        TreeNode *pNextNode = pCurrNode->_vChildren[uiCurrBits];
        
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
void ShaderCacheTree<ObjectT, LevelBits>::sub(UInt32 uiIdx)
{
    IdType uiStartLevel  = IdType(uiIdx * LevelFactor);

    if(uiStartLevel >= _vLevelEntries.size())
    {
        return;
    }

    UInt32    uiLevelSub = uiStartLevel * LevelBits;
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
void ShaderCacheTree<ObjectT, LevelBits>::dumpDot(const Char8 *szFilename)
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
void ShaderCacheTree<ObjectT, LevelBits>::dumpDotNode(
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
ShaderCacheTree<ObjectT, LevelBits>::ShaderCacheTree(void) :
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
ShaderCacheTree<ObjectT, LevelBits>::~ShaderCacheTree(void)
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
typename ShaderCacheTree<ObjectT, LevelBits>::TreeNode *
    ShaderCacheTree<ObjectT, LevelBits>::allocateNode(void)
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
void ShaderCacheTree<ObjectT, LevelBits>::eraseNode(TreeNode *pNode)
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
void ShaderCacheTree<ObjectT, LevelBits>::destroyNode(TreeNode     *pNode,
                                                      ElemDestFunc  destFunc)
{
    for(UInt32 i = 0; i < LevelSize; ++i)
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
void ShaderCacheTree<ObjectT, LevelBits>::destroy(ElemDestFunc destFunc)
{
    destroyNode(_pRoot, destFunc);

    _pRoot = NULL;
}
#endif

OSG_END_NAMESPACE
