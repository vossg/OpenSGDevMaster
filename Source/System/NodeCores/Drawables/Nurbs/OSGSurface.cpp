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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>


#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"
#include "OSGSimpleMaterial.h"
#include "OSGFatBorderChunk.h"

#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#include "OSGGeoFunctions.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"

#include "OSGSurface.h"

/*
#ifdef OSG_USE_ATI
#  include <GL/glx.h>
#  include <GL/glext.h>
#  include <GL/glATI.h>
#endif
*/

#include <boost/bind.hpp>

#include "OSGBSplineTrimmedSurface.h"
#include "OSGNurbsPatchSurface.h"
#include "OSGSimplePolygon.h"

#include "OSGpredicates.h" //for exactinit()

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector Surface::CurveFieldMask =
    (Surface::NumCurvesFieldMask |
     Surface::KnotLengthsFieldMask |
     Surface::DimensionsFieldMask |
     Surface::CurveControlPointsFieldMask |
     Surface::KnotsFieldMask |
     Surface::CurvesPerLoopFieldMask);

const OSG::BitVector Surface::SurfaceFieldMask =
    (Surface::DimUFieldMask |
     Surface::DimVFieldMask |
     Surface::KnotsUFieldMask |
     Surface::KnotsVFieldMask |
     Surface::ControlPointsFieldMask |
     Surface::ErrorFieldMask |
     Surface::IsDelaunayFieldMask |
     Surface::TextureControlPointsFieldMask);


/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Surface::Surface(void) :
    Inherited()
{
//    std::cerr<<"constructor"<<std::endl;
    _trimmedSurface = NULL;
    _surfacePatch   = NULL;
}

//! Copy Constructor

Surface::Surface(const Surface &source) :
    Inherited(source)
{
    // We need these for every class and every aspect, so we have to
    // allocate them here.
    _trimmedSurface = new BSplineTrimmedSurface;
    _surfacePatch   = new CNurbsPatchSurface;
}

//! Destructor

Surface::~Surface(void)
{
    delete _trimmedSurface;
    delete _surfacePatch;
}


/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Surface::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::renderActionEnterHandler));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::renderActionLeaveHandler));

        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::intersect));

        // init robust predicates
        ::exactinit();

        // turn appearance preserving tessellation on
        CErrorQuadTree::m_sbNormalApproximation = true;
    }
}

//! react to field changes

void Surface::changed(ConstFieldMaskArg whichField,
                      UInt32            origin,
                      BitVector         detail)
{
    if( (whichField & DimUFieldMask) ||
        (whichField & DimVFieldMask) ||
        (whichField & KnotsUFieldMask) ||
        (whichField & KnotsVFieldMask) ||
        (whichField & ControlPointsFieldMask) ||
        (whichField & NumCurvesFieldMask) ||
        (whichField & KnotLengthsFieldMask) ||
        (whichField & DimensionsFieldMask) ||
        (whichField & CurveControlPointsFieldMask) ||
        (whichField & KnotsFieldMask) ||
        (whichField & CurvesPerLoopFieldMask) ||
        (whichField & TextureControlPointsFieldMask) )
    {
        editDirtyMask() |= TESSELLATE;

        Window::refreshGLObject(getSurfaceGLId());
    }
    else if( (whichField & ErrorFieldMask) ||
             (whichField & IsDelaunayFieldMask) )
    {
        editDirtyMask() |= RETESSELLATE;

        Window::refreshGLObject(getSurfaceGLId());
    }

    // you should call the parent's changed() function in case
    // it needs to update inherited fields.
    Inherited::changed(whichField, origin, detail);
//    std::cerr<<"Surface::changed:   texcoords ptr: " << getTexCoords() << std::endl;
//    std::cerr<<"Surface::changed:   texcoords1 ptr: " << getTexCoords1() << std::endl;

}


//! get desired error.
/*
 *  This should be called from the user program once per frame for every
 *  patch. This returns the patch's desired error level for the
 * dynamic LOD balancing.
 */
Real64 Surface::getDesiredError(Pnt3f viewPos, Real64 halfPixelSize)
{
    Vec3f  dist;
    Real64 distance;

    findClosestPoint(dist, viewPos);
    distance = dist.squareLength();

/*    if( distance < _max.dist2( _min ) )
    {
        findClosestPointExact( dist, viewPos );
        distance = dist.squareLength( );
    }*/

    distance = osgSqrt(distance);
    // multiply the length of a line at distance one that projects
    // to half a pixel with the distance of the current BB to get
    // the maximum geometric error that is allowed for the surface
    // within the BB
    Real64 desired_error = halfPixelSize * distance;

//  std::cerr << distance << " " << desired_error << std::endl;

    if(desired_error < _max.dist(_min) * 0.001)     // 0.1% of bounding box
    {
//          printf( "error below minimum => setting to minimal error %f\n", _max.dist( _min ) * 0.001 );
        desired_error = _max.dist(_min) * 0.001;
    }

    return desired_error;
}

//! update error field according to dynamic LOD
/*
 *  This should becalled from the render() function in order
 *  to only call this for nodes that are not culled.
 *
 */
bool Surface::updateError(Pnt3f viewPos, Real64 halfPixelSize)
{
    Real64 d_max_error = getDesiredError(viewPos, halfPixelSize);

    // FIXME: this will convert the surface data once again,
    // not very effective... should only be retessellated !!!
    // FIXME: do we have to change the error in every frame ???
    Real32 current_error = getError();
    if(d_max_error < current_error)
    {
        std::cerr << "retessellating due to too high error: " << d_max_error
                  << " " << current_error << std::endl;
//        Real32 new_error = osgMin(d_max_error, current_error / 2.0);

        setError(d_max_error / 2.0);
    }
    else if(d_max_error > current_error * 4.0)
    {
        std::cerr << "retessellating due to too low error: " << d_max_error
                  << " " << current_error << std::endl;

        setError(d_max_error / 2.0);
    }
    return true;
}


// protected


/* given an set of arbitrary bounding volumes
 * find the vector to the point on the volume that is closest to the view pos
*/
void Surface::findClosestPoint(Vec3f& rDist, const Pnt3f viewPos) const
{
    const UInt32 parent_cnt = getParents().size();
    UInt32       parent_idx;
    Real64       min_dist = 1e300;
    Vec3f        temp_dist;
    Real64       curr_dist;

    for(parent_idx = 0; parent_idx < parent_cnt; ++parent_idx)
    {
        Node            *parent = dynamic_cast<Node *>(getParents()[0]);
        const BoxVolume &bVol   = parent->getVolume();

        Pnt3f bb_min;
        Pnt3f bb_max;

        bVol.getBounds(bb_min, bb_max);

        if(viewPos[0] < bb_min[0])
        {
            temp_dist[0] = viewPos[0] - bb_min[0];
        }
        else if(viewPos[0] > bb_max[0])
        {
            temp_dist[0] = viewPos[0] - bb_max[0];
        }
        else
        {
            temp_dist[0] = 0.0;
        }

        if(viewPos[1] < bb_min[1])
        {
            temp_dist[1] = viewPos[1] - bb_min[1];
        }
        else if(viewPos[1] > bb_max[1])
        {
            temp_dist[1] = viewPos[1] - bb_max[1];
        }
        else
        {
            temp_dist[1] = 0.0;
        }

        if(viewPos[2] < bb_min[2])
        {
            temp_dist[2] = viewPos[2] - bb_min[2];
        }
        else if(viewPos[2] > bb_max[2])
        {
            temp_dist[2] = viewPos[2] - bb_max[2];
        }
        else
        {
            temp_dist[2] = 0.0;
        }

        curr_dist = temp_dist.squareLength();

        if(curr_dist < min_dist)
        {
            min_dist = curr_dist;
            rDist    = temp_dist;
        }
    }
}


void Surface::findClosestPointExact(Vec3f& rDist, const Pnt3f viewPos) const
{
//  const GeoPositions3fPtr cpcl_points = GeoPositions3fPtr::dcast( cpcl_geo->getPositions( ) );
    const GeoPnt3fProperty *cpcl_points =
        dynamic_cast<const GeoPnt3fProperty *>(getPositions());
    const unsigned int      cui_idx_cnt = cpcl_points->getSize();
    Pnt3f                   cl_pos;
    unsigned int            ui_idx;
    Vec3f                   cl_temp;
    double                  d_min = DBL_MAX;
    double                  d_temp;

    for(ui_idx = 0; ui_idx < cui_idx_cnt; ++ui_idx)
    {
        cl_pos  = cpcl_points->getValue(ui_idx);
        cl_temp = cl_pos - viewPos;
        d_temp  = cl_temp.squareLength();
        if(d_temp <= d_min)
        {
            d_min = d_temp;
            rDist = cl_temp;
        }
    }
}


//! tessellate
void Surface::tessellate(void)
{
    // local variables for tessellation
//    BSplineTrimmedSurface _trimmedSurface;  // internal representation of surface
//    CNurbsPatchSurface cpatch;              // "tessellator" object
//    simplepolygonvector tris;               // resulting indexed triangle set
    std::vector<SimplePolygon> tris;
    std::vector<Pnt3f>         gverts;      // resulting vertices
    std::vector<Vec3f>         norms;       // resulting surface normals
    std::vector<Pnt2f>         texturecoords; // resulting texture coordinates

    Int32 err = convertSurface();
    if(err)
    {
//        exit(-1);
        return;
    }
    if(_sfTextureControlPoints.getValue() == NULL)
    {
        err = tessellateSurface(tris, gverts, norms);
#ifdef OSG_NURBS_DEBUG
        std::cerr << "Surface::tessellate err1: " << err << " #tris: " << tris.size() << std::endl;
#endif /* OSG_NURBS_DEBUG */
        if(err)
            return;
        buildSurface(tris, gverts, norms, texturecoords);
    }
    else
    {
/*
        // fragment program stuff (no normals)
        err = tessellateSurface( tris, gverts, texturecoords );
        if ( err ) return;
        (void) buildSurface( tris, gverts, texturecoords );
*/
        // classic texturemapping stuff (both normals and texcoords)
        err = tessellateSurface(tris, gverts, norms, texturecoords);
#ifdef OSG_NURBS_DEBUG
        std::cerr << "Surface::tessellate err2: " << err << " #tris: " << tris.size() << std::endl;
#endif /* OSG_NURBS_DEBUG */
        if(err)
            return;
        buildSurface(tris, gverts, norms, texturecoords);
    }

    // invalidate the volume cache -- strictly speaking this is only needed
    // for rational surfaces
    _volumeCache.setEmpty();

//        std::cerr<<"Surface::tessellate:   texcoords ptr: " << getTexCoords() << std::endl;
//        std::cerr<<"Surface::tessellate:   texcoords1 ptr: " << getTexCoords1() << std::endl;

//    buildPointSet();
//    SLOG << "tessellate NI" << endLog;
}

//! retessellate
void Surface::reTessellate(void)
{
    std::vector<SimplePolygon> tris;
    std::vector<Pnt3f>         gverts;      // resulting vertices
    std::vector<Vec3f>         norms;       // resulting surface normals
    std::vector<Pnt2f>         texturecoords; // resulting texture coordinates


    //FIXMEZ0RZ:
//    _surfacePatch->setSurface( _trimmedSurface );
    if(getError() < DCTP_EPS)
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//              endLog;
        setError(0.2f);
    }

    _surfacePatch->setError(getError() );
//    SSurface *surfdata = _surfacePatch->getSurfaceData();

    if(_sfTextureControlPoints.getValue() == NULL)
    {
        _surfacePatch->getTessellation(gverts, norms, tris, getIsDelaunay());
        buildSurface(tris, gverts, norms, texturecoords);
    }
    else
    {
/*
        //normalmap stuff
        _surfacePatch->getTessellation( gverts, texturecoords, tris, getIsDelaunay() );
        (void) buildSurface( tris, gverts, texturecoords );
*/

        //classic texturemapped stuff
        _surfacePatch->getTessellation(gverts, norms, texturecoords,
                                       tris, getIsDelaunay());
        buildSurface(tris, gverts, norms, texturecoords);

    }

    // invalidate the volume cache -- strictly speaking this is only needed
    // for rational surfaces
    _volumeCache.setEmpty();

//        std::cerr<<"Surface::reTessellate:   texcoords ptr: " << getTexCoords() << std::endl;
//        std::cerr<<"Surface::reTessellate:   texcoords1 ptr: " << getTexCoords1() << std::endl;

}

//internal
Int32 Surface::convertSurface(void)
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;

    bool                    israt;
    const GeoPnt3fProperty *pPos    =
        dynamic_cast<const GeoPnt3fProperty *>(getControlPoints());
    const GeoPnt4fProperty *pRatPos =
        dynamic_cast<const GeoPnt4fProperty *>(getControlPoints());

//    std::cerr<< "pPos: " << pPos << " pRatPos: " << pRatPos << std::endl;
    if(getControlPoints() == NULL)
    {
        SLOG << "Surface::tessellate: null surfacecontrol prop " << endLog;
        return -1;
    }

    if(pPos != NULL)
    {
        israt = false;
    }
    else if(pRatPos != NULL)
    {
        israt = true;
    }
    else
    {
        SLOG << "Surface::tessellate: null surfacecontrol prop " << endLog;
        return -1;
    }

    const MFPnt3f *polyControlPoints = NULL;
    const MFPnt4f *ratControlPoints  = NULL;
    UInt32         cpsize;

    if(!israt)
    {
        polyControlPoints = &(pPos->getField());
        cpsize            = polyControlPoints->size();
    }
    else
    {
        ratControlPoints = &(pRatPos->getField());
        cpsize           = ratControlPoints->size();
    }
//    MFPnt3f &_mfControlPoints = pPos->getField();

    // check knots, dimensions and control points
    if(cpsize == 0)
    {
        SLOG << "Surface::tessellate: null surfacecontrol points " << endLog;
        return -1;
    }
/*    if ( cpdim !=3 && cpdim !=4 )
    {
        SLOG << "Surface::tessellate: wrong control point dimensions " <<
                endLog;
    }*/
    UInt32 dimu = _sfDimU.getValue();
    UInt32 dimv = _sfDimV.getValue();
    if(dimu == 0 || dimv == 0)
    {
        SLOG << "Surface::tessellate: 0 dimensions " << endLog;
        return -1;
    }

    UInt32 knotusize = _mfKnotsU.size();
    UInt32 knotvsize = _mfKnotsV.size();
    if(knotusize == 0 || knotvsize == 0)
    {
        SLOG << "Surface::tessellate: empty knotvectors " << endLog;
        return -1;
    }

    UInt32 cpusize = knotusize - dimu - 1;
    UInt32 cpvsize = knotvsize - dimv - 1;
    if(cpusize < 1 || cpvsize < 1 || cpusize * cpvsize != cpsize)
    {
        SLOG << cpusize << "x" << cpvsize << ":" << cpsize << endLog;
        SLOG << "Surface::tessellate: inconsistent attributes " << endLog;
        return -1;
    }

    if(_sfNumCurves.getValue() == 0)     // no trimming specified, add dummy trimming
    {
        Real64 umin = _mfKnotsU[0];
        Real64 vmin = _mfKnotsV[0];
        Real64 umax = _mfKnotsU[knotusize - 1];
        Real64 vmax = _mfKnotsV[knotvsize - 1];

        std::vector<Real64> tmpknotvec(4);
        std::vector<Pnt2f>  tmpcps(2);
        UInt32              dim = 1;
        tmpknotvec[0] = 0.0;
        tmpknotvec[1] = 0.0;
        tmpknotvec[2] = 1.0;
        tmpknotvec[3] = 1.0;

        // (umin, vmin) -> (umax,vmin)
        tmpcps[0][0] = umin; tmpcps[0][1] = vmin;
        tmpcps[1][0] = umax; tmpcps[1][1] = vmin;
        addCurve(dim, tmpknotvec, tmpcps);

        // (umax, vmin) -> (umax,vmax)
        tmpcps[0][0] = umax; tmpcps[0][1] = vmin;
        tmpcps[1][0] = umax; tmpcps[1][1] = vmax;
        addCurve(dim, tmpknotvec, tmpcps);

        // (umax, vmax) -> (umin,vmax)
        tmpcps[0][0] = umax; tmpcps[0][1] = vmax;
        tmpcps[1][0] = umin; tmpcps[1][1] = vmax;
        addCurve(dim, tmpknotvec, tmpcps);

        // (umin, vmax) -> (umin,vmin)
        tmpcps[0][0] = umin; tmpcps[0][1] = vmax;
        tmpcps[1][0] = umin; tmpcps[1][1] = vmin;
        addCurve(dim, tmpknotvec, tmpcps);
    }

    // now we checked everything, let's convert the surface+trimcurves
    // to the internal representation

    // first create surface
    BSplineTensorSurface tensor_surface;
    UInt32               i, j, k;
    DCTPVec4dmatrix      qnet;
    Vec4d                vec4;
    qnet.resize(cpusize);

    for(i = 0; i < cpusize; ++i)
    {
        qnet[i].resize(cpvsize);

        for(j = 0; j < cpvsize; ++j)
        {
            k = i * cpvsize + j;
            if(!israt)
            {
                vec4[0] = (*polyControlPoints)[k][0];
                vec4[1] = (*polyControlPoints)[k][1];
                vec4[2] = (*polyControlPoints)[k][2];
                vec4[3] = 1.0f; //!!!!!!!!!!!!!!!!!!!!
//                SLOG << "qnet["<<i<<"]["<<j<<"]: " << vec4 << endLog;
//                SLOG << "k: " << k << endLog;
            }
            else
            {
                vec4[0] = (*ratControlPoints)[k][0];
                vec4[1] = (*ratControlPoints)[k][1];
                vec4[2] = (*ratControlPoints)[k][2];
                vec4[3] = (*ratControlPoints)[k][3];
//                SLOG << "qnet["<<i<<"]["<<j<<"]: " << vec4 << endLog;
//                SLOG << "k: " << k << endLog;
            }
            qnet[i][j] = vec4;
        }
    }

    tensor_surface.setControlPointMatrix(qnet);
    // convert knotvectors
    DCTPdvector knotuvec(knotusize);
    DCTPdvector knotvvec(knotvsize);

    for(i = 0; i < knotusize; ++i)
    {
        knotuvec[i] = _mfKnotsU[i];
    }

    for(i = 0; i < knotvsize; ++i)
    {
        knotvvec[i] = _mfKnotsV[i];
    }

    tensor_surface.setKnotsAndDimension(knotuvec, dimu, knotvvec, dimv);
//    std::cerr<<"0.2"<<std::endl;
//    fprintf(stderr,"%x\n", _trimmedSurface);
    _trimmedSurface->setSurface(tensor_surface);
//    std::cerr<<"0.3"<<std::endl;

    // now create/convert trimming loops
    trimmingloop trimloops;
    UInt32       cplsize = _mfCurvesPerLoop.size();
    trimloops.resize(cplsize);

    for(i = 0; i < cplsize; ++i)
    {
        trimloops[i].resize(_mfCurvesPerLoop[i]);
    }

    UInt32          actknotoffset = 0;
    UInt32          actcpoffset   = 0;
//    UInt32          actloopoffset = 0;
    UInt32          actcurveno    = 0;
    UInt32          acttrimcpsize = 0;
    DCTPdvector     actknots;
    DCTPVec3dvector acttrimcps;
    BSplineCurve2D  actcurve;

    for(i = 0; i < trimloops.size(); ++i)
    {
        for(j = 0; j < trimloops[i].size(); ++j)
        {
            actknots.resize(_mfKnotLengths[actcurveno]);
//            SLOG << "Debug: _mfKnotLengths[ actcurveno ]: " <<
//                    _mfKnotLengths[ actcurveno ] << " actcurveno: " <<
//                    actcurveno << endLog;
            acttrimcpsize = actknots.size() - _mfDimensions[actcurveno] - 1;
            if(acttrimcpsize < 1)
            {
                SLOG << "Surface::tessellate: wrong trimming curve attributes "
                     << endLog;
                return -1;
            }
            acttrimcps.resize(acttrimcpsize);

            for(k = 0; k < actknots.size(); ++k)
            {
                actknots[k] = _mfKnots[actknotoffset + k];
            }

            actknotoffset += actknots.size();
            actcurve.setKnotsAndDimension(actknots,
                                          _mfDimensions[actcurveno]);

//            SLOG << "Debug: actknotoffset: " << actknotoffset << endLog;
//            SLOG << "Debug: actcpoffset: " << actcpoffset << endLog;
//            SLOG << "Debug: _mfCurveControlPoints.size(): " <<
//                    _mfCurveControlPoints.size() << endLog;
//            SLOG << "Debug: _mfKnots.size(): " << _mfKnots.size() << endLog;
//            SLOG << "Debug: acttrimcps.size(): " << acttrimcps.size() << endLog;
            for(k = 0; k < acttrimcpsize; ++k)
            {
//                SLOG <<"Debug: k: " << k << endLog;
                acttrimcps[k][0] = _mfCurveControlPoints[actcpoffset + k][0];
                acttrimcps[k][1] = _mfCurveControlPoints[actcpoffset + k][1];
                acttrimcps[k][2] = _mfCurveControlPoints[actcpoffset + k][2];
            }

            actcpoffset += acttrimcpsize;
            actcurve.setControlPointVector(acttrimcps);

            trimloops[i][j] = actcurve;
            actcurveno++;
        }

    }

    _trimmedSurface->setTrimmingLoops(trimloops);
    _trimmedSurface->normalize();

//    global_surf = *_trimmedSurface;
    return 0;
}


//internal
// normal, nontexturemapped
Int32 Surface::tessellateSurface(std::vector<SimplePolygon> &triangles,
                                 std::vector<Pnt3f> &        gverts,
                                 std::vector<Vec3f> &        norms)
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;
//    std::vector< SimplePolygon > *triangles = (std::vector< SimplePolygon > *)tris;
//    CNurbsPatchSurface cpatch;              // "tessellator" object
    std::vector<Pnt2f> dummy;
    _surfacePatch->setSurface(_trimmedSurface, dummy, false);

    if(_sfError.getValue() < DCTP_EPS)
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//                endLog;
        _sfError.setValue(0.2f);
    }

    _surfacePatch->setError(_sfError.getValue() );
    _surfacePatch->getTessellation(gverts, norms, triangles, getIsDelaunay() );
    SSurface *surfaceData =  _surfacePatch->getSurfaceData();
    _min = Pnt3d(surfaceData->clMin[0], surfaceData->clMin[1],
                 surfaceData->clMin[2]);
    _max = Pnt3d(surfaceData->clMax[0], surfaceData->clMax[1],
                 surfaceData->clMax[2]);
#ifdef OSG_ARBITRARY_SPLIT
    _minParam = Pnt2d(surfaceData->clMinParam[0], surfaceData->clMinParam[1]);
    _maxParam = Pnt2d(surfaceData->clMaxParam[0], surfaceData->clMaxParam[1]);
#endif


//    std::cerr<< "min, max: [" << _min << "][" << _max << "]" << std::endl;
//    std::cerr<< "minparam, maxparam: [" << _minParam << "][ " << _maxParam  << "]" << std::endl;

    return 0;
}

//internal
// surface with texturemap, no normalmap!
Int32 Surface::tessellateSurface(std::vector<SimplePolygon> &triangles,
                                 std::vector<Pnt3f> &        gverts,
                                 std::vector<Vec3f> &        norms,
                                 std::vector<Pnt2f> &        texcoords)
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;
//    std::vector< SimplePolygon > *triangles = (std::vector< SimplePolygon > *)tris;
//    CNurbsPatchSurface cpatch;              // "tessellator" object
    const GeoVec2fProperty *pTexPos = dynamic_cast<const GeoVec2fProperty *>(
        getTextureControlPoints());
    std::vector<Pnt2f> tmptexcoords;
    UInt32             i;
    UInt32             s = pTexPos->getField().size();

    for(i = 0; i < s; ++i)
    {
        tmptexcoords.push_back(Pnt2f(pTexPos->getField()[i][0],
                                     pTexPos->getField()[i][1]));
    }

    _surfacePatch->setSurface(_trimmedSurface, tmptexcoords, true);
    if(_sfError.getValue() < DCTP_EPS)
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//                endLog;
        _sfError.setValue(0.2f);
    }

    _surfacePatch->setError(_sfError.getValue() );
    _surfacePatch->getTessellation(gverts, norms, texcoords, triangles, getIsDelaunay() );

//    std::cerr<< "norms.size(): " << norms.size() << " texcoords.size(): " <<
//            texcoords.size() << std::endl;
    SSurface *surfaceData =  _surfacePatch->getSurfaceData();
    _min = Pnt3d(surfaceData->clMin[0], surfaceData->clMin[1],
                 surfaceData->clMin[2]);
    _max = Pnt3d(surfaceData->clMax[0], surfaceData->clMax[1],
                 surfaceData->clMax[2]);
#ifdef OSG_ARBITRARY_SPLIT
    _minParam = Pnt2d(surfaceData->clMinParam[0], surfaceData->clMinParam[1]);
    _maxParam = Pnt2d(surfaceData->clMaxParam[0], surfaceData->clMaxParam[1]);
#endif


//    std::cerr<< "min, max: [" << _min << "][" << _max << "]" << std::endl;
//    std::cerr<< "minparam, maxparam: [" << _minParam << "][ " << _maxParam  << "]" << std::endl;

    return 0;
}

//internal
// surface with normalmaps
Int32 Surface::tessellateSurface(std::vector<SimplePolygon> &triangles,
                                 std::vector<Pnt3f> &        gverts,
                                 std::vector<Pnt2f> &        texcoords)
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;
//    std::vector< SimplePolygon > *triangles = (std::vector< SimplePolygon > *)tris;
//    CNurbsPatchSurface cpatch;              // "tessellator" object
    const GeoVec2fProperty *pTexPos = dynamic_cast<const GeoVec2fProperty *>(
        getTextureControlPoints());
    std::vector<Pnt2f> tmptexcoords;
    UInt32             i;
    UInt32             s =  pTexPos->getField().size();

    for(i = 0; i < s; ++i)
    {
        tmptexcoords.push_back(Pnt2f(pTexPos->getField()[i][0],
                                     pTexPos->getField()[i][1]));
    }

    _surfacePatch->setSurface(_trimmedSurface,
                              tmptexcoords,
                              true);
    if(_sfError.getValue() < DCTP_EPS)
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//                endLog;
        _sfError.setValue(0.2f);
    }

    _surfacePatch->setError(_sfError.getValue());
    std::vector<Vec3f> norms;
    _surfacePatch->getTessellation(gverts, norms, triangles, false);
    _surfacePatch->getTessellation(gverts, texcoords, triangles, getIsDelaunay() );

    SSurface *surfaceData =  _surfacePatch->getSurfaceData();
    _min = Pnt3d(surfaceData->clMin[0], surfaceData->clMin[1],
                 surfaceData->clMin[2]);
    _max = Pnt3d(surfaceData->clMax[0], surfaceData->clMax[1],
                 surfaceData->clMax[2]);

#ifdef OSG_ARBITRARY_SPLIT
    _minParam = Pnt2d(surfaceData->clMinParam[0], surfaceData->clMinParam[1]);
    _maxParam = Pnt2d(surfaceData->clMaxParam[0], surfaceData->clMaxParam[1]);
#endif


//    std::cerr<< "min, max: [" << _min << "][" << _max << "]" << std::endl;
//    std::cerr<< "minparam, maxparam: [" << _minParam << "][ " << _maxParam  << "]" << std::endl;

    return 0;
}

//internal
// normal surface
Int32 Surface::buildSurface(std::vector<SimplePolygon> &triangles,
                            std::vector<Pnt3f> &        gverts,
                            std::vector<Vec3f> &        norms,
                            std::vector<Pnt2f> &        texcoords)

{
    // FIXME:
    //
    // At least on Linux/ATI with the current OpenGL drivers
    // TextureCoordinate1 doesn't get passed to the vertex program
    // unless there's TextureCoordinate0 present.
    // Might even crash older drivers, and might also be a problem
    // on Windows with some driver versions.
    //
    // Therefore the Surface uses TextureCoordinate0 to pass tangent
    // coordinates to the FatBorderChunk, thus texturing an OSGSurface
    // that uses FBs should begin in TextureCoordinate1.
    //
    // Currently only 1 texture is supported (copied to the fragment
    // program for further processing, and built by this function)
    // more can be easily added if it's a problem.
    //
    // FIXME END

    GeoIntegralPropertyUnrecPtr pcl_type      = getTypes();
    GeoIntegralPropertyUnrecPtr pcl_size      = getLengths();
    GeoVectorPropertyUnrecPtr   pcl_points    = getPositions();
    GeoVectorPropertyUnrecPtr   pcl_norms     = getNormals();
    GeoIntegralPropertyUnrecPtr pcl_indices   = getIndices();
    GeoVectorPropertyUnrecPtr   pcl_texcoords = getTexCoords1();
    //FatBorderChunk parameters are always passed in TextureCoordinate.
    GeoVec3fPropertyUnrecPtr    pcl_tangents  =
        dynamic_cast<GeoVec3fProperty *>(getTexCoords());
    SimpleMaterialUnrecPtr      pcl_mat       =
        dynamic_cast<SimpleMaterial *>(getMaterial());
//  GeometryPtr         pcl_geo = Geometry::create( );
    SimplePolygon       *pcl_face;
    const UInt32         cui_faces = triangles.size();
    UInt32               ui_face;
    BSplineTensorSurface cl_surf = _trimmedSurface->getSurface();
//    int                  i_err;
    Vec3d                cl_norm;
    const UInt32         cui_verts = gverts.size();
    UInt32               ui_vert;
    SSurface            *pt_surfdata  = _surfacePatch->getSurfaceData();
    const UInt32         cui_loop_cnt = pt_surfdata->vvclEdgeLoops.size();
    UInt32               ui_loop;
    UInt32               ui_vertex_cnt;
    UInt32               ui_idx;
    UInt32               ui_used;
//    Vec3d               *pcl_actn;
    Vec3d               *pcl_actv;
    Vec3d               *pcl_nextv;
    Vec3d               *pcl_prevv;
    Vec3f                cl_v1, cl_v2, cl_tangent;
    std::vector<Int32>   vi_new_idx(cui_verts);
    bool                 b_show_trimming = false;

    // check if material has the fat border chunk
    if(pcl_mat != NULL)
    {
        if(pcl_mat->find(FatBorderChunk::getClassType()) != NULL)
            b_show_trimming = true;
    }

//    std::cerr<<"show_trimming: " << b_show_trimming << std::endl;
    if(pcl_type == NULL)
    {
        pcl_type = GeoUInt8Property::create();
    }
    if(pcl_size == NULL)
    {
        pcl_size = GeoUInt32Property::create();
    }
    if(pcl_points == NULL)
    {
        pcl_points = GeoPnt3fProperty::create();
    }
    if( (norms.size() > 0) && (pcl_norms == NULL) )
    {
        pcl_norms = GeoVec3fProperty::create();
    }
    if(pcl_indices == NULL)
    {
        pcl_indices = GeoUInt32Property::create();
    }
    if( (texcoords.size() > 0) && (pcl_texcoords == NULL) )
    {
        pcl_texcoords = GeoVec2fProperty::create();
    }
    if(b_show_trimming)
    {
        if(pcl_tangents == NULL)
        {
            pcl_tangents = GeoVec3fProperty::create();
        }
    }
    else
    {
        if(pcl_tangents != NULL)
        {
            setTexCoords(NULL);
        }
    }

    // check for unused points
    for(ui_vert = 0; ui_vert < cui_verts; ++ui_vert)
    {
        vi_new_idx[ui_vert] = -1;
    }

    for(ui_face = 0; ui_face < cui_faces; ++ui_face)
    {
        pcl_face                          = &triangles[ui_face];
        vi_new_idx[pcl_face->vertices[0]] = 0;
        vi_new_idx[pcl_face->vertices[1]] = 0;
        vi_new_idx[pcl_face->vertices[2]] = 0;
    }

    // calculate new indices
    ui_used = 0;

    for(ui_vert = 0; ui_vert < cui_verts; ++ui_vert)
    {
        if(vi_new_idx[ui_vert] >= 0)
        {
            vi_new_idx[ui_vert] = ui_used;
            ++ui_used;
        }
    }

//  m_vtSurfaces[ uiSurface ].uiTriangleCnt = cui_faces;
//  m_vclNormal.resize( m_vclParameterVertices.size( ) );

//        std::cerr<<"fuck3"<<std::endl;
    pcl_type->clear();
//        std::cerr<<"fuck4"<<std::endl;
    pcl_type->push_back(GL_TRIANGLES);
//        std::cerr<<"fuck5"<<std::endl;
    if(b_show_trimming)
    {
        for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
        {
            pcl_type->push_back(GL_TRIANGLE_STRIP);
        }
    } // b_show_trimming

//    std::cerr<<"types"<<std::endl;
    pcl_size->clear();
    pcl_size->push_back(3 * cui_faces);
    ui_idx = 3 * cui_faces;
    if(b_show_trimming)
    {
        for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
        {
            pcl_size->push_back(2 + 2 * pt_surfdata->vvclEdgeLoops[ui_loop].size() );
            ui_idx += 2 + 2 * pt_surfdata->vvclEdgeLoops[ui_loop].size();
        }
    }
//      std::cerr << ui_idx << " indices" << std::endl;

//    std::cerr<<"size"<<std::endl;
    pcl_points->clear();

    for(ui_vert = 0; ui_vert < cui_verts; ++ui_vert)
    {
        if(vi_new_idx[ui_vert] >= 0)
        {
            pcl_points->push_back(gverts[ui_vert]);
        }
    }

    if(b_show_trimming)
    {
        for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
        {
            ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ui_loop].size();

            for(ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert)
            {
                pcl_points->push_back(
                    Pnt3f(pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert][0],
                          pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert][1],
                          pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert][2] ));
                pcl_points->push_back(
                    Pnt3f(pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert][0],
                          pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert][1],
                          pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert][2] ));
            }
        }
    } // b_show_trimming

//    std::cerr<<"points"<<std::endl;
    if(norms.size() > 0)
    {
        pcl_norms->clear();

        for(ui_vert = 0; ui_vert < cui_verts; ++ui_vert)
        {
            if(vi_new_idx[ui_vert] >= 0)
                pcl_norms->push_back(norms[ui_vert]);
        }

        if(b_show_trimming)
        {
            for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
            {
                ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ui_loop].size();

                for(ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert)
                {
                    pcl_norms->push_back(
                        Vec3f(pt_surfdata->vvclEdgeLoopsNorm[ui_loop][ui_vert][0],
                              pt_surfdata->vvclEdgeLoopsNorm[ui_loop][ui_vert][1],
                              pt_surfdata->vvclEdgeLoopsNorm[ui_loop][ui_vert][2] ));
                    pcl_norms->push_back(
                        Vec3f(pt_surfdata->vvclEdgeLoopsNorm[ui_loop][ui_vert][0],
                              pt_surfdata->vvclEdgeLoopsNorm[ui_loop][ui_vert][1],
                              pt_surfdata->vvclEdgeLoopsNorm[ui_loop][ui_vert][2] ));
                }
            }
        } // b_show_trimming
//      std::cerr<<"norms"<<std::endl;
    }

    if(texcoords.size() > 0)
    {
        pcl_texcoords->clear();

        for(ui_vert = 0; ui_vert < cui_verts; ++ui_vert)
        {
            if(vi_new_idx[ui_vert] >= 0)
            {
                pcl_texcoords->push_back(Vec2f(texcoords[ui_vert][0],
                                               texcoords[ui_vert][1]) );
//                 std::cerr<<"texcoords: " << texcoords[ ui_vert ][ 0 ] <<
//                             " " << texcoords[ ui_vert ][ 1 ] << std::endl;
            }
        }

        if(b_show_trimming)
        {
            for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
            {
                ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ui_loop].size();

                for(ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert)
                {
                    pcl_texcoords->push_back(
                        Vec2f(pt_surfdata->vvclEdgeLoopsTex[ui_loop][ui_vert][0],
                              pt_surfdata->vvclEdgeLoopsTex[ui_loop][ui_vert][1]) );
                    pcl_texcoords->push_back(
                        Vec2f(pt_surfdata->vvclEdgeLoopsTex[ui_loop][ui_vert][0],
                              pt_surfdata->vvclEdgeLoopsTex[ui_loop][ui_vert][1]) );
                }
            }
        } // b_show_trimming
    }

    if(b_show_trimming)
    {
        pcl_tangents->clear();

        for(ui_vert = 0; ui_vert < cui_verts; ++ui_vert)
        {
            if(vi_new_idx[ui_vert] >= 0)
            {
                pcl_tangents->editFieldPtr()->push_back(Vec3f(0.0, 0.0, 0.0) );
            }
        }

        for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
        {
            ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ui_loop].size();

            for(ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert)
            {
                if(ui_vert == 0)
                {
                    pcl_prevv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vertex_cnt - 1];
                    pcl_nextv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][1];
                }
                else if(ui_vert == ui_vertex_cnt - 1)
                {
                    pcl_prevv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert - 1];
                    pcl_nextv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][0];
                }
                else
                {
                    pcl_prevv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert - 1];
                    pcl_nextv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert + 1];
                }
                pcl_actv = &pt_surfdata->vvclEdgeLoops3D[ui_loop][ui_vert];
                // calculate the tangents of the trimming polyloops:
                // (nextv - actv).normalize() plus
                // (actv - prevv).normalize()  -> and normalize it again
                cl_v1[0] = (*pcl_nextv)[0] - (*pcl_actv)[0];
                cl_v1[1] = (*pcl_nextv)[1] - (*pcl_actv)[1];
                cl_v1[2] = (*pcl_nextv)[2] - (*pcl_actv)[2];
                cl_v1.normalize();
                cl_v2[0] = (*pcl_actv)[0] - (*pcl_prevv)[0];
                cl_v2[1] = (*pcl_actv)[1] - (*pcl_prevv)[1];
                cl_v2[2] = (*pcl_actv)[2] - (*pcl_prevv)[2];
                cl_v2.normalize();
                cl_tangent = cl_v1 + cl_v2;
                cl_tangent.normalize();

                cl_tangent *= sqrt(getError() );

                pcl_tangents->editFieldPtr()->push_back(-cl_tangent);
                pcl_tangents->editFieldPtr()->push_back( cl_tangent);
            }
        }

//      std::cerr<<"tangents"<<std::endl;
    } // b_show_trimming

    pcl_indices->clear();

    for(ui_face = 0; ui_face < cui_faces; ++ui_face)
    {
        pcl_face = &triangles[ui_face];
        if( (norms.size() == 0) ||
            (checkOrient(pcl_face->vertices[0],
                         pcl_face->vertices[1],
                         pcl_face->vertices[2], gverts, norms) ) )
        {
            pcl_indices->push_back(vi_new_idx[pcl_face->vertices[0]]);
            pcl_indices->push_back(vi_new_idx[pcl_face->vertices[1]]);
            pcl_indices->push_back(vi_new_idx[pcl_face->vertices[2]]);
        }
        else
        {
            pcl_indices->push_back(vi_new_idx[pcl_face->vertices[0]]);
            pcl_indices->push_back(vi_new_idx[pcl_face->vertices[2]]);
            pcl_indices->push_back(vi_new_idx[pcl_face->vertices[1]]);
        }
    }

    ui_idx = ui_used;
    if(b_show_trimming)
    {
        for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
        {
            ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ui_loop].size();

            for(ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert)
            {
                pcl_indices->push_back(ui_idx++);
                pcl_indices->push_back(ui_idx++);
            }

            pcl_indices->push_back(ui_idx - 2 * ui_vertex_cnt);
            pcl_indices->push_back(ui_idx - 2 * ui_vertex_cnt + 1);
        }

//          std::cerr << ui_idx + 2 * cui_loop_cnt << " indices used" << std::endl;
    } // b_show_trimming
//    std::cerr<<"indices"<<std::endl;

    if(b_show_trimming)
    {
        if(norms.size() > 0)
        {
            if(texcoords.size() > 0)    // fatborders, normals and standard textures
            {
                setTypes     (pcl_type     );
                setLengths   (pcl_size     );
                setIndices   (pcl_indices  );

                setPositions (pcl_points   );
                setNormals   (pcl_norms    );
                setTexCoords (pcl_tangents );
                setTexCoords1(pcl_texcoords);
                //                   std::cerr<<"setting stuph3 "<<std::endl;
            }
            else // fatborders, normals but no standard textures (most used case)
            {
                setTypes    (pcl_type    );
                setLengths  (pcl_size    );
                setIndices  (pcl_indices );

                setPositions(pcl_points  );
                setNormals  (pcl_norms   );
                setTexCoords(pcl_tangents);

//                   std::cerr<<"setting stuph!"<<std::endl;
            }
        }
        else
        {
            if(texcoords.size() > 0)    //fatborders and normalmaps and no textures
            {
                setTypes     (pcl_type     );
                setLengths   (pcl_size     );
                setIndices   (pcl_indices  );

                setPositions (pcl_points   );
                setTexCoords (pcl_tangents );
                setTexCoords1(pcl_texcoords);
            }
            else // fatborders, no normals, no textures -- makes no sense??? NPR?
                 // essentially flat-shading
            {
                setTypes   (pcl_type     );
                setLengths (pcl_size     );
                setIndices (pcl_indices  );

                setPositions(pcl_points  );
                setTexCoords(pcl_tangents);
//                   std::cerr<<"setting stuph2"<<std::endl;
            }
        }
    }
    else
    {
        if(norms.size() > 0)
        {
            if(texcoords.size() > 0)     // no fatborders, normals and standard textures
            {
                setTypes    (pcl_type     );
                setLengths  (pcl_size     );
                setIndices  (pcl_indices  );

                setPositions(pcl_points   );
                setNormals  (pcl_norms    );
                setTexCoords(pcl_texcoords);
//                   std::cerr<<"setting stuph4"<<std::endl;
            }
            else // no fatborders, normals but no standard textures
            {
                setTypes    (pcl_type   );
                setLengths  (pcl_size   );
                setIndices  (pcl_indices);

                setPositions(pcl_points );
                setNormals  (pcl_norms  );
            }
        }
        else
        {
            if(texcoords.size() > 0)    // no fatborders, normalmaps
            {
                setTypes    (pcl_type     );
                setLengths  (pcl_size     );
                setIndices  (pcl_indices  );

                setPositions(pcl_points   );
                setTexCoords(pcl_texcoords);
            }
            else // no fatborders, no normals, no textures
            {
                setTypes    (pcl_type   );
                setLengths  (pcl_size   );
                setIndices  (pcl_indices);

                setPositions(pcl_points );
            }
        }
    }

//        std::cerr<<"Surface::buildSurface:   texcoords ptr: " << getTexCoords() << std::endl;
//        std::cerr<<"Surface::buildSurface:   texcoords1 ptr: " << getTexCoords1() << std::endl;


    // build new display list if used
//  invalidateDlistCache( );

    return 0;
}


//internal
bool Surface::checkOrient(UInt32 ui_v1, UInt32 ui_v2, UInt32 ui_v3,
                          std::vector<Pnt3f> &m_vclGlobalVertices,
                          std::vector<Vec3f> &m_vclNormal)
{
    const Vec3f ccl_norm_p = m_vclNormal[ui_v1] + m_vclNormal[ui_v2] + m_vclNormal[ui_v3];
    const Vec3f ccl_vec1   = m_vclGlobalVertices[ui_v2] - m_vclGlobalVertices[ui_v1];
    const Vec3f ccl_vec2   = m_vclGlobalVertices[ui_v3] - m_vclGlobalVertices[ui_v1];
    const Vec3f ccl_norm_t = ccl_vec1.cross(ccl_vec2);

    // FIXME: is 0.0 really better than -DCTP_EPS ?
    return(ccl_norm_p.dot(ccl_norm_t) > 0.0);
}


/*! \brief Add a (polynomial) trimming curve to the surface.
    This function allows you to add a new trimming curve to
    the Surface.
  
    \param dim the dimension of the curve
    \param knots the knotvector of the curve
    \param controlpoints the (rational) control points for the curve
    \param newloop false, this curve continues the current curveloop <BR>
                   true, starts a new loop
  
    If it's the first curve added to the surface, it always starts
    a new loop, regardless of the value of newloop.
  
    You are expected to call this function between corresponding
    beginEditCP()/endEditCP() pairs with the mask CurveFieldMask.
    You are responsible that when calling endEditCP() the
    trimming curves are in a consistend state (they form closed
    loops and the like).
 */

void Surface::addCurve(
    UInt32                     dim,
    const std::vector<Real64> &knots,
    const std::vector<Pnt2f> & controlpoints,
    bool                       newloop)
{
    UInt32             cpsize = controlpoints.size();
    std::vector<Pnt3f> ratcontrolpoints;

    ratcontrolpoints.reserve(cpsize);

    for(UInt32 i = 0; i < cpsize; ++i)
    {
        ratcontrolpoints.push_back(Pnt3f(controlpoints[i][0],
                                         controlpoints[i][1],
                                         1.0f) );
    }

    addCurve(dim, knots, ratcontrolpoints, newloop);
}

//! Add a (rational) trimming curve to the surface.
/*!
 *
 *  This function allows you to add a new trimming curve to
 *  the Surface.
 *
 *  \param dim the dimension of the curve
 *  \param knots the knotvector of the curve
 *  \param controlpoints the (nonrational) control points for the curve
 *  \param newloop false: this curve continues the current curveloop <BR>
 *                 true: starts a new loop
 *
 *  If it's the first curve added to the surface, it always starts
 *  a new loop, regardless of the value of newloop.
 *
 *  You are expected to call this function between corresponding
 *  beginEditCP()/endEditCP() pairs with the mask CurveFieldMask.
 *  You are responsible that when calling endEditCP() the
 *  trimming curves are in a consistend state (they form closed
 *  loops and the like).
 *
 */
void Surface::addCurve(
    UInt32                     dim,
    const std::vector<Real64> &knots,
    const std::vector<Pnt3f> & controlpoints,
    bool                       newloop)
{
    UInt32 cpsize   = controlpoints.size();
    UInt32 knotsize = knots.size();

    if(dim + cpsize + 1 != knotsize)
    {
//        SWARNING <<"Surface::addCurve: inconsistent curve attributes..." << endLog;
        return;
    }
//    SLOG <<"addCurve NI " << std::endl;

    if(_sfNumCurves.getValue() == 0)
    {
        //this is the first curve -> it starts a new loop
//        SLOG <<"addcurve first curve"<<endLog;
        newloop = true;
    }
    _mfDimensions.push_back(dim);
    if(newloop)
    {
        _mfCurvesPerLoop.push_back(1);   //1 curve in a new loop
//        SLOG <<"addcurve newloop"<<endLog;
    }
    else
    {
//        SLOG <<"addcurve NOT newloop"<<endLog;
        UInt32 cplsize = _mfCurvesPerLoop.size();
//        _mfCurvesPerLoop.setValue( _mfCurvesPerLoop.getValue( cplsize - 1 ) + 1,
//                                   cplsize - 1 );
        _mfCurvesPerLoop[cplsize - 1] = _mfCurvesPerLoop[cplsize - 1] + 1;
    }
    _mfKnotLengths.push_back(knotsize);
    UInt32 i;

    for(i = 0; i < knotsize; ++i)
    {
        _mfKnots.push_back(Real32(knots[i]) );
    }

    for(i = 0; i < cpsize; ++i)
    {
        _mfCurveControlPoints.push_back(controlpoints[i]);
    }

    _sfNumCurves.setValue(_sfNumCurves.getValue() + 1);
}

//! Remove all trimming curves from the surface.
/*!
 *
 *  This function removes all trimming curves from the surface.
 *
 *  You are expected to call this function between corresponding
 *  beginEditCP()/endEditCP() pairs with the mask CurveFieldMask.
 *
 */
void Surface::removeCurves(void)
{
    if(_sfNumCurves.getValue() == 0)    //we have no curves
    {
        return;
    }

    _sfNumCurves.setValue(0);
    _mfKnotLengths.clear();
    _mfDimensions.clear();
    _mfCurveControlPoints.clear();
    _mfKnots.clear();
    _mfCurvesPerLoop.clear();
}


//! Clone the Surface.
SurfaceTransitPtr Surface::clone(void)
{
    SurfaceTransitPtr surf = Surface::create();

    SWARNING << "Surface::clone not completely implemented!" << endLog;
    //  create copies of the attributes
    if(getMFKnotsU() != NULL)
        surf->editMFKnotsU()->setValues(*getMFKnotsU());

    if(getMFKnotsV() != NULL)
        surf->editMFKnotsV()->setValues(*getMFKnotsV());

    if(getMFKnotLengths() != NULL)
        surf->editMFKnotLengths()->setValues(*getMFKnotLengths());

    if(getMFDimensions() != NULL)
        surf->editMFDimensions()->setValues(*getMFDimensions());

    if(getMFCurveControlPoints() != NULL)
        surf->editMFCurveControlPoints()->setValues(*getMFCurveControlPoints());

    if(getMFKnots() != NULL)
        surf->editMFKnots()->setValues(*getMFKnots());

    if(getMFCurvesPerLoop() != NULL)
        surf->editMFCurvesPerLoop()->setValues(*getMFCurvesPerLoop());

    surf->setMaterial(getMaterial());
    surf->setDimU(getDimU());
    surf->setDimV(getDimV());
    surf->setNumCurves(getNumCurves());
    surf->setError(getError());
    surf->setIsDelaunay(getIsDelaunay());
    surf->setControlPoints(getControlPoints());
    surf->setTextureControlPoints(getTextureControlPoints());

    return surf;
}


//! Read from a .tso file. Temporary function
/*!
 *  Read surface (and trimming) information from
 *  a file in .tso format. This is mainly used
 *  for debugging the code (with complicated models),
 *  it's not meant to be a general user-loader function!
 *
 *  This function may or may not be removed/changed/etc. later,
 *  you have been warned...
 *
 *  Does not perform too many checks on the input data...
 *
 *  You are expected to call this function between corresponding
 *  beginEditCP()/endEditCP() pairs with the mask
 *  CurveFieldMask|SurfaceFieldMask.
 *
 *  \param infile istream to read surface data from.
 *  \param useTextures use textures or not
 */
//#pragma optimize("",off)
void Surface::readFromTSO(std::istream &infile, bool useTextures)
{
    Int32                  err                = 0;
    BSplineTrimmedSurface *cl_trimmed_surface = new BSplineTrimmedSurface;
    BSplineTensorSurface   tensor_surface;
    trimmingloop           trimloop;

    // this is actually rather inefficient: first we convert the data to the
    // OpenSG representation, and then we convert back
    // to the BSplineTrimmedSurface representation later
    // during the tessellation...
    // but it's somewhat simpler to extract the info from
    // the BSplineTrimmedSurface class than to read from the file
    // I might rewrite it later, though...

    err = cl_trimmed_surface->read(infile);
    if(err)
    {
        SWARNING << "Couldn't read surface, exiting... " << err << endLog;
        delete cl_trimmed_surface;
        return;
    }

    tensor_surface = cl_trimmed_surface->getSurface();
    trimloop       = cl_trimmed_surface->getTrimmingLoops();

    // OK, first do surface business
    DCTPVec4dmatrix v4cps =  tensor_surface.getControlPointMatrix();

    UInt32 cpusize = v4cps.size();
    UInt32 cpvsize = v4cps[0].size();
    UInt32 /*k,*/u,v;
    Vec4d  vec4;

    GeoPnt4fPropertyUnrecPtr pPos;

    if(_sfControlPoints.getValue() == NULL)
    {
        pPos = GeoPnt4fProperty::create();

        setControlPoints(pPos);
    }
    else
    {
        pPos = dynamic_cast<GeoPnt4fProperty *>(_sfControlPoints.getValue());
    }

    MFPnt4f *mfControlPoints = pPos->editFieldPtr();
//    MFPnt3f &mfControlPoints = pPos->getField();

//    mfControlPoints.resize( cpusize * cpvsize );
    mfControlPoints->clear();

    for(u = 0; u < cpusize; ++u)
    {
        for(v = 0; v < cpvsize; ++v)
        {
//            k = u * cpvsize + v;
            vec4 = v4cps[u][v];
            mfControlPoints->push_back(Pnt4f(vec4[0], vec4[1], vec4[2], vec4[3]));
//            mfControlPoints.push_back(Pnt3f(vec4[0], vec4[1], vec4[2]));
        }
    }

    _sfDimU.setValue(tensor_surface.getDimension_U() );
    _sfDimV.setValue(tensor_surface.getDimension_V() );

    DCTPdvector knots;

    knots = tensor_surface.getKnotVector_U();
    _mfKnotsU.clear();

    for(u = 0; u < knots.size(); ++u)
    {
        _mfKnotsU.push_back(Real32(knots[u]) );
    }

    knots = tensor_surface.getKnotVector_V();
    _mfKnotsV.clear();

    for(v = 0; v < knots.size(); ++v)
    {
        _mfKnotsV.push_back(Real32(knots[v]) );
    }

    // now deal with the trimming curves
    removeCurves();

    bool                isnewloop;
    UInt32              actdim;
    std::vector<Real64> actknots;
    std::vector<Pnt3f>  actcontrolpoints;
    DCTPVec3dvector     v3actcps;

    for(UInt32 i = 0; i < trimloop.size(); ++i)
    {
        isnewloop = true;

        for(UInt32 j = 0; j < trimloop[i].size(); ++j)
        {
            actknots = trimloop[i][j].getKnotVector();
            actdim   = trimloop[i][j].getDimension();
            v3actcps = trimloop[i][j].getControlPointVector();
            actcontrolpoints.clear();

            for(UInt32 kk = 0; kk < v3actcps.size(); ++kk)
            {
                actcontrolpoints.push_back(Pnt3f(v3actcps[kk][0],
                                                 v3actcps[kk][1],
                                                 v3actcps[kk][2]));
            }

            addCurve(actdim, actknots, actcontrolpoints, isnewloop);
            isnewloop = false;
        }
    }

    // trimming curves...
    delete cl_trimmed_surface;

    if(useTextures)
    {
//        std::cerr<<"read in texture coordinates..."<<std::endl;
        char buffer[1024];
        infile >> buffer >> std::ws;
//        std::cerr <<"buffer: " << buffer <<std::endl;
        UInt32 numoftexcps = cpusize * cpvsize;
//        _mfTextureControlPoints.clear();

        GeoVec2fPropertyUnrecPtr pTexPos;

        if(_sfTextureControlPoints.getValue() == NULL)
        {
            pTexPos = GeoVec2fProperty::create();

            setTextureControlPoints(pTexPos);
        }
        else
        {
            pTexPos = dynamic_cast<GeoVec2fProperty *>(
                _sfTextureControlPoints.getValue());
        }

        MFVec2f *mfTextureControlPoints = pTexPos->editFieldPtr();
        mfTextureControlPoints->clear();

        Vec2f temp;

        for(UInt32 ti = 0; ti < numoftexcps; ++ti)
        {
            infile >> std::ws >> temp[0] >> std::ws >> temp[1] >> std::ws;
            mfTextureControlPoints->push_back(temp);
        }

//        std::cerr<<"read " << mfTextureControlPoints.size() << " cps."<<std::endl;
    }
}
//#pragma optimize("",on)

/*! write surface
 */

void Surface::writeToTSO(std::ostream &outfile)
{
    _trimmedSurface->write(outfile);
}


//! Write tessellated geometry to an .obj file. Absolutely temporary function
/*!
 *
 *  \param outfile istream to read surface data from.
 *  \param offset triangle offset
 */
UInt32 Surface::writeToOBJ(std::ostream &outfile, UInt32 offset)
{
    unsigned int uicnt;
//     std::cerr << "current offset:" << g_current_obj_offset << std::endl;
    outfile << "g obj " << std::endl;
    GeoVectorProperty   *pcl_points    = getPositions();
    GeoVectorProperty   *pcl_norms     = getNormals();
    GeoIntegralProperty *pcl_indices   = getIndices();
    GeoVectorProperty   *pcl_texcoords = getTexCoords();
    std::cerr << " indices size: " << pcl_indices->size() << std::endl;
    std::cerr << " points size: " << pcl_points->size() << std::endl;
    UInt32 ui_faces   = pcl_indices->size() / 3;
    UInt32 uivertsize = pcl_points->size();
    outfile << "# vertices " << uivertsize << std::endl;

    //write out vertices
    for(uicnt = 0; uicnt < uivertsize; uicnt++)
    {
        Pnt3f ppp = pcl_points->getValue<Pnt3f>(uicnt);

        outfile << "v " << ppp.x() << " " <<
        ppp.y() << " " <<
        ppp.z() << std::endl;

    }

    //write out normals
    for(uicnt = 0; uicnt < uivertsize; uicnt++)
    {
        Vec3f ppp = pcl_norms->getValue<Vec3f>(uicnt);

        outfile << "vn " << ppp.x() << " " <<
        ppp.y() << " " <<
        ppp.z() << std::endl;

    }

    //write out texture coordinates
    for(uicnt = 0; uicnt < uivertsize; uicnt++)
    {
        Vec2f ppp = pcl_texcoords->getValue<Vec2f>(uicnt);

        outfile << "vt " << ppp.x() << " " <<
        ppp.y() << " " << std::endl;
    }

    outfile << "# faces " << ui_faces << std::endl;

    //write out triangles
    for(unsigned int uitricnt = 0; uitricnt < ui_faces; uitricnt++)
    {
        UInt32 ind1 = pcl_indices->getValue(uitricnt * 3);
        UInt32 ind2 = pcl_indices->getValue(uitricnt * 3 + 1);
        UInt32 ind3 = pcl_indices->getValue(uitricnt * 3 + 2);
        UInt32 i1   = ind1 + offset + 1;
        UInt32 i2   = ind2 + offset + 1;
        UInt32 i3   = ind3 + offset + 1;

        outfile << "f ";
        outfile << i1 << "/" << i1 << "/" << i1 << " " <<
        i2 << "/" << i2 << "/" << i2 << " " <<
        i3 << "/" << i3 << "/" << i3 << std::endl;
    }

    return offset + uivertsize;
}

//! output the instance for debug purposes

void Surface::dump(            UInt32,
                         const BitVector) const
{
    SLOG << "Dump Surface NI" << endLog;
}

void Surface::onCreate(const Surface *source)
{
    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

    setSurfaceGLId(
        Window::registerGLObject(
            boost::bind(&Surface::handleGL,
                        SurfaceMTUncountedPtr(this), _1, _2, _3, _4),
            &Surface::handleDestroyGL));

    Inherited::onCreate(source);
}

void Surface::onDestroy(UInt32 id)
{
    if(getSurfaceGLId() > 0)
        Window::destroyGLObject(getSurfaceGLId(), 1);

    Inherited::onDestroy(id);
}

UInt32 Surface::handleGL(DrawEnv                *pEnv,
                         UInt32                  id,
                         Window::GLObjectStatusE mode,
                         UInt32                  uiOptions)
{
    if(mode == Window::initialize  ||
       mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if((getDirtyMask() & DONTTESSELLATE) == 0x0000)
        {
            if((getDirtyMask() & TESSELLATE) != 0x0000)
            {
                tessellate();
            }
            else if((getDirtyMask() & RETESSELLATE) != 0x0000)
            {
                reTessellate();
            }

            editDirtyMask() &= ~(TESSELLATE | RETESSELLATE);
        }
    }

    return 0;
}

void Surface::handleDestroyGL(DrawEnv                *pEnv,
                              UInt32                  id,
                              Window::GLObjectStatusE mode)
{
    UInt32  glid;
    Window *pWin = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);

        pWin->setGLObjectId(id, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Surface::handleDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
}

// Calculate the volume based on bounding box of the control points.
// If any of the control points have 0 weight, also take into
// account the tessellated geometry, otherwise the volume will be
// too small.
// FIXME: a better solution might be to do de Casteljau steps
// FIXME: until there are no control points w/ 0 weights and
// FIXME: redo the calculation...
void Surface::adjustVolume(Volume & volume)
{
    if(!_volumeCache.isEmpty())
    {
        // use cached volume.
        volume.setValid();
        volume.extendBy(_volumeCache);

        return;
    }

    GeoVectorProperty *pos             = getControlPoints();
    bool               has_zeroweights = false;

    _volumeCache.setValid();

    GeoPnt3fProperty *pPos    = dynamic_cast<GeoPnt3fProperty *>(pos);
    GeoPnt4fProperty *pRatPos = dynamic_cast<GeoPnt4fProperty *>(pos);

    if(pos == NULL)
        return;                  // Node has no points, no volume

    if(pPos != NULL)
    {
        for(UInt32 i = 0; i < pPos->size(); ++i)
        {
            _volumeCache.extendBy(pPos->getValue(i));
        }
    }
    else if(pRatPos != NULL)
    {
        for(UInt32 i = 0; i < pRatPos->size(); ++i)
        {
            Pnt3f pnt;

            if(osgAbs(pRatPos->getField()[i][3]) > DCTP_EPS)
            {
                pnt[0] = pRatPos->getField()[i][0] / pRatPos->getField()[i][3];
                pnt[1] = pRatPos->getField()[i][1] / pRatPos->getField()[i][3];
                pnt[2] = pRatPos->getField()[i][2] / pRatPos->getField()[i][3];
                _volumeCache.extendBy(pnt);
            }
            else
            {
                has_zeroweights = true;
            }
        }
    }

    if(has_zeroweights)
    {
        GeoVectorProperty *points = getPositions();
        if(points != NULL)
        {
            for(UInt32 i = 0; i < points->size(); ++i)
            {
                _volumeCache.extendBy(points->getValue<Pnt3f>(i));
            }
        }
        // FIXME: a warning should be printed here since the calculated
        // FIXME: volume will not be exact if there was no tessellated
        // FIXME: geometry, but in that case there's nothing to render
        // FIXME: anyway so we skip the warning (which would be
        // FIXME: unnecessarily (and annoyingly) printed at startup
        // FIXME: e.g. when the SSM::showall() method is called).
        // FIXME: Better suggestions are welcome.
    }

    volume.extendBy(_volumeCache);
}

/*! force tessalate
 */

void Surface::forceTessellate(void)
{
    editDirtyMask() |= DONTTESSELLATE;

    if((getDirtyMask() & TESSELLATE) != 0x0000)
    {
        tessellate();
    }
    else if((getDirtyMask() & RETESSELLATE) != 0x0000)
    {
        reTessellate();
    }

    editDirtyMask() &= ~(TESSELLATE | RETESSELLATE);
}

/*! flip
 */

void Surface::flip(void)
{
    if(_trimmedSurface != NULL)
        _trimmedSurface->flip();
}

void Surface::drawPrimitives(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(getSurfaceGLId(), pEnv);

    Inherited::drawPrimitives(pEnv);
}
