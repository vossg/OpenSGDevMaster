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

#ifndef _OSGSTDSHADOWMAPHANDLER_H_
#define _OSGSTDSHADOWMAPHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGShadowTreeHandler.h"
#include "OSGTileCameraDecorator.h"
#include "OSGMatrixCameraDecorator.h"
#include "OSGPolygonChunk.h"

OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;
class DrawEnv;
class RenderAction;

/*! \ingroup GrpEffectsGroupsShadowTreeHandler
 */

class OSG_EFFECTGROUPS_DLLMAPPING StdShadowMapHandler : public ShadowTreeHandler
{
  public:
    
    typedef ShadowTreeHandler Inherited;

    StdShadowMapHandler(ShadowStage     *pSource,
                        ShadowStageData *pData  );
    ~StdShadowMapHandler(void);

    virtual void render(RenderAction *a,
                        DrawEnv      *pEnv);

  private:

    void createColorMapFBO       (RenderAction *a,
                                  DrawEnv      *pEnv);
    void createShadowMapsFBO     (RenderAction *a,
                                  DrawEnv      *pEnv);
    void createShadowFactorMapFBO(RenderAction *a,
                                  DrawEnv      *pEnv);

    TileCameraDecoratorUnrecPtr   _tiledeco;
    MatrixCameraDecoratorUnrecPtr _matrixDeco;
    BlendChunkUnrecPtr            _blender;
    ChunkMaterialUnrecPtr         _shadowCmat;
    SimpleSHLChunkUnrecPtr        _shadowSHL;
    SimpleSHLChunkUnrecPtr        _shadowCubeSHL;
    SimpleSHLChunkUnrecPtr        _shadowSHL2;
    SimpleSHLChunkUnrecPtr        _shadowSHL3;
    SimpleSHLChunkUnrecPtr        _shadowSHL4;
    SimpleSHLChunkUnrecPtr        _shadowSHL5;
    SimpleSHLChunkUnrecPtr        _shadowSHL6;
    SimpleSHLChunkUnrecPtr        _shadowSHL7;
    PolygonChunkUnrecPtr          _pPoly;
    Int32                         _firstRun;
};

OSG_END_NAMESPACE

#endif /* _OSGSTDSHADOWMAPHANDLER_H_ */

