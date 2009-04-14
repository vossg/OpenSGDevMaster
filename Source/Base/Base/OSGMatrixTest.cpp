/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <UnitTest++.h>

// Unit tests for matrix classes

#include <OSGMatrix.h>
#include <OSGQuaternion.h>

OSG_USING_NAMESPACE

SUITE(MatrixTests)
{

TEST(InstantiateAllMatrixTypes)
{
    Matrix m;

    CHECK(true);
}

TEST(ConvertFloatToDoubleMatrix)
{
    Matrix4f mf;
    Matrix4d md;

    mf.convertFrom(md);
    md.convertFrom(mf);
    md.convertFrom(md);
    mf.convertFrom(mf);
}

TEST(MatrixDecomposition)
{
    // construct test matrix m1
    Matrix4f m1;
    Matrix4f m2;
        
    Vec3f vT1(1.0, -12.0, 15.0);
    Vec3f vS1(4.5,   3.2,  2.1);
    
    Quaternion qR1 (Vec3f( 6.6,  23.4, 75.4),  1.345);
    Quaternion qSO1(Vec3f(23.2,   8.7,  9.4), -2.6  );

    m1.setTransform(vT1, qR1, vS1, qSO1);
    
    Vec3f      vT2;
    Vec3f      vS2;
    Quaternion qR2;
    Quaternion qSO2;
    
    Matrix4f mSO1;
    Matrix4f mSO1i;
    Matrix4f mS1;
    Matrix4f mSO1_S1_SO1i;
    
    Quaternion qSO1i(qSO1);
    
    qSO1i.invert();
    
    mSO1 .setRotate(qSO1 );
    mSO1i.setRotate(qSO1i);
    mS1.setScale(vS1);
    
    mSO1_S1_SO1i = mSO1;
    mSO1_S1_SO1i.mult(mS1);
    mSO1_S1_SO1i.mult(mSO1i);
      
    // decompose m1 and build m2 from components
    m1.getTransform(vT2, qR2, vS2, qSO2);
        
    m2.setTransform(vT2, qR2, vS2, qSO2);
        
    Matrix4f mSO2;
    Matrix4f mSO2i;
    Matrix4f mS2;
    Matrix4f mSO2_S2_SO2i;
    
    Quaternion qSO2i(qSO2);
    
    qSO2i.invert();
    
    mSO2 .setRotate(qSO2 );
    mSO2i.setRotate(qSO2i);
    mS2.setScale(vS2);
    
    mSO2_S2_SO2i = mSO2;
    mSO2_S2_SO2i.mult(mS2);
    mSO2_S2_SO2i.mult(mSO2i);
   
    // test ||m1 - m2|| <= 1.0e-6
    m1.addScaled(m2, -1.0);
        
    CHECK_CLOSE(0.0, m1.normInfinity(), 1.0e-6);
}

TEST(MatrixInverse)
{
    Matrix4f m1;

    for(UInt32 i = 0; i < 10; ++i)
    {
        switch(i % 3)
        {
        case 0:
        {
            Matrix4f m;
            m.setTranslate(Vec3f(osgRand(), osgRand(), osgRand()));

            m1.mult(m);
        }
        break;

        case 1:
        {
            Matrix4f m;
            m.setRotate(Quaternion(Vec3f(osgRand(), osgRand(), osgRand()), osgRand() * Pi));

            m1.mult(m);
        }
        break;

        case 2:
        {
            Matrix4f m;
            m.setScale(Vec3f(osgRand(), osgRand(), osgRand()));

            m1.mult(m);
        }
        break;
        }
    }

    // m2 is a 3x3 matrix
    Matrix4f m2(m1);
    m2.setTranslate(Vec3f(0.f, 0.f, 0.f));

    // all invert function forward to the same code, so it is enough
    // to test just one of them
    Matrix4f m1Inv;
    bool     m1InvValid = m1Inv.invertFrom(m1);

    Matrix4f m2Inv;
    bool     m2InvValid = m2Inv.invertFrom3(m2);

    CHECK_EQUAL(true, m1InvValid);
    CHECK_EQUAL(true, m2InvValid);

    // verify ||m1 - I|| <= 1.0e-6
    m1.mult     (m1Inv                   );
    m1.addScaled(Matrix::identity(), -1.f);

    m2.mult     (m2Inv                   );
    m2.addScaled(Matrix::identity(), -1.f);

    CHECK_CLOSE(0.0, m1.normInfinity(), 1.0e-6);
    CHECK_CLOSE(0.0, m2.normInfinity(), 1.0e-6);
}


} // SUITE
