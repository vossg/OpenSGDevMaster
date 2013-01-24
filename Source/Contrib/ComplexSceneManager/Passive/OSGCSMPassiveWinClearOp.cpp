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

#include "OSGCSMPassiveWinClearOp.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMPassiveWinClearOpBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMPassiveWinClearOp.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMPassiveWinClearOp::initMethod(InitPhase ePhase)
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

CSMPassiveWinClearOp::CSMPassiveWinClearOp(void) :
    Inherited()
{
}

CSMPassiveWinClearOp::CSMPassiveWinClearOp(const CSMPassiveWinClearOp &source) :
    Inherited(source)
{
}

CSMPassiveWinClearOp::~CSMPassiveWinClearOp(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMPassiveWinClearOp::changed(ConstFieldMaskArg whichField, 
                                   UInt32            origin,
                                   BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMPassiveWinClearOp::execute(CSMPassiveWindow *pWin)
{
    fprintf(stderr, "passivewinclearop::exe\n");

    glClearColor(0.2, 0.5, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CSMPassiveWinClearOp::postDraw(CSMPassiveWindow *pWin)
{
    fprintf(stderr, "passivewinclearop::postdraw\n");
}

void CSMPassiveWinClearOp::dump(      UInt32    ,
                                const BitVector ) const
{
    SLOG << "Dump CSMPassiveWinClearOp NI" << std::endl;
}

OSG_END_NAMESPACE
