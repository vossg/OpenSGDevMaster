/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGSHADERVARIABLESHADERSTORAGEBLOCK_H_
#define _OSGSHADERVARIABLESHADERSTORAGEBLOCK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableShaderStorageBlockBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderVariableShaderStorageBlock class. See \ref
           PageSystemShaderVariableShaderStorageBlock for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderVariableShaderStorageBlock : public ShaderVariableShaderStorageBlockBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderVariableShaderStorageBlockBase Inherited;
    typedef ShaderVariableShaderStorageBlock     Self;

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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShaderVariableShaderStorageBlockBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderVariableShaderStorageBlock(void);
    ShaderVariableShaderStorageBlock(const ShaderVariableShaderStorageBlock &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderVariableShaderStorageBlock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderVariableShaderStorageBlockBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariableShaderStorageBlock &source);
};

typedef ShaderVariableShaderStorageBlock *ShaderVariableShaderStorageBlockP;

OSG_END_NAMESPACE

#include "OSGShaderVariableShaderStorageBlockBase.inl"
#include "OSGShaderVariableShaderStorageBlock.inl"

#endif /* _OSGSHADERVARIABLESHADERSTORAGEBLOCK_H_ */
