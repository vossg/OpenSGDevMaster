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

#ifndef _OSGSHADERPROGRAMVARIABLES_H_
#define _OSGSHADERPROGRAMVARIABLES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderProgramVariablesBase.h"
#include "OSGShaderValueVariable.h"
#include "OSGVecMFields.h"
#include "OSGMathMFields.h"
#include "OSGShaderVariableFunctor.h"

OSG_BEGIN_NAMESPACE

class ShaderVariableAccess;

/*! \brief ShaderProgramVariables class. See \ref
           PageSystemShaderProgramVariables for a description.
    \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderProgramVariables : 
    public ShaderProgramVariablesBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderProgramVariablesBase                Inherited;
    typedef ShaderProgramVariables                    Self;

    typedef ShaderVariableFunctor::ProcVarFunctor     ProcVarFunctor;
    typedef ShaderVariableFunctor::ProcVarNodeFunctor ProcVarNodeFunctor;

#ifdef OSG_1_COMPAT
    typedef ShaderVariableFunctor::ParamFunctor       ParamFunctor;
    typedef ShaderVariableFunctor::OSGParamFunctor    OSGParamFunctor;
#endif

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

    const MFVariablesType           *getMFVariables          (void) const;
    const MFProceduralVariablesType *getMFProceduralVariables(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void addVariable    (ShaderVariable  * const value  );
    void subVariable    (UInt32                  uiIndex);
    void clearVariables (void                           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    const ShaderVariable *getVariable(const Char8 *name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void markAllChanged(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void addProceduralVariable   (ShaderVariable  * const value  );
    void subProceduralVariable   (UInt32                  uiIndex);
    void clearProceduralVariables(void                           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool addUniformVariable   (const Char8    *name,       
                                     bool      value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name,       
                                     Int32     value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name,       
                                     Real32    value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const Vec2f    &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const Vec3f    &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const Vec4f    &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const Matrix   &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const Pnt2f    &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const Pnt3f    &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFInt32  &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFReal32 &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFVec2f  &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFVec3f  &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFVec4f  &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFMatrix &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

#if 0
    bool addUniformVariable   (const Char8    *name, 
                               const MFPnt2f  &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);

    bool addUniformVariable   (const Char8    *name, 
                               const MFPnt3f  &value,
                                     MFInt32  *pVarLoc,
                                     MFInt32  *pProcVarLoc);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool updateUniformVariable(const Char8 *name,       bool      value);
    bool updateUniformVariable(const Char8 *name,       Int32     value);
    bool updateUniformVariable(const Char8 *name,       Real32    value);

    bool updateUniformVariable(const Char8 *name, const Vec2f    &value);
    bool updateUniformVariable(const Char8 *name, const Vec3f    &value);
    bool updateUniformVariable(const Char8 *name, const Vec4f    &value);
    bool updateUniformVariable(const Char8 *name, const Matrix   &value);
    bool updateUniformVariable(const Char8 *name, const Pnt2f    &value);
    bool updateUniformVariable(const Char8 *name, const Pnt3f    &value);
    bool updateUniformVariable(const Char8 *name, const MFInt32  &value);
    bool updateUniformVariable(const Char8 *name, const MFReal32 &value);
    bool updateUniformVariable(const Char8 *name, const MFVec2f  &value);
    bool updateUniformVariable(const Char8 *name, const MFVec3f  &value);
    bool updateUniformVariable(const Char8 *name, const MFVec4f  &value);
    bool updateUniformVariable(const Char8 *name, const MFMatrix &value);
#if 0
    bool updateUniformVariable(const Char8 *name, const MFPnt2f  &value);
    bool updateUniformVariable(const Char8 *name, const MFPnt3f  &value);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool getUniformVariable   (const Char8 *name,       bool     &value);
    bool getUniformVariable   (const Char8 *name,       Int32    &value);
    bool getUniformVariable   (const Char8 *name,       Real32   &value);
    bool getUniformVariable   (const Char8 *name,       Vec2f    &value);
    bool getUniformVariable   (const Char8 *name,       Vec3f    &value);
    bool getUniformVariable   (const Char8 *name,       Vec4f    &value);
    bool getUniformVariable   (const Char8 *name,       Matrix   &value);
    bool getUniformVariable   (const Char8 *name,       Pnt2f    &value);
    bool getUniformVariable   (const Char8 *name,       Pnt3f    &value);

    bool getUniformVariable   (const Char8 *name,       MFInt32  &value);
    bool getUniformVariable   (const Char8 *name,       MFReal32 &value);
    bool getUniformVariable   (const Char8 *name,       MFVec2f  &value);
    bool getUniformVariable   (const Char8 *name,       MFVec3f  &value);
    bool getUniformVariable   (const Char8 *name,       MFVec4f  &value);
    bool getUniformVariable   (const Char8 *name,       MFMatrix &value);
#if 0
    bool getUniformVariable   (const Char8 *name,       MFPnt2f  &value);
    bool getUniformVariable   (const Char8 *name,       MFPnt3f  &value);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool addOSGVariable              (const Char8              *name,
                                            MFInt32            *pProcVarLoc );

    bool addProceduralVariable       (const Char8              *name,
                                            ProcVarFunctor      pFunc,
                                            UInt32              uiDependency,
                                            MFInt32            *pProcVarLoc );

    bool addNodeProceduralVariable   (const Char8              *name,
                                            ProcVarNodeFunctor  pFunc,
                                            UInt32              uiDependency,
                                            MFInt32            *pProcVarLoc );

    bool updateProceduralVariable    (const Char8              *name,
                                            ProcVarFunctor      pFunc,
                                            UInt32              uiDependency);

    bool updateNodeProceduralVariable(const Char8              *name,
                                            ProcVarNodeFunctor  pFunc,
                                            UInt32              uiDependency);

#ifdef OSG_1_COMPAT
    bool addProceduralVariable       (const Char8              *name,
                                            ParamFunctor        pFunc,
                                            MFInt32            *pProcVarLoc );

    bool addProceduralVariable       (const Char8              *name,
                                            OSGParamFunctor     pFunc,
                                            MFInt32            *pProcVarLoc );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool subUniformVariable   (const Char8   *name,
                                     MFInt32 *pVarLoc,
                                     MFInt32 *pProcVarLoc);
                            
    void clearUniformVariables(void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void merge(ShaderProgramVariables *pVars,
               MFInt32                *pVarLoc,
               MFInt32                *pProcVarLoc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShaderProgramParametersBase.

    ShaderVariableAccess *_pVarAccess;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderProgramVariables(void);
    ShaderProgramVariables(const ShaderProgramVariables &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderProgramVariables(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreateAspect (const ShaderProgramVariables *createAspect,
                         const ShaderProgramVariables *source = NULL);
    
    void onDestroyAspect(      UInt32                  uiContainerId,
                               UInt32                  uiAspect     );

    void execSync       (      ShaderProgramVariables *pFrom,
                               ConstFieldMaskArg       whichField,
                               AspectOffsetStore      &oOffsets,
                               ConstFieldMaskArg       syncMode  ,
                         const UInt32                  uiSyncInfo   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    MFVariablesType           *editMFVariables          (void);
    MFProceduralVariablesType *editMFProceduralVariables(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ShaderVariableAccess;
    friend class FieldContainer;
    friend class ShaderProgramVariablesBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderProgramVariables &source);
};

typedef ShaderProgramVariables *ShaderProgramVariablesP;

OSG_END_NAMESPACE

#include "OSGShaderProgramVariablesBase.inl"
#include "OSGShaderProgramVariables.inl"

#endif /* _OSGSHADERVARIABLES_H_ */
