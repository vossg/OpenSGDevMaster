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

#include <boost/bind.hpp>

#include <OSGConfig.h>

#include "OSGConnectorAttachment.h"
#include "OSGAttachmentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGConnectorAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGConnectorAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConnectorAttachment::initMethod(InitPhase ePhase)
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

ConnectorAttachment::ConnectorAttachment(void) :
     Inherited   (), 
    _vConnections()
{
}

ConnectorAttachment::ConnectorAttachment(const ConnectorAttachment &source) :
     Inherited   (source), 
    _vConnections(      )
{
}

ConnectorAttachment::~ConnectorAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ConnectorAttachment::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ConnectorAttachment::dump(      UInt32    ,
                               const BitVector ) const
{
    SLOG << "Dump ConnectorAttachment NI" << std::endl;
}

void ConnectorAttachment::addConnection (BasicFieldConnector *pConnector)
{
    if(pConnector != NULL)
    {
        _vConnections.push_back(pConnector);
    }
}

void ConnectorAttachment::processChanged(FieldContainer      *pObj, 
                                         BitVector            whichField)
{
    ConnectionStore::const_iterator cIt  = _vConnections.begin();
    ConnectionStore::const_iterator cEnd = _vConnections.end  ();

    while(cIt != cEnd)
    {
        if((*cIt)->match(whichField) == true)
        {
            (*cIt)->process();
        }

        ++cIt;
    }
}

void ConnectorAttachment::targetDestroyed(FieldContainer      *pObj, 
                                          BitVector            whichField)
{
    if(whichField == 0x0000)
    {
        this->removeConnectionTo(pObj);
    }
}

bool ConnectorAttachment::hasConnectionTo(const FieldContainer *pDst) const
{
    bool returnValue = false;

    ConnectionStore::const_iterator cIt  = _vConnections.begin();
    ConnectionStore::const_iterator cEnd = _vConnections.end  ();

    while(cIt != cEnd)
    {
        if((*cIt)->getDst() == pDst)
        {
            returnValue = true;
            break;
        }

        ++cIt;
    }

    return returnValue;
}

void ConnectorAttachment::removeConnectionTo(const FieldContainer *pDst)
{
    ConnectionStore::iterator       cIt  = _vConnections.begin();
    ConnectionStore::const_iterator cEnd = _vConnections.end  ();

    while(cIt != cEnd)
    {
        if((*cIt)->getDst() == pDst)
        {
            delete (*cIt);

            cIt = _vConnections.erase(cIt);

            cEnd = _vConnections.end();
        }
        else
        {
            ++cIt;
        }
    }
}

void ConnectorAttachment::removeConnections(      BitVector       bSrcMask,
                                            const FieldContainer *pDst,
                                                  BitVector       bDstMask)
{
    ConnectionStore::iterator       cIt  = _vConnections.begin();
    ConnectionStore::const_iterator cEnd = _vConnections.end  ();

    ConnectionCount mConnCount;

    this->countConnections(mConnCount);

    while(cIt != cEnd)
    {
        if((*cIt)->match(bSrcMask, pDst, bDstMask) == true)
        {
            --(mConnCount[(*cIt)->getDst()]);

            delete (*cIt);

            cIt = _vConnections.erase(cIt);

            cEnd = _vConnections.end();
        }
        else
        {
            ++cIt;
        }
    }

    ConnectionCount::const_iterator ccIt  = mConnCount.begin();
    ConnectionCount::const_iterator ccEnd = mConnCount.end  ();

    while(ccIt != ccEnd)
    {
        if(ccIt->second == 0)
        {
            ccIt->first->subChangedFunctor(
                boost::bind(&ConnectorAttachment::targetDestroyed, 
                            this, 
                            _1, 
                            _2));
        }

        ++ccIt;
    }
}

void ConnectorAttachment::countConnections(ConnectionCount &mCount)
{
    ConnectionStore::const_iterator cIt  = _vConnections.begin();
    ConnectionStore::const_iterator cEnd = _vConnections.end  ();

    ConnectionCount::iterator ccIt;

    while(cIt != cEnd)
    {
        ccIt = mCount.find((*cIt)->getDst());

        if(ccIt == mCount.end())
        {
            mCount[(*cIt)->getDst()] = 1;
        }
        else
        {
            ++(ccIt->second);
        }

        ++cIt;
    }
    
}

bool ConnectorAttachment::unlinkParent(FieldContainer * const pParent,
                                       UInt16           const parentFieldId)
{
    pParent->subChangedFunctor(
        boost::bind(&ConnectorAttachment::processChanged, 
                    this, 
                    _1, 
                    _2));
    
    return Inherited::unlinkParent(pParent, parentFieldId);
}

void ConnectorAttachment::resolveLinks(void)
{
    for(UInt32 i = 0; i < _vConnections.size(); ++i)
    {
        FieldContainer *pDst = _vConnections[i]->getDst();

        pDst->subChangedFunctor(
            boost::bind(&ConnectorAttachment::targetDestroyed, 
                        this, 
                        _1, 
                        _2));

        delete _vConnections[i];
    }

    _vConnections.clear();
}

/*---------------------------------------------------------------------*/
/*! \name Connector handling                                           */
/*! \{                                                                 */

/*! \ingroup GrpBaseFieldContainerConnector
    \relatesalso AttachmentContainer
 */

void addConnector(OSG::AttachmentContainer *pContainer,
                  OSG::BasicFieldConnector *pConn     )
{
    if(pContainer == NULL)
    {
        FFATAL(("addConnector: no container?!?"));
        return;
    }

    if(pConn == NULL)
    {
        FFATAL(("addConnector: no connector?!?"));
        return;
    }

    ConnectorAttachmentUnrecPtr pCA = NULL;

    Attachment          *att = pContainer->findAttachment(
        ConnectorAttachment::getClassType().getGroupId());

    if(att == NULL)
    {
        pCA = ConnectorAttachment::create();

        pContainer->addChangedFunctor(
            boost::bind(&ConnectorAttachment::processChanged, 
                        pCA.get(), 
                        _1, 
                        _2),
            "");

        pContainer->addAttachment(pCA);
    }
    else
    {
        pCA = dynamic_cast<ConnectorAttachment *>(att);

        if(pCA == NULL)
        {
            FFATAL(("setName: Attachment is not castable to Conn?!?"));
            return;
        }
    }

    if(pCA->hasConnectionTo(pConn->getDst()) == false)
    {
        FieldContainer *pDst = pConn->getDst();

        pDst->addChangedFunctor(
            boost::bind(&ConnectorAttachment::targetDestroyed, 
                        pCA.get(), 
                        _1, 
                        _2),
            "");
    }

    pCA->addConnection(pConn);
}

/*! \ingroup GrpBaseFieldContainerConnector
    \relatesalso AttachmentContainer
 */

void subConnector(OSG::AttachmentContainer *pSrcContainer, 
                  OSG::BitVector            bSrcMask,
                  OSG::FieldContainer      *pDstContainer, 
                  OSG::BitVector            bDstMask)
{
    if(pSrcContainer == NULL)
    {
        FFATAL(("subConnector: no container?!?"));
        return;
    }

    ConnectorAttachmentUnrecPtr pCA = NULL;

    Attachment          *att = pSrcContainer->findAttachment(
        ConnectorAttachment::getClassType().getGroupId());

    pCA = dynamic_cast<ConnectorAttachment *>(att);
    
    if(pCA != NULL)
    {
        pCA->removeConnections(bSrcMask, pDstContainer, bDstMask);
    }
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
