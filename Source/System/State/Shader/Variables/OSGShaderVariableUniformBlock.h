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

#ifndef _OSGSHADERVARIABLEUNIFORMBLOCK_H_
#define _OSGSHADERVARIABLEUNIFORMBLOCK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableUniformBlockBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderVariableUniformBlock class. See \ref
           PageSystemShaderVariableUniformBlock for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderVariableUniformBlock : public ShaderVariableUniformBlockBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderVariableUniformBlockBase Inherited;
    typedef ShaderVariableUniformBlock     Self;

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

    // Variables should all be in ShaderVariableUniformBlockBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderVariableUniformBlock(void);
    ShaderVariableUniformBlock(const ShaderVariableUniformBlock &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderVariableUniformBlock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderVariableUniformBlockBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariableUniformBlock &source);
};

typedef ShaderVariableUniformBlock *ShaderVariableUniformBlockP;

OSG_END_NAMESPACE

#include "OSGShaderVariableUniformBlockBase.inl"
#include "OSGShaderVariableUniformBlock.inl"

#endif /* _OSGSHADERVARIABLEUNIFORMBLOCK_H_ */
