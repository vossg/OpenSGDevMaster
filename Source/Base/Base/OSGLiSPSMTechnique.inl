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

OSG_BEGIN_NAMESPACE

inline
void LiSPSMTechnique::setLightView(const Matrix& matrix, const View& view)
{
    _lViewMat = matrix;
    _lView    = view;
}

inline
void LiSPSMTechnique::setLightProjMat(const Matrix& matrix, Projection::Type type)
{
    _lProjMat = matrix;
    _lType    = type;
}

inline
void LiSPSMTechnique::setCamView(const Matrix& matrix, const View& view)
{
    _cViewMat = matrix;
    _cView    = view;
}

inline
void LiSPSMTechnique::setCamProjMat(const Matrix& matrix, Projection::Type type)
{
    _cProjMat = matrix;
    _cType    = type;
}

inline
void LiSPSMTechnique::setGamma(Real32 gamma)
{
    _gamma = gamma;
}

inline
void LiSPSMTechnique::setFieldOfView(Real32 fov)
{
    _fov = fov;
}

inline
void LiSPSMTechnique::setSplitParam(Real32 lambda)
{
    _lambda = lambda;
}

inline
void LiSPSMTechnique::setPseudoNear(Real32 value)
{
    _pseudoNear = value;
}

inline
void LiSPSMTechnique::setPseudoFar(Real32 value)
{
    _pseudoFar = value;
}

inline
const LiSPSMTechnique::VecParamsT& LiSPSMTechnique::getParamN() const
{
    return _paramN;
}

inline
void LiSPSMTechnique::setParamN(Real32 n, UInt32 split)
{
    if (split < _paramN.size())
        _paramN[split] = n;
}

inline
LiSPSMTechnique::Mode LiSPSMTechnique::getMode() const
{
    return _mode;
}

inline
void LiSPSMTechnique::setMode(Mode mode)
{
    _mode = mode;
}

inline
bool LiSPSMTechnique::getArbScaled() const
{
    return _arbScaled;
}

inline
void LiSPSMTechnique::setArbScaled(bool enable)
{
    _arbScaled = enable;
}

inline
Real32 LiSPSMTechnique::getParam() const
{
    return _eta;
}

inline
const LiSPSMTechnique::VecVecOfVec2fT& LiSPSMTechnique::getDistances() const
{
    return _nParams;
}


OSG_END_NAMESPACE

