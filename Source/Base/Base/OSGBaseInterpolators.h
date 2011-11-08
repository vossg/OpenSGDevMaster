/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGBASEINTERPOLATORS_H_
#define _OSGBASEINTERPOLATORS_H_

#include "OSGConfig.h"

#include "OSGBaseFunctions.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGColor.h"
#include "OSGQuaternion.h"

OSG_BEGIN_NAMESPACE

//Generic Lerp
template <class ElementTypeT> inline 
void lerp(const ElementTypeT &oFrom, 
          const ElementTypeT &oTo, 
          const Real32       &t, 
                ElementTypeT &oResult)
{
    //Return the linearly interpolated value
    oResult = (oFrom + ((oTo - oFrom) * t));
}

template <class ElementTypeT> inline 
ElementTypeT lerp(const ElementTypeT &oFrom, 
                  const ElementTypeT &oTo, 
                  const Real32       &t    )
{
    //Return the linearly interpolated value
    return (oFrom + ((oTo - oFrom) *  t));
}

//Generic Normal Lerp
template <class ElementTypeT> inline 
void lerpNormal(const ElementTypeT &oFrom, 
                const ElementTypeT &oTo, 
                const Real32       &t, 
                      ElementTypeT &oResult)
{
    //Create the Quaternion Representing int rotation from
    //Vec From to Vec To
    Quaternion qRotation(oFrom, oTo);

    //Scale the angle to t, which is our lerp amount
    qRotation.scaleAngle(t);
    
    //Rotate the Resulting Vector by the Quaternion
    qRotation.multVec(oFrom, oResult);
}

//Generic Normal Lerp
template <class ElementTypeT> inline 
ElementTypeT lerpNormal(const ElementTypeT &oFrom, 
                        const ElementTypeT &oTo, 
                        const Real32       &t    )
{
    Quaternion::VectorType oResult;

    //Create the Quaternion Representing int rotation from
    //Vec From to Vec To
    Quaternion qRotation(oFrom, oTo);

    //Scale the angle to t, which is our lerp amount
    qRotation.scaleAngle(t);

    //Rotate the Resulting Vector by the Quaternion
    qRotation.multVec(oFrom, oResult);

    return ElementTypeT(oResult.getValues());
}

//Matrix Lerp
template<class ValueTypeT> inline 
TransformationMatrix<ValueTypeT> lerp(
    const TransformationMatrix<ValueTypeT> &oFrom, 
    const TransformationMatrix<ValueTypeT> &oTo, 
    const Real32                           &t    )
{
    TransformationMatrix<ValueTypeT> oResult;

    lerp(oFrom, oTo, t, oResult);

    return oResult;
}

template<class ValueTypeT> inline
void lerp(const TransformationMatrix<ValueTypeT> &oFrom, 
          const TransformationMatrix<ValueTypeT> &oTo, 
          const Real32                           &t, 
                TransformationMatrix<ValueTypeT> &oResult)
{
    //Return the linearly interpolated value
    //Get The Translation, Scale, and Rotation

    typedef typename TransformationMatrix<ValueTypeT>::VectorType3f   VecType;
    typedef typename TransformationMatrix<ValueTypeT>::QuaternionType QuatType;

    VecType  oTranslationFrom;
    VecType  oScaleFactorFrom;
    QuatType oRotationFrom;
    QuatType oScaleOrientationFrom;

    oFrom.getTransform(oTranslationFrom, 
                       oRotationFrom, 
                       oScaleFactorFrom, 
                       oScaleOrientationFrom);
   
    VecType  oTranslationTo;
    VecType  oScaleFactorTo;
    QuatType oRotationTo;
    QuatType oScaleOrientationTo;

    oTo.getTransform(oTranslationTo, 
                     oRotationTo, 
                     oScaleFactorTo, 
                     oScaleOrientationTo);
   

    VecType  oTranslationResult;
    VecType  oScaleFactorResult;
    QuatType oRotationResult;
    QuatType oScaleOrientationResult;
   
    lerp(oTranslationFrom, oTranslationTo, t, oTranslationResult);
    lerp(oScaleFactorFrom, oScaleFactorTo, t, oScaleFactorResult);
    
    if(oRotationFrom != oRotationTo)
    {
        oRotationResult = QuatType::slerp(oRotationFrom, oRotationTo, t);
    }
    else
    {
        oRotationResult = oRotationTo;
    }
    
    if(oScaleOrientationFrom != oScaleOrientationTo)
    {
        oScaleOrientationResult = QuatType::slerp(oScaleOrientationFrom, 
                                                  oScaleOrientationTo, 
                                                  t                    );
    }
    else
    {
        oScaleOrientationResult = oScaleOrientationTo;
    }
    
    oResult.setTransform(oTranslationResult, 
                         oRotationResult, 
                         oScaleFactorResult, 
                         oScaleOrientationResult);
}

//Generic Spline
template <class ElementTypeT> inline
ElementTypeT spline(const std::vector<ElementTypeT> &V, 
                    const std::vector<Real32      > &t, 
                    const Real32                    &s)
{
    UInt8 i = 1;
    //Set up the Blend Function

    Vector<Real32, 4> S1(s * s * s, s * s, s, 1.0f);
   
    //std::cout << "S: " << S1 << std::endl;
   
    Vector<Real32, 4> H1( 2.0f, -3.0f, 0.0f, 1.0f);
    Vector<Real32, 4> H2(-2.0f,  3.0f, 0.0f, 0.0f);
    Vector<Real32, 4> H3( 1.0f, -2.0f, 1.0f, 0.0f);
    Vector<Real32, 4> H4( 1.0f, -1.0f, 0.0f, 0.0f);
   
    Vector<Real32, 4> S2;

    S2[0] = S1.dot(H1);
    S2[1] = S1.dot(H2);
    S2[2] = S1.dot(H3);
    S2[3] = S1.dot(H4);
   
    //Setup the Tangent Vectors
    ElementTypeT Ti      = (V[i + 1] -V[i - 1]) * 0.5f;
    ElementTypeT Tiplus1 = (V[i + 2] -V[i    ]) * 0.5f;
    
    //Get the Scaling values
    Real32 Fnegi;

    if(t[i - 1] == t[i + 1])
    {
        Fnegi = 0.0f;
    }
    else
    {
        Fnegi = (2.0f * (t[i + 1] - t[i]) / (t[i + 1] - t[i - 1]));
    }
   
    Real32 Fposiplus1;

    if(t[i + 2] == t[i])
    {
        Fposiplus1 = 0.0f;
    }
    else
    {
        Fposiplus1 = (2.0f * (t[i + 1] - t[i]) / (t[i + 2] - t[i]));
    }
         
    //Return the spline
    return 
        V[i    ]               * S2[0] + 
        V[i + 1]               * S2[1] +
        (Ti * Fnegi)           * S2[2] +
        (Tiplus1 * Fposiplus1) * S2[3];
}

template <class ElementTypeT> inline 
void spline(const std::vector<ElementTypeT> &V, 
            const std::vector<Real32      > &t, 
            const Real32                    &s, 
                  ElementTypeT              &oResult)
{
    oResult = spline(V, t, s); 
}

//Matrix Spline
template<class ValueTypeT> inline 
TransformationMatrix<ValueTypeT> spline(
    const std::vector< TransformationMatrix<ValueTypeT> > &V, 
    const std::vector< Real32                           > &t, 
    const Real32                                          &s)
{
    TransformationMatrix<ValueTypeT> oResult;

    spline(V, t, s, oResult);

    return oResult;
}

template <class ValueTypeT> inline 
void spline(const std::vector   < TransformationMatrix<ValueTypeT> > &V, 
            const std::vector   < Real32                           > &t, 
            const Real32                                             &s, 
            TransformationMatrix< ValueTypeT                       > &oResult)
{
   UInt8 i = 1;
   
   typedef typename TransformationMatrix<ValueTypeT>::VectorType3f   VecType;
   typedef typename TransformationMatrix<ValueTypeT>::QuaternionType QuatType;

   std::vector<VecType > vTransV;
   std::vector<VecType > vScaleV;
   std::vector<QuatType> vRotQ;
   std::vector<QuatType> vScaleOrientationQ;
      
   VecType  oTranslation;
   VecType  oScaleFactor;
   QuatType oRotation;
   QuatType oScaleOrientation;
   
   V[i - 1].getTransform(oTranslation, 
                         oRotation, 
                         oScaleFactor, 
                         oScaleOrientation);

   vTransV           .push_back(oTranslation     );
   vScaleV           .push_back(oScaleFactor     );
   vRotQ             .push_back(oRotation        );
   vScaleOrientationQ.push_back(oScaleOrientation);
   
   V[i].getTransform(oTranslation, oRotation, oScaleFactor, oScaleOrientation);

   vTransV           .push_back(oTranslation     );
   vScaleV           .push_back(oScaleFactor     );
   vRotQ             .push_back(oRotation        );
   vScaleOrientationQ.push_back(oScaleOrientation);
   
   V[i + 1].getTransform(oTranslation, 
                         oRotation, 
                         oScaleFactor, 
                         oScaleOrientation);

   vTransV           .push_back(oTranslation     );
   vScaleV           .push_back(oScaleFactor     );
   vRotQ             .push_back(oRotation        );
   vScaleOrientationQ.push_back(oScaleOrientation);
   
   V[i + 2].getTransform(oTranslation, 
                         oRotation, 
                         oScaleFactor, 
                         oScaleOrientation);

   vTransV           .push_back(oTranslation     );
   vScaleV           .push_back(oScaleFactor     );
   vRotQ             .push_back(oRotation        );
   vScaleOrientationQ.push_back(oScaleOrientation);
   
   spline(vTransV, t, s, oTranslation);
   spline(vScaleV, t, s, oScaleFactor);

   QuatType::squad(vRotQ,              t, s, oRotation        );
   QuatType::squad(vScaleOrientationQ, t, s, oScaleOrientation);
   
   oResult.setTransform(oTranslation, 
                        oRotation, 
                        oScaleFactor, 
                        oScaleOrientation);
}

OSG_END_NAMESPACE

#endif


