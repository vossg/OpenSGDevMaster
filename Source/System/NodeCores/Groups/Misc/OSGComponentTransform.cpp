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
#include "OSGIntersectAction.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGIntersectActor.h"
#endif

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGComponentTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGComponentTransform.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Changed                                   */

void ComponentTransform::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    if((whichField & CenterFieldMask          ) ||
       (whichField & RotationFieldMask        ) ||
       (whichField & ScaleFieldMask           ) ||
       (whichField & ScaleOrientationFieldMask) ||
       (whichField & TranslationFieldMask     )  )
    {
        // be careful not to mark the matrix as changed here to avoid
        // bouncing changes back and forth
        _sfMatrix.getValue().setTransform(getTranslation     (),
                                          getRotation        (),
                                          getScale           (),
                                          getScaleOrientation(),
                                          getCenter          ());

        invalidateVolume();
    }
    else if(whichField & Inherited::MatrixFieldMask)
    {
        Vec3f      translation;
        Quaternion rotation;
        Vec3f      scale;
        Quaternion scaleOrientation;
        Vec3f      center;

        _sfMatrix.getValue().getTransform(translation,
                                          rotation,
                                          scale,
                                          scaleOrientation,
                                          center           );

        // be careful not to mark the components as changed here to avoid
        // bouncing changes back and forth
        _sfTranslation     .setValue(translation     );
        _sfRotation        .setValue(rotation        );
        _sfScale           .setValue(scale           );
        _sfScaleOrientation.setValue(scaleOrientation);
        _sfCenter          .setValue(center          );
    }

    Inherited::changed(whichField, origin, details);
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
            ComponentTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::renderEnter));
        
        RenderAction::registerLeaveDefault(
            ComponentTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::renderLeave));
        
        
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ComponentTransform::intersectLeave));
        
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
