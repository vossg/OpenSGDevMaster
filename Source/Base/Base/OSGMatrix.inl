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

OSG_BEGIN_NAMESPACE

/*! \typedef TransformationMatrix::ValueType
    \brief Value type, eg Real32
*/

/*! \typedef VectorInterface<ValueTypeT, VecStorage4<ValueTypeT> >    \
             TransformationMatrix::VectorType;
    \brief Matrix vector type, eg Vec4f
*/

/*! \typedef QuaternionBase<ValueType> TransformationMatrix::QuaternionType;
    \brief Matrix quaternion type
*/

/*! \typedef VectorInterface<ValueTypeT, VecStorage3<ValueTypeT> >    \
             TransformationMatrix::VectorType3f;
    \brief Matrix vec3f type
*/

/*! \typedef PointInterface<ValueTypeT, VecStorage3<ValueTypeT> >     \
             TransformationMatrix::PointType3f;
    \brief Matrix pnt3f type
*/

/*! \var VectorType TransformationMatrix::_matrix[4];
    \brief Value store
*/

#if defined(__hpux)
template<class ValueTypeT>
const UInt32 TransformationMatrix<ValueTypeT>::JacobiRank;
#endif

template<class ValueTypeT>
TransformationMatrix<ValueTypeT>
    TransformationMatrix<ValueTypeT>::_identityMatrix;

/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

template<class ValueTypeT> inline
const TransformationMatrix<ValueTypeT> &
    TransformationMatrix<ValueTypeT>::identity(void)
{
    return _identityMatrix;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(void)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i][i] = TypeTraits<ValueType>::getOneElement();
    }
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const TransformationMatrix &source)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = source._matrix[i];
    }
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const VectorType3f &vector1,
    const VectorType3f &vector2,
    const VectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const VectorType3f &vector1,
    const VectorType3f &vector2,
    const VectorType3f &vector3,
    const VectorType3f &vector4)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
    _matrix[3].setValue(vector4);
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const ValueTypeT rVal00,
    const ValueTypeT rVal10,
    const ValueTypeT rVal20,
    const ValueTypeT rVal30,

    const ValueTypeT rVal01,
    const ValueTypeT rVal11,
    const ValueTypeT rVal21,
    const ValueTypeT rVal31,

    const ValueTypeT rVal02,
    const ValueTypeT rVal12,
    const ValueTypeT rVal22,
    const ValueTypeT rVal32,

    const ValueTypeT rVal03,
    const ValueTypeT rVal13,
    const ValueTypeT rVal23,
    const ValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::~TransformationMatrix(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setIdentity(void)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i].setNull();
        _matrix[i][i] = TypeTraits<ValueType>::getOneElement();
    }
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const TransformationMatrix &mat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = mat._matrix[i];
    }
}

template<class ValueTypeT>
template<class ValueTypeR>
inline
void TransformationMatrix<ValueTypeT>::convertFrom(
    const TransformationMatrix<ValueTypeR>& mat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        for(UInt32 j =0; j<4; j++)
        { 
           (*this)[i][j] = mat[i][j];
        }
    }
}


template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType3f &vector1,
                                                const VectorType3f &vector2,
                                                const VectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType3f &vector1,
                                                const VectorType3f &vector2,
                                                const VectorType3f &vector3,
                                                const VectorType3f &vector4)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
    _matrix[3].setValue(vector4);
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const ValueTypeT rVal00,
                                                const ValueTypeT rVal10,
                                                const ValueTypeT rVal20,
                                                const ValueTypeT rVal30,

                                                const ValueTypeT rVal01,
                                                const ValueTypeT rVal11,
                                                const ValueTypeT rVal21,
                                                const ValueTypeT rVal31,

                                                const ValueTypeT rVal02,
                                                const ValueTypeT rVal12,
                                                const ValueTypeT rVal22,
                                                const ValueTypeT rVal32,

                                                const ValueTypeT rVal03,
                                                const ValueTypeT rVal13,
                                                const ValueTypeT rVal23,
                                                const ValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValueTransposed(
    const ValueTypeT rVal00,
    const ValueTypeT rVal01,
    const ValueTypeT rVal02,
    const ValueTypeT rVal03,

    const ValueTypeT rVal10,
    const ValueTypeT rVal11,
    const ValueTypeT rVal12,
    const ValueTypeT rVal13,

    const ValueTypeT rVal20,
    const ValueTypeT rVal21,
    const ValueTypeT rVal22,
    const ValueTypeT rVal23,

    const ValueTypeT rVal30,
    const ValueTypeT rVal31,
    const ValueTypeT rVal32,
    const ValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

//! Set value from an ValueTypeT array, be shure the sizes match

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const ValueTypeT *pMat,
                                                      bool        bTransposed)
{
    const ValueTypeT *pTmpMat = pMat;

    if(bTransposed == true)
    {
        for(UInt32 i = 0; i < 4; i++)
        {
            _matrix[i].setValue(pTmpMat);

            pTmpMat += 4;
        }
    }
    else
    {
        for(UInt32 i = 0; i < 4; i++)
        {
            for(UInt32 j = 0; j < 4; j++)
            {
                _matrix[i][j] = pTmpMat[j * 4 + i];
            }
        }
    }
}

//! Set value from an VectorTypeT array, be shure the sizes match

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType *pMat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = pMat[i];
    }
}

#ifndef WIN32

//! Set value from an VectorType3f array, be shure the sizes match

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType3f *pMat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i].setValue(pMat[i]);
    }
}

#endif

/*! \brief Set matrix by a given str (like "1.0 0.0 0.0 0.0 ...
    (16 entries at all)"), be shure the size matches
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const Char8 *str,
                                                      bool   bTransposed)
{
    UInt32 i;
    UInt32 numOfToken = 16;

    Char8 *c = const_cast<char*>(str);

    Char8 *tokenC = 0;
    Char8  token[256];

    ValueTypeT vec[16];

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
            case ' ':
            case '\t':
            case '\n':
            case ',':
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

    if(bTransposed == true)
    {
        setValueTransposed(vec[0],  vec[1],  vec[2],  vec[3],
                           vec[4],  vec[5],  vec[6],  vec[7],
                           vec[8],  vec[9],  vec[10], vec[11],
                           vec[12], vec[13], vec[14], vec[15]);
    }
    else
    {
        setValue(vec[0],  vec[1],  vec[2],  vec[3],
                 vec[4],  vec[5],  vec[6],  vec[7],
                 vec[8],  vec[9],  vec[10], vec[11],
                 vec[12], vec[13], vec[14], vec[15]);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

//! Returns an C++ pointer to the value store

template<class ValueTypeT> inline
ValueTypeT *TransformationMatrix<ValueTypeT>::getValues(void)
{
    return _matrix[0].getValues();
}

template<class ValueTypeT> inline
const ValueTypeT *TransformationMatrix<ValueTypeT>::getValues(void) const
{
    return _matrix[0].getValues();
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::rowMulCol4(
    const TransformationMatrix &gRowMat, UInt32 iRow,
    const TransformationMatrix &gColMat, UInt32 iColumn) const
{
    return
        gRowMat[0][iRow] * gColMat[iColumn][0] +
        gRowMat[1][iRow] * gColMat[iColumn][1] +
        gRowMat[2][iRow] * gColMat[iColumn][2] +
        gRowMat[3][iRow] * gColMat[iColumn][3];
}


template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det2_calc(
    const ValueTypeT a1, const ValueTypeT a2,
    const ValueTypeT b1, const ValueTypeT b2) const
{
    return (a1 * b2) - (a2 * b1);
}

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det3_calc(
    const ValueTypeT a1,
    const ValueTypeT a2,
    const ValueTypeT a3,
    const ValueTypeT b1,
    const ValueTypeT b2,
    const ValueTypeT b3,
    const ValueTypeT c1,
    const ValueTypeT c2,
    const ValueTypeT c3) const
{
    return
        (a1 * b2 * c3) + (a2 * b3 * c1) + (a3 * b1 * c2) -
        (a1 * b3 * c2) - (a2 * b1 * c3) - (a3 * b2 * c1);
}

#ifdef __sgi
#pragma set woff 1424
#endif

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::jacobi(
    ValueTypeT    evalues [JacobiRank],
    VectorType3f  evectors[JacobiRank],
    Int32        &rots)
{
    Real64  sm;
    Real64  theta;
    Real64  c, s, t;
    Real64  tau;
    Real64  h, g;
    Real64  thresh;
    Real64  b[JacobiRank];
    Real64  z[JacobiRank];
    UInt32  p, q, i, j;
    Real64  a[JacobiRank][JacobiRank];

    // initializations
    for (i = 0; i < JacobiRank; i++)
    {
        b[i] = evalues[i] = _matrix[i][i];
        z[i] = 0.0;

        for (j = 0; j < JacobiRank; j++)
        {
            evectors[i][j] = (i == j) ? 1.0f : 0.0f;
            a[i][j] = _matrix[i][j];
        }
    }

    rots = 0;

    for(i = 0; i < 50; i++)
    {
        sm = 0.0;

        for(p = 0; p < JacobiRank - 1; p++)
        {
            for(q = p+1; q < JacobiRank; q++)
            {
                sm += osgAbs(a[p][q]);
            }
        }

        if (sm == 0.0)
            return false;

        thresh = (i < 3 ?
                  (.2 * sm / (JacobiRank * JacobiRank)) :
                  0.0);

        for (p = 0; p < JacobiRank - 1; p++)
        {
            for (q = p + 1; q < JacobiRank; q++)
            {
                g = 100.0 * osgAbs(a[p][q]);

                if (i > 3                                          &&
                    (osgAbs(evalues[p]) + g == osgAbs(evalues[p])) &&
                    (osgAbs(evalues[q]) + g == osgAbs(evalues[q])))
                {
                    a[p][q] = 0.0;
                }
                else if (osgAbs(a[p][q]) > thresh)
                {
                    h = evalues[q] - evalues[p];

                    if (osgAbs(h) + g == osgAbs(h))
                    {
                        t = a[p][q] / h;
                    }
                    else
                    {
                        theta = .5 * h / a[p][q];
                        t = 1.0 / (osgAbs(theta) + osgSqrt(1 + theta * theta));
                        if (theta < 0.0)  t = -t;
                    }
                    // End of computing tangent of rotation angle

                    c = 1.0 / osgSqrt(1.0 + t * t);
                    s = t * c;

                    tau = s / (1.0 + c);
                    h   = t * a[p][q];

                    z[p]    -= h;
                    z[q]    += h;

                    evalues[p] -= ValueTypeT(h);
                    evalues[q] += ValueTypeT(h);

                    a[p][q] = 0.0;

                    for (j = 0; j < p; j++)
                    {
                        g = a[j][p];
                        h = a[j][q];

                        a[j][p] = g - s * (h + g * tau);
                        a[j][q] = h + s * (g - h * tau);
                    }

                    for (j = p+1; j < q; j++)
                    {
                        g = a[p][j];
                        h = a[j][q];

                        a[p][j] = g - s * (h + g * tau);
                        a[j][q] = h + s * (g - h * tau);
                    }

                    for (j = q+1; j < JacobiRank; j++)
                    {
                        g = a[p][j];
                        h = a[q][j];

                        a[p][j] = g - s * (h + g * tau);
                        a[q][j] = h + s * (g - h * tau);
                    }

                    for (j = 0; j < JacobiRank; j++)
                    {
                        g = evectors[j][p];
                        h = evectors[j][q];

                        evectors[j][p] = ValueTypeT(g - s * (h + g * tau));
                        evectors[j][q] = ValueTypeT(h + s * (g - h * tau));
                    }
                }
                rots++;
            }
        }
        for (p = 0; p < JacobiRank; p++)
        {
            evalues[p] = ValueTypeT(b[p] += z[p]);

            z[p] = 0;
        }
    }

    return true;
}

#ifdef __sgi
#pragma reset woff 1424
#endif

/*-------------------------------------------------------------------------*/
/*                       Set Transformation                                */

//! Sets matrix to scale by given uniform factor

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const ValueTypeT s)
{
    _matrix[0][0] = s;
    _matrix[1][1] = s;
    _matrix[2][2] = s;
}

//! Sets matrix to scale by given uniform factor

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const ValueTypeT sx,
                                                const ValueTypeT sy,
                                                const ValueTypeT sz)
{
    _matrix[0][0] = sx;
    _matrix[1][1] = sy;
    _matrix[2][2] = sz;
}

//! Sets matrix to scale by given vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const VectorType3f &s)
{
    _matrix[0][0] = s[0];
    _matrix[1][1] = s[1];
    _matrix[2][2] = s[2];
}

//! Sets matrix to translate by given values

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(const ValueTypeT tx,
                                                    const ValueTypeT ty,
                                                    const ValueTypeT tz)
{
    _matrix[3][0] = tx;
    _matrix[3][1] = ty;
    _matrix[3][2] = tz;
}

//! Sets matrix to translate by given vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(const VectorType3f &t)
{
    _matrix[3].setValue(t);
}

//! Sets matrix to translate by given point

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(const PointType3f &t)
{
    _matrix[3].setValue(t);
}

//! Sets matrix to rotate by given rotation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setRotate(const QuaternionType &q)
{
    q.getValuesOnly(*this);
}

//! Composes the matrix based on a translation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f &t)
{
    setIdentity();

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];

}

//! Composes the matrix based on a rotation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const QuaternionType &r)
{
    // Calculate the 4x4 rotation matrix
    r.getValue(*this);
}

//! Composes the matrix based on a translation and rotation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f   &t,
                                                    const QuaternionType &r)
{
    r.getValuesOnly(*this);

    // Calculate the resulting transformation matrix
    _matrix[0][3] = 0.0;
    _matrix[1][3] = 0.0;
    _matrix[2][3] = 0.0;

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];
    _matrix[3][3] = 1.0;
}

//! Composes the matrix based on a translation, rotation and scale

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f   &t,
                                                    const QuaternionType &r,
                                                    const VectorType3f   &s)
{
    typedef TypeTraits<ValueTypeT> ValueTraits;

    // Calculate the 3x3 rotation matrix
    r.getValuesOnly(*this);

    // Calculate the resulting transformation matrix
    _matrix[0][0] *= s[0]; _matrix[0][1] *= s[0]; _matrix[0][2] *=s[0];
    _matrix[1][0] *= s[1]; _matrix[1][1] *= s[1]; _matrix[1][2] *=s[1];
    _matrix[2][0] *= s[2]; _matrix[2][1] *= s[2]; _matrix[2][2] *=s[2];

    _matrix[0][3] = ValueTraits::getZeroElement();
    _matrix[1][3] = ValueTraits::getZeroElement();
    _matrix[2][3] = ValueTraits::getZeroElement();

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];
    _matrix[3][3] = ValueTraits::getOneElement();
}

//! Composes the matrix based on a translation, rotation, scale and orientation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f   &t,
                                                    const QuaternionType &r,
                                                    const VectorType3f   &s,
                                                    const QuaternionType &so)
{
    Matrix tmpMat1;
    Matrix tmpMat2;

    // Concatenate the rotations r and so
    QuaternionType rg(r);
    rg.mult(so);

    // Calculate the inverse of so
    QuaternionType soi(so);
    soi.invert();

    // Calculate the 3x3 rotation matrix
    rg. getValue(tmpMat1);
    soi.getValue(tmpMat2);

    // Calculate the resulting transformation matrix
    tmpMat1[0][0] *= s[0]; tmpMat1[0][1] *= s[0]; tmpMat1[0][2] *=s[0];
    tmpMat1[1][0] *= s[1]; tmpMat1[1][1] *= s[1]; tmpMat1[1][2] *=s[1];
    tmpMat1[2][0] *= s[2]; tmpMat1[2][1] *= s[2]; tmpMat1[2][2] *=s[2];

    _matrix[0][0] =
        tmpMat2[0][0] * tmpMat1[0][0] +
        tmpMat2[0][1] * tmpMat1[1][0] +
        tmpMat2[0][2] * tmpMat1[2][0];

    _matrix[0][1] =
        tmpMat2[0][0] * tmpMat1[0][1] +
        tmpMat2[0][1] * tmpMat1[1][1] +
        tmpMat2[0][2] * tmpMat1[2][1];

    _matrix[0][2] =
        tmpMat2[0][0] * tmpMat1[0][2] +
        tmpMat2[0][1] * tmpMat1[1][2] +
        tmpMat2[0][2] * tmpMat1[2][2];

    _matrix[0][3] = 0.0;


    _matrix[1][0] =
        tmpMat2[1][0] * tmpMat1[0][0] +
        tmpMat2[1][1] * tmpMat1[1][0] +
        tmpMat2[1][2] * tmpMat1[2][0];

    _matrix[1][1] =
        tmpMat2[1][0] * tmpMat1[0][1] +
        tmpMat2[1][1] * tmpMat1[1][1] +
        tmpMat2[1][2] * tmpMat1[2][1];

    _matrix[1][2] =
        tmpMat2[1][0] * tmpMat1[0][2] +
        tmpMat2[1][1] * tmpMat1[1][2] +
        tmpMat2[1][2] * tmpMat1[2][2];

    _matrix[1][3] = 0.0;


    _matrix[2][0] =
        tmpMat2[2][0] * tmpMat1[0][0] +
        tmpMat2[2][1] * tmpMat1[1][0] +
        tmpMat2[2][2] * tmpMat1[2][0];

    _matrix[2][1] =
        tmpMat2[2][0] * tmpMat1[0][1] +
        tmpMat2[2][1] * tmpMat1[1][1] +
        tmpMat2[2][2] * tmpMat1[2][1];

    _matrix[2][2] =
        tmpMat2[2][0] * tmpMat1[0][2] +
        tmpMat2[2][1] * tmpMat1[1][2] +
        tmpMat2[2][2] * tmpMat1[2][2];

    _matrix[2][3] = 0.0;

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];
    _matrix[3][3] = 1.0;
}

/*! Composes the matrix based on a translation, rotation, scale,
   orientation for scale, and center.  The "center" is the
   center point for scaling and rotation.  The "scaleOrientation"
   chooses the primary axes for the scale.
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(
    const VectorType3f   &translation,
    const QuaternionType &rotation,
    const VectorType3f   &scaleFactor,
    const QuaternionType &scaleOrientation,
    const VectorType3f   &center)
{
    typedef TypeTraits<ValueTypeT> ValueTraits;

    Matrixr tmpMat1;
    Matrixr tmpMat2;

    // Concatenate the translations t and c
    VectorType3f tg(translation);
    tg += center;

    // Concatenate the rotations r and so
    QuaternionType rg(rotation);
    rg *= scaleOrientation;

    // Calculate the inverse of so
    QuaternionType soi(scaleOrientation);
    soi.invert();

    // Calculate the 3x3 rotation matrix
    rg. getValue(tmpMat1);
    soi.getValue(tmpMat2);

    // Calculate the resulting transformation matrix

    tmpMat1[0][0] *= scaleFactor[0];
    tmpMat1[0][1] *= scaleFactor[0];
    tmpMat1[0][2] *= scaleFactor[0];

    tmpMat1[1][0] *= scaleFactor[1];
    tmpMat1[1][1] *= scaleFactor[1];
    tmpMat1[1][2] *= scaleFactor[1];

    tmpMat1[2][0] *= scaleFactor[2];
    tmpMat1[2][1] *= scaleFactor[2];
    tmpMat1[2][2] *= scaleFactor[2];

    _matrix[0][0] =
        tmpMat2[0][0] * tmpMat1[0][0] +
        tmpMat2[0][1] * tmpMat1[1][0] +
        tmpMat2[0][2] * tmpMat1[2][0];

    _matrix[0][1] =
        tmpMat2[0][0] * tmpMat1[0][1] +
        tmpMat2[0][1] * tmpMat1[1][1] +
        tmpMat2[0][2] * tmpMat1[2][1];

    _matrix[0][2] =
        tmpMat2[0][0] * tmpMat1[0][2] +
        tmpMat2[0][1] * tmpMat1[1][2] +
        tmpMat2[0][2] * tmpMat1[2][2];

    _matrix[0][3] = ValueTraits::getZeroElement();


    _matrix[1][0] =
        tmpMat2[1][0] * tmpMat1[0][0] +
        tmpMat2[1][1] * tmpMat1[1][0] +
        tmpMat2[1][2] * tmpMat1[2][0];

    _matrix[1][1] =
        tmpMat2[1][0] * tmpMat1[0][1] +
        tmpMat2[1][1] * tmpMat1[1][1] +
        tmpMat2[1][2] * tmpMat1[2][1];

    _matrix[1][2] =
        tmpMat2[1][0] * tmpMat1[0][2] +
        tmpMat2[1][1] * tmpMat1[1][2] +
        tmpMat2[1][2] * tmpMat1[2][2];

    _matrix[1][3] = ValueTraits::getZeroElement();


    _matrix[2][0] =
        tmpMat2[2][0] * tmpMat1[0][0] +
        tmpMat2[2][1] * tmpMat1[1][0] +
        tmpMat2[2][2] * tmpMat1[2][0];

    _matrix[2][1] =
        tmpMat2[2][0] * tmpMat1[0][1] +
        tmpMat2[2][1] * tmpMat1[1][1] +
        tmpMat2[2][2] * tmpMat1[2][1];

    _matrix[2][2] =
        tmpMat2[2][0] * tmpMat1[0][2] +
        tmpMat2[2][1] * tmpMat1[1][2] +
        tmpMat2[2][2] * tmpMat1[2][2];

    _matrix[2][3] = ValueTraits::getZeroElement();


    _matrix[3][0] =
        _matrix[0][0] * -center[0] +
        _matrix[1][0] * -center[1] +
        _matrix[2][0] * -center[2] + tg[0];

    _matrix[3][1] =
        _matrix[0][1] * -center[0] +
        _matrix[1][1] * -center[1] +
        _matrix[2][1] * -center[2] + tg[1];

    _matrix[3][2] =
        _matrix[0][2] * -center[0] +
        _matrix[1][2] * -center[1] +
        _matrix[2][2] * -center[2] + tg[2];

    _matrix[3][3] = ValueTraits::getOneElement();

}

/*-------------------------------------------------------------------------*/
/*                           Get Transform                                 */

/*! \brief Decomposes the matrix into a translation, rotation, scale,
    and scale orientation.  Any projection information is discarded.
    The decomposition depends upon choice of center point for
    rotation and scaling, which is optional as the last parameter.
    Note that if the center is 0, decompose() is the same as
    factor() where "t" is translation, "u" is rotation, "s" is
    scaleFactor, and "r" is ScaleOrientattion.
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::getTransform(
          VectorType3f   &translation,
          QuaternionType &rotation,
          VectorType3f   &scaleFactor,
          QuaternionType &scaleOrientation,
    const VectorType3f   &center          ) const
{
    TransformationMatrix m;
    TransformationMatrix c;

    m.setTranslate(-center);

    m.mult(*this);

    c.setTranslate(center);

    m.mult(c);

    m.getTransform(translation, rotation, scaleFactor, scaleOrientation);
}

//! Decomposes the matrix into a translation, rotation  and scale

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::getTransform(
    VectorType3f   &translation,
    QuaternionType &rotation,
    VectorType3f   &scaleFactor,
    QuaternionType &scaleOrientation) const
{
    TransformationMatrix so;
    TransformationMatrix rot;
    TransformationMatrix proj;

    this->factor(so, scaleFactor, rot, translation, proj);

    so.transpose();
    scaleOrientation.setValue(so);

    // gives us transpose of correct answer.
    rotation.setValue(rot);

}

/*! \brief Factors a matrix m into 5 pieces: m = r s rt u t, where rt
    means transpose of r, and r and u are rotations, s is a scale,
    and t is a translation. Any projection information is returned
    in proj.
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::factor(TransformationMatrix &r,
                                              VectorType3f         &s,
                                              TransformationMatrix &u,
                                              VectorType3f         &t,
                                              TransformationMatrix &proj) const
{
    Real64               det;
    Real64               det_sign;
    Real64               scratch;
    Int32                i;
    Int32                j;
    Int32                junk;
    TransformationMatrix a;
    TransformationMatrix aT;
    TransformationMatrix rT;
    TransformationMatrix b;
    TransformationMatrix si;
    ValueTypeT           evalues [3];
    VectorType3f         evectors[3];

    a = *this;

    proj.setIdentity();

    scratch = 1.0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            a._matrix[i][j] *= ValueTypeT(scratch);
        }

        t[i] = _matrix[3][i] * ValueTypeT(scratch);

        a._matrix[3][i] = a._matrix[i][3] = 0.0;
    }

    a._matrix[3][3] = 1.0;

    /* (3) Compute det A. If negative, set sign = -1, else sign = 1 */

    det      = a.det3();

    det_sign = (det < 0.0 ? -1.0 : 1.0);

    if(det_sign * det < 1e-12)
        return false;      // singular

    /* (4) B = A * A^  (here A^ means A transpose) */

    aT.transposeFrom(a);
    b = a;
    b.mult(aT);

    b.jacobi(evalues, evectors, junk);

    r.setValue(evectors[0][0], evectors[0][1], evectors[0][2], 0.0,
               evectors[1][0], evectors[1][1], evectors[1][2], 0.0,
               evectors[2][0], evectors[2][1], evectors[2][2], 0.0,
                          0.0,            0.0,            0.0, 1.0);

    /* Compute s = sqrt(evalues), with sign. Set si = s-inverse */

    si.setIdentity();

    for(i = 0; i < 3; i++)
    {
        s[i] = ValueTypeT(det_sign * osgSqrt(evalues[i]));

        si._matrix[i][i] = 1.0f / s[i];
    }

    /* (5) Compute U = RT S! R A. */

    rT.transposeFrom(r);
    u = r;
    u.mult(si);
    u.mult(rT);
    u.mult(a);

    return true;
}

/*---------------------------- transform objects ---------------------------*/

/*! \brief Multiplies matrix by given column point, where the resulting point
    is given
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixPnt(
    const PointType3f &src,
          PointType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0] +
                            _matrix[3][0]),
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1] +
                            _matrix[3][1]),
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2] +
                            _matrix[3][2]));
}

//! Multiplies matrix by given column point

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixPnt(PointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/*! \brief Multiplies matrix by given column point, where the resulting point
    is given. The full (4x4) matrix is used.
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multFullMatrixPnt(
    const PointType3f &src,
          PointType3f &dst) const
{
    ValueTypeT w =  src[0] * _matrix[0][3] +
                    src[1] * _matrix[1][3] +
                    src[2] * _matrix[2][3] +
                             _matrix[3][3];

    if(w == TypeTraits<ValueType>::getZeroElement())
    {
        SINFO << "multFullMatrixPnt: w == 0.0f!" << std::endl;

        dst.setValues(TypeTraits<ValueType>::getZeroElement(),
                      TypeTraits<ValueType>::getZeroElement(),
                      TypeTraits<ValueType>::getZeroElement());

        return;
    }

    //CHECK
    w = ValueTypeT(1.f)/w;
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0] +
                            _matrix[3][0]) * w,
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1] +
                            _matrix[3][1]) * w,
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2] +
                            _matrix[3][2]) * w);
}

//! Multiplies matrix by given column point. The full (4x4) matrix is used.

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multFullMatrixPnt(PointType3f &pnt)const
{
    multFullMatrixPnt(pnt, pnt);
}

/*! \brief Multiplies matrix by given column vector,  where the resulting
    vector is given
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(
    const VectorType3f &src,
          VectorType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0]),
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1]),
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2]));
}


//! Multiplies matrix by given column vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(VectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}

/*! \brief Multiplies matrix by given column vector,  where the resulting
    vector is given
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(
    const VectorType &src,
          VectorType &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0] +
                   src[3] * _matrix[3][0]),
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1] +
                   src[3] * _matrix[3][1]),
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2] +
                   src[3] * _matrix[3][2]),
                  (src[0] * _matrix[0][3] +
                   src[1] * _matrix[1][3] +
                   src[2] * _matrix[2][3] +
                   src[3] * _matrix[3][3]));
}


//! Multiplies matrix by given column vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(VectorType &vec) const
{
    multMatrixVec(vec, vec);
}

/*! \brief Transforms the given point by the matrix and stores the result in
    dest
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(const PointType3f &src,
                                                  PointType3f &dest) const
{
    multMatrixPnt(src, dest);
}

//! Transforms the given point by the matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(PointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/*! \brief Transforms the given vector by the matrix and stores the result in
    dest
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(const VectorType3f &src,
                                                  VectorType3f &dest) const
{
    multMatrixVec(src, dest);
}

//! Transforms the given vector by the matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(VectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}



/*! \brief Multiplies given row point by matrix, where the resulting point
    is given (pT * M)
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntMatrix(
    const PointType3f &src,
          PointType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2] +
                            _matrix[0][3]),
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2] +
                            _matrix[1][3]),
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2] +
                            _matrix[2][3]));
}

//! Multiplies given row point by matrix (pT * M)

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntMatrix(PointType3f &pnt) const
{
    multPntMatrix(pnt, pnt);
}

/*! \brief Multiplies given row point by matrix, where the resulting point
    is given. The full (4x4) matrix is used (pT * M).
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntFullMatrix(
    const PointType3f &src,
          PointType3f &dst) const
{
    ValueTypeT w =  src[0] * _matrix[3][0] +
                    src[1] * _matrix[3][1] +
                    src[2] * _matrix[3][2] +
                             _matrix[3][3];

    if( w == 0.0f )
    {
        SINFO << "multFullMatrixPnt: w == 0.0f!" << std::endl;

        dst.setValues(0, 0, 0);

        return;
    }

    w = 1./w;

    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2] +
                            _matrix[0][3]) * w,
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2] +
                            _matrix[1][3]) * w,
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2] +
                            _matrix[2][3]) * w);
}

//! Multiplies given row point by matrix. The full (4x4) matrix is used (pT*M).

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntFullMatrix(PointType3f &pnt)const
{
    multPntFullMatrix(pnt, pnt);
}

/*! \brief Multiplies given row vector by matrix,  where the resulting
    vector is given (vT * M)
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multVecMatrix(
    const VectorType3f &src,
          VectorType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2]),
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2]),
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2]));
}

//! Multiplies given row vector by matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multVecMatrix(VectorType3f &vec) const
{
    multVecMatrix(vec, vec);
}

/*---------------------------- simple math ---------------------------------*/

/*! \brief Returns true iff all matrix elements are equal within the given
    tolerance
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::equals(
    const TransformationMatrix &matrix,
    const ValueType             tolerance) const
{
    UInt32 i;
    bool returnValue = true;

    for(i = 0; i < 4; i++)
    {
        returnValue &= _matrix[i].equals(matrix._matrix[i], tolerance);

        if(returnValue == false)
            break;
    }

    return returnValue;
}

//! Returns the determinat of the upper 3x3 submatrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det3(void) const
{
    return (_matrix[0][0] * _matrix[1][1] * _matrix[2][2] +
            _matrix[0][1] * _matrix[1][2] * _matrix[2][0] +
            _matrix[0][2] * _matrix[1][0] * _matrix[2][1] -
            _matrix[0][2] * _matrix[1][1] * _matrix[2][0] -
            _matrix[0][1] * _matrix[1][0] * _matrix[2][2] -
            _matrix[0][0] * _matrix[1][2] * _matrix[2][1]);
}

//! Returns the determinat of the whole 4x4 matrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det (void) const
{
    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = _matrix[0][0];
    b1 = _matrix[1][0];
    c1 = _matrix[2][0];
    d1 = _matrix[3][0];

    a2 = _matrix[0][1];
    b2 = _matrix[1][1];
    c2 = _matrix[2][1];
    d2 = _matrix[3][1];

    a3 = _matrix[0][2];
    b3 = _matrix[1][2];
    c3 = _matrix[2][2];
    d3 = _matrix[3][2];

    a4 = _matrix[0][3];
    b4 = _matrix[1][3];
    c4 = _matrix[2][3];
    d4 = _matrix[3][3];

    return(   a1 * det3_calc(b2, b3, b4, c2, c3, c4, d2, d3, d4)
            - b1 * det3_calc(a2, a3, a4, c2, c3, c4, d2, d3, d4)
            + c1 * det3_calc(a2, a3, a4, b2, b3, b4, d2, d3, d4)
            - d1 * det3_calc(a2, a3, a4, b2, b3, b4, c2, c3, c4));

}

// This inverse stuff should be grouped in a better way :-). It's just a
// Cut&Paste section. I will have a look at it lateron (GV)

/*! \brief Stores the inverse of the matrix into result, returns true if the
     matrix is not singular
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::inverse(
    TransformationMatrix &result) const
{
    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = _matrix[0][0];
    b1 = _matrix[1][0];
    c1 = _matrix[2][0];
    d1 = _matrix[3][0];

    a2 = _matrix[0][1];
    b2 = _matrix[1][1];
    c2 = _matrix[2][1];
    d2 = _matrix[3][1];

    a3 = _matrix[0][2];
    b3 = _matrix[1][2];
    c3 = _matrix[2][2];
    d3 = _matrix[3][2];

    a4 = _matrix[0][3];
    b4 = _matrix[1][3];
    c4 = _matrix[2][3];
    d4 = _matrix[3][3];

    ValueTypeT rDet( det() );

    if(osgAbs(rDet) < TypeTraits<ValueTypeT>::ZeroEps())
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertMatrix: Singular matrix, no inverse!\n");
#endif
        result.setIdentity();

        return false;
    }

    rDet = 1.f / rDet;

    result[0][0]  =   det3_calc(b2, b3, b4, c2, c3,
                                c4, d2, d3, d4) * rDet;
    result[0][1]  = - det3_calc(a2, a3, a4, c2, c3, c4,
                                d2, d3, d4) * rDet;
    result[0][2]  =   det3_calc(a2, a3, a4, b2, b3, b4,
                                d2, d3, d4) * rDet;
    result[0][3]  = - det3_calc(a2, a3, a4, b2, b3, b4,
                                c2, c3, c4) * rDet;

    result[1][0]  = - det3_calc(b1, b3, b4, c1, c3, c4,
                                d1, d3, d4) * rDet;
    result[1][1]  =   det3_calc(a1, a3, a4, c1, c3, c4,
                                d1, d3, d4) * rDet;
    result[1][2]  = - det3_calc(a1, a3, a4, b1, b3, b4,
                                d1, d3, d4) * rDet;
    result[1][3]  =   det3_calc(a1, a3, a4, b1, b3, b4,
                                c1, c3, c4) * rDet;

    result[2][0]  =   det3_calc(b1, b2, b4, c1, c2, c4,
                                d1, d2, d4) * rDet;
    result[2][1]  = - det3_calc(a1, a2, a4, c1, c2, c4,
                                d1, d2, d4) * rDet;
    result[2][2]  =   det3_calc(a1, a2, a4, b1, b2, b4,
                                d1, d2, d4) * rDet;
    result[2][3]  = - det3_calc(a1, a2, a4, b1, b2, b4,
                                c1, c2, c4) * rDet;

    result[3][0]  = - det3_calc(b1, b2, b3, c1, c2, c3,
                                d1, d2, d3) * rDet;
    result[3][1]  =   det3_calc(a1, a2, a3, c1, c2, c3,
                                d1, d2, d3) * rDet;
    result[3][2]  = - det3_calc(a1, a2, a3, b1, b2, b3,
                                d1, d2, d3) * rDet;
    result[3][3]  =   det3_calc(a1, a2, a3, b1, b2, b3,
                                c1, c2, c3) * rDet;

    return true;
}

/*! \brief Inverts the matrix, returns true if the
     matrix is not singular
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invert(void)
{
    TransformationMatrix result;

    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = _matrix[0][0];
    b1 = _matrix[1][0];
    c1 = _matrix[2][0];
    d1 = _matrix[3][0];

    a2 = _matrix[0][1];
    b2 = _matrix[1][1];
    c2 = _matrix[2][1];
    d2 = _matrix[3][1];

    a3 = _matrix[0][2];
    b3 = _matrix[1][2];
    c3 = _matrix[2][2];
    d3 = _matrix[3][2];

    a4 = _matrix[0][3];
    b4 = _matrix[1][3];
    c4 = _matrix[2][3];
    d4 = _matrix[3][3];

    ValueTypeT rDet( det() );

    if(osgAbs(rDet) < TypeTraits<ValueTypeT>::ZeroEps())
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertMatrix: Singular matrix, no inverse!\n");
#endif
        setIdentity();

        return false;
    }

    rDet = TypeTraits<Real>::getOneElement() / rDet;

    result[0][0]  =   det3_calc(b2, b3, b4, c2, c3,
                                c4, d2, d3, d4) * rDet;
    result[0][1]  = - det3_calc(a2, a3, a4, c2, c3, c4,
                                d2, d3, d4) * rDet;
    result[0][2]  =   det3_calc(a2, a3, a4, b2, b3, b4,
                                d2, d3, d4) * rDet;
    result[0][3]  = - det3_calc(a2, a3, a4, b2, b3, b4,
                                c2, c3, c4) * rDet;

    result[1][0]  = - det3_calc(b1, b3, b4, c1, c3, c4,
                                d1, d3, d4) * rDet;
    result[1][1]  =   det3_calc(a1, a3, a4, c1, c3, c4,
                                d1, d3, d4) * rDet;
    result[1][2]  = - det3_calc(a1, a3, a4, b1, b3, b4,
                                d1, d3, d4) * rDet;
    result[1][3]  =   det3_calc(a1, a3, a4, b1, b3, b4,
                                c1, c3, c4) * rDet;

    result[2][0]  =   det3_calc(b1, b2, b4, c1, c2, c4,
                                d1, d2, d4) * rDet;
    result[2][1]  = - det3_calc(a1, a2, a4, c1, c2, c4,
                                d1, d2, d4) * rDet;
    result[2][2]  =   det3_calc(a1, a2, a4, b1, b2, b4,
                                d1, d2, d4) * rDet;
    result[2][3]  = - det3_calc(a1, a2, a4, b1, b2, b4,
                                c1, c2, c4) * rDet;

    result[3][0]  = - det3_calc(b1, b2, b3, c1, c2, c3,
                                d1, d2, d3) * rDet;
    result[3][1]  =   det3_calc(a1, a2, a3, c1, c2, c3,
                                d1, d2, d3) * rDet;
    result[3][2]  = - det3_calc(a1, a2, a3, b1, b2, b3,
                                d1, d2, d3) * rDet;
    result[3][3]  =   det3_calc(a1, a2, a3, b1, b2, b3,
                                c1, c2, c3) * rDet;

    *this = result;

    return true;
}

/*! \brief Set the matrix to be the inverse of the given one, returns true if
     the matrix is not singular
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invertFrom(
    const TransformationMatrix &matrix)
{
    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = matrix._matrix[0][0];
    b1 = matrix._matrix[1][0];
    c1 = matrix._matrix[2][0];
    d1 = matrix._matrix[3][0];

    a2 = matrix._matrix[0][1];
    b2 = matrix._matrix[1][1];
    c2 = matrix._matrix[2][1];
    d2 = matrix._matrix[3][1];

    a3 = matrix._matrix[0][2];
    b3 = matrix._matrix[1][2];
    c3 = matrix._matrix[2][2];
    d3 = matrix._matrix[3][2];

    a4 = matrix._matrix[0][3];
    b4 = matrix._matrix[1][3];
    c4 = matrix._matrix[2][3];
    d4 = matrix._matrix[3][3];

    ValueTypeT rDet( matrix.det() );

    if (osgAbs(rDet) < TypeTraits<ValueTypeT>::ZeroEps())
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertMatrix: Singular matrix, no inverse!\n");
#endif
        setIdentity();

        return false;
    }

    rDet = 1.f / rDet;

    _matrix[0][0]  =   det3_calc(b2, b3, b4, c2, c3,
                                 c4, d2, d3, d4) * rDet;
    _matrix[0][1]  = - det3_calc(a2, a3, a4, c2, c3, c4,
                                 d2, d3, d4) * rDet;
    _matrix[0][2]  =   det3_calc(a2, a3, a4, b2, b3, b4,
                                 d2, d3, d4) * rDet;
    _matrix[0][3]  = - det3_calc(a2, a3, a4, b2, b3, b4,
                                 c2, c3, c4) * rDet;

    _matrix[1][0]  = - det3_calc(b1, b3, b4, c1, c3, c4,
                                 d1, d3, d4) * rDet;
    _matrix[1][1]  =   det3_calc(a1, a3, a4, c1, c3, c4,
                                 d1, d3, d4) * rDet;
    _matrix[1][2]  = - det3_calc(a1, a3, a4, b1, b3, b4,
                                 d1, d3, d4) * rDet;
    _matrix[1][3]  =   det3_calc(a1, a3, a4, b1, b3, b4,
                                 c1, c3, c4) * rDet;

    _matrix[2][0]  =   det3_calc(b1, b2, b4, c1, c2, c4,
                                 d1, d2, d4) * rDet;
    _matrix[2][1]  = - det3_calc(a1, a2, a4, c1, c2, c4,
                                 d1, d2, d4) * rDet;
    _matrix[2][2]  =   det3_calc(a1, a2, a4, b1, b2, b4,
                                 d1, d2, d4) * rDet;
    _matrix[2][3]  = - det3_calc(a1, a2, a4, b1, b2, b4,
                                 c1, c2, c4) * rDet;

    _matrix[3][0]  = - det3_calc(b1, b2, b3, c1, c2, c3,
                                 d1, d2, d3) * rDet;
    _matrix[3][1]  =   det3_calc(a1, a2, a3, c1, c2, c3,
                                 d1, d2, d3) * rDet;
    _matrix[3][2]  = - det3_calc(a1, a2, a3, b1, b2, b3,
                                 d1, d2, d3) * rDet;
    _matrix[3][3]  =   det3_calc(a1, a2, a3, b1, b2, b3,
                                 c1, c2, c3) * rDet;

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::inverse3(
    TransformationMatrix &result) const
{
    ValueTypeT rDet = det3();

    if(osgAbs(rDet) < TypeTraits<ValueTypeT>::ZeroEps())
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "inverse3: matrix singular, no inverse!\n");
#endif

        result.setIdentity();

        return false;
    }

    rDet = 1.0f / rDet;

    result[0][0]  =   det2_calc(_matrix[1][1],
                                _matrix[1][2],
                           _matrix[2][1],
                           _matrix[2][2]) * rDet;
    result[0][1]  = - det2_calc(_matrix[0][1],
                                _matrix[0][2],
                                _matrix[2][1],
                                _matrix[2][2]) * rDet;
    result[0][2]  =   det2_calc(_matrix[0][1],
                                _matrix[0][2],
                                _matrix[1][1],
                                _matrix[1][2]) * rDet;

    result[1][0]  = - det2_calc(_matrix[1][0],
                                _matrix[1][2],
                                _matrix[2][0],
                                _matrix[2][2]) * rDet;
    result[1][1]  =   det2_calc(_matrix[0][0],
                                _matrix[0][2],
                                _matrix[2][0],
                                _matrix[2][2]) * rDet;
    result[1][2]  = - det2_calc(_matrix[0][0],
                                _matrix[0][2],
                                _matrix[1][0],
                                _matrix[1][2]) * rDet;

    result[2][0]  =   det2_calc(_matrix[1][0],
                                _matrix[1][1],
                                _matrix[2][0],
                                _matrix[2][1]) * rDet;
    result[2][1]  = - det2_calc(_matrix[0][0],
                                _matrix[0][1],
                                _matrix[2][0],
                                _matrix[2][1]) * rDet;
    result[2][2]  =   det2_calc(_matrix[0][0],
                                _matrix[0][1],
                                _matrix[1][0],
                                _matrix[1][1]) * rDet;

    result[3][0] =
        result[3][1] =
        result[3][2] = TypeTraits<ValueType>::getZeroElement();

    result[3][3] = TypeTraits<ValueType>::getOneElement();

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invert3(void)
{
    ValueTypeT           rDet    = det3();
    TransformationMatrix result;

    if(osgAbs(rDet) < TypeTraits<ValueTypeT>::ZeroEps())
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invert3: matrix singular, no inverse!\n");
#endif
        result.setIdentity();

        return false;
    }

    rDet = 1.0f / rDet;

    result[0][0]  =   det2_calc(_matrix[1][1],
                                _matrix[1][2],
                                _matrix[2][1],
                                _matrix[2][2]) * rDet;
    result[0][1]  = - det2_calc(_matrix[0][1],
                                _matrix[0][2],
                                _matrix[2][1],
                                _matrix[2][2]) * rDet;
    result[0][2]  =   det2_calc(_matrix[0][1],
                                _matrix[0][2],
                                _matrix[1][1],
                                _matrix[1][2]) * rDet;

    result[1][0]  = - det2_calc(_matrix[1][0],
                                _matrix[1][2],
                                _matrix[2][0],
                                _matrix[2][2]) * rDet;
    result[1][1]  =   det2_calc(_matrix[0][0],
                                _matrix[0][2],
                                _matrix[2][0],
                                _matrix[2][2]) * rDet;
    result[1][2]  = - det2_calc(_matrix[0][0],
                                _matrix[0][2],
                                _matrix[1][0],
                                _matrix[1][2]) * rDet;

    result[2][0]  =   det2_calc(_matrix[1][0],
                                _matrix[1][1],
                                _matrix[2][0],
                                _matrix[2][1]) * rDet;
    result[2][1]  = - det2_calc(_matrix[0][0],
                                _matrix[0][1],
                                _matrix[2][0],
                                _matrix[2][1]) * rDet;
    result[2][2]  =   det2_calc(_matrix[0][0],
                                _matrix[0][1],
                                _matrix[1][0],
                                _matrix[1][1]) * rDet;

    result[3][0] =
        result[3][1] =
        result[3][2] = TypeTraits<ValueType>::getZeroElement();

    result[3][3] = TypeTraits<ValueType>::getOneElement();

    *this = result;

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invertFrom3(
    const TransformationMatrix &matrix)
{
    ValueTypeT rDet = matrix.det3();

    if(osgAbs(rDet) < TypeTraits<ValueTypeT>::ZeroEps())
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertFrom3: matrix singular, no inverse!\n");
#endif

        setIdentity();

        return false;
    }

    rDet = 1.0f / rDet;

    _matrix[0][0]  =   det2_calc(matrix._matrix[1][1],
                                 matrix._matrix[1][2],
                                 matrix._matrix[2][1],
                                 matrix._matrix[2][2]) * rDet;
    _matrix[0][1]  = - det2_calc(matrix._matrix[0][1],
                                 matrix._matrix[0][2],
                                 matrix._matrix[2][1],
                                 matrix._matrix[2][2]) * rDet;
    _matrix[0][2]  =   det2_calc(matrix._matrix[0][1],
                                 matrix._matrix[0][2],
                                 matrix._matrix[1][1],
                                 matrix._matrix[1][2]) * rDet;

    _matrix[1][0]  = - det2_calc(matrix._matrix[1][0],
                                 matrix._matrix[1][2],
                                 matrix._matrix[2][0],
                                 matrix._matrix[2][2]) * rDet;
    _matrix[1][1]  =   det2_calc(matrix._matrix[0][0],
                                 matrix._matrix[0][2],
                                 matrix._matrix[2][0],
                                 matrix._matrix[2][2]) * rDet;
    _matrix[1][2]  = - det2_calc(matrix._matrix[0][0],
                                 matrix._matrix[0][2],
                                 matrix._matrix[1][0],
                                 matrix._matrix[1][2]) * rDet;

    _matrix[2][0]  =   det2_calc(matrix._matrix[1][0],
                                 matrix._matrix[1][1],
                                 matrix._matrix[2][0],
                                 matrix._matrix[2][1]) * rDet;
    _matrix[2][1]  = - det2_calc(matrix._matrix[0][0],
                                 matrix._matrix[0][1],
                                 matrix._matrix[2][0],
                                 matrix._matrix[2][1]) * rDet;
    _matrix[2][2]  =   det2_calc(matrix._matrix[0][0],
                                 matrix._matrix[0][1],
                                 matrix._matrix[1][0],
                                 matrix._matrix[1][1]) * rDet;

    _matrix[3][0] =
        _matrix[3][1] =
        _matrix[3][2] = TypeTraits<ValueType>::getZeroElement();

    _matrix[3][3] = TypeTraits<ValueType>::getOneElement();

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::transposed(
        TransformationMatrix &result) const
{
    result.setValueTransposed(
        (*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0],
        (*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1],
        (*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2],
        (*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3]);

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::transpose(void)
{
    ValueTypeT tmp;

    tmp = (*this)[1][0]; (*this)[1][0] = (*this)[0][1]; (*this)[0][1] = tmp;
    tmp = (*this)[2][0]; (*this)[2][0] = (*this)[0][2]; (*this)[0][2] = tmp;
    tmp = (*this)[3][0]; (*this)[3][0] = (*this)[0][3]; (*this)[0][3] = tmp;
    tmp = (*this)[2][1]; (*this)[2][1] = (*this)[1][2]; (*this)[1][2] = tmp;
    tmp = (*this)[3][1]; (*this)[3][1] = (*this)[1][3]; (*this)[1][3] = tmp;
    tmp = (*this)[3][2]; (*this)[3][2] = (*this)[2][3]; (*this)[2][3] = tmp;

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::transposeFrom(
    const TransformationMatrix &matrix)
{
    this->setValueTransposed(
        matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
        matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
        matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
        matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);

    return true;
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(const TransformationMatrix &matrix)
{
    ValueTypeT rTmpMat[4][4];

    (rTmpMat)[0][0] = rowMulCol4((*this), 0, (matrix), 0);
    (rTmpMat)[0][1] = rowMulCol4((*this), 1, (matrix), 0);
    (rTmpMat)[0][2] = rowMulCol4((*this), 2, (matrix), 0);
    (rTmpMat)[0][3] = rowMulCol4((*this), 3, (matrix), 0);

    (rTmpMat)[1][0] = rowMulCol4((*this), 0, (matrix), 1);
    (rTmpMat)[1][1] = rowMulCol4((*this), 1, (matrix), 1);
    (rTmpMat)[1][2] = rowMulCol4((*this), 2, (matrix), 1);
    (rTmpMat)[1][3] = rowMulCol4((*this), 3, (matrix), 1);

    (rTmpMat)[2][0] = rowMulCol4((*this), 0, (matrix), 2);
    (rTmpMat)[2][1] = rowMulCol4((*this), 1, (matrix), 2);
    (rTmpMat)[2][2] = rowMulCol4((*this), 2, (matrix), 2);
    (rTmpMat)[2][3] = rowMulCol4((*this), 3, (matrix), 2);

    (rTmpMat)[3][0] = rowMulCol4((*this), 0, (matrix), 3);
    (rTmpMat)[3][1] = rowMulCol4((*this), 1, (matrix), 3);
    (rTmpMat)[3][2] = rowMulCol4((*this), 2, (matrix), 3);
    (rTmpMat)[3][3] = rowMulCol4((*this), 3, (matrix), 3);

    _matrix[0][0] = rTmpMat[0][0];
    _matrix[0][1] = rTmpMat[0][1];
    _matrix[0][2] = rTmpMat[0][2];
    _matrix[0][3] = rTmpMat[0][3];

    _matrix[1][0] = rTmpMat[1][0];
    _matrix[1][1] = rTmpMat[1][1];
    _matrix[1][2] = rTmpMat[1][2];
    _matrix[1][3] = rTmpMat[1][3];

    _matrix[2][0] = rTmpMat[2][0];
    _matrix[2][1] = rTmpMat[2][1];
    _matrix[2][2] = rTmpMat[2][2];
    _matrix[2][3] = rTmpMat[2][3];

    _matrix[3][0] = rTmpMat[3][0];
    _matrix[3][1] = rTmpMat[3][1];
    _matrix[3][2] = rTmpMat[3][2];
    _matrix[3][3] = rTmpMat[3][3];
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multLeft(
    const TransformationMatrix &matrix)
{
    ValueTypeT rTmpMat[4][4];

    (rTmpMat)[0][0] = rowMulCol4((matrix), 0, (*this), 0);
    (rTmpMat)[0][1] = rowMulCol4((matrix), 1, (*this), 0);
    (rTmpMat)[0][2] = rowMulCol4((matrix), 2, (*this), 0);
    (rTmpMat)[0][3] = rowMulCol4((matrix), 3, (*this), 0);

    (rTmpMat)[1][0] = rowMulCol4((matrix), 0, (*this), 1);
    (rTmpMat)[1][1] = rowMulCol4((matrix), 1, (*this), 1);
    (rTmpMat)[1][2] = rowMulCol4((matrix), 2, (*this), 1);
    (rTmpMat)[1][3] = rowMulCol4((matrix), 3, (*this), 1);

    (rTmpMat)[2][0] = rowMulCol4((matrix), 0, (*this), 2);
    (rTmpMat)[2][1] = rowMulCol4((matrix), 1, (*this), 2);
    (rTmpMat)[2][2] = rowMulCol4((matrix), 2, (*this), 2);
    (rTmpMat)[2][3] = rowMulCol4((matrix), 3, (*this), 2);

    (rTmpMat)[3][0] = rowMulCol4((matrix), 0, (*this), 3);
    (rTmpMat)[3][1] = rowMulCol4((matrix), 1, (*this), 3);
    (rTmpMat)[3][2] = rowMulCol4((matrix), 2, (*this), 3);
    (rTmpMat)[3][3] = rowMulCol4((matrix), 3, (*this), 3);

    _matrix[0][0] = rTmpMat[0][0];
    _matrix[0][1] = rTmpMat[0][1];
    _matrix[0][2] = rTmpMat[0][2];
    _matrix[0][3] = rTmpMat[0][3];

    _matrix[1][0] = rTmpMat[1][0];
    _matrix[1][1] = rTmpMat[1][1];
    _matrix[1][2] = rTmpMat[1][2];
    _matrix[1][3] = rTmpMat[1][3];

    _matrix[2][0] = rTmpMat[2][0];
    _matrix[2][1] = rTmpMat[2][1];
    _matrix[2][2] = rTmpMat[2][2];
    _matrix[2][3] = rTmpMat[2][3];

    _matrix[3][0] = rTmpMat[3][0];
    _matrix[3][1] = rTmpMat[3][1];
    _matrix[3][2] = rTmpMat[3][2];
    _matrix[3][3] = rTmpMat[3][3];
}

//! Adds the given matrix to this matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::add(const TransformationMatrix &matrix)
{
    _matrix[0][0] += matrix._matrix[0][0];
    _matrix[0][1] += matrix._matrix[0][1];
    _matrix[0][2] += matrix._matrix[0][2];
    _matrix[0][3] += matrix._matrix[0][3];

    _matrix[1][0] += matrix._matrix[1][0];
    _matrix[1][1] += matrix._matrix[1][1];
    _matrix[1][2] += matrix._matrix[1][2];
    _matrix[1][3] += matrix._matrix[1][3];

    _matrix[2][0] += matrix._matrix[2][0];
    _matrix[2][1] += matrix._matrix[2][1];
    _matrix[2][2] += matrix._matrix[2][2];
    _matrix[2][3] += matrix._matrix[2][3];

    _matrix[3][0] += matrix._matrix[3][0];
    _matrix[3][1] += matrix._matrix[3][1];
    _matrix[3][2] += matrix._matrix[3][2];
    _matrix[3][3] += matrix._matrix[3][3];
}

//! Scales the elements of this matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::scale(ValueTypeT s)
{
    _matrix[0][0] *= s;
    _matrix[0][1] *= s;
    _matrix[0][2] *= s;
    _matrix[0][3] *= s;

    _matrix[1][0] *= s;
    _matrix[1][1] *= s;
    _matrix[1][2] *= s;
    _matrix[1][3] *= s;

    _matrix[2][0] *= s;
    _matrix[2][1] *= s;
    _matrix[2][2] *= s;
    _matrix[2][3] *= s;

    _matrix[3][0] *= s;
    _matrix[3][1] *= s;
    _matrix[3][2] *= s;
    _matrix[3][3] *= s;
}

//! Adds a scaled version of the given matrix to this matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::addScaled(
    const TransformationMatrix &matrix,
          ValueTypeT            s)
{
    _matrix[0][0] += s*matrix._matrix[0][0];
    _matrix[0][1] += s*matrix._matrix[0][1];
    _matrix[0][2] += s*matrix._matrix[0][2];
    _matrix[0][3] += s*matrix._matrix[0][3];

    _matrix[1][0] += s*matrix._matrix[1][0];
    _matrix[1][1] += s*matrix._matrix[1][1];
    _matrix[1][2] += s*matrix._matrix[1][2];
    _matrix[1][3] += s*matrix._matrix[1][3];

    _matrix[2][0] += s*matrix._matrix[2][0];
    _matrix[2][1] += s*matrix._matrix[2][1];
    _matrix[2][2] += s*matrix._matrix[2][2];
    _matrix[2][3] += s*matrix._matrix[2][3];

    _matrix[3][0] += s*matrix._matrix[3][0];
    _matrix[3][1] += s*matrix._matrix[3][1];
    _matrix[3][2] += s*matrix._matrix[3][2];
    _matrix[3][3] += s*matrix._matrix[3][3];
}

//! Negates the matrix in place

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::negate(void)
{
    _matrix[0][0] *= -1.0;
    _matrix[0][1] *= -1.0;
    _matrix[0][2] *= -1.0;
    _matrix[0][3] *= -1.0;

    _matrix[1][0] *= -1.0;
    _matrix[1][1] *= -1.0;
    _matrix[1][2] *= -1.0;
    _matrix[1][3] *= -1.0;

    _matrix[2][0] *= -1.0;
    _matrix[2][1] *= -1.0;
    _matrix[2][2] *= -1.0;
    _matrix[2][3] *= -1.0;

    _matrix[3][0] *= -1.0;
    _matrix[3][1] *= -1.0;
    _matrix[3][2] *= -1.0;
    _matrix[3][3] *= -1.0;
}

//! Returns the 1-norm of _matrix matrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::norm1(void) const
{
    ValueTypeT m(0);

    m += osgAbs(_matrix[0][0]);
    m += osgAbs(_matrix[0][1]);
    m += osgAbs(_matrix[0][2]);
    m += osgAbs(_matrix[0][3]);
    m += osgAbs(_matrix[1][0]);
    m += osgAbs(_matrix[1][1]);
    m += osgAbs(_matrix[1][2]);
    m += osgAbs(_matrix[1][3]);
    m += osgAbs(_matrix[2][0]);
    m += osgAbs(_matrix[2][1]);
    m += osgAbs(_matrix[2][2]);
    m += osgAbs(_matrix[2][3]);
    m += osgAbs(_matrix[3][0]);
    m += osgAbs(_matrix[3][1]);
    m += osgAbs(_matrix[3][2]);
    m += osgAbs(_matrix[3][3]);

    return m;
}

//! Returns the 2-norm of this matrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::norm2(void) const
{
    ValueTypeT m = 0.;
    ValueTypeT t;

    t = _matrix[0][0]; m += t*t;
    t = _matrix[0][1]; m += t*t;
    t = _matrix[0][2]; m += t*t;
    t = _matrix[0][3]; m += t*t;
    t = _matrix[1][0]; m += t*t;
    t = _matrix[1][1]; m += t*t;
    t = _matrix[1][2]; m += t*t;
    t = _matrix[1][3]; m += t*t;
    t = _matrix[2][0]; m += t*t;
    t = _matrix[2][1]; m += t*t;
    t = _matrix[2][2]; m += t*t;
    t = _matrix[2][3]; m += t*t;
    t = _matrix[3][0]; m += t*t;
    t = _matrix[3][1]; m += t*t;
    t = _matrix[3][2]; m += t*t;
    t = _matrix[3][3]; m += t*t;

    return osgSqrt(m);
}

//! Returns the infinity norm of this matrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::normInfinity(void) const
{
    ValueTypeT m = 0.;
    ValueTypeT t;

    if((t = osgAbs(_matrix[0][0])) > m)
        m = t;
    if((t = osgAbs(_matrix[0][1])) > m)
        m = t;
    if((t = osgAbs(_matrix[0][2])) > m)
        m = t;
    if((t = osgAbs(_matrix[0][3])) > m)
        m = t;
    if((t = osgAbs(_matrix[1][0])) > m)
        m = t;
    if((t = osgAbs(_matrix[1][1])) > m)
        m = t;
    if((t = osgAbs(_matrix[1][2])) > m)
        m = t;
    if((t = osgAbs(_matrix[1][3])) > m)
        m = t;
    if((t = osgAbs(_matrix[2][0])) > m)
        m = t;
    if((t = osgAbs(_matrix[2][1])) > m)
        m = t;
    if((t = osgAbs(_matrix[2][2])) > m)
        m = t;
    if((t = osgAbs(_matrix[2][3])) > m)
        m = t;
    if((t = osgAbs(_matrix[3][0])) > m)
        m = t;
    if((t = osgAbs(_matrix[3][1])) > m)
        m = t;
    if((t = osgAbs(_matrix[3][2])) > m)
        m = t;
    if((t = osgAbs(_matrix[3][3])) > m)
        m = t;

    return m;
}

/*! \brief Computes the square root of the matrix and stores it in
    result, assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::sqrt(TransformationMatrix &result) const
{
    TransformationMatrix iX;
    TransformationMatrix  Y;
    TransformationMatrix iY;

    ValueTypeT  g;
    ValueTypeT ig;

    result.setValue(*this);

    Y.setIdentity();

    for(UInt32 i = 0; i < 6; i++)
    {
        result.inverse(iX);

        Y.inverse(iY);

        g = osgAbs(osgPow(result.det() * Y.det(), ValueTypeT(-0.125)));

        ig = ValueTypeT(1.0 / g);

        result.scale    (g     );
        result.addScaled(iY, ig);
        result.scale    (0.5   );

        Y.scale    (g     );
        Y.addScaled(iX, ig);
        Y.scale    (0.5   );
    }

    // ToDo: return should depend on achieved accuracy
    return true;
}

/*! \brief Sets this matrix to the square root of the given matrix,
     assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::sqrtOf(
    const TransformationMatrix &matrix)
{
    TransformationMatrix iX;
    TransformationMatrix  Y;
    TransformationMatrix iY;

    ValueTypeT  g;
    ValueTypeT ig;

    setValue(matrix);

    Y.setIdentity();

    for(Int32 i = 0; i < 6; i++)
    {
        inverse(iX);

        Y.inverse(iY);

        g = osgAbs(osgPow(det() * Y.det(), ValueTypeT(-0.125)));

        ig = ValueTypeT(1.0 / g);

        scale    (g     );
        addScaled(iY, ig);
        scale    (0.5   );

        Y.scale    (g     );
        Y.addScaled(iX, ig);
        Y.scale    (0.5);
    }

    // ToDo: return should depend on achieved accuracy
    return true;
}

//! Sets this matrix to its square root, assumes det > 0

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::sqrt(void)
{
    TransformationMatrix iX;
    TransformationMatrix  Y;
    TransformationMatrix iY;

    ValueTypeT  g;
    ValueTypeT ig;

    Y.setIdentity();

    for(Int32 i = 0; i < 6; i++)
    {
        inverse(iX);

        Y.inverse(iY);

        g = osgAbs(osgPow(det() * Y.det(), ValueTypeT(-0.125)));

        ig = ValueTypeT(1.0 / g);

        scale    (g     );
        addScaled(iY, ig);
        scale    (0.5   );

        Y.scale    (g     );
        Y.addScaled(iX, ig);
        Y.scale    (0.5   );
    }

    // ToDo: return should depend on achieved accuracy
    return true;
}

/*! \brief Computes the logarithm of this matrix and stores it in
    result, assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::log(TransformationMatrix &result) const
{
    const Int32      maxiter = 12;
          Int32      k       = 0;
          Int32      i       = 0;
    const ValueTypeT eps     = 1e-12;

    TransformationMatrix A(*this);
    TransformationMatrix Z;

    // Take repeated square roots to reduce spectral radius
    Z.setValue(A);

    Z[0][0] -= TypeTraits<ValueType>::getOneElement();
    Z[1][1] -= TypeTraits<ValueType>::getOneElement();
    Z[2][2] -= TypeTraits<ValueType>::getOneElement();
    Z[3][3] -= TypeTraits<ValueType>::getOneElement();

    while(Z.normInfinity() > 0.5)
    {
        A.sqrt    ( );
        Z.setValue(A);

        Z[0][0] -= TypeTraits<ValueType>::getOneElement();
        Z[1][1] -= TypeTraits<ValueType>::getOneElement();
        Z[2][2] -= TypeTraits<ValueType>::getOneElement();
        Z[3][3] -= TypeTraits<ValueType>::getOneElement();

        k++;
    }

    A[0][0] -= TypeTraits<ValueType>::getOneElement();
    A[1][1] -= TypeTraits<ValueType>::getOneElement();
    A[2][2] -= TypeTraits<ValueType>::getOneElement();
    A[3][3] -= TypeTraits<ValueType>::getOneElement();

    A.negate();

    result.setValue(A);

    Z.setValue(A);

    i = 1;

    while(Z.normInfinity() > eps && i < maxiter)
    {
        Z.mult(A);

        i++;

        result.addScaled(Z, ValueTypeT(1.0) / ValueTypeT(i));
    }

    result.scale(ValueTypeT(-1.0) * ValueTypeT(1 << k));

    return (i < maxiter);
}

/*! \brief Sets this matrix to the logarithm of the given matrix,
    assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::logOf(
    const TransformationMatrix &matrix)
{
    const Int32      maxiter = 12;
          Int32      k       = 0;
          Int32      i       = 0;
    const ValueTypeT eps     = 1e-12;

    TransformationMatrix<ValueTypeT> A(matrix),Z;

    // Take repeated square roots to reduce spectral radius
    Z.setValue(A);

    Z[0][0] -= TypeTraits<ValueType>::getOneElement();
    Z[1][1] -= TypeTraits<ValueType>::getOneElement();
    Z[2][2] -= TypeTraits<ValueType>::getOneElement();
    Z[3][3] -= TypeTraits<ValueType>::getOneElement();

    while(Z.normInfinity() > 0.5)
    {
        A.sqrt();

        Z.setValue(A);

        Z[0][0] -= TypeTraits<ValueType>::getOneElement();
        Z[1][1] -= TypeTraits<ValueType>::getOneElement();
        Z[2][2] -= TypeTraits<ValueType>::getOneElement();
        Z[3][3] -= TypeTraits<ValueType>::getOneElement();

        k++;
    }

    A[0][0] -= TypeTraits<ValueType>::getOneElement();
    A[1][1] -= TypeTraits<ValueType>::getOneElement();
    A[2][2] -= TypeTraits<ValueType>::getOneElement();
    A[3][3] -= TypeTraits<ValueType>::getOneElement();

    A.negate();

    setValue(A);

    Z.setValue(A);

    i = 1;
    while(Z.normInfinity() > eps && i < maxiter)
    {
        Z.mult(A);

        i++;

        addScaled(Z, ValueTypeT(1.0) / ValueTypeT(i));
    }

    scale(ValueTypeT(-1.0) * ValueTypeT(1 << k));

    return (i<maxiter);
}

/*! \brief Computes the exponential of this matrix and stores it in
    result
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::exp(TransformationMatrix &result) const
{
    const Int32                q = 6;

          TransformationMatrix A(*this);
          TransformationMatrix D;
          TransformationMatrix N;

          Int32                j = 1;
          Int32                k;

          ValueTypeT           c(1.0);

    j += Int32(osgLog(A.normInfinity() / 0.693));

    if(j < 0)
        j = 0;

    A.scale(ValueTypeT(1.0f / (1 << j)));

    result.setIdentity();

    for(k = 1; k <= q; k++)
    {
        c *= ValueTypeT(q - k + 1) / ValueTypeT(k * (2 * q - k + 1));

        result.multLeft(A);

        N.addScaled(result, c);

        if(k % 2)
        {
            D.addScaled(result, -c);
        }
        else
        {
            D.addScaled(result,  c);
        }
    }

    result.invertFrom(D);
    result.mult      (N);

    for(k = 0; k < j; k++)
        result.mult(result);

    // ToDo: return value
    return true;
}

/** \brief Sets this matrix to the exponential of the given matrix
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::expOf(
    const TransformationMatrix &matrix)
{
    const Int32                q = 6;

          TransformationMatrix A(matrix);
          TransformationMatrix D;
          TransformationMatrix N;

          Int32                j = 1;
          Int32                k;

          ValueTypeT           c(1.0);

    j += int(osgLog(A.normInfinity() / 0.693));

    if(j < 0)
        j = 0;

    A.scale(1.0 / (ValueTypeT(1 << j)));

    setIdentity();

    for(k = 1; k <= q; k++)
    {
        c *= ValueTypeT(q - k + 1) / ValueTypeT(k * (2 *q - k + 1));

        multLeft(A);

        N.addScaled(*this,c);

        if(k % 2)
        {
            D.addScaled(*this, -c);
        }
        else
        {
            D.addScaled(*this,  c);
        }
    }

    invertFrom(D);
    mult      (N);

    for(k = 0; k < j; k++)
        mult(*this);

    // ToDo: return value
    return true;
}

/*-------------------------------------------------------------------------*/
/*                          Element Access                                 */

template<class ValueTypeT> inline
typename TransformationMatrix<ValueTypeT>::VectorType &
    TransformationMatrix<ValueTypeT>::operator [](UInt32 uiIndex)
{
    return _matrix[uiIndex];
}

template<class ValueTypeT> inline
const typename TransformationMatrix<ValueTypeT>::VectorType &
    TransformationMatrix<ValueTypeT>::operator [](UInt32 uiIndex) const
{
    return _matrix[uiIndex];
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT> &
    TransformationMatrix<ValueTypeT>::operator = (
        const TransformationMatrix &source)
{
    UInt32 i;

    if (this == &source)
        return *this;

    for(i = 0; i < 4; i++)
        _matrix[i] = source._matrix[i];

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*! \brief equal, returns true if all matrix elements are equal with
    the tolerance of Eps
 */

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::operator == (
    const TransformationMatrix &other) const
{
    return equals(other, Eps);
}

/*! \brief not equal, returns true if all matrix elements are not equal with
    the tolerance of Eps
 */

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::operator != (
    const TransformationMatrix &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! write matrix to stream

template<class ValueTypeT> inline
std::ostream &operator <<(      std::ostream                     &os,
                          const TransformationMatrix<ValueTypeT> &obj)
{
    UInt32 i;
    UInt32 j;

    std::ios::fmtflags oldflags = os.flags(std::ios::showpoint |
                                           std::ios::fixed);

    Int32 pr    = os.precision(3  );
    Char8 fill  = os.fill     (' ');
    Int32 width = os.width    (8  );

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            os << std::setw(8) << obj[i][j] << " ";
        }

        os << "\n";
    }

    os.flags    (oldflags);
    os.precision(pr      );
    os.fill     (fill    );
    os.width    (width   );

    return os;
}

OSG_END_NAMESPACE

#define OSGMATRIX_INLINE_CVSID "@(#)$Id$"
