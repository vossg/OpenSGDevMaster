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

#include "OSGComputeCallbackAlgorithm.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComputeCallbackAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGComputeCallbackAlgorithm.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComputeCallbackAlgorithm::initMethod(InitPhase ePhase)
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

ComputeCallbackAlgorithm::ComputeCallbackAlgorithm(void) :
    Inherited()
{
}

ComputeCallbackAlgorithm::ComputeCallbackAlgorithm(
    const ComputeCallbackAlgorithm &source) :

    Inherited(source)
{
}

ComputeCallbackAlgorithm::~ComputeCallbackAlgorithm(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComputeCallbackAlgorithm::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ComputeCallbackAlgorithm::setCallback(ComputeFunctor func,
                                           std::string    createSymbol)
{
    ComputeFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _sfCallback.setValue(oTmp);
}

void ComputeCallbackAlgorithm::execute(HardwareContext *pContext, 
                                       DrawEnv         *pEnv    )
{
    if(_sfCallback.getValue()._func)
    {
        _sfCallback.getValue()._func(pContext, pEnv);
    }
}

ActionBase::ResultE ComputeCallbackAlgorithm::renderEnter(Action  *pAction)
{
#if 0
    if(_sfRenderEnter.getValue()._func)
    {
        return _sfRenderEnter.getValue()._func(pAction);
    }
#endif

    return ActionBase::Continue;
}

ActionBase::ResultE ComputeCallbackAlgorithm::renderLeave(Action  *pAction)
{
#if 0
    if(_sfRenderLeave.getValue()._func)
    {
        return _sfRenderLeave.getValue()._func(pAction);
    }
#endif

    return ActionBase::Continue;
}

void ComputeCallbackAlgorithm::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump ComputeCallbackAlgorithm NI" << std::endl;
}

OSG_END_NAMESPACE
