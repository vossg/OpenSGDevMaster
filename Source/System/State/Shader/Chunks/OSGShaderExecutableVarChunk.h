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

#ifndef _OSGSHADEREXECUTABLEVARCHUNK_H_
#define _OSGSHADEREXECUTABLEVARCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderExecutableVarChunkBase.h"
#include "OSGShaderExecutableChunk.h"

#include <map>

OSG_BEGIN_NAMESPACE

class ShaderCache;
class SimpleSHLVariableChunk;

/*! \brief ShaderExecutableVarChunk class. See \ref
           PageStateShaderExecutableVarChunk for a description.
    \ingroup GrpSystemShaderChunks
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderExecutableVarChunk : 
    public ShaderExecutableVarChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderExecutableVarChunkBase           Inherited;
    typedef ShaderExecutableVarChunk               Self;

    typedef MFProgramVarChunksType::const_iterator VarChunksIt;

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    static       UInt32           getStaticClassId(void);
    static const StateChunkClass *getStaticClass  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Chunk Id                                  */
    /*! \{                                                                 */

    virtual UInt16 getChunkId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void setShaderExecutableChunk(ShaderExecutableChunk * const);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void merge(ShaderProgramVariableChunk *pVar);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual void activate  (DrawEnv*,              UInt32 index = 0);
    virtual void changeFrom(DrawEnv*, StateChunk*, UInt32 index = 0);
    virtual void deactivate(DrawEnv*,              UInt32 index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

#ifdef OSG_MULTISHADER_VARCHUNK
    typedef std::map<UInt32, MFInt32>                 ShaderVarLocMap;
    typedef std::map<UInt32, MFInt32>::value_type     ShaderVarLocMapValueT;
    typedef std::map<UInt32, MFInt32>::iterator       ShaderVarLocMapIt;
    typedef std::map<UInt32, MFInt32>::const_iterator ShaderVarLocMapConstIt;
#endif

    /*---------------------------------------------------------------------*/

    static volatile UInt16 _uiChunkCounter;

#ifdef OSG_MULTISHADER_VARCHUNK
    ShaderVarLocMap _mShaderVarLocs;
#endif
    UInt16          _uiChunkId;

    // Variables should all be in SHLVariableChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate      (const ShaderExecutableVarChunk *source      = NULL);
    void onCreateAspect(const ShaderExecutableVarChunk *createAspect,
                        const ShaderExecutableVarChunk *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderExecutableVarChunk(void);
    ShaderExecutableVarChunk(const ShaderExecutableVarChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderExecutableVarChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void updateVariables (DrawEnv *pEnv);
    void remergeVariables(void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    const MFProgramVarChunksType *getMFProgramVarChunks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // class. Used for indexing in State
    static StateChunkClass _class;

    friend class FieldContainer;
    friend class ShaderExecutableVarChunkBase;
    friend class ShaderCache;
    friend class SimpleSHLVariableChunk;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderExecutableVarChunk &source);
};

typedef ShaderExecutableVarChunk *ShaderExecutableVarChunkP;

OSG_END_NAMESPACE

#include "OSGShaderExecutableVarChunkBase.inl"
#include "OSGShaderExecutableVarChunk.inl"

#endif /* _OSGSHADEREXECUTABLEVARCHUNK_H_ */
