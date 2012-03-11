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

#include "OSGCallbackAlgorithm.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCallbackAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGCallbackAlgorithm.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CallbackAlgorithm::initMethod(InitPhase ePhase)
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

CallbackAlgorithm::CallbackAlgorithm(void) :
    Inherited()
{
}

CallbackAlgorithm::CallbackAlgorithm(const CallbackAlgorithm &source) :
    Inherited(source)
{
}

CallbackAlgorithm::~CallbackAlgorithm(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CallbackAlgorithm::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CallbackAlgorithm::setCallback(RenderFunctor func,
                                    std::string   createSymbol)
{
    RenderFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _sfCallback.setValue(oTmp);
}

void CallbackAlgorithm::execute(DrawEnv *pEnv)
{
    if(_sfCallback.getValue()._func)
    {
        _sfCallback.getValue()._func(pEnv);
    }
}

Action::ResultE CallbackAlgorithm::renderEnter(Action  *pAction)
{
    if(_sfRenderEnter.getValue()._func)
    {
        return _sfRenderEnter.getValue()._func(pAction);
    }

    return Action::Continue;
}

Action::ResultE CallbackAlgorithm::renderLeave(Action  *pAction)
{
    if(_sfRenderLeave.getValue()._func)
    {
        return _sfRenderLeave.getValue()._func(pAction);
    }

    return Action::Continue;
}

void CallbackAlgorithm::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CallbackAlgorithm NI" << std::endl;
}

OSG_END_NAMESPACE
