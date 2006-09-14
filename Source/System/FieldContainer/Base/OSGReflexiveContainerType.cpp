/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGReflexiveContainerType.h"
#include "OSGLog.h"
#include "OSGFieldDescriptionBase.h"

#include <algorithm>

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ReflexiveContainerType::ReflexiveContainerType(bool foo,
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
    const UInt32                uiNameSpace,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable) :

      Inherited    (        szName, 
                      szParentName, 
                       uiNameSpace),

    _uiGroupId     (             0),
    _bDescsAddable ( bDescsAddable),
    _szGroupName   (   szGroupName),

    _vInitialDescs (              ),

	_mDescMap      (              ),
    _vDescVec      (              ),

    _descInsertFunc(descInsertFunc)
{
}

ReflexiveContainerType::ReflexiveContainerType(
    const ReflexiveContainerType &source) :
      Inherited    (source                ),

    _uiGroupId     (source._uiGroupId     ),
    _bDescsAddable (source._bDescsAddable ),
    _szGroupName   (source._szGroupName   ),

    _vInitialDescs (                      ),

	_mDescMap      (                      ),
    _vDescVec      (                      ),

    _descInsertFunc(source._descInsertFunc)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */


ReflexiveContainerType::~ReflexiveContainerType(void)
{
    terminate();
}


bool ReflexiveContainerType::initialize(void)
{
    if(_bInitialized == true)
        return true;

    _bInitialized = Inherited::initialize();

    if(_bInitialized == false)
        return false;

    if(_descInsertFunc != NULL)
    {
        _descInsertFunc(this);
    }

    _bInitialized = initParentFields();
    
    if(_bInitialized == false)
        return false;

    _bInitialized = initFields      ();

    if(_bInitialized == false)
        return false;


    FDEBUG(("init ContainerType %s (%d)\n",
            getCName(), 
            int(_bInitialized)));

    if(_vDescVec.size() > sizeof(BitVector) * 8)
    {
        FWARNING(("FCType %s has %d (>%d) fields!\n", 
                   getCName(),
                  _vDescVec.size(), 
                   sizeof(BitVector) * 8));
    }

    return true;
}


void ReflexiveContainerType::terminate(void)
{
    _bInitialized = false;

    for(UInt32 i = 0; i < _vInitialDescs.size(); ++i)
    {
        delete _vInitialDescs[i];
    }

    _vInitialDescs.clear();
}

bool ReflexiveContainerType::initFields(void)
{
    bool      returnValue = true;
    UInt32    i;
	DescMapIt descIt;

    for(i = 0; i < _vInitialDescs.size(); i++) 
    {
        if(_vInitialDescs[i]->isValid()) 
        {
            descIt = 
                _mDescMap.find(IDStringLink(_vInitialDescs[i]->getCName()));

            if(descIt == _mDescMap.end())
            {
                _mDescMap[IDStringLink(_vInitialDescs[i]->getCName())] = 
                    _vInitialDescs[i];

                _vDescVec.push_back(_vInitialDescs[i]); 
            }
            else
            {
                SWARNING << "ERROR: Double field description " 
                         << "in " << _szName.str() << "from " 
                         << _vInitialDescs[i]->getCName() 
                         << _vInitialDescs[i]->getTypeId() << std::endl;

                returnValue = false;
            }
        }
        else
        {
            SWARNING << "ERROR: Invalid field description " 
                     << "in " << _szName.str() << "from " 
                     << _vInitialDescs[i]->getTypeId() << std::endl;
            
            returnValue = false;
        }

    }

    std::sort(_vDescVec.begin(), _vDescVec.end(), FieldDescriptionBasePLT());

    return returnValue;
}

bool ReflexiveContainerType::initParentFields(void)
{
    bool      returnValue = true;
	DescMapIt dPIt;

    ReflexiveContainerType *pReflexParent = 
        dynamic_cast<ReflexiveContainerType *>(_pParentType);

    if(pReflexParent != NULL) 
    {
        if(pReflexParent->isInitialized() == true)
        {
            for(  dPIt  = pReflexParent->_mDescMap.begin();
                  dPIt != pReflexParent->_mDescMap.end  (); 
                ++dPIt) 
            {
                if(_mDescMap.find((*dPIt).first) == _mDescMap.end())
                {
                    _mDescMap[(*dPIt).first] = (*dPIt).second;
                }
                else
                {
                    SWARNING << "ERROR: Can't add field "
                             << "description a second time: " 
                             << (*dPIt).first.str() << std::endl; 
                }
            } 				
            
            _vDescVec.insert(_vDescVec.end(),
                              pReflexParent->_vDescVec.begin(),
                              pReflexParent->_vDescVec.end  ());
            
        }
        else 
        {
            SWARNING << "ERROR: parent not initialized "
                     << "name " << _szParentName.str() 
                     << std::endl;
            
            returnValue = false;
        }
    }

    return returnValue;
}

void ReflexiveContainerType::addInitialDesc(FieldDescriptionBase *pDesc)
{
    if(pDesc != NULL)
    {
        _vInitialDescs.push_back(pDesc);
    }
}

UInt32 ReflexiveContainerType::addDescription(const FieldDescriptionBase &desc)
{
    UInt32         returnValue = 0;
    DescMapConstIt descIt;
    DescVecIt      descVIt;

    FieldDescriptionBase *pDesc;
    FieldDescriptionBase *pNullDesc = NULL;

    if(_bDescsAddable == false)
        return returnValue;

    descIt = _mDescMap.find(IDStringLink(desc.getCName()));

    if(desc.isValid())
    {
        if(descIt == _mDescMap.end())
        {
            pDesc = desc.clone();

            _mDescMap[IDStringLink(pDesc->getCName())] = pDesc;

            descVIt = std::find(_vDescVec.begin(),
                                _vDescVec.end(),
                                 pNullDesc);

            if(descVIt == _vDescVec.end())
            {
                _vDescVec.push_back(pDesc);

                returnValue = _vDescVec.size();
            }
            else
            {
                (*descVIt) = pDesc;

                returnValue  = descVIt - _vDescVec.begin();
                returnValue += 1;
            }
        }
        else
        {
            SWARNING << "ERROR: Double field description "
                        << "in " << _szName.str() << " from "
                        << desc.getCName() << " (id:"
                        << desc.getTypeId() << ")" << std::endl;
        }
    }
    else
    {
        SWARNING << "ERROR: Invalid field description "
                    << "in " << _szName.str() << " from "
                    << desc.getTypeId() << std::endl;
    }

    return returnValue;
}

bool ReflexiveContainerType::subDescription(UInt32 uiFieldId)
{
    FieldDescriptionBase *pDesc = getFieldDesc(uiFieldId);
    DescMapIt             descMIt;
    DescVecIt             descVIt;
    bool                  returnValue = true;

    if(pDesc == NULL || _bDescsAddable == false)
        return false;

    descMIt = _mDescMap.find(IDStringLink(pDesc->getCName()));

    if(descMIt != _mDescMap.end())
    {
        _mDescMap.erase(descMIt);
    }
    else
    {
        returnValue = false;
    }

    descVIt = std::find(_vDescVec.begin(), _vDescVec.end(), pDesc);

    if(descVIt != _vDescVec.end())
    {
        (*descVIt) = NULL;

        returnValue &= true;
    }
    else
    {
        returnValue = false;
    }

    delete pDesc;

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGREFLEXIVECONTAINERTYPE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGREFLEXIVECONTAINERTYPE_INLINE_CVSID;
}

