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

#include "OSGShaderProgramVariables.h"
#include "OSGShaderVariableAccess.h"

#include "OSGShaderVariables.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderProgramVariablesBase.cpp file.
// To modify it, please change the .fcd file 
// (OSGShaderProgramVariables.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProgramVariables::initMethod(InitPhase ePhase)
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

ShaderProgramVariables::ShaderProgramVariables(void) :
     Inherited (    ),
    _pVarAccess(NULL)
{
}

ShaderProgramVariables::ShaderProgramVariables(
    const ShaderProgramVariables &source) :

     Inherited (source),
    _pVarAccess(NULL  )
{
}

ShaderProgramVariables::~ShaderProgramVariables(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderProgramVariables::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         details)
{
    if(0x0000 != (whichField & VariablesFieldMask))
    {
        BitVector d;

        if(origin != ChangedOrigin::Child)
        {
            d = 0x0001;
        }
        else
        {
            d = 0x0002;

            OSG_ASSERT(details < _mfVariableChanged.size());

            editVariableChanged(details) = true;
        }

        MFParentFieldContainerPtr::const_iterator parentsIt  = 
            this->_mfParents.begin();
        
        MFParentFieldContainerPtr::const_iterator parentsEnd = 
            this->_mfParents.end();
        
        while(parentsIt != parentsEnd)
        {
            (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
                ChangedOrigin::Child,
                d);
            
            ++parentsIt;
        }
    }

    if(0x0000 != (whichField & ProceduralVariablesFieldMask))
    {
        BitVector d;

        if(origin != ChangedOrigin::Child)
        {
            d = 0x0001;
        }
        else
        {
            d = 0x0002;
        }

        MFParentFieldContainerPtr::const_iterator parentsIt  = 
            this->_mfParents.begin();
        
        MFParentFieldContainerPtr::const_iterator parentsEnd = 
            this->_mfParents.end();
        
        while(parentsIt != parentsEnd)
        {
            (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
                ChangedOrigin::Child,
                d);
                
            ++parentsIt;
        }
    }

    Inherited::changed(whichField, origin, details);
}

const ShaderProgramVariables::MFVariablesType *
    ShaderProgramVariables::getMFVariables(void) const
{
    return &_mfVariables;
}

const ShaderProgramVariables::MFProceduralVariablesType *
    ShaderProgramVariables::getMFProceduralVariables(void) const
{
    return &_mfProceduralVariables;
}


#if 1
ShaderProgramVariables::MFVariablesType *
    ShaderProgramVariables::editMFVariables(void) 
{
    editMField(VariablesFieldMask, _mfVariables);

    return &_mfVariables;
}
#endif

ShaderProgramVariables::MFProceduralVariablesType *
    ShaderProgramVariables::editMFProceduralVariables(void)
{
    editMField(ProceduralVariablesFieldMask, _mfProceduralVariables);

    return &_mfProceduralVariables;
}

void ShaderProgramVariables::addVariable(ShaderVariable * const value)
{
    _pVarAccess->addVariable(value);
}

void ShaderProgramVariables::subVariable(UInt32 uiIndex)
{
    if(uiIndex < _mfVariables.size())
    {
        _pVarAccess->subVariable(_mfVariables[uiIndex]->getName().c_str(),
                                 NULL,
                                 NULL);
    }
}

void ShaderProgramVariables::clearVariables(void)
{
    ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
        _mfVariables.begin();
    ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
        _mfVariables.end  ();

    for(; mVarIt != mVarEnd; ++mVarIt)
    {
        if(*mVarIt != NULL)
            (*mVarIt)->subParent(this);
    }


    editMField(VariablesFieldMask, _mfVariables);

    _mfVariables.clear();

    editMField(VariableChangedFieldMask, _mfVariableChanged);

    _mfVariableChanged.clear();

    if(_pVarAccess != NULL)
        _pVarAccess->updateMap();
}

const ShaderVariable *
    ShaderProgramVariables::getVariable(const Char8 *name) const
{
    return _pVarAccess->getVariable(name);
}

void ShaderProgramVariables::markAllChanged(void)
{
    std::fill(editMFVariableChanged()->begin(),
              editMFVariableChanged()->end  (),
              true);
}

void ShaderProgramVariables::addProceduralVariable(
    ShaderVariable * const value)
{
    _pVarAccess->addVariable(value);
}

void ShaderProgramVariables::subProceduralVariable(UInt32 uiIndex)
{
    if(uiIndex < _mfProceduralVariables.size())
    {
        _pVarAccess->subVariable(
            _mfProceduralVariables[uiIndex]->getName().c_str(),
            NULL,
            NULL);
    }
}

void ShaderProgramVariables::clearProceduralVariables(void)
{
    editMField(ProceduralVariablesFieldMask, _mfProceduralVariables);

    _mfProceduralVariables.clear();

    if(_pVarAccess != NULL)
        _pVarAccess->updateMap();
}

void ShaderProgramVariables::merge(ShaderProgramVariables *pVars,
                                   MFInt32                *pVarLoc,
                                   MFInt32                *pProcVarLoc)
{
    if(pVars == NULL)
        return;

    editMField(VariablesFieldMask,           _mfVariables          );
    editMField(ProceduralVariablesFieldMask, _mfProceduralVariables);

    MFVariablesType::const_iterator vIt  = pVars->getMFVariables()->begin();
    MFVariablesType::const_iterator vEnd = pVars->getMFVariables()->end  ();

    UInt32 uiPos        = _mfVariables.size();
    UInt32 uiActiveVars = 0;

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt != NULL)
        {
            (*vIt)->addParent(this,
                              ShaderProgramVariables::VariablesFieldId,
                              uiPos);
            
            _mfVariables      .push_back(*vIt);
            _mfVariableChanged.push_back(true);

            ++uiPos;
            ++uiActiveVars;
        }
    }

    if(pVarLoc != NULL)
    {
        pVarLoc->resize(pVarLoc->size() + uiActiveVars,
                        -1);
    }

    _mfProceduralVariables.insert(_mfProceduralVariables.end_nc(),
                                   pVars->getMFProceduralVariables()->begin(),
                                   pVars->getMFProceduralVariables()->end  ());

    if(pProcVarLoc != NULL)
    {
        pProcVarLoc->resize(pProcVarLoc->size() + 
                            pVars->getMFProceduralVariables()->size(),
                            -1);
    }
}


void ShaderProgramVariables::dump(      UInt32    ,
                                  const BitVector ) const
{
    SLOG << "Dump ShaderProgramVariables NI" << std::endl;
}

bool ShaderProgramVariables::addUniformVariable(const Char8    *name,
                                                      bool      value,
                                                      MFInt32  *pVarLoc,
                                                      MFInt32  *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableBool>(name, 
                                                         value, 
                                                         pVarLoc,
                                                         pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name,       
                                                      Int32    value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableInt>(name, 
                                                        value, 
                                                        pVarLoc,
                                                        pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name,
                                                      Real32   value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableReal>(name, 
                                                         value, 
                                                         pVarLoc,
                                                         pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Vec2f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableVec2f>(name, 
                                                          value, 
                                                          pVarLoc,
                                                          pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Vec3f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableVec3f>(name, 
                                                          value, 
                                                          pVarLoc,
                                                          pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Vec4f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableVec4f>(name, 
                                                          value, 
                                                          pVarLoc,
                                                          pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Matrix  &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariableMatrix>(name, 
                                                           value, 
                                                           pVarLoc,
                                                           pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Pnt2f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariablePnt2f>(name, 
                                                          value, 
                                                          pVarLoc,
                                                          pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Pnt3f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addSVariable<ShaderVariablePnt3f>(name, 
                                                          value, 
                                                          pVarLoc,
                                                          pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFInt32 &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMInt>(name, 
                                                         value, 
                                                         pVarLoc,
                                                         pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8    *name, 
                                                const MFReal32 &value,
                                                      MFInt32  *pVarLoc,
                                                      MFInt32  *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMReal>(name, 
                                                          value, 
                                                          pVarLoc,
                                                          pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFVec2f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMVec2f>(name, 
                                                           value, 
                                                           pVarLoc,
                                                           pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFVec3f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMVec3f>(name, 
                                                           value, 
                                                           pVarLoc,
                                                           pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFVec4f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMVec4f>(name, 
                                                           value, 
                                                           pVarLoc,
                                                           pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8    *name, 
                                                const MFMatrix &value,
                                                      MFInt32  *pVarLoc,
                                                      MFInt32  *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMMatrix>(name, 
                                                            value, 
                                                            pVarLoc,
                                                            pProcVarLoc);
}

#if 0
bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFPnt2f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMPnt2f>(name, 
                                                           value, 
                                                           pVarLoc,
                                                           pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFPnt3f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addMVariable<ShaderVariableMPnt3f>(name, 
                                                           value, 
                                                           pVarLoc,
                                                           pProcVarLoc);
}
#endif


bool ShaderProgramVariables::updateUniformVariable(const Char8 *name,
                                                         bool   value)
{
    return _pVarAccess->updateSVariable<ShaderVariableBool>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name,       
                                                         Int32  value)
{
    return _pVarAccess->updateSVariable<ShaderVariableInt>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8  *name,
                                                         Real32  value)
{
    return _pVarAccess->updateSVariable<ShaderVariableReal>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Vec2f &value)
{
    return _pVarAccess->updateSVariable<ShaderVariableVec2f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Vec3f &value)
{
    return _pVarAccess->updateSVariable<ShaderVariableVec3f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Vec4f &value)
{
    return _pVarAccess->updateSVariable<ShaderVariableVec4f>(name, value);
}


bool ShaderProgramVariables::updateUniformVariable(const Char8  *name, 
                                                   const Matrix &value)
{
    return _pVarAccess->updateSVariable<ShaderVariableMatrix>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Pnt2f &value)
{
    return _pVarAccess->updateSVariable<ShaderVariablePnt2f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Pnt3f &value)
{
    return _pVarAccess->updateSVariable<ShaderVariablePnt3f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFInt32 &value)
{
    return _pVarAccess->updateMVariable<ShaderVariableMInt>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8    *name, 
                                                   const MFReal32 &value)
{
    return _pVarAccess->updateMVariable<ShaderVariableMReal>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFVec2f &value)
{
    return _pVarAccess->updateMVariable<ShaderVariableMVec2f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFVec3f &value)
{
    return _pVarAccess->updateMVariable<ShaderVariableMVec3f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFVec4f &value)
{
    return _pVarAccess->updateMVariable<ShaderVariableMVec4f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8    *name, 
                                                   const MFMatrix &value)
{
    return _pVarAccess->updateMVariable<ShaderVariableMMatrix>(name, value);
}




bool ShaderProgramVariables::getUniformVariable(const Char8    *name,  
                                                      bool     &value)
{
    return _pVarAccess->getSVariable<ShaderVariableBool>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,       
                                                      Int32    &value)
{
    return _pVarAccess->getSVariable<ShaderVariableInt>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Real32   &value)
{
    return _pVarAccess->getSVariable<ShaderVariableReal>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name, 
                                                      Vec2f    &value)
{
    return _pVarAccess->getSVariable<ShaderVariableVec2f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Vec3f    &value)
{
    return _pVarAccess->getSVariable<ShaderVariableVec3f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Vec4f    &value)
{
    return _pVarAccess->getSVariable<ShaderVariableVec4f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name, 
                                                      Matrix   &value)
{
    return _pVarAccess->getSVariable<ShaderVariableMatrix>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Pnt2f    &value)
{
    return _pVarAccess->getSVariable<ShaderVariablePnt2f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Pnt3f    &value)
{
    return _pVarAccess->getSVariable<ShaderVariablePnt3f>(name, value);
}


bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFInt32  &value)
{
    return _pVarAccess->getMVariable<ShaderVariableMInt>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFReal32 &value)
{
    return _pVarAccess->getMVariable<ShaderVariableMReal>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFVec2f  &value)
{
    return _pVarAccess->getMVariable<ShaderVariableMVec2f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFVec3f  &value)
{
    return _pVarAccess->getMVariable<ShaderVariableMVec3f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFVec4f  &value)
{
    return _pVarAccess->getMVariable<ShaderVariableMVec4f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFMatrix &value)
{
    return _pVarAccess->getMVariable<ShaderVariableMMatrix>(name, value);
}



bool ShaderProgramVariables::addOSGVariable(const Char8   *name,
                                                  MFInt32 *pProcVarLoc)
{
    return _pVarAccess->addVariableOSG(name, pProcVarLoc);
}


bool ShaderProgramVariables::addProceduralVariable(
    const Char8          *name,
          ProcVarFunctor  pFunc,
          UInt32          uiDependency,
          MFInt32        *pProcVarLoc)
{
    return _pVarAccess->addProceduralVariable(name, 
                                              pFunc, 
                                              uiDependency,
                                              pProcVarLoc);
}

bool ShaderProgramVariables::updateProceduralVariable(
    const Char8          *name,
          ProcVarFunctor  pFunc,
          UInt32          uiDependency)
{
    return _pVarAccess->updateProceduralVariable(name, pFunc, uiDependency);
}

#ifdef OSG_1_COMPAT
bool ShaderProgramVariables::addProceduralVariable(
    const Char8          *name,
          ParamFunctor    pFunc,
          MFInt32        *pProcVarLoc)
{
    return _pVarAccess->addProceduralVariable(name, 
                                              pFunc, 
                                              ShaderProcVariable::SHDAll,
                                              pProcVarLoc);
}

bool ShaderProgramVariables::addProceduralVariable(
    const Char8           *name,
          OSGParamFunctor  pFunc,
          MFInt32        *pProcVarLoc)
{
    return _pVarAccess->addProceduralVariable(name, 
                                              pFunc, 
                                              ShaderProcVariable::SHDAll,
                                              pProcVarLoc);
}
#endif

bool ShaderProgramVariables::subUniformVariable(const Char8   *name,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return _pVarAccess->subVariable(name, pVarLoc, pProcVarLoc);
}
                            
void ShaderProgramVariables::clearUniformVariables(void)
{
    this->clearVariables          ();
    this->clearProceduralVariables();
}

void ShaderProgramVariables::onCreateAspect(
    const ShaderProgramVariables *createAspect,
    const ShaderProgramVariables *source)
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _pVarAccess = new ShaderVariableAccess(*this);
}

void ShaderProgramVariables::onDestroyAspect(UInt32 uiContainerId,
                                             UInt32 uiAspect     )
{
    delete _pVarAccess;

    _pVarAccess = NULL;

    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

void ShaderProgramVariables::execSync(
          ShaderProgramVariables *pFrom,
          ConstFieldMaskArg       whichField,
          AspectOffsetStore      &oOffsets,
          ConstFieldMaskArg       syncMode  ,
    const UInt32                  uiSyncInfo   )
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != 
       ((VariablesFieldMask | ProceduralVariablesFieldMask) & whichField))
    {
        _pVarAccess->updateMap();
    }
}

OSG_END_NAMESPACE
