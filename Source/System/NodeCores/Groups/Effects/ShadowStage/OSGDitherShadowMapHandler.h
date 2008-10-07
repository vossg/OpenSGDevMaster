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

#ifndef _OSGDITHERSHADOWMAPHANDLER_H_
#define _OSGDITHERSHADOWMAPHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGShadowTreeHandler.h"
#include "OSGSHLVariableChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGMatrixCameraDecorator.h"

OSG_BEGIN_NAMESPACE

class ShadowStage;
class TreeRenderer;

class OSG_EFFECTGROUPS_DLLMAPPING DitherShadowMapHandler : 
    public ShadowTreeHandler
{
  public:

    typedef ShadowTreeHandler Inherited;

    DitherShadowMapHandler (ShadowStage     *pSource,
                            ShadowStageData *pData  );
    ~DitherShadowMapHandler(void);

    virtual void render(DrawEnv *pEnv);

  private:

    void createColorMapFBO       (DrawEnv *pEnv);
    void createShadowFactorMapFBO(DrawEnv *pEnv);
    void createShadowMapsFBO     (DrawEnv *pEnv);


    BlendChunkUnrecPtr                    _blender;
    MatrixCameraDecoratorUnrecPtr         _matrixDeco;

    std::vector<ChunkMaterialUnrecPtr>    _vShadowCmat;

    SHLChunkUnrecPtr                      _shadowSHL;
    SHLChunkUnrecPtr                      _shadowSHL2;
    SHLChunkUnrecPtr                      _shadowSHL3;
    SHLChunkUnrecPtr                      _shadowSHL4;
    SHLChunkUnrecPtr                      _shadowCubeSHL;
    PolygonChunkUnrecPtr                  _pPoly;

    Int32                                 _firstRun;

    std::vector<SHLVariableChunkUnrecPtr> _vShadowSHLVar;
    std::vector<SHLVariableChunkUnrecPtr> _vShadowSHLVar2;
    std::vector<SHLVariableChunkUnrecPtr> _vShadowSHLVar3;
    std::vector<SHLVariableChunkUnrecPtr> _vShadowSHLVar4;

    std::vector<SHLVariableChunkUnrecPtr> _vShadowCubeSHLVar;
};

OSG_END_NAMESPACE

#endif /* _OSGDITHERSHADOWMAPHANDLER_H_ */

