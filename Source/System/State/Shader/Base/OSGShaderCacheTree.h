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

#ifndef _OSGSHADERCACHETREE_H_
#define _OSGSHADERCACHETREE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"

#include "OSGShaderExecutableChunk.h"
#include "OSGShaderExecutableVarChunk.h"

OSG_BEGIN_NAMESPACE

#ifdef OSG_SHC_MODE_0
template<class ObjectT>
class ShaderVectorCache
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    typedef std::pair  <IdStore, 
                        ObjectUnrecPtr                      > StoreElement;

    typedef std::vector<StoreElement                        > ObjectStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ObjectT *find(const IdStore &vIds   );
    bool     add (const IdStore &vIds,
                        ObjectT *pObject);
    void     sub (      UInt32   uiIdx  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void dumpDot(const Char8 *szFilename);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    template <typename ElemDestFunc>
    void destroy(ElemDestFunc destFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderVectorCache(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderVectorCache(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    ObjectStore _vObjectStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

typedef ShaderVectorCache<ShaderExecutableChunk   > ActiveShaderExeTree;
typedef ShaderVectorCache<ShaderExecutableVarChunk> ActiveShaderVarTree;

inline
bool operator < (const ActiveShaderExeTree::StoreElement    &rhs,
                 const ActiveShaderExeTree::IdStore         &lhs)
{
    return rhs.first < lhs;
}

inline
bool operator < (const ActiveShaderVarTree::StoreElement    &rhs,
                 const ActiveShaderVarTree::IdStore         &lhs)
{
    return rhs.first < lhs;
}

#endif

#ifdef OSG_SHC_MODE_1
template<UInt32 Base, UInt32 Exponent>
struct osgPow_s
{
    static const UInt32 result = Base * osgPow_s<Base, Exponent - 1>::result;
};

template<UInt32 Base>
struct osgPow_s<Base, 1>
{
    static const UInt32 result = Base;
};


template<class ObjectT, UInt32 LevelBits>
class ShaderCacheTree
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    static const UInt32 LevelSize   = osgPow_s<2u, LevelBits>::result; 
    static const Real32 LevelFactor = 1.f / (LevelBits + 1);

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ObjectT *find(const IdStore &vIds   );
    bool     add (const IdStore &vIds,
                        ObjectT *pObject);
    void     sub (      UInt32   uiIdx  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void dumpDot(const Char8 *szFilename);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    template <typename ElemDestFunc>
    void destroy(ElemDestFunc destFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderCacheTree(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderCacheTree(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    struct TreeNode
    {
        TreeNode(void);
        ~TreeNode(void);
        
        void clear(void);

#ifdef OSG_DEBUG
        UInt32          _uiNodeId;
#endif
        ObjectUnrecPtr  _pObject;
        TreeNode       *_pPrev;
        TreeNode       *_pNext;
        TreeNode       *_vChildren[LevelSize];
    };

#ifdef OSG_DEBUG
    UInt32                   _uiNodeCount;
#endif
    TreeNode                *_pRoot;
    std::vector<TreeNode *>  _vLevelEntries;
    std::deque <TreeNode *>  _qFreeElements;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    TreeNode *allocateNode(void           );
    void      eraseNode   (TreeNode *pNode);

    template <typename ElemDestFunc>
    void destroyNode(TreeNode *pNode, ElemDestFunc destFunc);

    void dumpDotNode(TreeNode                               *pNode, 
                     FILE                                   *pOut,
                     std::vector< std::vector<TreeNode *> > &vLevelStore,
                     UInt32                                  uiLevel    );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

typedef ShaderCacheTree<ShaderExecutableChunk,
                        3                              > ActiveShaderExeTree;
typedef ShaderCacheTree<ShaderExecutableVarChunk,
                        6                              > ActiveShaderVarTree;
#endif

OSG_END_NAMESPACE

#include "OSGShaderCacheTree.inl"

#endif /* _OSGSHADERCACHETREE_H_ */
