/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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
#ifndef _OSG_ErrorQuadTree_h
#define _OSG_ErrorQuadTree_h
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>

#include "OSGdctptypes.h"

OSG_BEGIN_NAMESPACE

class DCTPMesh;
class BezierTensorSurface;
class BSplineTensorSurface;
class DCTPFace;

#define OSG_DIFF_TO_BILIN
#define OSG_ONE_CHILD_PTR
#define OSG_USE_NURBS_PATCH
//#define OSG_CONSERVATIVE_ERROR
#define OSG_USE_KD_TREE
#define OSG_ARBITRARY_SPLIT

#ifdef OSG_ARBITRARY_SPLIT
 #ifndef OSG_USE_KD_TREE
  #define OSG_USE_KD_TREE
 #endif
#endif

struct SErrorTreeCell
{
    float fError;
#ifdef OSG_ONE_CHILD_PTR
    SErrorTreeCell *ptChildren;      // nw, ne, sw, se
#else
 #ifdef OSG_USE_KD_TREE
    SErrorTreeCell *aptChildren[2];        // n/w, s/e
 #else
    SErrorTreeCell *aptChildren[4];        // nw, ne, sw, se
 #endif
#endif
#ifdef OSG_USE_KD_TREE
 #ifdef OSG_ARBITRARY_SPLIT
    float fSplitValue;                  // <0 => horizontal; >0 => vertikal
 #else
    bool bSplitHoriz;
 #endif
#endif
};

#ifndef OSG_USE_NURBS_PATCH
struct SBPETreeCell
{
    float fError;
    float fPrevError;
    SBPETreeCell *aptChildren[4];          // nw, ne, sw, se / n, -, s, - / w, e, -, -
    unsigned int uiTop;
    unsigned int uiBottom;
    unsigned int uiLeft;
    unsigned int uiRight;
};
#endif

struct SFaceTreeCell
{
#ifdef OSG_USE_NURBS_PATCH
    BSplineTensorSurface *pclBSplineSurface;
    SErrorTreeCell *ptErrorCell;
#else
    BezierTensorSurface *pclBezierSurface;
    SErrorTreeCell *ptErrorCell;
    SBPETreeCell *ptBPCell;
#endif
    bool bOwnSurface;
/*#ifdef OSG_ARBITRARY_SPLIT
    Vec2d					clMin;
    Vec2d					clMax;
#endif*/
};

class OSG_DRAWABLE_DLLMAPPING CErrorQuadTree
{

  public:

    CErrorQuadTree();
    ~CErrorQuadTree();

/*#ifdef OSG_ARBITRARY_SPLIT
    void CalculatePoints( std::vector< Vec2d > *pvclInsert, std::vector< Vec2d > *pvclDelete,
                          BSplineTensorSurface *pclPatch,
                          float fError, float &rfMinError, float &rfMaxError );
#else*/
    void BuildMesh(DCTPMesh * pclMesh,
 #ifdef OSG_USE_NURBS_PATCH
                   BSplineTensorSurface * pclPatch,
  #ifdef OSG_ARBITRARY_SPLIT
                   const Vec2d cclMinParam, const Vec2d cclMaxParam,
  #endif
 #else
                   std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                   const std::vector<double> *cpvdIntervalsU,
                   const std::vector<double> *cpvdIntervalsV,
 #endif
                   float fError, float & rfMinError, float & rfMaxError);

    void WriteTree(std::ostream &rclFile);

    void ReadTree(std::istream &rclFile);

  private:

#ifdef OSG_ONE_CHILD_PTR
    void DeleteNode(SErrorTreeCell *pclNode);
#else
    void DeleteNode(SErrorTreeCell *&rpclNode);
#endif

    void SetInitialCells(DCTPMesh * pclMesh, float fError,
 #ifdef OSG_USE_NURBS_PATCH
  #ifdef OSG_ARBITRARY_SPLIT
                         BSplineTensorSurface * pclPatch,
                         const Vec2d cclMinParam, const Vec2d cclMaxParam);
  #else
                         BSplineTensorSurface * pclPatch);
  #endif
 #else
                         std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                         const std::vector<double> *cpvdIntervalsU,
                         const std::vector<double> *cpvdIntervalsV);
 #endif

    void SubdivideNode(DCTPMesh *pclMesh, DCTPFace *pclFace);

    void SubdivideBuild(DCTPMesh *pclMesh, DCTPFace *pclFace);

    void ComputeError(DCTPFace *pclFace);

#ifndef OSG_USE_NURBS_PATCH
    void ComputeBPTree(std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                       const std::vector<double>                     * cpvdIntervalsU,
                       const std::vector<double>                     * cpvdIntervalsV);

    void ComputeBPError(SBPETreeCell                                  * pclBPNode,
                        std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                        const std::vector<double>                     * cpvdIntervalsU,
                        const std::vector<double>                     * cpvdIntervalsV);

    void SubdivideBPTree(SBPETreeCell                                  * pclBPNode,
                         std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                         const std::vector<double>                     * cpvdIntervalsU,
                         const std::vector<double>                     * cpvdIntervalsV);

    void DeleteBPNode(SBPETreeCell *&rpclNode);
#endif

#ifndef OSG_DIFF_TO_BILIN
    double computeDistToPlane(const Vec3d cclP, const Vec3d cclV1, const Vec3d cclV2, const Vec3d cclV3);

    double computeDistToTriangle(const Vec3d cclP, const Vec3d cclV1, const Vec3d cclV2, const Vec3d cclV3);
#endif

    double computeDistToLine(const Vec3d cclP, const Vec3d cclV1, const Vec3d cclV2);

    float m_fMaxError;
#ifdef OSG_USE_NURBS_PATCH
    SErrorTreeCell* m_ptRoot;
#else
    std::vector<std::vector<SErrorTreeCell*> > m_vvptRoot;
    SBPETreeCell                              *m_ptBPRoot;
#endif

    float m_fErrorCutoff;

  public:
    static bool m_sbNormalApproximation;
};

OSG_END_NAMESPACE

#endif
