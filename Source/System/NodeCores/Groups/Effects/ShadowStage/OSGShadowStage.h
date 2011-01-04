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

#ifndef _OSGSHADOWSTAGE_H_
#define _OSGSHADOWSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <utility>

#include "OSGShadowStageBase.h"

OSG_BEGIN_NAMESPACE

class ShadowStageData;

/*! \ingroup GrpEffectsGroupsShadowObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING ShadowStage : public ShadowStageBase
{

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShadowStageBase Inherited;

    enum Mode
    {
        NO_SHADOW=0,
        STD_SHADOW_MAP,
        PERSPECTIVE_SHADOW_MAP,
        DITHER_SHADOW_MAP,
        PCF_SHADOW_MAP,
        PCSS_SHADOW_MAP,
        VARIANCE_SHADOW_MAP
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details   );

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

    void triggerMapUpdate(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void checkLightsOcclusion(RenderActionBase *action);
    void drawOcclusionBB(const Pnt3f &bbmin, const Pnt3f &bbmax);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShadowStageBase.

    static UInt32 _extSHL;
    static UInt32 _extDepthTexture;
    static UInt32 _extShadows;
    static UInt32 _extFramebufferObject;
    static UInt32 _extDrawBuffers;

    static UInt32  FuncIdGenMipmaps;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShadowStage(void);
    ShadowStage(const ShadowStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShadowStage(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void onCreate (const ShadowStage *source        = NULL);
    void onDestroy(      UInt32       uiContainerId       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \{                                                                 */

    bool   _trigger_update;
    GLuint _occlusionQuery;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void checkLights     (RenderActionBase *action,
                          ShadowStageData  *pData );
    void updateLights    (RenderActionBase *action,
                          ShadowStageData  *pData );
    void initializeLights(RenderActionBase *action,
                          ShadowStageData  *pData );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    Action::ResultE findLight      (ShadowStageData *pData, Node * const node);
    Action::ResultE findTransparent(ShadowStageData *pData, Node * const node);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShadowStageBase;
    friend class TreeHandler;
    friend class StdShadowMapHandler;
    friend class PerspectiveShadowMapHandler;
    friend class DitherShadowMapHandler;
    friend class PCFShadowMapHandler;
    friend class VarianceShadowMapHandler;
    friend class PCSSShadowMapHandler;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShadowStage &source);
};

typedef ShadowStage *ShadowStageP;

OSG_END_NAMESPACE

#include "OSGShadowStageBase.inl"
#include "OSGShadowStage.inl"

#endif /* _OSGSHADOWSTAGE_H_ */
