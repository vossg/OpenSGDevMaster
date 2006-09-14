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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGGL.h>

#include "OSGBillboard.h"
#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"
#include "OSGCamera.h"
#include "OSGNode.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"

OSG_USING_NAMESPACE

/*! \class OSG::Billboard

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Billboard::Billboard(void) :
     Inherited   (),
    _camTransform()
{
}

//! Copy Constructor

Billboard::Billboard(const Billboard &source) :
     Inherited   (source              ),
    _camTransform(source._camTransform)
{
}

//! Destructor

Billboard::~Billboard(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Billboard::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Billboard::intersectEnter));

        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Billboard::intersectLeave));


        RenderAction::registerEnterDefault(
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Billboard::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Billboard::renderLeave));
    }
}

//! react to field changes

void Billboard::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void Billboard::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}


/*------------------------- volume update -------------------------------*/

void Billboard::adjustVolume( Volume & volume )
{
    Inherited::adjustVolume(volume);
    
    // enlarge the volume to adjust for rotations
    // keep the center, but make it a cube big enough to contain the 
    // billboard in all orientations
    
    Pnt3f min, max;
    
    volume.getBounds(min, max);
    
    Vec3f  dia    = max - min;
    Pnt3f  center = min + dia * .5;
    Real32 extend = dia.maxValue();
    
    dia.setValues(extend * Sqrt2, extend * Sqrt2, extend * Sqrt2);
    
    volume.extendBy( center - dia );
    volume.extendBy( center + dia );
}

void Billboard::accumulateMatrix(Matrix &result)
{
    result.mult(_camTransform);
}

void Billboard::calcMatrix(      DrawActionBase *pAction, 
                           const Matrix         &mToWorld,
                                 Matrix         &mResult)
{
    Pnt3f eyepos(0.f, 0.f, 0.f);
    Pnt3f objpos(0.f, 0.f, 0.f);

    Vec3f vDir;
    Vec3f n(0.f, 0.f, 1.f);

    Quaternion q1;

    Matrix mCamToWorld = pAction->getCameraToWorld();

    mResult.invertFrom(mToWorld);
    
    mToWorld.mult(n);

    if(getAxisOfRotation() == Vec3f::Null)
    {
        if(_sfFocusOnCamera.getValue() == true)
        {
            Vec3f vUp;
            Vec3f uW;
            Vec3f vX;

            mCamToWorld.mult(eyepos);
            mToWorld   .mult(objpos);
            
            vDir = eyepos - objpos;
            
            vUp.setValue (mCamToWorld[0]);
            
            vUp = vDir.cross(vUp);

            vUp.normalize();
            vDir.normalize();

            Matrix mTr;

            vX = vUp.cross(vDir);
            vX.normalize();

            mTr[0][0] = vX[0];
            mTr[0][1] = vX[1];
            mTr[0][2] = vX[2];
            mTr[1][0] = vUp[0];
            mTr[1][1] = vUp[1];
            mTr[1][2] = vUp[2];
            mTr[2][0] = vDir[0];
            mTr[2][1] = vDir[1];
            mTr[2][2] = vDir[2];

            q1.setValue(mTr);
        }
        else
        {
            if(_sfAlignToScreen.getValue() == false)
            {
                Vec3f u  (0.f, 1.f, 0.f);
                Vec3f vUp;
                Vec3f uW;
                
                mCamToWorld.mult(eyepos);
                mToWorld   .mult(objpos);
                
                vDir = eyepos - objpos;
                
//            vDir.setValue(mCamToWorld[2]);
                
                vUp.setValue (mCamToWorld[1]);
                
                Quaternion qN(n, vDir);
                
                mToWorld.mult(u);
                
                qN.multVec(u, uW);
                
                q1.setValue(uW, vUp);
                
                q1.mult(qN);
            }
            else
            {
                Vec3f u  (0.f, 1.f, 0.f);
                Vec3f vUp;
                Vec3f uW;
                
                vDir.setValue(mCamToWorld[2]);
                
                vUp.setValue (mCamToWorld[1]);
                
                Quaternion qN(n, vDir);
                
                mToWorld.mult(u);
                
                qN.multVec(u, uW);
            
                q1.setValue(uW, vUp);
                
                q1.mult(qN);
            }
        }
    }
    else
    {
        Vec3f wUp;
        Vec3f s;
        Vec3f tDir;

        mCamToWorld.mult(eyepos);

        mToWorld.mult(objpos);

        mToWorld.mult(getAxisOfRotation(), wUp);

        vDir = eyepos - objpos;

        s    = vDir.cross(wUp);
        tDir = wUp .cross(s  );
        
        q1.setValue(n, tDir);

        // clamp angle to [min; max]
        Vec3f  axis;
        Real32 angle;

        if(getMinAngle() <= getMaxAngle()) 
        {
            q1.getValueAsAxisRad(axis, angle);

            if(angle < getMinAngle())
                angle = getMinAngle();

            if(angle > getMaxAngle())
                angle = getMaxAngle();

            q1.setValueAsAxisRad(axis, angle);
        }
    }

    Matrix mTrans;
    Matrix mMat;
    
    mTrans[3][0] = mToWorld[3][0];
    mTrans[3][1] = mToWorld[3][1];
    mTrans[3][2] = mToWorld[3][2];

    mMat.setTransform(q1);

    mResult.mult(mTrans);
    mResult.mult(mMat  );

    mTrans[3][0] = -mToWorld[3][0];
    mTrans[3][1] = -mToWorld[3][1];
    mTrans[3][2] = -mToWorld[3][2];

    mResult.mult(mTrans);
    mResult.mult(mToWorld);

    _camTransform = mResult;
}


/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

ActionBase::ResultE Billboard::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_camTransform);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return ActionBase::Continue; 
}

ActionBase::ResultE Billboard::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_camTransform);

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE Billboard::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    Matrix mMat;

    calcMatrix(pAction, pAction->top_matrix(), mMat);

    pAction->push_matrix(mMat);

// !!! can't use visibles, as ToWorld gives garbage leading to wrong culling
//    pAction->selectVisibles();

    return ActionBase::Continue;
}

ActionBase::ResultE Billboard::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pop_matrix();

    return ActionBase::Continue;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id$";
    static char cvsid_hpp[] = OSGBILLBOARD_HEADER_CVSID;
    static char cvsid_inl[] = OSGBILLBOARD_INLINE_CVSID;
}
