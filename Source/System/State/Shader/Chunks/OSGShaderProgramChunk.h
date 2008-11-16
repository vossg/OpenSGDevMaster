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

#ifndef _OSGSHADERPROGRAMCHUNK_H_
#define _OSGSHADERPROGRAMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderProgram.h"
#include "OSGShaderProgramChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderProgramChunk class. See \ref
           PageSystemShaderProgramChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderProgramChunk : public ShaderProgramChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderProgramChunkBase Inherited;
    typedef ShaderProgramChunk     Self;

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

    void addShader(ShaderProgram * const value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void activate  (DrawEnv    *pEnv,              
                            UInt32      uiIdx = 0);
    virtual void changeFrom(DrawEnv    *pEnv, 
                            StateChunk *pOld, 
                            UInt32      uiIdx = 0);
    virtual void deactivate(DrawEnv    *pEnv,              
                            UInt32      uiIdx = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static UInt32 _extSHL;

    /*---------------------------------------------------------------------*/

    static volatile UInt16 _uiChunkCounter;

    UInt16 _uiChunkId;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderProgramChunk(void);
    ShaderProgramChunk(const ShaderProgramChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderProgramChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate      (const ShaderProgramChunk *source      = NULL);
    void onCreateAspect(const ShaderProgramChunk *createAspect,
                        const ShaderProgramChunk *source      = NULL);
    void onDestroy(           UInt32              uiId              );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // class. Used for indexing in State
    static StateChunkClass _class;

    friend class FieldContainer;
    friend class ShaderProgramChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderProgramChunk &source);
};

typedef ShaderProgramChunk *ShaderProgramChunkP;

OSG_END_NAMESPACE

#include "OSGShaderProgramChunkBase.inl"
#include "OSGShaderProgramChunk.inl"

#endif /* _OSGSHADERPROGRAMCHUNK_H_ */
