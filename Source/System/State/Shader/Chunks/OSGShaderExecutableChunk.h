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

#ifndef _OSGSHADEREXECUTABLECHUNK_H_
#define _OSGSHADEREXECUTABLECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderProgramVariables.h"
#include "OSGShaderProgram.h"
#include "OSGShaderExecutableChunkBase.h"

OSG_BEGIN_NAMESPACE

class ShaderProgramChunk;
class ShaderCache;
class SimpleSHLChunk;

/*! \brief ShaderExecutableChunk class. See \ref
           PageSystemShaderExecutableChunk for a description.
    \ingroup GrpSystemShaderChunks
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderExecutableChunk : 
    public ShaderExecutableChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderExecutableChunkBase            Inherited;
    typedef ShaderExecutableChunk                Self;

    static const UInt32 KeepProgActive = ShaderProgram::KeepProgActive;

    static const UInt32 ProgActive     = ShaderProgram::ProgActive;

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

    void merge(const ShaderProgramChunk *pChunk);

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

    typedef MFFragmentShaderType::const_iterator FragmentShaderIt;
    typedef MFGeometryShaderType::const_iterator GeometryShaderIt;
    typedef MFVertexShaderType  ::const_iterator VertexShaderIt;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderExecutableChunk(void);
    ShaderExecutableChunk(const ShaderExecutableChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderExecutableChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions);
    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate      (const ShaderExecutableChunk *source      = NULL);
    void onCreateAspect(const ShaderExecutableChunk *createAspect,
                        const ShaderExecutableChunk *source      = NULL);
    void onDestroy(           UInt32                 uiId              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void updateVariableLocations  (DrawEnv *pEnv,
                                   UInt32   uiProgram);
    void updateVariables          (DrawEnv *pEnv,
                                   UInt32   uiProgram);
    void updateParameters         (DrawEnv *pEnv,
                                   UInt32   uiProgram);
    void updateAttribBindings     (DrawEnv *pEnv,
                                   UInt32   uiProgram);

    void updateProceduralVariables(DrawEnv *pEnv,
                                   UInt32   uiUpdateDependents);

    void remergeVariables         (void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    const MFFragmentShaderType *getMFFragmentShader(void);
    const MFGeometryShaderType *getMFGeometryShader(void);
    const MFVertexShaderType   *getMFVertexShader  (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // class. Used for indexing in State
    static StateChunkClass _class;

    friend class FieldContainer;
    friend class ShaderExecutableChunkBase;
    friend class ShaderCache;
    friend class SimpleSHLChunk;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderExecutableChunk &source);
};

typedef ShaderExecutableChunk *ShaderExecutableChunkP;

OSG_END_NAMESPACE

#include "OSGShaderExecutableChunkBase.inl"
#include "OSGShaderExecutableChunk.inl"

#endif /* _OSGSHADEREXECUTABLECHUNK_H_ */
