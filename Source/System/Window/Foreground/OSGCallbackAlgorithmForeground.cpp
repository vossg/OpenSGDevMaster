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

#include "OSGConfig.h"

#include "OSGCallbackAlgorithm.h"
#include "OSGCallbackAlgorithmForeground.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCallbackAlgorithmForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGCallbackAlgorithmForeground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CallbackAlgorithmForeground::initMethod(InitPhase ePhase)
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

CallbackAlgorithmForeground::CallbackAlgorithmForeground(void) :
    Inherited()
{
}

CallbackAlgorithmForeground::CallbackAlgorithmForeground(const CallbackAlgorithmForeground &source) :
    Inherited(source)
{
}

CallbackAlgorithmForeground::~CallbackAlgorithmForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CallbackAlgorithmForeground::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CallbackAlgorithmForeground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CallbackAlgorithmForeground NI" << std::endl;
}

/*----------------------------- Draw --------------------------------------*/

void CallbackAlgorithmForeground::draw(DrawEnv *pEnv)
{
    if(getActive() == false)
        return;

    CallbackAlgorithm* cb = getCallbackAlgorithm();
    if (cb == NULL)
        return;

    cb->execute(pEnv);
}

OSG_END_NAMESPACE
