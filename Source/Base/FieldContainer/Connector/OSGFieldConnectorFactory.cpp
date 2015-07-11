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
#include "OSGFieldConnectorFactory.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGFactoryController.h"

#include "OSGSingletonHolder.ins"

#include "OSGFieldContainer.h"

#include "OSGVecSFields.h"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(FieldConnectorFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<FieldConnectorFactoryBase>;

OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Class Variable                               */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldConnectorFactoryBase::~FieldConnectorFactoryBase(void)
{
    // At this point, the Log is already destroyed
    //SINFO << "INFO: Destroy Singleton FieldConnectorFactory" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                               Create                                    */

BasicFieldConnector *FieldConnectorFactoryBase::createConnector(
        const FieldDescriptionBase *pSrcDesc,
        const Field                *pSrc,
        const FieldDescriptionBase *pDstDesc,
              Field                *pDst        ) const
{
    BasicFieldConnector *returnValue = NULL;

    EntryMapConstIt srcIt = 
        _mConnectorMap.find(pSrcDesc->getFieldType().getId());

    if(srcIt != _mConnectorMap.end())
    {
        ConnectorMapConstIt dstIt = 
            srcIt->second->find(pDstDesc->getFieldType().getId());

        if(dstIt != srcIt->second->end() && dstIt->second != NULL)
        {
            returnValue = dstIt->second->clone(pSrc, pSrcDesc->getFieldMask(),
                                               pDst, pDstDesc->getFieldMask());
        }
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

void FieldConnectorFactoryBase::registerConnector(
    const FieldType           &oSrcType,
    const FieldType           &oDstType,
          BasicFieldConnector *pSrcToDst,
          BasicFieldConnector *pDstToSrc)
{
    // src -> dst
    {
        EntryMapConstIt srcIt = _mConnectorMap.find(oSrcType.getId());

        if(srcIt != _mConnectorMap.end())
        {
            ConnectorMapConstIt dstIt = 
                srcIt->second->find(oDstType.getId());

            if(dstIt != srcIt->second->end())
            {
                fprintf(stderr, 
                        "error conversion already registered for %s -> %s\n",
                        oSrcType.getCName(),
                        oDstType.getCName());

                delete pSrcToDst;
            }
            else
            {
                (*(srcIt->second))[oDstType.getId()] = pSrcToDst;
            }
        }
        else
        {
            ConnectorMap *tmpMap = new ConnectorMap;
            
            (*tmpMap)[oDstType.getId()] = pSrcToDst;

            _mConnectorMap[oSrcType.getId()] = tmpMap;
        }
    }

    // src -> dst
    {
        EntryMapConstIt dstIt = _mConnectorMap.find(oDstType.getId());

        if(dstIt != _mConnectorMap.end())
        {
            ConnectorMapConstIt srcIt = 
                dstIt->second->find(oSrcType.getId());

            if(srcIt != dstIt->second->end())
            {
                fprintf(stderr, 
                        "error conversion already registered for %s -> %s\n",
                        oDstType.getCName(),
                        oSrcType.getCName());

                delete pDstToSrc;
            }
            else
            {
                (*(dstIt->second))[oSrcType.getId()] = pDstToSrc;
            }
        }
        else
        {
            ConnectorMap *tmpMap = new ConnectorMap;
            
            (*tmpMap)[oSrcType.getId()] = pDstToSrc;

            _mConnectorMap[oDstType.getId()] = tmpMap;
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                 the                                     */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldConnectorFactoryBase::FieldConnectorFactoryBase(void) : 
     Inherited    ("FieldConnectorFactory"),
    _mConnectorMap(                       )
{
    FactoryController::the()->registerFactory(this);
}


bool FieldConnectorFactoryBase::initialize(void)
{
//    fprintf(stderr, "FieldConnectorFactoryBase::initialize\n");

    return true;
}


bool FieldConnectorFactoryBase::terminate(void)
{
    fprintf(stderr, "FieldConnectorFactoryBase::terminate\n");

    EntryMapIt      eIt  = _mConnectorMap.begin();
    EntryMapConstIt eEnd = _mConnectorMap.end  ();

    for(; eIt != eEnd; ++eIt)
    {
        ConnectorMapIt      cIt  = eIt->second->begin();
        ConnectorMapConstIt cEnd = eIt->second->end  ();

        for(; cIt != cEnd; ++cIt)
        {
            delete cIt->second;
            
            cIt->second = NULL;
        }

        delete eIt->second;

        eIt->second = NULL;
    }

    return true;
}


bool FieldConnectorFactoryBase::initializePendingElements(void)
{
//    fprintf(stderr, "FieldConnectorFactoryBase::initializePendingElements\n");

    return true;
}


bool FieldConnectorFactoryBase::initializeFactoryPost(void)
{
//    fprintf(stderr, "FieldConnectorFactoryBase::initializeFactoryPost\n");

    return true;
}

bool FieldConnectorFactoryBase::initializePendingElementsFactoryPost(void)
{
//    fprintf(stderr, 
//            "FieldConnectorFactoryBase::initializePendingElementsFactoryPost\n");

    return true;
}

/*-------------------------------------------------------------------------*/
/*                                 Add                                     */

OSG_END_NAMESPACE
