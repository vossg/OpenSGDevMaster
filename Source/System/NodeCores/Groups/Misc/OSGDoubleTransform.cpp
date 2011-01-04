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

#include "OSGConfig.h"

#include "OSGGL.h"

#include "OSGIntersectAction.h"

#include "OSGRenderAction.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGIntersectActor.h"
#endif

#include "OSGDoubleTransform.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDoubleTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGDoubleTransform.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void DoubleTransform::changed(ConstFieldMaskArg whichField,
                              UInt32            origin,
                              BitVector         details)
{
    if(whichField & MatrixFieldMask)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin, details);
}

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- class specific ----------------------------*/

void DoubleTransform::accumulateMatrix(Matrix &result)
{
    result.mult(getMatrix());
}

void DoubleTransform::adjustVolume(Volume &volume)
{
    Matrix4f temp;
    temp.convertFrom(_sfMatrix.getValue());
    volume.transform(temp);
}

void DoubleTransform::dump(      UInt32    uiIndent, 
                           const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DoubleTransform::DoubleTransform(void) :
    Inherited()
{
    _sfMatrix.getValue().setIdentity();
}

DoubleTransform::DoubleTransform(const DoubleTransform &source) :
    Inherited(source)
{
}

DoubleTransform::~DoubleTransform(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE DoubleTransform::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    pAction->pushMatrix(this->getMatrix());

    return ActionBase::Continue;
}

ActionBase::ResultE DoubleTransform::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

ActionBase::ResultE DoubleTransform::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix4d         matd = this->getMatrix();

    matd.invert();

    Matrix4f m;
    m.convertFrom(matd);

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return ActionBase::Continue; 
}

ActionBase::ResultE DoubleTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix4d         matd = this->getMatrix();

    Matrix4f m;
    m.convertFrom(matd);

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return ActionBase::Continue;
}

#ifdef OSG_HAVE_ACTION //CHECK
NewActionTypes::ResultE Transform::intersectActorEnter(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA        = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    Matrix          matrix     = this->getMatrix();
    Line            transLine;
    Pnt3f           pos;
    Vec3f           dir;

    matrix.invert();

    matrix.multFullMatrixPnt(pIA->getRay().getPosition (), pos);
    matrix.multMatrixVec    (pIA->getRay().getDirection(), dir);

    transLine.setValue(pos, dir);

    pIA->beginEditState();
    {
        pIA->setRay        (transLine                           );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    pIA->setupChildrenPriorities();

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE Transform::intersectActorLeave(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA    = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    const Matrix   &matrix = this->getMatrix();
          Pnt3f     pos;
          Vec3f     dir;

    matrix.multFullMatrixPnt(pIA->getRay().getPosition (), pos);
    matrix.multMatrixVec    (pIA->getRay().getDirection(), dir);

    pIA->beginEditState();
    {
        pIA->setRay        (Line(pos, dir)                      );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    return NewActionTypes::Continue;
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void DoubleTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&DoubleTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&DoubleTransform::intersectLeave));
       
        RenderAction::registerEnterDefault(
            getClassType(), 
            reinterpret_cast<Action::Callback>(&DoubleTransform::renderEnter));
        
        RenderAction::registerLeaveDefault(
            getClassType(), 
            reinterpret_cast<Action::Callback>(&DoubleTransform::renderLeave));

#ifdef OSG_HAVE_ACTION //CHECK
    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          TransformPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&DoubleTransform::intersectActorEnter),
        getClassType());

    IntersectActor::regClassLeave(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          TransformPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&DoubleTransform::intersectActorLeave),
        getClassType());
#endif
    }
}


OSG_END_NAMESPACE
