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

#ifndef _OSGPERSPECTIVESHADOWMAPHANDLER_H_
#define _OSGPERSPECTIVESHADOWMAPHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGShadowTreeHandler.h"
#include "OSGTileCameraDecorator.h"
#include "OSGMatrixCamera.h"
#include "OSGPolygonChunk.h"
#include "OSGMatrixCameraDecorator.h"

OSG_BEGIN_NAMESPACE

class ShadowStage;
class TreeRenderer;

/*! \ingroup GrpEffectsGroupsShadowTreeHandler
 */

class OSG_EFFECTGROUPS_DLLMAPPING PerspectiveShadowMapHandler : 
    public ShadowTreeHandler
{
  public:

    typedef ShadowTreeHandler Inherited;

    PerspectiveShadowMapHandler (ShadowStage     *pSource,
                                 ShadowStageData *pData  );
    ~PerspectiveShadowMapHandler(void);

    virtual void render(RenderAction *a,
                        DrawEnv      *pEnv);

  private:

    void createColorMapFBO       (RenderAction *a,
                                  DrawEnv      *pEnv);
    void createShadowMapsFBO     (RenderAction *a,
                                  DrawEnv      *pEnv);
    void createShadowFactorMapFBO(RenderAction *a,
                                  DrawEnv      *pEnv);

    /*----------------------------------------------------------------------*/


    void calcPerspectiveSpot (      Matrix             &_LPM, 
                                    Matrix             &_LVM, 
                                    UInt32              num,
                                    DrawEnv            *pEnv            );
    bool bbInsideFrustum     (      Pnt3f               sceneMin, 
                                    Pnt3f               sceneMax, 
                                    Matrix              LPVM            );
    void calcHull2           (      std::vector<Pnt3f> *points, 
                                    Matrix              invEyeProjMatrix, 
                                    Pnt3f               sceneMin, 
                                    Pnt3f               sceneMax, 
                                    Matrix              LPVM            );
    void calcUpVec2          (      Vec3f              &up99,
                                    Vec3f               viewDir,
                                    Vec3f               lightDir        );
    void calcCubicHull2      (      Pnt3f              &min99, 
                                    Pnt3f              &max99, 
                                    std::vector<Pnt3f> *points          );
    void scaleTranslateToFit2(      Matrix             &mat, 
                              const Pnt3f               vMin, 
                              const Pnt3f               vMax            ); 
    void calcBodyVec         (      Vec3f              &dir, 
                                    Pnt3f               eyePos, 
                                    std::vector<Pnt3f> *points          );
    bool pntInFrontOf        (      Pnt3f               p1, 
                                    Pnt3f               p2, 
                                    Pnt3f               p3, 
                                    Pnt3f               p               );

    /*----------------------------------------------------------------------*/

    void printMatrix(Matrix m);
    void printPoint (Pnt3f  p);

    /*----------------------------------------------------------------------*/

    std::vector<Matrix>           _perspectiveLPM;
    std::vector<Matrix>           _perspectiveLVM;

    TileCameraDecoratorUnrecPtr   _tiledeco;
    MatrixCameraDecoratorUnrecPtr _matrixDeco;
    BlendChunkUnrecPtr            _blender;
    MatrixCameraUnrecPtr          _matrixCam2;
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

#endif /* _OSGPERSPECTIVESHADOWMAPHANDLER_H_ */

