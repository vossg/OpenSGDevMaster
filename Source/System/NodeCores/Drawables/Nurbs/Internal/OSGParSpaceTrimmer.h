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
#ifndef _OSG_PARSPACETRIMMER_H_
#define _OSG_PARSPACETRIMMER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>

#include <stdlib.h>
#include <iostream>
#include "OSGBezierCurve2D.h"
#include "OSGDCTPMesh.h"
#include "OSGDirectedGraph.h"
#include "OSGBSplineTensorSurface.h"

OSG_BEGIN_NAMESPACE

#ifdef OSG_WIN32_ICL
#pragma warning( disable : 171 )
#endif

#define OSG_ADAPTIVE_QUAD_TREE
//#define OSG_FORCE_NO_T_VERTICES
//#define OSG_KEEP_2D_POINTS
#define OSG_USE_SIMPLIFIER

//#include "NurbsPatchSurface.h"

#ifdef OSG_ADAPTIVE_QUAD_TREE
class QuadTreeCreator;
#endif

static const int ERR_NO_STARTING_FACE = -1;
static const int ERR_SET_MININTERSECTION = -2;
static const int ERR_DIRECTEDGE          = -3;
static const int ERR_STATETRANSITION_I   = -4;
static const int ERR_STATETRANSITION_II  = -5;
static const int ERR_NULL_END_NODE       = -6;
static const int ERR_NO_MERGECURVE_START = -7;
static const int ERR_NO_MERGECURVE_END   = -8;
static const int ERR_DEGENERATE_BEZIER   = -9;

#ifdef OSG_FORCE_NO_T_VERTICES
struct SPosNorm
{
    Vec3d clPos;
/* #ifndef OSG_CREATE_NORMAL_MAPS
        Vec3d			clNorm;
 #endif*/
 #ifdef OSG_KEEP_2D_POINTS
    unsigned int uiNum;
 #endif
};
#endif

class ParSpaceTrimmer;

class OSG_DRAWABLE_DLLMAPPING ParSpaceTrimmerError
{
  public:
    int errtype;

    inline ParSpaceTrimmerError(void);
    inline ParSpaceTrimmerError(int t);

    inline ~ParSpaceTrimmerError(void);
};


class OSG_DRAWABLE_DLLMAPPING TrimState
{
    friend class ParSpaceTrimmer;

    enum state_type
    {
        IN_VERTEX,
        OVER_FACE
    };

    state_type  state;
    DCTPFace   *f;
    DCTPVertex *v;
};

struct SScanLineEntry;

struct SScanLineEdge
{
    DCTPVertex *pclFromVertex;
    DCTPVertex *pclToVertex;
    SScanLineEdge *ptPrev;
    SScanLineEdge *ptNext;
    SScanLineEntry *ptEntry;
//	unsigned int	uiOrigNum;
    bool bInvalid;
};

struct SScanLineEntry
{
    SScanLineEdge *ptEdge;
    SScanLineEntry *ptPrev;
    SScanLineEntry *ptNext;
};

struct SScanLineEvent
{
    SScanLineEdge *ptEdge;
    bool bStart;
    Vec2d clPos;
    Vec2d clOther;
};

struct OSG_DRAWABLE_DLLMAPPING SScanLineEventLess
{
    inline bool operator() (const SScanLineEvent *ptEvent1,
                            const SScanLineEvent *ptEvent2) const;
};

typedef std::set<SScanLineEvent*, SScanLineEventLess> ScanLineEventSet;

#ifdef OSG_USE_SIMPLIFIER
struct SPolySimVertex
{
    unsigned int uiIndex;
    unsigned int uiPrev;
    unsigned int uiNext;
    Vec3d clPos;
    double dSimplifyError;
};

struct OSG_DRAWABLE_DLLMAPPING SPolySimVertexLess
{
    inline bool operator() (const SPolySimVertex *ptVertex1,
                            const SPolySimVertex *ptVertex2) const;
};

typedef std::set<SPolySimVertex*, SPolySimVertexLess> SPolySimVertexSet;
#endif

class OSG_DRAWABLE_DLLMAPPING ParSpaceTrimmer
{
  private:
    DCTPMesh                              *mesh;
    bezier2ddequevector                   *tcs;         //trimming curves
    bezier3ddequevector                   *tcs3d;       // 3d trimming curves
    double                                 terr;        // trimming error (used for 3d loops only!)
    TrimState                              state;
    DCTPFace                              *start_face;  //the face in which the curve starts (if it starts OVER_FACE)
    DCTPEdge                              *ie;          //last intersected edge
    double                                 ip;          //intersection parameter on bezier curve
    std::vector<std::vector<DCTPVertex*> > vcel;
    std::vector<std::vector<Vec2d> >      *pvccrd;
    std::vector<std::vector<Vec3d> >      *m_pvvclSewed;
#ifdef OSG_FORCE_NO_T_VERTICES
/* #ifndef OSG_CREATE_NORMAL_MAPS
        std::vector< std::vector< Vec3d > >		*m_pvvclNormals;
 #endif*/
 #ifdef OSG_KEEP_2D_POINTS
    unsigned int m_uiPosCnt;
 #endif
#endif
    bool  m_bDeleteVertexInfo;
    Vec2d m_clMin, m_clMax;
#ifdef OSG_ADAPTIVE_QUAD_TREE
    QuadTreeCreator *m_pclQuadTree;
#endif
    std::vector<bool> *m_pvbReversed;
    std::vector<bool> *m_pvbUsed;

#ifdef OSG_USE_SIMPLIFIER
    BSplineTensorSurface *m_pclNurbs;
#endif

    bool isOverQuad(DCTPFace *f, Vec2d &p);
    bool isNearQuad(DCTPFace *f, Vec2d &p);
    bool isOverFace(DCTPFace *f, Vec2d &p);

    void getStartingFace(Vec2d p);
    void initializeStartState(bezier2ddeque& tc);
    void initializeStartState2(unsigned int uiLoop, std::vector<DCTPVertex*> &el);

    void *isOnFaceBoundary(DCTPFace *f, Vec2d &p, bool &isedge);
    bool  isOnEdge(DCTPEdge *e, Vec2d &p, DCTPVertex* &v);
    bool  isOnSection(Vec2d &p1, Vec2d &p2, Vec2d &p);

    void processCurve(bezier2ddeque &tc, std::vector<DCTPVertex*> &el);
    void processCurve2(unsigned int uiLoop, std::vector<DCTPVertex*> &el);
    bool StateTransition(BezierCurve2D &b, std::vector<DCTPVertex*> &el);
#ifdef OSG_FORCE_NO_T_VERTICES
// #ifdef OSG_CREATE_NORMAL_MAPS
    bool StateTransition2(Vec2d &rclAct, Vec2d clNext, std::vector<DCTPVertex*> &el, Vec3d &rclActS, Vec3d clNextS);
/* #else
        bool StateTransition2( Vec2d &rclAct, Vec2d clNext, std::vector< DCTPVertex* > &el, Vec3d &rclActS, Vec3d clNextS, Vec3d &rclActN, Vec3d clNextN );
 #endif*/
#else
    bool StateTransition2(Vec2d &rclAct, Vec2d clNext, std::vector<DCTPVertex*> &el, Vec3d &rclActS, Vec3d clNextS);
#endif
    bool setMinIntersectionWithFace(BezierCurve2D &b);
    bool setMinIntersectionWithFace2(Vec2d clAct, Vec2d clNext);
    bool goingOutOnEdge(BezierCurve2D& bc, DCTPVertex *&v, bool &feu, std::vector<DCTPVertex*> &el);
    bool goingOutOnEdge2(Vec2d clAct, Vec2d clNext, DCTPVertex *&v, bool &feu, std::vector<DCTPVertex*> &el);
//        bool StoreCurveToFace( BezierCurve2D &bc, double t, DCTPVertex *v );
    bool            StoreCurveApproximation(BezierCurve2D &bc, double t, std::vector<DCTPVertex*> &el);
    DCTPFace*       getContinuingFace(BezierCurve2D &bc);
    DCTPFace*       getContinuingFace2(Vec2d clAct, Vec2d clNext);
    Vec2d           calcNormal(Vec2d &a, Vec2d &b);
    bool            checkEdgeNormals(DirectedGraph<Vec2d, unsigned char> &sg, int from, int to);
    void            checkEdgeloops(); //check for intersections/overlappings in edgeloops and remove them
    bool            insertScanLineEvents(SScanLineEdge *ptEdge, ScanLineEventSet &rsptEvents, char cWhich = -1); // ucWhich = -1 for both
    SScanLineEntry *insertInScanLine(SScanLineEntry *ptActEntry, SScanLineEntry *ptScanLine);
    void            saveLoop(SScanLineEdge *ptEdge);
    void            checkSLIntersection(SScanLineEntry *ptActEntry, ScanLineEventSet &rsptEvents);
    void            ScanLineIntersect(SScanLineEntry *ptEntry1, SScanLineEntry *ptEntry2, ScanLineEventSet &rsptEvents);
    bool            isSLEntryLess(SScanLineEdge *ptEdge1, SScanLineEdge *ptEdge2);
    void            removeSLEntry(SScanLineEntry *ptEntry, ScanLineEventSet &rsptEvents);
    DCTPVertex *    intersectsLoop(DCTPVertex *pclVertex1, DCTPVertex *pclVertex2, unsigned int uiLoop);
    bool            doIntersect(Vec2d clV1, Vec2d clV2, Vec2d clV3, Vec2d clV4, double &rdParam);
    void            deleteVertexInfo();
    bool            isLoopValid(const unsigned int cuiLoop);
    bool            intersectsRay(const Vec2d cclV1, const Vec2d cclV2, const Vec2d cclStart, const Vec2d cclEnd);

  public:
    inline ParSpaceTrimmer(void);
    inline ~ParSpaceTrimmer(void);

    void Initialize(DCTPMesh &m, bezier2ddequevector &c2d, bezier3ddequevector &c3d, std::vector<std::vector<Vec2d> > &vccrd, double err
#ifdef OSG_USE_SIMPLIFIER
                    , BSplineTensorSurface *pclNurbs
#endif
                    )
    {
//			std::cerr << "trim with err = " << err << std::endl;
        mesh   = &m;
        tcs    = &c2d;
        pvccrd = &vccrd;
        tcs3d  = &c3d;
        terr   = err;
        mesh->reinit();
#ifdef OSG_USE_SIMPLIFIER
        m_pclNurbs = pclNurbs;
#endif
    }
    void Initialize(DCTPMesh &m, bezier2ddequevector &tc, std::vector<std::vector<Vec2d> > &vccrd
#ifdef OSG_ADAPTIVE_QUAD_TREE
                    , QuadTreeCreator *pclQuadTree
#endif
#ifdef OSG_USE_SIMPLIFIER
                    , BSplineTensorSurface *pclNurbs
#endif
                    )
    {
        mesh       = &m;
        tcs        = &tc;
        pvccrd     = &vccrd;
        m_clMin[0] = m_clMax[0] = (*mesh->vertices.begin() )->coords[0];
        m_clMin[1] = m_clMax[1] = (*mesh->vertices.begin() )->coords[1];

        for(dctpvertexset::iterator it_vertex = mesh->vertices.begin(); it_vertex != mesh->vertices.end(); ++it_vertex)
        {
            (*it_vertex)->vertexinfo = reinterpret_cast<void*>(1);
            if( (*it_vertex)->coords[0] < m_clMin[0])
                m_clMin[0] = (*it_vertex)->coords[0];
            else if( (*it_vertex)->coords[0] > m_clMax[0])
                m_clMax[0] = (*it_vertex)->coords[0];
            if( (*it_vertex)->coords[1] < m_clMin[1])
                m_clMin[1] = (*it_vertex)->coords[1];
            else if( (*it_vertex)->coords[1] > m_clMax[1])
                m_clMax[1] = (*it_vertex)->coords[1];
        }

        m_clMin[0] += DCTP_EPS * 0.5;
        m_clMin[1] += DCTP_EPS * 0.5;
        m_clMax[0] -= DCTP_EPS * 0.5;
        m_clMax[1] -= DCTP_EPS * 0.5;
#ifdef OSG_ADAPTIVE_QUAD_TREE
        m_pclQuadTree = pclQuadTree;
#endif
#ifdef OSG_USE_SIMPLIFIER
        m_pclNurbs = pclNurbs;
#endif
//				m_bMaxLength = false;
        tcs3d = NULL;
    }

#ifdef OSG_FORCE_NO_T_VERTICES
// #ifdef OSG_CREATE_NORMAL_MAPS
    void Initialize2(DCTPMesh &m, std::vector<std::vector<Vec2d> > &vccrd, std::vector<std::vector<Vec3d> > &vvclSewed, std::vector<bool> &rvbRev, std::vector<bool> &rvbUsed)
/* #else
        void Initialize2( DCTPMesh &m, std::vector< std::vector< Vec2d > > &vccrd, std::vector< std::vector< Vec3d > > &vvclSewed, std::vector< std::vector< Vec3d > > &vvclNormals, std::vector< bool > &rvbRev, std::vector< bool > &rvbUsed )
 #endif*/
#else
    void Initialize2(DCTPMesh &m, std::vector<std::vector<Vec2d> > &vccrd, std::vector<std::vector<Vec3d> > &vvclSewed, std::vector<bool> &rvbRev, std::vector<bool> &rvbUsed)
#endif
    {
        mesh         = &m;
        tcs          = NULL;
        pvccrd       = &vccrd;
        m_pvvclSewed = &vvclSewed;
#ifdef OSG_FORCE_NO_T_VERTICES
/* #ifndef OSG_CREATE_NORMAL_MAPS
                m_pvvclNormals = &vvclNormals;
 #endif*/
#endif
        m_pvbReversed = &rvbRev;
        m_pvbUsed     = &rvbUsed;
        if(mesh->vertices.size() )
        {
            m_clMin[0] = m_clMax[0] = (*mesh->vertices.begin() )->coords[0];
            m_clMin[1] = m_clMax[1] = (*mesh->vertices.begin() )->coords[1];
        }

        for(dctpvertexset::iterator it_vertex = mesh->vertices.begin(); it_vertex != mesh->vertices.end(); ++it_vertex)
        {
            (*it_vertex)->vertexinfo = NULL;
            if( (*it_vertex)->coords[0] < m_clMin[0])
                m_clMin[0] = (*it_vertex)->coords[0];
            else if( (*it_vertex)->coords[0] > m_clMax[0])
                m_clMax[0] = (*it_vertex)->coords[0];
            if( (*it_vertex)->coords[1] < m_clMin[1])
                m_clMin[1] = (*it_vertex)->coords[1];
            else if( (*it_vertex)->coords[1] > m_clMax[1])
                m_clMax[1] = (*it_vertex)->coords[1];
        }

        m_clMin[0] += DCTP_EPS * 0.5;
        m_clMin[1] += DCTP_EPS * 0.5;
        m_clMax[0] -= DCTP_EPS * 0.5;
        m_clMax[1] -= DCTP_EPS * 0.5;
    }

    int PerformTrimming(void);
    int PerformTrimming2(void);
#ifdef OSG_FORCE_NO_T_VERTICES
 #ifdef OSG_KEEP_2D_POINTS
    int buildSurfaceGraph(DirectedGraph<Vec2d, unsigned char> *pGraph, std::vector<Vec3d> *pvclSewed = NULL, std::vector<Vec3d> *pvclNormals = NULL, std::vector<unsigned int> *pvclIdx = NULL);
 #else
    int buildSurfaceGraph(DirectedGraph<Vec2d, unsigned char> *pGraph, std::vector<Vec3d> *pvclSewed = NULL, std::vector<Vec3d> *pvclNormals = NULL);
 #endif
#else
    int  buildSurfaceGraph(DirectedGraph<Vec2d, unsigned char> *pGraph, std::vector<Vec3d> *pvclSewed = NULL);
    void getTrimmingLoops(std::vector<std::vector<Vec2d> > &rvvclTrimmingLoops);
#endif


#ifdef OSG_USE_SIMPLIFIER
    double DistToEdge(const Vec3d cclPoint, const Vec3d cclLine1, const Vec3d cclLine2) const;
#endif
};

#ifdef OSG_WIN32_ICL
#pragma warning( default : 171 )
#endif

OSG_END_NAMESPACE

#include <OSGParSpaceTrimmer.inl>

#endif
