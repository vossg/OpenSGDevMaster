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

#ifndef _OSGSHADERVARIABLE_H_
#define _OSGSHADERVARIABLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableBase.h"

OSG_BEGIN_NAMESPACE

class ShaderVariableAccess;

/*! \brief ShaderParameter class. See \ref 
           PageSystemShaderParameter for a description.
    \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderVariable : public ShaderVariableBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderVariableBase Inherited;

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

    const std::string &getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual bool isProcedural(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     TypeId's                                 */
    /*! \{                                                                 */

    enum SHVType
    {
        SHVTypeUnknown = 0,
        SHVTypeBool,
        SHVTypeInt,
        SHVTypeReal,
        SHVTypeVec2s,            // missing
        SHVTypeVec3s,            // missing
        SHVTypeVec4s,            // missing
        SHVTypeVec2f,
        SHVTypeVec3f,
        SHVTypeVec4f,
        SHVTypePnt2f,
        SHVTypePnt3f,
        SHVTypeMatrix,
        SHVTypeString,           // missing
        SHVTypeMBool,            // missing
        SHVTypeMInt,
        SHVTypeMReal,
        SHVTypeMVec2s,           // missing
        SHVTypeMVec3s,           // missing
        SHVTypeMVec4s,           // missing
        SHVTypeMVec2f,
        SHVTypeMVec3f,
        SHVTypeMVec4f,
        SHVTypeMMatrix,
        SHVTypeMString,          // missing
        SHVTypeOSG,
        SHVTypeFunctor
    };

    enum SHVFlags
    {
        SHVFlagNone = 0,
        SHVFlagUpdate = 1
    };

    SHVType getTypeId(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    SHVType _typeid;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderVariable(void);
    ShaderVariable(const ShaderVariable &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderVariable(void); 

    void setTypeId (SHVType type);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderVariableBase;

    friend class ShaderVariableAccess;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariable &source);
};

typedef ShaderVariable *ShaderVariableP;

OSG_END_NAMESPACE

#include "OSGShaderVariableBase.inl"
#include "OSGShaderVariable.inl"

#endif /* _OSGSHADERVARIABLE_H_ */
