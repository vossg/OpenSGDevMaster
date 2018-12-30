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

#ifndef _OSGLISPSMTECHNIQUE_H_
#define _OSGLISPSMTECHNIQUE_H_

#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGProjection.h"
#include "OSGView.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

 class BoxVolume;
 class FrustumVolume;
 class PolygonBody;

class OSG_BASE_DLLMAPPING LiSPSMTechnique
{
    /*==========================  PUBLIC  =================================*/

  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Enumerations                               */
    /*! \{                                                                 */

    enum Mode
    {
        NOPT = 1,
        REPARAMETRIZED,
        ARBITRARY,
        PSEUDO_NEAR,
        MODE_COUNT
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Types                                  */
    /*! \{                                                                 */

    typedef std::vector<Vec2f>                  VecOfVec2fT;
    typedef std::vector< VecOfVec2fT >          VecVecOfVec2fT;
    typedef std::vector<Real32>                 VecParamsT;
    typedef std::vector<Pnt3f>                  VecVerticesT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LiSPSMTechnique(UInt32 nbrOfSplits);
    LiSPSMTechnique(const LiSPSMTechnique& rhs);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~LiSPSMTechnique();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    LiSPSMTechnique& operator=(const LiSPSMTechnique& rhs);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set                                       */
    /*! \{                                                                 */

    void    setLightView    (const Matrix& matrix, const View& view);
    void    setLightProjMat (const Matrix& matrix, Projection::Type type);

    void    setCamView      (const Matrix& matrix, const View& view);
    void    setCamProjMat   (const Matrix& matrix, Projection::Type type);

    void    setGamma        (Real32 gamma);
    void    setFieldOfView  (Real32 fov);
    void    setSplitParam   (Real32 lambda);

    void    setPseudoNear   (Real32 value);
    void    setPseudoFar    (Real32 value);

    void    setParamN       (Real32 n, UInt32 split);
    void    setMode         (Mode mode);
    void    setArbScaled    (bool enable);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    const VecParamsT&       getParamN           () const;
    Mode                    getMode             () const;
    bool                    getArbScaled        () const;

    Real32                  getParam            () const;
    const VecVecOfVec2fT&   getDistances        () const;

    const Matrix&           getLiSPMtx          (
                                UInt32                  split,
                                const PolygonBody&      bodyB,
                                const FrustumVolume&    camFrust,
                                const FrustumVolume*    lightFrust,
                                const BoxVolume&        sceneAABB,
                                const Vec2f&            zRange
                             );


    // Test Begin
    const Matrix&           getLiSPMtx          (
                                UInt32                  split,
                                const PolygonBody&      bodyB,
                                const VecVerticesT&     camFrustCorners,
                                const FrustumVolume*    lightFrust,
                                const BoxVolume&        sceneAABB,
                                const Vec2f&            zRange
                             );
    // Test End

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operations                                */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    Pnt3f       getNearCamPoint (
                    const VecVerticesT&     camFrustCorners,
                    const FrustumVolume*    lightFrust,
                    const BoxVolume&        sceneAABB
                );
    Real32      getDistN        (
                    const Matrix&           lViewProjMat,
                    const BoxVolume&        bodyBaabb_LS,
                    const Pnt3f&            nearCamPt,
                    Real32                  nPseudo,
                    Real32                  fPseudo,
                    UInt32                  split
                );
    Real32      getReparamDistN (
                    const Matrix&           lViewProjMat,
                    const BoxVolume&        bodyBaabb_LS,
                    const Pnt3f&            nearCamPt,
                    const Pnt3f&            nearRightBottom,
                    const Pnt3f&            nearRightTop,
                    Real32                  nPseudo,
                    Real32                  fPseudo,
                    UInt32                  split
                );
    Real32      getDistArbN     (
                    const Matrix&           lViewProjMat,
                    const BoxVolume&        bodyBaabb_LS,
                    const Pnt3f&            nearCamPt,
                    UInt32                  split,
                    const Vec2f&            vZRange
                );
    Real32      getPseudoNearN  (
                    const Matrix&           lViewProjMat,
                    const BoxVolume&        bodyBaabb_LS,
                    const Pnt3f&            nearCamPt,
                    Real32                  nPseudo,
                    UInt32                  split
                );

    bool        getFrustumMatrix(        Matrix& matrix,
                                         Real32 l, Real32 r,
                                         Real32 b, Real32 t,
                                         Real32 n, Real32 f) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operations                                */
    /*! \{                                                                 */

    void        calcZ0Z1_LS     (
                    Pnt3f&                  z0_LS,
                    Pnt3f&                  z1_LS,
                    const Matrix&           lViewProjMat,
                    const BoxVolume&        bodyBaabb_LS,
                    const Pnt3f&            nearCamPt
                ) const;

    /*! \}                                                                 */

  private:
    static const Matrix _exchangeAxisTrafo;

  private:
    View                _cView;
    Projection::Type    _cType;

    View                _lView;
    Projection::Type    _lType;

    Mode                _mode;
    bool                _arbScaled;

    Real32              _gamma;
    Real32              _fov;
    Real32              _eta;
    Real32              _lambda;
    Real32              _pseudoNear;
    Real32              _pseudoFar;


    Matrix              _lViewMat;
    Matrix              _lProjMat;
    Matrix              _cViewMat;
    Matrix              _cProjMat;
    Matrix              _liSPMat;
    VecVecOfVec2fT      _distances;
    VecVecOfVec2fT      _nParams;
    VecParamsT          _paramN;
};

OSG_END_NAMESPACE

#include "OSGLiSPSMTechnique.inl"

#endif // _OSGLISPSMTECHNIQUE_H_
