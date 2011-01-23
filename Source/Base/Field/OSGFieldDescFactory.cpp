/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldDescFactory.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGFactoryController.h"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(FieldDescFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<FieldDescFactoryBase>;

OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Class Variable                               */

//std::map<UInt32, FieldType *> *FieldDescFactory::_fieldTypeM  = NULL;

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldDescFactoryBase::~FieldDescFactoryBase(void)
{
    // At this point, the Log is already destroyed
    //SINFO << "INFO: Destroy Singleton FieldDescFactory" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                               Create                                    */

Field *FieldDescFactoryBase::createField(UInt32 typeId)
{
#if 0
    FieldType *pType = getFieldType(typeId);


    if((pType                != NULL) &&
       (pType->_createMethod != NULL))
    {
        return pType->_createMethod();
    }
    else
    {
        return NULL;
    }
#else
    return NULL;
#endif
}

Field *FieldDescFactoryBase::createField(const Char8 *szName)
{
#if 0
    FieldType *pType          = getFieldType(szName);

    if((pType                != NULL) &&
       (pType->_createMethod != NULL))
    {
        return pType->_createMethod();
    }
    else
    {
        return NULL;
    }
#else
    return NULL;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

UInt32 FieldDescFactoryBase::getNumFieldTypes(void)
{
#if 0
    if(_fieldTypeM != NULL) 
        return _fieldTypeM->size();
#endif

    return 0;
}
    
FieldType *FieldDescFactoryBase::getFieldType(const Char8 *szName)
{
#if 0
    std::map<UInt32, FieldType *>::iterator  mIt;
    FieldType                               *returnValue = NULL;
    
    if(_fieldTypeM != NULL) 
    {
        mIt = _fieldTypeM->begin();

        while(mIt != _fieldTypeM->end())
        {
            if(strcmp(szName, (*mIt).second->getCName()) == 0)
            {
                returnValue = (*mIt).second;
                break;
            }
            
            mIt++;
        }
    }

    return returnValue;
#else
    return NULL;
#endif
}

FieldType *FieldDescFactoryBase::getFieldType(UInt32 typeId)
{
#if 0
    std::map<UInt32, FieldType *>::iterator  mIt;

    if(_fieldTypeM == NULL)
        return NULL;
   
    mIt = _fieldTypeM->find(typeId);

    if(mIt != _fieldTypeM->end())
    {
        return (*mIt).second;
    }
    else
    {
        return NULL;
    }
#else
    return NULL;
#endif
}

const Char8 *FieldDescFactoryBase::getFieldTypeName(UInt32 typeId)
{
#if 0
    FieldType *pFieldType = getFieldType(typeId);

    return pFieldType ? pFieldType->getCName() : NULL;
#else
    return NULL;
#endif
}

FieldDescriptionBase *FieldDescFactoryBase::createByName(
    const Char8           *szFieldTypename,
    const Char8           *szFieldname,
          FieldEditMethod  fEditMethod,
          FieldGetMethod   fGetMethod,
          UInt32           uiFieldFlags )
{
    if(szFieldTypename == NULL)
    {
        FWARNING(("FieldDescFactory::create, no typename given\n"));

        return NULL;
    }

    FieldDescriptionBase *returnValue = NULL;
    std::string           tmpStr      = szFieldTypename;

    NameCreatorMapConstIt ncIt = _mNameCreatorMap.find(tmpStr);

    if(ncIt != _mNameCreatorMap.end())
    {
        if(ncIt->second.first)
        {
            returnValue = ncIt->second.first(szFieldname,
                                             uiFieldFlags,
                                                                     
                                             fEditMethod,
                                             fGetMethod);
        }
        else
        {
            FWARNING(("no desc creator registered for %s\n",
                      szFieldTypename));
        }
    }
    else
    {
        FWARNING(("could not find desc creator for %s\n",
                  szFieldTypename));
    }
    
    return returnValue;
}

FieldDescriptionBase *FieldDescFactoryBase::createByNameIdx(
    const Char8               *szFieldTypename,
    const Char8               *szFieldname,
          FieldIndexEditMethod fEditMethod,
          FieldIndexGetMethod  fGetMethod,
          UInt32               uiFieldFlags )
{
    if(szFieldTypename == NULL)
    {
        FWARNING(("FieldDescFactory::createIdx, no typename given\n"));

        return NULL;
    }

    FieldDescriptionBase *returnValue = NULL;
    std::string           tmpStr      = szFieldTypename;

    NameCreatorMapConstIt ncIt = _mNameCreatorMap.find(tmpStr);

    if(ncIt != _mNameCreatorMap.end())
    {
        if(ncIt->second.second)
        {
            returnValue = ncIt->second.second(szFieldname,
                                              uiFieldFlags,
                                              
                                              fEditMethod,
                                              fGetMethod);
        }
        else
        {
            FWARNING(("no desc idx creator registered for %s\n",
                      szFieldTypename));
        }
    }
    else
    {
        FWARNING(("could not find desc idx creator for %s\n",
                  szFieldTypename));
    }
    
    return returnValue;
}


FieldDescriptionBase *FieldDescFactoryBase::create(
          UInt32           uiFieldTypeId, 
    const Char8           *szFieldname,
          FieldEditMethod  fEditMethod,
          FieldGetMethod   fGetMethod,
          UInt32           uiFieldFlags )
{
    if(uiFieldTypeId >= _vCreators.size())
    {
        FWARNING(("FieldDescFactory::create, unknown type id %d (%"PRISize")\n",
                   uiFieldTypeId,
                  _vCreators.size()));

        return NULL;
    }

    FieldDescriptionBase *returnValue = NULL;

    if(_vCreators[uiFieldTypeId].first)
    {
        returnValue = _vCreators[uiFieldTypeId].first(szFieldname,
                                                      uiFieldFlags,
                                                      
                                                      fEditMethod,
                                                      fGetMethod);
    }
    else
    {
        FWARNING(("no desc creator registered for %d\n",
                  uiFieldTypeId));
    }
   
    return returnValue;
}

FieldDescriptionBase *FieldDescFactoryBase::createIdx(
          UInt32               uiFieldTypeId, 
    const Char8               *szFieldname,
          FieldIndexEditMethod fEditMethod,
          FieldIndexGetMethod  fGetMethod,
          UInt32               uiFieldFlags )
{
    if(uiFieldTypeId >= _vCreators.size())
    {
        FWARNING(("FieldDescFactory::createIdx, unknown type id %d (%"
                  PRISize")\n",

                   uiFieldTypeId,
                  _vCreators.size()));

        return NULL;
    }

    FieldDescriptionBase *returnValue = NULL;

    if(_vCreators[uiFieldTypeId].second)
    {
        returnValue = _vCreators[uiFieldTypeId].second(szFieldname,
                                                       uiFieldFlags,
                                                       
                                                       fEditMethod,
                                                       fGetMethod);
    }
    else
    {
        FWARNING(("no desc idx creator registered for %d\n",
                  uiFieldTypeId));
    }
    
    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                                 the                                     */

void FieldDescFactoryBase::registerDescription(
    const Char8                   *szFieldTypename,
          UInt32                   uiTypeId,
          FieldDescCreator         fCreator,
          IndexedFieldDescCreator  fIdxCreator    )
{
    if(szFieldTypename == NULL)
        return;

//    fprintf(stderr, "register %s (%d)\n", szFieldTypename, uiTypeId);

    std::string tmpStr = szFieldTypename;

    NameCreatorMapConstIt ncIt = _mNameCreatorMap.find(tmpStr);

    if(ncIt == _mNameCreatorMap.end())
    {
        DescCreators tmpCreators;

        tmpCreators.first  = fCreator;
        tmpCreators.second = fIdxCreator;

        _mNameCreatorMap[tmpStr] = tmpCreators;

        if(uiTypeId >= _vCreators.size())
        {
            _vCreators.resize(uiTypeId + 1);
        }

        _vCreators[uiTypeId] = tmpCreators;
    }
    else
    {
        FWARNING(("could not add second desc creator for %s\n",
                  szFieldTypename));
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldDescFactoryBase::FieldDescFactoryBase(void) : 
     Inherited      ("FieldDescFactory"),
    _mNameCreatorMap(                  ),
    _vCreators      (                  )
{
    FactoryController::the()->registerFactory(this);
}


bool FieldDescFactoryBase::initialize(void)
{
//    fprintf(stderr, "FieldDescFactoryBase::initialize\n");

    return true;
}


bool FieldDescFactoryBase::terminate(void)
{
//    fprintf(stderr, "FieldDescFactoryBase::terminate\n");

    return true;
}


bool FieldDescFactoryBase::initializePendingElements(void)
{
//    fprintf(stderr, "FieldDescFactoryBase::initializePendingElements\n");

    return true;
}


bool FieldDescFactoryBase::initializeFactoryPost(void)
{
//    fprintf(stderr, "FieldDescFactoryBase::initializeFactoryPost\n");

    return true;
}

bool FieldDescFactoryBase::initializePendingElementsFactoryPost(void)
{
//    fprintf(stderr, 
//            "FieldDescFactoryBase::initializePendingElementsFactoryPost\n");

    return true;
}

/*-------------------------------------------------------------------------*/
/*                                 Add                                     */

#if 0
void FieldDescFactoryBase::registerType(FieldType *pType)
{
}

void FieldDescFactoryBase::addType(FieldType *pType)
{
    if(pType == NULL)
        return;

    if(getFieldType(pType->getId()) != NULL)
        return;

    if(_fieldTypeM == NULL)
        _fieldTypeM = new std::map<UInt32, FieldType *>();

    (*_fieldTypeM)[pType->getId()] = pType;
}
#endif

OSG_END_NAMESPACE
