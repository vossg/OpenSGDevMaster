/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGSHADOWMAPENGINE_H_
#define _OSGSHADOWMAPENGINE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGAction.h"
#include "OSGShadowMapEngineBase.h"
#include "OSGLightFields.h"
#include "OSGChunkMaterialFields.h"
#include "OSGTextureObjChunk.h"


OSG_BEGIN_NAMESPACE

class RenderAction;

/*! \brief ShadowMapEngine is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpGroupLightShadowBaseObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING ShadowMapEngine : public ShadowMapEngineBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Render                                 */
    /*! \{                                                                 */

    virtual ActionBase::ResultE runOnEnter(Light        *pLight,
                                           LightTypeE    eType,
                                           RenderAction *pAction) = 0;
    virtual ActionBase::ResultE runOnLeave(Light        *pLight,
                                           LightTypeE    eType,
                                           RenderAction *pAction) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ShadowMapEngineBase   Inherited;

    static ChunkMaterialUnrecPtr _pLightPassMat;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShadowMapEngine(void);
    ShadowMapEngine(const ShadowMapEngine &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShadowMapEngine(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    static void exitMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    static BitVector bvLightPassMask;
    static BitVector bvAmbientPassMask;
    static BitVector bvDiffusePassMask;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShadowMapEngineBase;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ShadowMapEngine &source);
};

typedef ShadowMapEngine *ShadowMapEngineP;

OSG_END_NAMESPACE

#include "OSGShadowMapEngineBase.inl"
#include "OSGShadowMapEngine.inl"

#endif /* _OSGSHADOWMAPENGINE_H_ */
