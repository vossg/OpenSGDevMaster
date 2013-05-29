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

#include "OSGShaderValueVariable.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderValueVariableBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderValueVariable.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderValueVariable::initMethod(InitPhase ePhase)
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

ShaderValueVariable::ShaderValueVariable(void) :
    Inherited()
{
}

ShaderValueVariable::ShaderValueVariable(const ShaderValueVariable &source) :
    Inherited(source)
{
}

ShaderValueVariable::~ShaderValueVariable(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderValueVariable::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    MFParentFieldContainerPtr::const_iterator parentsIt  = 
        this->_mfExeParents.begin();

    MFParentFieldContainerPtr::const_iterator parentsEnd = 
        this->_mfExeParents.end();
    
    MFUInt16::const_iterator idxIt = _mfExeVariableIdx.begin();

    OSG_ASSERT(_mfExeParents.size() == _mfExeVariableIdx.size());

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
            TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
            ChangedOrigin::Child,
            *idxIt);
        
        ++parentsIt;
        ++idxIt;
    }



    parentsIt  = this->_mfParents.begin();
    parentsEnd = this->_mfParents.end();
    
    idxIt      = _mfVariableIdx.begin();

    OSG_ASSERT(_mfParents.size() == _mfVariableIdx.size());

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
            TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
            ChangedOrigin::Child,
            *idxIt);
        
        ++parentsIt;
        ++idxIt;
    }


    Inherited::changed(whichField, origin, details);
}

void ShaderValueVariable::dump(      UInt32    , 
                               const BitVector ) const
{
    SLOG << "Dump ShaderValueVariable NI" << std::endl;
}

bool ShaderValueVariable::linkParent(FieldContainer * const pParent,
                                     UInt16           const childFieldId,
                                     UInt16           const parentFieldId)
{
    OSG_ASSERT(false);

    return false;
}

bool ShaderValueVariable::unlinkParent(FieldContainer * const pParent,
                                       UInt16           const parentFieldId)
{
    OSG_ASSERT(false);

    return false;
}

void ShaderValueVariable::addParent(FieldContainer * const pParent,
                                    UInt16                 uiParentFieldId,
                                    UInt16                 uiVarIdx       )
{
    editMField(ParentsFieldMask,     _mfParents    );
    editMField(VariableIdxFieldMask, _mfVariableIdx);

    _mfParents    .push_back(pParent, uiParentFieldId);
    _mfVariableIdx.push_back(uiVarIdx                );
    
}

void ShaderValueVariable::subParent(FieldContainer * const pParent)
{
    Int32 iParentIdx = _mfParents.findIndex(pParent);

    if(iParentIdx != -1)
    {
        editMField(ParentsFieldMask,     _mfParents    );
        editMField(VariableIdxFieldMask, _mfVariableIdx);

        _mfParents    .erase(iParentIdx);
        _mfVariableIdx.erase(iParentIdx);
    }
}

void ShaderValueVariable::addExeParent(FieldContainer * const pParent,
                                       UInt16                 uiParentFieldId,
                                       UInt16                 uiVarIdx       )
{
    editMField(ExeParentsFieldMask,     _mfExeParents    );
    editMField(ExeVariableIdxFieldMask, _mfExeVariableIdx);

    _mfExeParents    .push_back(pParent, uiParentFieldId);
    _mfExeVariableIdx.push_back(uiVarIdx                );
    
}

void ShaderValueVariable::subExeParent(FieldContainer * const pParent)
{
    Int32 iParentIdx = _mfExeParents.findIndex(pParent);

    if(iParentIdx != -1)
    {
        editMField(ExeParentsFieldMask,     _mfExeParents    );
        editMField(ExeVariableIdxFieldMask, _mfExeVariableIdx);

        _mfExeParents    .erase(iParentIdx);
        _mfExeVariableIdx.erase(iParentIdx);
    }
}
