/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGSHADERVARIABLEFUNCTOR_H_
#define _OSGSHADERVARIABLEFUNCTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableFunctorBase.h"
#include "OSGDrawEnv.h"

#include "boost/function.hpp"

OSG_BEGIN_NAMESPACE

class ShaderVariableAccess;

/*! \brief ShaderVariableFunctor class. See \ref 
           PageSystemShaderVariableFunctor for a description.
    \ingroup GrpSystemShaderVariables
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderVariableFunctor : 
    public ShaderVariableFunctorBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderVariableFunctorBase Inherited;

    typedef GLint (OSG_APIENTRY *GetUniformLocProc)(      GLuint  programObj,
                                                    const Char8  *name      );

    typedef boost::function<void (DrawEnv *, Int32        )> ProcVarFunctor;
    typedef boost::function<void (DrawEnv *, Int32, Node *)> ProcVarNodeFunctor;

#ifdef OSG_1_COMPAT
    typedef boost::function<void (GetUniformLocProc  ,
                                  DrawEnv           *,
                                  GLuint                 )> ParamFunctor;

    typedef boost::function<void (ShaderVariable  * const,
                                  DrawEnv         *      ,
                                  GLuint                 )> OSGParamFunctor;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details);

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

    void   setFunctor (ProcVarFunctor     pFunc    );
    void   setFunctor (ProcVarNodeFunctor pFunc    );
#ifdef OSG_1_COMPAT
    void   setFunctor (ParamFunctor       pPFunc   );
    void   setFunctor (OSGParamFunctor    pOSGPFunc);

    UInt32 getFuncMode(void                        );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual bool isProcedural(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void evaluate(DrawEnv           *pEnv,
                  Int32             &iLocation);

#ifdef OSG_1_COMPAT
    void evaluate(GetUniformLocProc  getULoc,
                  DrawEnv           *pEnv,
                  UInt32             uiProg   );

    void evaluate(ShaderVariable    *pVar,
                  DrawEnv           *pEnv,
                  UInt32             uiProg   );
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

#ifdef OSG_1_COMPAT
    UInt32             _uiFuncMode;

    ParamFunctor       _pPFunc;
    OSGParamFunctor    _pOSGPFunc;
#endif

    ProcVarFunctor     _pFunc;
    ProcVarNodeFunctor _pNodeFunc;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderVariableFunctor(void);
    ShaderVariableFunctor(const ShaderVariableFunctor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderVariableFunctor(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderVariableFunctorBase;

    friend class ShaderVariableAccess;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariableFunctor &source);
};

typedef ShaderVariableFunctor *ShaderVariableFunctorP;

OSG_END_NAMESPACE

#include "OSGShaderVariableFunctorBase.inl"
#include "OSGShaderVariableFunctor.inl"

#endif /* _OSGSHADERVARIABLEFUNCTOR_H_ */
