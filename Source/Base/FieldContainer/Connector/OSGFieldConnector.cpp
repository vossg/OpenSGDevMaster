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

/*---------------------------------------------------------------------*/
/*! \name Connection handling                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseFieldContainerConnector
    \relatesalso AttachmentContainer
 */

bool addConnection(      OSG::AttachmentContainer *pSrcContainer, 
                   const OSG::Char8               *szSrcName,
                         OSG::FieldContainer      *pDstContainer, 
                   const OSG::Char8               *szDstName    )
{
    if(pSrcContainer == NULL || szSrcName == NULL ||
       pDstContainer == NULL || szDstName == NULL  )
    {
        return false;
    }

    const FieldDescriptionBase *pSrcDesc = NULL;
    const FieldDescriptionBase *pDstDesc = NULL;

    GetFieldHandlePtr pSrcHnd = pSrcContainer->getField(szSrcName);
    GetFieldHandlePtr pDstHnd = pDstContainer->getField(szDstName);

    if(pSrcHnd != NULL && pSrcHnd->isValid() == true)
    {
        pSrcDesc = pSrcHnd->getDescription();
    }

    if(pDstHnd != NULL && pDstHnd->isValid() == true)
    {
        pDstDesc = pDstHnd->getDescription();
    }

    // check core for node
    if(pSrcDesc == NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pSrcContainer);

        if(pNode != NULL && pNode->getCore() != NULL)
        {
            pSrcHnd = pNode->getCore()->getField(szSrcName);

            if(pSrcHnd != NULL && pSrcHnd->isValid() == true)
            {
                pSrcDesc = pSrcHnd->getDescription();
            }
        }
    }

    // same here
    if(pDstDesc == NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pDstContainer);

        if(pNode != NULL && pNode->getCore() != NULL)
        {
            pDstHnd = pNode->getCore()->getField(szDstName);

            if(pDstHnd != NULL && pDstHnd->isValid() == true)
            {
                pDstDesc = pDstHnd->getDescription();
            }
        }
    }

    if(pSrcDesc == NULL || pDstDesc == NULL)
    {
        FWARNING(("addConnection: Failed to obtain field descriptions for "
                  "source container [%p] field [%s] desc [%p] - "
                  "destination container [%p] field [%s] desc [%p]\n",
                  pSrcContainer, szSrcName, pSrcDesc,
                  pDstContainer, szDstName, pDstDesc));

        return false;
    }

    const Field *pSrcField = pSrcHnd->getField();
          Field *pDstField = const_cast<Field *>(pDstHnd->getField());

    pSrcContainer = 
              dynamic_cast<AttachmentContainer *>(pSrcHnd->getContainer());

    pDstContainer = 
              dynamic_cast<AttachmentContainer *>(pDstHnd->getContainer());
          
    if(pSrcContainer == NULL || pDstContainer == NULL)
    {
        FWARNING(("addConnection: Failed to obtain field handles for "
                  "source container [%p] - destination container [%p]\n",
                  pSrcContainer, pDstContainer));

        return false;
    }

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

/*! \ingroup GrpBaseFieldContainerConnector
    \relatesalso AttachmentContainer
 */

bool subConnection(      OSG::AttachmentContainer *pSrcContainer, 
                   const OSG::Char8               *szSrcName,
                         OSG::FieldContainer      *pDstContainer, 
                   const OSG::Char8               *szDstName    )
{
    if(pSrcContainer == NULL)
    {
        return false;
    }

    
    const FieldDescriptionBase *pSrcDesc = NULL;

    GetFieldHandlePtr pSrcHnd;

    if(szSrcName != NULL)
    {
        pSrcHnd = pSrcContainer->getField(szSrcName);

        if(pSrcHnd != NULL && pSrcHnd->isValid() == true)
        {
            pSrcDesc = pSrcHnd->getDescription();
        }

        // check core for node
        if(pSrcDesc == NULL)
        {
            Node *pNode = dynamic_cast<Node *>(pSrcContainer);
            
            if(pNode != NULL && pNode->getCore() != NULL)
            {
                pSrcHnd = pNode->getCore()->getField(szSrcName);

                if(pSrcHnd != NULL && pSrcHnd->isValid() == true)
                {
                    pSrcDesc = pSrcHnd->getDescription();
                }
            }
        }
    }


    const FieldDescriptionBase *pDstDesc = NULL;

    GetFieldHandlePtr pDstHnd;

    if(pDstContainer != NULL && szDstName != NULL)
    {
        pDstHnd = pDstContainer->getField(szDstName);

        if(pDstHnd != NULL && pDstHnd->isValid() == true)
        {
            pDstDesc = pDstHnd->getDescription();
        }

        // same here
        if(pDstDesc == NULL)
        {
            Node *pNode = dynamic_cast<Node *>(pDstContainer);

            if(pNode != NULL && pNode->getCore() != NULL)
            {
                pDstHnd = pNode->getCore()->getField(szDstName);

                if(pDstHnd != NULL && pDstHnd->isValid() == true)
                {
                    pDstDesc = pDstHnd->getDescription();
                }
            }
        }
    }

    if(pSrcDesc == NULL)
    {
        FWARNING(("subConnection: Failed to obtain field description for: "
                  "source container [%p] field [%s]\n",
                  pSrcContainer, szSrcName));

        return false;
    }

    BitVector bSrcMask = TypeTraits<BitVector>::BitsClear;
    BitVector bDstMask = TypeTraits<BitVector>::BitsClear;

    if(pSrcDesc != NULL)
    {
        bSrcMask = pSrcDesc->getFieldMask();
    }
    else if(szSrcName == NULL)
    {
        bSrcMask = TypeTraits<BitVector>::BitsSet;
    }

    if(pDstDesc != NULL)
    {
        bDstMask = pDstDesc->getFieldMask();
    }
    else if(szDstName == NULL)
    {
        bDstMask = TypeTraits<BitVector>::BitsSet;
    }

    subConnector(pSrcContainer, bSrcMask,
                 pDstContainer, bDstMask);

    return false;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
