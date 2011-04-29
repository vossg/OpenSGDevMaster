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

#ifndef _OSGSHADERVARIABLEOSG_H_
#define _OSGSHADERVARIABLEOSG_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableOSGBase.h"

OSG_BEGIN_NAMESPACE

class ShaderVariableAccess;

/*! \brief ShaderVariableOSG class. See \ref 
           PageSystemShaderVariableOSG for a description.
    \ingroup GrpSystemShaderVariables
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING ShaderVariableOSG : public ShaderVariableOSGBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderVariableOSGBase Inherited;

    enum SHVOSGType
    {
        OSGUnknown     = 0,
        OSGWorldMatrix,
        OSGInvWorldMatrix,
        OSGTransInvWorldMatrix,
        OSGCameraOrientation,
        OSGCameraPosition,
        OSGViewMatrix,
        OSGInvViewMatrix,
        OSGProjectionMatrix,
        OSGModelViewMatrix,
#ifdef OSG_OGL_COREONLY
        OSGNormalMatrix,
        OSGModelViewProjectionMatrix,
#endif
        OSGStereoLeftEye,
        OSGDrawerId,
        OSGDrawableId,
        OSGNodeId,
        OSGNodeBoxMin,
        OSGNodeBoxMax,
        OSGNodeBoxCenter,
        OSGNodeWorldBoxMin,
        OSGNodeWorldBoxMax,
        OSGNodeWorldBoxCenter,
        OSGActiveLightsMask,
        OSGLight0Active,
        OSGLight1Active,
        OSGLight2Active,
        OSGLight3Active,
        OSGLight4Active,
        OSGLight5Active,
        OSGLight6Active,
        OSGLight7Active
    };


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

    virtual bool isProcedural(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void evaluate(DrawEnv *pEnv,
                  Int32   &iLocation);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderVariableOSG(void);
    ShaderVariableOSG(const ShaderVariableOSG &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderVariableOSG(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    void setName(const std::string &value);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderVariableOSGBase;

    friend class ShaderVariableAccess;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderVariableOSG &source);
};

typedef ShaderVariableOSG *ShaderVariableOSGP;

OSG_END_NAMESPACE

#include "OSGShaderVariableOSGBase.inl"
#include "OSGShaderVariableOSG.inl"

#endif /* _OSGSHADERVARIABLEOSG_H_ */
