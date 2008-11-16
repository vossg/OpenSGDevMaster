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

#ifndef _OSGSHADERPROGRAMVARIABLECHUNK_H_
#define _OSGSHADERPROGRAMVARIABLECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderProgramVariableChunkBase.h"
#include "OSGShaderProgramVariables.h"
#include "OSGLockPolicies.h"
#include "OSGSimpleReusePool.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderProgramVariableChunk class. See \ref
           PageStateShaderProgramVariableChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderProgramVariableChunk : 
    public ShaderProgramVariableChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderProgramVariableChunkBase Inherited;
    typedef ShaderProgramVariableChunk     Self;

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

    UInt16 getVariableId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */
    template<class ValueT>
    bool addUniformVariable    (const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool updateUniformVariable (const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool getUniformVariable    (const Char8 *name,       ValueT &value);

    bool subUniformVariable    (const Char8 *name                     );
    void clearUniformVariables (      void                            );

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

    void   addDestroyedFunctor   (ChangedFunctor func,
                                  std::string    createSymbol);

    template<class FunctorT>
    void   subDestroyedFunctor   (FunctorT       func        );

    template<class FunctorT>
    bool   hasDestroyedFunctor   (FunctorT       func        );

    void   clearDestroyedFunctors(void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void addParent(FieldContainer * const pParent,
                   UInt16                 uiParentFieldId);

    void subParent(FieldContainer * const pParent        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    struct VariableIdPoolTag;

    typedef SimpleReusePool<Int32, 
                            VariableIdPoolTag, 
                            SingleLockPolicy > VarIdPool;


    static VarIdPool *_pVarIdPool;

           UInt16     _uiVarId;

    /*---------------------------------------------------------------------*/

    static volatile UInt16 _uiChunkCounter;

    UInt16 _uiChunkId;

    // Variables should all be in ShaderProgramVariableChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate      (const ShaderProgramVariableChunk *source      = NULL);
    void onCreateAspect(const ShaderProgramVariableChunk *createAspect,
                        const ShaderProgramVariableChunk *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    virtual void onDestroy(UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderProgramVariableChunk(void);
    ShaderProgramVariableChunk(const ShaderProgramVariableChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderProgramVariableChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // class. Used for indexing in State
    static StateChunkClass _class;

    friend class FieldContainer;
    friend class ShaderProgramVariableChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderProgramVariableChunk &source);
};

typedef ShaderProgramVariableChunk *ShaderProgramVariableChunkP;

OSG_END_NAMESPACE

#include "OSGShaderProgramVariableChunkBase.inl"
#include "OSGShaderProgramVariableChunk.inl"

#endif /* _OSGSHADERPROGRAMVARIABLECHUNK_H_ */
