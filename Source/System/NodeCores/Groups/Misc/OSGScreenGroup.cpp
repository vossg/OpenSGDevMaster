/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGConfig.h"

#include "OSGScreenGroup.h"
#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ScreenGroup
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScreenGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            ScreenGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenGroup::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            ScreenGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenGroup::intersectLeave));

        RenderAction::registerEnterDefault(
            ScreenGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenGroup::renderEnter));

        RenderAction::registerLeaveDefault(
            ScreenGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenGroup::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScreenGroup::ScreenGroup(void) :
    Inherited()
{
}

ScreenGroup::ScreenGroup(const ScreenGroup &source) :
    Inherited(source)
{
}

ScreenGroup::~ScreenGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScreenGroup::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ScreenGroup::dump(      UInt32    , 
                       const BitVector ) const
{
    SLOG << "Dump ScreenGroup NI" << std::endl;
}


/*------------------------- volume update -------------------------------*/

void ScreenGroup::adjustVolume(Volume &volume)
{
    volume.transform(_camTransform);
}

void ScreenGroup::accumulateMatrix(Matrix &result)
{
    result.mult(_camTransform);
}

void ScreenGroup::calcMatrix(      RenderAction *pAction,
                             const Matrix        &mToWorld,
                                   Matrix        &mResult )
{
    const DrawEnv &oEnv = pAction->getActivePartition()->getDrawEnv();

    Matrix mToScreen = oEnv.getVPWorldToScreen();

#if 0
    Viewport *viewport = pAction->getViewport();
    pAction->getCamera()->getWorldToScreen(mToScreen, *viewport);
#endif

    mToScreen.mult(mToWorld);

    Pnt3f origin(0.f, 0.f, 0.f);

    mToScreen.multFull(origin, origin);

    Pnt3f xAxis(1.f, 0.f, 0.f);

    mToScreen.multFull(xAxis, xAxis);

    Real32 scaleX =  
        2.f / oEnv.getPixelWidth() / (xAxis - origin).length();

    Pnt3f yAxis(0.f, 1.f, 0.f);

    mToScreen.multFull(yAxis, yAxis);

    Real32 scaleY = 
        2.f / oEnv.getPixelHeight() / (yAxis - origin).length();

    mResult.setScale    (scaleX, scaleY, 1.f);
    mResult.setTranslate(0.375 * scaleX, 0.375 * scaleY, 0.f);
    
    bool equal = mResult.equals(_camTransform, 0.00001f);
        
    _camTransform = mResult;
        
    if(!equal)
        this->invalidateVolume();
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

Action::ResultE ScreenGroup::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_camTransform);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

Action::ResultE ScreenGroup::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_camTransform);

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE ScreenGroup::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    Matrix mMat;

#if 0
    if(!pAction->getEffectsPass())
		calcMatrix(pAction, pAction->top_matrix(), mMat);
	else
		mMat = _camTransform;
#else
    calcMatrix(pAction, pAction->topMatrix(), mMat);
#endif

    pAction->pushMatrix(mMat);

// !!! can't use visibles, as ToWorld gives garbage leading to wrong culling
//    pAction->selectVisibles();

    return Action::Continue;
}

Action::ResultE ScreenGroup::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->popMatrix();

    return Action::Continue;
}

OSG_END_NAMESPACE

