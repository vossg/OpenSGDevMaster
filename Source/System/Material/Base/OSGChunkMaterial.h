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


#ifndef _OSGCHUNKMATERIAL_H_
#define _OSGCHUNKMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGChunkMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Material using chunk set.  See \ref 
    PageSystemMaterialChunkMaterial for a description.
*/

class OSG_SYSTEM_DLLMAPPING ChunkMaterial : public ChunkMaterialBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

#ifdef OLD
    virtual void     draw         (DrawFunctor      &func,
                                   DrawActionBase   *action);

    virtual void     draw         (MaterialDrawable *geo,
                                   DrawActionBase   *action);

    virtual StatePtr makeState    (void                    );
#endif

    virtual void     rebuildState (void                    );

    virtual bool     isTransparent(void                    ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    bool addChunk(StateChunkPtr chunk, 
                  Int32         slot = State::AutoSlotReplace);
    bool subChunk(StateChunkPtr chunk, 
                  Int32         slot = State::AutoSlotReplace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

    Int32         find(      StateChunkPtr chunk);
    StateChunkPtr find(const FieldContainerType &type, 
                             Int32               slot =State::AutoSlotReplace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

    void clearChunks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

    virtual bool operator == (const ChunkMaterial &other);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ChunkMaterial(void);
    ChunkMaterial(const ChunkMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ChunkMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void addChunks(StatePtr state);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ChunkMaterialBase Inherited;

    friend class ChunkMaterialBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ChunkMaterial &source);
};

typedef ChunkMaterial              *ChunkMaterialP;

OSG_END_NAMESPACE

#include "OSGChunkMaterialBase.inl"
#include "OSGChunkMaterial.inl"

#define OSGCHUNKMATERIAL_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGCHUNKMATERIAL_H_ */
