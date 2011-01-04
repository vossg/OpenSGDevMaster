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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGL.h"

#include "OSGIntersectAction.h"

#include "OSGRenderAction.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGIntersectActor.h"
#endif

#include "OSGTransform.h"
#include "OSGVolume.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGTransform.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Transform::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    if(whichField & MatrixFieldMask)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void Transform::accumulateMatrix(Matrix &result)
{
    result.mult(getMatrix());
}

void Transform::adjustVolume(Volume &volume)
{
    volume.transform(_sfMatrix.getValue());
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void Transform::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags ) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Transform::Transform(void) :
    Inherited()
{
    _sfMatrix.getValue().setIdentity();
}

Transform::Transform(const Transform &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Transform::~Transform(void)
{
}


/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE Transform::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    pAction->pushMatrix(this->getMatrix());

    return ActionBase::Continue;
}

ActionBase::ResultE Transform::renderLeave(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

ActionBase::ResultE Transform::intersectEnter(Action *action)
{
    // Use parent class for trivial reject
    if(Inherited::intersect(action) == Action::Skip)
        return Action::Skip;
    
    // Need to check children
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    Real32 length = dir.length();

    if(length < TypeTraits<Real32>::getDefaultEps())
        SWARNING << "Transform::intersectEnter: Near-zero scale!" << std::endl;

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale  (length                          );
    
    return ActionBase::Continue; 
}

ActionBase::ResultE Transform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();
    
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

    matrix.multFull(pIA->getRay().getPosition (), pos);
    matrix.mult    (pIA->getRay().getDirection(), dir);

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

    matrix.multFull(pIA->getRay().getPosition (), pos);
    matrix.mult    (pIA->getRay().getDirection(), dir);

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

void Transform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::intersectLeave));
       
        RenderAction::registerEnterDefault(
            Transform::getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::renderEnter));

        RenderAction::registerLeaveDefault(
            Transform::getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::renderLeave));

#ifdef OSG_HAVE_ACTION //CHECK
    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          TransformPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&Transform::intersectActorEnter),
        getClassType());

    IntersectActor::regClassLeave(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          TransformPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&Transform::intersectActorLeave),
        getClassType());
#endif
    }
}

