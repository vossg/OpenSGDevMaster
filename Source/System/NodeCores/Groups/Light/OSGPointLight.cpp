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

#include <OSGRenderAction.h>
#include "OSGPointLight.h"

#include <OSGStatCollector.h>

OSG_USING_NAMESPACE

/*! \class OSG::PointLight
    PointLight is a located lightsource. The position of the light source
    (in the beacon's coordinate system) is defined by the \c position 
    attribute. The influence of the light diminishes with distance, controlled
    by the \c constantAttenuation, \c linearAttenuation and \c
    quadraticAttenuation attributes.
*/

/*----------------------------- class variables ---------------------------*/

StatElemDesc<StatIntElem>  PointLight::statNPointLights(
    "NPointLights", 
    "number of point light sources");

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void PointLight::setPosition(Real32 rX, Real32 rY, Real32 rZ)
{
    editSField(PositionFieldMask);

    _sfPosition.getValue().setValues(rX, rY, rZ);
}

void PointLight::setAttenuation(Real32 rConstant, 
                                Real32 rLinear, 
                                Real32 rQuadratic)
{
    editSField(ConstantAttenuationFieldMask );
    editSField(LinearAttenuationFieldMask   );
    editSField(QuadraticAttenuationFieldMask);

    _sfConstantAttenuation .setValue(rConstant );
    _sfLinearAttenuation   .setValue(rLinear   );
    _sfQuadraticAttenuation.setValue(rQuadratic);
}

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

void PointLight::makeChunk(void)
{
    Inherited::makeChunk();

    Vec4r pos(_sfPosition.getValue());

    pos[3] = 1.f;
   
    _pChunk->setPosition            (pos                      );
    _pChunk->setConstantAttenuation (getConstantAttenuation ());
    _pChunk->setLinearAttenuation   (getLinearAttenuation   ());
    _pChunk->setQuadraticAttenuation(getQuadraticAttenuation());
}

/*-------------------------------------------------------------------------*/
/*                             Changed                                     */

void PointLight::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void PointLight::dump(      UInt32    uiIndent, 
                      const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

PointLight::PointLight(void) :
    Inherited()
{
}

PointLight::PointLight(const PointLight &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

PointLight::~PointLight(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

Action::ResultE PointLight::renderEnter(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    da->getStatistics()->getElem(PointLight::statNPointLights)->inc();

    return Light::renderEnter(action);
}

Action::ResultE PointLight::renderLeave(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    return Light::renderLeave(action);
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void PointLight::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&PointLight::renderEnter));

        RenderAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&PointLight::renderLeave));
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
    static Char8 cvsid_hpp[] = OSGPOINTLIGHT_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGPOINTLIGHT_INLINE_CVSID;
}
