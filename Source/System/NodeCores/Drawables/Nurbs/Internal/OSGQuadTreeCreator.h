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
#ifndef _OSG_QUADTREECREATOR_H_
#define _OSG_QUADTREECREATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"


#include <math.h>
#include <vector>
#include <stdlib.h>
#include "OSGBezierCurve2D.h"
#include "OSGBezierTensorSurface.h"
#include "OSGDCTPMesh.h"

OSG_BEGIN_NAMESPACE

class ParSpaceTrimmer;

class OSG_DRAWABLE_DLLMAPPING QuadTreeCreator
{

    friend class ParSpaceTrimmer;

//this class contains the algorithm to create a quadtree for the triangulation
//of a BezierTensorSurface matrix
//there is a constraint on the letters of the quadtree: their depth level should
//not differ more than 1 (it's a constraint to be able to triangulate easily)
  protected:
    DCTPMesh *qtm; //quadtreemesh
//	bool	m_bForTrimming;

    double error_epsilon;
    double computeApproximationError(DCTPFace *f);
    //returns error of triangualtion when creating an approximation of
    //a B.TensorSurf. with two triangles
    double computeBilinearNorm(DCTPFace *face);
    int    finishSubdivisions(DCTPFace *f);

  public:
    QuadTreeCreator(DCTPMesh * mesh /*, bool bForTrimming*/)
    {
        qtm = mesh;                                                        /*m_bForTrimming = bForTrimming;*/
    }
    ~QuadTreeCreator()
    {
        dctpfacevector::iterator fe = qtm->faces.end();

        for(dctpfacevector::iterator f = qtm->faces.begin(); f != fe; ++f)
            delete static_cast<BezierTensorSurface*>((*f)->faceinfo);
    }
    void setErrorTolerance(double epsilon)
    {
        error_epsilon = epsilon;
    }
    int setInitialLeaves(const beziersurfacematrix& patches,
                         const DCTPdvector&         intervals_u,
                         const DCTPdvector&         intervals_v); //sets starting leaves
    int  createQuadTree(void); //well... go figure
    void resetMesh(void);
};

OSG_END_NAMESPACE

#endif //QuadTreeCreator.h
