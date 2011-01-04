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

#ifndef _OSGDEFERREDSHADINGSTAGE_H_
#define _OSGDEFERREDSHADINGSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDeferredShadingStageBase.h"
#include "OSGDeferredShadingStageData.h"
#include "OSGFrameBufferObject.h"
#include "OSGLight.h"
#include "OSGShaderProgramChunk.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief DeferredShadingStage class. See \ref
           PageEffectGroupsDeferredShadingStage for a description.

    \ingroup GrpEffectsGroupsDeferredShadingObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING DeferredShadingStage : public DeferredShadingStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DeferredShadingStageBase Inherited;
    typedef DeferredShadingStage     Self;

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

    // Variables should all be in DeferredShadingStageBase.

    typedef DeferredShadingStageData            DSStageData;
    typedef DeferredShadingStageDataUnrecPtr    DSStageDataUnrecPtr;
    typedef DeferredShadingStageDataTransitPtr  DSStageDataTransitPtr;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DeferredShadingStage(void);
    DeferredShadingStage(const DeferredShadingStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DeferredShadingStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Render                                   */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    DSStageDataTransitPtr   createStageData(void           );
    TextureBufferTransitPtr createGBuffer  (UInt32 index,
                                            Int32  width,
                                            Int32  height  );

    void updateStageData (DSStageData        *data,
                          FrameBufferObject  *shadingTarget,
                          RenderPartition    *parentPart    );
    void updateGBuffer   (TextureBuffer      *buf,
                          UInt32              index,
                          Int32               width,
                          Int32               height        );
    void updateLightChunk(DSLightChunk       *lightChunk,
                          Light              *light         );

    void copyProgramChunk(ShaderProgramChunk *spcDest,
                          ShaderProgramChunk *spcSource     );

    void setupGBufferPartition(RenderPartition  *part,
                               RenderAction     *ract,
                               DSStageData      *data );
    void setupShadingPartition(RenderPartition  *part,
                               RenderAction     *ract,
                               DSStageData      *data );

    void            scheduleGBufferPass(RenderAction *ract   );
    void            scheduleShadingPass(RenderAction *ract   );
    Action::ResultE executeShadingPass (DrawEnv      *drawEnv);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DeferredShadingStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DeferredShadingStage &source);

    BitVector _changeCache;
    bool      _targetSizeChanged;
};

typedef DeferredShadingStage *DeferredShadingStageP;

OSG_END_NAMESPACE

#include "OSGDeferredShadingStageBase.inl"
#include "OSGDeferredShadingStage.inl"

#endif /* _OSGDEFERREDSHADINGSTAGE_H_ */
