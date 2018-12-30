/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include "OSGLiSPSMTechnique.h"

#include <OSGBaseFunctions.h>

#include "OSGBoxVolume.h"
#include "OSGFrustumVolume.h"
#include "OSGPolygonBody.h"

#include <OSGMatrixUtility.h>
#include "OSGPlane.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::LiSPSMTechnique
*/

const Matrix LiSPSMTechnique::_exchangeAxisTrafo = Matrix (
    1.f,  0.f, 0.f, 0.f,
    0.f,  0.f, 1.f, 0.f,        // y -> z
    0.f,  1.f, 0.f, 0.f,        // z -> y
    0.f,  0.f, 0.f, 1.f
);


/*-------------------------- constructor ----------------------------------*/

LiSPSMTechnique::LiSPSMTechnique(UInt32 nbrOfSplits)
: _cView        (Pnt3f(0.f, 0.f, 0.f),
                 Pnt3f(0.f, 0.f, 1.f),
                 Vec3f(0.f, 1.f, 0.f))          // camera view (eye, center, up)
, _cType        (Projection::PERSPECTIVE)       // camera projection type
, _lView        (Pnt3f(0.f, 1.f, 0.f),
                 Pnt3f(0.f, 0.f, 0.f),
                 Vec3f(0.f, 0.f,-1.f))          // light  view (eye, center, up)
, _lType        (Projection::ORTHOGRAPHIC)      // light projection type
, _mode         (NOPT)                          // optimization modes: NOPT, REPARAMETRIZED, ARBITRARY, PSEUDO_NEAR
, _arbScaled    (false)
, _gamma        (90.f)
, _fov          (45.f)
, _eta          (-1.f)
, _lambda       (0.5f)                          // helps calc schemeFactor
, _pseudoNear   (0.f)
, _pseudoFar    (0.f)
, _lViewMat     ()                              // light view matrix (identity)
, _lProjMat     ()                              // light projection matrix (identity)
, _cViewMat     ()                              // camera view matrix (identity)
, _cProjMat     ()                              // camera projection matrix (identity)
, _liSPMat      ()                              // light space perspective shadow matrix
, _distances    (MODE_COUNT)                    // distances for each mode and for each split
, _nParams      (MODE_COUNT)                    // parameters for each mode and for each split
, _paramN       (nbrOfSplits, 1.f)              // near plane for each split
{
    for (UInt32 i = NOPT; i < MODE_COUNT; ++i)
    {
        _nParams  [i].resize(nbrOfSplits);
        _distances[i].resize(nbrOfSplits);
    }
}

LiSPSMTechnique::LiSPSMTechnique(const LiSPSMTechnique& rhs)
: _cView        (rhs._cView)
, _cType        (rhs._cType)
, _lView        (rhs._lView)
, _lType        (rhs._lType)
, _mode         (rhs._mode)
, _arbScaled    (rhs._arbScaled)
, _gamma        (rhs._gamma)
, _fov          (rhs._fov)
, _eta          (rhs._eta)
, _lambda       (rhs._lambda)
, _pseudoNear   (rhs._pseudoNear)
, _pseudoFar    (rhs._pseudoFar)
, _lViewMat     (rhs._lViewMat)
, _lProjMat     (rhs._lProjMat)
, _cViewMat     (rhs._cViewMat)
, _cProjMat     (rhs._cProjMat)
, _liSPMat      (rhs._liSPMat)
, _distances    (rhs._distances)
, _nParams      (rhs._nParams)
, _paramN       (rhs._paramN)
{
}

LiSPSMTechnique::~LiSPSMTechnique()
{
}

LiSPSMTechnique& LiSPSMTechnique::operator=(const LiSPSMTechnique& rhs)
{
    if (&rhs == this) return *this;

    _cView        = _cView;
    _cType        = _cType;
    _lView        = _lView;
    _lType        = _lType;
    _mode         = _mode;
    _arbScaled    = _arbScaled;
    _gamma        = _gamma;
    _fov          = _fov;
    _eta          = _eta;
    _lambda       = _lambda;
    _pseudoNear   = _pseudoNear;
    _pseudoFar    = _pseudoFar;
    _lViewMat     = _lViewMat;
    _lProjMat     = _lProjMat;
    _cViewMat     = _cViewMat;
    _cProjMat     = _cProjMat;
    _liSPMat      = _liSPMat;
    _distances    = _distances;
    _nParams      = _nParams;
    _paramN       = _paramN;

    return *this;
}

const Matrix& LiSPSMTechnique::getLiSPMtx(
    UInt32                  split,
    const PolygonBody&      bodyB,
    const FrustumVolume&    camFrust,
    const FrustumVolume*    lightFrust,
    const BoxVolume&        sceneAABB,
    const Vec2f&            zRange)
{
    VecVerticesT camFrustCorners(FrustumVolume::CORNER_COUNT);
    for (std::size_t i = 0; i < FrustumVolume::CORNER_COUNT; ++i)
    {
        camFrustCorners[i] = camFrust.getCorner(static_cast<FrustumVolume::Corner>(i));
    }

    return getLiSPMtx(split, bodyB, camFrustCorners, lightFrust, sceneAABB, zRange);
}

const Matrix& LiSPSMTechnique::getLiSPMtx(
    UInt32                  split,
    const PolygonBody&      bodyB,
    const VecVerticesT&     camFrustCorners,
    const FrustumVolume*    lightFrust,
    const BoxVolume&        sceneAABB,
    const Vec2f&            vZRange)
{
    Matrix lProjMat = _lProjMat;
    Matrix lViewMat = _lViewMat;

    const std::size_t nbrOfSplits = _paramN.size();

    const PolygonBody::VecVerticesT& vertices = bodyB.getVertices();
    std::size_t size = bodyB.getNumVertices();

    Pnt3f nearCamPt = getNearCamPoint(camFrustCorners, lightFrust, sceneAABB);

    Matrix lViewProjMat(lProjMat);  // Matrix lViewProjMat = lProjMat * lViewMat;
    lViewProjMat.mult(lViewMat);

    Vec3f lViewDir = _lView.getCenter() - _lView.getEye(); lViewDir.normalize();

    Vec3f viewDir(_cView.getCenter()-_cView.getEye()); viewDir.normalize();
    Vec3f leftVec(_cView.getUp().cross(viewDir)); leftVec.normalize();
    Vec3f up     (lViewDir.cross(leftVec)); up.normalize();

    const Pnt3f center = nearCamPt + viewDir;

    Pnt3f trCenter, trNearCamPt;

    lViewProjMat.multFull(center,    trCenter);     // multFull
    lViewProjMat.multFull(nearCamPt, trNearCamPt);  // multFull

    Vec3f projViewDir_LS(trCenter - trNearCamPt);

    projViewDir_LS[2] = 0.f;

    //
    // do Light Space Perspective shadow mapping
    // rotate the lightspace so that the proj light view always points upwards
    // calculate a frame matrix that uses the projViewDir[light-space] as up vector
    // look(from position, into the direction of the projected direction, with unchanged up-vector)
    //
    Matrix viewMat;
    MatrixLookAtGL(viewMat, Pnt3f(0.f, 0.f, 0.f), projViewDir_LS, Vec3f(0.f, 0.f, 1.f));

    lProjMat.multLeft(viewMat);

    lViewProjMat = lProjMat;
    lViewProjMat.mult(lViewMat);


    BoxVolume bodyBaabb_LS;
    for (UInt32 i = 0; i < size; ++i)
    {
        Pnt3f pnt;
        lViewProjMat.multFull(vertices[i], pnt);
        bodyBaabb_LS.extendBy(pnt);
    }

    _distances[NOPT][split][0] =
            getDistN(
                lViewProjMat,
                bodyBaabb_LS,
                nearCamPt,
                split == 0             ? _pseudoNear : 0.f,
                split == nbrOfSplits-1 ? _pseudoFar  : 0.f,
                split
            );

    _distances[REPARAMETRIZED][split][0] =
            getReparamDistN(
                lViewProjMat,
                bodyBaabb_LS,
                nearCamPt,
                camFrustCorners[FrustumVolume::NEAR_RIGHT_BOTTOM],
                camFrustCorners[FrustumVolume::NEAR_RIGHT_TOP],
                split == 0             ? _pseudoNear : 0.f,
                split == nbrOfSplits-1 ? _pseudoFar  : 0.f,
                split
            );

    _distances[ARBITRARY][split][0] =
            getDistArbN(
                lViewProjMat,
                bodyBaabb_LS,
                nearCamPt,
                split,
                vZRange
            );

    _distances[PSEUDO_NEAR][split][0] =
            getPseudoNearN(
                lViewProjMat,
                bodyBaabb_LS,
                nearCamPt,
                split == 0 ? _pseudoNear : 0.f,
                split
            );



    Real32 projLen = osgAbs( viewDir.dot(nearCamPt - _cView.getEye()) );

    Pnt3f nearCamCtr   ( _cView.getEye() + projLen * viewDir );

    Pnt3f nearCamCtr_LS;
    lViewProjMat.multFull(nearCamCtr, nearCamCtr_LS);


    //
    // c_start has the x and y coordinate of nearCamCtr_LS, the z coord of B.min()
    //
    const Pnt3f cStart_LS = Pnt3f( nearCamCtr_LS.x(), nearCamCtr_LS.y(), bodyBaabb_LS.getMax().z() );

    for (UInt32 mode = NOPT; mode < MODE_COUNT; ++mode)
    {
        Real32 n = _distances[mode][split][0];

        if (n < std::numeric_limits<Real32>::infinity())
        {
            //
            // calc depth range of the perspective transform depth or light space y extents
            //
            Real32 zRange = osgAbs( bodyBaabb_LS.getMin().z() - bodyBaabb_LS.getMax().z() );

            _distances[mode][split][1] = n + zRange;

            if (mode == static_cast<UInt32>(_mode))
            {
                //
                // calc projection center
                //
                Pnt3f projCenter( cStart_LS + Vec3f(0.f, 0.f, n) );

                Pnt3f projCtr;
                Matrix lInvViewProjMat;
                lViewProjMat.inverse(lInvViewProjMat);

                lInvViewProjMat.multFull(projCenter, projCtr);

                //
                // the lispsm perspective transformation
                // here done with a standard FrustumVolume call that maps lispPersp onto the unit cube
                //
                Matrix liSP;
                getFrustumMatrix(liSP, -1.f, 1.f, -1.f, 1.f, n, n + zRange);

                Matrix trans;
                trans.setTranslate(-projCenter);

                liSP.mult(trans);
                liSP.multLeft(_exchangeAxisTrafo);
                liSP.mult(viewMat);

                _liSPMat = liSP;
            }
        }
        else
        {
            const Real32 _Infinity  = 9.0e10f;

            _distances[mode][split] = Vec2f(_Infinity, _Infinity);
            _nParams  [mode][split] = Vec2f(_Infinity, _Infinity);

            if (mode == static_cast<UInt32>(_mode))
                _liSPMat.setIdentity();
        }
    }

    return _liSPMat;
}

Pnt3f LiSPSMTechnique::getNearCamPoint(
    const VecVerticesT&     camFrustCorners,
    const FrustumVolume*    lightFrust,
    const BoxVolume&        sceneAABB)
{
    PolygonBody bodyLVS;

    Pnt3f nlt, nlb, nrt, nrb, flt, flb, frt, frb;

    nlt = camFrustCorners[FrustumVolume::NEAR_LEFT_TOP];
    nlb = camFrustCorners[FrustumVolume::NEAR_LEFT_BOTTOM];
    nrt = camFrustCorners[FrustumVolume::NEAR_RIGHT_TOP];
    nrb = camFrustCorners[FrustumVolume::NEAR_RIGHT_BOTTOM];
    flt = camFrustCorners[FrustumVolume::FAR_LEFT_TOP];
    flb = camFrustCorners[FrustumVolume::FAR_LEFT_BOTTOM];
    frt = camFrustCorners[FrustumVolume::FAR_RIGHT_TOP];
    frb = camFrustCorners[FrustumVolume::FAR_RIGHT_BOTTOM];

    bodyLVS.add(new Polygon(nlb, nrb, nrt, nlt));   // near polygon ccw
    bodyLVS.add(new Polygon(flt, frt, frb, flb));   // far polygon ccw
    bodyLVS.add(new Polygon(nlb, nlt, flt, flb));   // left polygon ccw
    bodyLVS.add(new Polygon(nrb, frb, frt, nrt));   // right polygon ccw
    bodyLVS.add(new Polygon(flb, frb, nrb, nlb));   // bottom polygon ccw
    bodyLVS.add(new Polygon(frt, flt, nlt, nrt));   // top polygon ccw

    bodyLVS.clip(sceneAABB);

    //
    // perspective lightProjection
    //
    if (_lType == Projection::PERSPECTIVE)
        bodyLVS.clip(*lightFrust);

    bodyLVS.createUniqueVertices();

    const Polygon::VecVerticesT& vertices = bodyLVS.getVertices();
    std::size_t size = vertices.size();

    if (size)
    {
        //
        // transform to eyespace and find the nearest point to camera -> z = max()
        //
        std::size_t index = 0;

        for (std::size_t i = 1; i < size; ++i)
        {
            Pnt3f p1, p2;

            _cViewMat.multFull(vertices[index], p1);
            _cViewMat.multFull(vertices[i],     p2);

            if ( p1.z() < p2.z() )
                index = i;
        }
        return vertices[index];
    }
    else
    {
        Vec3f cViewDir(_cView.getCenter() - _cView.getEye());
        cViewDir.normalize();
        return _cView.getEye() + cViewDir;
    }

    return Pnt3f(0,0,0);
}

Real32 LiSPSMTechnique::getDistN(
    const Matrix&           lViewProjMat,
    const BoxVolume&        bodyBaabb_LS,
    const Pnt3f&            nearCamPt,
    Real32                  nPseudo,
    Real32                  fPseudo,
    UInt32                  split)
{
    Pnt3f z0_LS;
    Pnt3f z1_LS;

    calcZ0Z1_LS(
        z0_LS,
        z1_LS,
        lViewProjMat,
        bodyBaabb_LS,
        nearCamPt);

    Matrix lInvViewProjMat;
    lViewProjMat.inverse(lInvViewProjMat);

    //
    // transform to world
    //
    Pnt3f z0_WS, z1_WS;
    lInvViewProjMat.multFull(z0_LS, z0_WS);
    lInvViewProjMat.multFull(z1_LS, z1_WS);

    //
    // transform to eye
    //
    Pnt3f z0_ES, z1_ES;
    _cViewMat.multFull(z0_WS, z0_ES);
    _cViewMat.multFull(z1_WS, z1_ES);

    const Real32 n_e = osgAbs(z0_ES.z());
    const Real32 f_e = osgAbs(z1_ES.z());

    const Real32 zRange_LS = osgAbs(bodyBaabb_LS.getMax().z() - bodyBaabb_LS.getMin().z());
    const Real32 zRange_ES = osgAbs(f_e - n_e);

    const Real32 n = zRange_LS / (f_e - n_e) * (n_e + osgSqrt((n_e + nPseudo * (f_e - n_e)) * (f_e - fPseudo * (f_e - n_e))));

    _nParams[NOPT][split][0] = zRange_ES / zRange_LS * n;
    _nParams[NOPT][split][1] = _nParams[NOPT][split][0] + zRange_ES;

    return n;
}

Real32 LiSPSMTechnique::getReparamDistN(
    const Matrix&           lViewProjMat,
    const BoxVolume&        bodyBaabb_LS,
    const Pnt3f&            nearCamPt,
    const Pnt3f&            nearRightBottom,
    const Pnt3f&            nearRightTop,
    Real32                  nPseudo,
    Real32                  fPseudo,
    UInt32                  split)
{
    Pnt3f z0_LS;
    Pnt3f z1_LS;

    calcZ0Z1_LS(
        z0_LS,
        z1_LS,
        lViewProjMat,
        bodyBaabb_LS,
        nearCamPt);

    Matrix lInvViewProjMat;
    lViewProjMat.inverse(lInvViewProjMat);

    //
    // transform to world
    //
    Pnt3f z0_WS, z1_WS;
    lInvViewProjMat.multFull(z0_LS, z0_WS);
    lInvViewProjMat.multFull(z1_LS, z1_WS);

    //
    // transform to eye
    //
    Pnt3f z0_ES, z1_ES;
    _cViewMat.multFull(z0_WS, z0_ES);
    _cViewMat.multFull(z1_WS, z1_ES);

    const Real32 theta   = _fov / 2.f;

    const Real32 gamma_a = theta / 3.f;
    const Real32 gamma_b = theta;
    const Real32 gamma_c = theta + 0.3f * (90.f - theta);

    const Real32 eta_b   = -0.2f;
    const Real32 eta_c   = 0.f;

    const Real32 n_e     = osgAbs(z0_ES.z());
    const Real32 f_e     = osgAbs(z1_ES.z());

    if (_gamma <= gamma_a)
    {
        _eta = -1;
    }
    else if (_gamma > gamma_a && _gamma <= gamma_b)
    {
        _eta = -1 + (eta_b + 1) * (_gamma - gamma_a) / (gamma_b - gamma_a);
    }
    else if (_gamma > gamma_b && _gamma <= gamma_c)
    {
        _eta = eta_b + (eta_c - eta_b) * osgSin(90.f * (_gamma - gamma_b)/(gamma_c - gamma_b) * OSG::Pi / 180.f);
    }
    else // gamma > gamma_c
    {
        _eta = eta_c;
    }

    const Real32 w_n       = (nearRightBottom - nearRightTop).length();

    const Real32 w_s       = (f_e - n_e) / osgCos(theta * OSG::Pi / 180.f);

    const Real32 w_n_proj  = w_n * osgCos(_gamma * OSG::Pi / 180.f);

    const Real32 w_s1_proj = _gamma <= theta
                                ? w_s * (1 - osgCos((theta - _gamma) * OSG::Pi / 180.f))
                                : 0.f;

    const Real32 w_s2_proj = w_s * osgSin((theta + _gamma) * OSG::Pi / 180.f);

    const Real32 w_lz      = w_n_proj + w_s1_proj + w_s2_proj; // equivalent to w_ly in paper

    const Real32 alpha     = f_e / n_e;


    Real32 n = 0.f;

    if (_eta < 0.f)
    {
        n = w_lz / (alpha - 1) * (1 + osgSqrt(alpha) - _eta * (alpha - 1)) / (_eta + 1);
    }
    else
    {
        n = w_lz / (alpha - 1) * (1 + osgSqrt(alpha)) / (_eta * osgSqrt(alpha) + 1);
    }

    const Real32 zRange_LS = osgAbs(bodyBaabb_LS.getMax().z() - bodyBaabb_LS.getMin().z());
    const Real32 zRange_ES = f_e - n_e;

    _nParams[REPARAMETRIZED][split] = Vec2f(n, n + zRange_ES);

    return zRange_LS / zRange_ES * n;
}

Real32 LiSPSMTechnique::getDistArbN(
    const Matrix&           lViewProjMat,
    const BoxVolume&        bodyBaabb_LS,
    const Pnt3f&            nearCamPt,
    UInt32                  split,
    const Vec2f&            zRange)
{
    if (_arbScaled && split > 0)
    {
        const Real32 n = zRange.x();
        const Real32 f = zRange.y();
        const Real32 s = split / static_cast<Real32>(_paramN.size());

        const Real32 schemeFactor = ((1.f - _lambda) * (n + (f - n) * s) + _lambda * (n * powf(f / n, s)));

        _nParams[ARBITRARY][split] = Vec2f( schemeFactor * _nParams[ARBITRARY][0] );
        _paramN[split]             = _nParams[ARBITRARY][split][0];

        return _distances[ARBITRARY][0][0] / _nParams[ARBITRARY][0][0] * _nParams[ARBITRARY][split][0];
    }
    else
    {
        Pnt3f z0_LS;
        Pnt3f z1_LS;

        calcZ0Z1_LS(
            z0_LS,
            z1_LS,
            lViewProjMat,
            bodyBaabb_LS,
            nearCamPt);


        Matrix lInvViewProjMat;
        lViewProjMat.inverse(lInvViewProjMat);

        //
        // transform to world
        //
        Pnt3f z0_WS, z1_WS;
        lInvViewProjMat.multFull(z0_LS, z0_WS);
        lInvViewProjMat.multFull(z1_LS, z1_WS);

        //
        // transform to eye
        //
        Pnt3f z0_ES, z1_ES;
        _cViewMat.multFull(z0_WS, z0_ES);
        _cViewMat.multFull(z1_WS, z1_ES);

        const Real32 n_e = osgAbs(z0_ES.z());
        const Real32 f_e = osgAbs(z1_ES.z());

        const Real32 zRange_LS = osgAbs(bodyBaabb_LS.getMax().z() - bodyBaabb_LS.getMin().z());
        const Real32 zRange_ES = f_e - n_e;

        const Real32 n = _paramN[split];

        _nParams[ARBITRARY][split] = Vec2f(n, n + zRange_ES);

        return zRange_LS / zRange_ES * n;
    }
}

Real32 LiSPSMTechnique::getPseudoNearN(
    const Matrix&           lViewProjMat,
    const BoxVolume&        bodyBaabb_LS,
    const Pnt3f&            nearCamPt,
    Real32                  nPseudo,
    UInt32                  split)
{
    if (nPseudo >= 2 / 3.f)
        nPseudo = 2 / 3.f;

    Pnt3f z0_LS;
    Pnt3f z1_LS;

    calcZ0Z1_LS(
        z0_LS,
        z1_LS,
        lViewProjMat,
        bodyBaabb_LS,
        nearCamPt);

    Matrix lInvViewProjMat;
    lViewProjMat.inverse(lInvViewProjMat);

    //
    // transform to world
    //
    Pnt3f z0_WS, z1_WS;
    lInvViewProjMat.multFull(z0_LS, z0_WS);
    lInvViewProjMat.multFull(z1_LS, z1_WS);

    //
    // transform to eye
    //
    Pnt3f z0_ES, z1_ES;
    _cViewMat.multFull(z0_WS, z0_ES);
    _cViewMat.multFull(z1_WS, z1_ES);

    const Real32 n_e = osgAbs(z0_ES.z());
    const Real32 f_e = osgAbs(z1_ES.z());

    const Real32 zRange_LS = osgAbs(bodyBaabb_LS.getMax().z() - bodyBaabb_LS.getMin().z());
    const Real32 zRange_ES = f_e - n_e;

    const Real32 n_0 = n_e / zRange_ES;
    const Real32 n1  = n_0 + osgSqrt( ( n_0 + nPseudo ) * ( n_0 + 1 ) );
    const Real32 n2  = osgAbs( nPseudo / ( 2 - 3 * nPseudo ) );

    Real32 n = osgMax(n1, n2);

    _nParams[PSEUDO_NEAR][split] = Vec2f(n * zRange_ES, n * zRange_ES + zRange_ES);

    return zRange_LS * n;
}

void LiSPSMTechnique::calcZ0Z1_LS(
    Pnt3f&                  z0_LS,
    Pnt3f&                  z1_LS,
    const Matrix&           lViewProjMat,
    const BoxVolume&        bodyBaabb_LS,
    const Pnt3f&            nearCamPt) const
{
    //
    // calculate the parallel plane to the near plane through eye
    //
    Plane planeZ0(_cView.getCenter() - _cView.getEye(), nearCamPt);

    //
    // transform into lightspace with transposed inverted lightViewProj
    //
    Matrix lTranspInvViewProjMat;
    lViewProjMat.inverse(lTranspInvViewProjMat);
    lTranspInvViewProjMat.transpose();

    planeZ0.transformTransposedInverse(lTranspInvViewProjMat);

    //
    // get the parameters of plane from the plane equation n dot d = 0
    //
    const Vec3f& normal   = planeZ0.getNormal();
    const Real32 distance = planeZ0.getDistanceFromOrigin();

    //
    // z0_LS has the x coordinate of nearCamPoint_LS, the y coord of
    // the plane intersection and the z coord of bodyB_LS.max()
    //
    const Real32 bMaxZ = bodyBaabb_LS.getMax().z();
    const Real32 bMinZ = bodyBaabb_LS.getMin().z();

    Pnt3f nearCamPt_LS;
    lViewProjMat.multFull(nearCamPt, nearCamPt_LS);

    z0_LS = Pnt3f(
                nearCamPt_LS.x(),
                (distance - normal.z() * bMaxZ - normal.x() * nearCamPt_LS.x()) / normal.y(),
                bMaxZ
            );

    z1_LS = Pnt3f(
                z0_LS.x(),
                z0_LS.y(),
                bMinZ
            );
}

bool LiSPSMTechnique::getFrustumMatrix(
    Matrix& matrix,
    Real32 l, Real32 r,
    Real32 b, Real32 t,
    Real32 n, Real32 f) const
{
    OSG::Real32 eps = OSG::TypeTraits<OSG::Real32>::getDefaultEps();
    if (osgAbs(r-l) < eps || osgAbs(t-b) < eps || osgAbs(n-f) < eps)
        return false;

    matrix.setValue(
        2*n/(r-l), .0f,       (l+r)/(r-l), .0f,
        .0f,       2*n/(t-b), (t+b)/(t-b), .0f,
        .0f,       .0f,       f/(n-f),     n*f/(n-f),
        .0f,       .0f,       -1.0f,       .0f
    );

    return true;
}

OSG_END_NAMESPACE
