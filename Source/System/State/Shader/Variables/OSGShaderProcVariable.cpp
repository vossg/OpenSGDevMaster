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

#include <OSGConfig.h>

#include "OSGShaderProcVariable.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderProcVariableBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderProcVariable.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProcVariable::initMethod(InitPhase ePhase)
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

ShaderProcVariable::ShaderProcVariable(void) :
    Inherited()
{
}

ShaderProcVariable::ShaderProcVariable(const ShaderProcVariable &source) :
    Inherited(source)
{
}

ShaderProcVariable::~ShaderProcVariable(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderProcVariable::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    MFParentFieldContainerPtr::const_iterator parentsIt  = 
        this->_mfParents.begin();

    MFParentFieldContainerPtr::const_iterator parentsEnd = 
        this->_mfParents.end();
    
    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
            TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
            ChangedOrigin::Child,
            0);
        
        ++parentsIt;
    }

    Inherited::changed(whichField, origin, details);
}

void ShaderProcVariable::dump(      UInt32    , 
                              const BitVector ) const
{
    SLOG << "Dump ShaderProcVariable NI" << std::endl;
}

