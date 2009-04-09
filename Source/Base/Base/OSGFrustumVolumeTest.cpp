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

// Unit tests for FrustumVolume

#include <OSGFrustumVolume.h>

OSG_USING_NAMESPACE


SUITE(FrustumVolumeTests)
{

TEST(GetCorners)
{
    Pnt3f testCorners[8] =
    {
	Pnt3f(-1.f,  1.f,  0.f),
	Pnt3f(-1.f, -1.f,  0.f),
	Pnt3f( 1.f,  1.f,  0.f),
	Pnt3f( 1.f, -1.f,  0.f),
	Pnt3f(-2.f,  2.f, -8.f),
	Pnt3f(-2.f, -2.f, -8.f),
	Pnt3f( 2.f,  2.f, -8.f),
	Pnt3f( 2.f, -2.f, -8.f)
    };

    Pnt3f corners[8];


    FrustumVolume fv;

    fv.setPlanes (testCorners[0], testCorners[1], testCorners[2], testCorners[3],
		  testCorners[4], testCorners[5], testCorners[6], testCorners[7] );

    fv.getCorners(corners[0], corners[1], corners[2], corners[3],
		  corners[4], corners[5], corners[6], corners[7] );

    CHECK_CLOSE(0.f, (testCorners[0] - corners[0]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[1] - corners[1]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[2] - corners[2]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[3] - corners[3]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[4] - corners[4]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[5] - corners[5]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[6] - corners[6]).length(), 1e-6);
    CHECK_CLOSE(0.f, (testCorners[7] - corners[7]).length(), 1e-6);
}

} // SUITE
