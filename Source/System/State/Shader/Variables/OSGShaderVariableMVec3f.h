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

#ifndef _OSGSHADERVARIABLEMVEC3F_H_
#define _OSGSHADERVARIABLEMVEC3F_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableMVec3fBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderVariableMVec3f class. See \ref 
           PageSystemShaderVariableMVec3f for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderVariableMVec3f : 
    public ShaderVariableMVec3fBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderVariableMVec3fBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShaderVariableMVec3fBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderVariableMVec3f(void);
    ShaderVariableMVec3f(const ShaderVariableMVec3f &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderVariableMVec3f(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    
    friend class FieldContainer;
    friend class ShaderVariableMVec3fBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariableMVec3f &source);
};

typedef ShaderVariableMVec3f *ShaderVariableMVec3fP;

OSG_END_NAMESPACE

#include "OSGShaderVariableMVec3fBase.inl"
#include "OSGShaderVariableMVec3f.inl"

#endif /* _OSGSHADERVARIABLEMVEC3F_H_ */
