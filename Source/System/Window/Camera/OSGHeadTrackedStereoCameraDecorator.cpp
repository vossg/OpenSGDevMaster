/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#define OSG_COMPILEEXTLIB

#include "OSGConfig.h"
#include "OSGNode.h"
#include "OSGHeadTrackedStereoCameraDecorator.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// HeadTrackedStereoCameraDecoratorBase.cpp file.
// To modify it, please change the .fcd file (OSGHeadTrackedStereoCameraDecorator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HeadTrackedStereoCameraDecorator::initMethod(InitPhase ePhase)
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

HeadTrackedStereoCameraDecorator::HeadTrackedStereoCameraDecorator(void) :
    Inherited()
{
}

HeadTrackedStereoCameraDecorator::HeadTrackedStereoCameraDecorator(const HeadTrackedStereoCameraDecorator &source) :
    Inherited(source)
{
}

HeadTrackedStereoCameraDecorator::~HeadTrackedStereoCameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HeadTrackedStereoCameraDecorator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HeadTrackedStereoCameraDecorator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump HeadTrackedStereoCameraDecorator NI" << std::endl;
}

void HeadTrackedStereoCameraDecorator::getViewing(Matrix &result, 
                                           UInt32  OSG_CHECK_ARG(width ),
                                           UInt32  OSG_CHECK_ARG(height))
{
    Node *pUser = getUser();

    if(pUser == NULL)
    {
        FWARNING(("HeadTrackedStereoCameraDecorator::getViewing: no user!\n"));

        Camera *pCamera = getDecoratee();

        if(pCamera == NULL)
        {
            result.setIdentity();

            return;
        }

        pCamera->getBeacon()->getToWorld(result);

        result.invert();
    }
    else
    {
        pUser->getToWorld(result);

        result.invert();
    }
}

OSG_END_NAMESPACE
