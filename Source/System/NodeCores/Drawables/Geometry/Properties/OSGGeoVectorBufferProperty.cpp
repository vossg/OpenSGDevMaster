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

#include "OSGGeoVectorBufferProperty.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGeoVectorBufferPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoVectorBufferProperty.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoVectorBufferProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoVectorBufferProperty::GeoVectorBufferProperty(void) :
    Inherited()
{
}

GeoVectorBufferProperty::GeoVectorBufferProperty(
    const GeoVectorBufferProperty &source) :

    Inherited(source)
{
}

GeoVectorBufferProperty::~GeoVectorBufferProperty(void)
{
}

/*----------------------------- onCreate --------------------------------*/

void GeoVectorBufferProperty::onCreate(const GeoVectorBufferProperty *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&Self::handleGL, 
                        GeoPropertyMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &GeoProperty::handleDestroyGL));
}

void GeoVectorBufferProperty::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
    {
        Window::destroyGLObject(getGLId(), 1);
    }

    Inherited::onDestroy(uiContainerId);
}

/*----------------------------- class specific ----------------------------*/

void GeoVectorBufferProperty::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoVectorBufferProperty::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GeoVectorBufferProperty NI" << std::endl;
}

bool GeoVectorBufferProperty::getNormalize(void) const
{
    return false;
}

void GeoVectorBufferProperty::clear(void)
{
    OSG_ASSERT(false);
}

void GeoVectorBufferProperty::resize(size_t)
{
    OSG_ASSERT(false);
}

void GeoVectorBufferProperty::getGenericValue(MaxTypeT&, const UInt32) const
{
    OSG_ASSERT(false);
}

void GeoVectorBufferProperty::setGenericValue(const MaxTypeT&, const UInt32)
{
    OSG_ASSERT(false);
}

GeoPropertyTransitPtr GeoVectorBufferProperty::clone(void)
{
    OSG_ASSERT(false);

    return GeoPropertyTransitPtr(NULL);
}


OSG_END_NAMESPACE
