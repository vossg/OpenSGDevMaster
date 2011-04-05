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

#include "OSGShaderVariableAccess.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderVariableAccess

*/

/*----------------------- constructors & destructors ----------------------*/

ShaderVariableAccess::ShaderVariableAccess(ShaderProgramVariables &oVariables):

    _oVariables(oVariables),
    _mVarMap   (           ),
    _uiMapsize (          0)
{
}

ShaderVariableAccess::~ShaderVariableAccess(void)
{
}

void ShaderVariableAccess::operator =(const ShaderVariableAccess &/*source*/)
{
}

bool ShaderVariableAccess::addVariableOSG(const Char8   *name,
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
    }

    return returnValue;
}


bool ShaderVariableAccess::updateProceduralVariable(
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
                    _oVariables.getProceduralVariables((*it).second.second));

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


bool ShaderVariableAccess::updateProceduralVariable(
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
                    _oVariables.getProceduralVariables((*it).second.second));

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

void ShaderVariableAccess::addVariable(ShaderVariable *pVar)
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

            _oVariables.editMFProceduralVariables()->push_back(pProcVar);

            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    pVar->getName(), 
                    IntPair(
                        -1,
                        _oVariables.getMFProceduralVariables()->size() - 1)));

            _uiMapsize = 
                _oVariables.getMFVariables          ()->size() +
                _oVariables.getMFProceduralVariables()->size();
        }
        else
        {
            ShaderValueVariable *pValVar = 
                static_cast<ShaderValueVariable *>(pVar);

            pValVar->addParent(&_oVariables,
                                 ShaderProgramVariables::VariablesFieldId,
                                _oVariables.getMFVariables()->size());

            _oVariables.editMFVariables      ()->push_back(pValVar);
            _oVariables.editMFVariableChanged()->push_back(true   );
        
            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    name,
                    IntPair(_oVariables.getMFVariables()->size() - 1,
                            -1)));
        
            _uiMapsize =
                _oVariables.getMFVariables          ()->size() +
                _oVariables.getMFProceduralVariables()->size();
        }
    }

    OSG_ASSERT(_oVariables.getMFVariables      ()->size() == 
               _oVariables.getMFVariableChanged()->size());
}

bool ShaderVariableAccess::subVariable(const Char8   *name,
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
                _oVariables.getVariables((*it).second.first));

        pVar->subParent(&_oVariables);

#if 0
        _oVariables.editMFVariables      ()->erase((*it).second.first);
        _oVariables.editMFVariableChanged()->erase((*it).second.first);

        if(pVarLoc != NULL)
            pVarLoc->erase((*it).second.first);
#endif

        _oVariables.editMFVariables()->replace((*it).second.first, NULL);

        _oVariables.editVariableChanged((*it).second.first) = false;

        if(pVarLoc != NULL)
            (*pVarLoc)[(*it).second.first] = -1;

        _mVarMap.erase(it);

        --_uiMapsize;
    }
    else if((*it).second.second != -1)
    {
        _oVariables.editMFProceduralVariables()->erase((*it).second.second);

        if(pProcVarLoc != NULL)
            pProcVarLoc->erase((*it).second.second);

        _mVarMap.erase(it);

        --_uiMapsize;
    }

    updateMap();

    return true;
}

const ShaderVariable *
    ShaderVariableAccess::getVariable(const Char8 *name) const
{
    if(name == NULL)
        return NULL;

    VariableConstIt it = _mVarMap.find(name);
    
    if(it == _mVarMap.end())
        return NULL;

    if((*it).second.first != -1)
    {
        return _oVariables.getVariables((*it).second.first);
    }

    return NULL;
}

void ShaderVariableAccess::updateMap(void)
{
    if(_uiMapsize == _oVariables.getMFVariables()->size())
        return;
    
    UInt32 size = _oVariables.getMFVariables()->size();
    
    _uiMapsize = 0;

    _mVarMap.clear();

    for(UInt32 i = 0; i < size; ++i)
    {
        if(_oVariables.getVariables(i) != NULL)
        {
            _mVarMap.insert(
                std::pair<std::string, IntPair>(
                    _oVariables.getVariables(i)->getName(), 
                    IntPair(i, -1)));

            ++_uiMapsize;
        }
    }

    size = _oVariables.getMFProceduralVariables()->size();

    for(UInt32 i = 0; i < size; ++i)
    {
        _mVarMap.insert(
            std::pair<std::string, IntPair>(
                _oVariables.getProceduralVariables(i)->getName(), 
                IntPair(-1, i)));
    }

    _uiMapsize += size;

    OSG_ASSERT(_oVariables.getMFVariables      ()->size() == 
               _oVariables.getMFVariableChanged()->size());
}
