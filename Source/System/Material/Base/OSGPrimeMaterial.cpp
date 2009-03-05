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

#include "OSGPrimeMaterial.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPrimeMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGPrimeMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PrimeMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void PrimeMaterial::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pState = NULL;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PrimeMaterial::PrimeMaterial(void) :
     Inherited(    ),
    _pState   (NULL)
{
}

PrimeMaterial::PrimeMaterial(const PrimeMaterial &source) :
     Inherited(source),
    _pState   (NULL  )
{
}

PrimeMaterial::~PrimeMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PrimeMaterial::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    rebuildState();
}

void PrimeMaterial::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PrimeMaterial NI" << std::endl;
}

State *PrimeMaterial::getState(UInt32)
{
    return _pState;
}

UInt32 PrimeMaterial::getNPasses(void)
{
    return 1;
}

PrimeMaterial *PrimeMaterial::finalize(MaterialMapKey)
{
    return this;
}

OSG_END_NAMESPACE
