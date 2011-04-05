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

#include "OSGConfig.h"

#include "OSGShaderVariableFunctor.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderVariableFunctorBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderVariableFunctor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderVariableFunctor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderVariableFunctor::ShaderVariableFunctor(void) :
     Inherited ( ),
#ifdef OSG_1_COMPAT
    _uiFuncMode(0),

    _pPFunc    ( ),
    _pOSGPFunc ( ),
#endif

    _pFunc     ( ),
    _pNodeFunc ( )
{
    setTypeId(ShaderVariable::SHVTypeFunctor);
}

ShaderVariableFunctor::ShaderVariableFunctor(
    const ShaderVariableFunctor &source) :
    
     Inherited (source),
#ifdef OSG_1_COMPAT
    _uiFuncMode(0     ),

    _pPFunc    (      ),
    _pOSGPFunc (      ),
#endif

    _pFunc     (      ),
    _pNodeFunc (      )
{
}

ShaderVariableFunctor::~ShaderVariableFunctor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderVariableFunctor::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderVariableFunctor::dump(      UInt32    , 
                                 const BitVector ) const
{
    SLOG << "Dump ShaderVariableFunctor NI" << std::endl;
}

bool ShaderVariableFunctor::isProcedural(void) const
{
    return true;
}

