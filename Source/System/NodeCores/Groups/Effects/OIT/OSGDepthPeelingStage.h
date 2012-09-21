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

#ifndef _OSGDEPTHPEELINGSTAGE_H_
#define _OSGDEPTHPEELINGSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDepthPeelingStageBase.h"
#include "OSGDepthPeelingStageDataFields.h"
#include "OSGDepthChunk.h"
#include "OSGBlendChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGShaderProgramVariableChunk.h"
#include "OSGBackground.h"
#include "OSGSolidBackground.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderAction;

/*! \brief DepthPeelingStage class. See \ref
           PageEffectGroupsDepthPeelingStage for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING DepthPeelingStage : public DepthPeelingStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DepthPeelingStageBase Inherited;
    typedef DepthPeelingStage     Self;

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

    // Variables should all be in DepthPeelingStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DepthPeelingStage(void);
    DepthPeelingStage(const DepthPeelingStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DepthPeelingStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebufferObjectExt;
    static UInt32 _uiFuncDrawBuffers;
    static UInt32 _uiDepthBufferFloatExt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void initData  (RenderAction *a,
                    Int32         iVPWidth,
                    Int32         iVPHeight);

    void updateData(RenderAction *a,
                    Int32         iVPWidth,
                    Int32         iVPHeight);

    void setupRenderScene(RenderAction* a,
                          Int32         iVPWidth,
                          Int32         iVPHeight,
                          bool          isInitial,
                          bool          isPing    );

    void setupPostProcess(RenderAction* a,
                          bool          isFinal,
                          bool          isPing  );
    void postProcess     (DrawEnv*      drawEnv,
                          bool          isPing  );
    void postProcessFinal(DrawEnv*      pEnv    );

    void drawQuad        (bool          isFinal );

    DepthPeelingStageDataTransitPtr
         setupStageData (Int32                  iPixelWidth,
                         Int32                  iPixelHeight);
    void resizeStageData(DepthPeelingStageData *pData,
                         Int32                  iPixelWidth,
                         Int32                  iPixelHeight);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DepthPeelingStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DepthPeelingStage &source);
};

typedef DepthPeelingStage *DepthPeelingStageP;

OSG_END_NAMESPACE

#include "OSGDepthPeelingStageBase.inl"
#include "OSGDepthPeelingStage.inl"

#endif /* _OSGDEPTHPEELINGSTAGE_H_ */
