/*---------------------------------------------------------------------------*\
 *                        OpenSG openNURBS SceneFileType                     *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2007-2008 by Seac02 S.r.l.     http://www.seac02.it         *
 * Copyright (C) 2008  by Patrik Mueller    muellerptr@users.sourceforge.net *
 * Copyright (C) 2008  by Akos Balazs       edhellon@cs.uni-bonn.de          *
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
/*
// Some portions are based on example_gl.h in the openNURBS distribution:
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//                
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#ifndef RHINO2OSB_H_
#define RHINO2OSB_H_

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic warning "-Wignored-qualifiers"
#endif

#include <string>
#include <map>

#include <opennurbs/opennurbs.h>
#include <OSGNode.h>
#include <OSGSimpleMaterial.h>
#include <OSGSurface.h>

class rhino2osb
{
  public:

    rhino2osb(int   curveInterpolationSteps = 100, 
              float tessError               = 0.1f, 
              bool  doTessellation          = true, 
              bool  importRenderMeshes      = false);

    virtual ~rhino2osb(void);

    OSG::NodeTransitPtr load(const OSG::Char8 *fileName);

  protected:

    void                doTess      (      OSG::Node *node);
    
    OSG::NodeTransitPtr process_brep(const ON_Brep   &);

    // optional transformation applied to curve
    OSG::NodeTransitPtr process_curve(const ON_Curve &,
                                            double[][4] = NULL);

    OSG::NodeTransitPtr process_surface( const ON_Surface& );

    OSG::NodeTransitPtr process_trimcurve( // low level NURBS curve render
            int,                // dim
            int,                // is_rat
            int,                // cv_count
            int,                // order
      const double *,           // knot_vector[]
            int,                // cv_stride
      const double *,           // cv
            int         = 1,    // bPermitKnotScaling - If TRUE, curve knots
                                // maybe rescaled to avoid knot vectors GL
                                // cannot handle. 
            double *    = NULL, // knot_scale[2] - If not NULL and
                                // bPermitKnotScaling, the scaling applied to
                                // the knot vector is returned here.
            double[][4] = NULL // optional transformation applied to curve
                                         );

    OSG::NodeTransitPtr process_NURBS_surface( 
        const ON_NurbsSurface &,
              int               = 1,       // bPermitKnotScaling - If TRUE,
                                           // surface knots may be rescaled to
                                           // avoid knot vectors GL cannot
                                           // handle. 
        double                * = NULL,    // knot_scale0[2] - If not NULL and
                                           // bPermitKnotScaling, the scaleing
                                           // applied to the first parameter
                                           // is returned here.
        double                * = NULL     // knot_scale0[2] - If not NULL and
                                           // bPermitKnotScaling, the scaleing
                                           // applied to the second parameter
                                           // is returned here.
                                             );

    OSG::NodeTransitPtr process_brepface(const ON_BrepFace &);

    OSG::NodeTransitPtr convert_knots( 
          const int,             // order, ON_NurbsCurve... order
          const int,             // cv_count, ON_NurbsCurve... cv count
          const double  *,       // knot, ON_NurbsCurve... knot vector
                GLfloat *,       // glknot[] - GL knot vector
                int       = 0,   // bPermitScaling - TRUE if re-scaling is
                                 // allowed 
                double  * = NULL // scale[2] - If not NULL and bPermitScaling is
                                 // TRUE, then the scaling parameters are
                                 // returned here. 
                                 // ( glknot = (knot = scale[0])*scale[1] )
                                     );

    void process_material                     (const ONX_Model        &model,
                                                     int               index );


    OSG::NodeTransitPtr buildNode             (const ONX_Model        &model, 
                                                     int               index );
    OSG::NodeTransitPtr convert_surface_to_osg(const ON_NurbsSurface  &s, 
                                                     GLfloat          *sknot, 
                                                     GLfloat          *tknot );
    OSG::NodeTransitPtr process_point         (const ON_Point         *theGeo);
    OSG::NodeTransitPtr process_pointcloud    (const ON_PointCloud    *theGeo);
    OSG::NodeTransitPtr process_pointgrid     (const ON_PointGrid     *theGeo);
    OSG::NodeTransitPtr process_points        (const ON_Geometry      *theGeo);
    OSG::NodeTransitPtr process_curve         (const ON_Geometry      *theGeo);
    OSG::NodeTransitPtr process_nurbscurve    (const ON_NurbsCurve    *theGeo);
    OSG::NodeTransitPtr process_linecurve     (const ON_LineCurve     *theGeo);
    OSG::NodeTransitPtr process_polylinecurve (const ON_PolylineCurve *theGeo);
    OSG::NodeTransitPtr process_mesh          (const ON_Mesh          *theGeo);


    // member variables
    OSG::NodeUnrecPtr           m_pRootNode;
    OSG::SimpleMaterialUnrecPtr m_actMaterial;
    OSG::SurfaceUnrecPtr        m_cCurrentSurface;
    bool                        m_bNewTrimLoop;

    // member variables that influence the loading/conversion
    int   m_curveInterpolationSteps;
    float m_tessellationError;
    bool  m_bDoTessellation;
    bool  m_bImportRenderMeshes;

    std::map<int, OSG::SimpleMaterialUnrecPtr> m_materials;
};
#endif // RHINO2OSB_H_
