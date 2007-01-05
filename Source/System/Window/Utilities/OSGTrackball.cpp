/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdio>

#include "OSGTrackball.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Trackball
    \ingroup GrpSystemWindows

The old Trackball class. Use is deprecated, use the TrackballNavigator instead,
it's a lot easier to use.

*/

Trackball::Trackball(Real32 rSize) :
    _bSum(false),
    _bAutoPosition(false),
    _gMode(OSGCamera),
    _gTransMode(OSGFixedZ),
    _gTransGen (OSGAbsoluteTranslation),
    _rAutoPositionStep(1.),
    _rAutoPositionIncrement(1.),
    _rTrackballSize(rSize),
    _rTranslationScale(1.),
    _qVal(),
    _pVal(),
    _qValStart(),
    _pValStart(),
    _pRotationCenter()
{
}

Trackball::~Trackball(void)
{
}

void Trackball::setSize( Real32 s )
{
    _rTrackballSize = s;
}

Real32 Trackball::getSize() const
{
    return _rTrackballSize;
}

Real32 Trackball::projectToSphere(Real32 rRadius, Real32 rX, Real32 rY)
{
    Real32 d, t, z;

    d = sqrt(rX * rX + rY * rY);

    if (d < rRadius * 0.70710678118654752440f) 
    {    /* Inside sphere */
        z = sqrt(rRadius * rRadius - d * d);
    } 
    else 
    {           /* On hyperbola */
        t = rRadius / 1.41421356237309504880f;
        z = t * t / d;
    }

    return z;
}

void Trackball::setSum(bool bVal)
{
    _bSum = bVal;
}

void Trackball::updateRotation(Real32 rLastX,    Real32 rLastY, 
                                 Real32 rCurrentX, Real32 rCurrentY)
{
    Quaternion qCurrVal;

    Vec3f  gAxis; /* Axis of rotation */
    Real32 rPhi = 0.f;  /* how much to rotate about axis */
    Vec3f  gP1;
    Vec3f  gP2;
    Vec3f  gDiff;
    Real32 rTmp;

    if( (osgAbs(rLastX - rCurrentX) > Eps) ||
        (osgAbs(rLastY - rCurrentY) > Eps))
    {
        /*
         * First, figure out z-coordinates for projection of P1 and P2 to
         * deformed sphere
         */
        
        gP1.setValues(  rLastX,
                        rLastY,
                         projectToSphere(_rTrackballSize, rLastX, rLastY));

        gP2.setValues(  rCurrentX,
                        rCurrentY,
                        projectToSphere(_rTrackballSize, rCurrentX, rCurrentY));
        
        /*
         *  Now, we want the cross product of P1 and P2
         */

        gAxis = gP2;
        gAxis.crossThis(gP1);

        /*
         *  Figure out how much to rotate around that axis.
         */

        gDiff = gP2;
        gDiff -= gP1;

        rTmp = gDiff.length() / (2.0f * _rTrackballSize);


        /*
         * Avoid problems with out-of-control values...
         */
        
        if(rTmp > 1.0) 
            rTmp = 1.0;

        if(rTmp < -1.0) 
            rTmp = -1.0;

        if(_gMode == OSGObject)
            rPhi = (Real32) -2.0 * osgASin(rTmp);
        else
            rPhi = (Real32)  2.0 * osgASin(rTmp);

    }

    if(_bSum == false)
    {
        _qVal.setValueAsAxisRad(gAxis, rPhi);
    }
    else
    {
        qCurrVal.setValueAsAxisRad(gAxis, rPhi);
        _qVal *= qCurrVal;
//        _qVal.multLeft(qCurrVal);
    }
}

void Trackball::updatePosition(Real32 rLastX,    Real32 rLastY, 
                                 Real32 rCurrentX, Real32 rCurrentY)
{
    if(_gTransMode == OSGFree)
    {
        if(_gTransGen == OSGAbsoluteTranslation)
        {
            _pVal[0] += (rLastX - rCurrentX) * -_rTranslationScale;
            _pVal[1] += (rLastY - rCurrentY) * -_rTranslationScale;
        }
        else
        {
            Vec3f tmpVec((rLastX - rCurrentX) * -_rTranslationScale,
                         (rLastY - rCurrentY) * -_rTranslationScale,
                         0.);
                
            Matrix m1;

            m1.setRotate(getRotation());

            m1.mult(tmpVec);

            _pVal[0] += tmpVec[0];
            _pVal[1] += tmpVec[1];
            _pVal[2] += tmpVec[2];
        }
    }   
}

void Trackball::updatePositionNeg(Real32 /*rLastX*/,    Real32 rLastY, 
                                    Real32 /*rCurrentX*/, Real32 rCurrentY)
{
    if(_gTransMode == OSGFree)
    {
        if(_gTransGen == OSGAbsoluteTranslation)
        {
            _pVal[2] += (rLastY - rCurrentY) * -_rTranslationScale;
        }
        else
        {
            Vec3f tmpVec(0.,
                         0.,
                         (rLastY - rCurrentY) * -_rTranslationScale);
            
            Matrix m1;
            
            m1.setRotate(getRotation());

            m1.mult(tmpVec);

            _pVal[0] += tmpVec[0];
            _pVal[1] += tmpVec[1];
            _pVal[2] += tmpVec[2];
        }
    }
}

void Trackball::setAutoPositionIncrement(Real32 rVal)
{
    _rAutoPositionIncrement = rVal;
}

void Trackball::setAutoPosition(bool bVal)
{
    _bAutoPosition = bVal;
    _rAutoPositionStep = -_rAutoPositionIncrement;
}

void Trackball::setAutoPositionNeg(bool bVal)
{
    _bAutoPosition = bVal;
    _rAutoPositionStep = _rAutoPositionIncrement;
}

void Trackball::setMode(Mode gMode)
{
    _gMode = gMode;
}

void Trackball::setTranslationMode(TranslationMode gMode)
{
    _gTransMode = gMode;
}

void Trackball::setTranslationScale(Real32 rTranslationScale)
{
    _rTranslationScale = rTranslationScale;
}

void Trackball::setTranslationGen(TranslationGen gMode)
{
    if(_gTransGen == OSGAbsoluteTranslation && 
        gMode     == OSGOrientedTranslation)
    {
        Matrix tmpMat = getFullTrackballMatrix();

        _pVal[0] = tmpMat[3][0];
        _pVal[1] = tmpMat[3][1];
        _pVal[2] = tmpMat[3][2];
    }

    _gTransGen = gMode;
}

void Trackball::reset(void)
{
    _qVal = _qValStart;
    _pVal = _pValStart;
}

void Trackball::setStartPosition(Real32 rX, Real32 rY, Real32 rZ,
                                   bool bUpdate)
{
    _pValStart.setValues(rX, rY, rZ);
    
    if(bUpdate == true)
        _pVal = _pValStart;
}

void Trackball::setStartPosition(Vec3f &gStartPos, bool bUpdate)
{
    _pValStart = gStartPos;
    
    if(bUpdate == true)
        _pVal = _pValStart;
}

Vec3f &Trackball::getPosition(void)
{
    /*
    if(_bAutoPosition == true)
        _pVal[2] += _rAutoPositionStep;

    return _pVal;
    */    
    if(_bAutoPosition == true)
    {
        switch(_gTransMode)
        {
            case OSGFixedX:
                _pVal[0] += _rAutoPositionStep;
                break;
                
            case OSGFixedY:
                _pVal[1] += _rAutoPositionStep;
                break;
                
            case OSGFixedZ:
                _pVal[2] += _rAutoPositionStep;
                break;
                
            default:
                break;
        }
    }

    return _pVal;
}

void Trackball::setStartRotation(Real32 rX, Real32 rY, Real32 rZ, Real32 rW, 
                                  bool bUpdate)
{
    _qValStart.setValueAsAxisDeg(rX, rY, rZ, rW);

    if(bUpdate == true)
        _qVal = _qValStart;
}

void Trackball::setStartRotation(Quaternion &gStartRot, bool bUpdate)
{
    _qValStart = gStartRot;

    if(bUpdate == true)
        _qVal = _qValStart;
}

void Trackball::setRotationCenter(const Pnt3f &pRotationCenter)
{
    _pRotationCenter = pRotationCenter;
}

Quaternion &Trackball::getRotation(void)
{
    return _qVal;
}

Matrix &Trackball::getFullExamineMatrix(void)
{
    OSG::Matrix m1;

    _fullMatrix.setIdentity();

    _fullMatrix[3][0] = _pVal[0];
    _fullMatrix[3][1] = _pVal[1];
    _fullMatrix[3][2] = _pVal[2];
    
    m1.setRotate    (getRotation());
    _fullMatrix.mult(m1);

    m1.setIdentity ();
    m1.setTranslate(getPosition());
        
    _fullMatrix.mult(m1);

    m1.setIdentity();

    m1[3][0] = -_pVal[0];
    m1[3][1] = -_pVal[1];
    m1[3][2] = -_pVal[2];

    _fullMatrix.mult(m1);

    return _fullMatrix;
}

Matrix &Trackball::getFullTrackballMatrix(void)
{
    OSG::Matrix m1;

    _fullMatrix.setIdentity();

    _fullMatrix[3][0] = _pRotationCenter[0];
    _fullMatrix[3][1] = _pRotationCenter[1];
    _fullMatrix[3][2] = _pRotationCenter[2];
    
    m1.setRotate    (getRotation());
    _fullMatrix.mult(m1);

    m1.setIdentity ();
    m1.setTranslate(getPosition());
        
    _fullMatrix.mult(m1);

    m1.setIdentity();

    m1[3][0] = -_pRotationCenter[0];
    m1[3][1] = -_pRotationCenter[1];
    m1[3][2] = -_pRotationCenter[2];

    _fullMatrix.mult(m1);

    return _fullMatrix;
}



