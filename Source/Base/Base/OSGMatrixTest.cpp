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

#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGQuaternion.h>

#include <iostream>

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
   
    std::cerr << "mSO1_S1_SO1i =\n" << mSO1_S1_SO1i << std::endl;
    
    // decompose m1 and build m2 from components
    m1.getTransform(vT2, qR2, vS2, qSO2);
    
    std::cerr << "vT1  = " << vT1 << "\n"
              << "vS1  = " << vS1 << "\n"
              << "qR1  = " << qR1 << "\n"
              << "qSO1 = " << qSO1 << std::endl;
    
    std::cerr << "m1 =\n" << m1 << std::endl;
    std::cerr << "vT2  = " << vT2 << "\n"
              << "vS2  = " << vS2 << "\n"
              << "qR2  = " << qR2 << "\n"
              << "qSO2 = " << qSO2 << std::endl;
    
    m2.setTransform(vT2, qR2, vS2, qSO2);
    
    std::cerr << "m2 =\n" << m2 << std::endl;
    
    
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
   
    std::cerr << "mSO2_S2_SO2i =\n" << mSO2_S2_SO2i << std::endl;
        
    
    // test ||m1 - m2|| <= 1.0e-6
    m1.addScaled(m2, -1.0);
        
    CHECK_CLOSE(0.0, m1.normInfinity(), 1.0e-6);
}

} // SUITE
