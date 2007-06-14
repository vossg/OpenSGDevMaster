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

#ifndef _OSGSHADERPARAMETER_H_
#define _OSGSHADERPARAMETER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderParameterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameter class. See \ref 
    PageSystemShaderParameter for a description.
*/

class OSG_STATE_DLLMAPPING ShaderParameter : public ShaderParameterBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderParameterBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void addParent(
              FieldContainerPtrConst &parent, 
        const UInt16                  uiStoredInFieldId = InvalidParentEPos);

    void subParent(FieldContainerPtrConst &parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    bool hasChanged  (void);
    void resetChanged(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     TypeId's                                 */
    /*! \{                                                                 */

    enum SHPType
    {
        SHPTypeUnknown = 0,
        SHPTypeBool,
        SHPTypeInt,
        SHPTypeReal,
        SHPTypeVec2s,
        SHPTypeVec3s,
        SHPTypeVec4s,
        SHPTypeVec2f,
        SHPTypeVec3f,
        SHPTypeVec4f,
        SHPTypeMatrix,
        SHPTypeString,
        SHPTypeMBool,
        SHPTypeMInt,
        SHPTypeMReal,
        SHPTypeMVec2s,
        SHPTypeMVec3s,
        SHPTypeMVec4s,
        SHPTypeMVec2f,
        SHPTypeMVec3f,
        SHPTypeMVec4f,
        SHPTypeMMatrix,
        SHPTypeMString
    };

    enum SHPFlags
    {
        SHPFlagNone = 0,
        SHPFlagUpdate = 1
    };

    SHPType getTypeId(void);

    GLint getLocation(void);
    void  setLocation(GLint location);

    UInt32 getFlags(void);
    void  setFlags(UInt32 flags);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    bool    _changed;
    SHPType _typeid;
    GLint   _location;
    UInt32  _flags;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameter(void);
    ShaderParameter(const ShaderParameter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameter(void); 

    void setTypeId (SHPType type);
    void setChanged(void        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ShaderParameterBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderParameter &source);
};

typedef ShaderParameter *ShaderParameterP;

OSG_END_NAMESPACE

#include "OSGShaderParameterBase.inl"
#include "OSGShaderParameter.inl"

#endif /* _OSGSHADERPARAMETER_H_ */
