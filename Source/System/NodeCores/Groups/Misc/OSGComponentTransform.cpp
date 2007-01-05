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

#include "OSGComponentTransform.h"
#include "OSGRenderAction.h"
#ifndef OSG_WINCE
#include "OSGIntersectAction.h"
#endif

#ifdef OSG_HAVE_ACTION //CHECK
#include <OSGIntersectActor.h>
#endif

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGComponentTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGComponentTransform.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Changed                                   */

void ComponentTransform::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    ComponentTransformPtr ptr = 
        Inherited::constructPtr<ComponentTransform>(this);

    if((whichField & CenterFieldMask          ) ||
       (whichField & RotationFieldMask        ) ||
       (whichField & ScaleFieldMask           ) ||
       (whichField & ScaleOrientationFieldMask) ||
       (whichField & TranslationFieldMask     )  )
    {
        editMatrix().setTransform(getTranslation     (),
                                  getRotation        (),
                                  getScale           (),
                                  getScaleOrientation(),
                                  getCenter          ());
    }

    Inherited::changed(whichField, origin);
}

void ComponentTransform::dump(      UInt32    uiIndent,
                              const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ComponentTransform::ComponentTransform(void) :
    Inherited()
{
    _sfScale.getValue().setValues(1.f, 1.f, 1.f);
}

ComponentTransform::ComponentTransform(const ComponentTransform &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ComponentTransform::~ComponentTransform(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ComponentTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::renderEnter));
        
        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::renderLeave));
        
        
#ifndef OSG_WINCE
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::intersectLeave));
#endif
        
#ifdef OSG_HAVE_ACTION //CHECK
        IntersectActor::regClassEnter(
            osgTypedMethodFunctor2BaseCPtr<
                NewActionTypes::ResultE,
                ComponentTransformPtr  ,
                NodeCorePtr            ,
                ActorBase::FunctorArgumentType &>(
                    &ComponentTransform::intersectActorEnter),
            getClassType());
        
        IntersectActor::regClassLeave(
            osgTypedMethodFunctor2BaseCPtr<
                NewActionTypes::ResultE,
                ComponentTransformPtr  ,
                NodeCorePtr            ,
                ActorBase::FunctorArgumentType &>(
                    &ComponentTransform::intersectActorLeave),
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
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGCOMPONENTTRANSFORM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGCOMPONENTTRANSFORM_INLINE_CVSID;
}


