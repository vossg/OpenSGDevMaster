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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGReflexiveContainerType.h"
#include "OSGLog.h"
#include "OSGFieldDescriptionBase.h"

#include <algorithm>

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */
ReflexiveContainerType::ReflexiveContainerType(
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
    const UInt32                uiNameSpace,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable,
          BitVector             bvUnmarkedOnCreate) :

     Inherited        (             szName,
                              szParentName,
                               uiNameSpace),

    _uiGroupId        (                  0),
    _bDescsAddable    (      bDescsAddable),
    _szGroupName      (                   ),

    _vInitialDescs    (                   ),

    _mDescMap         (                   ),
    _vDescVec         (                   ),

   _descInsertFunc    (descInsertFunc     ),
   _bvUnmarkedOnCreate(~bvUnmarkedOnCreate)      
{
    if(szGroupName != NULL)
        _szGroupName.assign(szGroupName);

}

ReflexiveContainerType::ReflexiveContainerType(
    const ReflexiveContainerType &source) :
     Inherited         (source                    ),

    _uiGroupId         (source._uiGroupId         ),
    _bDescsAddable     (source._bDescsAddable     ),
    _szGroupName       (source._szGroupName       ),

    _vInitialDescs     (                          ),

    _mDescMap          (                          ),
    _vDescVec          (                          ),

    _descInsertFunc    (source._descInsertFunc    ),
    _bvUnmarkedOnCreate(source._bvUnmarkedOnCreate)      
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
        _descInsertFunc(*this);
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
        FWARNING(("FCType %s has %" PRISize " (>%" PRISize ") fields!\n",
                   getCName(),
                  _vDescVec.size(),
                   sizeof(BitVector) * 8));
    }

    return true;
}


void ReflexiveContainerType::terminate(void)
{
    _bInitialized = false;

    for(UInt32 i = 0; i < _vDescVec.size(); ++i)
    {
        delete _vDescVec[i];
    }

    for(UInt32 i = 0; i < _vInitialDescs.size(); ++i)
    {
        delete _vInitialDescs[i];
    }

    _vDescVec     .clear();
    _vInitialDescs.clear();
}

bool ReflexiveContainerType::initFields(void)
{
    bool                  returnValue = true;
    UInt32                i;
    DescMapIt             descIt;
    FieldDescriptionBase *pDesc;

    for(i = 0; i < _vInitialDescs.size(); i++)
    {
        if(_vInitialDescs[i]->isValid())
        {
            descIt =
                _mDescMap.find(_vInitialDescs[i]->getName());

            if(descIt == _mDescMap.end())
            {
                pDesc = _vInitialDescs[i]->clone();

                _mDescMap[_vInitialDescs[i]->getName()] =
                    pDesc;

                _vDescVec.push_back(pDesc);
            }
            else
            {
                SWARNING << "ERROR: Double field description "
                         << "in " << _szName.c_str() << "from "
                         << _vInitialDescs[i]->getCName()
                         << _vInitialDescs[i]->getTypeId() << std::endl;

                returnValue = false;
            }
        }
        else
        {
            SWARNING << "ERROR: Invalid field description "
                     << "in " << _szName.c_str() << "from "
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
#if 0
    DescMapIt dPIt;
#endif
    DescVecIt             dVIt;
    FieldDescriptionBase *pDesc;

    ReflexiveContainerType *pReflexParent =
        dynamic_cast<ReflexiveContainerType *>(_pParentType);

    if(pReflexParent != NULL)
    {
        if(pReflexParent->isInitialized() == true)
        {
            _vDescVec.reserve(               _vDescVec.size() + 
                              pReflexParent->_vDescVec.size());


            for(  dVIt  = pReflexParent->_vDescVec.begin();
                  dVIt != pReflexParent->_vDescVec.end  ();
                ++dVIt)
            {
                if(_mDescMap.find((*dVIt)->getName()) == 
                       _mDescMap.end())
                {
                    pDesc = (*dVIt)->clone();

                    _mDescMap[(*dVIt)->getName()] =
                        pDesc;
                    
                    _vDescVec.push_back(pDesc);
                }
                else
                {
                    SWARNING << "ERROR: Can't add field "
                             << "description a second time: "
                             << (*dVIt)->getName().c_str() << std::endl;
                }

            }

#if 0
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
#endif

            _bvUnmarkedOnCreate &= pReflexParent->getUnmarkedOnCreate();
        }
        else
        {
            SWARNING << "ERROR: parent not initialized "
                     << "name " << _szParentName.c_str()
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

    descIt = _mDescMap.find(desc.getName());

    if(desc.isValid())
    {
        if(descIt == _mDescMap.end())
        {
            pDesc = desc.clone();

            _mDescMap[pDesc->getName()] = pDesc;

            descVIt = std::find(_vDescVec.begin(),
                                _vDescVec.end(),
                                 pNullDesc);

            if(descVIt == _vDescVec.end())
            {
                _vDescVec.push_back(pDesc);

                returnValue = UInt32(_vDescVec.size());
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
                        << "in " << _szName.c_str() << " from "
                        << desc.getCName() << " (id:"
                        << desc.getTypeId() << ")" << std::endl;
        }
    }
    else
    {
        SWARNING << "ERROR: Invalid field description "
                    << "in " << _szName.c_str() << " from "
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

    descMIt = _mDescMap.find(pDesc->getName());

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

#define WS20 "                    "

void ReflexiveContainerType::dumpFieldInfo(void) const
{
    fprintf(stderr, "Dump type (%s) Field Info\n", this->getCName());


    for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
    {
        FieldDescriptionBase *pDesc = this->getFieldDesc(i);

        if(pDesc != NULL)
        {
            UInt32 uiTmp = 
                (_bvUnmarkedOnCreate & pDesc->getFieldMask()) == 0x0000;

            fprintf(stderr, WS20"                                  cr : %x\r", 
                    uiTmp);


            uiTmp = (pDesc->getFlags() & Field::FClusterLocal) != 0x0000;

            fprintf(stderr, WS20"                          cl : %x\r",
                    uiTmp);


            uiTmp = (pDesc->getFlags() & Field::FThreadLocal) != 0x0000;

            fprintf(stderr, WS20"                  tl : %x\r",
                    uiTmp);


            fprintf(stderr, "(%d) : %s :\r", 
                    i, 
                    pDesc->getCName());


            fprintf(stderr, "\n");
        }
        else
        {
            fprintf(stderr, "(%d) : NULL\n", i);
        }
    }
}

OSG_END_NAMESPACE
