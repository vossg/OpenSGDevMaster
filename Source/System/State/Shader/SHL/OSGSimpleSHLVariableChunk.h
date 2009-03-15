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

#ifndef _OSGSIMPLESHLVARIABLECHUNK_H_
#define _OSGSIMPLESHLVARIABLECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSimpleSHLVariableChunkBase.h"
#include "OSGShaderProgramVariables.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGShaderExecutableVarChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief SimpleSHLVariableChunk class. See \ref
           PageStateSimpleSHLVariableChunk for a description.
    \ingroup GrpSystemShaderSHLChunk
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING SimpleSHLVariableChunk : 
    public SimpleSHLVariableChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SimpleSHLVariableChunkBase Inherited;
    typedef SimpleSHLVariableChunk     Self;

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

#ifdef OSG_1_COMPAT
    void setSHLChunk(SimpleSHLChunk *) {}
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    template<class ValueT>
    bool setUniformParameter   (const Char8 *name, const ValueT &value);
#endif

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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/

#if 0
    static volatile UInt16 _uiChunkCounter;
#endif

    UInt16 _uiChunkId;

    // Variables should all be in SimpleSHLVariableChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate      (const SimpleSHLVariableChunk *source      = NULL);
    void onCreateAspect(const SimpleSHLVariableChunk *createAspect,
                        const SimpleSHLVariableChunk *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleSHLVariableChunk(void);
    SimpleSHLVariableChunk(const SimpleSHLVariableChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleSHLVariableChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void updateVariables(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SimpleSHLVariableChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleSHLVariableChunk &source);
};

typedef SimpleSHLVariableChunk *SimpleSHLVariableChunkP;

OSG_END_NAMESPACE

#include "OSGSimpleSHLVariableChunkBase.inl"
#include "OSGSimpleSHLVariableChunk.inl"

#endif /* _OSGSIMPLESHLVARIABLECHUNK_H_ */
