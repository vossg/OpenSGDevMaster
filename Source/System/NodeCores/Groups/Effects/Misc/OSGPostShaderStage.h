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

#ifndef _OSGPOSTSHADERSTAGE_H_
#define _OSGPOSTSHADERSTAGE_H_

#include "OSGPostShaderStageBase.h"

#include "OSGRenderAction.h"
#include "OSGPostShaderStageDataFields.h"
#include "OSGTextureObjChunkFields.h"
#include "OSGSimpleSHLChunk.h"

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief PostShaderStage class. See \ref
           PageEffectGroupsPostShaderStage for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING PostShaderStage : public PostShaderStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PostShaderStageBase Inherited;
    typedef PostShaderStage     Self;

    static const std::string ShaderSceneColorTexName;
    static const std::string ShaderSceneDepthTexName;
    static const std::string ShaderFBOWidthName;
    static const std::string ShaderFBOHeightName;
    static const std::string ShaderCameraNearName;
    static const std::string ShaderCameraFarName;
    static const std::string PrePassXName;
    static const std::string PostPassXColorTexName;
    static const std::string PostPassXColorWidthName;
    static const std::string PostPassXColorHeightName;

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
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebuffer_object_extension;
    static UInt32 _extDepthTexture;
    static UInt32 _uiFuncDrawBuffers;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Render Passes                              */
    /*! \{                                                                 */

    UInt32          getNumPasses (void) const;

    void            insertPass   (      UInt32       uiIndex,
                                  const std::string &szVertexProgram,
                                  const std::string &szFragmentProgram,
                                        Vec2f        vSize = Vec2f(1.0f, 1.0f));

    void            addPass      (const std::string &szVertexProgram,
                                  const std::string &szFragmentProgram,
                                        Vec2f        vSize = Vec2f(1.0f, 1.0f));

    void            clearPasses  (      void                                  );

    void            erasePass    (      UInt32       uiIndex                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Render Passes                              */
    /*! \{                                                                 */

    SimpleSHLChunk *getPassShader(UInt32 Index) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PostShaderStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PostShaderStage(void);
    PostShaderStage(const PostShaderStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PostShaderStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Stage init                                 */
    /*! \{                                                                 */

    void initData       (RenderAction        *pAction     );

    PostShaderStageDataTransitPtr 
         setupStageData (Int32                iPixelWidth,
                         Int32                iPixelHeight);

    void resizeStageData(PostShaderStageData *pData,
                         Int32                iPixelWidth,
                         Int32                iPixelHeight);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Process                                 */
    /*! \{                                                                 */

    void postProcess(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    
    class RenderPassData;

    typedef boost::shared_ptr<RenderPassData   > RenderPassDataPtr;
    typedef std::vector      <RenderPassDataPtr> RenderPassVector;

    class RenderPassData
    {
      public:

        static 
        RenderPassDataPtr create(
            const std::string         &       szVertexProgram,
            const std::string         &       szFragmentProgram,
                  bool                        bIsLastPass,
                  UInt32                      uiIndex,
                  Int32                       iPixelWidth,
                  Int32                       iPixelHeight,
                  PostShaderStageData *       pStageData,
            const Vec2f               &       vFBOSize,
                  TextureObjChunk     * const pSceneColorTex,
                  TextureObjChunk     * const pSceneDepthTex,
            const RenderPassVector    &       oPasses,
                  FrameBufferObject   * const pSceneFBO);
        
        /*----------------------------------------------------------------*/

        void updateUniformVariables(      RenderAction     *action      );
        void updateSize            (      Int32             iPixelWidth,
                                          Int32             iPixelHeight,
                                    const RenderPassVector &vPasses     );

        /*----------------------------------------------------------------*/

        void draw(DrawEnv             *       pEnv,
                  PostShaderStageData * const pStageData);

        /*----------------------------------------------------------------*/

        TextureObjChunk *getOutputTexture    (void) const;
        std::string      getOutputTextureName(void) const;
        std::string      getWidthName        (void) const;
        std::string      getHeightName       (void) const;
        bool             getIsLastPass       (void) const;
        SimpleSHLChunk  *getShader           (void) const;
        UInt32           getIndex            (void) const;

        /*----------------------------------------------------------------*/

      private:

        RenderPassData(const std::string         &       szVertexProgram,
                       const std::string         &       szFragmentProgram,
                             bool                        isLastPass,
                             UInt32                      uiIndex,
                             Int32                       iPixelWidth,
                             Int32                       iPixelHeight,
                             PostShaderStageData *       pStageData,
                       const Vec2f               &       vFBOSize,
                             TextureObjChunk     * const pSceneColorTex,
                             TextureObjChunk     * const pSceneDepthTex,
                       const RenderPassVector    &       vPasses,
                             FrameBufferObject   * const pSceneFBO);

        // prohibit default functions
        RenderPassData(const RenderPassData &);
        void operator=(const RenderPassData &);

        /*----------------------------------------------------------------*/

        SimpleSHLChunkUnrecPtr    _pShader;
        FrameBufferObjectUnrecPtr _pFBO;
        TextureObjChunkRecPtr     _pOutputTexture;
        bool                      _bIsLassPass;
        UInt32                    _uiIndex;
        Vec2f                     _vFBOSize;
        std::vector<UInt32>       _vWidthRefs;
        std::vector<UInt32>       _vHeightRefs;

        bool                      _bShaderHasSceneColorTex;
        bool                      _bShaderHasSceneDepthTex;
        bool                      _bShaderHasFBOWidth;
        bool                      _bShaderHasFBOHeight;
        bool                      _bShaderHasCameraNear;
        bool                      _bShaderHasCameraFar;
    };

    RenderPassVector        _vPostProcessPasses;
    TextureObjChunkUnrecPtr _pSceneTex;
    TextureObjChunkUnrecPtr _pSceneDepthTex;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PostShaderStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PostShaderStage &source);
};

typedef PostShaderStage *PostShaderStageP;

OSG_END_NAMESPACE

#include "OSGPostShaderStageBase.inl"
#include "OSGPostShaderStage.inl"

#endif /* _OSGPOSTSHADERSTAGE_H_ */
