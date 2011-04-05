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

#ifndef _OSGSHADERVARIABLEACCESS_H_
#define _OSGSHADERVARIABLEACCESS_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include <string>

#include "OSGShaderProgramVariables.h"
#include "OSGShaderVariableOSG.h"
#include "OSGShaderVariableFunctor.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderVariableAccess class. 
    \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

class OSG_SYSTEM_DLLMAPPING ShaderVariableAccess 
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef ShaderVariableFunctor::ProcVarFunctor     ProcVarFunctor;
    typedef ShaderVariableFunctor::ProcVarNodeFunctor ProcVarNodeFunctor;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */
    
    ShaderVariableAccess(ShaderProgramVariables &oVariables);
    ~ShaderVariableAccess(void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */
  
    template<class VariableType, class ValueType> 
    bool addSVariable   (const Char8     *name, 
                         const ValueType &value,
                               MFInt32   *pVarLoc,
                               MFInt32   *pProcVarLoc);

    template<class VariableType, class ValueType> 
    bool updateSVariable(const Char8     *name, 
                         const ValueType &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    template<class VariableType, class ValueType> 
    bool addMVariable   (const char      *name, 
                         const ValueType &value,
                               MFInt32   *pVarLoc,
                               MFInt32   *pProcVarLoc);

    template<class VariableType, class ValueType> 
    bool updateMVariable(const char      *name, 
                         const ValueType &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    template<class VariableType, class ValueType> 
    bool getSVariable(const Char8 *name, ValueType &value);

    template<class VariableType, class ValueType> 
    bool getMVariable(const Char8 *name, ValueType &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    bool addVariableOSG          (const Char8              *name,
                                        MFInt32            *pProcVarLoc );

    template<class FunctorT>
    bool addProceduralVariable   (const Char8              *name, 
                                        FunctorT            pFunctor,
                                        UInt32              uiDependency,
                                        MFInt32            *pProcVarLoc );

    bool updateProceduralVariable(const Char8              *name, 
                                        ProcVarFunctor      pFunctor,
                                        UInt32              uiDependency);

    bool updateProceduralVariable(const Char8              *name, 
                                        ProcVarNodeFunctor  pFunctor,
                                        UInt32              uiDependency);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    void addVariable(      ShaderVariable *pVar       );

    bool subVariable(const Char8          *name,
                           MFInt32        *pVarLoc,
                           MFInt32        *pProcVarLoc);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    const ShaderVariable *getVariable(const Char8 *name) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    friend class ShaderProgramVariables;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariableAccess &source);

    void updateMap(void);

    ShaderProgramVariables &_oVariables;

    typedef std::pair<Int32, Int32> IntPair;

    typedef std::map<std::string, IntPair> VariableMap;

    typedef VariableMap::      iterator VariableIt;
    typedef VariableMap::const_iterator VariableConstIt;

    VariableMap _mVarMap;
    UInt32      _uiMapsize;
};

OSG_END_NAMESPACE

#include "OSGShaderVariableAccess.inl"

#endif /* _OSGSHADERVARIABLEACCESS_H_ */
