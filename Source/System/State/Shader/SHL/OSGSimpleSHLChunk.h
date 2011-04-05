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

#ifndef _OSGSIMPLESHLCHUNK_H_
#define _OSGSIMPLESHLCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSimpleSHLChunkBase.h"
#include "OSGShaderProgram.h"
#include "OSGShaderProgramVariables.h"
#include "OSGShaderVariableFunctor.h"
#include "OSGGLFuncProtos.h"

#include "OSGShaderExecutableChunk.h"

OSG_BEGIN_NAMESPACE

class Window;

/*! \brief SimpleSHLChunk class. See \ref
           PageStateSimpleSHLChunk for a description.
    \ingroup GrpSystemShaderSHLChunk
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING SimpleSHLChunk : public SimpleSHLChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SimpleSHLChunkBase                           Inherited;
    typedef SimpleSHLChunk                               Self;

    typedef ShaderVariableFunctor::GetUniformLocProc     GetUniformLocProc;
    typedef ShaderVariableFunctor::ProcVarFunctor        ProcVarFunctor;
    typedef ShaderVariableFunctor::ProcVarNodeFunctor    ProcVarNodeFunctor;

    static const UInt32 KeepProgActive = ShaderProgram::KeepProgActive;

    static const UInt32 ProgActive     = ShaderProgram::ProgActive;

#ifdef OSG_1_COMPAT
    typedef ShaderVariableFunctor::ParamFunctor          ParamFunctor;
    typedef ShaderVariableFunctor::OSGParamFunctor       OSGParamFunctor;

    static const OSG::BitVector ParametersFieldMask = VariablesFieldMask;
#endif

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

    bool readFragmentProgram(const Char8 *file);
    bool readGeometryProgram(const Char8 *file);
    bool readVertexProgram  (const Char8 *file);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Program Parameter                         */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    void   addProgramParameter   (GLenum name, UInt32 value);
    void   subProgramParameter   (GLenum name              );
#endif

    void   setProgramParameter   (GLenum name, UInt32 value);

    UInt32 getProgramParameter   (GLenum name              );

    void   clearProgramParameters(void                     );

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

#ifdef OSG_1_COMPAT
    template<class ValueT>
    bool setUniformParameter   (const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool getUniformParameter   (const Char8 *name,       ValueT &value);

    bool subUniformParameter   (const Char8 *name                     );
    void clearUniformParameters(      void                            );
#endif

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

#ifdef OSG_1_COMPAT
           void addParameterCallback(const Char8 *name, ParamFunctor    fp);
           void addParameterCallback(const Char8 *name, OSGParamFunctor fp);

    static void setParameterCallback(                   ParamFunctor    fp);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

#if 1
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

#ifdef OSG_1_COMPAT
    static UInt32 getFuncUniform1i       (void);
    static UInt32 getFuncUniform1iv      (void);
    static UInt32 getFuncUniform2iv      (void);
    static UInt32 getFuncUniform3iv      (void);
    static UInt32 getFuncUniform4iv      (void);

    static UInt32 getFuncUniform1f       (void);
    static UInt32 getFuncUniform1fv      (void);
    static UInt32 getFuncUniform2fv      (void);
    static UInt32 getFuncUniform3fv      (void);
    static UInt32 getFuncUniform4fv      (void);

    static UInt32 getFuncUniformMatrix4fv(void);

    static UInt32 getFuncGetUniformiv    (void);
    static UInt32 getFuncGetUniformfv    (void);
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

#ifdef OSG_1_COMPAT
    static ParamFunctor _fParameterCallback;
#endif

    /*---------------------------------------------------------------------*/

#if 0
    static volatile UInt16 _uiChunkCounter;
#endif

    UInt16 _uiChunkId;

    // Variables should all be in SimpleSHLChunkBase.

    typedef MFFragmentShaderType::const_iterator FragmentShaderIt;
    typedef MFGeometryShaderType::const_iterator GeometryShaderIt;
    typedef MFVertexShaderType  ::const_iterator VertexShaderIt;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleSHLChunk(void);
    SimpleSHLChunk(const SimpleSHLChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleSHLChunk(void);

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
                                  UInt32                   uiOptions);
    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate      (const SimpleSHLChunk *source      = NULL);
    void onCreateAspect(const SimpleSHLChunk *createAspect,
                        const SimpleSHLChunk *source      = NULL);
    void onDestroy(           UInt32          uiId              );

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

    friend class FieldContainer;
    friend class SimpleSHLChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleSHLChunk &source);
};

typedef SimpleSHLChunk *SimpleSHLChunkP;

OSG_END_NAMESPACE

#include "OSGSimpleSHLChunkBase.inl"
#include "OSGSimpleSHLChunk.inl"

#endif /* _OSGSIMPLESHLCHUNK_H_ */
