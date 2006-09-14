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

#ifndef _OSGSIMPLESHADOWMAPENGINE_H_
#define _OSGSIMPLESHADOWMAPENGINE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSimpleShadowMapEngineBase.h"
#include "OSGLightEngineData.h"

#include "OSGCamera.h"
#include "OSGTextureChunk.h"
#include "OSGTextureBuffer.h"
#include "OSGLightChunk.h"
#include "OSGBlendChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGPolygonChunk.h"

#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShadowEngine is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpSystemNodeCoresMisc
*/

class OSG_RENDERTRAV_DLLMAPPING SimpleShadowMapEngine : 
    public SimpleShadowMapEngineBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    struct EngineData : public LightEngineData
    {
        typedef LightEngineData Inherited;

      private:

        CameraPtr        _pCamera;
        TextureChunkPtr  _pTexChunk;
        TextureBufferPtr _pTexBuffer;
        LightChunkPtr    _pLightChunk;
        BlendChunkPtr    _pBlendChunk;
        TexGenChunkPtr   _pTexGenChunk;
        PolygonChunkPtr  _pPolyChunk;

      public:

        EngineData(void);
        virtual ~EngineData(void);

        void             setCamera       (CameraPtr pCamera       );
        CameraPtr        getCamera       (void                    );

        void             setTextureChunk (TextureChunkPtr pChunk  );
        TextureChunkPtr  getTextureChunk (void                    );
        
        void             setTextureBuffer(TextureBufferPtr pBuffer);
        TextureBufferPtr getTextureBuffer(void                    );
        
        void             setLightChunk   (LightChunkPtr    pLight );
        LightChunkPtr    getLightChunk   (void                    );
        
        void             setBlendChunk   (BlendChunkPtr    pBlend );
        BlendChunkPtr    getBlendChunk   (void                    );
        
        void             setTexGenChunk  (TexGenChunkPtr   pTexGen);
        TexGenChunkPtr   getTexGenChunk  (void                    );
        
        void             setPolyChunk    (PolygonChunkPtr  pPoly  );
        PolygonChunkPtr  getPolyChunk    (void                    );
    };

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Render                                 */
    /*! \{                                                                 */

    virtual ActionBase::ResultE runOnEnter(LightPtr               pLight,
                                           LightTypeE             eType,
                                           RenderTraversalAction *pAction);
    virtual ActionBase::ResultE runOnLeave(LightPtr               pLight,
                                           LightTypeE             eType,
                                           RenderTraversalAction *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Helper                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SimpleShadowMapEngineBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleShadowMapEngine(void);
    SimpleShadowMapEngine(const SimpleShadowMapEngine &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleShadowMapEngine(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    void lightRenderEnter(LightPtr               pLight,
                          RenderTraversalAction *pAction);
    
    void setupCamera     (LightPtr               pLight,
                          LightTypeE             eType,
                          RenderTraversalAction *pAction,
                          EngineData            *pEngineData);
    void setupLightChunk (LightPtr               pLight,
                          LightTypeE             eType,
                          RenderTraversalAction *pAction,
                          EngineData            *pEngineData);

    void doLightPass     (LightPtr               pLight,
                          RenderTraversalAction *pAction,
                          EngineData            *pEngineData);
    void doAmbientPass   (LightPtr               pLight,
                          RenderTraversalAction *pAction,
                          EngineData            *pEngineData);
    void doFinalPass     (LightPtr               pLight,
                          RenderTraversalAction *pAction,
                          EngineData            *pEngineData);
                     
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class SimpleShadowMapEngineBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SimpleShadowMapEngine &source);
};

typedef SimpleShadowMapEngine              *SimpleShadowMapEngineP;

OSG_END_NAMESPACE

#include "OSGSimpleShadowMapEngineBase.inl"
#include "OSGSimpleShadowMapEngine.inl"

#define OSGSIMPLESHADOWMAPENGINE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSIMPLESHADOWMAPENGINE_H_ */
