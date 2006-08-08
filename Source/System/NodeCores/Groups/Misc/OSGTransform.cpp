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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>

#ifndef OSG_WINCE
#include <OSGIntersectAction.h>
#endif

#include <OSGRenderAction.h>

#ifdef OSG_HAVE_ACTION //CHECK
#include <OSGIntersectActor.h>
#endif

#include "OSGTransform.h"
#include "OSGVolume.h"

OSG_USING_NAMESPACE

/*! \class osg::Transform

  The basic Transformation class. Just keeps a single matrix. For more complex 
  behaviour, see its descendents.     

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Transform::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    if(whichField & MatrixFieldMask)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void Transform::accumulateMatrix(Matrixr &result)
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
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    pAction->push_matrix(this->getMatrix());

    return ActionBase::Continue;
}

ActionBase::ResultE Transform::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->pop_matrix();

    return ActionBase::Continue;
}


/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

#ifndef OSG_WINCE
ActionBase::ResultE Transform::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());
    
    return ActionBase::Continue; 
}

ActionBase::ResultE Transform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return ActionBase::Continue;
}
#endif

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

void Transform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#ifndef OSG_WINCE
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::intersectLeave));
#endif
       
        RenderAction::registerEnterDefault(
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Transform::renderEnter));
        
        RenderAction::registerLeaveDefault(
            getClassType(), 
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
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGTRANSFORM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGTRANSFORM_INLINE_CVSID;
}
