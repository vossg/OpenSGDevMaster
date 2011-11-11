/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGScreenTransform.h"
#include "OSGVolume.h"
#include "OSGPlane.h"
#include "OSGIntersectAction.h"

#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGScreenTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGScreenTransform.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScreenTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ScreenTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ScreenTransform::intersectLeave));
       
        RenderAction::registerEnterDefault(
            ScreenTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenTransform::renderEnter));

        RenderAction::registerLeaveDefault(
            ScreenTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenTransform::renderLeave));

    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ScreenTransform::calcMatrix(const Matrix  &toWorld, 
                                       DrawEnv &oEnv   )
{
    //Get the local to world transformation
    Matrix mBeaconToWorld;

    if(getBeacon() != NULL)
    {
        mBeaconToWorld = getBeacon()->getToWorld();
    }
    else
    {
        mBeaconToWorld.setIdentity();
    }
    
#if 0
    //Get the Viewport Camera
    CameraUnrecPtr ViewportCamera = theViewport->getCamera();

    //Get the World to View transformation
    ViewportCamera->getViewing(WorldToView, theViewport->getPixelWidth(), theViewport->getPixelHeight());
#endif

    Matrix mWorldToView = oEnv.getVPCameraViewing();

    //Store the previous value
    Matrix mPrevValue = _mTransform;
    
    //Invert the current Model Transformation
    if(getInvertWorldTransform())
    {
        _mTransform.invertFrom(toWorld);
    }
    else
    {
        _mTransform.setIdentity();
    }

    //Invert the current View Transformation
    if(getInvertViewTransform())
    {
        Matrix mViewToWorld;

        mViewToWorld.invertFrom(mWorldToView);

        _mTransform.mult(mViewToWorld);
        

        //Setup a new view transformation
        _mTransform.mult(getView());
    }

    //Setup a new Model Transformation, transform such that the screen
    //position of the origin of the beacon 
    //node and the screen position of the origin of child nodes are the same.
    if(getApplyBeaconScreenTranslation())
    {
#if 0
        //The Screen Pos should now be projected to the near plane
        Matrix proj, projtrans;

        ViewportCamera->getProjection(proj,
                           theViewport->getPixelWidth(),
                           theViewport->getPixelHeight());

        ViewportCamera->getProjectionTranslation(projtrans,
                                      theViewport->getPixelWidth(),
                                      theViewport->getPixelHeight());
#endif

        Matrix proj      = oEnv.getVPCameraProjection     ();
        Matrix projtrans = oEnv.getVPCameraProjectionTrans();

        Matrix wctocc = proj;

        wctocc.mult(projtrans);

        Matrix cctowc;

        cctowc.invertFrom(wctocc);

        Pnt3f from, at;

        Pnt3f vBeaconScreenPos = mBeaconToWorld * Pnt3f(0.0f,0.0f,0.0f);


        //Get the World to Screen transformation
        Matrix mWorldToScreen = oEnv.getVPWorldToScreen();
//        ViewportCamera->getWorldToScreen(WorldToScreen, *theViewport);

        mWorldToScreen.multFull(vBeaconScreenPos, vBeaconScreenPos);

        cctowc.multFull(Pnt3f(vBeaconScreenPos.x(), 
                              vBeaconScreenPos.y(), -1), from);

        cctowc.multFull(Pnt3f(vBeaconScreenPos.x(), 
                              vBeaconScreenPos.y(),  1), at  );

        Vec3f dir = at - from;

        Line line;
        line.setValue(from, dir);

        Vec3f vPlaneNormal(0.0f, 0.0f, 1.0f);
        Pnt3f vPlanePoint (0.0f, 0.0f, 0.0f);

        getView().mult(vPlaneNormal, vPlaneNormal);
        getView().mult(vPlanePoint,  vPlanePoint );

        Plane p(vPlaneNormal, vPlanePoint);

        Real32 t;

        p.intersect(line,t);

        Pnt3f vTransformedPoint = line.getPosition() + line.getDirection() * t;
        
        Matrix mTranslateMat;

        mTranslateMat.setIdentity();

        mTranslateMat.setTranslate(Vec3f(vTransformedPoint.x(),
                                         vTransformedPoint.y(),
                                         0.0f                 ));

        _mTransform.mult(mTranslateMat);
    }
    
    //The new model transformation should be rotated by the Beacons rotation
    if(getApplyBeaconRotation())
    {
        Matrix mBeaconToView = mBeaconToWorld;

        if(getInvertViewTransform())
        {
            mBeaconToView.multLeft(mWorldToView);
        }

        Vec3f      vTranslation;       // for matrix decomposition
        Quaternion qBeaconRot;
        Vec3f      vScaleFactor;
        Quaternion qScaleOrientation;
        
        mBeaconToView.getTransform(vTranslation, 
                                   qBeaconRot, 
                                   vScaleFactor, 
                                   qScaleOrientation);

        Matrix mRotMat;

        mRotMat.setRotate(qBeaconRot);

        _mTransform.mult(mRotMat);
    }

    if(_mTransform != mPrevValue)
    {
        invalidateVolume();
    }
}

void ScreenTransform::accumulateMatrix(Matrix &result)
{
    result.mult(_mTransform);
}

void ScreenTransform::adjustVolume(Volume &volume)
{
    volume.transform(_mTransform);
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE ScreenTransform::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    calcMatrix(pAction->topMatrix(), 
               pAction->getActivePartition()->getDrawEnv());

    pAction->pushVisibility();

    pAction->pushMatrix(_mTransform);

    return Action::Continue;
}

ActionBase::ResultE ScreenTransform::renderLeave(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

ActionBase::ResultE ScreenTransform::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = _mTransform;

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

ActionBase::ResultE ScreenTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = _mTransform;

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScreenTransform::ScreenTransform(void) :
     Inherited (),
    _mTransform()
{
}

ScreenTransform::ScreenTransform(const ScreenTransform &source) :
     Inherited (source            ),
    _mTransform(source._mTransform)
{
}

ScreenTransform::~ScreenTransform(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScreenTransform::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & BeaconFieldMask)
    {
        invalidateVolume();
    }
}

void ScreenTransform::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump ScreenTransform NI" << std::endl;
}

OSG_END_NAMESPACE
