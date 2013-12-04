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

#ifndef _OSGCOMPUTESHADERCHUNK_H_
#define _OSGCOMPUTESHADERCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComputeShaderChunkBase.h"
#include "OSGShaderProgram.h"
#include "OSGShaderExecutableChunk.h"

OSG_BEGIN_NAMESPACE

class Window;

/*! \brief ComputeShaderChunk class. See \ref
           PageStateComputeShaderChunk for a description.
    \ingroup GrpSystemShaderSHLChunk
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_CONTRIBCOMPUTEBASE_DLLMAPPING ComputeShaderChunk : 
    public ComputeShaderChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComputeShaderChunkBase                       Inherited;
    typedef ComputeShaderChunk                           Self;

    typedef ShaderVariableFunctor::GetUniformLocProc     GetUniformLocProc;
    typedef ShaderVariableFunctor::ProcVarFunctor        ProcVarFunctor;
    typedef ShaderVariableFunctor::ProcVarNodeFunctor    ProcVarNodeFunctor;

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

    bool readComputeProgram  (const Char8 *file);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Program Parameter                         */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

#if 0
    virtual void update    (DrawEnv    *pEnv     );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    template<class ValueT>
    bool addUniformVariable      (const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool updateUniformVariable   (const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool getUniformVariable      (const Char8 *name,       ValueT &value);

    bool subUniformVariable      (const Char8 *name                     );
    void clearUniformVariables   (      void                            );

    bool addOSGVariable          (const Char8 *name                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool addProceduralVariable       (const Char8              *name,
                                            ProcVarFunctor      pFunc,
                                            UInt32              uiDependency =
                                               ShaderProcVariable::SHDObject);

    bool updateProceduralVariable    (const Char8              *name,
                                            ProcVarFunctor      pFunc,
                                            UInt32              uiDependency =
                                               ShaderProcVariable::SHDObject);

    bool addNodeProceduralVariable   (const Char8              *name,
                                            ProcVarNodeFunctor  pFunc,
                                            UInt32              uiDependency =
                                               ShaderProcVariable::SHDObject);

    bool updateNodeProceduralVariable(const Char8              *name,
                                            ProcVarNodeFunctor  pFunc,
                                            UInt32              uiDependency =
                                               ShaderProcVariable::SHDObject);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

#if 0
    void updateParameters(      
              Window                         *win,
        const UInt32                         &parameters,
              bool                            useProgram       = true,
              bool                            force            = false,
              bool                            keepProgramActive=false);

    const UInt32 *getMFParameters(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static UInt32 _arbComputeShader;

    /*---------------------------------------------------------------------*/

    static volatile UInt16 _uiChunkCounter;

    UInt16 _uiChunkId;

    // Variables should all be in ComputeShaderChunkBase.

    typedef MFComputeShaderType::const_iterator ComputeShaderIt;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComputeShaderChunk(void);
    ComputeShaderChunk(const ComputeShaderChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComputeShaderChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt64                   uiOptions);
    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate      (const ComputeShaderChunk *source      = NULL);
    void onCreateAspect(const ComputeShaderChunk *createAspect,
                        const ComputeShaderChunk *source      = NULL);
    void onDestroy(           UInt32              uiId              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void updateVariableLocations  (DrawEnv *pEnv,
                                   UInt32   uiProgram);
    void updateVariables          (DrawEnv *pEnv,
                                   UInt32   uiProgram);
    void updateProceduralVariables(DrawEnv *pEnv,
                                   UInt32   uiUpdateDependents);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    bool readProgram(      std::string  &szTarget,
                     const Char8        *szFilename);

    bool readProgram(      std::string  &szTarget,
                           std::istream &iStream);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // class. Used for indexing in State
    static StateChunkClass _class;

    friend class FieldContainer;
    friend class ComputeShaderChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComputeShaderChunk &source);
};

typedef ComputeShaderChunk *ComputeShaderChunkP;

OSG_END_NAMESPACE

#include "OSGComputeShaderChunkBase.inl"
#include "OSGComputeShaderChunk.inl"

#endif /* _OSGCOMPUTESHADERCHUNK_H_ */
