/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

template<class VariableType, class ValueType> inline
bool ShaderVariableAccess::addSVariable(const Char8     *name, 
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
                dynamic_cast<VarPtr>(
                    _oVariables.getVariables((*it).second.first));

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
                _oVariables.getFieldFlags()->_bNamespaceMask);
            
            if(p != NULL)
            {
                p->setName (name );
                
                _oVariables.editMFProceduralVariables()->push_back(p);

                if(pProcVarLoc != NULL)
                    pProcVarLoc->push_back(-1);

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(
                            -1,
                            _oVariables.getMFProceduralVariables()->size() - 1
                            )));

                _uiMapsize = 
                    _oVariables.getMFVariables          ()->size() +
                    _oVariables.getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
        else
        {
            VarUnrecPtr p = VariableType::createDependent(
                _oVariables.getFieldFlags()->_bNamespaceMask);
            
            if(p != NULL)
            {
                p->setName (name );
                p->setValue(value);

                Int32 iIdx = _oVariables.getMFVariables()->findIndex(NULL);

                if(iIdx == -1)
                {
                    iIdx = _oVariables.getMFVariables()->size();

                    p->addParent(&_oVariables,
                                   ShaderProgramVariables::VariablesFieldId,
                                   iIdx                                    );
                
                    _oVariables.editMFVariables      ()->push_back(p   );
                    _oVariables.editMFVariableChanged()->push_back(true);

                    if(pVarLoc != NULL)
                        pVarLoc->push_back(-1);
                }
                else
                {
                    p->addParent(&_oVariables,
                                   ShaderProgramVariables::VariablesFieldId,
                                   iIdx                                    );
                
                    _oVariables.editMFVariables()->replace(iIdx, p);

                    _oVariables.editVariableChanged(iIdx) = true;

                    if(pVarLoc != NULL)
                        (*pVarLoc)[iIdx] = -1;
                }

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(iIdx, -1)));

                _uiMapsize = 
                    _oVariables.getMFVariables          ()->size() +
                    _oVariables.getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
    }

    OSG_ASSERT(_oVariables.getMFVariables      ()->size() == 
               _oVariables.getMFVariableChanged()->size());

    return returnValue;
}

template<class VariableType, class ValueType> inline
bool ShaderVariableAccess::updateSVariable(const Char8     *name, 
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
                dynamic_cast<VarPtr>(
                    _oVariables.getVariables((*it).second.first));

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
bool ShaderVariableAccess::addMVariable(const char      *name, 
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
                _oVariables.getVariables((*it).second.first));

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
                _oVariables.getFieldFlags()->_bNamespaceMask);
            
            if(p != NULL)
            {
                p->setName(name);
                
                _oVariables.editMFProceduralVariables()->push_back(p);

                if(pProcVarLoc != NULL)
                    pProcVarLoc->push_back(-1);

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(
                            -1,
                            _oVariables.getMFProceduralVariables()->size() - 1
                            )));

                _uiMapsize = 
                    _oVariables.getMFVariables          ()->size() +
                    _oVariables.getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
        else
        {
            VarUnrecPtr p = VariableType::createDependent(
                _oVariables.getFieldFlags()->_bNamespaceMask);

            if(p != NULL)
            {
                p->setName(name );
                
                *(p->editMFValue()) = value;

                Int32 iIdx = _oVariables.getMFVariables()->findIndex(NULL);

                if(iIdx == -1)
                {
                    iIdx = _oVariables.getMFVariables()->size();

                    p->addParent(&_oVariables,
                                   ShaderProgramVariables::VariablesFieldId,
                                   iIdx                                    );

                    _oVariables.editMFVariables      ()->push_back(p   );
                    _oVariables.editMFVariableChanged()->push_back(true);

                    if(pVarLoc != NULL)
                        pVarLoc->push_back(-1);
                }
                else
                {
                    p->addParent(&_oVariables,
                                   ShaderProgramVariables::VariablesFieldId,
                                   iIdx                                    );
                
                    _oVariables.editMFVariables()->replace(iIdx, p);

                    _oVariables.editVariableChanged(iIdx) = true;

                    if(pVarLoc != NULL)
                        (*pVarLoc)[iIdx] = -1;
                }

                _mVarMap.insert(
                    std::pair<std::string, IntPair>(
                        name, 
                        IntPair(iIdx, -1)));

                _uiMapsize = 
                    _oVariables.getMFVariables          ()->size() +
                    _oVariables.getMFProceduralVariables()->size();

                returnValue = true;
            }
        }
    }

    OSG_ASSERT(_oVariables.getMFVariables      ()->size() == 
               _oVariables.getMFVariableChanged()->size());

    return returnValue;
}


template<class VariableType, class ValueType> inline
bool ShaderVariableAccess::updateMVariable(const char      *name, 
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
                _oVariables.getVariables((*it).second.first));

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

    OSG_ASSERT(_oVariables.getMFVariables      ()->size() == 
               _oVariables.getMFVariableChanged()->size());

    return returnValue;
}

template<class VariableType, class ValueType> inline
bool ShaderVariableAccess::getSVariable(const Char8 *name, ValueType &value)
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
                _oVariables.getVariables((*it).second.first));
            
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
bool ShaderVariableAccess::getMVariable(const Char8 *name, ValueType &value)
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
                _oVariables.getVariables((*it).second.first));

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
bool ShaderVariableAccess::addProceduralVariable(
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
                    _oVariables.getProceduralVariables((*it).second.second));

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
                _oVariables.getFieldFlags()->_bNamespaceMask);
            
        if(p != NULL)
        {
            p->setName      (name        );
            p->setFunctor   (pFunctor    );
            p->setDependency(uiDependency);

            _oVariables.editMFProceduralVariables()->push_back(p);
            
            if(pProcVarLoc != NULL)
                pProcVarLoc->push_back(-1);
            
            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    name, 
                    IntPair(
                        -1,
                        _oVariables.getMFProceduralVariables()->size() - 1)));
            
            _uiMapsize = 
                _oVariables.getMFVariables          ()->size() +
                _oVariables.getMFProceduralVariables()->size();
            
            returnValue = true;
        }
    }

    return returnValue;
}

OSG_END_NAMESPACE
