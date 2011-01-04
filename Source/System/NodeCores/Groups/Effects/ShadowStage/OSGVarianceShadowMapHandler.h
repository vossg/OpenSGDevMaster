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

#ifndef _OSGVARIANCESHADOWMAPHANDLER_H_
#define _OSGVARIANCESHADOWMAPHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGShadowTreeHandler.h"
#include "OSGSimpleSHLVariableChunk.h"
#include "OSGTileCameraDecorator.h"

OSG_BEGIN_NAMESPACE

class ShadowStage;
class TreeRenderer;

/*! \ingroup GrpEffectsGroupsShadowTreeHandler
 */

class OSG_EFFECTGROUPS_DLLMAPPING VarianceShadowMapHandler : 
    public ShadowTreeHandler
{
    /*==========================  PUBLIC  =================================*/

  public:
    
    typedef ShadowTreeHandler Inherited;

    VarianceShadowMapHandler (ShadowStage     *pSource,
                              ShadowStageData *pData  );

    ~VarianceShadowMapHandler(void);

    virtual void render(RenderAction *a,
                        DrawEnv      *pEnv);

  private:

    void createColorMapFBO       (RenderAction *a,
                                  DrawEnv      *pEnv              );
    void createShadowFactorMapFBO(RenderAction *a,
                                  DrawEnv      *pEnv,
                                  UInt32        num,
                                  UInt32        uiActiveLightCount);
    void createShadowMapsFBO     (RenderAction *a,
                                  DrawEnv      *pEnv              );

    void genMipMapCB             (DrawEnv *pEnv,
                                  UInt32   uiLightIdx             );

    void initShadowMaps          (void                            );
    void updateShadowMapSize     (void                            );
    void configureShadowMaps     (void                            );


    SolidBackgroundUnrecPtr               _pClearSMapBack;

    SimpleSHLChunkUnrecPtr                _shadowSHL;
    SimpleSHLChunkUnrecPtr                _depthSHL;
    Int32                                 _firstRun;

    std::vector<ChunkMaterialUnrecPtr         >    _vShadowCmat;
    std::vector<SimpleSHLVariableChunkUnrecPtr> _vShadowSHLVar;
    std::vector<ChunkMaterialUnrecPtr         >    _vDepthCmat;
    std::vector<SimpleSHLVariableChunkUnrecPtr> _vDepthSHLVar;
};

OSG_END_NAMESPACE

#endif /* _OSGVARIANCESHADOWMAPHANDLER_H_ */

