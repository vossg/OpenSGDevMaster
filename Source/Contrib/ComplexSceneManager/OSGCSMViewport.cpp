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

#include <OSGConfig.h>

#include "OSGCSMViewport.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMViewport::initMethod(InitPhase ePhase)
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

CSMViewport::CSMViewport(void) :
    Inherited()
{
}

CSMViewport::CSMViewport(const CSMViewport &source) :
    Inherited(source)
{
}

CSMViewport::~CSMViewport(void)
{
}

void CSMViewport::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pViewport = NULL;
}

/*----------------------------- class specific ----------------------------*/

void CSMViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMViewport NI" << std::endl;
}

bool CSMViewport::init(void)
{
    bool returnValue = true;

    _pViewport = Viewport::create();

    _pViewport->setRoot      (_sfRoot      .getValue());
    _pViewport->setCamera    (_sfCamera    .getValue());
    _pViewport->setBackground(_sfBackground.getValue());

    MFUnrecForegroundPtr::const_iterator fIt  = getMFForegrounds()->begin();
    MFUnrecForegroundPtr::const_iterator fEnd = getMFForegrounds()->end  ();

    while(fIt != fEnd)
    {
        _pViewport->addForeground(*fIt);

        ++fIt;
    }

    return returnValue;
}

Viewport *CSMViewport::getPort(void)
{
    return _pViewport;
}

OSG_END_NAMESPACE
