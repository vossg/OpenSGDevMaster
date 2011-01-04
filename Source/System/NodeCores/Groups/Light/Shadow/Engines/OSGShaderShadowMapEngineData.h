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

#ifndef _OSGDSSHADOWMAPENGINEDATA_H_
#define _OSGDSSHADOWMAPENGINEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderShadowMapEngineDataBase.h"

#include "OSGFrameBufferObject.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"
#include "OSGChunkMaterial.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderShadowMapEngineData class. See \ref
           PageEffectGroupsShaderShadowMapEngineData for a description.

    \ingroup GrpGroupLightShadowEnginesObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
*/

class OSG_GROUP_DLLMAPPING ShaderShadowMapEngineData : 
    public ShaderShadowMapEngineDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderShadowMapEngineDataBase Inherited;
    typedef ShaderShadowMapEngineData     Self;

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

    // Variables should all be in ShaderShadowMapEngineDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderShadowMapEngineData(void);
    ShaderShadowMapEngineData(const ShaderShadowMapEngineData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderShadowMapEngineData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderShadowMapEngineDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderShadowMapEngineData &source);
};

typedef ShaderShadowMapEngineData *ShaderShadowMapEngineDataP;

OSG_END_NAMESPACE

#include "OSGShaderShadowMapEngineDataBase.inl"
#include "OSGShaderShadowMapEngineData.inl"

#endif /* _OSGDSSHADOWMAPENGINEDATA_H_ */
