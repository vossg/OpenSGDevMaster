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

#ifndef _OSGPCF2SHADOWMAPHANDLER_H_
#define _OSGPCF2SHADOWMAPHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGShadowTreeHandler.h"
#include "OSGChunkBlock.h"
#include "OSGSimpleSHLVariableChunk.h"
#include "OSGMatrixCameraDecorator.h"
#include "OSGColorMaskChunk.h"
#include "OSGLightModelChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGShadeModelChunk.h"
#include "OSGPolygonChunk.h"

OSG_BEGIN_NAMESPACE

class ShadowStage;
class TreeRenderer;

/*! \ingroup GrpEffectsGroupsShadowTreeHandler
 */

class OSG_EFFECTGROUPS_DLLMAPPING PCF2ShadowMapHandler : public ShadowTreeHandler
{

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShadowTreeHandler Inherited;

    PCF2ShadowMapHandler (ShadowStage     *pSource,
                         ShadowStageData *pData  );
    ~PCF2ShadowMapHandler(void);

    virtual void render(RenderAction *a,
                        DrawEnv      *pEnv);

  private:
    // typedef std::vector<ChunkBlockUnrecPtr>  LightChunksStore;
    typedef std::vector<ChunkMaterialUnrecPtr>  LightChunksStore;

    void createColorMapFBO       (RenderAction *a,
                                  DrawEnv      *pEnv);
    void createShadowFactorMapFBO(RenderAction *a,
                                  DrawEnv      *pEnv);
    void createShadowMapsFBO     (RenderAction *a,
                                  DrawEnv      *pEnv);

    void doCreateShadowFactorMapFBO(DrawEnv *pEnv, UInt32 uiMatCount);

    LightChunksStore                      _shadowChunks;

    ColorMaskChunkUnrecPtr                _pColorMask;
    LightModelChunkUnrecPtr               _pLightModel;
    MaterialChunkUnrecPtr                 _pMaterial;
    ShadeModelChunkUnrecPtr               _pShadeModel;
    PolygonChunkUnrecPtr                  _pPoly;
    MatrixCameraDecoratorUnrecPtr         _matrixDeco;

    SimpleSHLChunkUnrecPtr                _shadowSHL;
    SimpleSHLChunkUnrecPtr                _shadowSHL2;
    SimpleSHLChunkUnrecPtr                _shadowSHL3;
    SimpleSHLChunkUnrecPtr                _shadowSHL4;
    SimpleSHLChunkUnrecPtr                _shadowCubeSHL;

    Int32                                 _firstRun;
    Real32                                _oldRange;
    
    SolidBackgroundUnrecPtr               _pClearColorBG;

    std::vector<SimpleSHLVariableChunkUnrecPtr> _vShadowSHLVar;
    std::vector<SimpleSHLVariableChunkUnrecPtr> _vShadowSHLVar2;
    std::vector<SimpleSHLVariableChunkUnrecPtr> _vShadowSHLVar3;
    std::vector<SimpleSHLVariableChunkUnrecPtr> _vShadowSHLVar4;

    std::vector<SimpleSHLVariableChunkUnrecPtr> _vShadowCubeSHLVar;
};

OSG_END_NAMESPACE

#endif /* _OSGPCF2SHADOWMAPHANDLER_H_ */
