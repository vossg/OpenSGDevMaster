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

#include "OSGShaderParameter.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderParameterBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderParameter.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderParameter::initMethod(InitPhase ePhase)
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

ShaderParameter::ShaderParameter(void) :
     Inherited(              ),
    _changed  (false         ),
    _typeid   (SHPTypeUnknown),
    _location (            -1),
    _flags    (SHPFlagNone   )
{
}

ShaderParameter::ShaderParameter(const ShaderParameter &source) :
     Inherited(source          ),
    _changed  (source._changed ),
    _typeid   (source._typeid  ),
    _location (source._location),
    _flags    (source._flags   )
{
}

ShaderParameter::~ShaderParameter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderParameter::addParent(
          FieldContainerPtrConst &parent,
    const UInt16                  uiStoredInFieldMask)
{
    editMField(ParentsFieldMask, _mfParents);

//    _mfParents.push_back(parent);
//    _mfParents.back().setParentFieldPos(uiStoredInFieldMask);
    _mfParents.push_back(parent, uiStoredInFieldMask);
}

void ShaderParameter::subParent(FieldContainerPtrConst &parent)
{
    Int32 iParentIdx = _mfParents.findIndex(parent);

    if(iParentIdx != -1)
    {
        editMField(ParentsFieldMask, _mfParents);

#if 0
        MFParentFieldContainerPtr::iterator parentIt = _mfParents.begin();

        parentIt += iParentIdx;

        _mfParents.erase(parentIt);
#endif
        _mfParents.erase(iParentIdx);
    }
}

void ShaderParameter::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    MFParentFieldContainerPtr::iterator parentsIt  = _mfParents.begin();
    MFParentFieldContainerPtr::iterator parentsEnd = _mfParents.end();
    
    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(parentsIt.getParentFieldPos(),
                              ChangedOrigin::Child,
                              0);
        
        ++parentsIt;
    }

    Inherited::changed(whichField, origin, details);
}

void ShaderParameter::dump(      UInt32    , 
                           const BitVector ) const
{
    SLOG << "Dump ShaderParameter NI" << std::endl;
}

