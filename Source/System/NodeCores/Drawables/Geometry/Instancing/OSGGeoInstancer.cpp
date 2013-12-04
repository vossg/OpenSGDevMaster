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

#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGeoInstancer.h"
#include "OSGDrawEnv.h"

#include "OSGGLFuncProtos.h"

#include "OSGConceptPropertyChecks.h"
#include "OSGIntersectAction.h"
#include "OSGGeometry.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoInstancerBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoInstancer.fcd) and
// regenerate the base file.


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoInstancer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&GeoInstancer::intersectEnter));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderEnter));
                
        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoInstancer::GeoInstancer(void) :
    Inherited()
{
}

GeoInstancer::GeoInstancer(const GeoInstancer &source) :
    Inherited(source)
{
}

GeoInstancer::~GeoInstancer(void)
{
}


/*------------------------- Chunk Class Access ---------------------------*/

/*----------------------------- class specific ----------------------------*/

void GeoInstancer::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoInstancer::dump(      UInt32    , 
                        const BitVector ) const
{
    SLOG << "GeoInstancer:" << std::endl;
}

/*------------------------------ State ------------------------------------*/


/*-------------------------- Comparison -----------------------------------*/

const SFUnrecMaterialPtr *GeoInstancer::getSFMaterial (void) const
{
    if(_sfBaseGeometry.getValue() != NULL)
    {
        return _sfBaseGeometry.getValue()->getSFMaterial();
    }

    return NULL;
}

SFUnrecMaterialPtr *GeoInstancer::editSFMaterial(void)
{
    if(_sfBaseGeometry.getValue() != NULL)
    {
        return _sfBaseGeometry.getValue()->editSFMaterial();
    }

    return NULL;
}

Material *GeoInstancer::getMaterial(void) const
{
    if(_sfBaseGeometry.getValue() != NULL)
    {
        return _sfBaseGeometry.getValue()->getMaterial();
    }

    return NULL;
}

void GeoInstancer::setMaterial(Material * const value)
{
    if(_sfBaseGeometry.getValue() != NULL)
    {
        return _sfBaseGeometry.getValue()->setMaterial(value);
    }
}

void GeoInstancer::drawPrimitives(DrawEnv *pEnv)
{
    if(_sfBaseGeometry.getValue() == NULL)
        return;

    _sfBaseGeometry.getValue()->drawPrimitives(pEnv, 
                                               _sfNumInstances.getValue());
}

Action::ResultE GeoInstancer::intersectEnter(Action  *action)
{
    if(_sfBaseGeometry.getValue() == NULL)
        return Action::Continue;

    return _sfBaseGeometry.getValue()->intersectEnter(action);

    return Action::Continue;
}

void GeoInstancer::adjustVolume(Volume &volume)
{
    if(_sfBaseGeometry.getValue() == NULL)
        return;

    _sfBaseGeometry.getValue()->adjustVolume(volume);
}

void GeoInstancer::fill(DrawableStatsAttachment *pStat)
{
}

GetFieldHandlePtr GeoInstancer::getHandleMaterial(void) const
{
    if(_sfBaseGeometry.getValue() != NULL)
    {
        return _sfBaseGeometry.getValue()->getHandleMaterial();
    }

    return GetFieldHandlePtr();
}

EditFieldHandlePtr GeoInstancer::editHandleMaterial(void)
{
    if(_sfBaseGeometry.getValue() != NULL)
    {
        return _sfBaseGeometry.getValue()->editHandleMaterial();
    }

    return EditFieldHandlePtr();
}


