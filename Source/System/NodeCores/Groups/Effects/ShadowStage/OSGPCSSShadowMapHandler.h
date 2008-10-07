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

#ifndef _OSGPCSSSHADOWMAPHANDLER_H_
#define _OSGPCSSSHADOWMAPHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGShadowTreeHandler.h"

#include "OSGSHLVariableChunk.h"
#include "OSGTileCameraDecorator.h"
#include "OSGPolygonChunk.h"

OSG_BEGIN_NAMESPACE

class ShadowStage;
class TreeRenderer;

class OSG_EFFECTGROUPS_DLLMAPPING PCSSShadowMapHandler : 
    public ShadowTreeHandler
{
  public:

    typedef ShadowTreeHandler Inherited;

    PCSSShadowMapHandler (ShadowStage     *pSource,
                          ShadowStageData *pData  );

    ~PCSSShadowMapHandler(void);

    virtual void render(DrawEnv *pEnv);

  private:



    void createColorMapFBO       (DrawEnv *pEnv              );
    void createShadowFactorMapFBO(DrawEnv *pEnv,
                                  UInt32   num,
                                  UInt32   uiActiveLightCount);
    void createShadowMapsFBO     (DrawEnv *pEnv              );

    void configureShadowMaps     (void                       );


    SolidBackgroundUnrecPtr               _pClearSMapBack;
    PolygonChunkUnrecPtr                  _pPoly; 
    SHLChunkUnrecPtr                      _shadowSHL;
    Int32                                 _firstRun;

    std::vector<ChunkMaterialUnrecPtr>    _vShadowCmat;
    std::vector<SHLVariableChunkUnrecPtr> _vShadowSHLVar;
};

OSG_END_NAMESPACE

#endif /* _OSGPCSSSHADOWMAPHANDLER_H_ */

