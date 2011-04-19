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

#ifndef _OSGSHADERPROGRAM_H_
#define _OSGSHADERPROGRAM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderProgramBase.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"
#include "OSGShaderProgramVariables.h"
#include "OSGLockPolicies.h"
#include "OSGSimpleReusePool.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderProgram class. See \ref
           PageSystemShaderProgram for a description.
    \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderProgram : public ShaderProgramBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderProgramBase Inherited;
    typedef ShaderProgram     Self;

    typedef ShaderVariableFunctor::ProcVarFunctor     ProcVarFunctor;
    typedef ShaderVariableFunctor::ProcVarNodeFunctor ProcVarNodeFunctor;

    static const UInt32 KeepProgActive = 0x0001;

    static const UInt32 ProgActive     = 0x0001;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    static UInt32 getFuncIdCreateShader      (void);
    static UInt32 getFuncIdDeleteShader      (void);
    static UInt32 getFuncIdShaderSource      (void);
    static UInt32 getFuncIdCompileShader     (void);
    static UInt32 getFuncIdAttachShader      (void);
    static UInt32 getFuncIdGetShaderiv       (void);
    static UInt32 getFuncIdGetShaderInfoLog  (void);

    static UInt32 getFuncIdCreateProgram     (void);
    static UInt32 getFuncIdDeleteProgram     (void);
    static UInt32 getFuncIdLinkProgram       (void);
    static UInt32 getFuncIdGetProgramiv      (void);
    static UInt32 getFuncIdGetProgramInfoLog (void);
    static UInt32 getFuncIdUseProgram        (void);

    static UInt32 getFuncIdGetUniformLocation(void);

    static UInt32 getFuncIdUniform1i         (void);
    static UInt32 getFuncIdUniform2i         (void);
    static UInt32 getFuncIdUniform3i         (void);
    static UInt32 getFuncIdUniform4i         (void);

    static UInt32 getFuncIdUniform1f         (void);
    static UInt32 getFuncIdUniform2f         (void);
    static UInt32 getFuncIdUniform3f         (void);
    static UInt32 getFuncIdUniform4f         (void);

    static UInt32 getFuncIdUniform1iv        (void);
    static UInt32 getFuncIdUniform2iv        (void);
    static UInt32 getFuncIdUniform3iv        (void);
    static UInt32 getFuncIdUniform4iv        (void);

    static UInt32 getFuncIdUniform1fv        (void);
    static UInt32 getFuncIdUniform2fv        (void);
    static UInt32 getFuncIdUniform3fv        (void);
    static UInt32 getFuncIdUniform4fv        (void);

    static UInt32 getFuncIdUniformMatrix2fv  (void);
    static UInt32 getFuncIdUniformMatrix3fv  (void);
    static UInt32 getFuncIdUniformMatrix4fv  (void);

    static UInt32 getFuncIdGetUniformiv      (void);
    static UInt32 getFuncIdGetUniformfv      (void);

    static UInt32 getFuncIdProgramParameteri (void);
    static UInt32 getFuncIdBindAttribLocation(void);

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

    void validate(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    static ShaderProgramTransitPtr createVertexShader  (
                                             bool bCreateDefAttribMap = false);
    static ShaderProgramTransitPtr createGeometryShader(void                 );
    static ShaderProgramTransitPtr createFragmentShader(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool readProgram(const Char8 *file);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    template<class ValueT>
    bool addUniformVariable   (const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool updateUniformVariable(const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool getUniformVariable   (const Char8 *name,       ValueT &value);

    bool subUniformVariable   (const Char8 *name                     );

    void clearUniformVariables(      void                            );

    bool addOSGVariable       (const Char8 *name                     );

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

    void setProgramParameter(GLenum name, UInt32 value);
    void subProgramParameter(GLenum name              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void setProgramAttribute      (UInt16 uiIndex, std::string szName);
    void subProgramAttribute      (UInt16 uiIndex                    );

    void createDefaulAttribMapping(void                              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool   hasParameter (void);
    bool   hasAttributes(void);
    UInt16 getProgramId (void);

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
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void   addDestroyedFunctor    (ChangedFunctor func,
                                   std::string    createSymbol);

    template<class FunctorT>
    void   subDestroyedFunctor    (FunctorT       func        );

    template<class FunctorT>
    bool   hasDestroyedFunctor    (FunctorT       func        );

    void   clearDestroyedFunctors (void                       );

    UInt32 getNumDestroyedFunctors(void                       ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static UInt32 _extSHL;
    static UInt32 _extCG;
    static UInt32 _extGeoShader4;

    static UInt32 FuncIdCreateShader;
    static UInt32 FuncIdDeleteShader;
    static UInt32 FuncIdShaderSource;
    static UInt32 FuncIdCompileShader;
    static UInt32 FuncIdAttachShader;
    static UInt32 FuncIdGetShaderiv;
    static UInt32 FuncIdGetShaderInfoLog;

    static UInt32 FuncIdCreateProgram;
    static UInt32 FuncIdDeleteProgram;
    static UInt32 FuncIdLinkProgram;
    static UInt32 FuncIdGetProgramiv;
    static UInt32 FuncIdGetProgramInfoLog;
    static UInt32 FuncIdUseProgram;

    static UInt32 FuncIdGetUniformLocation;

    static UInt32 FuncIdUniform1i;
    static UInt32 FuncIdUniform2i;
    static UInt32 FuncIdUniform3i;
    static UInt32 FuncIdUniform4i;

    static UInt32 FuncIdUniform1f;
    static UInt32 FuncIdUniform2f;
    static UInt32 FuncIdUniform3f;
    static UInt32 FuncIdUniform4f;

    static UInt32 FuncIdUniform1iv;
    static UInt32 FuncIdUniform2iv;
    static UInt32 FuncIdUniform3iv;
    static UInt32 FuncIdUniform4iv;

    static UInt32 FuncIdUniform1fv;
    static UInt32 FuncIdUniform2fv;
    static UInt32 FuncIdUniform3fv;
    static UInt32 FuncIdUniform4fv;

    static UInt32 FuncIdUniformMatrix2fv;
    static UInt32 FuncIdUniformMatrix3fv;
    static UInt32 FuncIdUniformMatrix4fv;

    static UInt32 FuncIdGetUniformiv;
    static UInt32 FuncIdGetUniformfv;

    static UInt32 FuncIdProgramParameteri;
    static UInt32 FuncIdBindAttribLocation;

    /*---------------------------------------------------------------------*/

    struct ProgramIdPoolTag;

    typedef SimpleReusePool<Int32, 
                            ProgramIdPoolTag, 
                            SingleLockPolicy> ProgramIdPool;


    static ProgramIdPool *_pProgIdPool;

           UInt16         _uiProgId;

    /*---------------------------------------------------------------------*/

    // Variables should all be in ShaderProgramBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderProgram(void);
    ShaderProgram(const ShaderProgram &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderProgram(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

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

            void onCreate       (const ShaderProgram *source      = NULL);
            void onCreateAspect (const ShaderProgram *createAspect,
                                 const ShaderProgram *source      = NULL);
    virtual void onDestroy      (      UInt32         uiId              );
    
    virtual void onDestroyAspect(      UInt32         uiContainerId,
                                       UInt32         uiAspect          );

    virtual void resolveLinks   (      void                             );

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
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderProgramBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderProgram &source);
};

typedef ShaderProgram *ShaderProgramP;

OSG_END_NAMESPACE

#include "OSGShaderProgramBase.inl"
#include "OSGShaderProgram.inl"

#endif /* _OSGSHADERPROGRAM_H_ */
