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

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"

#include "OSGNoneEngine.h"

#include "OSGNode.h"
#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NoneEngine
    \ingroup GrpSystemWindowNavigators

\dev 

\enddev

*/


/*------------------------- constructors ----------------------------------*/

NoneEngine::NoneEngine(void) : Inherited(), _noneMatrix()
{
}

/*-------------------------- destructors ----------------------------------*/

NoneEngine::~NoneEngine()
{
}

/*------------------------------ get --------------------------------------*/

const Pnt3f& NoneEngine::getFrom(void)
{
    static Pnt3f returnValue(0.f, 0.f, 0.f);
    returnValue = Pnt3f(_noneMatrix[3]);
    return returnValue;
}

const Pnt3f& NoneEngine::getAt(void)
{
    static Pnt3f returnValue(0.f, 0.f, 0.f);
    returnValue = Pnt3f(_noneMatrix[3] - _noneMatrix[2]);
    return returnValue;
}

const Vec3f& NoneEngine::getUp(void)
{
    static Vec3f returnValue(0.f, 0.f, 0.f);
    returnValue = Vec3f(_noneMatrix[1]);
    return returnValue;
}

const Matrix& NoneEngine::getMatrix(void)
{
    return _noneMatrix;
}

Real32 NoneEngine::getDistance(void)
{
    return 0.0f;
}



/*------------------------------ set --------------------------------------*/

void NoneEngine::setFrom(Pnt3f new_from)
{
    set(new_from, 
        Pnt3f(_noneMatrix[3]-_noneMatrix[2]),
        Vec3f(_noneMatrix[1]));
}

void NoneEngine::setAt(Pnt3f new_at)
{
    set(Pnt3f(_noneMatrix[3]), new_at, Vec3f(_noneMatrix[1]));
}

void NoneEngine::setUp(Vec3f new_up)
{
    set(Pnt3f(_noneMatrix[3]),
        Pnt3f(_noneMatrix[3]-_noneMatrix[2]), 
        new_up);
}

void NoneEngine::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    bool b = MatrixLookAt(_noneMatrix,new_at,new_at+(new_at-new_from),new_up);

    if (b) FNOTICE(("Navigator: set(.,.,.) failed\n"));
}

void NoneEngine::set(const Matrix & new_matrix)
{
    _noneMatrix = new_matrix;
}

void NoneEngine::setDistance(Real32 new_distance)
{
    // nothing to do
}




/*-------------------- navigator engine callbacks --------------------------*/

void NoneEngine::buttonPress(Int16 button, Int16 x, Int16 y, Navigator* nav)
{
    _currentState = Navigator::IDLE;
}

void NoneEngine::buttonRelease(Int16 button, Int16 x, Int16 y, Navigator* nav)
{
    // nothing to do
}

void NoneEngine::keyPress(Int16 key, Int16 x, Int16 y, Navigator* nav)
{
    // nothing to do
}

void NoneEngine::moveTo(Int16 x, Int16 y, Navigator* nav)
{
    FNOTICE(("NoneEngine: moveTo NONE mode\n"));
}

void NoneEngine::idle(Int16 buttons, Int16 x, Int16 y, Navigator* nav)
{
    // nothing to do
}

