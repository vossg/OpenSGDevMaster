/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#ifndef _OSGFOGSTAGE_H_
#define _OSGFOGSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFogStageBase.h"
#include "OSGAction.h"
#include "OSGFogStageDataFields.h"
#include "OSGTextureObjChunkFields.h"
#include "OSGSimpleSHLChunkFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief FogStage class. See \ref
           PageEffectGroupsFogStage for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING FogStage : public FogStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FogStageBase Inherited;
    typedef FogStage     Self;

    enum FogModes
    {
        FOG_MODE_LINEAR = 1,
        FOG_MODE_EXP    = 2,
        FOG_MODE_EXP2   = 3
    };

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Process                                 */
    /*! \{                                                                 */

    void postProcess(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    void initData(Viewport         *pViewport,
                  RenderActionBase *pAction  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebuffer_object_extension;
    static UInt32 _extDepthTexture;
    static UInt32 _uiFuncDrawBuffers;

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

    FogStageDataTransitPtr setupStageData (Int32         iPixelWidth,
                                           Int32         iPixelHeight);

    void                   resizeStageData(FogStageData *pData,
                                           Int32         iPixelWidth,
                                           Int32         iPixelHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    SimpleSHLChunkTransitPtr generateFogFragmentProgram(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FogStageBase.

    SimpleSHLChunkUnrecPtr _pFogShader;
    TextureObjChunkRecPtr  _pSceneTex;
    TextureObjChunkRecPtr  _pSceneDepthTex;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FogStage(void);
    FogStage(const FogStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FogStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FogStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FogStage &source);
};

typedef FogStage *FogStageP;

OSG_END_NAMESPACE

#include "OSGFogStageBase.inl"
#include "OSGFogStage.inl"

#endif /* _OSGFOGSTAGE_H_ */
