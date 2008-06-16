/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#include "OSGAttachmentContainer.h"
#include "OSGFieldConnector.h"
#include "OSGConnectorAttachment.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

bool addConnection(AttachmentContainer *pSrcContainer, const Char8 *szSrcName,
                   FieldContainer      *pDstContainer, const Char8 *szDstName)
{
    if(pSrcContainer == NULL || szSrcName == NULL ||
       pDstContainer == NULL || szDstName == NULL  )
    {
        return false;
    }

    FieldDescriptionBase *pSrcDesc = 
        pSrcContainer->getFieldDescription(szSrcName);

    FieldDescriptionBase *pDstDesc = 
        pDstContainer->getFieldDescription(szDstName);

    // check core for node
    if(pSrcDesc == NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pSrcContainer);

        if(pNode != NULL && pNode->getCore() != NULL)
        {
            pSrcDesc = pNode->getCore()->getFieldDescription(szSrcName);
        }
    }

    // same here
    if(pDstDesc == NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pDstContainer);

        if(pNode != NULL && pNode->getCore() != NULL)
        {
            pDstDesc = pNode->getCore()->getFieldDescription(szDstName);

            pDstContainer = pNode->getCore();
        }
    }

    if(pSrcDesc == NULL || pDstDesc == NULL)
    {
        FWARNING(("Failed desc %p %p\n", pSrcDesc, pDstDesc));

        return false;
    }

    const Field *pSrcField = pSrcContainer->getField(szSrcName)->getField();

          Field *pDstField = 
              const_cast<Field *>(
                  pDstContainer->getField(szDstName)->getField());

          
    BasicFieldConnector *pConn = pSrcDesc->createConnector(pSrcField,
                                                           pDstDesc,
                                                           pDstField);

    if(pConn != NULL)
    {
        pConn->setTargetContainer(pDstContainer);

        addConnector(pSrcContainer, pConn);
    }

    return true;
}

OSG_END_NAMESPACE
