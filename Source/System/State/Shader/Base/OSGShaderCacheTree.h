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

/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

template<class ObjectT>
class ShaderMapCache
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    typedef std::map<IdStore, ObjectUnrecPtr                > ObjectStore;

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

    ShaderMapCache(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderMapCache(void);

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

typedef ShaderMapCache<ShaderExecutableChunk   > ShaderExeMap;
typedef ShaderMapCache<ShaderExecutableVarChunk> ShaderVarMap;

#ifdef OSG_SHC_MODE_0
typedef ShaderMapCache<ShaderExecutableChunk   > ActiveShaderExeTree;
typedef ShaderMapCache<ShaderExecutableVarChunk> ActiveShaderVarTree;
#endif



/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

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

#ifdef OSG_SHC_MODE_1
typedef ShaderVectorCache<ShaderExecutableChunk   > ActiveShaderExeTree;
typedef ShaderVectorCache<ShaderExecutableVarChunk> ActiveShaderVarTree;
#endif

typedef ShaderVectorCache<ShaderExecutableChunk   > ShaderExeVector;
typedef ShaderVectorCache<ShaderExecutableVarChunk> ShaderVarVector;

inline
bool operator < (const ShaderExeVector::StoreElement    &rhs,
                 const ShaderExeVector::IdStore         &lhs)
{
    return rhs.first < lhs;
}

inline
bool operator < (const ShaderVarVector::StoreElement    &rhs,
                 const ShaderVarVector::IdStore         &lhs)
{
    return rhs.first < lhs;
}



/*! \nohierarchy
 */

template<UInt32 Base, UInt32 Exponent>
struct osgPow_s
{
    static const UInt32 result = Base * osgPow_s<Base, Exponent - 1>::result;
};

/*! \nohierarchy
 */

template<UInt32 Base>
struct osgPow_s<Base, 1>
{
    static const UInt32 result = Base;
};

/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

template<class ObjectT, UInt32 LevelBits>
class ShaderCacheTreeV0
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    static const UInt32 LevelSize   = osgPow_s<2u, LevelBits>::result; 
#if !defined(WIN32) && !defined(__APPLE__) 
    static const Real32 LevelFactor = 1.f / (LevelBits);
#else
    static const Real32 LevelFactor;
#endif

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

    ShaderCacheTreeV0(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderCacheTreeV0(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
  
    /*! \nohierarchy
     */
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

#ifdef OSG_SHC_MODE_2
typedef ShaderCacheTreeV0<ShaderExecutableChunk,
                          3                              > ActiveShaderExeTree;
typedef ShaderCacheTreeV0<ShaderExecutableVarChunk,
                          6                              > ActiveShaderVarTree;
#endif


/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

template<typename Object1T, typename RefCountPol1, 
         typename Object2T, typename RefCountPol2>
class VariantPtr
{
  public:

    VariantPtr(void);
    ~VariantPtr(void);

    Object1T *asT1(void) const;
    Object2T *asT2(void) const;

    void setAsT1(Object1T * const rhs);
    void setAsT2(Object2T * const rhs);

    void operator =(Object1T * const rhs);
    void operator =(Object2T * const rhs);

    Object2T *operator ->(void) const;

  protected:

    static const UIntPointer UIMaskChoice =  0x0001;
    static const UIntPointer UIMaskPtr    = ~0x0001;

    /*! \nohierarchy
     */
    union MemberU
    {
        UIntPointer  _uiIntVal;
        Object1T    *_pObj1;
        Object2T    *_pObj2;
    };

    MemberU _val;

  private:
    
    VariantPtr(const VariantPtr &source);
    void operator =(const VariantPtr &rhs);
};

/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

template<class ObjectT, UInt32 LevelBits>
class ShaderCacheTreeV1
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    static const UInt32 LevelSize   = osgPow_s<2u, LevelBits>::result; 
#if !defined(WIN32) && !defined(__APPLE__) 
    static const Real32 LevelFactor = 1.f / (LevelBits);
#else
    static const Real32 LevelFactor;
#endif

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

    ShaderCacheTreeV1(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderCacheTreeV1(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
  
    /*! \nohierarchy
     */
    struct TreeNode
    {
        typedef VariantPtr<ObjectT,  UnrecordedRefCountPolicy,
                           TreeNode, NoRefCountPolicy        > ChildPtr;

        TreeNode(void);
        ~TreeNode(void);
        
        void clear(void);

#ifdef OSG_DEBUG
        UInt32          _uiNodeId;
#endif
        ObjectUnrecPtr  _pObject;
        TreeNode       *_pPrev;
        TreeNode       *_pNext;
        ChildPtr        _vChildren[LevelSize];
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

#ifdef OSG_SHC_MODE_3
typedef ShaderCacheTreeV1<ShaderExecutableChunk,
                          3                              > ActiveShaderExeTree;
typedef ShaderCacheTreeV1<ShaderExecutableVarChunk,
                          6                              > ActiveShaderVarTree;
#endif

/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

template<class ObjectT, UInt32 LevelBits>
class ShaderCacheTreeV2
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    static const UInt32 LevelSize   = osgPow_s<2u, LevelBits>::result; 
#if !defined(WIN32) && !defined(__APPLE__) 
    static const Real32 LevelFactor = 1.f / (LevelBits);
#else
    static const Real32 LevelFactor;
#endif

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

    ShaderCacheTreeV2(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderCacheTreeV2(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
  
    /*! \nohierarchy
     */

    struct TreeNode
    {
        typedef VariantPtr<ObjectT,  UnrecordedRefCountPolicy,
                           TreeNode, NoRefCountPolicy        > ChildPtr;

        TreeNode(void);
        ~TreeNode(void);
        
        void clear(void);

#ifdef OSG_DEBUG
        UInt32          _uiNodeId;
#endif
        ObjectUnrecPtr  _pObject;
        TreeNode       *_pPrev;
        TreeNode       *_pNext;
        UInt16          _vJumps[LevelSize];
        ChildPtr        _vChildren[LevelSize];
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

#ifdef OSG_SHC_MODE_4
typedef ShaderCacheTreeV2<ShaderExecutableChunk,
                          3                              > ActiveShaderExeTree;
typedef ShaderCacheTreeV2<ShaderExecutableVarChunk,
                          6                              > ActiveShaderVarTree;
#endif


/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

template<class ObjectT, UInt32 LevelBits>
class ShaderCacheTreeV3
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ObjectT::ObjUnrecPtr  ObjectUnrecPtr;

    typedef UInt16                                            IdType;
    typedef std::vector<IdType                              > IdStore;

    static const UInt32 LevelSize   = osgPow_s<2u, LevelBits>::result; 
#if !defined(WIN32) && !defined(__APPLE__) 
    static const Real32 LevelFactor = 1.f / (LevelBits);
#else
    static const Real32 LevelFactor;
#endif

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

    void dumpDot(const Char8 *szFilename, 
                       bool   dumpEmptyLevelEntries = false);

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

    ShaderCacheTreeV3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ShaderCacheTreeV3(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
  
    /*! \nohierarchy
     */
    struct TreeNode
    {
        typedef VariantPtr<ObjectT,  UnrecordedRefCountPolicy,
                           TreeNode, NoRefCountPolicy        > ChildPtr;

        TreeNode(void);
        ~TreeNode(void);
        
        void clear(void);

#ifdef OSG_DEBUG
        UInt32          _uiNodeId;
#endif
        ObjectUnrecPtr  _pObject;
        TreeNode       *_pPrev;
        TreeNode       *_pNext;
        UInt16          _vJumps[LevelSize];
        ChildPtr        _vChildren[LevelSize];
    };

#ifdef OSG_DEBUG
    UInt32                   _uiNodeCount;
#endif
    TreeNode                *_pRoot;
    std::vector<TreeNode *>  _vLevelEntries;
    std::deque <TreeNode *>  _qFreeElements;

    typedef typename std::vector<TreeNode *>::      iterator TreeNodeVecIt;
    typedef typename std::vector<TreeNode *>::const_iterator TreeNodeVecConstIt;

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

#ifdef OSG_SHC_MODE_5
typedef ShaderCacheTreeV3<ShaderExecutableChunk,
                          3                              > ActiveShaderExeTree;
typedef ShaderCacheTreeV3<ShaderExecutableVarChunk,
                          6                              > ActiveShaderVarTree;
#endif

OSG_END_NAMESPACE

#include "OSGShaderCacheTree.inl"

#endif /* _OSGSHADERCACHETREE_H_ */

