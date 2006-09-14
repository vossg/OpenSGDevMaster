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

/*! \class QuaternionBase
 */

/*! \typedef VectorInterface <ValueTypeT,                   \
                              VecStorage3<ValueTypeT> >     \
     QuaternionBase::VectorType
    \brief Quaternion vector type
*/

/*! \typedef TransformationMatrix<ValueTypeT>               \
     QuaternionBase::MatrixType;
    \brief Quaternion matrix type
*/


/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

//! Identity quaternion

template <class ValueTypeT>
QuaternionBase<ValueTypeT> QuaternionBase<ValueTypeT>::_identity;

//! Returns identity quaternion

template <class ValueTypeT> inline
const QuaternionBase<ValueTypeT> &QuaternionBase<ValueTypeT>::identity(void)
{
    return _identity;
}

//! Returns the slerp betweet rot0 and rot1 at t

template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>
    QuaternionBase<ValueTypeT>::slerp(const QuaternionBase &rot0,
                                      const QuaternionBase &rot1,
                                      const ValueTypeT      t   )
{
    QuaternionBase returnValue;

    slerp(rot0, rot1, returnValue, t);

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>::QuaternionBase(void)
{
    _quat[0] =
        _quat[1] =
        _quat[2] = TypeTraits<ValueTypeT>::getZeroElement();

    _quat[3] = TypeTraits<ValueTypeT>::getOneElement();
}


template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>::QuaternionBase(const QuaternionBase &source)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _quat[i] = source._quat[i];
    }
}


template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>::QuaternionBase(const MatrixType &matrix)
{
    setValue(matrix);
}


template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>::QuaternionBase(const VectorType &axis,
                                           const ValueTypeT  angle)
{
    setValueAsAxisRad(axis, angle);
}

//! Constructor defined by the rotation from from to to 

template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>::QuaternionBase(const VectorType &rotateFrom,
                                           const VectorType &rotateTo)
{
    setValue(rotateFrom, rotateTo);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>::~QuaternionBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

//! Resets the quaternion to be the identity (0., 0., 0., 1.)

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setIdentity(void)
{
    _quat[0] =
        _quat[1] =
        _quat[2] = TypeTraits<ValueTypeT>::getZeroElement();

    _quat[3] = TypeTraits<ValueTypeT>::getOneElement();
}

/*! \brief Sets value of rotation from array interpreted as axis and angle
    given in radians
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisRad(
    const ValueTypeT *valsP)
{
    setValueAsAxisRad(valsP[0], valsP[1], valsP[2], valsP[3]);
}

/*! \brief Sets value of rotation from array interpreted as axis and angle
    given in degrees
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisDeg(
    const ValueTypeT *valsP)
{
    setValueAsAxisDeg(valsP[0], valsP[1], valsP[2], valsP[3]);
}

//! Sets value of rotation from array of 4 components of a quaternion

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsQuat(
    const ValueTypeT *valsP)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _quat[i] = valsP[i];
    }
}

/*! \brief Sets value of rotation from 4 individual components interpreted as
    axis and angle in rad
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisRad(const ValueTypeT x,
                                                   const ValueTypeT y,
                                                   const ValueTypeT z,
                                                   const ValueTypeT w)
{
    ValueTypeT rTmp = osgsqrt(x * x + y * y + z * z);

    if(rTmp > Eps)
    {
        rTmp = osgsin(w / 2.0f) / rTmp;

        _quat[0] = x * rTmp;
        _quat[1] = y * rTmp;
        _quat[2] = z * rTmp;
        _quat[3] = osgcos(w / 2.0f);
    }
    else
    {
        setIdentity();
    }
}

/*! \brief Sets value of rotation from 4 individual components interpreted as
    axis and angle in degrees
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisDeg(const ValueTypeT x,
                                                   const ValueTypeT y,
                                                   const ValueTypeT z,
                                                   const ValueTypeT w)
{
    setValueAsAxisRad(x,y,z,osgdegree2rad(w));
}

/*! \brief Sets value of rotation from 4 individual components interpreted as
    a quaternion
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsQuat(const ValueTypeT x,
                                                const ValueTypeT y,
                                                const ValueTypeT z,
                                                const ValueTypeT w)
{
    _quat[0] = x;
    _quat[1] = y;
    _quat[2] = z;
    _quat[3] = w;
}

//! Sets value of rotation from a rotation matrix

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValue(const MatrixType &matrix)
{
    Real64 tr;
    Real64 s;
    Real64 qt[3];

    UInt32 i;
    UInt32 j;
    UInt32 k;

    UInt32 nxt[3] = { 1, 2, 0};

    tr = matrix[0][0] + matrix[1][1] + matrix[2][2];

    if(tr > 0.0)
    {
        s = osgsqrt(tr + 1.0);

        _quat[3] = ValueTypeT(s * 0.5);

        s = 0.5 / s;
        _quat[0] = ValueTypeT((matrix[1][2] - matrix[2][1]) * s);
        _quat[1] = ValueTypeT((matrix[2][0] - matrix[0][2]) * s);
        _quat[2] = ValueTypeT((matrix[0][1] - matrix[1][0]) * s);
    }
    else
    {
        if(matrix[1][1] > matrix[0][0])
            i = 1;
        else
            i = 0;

        if(matrix[2][2] > matrix[i][i])
            i = 2;

        j = nxt[i];
        k = nxt[j];

        s = osgsqrt(matrix[i][i] - (matrix[j][j] + matrix[k][k]) + 1.0 );

        qt[i] = s * 0.5;
        s     = 0.5 / s;

        _quat[3] = ValueTypeT((matrix[j][k] - matrix[k][j]) * s);

        qt[j] = (matrix[i][j] + matrix[j][i]) * s;
        qt[k] = (matrix[i][k] + matrix[k][i]) * s;

        _quat[0] = ValueTypeT(qt[0]);
        _quat[1] = ValueTypeT(qt[1]);
        _quat[2] = ValueTypeT(qt[2]);
    }

    if(_quat[3] > 1.0 || _quat[3] < -1.0)
    {
        if(_quat[3] > 1.0 + Eps || _quat[3] < -1.0 - Eps)
        {
            fprintf(stderr,
                    "\nMatToQuat: BUG: |quat[4]| (%f) >> 1.0 !\n\n",
                    _quat[3]);
        }

        if(_quat[3] > 1.0)
        {
            _quat[3] = 1.0;
        }
        else
        {
            _quat[3] = -1.0;
        }
    }
}

/*! \brief Sets value of quaternion from 3D rotation axis vector and angle in
    degrees
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisRad(const VectorType &axis,
                                                         ValueTypeT  angle)
{
  setValueAsAxisRad(axis[0], axis[1], axis[2], angle);
}

/*! \brief Sets value of quaternion from 3D rotation axis vector and angle in
    degrees
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisDeg(const VectorType &axis,
                                                         ValueTypeT  angle)
{
  setValueAsAxisDeg(axis[0], axis[1], axis[2], angle);
}

//! Sets rotation to rotate one direction vector to another

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValue(const VectorType &rotateFrom,
                                          const VectorType &rotateTo)
{
    VectorType from = rotateFrom;
    VectorType to   = rotateTo;
    VectorType axis;
    ValueTypeT cost;

    from.normalize();
    to  .normalize();

    cost = from.dot(to);

    // check for degeneracies
    if(cost > 0.99999)
    {   // vectors are parallel
        setIdentity();
        return;
    }
    else if(cost < -0.99999)
    {
        // vectors are opposite
        // find an axis to rotate around, which should be
        // perpendicular to the original axis
        // Try cross product with (1,0,0) first, if that's one of our
        // original vectors then try  (0,1,0).

        VectorType cAxis(1.0, 0.0, 0.0);

        VectorType tmp = from.cross(cAxis);

        if(tmp.length() < 0.00001)
        {
            cAxis.setValues(0.0, 1.0, 0.0);

            tmp = from.cross(cAxis);
        }

        tmp.normalize();

        setValueAsAxisRad(tmp[0], tmp[1], tmp[2], Pi);

        return;
    }

    axis = rotateFrom.cross(rotateTo);
    axis.normalize();

    // use half-angle formulae
    // sin^2 t = ( 1 - cos (2t) ) / 2

    axis *= ValueTypeT(osgsqrt(0.5 * (1.0 - cost)));

    // scale the axis by the sine of half the rotation angle to get
    // the normalized quaternion

    _quat[0] = axis[0];
    _quat[1] = axis[1];
    _quat[2] = axis[2];

    // cos^2 t = ( 1 + cos (2t) ) / 2
    // w part is cosine of half the rotation angle

    _quat[3] = ValueTypeT(osgsqrt(0.5 * (1.0 + cost)));
}


/*! \brief Sets rotation by a given str (like "0.0 1.0 0.0 3.14"), be aware
    that these values are interpreted as axis, angle in rad
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisRad(const Char8 *str)
{
    setValueAsQuat(str);

    if(osgfinite(_quat[0]) == 0 ||
       osgfinite(_quat[1]) == 0 ||
       osgfinite(_quat[2]) == 0 ||
       osgfinite(_quat[3]) == 0   )
    {
        setIdentity();
    }
    else
    {
        setValueAsAxisRad(_quat[0], _quat[1], _quat[2], _quat[3]);
    }
}

/*! \brief Sets rotation by a given str (like "0.0 1.0 0.0 180"), be aware
    that these values are interpreted as axis, angle in degree
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsAxisDeg(const Char8 *str)
{
    setValueAsQuat(str);

    if(osgfinite(_quat[0]) == 0 ||
       osgfinite(_quat[1]) == 0 ||
       osgfinite(_quat[2]) == 0 ||
       osgfinite(_quat[3]) == 0   )
    {
        setIdentity();
    }
    else
    {
        setValueAsAxisDeg(_quat[0], _quat[1], _quat[2], _quat[3]);
    }
}

/*! \brief Sets rotation by a given str (like "0.0 1.0 0.0 0.0"), be aware
    that these values are interpreted as a quat
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValueAsQuat(const Char8 *str)
{
    UInt32 i;
    UInt32 numOfToken = 4;

    Char8 *c = const_cast<Char8 *>(str);

    Char8 *tokenC = 0;
    Char8  token[256];

    ValueTypeT vec[4];

    if( (str  == NULL) ||
        (*str == '\0') )
    {
        setIdentity();
        return;
    }

    for(i = 0; i < numOfToken; c++)
    {
        switch (*c)
        {
            case '\0':
                if (tokenC)
                {
                    *tokenC   = 0;
                     vec[i++] = TypeTraits<ValueTypeT>::getFromCString(token);

                }

                while (i < numOfToken)
                {
                    vec[i++] = TypeTraits<ValueTypeT>::getZeroElement();
                }

                break;
            case ' ' :
            case '\t':
            case '\n':
                if (tokenC)
                {
                    *tokenC   = 0;
                     vec[i++] = TypeTraits<ValueTypeT>::getFromCString(token);
                     tokenC   = 0;
                }
                break;
            default:
                if (!tokenC)
                {
                    tokenC = token;
                }
                *tokenC++ = *c;
                break;
        }
    }

  _quat[0] = vec[0];
  _quat[1] = vec[1];
  _quat[2] = vec[2];
  _quat[3] = vec[3];
}

//! Sets rotation by three given euler angles

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::setValue(const ValueTypeT alpha,
                                          const ValueTypeT beta,
                                          const ValueTypeT gamma)
{
    ValueTypeT sx = osgsin(alpha * 0.5f);
    ValueTypeT cx = osgcos(alpha * 0.5f);

    ValueTypeT sy = osgsin(beta  * 0.5f);
    ValueTypeT cy = osgcos(beta  * 0.5f);

    ValueTypeT sz = osgsin(gamma * 0.5f);
    ValueTypeT cz = osgcos(gamma * 0.5f);

    _quat[0] = (sx * cy * cz) - (cx * sy * sz);
    _quat[1] = (cx * sy * cz) + (sx * cy * sz);
    _quat[2] = (cx * cy * sz) - (sx * sy * cz);
    _quat[3] = (cx * cy * cz) + (sx * sy * sz);
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

//! Returns pointer to array of 4 components defining quaternion

template <class ValueTypeT> inline
const ValueTypeT *QuaternionBase<ValueTypeT>::getValues(void) const
{
    return _quat;
}

/*! \brief Returns 4 individual components of rotation quaternion as axis and
    angle in degrees
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValueAsAxisRad(ValueTypeT &x,
                                                   ValueTypeT &y,
                                                   ValueTypeT &z,
                                                   ValueTypeT &w) const
{
    getValueAsAxisDeg(x, y, z, w);

    w = osgdegree2rad(w);
}

/*! \brief Returns 4 individual components of rotation quaternion as axis and
    angle in degrees
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValueAsAxisDeg(ValueTypeT &x,
                                                   ValueTypeT &y,
                                                   ValueTypeT &z,
                                                   ValueTypeT &w) const
{
    ValueTypeT len;

    VectorType q(_quat[0], _quat[1], _quat[2]);

    len = q.length();

    if(len > Eps)
    {
        q *= (TypeTraits<ValueTypeT>::getOneElement() / len);

        x  = q[0];
        y  = q[1];
        z  = q[2];

        w = osgrad2degree(2.0f * osgacos(_quat[3]));
    }
    else
    {
        x = TypeTraits<ValueTypeT>::getZeroElement();
        y = TypeTraits<ValueTypeT>::getZeroElement();
        z = TypeTraits<ValueTypeT>::getOneElement();

        w = TypeTraits<ValueTypeT>::getZeroElement();
    }
}

//! Returns 4 individual components of rotation quaternion

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValueAsQuat(ValueTypeT &x,
                                                ValueTypeT &y,
                                                ValueTypeT &z,
                                                ValueTypeT &w) const
{
    x = _quat[0];
    y = _quat[1];
    z = _quat[2];
    w = _quat[3];
}

//! Returns corresponding 3D rotation axis vector and angle in rad

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValueAsAxisRad(VectorType &axis,
                                                   ValueTypeT &radians) const
{
  ValueTypeT x;
  ValueTypeT y;
  ValueTypeT z;
  ValueTypeT w;

  getValueAsAxisRad(x, y, z, w);

  axis.setValues(x, y, z);

  radians = w;
}

//! Returns corresponding 3D rotation axis vector and angle in degrees

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValueAsAxisDeg(VectorType &axis,
                                                   ValueTypeT &degrees) const
{
  ValueTypeT x;
  ValueTypeT y;
  ValueTypeT z;
  ValueTypeT w;

  getValueAsAxisDeg(x, y, z, w);

  axis.setValues(x, y, z);

  degrees = w;
}

//! Fills corresponding 4x4 rotation matrix

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValue(MatrixType &matrix) const
{
    getValuesOnly(matrix);

    matrix[0][3] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

//! Fills the corresponding 3x3 rotation matrix

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::getValuesOnly(MatrixType &matrix) const
{
    matrix[0][0] = 1.0f - 2.0f * (_quat[Q_Y] * _quat[Q_Y] +
                                  _quat[Q_Z] * _quat[Q_Z]);
    matrix[0][1] =        2.0f * (_quat[Q_X] * _quat[Q_Y] +
                                  _quat[Q_Z] * _quat[Q_W]);
    matrix[0][2] =        2.0f * (_quat[Q_Z] * _quat[Q_X] -
                                  _quat[Q_Y] * _quat[Q_W]);

    matrix[1][0] =        2.0f * (_quat[Q_X] * _quat[Q_Y] -
                                  _quat[Q_Z] * _quat[Q_W]);
    matrix[1][1] = 1.0f - 2.0f * (_quat[Q_Z] * _quat[Q_Z] +
                                  _quat[Q_X] * _quat[Q_X]);
    matrix[1][2] =        2.0f * (_quat[Q_Y] * _quat[Q_Z] +
                                  _quat[Q_X] * _quat[Q_W]);

    matrix[2][0] =        2.0f * (_quat[Q_Z] * _quat[Q_X] +
                                  _quat[Q_Y] * _quat[Q_W]);
    matrix[2][1] =        2.0f * (_quat[Q_Y] * _quat[Q_Z] -
                                  _quat[Q_X] * _quat[Q_W]);
    matrix[2][2] = 1.0f - 2.0f * (_quat[Q_Y] * _quat[Q_Y] +
                                  _quat[Q_X] * _quat[Q_X]);
}

template <class ValueTypeT> inline
ValueTypeT QuaternionBase<ValueTypeT>::x(void) const
{
    return _quat[0];
}

template <class ValueTypeT> inline
ValueTypeT QuaternionBase<ValueTypeT>::y(void) const
{
    return _quat[1];
}

template <class ValueTypeT> inline
ValueTypeT QuaternionBase<ValueTypeT>::z(void) const
{
    return _quat[2];
}

template <class ValueTypeT> inline
ValueTypeT QuaternionBase<ValueTypeT>::w(void) const
{
    return _quat[3];
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

//! Returns the 4 dimensional euclidian length of the quaternion

template <class ValueTypeT> inline
ValueTypeT QuaternionBase<ValueTypeT>::length(void) const
{
    return osgsqrt(_quat[0] * _quat[0] +
                   _quat[1] * _quat[1] +
                   _quat[2] * _quat[2] +
                   _quat[3] * _quat[3]);
}

//! Norm the quaternion to be of unit length

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::normalize(void)
{
    ValueTypeT rLength = length();

    if(osgabs(rLength) < Eps)
    {
        rLength =  TypeTraits<ValueTypeT>::getOneElement();
    }
    else
    {
        rLength =  TypeTraits<ValueTypeT>::getOneElement() / rLength;
    }

    for(UInt32 i = 0; i < 4; i++)
    {
        _quat[i] *= rLength;
    }
}

//! Changes a rotation to be its inverse

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::invert(void)
{
    _quat[0] = -_quat[0];
    _quat[1] = -_quat[1];
    _quat[2] = -_quat[2];
//    _quat[3] =  _quat[3];
}

//! Returns the inverse of a rotation

template <class ValueTypeT> inline
const QuaternionBase<ValueTypeT>QuaternionBase<ValueTypeT>::inverse(void) const
{
    QuaternionBase returnValue(*this);

    returnValue.invert();

    return returnValue;
}

//! Puts the given vector through this rotation

// this one should be optimized a little bit too (GV)
// Luckily somebody did it for us. ;) Thanks to Daniel Grest
// (grest@mip.informatik.uni-kiel.de) for the code. (DR, 20030626)

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::multVec(const VectorType &src,
                                               VectorType &dst) const
{
    ValueTypeT rx,ry,rz;
    ValueTypeT QwQx, QwQy, QwQz, QxQy, QxQz, QyQz;
    
    QwQx = _quat[3] * _quat[0]; 
    QwQy = _quat[3] * _quat[1]; 
    QwQz = _quat[3] * _quat[2];
    QxQy = _quat[0] * _quat[1]; 
    QxQz = _quat[0] * _quat[2]; 
    QyQz = _quat[1] * _quat[2];
    
    ValueTypeT Vx = src[0], Vy = src[1], Vz = src[2];
    
    rx = 2* (Vy * (-QwQz + QxQy) + Vz *( QwQy + QxQz));
    ry = 2* (Vx * ( QwQz + QxQy) + Vz *(-QwQx + QyQz));
    rz = 2* (Vx * (-QwQy + QxQz) + Vy *( QwQx + QyQz));
    
    ValueTypeT QwQw, QxQx, QyQy, QzQz;

    QwQw = _quat[3] * _quat[3]; 
    QxQx = _quat[0] * _quat[0]; 
    QyQy = _quat[1] * _quat[1]; 
    QzQz = _quat[2] * _quat[2];

    rx+= Vx * (QwQw + QxQx - QyQy - QzQz);
    ry+= Vy * (QwQw - QxQx + QyQy - QzQz);
    rz+= Vz * (QwQw - QxQx - QyQy + QzQz);
    
    dst.setValues(rx,ry,rz);
}

/*! \brief Keep the axis the same. Multiply the angle of rotation by
     the amount 'scaleFactor'
*/

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::scaleAngle(ValueTypeT scaleFactor)
{
    VectorType axis;
    ValueTypeT radians;

    getValueAsAxisRad(axis, radians);
    setValueAsAxisRad(axis, radians * scaleFactor);
}

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::slerpThis(const QuaternionBase &rot0,
                                           const QuaternionBase &rot1,
                                           const ValueTypeT      t)
{
    slerp(rot0, rot1, *this, t);
}

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::mult(const QuaternionBase &other)
{
    mult(_quat, other._quat);
}

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::multLeft(const QuaternionBase &other)
{
    mult(other._quat, _quat);
}

template <class ValueTypeT> inline
bool QuaternionBase<ValueTypeT>::equals(const QuaternionBase &rot,
                                        const ValueTypeT tolerance) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < 4; i++)
    {
        returnValue &= ( (    _quat[i] - rot._quat[i] <= tolerance) &&
                         (rot._quat[i] -     _quat[i] <= tolerance));
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                           Element Access                                */

template <class ValueTypeT> inline
ValueTypeT &QuaternionBase<ValueTypeT>::operator [](const UInt32 index)
{
    return _quat[index];
}

template <class ValueTypeT> inline
const ValueTypeT &QuaternionBase<ValueTypeT>::operator [](
    const UInt32 index) const
{
    return _quat[index];
}

/*-------------------------------------------------------------------------*/
/*                             Math Operators                              */

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::operator *=(const QuaternionBase &other)
{
    mult(_quat, other._quat);
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ValueTypeT> inline
const QuaternionBase<ValueTypeT> &
    QuaternionBase<ValueTypeT>::operator =(const QuaternionBase &source)
{
    if (this == &source)
        return *this;

    for(UInt32 i = 0; i < 4; i++)
    {
        _quat[i] = source._quat[i];
    }

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

template <class ValueTypeT> inline
bool QuaternionBase<ValueTypeT>::operator ==(const QuaternionBase &other) const
{
    return equals(other, Eps);
}

template <class ValueTypeT> inline
bool QuaternionBase<ValueTypeT>::operator !=(const QuaternionBase &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

//! The actual internal slerp code

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::slerp(const QuaternionBase &rot0,
                                       const QuaternionBase &rot1,
                                             QuaternionBase &result,
                                       const ValueTypeT      t     )
{
    ValueTypeT rot1q[4];

    Real64     omega;
    Real64     cosom;
    Real64     sinom;
    Real64     scalerot0;
    Real64     scalerot1;

    UInt32     i;
    UInt32     j;

    // Calculate the cosine
    cosom =
        rot0._quat[0] * rot1._quat[0] +
        rot0._quat[1] * rot1._quat[1] +
        rot0._quat[2] * rot1._quat[2] +
        rot0._quat[3] * rot1._quat[3];

    // adjust signs if necessary
    if(cosom < 0.0)
    {
        cosom = -cosom;

        for(j = 0; j < 4; j++)
        {
            rot1q[j] = -rot1[j];
        }
    }
    else
    {
        for(j = 0; j < 4; j++)
        {
            rot1q[j] = rot1[j];
        }
    }

    // calculate interpolating coeffs
    if ((1.0 - cosom) > 0.00001)
    {
        // standard case
        omega = osgacos(cosom);
        sinom = osgsin(omega);
        scalerot0 = osgsin((1.0 - t) * omega) / sinom;
        scalerot1 = osgsin(t * omega) / sinom;
    }
    else
    {
        // rot0 and rot1 very close - just do linear interp.
        scalerot0 = 1.0 - t;
        scalerot1 = t;
    }

    // build the new quarternion
    for (i = 0; i < 4; i++)
        result[i] = (ValueTypeT) (scalerot0 * rot0._quat[i] +
                                     scalerot1 * rot1q[i]);
}
/*! \brief \internal Take the give buffers as quaternions and write the
    result to the current.
 */

template <class ValueTypeT> inline
void QuaternionBase<ValueTypeT>::mult(const ValueTypeT rVal1[4],
                                      const ValueTypeT rVal2[4])
{
    ValueTypeT s1, s2, s3, s4, s5, s6, s7, s8, s9, t;

    s1 = (rVal1[2] - rVal1[1]) * (rVal2[1] - rVal2[2]);
    s2 = (rVal1[3] + rVal1[0]) * (rVal2[3] + rVal2[0]);
    s3 = (rVal1[3] - rVal1[0]) * (rVal2[1] + rVal2[2]);
    s4 = (rVal1[2] + rVal1[1]) * (rVal2[3] - rVal2[0]);
    s5 = (rVal1[2] - rVal1[0]) * (rVal2[0] - rVal2[1]);
    s6 = (rVal1[2] + rVal1[0]) * (rVal2[0] + rVal2[1]);
    s7 = (rVal1[3] + rVal1[1]) * (rVal2[3] - rVal2[2]);
    s8 = (rVal1[3] - rVal1[1]) * (rVal2[3] + rVal2[2]);

    s9 = s6 + s7 + s8;

    t  = (s5 + s9) / 2.0f;

    _quat[3] = s1 + t - s6;
    _quat[0] = s2 + t - s9;
    _quat[1] = s3 + t - s8;
    _quat[2] = s4 + t - s7;

    normalize();
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

template <class ValueTypeT> inline
std::ostream &operator <<(      std::ostream               &os, 
                          const QuaternionBase<ValueTypeT> &obj)
{
#ifdef OSG_SGI_STL
    os << std::fixed 
       << std::showpoint 
       << std::setprecision(3) 
       << std::setfill(' ');
#else
    os << std::setprecision(3) << std::setfill(' ');
#endif

    return os << std::setw(8)
              << obj.x() << " " 
              << obj.y() << " "
              << obj.z() << " " 
              << obj.w();
}

OSG_END_NAMESPACE

#define OSGQUATERNION_INLINE_CVSID "@(#)$Id$"
