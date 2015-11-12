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

#ifndef _OSGSTATEOVERRIDE_H_
#define _OSGSTATEOVERRIDE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGSimplePool.h"
#include "OSGState.h"

#include <vector>
#include <utility>
#include <algorithm>

OSG_BEGIN_NAMESPACE

class ShaderExecutableChunk;
class ShaderExecutableVarChunk;
class ShaderProgramChunk;
class ShaderProgramVariableChunk;
class ShaderProgram;
class SimpleSHLChunk;

/*! \ingroup GrpSystemStateBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
*/

class OSG_SYSTEM_DLLMAPPING StateOverride 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::pair  <UInt32, StateChunk *>                 ChunkElement;

    typedef std::vector<ChunkElement        >                 ChunkStore;
    typedef std::vector<ChunkElement        >::iterator       ChunkStoreIt;
    typedef std::vector<ChunkElement        >::const_iterator ChunkStoreConstIt;

    typedef std::vector<UInt16              >                 IdStore;
    typedef std::vector<UInt16              >::iterator       IdStoreIt;


    typedef std::vector<ShaderProgramChunk *>           ProgramChunkStore;
    typedef std::vector<ShaderProgramVariableChunk *>   ProgramVarChunkStore;


    static const UInt32 InvalidKey     = State::InvalidKey;

    static const UInt32 SkipRebuild    = State::SkipRebuild;

    static const UInt32 Key1Mask       = State::Key1Mask;
    static const UInt32 Key2Mask       = State::Key2Mask;
    static const UInt32 Key3Mask       = State::Key3Mask;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StateOverride(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StateOverride(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void fillFrom(StateOverride *pState);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */
    
    void setKeyGen    (UInt32  uiKeyGen                                );
    void updateSortKey(UInt32 &uiSortKey, UInt32 uiKeyGen = SkipRebuild);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ChunkStoreConstIt begin (void) const;
    ChunkStoreConstIt end   (void) const;
    SizeT             size  (void) const;
    UInt32            size32(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void reset        (void                              );

    void addOverride  (UInt32                      uiSlot, 
                       StateChunk                 *pChunk);
    void addOverride  (UInt32                      uiSlot, 
                       SimpleSHLChunk             *pChunk);
    void addOverride  (UInt32                      uiSlot, 
                       ShaderProgramChunk         *pChunk);
    void addOverride  (UInt32                      uiSlot, 
                       ShaderProgramVariableChunk *pChunk);


    void subOverride  (UInt32                      uiSlot, 
                       StateChunk                 *pChunk);
    void subOverride  (UInt32                      uiSlot, 
                       SimpleSHLChunk             *pChunk);
    void subOverride  (UInt32                      uiSlot, 
                       ShaderProgramChunk         *pChunk);
    void subOverride  (UInt32                      uiSlot, 
                       ShaderProgramVariableChunk *pChunk);


    bool empty        (void                      );

    bool isTransparent(void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    const IdStore              &getProgIds  (void);
    const ProgramChunkStore    &getPrograms (void);

    const IdStore              &getVarIds   (void);
    const ProgramVarChunkStore &getVariables(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void                      setShader   (ShaderExecutableChunk    *pShader);
    ShaderExecutableChunk    *getShader   (void                             );

    void                      setShaderVar(ShaderExecutableVarChunk *pVar   );
    ShaderExecutableVarChunk *getShaderVar(void                             );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:


    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ChunkStore                _vChunks;

    ShaderExecutableChunk    *_pShader;
    ShaderExecutableVarChunk *_pShaderVar;

    ProgramChunkStore         _vProgChunks;
    IdStore                   _vProgIds;

    ProgramVarChunkStore      _vProgVarChunks;
    IdStore                   _vProgVarIds;

    UInt32                    _uiSortKey;
    UInt32                    _uiKeyGen;
    UInt32                    _uiKeyMask;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void rebuildSortKey(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void insertOverride(UInt32      uiSlot, 
                        StateChunk *pChunk);

    void eraseOverride (UInt32      uiSlot, 
                        StateChunk *pChunk);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class T, 
              class Tag, 
              class RefCountPolicy, 
              class LockPolicy    > friend class SimplePool;

    /*! \brief prohibit default function (move to 'public' if needed) */
    StateOverride(const StateOverride &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const StateOverride &source);
};

bool operator <(const StateOverride::ChunkElement &lhs, 
                const StateOverride::ChunkElement &rhs);

OSG_END_NAMESPACE

#include "OSGStateOverride.inl"

#endif /* _OSGSTATEOVERRIDE_H_ */
