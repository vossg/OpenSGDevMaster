/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGCHUNKOVERRIDEGROUP_H_
#define _OSGCHUNKOVERRIDEGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGChunkOverrideGroupBase.h"
#include "OSGChunkBlock.h"
#include "OSGChunkBlockMapFields.h"
#include "OSGMapCacheHandlerMixin.h"
#include "OSGState.h"

OSG_BEGIN_NAMESPACE

class StateChunk;
class ChunkOverrideGroup;

/*! \ingroup GrpSystemNodeCoreGroupsCores
    \nohierarchy
 */

struct ChunkOverrideMapCache
{
    typedef ChunkOverrideGroupBase                  ParentT;
    typedef ChunkOverrideGroup                      FinalContainer;

    typedef SFChunkBlockPtrMap                      MapCacheField;
    typedef MapCacheField::StoredType               MapCache;
    typedef SFChunkBlockPtrMap::EditHandle::KeyPool MapKeyPool;

    typedef MapCache::mapped_type                   MapCacheElement;
    typedef MapCache::key_type                      MapCacheKey;

    typedef ChunkBlock                              FinalizedElement;

    static void setFallback(ParentT *pContainer, MapCacheElement pElem)
    {
        pContainer->setFallbackChunkBlock(pElem);
    }
                     
    static MapCacheElement getFallback(ParentT *pContainer)
    {
        return pContainer->getFallbackChunkBlock();
    }

    static const Char8 *getFieldName(void)
    {
        return "chunkBlockStore";
    }
};

/*! \brief ChunkOverrideGroup class. See \ref
    PageSystemChunkOverrideGroup for a description.
    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ChunkOverrideGroup : 
    public MapCacheHandlerMixin<ChunkOverrideMapCache>
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MapCacheHandlerMixin<ChunkOverrideMapCache> Inherited;
    typedef ChunkOverrideGroup                          Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void             addChunkBlock(ChunkBlock       * const pChunkBlock,
                                   ChunkBlockMapKey         key    = 0);

    void             subChunkBlock(ChunkBlockMapKey         key    = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    ChunkBlock *findChunkBlock(ChunkBlockMapKey key) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    const SFChunkBlockPtrMap *getSFChunkBlockStore(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool addChunk(StateChunk *chunk, 
                  Int32       slot = State::AutoSlotReplace);

    bool subChunk(StateChunk *chunk, 
                  Int32       slot = State::AutoSlotReplace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    Int32       find(      StateChunk      *chunk);
    StateChunk *find(const StateChunkClass &type, 
                           Int32            slot =State::AutoSlotReplace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static void classDescInserter(TypeObject &oType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ChunkOverrideGroup(void);
    ChunkOverrideGroup(const ChunkOverrideGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ChunkOverrideGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Render                                  */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ChunkOverrideGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ChunkOverrideGroup &source);
};

typedef ChunkOverrideGroup *ChunkOverrideGroupP;

OSG_END_NAMESPACE

#include "OSGChunkOverrideGroupBase.inl"
#include "OSGChunkOverrideGroup.inl"

#endif /* _OSGCHUNKOVERRIDEGROUP_H_ */
