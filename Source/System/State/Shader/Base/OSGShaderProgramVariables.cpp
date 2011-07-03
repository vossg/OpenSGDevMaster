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

#include "OSGShaderVariables.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderProgramVariablesBase.cpp file.
// To modify it, please change the .fcd file 
// (OSGShaderProgramVariables.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class VariableType, class ValueType> inline
bool ShaderProgramVariables::addMapSVariable(const Char8     *name, 
                                             const ValueType &value,
                                                   MFInt32   *pVarLoc,
                                                   MFInt32   *pProcVarLoc)
{
    typedef          VariableType              *VarPtr;
    typedef typename VariableType::ObjUnrecPtr  VarUnrecPtr;

    if(name == NULL)
        return false;

//    updateMap();

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);
    
    if(it != _mVarMap.end())
    {
        if((*it).second.first != -1)
        {
            VarPtr p = 
                dynamic_cast<VarPtr>(this->getVariables((*it).second.first));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::addSVariable : Variable "
                          "'%s' has wrong type!\n", name));
                return returnValue;
            }
            
            p->setValue(value);
            
            returnValue = true;
        }
    }
    else
    {
        if(name[0] != '\0' && name[0] == 'O' &&
           name[1] != '\0' && name[1] == 'S' &&
           name[2] != '\0' && name[2] == 'G'   )
        {
            FDEBUG(("Add osg param '%s'\n", name));

            ShaderVariableOSGUnrecPtr p = ShaderVariableOSG::createDependent(
                this->getFieldFlags()->_bNamespaceMask);
            
            if(p != NULL)
            {
                p->setName (name );
                
                this->editMFProceduralVariables()->push_back(p);

                if(pProcVarLoc != NULL)
                    pProcVarLoc->push_back(-1);

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(-1,
                                this->getMFProceduralVariables()->size() - 1)));

                _uiMapsize = 
                    this->getMFVariables          ()->size() +
                    this->getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
        else
        {
            VarUnrecPtr p = VariableType::createDependent(
                this->getFieldFlags()->_bNamespaceMask);
            
            if(p != NULL)
            {
                p->setName (name );
                p->setValue(value);

                Int32 iIdx = this->getMFVariables()->findIndex(NULL);

                if(iIdx == -1)
                {
                    iIdx = this->getMFVariables()->size();

                    p->addParent(this,
                                 ShaderProgramVariables::VariablesFieldId,
                                 iIdx                                    );
                
                    this->editMFVariables      ()->push_back(p   );
                    this->editMFVariableChanged()->push_back(true);

                    if(pVarLoc != NULL)
                        pVarLoc->push_back(-1);
                }
                else
                {
                    p->addParent(this,
                                 ShaderProgramVariables::VariablesFieldId,
                                 iIdx                                    );
                
                    this->editMFVariables()->replace(iIdx, p);

                    this->editVariableChanged(iIdx) = true;

                    if(pVarLoc != NULL)
                        (*pVarLoc)[iIdx] = -1;
                }

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(iIdx, -1)));

                _uiMapsize = 
                    this->getMFVariables          ()->size() +
                    this->getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
    }

    OSG_ASSERT(this->getMFVariables      ()->size() == 
               this->getMFVariableChanged()->size());

    return returnValue;
}

template<class VariableType, class ValueType> inline
bool ShaderProgramVariables::updateMapSVariable(const Char8     *name, 
                                                const ValueType &value)
{
    typedef          VariableType              *VarPtr;
    typedef typename VariableType::ObjUnrecPtr  VarUnrecPtr;

    if(name == NULL)
        return false;

//    updateMap();

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);
    
    if(it != _mVarMap.end())
    {
        if((*it).second.first != -1)
        {
            VarPtr p = 
                dynamic_cast<VarPtr>(this->getVariables((*it).second.first));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::updateSVariable : Variable "
                          "'%s' has wrong type!\n", name));
                return false;
            }
            
            p->setValue(value);
            
            returnValue = true;
        }
    }
    else
    {
        FWARNING(("ShaderVariableAccess::updateSVariable : Variable "
                  "'%s' not found!\n", name));
    }

    return returnValue;
}



template<class VariableType, class ValueType> inline
bool ShaderProgramVariables::addMapMVariable(const char      *name, 
                                             const ValueType &value,
                                                   MFInt32   *pVarLoc,
                                                   MFInt32   *pProcVarLoc)
{
    typedef          VariableType              *VarPtr;
    typedef typename VariableType::ObjUnrecPtr  VarUnrecPtr;

    if(name == NULL)
        return false;

//    updateMap();

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);
    
    if(it != _mVarMap.end())
    {
        if((*it).second.first != -1)
        {
            VarPtr p = dynamic_cast<VarPtr>(
                this->getVariables((*it).second.first));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::addMVariable : "
                          "Variable '%s' has wrong type!\n", name));

                return returnValue;
            }

            *(p->editMFValue()) = value;
        }
    }
    else
    {
        if(name[0] != '\0' && name[0] == 'O' &&
           name[1] != '\0' && name[1] == 'S' &&
           name[2] != '\0' && name[2] == 'G'   )
        {
            FDEBUG(("Add osg param '%s'\n", name));

            ShaderVariableOSGUnrecPtr p = ShaderVariableOSG::createDependent(
                this->getFieldFlags()->_bNamespaceMask);
            
            if(p != NULL)
            {
                p->setName(name);
                
                this->editMFProceduralVariables()->push_back(p);

                if(pProcVarLoc != NULL)
                    pProcVarLoc->push_back(-1);

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(-1,
                                this->getMFProceduralVariables()->size() - 1)));

                _uiMapsize = 
                    this->getMFVariables          ()->size() +
                    this->getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
        else
        {
            VarUnrecPtr p = VariableType::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

            if(p != NULL)
            {
                p->setName(name );
                
                *(p->editMFValue()) = value;

                Int32 iIdx = this->getMFVariables()->findIndex(NULL);

                if(iIdx == -1)
                {
                    iIdx = this->getMFVariables()->size();

                    p->addParent(this,
                                 ShaderProgramVariables::VariablesFieldId,
                                 iIdx                                    );

                    this->editMFVariables      ()->push_back(p   );
                    this->editMFVariableChanged()->push_back(true);

                    if(pVarLoc != NULL)
                        pVarLoc->push_back(-1);
                }
                else
                {
                    p->addParent(this,
                                 ShaderProgramVariables::VariablesFieldId,
                                 iIdx                                    );
                
                    this->editMFVariables()->replace(iIdx, p);

                    this->editVariableChanged(iIdx) = true;

                    if(pVarLoc != NULL)
                        (*pVarLoc)[iIdx] = -1;
                }

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(iIdx, -1)));

                _uiMapsize = 
                    this->getMFVariables          ()->size() +
                    this->getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
    }

    OSG_ASSERT(this->getMFVariables      ()->size() == 
               this->getMFVariableChanged()->size());

    return returnValue;
}


template<class VariableType, class ValueType> inline
bool ShaderProgramVariables::updateMapMVariable(const char      *name, 
                                                const ValueType &value)
{
    typedef          VariableType              *VarPtr;
    typedef typename VariableType::ObjUnrecPtr  VarUnrecPtr;

    if(name == NULL)
        return false;

//    updateMap();

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);
    
    if(it != _mVarMap.end())
    {
        if((*it).second.first != -1)
        {
            VarPtr p = dynamic_cast<VarPtr>(
                this->getVariables((*it).second.first));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::updateMVariable : "
                          "Variable '%s' has wrong type!\n", name));

                return false;
            }

            *(p->editMFValue()) = value;

            returnValue = true;
        }
    }

    OSG_ASSERT(this->getMFVariables      ()->size() == 
               this->getMFVariableChanged()->size());

    return returnValue;
}

template<class VariableType, class ValueType> inline
bool ShaderProgramVariables::getMapSVariable(const Char8     *name, 
                                                   ValueType &value)
{
    typedef VariableType *VarPtr;

    if(name == NULL)
        return false;

//    updateMap();

    VariableIt it = _mVarMap.find(name);
    
    if(it != _mVarMap.end())
    {
        if((*it).second.first != -1)
        {
            VarPtr p = dynamic_cast<VarPtr>(
                this->getVariables((*it).second.first));
            
            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::getSVariable : Variable "
                          "'%s' has wrong type!\n", name));

                return false;
            }

            value = p->getValue();
        }
        else
        {
            return false;
        }
    }
    else
    {
        FINFO(("ShaderVariableAccess::getSVariable : Variable '%s' "
               "doesn't exist!\n", name));

        return false;
    }

    return true;
}

template<class VariableType, class ValueType> inline
bool ShaderProgramVariables::getMapMVariable(const Char8     *name, 
                                                   ValueType &value)
{
    typedef VariableType *VarPtr;

    if(name == NULL)
        return false;

//    updateMap();

    VariableIt it = _mVarMap.find(name);
    
    if(it != _mVarMap.end())
    {
        if((*it).second.first != -1)
        {
            VarPtr p = dynamic_cast<VarPtr>(
                this->getVariables((*it).second.first));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::getMVariable : Variable "
                          "'%s' has wrong type!\n", name));
                
                return false;
            }

            value = *(p->getMFValue());
        }
        else
        {
            return false;
        }
    }
    else
    {
        FINFO(("ShaderVariableAccess::getMVariable : Variable '%s' "
               "doesn't exist!\n", name));

        return false;
    }

    return true;
}

template<class FunctorT> inline
bool ShaderProgramVariables::addMapProceduralVariable(
    const Char8          *name, 
          FunctorT        pFunctor,
          UInt32          uiDependency,
          MFInt32        *pProcVarLoc)
{
    if(name == NULL)
        return false;

    FDEBUG(("Add procedural param '%s'\n", name));

    bool                          returnValue = false;
    VariableIt it          = _mVarMap.find(name);

    if(it != _mVarMap.end())
    {
        if((*it).second.second != -1)
        {
            ShaderVariableFunctor *p = 
                dynamic_cast<ShaderVariableFunctor *>(
                    this->getProceduralVariables((*it).second.second));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::addProceduralVariable : "
                          "Variable '%s' has wrong type!\n", name));
                return false;
            }

            p->setFunctor   (pFunctor    );
            p->setDependency(uiDependency);

            returnValue = true;
        }
    }
    else
    {
        ShaderVariableFunctorUnrecPtr p= ShaderVariableFunctor::createDependent(
                this->getFieldFlags()->_bNamespaceMask);
            
        if(p != NULL)
        {
            p->setName      (name        );
            p->setFunctor   (pFunctor    );
            p->setDependency(uiDependency);

            this->editMFProceduralVariables()->push_back(p);
            
            if(pProcVarLoc != NULL)
                pProcVarLoc->push_back(-1);
            
            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    name, 
                    IntPair(-1,
                            this->getMFProceduralVariables()->size() - 1)));
            
            _uiMapsize = 
                this->getMFVariables          ()->size() +
                this->getMFProceduralVariables()->size();
            
            returnValue = true;
        }
    }

    return returnValue;
}


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
     Inherited ( ),
    _mVarMap   ( ),
    _uiMapsize (0)
{
}

ShaderProgramVariables::ShaderProgramVariables(
    const ShaderProgramVariables &source) :

     Inherited (source),
    _mVarMap   (      ),
    _uiMapsize (     0)
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
    this->addMapVariable(value);
}

void ShaderProgramVariables::subVariable(UInt32 uiIndex)
{
    if(uiIndex < _mfVariables.size())
    {
        this->subMapVariable(_mfVariables[uiIndex]->getName().c_str(),
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

    this->updateMap();
}

const ShaderVariable *
    ShaderProgramVariables::getVariable(const Char8 *name) const
{
    return this->getMapVariable(name);
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
    this->addMapVariable(value);
}

void ShaderProgramVariables::subProceduralVariable(UInt32 uiIndex)
{
    if(uiIndex < _mfProceduralVariables.size())
    {
        this->subMapVariable(_mfProceduralVariables[uiIndex]->getName().c_str(),
                              NULL,
                              NULL);
    }
}

void ShaderProgramVariables::clearProceduralVariables(void)
{
    editMField(ProceduralVariablesFieldMask, _mfProceduralVariables);

    _mfProceduralVariables.clear();

    this->updateMap();
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
    return this->addMapSVariable<ShaderVariableBool>(name, 
                                                     value, 
                                                     pVarLoc,
                                                     pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name,       
                                                      Int32    value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariableInt>(name, 
                                                    value, 
                                                    pVarLoc,
                                                    pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name,
                                                      Real32   value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariableReal>(name, 
                                                     value, 
                                                     pVarLoc,
                                                     pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Vec2f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariableVec2f>(name, 
                                                      value, 
                                                      pVarLoc,
                                                      pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Vec3f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariableVec3f>(name, 
                                                      value, 
                                                      pVarLoc,
                                                      pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Vec4f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariableVec4f>(name, 
                                                      value, 
                                                      pVarLoc,
                                                      pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Matrix  &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariableMatrix>(name, 
                                                       value, 
                                                       pVarLoc,
                                                       pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Pnt2f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariablePnt2f>(name, 
                                                      value, 
                                                      pVarLoc,
                                                      pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const Pnt3f   &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapSVariable<ShaderVariablePnt3f>(name, 
                                                      value, 
                                                      pVarLoc,
                                                      pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFInt32 &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapMVariable<ShaderVariableMInt>(name, 
                                                     value, 
                                                     pVarLoc,
                                                     pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8    *name, 
                                                const MFReal32 &value,
                                                      MFInt32  *pVarLoc,
                                                      MFInt32  *pProcVarLoc)
{
    return this->addMapMVariable<ShaderVariableMReal>(name, 
                                                      value, 
                                                      pVarLoc,
                                                      pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFVec2f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapMVariable<ShaderVariableMVec2f>(name, 
                                                       value, 
                                                       pVarLoc,
                                                       pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFVec3f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapMVariable<ShaderVariableMVec3f>(name, 
                                                       value, 
                                                       pVarLoc,
                                                       pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8   *name, 
                                                const MFVec4f &value,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->addMapMVariable<ShaderVariableMVec4f>(name, 
                                                       value, 
                                                       pVarLoc,
                                                       pProcVarLoc);
}

bool ShaderProgramVariables::addUniformVariable(const Char8    *name, 
                                                const MFMatrix &value,
                                                      MFInt32  *pVarLoc,
                                                      MFInt32  *pProcVarLoc)
{
    return this->addMapMVariable<ShaderVariableMMatrix>(name, 
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
    return this->updateMapSVariable<ShaderVariableBool>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name,       
                                                         Int32  value)
{
    return this->updateMapSVariable<ShaderVariableInt>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8  *name,
                                                         Real32  value)
{
    return this->updateMapSVariable<ShaderVariableReal>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Vec2f &value)
{
    return this->updateMapSVariable<ShaderVariableVec2f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Vec3f &value)
{
    return this->updateMapSVariable<ShaderVariableVec3f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Vec4f &value)
{
    return this->updateMapSVariable<ShaderVariableVec4f>(name, value);
}


bool ShaderProgramVariables::updateUniformVariable(const Char8  *name, 
                                                   const Matrix &value)
{
    return this->updateMapSVariable<ShaderVariableMatrix>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Pnt2f &value)
{
    return this->updateMapSVariable<ShaderVariablePnt2f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8 *name, 
                                                   const Pnt3f &value)
{
    return this->updateMapSVariable<ShaderVariablePnt3f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFInt32 &value)
{
    return this->updateMapMVariable<ShaderVariableMInt>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8    *name, 
                                                   const MFReal32 &value)
{
    return this->updateMapMVariable<ShaderVariableMReal>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFVec2f &value)
{
    return this->updateMapMVariable<ShaderVariableMVec2f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFVec3f &value)
{
    return this->updateMapMVariable<ShaderVariableMVec3f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8   *name, 
                                                   const MFVec4f &value)
{
    return this->updateMapMVariable<ShaderVariableMVec4f>(name, value);
}

bool ShaderProgramVariables::updateUniformVariable(const Char8    *name, 
                                                   const MFMatrix &value)
{
    return this->updateMapMVariable<ShaderVariableMMatrix>(name, value);
}




bool ShaderProgramVariables::getUniformVariable(const Char8    *name,  
                                                      bool     &value)
{
    return this->getMapSVariable<ShaderVariableBool>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,       
                                                      Int32    &value)
{
    return this->getMapSVariable<ShaderVariableInt>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Real32   &value)
{
    return this->getMapSVariable<ShaderVariableReal>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name, 
                                                      Vec2f    &value)
{
    return this->getMapSVariable<ShaderVariableVec2f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Vec3f    &value)
{
    return this->getMapSVariable<ShaderVariableVec3f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Vec4f    &value)
{
    return this->getMapSVariable<ShaderVariableVec4f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name, 
                                                      Matrix   &value)
{
    return this->getMapSVariable<ShaderVariableMatrix>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Pnt2f    &value)
{
    return this->getMapSVariable<ShaderVariablePnt2f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      Pnt3f    &value)
{
    return this->getMapSVariable<ShaderVariablePnt3f>(name, value);
}


bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFInt32  &value)
{
    return this->getMapMVariable<ShaderVariableMInt>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFReal32 &value)
{
    return this->getMapMVariable<ShaderVariableMReal>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFVec2f  &value)
{
    return this->getMapMVariable<ShaderVariableMVec2f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFVec3f  &value)
{
    return this->getMapMVariable<ShaderVariableMVec3f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFVec4f  &value)
{
    return this->getMapMVariable<ShaderVariableMVec4f>(name, value);
}

bool ShaderProgramVariables::getUniformVariable(const Char8    *name,
                                                      MFMatrix &value)
{
    return this->getMapMVariable<ShaderVariableMMatrix>(name, value);
}



bool ShaderProgramVariables::addOSGVariable(const Char8   *name,
                                                  MFInt32 *pProcVarLoc)
{
    return this->addMapVariableOSG(name, pProcVarLoc);
}


bool ShaderProgramVariables::addProceduralVariable(
    const Char8          *name,
          ProcVarFunctor  pFunc,
          UInt32          uiDependency,
          MFInt32        *pProcVarLoc)
{
    return this->addMapProceduralVariable(name, 
                                          pFunc, 
                                          uiDependency,
                                          pProcVarLoc);
}

bool ShaderProgramVariables::addNodeProceduralVariable(
    const Char8              *name,
          ProcVarNodeFunctor  pFunc,
          UInt32              uiDependency,
          MFInt32            *pProcVarLoc)
{
    return this->addMapProceduralVariable(name, 
                                          pFunc, 
                                          uiDependency,
                                          pProcVarLoc);
}

bool ShaderProgramVariables::updateProceduralVariable(
    const Char8          *name,
          ProcVarFunctor  pFunc,
          UInt32          uiDependency)
{
    return this->updateMapProceduralVariable(name, pFunc, uiDependency);
}

bool ShaderProgramVariables::updateNodeProceduralVariable(
    const Char8              *name,
          ProcVarNodeFunctor  pFunc,
          UInt32              uiDependency)
{
    return this->updateMapProceduralVariable(name, pFunc, uiDependency);
}

#ifdef OSG_1_COMPAT
bool ShaderProgramVariables::addProceduralVariable(
    const Char8          *name,
          ParamFunctor    pFunc,
          MFInt32        *pProcVarLoc)
{
    return this->addMapProceduralVariable(name, 
                                          pFunc, 
                                          ShaderProcVariable::SHDAll,
                                          pProcVarLoc);
}

bool ShaderProgramVariables::addProceduralVariable(
    const Char8           *name,
          OSGParamFunctor  pFunc,
          MFInt32        *pProcVarLoc)
{
    return this->addMapProceduralVariable(name, 
                                          pFunc, 
                                          ShaderProcVariable::SHDAll,
                                          pProcVarLoc);
}
#endif

bool ShaderProgramVariables::subUniformVariable(const Char8   *name,
                                                      MFInt32 *pVarLoc,
                                                      MFInt32 *pProcVarLoc)
{
    return this->subMapVariable(name, pVarLoc, pProcVarLoc);
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
}

void ShaderProgramVariables::onDestroyAspect(UInt32 uiContainerId,
                                             UInt32 uiAspect     )
{
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
        this->updateMap();
    }
}









bool ShaderProgramVariables::addMapVariableOSG(const Char8   *name,
                                                     MFInt32 *pProcVarLoc)
{
    if(name == NULL)
        return false;

    FDEBUG(("Add osg param '%s'\n", name));

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);

    if(it == _mVarMap.end())
    {
        ShaderVariableOSGUnrecPtr p = ShaderVariableOSG::create();
            
        if(p != NULL)
        {
            p->setName(name);
            
            if(p->getOsgVarType() != ShaderVariableOSG::OSGUnknown)
            {
                this->editMFProceduralVariables()->push_back(p);
                
                if(pProcVarLoc != NULL)
                    pProcVarLoc->push_back(-1);
                
                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(
                            -1,
                            this->getMFProceduralVariables()->size() - 1
                               )));
                
                _uiMapsize = 
                    this->getMFVariables          ()->size() +
                    this->getMFProceduralVariables()->size();
                
                returnValue = true;
            }
        }
    }

    return returnValue;
}


bool ShaderProgramVariables::updateMapProceduralVariable(
    const Char8          *name, 
          ProcVarFunctor  pFunctor,                                        
          UInt32          uiDependency)
{
    if(name == NULL)
        return false;

    FDEBUG(("Update procedural param '%s'\n", name));

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);

    if(it != _mVarMap.end())
    {
        if((*it).second.second != -1)
        {
            ShaderVariableFunctor *p = 
                dynamic_cast<ShaderVariableFunctor *>(
                    this->getProceduralVariables((*it).second.second));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::setVariable : Variable "
                          "'%s' has wrong type!\n", name));
                return false;
            }

            p->setFunctor   (pFunctor    );
            p->setDependency(uiDependency);

            returnValue = true;
        }
    }

    return returnValue;
}


bool ShaderProgramVariables::updateMapProceduralVariable(
    const Char8              *name, 
          ProcVarNodeFunctor  pFunctor,                                        
          UInt32              uiDependency)
{
    if(name == NULL)
        return false;

    FDEBUG(("Update procedural param '%s'\n", name));

    bool       returnValue = false;
    VariableIt it          = _mVarMap.find(name);

    if(it != _mVarMap.end())
    {
        if((*it).second.second != -1)
        {
            ShaderVariableFunctor *p = 
                dynamic_cast<ShaderVariableFunctor *>(
                    this->getProceduralVariables((*it).second.second));

            if(p == NULL)
            {
                FWARNING(("ShaderVariableAccess::setVariable : Variable "
                          "'%s' has wrong type!\n", name));
                return false;
            }

            p->setFunctor   (pFunctor    );
            p->setDependency(uiDependency);

            returnValue = true;
        }
    }

    return returnValue;
}

void ShaderProgramVariables::addMapVariable(ShaderVariable *pVar)
{
    if(pVar == NULL)
        return;

    VariableIt it = _mVarMap.find(pVar->getName());
    
    if(it != _mVarMap.end())
    {
        FWARNING(("ShaderVariables::addVariable : Variable "
                  "'%s' already there, ignoring!\n", 
                  pVar->getName().c_str()));

        return ;
    }
    else
    {
        const std::string &name = pVar->getName();

        if(pVar->isProcedural() == true)
        {
            FDEBUG(("Add procedural param variable '%s'\n", name.c_str()));
 
            ShaderProcVariable *pProcVar = 
                static_cast<ShaderProcVariable *>(pVar);

            this->editMFProceduralVariables()->push_back(pProcVar);

            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    pVar->getName(), 
                    IntPair(
                        -1,
                        this->getMFProceduralVariables()->size() - 1)));

            _uiMapsize = 
                this->getMFVariables          ()->size() +
                this->getMFProceduralVariables()->size();
        }
        else
        {
            ShaderValueVariable *pValVar = 
                static_cast<ShaderValueVariable *>(pVar);

            pValVar->addParent(this,
                               ShaderProgramVariables::VariablesFieldId,
                               this->getMFVariables()->size());

            this->editMFVariables      ()->push_back(pValVar);
            this->editMFVariableChanged()->push_back(true   );
        
            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    name,
                    IntPair(this->getMFVariables()->size() - 1,
                            -1)));
        
            _uiMapsize =
                this->getMFVariables          ()->size() +
                this->getMFProceduralVariables()->size();
        }
    }

    OSG_ASSERT(this->getMFVariables      ()->size() == 
               this->getMFVariableChanged()->size());
}

bool ShaderProgramVariables::subMapVariable(const Char8   *name,
                                             MFInt32 *pVarLoc,
                                             MFInt32 *pProcVarLoc)
{
    if(name == NULL)
        return false;

    VariableIt it = _mVarMap.find(name);
    
    if(it == _mVarMap.end())
        return false;

    if((*it).second.first != -1)
    {
        ShaderValueVariable *pVar = 
            static_cast<ShaderValueVariable *>(
                this->getVariables((*it).second.first));

        pVar->subParent(this);

#if 0
        this->editMFVariables      ()->erase((*it).second.first);
        this->editMFVariableChanged()->erase((*it).second.first);

        if(pVarLoc != NULL)
            pVarLoc->erase((*it).second.first);
#endif

        this->editMFVariables()->replace((*it).second.first, NULL);

        this->editVariableChanged((*it).second.first) = false;

        if(pVarLoc != NULL)
            (*pVarLoc)[(*it).second.first] = -1;

        _mVarMap.erase(it);

        --_uiMapsize;
    }
    else if((*it).second.second != -1)
    {
        this->editMFProceduralVariables()->erase((*it).second.second);

        if(pProcVarLoc != NULL)
            pProcVarLoc->erase((*it).second.second);

        _mVarMap.erase(it);

        --_uiMapsize;
    }

    updateMap();

    return true;
}

const ShaderVariable *
    ShaderProgramVariables::getMapVariable(const Char8 *name) const
{
    if(name == NULL)
        return NULL;

    VariableConstIt it = _mVarMap.find(name);
    
    if(it == _mVarMap.end())
        return NULL;

    if((*it).second.first != -1)
    {
        return this->getVariables((*it).second.first);
    }

    return NULL;
}

void ShaderProgramVariables::updateMap(void)
{
    if(_uiMapsize == this->getMFVariables()->size())
        return;
    
    UInt32 size = this->getMFVariables()->size();
    
    _uiMapsize = 0;

    _mVarMap.clear();

    for(UInt32 i = 0; i < size; ++i)
    {
        if(this->getVariables(i) != NULL)
        {
            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    this->getVariables(i)->getName(), 
                    IntPair(i, -1)));

            ++_uiMapsize;
        }
    }

    size = this->getMFProceduralVariables()->size();

    for(UInt32 i = 0; i < size; ++i)
    {
        _mVarMap.insert(
            std::pair<std::string, IntPair>(
                this->getProceduralVariables(i)->getName(), 
                IntPair(-1, i)));
    }

    _uiMapsize += size;

    OSG_ASSERT(this->getMFVariables      ()->size() == 
               this->getMFVariableChanged()->size());
}



OSG_END_NAMESPACE
